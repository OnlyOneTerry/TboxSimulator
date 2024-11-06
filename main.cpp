#include "TBoxWidget.h"
#include <QApplication>

#include <QTimer>
#include <QUuid>
#include <QTime>
#include <QCryptographicHash>
#include <QString>
#include <QDateTime>
#include <QObject>

#include <thread>
#include <stdio.h>
#include <mosquitto.h>
#include "string.h"
#include "stdio.h"

extern "C"{
#include "iwall_pki.h"
#include "iwall_error.h"
#include "iwall_tls.h"
}

#include <openssl/sha.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#include <curl/curl.h>
#include <unistd.h>
#include <vector>
#include <mutex>
#include <fstream>
#include <iomanip>
#include <csignal>


#include "./protoBuf/connection.pb.h"
#include "./protoBuf/location.pb.h"
#include "./protoBuf/status.pb.h"
#include "./protoBuf/envelope.pb.h"
#include "./protoBuf/message.pb.h"
#include "./protoBuf/fault.pb.h"
#include "./protoBuf/alert.pb.h"
#include "./protoBuf/event.pb.h"
#include "./protoBuf/marks.pb.h"

/*
// 浩万测试环境
static void *hAppHandle = NULL;
static char *pGlbBaseUrl = "https://10.10.9.79:8080";
static int   iGlbChainFlag = 112; // rsa
static char *pGlbAppFilePath = "./svkd/";

static unsigned char pucContainerName[] = "Device_identification";
static unsigned int uiContainerNameLen = 21;

static unsigned char pucPinInfo[] = "1234567887654321";
static unsigned int uiPinInfoLen = 16;
*/

struct mosquitto *mosq = NULL;

#if 1
QString base_vin = "HORWINMOTOR000000";
QString hw_vin = "HORWINMOTOR000000";
QString hw_tbsn = "HORWIN00000";
QString hw_iccid = "59826410375920400000";
QString hw_imei = "926385014700000";

static std::string vid = "f59f8440a0455f8e8e1e02b79ffa7ea4";
static std::string tbsn = "HORWIN00000";
static std::string iccid = "59826410375920400000";
static std::string imei = "926385014700000";
#else

QString base_vin = "HORWINMOTOR000012";
QString hw_vin = "HORWINMOTOR000012";
QString hw_tbsn = "HORWIN00012";
QString hw_iccid = "59826410375920400012";
QString hw_imei = "926385014700012";

static std::string vid = "469ad05856c35dbc92f7aeb9e6362c86";
static std::string tbsn = "HORWIN00012";
static std::string iccid = "59826410375920400012";
static std::string imei = "926385014700012";
#endif

static StatusNS::Status g_status;
static FaultNS::Fault  g_fault;
static AlertNS::Alert g_alert;
static EventNS::Event g_event;
static ControlNS::Control g_control;
int g_report_interval = 3;
QString callback_info ;
static bool isControlResped = true;
std::mutex control_mutex;
std::string controlSerialString;
std::string diagnoseSerialString;
std::mutex diagnose_mutex;
static bool isDiagnoseResped = true;
int g_encrypted_data_len = 0;
static MarksNS::Marks g_marks;
int g_index = 0 ;

void time_out_publish_message(struct mosquitto* mosq,std::string vid,int interval);
void parseStatus(std::string msgString);
void reportAlertToTsp(struct mosquitto* mosq,std::string vid);
void reportFaultToTsp(struct mosquitto* mosq ,std::string vid);
void reportEventToTsp(struct mosquitto* mosq ,std::string vid);
void reportEventEngineOnOff(struct mosquitto* mosq ,std::string vid,bool on);
void reportStatusToTsp(struct mosquitto* mosq,std::string vid);
void reportOtaToTsp(struct mosquitto* mosq,std::string vid);
void parseAlert(std::string msgString);
void parseFault(std::string msgString);
void parseEvent(std::string msgString);
void parseControlDown(std::string msgString);
bool publishControlResp(ControlNS::ControlCommand ctrlCmd,std::string taskId);
bool publishOtaResp(OTANS::OTAResponse otaResp);
bool publishLockResp(LockNS::LockOpt lockOpt,std::string taskId);
void parseOta(std::string msgString);
bool publishDiagnoseResp(struct mosquitto* mosq,std::string vid,DiagnoseNS::Diagnose* diagnose);
std::string encryptLocation(std::string location);
std::string decryptLocation(std::string location);
void reportGearPos(struct mosquitto* mosq,std::string vid,StatusNS::GearPosition gear);
enum class SubScribeType
{
    SUBSCRIBE_CONNECTION,
    SUBSCRIBE_CONTROL,
    SUBSCRIBE_OTA,
    SUBSCRIBE_LOCK,
    SUBSCRIBE_DIAGNOSE,
    SUBSCRIBE_TEST,
    SUBSCRIBE_STATUS,
    SUBSCRIBE_ALERT,
    SUBSCRIBE_FAULT,
    SUBSCRIBE_GB32960,
    SUBSCRIBE_EVENT
};

std::map<SubScribeType,std::string> subscribe_topic_map;

void initTopics(std::string vid)
{
    subscribe_topic_map.insert(std::make_pair<SubScribeType,std::string>(SubScribeType::SUBSCRIBE_CONNECTION,"/tbox/connection/"+vid+"/resp"));
    subscribe_topic_map.insert(std::make_pair<SubScribeType,std::string>(SubScribeType::SUBSCRIBE_CONTROL,"/tbox/control/"+vid+"/req"));
    subscribe_topic_map.insert(std::make_pair<SubScribeType,std::string>(SubScribeType::SUBSCRIBE_OTA,"/tbox/ota/"+vid+"/req"));
    subscribe_topic_map.insert(std::make_pair<SubScribeType,std::string>(SubScribeType::SUBSCRIBE_LOCK,"/tbox/lock/"+vid+"/req"));
    subscribe_topic_map.insert(std::make_pair<SubScribeType,std::string>(SubScribeType::SUBSCRIBE_DIAGNOSE,"/tbox/diagnose/"+vid+"/req"));
    subscribe_topic_map.insert(std::make_pair<SubScribeType,std::string>(SubScribeType::SUBSCRIBE_TEST,"topic_LKLA6L7L9RA797270"));
    subscribe_topic_map.insert(std::make_pair<SubScribeType,std::string>(SubScribeType::SUBSCRIBE_STATUS,"/tbox/status/"+vid+"/v"));
    subscribe_topic_map.insert(std::make_pair<SubScribeType,std::string>(SubScribeType::SUBSCRIBE_ALERT,"/tbox/alert/"+vid+"/v"));
    subscribe_topic_map.insert(std::make_pair<SubScribeType,std::string>(SubScribeType::SUBSCRIBE_FAULT,"/tbox/fault/"+vid+"/v"));
    subscribe_topic_map.insert(std::make_pair<SubScribeType,std::string>(SubScribeType::SUBSCRIBE_GB32960,"/tbox/fault/"+vid+"/v"));
    subscribe_topic_map.insert(std::make_pair<SubScribeType,std::string>(SubScribeType::SUBSCRIBE_EVENT,"/tbox/event/"+vid+"/resp"));
}

void hex_print(const unsigned char *val, unsigned int len) {
    if (val == NULL) { return; }
    for (int i = 0; i < len; ++i) {
        printf("%02x", val[i]);
    }
    printf("\n");
}

// 使用 Mosquito 建立 mqtts 通讯
static int run = 1;
void handle_signal(int s) {
    run = 0;
}

std::string sha256_hash(const char* data){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256,data,strlen(data));
    SHA256_Final(hash,&sha256);

    std::string has_hex;
    for(int i = 0;i<SHA256_DIGEST_LENGTH;i++)
    {
        char hex_byte[3];
        sprintf(hex_byte,"%02x",hash[i]);
        has_hex += hex_byte;
    }

    return has_hex;
}

std::string calculate_sha256_hash(const char* data){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256,data,strlen(data));
    SHA256_Final(hash,&sha256);

    std::string has_hex;
    for(int i = 0;i<SHA256_DIGEST_LENGTH;i++)
    {
        char hex_byte[3];
        sprintf(hex_byte,"%02x",hash[i]);
        has_hex += hex_byte;
    }

    return has_hex;
}

QString md5Encryption(QString& str)
{
    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(str.toLocal8Bit());
    QString md5Hash = md5.result().toHex();
    return md5Hash;
}

bool subscribeDiagnoseReq(struct mosquitto *mosq,std::string vid)
{
    // 发布消息
    int rv = mosquitto_subscribe(mosq,NULL,std::string("/tbox/diagnose/"+vid+"/req").c_str(),2);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"status failed to publish"<<std::endl;
        return false;
    }
    return true;
}

bool subscribeLockReq(struct mosquitto* mosq,std::string vid)
{
    // 发布消息
    int rv = mosquitto_subscribe(mosq,NULL,std::string("/tbox/lock/"+vid+"/req").c_str(),2);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"status failed to publish"<<std::endl;
        return false;
    }
    return true;
}

bool subscribeOtaReq(struct mosquitto* mosq,std::string vid)
{
    // 发布消息
    int rv = mosquitto_subscribe(mosq,NULL,std::string("/tbox/ota/"+vid+"/req").c_str(),2);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"status failed to publish"<<std::endl;
        return false;
    }
    return true;
}

bool parseDiagnose(std::string msgString)
{
    //parse message
    std::string  envelopStr = msgString;

    EvelopeNS::Envelope envelop;
    envelop.ParseFromString(envelopStr);
    std::cout<<"envelop info version :"<<envelop.version()<<"\n"<<" time: "<<envelop.time()<<"\n source : "<<envelop.source()<<"\n"<<" vid : "<<envelop.vid()<<"\n";

    MessageNS::Message msg = envelop.msg();
    std::cout<<"msg info aid :"<<msg.aid()<<"\n";
    {
        DiagnoseNS::Diagnose* diagnose = msg.mutable_diagnose();
        std::string taskId = diagnose->taskid();
        DiagnoseNS::DiagnoseOpt diagnoseOpt = diagnose->diagnoseopt();
        switch (diagnoseOpt) {
        case DiagnoseNS::DiagnoseOpt::CLEAN_DTC:
        {
            DiagnoseNS::CleanDTC cleanDtc = diagnose->cleandtc();
            {
                int ecuSize = cleanDtc.ecu_size();
                for(int i = 0;i<ecuSize;i++)
                {
                    std::cout<<i<<" ecu "<<cleanDtc.ecu(i)<<std::endl;
                }

                std::cout<<" diagnoseCode is : "<<cleanDtc.diagnoseresultcode();
            }
        }
            break;
        case DiagnoseNS::DiagnoseOpt::READ_DID:
        {
            DiagnoseNS::ReadDID readDid = diagnose->readdid();
            {
                int didSize = readDid.readdidcontent_size();
                for(int i = 0;i<didSize;i++)
                {
                    DiagnoseNS::DIDContent didContent = readDid.readdidcontent(i);

                    std::cout<<"didcontent ecus : "<<didContent.ecu()<<std::endl;

                    int diagDidSize = didContent.diagdid_size();

                    for(int j = 0;j<diagDidSize;j++)
                    {
                        DiagnoseNS::DiagDID diagDid = didContent.diagdid(j);

                        std::cout<<"did is : "<<diagDid.did()<<std::endl;

                        std::cout<<"didValue is :"<<diagDid.didvalue()<<std::endl;
                    }
                }

                DiagnoseNS::DiagnoseResultCode diagResultCode = readDid.diagnoseresultcode();

                std::cout<<"diagResult code : "<<diagResultCode<<std::endl;


            }
        }
            break;
        case DiagnoseNS::DiagnoseOpt::WRITE_DID:
        {
            DiagnoseNS::WriteDID writeDid = diagnose->writedid();
            {
                int writeDidSize = writeDid.writedidcontent_size();
                for(int i = 0; i< writeDidSize;i++)
                {
                    DiagnoseNS::DIDContent didContent = writeDid.writedidcontent(i);
                    std::cout<<"didcontent ecus : "<<didContent.ecu()<<std::endl;

                    int diagDidSize = didContent.diagdid_size();

                    for(int j = 0;j<diagDidSize;j++)
                    {
                        DiagnoseNS::DiagDID diagDid = didContent.diagdid(j);

                        std::cout<<"did is : "<<diagDid.did()<<std::endl;

                        std::cout<<"didValue is :"<<diagDid.didvalue()<<std::endl;
                    }
                }

                DiagnoseNS::DiagnoseResultCode diagResultCode = writeDid.diagnoseresultcode();

                std::cout<<"diagResult code : "<<diagResultCode<<std::endl;

            }
        }
            break;
        case DiagnoseNS::DiagnoseOpt::ECU_ADDR:
        {
            DiagnoseNS::DiagEcuAddr diagEcuAddr = diagnose->diagecuaddr();
            {
                int ecuAddrSize = diagEcuAddr.ecuaddr_size();
                for(int i =0;i<ecuAddrSize;i++)
                {
                    DiagnoseNS::EcuAddr ecuAddr = diagEcuAddr.ecuaddr(i);
                    std::cout<<"ecuAddrTx is :"<<ecuAddr.ecuaddrtx()<<" ecuAddrRx is :"<<ecuAddr.ecuaddrrx()<<std::endl;
                }

                int ecuAddrDtcSize =diagEcuAddr.ecuaddrdtc_size();
                for(int j = 0;j<ecuAddrDtcSize;j++)
                {
                    DiagnoseNS::EcuAddrDTC ecuAddrDtc = diagEcuAddr.ecuaddrdtc(j);
                    DiagnoseNS::EcuAddr ecuAddr = ecuAddrDtc.ecuaddr();
                    std::cout<<"ecuAddrTx is :"<<ecuAddr.ecuaddrtx()<<" ecuAddrRx is :"<<ecuAddr.ecuaddrrx()<<std::endl;

                    int diagnoseCodeSize = ecuAddrDtc.diagnosecode_size();

                    for(int j = 0;j<diagnoseCodeSize;j++)
                    {
                        std::cout<<j<<" diagnoseCode is : "<<ecuAddrDtc.diagnosecode(j)<<std::endl;
                    }
                }

                DiagnoseNS::DiagnoseResultCode diagResultCode = diagEcuAddr.diagnoseresultcode();

                std::cout<<" diagnoseCode is : "<<diagResultCode<<std::endl;

            }
        }
            break;
        case DiagnoseNS::DiagnoseOpt::READ_DTC:
        {
            DiagnoseNS::ReadDTC readDtc = diagnose->readdtc();
            {
                int ecuSize = readDtc.ecu_size();
                for(int i = 0;i<ecuSize;i++)
                {
                    std::cout<<i<<" ecu "<<readDtc.ecu(i)<<std::endl;
                }

                int ecuDtcSize = readDtc.ecudtc_size();

                for(int i = 0;i<ecuDtcSize;i++)
                {
                    DiagnoseNS::EcuDTC ecuDtc = readDtc.ecudtc(i);
                    std::cout<<i<<" ecu "<<ecuDtc.ecu()<<std::endl;

                    int diagnoseCodeSize = ecuDtc.diagnosecode_size();

                    for(int j = 0;j<diagnoseCodeSize;j++)
                    {
                        std::cout<<j<<" diagnoseCode is : "<<ecuDtc.diagnosecode(j)<<std::endl;
                    }
                }
            }
        }
            break;
        case DiagnoseNS::DiagnoseOpt::INVALID:
            break;
        default:
            break;
        }
        publishDiagnoseResp(mosq,vid,diagnose);
    }
}

void publishDiagnoseTest()
{
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::DIAGNOSE);
        {
            DiagnoseNS::Diagnose *diagnose = msg->mutable_diagnose();
            QUuid uuid = QUuid::createUuid();
            diagnose->set_taskid(uuid.toString().toStdString());
            /*
            diagnose->set_diagnoseopt(::DiagnoseNS::DiagnoseOpt::ECU_ADDR);

            DiagnoseNS::DiagEcuAddr* diaEcuAddr = diagnose->mutable_diagecuaddr();

            DiagnoseNS::EcuAddr* ecuAddr1 = diaEcuAddr->add_ecuaddr();
            ecuAddr1->set_ecuaddrrx(0x1111);
            ecuAddr1->set_ecuaddrtx(0x1129);


            DiagnoseNS::EcuAddr* ecuAddr2 = diaEcuAddr->add_ecuaddr();
            ecuAddr2->set_ecuaddrrx(0x1112);
            ecuAddr2->set_ecuaddrtx(0x1119);

            DiagnoseNS::EcuAddr* ecuAddr3 = diaEcuAddr->add_ecuaddr();
            ecuAddr3->set_ecuaddrrx(0x1114);
            ecuAddr3->set_ecuaddrtx(0x1139);
           */
            /*
            diagnose->set_diagnoseopt(::DiagnoseNS::DiagnoseOpt::CLEAN_DTC);

             DiagnoseNS::CleanDTC* cleanDtc = diagnose->mutable_cleandtc();

             cleanDtc->add_ecu(DiagnoseNS::Ecus::Abs);
             cleanDtc->add_ecu(DiagnoseNS::Ecus::Bms);
             cleanDtc->add_ecu(DiagnoseNS::Ecus::Cddc);
            */

            /*
            diagnose->set_diagnoseopt(::DiagnoseNS::DiagnoseOpt::READ_DTC );

            DiagnoseNS::ReadDTC * readDtc = diagnose->mutable_readdtc();

            readDtc->add_ecu(DiagnoseNS::Ecus::Abs);
            readDtc->add_ecu(DiagnoseNS::Ecus::Bms);
            readDtc->add_ecu(DiagnoseNS::Ecus::Cddc);
            */


            diagnose->set_diagnoseopt(::DiagnoseNS::DiagnoseOpt::READ_DID);

            DiagnoseNS::ReadDID * readDid = diagnose->mutable_readdid();

            DiagnoseNS::DIDContent* didContent = readDid->add_readdidcontent();
            didContent->set_ecu(DiagnoseNS::Ecus::Abs);

            DiagnoseNS::DiagDID* diagDid = didContent->add_diagdid();
            diagDid->set_did(1);
            char dv = '3';
            diagDid->set_didvalue(&dv);

            DiagnoseNS::DiagDID* diagDid1 = didContent->add_diagdid();
            diagDid1->set_did(2);
            dv ='4';
            diagDid1->set_didvalue(&dv);


            DiagnoseNS::DIDContent* didContent1 = readDid->add_readdidcontent();
            didContent->set_ecu(DiagnoseNS::Ecus::Abs);

            DiagnoseNS::DiagDID* diagDid11 = didContent1->add_diagdid();
            diagDid11->set_did(11);
            dv ='5';
            diagDid11->set_didvalue(&dv);

        }
    }

    std::string diagnoseStr = envelop.SerializeAsString();
    int len = diagnoseStr.length();

    // 发布消息
    int rv = mosquitto_publish(mosq,NULL,std::string("/tbox/diagnose/"+vid+"/req").c_str(),len,diagnoseStr.c_str(),2,false);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"status failed to publish"<<std::endl;
    }

}

bool publishDiagnoseResp(struct mosquitto* mosq,std::string vid,DiagnoseNS::Diagnose* diagnose)
{
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::DIAGNOSE);
        {
            DiagnoseNS::Diagnose *diagnoseRes = msg->mutable_diagnose();
            diagnoseRes->set_taskid(diagnose->taskid());
            diagnoseRes->set_diagnoseopt(diagnose->diagnoseopt());

            switch (diagnose->diagnoseopt()) {
            case DiagnoseNS::DiagnoseOpt::CLEAN_DTC:
            {
                std::cout<<"send clean dtc "<<std::endl;
                DiagnoseNS::CleanDTC* cleanDtc = diagnoseRes->mutable_cleandtc();
                cleanDtc->set_diagnoseresultcode(::DiagnoseNS::DiagnoseResultCode::DID_READ_NOT_EXIST);
            }
                break;
            case DiagnoseNS::DiagnoseOpt::READ_DID:
            {
                std::cout<<"send read did "<<std::endl;
                DiagnoseNS::ReadDID* readDid = diagnoseRes->mutable_readdid();
                {
                    int didSize = readDid->readdidcontent_size();
                    readDid->set_diagnoseresultcode(::DiagnoseNS::DiagnoseResultCode::DID_READ_NOT_EXIST);
                }
            }
                break;
            case DiagnoseNS::DiagnoseOpt::WRITE_DID:
            {
                std::cout<<"send write did "<<std::endl;
                DiagnoseNS::WriteDID* writeDid = diagnoseRes->mutable_writedid();
                {
                    writeDid->set_diagnoseresultcode(::DiagnoseNS::DiagnoseResultCode::ECU_NOT_MATCH);
                }
            }
                break;
            case DiagnoseNS::DiagnoseOpt::ECU_ADDR:
            {
                std::cout<<"send ecu addr "<<std::endl;
                DiagnoseNS::DiagEcuAddr* diagEcuAddrResp = diagnoseRes->mutable_diagecuaddr();

                DiagnoseNS::DiagEcuAddr* diagEcuAddr = diagnose->mutable_diagecuaddr();

                int ecuAddrDtcSize = diagEcuAddr->ecuaddr_size();

                for(int i = 0;i<ecuAddrDtcSize;i++)
                {
                    DiagnoseNS::EcuAddr ecuAddr = diagEcuAddr->ecuaddr(i);

                    DiagnoseNS::EcuAddrDTC* ecuAddDtcResp = diagEcuAddrResp->add_ecuaddrdtc();

                    DiagnoseNS::EcuAddr* ecuAddrResp = ecuAddDtcResp->mutable_ecuaddr();
                    ecuAddrResp->set_ecuaddrrx(ecuAddr.ecuaddrrx());
                    ecuAddrResp->set_ecuaddrtx(ecuAddr.ecuaddrtx());

                    ecuAddDtcResp->add_diagnosecode("0x1001");
                    ecuAddDtcResp->add_diagnosecode("0x1002");
                    ecuAddDtcResp->add_diagnosecode("0x1003");
                }

                diagEcuAddrResp->set_diagnoseresultcode(::DiagnoseNS::DiagnoseResultCode::ECU_ADDR_NO_RESP);
            }
                break;
            case DiagnoseNS::DiagnoseOpt::READ_DTC:
            {
                std::cout<<"send read dtc "<<std::endl;
                DiagnoseNS::ReadDTC* readDtcResp = diagnoseRes->mutable_readdtc();

                DiagnoseNS::ReadDTC* readDtc  = diagnose->mutable_readdtc();

                int ecusSize = readDtc->ecu_size();

                for(int i = 0;i<ecusSize;i++)
                {
                    DiagnoseNS::EcuDTC* ecuDtsResp = readDtcResp->add_ecudtc();
                    ecuDtsResp->set_ecu(readDtc->ecu(i));

                    ecuDtsResp->add_diagnosecode("0x1001");
                    ecuDtsResp->add_diagnosecode("0x1002");

                }
                readDtcResp->set_diagnoseresultcode(::DiagnoseNS::DiagnoseResultCode::SUCCESS);

            }
                break;
            case DiagnoseNS::DiagnoseOpt::INVALID:
                break;
            default:
                break;
            }
        }
    }

    std::string diagnoseStr = envelop.SerializeAsString();
    int len = diagnoseStr.length();

    // 发布消息
    int rv = mosquitto_publish(mosq,NULL,std::string("/tbox/diagnose/"+vid+"/resp").c_str(),len,diagnoseStr.c_str(),2,false);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"status failed to publish"<<std::endl;
        return false;
    }

    return true;

}

bool publishControlResponse(struct mosquitto *mosq,std::string vid,ControlNS::Control& ctrl)
{
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::CONTROL);
        {
            ControlNS::Control *control = msg->mutable_control();
            control->CopyFrom(ctrl);

            ControlNS::Parameters para = control->para();

            switch(control->controlcommand())
            {
            case ControlNS::ControlCommand::CONTROL_ENGINE_COMMAND:
            {
                ControlNS::ControlEnginePara enginePara = para.controlenginepara();
                ControlNS::EngineOpt engineOpt = enginePara.enginstart();
                std::cout<<"engineOPt "<<engineOpt<<std::endl;

                switch (engineOpt) {
                case ControlNS::EngineOpt::START:
                {
                    std::cout<<"control engine start"<<std::endl;
                }
                    break;
                case ControlNS::EngineOpt::STOP:
                {
                    std::cout<<"control engine stop"<<std::endl;
                }
                    break;
                default:
                    break;
                }
            }
                break;
            case ControlNS::ControlCommand::CONTROL_FIND_CAR_COMMAND:
            {
                ControlNS::ControlFindCarPara findCarPara = para.controlfindcarpara();
                ControlNS::FindCarOpt findCarOpt = findCarPara.findcaropt();
                switch (findCarOpt) {
                case ControlNS::FindCarOpt::LIGHT:
                    std::cout<<"control find car by light"<<std::endl;
                    break;
                case ControlNS::FindCarOpt::HORN:
                    std::cout<<"control find car by horn"<<std::endl;
                    break;
                case ControlNS::FindCarOpt::LIGHT_HORN:
                    std::cout<<"control find car by light and horn"<<std::endl;
                    break;
                default:
                    break;
                }
            }
                break;
            case ControlNS::ControlCommand::ENABLE_GEAR_REPORT:

                break;
            case ControlNS::ControlCommand::CONTROL_GET_POSITION:

                break;
            case ControlNS::ControlCommand::CONTROL_GET_TIER_PRESSURE:
            {
                ControlNS::ControlGetTPMSPara getTmpPara = para.controlgettmpspara();
                StatusNS::TpmsInfo tmp = getTmpPara.tpmsinfo();

                std::cout<<"trie front temp "<<tmp.fronttiertemp()<<std::endl;
                std::cout<<"tire rear temp "<<tmp.reartiretemp()<<std::endl;
                std::cout<<"tire front press"<<tmp.fronttirepressure()<<std::endl;
                std::cout<<"tire rear press "<<tmp.reartirepressure()<<std::endl;
            }

                break;
            case ControlNS::ControlCommand::CONTROL_TAKE_PARKING_PHOTO:

                break;
            case ControlNS::ControlCommand::IN_VALID:

            default:

                break;
            }

        }
    }

    std::string controlStr = envelop.SerializeAsString();
    int len = controlStr.length();

    // 发布消息
    int rv = mosquitto_publish(mosq,NULL,std::string("/tbox/control/"+vid+"/resp").c_str(),len,controlStr.c_str(),2,false);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"status failed to publish"<<std::endl;
        return false;
    }
    return true;
}

bool publishControlResp(struct mosquitto *mosq,std::string vid,ControlNS::ControlCommand ctrlCmd,std::string taskId)
{
    std::cout<<"-------publish control resp-------"<<std::endl;
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::CONTROL);
        {
            ControlNS::Control *control = msg->mutable_control();
            control->CopyFrom(g_control);
            control->set_taskid(taskId);
            control->set_controlcommand(ctrlCmd);
            ControlNS::ControlResponse* contrlResp = control->mutable_controlresponse();
            ControlNS::Parameters* param = control->mutable_para();


            switch(ctrlCmd)
            {
            case ControlNS::ControlCommand::CONTROL_ENGINE_COMMAND:
            {
                std::cout<<"send engine result "<<contrlResp->controlengineresponse().result()<<std::endl;
            }
                break;
            case ControlNS::ControlCommand::CONTROL_FIND_CAR_COMMAND:
            {
                std::cout<<"send find car result "<<contrlResp->controlfindcarresponse().result()<<std::endl;
            }
                break;
            case ControlNS::ControlCommand::ENABLE_GEAR_REPORT:
            {
                std::cout<<"send enable gear report result "<<contrlResp->controlgearreportresponse().result()<<std::endl;
            }
                break;
            case ControlNS::ControlCommand::CONTROL_GET_POSITION:
            {
                std::cout<<"send get position result "<<contrlResp->controlgetpositionresponse().result()<<std::endl;

                ControlNS::ControlGetPositionPara* getPositionPara = param->mutable_controlgetpositionpara();

                std::string* loc = getPositionPara->mutable_location();
                *loc = encryptLocation(*loc);
                LocationNS::Location location ;
                location.ParseFromString(*loc);

                std::cout<<"altitude is :"<<location.altitude()<<std::endl;
                std::cout<<"angle is :"<<location.angle()<<std::endl;
                std::cout<<"hemisphere is :"<<location.hemisphere()<<std::endl;
                std::cout<<"satname is :"<<location.satnumber()<<std::endl;
                std::cout<<"speed is :"<<location.speed()<<std::endl;
                std::cout<<"valid is :"<<location.valid()<<std::endl;
                std::cout<<"timestamp is :"<<location.timestamp()<<std::endl;
                std::cout<<"longitude is :"<<location.longitude()<<std::endl;

                std::string encrytion_loc = encryptLocation(*loc);
                *loc = encrytion_loc;
            }
                break;
            case ControlNS::ControlCommand::CONTROL_GET_TIER_PRESSURE:
            {
                std::cout<<"send get tire press result "<<contrlResp->controlgettpmsresponse().result()<<std::endl;
                ControlNS::ControlGetTPMSPara tpmPara = param->controlgettmpspara();
                StatusNS::TpmsInfo tpmInfo = tpmPara.tpmsinfo();
                std::cout<<"front pressure is :"<<tpmInfo.fronttirepressure()<<std::endl;
                std::cout<<"front temperature is :"<<tpmInfo.fronttiertemp()<<std::endl;
                std::cout<<"rear pressure is :"<<tpmInfo.reartirepressure()<<std::endl;
                std::cout<<"rear temperature is :"<<tpmInfo.reartiretemp()<<std::endl;

            }
                break;
            case ControlNS::ControlCommand::CONTROL_HEAT_HANDLEBAR:
            {
                std::cout<<"send get heat handlerbar result "<<contrlResp->controlheathandlebarresponse().result()<<std::endl;


            }
                break;
            case ControlNS::ControlCommand::CONTROL_HEAT_RESERVE:
            {
                std::cout<<"send get heat reserve result "<<contrlResp->controlheatreserveresponse().result()<<std::endl;

            }
                break;
            case ControlNS::ControlCommand::CONTROL_HEAT_SEAT:
            {
                std::cout<<"send get heat seat result "<<contrlResp->controlheatseatresponse().result()<<std::endl;

            }
                break;
            {

            }
            case ControlNS::ControlCommand::CONTROL_TAKE_PARKING_PHOTO:
            {
                std::cout<<"send get take paking photo result "<<contrlResp->controltakeparkingphotoresponse().result()<<std::endl;
            }
                break;
            case ControlNS::ControlCommand::CONTROL_GET_SIGNAL_INTENSITY:
            {
                std::cout<<"send get signal intensity result "<<contrlResp->controltakeparkingphotoresponse().result()<<std::endl;

            }
                break;
            case ControlNS::ControlCommand::CONTROL_GET_APN_NAME:
            {
                std::cout<<"send get apn name result "<<contrlResp->controlgetapnnameresponse().result()<<std::endl;
                ControlNS::ControlAPNNamePara* apnPara = param->mutable_controlapnnamepara();
                int size = apnPara->names_size();
                for(int i = 0;i<size;i++)
                {
                    std::cout<<"channel is "<<apnPara->names(i).channel()<<" apn is :"<<apnPara->names(i).apn()<<std::endl;
                }

            }
                break;
            case ControlNS::ControlCommand::IN_VALID:
                break;
            case ControlNS::ControlCommand::CONTROL_GET_ECU_VERSION:
            {
                ControlNS::ControlGetECUVersionPara* ecuPara = param->mutable_controlgetecuversionpara();
                int size = ecuPara->info_size();
                for(int i = 0;i<size;i++)
                {
                    ControlNS::ECUVersion ecuVersion = ecuPara->info(i);
                }
            }
                break;
            default:

                break;
            }


        }
    }

    std::string controlStr = envelop.SerializeAsString();
    int len = controlStr.length();

    // 发布消息
    int rv = mosquitto_publish(mosq,NULL,std::string("/tbox/control/"+vid+"/resp").c_str(),len,controlStr.c_str(),2,false);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"status failed to publish"<<std::endl;
        return false;
    }
    return true;
}

bool subscribeControlReq(struct mosquitto *mosq,std::string vid)
{
    // 发布消息
    int rv = mosquitto_subscribe(mosq,NULL,std::string("/tbox/control/"+vid+"/req").c_str(),2);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"status failed to publish"<<std::endl;
        return false;
    }
    return true;
}

void parseControlDown(std::string msgString)
{
    //parse message
    std::string  envelopStr = msgString;
    std::string taskId;
    EvelopeNS::Envelope envelop;
    envelop.ParseFromString(envelopStr);
    std::cout<<"envelop info version :"<<envelop.version()<<"\n"<<" time: "<<envelop.time()<<"\n source : "<<envelop.source()<<"\n"<<" vid : "<<envelop.vid()<<"\n";

    MessageNS::Message msg = envelop.msg();
    std::cout<<"msg info aid :"<<msg.aid()<<std::endl;
    {
        ControlNS::Control* control = msg.mutable_control();
        taskId = control->taskid();
        uint32_t command = control->command();
        std::cout<<"control command :"<<command<<std::endl;
        ControlNS::ControlCommand ctrlCmd = control->controlcommand();
        std::cout<<"ctrl cmd : "<<ctrlCmd<<std::endl;
        int paraType = control->paratype();
        std::cout<<"para type is :"<<paraType<<std::endl;
        ControlNS::Parameters para = control->para();

        switch(ctrlCmd)
        {
        case ControlNS::ControlCommand::CONTROL_ENGINE_COMMAND:
        {
            ControlNS::ControlEnginePara enginePara = para.controlenginepara();
            ControlNS::EngineOpt engineOpt = enginePara.enginstart();
            std::cout<<"engineOPt "<<engineOpt<<std::endl;

            switch (engineOpt) {
            case ControlNS::EngineOpt::START:
            {
                std::cout<<"control engine start"<<std::endl;
            }
                break;
            case ControlNS::EngineOpt::STOP:
            {
                std::cout<<"control engine stop"<<std::endl;
            }
                break;
            default:
                break;
            }
        }
            break;
        case ControlNS::ControlCommand::CONTROL_FIND_CAR_COMMAND:
        {
            ControlNS::ControlFindCarPara findCarPara = para.controlfindcarpara();
            ControlNS::FindCarOpt findCarOpt = findCarPara.findcaropt();
            switch (findCarOpt) {
            case ControlNS::FindCarOpt::LIGHT:
                std::cout<<"control find car by light"<<std::endl;
                break;
            case ControlNS::FindCarOpt::HORN:
                std::cout<<"control find car by horn"<<std::endl;
                break;
            case ControlNS::FindCarOpt::LIGHT_HORN:
                std::cout<<"control find car by light and horn"<<std::endl;
                break;
            default:
                break;
            }
        }
            break;
        case ControlNS::ControlCommand::ENABLE_GEAR_REPORT:
        {
            for(int i = 2;i<5;i++)
            {
                sleep(1);
                reportGearPos(mosq,vid,(StatusNS::GearPosition)i);
            }
        }
            break;
        case ControlNS::ControlCommand::CONTROL_GET_POSITION:

            break;
        case ControlNS::ControlCommand::CONTROL_GET_TIER_PRESSURE:

            break;
        case ControlNS::ControlCommand::CONTROL_TAKE_PARKING_PHOTO:

            break;
        case ControlNS::ControlCommand::IN_VALID:
            break;
        case ControlNS::ControlCommand::CONTROL_SET_FREQUENCY:
        {
            ControlNS::ControlSetFrequencyPara frequencyPara = para.controlsetfrequencypara();
            g_report_interval = frequencyPara.frequency();
        }
            break;
        default:

            break;
        }

        if(ctrlCmd!= ControlNS::ControlCommand::ENABLE_GEAR_REPORT){
            publishControlResp(mosq,vid,ctrlCmd,taskId);
        }
    }
}

void publishControlTest()
{
    std::cout<<"-------------control test-------------"<<std::endl;
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::CONTROL);
        {
            ControlNS::Control *control = msg->mutable_control();
            QUuid id = QUuid::createUuid();
            std::string  uuid = id.toString().toStdString();
            control->set_taskid(uuid);
            /*
#if 1
            control->set_controlcommand(ControlNS::ControlCommand::CONTROL_ENGINE_COMMAND);
            control->set_command(0x9001);
            control->set_paratype(0x0010);
            ControlNS::Parameters* param = control->mutable_para();
            ControlNS::ControlEnginePara* engineParam = param->mutable_controlenginepara();
            engineParam->set_enginstart(ControlNS::EngineOpt::STOP);
#else
            control->set_controlcommand(ControlNS::ControlCommand::CONTROL_FIND_CAR_COMMAND);
            control->set_command(0x9002);
            control->set_paratype(0x0011);
            ControlNS::Parameters* param = control->mutable_para();
            ControlNS::ControlFindCarPara * findCarParam = param->mutable_controlfindcarpara();
            findCarParam->set_findcaropt(::ControlNS::FindCarOpt::LIGHT);

#endif
*/

            /*
#if 1
            control->set_controlcommand(ControlNS::ControlCommand::CONTROL_GET_TIER_PRESSURE);
            control->set_command(0x9016);
            control->set_paratype(0x0012);
#else
            control->set_controlcommand(ControlNS::ControlCommand::CONTROL_HEAT_HANDLEBAR);
            control->set_command(0x900B);
            control->set_paratype(0x0018);

            ControlNS::Parameters* param = control->mutable_para();

            ControlNS::ControlHeatHandleBarPara* handleBarpara = param->mutable_controlheathandlebarpara();
            handleBarpara->set_level(2);
            handleBarpara->set_switch_(ControlNS::SWITCH::OFF);
            handleBarpara->set_type(ControlNS::ControlHeatHandleBarPara_HandleType_LEFT);


            //             ControlNS::ControlHeatReservePara* reservePara = param->mutable_controlheatreservepara();
            //             reservePara->set_appointment(10);
            //             reservePara->set_reservation(ControlNS::ControlCommand::CONTROL_HEAT_HANDLEBAR);
            //             ControlNS::ControlHeatHandleBarPara* reserverHandlePara = reservePara->mutable_heathandlebarpara();
            //             reserverHandlePara->set_level(2);
            //             reserverHandlePara->set_switch_(ControlNS::SWITCH::ON);
            //             reserverHandlePara->set_type(ControlNS::ControlHeatHandleBarPara_HandleType::ControlHeatHandleBarPara_HandleType_LEFT  );


#endif
*/

            /*

            control->set_controlcommand(ControlNS::ControlCommand::CONTROL_SET_POLYGON_FENCE);
            control->set_command(0x9018);
            control->set_paratype(0x0015);
            ControlNS::Parameters* param1 = control->mutable_para();
            ControlNS::ControlSetPolygonFencePara* polyParam = param1->mutable_controlsetpolygonfencepara();
            polyParam->set_end(110);
            polyParam->set_start(80);
            polyParam->set_speed(120);

            for(int i = 0;i<10;i++)
            {
                ControlNS::Point* point = polyParam->add_points();
                point->set_hemisphere(2+i);
                point->set_latitude(3+i);
                point->set_hemisphere(4*i);
            }
          */
            /*
            control->set_controlcommand(ControlNS::ControlCommand::CONTROL_GET_APN_NAME);
            control->set_command(0x9012);
            control->set_paratype(0x001A);
            */
            // control->set_controlcommand(ControlNS::ControlCommand::CONTROL_GET_POSITION);
            // control->set_command(0x9005);

            //control->set_controlcommand(ControlNS::ControlCommand::ENABLE_GEAR_REPORT);
            control->set_controlcommand(ControlNS::ControlCommand::ENABLE_GEAR_REPORT);

            //control->set_controlcommand(ControlNS::ControlCommand::CONTROL_SET_FREQUENCY);

        }
    }

    std::string controlStr = envelop.SerializeAsString();
    int len = controlStr.length();

    // 发布消息
    int rv = mosquitto_publish(mosq,NULL,std::string("/tbox/control/"+vid+"/req").c_str(),len,controlStr.c_str(),2,false);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"status failed to publish"<<std::endl;
        return ;
    }
    return ;
}

bool  parseRemoteLock(std::string msgString)
{
    //parse message
    std::string  envelopStr = msgString;

    EvelopeNS::Envelope envelop;
    envelop.ParseFromString(envelopStr);
    std::cout<<"envelop info version :"<<envelop.version()<<"\n"<<" time: "<<envelop.time()<<"\n source : "<<envelop.source()<<"\n"<<" vid : "<<envelop.vid()<<"\n";

    MessageNS::Message msg = envelop.msg();
    std::cout<<"msg info aid :"<<msg.aid()<<"\n";
    {
        LockNS::Lock lock = msg.lock();
        std::cout<<"task id :"<<lock.taskid()<<std::endl;
        LockNS::LockRequest request = lock.lockrequest();
        std::string taskId = lock.taskid();
        LockNS::LockOpt lockOpt = request.lockopt();
        switch (lockOpt) {
        case LockNS::LockOpt::LOCK_REQ:
            std::cout<<"lock opt lock req"<<std::endl;

            break;
        case LockNS::LockOpt::UNLOCK_REQ:
            std::cout<<"lock opt unlock req"<<std::endl;

            break;
        case LockNS::LockOpt::QUERY_REQ:
            std::cout<<"lock opt query req"<<std::endl;

            break;
        case LockNS::LockOpt::INVALID:
            std::cout<<"lock opt INVALID"<<std::endl;
            break;
        default:
            break;
        }

        publishLockResp(lockOpt,taskId);
    }

    return true;
}

bool publishLockResp(LockNS::LockOpt lockOpt,std::string taskId)
{
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::TBOX);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::LOCK);
        LockNS::Lock* lock = msg->mutable_lock();
        lock->set_taskid(taskId);
        LockNS::LockResponse* lockResponse = lock->mutable_lockresponse();
        switch (lockOpt) {
        case LockNS::LockOpt::LOCK_REQ:
            lockResponse->set_lockstatus(::LockNS::LockStatus::LOCK);
            std::cout<<"lock req :"<<::LockNS::LockStatus::LOCK<<std::endl;
            break;
        case LockNS::LockOpt::UNLOCK_REQ:
            lockResponse->set_lockstatus(::LockNS::LockStatus::UNLOCK );
            std::cout<<"unlock req :"<<::LockNS::LockStatus::UNLOCK<<std::endl;
            break;
        case LockNS::LockOpt::QUERY_REQ:
            lockResponse->set_lockstatus(::LockNS::LockStatus::LOCK);
            std::cout<<"query req :"<<::LockNS::LockStatus::LOCK<<std::endl;
            break;
        default:
            break;
        }

        lockResponse->set_resultcode(::LockNS::LockResultCode::SUCCESS);
        std::cout<<"lock result code :"<<::LockNS::LockResultCode::SUCCESS<<std::endl;
    }

    std::string lockRespStr = envelop.SerializeAsString();
    int len = lockRespStr.length();

    // 发布消息
    int rv = mosquitto_publish(mosq,NULL,std::string("/tbox/lock/"+vid+"/resp").c_str(),len,lockRespStr.c_str(),2,false);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"failed to publish"<<std::endl;
    }
    else
    {
        std::cout<<"sucess to response to lock request "<<std::endl;
    }
    return true;
}

void publishLockTest()
{
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::TBOX);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::LOCK);
        LockNS::Lock* lock = msg->mutable_lock();
        QUuid id = QUuid::createUuid();
        std::string  uuid = id.toString().toStdString();
        lock->set_taskid(uuid);
        std::cout<<"lock task id is: "<<uuid<<std::endl;
        LockNS::LockRequest* lockReq = lock->mutable_lockrequest();
        lockReq->set_lockopt(::LockNS::LockOpt::UNLOCK_REQ);
    }

    std::string lockRespStr = envelop.SerializeAsString();
    int len = lockRespStr.length();

    // 发布消息
    int rv = mosquitto_publish(mosq,NULL,std::string("/tbox/lock/"+vid+"/req").c_str(),len,lockRespStr.c_str(),2,false);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"failed to publish"<<std::endl;
    }
}

bool subscribeConnectResp(struct mosquitto *mosq,std::string vid)
{
    // 订阅主题
    int rv = mosquitto_subscribe(mosq, NULL,std::string("/tbox/connection/"+vid+"/resp").c_str(), 2);
    if (rv != MOSQ_ERR_SUCCESS) {
        printf("mosquitto_subscribe fail, fail code: %d\n", rv);
        return false;
    }
    return true;
}

bool publishConnectReq(struct mosquitto *mosq,std::string vid,std::string tbsn,std::string imei,std::string iccid)
{
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);

    envelop.set_source(::EvelopeNS::Source::TBOX);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::CONNECTION);
        {
            std::string tokenStr = vid+tbsn+imei+iccid;
            const char* vid0 = tokenStr.c_str();                    ;
            //Hash运算
            std::string token = calculate_sha256_hash(vid0);
            std::cout<<"token is :"<<token<<std::endl;
            ConnectionNS::Connection *con = msg->mutable_connection();
            QUuid id = QUuid::createUuid();
            std::string  uuid = id.toString().toStdString();
            con->set_taskid(uuid);
            con->set_token(token);
            con->set_connectionoption(ConnectionNS::ConnectionOption::LOGIN_REQ);
            ConnectionNS::VehicleSN *vehicSn = con->mutable_vehiclesn();
            vehicSn->set_vid(vid);
            vehicSn->set_tboxsn(tbsn);
            vehicSn->set_iccid(iccid);
            vehicSn->set_imei(imei);
            con->set_connectioninfo("connect to tsp");
        }
    }
    std::string connectStr = envelop.SerializeAsString();
    int len = connectStr.length();

    // 发布消息
    int rv = mosquitto_publish(mosq,NULL,std::string("/tbox/connection/"+vid+"/req").c_str(),len,connectStr.c_str(),2,false);
    if(rv!=MOSQ_ERR_SUCCESS)
    {
        std::cout<<"failed to publish"<<std::endl;
    }
    return true;
}

void on_connect(struct mosquitto *mosq, void *obj, int rc) {
    printf("mosquitto_connect::on_connect = %d\n", rc);

    if(publishConnectReq(mosq,vid,hw_tbsn.toStdString(),hw_imei.toStdString(),hw_iccid.toStdString()))
    {
        std::cout<<"connect tsp success !"<<"\n";
    }
    else
    {
        std::cout<<"failed to connect tsp"<<"\n";
    }

    reportEventEngineOnOff(mosq,vid,true);
}

void on_disconnect(struct mosquitto *mosq, void *obj, int rc) {
    printf("mosquitto_connect::on_disconnect = %d\n", rc);
    run = rc;
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {
    // printf("got message payload=\'%d, \n %s\' \nfor topic=\'%s\'\n",
    //      message->payloadlen, (char *) message->payload, message->topic);

    std::string msgString = std::string((char*)message->payload);

    //parse receive message
    std::string  topic_str = std::string((char*)message->topic);

    std::map<SubScribeType,std::string>::iterator iter = subscribe_topic_map.begin();
    for(; iter!= subscribe_topic_map.end(); iter++)
    {
        if(topic_str == iter->second){
            SubScribeType subType = iter->first;
            switch (subType)
            {
            case SubScribeType::SUBSCRIBE_CONNECTION:
                std::cout<<" ------- connection topic -----"<<"\n";
                break;
            case SubScribeType::SUBSCRIBE_CONTROL:
            {
                //std::cout<<" ------- control topic -----"<<std::endl;
                parseControlDown(msgString);
                control_mutex.lock();
                isControlResped = false;
                controlSerialString = msgString;
                control_mutex.unlock();
            }
                break;
            case SubScribeType::SUBSCRIBE_DIAGNOSE:
            {
                //std::cout<<" ------- diagnose topic -----"<<"\n";
                parseDiagnose(msgString);
                diagnose_mutex.lock();
                isDiagnoseResped = false;
                diagnoseSerialString = msgString;
                diagnose_mutex.unlock();
            }
                break;
            case SubScribeType::SUBSCRIBE_LOCK:
                std::cout<<" ------- lock topic -----"<<"\n";
                parseRemoteLock(msgString);
                break;
            case SubScribeType::SUBSCRIBE_OTA:
                std::cout<<" ------- ota topic -----"<<"\n";
                break;
            case SubScribeType::SUBSCRIBE_TEST:
                std::cout<<" ------- test topic -----"<<"\n";
                break;
            case SubScribeType::SUBSCRIBE_STATUS:
            {
                std::cout<<" ------- STATUS topic -----"<<"\n";
                parseStatus(msgString);
            }
                break;
            case SubScribeType::SUBSCRIBE_ALERT:
            {
                std::cout<<" ------- ALERT topic -----"<<"\n";
                parseAlert(msgString);
            }
                break;
            case SubScribeType::SUBSCRIBE_FAULT:
            {
                std::cout<<" ------- FAULT topic -----"<<"\n";
                parseFault(msgString);
            }
                break;
            case SubScribeType::SUBSCRIBE_EVENT:
            {
                std::cout<<" ------- EVENT topic -----"<<"\n";
                parseEvent(msgString);
            }
                break;
            }
        }
    }
}

void on_log_callback(struct mosquitto *mosq, void *obj, int level, const char *str) {
    //printf("mosquitto_log::on_log = %s\n", str);
}

bool configMqttEnv(std::string vid)
{
    mosquitto_lib_init();
    mosq = mosquitto_new(vid.c_str(), true, NULL);
    std::cout<<"client id :"<<vid<<std::endl;
    if (mosq == NULL) {
        printf("mosquitto new fail.\n");
        return false;
    }

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);
    mosquitto_log_callback_set(mosq, on_log_callback);
    mosquitto_message_callback_set(mosq, message_callback);

    mosquitto_username_pw_set(mosq,"hw_test ","hw_test");
    int rv = mosquitto_connect_async(mosq, "10.10.9.78", 1883, 9);
    //192.168.8.94
    //int rv = mosquitto_connect_async(mosq, "192.168.8.94", 1883, 9);

    if (rv != MOSQ_ERR_SUCCESS) {
        printf("mosquitto_connect_async fail, fail code: %d\n", rv);
        return  false;
    }
    else
    {
        printf("connect server success !\n");
        return true;
    }
}
/*
bool configTlsEnv()
{
    int rv = mosquitto_tls_opts_set(mosq, 0x00, NULL, NULL);
    if (rv != MOSQ_ERR_SUCCESS) {
        printf("mosquitto_tls_opts_set fail, fail code: %d\n", rv);
        return false;
    }

    rv = mosquitto_tls_opts_set_cert_and_privatekey(
                mosq,
                hAppHandle,
                pucContainerName,
                uiContainerNameLen,
                pucPinInfo,
                uiPinInfoLen);

    if (rv != IW_R_SUCCESS) {
        printf("IW_GetSSLContext fail, fail code: %d\n", rv);
        return false;
    }

    return true;
}
*/

void loopMqttEnv()
{
    while (run) {
        int rv = mosquitto_loop(mosq, -1, 1);
        if (run && rv) {
            printf("connection error! rc=%d\n", rv);
            sleep(10);
            break;
            // mosquitto_reconnect(mosq);
        }
    }
}

int Mosquito_mqtts(std::string vid){

    initTopics(vid);
    if(!configMqttEnv(vid)) return 0;
    //if(!configTlsEnv()) return 0;

    subscribeConnectResp(mosq,vid);

    subscribeControlReq(mosq,vid);

    //subscribeDiagnoseReq(mosq,vid);

     subscribeLockReq(mosq,vid);
    // 订阅主题
    /*
    int rv = mosquitto_subscribe(mosq,NULL,std::string("/tbox/status/"+vid+"/v").c_str(),0);
    if (rv != MOSQ_ERR_SUCCESS) {
        // printf("mosquitto_subscribe /tbox/status/b847ac7f9bb7a47d6e3aa3aa812c5e02/v fail, fail code: %d\n", rv);
    }

    rv = mosquitto_subscribe(mosq,NULL,std::string("/tbox/alert/"+vid+"/v").c_str(),0);
    if (rv != MOSQ_ERR_SUCCESS) {
        printf("mosquitto_subscribe /tbox/alert/b847ac7f9bb7a47d6e3aa3aa812c5e02/v fail, fail code: %d\n", rv);
    }

    rv = mosquitto_subscribe(mosq,NULL,std::string("/tbox/fault/"+vid+"/v").c_str(),0);
    if (rv != MOSQ_ERR_SUCCESS) {
        printf("mosquitto_subscribe /tbox/fault/b847ac7f9bb7a47d6e3aa3aa812c5e02/v fail, fail code: %d\n", rv);
    }

    rv = mosquitto_subscribe(mosq,NULL,std::string("/tbox/event/"+vid+"/v").c_str(),0);
    if (rv != MOSQ_ERR_SUCCESS) {
        printf("mosquitto_subscribe /tbox/event/b847ac7f9bb7a47d6e3aa3aa812c5e02/v fail, fail code: %d\n", rv);
    }


    rv = mosquitto_subscribe(mosq,NULL,std::string("/tbox/event/"+vid+"/resp").c_str(),0);
    if (rv != MOSQ_ERR_SUCCESS) {
        //printf("mosquitto_subscribe /tbox/status/b847ac7f9bb7a47d6e3aa3aa812c5e02/v fail, fail code: %d\n", rv);
    }
    */
    return 0;
}
/*
void configureCrt()
{
    int rv = IW_InitService(&hAppHandle, pGlbAppFilePath, pGlbBaseUrl, iGlbChainFlag);
    printf("IW_InitService: %02x\n", rv);
    unsigned char ucCertificate[4096] = {0};
    unsigned int  uiCertificateLen = 4096;
    // 检测 TLS 证书是否可用
    rv = IW_CheckCertificateKeyMatcher(
                hAppHandle,
                pucContainerName,
                uiContainerNameLen,
                pucPinInfo, //设备口令
                uiPinInfoLen);//设备口令长度
    printf("IW_CheckCertificateKeyMatcher: %02x\n", rv);
    if (rv != IW_R_SUCCESS) {
        // 申请用户证书
        //生成RSA密钥对
        rv = IW_GenRsaKeyPair(
                    hAppHandle,
                    pucContainerName,
                    uiContainerNameLen,
                    pucPinInfo,
                    uiPinInfoLen,
                    2048,
                    SGD_KEYUSAGE_SIGN,
                    0);
        if (rv != IW_R_SUCCESS) {
            printf("IW_GenKeyPair error, error code: %02x\n", rv);
        } else {
            printf("IW_GenKeyPair Success\n");
        }

        unsigned char ucPublicKey[1024] = {0};
        unsigned int uiPublicKeyLen = 1024;
        //获取RSA公钥
        rv = IW_GetRsaPublicKey(
                    hAppHandle,
                    pucContainerName,
                    uiContainerNameLen,
                    1,
                    ucPublicKey,
                    &uiPublicKeyLen);
        if (rv != IW_R_SUCCESS) {
            printf("IW_GetRsaPublicKey error, error code: %02x\n", rv);
        } else {
            printf("IW_GetRsaPublicKey Success\n");
            hex_print(ucPublicKey, uiPublicKeyLen);
        }
        // 车架号 SN 号 测试号，正式环境需采用真实号码，平台会进行校验。
        const char *pcVin = "123456";
        const char *pcSN  = "123456";

        char hexVin[65] = {0};
        unsigned char ucVinHash[32] = {0};
        unsigned int uiVinHashLen   = 32;
        //Hash运算
        rv = IW_Hash(SGD_SHA256, (unsigned char *)pcVin, strlen(pcVin), ucVinHash, &uiVinHashLen);
        if (rv != IW_R_SUCCESS) {
            printf("IW_Hash error, error code: %02x\n", rv);
        } else {
            printf("IW_Hash SHA256 Success\n");
            hex_print(ucVinHash, uiVinHashLen);
        }
        for (int i = 0; i < uiVinHashLen; ++i) {
            sprintf(hexVin + 2 * i, "%.2x", ucVinHash[i]);
        }
        SGD_NAME_INFO nameInfo = {0};
        strcpy(nameInfo.dn_c,   "CN");
        strcpy(nameInfo.dn_s,   "Beijing");
        strcpy(nameInfo.dn_l,   "Beijing");
        strcpy(nameInfo.dn_o,   "Haowan");
        strcpy(nameInfo.dn_ou,  "Haowan CA");
        strcpy(nameInfo.dn_sn,  hexVin);
        strcpy(nameInfo.dn_cn,  pcSN);
        strcpy(nameInfo.dn_dc1, "cdc_generic_tls");
        strcpy(nameInfo.dn_dc2, "cdc");
        strcpy(nameInfo.dn_dc3, "vehicle");
        unsigned char ucDerCertificateRequest[4096] = {0};
        unsigned int uiDerCertificateRequestLen = 4096;
        //生成证书请求文件
        rv = IW_GenerateCertificateSigningRequest(
                    hAppHandle,
                    pucContainerName,
                    uiContainerNameLen,
                    pucPinInfo,
                    uiPinInfoLen,
                    &nameInfo,
                    ucDerCertificateRequest,
                    &uiDerCertificateRequestLen);
        if (rv != IW_R_SUCCESS) {
            printf("IW_GenerateCertificateSigningRequest fail, fail code: %02x\n", rv);
        } else {
            printf("IW_GenerateCertificateSigningRequest Success\n");
            hex_print(ucDerCertificateRequest, uiDerCertificateRequestLen);
        }
        //请求用户证书
        rv = IW_GetUserCertificateFromServerByCsr(
                    hAppHandle,
                    pGlbBaseUrl,
                    ucDerCertificateRequest,
                    uiDerCertificateRequestLen,
                    pucContainerName,
                    uiContainerNameLen,
                    ucCertificate,
                    &uiCertificateLen);
        if (rv != IW_R_SUCCESS) {
            printf("IW_GetUserCertificateFromServerByCsr fail, fail code: %02x\n", rv);
        } else {
            printf("IW_GetUserCertificateFromServerByCsr success.\n");
            hex_print(ucCertificate, uiCertificateLen);
        }
    }
}*/

static int inty = 121406920;
static int latitude_min = 30*1000000;
static int latitude_max = 90*1000000;
static int longitude_min = 110*1000000;
static int longitude_max = 130*1000000;

static int mark_num = 2*1000000;
static double deltx = (latitude_max-latitude_min)/mark_num;
static double delty = (longitude_max-longitude_min)/mark_num;
static int move_times = 10;

void reportStatusToTsp(struct mosquitto* mosq, std::string vid)
{
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::STATUS);
        {
            {
                StatusNS::Status *status = msg->mutable_status();
                //update location
                std::string location = g_status.tboxskinfo().location();
                StatusNS::Status temp_status;
                temp_status.CopyFrom(g_status);
#if 0
                //generate location and time dynamically
                LocationNS::Location location_obj;
                location_obj.ParseFromString(location);
                location_obj.set_latitude(31143210);
                location_obj.set_longitude(inty);
                location_obj.set_hemisphere(17);
                //inty+=10000;

                std::cout<<"location latitude "<<location_obj.latitude()<<std::endl;
                std::cout<<"location longitude "<<location_obj.longitude()<<std::endl;
                std::cout<<"location hemisphere "<<location_obj.hemisphere()<<std::endl;
                location = location_obj.SerializeAsString();
                std::string location1 = encryptLocation(location);
                temp_status.mutable_tboxskinfo()->set_location(location1);

#else
                //int speed = rand()%120+60;
                //temp_status.mutable_hmiinfo()->set_speed(speed);

                int marksize = g_marks.loaction_size();
                std::cout<<"mark size is :"<<marksize<<std::endl;

                //                for(int i = 0;i<marksize;i++)
                //                {
                //                    LocationNS::Location loc ;
                //                    loc.ParseFromString(g_marks.loaction(i));
                //                    std::cout<<"o location latitude "<<loc.latitude()<<std::endl;
                //                    std::cout<<"o location longitude "<<loc.longitude()<<std::endl;
                //                    std::cout<<"o location hemisphere "<<loc.hemisphere()<<std::endl;
                //                }

                static int mark_index = 0;
                if(mark_index<marksize)
                {
#if 0
                    LocationNS::Location location_obj;
                    location_obj.ParseFromString(location);

                    location_obj.set_latitude(latitude_min+deltx*mark_index);
                    location_obj.set_longitude(longitude_min+g_index*delty);
                    location_obj.set_hemisphere(17);
                    std::cout<<"location latitude "<<location_obj.latitude()<<std::endl;
                    std::cout<<"location longitude "<<location_obj.longitude()<<std::endl;
                    std::cout<<"location hemisphere "<<location_obj.hemisphere()<<std::endl;
                    std::string serialLocation = location_obj.SerializeAsString();
                    std::string location1 = encryptLocation(serialLocation);
                    temp_status.mutable_tboxskinfo()->set_location(location1);
#else
                    LocationNS::Location location_obj;
                    location_obj.ParseFromString(location);

                    LocationNS::Location location_obj2;
                    location_obj2.ParseFromString(g_marks.loaction(mark_index));
                    location_obj.set_latitude(location_obj2.latitude());
                    location_obj.set_longitude(location_obj2.longitude());
                    location_obj.set_hemisphere(location_obj2.hemisphere());
                    temp_status.mutable_hmiinfo()->set_speed(location_obj2.speed());
                    std::cout<<"location latitude "<<location_obj.latitude()<<std::endl;
                    std::cout<<"location longitude "<<location_obj.longitude()<<std::endl;
                    std::cout<<"location hemisphere "<<location_obj.hemisphere()<<std::endl;
                    std::string serialLocation = location_obj.SerializeAsString();
                    std::string location1 = encryptLocation(serialLocation);
                    temp_status.mutable_tboxskinfo()->set_location(location1);
#endif
                }
                else
                {
                    reportEventEngineOnOff(mosq,vid,false);

                    LocationNS::Location location_obj;
                    location_obj.ParseFromString(location);

                    LocationNS::Location location_obj2;
                    location_obj2.ParseFromString(g_marks.loaction(marksize-1));
                    location_obj.set_latitude(location_obj2.latitude());
                    location_obj.set_longitude(location_obj2.longitude());
                    location_obj.set_hemisphere(location_obj2.hemisphere());
                    std::cout<<"location latitude "<<location_obj.latitude()<<std::endl;
                    std::cout<<"location longitude "<<location_obj.longitude()<<std::endl;
                    std::cout<<"location hemisphere "<<location_obj.hemisphere()<<std::endl;
                    std::string serialLocation = location_obj.SerializeAsString();
                    std::string location1 = encryptLocation(serialLocation);
                    temp_status.mutable_tboxskinfo()->set_location(location1);
                }
                mark_index++;
#endif
                //-----------------------------------------//
                status->CopyFrom(temp_status);
            }
        }
    }

    std::string statusStr = envelop.SerializeAsString();
    // 发布消息
    int len = statusStr.size();
    std::cout<<"serialize status string length is :"<<len<<std::endl;
    mosquitto_publish(mosq,NULL,std::string("/tbox/status/"+vid+"/v").c_str(),statusStr.size(),statusStr.c_str(),0,false);
}

void parseStatus(std::string statusString)
{
    //parse message
    std::string  envelopStr = statusString;

    EvelopeNS::Envelope envelop;
    envelop.ParseFromString(envelopStr);
    std::cout<<"envelop info version :"<<envelop.version()<<"\n"<<" time: "<<envelop.time()<<"\n source : "<<envelop.source()<<"\n"<<" vid : "<<envelop.vid()<<"\n";

    MessageNS::Message msg = envelop.msg();
    std::cout<<"msg info aid :"<<msg.aid()<<"\n";
    {
        StatusNS::HmiInfo hmiInfo = msg.status().hmiinfo();
        std::cout<<"hmiinfo odoMetro is :"<<hmiInfo.odometro()<<"\n";
        std::cout<<"hmiinfo enduratnceMileage is :"<<hmiInfo.endurancemileage()<<"\n";
        std::cout<<"hmiinfo speed is :"<<hmiInfo.speed() <<"\n";
        std::cout<<"hmiinfo revSpeed is :"<<hmiInfo.revspeed() <<"\n";
    }

    {
        StatusNS::BmsInfo bmsSkInfo = msg.status().bmsinfo();

        std::cout<<"bmSkinfo odoMetro is :"<<bmsSkInfo.bmsvoltage() <<"\n";
        std::cout<<"bmSkinfo enduratnceMileage is :"<<bmsSkInfo.bmselectric() <<"\n";
        std::cout<<"bmSkinfo speed is :"<<bmsSkInfo.bmssoc() <<"\n";
        std::cout<<"bmSkinfo revSpeed is :"<<bmsSkInfo.bmstemp() <<"\n";

    }

    {
        StatusNS::TboxSKInfo tbxSkInfo = msg.status().tboxskinfo();
        std::cout<<"TbSkinfo kl15 is :"<<tbxSkInfo.kl15() <<"\n";
        std::cout<<"TbSkinfo kl30 is :"<<tbxSkInfo.kl30() <<"\n";
        std::cout<<"TbSkinfo batterayVoltage is :"<<tbxSkInfo.batteryvoltage() <<"\n";
        std::cout<<"TbSkinfo csq is :"<<tbxSkInfo.csq() <<"\n";
        std::cout<<"tbxInfo rapidAccelerationCount "<<tbxSkInfo.rapidaccelerationcount()<<std::endl;
        std::cout<<"tbxInfo rapidDecelerationCount "<<tbxSkInfo.rapiddecelerationcount()<<std::endl;
        std::cout<<"tbxInfo emergencyBrakeCount "<<tbxSkInfo.emergencybrakecount()<<std::endl;
        std::cout<<"tbxInfo sharpTurnCount "<<tbxSkInfo.sharpturncount()<<std::endl;

        int canSize = tbxSkInfo.caninfo_size();
        for(int i = 0;i<canSize;i++)
        {
            StatusNS::CanInfo* canInfo = tbxSkInfo.mutable_caninfo(i);
            std::cout<<"caninfo canChannel :"<<canInfo->canchannel()<<"\n";
            std::cout<<"caninfo bufOff :"<<canInfo->busoff()<<"\n";
            std::cout<<"caninfo noAck :"<<canInfo->noack()<<"\n";
            std::cout<<"caninof recvNum :"<<canInfo->recvnum()<<"\n";
        }

        std::string loc = tbxSkInfo.location();

        LocationNS::Location location;
        location.ParseFromString(loc);
        std::cout<<"TbSkinfo location is "<<"\n";
        std::cout<<"tbSkinfo location valid :"<<location.valid()<<"\n";
        std::cout<<"tbSkinfo location latitude :"<<location.altitude()<<"\n";
        std::cout<<"tbSkinfo location longitude :"<<location.longitude()<<"\n";
        std::cout<<"tbSkinfo location angle :"<<location.angle()<<"\n";
        std::cout<<"tbSkinfo location speed :"<<location.speed()<<"\n";
        std::cout<<"tbSkinfo location satNumber :"<<location.satnumber()<<"\n";
        std::cout<<"tbSkinfo location hemisphere:"<<location.hemisphere()<<"\n";
        std::cout<<"tbSkinfo location timestamp:"<<location.timestamp()<<"\n";


        int canSize0 = tbxSkInfo.caninfo_size();
        for(int i = 0;i<canSize0;i++)
        {
            StatusNS::CanInfo* canInfo = tbxSkInfo.mutable_caninfo(i);
            std::cout<<"tbxInfo caninfo canChannel :"<<canInfo->canchannel()<<"\n";
            std::cout<<"tbxInfo caninfo bufOff :"<<canInfo->busoff()<<"\n";
            std::cout<<"tbxInfo caninfo noAck :"<<canInfo->noack()<<"\n";
            std::cout<<"tbxInfo caninof recvNum :"<<canInfo->recvnum()<<"\n";
        }

    }
}

void reportAlertToTsp(struct mosquitto* mosq,std::string vid)
{
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    std::cout<<"time stamp is :"<<timeInt<<std::endl;
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::ALERT);
        {
            AlertNS::Alert *alert = msg->mutable_alert();

            alert->CopyFrom(g_alert);

            std::string location1 = encryptLocation(g_fault.location());
            alert->set_location(location1);
        }
    }
    std::string alertStr = envelop.SerializeAsString();
    // 发布消息
    int len = alertStr.size();
    std::cout<<"serialize  alert string length is :"<<len<<std::endl;
    mosquitto_publish(mosq,NULL,std::string("/tbox/alert/"+vid+"/v").c_str(),alertStr.size(),alertStr.c_str(),0,false);

}
void parseAlert(std::string msgString)
{
    //parse message
    std::string  envelopStr = msgString;

    EvelopeNS::Envelope envelop;
    envelop.ParseFromString(envelopStr);
    std::cout<<"envelop info version :"<<envelop.version()<<"\n"<<" time: "<<envelop.time()<<"\n source : "<<envelop.source()<<"\n"<<" vid : "<<envelop.vid()<<"\n";

    MessageNS::Message msg = envelop.msg();
    std::cout<<"msg info aid :"<<msg.aid()<<"\n";
    {
        AlertNS::Alert *alert = msg.mutable_alert();
        int size = alert->alertmsg_size();
        for(int i = 0;i<size;i++)
        {
            AlertNS::AlertMsg alert_msg = alert->alertmsg(i);
            std::cout<<"alert_msg status"<<alert_msg.status()<<"\n";
            std::cout<<"alert_msg alertItem"<<alert_msg.alertitem()<<"\n";
        }
        {
            std::string loc = alert->location();

            LocationNS::Location location ;
            location.ParseFromString(loc);

            std::cout<<"alert location is "<<"\n";
            std::cout<<"valid :"<<location.valid()<<"\n";
            std::cout<<"latitude :"<<location.altitude()<<"\n";
            std::cout<<"longitude :"<<location.longitude()<<"\n";
            std::cout<<"angle :"<<location.angle()<<"\n";
            std::cout<<"spped :"<<location.speed()<<"\n";
            std::cout<<"satNumber :"<<location.satnumber()<<"\n";
            std::cout<<"hemisphere:"<<location.hemisphere()<<"\n";
            std::cout<<"timestamp:"<<location.timestamp()<<"\n";
        }
    }
}

void reportFaultToTsp(struct mosquitto* mosq,std::string vid)
{
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::FAULT);
        {
            FaultNS::Fault *fault = msg->mutable_fault();
            fault->CopyFrom(g_fault);
            std::string location1 = encryptLocation(g_fault.location());
            fault->set_location(location1);
        }
    }
    std::string faultStr = envelop.SerializeAsString();
    // 发布消息
    int len = faultStr.size();
    std::cout<<"serialize fault string length is :"<<len<<std::endl;
    mosquitto_publish(mosq,NULL,std::string("/tbox/fault/"+vid+"/v").c_str(),faultStr.size(),faultStr.c_str(),0,false);

}
void parseFault(std::string msgString)
{
    //parse message
    std::string  envelopStr = msgString;

    EvelopeNS::Envelope envelop;
    envelop.ParseFromString(envelopStr);
    std::cout<<"envelop info version :"<<envelop.version()<<"\n"<<" time: "<<envelop.time()<<"\n source : "<<envelop.source()<<"\n"<<" vid : "<<envelop.vid()<<"\n";

    MessageNS::Message msg = envelop.msg();
    std::cout<<"msg info aid :"<<msg.aid()<<"\n";
    {
        FaultNS::Fault  *fault = msg.mutable_fault();
        int size = fault->faultmsg_size();
        for(int i = 0;i<size;i++)
        {
            FaultNS::FaultMsg fault_msg = fault->faultmsg(i);
            FaultNS::FaultItem fault_item = fault_msg.faultitem();
            std::cout<<"fault_msg span"<<fault_item.spn() <<"\n";
            std::cout<<"fault_msg fmi"<<fault_item.fmi() <<"\n";
            std::cout<<"fault_msg model"<<fault_item.model()<<"\n";
            std::cout<<"fault_msg counter"<<fault_item.counter()<<"\n";
        }

        {
            std::string loc = fault->location();

            LocationNS::Location location;
            location.ParseFromString(loc);

            std::cout<<"alert location is "<<"\n";
            std::cout<<"valid :"<<location.valid()<<"\n";
            std::cout<<"latitude :"<<location.altitude()<<"\n";
            std::cout<<"longitude :"<<location.longitude()<<"\n";
            std::cout<<"angle :"<<location.angle()<<"\n";
            std::cout<<"spped :"<<location.speed()<<"\n";
            std::cout<<"satNumber :"<<location.satnumber()<<"\n";
            std::cout<<"hemisphere:"<<location.hemisphere()<<"\n";
            std::cout<<"timestamp:"<<location.timestamp()<<"\n";
        }
    }
}

void  reportGb32960ToTsp(struct mosquitto* mosq,std::string vid)
{
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::GB32960);
        {
            Gb32960NS::Gb32960 *gb32 = msg->mutable_gb32960();
            char data=0x01;
            gb32->set_data(&data);
        }
    }
    std::string gb32Str = envelop.SerializeAsString();
    // 发布消息
    int len = gb32Str.size();
    std::cout<<"serialize gb32960 string length is :"<<len<<std::endl;
    mosquitto_publish(mosq,NULL,std::string("/tbox/gb32960/"+vid+"/v").c_str(),gb32Str.size(),gb32Str.c_str(),0,false);

}

void parseGb32960(std::string msgString)
{
    //parse message
    std::string  envelopStr = msgString;

    EvelopeNS::Envelope envelop;
    envelop.ParseFromString(envelopStr);
    std::cout<<"envelop info version :"<<envelop.version()<<"\n"<<" time: "<<envelop.time()<<"\n source : "<<envelop.source()<<"\n"<<" vid : "<<envelop.vid()<<"\n";

    MessageNS::Message msg = envelop.msg();
    std::cout<<"msg info aid :"<<msg.aid()<<"\n";
    {
        Gb32960NS::Gb32960* gb32 = msg.mutable_gb32960();
        std::cout<<"gb32960 data is: "<<gb32->data()<<"\n";
    }
}

void reportGearPos(struct mosquitto* mosq,std::string vid,StatusNS::GearPosition gear)
{
    std::cout<<"report gear pos vid :"<<vid<<" gear is :"<<gear<<std::endl;
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::EVENT);
        {
            EventNS::Event *event = msg->mutable_event();
            EventNS::EventMsg* eventmsg = event->add_eventmsg();
            eventmsg->set_eventitem(EventNS::EventItem::GEAR_POSITION);
            eventmsg->set_gearposition(gear);
        }
    }
    std::string eventStr = envelop.SerializeAsString();
    // 发布消息
    int len = eventStr.size();
    mosquitto_publish(mosq,NULL,std::string("/tbox/event/"+vid+"/v").c_str(),eventStr.size(),eventStr.c_str(),0,false);
}

void reportEventEngineOnOff(struct mosquitto* mosq,std::string vid,bool on)
{
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::EVENT);
        {
            EventNS::Event *event = msg->mutable_event();
            event->CopyFrom(g_event);

            if(event->eventmsg_size())
            {
                event->mutable_eventmsg(0)->mutable_engineonoff()->set_kl15(on);
            }
            else
            {
                EventNS::EventMsg* eveMsg = event->add_eventmsg();
                eveMsg->mutable_engineonoff()->set_kl15(on);
            }

            std::cout<<"engine is on :"<<event->eventmsg(0).engineonoff().kl15()<<std::endl;
        }
    }
    std::string eventStr = envelop.SerializeAsString();
    // 发布消息
    int len = eventStr.size();
    std::cout<<"serialize event string length is :"<<len<<std::endl;
    mosquitto_publish(mosq,NULL,std::string("/tbox/event/"+vid+"/v").c_str(),eventStr.size(),eventStr.c_str(),0,false);
}

void reportEventToTsp(struct mosquitto* mosq,std::string vid)
{
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::EVENT);
        {
            EventNS::Event *event = msg->mutable_event();
            event->CopyFrom(g_event);
        }
    }
    std::string eventStr = envelop.SerializeAsString();
    // 发布消息
    int len = eventStr.size();
    std::cout<<"serialize event string length is :"<<len<<std::endl;
    mosquitto_publish(mosq,NULL,std::string("/tbox/event/"+vid+"/v").c_str(),eventStr.size(),eventStr.c_str(),0,false);

}
void parseEvent(std::string msgString)
{
    //parse message
    std::string  envelopStr = msgString;

    EvelopeNS::Envelope envelop;
    envelop.ParseFromString(envelopStr);
    std::cout<<"envelop info version :"<<envelop.version()<<"\n"<<" time: "<<envelop.time()<<"\n source : "<<envelop.source()<<"\n"<<" vid : "<<envelop.vid()<<"\n";

    MessageNS::Message msg = envelop.msg();
    std::cout<<"msg info aid :"<<msg.aid()<<"\n";
    {
        EventNS::Event* event = msg.mutable_event();
        int size = event->eventmsg_size();

        for(int i = 0;i<size;i++)
        {
            EventNS::EventMsg eventMsg = event->eventmsg(i);
            std::cout<<"event item "<<eventMsg.eventitem()<<"\n";

            EventNS::EngineOnOff engineOnOff = eventMsg.engineonoff();
            bool kl15 = engineOnOff.kl15();
            std::cout<<"kl15 is :"<<kl15<<"\n";
            std::string taskId = engineOnOff.taskid();
            std::cout<<"taskId is :"<<taskId<<"\n";



            std::string loc = engineOnOff.location();

            LocationNS::Location location ;
            location.ParseFromString(loc);

            callback_info+="valid :"+QString("%1").arg(location.valid())+"\n";
            std::cout<<"alert location is "<<"\n";
            std::cout<<"valid :"<<location.valid()<<"\n";
            std::cout<<"latitude :"<<location.altitude()<<"\n";
            callback_info+="latitude :"+QString("%1").arg(location.altitude())+"\n";
            std::cout<<"longitude :"<<location.longitude()<<"\n";
            callback_info+="longitude :"+QString("%1").arg(location.longitude())+"\n";
            std::cout<<"angle :"<<location.angle()<<"\n";
            callback_info+="angle :"+QString("%1").arg(location.angle())+"\n";
            std::cout<<"spped :"<<location.speed()<<"\n";
            callback_info+="spped :"+QString("%1").arg(location.speed())+"\n";
            std::cout<<"satNumber :"<<location.satnumber()<<"\n";
            callback_info+="satNumber :"+QString("%1").arg(location.satnumber())+"\n";
            std::cout<<"hemisphere:"<<location.hemisphere()<<"\n";
            callback_info+="hemisphere :"+QString("%1").arg(location.hemisphere())+"\n";
            std::cout<<"timestamp:"<<location.timestamp()<<"\n";
            callback_info+="timestamp :"+QString("%1").arg(location.timestamp())+"\n";

            StatusNS::HmiInfo hmiInfo = engineOnOff.hmiinfo() ;
            std::cout<<"speed is :"<<hmiInfo.speed()<<"\n";
            std::cout<<"revspeed is :"<<hmiInfo.revspeed()<<"\n ";
            std::cout<<"odometro is :"<<hmiInfo.odometro()<<"\n";
            std::cout<<"gearPositoin is :"<<hmiInfo.gearposition()<<"\n";

            EventNS::BluetoothInfo blueToolThInfo = engineOnOff.bluetoothinfo();
            std::cout<<"blueToothName is :"<<blueToolThInfo.bluetoothname()<<"\n";
            std::cout<<"blueToothPwd is :"<<blueToolThInfo.bluetoothpwd()<<"\n";
            std::cout<<"blueToothSecretkey is :"<<blueToolThInfo.bluetoothsecretkey()<<"\n";
            std::cout<<"blueToothMac is :"<<blueToolThInfo.bluetoothmac()<<"\n";

            int batterySize = eventMsg.batteryinfo_size();
            for(int i = 0;i<batterySize;i++)
            {
                EventNS::BatteryInfo batteryInfo = eventMsg.batteryinfo(i);
                std::cout<<"battery info cycle :"<<batteryInfo.cycle()<<"\n";
                std::cout<<"battery info quantity :"<<batteryInfo.quantity()<<"\n";
                std::cout<<"battery info temp :"<<batteryInfo.temp()<<"\n";
                std::cout<<"battery info charging :"<<batteryInfo.charging()<<"\n";
                std::cout<<"battery info remaining :"<<batteryInfo.remaining()<<"\n";
            }

        }

        EventNS::EventAck ack = event->eventack();
        int result = ack.result();
        std::string taskId = ack.taskid();
        std::cout<<"ack result is :"<<result<<std::endl;
        std::cout<<"ack taskID is :"<<taskId<<std::endl;
    }
}

void reportOtaToTsp(struct mosquitto* mosq,std::string vid)
{
    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::OTA_STEP);
        {
            OTANS::OTAStep* otaStep = msg->mutable_otastep();
            QUuid uuid = QUuid::createUuid();
            otaStep->set_taskid(uuid.toString().toStdString());

            OTANS::StepEvent* stepEvent1 = otaStep->add_stepevent();
            stepEvent1->set_step(20);
            stepEvent1->set_desc("fine");
            stepEvent1->set_ecu(DiagnoseNS::Ecus::Abs);

            OTANS::StepEvent* stepEvent2 = otaStep->add_stepevent();
            stepEvent2->set_step(30);
            stepEvent2->set_desc("ok");
            stepEvent2->set_ecu(::DiagnoseNS::Ecus::Bms);
        }

    }

    std::string otaProgressStr = envelop.SerializeAsString();
    // 发布消息
    int len = otaProgressStr.size();
    std::cout<<"serialize ota progress string length is :"<<len<<std::endl;
    mosquitto_publish(mosq,NULL,std::string("/tbox/otastep/"+vid+"/v").c_str(),otaProgressStr.size(),otaProgressStr.c_str(),0,false);

}
void parseOta(std::string msgString)
{
    //parse message
    std::string  envelopStr = msgString;

    EvelopeNS::Envelope envelop;
    envelop.ParseFromString(envelopStr);
    std::cout<<"envelop info version :"<<envelop.version()<<"\n"<<" time: "<<envelop.time()<<"\n source : "<<envelop.source()<<"\n"<<" vid : "<<envelop.vid()<<"\n";

    MessageNS::Message msg = envelop.msg();
    std::cout<<"msg info aid :"<<msg.aid()<<"\n";
    {
        OTANS::OTA* ota = msg.mutable_ota();
        int timestamp = ota->timestamp();
        std::string taskId = ota->taskid();
        OTANS::OTARequest otaRequest = ota->otarequest();
        int totalSize = otaRequest.totalsize();

        int ecuInfoSize = otaRequest.ecuinfo_size();
        for(int i = 0;i<ecuInfoSize;i++)
        {
            OTANS::EcuInfo ecuInfo = otaRequest.ecuinfo(i);

            int index = ecuInfo.index();
            std::cout<<"ecu index :"<<index<<"\n";
            DiagnoseNS::Ecus ecu = ecuInfo.ecu();

            std::string softVer = ecuInfo.softver();
            std::cout<<"softVer is : "<<softVer<<"\n";
            std::string fileUrl = ecuInfo.fileurl();
            std::cout<<"fileUrl :"<<fileUrl<<"\n";
            int fileSize = ecuInfo.filesize();
            std::cout<<"fileSize :"<<fileSize<<"\n";
            std::string md5 = ecuInfo.md5();
            std::cout<<"md5 :"<<md5<<"\n";
        }
    }

}

bool publishOtaResp(OTANS::OTAResponse otaResp)
{

    //组织Envelop
    EvelopeNS::Envelope envelop;
    envelop.set_version("1.0.0.1");

    qint64 timeInt = QDateTime::currentDateTime().toMSecsSinceEpoch();
    envelop.set_time(timeInt);
    envelop.set_vid(vid);
    envelop.set_source(::EvelopeNS::Source::MOBILE);
    {
        MessageNS::Message *msg = envelop.mutable_msg() ;
        msg->set_aid(MessageNS::Aid::OTA);
        {

            OTANS::OTA * ota = msg->mutable_ota();
            OTANS::OTAResponse* otaResp = ota->mutable_otaresponse();

            OTANS::OTAResult* otaResult0 = otaResp->add_otaresult();
            otaResult0->set_index(0);
            otaResult0->set_ecu(::DiagnoseNS::Ecus::Bms);
            otaResult0->set_softver("1.0.0.1");
            otaResult0->set_updateresult(0x0);
            otaResult0->set_updatestarttime(12121212);
            otaResult0->set_updateendtime(2333333);

            OTANS::OTAResult* otaResult1 = otaResp->add_otaresult();

            OTANS::OTAResult* otaResult2 = otaResp->add_otaresult();
        }
    }

    std::string otaRespStr = envelop.SerializeAsString();
    // 发布消息
    int len = otaRespStr.size();
    std::cout<<"serialize ota resp string length is :"<<len<<std::endl;
    mosquitto_publish(mosq,NULL,std::string("/tbox/otastep/"+vid+"/v").c_str(),otaRespStr.size(),otaRespStr.c_str(),0,false);
}

void time_out_publish_message(struct mosquitto* mosq,std::string vid,int interval){

    std::cout<<"report infomation  to tsp "<<std::endl;
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(interval));
        //上报状态信息
        reportStatusToTsp(mosq,vid);
        //告警上报
        //reportAlertToTsp(mosq,vid);
        //上报故障
        //reportFaultToTsp(mosq,vid);
    }
}

QString getProcessedStr(QString configStr,int index)
{
    QString left_str = configStr.left(configStr.length()-5);
    //std::cout<<"left_str is "<<left_str.toStdString()<<std::endl;
    QString index_str = QString("%1").arg(index).rightJustified(5,'0');
    // std::cout<<"index_str is "<<index_str.toStdString()<<std::endl;
    return left_str+index_str;
}

std::string  readString(std::string readPath)
{
    std::ifstream readFile(readPath,std::ios::in|std::ios::binary);
    if(!readFile)
    {
        std::cerr<<"Cannot open file"<<std::endl;
        return std::string();
    }

    readFile.seekg(0,std::ios::end);
    int fileSize = readFile.tellg();

    readFile.seekg(0,std::ios::beg);
    char* buffer = new char[fileSize];
    readFile.read(buffer,sizeof(char)*fileSize);

    std::string pbStr(buffer);
    delete [] buffer;
    return pbStr;
}

int aes_encrypt(unsigned char* plaintext, int plaintext_len, unsigned char* key,
                unsigned char* iv, unsigned char* ciphertext)
{
    EVP_CIPHER_CTX* ctx;
    int len;
    int ciphertext_len;

    // 创建并初始化上下文
    if (!(ctx = EVP_CIPHER_CTX_new()))
        return -1;

    // 初始化加密操作，指定使用AES-128-CBC模式，并且启用PKCS7Padding
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        return -1;

    // 执行加密操作
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        return -1;
    ciphertext_len = len;

    // 执行加密最后一步，并自动进行PKCS7Padding填充
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        return -1;
    ciphertext_len += len;

    // 清理上下文
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int decrypt_location(const unsigned char *encrypted_data, int encrypted_data_len, const unsigned char *key,
                     const unsigned char *iv, unsigned char *decrypted_data)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int decrypted_data_len;

    // 创建并初始化上下文
    if (!(ctx = EVP_CIPHER_CTX_new()))
        return -1;

    // 初始化解密操作，使用AES-128-CBC模式
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        return -1;

    // 执行解密操作
    if (1 != EVP_DecryptUpdate(ctx, decrypted_data, &len, encrypted_data, encrypted_data_len))
        return -1;
    decrypted_data_len = len;

    // 解密最后一块数据并自动去除PKCS7填充
    if (1 != EVP_DecryptFinal_ex(ctx, decrypted_data + len, &len))
        return -1;
    decrypted_data_len += len;

    // 清理上下文
    EVP_CIPHER_CTX_free(ctx);

    return decrypted_data_len;
}

void generate_key_iv(const char *vin, unsigned char *key, unsigned char *iv) {
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    // 计算SHA-256哈希
    SHA256((const unsigned char *)vin, strlen(vin), sha256_hash);
    // 取前16字节作为AES-128密钥和IV
    memcpy(key, sha256_hash, 16);
    memcpy(iv, sha256_hash, 16);
}


std::string decryptLocation(std::string location)
{
    unsigned char key[16];
    unsigned char iv[16];
    generate_key_iv(hw_vin.toStdString().c_str(),key,iv);

    size_t len = location.length();
    unsigned char* buffer = new unsigned char[len + 1];  // 额外的空间用于'\0'
    strncpy(reinterpret_cast<char*>(buffer), location.c_str(), len);
    buffer[len] = '\0';  // 添加字符串终止符
    std::string decrypted_data;
    int decrypted_data_len = decrypt_location(buffer,location.length(),key,iv,(unsigned char*)decrypted_data.c_str());

    return decrypted_data;
}


std::string encryptLocation(std::string location)
{
    unsigned char key[16];
    unsigned char iv[16];
    unsigned char encrypted_data[128];
    generate_key_iv(hw_vin.toStdString().c_str(),key,iv);

    int encrypted_data_len =  aes_encrypt((unsigned char*)location.c_str(),location.length(),key,iv,encrypted_data);
    g_encrypted_data_len = encrypted_data_len;

    std::string cipherText ;
    unsigned char* foo;
    foo = encrypted_data;
    cipherText.append(reinterpret_cast<const char*>(foo));

    return cipherText;
}

void loadConfigInfo()
{
    std::string statusStr = readString("./configure/status.pb");
    std::string faultStr = readString("./configure/fault.pb");
    std::string alertStr = readString("./configure/alert.pb");

    g_status.ParseFromString(statusStr);
    g_fault.ParseFromString(faultStr);
    g_alert.ParseFromString(alertStr);

    std::ifstream readFileMarks("./configure/marks.pb",std::ios::in|std::ios::binary);
    if(!readFileMarks)
    {
        std::cerr<<"Cannot open file"<<std::endl;
    }
    g_marks.ParseFromIstream(&readFileMarks);


    std::ifstream readFile0("./configure/event.pb",std::ios::in|std::ios::binary);
    if(!readFile0)
    {
        std::cerr<<"Cannot open file"<<std::endl;
    }
    g_event.ParseFromIstream(&readFile0);


    std::ifstream readFile("./configure/control.pb",std::ios::in|std::ios::binary);
    if(!readFile)
    {
        std::cerr<<"Cannot open file"<<std::endl;
    }

    g_control.ParseFromIstream(&readFile);


    //encryt location info
    std::string cipherText ;
    //alert
    {
        cipherText = encryptLocation(g_alert.location());
        g_alert.set_location(cipherText);
    }

    //status
    {
        //        StatusNS::TboxSKInfo tbxSkInfo = g_status.tboxskinfo();
        //        cipherText = encryptLocation(tbxSkInfo.location());
        //        tbxSkInfo.set_location(cipherText);
        //        g_status.mutable_tboxskinfo()->set_location(cipherText);
    }

    //event
    {
        int eventMsgSize = g_event.eventmsg_size();
        //std::cout<<"event msg size is :"<<eventMsgSize<<std::endl;
        for(int i = 0;i<eventMsgSize;i++)
        {
            EventNS::EventMsg eventMsg = g_event.eventmsg(i);
            EventNS::EngineOnOff engineOff = eventMsg.engineonoff();
            cipherText = encryptLocation(engineOff.location());
            g_event.mutable_eventmsg(i)->mutable_engineonoff()->set_location(cipherText);
        }

    }

    //fault
    {
        cipherText = encryptLocation(g_fault.location());
        g_fault.set_location(cipherText);
    }

    //control
    {
        ControlNS::Parameters param = g_control.para();
        ControlNS::ControlGetPositionPara getPositionPara = param.controlgetpositionpara();
        cipherText = encryptLocation(getPositionPara.location());
        //update
        g_control.mutable_para()->mutable_controlgetpositionpara()->set_location(cipherText);
    }

}

void signalHandler(int signal)
{
    reportEventEngineOnOff(mosq,vid,false);
    exit(signal);
}

int main(int argc, char *argv[])
{
    // 绑定信号处理器
    signal(SIGINT, signalHandler);   // 监听 Ctrl+C (SIGINT)
    signal(SIGTERM, signalHandler);  // 监听终止信号 (SIGTERM)

    QApplication a(argc, argv);

    int is_show_window = 1;

    for(int i = 1;i<argc;i++)
    {
        int idx = QString("%1").arg(argv[i]).toInt();
        if(1 == i)
        {
            g_index = idx;
            std::cout<<"i is :"<<i<<" argv index is :"<<idx<<std::endl;
            std::cout<<"result str is :"<<getProcessedStr(base_vin,idx).toStdString()<<std::endl;
            hw_vin = getProcessedStr(base_vin,idx);
            vid = md5Encryption(hw_vin).toStdString();
            std::cout<<"vid is :"<<vid<<std::endl;
            hw_tbsn = getProcessedStr(hw_tbsn,idx);
            std::cout<<"tbsn is :"<<hw_tbsn.toStdString()<<std::endl;
            hw_iccid = getProcessedStr(hw_iccid,idx);
            std::cout<<"iccid is :"<<hw_iccid.toStdString()<<std::endl;
            hw_imei = getProcessedStr(hw_imei,idx);
            std::cout<<"imei is :"<<hw_imei.toStdString()<<std::endl;
        }
        else if(2 == i)
        {
            is_show_window = QString("%1").arg(argv[i]).toInt();
            std::cout<<"is_show_window is :"<<is_show_window<<std::endl;
        }
        else if(3 == i)
        {
            latitude_min = idx*1000000;
            std::cout<<"latitude_min is :"<<latitude_min<<std::endl;
        }
        else if(4 == i)
        {
            latitude_max = idx*1000000;
            std::cout<<"latitude_max is :"<<latitude_max<<std::endl;
        }
        else if(5 == i)
        {
            longitude_min = idx*1000000;
            std::cout<<"longitude_min is :"<<longitude_min<<std::endl;
        }
        else if(6 == i)
        {
            longitude_max = idx*1000000;
            std::cout<<"longitude_max is :"<<longitude_max<<std::endl;
        }
        else if(7 == i)
        {
            move_times = idx;
            if(move_times>1000||move_times<=0)
            {
                move_times = 30;
            }
            std::cout<<"move times is :"<<move_times<<std::endl;
        }

    }

    deltx = 0.0001*1000000;
    delty = 0.0001*1000000;

    loadConfigInfo();

    if(1 == is_show_window)
    {
        TBoxWidget* w = new TBoxWidget;

        QObject::connect(w,&TBoxWidget::subscribeTopicSig,[=](QString topic){

            int rv = mosquitto_subscribe(mosq,NULL,std::string(topic.toStdString()).c_str(),0);
            if (rv != MOSQ_ERR_SUCCESS) {
                std::cout<<"failed to subscribe topic "<<topic.toStdString()<<"\n";
            }
        });

        //report relation signal

        QObject::connect(w,&TBoxWidget::updateStatusSignal,[&](){

            w->getStatus(g_status);

            reportStatusToTsp(mosq,vid);
        });

        QObject::connect(w,&TBoxWidget::updateFaultSignal ,[&](){

            w->getFault(g_fault);

            reportFaultToTsp(mosq,vid);
        });

        QObject::connect(w,&TBoxWidget::updateAlertSignal,[&](){

            w->getAlert(g_alert);

            reportAlertToTsp(mosq,vid);
        });

        QObject::connect(w,&TBoxWidget::updateEventSignal ,[&](){
            w->getEvent(g_event);
            reportEventToTsp(mosq,vid);
        });

        QObject::connect(w,&TBoxWidget::responseToControl,[&](QString ctrlString){
            ControlNS::Control ctrl;
            ctrl.ParseFromString(ctrlString.toStdString());
            publishControlResponse(mosq,vid,ctrl);
        });

        w->show();
    }

    /*
    QTimer timer;
    timer.setInterval(200);
    timer.setSingleShot(false);
    QObject::connect(&timer,&QTimer::timeout,[&](){
        w->updateCallbackText(callback_info);
        if(!isControlResped)
        {
            //to deal with control response
            control_mutex.lock();
            EvelopeNS::Envelope envelop;
            envelop.ParseFromString(controlSerialString);
            MessageNS::Message msg = envelop.msg();
            ControlNS::Control* control = msg.mutable_control();
            w->showRecieveControlInfo(*control);
            control_mutex.unlock();
            isControlResped = true;
            std::cout<<"............receive control .........."<<std::endl;
        }

        if(!isDiagnoseResped)
        {
            diagnose_mutex.lock();
            EvelopeNS::Envelope envelop;
            envelop.ParseFromString(diagnoseSerialString);
            MessageNS::Message msg = envelop.msg();
            DiagnoseNS::Diagnose* diagnose = msg.mutable_diagnose();
            w->showRecieveDiagnoseInfo(*diagnose);
            diagnose_mutex.unlock();
            isDiagnoseResped = true;
            std::cout<<"............receive diagnose .........."<<std::endl;
        }
    });

    timer.start();
*/
    //configureCrt();

    Mosquito_mqtts(vid);  //初始化

    std::thread t_init(loopMqttEnv);
    //定时上报
    std::thread t_report(time_out_publish_message,mosq,vid,g_report_interval);
    if(is_show_window)
    {
        a.exec();
    }

    t_init.join();
    t_report.join();

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    std::cout<<"process finished "<<std::endl;
    return 0;
}


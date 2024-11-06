#include "ControlConfigForm.h"
#include "ui_ControlConfigForm.h"
#include "LocationForm.h"
#include "ApnItemForm.h"
#include "EcuVersionForm.h"
#include "protoBuf/control.pb.h"
#include "protoBuf/location.pb.h"
#include "protoBuf/status.pb.h"
#include <fstream>

ControlConfigForm::ControlConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlConfigForm)
{
    ui->setupUi(this);
    initUI();
    initData();
}

ControlConfigForm::~ControlConfigForm()
{
    delete ui;
}

void ControlConfigForm::initUI()
{
    location_ = new LocationForm;
    ui->verticalLayout_location->addWidget(location_);
    ui->comboBox_result->addItem(QString("控制成功"),0);
    ui->comboBox_result->addItem(QString("已禁止远程启动"),257);
    ui->comboBox_result->addItem(QString("钥匙状态不满足条件"),258);
    ui->comboBox_result->addItem(QString("未设防错误"),259);
    ui->comboBox_result->addItem(QString("未处于驻车状态"),260);
    ui->comboBox_result->addItem(QString("远控失败,未知错误"),261);
    ui->comboBox_result->addItem(QString("车速不为0"),262);
    ui->comboBox_result->addItem(QString("发动机启动失败"),263);
    ui->comboBox_result->addItem(QString("预留1"),264);
    ui->comboBox_result->addItem(QString("预留2"),265);
    ui->comboBox_result->addItem(QString("鉴权失败,不使用"),266);
    ui->comboBox_result->addItem(QString("本地启动，远程启动退出"),267);
    ui->comboBox_result->addItem(QString("远程启动时间到退出"),268);
    ui->comboBox_result->addItem(QString("远程启动时间TBOX强制退出"),269);
    ui->comboBox_result->addItem(QString("远程启动时间TBOX强制退出失败"),270);
    ui->comboBox_result->addItem(QString("VIN号错误"),271);
    ui->comboBox_result->addItem(QString("TBOX内部故障，MCU未响应或者格式不对"),272);
    ui->comboBox_result->addItem(QString("ACC on,解锁失败"),273);
    ui->comboBox_result->addItem(QString("龙头锁上锁失败"),288);
    ui->comboBox_result->addItem(QString("龙头锁解锁失败"),289);
    ui->comboBox_result->addItem(QString("远程开锁失败"),290);
    ui->comboBox_result->addItem(QString("座椅加热失败"),291);
    ui->comboBox_result->addItem(QString("预约加热失败"),292);
    ui->comboBox_result->addItem(QString("手把加热失败"),292);

    ui->comboBox_result->addItem(QString("超时"),512);
    ui->comboBox_result->addItem(QString("车辆连接失败"),513);
    ui->comboBox_result->addItem(QString("车辆系统错误"),514);
    ui->comboBox_result->addItem(QString("车控指令发送超时"),515);
    ui->comboBox_result->addItem(QString("车控指令执行超时"),516);
    ui->comboBox_result->addItem(QString("车控指令执行成功"),517);
    ui->comboBox_result->addItem(QString("指令被禁止操作"),518);
    ui->comboBox_result->addItem(QString("已经下发太多指令，不能继续执行"),519);
    ui->comboBox_result->addItem(QString("指令执行条件不满足"),520);
    ui->comboBox_result->addItem(QString("无错误"),521);
    ui->comboBox_result->addItem(QString("TSP身份验证失败（后台下发）"),522);
    ui->comboBox_result->addItem(QString("CAN通信错误"),523);
    ui->comboBox_result->addItem(QString("TBOX系统忙"),524);
    ui->comboBox_result->addItem(QString("任务执行失败"),525);
    ui->comboBox_result->addItem(QString("任务执行超时"),526);
    ui->comboBox_result->addItem(QString("应答数据过长"),527);
    ui->comboBox_result->addItem(QString("任务执行条件不满足"),528);
    ui->comboBox_result->addItem(QString("功能禁止"),529);
    ui->comboBox_result->addItem(QString("文件校验失败"),530);
}

void ControlConfigForm::initData()
{

    std::ifstream readFile("./configure/control.pb",std::ios::in|std::ios::binary);
    if(!readFile)
    {
        std::cerr<<"Cannot open file"<<std::endl;
    }

    ControlNS::Control control;
    control.ParseFromIstream(&readFile);

    ControlNS::Parameters param = control.para();

    ControlNS::ControlResponse response = control.controlresponse();
    ControlNS::ControlGetAPNNameResponse apnResp = response.controlgetapnnameresponse();
    int result = apnResp.result();

    for(int i = 0;i<ui->comboBox_result->count();i++)
    {
        if(ui->comboBox_result->itemData(i)==result)
        {
            ui->comboBox_result->setCurrentIndex(i);
            break;
        }
    }

    ControlNS::ControlGetTPMSPara tpmPara = param.controlgettmpspara();
    StatusNS::TpmsInfo tpmInfo = tpmPara.tpmsinfo();
    ui->lineEdit_frontPressure->setText(QString("%1").arg(tpmInfo.fronttirepressure()));
    ui->lineEdit_frontTemp->setText(QString("%1").arg(tpmInfo.fronttiertemp()));
    ui->lineEdit_rearPressure->setText(QString("%1").arg(tpmInfo.reartirepressure()));
    ui->lineEdit_rearTemp->setText(QString("%1").arg(tpmInfo.reartiretemp()));
    ui->lineEdit_status->setText(QString("%1").arg(tpmInfo.status()));

    ControlNS::ControlGetPositionPara posPara = param.controlgetpositionpara();

    std::string loc = posPara.location();

    LocationNS::Location location ;
    location.ParseFromString(loc);
    location_->setData(location);

    ControlNS::ControlAPNNamePara apnPara = param.controlapnnamepara();
    int size = apnPara.names_size();
    for(int i = 0;i<size;i++)
    {
        addApnItem(apnPara.names(i).channel(),apnPara.names(i).apn());
    }

    ControlNS::ControlGetSignalIntensityPara signalIntensityPara = param.controlgetsignalintensitypara();
    ui->lineEdit_sigIntensity->setText(QString("%1").arg(signalIntensityPara.signalintensity()));

    ControlNS::ControlGetECUVersionPara ecuPara = param.controlgetecuversionpara();
    size = ecuPara.info_size();
    for(int i = 0;i<size;i++)
    {
        ControlNS::ECUVersion ecuversion = ecuPara.info(i);
        addEcuVersion(ecuversion);
    }
}

void ControlConfigForm::saveAsString(std::string savePath, std::string str)
{
    //save
    std::ofstream outfile(savePath,std::ios::binary);
    if(!outfile.is_open())
    {
        std::cerr<<"can't open file"<<std::endl;
        return ;
    }

    outfile.write(str.data(),str.size());
    outfile.close();
}

void ControlConfigForm::addApnItem(int channel ,std::string apnName)
{
    static int  index = 0;
    ApnItemForm * apnItem = new ApnItemForm;
    apnItem->setApn(channel,apnName);
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(240,48));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,apnItem);
    apnItem->setProperty("index",index);
    connect(apnItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
    index++;
}

void ControlConfigForm::getEcuVersionParaData(ControlNS::ControlGetECUVersionPara &para)
{

    for(int i = 0;i<ui->listWidget_ecu->count();i++)
    {
        QListWidgetItem* item = ui->listWidget_ecu->item(i);
        EcuVersionForm * ecuForm = dynamic_cast<EcuVersionForm*>(ui->listWidget_ecu->itemWidget(item));
        ControlNS::ECUVersion*  ecuVersion =  para.add_info();
        ecuForm->getEcuVersion(*ecuVersion);
    }
}

void ControlConfigForm::addEcuVersion(ControlNS::ECUVersion &version)
{
    static int  index = ui->listWidget_ecu->count();
    EcuVersionForm * ecuVersionItem = new EcuVersionForm;
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(240,107));
    ui->listWidget_ecu->addItem(item);
    ui->listWidget_ecu->setItemWidget(item,ecuVersionItem);
    ecuVersionItem->setData(version);
    ecuVersionItem->setProperty("index",index);
    connect(ecuVersionItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_delete_ecu_Item(int)));
    index++;
}

void ControlConfigForm::on_pushButton_addApn_clicked()
{
    addApnItem();
}


void ControlConfigForm::on_pushButton_apply_clicked()
{
    ControlNS::Control control;
    ControlNS::Parameters* param = control.mutable_para();
    ControlNS::ControlResponse* response = control.mutable_controlresponse();

    ControlNS::ControlGetPositionPara* posPara = param->mutable_controlgetpositionpara();
    //TODO
    std::string* loc = posPara->mutable_location();

    LocationNS::Location* location = new LocationNS::Location();
    location_->getLocation(*location);
    *loc = location->SerializeAsString();
    ControlNS::ControlGetPositionResponse* posResp = response->mutable_controlgetpositionresponse();
    posResp->set_result(ui->comboBox_result->currentData().toUInt());

    ControlNS::ControlGetTPMSPara* tpmPara = param->mutable_controlgettmpspara();
    StatusNS::TpmsInfo* tpmInfo = tpmPara->mutable_tpmsinfo();
    tpmInfo->set_fronttiertemp(ui->lineEdit_frontTemp->text().toUInt());
    tpmInfo->set_fronttirepressure(ui->lineEdit_frontPressure->text().toUInt());
    tpmInfo->set_reartirepressure(ui->lineEdit_rearPressure->text().toUInt());
    tpmInfo->set_reartiretemp(ui->lineEdit_rearTemp->text().toUInt());
    tpmInfo->set_status(ui->lineEdit_status->text().toUInt());

    ControlNS::ControlGetTPMSResponse* tpmResp = response->mutable_controlgettpmsresponse();
    tpmResp->set_result(ui->comboBox_result->currentData().toUInt());


    ControlNS::ControlGetSignalIntensityPara* signalPara = param->mutable_controlgetsignalintensitypara();
    signalPara->set_signalintensity(ui->lineEdit_sigIntensity->text().toUInt());

    ControlNS::ControlGetSignalIntensityResponse* sigResp = response->mutable_controlgetsignalintensityresponse();
    sigResp->set_result(ui->comboBox_result->currentData().toUInt());


    ControlNS::ControlGetAPNNameResponse* apnResp = response->mutable_controlgetapnnameresponse();
    apnResp->set_result(ui->comboBox_result->currentData().toUInt());

    ControlNS::ControlAPNNamePara* apnNamePara = param->mutable_controlapnnamepara();

    //get apn
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        ApnItemForm* apnForm = dynamic_cast<ApnItemForm*>(ui->listWidget->itemWidget(item));
        ControlNS::APN* apn =  apnNamePara->add_names();
        int channel  = 0;
        std::string apnName = "";
        apnForm->getAPn(channel,apnName);
        apn->set_channel(channel);
        apn->set_apn(apnName);
    }

    ControlNS::ControlEngineResponse* engineResp = response->mutable_controlengineresponse();
    engineResp->set_result(ui->comboBox_result->currentData().toUInt());

    ControlNS::ControlHeatSeatResponse*  heatSeatResp = response->mutable_controlheatseatresponse();
    heatSeatResp->set_result(ui->comboBox_result->currentData().toUInt());

    ControlNS::ControlHeatHandleBarResponse* heatHandlResp = response->mutable_controlheathandlebarresponse();
    heatHandlResp->set_result(ui->comboBox_result->currentData().toUInt());

    ControlNS::ControlHeatReserveResponse* heatReserveResp = response->mutable_controlheatreserveresponse();
    heatReserveResp->set_result(ui->comboBox_result->currentData().toUInt());

    ControlNS::ControlTakeParkingPhotoResponse* takePhoneResp = response->mutable_controltakeparkingphotoresponse();
    takePhoneResp->set_result(ui->comboBox_result->currentData().toUInt());


    ControlNS::ControlGetECUVersionResponse* ecuVersonResp = response->mutable_controlgetecuversionresponse();
    ecuVersonResp->set_result(ui->comboBox_result->currentData().toUInt());

    ControlNS::ControlGetECUVersionPara* ecuVersionPara = param->mutable_controlgetecuversionpara();
    getEcuVersionParaData(*ecuVersionPara);

    std::string configStr = control.SerializeAsString();

    saveAsString("./configure/control.pb",configStr);

}

void ControlConfigForm::slot_deleteItem(int index)
{
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        ApnItemForm* wid = dynamic_cast<ApnItemForm*>(ui->listWidget->itemWidget(item));

        if(wid->property("index").toUInt()== index)
        {
            ui->listWidget->removeItemWidget(item);
            delete  wid;
            delete  item;
            break;
        }
    }
}

void ControlConfigForm::slot_delete_ecu_Item(int index)
{
    for(int i = 0;i<ui->listWidget_ecu->count();i++)
    {
        QListWidgetItem* item = ui->listWidget_ecu->item(i);
        EcuVersionForm* wid = dynamic_cast<EcuVersionForm*>(ui->listWidget_ecu->itemWidget(item));

        if(wid->property("index").toUInt()== index)
        {
            ui->listWidget_ecu->removeItemWidget(item);
            delete  wid;
            delete  item;
            break;
        }
    }
}


void ControlConfigForm::on_pushButton_addEcu_clicked()
{
    static int  index = ui->listWidget_ecu->count();
    EcuVersionForm * ecuVersionItem = new EcuVersionForm;
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(240,107));
    ui->listWidget_ecu->addItem(item);
    ui->listWidget_ecu->setItemWidget(item,ecuVersionItem);
    ecuVersionItem->setProperty("index",index);
    connect(ecuVersionItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_delete_ecu_Item(int)));
    index++;
}


#include "DiagnoseForm.h"
#include "ui_DiagnoseForm.h"
#include "DIDContentForm.h"
#include "ReadDtcRespForm.h"
#include "EcuList.h"
#include "EcuAddrListForm.h"

DiagnoseForm::DiagnoseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagnoseForm)
{
    ui->setupUi(this);
    initUI();
}

DiagnoseForm::~DiagnoseForm()
{
    delete ui;
}

void DiagnoseForm::initUI()
{
    read_dtc_resp_ = new ReadDtcRespForm;
    read_dtc_component = new EcuList;
    clean_dtc_component = new  EcuList;
    diag_Ecu_Addr_ = new EcuAddrListForm;
    diag_Ecu_Addr_resp_ = new EcuAddrListForm;

    ui->verticalLayout_readDtc->addWidget(read_dtc_component);
    ui->verticalLayout_cleanDtc->addWidget(clean_dtc_component);
    ui->verticalLayout_ecuAddr->addWidget(diag_Ecu_Addr_);
    ui->verticalLayout_readDtc_resp->addWidget(read_dtc_resp_);
    ui->verticalLayout_ecuAddr_resp->addWidget(diag_Ecu_Addr_resp_);

    diagnose_wid_opt_map.insert(ui->widget_readDid,DiagnoseNS::DiagnoseOpt::READ_DID);
    diagnose_wid_opt_map.insert(ui->widget_EcuAddr,DiagnoseNS::DiagnoseOpt::ECU_ADDR);
    diagnose_wid_opt_map.insert(ui->widget_cleanDtc,DiagnoseNS::DiagnoseOpt::CLEAN_DTC);
    diagnose_wid_opt_map.insert(ui->widget_readDtc,DiagnoseNS::DiagnoseOpt::READ_DTC);
    diagnose_wid_opt_map.insert(ui->widget_readDtc_resp,DiagnoseNS::DiagnoseOpt::READ_DTC);
    diagnose_wid_opt_map.insert(ui->widget_EcuAddr_resp,DiagnoseNS::DiagnoseOpt::ECU_ADDR);
    diagnose_wid_opt_map.insert(ui->widget_writeDid,DiagnoseNS::DiagnoseOpt::WRITE_DID);
    diagnose_wid_opt_map.insert(ui->widget_readDid_resp,DiagnoseNS::DiagnoseOpt::READ_DID);

}

void DiagnoseForm::showDiagnoseByType(DiagnoseNS::DiagnoseOpt &diagnoseOpt)
{

    QMap<QWidget*,DiagnoseNS::DiagnoseOpt>::iterator iter = diagnose_wid_opt_map.begin();

    for(;iter!= diagnose_wid_opt_map.end();iter++)
    {
        iter.key()->setVisible(false);
    }

    iter = diagnose_wid_opt_map.begin();
    for(;iter!= diagnose_wid_opt_map.end();iter++)
    {
        if(iter.value()==diagnoseOpt)
        {
            iter.key()->setVisible(true);
        }
    }
}

void DiagnoseForm::setDiagnoseData(DiagnoseNS::Diagnose &diagnose)
{

    std::string  taskId = diagnose.taskid();
    DiagnoseNS::DiagnoseOpt diagnoseOpt = diagnose.diagnoseopt();

    showDiagnoseByType(diagnoseOpt);

    ui->label_taskId->setText(QString::fromStdString(taskId));
    ui->comboBox_diagnoseType->setCurrentIndex(diagnoseOpt);

    DiagnoseNS::ReadDID readDid = diagnose.readdid();
    setReadDidData(readDid);

    DiagnoseNS::WriteDID writeDid = diagnose.writedid();
    setWriteDidData(writeDid);

    DiagnoseNS::ReadDTC readDtc = diagnose.readdtc();
    setReadDtcData(readDtc);

    DiagnoseNS::CleanDTC cleanDtc = diagnose.cleandtc();
    setCleanDtcData(cleanDtc);

    DiagnoseNS::DiagEcuAddr diagEcuAddr = diagnose.diagecuaddr();
    diag_Ecu_Addr_->setDiagEcuAddrData(diagEcuAddr);

    diag_Ecu_Addr_resp_->setDiagEcuAddrData(diagEcuAddr,true);

    ui->label_taskId_resp->setText(QString::fromStdString(taskId));
}

void DiagnoseForm::setReadDidData(DiagnoseNS::ReadDID &readDid)
{
    int readSize = readDid.readdidcontent_size();
    for(int i = 0;i<readSize;i++)
    {
        DIDContentForm* didContent = new  DIDContentForm;
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(240,136));
        ui->listWidget_readDid->addItem(item);
        ui->listWidget_readDid->setItemWidget(item,didContent);
    }
}

void DiagnoseForm::setWriteDidData(DiagnoseNS::WriteDID &writeDid)
{
    int writeSize = writeDid.writedidcontent_size();
    for(int i = 0;i<writeSize;i++)
    {
        DIDContentForm* didContent = new  DIDContentForm;
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(240,36));
        ui->listWidget_readDid->addItem(item);
        ui->listWidget_readDid->setItemWidget(item,didContent);
    }
}

void DiagnoseForm::setReadDtcData(DiagnoseNS::ReadDTC &readDtc)
{
    int ecuSize = readDtc.ecu_size();
    for(int i = 0;i<ecuSize;i++)
    {
        read_dtc_component->addEcus(readDtc.ecu(i));
    }

    read_dtc_resp_->setEcuDtcData(readDtc);
}

void DiagnoseForm::setCleanDtcData(DiagnoseNS::CleanDTC &cleanDtc)
{
    int ecuSize = cleanDtc.ecu_size();
    for(int i = 0;i<ecuSize;i++)
    {
        clean_dtc_component->addEcus(cleanDtc.ecu(i));
    }
}



















#include "RemoteControlWid.h"
#include "ui_RemoteControlWid.h"
#include "LocationForm.h"
#include "EfenceForm.h"
#include "SeatHeatForm.h"

RemoteControlWid::RemoteControlWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoteControlWid)
{
    ui->setupUi(this);
    initUI();
}

RemoteControlWid::~RemoteControlWid()
{
    delete ui;
}

void RemoteControlWid::initUI()
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

    eFence_wid_ = new EfenceForm;

    ui->verticalLayout_fence->addWidget(eFence_wid_);

    seat_heat_ = new SeatHeatForm;

    ui->verticalLayout_seatHeat->addWidget(seat_heat_);

    wid_control_type_map_.insert(ControlNS::ControlCommand::CONTROL_SET_ROUND_FENCE,eFence_wid_);
    wid_control_type_map_.insert(ControlNS::ControlCommand::CONTROL_SET_POLYGON_FENCE ,eFence_wid_);
    wid_control_type_map_.insert(ControlNS::ControlCommand::CONTROL_HEAT_SEAT,seat_heat_);
    wid_control_type_map_.insert(ControlNS::ControlCommand::CONTROL_HEAT_HANDLEBAR,seat_heat_);
    wid_control_type_map_.insert(ControlNS::ControlCommand::CONTROL_HEAT_RESERVE,seat_heat_);
    wid_control_type_map_.insert(ControlNS::ControlCommand::CONTROL_GET_POSITION,ui->groupBox_location);
    wid_control_type_map_.insert(ControlNS::ControlCommand::CONTROL_ENGINE_COMMAND,ui->widget_engine);
    wid_control_type_map_.insert(ControlNS::ControlCommand::CONTROL_FIND_CAR_COMMAND,ui->widget_findCar);
    wid_control_type_map_.insert(ControlNS::ControlCommand::CONTROL_TAKE_PARKING_PHOTO,ui->widget_photo);
    wid_control_type_map_.insert(ControlNS::ControlCommand::CONTROL_GET_TIER_PRESSURE,ui->groupBox_tire);
    ControlNS::Parameters para;
    ControlNS::ControlCommand cmd = ControlNS::ControlCommand::IN_VALID;
    showControlComponent(cmd,para);
}

void RemoteControlWid::setControl(ControlNS::Control &ctrl)
{
    setApplyBtnEnable(true);

    control_.CopyFrom(ctrl);

    std::string taskID = ctrl.taskid();
    int cmd = ctrl.command();
    ui->label_cmd->setText(QString("%1").arg(cmd));
    ControlNS::ControlCommand ctrlCmd = ctrl.controlcommand();
    int paraType = ctrl.paratype();
    ui->label_taskId->setText(QString::fromStdString(taskID));

    ui->label_paraType->setText(QString("%1").arg(paraType));


    ui->label_taskIdResp->setText(QString::fromStdString(taskID));
    ui->label_cmdResp->setText(QString("%1").arg(cmd));
    ui->label_paraTypeResp->setText(QString("%1").arg(paraType));

    std::cout<<"para type is :"<<paraType<<std::endl;
    ControlNS::Parameters para = ctrl.para();

    //widget show manage

    showControlComponent(ctrlCmd,para);

    switch(ctrlCmd)
    {
    case ControlNS::ControlCommand::CONTROL_ENGINE_COMMAND:
    {
        ui->comboBox_ctrlCmd->setCurrentIndex(1);

        ControlNS::ControlEnginePara enginePara = para.controlenginepara();
        ControlNS::EngineOpt engineOpt = enginePara.enginstart();
        std::cout<<"engineOPt "<<engineOpt<<std::endl;

        switch (engineOpt) {
        case ControlNS::EngineOpt::START:
        {
            std::cout<<"control engine start"<<std::endl;
            ui->comboBox_engine->setCurrentIndex(0);
        }
            break;
        case ControlNS::EngineOpt::STOP:
        {
            std::cout<<"control engine stop"<<std::endl;
            ui->comboBox_engine->setCurrentIndex(1);
        }
            break;
        default:
            break;
        }
    }
        break;
    case ControlNS::ControlCommand::CONTROL_FIND_CAR_COMMAND:
    {
        ui->comboBox_ctrlCmd->setCurrentIndex(2);

        ControlNS::ControlFindCarPara findCarPara = para.controlfindcarpara();
        ControlNS::FindCarOpt findCarOpt = findCarPara.findcaropt();
        switch (findCarOpt) {
        case ControlNS::FindCarOpt::LIGHT:
            std::cout<<"control find car by light"<<std::endl;
            ui->comboBox_findCar->setCurrentIndex(0);
            break;
        case ControlNS::FindCarOpt::HORN:
            std::cout<<"control find car by horn"<<std::endl;
            ui->comboBox_findCar->setCurrentIndex(1);
            break;
        case ControlNS::FindCarOpt::LIGHT_HORN:
            std::cout<<"control find car by light and horn"<<std::endl;
            ui->comboBox_findCar->setCurrentIndex(2);
            break;
        default:
            break;
        }
    }
        break;
    case ControlNS::ControlCommand::ENABLE_GEAR_REPORT:
        ui->comboBox_ctrlCmd->setCurrentIndex(3);
        break;
    case ControlNS::ControlCommand::CONTROL_GET_POSITION:
        ui->comboBox_ctrlCmd->setCurrentIndex(4);
        break;
    case ControlNS::ControlCommand::CONTROL_GET_TIER_PRESSURE:
        ui->comboBox_ctrlCmd->setCurrentIndex(5);
        break;
    case ControlNS::ControlCommand::CONTROL_TAKE_PARKING_PHOTO:
    {
        ui->comboBox_ctrlCmd->setCurrentIndex(6);

        ControlNS::ControlTakeParkingPhotoPara takePhtPara = para.controltakeparkingphotopara();
        ControlNS::CameraOpt cameraOpt = takePhtPara.cameraopt();

        switch (cameraOpt) {
        case ControlNS::CameraOpt::ALL:
            ui->comboBox_photo->setCurrentIndex(0);
            break;
        case ControlNS::CameraOpt::FRONT:
            ui->comboBox_photo->setCurrentIndex(1);
            break;
        case ControlNS::CameraOpt::REAR:
            ui->comboBox_photo->setCurrentIndex(2);
            break;
        case ControlNS::CameraOpt::LEFT:
            ui->comboBox_photo->setCurrentIndex(3);
            break;
        case ControlNS::CameraOpt::RIGHT:
            ui->comboBox_photo->setCurrentIndex(4);
            break;
        }
    }
        break;
    case ControlNS::ControlCommand::CONTROL_SET_ROUND_FENCE:
    {
        ui->comboBox_ctrlCmd->setCurrentIndex(7);
        ControlNS::ControlSetRoundFencePara roundFencePara = para.controlsetroundfencepara();
        eFence_wid_->setCircleFenceData(roundFencePara);
    }
        break;
    case ControlNS::ControlCommand::CONTROL_SET_POLYGON_FENCE:
    {
        ui->comboBox_ctrlCmd->setCurrentIndex(8);
        ControlNS::ControlSetPolygonFencePara polygonFencePara = para.controlsetpolygonfencepara();
        eFence_wid_->setPolygonFenceData(polygonFencePara);
    }
        break;
    case ControlNS::ControlCommand::CONTROL_CLEAR_FENCE:
    {
        ui->comboBox_ctrlCmd->setCurrentIndex(9);
    }
        break;
    case ControlNS::ControlCommand::CONTROL_HEAT_SEAT:
    {
        ui->comboBox_ctrlCmd->setCurrentIndex(10);
        ControlNS::ControlHeatSeatPara* heatSeatPara = para.mutable_controlheatseatpara();

        seat_heat_->setSeatHeatData(*heatSeatPara);
    }
        break;
    case ControlNS::ControlCommand::CONTROL_HEAT_HANDLEBAR:
    {
        ui->comboBox_ctrlCmd->setCurrentIndex(11);
        ControlNS::ControlHeatHandleBarPara* handleHeatPara = para.mutable_controlheathandlebarpara();
        seat_heat_->setHandleHeatData(*handleHeatPara);
    }
        break;
    case ControlNS::ControlCommand::CONTROL_HEAT_RESERVE:
    {
        ui->comboBox_ctrlCmd->setCurrentIndex(12);
        ControlNS::ControlHeatReservePara* reserveHeatPara = para.mutable_controlheatreservepara();
        seat_heat_->setHeatReserveData(*reserveHeatPara);
    }
        break;
    case ControlNS::ControlCommand::IN_VALID:
    {
        ui->comboBox_ctrlCmd->setCurrentIndex(0);
    }
    case ControlNS::ControlCommand::CONTROL_GET_SIGNAL_INTENSITY:
    {

    }
        break;
    case ControlNS::ControlCommand::CONTROL_GET_APN_NAME:
    {

    }
        break;
     case ControlNS::ControlCommand::CONTROL_SET_FREQUENCY:
    {

    }
        break;
     case ControlNS::ControlCommand::CONTROL_SET_APN_NAME:
    {

    }
        break;
    case ControlNS::ControlCommand::CONTROL_SET_SENTINEL_MODE:
    {

    }
        break;
    case ControlNS::ControlCommand::CONTROL_GET_ECU_VERSION:
    {

    }
        break;
    default:

        break;
    }

}


void RemoteControlWid::showControlComponent(ControlNS::ControlCommand &ctrlCmd, ControlNS::Parameters &para)
{

    QMap<ControlNS::ControlCommand,QWidget*>::iterator iter = wid_control_type_map_.begin();

    for(;iter != wid_control_type_map_.end();iter++)
    {

        if(iter.key()==ctrlCmd)
        {
            iter.value()->setVisible(true);
        }
        else
        {
            iter.value()->setVisible(false);
        }

        if(ctrlCmd == ControlNS::ControlCommand::CONTROL_HEAT_HANDLEBAR||ctrlCmd == ControlNS::ControlCommand::CONTROL_HEAT_RESERVE||
                ctrlCmd == ControlNS::ControlCommand::CONTROL_HEAT_SEAT)
        {
            seat_heat_->setVisible(true);
        }

        if(ctrlCmd == ControlNS::CONTROL_SET_POLYGON_FENCE||ctrlCmd == ControlNS::CONTROL_SET_ROUND_FENCE)
        {
            eFence_wid_->setVisible(true);
        }
    }

    switch (ctrlCmd) {
    case ControlNS::ControlCommand::CONTROL_HEAT_HANDLEBAR:
        seat_heat_->setHandleHeat();
        std::cout<<"setHandleHeat...."<<std::endl;
        break;
    case ControlNS::ControlCommand::CONTROL_HEAT_RESERVE:
    {
        ControlNS::ControlHeatReservePara heatReservePara = para.controlheatreservepara();
        ControlNS::ControlCommand heatCmd = heatReservePara.reservation();

        switch (heatCmd) {
        case ControlNS::ControlCommand::CONTROL_HEAT_HANDLEBAR:
            seat_heat_->setHeatReserve(true);
            break;
        case ControlNS::ControlCommand::CONTROL_HEAT_SEAT:
            seat_heat_->setHeatReserve(false);
            break;
        }
    }
        break;
    case ControlNS::ControlCommand::CONTROL_HEAT_SEAT:
        seat_heat_->setSeatHeat();
        std::cout<<"setSeatHeat...."<<std::endl;
        break;
    case ControlNS::ControlCommand::CONTROL_SET_POLYGON_FENCE:
        eFence_wid_->showCircleFence(false);
        break;
    case ControlNS::ControlCommand::CONTROL_SET_ROUND_FENCE:
        eFence_wid_->showCircleFence(true);
        break;
    }
}

void RemoteControlWid::setApplyBtnEnable(bool enable)
{
    QString styleSheetStr ;
    if(enable)
    {
        styleSheetStr = "QPushButton{background-color:green;color:white;}";
    }
    else
    {
        styleSheetStr = "QPushButton{background-color:gray;color:white;}";
    }

    ui->pushButton_apply->setStyleSheet(styleSheetStr);
    ui->pushButton_apply->setEnabled(enable);
}

void RemoteControlWid::reset()
{
    this->blockSignals(true);
    ui->widget_engine->setVisible(false);
    ui->widget_findCar->setVisible(false);
    ui->widget_photo->setVisible(false);
    eFence_wid_->setVisible(false);
    ui->comboBox_ctrlCmd->setCurrentIndex(0);
    ui->label_taskIdResp->clear();
    ui->label_taskId->clear();
    ui->groupBox_tire->setVisible(false);
    ui->groupBox_location->setVisible(false);
    ui->label_cmd->clear();
    ui->label_cmdResp->clear();
    ui->label_paraType->clear();
    ui->label_paraTypeResp->clear();
    seat_heat_->setVisible(false);
    this->blockSignals(false);
}

void RemoteControlWid::on_pushButton_apply_clicked()
{
    ControlNS::ControlResponse *contrlResp = control_.mutable_controlresponse();
    ControlNS::Parameters* para  = control_.mutable_para();
    if(ui->widget_engine->isVisible())
    {

        ControlNS::ControlEngineResponse* engResp = contrlResp->mutable_controlengineresponse();
        engResp->set_result(ui->comboBox_result->currentData().toUInt());
    }

    if(ui->widget_findCar->isVisible())
    {
        ControlNS::ControlFindCarResponse* findCarResp = contrlResp->mutable_controlfindcarresponse();
        findCarResp->set_result(ui->comboBox_result->currentData().toUInt());
    }

    if(ui->comboBox_photo->isVisible())
    {
        ControlNS::ControlTakeParkingPhotoResponse  * takePhtResp = contrlResp->mutable_controltakeparkingphotoresponse();
        takePhtResp->set_result(ui->comboBox_result->currentData().toUInt());
    }

    if(ui->groupBox_location->isVisible())
    {
        ControlNS::ControlGetPositionResponse* getPosResp = contrlResp->mutable_controlgetpositionresponse();
        getPosResp->set_result(ui->comboBox_result->currentData().toUInt());

        ControlNS::ControlGetPositionPara* posPara = para->mutable_controlgetpositionpara();

        std::string* loc = posPara->mutable_location();

        LocationNS::Location * location = new LocationNS::Location();
        location->ParseFromString(*loc);
        location_->getLocation(*location);
    }

    if(ui->groupBox_tire->isVisible())
    {
        ControlNS::ControlGetTPMSResponse * getTpmResp = contrlResp->mutable_controlgettpmsresponse();

        getTpmResp->set_result(ui->comboBox_result->currentData().toUInt());

        ControlNS::ControlGetTPMSPara * tmpPara = para->mutable_controlgettmpspara();

        StatusNS::TpmsInfo * tmpSts = tmpPara->mutable_tpmsinfo();

        tmpSts->set_fronttiertemp(ui->lineEdit_frontTemp->text().toInt());
        tmpSts->set_reartiretemp(ui->lineEdit_rearTemp->text().toInt());
        tmpSts->set_fronttirepressure(ui->lineEdit_frontPressure->text().toInt());
        tmpSts->set_reartirepressure(ui->lineEdit_rearPressure->text().toInt());
        tmpSts->set_status(ui->lineEdit_status->text().toInt());
    }
    std::cout<<"result is "<<ui->comboBox_result->currentData().toUInt()<<std::endl;
    std::string contrlStr = control_.SerializeAsString();

    reset();

    emit responseToControl(QString::fromStdString(contrlStr));

    setApplyBtnEnable(false);
}


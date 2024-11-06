#include "EventForm.h"
#include "ui_EventForm.h"
#include "LocationForm.h"
#include "BatteryInfoForm.h"
#include "LampForm.h"
#include <QUuid>

EventForm::EventForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventForm)
{
    ui->setupUi(this);
    initUI();
    win_group_map_.insert(EventNS::EventItem::INVALID,nullptr);
    win_group_map_.insert(EventNS::EventItem::ENGINE_ON_OFF,ui->groupBox_engineOnOff);
    win_group_map_.insert(EventNS::EventItem::GEAR_POSITION,ui->groupBox_gear);
    win_group_map_.insert(EventNS::EventItem::BATTERY_QTY,ui->groupBox_bmsInfo);
    win_group_map_.insert(EventNS::EventItem::SK_FAULT,ui->groupBox_fault);
    win_group_map_.insert(EventNS::EventItem::SIDE_STAND_LOWER_RAISE,ui->groupBox_sidestand);
    win_group_map_.insert(EventNS::EventItem::LAMP_ON_OFF,ui->groupBox_lamp );
    win_group_map_.insert(EventNS::EventItem::SEAT_BUCKET_OPEN_CLOSE,ui->groupBox_seatBucket);
}

EventForm::~EventForm()
{
    delete ui;
}

void EventForm::initUI()
{
    locationForm_ = new LocationForm;
    ui->layout_location->addWidget(locationForm_);
}

void EventForm::setData(EventNS::EventMsg &eventMsg)
{

    ui->checkBox_kl15->setChecked(eventMsg.engineonoff().kl15());

    ui->lineEdit_taskId->setText(QString::fromStdString(eventMsg.engineonoff().taskid()));

    ui->lineEdit_power->setText(QString("%1").arg(eventMsg.engineonoff().power()));
    std::string location = eventMsg.engineonoff().location();
    locationForm_->setData(location);

    ui->lineEdit_enduranceMile->setText(QString("%1").arg(eventMsg.engineonoff().hmiinfo().endurancemileage()));
    ui->lineEdit_speed->setText(QString("%1").arg(eventMsg.engineonoff().hmiinfo().speed()));
    ui->lineEdit_revSpeed->setText(QString("%1").arg(eventMsg.engineonoff().hmiinfo().revspeed()));
    ui->lineEdit_odoMetro->setText(QString("%1").arg(eventMsg.engineonoff().hmiinfo().odometro()));
    ui->comboBox_gear->setCurrentIndex(eventMsg.engineonoff().hmiinfo().gearposition());

    ui->lineEdit_blueToothMac->setText(QString::fromStdString(eventMsg.engineonoff().bluetoothinfo().bluetoothmac()));
    ui->lineEdit_blueToothName->setText(QString::fromStdString(eventMsg.engineonoff().bluetoothinfo().bluetoothname()));
    ui->lineEdit_blueToothPwd->setText(QString::fromStdString(eventMsg.engineonoff().bluetoothinfo().bluetoothpwd()));
    ui->lineEdit_blueToothSecretKey->setText(QString::fromStdString(eventMsg.engineonoff().bluetoothinfo().bluetoothsecretkey()));

    for(int i = 0;i<eventMsg.batteryinfo_size();i++)
    {
        EventNS::BatteryInfo battery = eventMsg.batteryinfo(i);
        addBattery(battery);
    }

    ui->lineEdit_mcuFault->setText(QString::fromStdString(eventMsg.skfaultinfo().mcufault()));
    ui->lineEdit_bmsFault->setText(QString::fromStdString(eventMsg.skfaultinfo().bmsfault()));

    for(int i = 0;i<eventMsg.lamps_size();i++)
    {

        EventNS::LampInfo lampInfo = eventMsg.lamps(i);
        addLamp(lampInfo);
    }

    EventNS::SeatBucketOpenClose type = eventMsg.seatbucketopenclose();
    bool isClose = type.status()==EventNS::SeatBucketStatus::CLOSE?true:false;
    ui->radioButton_close->setChecked(isClose);
    ui->radioButton_open->setChecked(!isClose);

    EventNS::SideStandInfo sideStand = eventMsg.sidestandinfo();
    bool isRaise = sideStand.status()== EventNS::SideStandStatus::RAISE?true:false;
    ui->radioButton_raise->setChecked(isRaise);
    ui->radioButton_lower->setChecked(!isRaise);

    StatusNS::GearPosition gearPos = eventMsg.gearposition();

    ui->comboBox_gear_single->setCurrentIndex(gearPos);

}

void EventForm::getEventEngineOnOff(EventNS::EngineOnOff &eventOnOff)
{
    eventOnOff.set_kl15(ui->checkBox_kl15->isChecked());
    eventOnOff.set_taskid(ui->lineEdit_taskId->text().toStdString());
    eventOnOff.set_power(ui->lineEdit_power->text().toUInt());
    std::string* loc = eventOnOff.mutable_location();
    //TODO
    LocationNS::Location location ;
    std::cout<<"getEventEngineOnOff --------------0"<<std::endl;
    locationForm_->getLocation(location);
    *loc = location.SerializeAsString();

    std::cout<<"getEventEngineOnOff --------------1"<<std::endl;
    StatusNS::HmiInfo* hmiInfo = eventOnOff.mutable_hmiinfo();
    hmiInfo->set_endurancemileage(ui->lineEdit_enduranceMile->text().toUInt());
    hmiInfo->set_gearposition(::StatusNS::GearPosition(ui->comboBox_gear->currentIndex()));
    hmiInfo->set_revspeed(ui->lineEdit_revSpeed->text().toUInt());
    hmiInfo->set_odometro(ui->lineEdit_odoMetro->text().toUInt());
    hmiInfo->set_speed(ui->lineEdit_speed->text().toUInt());

    EventNS::BluetoothInfo* blueTooth = eventOnOff.mutable_bluetoothinfo();

    blueTooth->set_bluetoothmac(ui->lineEdit_blueToothMac->text().toStdString());
    blueTooth->set_bluetoothname(ui->lineEdit_blueToothName->text().toStdString());
    blueTooth->set_bluetoothpwd(ui->lineEdit_blueToothPwd->text().toStdString());
    blueTooth->set_bluetoothsecretkey(ui->lineEdit_blueToothSecretKey->text().toStdString());

}

void EventForm::getBatteryInfo(EventNS::EventMsg &eventMsg)
{
    for(int i = 0;i<ui->listWidget_battery->count();i++)
    {
        EventNS::BatteryInfo* batteryInfo = eventMsg.add_batteryinfo();
        QListWidgetItem* item = ui->listWidget_battery->item(i);
        BatteryInfoForm* wid = dynamic_cast<BatteryInfoForm*>(ui->listWidget_battery->itemWidget(item));
        wid->getBatteryInfo(*batteryInfo);
    }
}

void EventForm::getSKFaultInfo(EventNS::SKFaultInfo &skFaultInfo)
{
    skFaultInfo.set_bmsfault(ui->lineEdit_bmsFault->text().toStdString().c_str());
    skFaultInfo.set_mcufault(ui->lineEdit_mcuFault->text().toStdString().c_str());
}

void EventForm::getSideStandInfo(EventNS::SideStandInfo &sideStand)
{

   ui->radioButton_lower->isChecked()? sideStand.set_status(EventNS::SideStandStatus::LOWER):sideStand.set_status(EventNS::SideStandStatus::RAISE);
}

void EventForm::getSeatBucketInfo(EventNS::SeatBucketOpenClose &seatInfo)
{
    ui->radioButton_open->isChecked()?seatInfo.set_status(EventNS::SeatBucketStatus::OPEN):seatInfo.set_status(EventNS::SeatBucketStatus::CLOSE);
}

void EventForm::getLampInfo(EventNS::EventMsg &eventMsg)
{
    for(int i = 0;i<ui->listWidget_lamp->count();i++)
    {
        EventNS::LampInfo* lampInfo = eventMsg.add_lamps();
        QListWidgetItem* item = ui->listWidget_lamp->item(i);
        LampForm* wid = dynamic_cast<LampForm*>(ui->listWidget_lamp->itemWidget(item));
        wid->getLampInfo(*lampInfo);
    }
}

void EventForm::getGearPosition(EventNS::EventMsg &eventMsg)
{
    eventMsg.set_gearposition((StatusNS::GearPosition)ui->comboBox_gear_single->currentIndex());
}

void EventForm::addBattery(EventNS::BatteryInfo &battery)
{
    static int  index = ui->listWidget_battery->count();
    BatteryInfoForm * batteryItem = new BatteryInfoForm;
    batteryItem->setData(battery);
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(240,60));
    ui->listWidget_battery->addItem(item);
    ui->listWidget_battery->setItemWidget(item,batteryItem);
    batteryItem->setProperty("index",index);
    connect(batteryItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteBatteryItem(int)));
    index++;
}

void EventForm::addLamp(EventNS::LampInfo &lampInfo)
{
    static int  index = ui->listWidget_lamp->count();
    LampForm * lampItem = new LampForm;
    lampItem->setData(lampInfo);
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(240,40));
    ui->listWidget_lamp->addItem(item);
    ui->listWidget_lamp->setItemWidget(item,lampItem);
    lampItem->setProperty("index",index);
    connect(lampItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteLampItem(int)));
    index++;
}

void EventForm::showGroupBoxByType(EventNS::EventItem item)
{
    QMap<EventNS::EventItem,QGroupBox*>::Iterator iter =  win_group_map_.begin();
    for(;iter!=win_group_map_.end();iter++)
    {
       if(iter.value()){
        iter.value()->setVisible(false);
       }

    }

   iter =  win_group_map_.begin();
    for(;iter!=win_group_map_.end();iter++)
    {
        if(iter.key()==item)
        {
            iter.value()->setVisible(true);
        }
    }
}

QString EventForm::getTaskId()
{
    return ui->lineEdit_taskId->text();
}

void EventForm::on_pushButton_addBattery_clicked()
{
    static int  index = ui->listWidget_battery->count();
    BatteryInfoForm * batteryItem = new BatteryInfoForm;
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(240,60));
    ui->listWidget_battery->addItem(item);
    ui->listWidget_battery->setItemWidget(item,batteryItem);
    batteryItem->setProperty("index",index);
    connect(batteryItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteBatteryItem(int)));
    index++;
}

void EventForm::slot_deleteBatteryItem(int index)
{
    for(int i = 0;i<ui->listWidget_battery->count();i++)
    {
        QListWidgetItem* item = ui->listWidget_battery->item(i);
        BatteryInfoForm* wid = dynamic_cast<BatteryInfoForm*>(ui->listWidget_battery->itemWidget(item));

        if(wid->property("index").toUInt()== index)
        {
            ui->listWidget_battery->removeItemWidget(item);
            delete  wid;
            delete  item;
            break;
        }
    }
}

void EventForm::on_pushButton_addLamp_clicked()
{
    static int  index = ui->listWidget_lamp->count();
    LampForm * lampItem = new LampForm;
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(240,40));
    ui->listWidget_lamp->addItem(item);
    ui->listWidget_lamp->setItemWidget(item,lampItem);
    lampItem->setProperty("index",index);
    connect(lampItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteLampItem(int)));
    index++;
}

void EventForm::slot_deleteLampItem(int index)
{
    for(int i = 0;i<ui->listWidget_lamp->count();i++)
    {
        QListWidgetItem* item = ui->listWidget_lamp->item(i);
        LampForm* wid = dynamic_cast<LampForm*>(ui->listWidget_lamp->itemWidget(item));

        if(wid->property("index").toUInt()== index)
        {
            ui->listWidget_lamp->removeItemWidget(item);
            delete  wid;
            delete  item;
            break;
        }
    }
}


void EventForm::on_radioButton_open_clicked()
{

}


void EventForm::on_radioButton_close_clicked()
{

}


void EventForm::on_radioButton_raise_clicked()
{

}


void EventForm::on_radioButton_lower_clicked()
{

}


void EventForm::on_pushButton_taskId_clicked()
{
    QUuid uuid = QUuid::createUuid();
    ui->lineEdit_taskId->setText(uuid.toString());
}


#include "TboxSkInfoForm.h"
#include "ui_TboxSkInfoForm.h"
#include "CanInfoForm.h"
#include <QListWidget>
#include<QListWidgetItem>
#include "protoBuf/location.pb.h"

TboxSkInfoForm::TboxSkInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TboxSkInfoForm)
{
    ui->setupUi(this);
    QPalette palette = ui->listWidget->palette();
    palette.setColor(QPalette::Highlight,QColor::fromRgb(188,188,188));
    ui->listWidget->setPalette(palette);
}

TboxSkInfoForm::~TboxSkInfoForm()
{
    delete ui;
}

void TboxSkInfoForm::initData(StatusNS::TboxSKInfo &status)
{
    ui->checkBox_kl15->setChecked(status.kl15());
    ui->lineEdit_kl30->setText(QString("%1").arg(status.kl30()));
    ui->lineEdit_batteryVol->setText(QString("%1").arg(status.batteryvoltage()));
    ui->lineEdit_csq->setText(QString("%1").arg(status.csq()));
    ui->lineEdit_emergencyBrakeCount->setText(QString("%1").arg(status.emergencybrakecount()));
    ui->lineEdit_rapidAccelerationCount->setText(QString("%1").arg(status.rapidaccelerationcount()));
    ui->lineEdit_rapidDeceleartionCount->setText(QString("%1").arg(status.rapiddecelerationcount()));
    std::string loc = status.location();
    LocationNS::Location location ;
    location.ParseFromString(loc);
    ui->lineEdit_altitude->setText(QString("%1").arg(location.altitude()));
    ui->lineEdit_angle->setText(QString("%1").arg(location.angle()));
    ui->lineEdit_latitude->setText(QString("%1").arg(location.latitude()));
    ui->lineEdit_satNumber->setText(QString("%1").arg(location.satnumber()));
    ui->lineEdit_longitude->setText(QString("%1").arg(location.longitude()));
    ui->lineEdit_hemisphere->setText(QString("%1").arg(location.hemisphere()));
    ui->lineEdit_speed->setText(QString("%1").arg(location.speed()));
    ui->lineEdit_timestamp->setText(QString("%1").arg(location.timestamp()));
    ui->checkBox_valid->setChecked(location.valid());
    ui->lineEdit_batteryVol->setText(QString("%1").arg(status.batteryvoltage()));
    ui->lineEdit_sharpTurnCount->setText(QString("%1").arg(status.sharpturncount()));


    for(int i = 0;i<status.caninfo_size();i++)
    {
        StatusNS::CanInfo canInfo = status.caninfo(i);
        static int  index = 0;
        CanInfoForm* can = new CanInfoForm;
        can->initData(canInfo);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(this->width()-20,40));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,can);
        can->setProperty("index",index);
        connect(can,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
        index++;
    }
}

void TboxSkInfoForm::initData(StatusNS::TboxInfo &tbxInfo)
{
    ui->checkBox_kl15->setChecked(tbxInfo.kl15());
    ui->lineEdit_kl30->setText(QString("%1").arg(tbxInfo.kl30()));
    ui->lineEdit_batteryVol->setText(QString("%1").arg(tbxInfo.batteryvoltage()));
    ui->lineEdit_csq->setText(QString("%1").arg(tbxInfo.csq()));
    ui->lineEdit_emergencyBrakeCount->setText(QString("%1").arg(tbxInfo.emergencybrakecount()));
    ui->lineEdit_rapidAccelerationCount->setText(QString("%1").arg(tbxInfo.rapidaccelerationcount()));
    ui->lineEdit_rapidDeceleartionCount->setText(QString("%1").arg(tbxInfo.rapiddecelerationcount()));
    std::string loc = tbxInfo.location();
    LocationNS::Location location ;
    location.ParseFromString(loc);
    ui->lineEdit_altitude->setText(QString("%1").arg(location.altitude()));
    ui->lineEdit_angle->setText(QString("%1").arg(location.angle()));
    ui->lineEdit_latitude->setText(QString("%1").arg(location.latitude()));
    ui->lineEdit_satNumber->setText(QString("%1").arg(location.satnumber()));
    ui->lineEdit_longitude->setText(QString("%1").arg(location.longitude()));
    ui->lineEdit_hemisphere->setText(QString("%1").arg(location.hemisphere()));
    ui->lineEdit_speed->setText(QString("%1").arg(location.speed()));
    ui->lineEdit_timestamp->setText(QString("%1").arg(location.timestamp()));
    ui->checkBox_valid->setChecked(location.valid());
    ui->lineEdit_batteryVol->setText(QString("%1").arg(tbxInfo.batteryvoltage()));
    ui->lineEdit_sharpTurnCount->setText(QString("%1").arg(tbxInfo.sharpturncount()));


    for(int i = 0;i<tbxInfo.caninfo_size();i++)
    {
        StatusNS::CanInfo canInfo = tbxInfo.caninfo(i);
        static int  index = 0;
        CanInfoForm* can = new CanInfoForm;
        can->initData(canInfo);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(this->width()-20,40));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,can);
        can->setProperty("index",index);
        connect(can,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
        index++;
    }
}

bool TboxSkInfoForm::getTboxSkInfo(StatusNS::TboxSKInfo &status)
{

    tbxSkInfo_.set_kl15(ui->checkBox_kl15->isChecked());
    tbxSkInfo_.set_kl30(ui->lineEdit_kl30->text().toUInt());
    tbxSkInfo_.set_batteryvoltage(ui->lineEdit_batteryVol->text().toUInt());
    tbxSkInfo_.set_csq(ui->lineEdit_csq->text().toUInt());
    tbxSkInfo_.set_rapiddecelerationcount(ui->lineEdit_rapidDeceleartionCount->text().toUInt());
    tbxSkInfo_.set_rapidaccelerationcount(ui->lineEdit_rapidAccelerationCount->text().toUInt());
    tbxSkInfo_.set_emergencybrakecount(ui->lineEdit_emergencyBrakeCount->text().toUInt());
    tbxSkInfo_.set_sharpturncount(ui->lineEdit_sharpTurnCount->text().toUInt());
    std::string* loc = tbxSkInfo_.mutable_location();
    LocationNS::Location location;
    location.set_altitude(ui->lineEdit_altitude->text().toUInt());
    location.set_angle(ui->lineEdit_angle->text().toUInt());
    location.set_longitude(ui->lineEdit_longitude->text().toUInt());
    location.set_satnumber(ui->lineEdit_satNumber->text().toUInt());
    location.set_timestamp(ui->lineEdit_timestamp->text().toInt());
    location.set_hemisphere(ui->lineEdit_hemisphere->text().toUInt());
    location.set_speed(ui->lineEdit_speed->text().toUInt());
    location.set_valid(ui->checkBox_valid->isChecked());
    location.set_latitude(ui->lineEdit_latitude->text().toUInt());
    *loc = location.SerializeAsString();
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        CanInfoForm* canWid = dynamic_cast<CanInfoForm*>(ui->listWidget->itemWidget(item));
        StatusNS::CanInfo* canInfo = tbxSkInfo_.add_caninfo();
        canWid->getCanInfo(*canInfo);
    }
    status.CopyFrom(tbxSkInfo_);

    return  true;
}

bool TboxSkInfoForm::getTboxInfo(StatusNS::TboxInfo &tbxInfo)
{
    tbxInfo.set_kl15(ui->checkBox_kl15->isChecked());
    tbxInfo.set_kl30(ui->lineEdit_kl30->text().toUInt());
    tbxInfo.set_batteryvoltage(ui->lineEdit_batteryVol->text().toUInt());
    tbxInfo.set_csq(ui->lineEdit_csq->text().toUInt());
    tbxInfo.set_rapiddecelerationcount(ui->lineEdit_rapidDeceleartionCount->text().toUInt());
    tbxInfo.set_rapidaccelerationcount(ui->lineEdit_rapidAccelerationCount->text().toUInt());
    tbxInfo.set_emergencybrakecount(ui->lineEdit_emergencyBrakeCount->text().toUInt());
    tbxInfo.set_sharpturncount(ui->lineEdit_sharpTurnCount->text().toUInt());
    std::string* loc = tbxInfo.mutable_location();
    LocationNS::Location location;
    location.set_altitude(ui->lineEdit_altitude->text().toUInt());
    location.set_angle(ui->lineEdit_angle->text().toUInt());
    location.set_longitude(ui->lineEdit_longitude->text().toUInt());
    location.set_satnumber(ui->lineEdit_satNumber->text().toUInt());
    location.set_timestamp(ui->lineEdit_timestamp->text().toInt());
    location.set_hemisphere(ui->lineEdit_hemisphere->text().toUInt());
    location.set_speed(ui->lineEdit_speed->text().toUInt());
    location.set_valid(ui->checkBox_valid->isChecked());
    location.set_latitude(ui->lineEdit_latitude->text().toUInt());
    *loc = location.SerializeAsString();
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        CanInfoForm* canWid = dynamic_cast<CanInfoForm*>(ui->listWidget->itemWidget(item));
        StatusNS::CanInfo* canInfo = tbxInfo.add_caninfo();
        canWid->getCanInfo(*canInfo);
    }

    return  true;
}

void TboxSkInfoForm::on_pushButton_addCanInfo_clicked()
{
    static int  index = 0;
    CanInfoForm* can = new CanInfoForm;
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(this->width()-20,40));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,can);
    can->setProperty("index",index);
    connect(can,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));

    index++;
}

void TboxSkInfoForm::slot_deleteItem(int index)
{
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        CanInfoForm* wid = dynamic_cast<CanInfoForm*>(ui->listWidget->itemWidget(item));

        if(wid->property("index").toUInt()== index)
        {
            ui->listWidget->removeItemWidget(item);
            delete  wid;
            delete  item;
            break;
        }

    }
}


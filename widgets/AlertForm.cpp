#include "AlertForm.h"
#include "ui_AlertForm.h"

AlertForm::AlertForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlertForm)
{
    ui->setupUi(this);
}

AlertForm::~AlertForm()
{
    delete ui;
}

bool AlertForm::getAlertMsg(AlertNS::AlertMsg &alertMsg)
{
    AlertNS::AlertItem item =(AlertNS::AlertItem)ui->comboBox->currentIndex();
//    switch (ui->comboBox->currentIndex()) {
//    case 0:
//        item = AlertNS::UNKNOWN;
//        break;
//    case 1:
//        item = AlertNS::ALERT_Vibration;
//        break;
//    case 2:
//        item =AlertNS::ALERT_Position_Move;
//        break;
//    case 3:
//        item = AlertNS::ALERT_FP_LEAK;
//        break;
//    case 4:
//        item = AlertNS::ALERT_RP_LEAK;
//        break;
//    case 5:
//        item = AlertNS::ALERT_TYRE_HIGH_TEMP;
//        break;
//    case 6:
//        item = AlertNS::ALERT_RP_HIGH_PRESSURE;
//        break;
//    case 7:
//        item = AlertNS::ALERT_FP_LOW_PRESSURE;
//        break;
//    case 8:
//        item = AlertNS::ALERT_RP_LOW_PRESSURE;
//        break;
//    case 9:
//        break;
//    default:
//        break;

//    }
    alertMsg.set_alertitem(item);
    alertMsg.set_status(ui->checkBox->isChecked());
}

void AlertForm::setData(AlertNS::AlertMsg &alertMsg)
{
   ui->checkBox->setChecked(alertMsg.status());
   ui->comboBox->setCurrentIndex(alertMsg.alertitem());
}

void AlertForm::on_btn_del_clicked()
{
    int idex = this->property("index").toUInt();
   emit deleteSignal(idex);
}


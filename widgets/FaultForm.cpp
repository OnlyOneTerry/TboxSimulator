#include "FaultForm.h"
#include "ui_FaultForm.h"

FaultForm::FaultForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FaultForm)
{
    ui->setupUi(this);
}

FaultForm::~FaultForm()
{
    delete ui;
}

void FaultForm::setData(FaultNS::FaultMsg &faultMsg)
{
    ui->lineEdit_counter->setText(QString("%1").arg(faultMsg.faultitem().counter()));
    ui->lineEdit_fmi->setText(QString("%1").arg(faultMsg.faultitem().fmi()));
    ui->lineEdit_model->setText(QString("%1").arg(faultMsg.faultitem().model()));
    ui->lineEdit_spn->setText(QString("%1").arg(faultMsg.faultitem().spn()));
    ui->checkBox_status->setChecked(faultMsg.status());
}

bool FaultForm::getFaultMsg(FaultNS::FaultMsg &faultMsg)
{
    FaultNS::FaultItem* faultItem = faultMsg.mutable_faultitem();
    faultItem->set_counter(ui->lineEdit_counter->text().toUInt());
    faultItem->set_fmi(ui->lineEdit_fmi->text().toUInt());
    faultItem->set_model(ui->lineEdit_model->text().toUInt());
    faultItem->set_spn(ui->lineEdit_spn->text().toUInt());
    faultMsg.set_status(ui->checkBox_status->isChecked());
}

void FaultForm::on_btn_del_clicked()
{
    int idex = this->property("index").toUInt();
    emit deleteSignal(idex);
}


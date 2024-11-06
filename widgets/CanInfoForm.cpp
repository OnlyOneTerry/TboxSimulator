#include "CanInfoForm.h"
#include "ui_CanInfoForm.h"

CanInfoForm::CanInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CanInfoForm)
{
    ui->setupUi(this);
}

CanInfoForm::~CanInfoForm()
{
    delete ui;
}

bool CanInfoForm::getCanInfo(StatusNS::CanInfo &canInfo)
{
    canInfo_.set_canchannel(ui->lineEdit_canChannel->text().toUInt());
    canInfo_.set_busoff(ui->checkBox_busoff->isChecked());
    canInfo_.set_noack(ui->checkBox_noAck->isChecked());
    canInfo_.set_recvnum(ui->lineEdit_recvNum->text().toUInt());
    canInfo_.set_sendnum(ui->lineEdit_sendNum->text().toUInt());

    canInfo.CopyFrom(canInfo_);
    return true;
}

void CanInfoForm::initData(StatusNS::CanInfo &canInfo)
{
    ui->lineEdit_canChannel->setText(QString("%1").arg(canInfo.canchannel()));
    ui->checkBox_busoff->setChecked(canInfo.busoff());
    ui->checkBox_noAck->setChecked(canInfo.noack());
    ui->lineEdit_recvNum->setText(QString("%1").arg(canInfo.recvnum()));
    ui->lineEdit_sendNum->setText(QString("%1").arg(canInfo.sendnum()));
}

void CanInfoForm::on_btn_del_clicked()
{
    int index = this->property("index").toUInt();
     emit deleteSignal(index);
}


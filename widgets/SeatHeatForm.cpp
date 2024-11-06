#include "SeatHeatForm.h"
#include "ui_SeatHeatForm.h"

SeatHeatForm::SeatHeatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeatHeatForm)
{
    ui->setupUi(this);

    ui->groupBox_HandleHeat->setVisible(false);
    ui->groupBox_HeatReserve->setVisible(false);
    ui->groupBox_seatHeat->setVisible(false);
}

SeatHeatForm::~SeatHeatForm()
{
    delete ui;
}

void SeatHeatForm::setHandleHeat()
{
    ui->groupBox_HandleHeat->setVisible(true);
    ui->groupBox_HeatReserve->setVisible(false);
    ui->groupBox_seatHeat->setVisible(false);
}

void SeatHeatForm::setSeatHeat()
{
    ui->groupBox_HandleHeat->setVisible(false);
    ui->groupBox_HeatReserve->setVisible(false);
    ui->groupBox_seatHeat->setVisible(true);
}

void SeatHeatForm::setHeatReserve(bool isHeatHandle)
{
    ui->groupBox_HandleHeat->setVisible(false);
    ui->groupBox_seatHeat->setVisible(false);
    ui->groupBox_HeatReserve->setVisible(true);
    ui->widget_handleReserve->setVisible(isHeatHandle);
    ui->widget_seatReserve->setVisible(!isHeatHandle);
}

void SeatHeatForm::setSeatHeatData(ControlNS::ControlHeatSeatPara &heatSeatPara)
{
    int level = heatSeatPara.level()-1;
    level = level>0?level:0;
    ui->comboBox_handle_level->setCurrentIndex(level);
    ui->comboBox_handle_switch->setCurrentIndex(heatSeatPara.switch_());

}

void SeatHeatForm::setHandleHeatData(ControlNS::ControlHeatHandleBarPara &handleBarPara)
{
    ui->comboBox_seat_h_level->setCurrentIndex(handleBarPara.level());
    ui->comboBox_handle_switch->setCurrentIndex(handleBarPara.switch_());
    ui->comboBox_handle_type->setCurrentIndex(handleBarPara.type());
}

void SeatHeatForm::setHeatReserveData(ControlNS::ControlHeatReservePara &reservePara)
{
    ControlNS::ControlCommand cmd = reservePara.reservation();
    switch (cmd) {
    case ControlNS::ControlCommand::CONTROL_HEAT_SEAT:
    {
        int level = reservePara.heatseatpara().level()-1;
        level = level>0?level:0;
        ui->comboBox_handle_level->setCurrentIndex(level);
        ui->comboBox_handle_switch->setCurrentIndex(reservePara.heatseatpara().switch_());
    }
        break;
    case ControlNS::ControlCommand::CONTROL_HEAT_HANDLEBAR:
    {
        int level = reservePara.heatseatpara().level()-1;
        level = level>0?level:0;
        ui->comboBox_reserve_handle_level->setCurrentIndex(level);
        ui->comboBox_reserve_handle_switch->setCurrentIndex(reservePara.heathandlebarpara().switch_());
        ui->comboBox_reserve_handle_type->setCurrentIndex(reservePara.heathandlebarpara().type());
    }
        break;
    }
    ui->lineEdit_reserve_appoint->setText(QString("%1").arg(reservePara.appointment()));
    int cmdIndex  = 0;
    if(reservePara.reservation()==ControlNS::ControlCommand::CONTROL_HEAT_SEAT)
    {
        cmdIndex = 0;
    }
    else{
        cmdIndex = 1;
    }

    ui->comboBox_reservation_cmd->setCurrentIndex(cmdIndex);

    //std::cout<<"level is :"<<reservePara.has_heathandlebarpara()

}

#ifndef SEATHEATFORM_H
#define SEATHEATFORM_H

#include <QWidget>
#include "protoBuf/control.pb.h"

namespace Ui {
class SeatHeatForm;
}

class SeatHeatForm : public QWidget
{
    Q_OBJECT

public:
    explicit SeatHeatForm(QWidget *parent = nullptr);
    ~SeatHeatForm();
   void setHandleHeat();
   void setSeatHeat();
   void setHeatReserve(bool isHeatHandle);
   void setSeatHeatData(ControlNS::ControlHeatSeatPara& heatSeatPara);
   void setHandleHeatData(ControlNS::ControlHeatHandleBarPara& handleBarPara);
   void setHeatReserveData(ControlNS::ControlHeatReservePara& reservePara);
private:
    Ui::SeatHeatForm *ui;
};

#endif // SEATHEATFORM_H

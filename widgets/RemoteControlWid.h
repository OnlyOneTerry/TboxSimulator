#ifndef REMOTECONTROLWID_H
#define REMOTECONTROLWID_H

#include <QWidget>
#include "protoBuf/control.pb.h"

class LocationForm;

namespace Ui {
class RemoteControlWid;
}

class EfenceForm;
class SeatHeatForm;
class RemoteControlWid : public QWidget
{
    Q_OBJECT

public:
    explicit RemoteControlWid(QWidget *parent = nullptr);
    ~RemoteControlWid();
    void initUI();
    void setControl(ControlNS::Control& ctrl);
    void showControlComponent(ControlNS::ControlCommand& ctrlCmd,ControlNS::Parameters& para);
    void setApplyBtnEnable(bool enable);
    void reset();
private slots:
    void on_pushButton_apply_clicked();
signals:
    void responseToControl(QString serialCtrl);
private:
    Ui::RemoteControlWid *ui;
    LocationForm* location_=nullptr;
    EfenceForm* eFence_wid_ = nullptr;
    ControlNS::Control control_;
    SeatHeatForm* seat_heat_ = nullptr;
    QMap<ControlNS::ControlCommand,QWidget*> wid_control_type_map_;
};

#endif // REMOTECONTROLWID_H

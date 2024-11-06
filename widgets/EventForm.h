#ifndef EVENTFORM_H
#define EVENTFORM_H

#include <QWidget>
#include "protoBuf/event.pb.h"
#include "protoBuf/status.pb.h"
#include <QMap>
#include <QGroupBox>

namespace Ui {
class EventForm;
}
class LocationForm;
class EventForm : public QWidget
{
    Q_OBJECT

public:
    explicit EventForm(QWidget *parent = nullptr);
    ~EventForm();
     void initUI();
     void setData(EventNS::EventMsg& eventMsg);
     void getEventEngineOnOff(EventNS::EngineOnOff& eventOnOff);
     void getEventGearPosition(StatusNS::GearPosition& positoin);
     void getBatteryInfo(EventNS::BatteryInfo& batterInfo);
     void getBatteryInfo(EventNS::EventMsg& eventMsg);
     void getSKFaultInfo(EventNS::SKFaultInfo& skFaultInfo);
     void getSideStandInfo(EventNS::SideStandInfo& sideStand);
     void getSeatBucketInfo(EventNS::SeatBucketOpenClose& seatInfo);
     void getLampInfo(EventNS::EventMsg& eventMsg);
     void getGearPosition(EventNS::EventMsg& eventMsg);
     void addBattery(EventNS::BatteryInfo &eventMsg);
     void addLamp(EventNS::LampInfo& lampInfo);
     void showGroupBoxByType(EventNS::EventItem item);
     QString getTaskId();
private slots:
     void on_pushButton_addBattery_clicked();
     void slot_deleteBatteryItem(int index);

     void on_pushButton_addLamp_clicked();

     void slot_deleteLampItem(int index);

     void on_radioButton_open_clicked();

     void on_radioButton_close_clicked();

     void on_radioButton_raise_clicked();

     void on_radioButton_lower_clicked();

     void on_pushButton_taskId_clicked();

private:
    Ui::EventForm *ui;
    LocationForm* locationForm_ = nullptr;
    QMap<EventNS::EventItem,QGroupBox*> win_group_map_;
};

#endif // EVENTFORM_H

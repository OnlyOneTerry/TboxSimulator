#ifndef BATTERYINFOFORM_H
#define BATTERYINFOFORM_H

#include <QWidget>
#include "protoBuf/event.pb.h"

namespace Ui {
class BatteryInfoForm;
}

class BatteryInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit BatteryInfoForm(QWidget *parent = nullptr);
    ~BatteryInfoForm();
    void  getBatteryInfo(EventNS::BatteryInfo& batteryInfo);
    void  setData(EventNS::BatteryInfo& batteryInfo);
signals:
    void deleteSignal(int);
private slots:
    void on_pushButton_del_clicked();

private:
    Ui::BatteryInfoForm *ui;
};

#endif // BATTERYINFOFORM_H

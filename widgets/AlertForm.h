#ifndef ALERTFORM_H
#define ALERTFORM_H

#include <QWidget>
#include "protoBuf/alert.pb.h"

namespace Ui {
class AlertForm;
}

class AlertForm : public QWidget
{
    Q_OBJECT

public:
    explicit AlertForm(QWidget *parent = nullptr);
    ~AlertForm();
    bool getAlertMsg(AlertNS::AlertMsg& alertMsg);
    void setData(AlertNS::AlertMsg& alertMsg);
signals:
     void deleteSignal(int);
private slots:
    void on_btn_del_clicked();

private:
    Ui::AlertForm *ui;

};

#endif // ALERTFORM_H

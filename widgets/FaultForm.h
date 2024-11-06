#ifndef FAULTFORM_H
#define FAULTFORM_H

#include <QWidget>
#include "protoBuf/fault.pb.h"

namespace Ui {
class FaultForm;
}

class FaultForm : public QWidget
{
    Q_OBJECT

public:
    explicit FaultForm(QWidget *parent = nullptr);
    ~FaultForm();
    void setData(FaultNS::FaultMsg& faultMsg);
    bool getFaultMsg(FaultNS::FaultMsg& faultMsg);
private slots:
    void on_btn_del_clicked();
signals:
    void deleteSignal(int);
private:
    Ui::FaultForm *ui;
    FaultNS::FaultMsg fault_msg_;
};

#endif // FAULTFORM_H

#ifndef ECUVERSIONFORM_H
#define ECUVERSIONFORM_H

#include <QWidget>
#include "protoBuf/control.pb.h"

namespace Ui {
class EcuVersionForm;
}

class EcuVersionForm : public QWidget
{
    Q_OBJECT

public:
    explicit EcuVersionForm(QWidget *parent = nullptr);
    ~EcuVersionForm();
    void getEcuVersion(ControlNS::ECUVersion& ecuVersion);
    void setData(ControlNS::ECUVersion& ecuVersion);
signals:
    void deleteSignal(int idex);
private slots:
    void on_pushButton_del_clicked();

private:
    Ui::EcuVersionForm *ui;
};

#endif // ECUVERSIONFORM_H

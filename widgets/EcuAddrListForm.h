#ifndef ECUADDRLISTFORM_H
#define ECUADDRLISTFORM_H

#include <QWidget>
#include "protoBuf/diagnose.pb.h"

namespace Ui {
class EcuAddrListForm;
}

class EcuAddrListForm : public QWidget
{
    Q_OBJECT

public:
    explicit EcuAddrListForm(QWidget *parent = nullptr);
    ~EcuAddrListForm();
    void setDiagEcuAddrData(DiagnoseNS::DiagEcuAddr& diagEcuAddr,bool isResp = false);
private:
    Ui::EcuAddrListForm *ui;
};

#endif // ECUADDRLISTFORM_H

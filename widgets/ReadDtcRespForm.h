#ifndef READDTCRESPFORM_H
#define READDTCRESPFORM_H

#include <QWidget>
#include "protoBuf/diagnose.pb.h"

namespace Ui {
class ReadDtcRespForm;
}

class ReadDtcRespForm : public QWidget
{
    Q_OBJECT

public:
    explicit ReadDtcRespForm(QWidget *parent = nullptr);
    ~ReadDtcRespForm();
    void setEcuDtcData(DiagnoseNS::ReadDTC& readDtc);
private:
    Ui::ReadDtcRespForm *ui;
};

#endif // READDTCRESPFORM_H

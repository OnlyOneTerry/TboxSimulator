#ifndef HMIFORM_H
#define HMIFORM_H
#include <QWidget>
#include "protoBuf/status.pb.h"

namespace Ui {
class HmiForm;
}

class HmiForm : public QWidget
{
    Q_OBJECT

public:
    explicit HmiForm(QWidget *parent = nullptr);
    ~HmiForm();
    bool getHmiInfo(StatusNS::HmiInfo& hmiInfo);
    void initData(StatusNS::HmiInfo& hmiInfo);
private:
    Ui::HmiForm *ui;
    StatusNS::HmiInfo hmiInfo_;
};

#endif // HMIFORM_H

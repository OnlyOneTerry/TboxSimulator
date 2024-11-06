#ifndef EFENCEFORM_H
#define EFENCEFORM_H

#include <QWidget>
#include "protoBuf/control.pb.h"

namespace Ui {
class EfenceForm;
}

class EfenceForm : public QWidget
{
    Q_OBJECT

public:
    explicit EfenceForm(QWidget *parent = nullptr);
    ~EfenceForm();
    void initUI();
    void showCircleFence(bool show);
    void setCircleFenceData(ControlNS::ControlSetRoundFencePara& circlePara);
    void setPolygonFenceData(ControlNS::ControlSetPolygonFencePara& polygonPara);
private:
    Ui::EfenceForm *ui;
};

#endif // EFENCEFORM_H

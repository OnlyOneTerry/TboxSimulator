#ifndef CONTROLCONFIGFORM_H
#define CONTROLCONFIGFORM_H

#include <QWidget>
#include "protoBuf/control.pb.h"

class LocationForm;

namespace Ui {
class ControlConfigForm;
}

class ControlConfigForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlConfigForm(QWidget *parent = nullptr);
    ~ControlConfigForm();
    void initUI();
    void initData();
    void saveAsString(std::string savePath, std::string str);
    void addApnItem(int channel = 0,std::string apnName="test");
    void getEcuVersionParaData(ControlNS::ControlGetECUVersionPara& para);
    void addEcuVersion(ControlNS::ECUVersion& version);
private slots:
    void on_pushButton_addApn_clicked();

    void on_pushButton_apply_clicked();
    void slot_deleteItem(int index);
        void slot_delete_ecu_Item(int index);
    void on_pushButton_addEcu_clicked();

private:
    Ui::ControlConfigForm *ui;
    LocationForm* location_ = nullptr;
};

#endif // CONTROLCONFIGFORM_H

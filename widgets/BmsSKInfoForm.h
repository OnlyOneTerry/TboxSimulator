#ifndef BMSSKINFOFORM_H
#define BMSSKINFOFORM_H

#include <QWidget>
#include "protoBuf/status.pb.h"

namespace Ui {
class BmsSKInfoForm;
}

class BmsSKInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit BmsSKInfoForm(bool delBtnVisible=true,QWidget *parent = nullptr);
    ~BmsSKInfoForm();
     bool getInfo(StatusNS::BmsInfo& bmsInfo);
     bool getInfo(StatusNS::BmsSKInfo& bmsSKInfo);
     bool initData(StatusNS::BmsInfo& bmsInfo);
     bool initData(StatusNS::BmsSKInfo&  bmsSkInfo);
signals:
    void deleteSignal(int);
private slots:
    void on_pushButton_del_clicked();

private:
    Ui::BmsSKInfoForm *ui;
    StatusNS::BmsInfo bmsInfo_;
};

#endif // BMSSKINFOFORM_H

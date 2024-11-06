#ifndef STATUSREPORTWIDGET_H
#define STATUSREPORTWIDGET_H

#include <QWidget>
#include "ReportParent.h"
#include "protoBuf/status.pb.h"
namespace Ui {
class StatusReportWidget;
}

class HmiForm;
class TboxSkInfoForm;
class BmsSKInfoForm;
class BmsSKInfoListForm;
class StatusReportWidget :public ReportParent
{
    Q_OBJECT

public:
    explicit StatusReportWidget(QWidget *parent = nullptr);
    ~StatusReportWidget();
    void InitUI();
    void initData();
    bool getStatus(StatusNS::Status& status);
signals:
    void updateStatusSignal();
private slots:
   void on_pushButton_apply_clicked();
   void on_radioButton_1_clicked();

   void on_radioButton_2_clicked();

private:
    Ui::StatusReportWidget *ui;
    HmiForm* hmiInfo_form_=nullptr;
    TboxSkInfoForm* tbSkInfo_form_=nullptr;
    BmsSKInfoForm* bmsInfo_form_ = nullptr;
    StatusNS::Status data_status_;
    BmsSKInfoListForm* bmsSkInfo_list_form_ = nullptr;
};

#endif // STATUSREPORTWIDGET_H

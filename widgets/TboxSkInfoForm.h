#ifndef TBOXSKINFOFORM_H
#define TBOXSKINFOFORM_H

#include <QWidget>
#include "protoBuf/status.pb.h"

namespace Ui {
class TboxSkInfoForm;
}

class TboxSkInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit TboxSkInfoForm(QWidget *parent = nullptr);
    ~TboxSkInfoForm();
    void initData(StatusNS::TboxSKInfo& status);
    void initData(StatusNS::TboxInfo& tbxInfo);
    bool getTboxSkInfo(StatusNS::TboxSKInfo& status);
    bool getTboxInfo(StatusNS::TboxInfo& status);
private slots:
    void on_pushButton_addCanInfo_clicked();
    void slot_deleteItem(int index);
private:
    Ui::TboxSkInfoForm *ui;

    StatusNS::TboxSKInfo tbxSkInfo_;
};

#endif // TBOXSKINFOFORM_H

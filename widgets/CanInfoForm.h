#ifndef CANINFOFORM_H
#define CANINFOFORM_H

#include <QWidget>
#include "protoBuf/status.pb.h"

namespace Ui {
class CanInfoForm;
}

class CanInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit CanInfoForm(QWidget *parent = nullptr);
    ~CanInfoForm();
    bool getCanInfo(StatusNS::CanInfo& canInfo);
    void initData(StatusNS::CanInfo& canInfo);
signals:
    void deleteSignal(int index);
private slots:
    void on_btn_del_clicked();

private:
    Ui::CanInfoForm *ui;
    StatusNS::CanInfo canInfo_;
};

#endif // CANINFOFORM_H

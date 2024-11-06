#ifndef ECUDTCITEM_H
#define ECUDTCITEM_H

#include <QWidget>
#include "protoBuf/diagnose.pb.h"
namespace Ui {
class EcuDtcItem;
}

class EcuDtcItem : public QWidget
{
    Q_OBJECT

public:
    explicit EcuDtcItem(QWidget *parent = nullptr);
    ~EcuDtcItem();
    void addEcuDtc();
    void setEcuType(DiagnoseNS::Ecus& ecu);
private slots:
    void slot_deleteItem(int index);
    void on_btn_add_clicked();

private:
    Ui::EcuDtcItem *ui;
};

#endif // ECUDTCITEM_H

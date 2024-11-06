#ifndef DIAGDIDITEM_H
#define DIAGDIDITEM_H

#include <QWidget>
#include "protoBuf/diagnose.pb.h"

namespace Ui {
class DiagDiDItem;
}

class DiagDiDItem : public QWidget
{
    Q_OBJECT

public:
    explicit DiagDiDItem(QWidget *parent = nullptr);
    ~DiagDiDItem();
    void setDidAndDidValue(DiagnoseNS::DiagDID& diagDid);
private:
    Ui::DiagDiDItem *ui;
};

#endif // DIAGDIDITEM_H

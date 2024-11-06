#ifndef ECULISTITEM_H
#define ECULISTITEM_H

#include <QWidget>
#include "protoBuf/diagnose.pb.h"

namespace Ui {
class EcuListItem;
}

class EcuListItem : public QWidget
{
    Q_OBJECT

public:
    explicit EcuListItem(QWidget *parent = nullptr);
    ~EcuListItem();
   void setCurrentType(DiagnoseNS::Ecus& ecuType);
private:
    Ui::EcuListItem *ui;
};

#endif // ECULISTITEM_H

#ifndef ECUADDRITEM_H
#define ECUADDRITEM_H

#include <QWidget>

namespace Ui {
class EcuAddrItem;
}

class EcuAddrItem : public QWidget
{
    Q_OBJECT

public:
    explicit EcuAddrItem(QWidget *parent = nullptr);
    ~EcuAddrItem();
   void setEcuAddrData(int ecuAddtx,int ecuAddrRx);
private:
    Ui::EcuAddrItem *ui;
};

#endif // ECUADDRITEM_H

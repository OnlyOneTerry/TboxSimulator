#ifndef ECULIST_H
#define ECULIST_H

#include <QWidget>
#include "protoBuf/diagnose.pb.h"

namespace Ui {
class EcuList;
}

class EcuList : public QWidget
{
    Q_OBJECT

public:
    explicit EcuList(QWidget *parent = nullptr);
    ~EcuList();
    void addEcus(DiagnoseNS::Ecus ecu);
private:
    Ui::EcuList *ui;
};

#endif // ECULIST_H

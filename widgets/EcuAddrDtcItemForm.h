#ifndef ECUADDRDTCITEMFORM_H
#define ECUADDRDTCITEMFORM_H

#include <QWidget>

class EcuAddrItem;
namespace Ui {
class EcuAddrDtcItemForm;
}

class EcuAddrDtcItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit EcuAddrDtcItemForm(QWidget *parent = nullptr);
    ~EcuAddrDtcItemForm();
   void initUI();
   void setEcuAddrData(int ecuAddtx, int ecuAddrRx);
private slots:
   void on_pushButton_addDiagnoseCode_clicked();
   void slot_deleteItem(int index);
private:
    Ui::EcuAddrDtcItemForm *ui;
    EcuAddrItem* ecutAddrItem_ = nullptr;
};

#endif // ECUADDRDTCITEMFORM_H

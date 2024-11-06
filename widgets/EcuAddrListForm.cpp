#include "EcuAddrListForm.h"
#include "ui_EcuAddrListForm.h"
#include "EcuAddrItem.h"
#include <QListWidgetItem>
#include "EcuAddrDtcItemForm.h"
EcuAddrListForm::EcuAddrListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EcuAddrListForm)
{
    ui->setupUi(this);

    QPalette palette = ui->listWidget->palette();
    palette.setColor(QPalette::Highlight,QColor::fromRgb(188,188,188));
    ui->listWidget->setPalette(palette);
}

EcuAddrListForm::~EcuAddrListForm()
{
    delete ui;
}

void EcuAddrListForm::setDiagEcuAddrData(DiagnoseNS::DiagEcuAddr &diagEcuAddr, bool isResp)
{
    int size = diagEcuAddr.ecuaddr_size();

    if(isResp)
    {
        for(int i = 0;i<size;i++)
        {
            EcuAddrDtcItemForm* addrItem = new  EcuAddrDtcItemForm;
            addrItem->setEcuAddrData(diagEcuAddr.ecuaddr(i).ecuaddrtx(),diagEcuAddr.ecuaddr(i).ecuaddrrx());
            QListWidgetItem* item = new QListWidgetItem;
            item->setSizeHint(QSize(100,200));
            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item,addrItem);
        }
    }
    else
    {
        for(int i = 0;i<size;i++)
        {
            EcuAddrItem* addrItem = new  EcuAddrItem;
            addrItem->setEcuAddrData(diagEcuAddr.ecuaddr(i).ecuaddrtx(),diagEcuAddr.ecuaddr(i).ecuaddrrx());
            QListWidgetItem* item = new QListWidgetItem;
            item->setSizeHint(QSize(100,36));
            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item,addrItem);
        }
    }


}

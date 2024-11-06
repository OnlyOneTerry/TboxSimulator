#include "EcuAddrDtcItemForm.h"
#include "ui_EcuAddrDtcItemForm.h"
#include "EcuAddrItem.h"
#include "DiagnoseCodeItemForm.h"

EcuAddrDtcItemForm::EcuAddrDtcItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EcuAddrDtcItemForm)
{
    ui->setupUi(this);
    initUI();
}

EcuAddrDtcItemForm::~EcuAddrDtcItemForm()
{
    delete ui;
}

void EcuAddrDtcItemForm::initUI()
{
    ecutAddrItem_ = new EcuAddrItem;
    ui->verticalLayout->addWidget(ecutAddrItem_);
}

void EcuAddrDtcItemForm::on_pushButton_addDiagnoseCode_clicked()
{
    static int  index = 0;
    DiagnoseCodeItemForm * codeItem = new DiagnoseCodeItemForm;
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(240,35));
    ui->listWidget_diagnoseCode->addItem(item);
    ui->listWidget_diagnoseCode->setItemWidget(item,codeItem);
    codeItem->setProperty("index",index);
    connect(codeItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
    index++;
}

void EcuAddrDtcItemForm::slot_deleteItem(int index)
{
    for(int i = 0;i<ui->listWidget_diagnoseCode->count();i++)
    {
        QListWidgetItem* item = ui->listWidget_diagnoseCode->item(i);
        DiagnoseCodeItemForm* wid = dynamic_cast<DiagnoseCodeItemForm*>(ui->listWidget_diagnoseCode->itemWidget(item));

        if(wid->property("index").toUInt()== index)
        {
            ui->listWidget_diagnoseCode->removeItemWidget(item);
            delete  wid;
            delete  item;
            break;
        }
    }
}

void EcuAddrDtcItemForm::setEcuAddrData(int ecuAddtx, int ecuAddrRx)
{
    ecutAddrItem_->setEcuAddrData(ecuAddtx,ecuAddrRx);
}

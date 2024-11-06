#include "EcuDtcItem.h"
#include "ui_EcuDtcItem.h"
#include <QLineEdit>
#include "DiagnoseCodeItemForm.h"

EcuDtcItem::EcuDtcItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EcuDtcItem)
{
    ui->setupUi(this);
}

EcuDtcItem::~EcuDtcItem()
{
    delete ui;
}

void EcuDtcItem::addEcuDtc()
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

void EcuDtcItem::setEcuType(DiagnoseNS::Ecus &ecu)
{
    ui->comboBox_ecu->setCurrentIndex(ecu);
}


void EcuDtcItem::slot_deleteItem(int index)
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

void EcuDtcItem::on_btn_add_clicked()
{
    addEcuDtc();
}


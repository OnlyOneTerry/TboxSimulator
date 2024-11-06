#include "BmsSKInfoListForm.h"
#include "ui_BmsSKInfoListForm.h"
#include "BmsSKInfoForm.h"

BmsSKInfoListForm::BmsSKInfoListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BmsSKInfoListForm)
{
    ui->setupUi(this);

    QPalette palette = ui->listWidget->palette();
    palette.setColor(QPalette::Highlight,QColor::fromRgb(188,188,188));
    ui->listWidget->setPalette(palette);
}

BmsSKInfoListForm::~BmsSKInfoListForm()
{
    delete ui;
}

void BmsSKInfoListForm::initData(StatusNS::Status &status)
{
    int size = status.bmsskinfo_size();
    for(int i = 0;i<size;i++)
    {
        StatusNS::BmsSKInfo bmsSkInfo = status.bmsskinfo(i);
        int  index = ui->listWidget->count();
        BmsSKInfoForm * statusItem = new BmsSKInfoForm;
        statusItem->initData(bmsSkInfo);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(240,58));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,statusItem);
        statusItem->setProperty("index",index);
        connect(statusItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
        index++;
    }
}

void BmsSKInfoListForm::getInfo(StatusNS::Status &status)
{
      for(int i  = 0;i<ui->listWidget->count();i++)
      {
          StatusNS::BmsSKInfo* bmsSkInfo = status.add_bmsskinfo();

          QListWidgetItem* item = ui->listWidget->item(i);
          BmsSKInfoForm* skwid = dynamic_cast<BmsSKInfoForm*>(ui->listWidget->itemWidget(item));
          skwid->getInfo(*bmsSkInfo);
      }
}

void BmsSKInfoListForm::on_pushButton_add_clicked()
{
    static int  index = ui->listWidget->count();
    BmsSKInfoForm * statusItem = new BmsSKInfoForm;
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(240,58));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,statusItem);
    statusItem->setProperty("index",index);
    connect(statusItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
    index++;
}

void BmsSKInfoListForm::slot_deleteItem(int index)
{
    for(int i = 0;i<ui->listWidget->count();i++)
        {
            QListWidgetItem* item = ui->listWidget->item(i);
            BmsSKInfoForm* wid = dynamic_cast<BmsSKInfoForm*>(ui->listWidget->itemWidget(item));

            if(wid->property("index").toUInt()== index)
            {
                ui->listWidget->removeItemWidget(item);
                delete  wid;
                delete  item;
                break;
            }
        }
}


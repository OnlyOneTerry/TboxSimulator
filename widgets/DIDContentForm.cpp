#include "DIDContentForm.h"
#include "ui_DIDContentForm.h"
#include "DiagDiDItem.h"
DIDContentForm::DIDContentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DIDContentForm)
{
    ui->setupUi(this);
}

DIDContentForm::~DIDContentForm()
{
    delete ui;
}

void DIDContentForm::setDidcontentData(DiagnoseNS::DIDContent &didContent)
{
    int size = didContent.diagdid_size();
    static int index = 0;
    for(int i = 0;i<size;i++)
    {
        DiagnoseNS::DiagDID diagDid = didContent.diagdid(i);
        DiagDiDItem * didItem = new DiagDiDItem;
        didItem->setDidAndDidValue(diagDid);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(200,36));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,didItem);
        didItem->setProperty("index",index);
        connect(didItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
    }
    index++;
    ui->comboBox_ecu->setCurrentIndex(didContent.ecu());
}

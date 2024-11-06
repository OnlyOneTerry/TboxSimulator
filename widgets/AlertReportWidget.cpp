#include "AlertReportWidget.h"
#include "ui_AlertReportWidget.h"
#include "AlertForm.h"
#include "LocationForm.h"

AlertReportWidget::AlertReportWidget(QWidget *parent) :
    ReportParent(TBOX::REPORT_WIDGET::REPORT_ALERT,parent),
    ui(new Ui::AlertReportWidget)
{
    ui->setupUi(this);
    initUI();
    initData();
}

AlertReportWidget::~AlertReportWidget()
{
    delete ui;
}

void AlertReportWidget::initUI()
{
  location_ = new LocationForm;
  ui->verticalLayout_location->addWidget(location_);
  QPalette palette = ui->listWidget->palette();
  palette.setColor(QPalette::Highlight,QColor::fromRgb(188,188,188));
  ui->listWidget->setPalette(palette);
}

void AlertReportWidget::initData()
{
   std::string alertStr = readString("./configure/alert.pb");
   AlertNS::Alert alert ;
   alert.ParseFromString(alertStr);
   std::string  location = alert.location();
   location_->setData(location);

   int size = alert.alertmsg_size();
   for(int i = 0;i<size;i++)
   {
       AlertNS::AlertMsg alertMsg = alert.alertmsg(i);
       static int  index = ui->listWidget->count();
       AlertForm * alert = new AlertForm;
       alert->setData(alertMsg);
       QListWidgetItem* item = new QListWidgetItem;
       item->setSizeHint(QSize(this->width()-20,45));
       ui->listWidget->addItem(item);
       ui->listWidget->setItemWidget(item,alert);
       alert->setProperty("index",index);
       connect(alert,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
       index++;

   }

}

void AlertReportWidget::getAlert(AlertNS::Alert &alert)
{
   for(int i = 0;i<ui->listWidget->count();i++)
   {
       QListWidgetItem* item = ui->listWidget->item(i);

       AlertForm* form = dynamic_cast<AlertForm*>(ui->listWidget->itemWidget(item));

       AlertNS::AlertMsg* alertMsg = alert.add_alertmsg();
       form->getAlertMsg(*alertMsg);
   }

   std::string *loc = alert.mutable_location();
   LocationNS::Location location ;
   location_->getLocation(location);
   *loc = location.SerializeAsString();
}

void AlertReportWidget::on_btn_addAlert_clicked()
{
    static int  index = ui->listWidget->count();
    AlertForm * alert = new AlertForm;
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(this->width()-20,45));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,alert);
    alert->setProperty("index",index);
    connect(alert,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
    index++;
}

void AlertReportWidget::slot_deleteItem(int index)
{
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        AlertForm* wid = dynamic_cast<AlertForm*>(ui->listWidget->itemWidget(item));

        if(wid->property("index").toUInt()== index)
        {
            ui->listWidget->removeItemWidget(item);
            delete  wid;
            delete  item;
            break;
        }
    }
}


void AlertReportWidget::on_btn_apply_clicked()
{

    AlertNS::Alert alert;
    getAlert(alert);
    std::string alertStr = alert.SerializeAsString();
    saveAsString("./configure/alert.pb",alertStr);
     emit updateAlertSignal();
}


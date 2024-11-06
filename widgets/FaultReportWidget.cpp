#include "FaultReportWidget.h"
#include "ui_FaultReportWidget.h"
#include "LocationForm.h"
#include "FaultForm.h"
#include "protoBuf/location.pb.h"

FaultReportWidget::FaultReportWidget(QWidget *parent) :
    ReportParent(TBOX::REPORT_WIDGET::REPORT_FAULT,parent),
    ui(new Ui::FaultReportWidget)
{
    ui->setupUi(this);
    initUI();
    initData();
}

FaultReportWidget::~FaultReportWidget()
{
    delete ui;
}

void FaultReportWidget::initUI()
{
    location_ = new LocationForm;

    ui->verticalLayout_location->addWidget(location_);

    QPalette palette = ui->listWidget->palette();
    palette.setColor(QPalette::Highlight,QColor::fromRgb(188,188,188));
    ui->listWidget->setPalette(palette);
}

void FaultReportWidget::initData()
{
    std::string faultStr = readString("./configure/fault.pb");

    FaultNS::Fault fault;
    fault.ParseFromString(faultStr);
    std::string location = fault.location();
    location_->setData(location);

    int size = fault.faultmsg_size();

    for(int i = 0; i<size; i++)
    {
        FaultNS::FaultMsg faultMsg = fault.faultmsg(i);
        static int  index = ui->listWidget->count();
        FaultForm * fault = new FaultForm;
        fault->setData(faultMsg);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(this->width()-20,45));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,fault);
        fault->setProperty("index",index);
        connect(fault,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
        index++;
    }
}

bool FaultReportWidget::getFault(FaultNS::Fault &fault)
{
   for(int i = 0;i<ui->listWidget->count();i++)
   {
       QListWidgetItem* item = ui->listWidget->item(i);
       FaultForm* form = dynamic_cast<FaultForm*>(ui->listWidget->itemWidget(item));
       FaultNS::FaultMsg* faultMsg = fault.add_faultmsg();
       form->getFaultMsg(*faultMsg);
   }

   std::string* loc = fault.mutable_location();
   LocationNS::Location location ;
   location_->getLocation(location);
   *loc = location.SerializeAsString();
   return true;

//   int size = fault.faultmsg_size();
//   for(int i = 0;i<size;i++)
//   {
//       FaultNS::FaultMsg fault_msg = fault.faultmsg(i);
//       FaultNS::FaultItem fault_item = fault_msg.faultitem();
//       std::cout<<"fault_msg span"<<fault_item.spn() <<"\n";
//       std::cout<<"fault_msg fmi"<<fault_item.fmi() <<"\n";
//       std::cout<<"fault_msg model"<<fault_item.model()<<"\n";
//       std::cout<<"fault_msg counter"<<fault_item.counter()<<"\n";
//   }

//   {
//       std::string loc = fault.location();
//       LocationNS::Location location ;
//       location.ParseFromString(loc);

//       std::cout<<"fault location is "<<"\n";
//       std::cout<<"valid :"<<location.valid()<<"\n";
//       std::cout<<"latitude :"<<location.altitude()<<"\n";
//       std::cout<<"longitude :"<<location.longitude()<<"\n";
//       std::cout<<"angle :"<<location.angle()<<"\n";
//       std::cout<<"spped :"<<location.speed()<<"\n";
//       std::cout<<"satNumber :"<<location.satnumber()<<"\n";
//       std::cout<<"hemisphere:"<<location.hemisphere()<<"\n";
//       std::cout<<"timestamp:"<<location.timestamp()<<"\n";
//   }
}

void FaultReportWidget::on_btn_addError_clicked()
{
    static int  index = ui->listWidget->count();
    FaultForm * fault = new FaultForm;
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(this->width()-20,45));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,fault);
    fault->setProperty("index",index);
    connect(fault,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
    index++;
}

void FaultReportWidget::slot_deleteItem(int index)
{
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        FaultForm* wid = dynamic_cast<FaultForm*>(ui->listWidget->itemWidget(item));

        if(wid->property("index").toUInt()== index)
        {
            ui->listWidget->removeItemWidget(item);
            delete  wid;
            delete  item;
            break;
        }
    }
}

void FaultReportWidget::on_btn_apply_clicked()
{

    FaultNS::Fault fault;
    getFault(fault);
    std::string faultStr= fault.SerializeAsString();
    saveAsString("./configure/fault.pb",faultStr);
    emit updateFaultSignal();
}


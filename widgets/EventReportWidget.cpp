#include "EventReportWidget.h"
#include "ui_EventReportWidget.h"
#include <QListWidget>
#include <EventListItemForm.h>
#include <EventForm.h>
#include <fstream>

EventReportWidget::EventReportWidget(QWidget *parent) :
    ReportParent(TBOX::REPORT_WIDGET::REPORT_EVENT,parent),
    ui(new Ui::EventReportWidget)
{
    ui->setupUi(this);
    initUI();
    initData();
}

EventReportWidget::~EventReportWidget()
{
    delete ui;
}

void EventReportWidget::initUI()
{
    //updateApplyBtnEnableStatus();
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(slotShowCurrentContent(int)));
    QPalette palette = ui->listWidget->palette();
    palette.setColor(QPalette::Highlight,QColor::fromRgb(188,188,188));
    ui->listWidget->setPalette(palette);
}

void EventReportWidget::initData()
{
    std::ifstream readFile("./configure/event.pb",std::ios::in|std::ios::binary);
    if(!readFile)
    {
        std::cerr<<"Cannot open file"<<std::endl;
    }
    EventNS::Event event;
    event.ParseFromIstream(&readFile);

    int size = event.eventmsg_size();

    std::cout<<"read event size is :"<<size<<std::endl;
    for(int i = 0;i<size;i++)
    {
        EventNS::EventMsg eventMsg = event.eventmsg(i);
        static int  index = ui->listWidget->count();
        EventListItemForm * eventItem = new EventListItemForm;
        eventItem->setData(eventMsg);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(240,36));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,eventItem);
        eventItem->setProperty("index",index);
        connect(eventItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
        index++;
    }
}

void EventReportWidget::clearContentLayout()
{
    while (ui->verticalLayout_content->count()) {
        QWidget* p = this->ui->verticalLayout_content->itemAt(0)->widget();
        p->setParent(NULL);
        ui->verticalLayout_content->removeWidget(p);
    }
}

void EventReportWidget::getEvent(EventNS::Event &event)
{
    event.CopyFrom(data_event_);

    int size = event.eventmsg_size();
    std::cout<<"event msg size : "<<size<<std::endl;
    QString callback_info ;
    for(int i = 0;i<size;i++)
    {
        EventNS::EventMsg eventMsg = event.eventmsg(i);

        std::cout<<"event item "<<eventMsg.eventitem()<<"\n";

        EventNS::EngineOnOff engineOnOff = eventMsg.engineonoff();
        std::cout<<"event kl15 is : "<<engineOnOff.kl15()<<std::endl;
        std::cout<<"power is : "<<engineOnOff.power()<<std::endl;

        std::string loc = engineOnOff.location();

        LocationNS::Location location ;
        location.ParseFromString(loc);

        std::cout<<"alert location is "<<"\n";
        std::cout<<"valid :"<<location.valid()<<"\n";
        std::cout<<"latitude :"<<location.altitude()<<"\n";

        std::cout<<"longitude :"<<location.longitude()<<"\n";

        std::cout<<"angle :"<<location.angle()<<"\n";

        std::cout<<"spped :"<<location.speed()<<"\n";

        std::cout<<"satNumber :"<<location.satnumber()<<"\n";

        std::cout<<"hemisphere:"<<location.hemisphere()<<"\n";

        std::cout<<"timestamp:"<<location.timestamp()<<"\n";


        StatusNS::HmiInfo hmiInfo = engineOnOff.hmiinfo() ;
        std::cout<<"speed is :"<<hmiInfo.speed()<<"\n";
        std::cout<<"revspeed is :"<<hmiInfo.revspeed()<<"\n ";
        std::cout<<"odometro is :"<<hmiInfo.odometro()<<"\n";
        std::cout<<"gearPositoin is :"<<hmiInfo.gearposition()<<"\n";

        EventNS::BluetoothInfo blueToolThInfo = engineOnOff.bluetoothinfo();

        std::cout<<"blueToothName is :"<<blueToolThInfo.bluetoothname()<<"\n";
        std::cout<<"blueToothPwd is :"<<blueToolThInfo.bluetoothpwd()<<"\n";
        std::cout<<"blueToothSecretkey is :"<<blueToolThInfo.bluetoothsecretkey()<<"\n";
        std::cout<<"blueToothMac is :"<<blueToolThInfo.bluetoothmac()<<"\n";

        int batterySize = eventMsg.batteryinfo_size();
        for(int i = 0;i<batterySize;i++)
        {
            EventNS::BatteryInfo batteryInfo = eventMsg.batteryinfo(i);
            std::cout<<"battery info cycle :"<<batteryInfo.cycle()<<"\n";
            std::cout<<"battery info quantity :"<<batteryInfo.quantity()<<"\n";
            std::cout<<"battery info temp :"<<batteryInfo.temp()<<"\n";
            std::cout<<"battery info charging :"<<batteryInfo.charging()<<"\n";
            std::cout<<"battery info remaining :"<<batteryInfo.remaining()<<"\n";
        }

    }
    return ;
}

void EventReportWidget::updateApplyBtnEnableStatus()
{
    ui->btn_apply->setEnabled(ui->listWidget->count());
    if(ui->listWidget->count())
    {
        ui->btn_apply->setStyleSheet("QPushButton{background-color:green;color:white;}");
    }
    else
    {
        ui->btn_apply->setStyleSheet("QPushButton{background-color:gray;color:white;}");
    }
}

void EventReportWidget::slotShowCurrentContent(int currentIndex)
{
    if(currentIndex<0) return;
    QListWidgetItem* item = ui->listWidget->item(currentIndex);
    EventListItemForm* wid = dynamic_cast<EventListItemForm*>(ui->listWidget->itemWidget(item));
    EventForm* contentWid = wid->getEventForm();
    clearContentLayout();
    ui->verticalLayout_content->addWidget(contentWid);
}

void EventReportWidget::slot_deleteItem(int index)
{
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        EventListItemForm* wid = dynamic_cast<EventListItemForm*>(ui->listWidget->itemWidget(item));

        if(wid->property("index").toUInt()== index)
        {
            ui->listWidget->removeItemWidget(item);
            delete  wid;
            delete  item;
            break;
        }
    }
    //updateApplyBtnEnableStatus();
}

void EventReportWidget::on_btn_addEvent_clicked()
{
    static int  index = ui->listWidget->count();
    EventListItemForm * eventItem = new EventListItemForm;
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(240,36));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,eventItem);
    eventItem->setProperty("index",index);
    connect(eventItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
    index++;
    //updateApplyBtnEnableStatus();
}


void EventReportWidget::on_btn_apply_clicked()
{
    std::cout<<"listwidget size is :"<<ui->listWidget->count()<<std::endl;
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        EventListItemForm* itemForm = dynamic_cast<EventListItemForm*>(ui->listWidget->itemWidget(item));
        std::string taskID = itemForm->getTaskId().toStdString();
        EventNS::EventMsg* eventMsg = data_event_.add_eventmsg();
        itemForm->getEventMsg(*eventMsg,taskID);
    }

    EventNS::Event event;
    getEvent(event);
    std::string eventStr = data_event_.SerializeAsString();
    saveAsString("./configure/event.pb",eventStr);

     emit updateEventSignal();
}



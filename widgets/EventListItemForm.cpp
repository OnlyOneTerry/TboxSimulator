#include "EventListItemForm.h"
#include "ui_EventListItemForm.h"
#include "EventForm.h"

EventListItemForm::EventListItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventListItemForm)
{
    ui->setupUi(this);
    initUI();
}

EventListItemForm::~EventListItemForm()
{
    delete ui;
    if(eventForm_){
        delete  eventForm_;
    }
}

void EventListItemForm::initUI()
{
    eventForm_ = new  EventForm;
}

void EventListItemForm::setData(EventNS::EventMsg &eventMsg)
{
    ui->comboBox_event_type->setCurrentIndex(eventMsg.eventitem());
    eventForm_->setData(eventMsg);
    eventForm_->showGroupBoxByType(eventMsg.eventitem());
}

EventForm *EventListItemForm::getEventForm()
{
    return eventForm_;
}

QString EventListItemForm::getTaskId()
{
    return eventForm_->getTaskId();
}

bool EventListItemForm::getEventMsg(EventNS::EventMsg &eventMsg,std::string taskId)
{
    EventNS::EventItem item ;
    switch (ui->comboBox_event_type->currentIndex()) {
       case 0:
        item = EventNS::EventItem::INVALID;
        break;
    case 1:
        item = EventNS::EventItem::ENGINE_ON_OFF;
        break;
    case 2:
        item  = EventNS::EventItem::GEAR_POSITION;
        break;
    case 3:
        item = EventNS::EventItem::BATTERY_QTY;
        break;
       case 4:
        item = EventNS::SK_FAULT;
        break;
    default:
        break;
    }

    eventMsg.set_eventitem(item);

    std::cout<<"get event msg ------------"<<std::endl;

    EventNS::EngineOnOff* engineOnOff = eventMsg.mutable_engineonoff();
    eventForm_->getEventEngineOnOff(*engineOnOff);
    engineOnOff->set_taskid(taskId);
    //TOTO
    eventForm_->getBatteryInfo(eventMsg);

    EventNS::SKFaultInfo* skFaultInfo = eventMsg.mutable_skfaultinfo();
    eventForm_->getSKFaultInfo(*skFaultInfo);

    eventForm_->getLampInfo(eventMsg);

    eventForm_->getSideStandInfo(*eventMsg.mutable_sidestandinfo());
    eventForm_->getSeatBucketInfo(*eventMsg.mutable_seatbucketopenclose());
    return true;
}

void EventListItemForm::on_btn_del_clicked()
{
    int idex = this->property("index").toUInt();
    emit deleteSignal(idex);
}


void EventListItemForm::on_comboBox_event_type_currentIndexChanged(int index)
{
    EventNS::EventItem eventType = (EventNS::EventItem)index;
    eventForm_->showGroupBoxByType(eventType);
}


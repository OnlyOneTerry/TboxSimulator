#ifndef EVENTLISTITEMFORM_H
#define EVENTLISTITEMFORM_H

#include <QWidget>
#include "protoBuf/event.pb.h"

namespace Ui {
class EventListItemForm;
}
class EventForm;
class EventListItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit EventListItemForm(QWidget *parent = nullptr);
    ~EventListItemForm();
    void initUI();
    void setData(EventNS::EventMsg& eventMsg);
    EventForm* getEventForm();
    QString getTaskId();
    bool getEventMsg(EventNS::EventMsg & eventMsg,std::string taskId);
signals:
    void deleteSignal(int);
private slots:
    void on_btn_del_clicked();

    void on_comboBox_event_type_currentIndexChanged(int index);

private:
    Ui::EventListItemForm *ui;
    EventForm* eventForm_=nullptr;

};

#endif // EVENTLISTITEMFORM_H

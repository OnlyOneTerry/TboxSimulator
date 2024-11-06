#ifndef LAMPFORM_H
#define LAMPFORM_H

#include <QWidget>
#include "protoBuf/event.pb.h"

namespace Ui {
class LampForm;
}

class LampForm : public QWidget
{
    Q_OBJECT

public:
    explicit LampForm(QWidget *parent = nullptr);
    ~LampForm();
    void initUI();
    void getLampInfo(EventNS::LampInfo& lampInfo);
    void setData(EventNS::LampInfo& lampInfo);
signals:
   void deleteSignal(int);
private slots:
   void on_pushButton_del_clicked();

private:
    Ui::LampForm *ui;
};

#endif // LAMPFORM_H

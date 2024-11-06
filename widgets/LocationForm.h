#ifndef LOCATIONFORM_H
#define LOCATIONFORM_H

#include <QWidget>
#include"protoBuf/location.pb.h"

namespace Ui {
class LocationForm;
}

class LocationForm : public QWidget
{
    Q_OBJECT

public:
    explicit LocationForm(QWidget *parent = nullptr);
    ~LocationForm();
    bool getLocation(LocationNS::Location& location);
    void setData(LocationNS::Location& location);
    void setData(std::string& location);
    void showDelBtn(bool visible);
signals:
    void deleteSignal(int);
private slots:
    void on_pushButton_del_clicked();

private:
    Ui::LocationForm *ui;
    LocationNS::Location location_;
};

#endif // LOCATIONFORM_H

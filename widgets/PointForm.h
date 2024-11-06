#ifndef POINTFORM_H
#define POINTFORM_H

#include <QWidget>

namespace Ui {
class PointForm;
}

class PointForm : public QWidget
{
    Q_OBJECT

public:
    explicit PointForm(QWidget *parent = nullptr);
    ~PointForm();
    void setPoint(int latitude,int longitude,int hemisphere);
private:
    Ui::PointForm *ui;
};

#endif // POINTFORM_H

#ifndef APNITEMFORM_H
#define APNITEMFORM_H

#include <QWidget>

namespace Ui {
class ApnItemForm;
}

class ApnItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit ApnItemForm(QWidget *parent = nullptr);
    ~ApnItemForm();
    void getAPn(int& channel,std::string& apn);
    void setApn(int channel,std::string apn);
signals:
    void deleteSignal(int);
private slots:
    void on_btn_del_clicked();

private:
    Ui::ApnItemForm *ui;
};

#endif // APNITEMFORM_H

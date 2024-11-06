#ifndef TPMSINFOFORM_H
#define TPMSINFOFORM_H

#include <QWidget>

namespace Ui {
class TpmsInfoForm;
}

class TpmsInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit TpmsInfoForm(QWidget *parent = nullptr);
    ~TpmsInfoForm();

private:
    Ui::TpmsInfoForm *ui;
};

#endif // TPMSINFOFORM_H

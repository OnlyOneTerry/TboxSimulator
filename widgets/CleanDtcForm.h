#ifndef CLEANDTCFORM_H
#define CLEANDTCFORM_H

#include <QWidget>

namespace Ui {
class CleanDtcForm;
}

class CleanDtcForm : public QWidget
{
    Q_OBJECT

public:
    explicit CleanDtcForm(QWidget *parent = nullptr);
    ~CleanDtcForm();

private:
    Ui::CleanDtcForm *ui;
};

#endif // CLEANDTCFORM_H

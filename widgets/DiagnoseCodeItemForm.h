#ifndef DIAGNOSECODEITEMFORM_H
#define DIAGNOSECODEITEMFORM_H

#include <QWidget>

namespace Ui {
class DiagnoseCodeItemForm;
}

class DiagnoseCodeItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit DiagnoseCodeItemForm(QWidget *parent = nullptr);
    ~DiagnoseCodeItemForm();
signals:
   void deleteSignal(int);
private slots:
   void on_btn_del_clicked();

private:
    Ui::DiagnoseCodeItemForm *ui;
};

#endif // DIAGNOSECODEITEMFORM_H

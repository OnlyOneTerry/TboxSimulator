#ifndef DIAGECUADDRRESPFORM_H
#define DIAGECUADDRRESPFORM_H

#include <QWidget>

namespace Ui {
class DiagEcuAddrRespForm;
}

class DiagEcuAddrRespForm : public QWidget
{
    Q_OBJECT

public:
    explicit DiagEcuAddrRespForm(QWidget *parent = nullptr);
    ~DiagEcuAddrRespForm();

private:
    Ui::DiagEcuAddrRespForm *ui;
};

#endif // DIAGECUADDRRESPFORM_H

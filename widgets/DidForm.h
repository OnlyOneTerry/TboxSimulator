#ifndef DIDFORM_H
#define DIDFORM_H

#include <QWidget>

namespace Ui {
class DidForm;
}

class DidForm : public QWidget
{
    Q_OBJECT

public:
    explicit DidForm(QWidget *parent = nullptr);
    ~DidForm();

private:
    Ui::DidForm *ui;
};

#endif // DIDFORM_H

#ifndef DIDCONTENTFORM_H
#define DIDCONTENTFORM_H

#include <QWidget>
#include "protoBuf/diagnose.pb.h"

namespace Ui {
class DIDContentForm;
}

class DIDContentForm : public QWidget
{
    Q_OBJECT

public:
    explicit DIDContentForm(QWidget *parent = nullptr);
    ~DIDContentForm();
   void setDidcontentData(DiagnoseNS::DIDContent& didContent);
private:
    Ui::DIDContentForm *ui;
};

#endif // DIDCONTENTFORM_H

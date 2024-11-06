#ifndef BMSSKINFOLISTFORM_H
#define BMSSKINFOLISTFORM_H

#include <QWidget>
#include "protoBuf/status.pb.h"

namespace Ui {
class BmsSKInfoListForm;
}

class BmsSKInfoListForm : public QWidget
{
    Q_OBJECT

public:
    explicit BmsSKInfoListForm(QWidget *parent = nullptr);
    ~BmsSKInfoListForm();
    void initData(StatusNS::Status& status);
    void getInfo(StatusNS::Status& status);
private slots:
    void on_pushButton_add_clicked();
    void slot_deleteItem(int index);
private:
    Ui::BmsSKInfoListForm *ui;
};

#endif // BMSSKINFOLISTFORM_H

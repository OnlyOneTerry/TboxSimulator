#ifndef PATHPLANFORM_H
#define PATHPLANFORM_H

#include <QWidget>

namespace Ui {
class PathPlanForm;
}

class PathPlanForm : public QWidget
{
    Q_OBJECT

public:
    explicit PathPlanForm(QWidget *parent = nullptr);
    ~PathPlanForm();
    std::vector<std::string> getMarks();
    void saveAsString(std::string savePath, std::string str);
    void initData();
    void initUI();
    void updatePointNum();
private slots:
    void on_pushButton_mark_clicked();
    void slot_deleteItem(int index);

    void on_pushButton_apply_clicked();

private:
    Ui::PathPlanForm *ui;
};

#endif // PATHPLANFORM_H

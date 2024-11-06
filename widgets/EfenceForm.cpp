#include "EfenceForm.h"
#include "ui_EfenceForm.h"
#include "PointForm.h"

EfenceForm::EfenceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EfenceForm)
{
    ui->setupUi(this);
    initUI();
}

EfenceForm::~EfenceForm()
{
    delete ui;
}

void EfenceForm::initUI()
{

}

void EfenceForm::showCircleFence(bool show)
{
    if(show)
    {
        ui->groupBox_circle->setVisible(true);
        ui->groupBox_polygon->setVisible(false);
    }
    else
    {
        ui->groupBox_circle->setVisible(false);
        ui->groupBox_polygon->setVisible(true);
    }
}

void EfenceForm::setCircleFenceData(ControlNS::ControlSetRoundFencePara &circlePara)
{
    ControlNS::Point point = circlePara.center();
    this->blockSignals(true);
    ui->label_latitude->setText(QString("%1").arg(point.latitude()));
    ui->label_longtitude->setText(QString("%1").arg(point.longitude()));
    ui->label_hemisphere->setText(QString("%1").arg(point.hemisphere()));
    ui->label_start->setText(QString("%1").arg(circlePara.start()));
    ui->label_end->setText(QString("%1").arg(circlePara.end()));
    ui->label_speed->setText(QString("%1").arg(circlePara.speed()));
    ui->label_fenceId->setText(QString::fromStdString(circlePara.fenceid()));
    ui->label_direction->setText(QString("%1").arg(circlePara.direction()));
    ui->label_radius->setText(QString("%1").arg(circlePara.radius()));
    this->blockSignals(false);
}

void EfenceForm::setPolygonFenceData(ControlNS::ControlSetPolygonFencePara &polygonPara)
{

    int pointSize = polygonPara.points_size();
    for(int i = 0;i<pointSize;i++)
    {
        ControlNS::Point point = polygonPara.points(i);

        static int  index = 0;
        PointForm * pointItem = new PointForm;
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(240,36));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,pointItem);
        pointItem->setProperty("index",index);
        pointItem->setPoint(point.latitude(),point.longitude(),point.hemisphere());
        index++;
    }

    ui->label_start->setText(QString("%1").arg(polygonPara.start()));
    ui->label_end->setText(QString("%1").arg(polygonPara.end()));
    ui->label_speed->setText(QString("%1").arg(polygonPara.speed()));
    ui->label_direction->setText(QString("%1").arg(polygonPara.direction()));
    ui->label_fenceId->setText(QString::fromStdString(polygonPara.fenceid()));

}

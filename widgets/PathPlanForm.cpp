#include "PathPlanForm.h"
#include "ui_PathPlanForm.h"
#include "LocationForm.h"
#include "protoBuf/location.pb.h"
#include "protoBuf/marks.pb.h"
#include <iostream>
#include <fstream>
#include <QPalette>

PathPlanForm::PathPlanForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PathPlanForm)
{
    ui->setupUi(this);
    initUI();
    initData();
}

PathPlanForm::~PathPlanForm()
{
    delete ui;
}

std::vector<std::string> PathPlanForm::getMarks()
{
    std::vector<std::string> locList;
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        LocationNS::Location location;
        QListWidgetItem* item = ui->listWidget->item(i);
        LocationForm* wid = dynamic_cast<LocationForm*>(ui->listWidget->itemWidget(item));
        wid->getLocation(location);
        std::string loc = location.SerializeAsString();
        locList.push_back(loc);
    }
    return locList;
}

void PathPlanForm::on_pushButton_mark_clicked()
{
    static int  index = ui->listWidget->count();
    LocationForm* locationItem = new  LocationForm;
    locationItem->showDelBtn(true);
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(QSize(100,100));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,locationItem);
    locationItem->setProperty("index",index);
    connect(locationItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
    index++;
    updatePointNum();
}

void PathPlanForm::slot_deleteItem(int index)
{
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        LocationForm* wid = dynamic_cast<LocationForm*>(ui->listWidget->itemWidget(item));

        if(wid->property("index").toUInt()== index)
        {
            ui->listWidget->removeItemWidget(item);
            delete  wid;
            delete  item;
            break;
        }
    }
    updatePointNum();
}


void PathPlanForm::saveAsString(std::string savePath, std::string str)
{
    //save
    if(!std::remove(savePath.c_str()))
    {
        std::cout<<"failed to delete file"<<std::endl;
    }

    std::ofstream outfile(savePath,std::ios::binary);
    if(!outfile.is_open())
    {
        std::cerr<<"can't open file"<<std::endl;
        return ;
    }

    outfile.write(str.data(),str.size());
    outfile.close();
}

void PathPlanForm::initData()
{
    MarksNS::Marks mark;
    std::ifstream readFileMarks("./configure/marks.pb",std::ios::in|std::ios::binary);
    if(!readFileMarks)
    {
        std::cerr<<"Cannot open file"<<std::endl;
    }
    mark.ParseFromIstream(&readFileMarks);

    int mark_size = mark.loaction_size();
    for(int i = 0;i<mark_size;i++)
    {
        LocationNS::Location location ;
        location.ParseFromString(mark.loaction(i));

        static int  index = ui->listWidget->count();
        LocationForm* locationItem = new  LocationForm;
        locationItem->showDelBtn(true);
        locationItem->setData(location);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(100,100));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,locationItem);
        locationItem->setProperty("index",index);
        connect(locationItem,SIGNAL(deleteSignal(int)),this,SLOT(slot_deleteItem(int)));
        index++;
    }
    updatePointNum();
}

void PathPlanForm::initUI()
{
    QPalette palette = ui->listWidget->palette();
    palette.setColor(QPalette::Highlight,QColor::fromRgb(188,188,188));
    ui->listWidget->setPalette(palette);
}

void PathPlanForm::updatePointNum()
{
    ui->label_num->setText(QString("%1").arg(ui->listWidget->count()));
}

void PathPlanForm::on_pushButton_apply_clicked()
{
    MarksNS::Marks marks;
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        LocationNS::Location location;
        QListWidgetItem* item = ui->listWidget->item(i);
        LocationForm* wid = dynamic_cast<LocationForm*>(ui->listWidget->itemWidget(item));
        wid->getLocation(location);
        std::string loc = location.SerializeAsString();
        std::string* loc1 =  marks.add_loaction();
        *loc1 = loc;
    }
    std::cout<<"list size is :"<<ui->listWidget->count()<<std::endl;

    std::string serializeStr = marks.SerializeAsString();
    saveAsString("./configure/marks.pb",serializeStr);
}


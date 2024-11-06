#ifndef REPORTPARENT_H
#define REPORTPARENT_H

#include<QWidget>
#include "CommonDef.h"

class ReportParent:public QWidget
{
        Q_OBJECT
public:
    explicit ReportParent(TBOX::REPORT_WIDGET type,QWidget *parent = nullptr);
    void setReportType(TBOX::REPORT_WIDGET type);
    TBOX::REPORT_WIDGET getReportType();
    void saveAsString(std::string savePath,std::string str);
    std::string  readString(std::string readPath);
protected:
   TBOX::REPORT_WIDGET report_type_= TBOX::REPORT_WIDGET::INVALID;
};

#endif // REPORTPARENT_H

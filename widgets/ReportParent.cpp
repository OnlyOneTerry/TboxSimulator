#include "ReportParent.h"
#include <iostream>
#include <fstream>

ReportParent::ReportParent(TBOX::REPORT_WIDGET type,QWidget *parent) : report_type_(type)
{

}

void ReportParent::setReportType(TBOX::REPORT_WIDGET type)
{
    report_type_ = type;
}

TBOX::REPORT_WIDGET ReportParent::getReportType()
{
    return report_type_;
}

void ReportParent::saveAsString(std::string savePath, std::string str)
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

std::string ReportParent::readString(std::string readPath)
{
    std::ifstream readFile(readPath,std::ios::in|std::ios::binary);
    if(!readFile)
    {
        std::cerr<<"Cannot open file"<<std::endl;
        return std::string();
    }

    readFile.seekg(0,std::ios::end);
    int fileSize = readFile.tellg();
    std::cout<<"fileSize is :"<<fileSize<<std::endl;

    readFile.seekg(0,std::ios::beg);
    char* buffer = new char[fileSize];
    readFile.read(buffer,sizeof(char)*fileSize);

    std::string pbStr(buffer);
    delete [] buffer;
    return pbStr;
}

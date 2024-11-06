#ifndef DIAGNOSEFORM_H
#define DIAGNOSEFORM_H

#include <QWidget>
#include "protoBuf/diagnose.pb.h"

class DIDContentForm;
class ReadDtcRespForm;
class EcuList;
class EcuAddrListForm;
namespace Ui {
class DiagnoseForm;
}

class DiagnoseForm : public QWidget
{
    Q_OBJECT

public:
    explicit DiagnoseForm(QWidget *parent = nullptr);
    ~DiagnoseForm();
    void initUI();
    void showDiagnoseByType(DiagnoseNS::DiagnoseOpt& diagnoseOpt);
    void setDiagnoseData(DiagnoseNS::Diagnose& diagnose);
    void setReadDidData(DiagnoseNS::ReadDID& readDid);
    void setWriteDidData(DiagnoseNS::WriteDID& writeDid);
    void setReadDtcData(DiagnoseNS::ReadDTC& readDtc);
    void setCleanDtcData(DiagnoseNS::CleanDTC& cleanDtc);

private:
    Ui::DiagnoseForm *ui;
    ReadDtcRespForm* read_dtc_resp_ = nullptr;
    EcuList* read_dtc_component = nullptr;
    EcuList* clean_dtc_component = nullptr;
    EcuAddrListForm* diag_Ecu_Addr_ = nullptr;
     EcuAddrListForm* diag_Ecu_Addr_resp_ = nullptr;
    QMap<QWidget*,DiagnoseNS::DiagnoseOpt> diagnose_wid_opt_map;
};

#endif // DIAGNOSEFORM_H

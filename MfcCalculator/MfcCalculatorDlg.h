#pragma once

#include "framework.h"
#include "../calc.h"
#include <afxdialogex.h>

class CMfcCalculatorDlg : public CDialogEx
{
public:
    CMfcCalculatorDlg() noexcept;

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MFCCALCULATOR_DIALOG };
#endif

protected:
    void DoDataExchange(CDataExchange* pDX) override;
    BOOL OnInitDialog() override;
    afx_msg void OnBnClickedCalculate();
    afx_msg void OnSelChangeOperation();
    DECLARE_MESSAGE_MAP()

private:
    enum OperationIndex
    {
        OpAdd = 0,
        OpSubtract,
        OpMultiply,
        OpDivide,
        OpModulo,
        OpPower,
        OpSquareRoot,
    };

    void UpdateResult(const CString& text);
    void UpdateSecondOperandState();
    double ReadDoubleFromEdit(const CEdit& edit, bool& success) const;
    long long ReadLongLongFromEdit(const CEdit& edit, bool& success) const;

    Calculator m_calculator;
    CEdit m_editFirst;
    CEdit m_editSecond;
    CComboBox m_comboOperation;
    CStatic m_staticResult;
};

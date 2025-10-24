#include "framework.h"
#include "MfcCalculatorDlg.h"
#include "resource.h"

#include <cwchar>
#include <stdexcept>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
    constexpr double kDefaultDisplayPrecision = 10;

    CString FormatDouble(double value)
    {
        CString formatted;
        formatted.Format(L"%.*g", static_cast<int>(kDefaultDisplayPrecision), value);
        return formatted;
    }
}

CMfcCalculatorDlg::CMfcCalculatorDlg() noexcept
    : CDialogEx(IDD_MFCCALCULATOR_DIALOG)
{
}

void CMfcCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_FIRST, m_editFirst);
    DDX_Control(pDX, IDC_EDIT_SECOND, m_editSecond);
    DDX_Control(pDX, IDC_COMBO_OPERATION, m_comboOperation);
    DDX_Control(pDX, IDC_STATIC_RESULT, m_staticResult);
}

BEGIN_MESSAGE_MAP(CMfcCalculatorDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CMfcCalculatorDlg::OnBnClickedCalculate)
    ON_CBN_SELCHANGE(IDC_COMBO_OPERATION, &CMfcCalculatorDlg::OnSelChangeOperation)
END_MESSAGE_MAP()

BOOL CMfcCalculatorDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    const HICON hIcon = ::LoadIconW(nullptr, IDI_APPLICATION);
    SetIcon(hIcon, TRUE);
    SetIcon(hIcon, FALSE);

    m_comboOperation.AddString(L"Add (+)");
    m_comboOperation.AddString(L"Subtract (-)");
    m_comboOperation.AddString(L"Multiply (*)");
    m_comboOperation.AddString(L"Divide (/)");
    m_comboOperation.AddString(L"Modulo (%)");
    m_comboOperation.AddString(L"Power (^)");
    m_comboOperation.AddString(L"Square root (sqrt)");
    m_comboOperation.SetCurSel(OpAdd);

    UpdateSecondOperandState();
    UpdateResult(L"");

    return TRUE;
}

void CMfcCalculatorDlg::OnBnClickedCalculate()
{
    const int selection = m_comboOperation.GetCurSel();
    if (selection == CB_ERR)
    {
        AfxMessageBox(L"Please select an operation.");
        return;
    }

    bool firstValueOk = false;
    const double firstValue = ReadDoubleFromEdit(m_editFirst, firstValueOk);
    if (!firstValueOk)
    {
        AfxMessageBox(L"Please enter a valid first value.");
        return;
    }

    CString resultText;

    try
    {
        switch (selection)
        {
        case OpAdd:
        case OpSubtract:
        case OpMultiply:
        case OpDivide:
        case OpPower:
        {
            bool secondValueOk = false;
            const double secondValue = ReadDoubleFromEdit(m_editSecond, secondValueOk);
            if (!secondValueOk)
            {
                AfxMessageBox(L"Please enter a valid second value.");
                return;
            }

            double result = 0.0;
            if (selection == OpAdd)
            {
                result = m_calculator.add(firstValue, secondValue);
            }
            else if (selection == OpSubtract)
            {
                result = m_calculator.subtract(firstValue, secondValue);
            }
            else if (selection == OpMultiply)
            {
                result = m_calculator.multiply(firstValue, secondValue);
            }
            else if (selection == OpDivide)
            {
                result = m_calculator.divide(firstValue, secondValue);
            }
            else // OpPower
            {
                result = m_calculator.power(firstValue, secondValue);
            }

            resultText = FormatDouble(result);
            break;
        }
        case OpModulo:
        {
            bool firstIntOk = false;
            const long long firstInt = ReadLongLongFromEdit(m_editFirst, firstIntOk);
            if (!firstIntOk)
            {
                AfxMessageBox(L"Please enter an integer first value for modulo.");
                return;
            }

            bool secondIntOk = false;
            const long long secondInt = ReadLongLongFromEdit(m_editSecond, secondIntOk);
            if (!secondIntOk)
            {
                AfxMessageBox(L"Please enter an integer second value for modulo.");
                return;
            }

            const long long result = m_calculator.modulo(firstInt, secondInt);
            resultText.Format(L"%lld", result);
            break;
        }
        case OpSquareRoot:
        {
            const double result = m_calculator.square_root(firstValue);
            resultText = FormatDouble(result);
            break;
        }
        default:
            AfxMessageBox(L"Unsupported operation selected.");
            return;
        }
    }
    catch (const std::exception& ex)
    {
        CString message;
        message.Format(L"Error: %S", ex.what());
        AfxMessageBox(message);
        UpdateResult(L"");
        return;
    }

    UpdateResult(resultText);
}

void CMfcCalculatorDlg::OnSelChangeOperation()
{
    UpdateSecondOperandState();
}

void CMfcCalculatorDlg::UpdateResult(const CString& text)
{
    m_staticResult.SetWindowTextW(text);
}

void CMfcCalculatorDlg::UpdateSecondOperandState()
{
    const int selection = m_comboOperation.GetCurSel();
    const bool requiresSecondValue = (selection != OpSquareRoot);
    m_editSecond.EnableWindow(requiresSecondValue);
    if (!requiresSecondValue)
    {
        m_editSecond.SetWindowTextW(L"");
    }
}

double CMfcCalculatorDlg::ReadDoubleFromEdit(const CEdit& edit, bool& success) const
{
    CString text;
    edit.GetWindowTextW(text);
    text.Trim();
    if (text.IsEmpty())
    {
        success = false;
        return 0.0;
    }

    wchar_t* endPtr = nullptr;
    const double value = std::wcstod(text.GetString(), &endPtr);
    if (endPtr == text.GetString() || *endPtr != L'\0')
    {
        success = false;
        return 0.0;
    }

    success = true;
    return value;
}

long long CMfcCalculatorDlg::ReadLongLongFromEdit(const CEdit& edit, bool& success) const
{
    CString text;
    edit.GetWindowTextW(text);
    text.Trim();
    if (text.IsEmpty())
    {
        success = false;
        return 0;
    }

    wchar_t* endPtr = nullptr;
    const long long value = _wcstoi64(text.GetString(), &endPtr, 10);
    if (endPtr == text.GetString() || *endPtr != L'\0')
    {
        success = false;
        return 0;
    }

    success = true;
    return value;
}

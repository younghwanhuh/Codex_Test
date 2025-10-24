#include "framework.h"
#include "MfcCalculatorApp.h"

#include "MfcCalculatorDlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMfcCalculatorApp theApp;

CMfcCalculatorApp::CMfcCalculatorApp() noexcept
{
    SetAppID(L"MfcCalculator.AppID");
}

BEGIN_MESSAGE_MAP(CMfcCalculatorApp, CWinApp)
END_MESSAGE_MAP()

BOOL CMfcCalculatorApp::InitInstance()
{
    INITCOMMONCONTROLSEX icex = {};
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES;
    ::InitCommonControlsEx(&icex);

    CWinApp::InitInstance();

    CMfcCalculatorDlg dlg;
    m_pMainWnd = &dlg;
    dlg.DoModal();

    return FALSE;
}

#pragma once

#include "framework.h"

class CMfcCalculatorApp : public CWinApp
{
public:
    CMfcCalculatorApp() noexcept;

    BOOL InitInstance() override;

    DECLARE_MESSAGE_MAP()
};

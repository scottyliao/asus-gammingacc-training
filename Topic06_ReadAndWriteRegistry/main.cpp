#include <windows.h>
#include <iostream>

int main()
{
    // Define a version number
    LPCWSTR szVersion = L"v1.0.0";

    // Write the version number to the registry
    LSTATUS lResult = RegSetKeyValue(
        HKEY_CURRENT_USER,
        L"Software\\My Application",
        L"Version",
        REG_SZ,
        szVersion,
        (lstrlenW(szVersion) + 1) * sizeof(wchar_t)
    );

    //if (lResult == ERROR_SUCCESS)
    //    std::cout << "Write Successfully!!!" << std::endl;

    WCHAR szBuffer[256];
    DWORD dwBufferSize = sizeof(szBuffer);

    // Read the version number to the buffer
    lResult = RegGetValue(
        HKEY_CURRENT_USER,
        L"Software\\My Application",
        L"Version",
        RRF_RT_REG_SZ,
        NULL,
        szBuffer,
        &dwBufferSize
    );

    if (lResult == ERROR_SUCCESS)
        std::wcout << szBuffer;
    
    return 0;
}
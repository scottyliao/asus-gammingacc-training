#include <windows.h>
#include <iostream>
#include <dbt.h>
#include <initguid.h>
#include <usbiodef.h>

HDEVNOTIFY hDevNotify = NULL;
HPOWERNOTIFY hPowerNotify = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_POWERBROADCAST:
        if (wParam == PBT_POWERSETTINGCHANGE) {
            POWERBROADCAST_SETTING* pSetting = (POWERBROADCAST_SETTING*)lParam;
            if (pSetting->PowerSetting == GUID_CONSOLE_DISPLAY_STATE) {
                DWORD state = *(DWORD*)(pSetting->Data);
                if (state == 0) {
                    std::cout << "\n【電源事件】偵測到螢幕關閉 / 系統進入現代睡眠 (S0)！" << std::endl;
                }
                else {
                    std::cout << "\n【電源事件】偵測到螢幕開啟 / 系統喚醒！" << std::endl;
                }
            }
        }
        break;

    case WM_DEVICECHANGE:
        if (wParam == DBT_DEVICEARRIVAL) std::cout << "\n【硬體事件】USB 插入！" << std::endl;
        if (wParam == DBT_DEVICEREMOVECOMPLETE) std::cout << "\n【硬體事件】USB 拔除！" << std::endl;
        break;

    case WM_DESTROY:
        if (hDevNotify) UnregisterDeviceNotification(hDevNotify);
        if (hPowerNotify) UnregisterPowerSettingNotification(hPowerNotify);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int main() {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"EventMonitorWindowClass";
    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(0, wc.lpszClassName, L"EventMonitor", 0, 0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);

    DEV_BROADCAST_DEVICEINTERFACE notificationFilter = { 0 };
    notificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    notificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    notificationFilter.dbcc_classguid = GUID_DEVINTERFACE_USB_DEVICE;
    hDevNotify = RegisterDeviceNotification(hWnd, &notificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);

    hPowerNotify = RegisterPowerSettingNotification(hWnd, &GUID_CONSOLE_DISPLAY_STATE, DEVICE_NOTIFY_WINDOW_HANDLE);

    std::cout << "測試【拔插USB】或【按下Power鍵/睡眠】..." << std::endl;

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
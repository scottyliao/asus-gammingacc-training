#include <windows.h>
#include <tchar.h>    // 引入支援 Unicode/ANSI 的文字處理標頭檔（例如 _T 巨集）

// 宣告視窗回呼函式（Window Procedure），負責處理視窗接收到的所有訊息
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// 使用匈牙利命名法定義全域字串
LPCTSTR g_lpszClassName = _T("MyCopyDataClass"); // g_ (全域) lpsz (指向以零結尾字串的長指標)
LPCTSTR g_lpszWindowTitle = _T("CopyData Demo"); // 視窗的標題名稱

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = g_lpszClassName;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    // Register this window to the OS
    RegisterClass(&wc);

    // Create the instance of window
    HWND hwndMain = CreateWindow(
        g_lpszClassName,    // 使用剛剛註冊的類別名稱
        g_lpszWindowTitle,  // 視窗上方標題列顯示的文字
        WS_OVERLAPPEDWINDOW,// 視窗樣式：擁有標題列、系統選單、最大化最小化和邊框的標準視窗
        CW_USEDEFAULT, CW_USEDEFAULT, // 視窗初始的 X, Y 座標（由系統決定）
        400, 300,           // 視窗的寬度與高度（400x300 像素）
        NULL,               // 沒有父視窗
        NULL,               // 沒有功能選單
        hInstance,          // 程式執行實體控制代碼
        NULL                // 額外參數，設為 NULL
    );

    ShowWindow(hwndMain, nCmdShow);

    // 1. 使用 FindWindow 尋找目標視窗
    HWND hwndTarget = FindWindow(g_lpszClassName, g_lpszWindowTitle);

    if (hwndTarget != NULL)
    {
        // 2. 準備要傳送的文字資料
        TCHAR szMessage[] = _T("這是從 SendMessage 傳過來的機密資料！");

        // 3. 設定 Windows 規定的 COPYDATASTRUCT 結構體
        COPYDATASTRUCT cds; // cds: Hungarian notation for CopyData Struct
        cds.dwData = 1234;  // dwData (Double Word): 自定義的識別碼，這裡隨便設個 1234
        cds.cbData = sizeof(szMessage); // cbData (Count of Bytes): 資料的總位元組大小
        cds.lpData = szMessage;         // lpData (Long Pointer): 指向實際資料記憶體位址的指標

        // 4. 發送訊息。引數：(目標視窗, 訊息類型, 發送者視窗, 結構體記憶體指標)
        SendMessage(hwndTarget, WM_COPYDATA, (WPARAM)hwndMain, (LPARAM)&cds);
    }

    // 訊息迴圈：負責監聽並派發系統訊息，維持視窗運作不關閉
    MSG msg; // msg: Message 結構體
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); // 轉譯鍵盤訊息
        DispatchMessage(&msg);  // 將訊息分派給 WndProc 處理
    }

    return (int)msg.wParam; // 程式結束，回傳結束碼
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // 根據傳進來的訊息類型 (uMsg) 進行分支處理
    switch (uMsg)
    {
    case WM_COPYDATA:
    {
        PCOPYDATASTRUCT pCds = (PCOPYDATASTRUCT)lParam;

        // 2. 從結構體中取出文字資料
        //    因為知道傳過來的是 TCHAR 字串，所以轉型成 LPCTSTR
        LPCTSTR lpszReceivedText = (LPCTSTR)pCds->lpData;

        // 3. 額外驗證：順便取出我們自訂的 dwData 密碼
        DWORD dwCustomId = pCds->dwData;

        // 宣告一個緩衝區用來組合等等要顯示的文字
        TCHAR szDisplayBuf[256]; // sz: String Zero-terminated, Buf: Buffer

        // 格式化字串，把收到的資料填入緩衝區中
        _stprintf_s(szDisplayBuf, 256, _T("收到WM_COPYDATA！\n自訂代碼 dwData: %u\n收到內容: %s"), dwCustomId, lpszReceivedText);

        // 跳出對話視窗顯示結果
        MessageBox(hwnd, szDisplayBuf, _T("接收端報告"), MB_OK | MB_ICONINFORMATION);

        return TRUE; // 成功處理 WM_COPYDATA 訊息，依規定回傳 TRUE
    }
    break;

    case WM_DESTROY:
        // 當視窗被關閉時，系統會發送此訊息
        PostQuitMessage(0); // 發送結束通知給訊息迴圈，讓 GetMessage 傳回 0 以終止程式
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
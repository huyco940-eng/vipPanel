#include <windows.h>

// Khai bao ID cho cac nut bam
#define ID_AIMBOT 101
#define ID_AIMLOCK 102
#define ID_AIMDRAG 103
#define ID_NORECOIL 104
#define ID_ESP 105
#define ID_ACTIVATE 106

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowA("static", "--- vipPanel PREMIUM MENU ---", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 260, 20, hWnd, NULL, NULL, NULL);
        CreateWindowA("button", "Kich hoat Aimbot", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 20, 40, 200, 30, hWnd, (HMENU)ID_AIMBOT, NULL, NULL);
        CreateWindowA("button", "Kich hoat AimLock", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 20, 70, 200, 30, hWnd, (HMENU)ID_AIMLOCK, NULL, NULL);
        CreateWindowA("button", "Kich hoat AimDrag", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 20, 100, 200, 30, hWnd, (HMENU)ID_AIMDRAG, NULL, NULL);
        CreateWindowA("button", "Kich hoat NoRecoil", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 20, 130, 200, 30, hWnd, (HMENU)ID_NORECOIL, NULL, NULL);
        CreateWindowA("button", "Kich hoat ESP (X-Ray)", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 20, 160, 200, 30, hWnd, (HMENU)ID_ESP, NULL, NULL);
        CreateWindowA("button", "APPLY SETTINGS", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 210, 240, 40, hWnd, (HMENU)ID_ACTIVATE, NULL, NULL);
        CreateWindowA("static", "Dev: MinhKha | Status: Safe", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 260, 260, 20, hWnd, NULL, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wp) == ID_ACTIVATE) {
            MessageBoxA(hWnd, "vipPanel: Da kich hoat thanh cong!", "Thong bao", MB_OK | MB_ICONINFORMATION);
        }
        if (LOWORD(wp) >= 101 && LOWORD(wp) <= 105) {
            HWND hChk = GetDlgItem(hWnd, LOWORD(wp));
            LRESULT st = SendMessage(hChk, BM_GETCHECK, 0, 0);
            SendMessage(hChk, BM_SETCHECK, !st, 0);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wp, lp);
    }
    return 0;
}

int main() {
    HINSTANCE hInst = GetModuleHandle(NULL);
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"vipPanelClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc)) return -1;
    HWND hWnd = CreateWindowW(L"vipPanelClass", L"vipPanel - DevMinhKha", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 400, 200, 300, 330, NULL, NULL, hInst, NULL);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

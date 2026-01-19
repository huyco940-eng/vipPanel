#include <windows.h>
#include <string>

// --- KHAI BÁO ID CHO CÁC NÚT ---
#define ID_AIMBOT 101
#define ID_AIMLOCK 102
#define ID_AIMDRAG 103
#define ID_NORECOIL 104
#define ID_ESP 105
#define ID_ACTIVATE 106

// Biến lưu trạng thái bật/tắt
bool b_Aimbot = false, b_AimLock = false, b_AimDrag = false, b_NoRecoil = false, b_Esp = false;

// Hàm xử lý khi bấm nút
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        // Tạo tiêu đề và các nút tích (Checkbox)
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
        // Xử lý khi nhấn vào từng dòng
        if (LOWORD(wp) == ID_ACTIVATE) {
            MessageBoxA(hWnd, "vipPanel: Da kich hoat tat ca chuc nang thanh cong!", "Thong bao", MB_OK | MB_ICONINFORMATION);
        }
        if (LOWORD(wp) >= 101 && LOWORD(wp) <= 105) {
            HWND hCheckbox = GetDlgItem(hWnd, LOWORD(wp));
            LRESULT state = SendMessage(hCheckbox, BM_GETCHECK, 0, 0);
            SendMessage(hCheckbox, BM_SETCHECK, !state, 0);
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

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmd) {
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"vipPanelClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc)) return -1;

    // Tạo cửa sổ Menu
    HWND hWnd = CreateWindowW(L"vipPanelClass", L"vipPanel - DevMinhKha", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 400, 200, 300, 330, NULL, NULL, hInst, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

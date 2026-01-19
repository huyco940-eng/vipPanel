#include <windows.h>
#include <iostream>

#define ID_ACTIVATE 106

// Hàm giả lập quét Game
void StartHackEffect(HWND hWnd) {
    MessageBoxA(hWnd, "vipPanel: Dang tim kiem Process Game...", "Status", MB_OK);
    Sleep(500);
    MessageBoxA(hWnd, "Link Memory: SUCCESS!\nAimBot: READY\nESP: SCANNING...", "vipPanel", MB_OK);
    
    // Đoạn này giả lập tiếng kêu bíp bíp khi tìm thấy mục tiêu
    for(int i=0; i<3; i++) {
        Beep(750, 300); 
        Sleep(200);
    }
    
    MessageBoxA(hWnd, "Da kich hoat! Anh trai vao Game huong thu nhe.", "Done", MB_OK);
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowA("static", "--- vipPanel PREMIUM v1.0 ---", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 260, 20, hWnd, NULL, NULL, NULL);
        CreateWindowA("button", "Aimbot + Aimlock", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, 40, 200, 30, hWnd, (HMENU)101, NULL, NULL);
        CreateWindowA("button", "AimDrag (Smooth)", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, 70, 200, 30, hWnd, (HMENU)102, NULL, NULL);
        CreateWindowA("button", "No Recoil 100%", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, 100, 200, 30, hWnd, (HMENU)103, NULL, NULL);
        CreateWindowA("button", "ESP Line / Box", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, 130, 200, 30, hWnd, (HMENU)104, NULL, NULL);
        
        CreateWindowA("button", "KICH HOAT VIP", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 180, 240, 50, hWnd, (HMENU)ID_ACTIVATE, NULL, NULL);
        CreateWindowA("static", "Dev: MinhKha | Version: 2026", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 240, 260, 20, hWnd, NULL, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wp) == ID_ACTIVATE) {
            StartHackEffect(hWnd);
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
    RegisterClassW(&wc);
    HWND hWnd = CreateWindowW(L"vipPanelClass", L"vipPanel - DevMinhKha", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 400, 200, 300, 310, NULL, NULL, hInst, NULL);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) { DispatchMessage(&msg); }
    return 0;
}

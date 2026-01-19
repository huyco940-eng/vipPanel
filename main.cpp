#include <windows.h>

// ID cho các nút
#define ID_AUTO_PULL 101

bool b_AutoPull = false;

// Hàm kéo tâm tự động (Macro)
void DragShoot() {
    if (b_AutoPull && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
        // Tự động nhích chuột lên trên một chút để vào đầu
        mouse_event(MOUSEEVENTF_MOVE, 0, -5, 0, 0); 
        Sleep(20); // Tốc độ kéo
    }
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowA("static", "--- FF vipPanel Macro ---", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 260, 20, hWnd, NULL, NULL, NULL);
        CreateWindowA("button", "BAT KEO TAM (HOLD L-CLICK)", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, 50, 240, 40, hWnd, (HMENU)ID_AUTO_PULL, NULL, NULL);
        CreateWindowA("static", "Trang thai: Dang hoat dong", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 110, 260, 20, hWnd, NULL, NULL, NULL);
        
        // Tạo vòng lặp kiểm tra phím
        SetTimer(hWnd, 1, 10, NULL);
        break;
    case WM_TIMER:
        DragShoot();
        break;
    case WM_COMMAND:
        if (LOWORD(wp) == ID_AUTO_PULL) {
            b_AutoPull = !b_AutoPull;
        }
        break;
    case WM_DESTROY: PostQuitMessage(0); break;
    default: return DefWindowProc(hWnd, msg, wp, lp);
    }
    return 0;
}

int main() {
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"vipPanelMacro";
    wc.lpfnWndProc = WindowProcedure;
    RegisterClassW(&wc);
    HWND hWnd = CreateWindowW(L"vipPanelMacro", L"vipPanel FF - MinhKha", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 400, 200, 300, 180, NULL, NULL, NULL, NULL);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) { DispatchMessage(&msg); }
    return 0;
}

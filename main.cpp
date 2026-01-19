#include <windows.h>
#include <vector>
#include <tlhelp32.h>

// --- KHU VỰC ÉP OFFSET (Ví dụ cho FF) ---
// Lưu ý: Offset thay đổi theo phiên bản, đây là khung sườn để anh tự thay
DWORD offset_Aimbot = 0x1A2B3C; 
DWORD offset_NoRecoil = 0x4D5E6F;

// Hàm tìm tiến trình giả lập (BlueStacks/SmartGaGa)
DWORD GetProcessId(const char* procName) {
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!_stricmp(procEntry.szExeFile, procName)) {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

// Hàm ép dữ liệu vào Game
void WriteToMemory(DWORD address, int value) {
    DWORD pID = GetProcessId("HD-Player.exe"); // BlueStacks
    if (pID == 0) pID = GetProcessId("SmartGaGa.exe");
    
    if (pID != 0) {
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
        if (hProc) {
            WriteProcessMemory(hProc, (LPVOID)address, &value, sizeof(value), NULL);
            CloseHandle(hProc);
        }
    }
}

// --- GIAO DIỆN MENU ---
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowA("static", "--- FF vipPanel PREMIUM ---", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 260, 20, hWnd, NULL, NULL, NULL);
        CreateWindowA("button", "Kich hoat AIMBOT", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 50, 240, 40, hWnd, (HMENU)1, NULL, NULL);
        CreateWindowA("button", "Kich hoat NO RECOIL", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 100, 240, 40, hWnd, (HMENU)2, NULL, NULL);
        CreateWindowA("button", "Kich hoat ANTIBAN", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 150, 240, 40, hWnd, (HMENU)3, NULL, NULL);
        CreateWindowA("static", "Dev: MinhKha | Status: Ready", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 210, 260, 20, hWnd, NULL, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wp) == 1) {
            WriteToMemory(offset_Aimbot, 1);
            MessageBoxA(hWnd, "Da ep Aimbot!", "vipPanel", MB_OK);
        }
        if (LOWORD(wp) == 2) {
            WriteToMemory(offset_NoRecoil, 1);
            MessageBoxA(hWnd, "Da ep NoRecoil!", "vipPanel", MB_OK);
        }
        if (LOWORD(wp) == 3) {
            MessageBoxA(hWnd, "Antiband Protection: ON", "vipPanel", MB_OK);
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
    wc.lpszClassName = L"vipPanelClass";
    wc.lpfnWndProc = WindowProcedure;
    RegisterClassW(&wc);
    HWND hWnd = CreateWindowW(L"vipPanelClass", L"vipPanel Free Fire", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 400, 200, 300, 300, NULL, NULL, NULL, NULL);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) { DispatchMessage(&msg); }
    return 0;
}

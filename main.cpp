#include <windows.h>
#include <vector>

// Hàm ép mã máy (Dành cho pháp sư thực thụ)
void PatchEx(LPVOID address, std::vector<unsigned char> bytes, HANDLE hProcess) {
    DWORD oldProtect;
    // Mở khóa bộ nhớ game để ghi đè
    VirtualProtectEx(hProcess, address, bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
    WriteProcessMemory(hProcess, address, bytes.data(), bytes.size(), NULL);
    // Khóa lại như cũ để tránh bị phát hiện
    VirtualProtectEx(hProcess, address, bytes.size(), oldProtect, &oldProtect);
}

// Khi nhấn nút AIMBOT, anh gọi lệnh này:
// Giả sử mã để ghim tâm là: 0x90, 0x90 (lệnh NOP trong assembly)
void KichHoatAimbot(HANDLE hProc, DWORD offset) {
    std::vector<unsigned char> aimbotCode = { 0x90, 0x90, 0x90 }; 
    PatchEx((LPVOID)offset, aimbotCode, hProc);
}

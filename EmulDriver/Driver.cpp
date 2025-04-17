#include "Driver.h"
#include "CryptoHelper.h"
#include <iostream>
#include <Windows.h>

#define IOCTL_ENCRYPT_FILE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DECRYPT_FILE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define XOR_KEY 0x5A

HANDLE CreateVirtualDevice() {
    std::wcout << L"[INFO] Попытка подключения к виртуальному устройству Driver...\n";

    // Эмуляция успешного подключения к виртуальному устройству
    HANDLE hDevice = reinterpret_cast<HANDLE>(1); // Псевдодескриптор
    if (hDevice == INVALID_HANDLE_VALUE) {
        std::wcerr << L"[ERROR] Не удалось создать виртуальное устройство. Код ошибки: " << GetLastError() << L"\n";
    }
    else {
        std::wcout << L"[INFO] Виртуальное устройство успешно подключено.\n";
    }
    return hDevice;
}


void HandleIoctl(HANDLE hDevice, DWORD ioctlCode, const char* filePath) {
    DWORD bytesReturned;
    BOOL result = DeviceIoControl(
        hDevice,
        ioctlCode,
        (LPVOID)filePath,
        strlen(filePath) + 1,
        NULL,
        0,
        &bytesReturned,
        NULL
    );

    if (result) {
        std::cout << "[INFO] IOCTL command executed successfully.\n";
    }
    else {
        std::cerr << "[ERROR] IOCTL command failed with error code: " << GetLastError() << "\n";
    }
}

void HandleIoctlEmulation(DWORD ioctlCode, const wchar_t* filePath, const wchar_t* outputDir) {
    std::wcout << L"[INFO] Обработка команды IOCTL через виртуальное устройство: " << ioctlCode << L"\n";
    wchar_t outputPath[MAX_PATH];

    if (ioctlCode == IOCTL_ENCRYPT_FILE) {
        swprintf(outputPath, MAX_PATH, L"%s\\encrypted_%s", outputDir, wcsrchr(filePath, L'\\') + 1);
    }
    else if (ioctlCode == IOCTL_DECRYPT_FILE) {
        swprintf(outputPath, MAX_PATH, L"%s\\decrypted_%s", outputDir, wcsrchr(filePath, L'\\') + 1);
    }

    xor_encrypt_decrypt(filePath, outputPath, XOR_KEY);
    std::wcout << L"[INFO] Файл сохранен в: " << outputPath << L"\n";
}

#include "FileManager.h"
#include "CryptoHelper.h"
#include "Driver.h"

#include <iostream>
#include <locale>
#include <Windows.h>

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    wchar_t directoryPath[MAX_PATH] = { 0 };
    wchar_t filePath[MAX_PATH] = { 0 };

    // Создаем виртуальное устройство
    HANDLE hDevice = CreateVirtualDevice();
    if (hDevice == INVALID_HANDLE_VALUE) {
        std::wcerr << L"[ERROR] Не удалось подключиться к виртуальному устройству.\n";
        return 1;
    }

    // Выбор директории
    std::wcout << L"[INFO] Выберите директорию.\n";
    select_directory(directoryPath);
    if (wcslen(directoryPath) == 0) {
        std::wcerr << L"[ERROR] Директория не выбрана. Программа завершена.\n";
        return 1;
    }
    std::wcout << L"[INFO] Выбрана директория: " << directoryPath << L"\n";

    // Выбор файла
    std::wcout << L"[INFO] Выберите файл для шифрования/дешифрования.\n";
    select_file(filePath);
    if (wcslen(filePath) == 0) {
        std::wcerr << L"[ERROR] Файл не выбран. Программа завершена.\n";
        return 1;
    }
    std::wcout << L"[INFO] Выбран файл: " << filePath << L"\n";

    int choice;
    std::wcout << L"1 - Зашифровать файл\n2 - Расшифровать файл\nВаш выбор: ";
    std::wcin >> choice;

    wchar_t outputDir[MAX_PATH];
    swprintf(outputDir, MAX_PATH, L"%s\\ProcessedFiles", directoryPath);
    if (!CreateDirectoryIfNotExist(outputDir)) {
        return 1;
    }

    if (choice == 1) {
        std::wcout << L"[INFO] Начинается процесс шифрования...\n";
    }
    else if (choice == 2) {
        std::wcout << L"[INFO] Начинается процесс дешифрования...\n";
    }
    else {
        std::wcerr << L"[ERROR] Неверный выбор. Программа завершена.\n";
        return 1;
    }

    HandleIoctlEmulation(choice == 1 ? IOCTL_ENCRYPT_FILE : IOCTL_DECRYPT_FILE, filePath, outputDir);

    std::wcout << L"[INFO] Операция завершена. Результат сохранен в: " << outputDir << L"\n";
    CloseHandle(hDevice);
    return 0;
}
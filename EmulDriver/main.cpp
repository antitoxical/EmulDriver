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

    // ������� ����������� ����������
    HANDLE hDevice = CreateVirtualDevice();
    if (hDevice == INVALID_HANDLE_VALUE) {
        std::wcerr << L"[ERROR] �� ������� ������������ � ������������ ����������.\n";
        return 1;
    }

    // ����� ����������
    std::wcout << L"[INFO] �������� ����������.\n";
    select_directory(directoryPath);
    if (wcslen(directoryPath) == 0) {
        std::wcerr << L"[ERROR] ���������� �� �������. ��������� ���������.\n";
        return 1;
    }
    std::wcout << L"[INFO] ������� ����������: " << directoryPath << L"\n";

    // ����� �����
    std::wcout << L"[INFO] �������� ���� ��� ����������/������������.\n";
    select_file(filePath);
    if (wcslen(filePath) == 0) {
        std::wcerr << L"[ERROR] ���� �� ������. ��������� ���������.\n";
        return 1;
    }
    std::wcout << L"[INFO] ������ ����: " << filePath << L"\n";

    int choice;
    std::wcout << L"1 - ����������� ����\n2 - ������������ ����\n��� �����: ";
    std::wcin >> choice;

    wchar_t outputDir[MAX_PATH];
    swprintf(outputDir, MAX_PATH, L"%s\\ProcessedFiles", directoryPath);
    if (!CreateDirectoryIfNotExist(outputDir)) {
        return 1;
    }

    if (choice == 1) {
        std::wcout << L"[INFO] ���������� ������� ����������...\n";
    }
    else if (choice == 2) {
        std::wcout << L"[INFO] ���������� ������� ������������...\n";
    }
    else {
        std::wcerr << L"[ERROR] �������� �����. ��������� ���������.\n";
        return 1;
    }

    HandleIoctlEmulation(choice == 1 ? IOCTL_ENCRYPT_FILE : IOCTL_DECRYPT_FILE, filePath, outputDir);

    std::wcout << L"[INFO] �������� ���������. ��������� �������� �: " << outputDir << L"\n";
    CloseHandle(hDevice);
    return 0;
}
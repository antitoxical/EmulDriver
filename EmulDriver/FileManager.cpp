#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <windows.h>
#include <shlobj.h>
#include <iostream>

// Функция для выбора директории
void select_directory(wchar_t* selectedPath) {
    BROWSEINFOW bi = { 0 };
    bi.lpszTitle = L"Выберите директорию";
    LPITEMIDLIST pidl = SHBrowseForFolderW(&bi);
    if (pidl) {
        SHGetPathFromIDListW(pidl, selectedPath);
    }
    else {
        std::wcerr << L"[ERROR] Директория не выбрана.\n";
    }
}

// Функция для выбора файла
void select_file(wchar_t* selectedPath) {
    OPENFILENAMEW ofn = { 0 };
    wchar_t fileName[MAX_PATH] = L"";

    ofn.lStructSize = sizeof(OPENFILENAMEW);
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"Все файлы\0*.*\0";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameW(&ofn)) {
        wcscpy_s(selectedPath, MAX_PATH, ofn.lpstrFile);
    }
    else {
        std::wcerr << L"[ERROR] Файл не выбран.\n";
    }
}

// Функция для создания директории, если она не существует
bool CreateDirectoryIfNotExist(const wchar_t* dirPath) {
    DWORD dwAttrib = GetFileAttributesW(dirPath);

    if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
        if (CreateDirectoryW(dirPath, NULL)) {
            std::wcout << L"[INFO] Директория успешно создана: " << dirPath << L"\n";
            return true;
        }
        else {
            std::wcerr << L"[ERROR] Не удалось создать директорию: " << dirPath << L"\n";
            return false;
        }
    }
    return true;
}

#endif // FILE_MANAGER_H

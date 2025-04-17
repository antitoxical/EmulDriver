#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <windows.h>
#include <shlobj.h>
#include <iostream>

// ������� ��� ������ ����������
void select_directory(wchar_t* selectedPath) {
    BROWSEINFOW bi = { 0 };
    bi.lpszTitle = L"�������� ����������";
    LPITEMIDLIST pidl = SHBrowseForFolderW(&bi);
    if (pidl) {
        SHGetPathFromIDListW(pidl, selectedPath);
    }
    else {
        std::wcerr << L"[ERROR] ���������� �� �������.\n";
    }
}

// ������� ��� ������ �����
void select_file(wchar_t* selectedPath) {
    OPENFILENAMEW ofn = { 0 };
    wchar_t fileName[MAX_PATH] = L"";

    ofn.lStructSize = sizeof(OPENFILENAMEW);
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"��� �����\0*.*\0";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameW(&ofn)) {
        wcscpy_s(selectedPath, MAX_PATH, ofn.lpstrFile);
    }
    else {
        std::wcerr << L"[ERROR] ���� �� ������.\n";
    }
}

// ������� ��� �������� ����������, ���� ��� �� ����������
bool CreateDirectoryIfNotExist(const wchar_t* dirPath) {
    DWORD dwAttrib = GetFileAttributesW(dirPath);

    if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
        if (CreateDirectoryW(dirPath, NULL)) {
            std::wcout << L"[INFO] ���������� ������� �������: " << dirPath << L"\n";
            return true;
        }
        else {
            std::wcerr << L"[ERROR] �� ������� ������� ����������: " << dirPath << L"\n";
            return false;
        }
    }
    return true;
}

#endif // FILE_MANAGER_H

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

void select_directory(wchar_t* selectedPath);
void select_file(wchar_t* selectedPath);
bool CreateDirectoryIfNotExist(const wchar_t* dirPath);

#endif

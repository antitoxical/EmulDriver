#ifndef DRIVER_H
#define DDRIVER_H
#include <Windows.h>

#define IOCTL_ENCRYPT_FILE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DECRYPT_FILE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)

HANDLE CreateVirtualDevice();
void HandleIoctl(HANDLE hDevice, DWORD ioctlCode, const char* filePath);
void HandleIoctlEmulation(DWORD ioctlCode, const wchar_t* filePath, const wchar_t* outputDir);

#endif

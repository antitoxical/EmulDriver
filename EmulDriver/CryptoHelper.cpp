#include "CryptoHelper.h"
#include <iostream>
#include <fstream>

void xor_encrypt_decrypt(const wchar_t* inputPath, const wchar_t* outputPath, unsigned char key) {
    std::ifstream inputFile(inputPath, std::ios::binary); // ��������� ��� �������� ����
    std::ofstream outputFile(outputPath, std::ios::binary); // ��������� ��� ������ ��������� �����

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::wcerr << L"[ERROR] Unable to open files.\n";
        return;
    }

    char buffer; // �������� � ���������� �����������
    while (inputFile.read(&buffer, sizeof(buffer))) {
        buffer ^= key; // XOR ����������
        outputFile.write(&buffer, sizeof(buffer));
    }

    inputFile.close();
    outputFile.close();
}



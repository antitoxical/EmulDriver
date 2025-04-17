#include "CryptoHelper.h"
#include <iostream>
#include <fstream>

void xor_encrypt_decrypt(const wchar_t* inputPath, const wchar_t* outputPath, unsigned char key) {
    std::ifstream inputFile(inputPath, std::ios::binary); // Открываем как бинарный файл
    std::ofstream outputFile(outputPath, std::ios::binary); // Открываем для записи бинарного файла

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::wcerr << L"[ERROR] Unable to open files.\n";
        return;
    }

    char buffer; // Работаем с побайтовым шифрованием
    while (inputFile.read(&buffer, sizeof(buffer))) {
        buffer ^= key; // XOR шифрование
        outputFile.write(&buffer, sizeof(buffer));
    }

    inputFile.close();
    outputFile.close();
}



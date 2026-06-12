#include "../crossMenu.h"

int CrossPlatform::checkKeyAscii() {
    cout << "Введите сдвиг (0-255): " << endl;
    int shift;
    while (true) {
        cin >> shift;
        cin.ignore();
        if (shift >= 0 && shift <= 255) return shift;
        cout << "Сдвиг должен быть от 0 до 255!" << endl;
    }
}

void CrossPlatform::enterTextToEncryptAscii(int shift) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();
    string hexText = strToHex(text);
    string encryptedHex = encrAsciiText(hexText, shift);
    stringstream ss;
    ss << hex << setfill('0');
    for (unsigned char c : encryptedHex) ss << setw(2) << (int)c;
    cout << "Зашифрованный текст (HEX): " << ss.str() << endl;
}

void CrossPlatform::enterTextToDecryptAscii(int shift) {
    cout << "Введите HEX текст для расшифрования" << endl;
    string hexInput = checkText();
    string clean;
    for (char c : hexInput) if (isxdigit(c)) clean += c;
    string encryptedData = hexToStr(clean);
    string decryptedHex = decrAsciiText(encryptedData, shift);
    string originalText = hexToStr(decryptedHex);
    cout << "Расшифрованный текст: " << originalText << endl;
}

void CrossPlatform::enterFileToEncryptAscii(int shift) {
    string pathFileToEncr = existFile("зашифровать", INPUT_DIR);
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
    if (encrAsciiFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, shift)) {
        cout << "Файл успешно зашифрован! Путь: " << ENCR_DIR + pathFileEncr << endl;
    }
    else cout << "Ошибка при шифровании!" << endl;
}

void CrossPlatform::enterFileToDecryptAscii(int shift) {
    string pathFileToDecr = existFile("расшифровать", ENCR_DIR);
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);
    if (decrAsciiFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, shift)) {
        cout << "Файл успешно расшифрован! Путь: " << DECR_DIR + pathFileDecr << endl;
    }
    else cout << "Ошибка при расшифровании!" << endl;
}

void CrossPlatform::choiceFuncOfTextAscii() {
    try {
        int shift = checkKeyAscii();
        int choice = showTextOperations();
        switch (FunctionsOfText(choice)) {
        case FunctionsOfText::ENCRYPT_TEXT:
            enterTextToEncryptAscii(shift);
            break;
        case FunctionsOfText::DECRYPT_TEXT:
            enterTextToDecryptAscii(shift);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}

void CrossPlatform::choiceFuncOfFileAscii() {
    try {
        int shift = checkKeyAscii();
        int choice = showFileOperations();
        switch (FunctionsOfFile(choice)) {
        case FunctionsOfFile::ENCRYPT_FILE:
            enterFileToEncryptAscii(shift);
            break;
        case FunctionsOfFile::DECRYPT_FILE:
            enterFileToDecryptAscii(shift);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}
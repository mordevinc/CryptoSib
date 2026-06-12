#include "../menu.h"

int Windows::checkKeyAscii() {
    cout << "Введите сдвиг (0-255): " << endl;
    int shift;
    while (true) {
        cin >> shift;
        cin.ignore();
        if (shift >= 0 && shift <= 255) return shift;
        cout << "Сдвиг должен быть от 0 до 255!" << endl;
    }
}

void Windows::enterTextToEncryptAscii(int shift) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();
    cout << "Зашифрованный текст: " << endl;
    cout << encrAsciiText(text, shift) << endl;
}

void Windows::enterTextToDecryptAscii(int shift) {
    cout << "Введите текст для расшифрования" << endl;
    string text = checkText();
    cout << "Расшифрованный текст: " << endl;
    cout << decrAsciiText(text, shift) << endl;
}

void Windows::enterFileToEncryptAscii(int shift) {
    string pathFileToEncr = existFile("зашифровать", INPUT_DIR);
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
    if (encrAsciiFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, shift)) {
        cout << "Файл успешно зашифрован! Путь: " << ENCR_DIR + pathFileEncr << endl;
    }
    else {
        cout << "Ошибка при шифровании!" << endl;
    }
}

void Windows::enterFileToDecryptAscii(int shift) {
    string pathFileToDecr = existFile("расшифровать", ENCR_DIR);
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);
    if (decrAsciiFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, shift)) {
        cout << "Файл успешно расшифрован! Путь: " << DECR_DIR + pathFileDecr << endl;
    }
    else {
        cout << "Ошибка при расшифровании!" << endl;
    }
}

void Windows::choiceFuncOfTextAscii() {
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
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void Windows::choiceFuncOfFileAscii() {
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
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}
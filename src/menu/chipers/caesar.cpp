#include "../menu.h"

uint64_t Windows::checkKeyCaesar() {
    cout << "Введите ключ (сдвиг от 1 до " << MODULE - 1 << ")" << endl;
    uint64_t shift;
    while (true) {
        cin >> shift;
        cin.ignore();
        if (shift > 0 && shift < MODULE) return shift;
        cout << "Сдвиг должен быть от 1 до " << MODULE - 1 << "!" << endl;
    }
}

void Windows::enterTextToEncryptCaesar(uint64_t shift, int mod) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();
    cout << "Зашифрованный текст: " << endl;
    cout << encrCaesarText(text, shift, mod) << endl;
}

void Windows::enterTextToDecryptCaesar(uint64_t shift, int mod) {
    cout << "Введите текст для расшифрования" << endl;
    string text = checkText();
    cout << "Расшифрованный текст: " << endl;
    cout << decrCaesarText(text, shift, mod) << endl;
}

void Windows::enterFileToEncryptCaesar(uint64_t shift, int mod) {
    string pathFileToEncr = existFile("зашифровать");
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
    if (encrCaesarFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, shift, mod)) {
        cout << "Файл успешно зашифрован!" << endl;
        cout << "Зашифрованный файл: " << ENCR_DIR + pathFileEncr << endl;
    }
    else {
        cout << "Ошибка при шифровании!" << endl;
    }
}

void Windows::enterFileToDecryptCaesar(uint64_t shift, int mod) {
    string pathFileToDecr = existFile("расшифровать");
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);
    if (decrCaesarFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, shift, mod)) {
        cout << "Файл успешно расшифрован!" << endl;
        cout << "Расшифрованный файл: " << DECR_DIR + pathFileDecr << endl;
    }
    else {
        cout << "Ошибка при расшифровании!" << endl;
    }
}

void Windows::choiceFuncOfTextCaesar() {
    try {
        uint64_t shift = checkKeyCaesar();
        int choice = showTextOperations();
        switch (FunctionsOfText(choice)) {
        case FunctionsOfText::ENCRYPT_TEXT:
            enterTextToEncryptCaesar(shift, MODULE);
            break;
        case FunctionsOfText::DECRYPT_TEXT:
            enterTextToDecryptCaesar(shift, MODULE);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void Windows::choiceFuncOfFileCaesar() {
    try {
        uint64_t shift = checkKeyCaesar();
        int choice = showFileOperations();
        switch (FunctionsOfFile(choice)) {
        case FunctionsOfFile::ENCRYPT_FILE:
            enterFileToEncryptCaesar(shift, MODULE);
            break;
        case FunctionsOfFile::DECRYPT_FILE:
            enterFileToDecryptCaesar(shift, MODULE);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}
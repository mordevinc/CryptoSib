#include "../crossMenu.h"

void CrossPlatform::enterTextToEncryptRsa(uint64_t e, uint64_t n) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();
    string hexText = strToHex(text);
    cout << "Зашифрованный текст (HEX): " << encrRsaText(hexText, e, n) << endl;
}

void CrossPlatform::enterTextToDecryptRsa(uint64_t d, uint64_t n) {
    cout << "Введите HEX текст для расшифрования" << endl;
    string cipher = checkText();
    string decryptedHex = decrRsaText(cipher, d, n);
    string originalText = hexToStr(decryptedHex);
    cout << "Расшифрованный текст: " << originalText << endl;
}

void CrossPlatform::enterFileToEncryptRsa(uint64_t e, uint64_t n) {
    string pathFileToEncr = existFile("зашифровать");
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
    if (encrRsaFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, e, n)) {
        cout << "Файл успешно зашифрован! Путь: " << ENCR_DIR + pathFileEncr << endl;
    }
    else cout << "Ошибка при шифровании!" << endl;
}

void CrossPlatform::enterFileToDecryptRsa(uint64_t d, uint64_t n) {
    string pathFileToDecr = existFile("расшифровать");
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);
    if (decrRsaFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, d, n)) {
        cout << "Файл успешно расшифрован! Путь: " << DECR_DIR + pathFileDecr << endl;
    }
    else cout << "Ошибка при расшифровании!" << endl;
}

void CrossPlatform::choiceFuncOfTextRsa() {
    try {
        uint64_t e, d, n;
        cout << "Введите модуль n: "; cin >> n;
        cout << "Введите открытую экспоненту e: "; cin >> e; cin.ignore();
        int choice = showTextOperations();
        switch (FunctionsOfText(choice)) {
        case FunctionsOfText::ENCRYPT_TEXT:
            enterTextToEncryptRsa(e, n); break;
        case FunctionsOfText::DECRYPT_TEXT: {
            cout << "Введите закрытую экспоненту d: "; cin >> d; cin.ignore();
            enterTextToDecryptRsa(d, n); break;
        }
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}

void CrossPlatform::choiceFuncOfFileRsa() {
    try {
        uint64_t e, d, n;
        cout << "Введите модуль n: "; cin >> n;
        cout << "Введите открытую экспоненту e: "; cin >> e; cin.ignore();
        int choice = showFileOperations();
        switch (FunctionsOfFile(choice)) {
        case FunctionsOfFile::ENCRYPT_FILE:
            enterFileToEncryptRsa(e, n); break;
        case FunctionsOfFile::DECRYPT_FILE: {
            cout << "Введите закрытую экспоненту d: "; cin >> d; cin.ignore();
            enterFileToDecryptRsa(d, n); break;
        }
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}

void CrossPlatform::choiceKeyGenRsa() {
    try {
        uint64_t p, q;
        cout << "Введите простое число p: "; cin >> p;
        cout << "Введите простое число q: "; cin >> q; cin.ignore();
        auto keys = genRsaKeys(p, q);
        cout << "Открытый ключ (e, n): (" << keys.first << ", " << p * q << ")" << endl;
        cout << "Закрытый ключ (d, n): (" << keys.second << ", " << p * q << ")" << endl;
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}
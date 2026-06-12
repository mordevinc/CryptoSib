#include "../menu.h"

void Windows::enterTextToEncryptRsa(uint64_t e, uint64_t n) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();
    cout << "Зашифрованный текст (блоки): " << endl;
    cout << encrRsaText(text, e, n) << endl;
}

void Windows::enterTextToDecryptRsa(uint64_t d, uint64_t n) {
    cout << "Введите зашифрованный текст (блоки через пробел):" << endl;
    string cipher;
    getline(cin, cipher);
    cout << "Расшифрованный текст: " << endl;
    cout << decrRsaText(cipher, d, n) << endl;
}

void Windows::enterFileToEncryptRsa(uint64_t e, uint64_t n) {
    string pathFileToEncr = existFile("зашифровать");
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
    if (encrRsaFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, e, n)) {
        cout << "Файл успешно зашифрован!" << endl;
        cout << "Путь: " << ENCR_DIR + pathFileEncr << endl;
    }
    else {
        cout << "Ошибка при шифровании!" << endl;
    }
}

void Windows::enterFileToDecryptRsa(uint64_t d, uint64_t n) {
    string pathFileToDecr = existFile("расшифровать");
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);
    if (decrRsaFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, d, n)) {
        cout << "Файл успешно расшифрован!" << endl;
        cout << "Путь: " << DECR_DIR + pathFileDecr << endl;
    }
    else {
        cout << "Ошибка при расшифровании!" << endl;
    }
}

void Windows::choiceFuncOfTextRsa() {
    try {
        uint64_t e, d, n;
        cout << "Введите модуль n: "; cin >> n;
        cout << "Введите открытую экспоненту e (шифрование): "; cin >> e;
        cin.ignore();
        int choice = showTextOperations();
        switch (FunctionsOfText(choice)) {
        case FunctionsOfText::ENCRYPT_TEXT:
            enterTextToEncryptRsa(e, n);
            break;
        case FunctionsOfText::DECRYPT_TEXT: {
            cout << "Введите закрытую экспоненту d (расшифрование): "; cin >> d; cin.ignore();
            enterTextToDecryptRsa(d, n);
            break;
        }
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}

void Windows::choiceFuncOfFileRsa() {
    try {
        uint64_t e, d, n;
        cout << "Введите модуль n: "; cin >> n;
        cout << "Введите открытую экспоненту e (шифрование): "; cin >> e;
        cin.ignore();
        int choice = showFileOperations();
        switch (FunctionsOfFile(choice)) {
        case FunctionsOfFile::ENCRYPT_FILE:
            enterFileToEncryptRsa(e, n);
            break;
        case FunctionsOfFile::DECRYPT_FILE: {
            cout << "Введите закрытую экспоненту d (расшифрование): "; cin >> d; cin.ignore();
            enterFileToDecryptRsa(d, n);
            break;
        }
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}

void Windows::choiceKeyGenRsa() {
    try {
        uint64_t p, q;
        cout << "Введите простое число p: "; cin >> p;
        cout << "Введите простое число q: "; cin >> q;
        cin.ignore();
        auto keys = genRsaKeys(p, q);
        cout << "Открытый ключ (e, n): (" << keys.first << ", " << p * q << ")" << endl;
        cout << "Закрытый ключ (d, n): (" << keys.second << ", " << p * q << ")" << endl;
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}
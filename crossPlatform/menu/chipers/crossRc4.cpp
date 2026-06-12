#include "../crossMenu.h"

string CrossPlatform::checkKeyRc4() {
    string key;
    cout << "Введите ключ для RC4: " << endl;
    getline(cin, key);
    return key;
}

void CrossPlatform::enterTextToEncryptRc4(const string& key) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();
    string hexText = strToHex(text);
    string encrypted = rc4Crypt(hexText, key);
    stringstream ss;
    ss << hex << setfill('0');
    for (unsigned char c : encrypted) {
        ss << setw(2) << (int)c;
    }
    cout << "Зашифрованный текст (HEX): " << ss.str() << endl;
}

void CrossPlatform::enterTextToDecryptRc4(const string& key) {
    cout << "Введите HEX текст для расшифрования" << endl;
    string hexInput = checkText();
    string clean;
    for (char c : hexInput) {
        if (isxdigit(c)) clean += c;
    }
    string data;
    for (size_t i = 0; i < clean.size(); i += 2) {
        data.push_back((char)stoi(clean.substr(i, 2), nullptr, 16));
    }
    string decryptedHex = rc4Crypt(data, key);
    string originalText = hexToStr(decryptedHex);
    cout << "Расшифрованный текст: " << originalText << endl;
}

void CrossPlatform::enterFileToEncryptRc4(const string& key) {
    string pathFileToEncr = existFile("зашифровать", INPUT_DIR);
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
    if (rc4EncryptFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, key)) {
        cout << "Файл успешно зашифрован! Путь: " << ENCR_DIR + pathFileEncr << endl;
    }
    else {
        cout << "Ошибка при шифровании!" << endl;
    }
}

void CrossPlatform::enterFileToDecryptRc4(const string& key) {
    string pathFileToDecr = existFile("расшифровать", ENCR_DIR);
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);
    if (rc4DecryptFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, key)) {
        cout << "Файл успешно расшифрован! Путь: " << DECR_DIR + pathFileDecr << endl;
    }
    else {
        cout << "Ошибка при расшифровании!" << endl;
    }
}

void CrossPlatform::choiceFuncOfTextRc4() {
    try {
        string key = checkKeyRc4();
        int choice = showTextOperations();
        switch (FunctionsOfText(choice)) {
        case FunctionsOfText::ENCRYPT_TEXT:
            enterTextToEncryptRc4(key);
            break;
        case FunctionsOfText::DECRYPT_TEXT:
            enterTextToDecryptRc4(key);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void CrossPlatform::choiceFuncOfFileRc4() {
    try {
        string key = checkKeyRc4();
        int choice = showFileOperations();
        switch (FunctionsOfFile(choice)) {
        case FunctionsOfFile::ENCRYPT_FILE:
            enterFileToEncryptRc4(key);
            break;
        case FunctionsOfFile::DECRYPT_FILE:
            enterFileToDecryptRc4(key);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}
#include "../crossMenu.h"

string CrossPlatform::checkKeyXOR() {
    string password;
    cout << "Введите пароль для XOR: " << endl;
    getline(cin, password);
    return password;
}

void CrossPlatform::enterTextToEncryptXOR(const string& password) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();
    string hexText = strToHex(text);
    string encryptedHex = XOREncryptText(hexText, password);
    stringstream ss;
    ss << hex << setfill('0');
    for (unsigned char c : encryptedHex) ss << setw(2) << (int)c;
    cout << "Зашифрованный текст (HEX): " << ss.str() << endl;
}

void CrossPlatform::enterTextToDecryptXOR(const string& password) {
    cout << "Введите HEX текст для расшифрования" << endl;
    string hexInput = checkText();
    string clean;
    for (char c : hexInput) if (isxdigit(c)) clean += c;
    string encryptedData = hexToStr(clean);
    string decryptedHex = XORDecryptText(encryptedData, password);
    string originalText = hexToStr(decryptedHex);
    cout << "Расшифрованный текст: " << originalText << endl;
}

void CrossPlatform::enterFileToEncryptXOR(const string& password) {
    string pathFileToEncr = existFile("зашифровать", INPUT_DIR);
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
    if (XOREncryptFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, password)) {
        cout << "Файл успешно зашифрован! Путь: " << ENCR_DIR + pathFileEncr << endl;
    }
    else cout << "Ошибка при шифровании!" << endl;
}

void CrossPlatform::enterFileToDecryptXOR(const string& password) {
    string pathFileToDecr = existFile("расшифровать", ENCR_DIR);
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);
    if (XORDecryptFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, password)) {
        cout << "Файл успешно расшифрован! Путь: " << DECR_DIR + pathFileDecr << endl;
    }
    else cout << "Ошибка при расшифровании!" << endl;
}

void CrossPlatform::choiceFuncOfTextXOR() {
    try {
        string password = checkKeyXOR();
        int choice = showTextOperations();
        switch (FunctionsOfText(choice)) {
        case FunctionsOfText::ENCRYPT_TEXT:
            enterTextToEncryptXOR(password);
            break;
        case FunctionsOfText::DECRYPT_TEXT:
            enterTextToDecryptXOR(password);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}

void CrossPlatform::choiceFuncOfFileXOR() {
    try {
        string password = checkKeyXOR();
        int choice = showFileOperations();
        switch (FunctionsOfFile(choice)) {
        case FunctionsOfFile::ENCRYPT_FILE:
            enterFileToEncryptXOR(password);
            break;
        case FunctionsOfFile::DECRYPT_FILE:
            enterFileToDecryptXOR(password);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}
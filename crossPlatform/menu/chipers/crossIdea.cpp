#include "../crossMenu.h"

string CrossPlatform::checkKeyIdea() {
    string password;
    cout << "Введите пароль для IDEA: " << endl;
    getline(cin, password);
    return password;
}

void CrossPlatform::enterTextToEncryptIdea(const string& password) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();
    string hexText = strToHex(text);
    string encryptedHex = ideaEncryptText(hexText, password);
    stringstream ss;
    ss << hex << setfill('0');
    for (unsigned char c : encryptedHex) ss << setw(2) << (int)c;
    cout << "Зашифрованный текст (HEX): " << ss.str() << endl;
}

void CrossPlatform::enterTextToDecryptIdea(const string& password) {
    cout << "Введите HEX текст для расшифрования" << endl;
    string hexInput = checkText();
    string clean;
    for (char c : hexInput) if (isxdigit(c)) clean += c;
    string encryptedData = hexToStr(clean);
    string decryptedHex = ideaDecryptText(encryptedData, password);
    string originalText = hexToStr(decryptedHex);
    cout << "Расшифрованный текст: " << originalText << endl;
}

void CrossPlatform::enterFileToEncryptIdea(const string& password) {
    string pathFileToEncr = existFile("зашифровать", INPUT_DIR);
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
    if (ideaEncryptFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, password)) {
        cout << "Файл успешно зашифрован! Путь: " << ENCR_DIR + pathFileEncr << endl;
    }
    else cout << "Ошибка при шифровании!" << endl;
}

void CrossPlatform::enterFileToDecryptIdea(const string& password) {
    string pathFileToDecr = existFile("расшифровать", ENCR_DIR);
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);
    if (ideaDecryptFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, password)) {
        cout << "Файл успешно расшифрован! Путь: " << DECR_DIR + pathFileDecr << endl;
    }
    else cout << "Ошибка при расшифровании!" << endl;
}

void CrossPlatform::choiceFuncOfTextIdea() {
    try {
        string password = checkKeyIdea();
        int choice = showTextOperations();
        switch (FunctionsOfText(choice)) {
        case FunctionsOfText::ENCRYPT_TEXT:
            enterTextToEncryptIdea(password);
            break;
        case FunctionsOfText::DECRYPT_TEXT:
            enterTextToDecryptIdea(password);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}

void CrossPlatform::choiceFuncOfFileIdea() {
    try {
        string password = checkKeyIdea();
        int choice = showFileOperations();
        switch (FunctionsOfFile(choice)) {
        case FunctionsOfFile::ENCRYPT_FILE:
            enterFileToEncryptIdea(password);
            break;
        case FunctionsOfFile::DECRYPT_FILE:
            enterFileToDecryptIdea(password);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}
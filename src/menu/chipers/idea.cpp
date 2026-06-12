#include "../menu.h"

string Windows::checkKeyIdea() {
    string password;
    cout << "Введите пароль для IDEA: " << endl;
    getline(cin, password);
    return password;
}

void Windows::enterTextToEncryptIdea(const string& password) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();
    cout << "Зашифрованный текст: " << endl;
    cout << ideaEncryptText(text, password) << endl;
}

void Windows::enterTextToDecryptIdea(const string& password) {
    cout << "Введите текст для расшифрования" << endl;
    string text = checkText();
    cout << "Расшифрованный текст: " << endl;
    cout << ideaDecryptText(text, password) << endl;
}

void Windows::enterFileToEncryptIdea(const string& password) {
    string pathFileToEncr = existFile("зашифровать");
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
    if (ideaEncryptFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, password)) {
        cout << "Файл успешно зашифрован! Путь: " << ENCR_DIR + pathFileEncr << endl;
    }
    else {
        cout << "Ошибка при шифровании!" << endl;
    }
}

void Windows::enterFileToDecryptIdea(const string& password) {
    string pathFileToDecr = existFile("расшифровать");
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);
    if (ideaDecryptFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, password)) {
        cout << "Файл успешно расшифрован! Путь: " << DECR_DIR + pathFileDecr << endl;
    }
    else {
        cout << "Ошибка при расшифровании!" << endl;
    }
}

void Windows::choiceFuncOfTextIdea() {
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
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void Windows::choiceFuncOfFileIdea() {
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
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}
#include "../crossMenu.h"

vector<int> CrossPlatform::checkKeyPermutation() {
    string input;
    vector<int> key;
    cout << "Введите ключ перестановки (номера столбцов через пробел, начиная с 0): " << endl;
    getline(cin, input);
    stringstream ss(input);
    int num;
    while (ss >> num) {
        key.push_back(num);
    }
    return key;
}

void CrossPlatform::enterTextToEncryptPermutation(const vector<int>& key) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();
    string hexText = strToHex(text);
    string encryptedHex = encrPermutationText(hexText, key);
    cout << "Зашифрованный текст (HEX): " << encryptedHex << endl;
}

void CrossPlatform::enterTextToDecryptPermutation(const vector<int>& key) {
    cout << "Введите HEX текст для расшифрования" << endl;
    string hexInput = checkText();
    string decryptedHex = decrPermutationText(hexInput, key);
    string originalText = hexToStr(decryptedHex);
    cout << "Расшифрованный текст: " << originalText << endl;
}

void CrossPlatform::enterFileToEncryptPermutation(const vector<int>& key) {
    string pathFileToEncr = existFile("зашифровать", INPUT_DIR);
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
    if (encrPermutationFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, key)) {
        cout << "Файл успешно зашифрован! Путь: " << ENCR_DIR + pathFileEncr << endl;
    }
    else {
        cout << "Ошибка при шифровании!" << endl;
    }
}

void CrossPlatform::enterFileToDecryptPermutation(const vector<int>& key) {
    string pathFileToDecr = existFile("расшифровать", ENCR_DIR);
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);
    if (decrPermutationFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, key)) {
        cout << "Файл успешно расшифрован! Путь: " << DECR_DIR + pathFileDecr << endl;
    }
    else {
        cout << "Ошибка при расшифровании!" << endl;
    }
}

void CrossPlatform::choiceFuncOfTextPermutation() {
    try {
        vector<int> key = checkKeyPermutation();
        int choice = showTextOperations();
        switch (FunctionsOfText(choice)) {
        case FunctionsOfText::ENCRYPT_TEXT:
            enterTextToEncryptPermutation(key);
            break;
        case FunctionsOfText::DECRYPT_TEXT:
            enterTextToDecryptPermutation(key);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void CrossPlatform::choiceFuncOfFilePermutation() {
    try {
        vector<int> key = checkKeyPermutation();
        int choice = showFileOperations();
        switch (FunctionsOfFile(choice)) {
        case FunctionsOfFile::ENCRYPT_FILE:
            enterFileToEncryptPermutation(key);
            break;
        case FunctionsOfFile::DECRYPT_FILE:
            enterFileToDecryptPermutation(key);
            break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}
#include "../crossMenu.h"

uint64_t CrossPlatform::checkKeyCaesar() {
    cout << "Введите ключ (сдвиг от 1 до " << MODULE - 1 << ")" << endl;
    uint64_t shift;
    while (true) {
        cin >> shift; cin.ignore();
        if (shift > 0 && shift < MODULE) return shift;
        cout << "Сдвиг должен быть от 1 до " << MODULE - 1 << "!" << endl;
    }
}

void CrossPlatform::enterTextToEncryptCaesar(uint64_t shift, int mod) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();
    string hexText = strToHex(text);
    string encryptedHex = encrCaesarText(hexText, shift, mod);
    stringstream ss;
    ss << hex << setfill('0');
    for (unsigned char c : encryptedHex) ss << setw(2) << (int)c;
    cout << "Зашифрованный текст (HEX): " << ss.str() << endl;
}

void CrossPlatform::enterTextToDecryptCaesar(uint64_t shift, int mod) {
    cout << "Введите HEX текст для расшифрования" << endl;
    string hexInput = checkText();
    string clean;
    for (char c : hexInput) if (isxdigit(c)) clean += c;
    string encryptedData = hexToStr(clean);
    string decryptedHex = decrCaesarText(encryptedData, shift, mod);
    string originalText = hexToStr(decryptedHex);
    cout << "Расшифрованный текст: " << originalText << endl;
}

void CrossPlatform::enterFileToEncryptCaesar(uint64_t shift, int mod) {
    string pathFileToEncr = existFile("зашифровать", INPUT_DIR);
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
    if (encrCaesarFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, shift, mod)) {
        cout << "Файл успешно зашифрован! Путь: " << ENCR_DIR + pathFileEncr << endl;
    }
    else cout << "Ошибка при шифровании!" << endl;
}

void CrossPlatform::enterFileToDecryptCaesar(uint64_t shift, int mod) {
    string pathFileToDecr = existFile("расшифровать", ENCR_DIR);
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);
    if (decrCaesarFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, shift, mod)) {
        cout << "Файл успешно расшифрован! Путь: " << DECR_DIR + pathFileDecr << endl;
    }
    else cout << "Ошибка при расшифровании!" << endl;
}

void CrossPlatform::choiceFuncOfTextCaesar() {
    try {
        uint64_t shift = checkKeyCaesar();
        int choice = showTextOperations();
        switch (FunctionsOfText(choice)) {
        case FunctionsOfText::ENCRYPT_TEXT:
            enterTextToEncryptCaesar(shift, MODULE); break;
        case FunctionsOfText::DECRYPT_TEXT:
            enterTextToDecryptCaesar(shift, MODULE); break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}

void CrossPlatform::choiceFuncOfFileCaesar() {
    try {
        uint64_t shift = checkKeyCaesar();
        int choice = showFileOperations();
        switch (FunctionsOfFile(choice)) {
        case FunctionsOfFile::ENCRYPT_FILE:
            enterFileToEncryptCaesar(shift, MODULE); break;
        case FunctionsOfFile::DECRYPT_FILE:
            enterFileToDecryptCaesar(shift, MODULE); break;
        default: cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) { cerr << "Ошибка: " << e.what() << endl; }
}
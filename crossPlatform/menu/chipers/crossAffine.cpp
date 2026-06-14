#include "../crossMenu.h"

uint64_t CrossPlatform::checkKeyAffine() {
    cout << "Введите ключ 'a'" << endl;
    uint64_t a;
    while (true) {
        cin >> a;
        if (isPrimeAM(a, MODULE)) {
            return a;
        }
        cout << "Числа a и m не являются взаимно простыми! Попробуйте снова!" << endl;
    }
}

void CrossPlatform::enterTextToEncryptAffine(uint64_t a, uint64_t b, int mod) {
    cout << "Введите текст для шифрования" << endl;
    string text = checkText();

    // HEX преобразование (ключевое отличие от Windows-версии!)
    string hexText = strToHex(text);
    string encryptedHex = encrAffineHex(hexText, a, b, mod);

    cout << "Зашифрованный текст (HEX): " << encryptedHex << endl;
}

void CrossPlatform::enterTextToDecryptAffine(uint64_t a, uint64_t b, int mod) {
    cout << "Введите HEX текст для расшифрования" << endl;
    string hexInput = checkText();

    // Очистка от пробелов
    string clean;
    for (char c : hexInput) {
        if (isxdigit(c)) clean += c;
    }

    string decryptedHex = decrAffineHex(clean, a, b, mod);
    string originalText = hexToStr(decryptedHex);

    cout << "Расшифрованный текст: " << originalText << endl;
}

void CrossPlatform::enterFileToEncryptAffine(uint64_t a, uint64_t b, int mod) {
    string pathFileToEncr = existFile("зашифровать");
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);

    if (encrAffineFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, a, b, mod)) {
        cout << "Файл успешно зашифрован!" << endl;
        cout << "Зашифрованный файл находится по пути: " << ENCR_DIR + pathFileEncr << endl;
    }
    else {
        cout << "Ошибка при шифровании файла!" << endl;
    }
}

void CrossPlatform::enterFileToDecryptAffine(uint64_t a, uint64_t b, int mod) {
    string pathFileToDecr = existFile("расшифровать");
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);

    if (decrAffineFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, a, b, mod)) {
        cout << "Файл успешно расшифрован!" << endl;
        cout << "Расшифрованный файл находится по пути: " << DECR_DIR + pathFileDecr << endl;
    }
    else {
        cout << "Ошибка при расшифровании файла!" << endl;
    }
}

void CrossPlatform::choiceFuncOfTextAffine() {
    try {
        uint64_t a = checkKeyAffine();
        cout << "Введите ключ 'b'" << endl;
        uint64_t b;
        cin >> b;
        cin.ignore();

        int choice = showTextOperations();
        switch (FunctionsOfText(choice)) {
        case FunctionsOfText::ENCRYPT_TEXT:
            enterTextToEncryptAffine(a, b, MODULE);
            break;
        case FunctionsOfText::DECRYPT_TEXT:
            enterTextToDecryptAffine(a, b, MODULE);
            break;
        default:
            cout << "ОШИБКА" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void CrossPlatform::choiceFuncOfFileAffine() {
    try {
        uint64_t a = checkKeyAffine();
        cout << "Введите ключ 'b'" << endl;
        uint64_t b;
        cin >> b;
        cin.ignore();

        int choice = showFileOperations();
        switch (FunctionsOfFile(choice)) {
        case FunctionsOfFile::ENCRYPT_FILE:
            enterFileToEncryptAffine(a, b, MODULE);
            break;
        case FunctionsOfFile::DECRYPT_FILE:
            enterFileToDecryptAffine(a, b, MODULE);
            break;
        default:
            cout << "ERROR" << endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Ошибка файловой системы: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}
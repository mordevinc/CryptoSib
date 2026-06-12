#include "../crossMenu.h"

string CrossPlatform::checkKeyPleyfair() {
    string key;
    while (true) {
        cout << "Введите ключ" << endl;
        getline(cin, key);
        bool validKey = true;
        for (unsigned char item : key) {
            if (item >= MODULE) {
                cout << "Символы, содержащиеся в ключе, не относятся к данному алфавиту" << endl;
                validKey = false;
                break;
            }
        }
        if (validKey && !key.empty()) {
            return key;
        }
        if (key.empty()) cout << "Ключ не может быть пустым!" << endl;
    }
}

unsigned char CrossPlatform::checkMarkerPleyfair() {
    unsigned char marker;
    while (true) {
        cout << "Введите маркер для склейки биграм" << endl;
        cin >> marker;
        cin.ignore();
        if (marker < MODULE) {
            return marker;
        }
        cout << "Символ для маркера не относится к данному алфавиту" << endl;
    }
}

void CrossPlatform::enterTextToEncryptPleyfair(const string& key, unsigned char marker, int mod) {
    string text = checkText();

    // HEX преобразование (ключевое отличие!)
    string hexText = strToHex(text);

    unsigned char** pm = genMatrixPleyfair(key, mod);
    if (!pm) throw runtime_error("Не удалось создать матрицу");

    vector<string> bgr = genBigramsPleyfair(hexText, marker);
    vector<string> encrBgr = encrBigramsPleyfair(pm, bgr, mod);
    string encryptedData = encrTextPleyfair(encrBgr);
    deleteMatrix(pm, mod);

    cout << "Зашифрованный текст (HEX): ";
    for (unsigned char c : encryptedData) {
        cout << hex << setw(2) << setfill('0') << (int)c;
    }
    cout << dec << endl;
}

void CrossPlatform::enterTextToDecryptPleyfair(const string& key, unsigned char marker, int mod) {
    cout << "Введите HEX текст для расшифрования" << endl;
    string hexInput = checkText();

    // Очистка от пробелов
    string clean;
    for (char c : hexInput) {
        if (isxdigit(c)) clean += c;
    }

    if (clean.length() % 2 != 0) {
        throw runtime_error("Нечётная длина HEX строки");
    }

    string encryptedData = hexToStr(clean);

    unsigned char** pm = genMatrixPleyfair(key, mod);
    if (!pm) throw runtime_error("Не удалось создать матрицу");

    vector<string> encrBgr = genEncrBigramsPleyfair(encryptedData, marker);
    vector<string> decrBgr = decrBigramsPleyfair(pm, encrBgr, mod);
    string decryptedHex = decrTextPleyfair(decrBgr, marker);
    deleteMatrix(pm, mod);

    string originalText = hexToStr(decryptedHex);
    cout << "Расшифрованный текст: " << originalText << endl;
}

void CrossPlatform::enterFileToEncryptPleyfair(const string& key, unsigned char marker, int mod) {
    string pathFileToEncr = existFile("зашифровать", INPUT_DIR);
    string pathFileEncr = accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);

    if (encrFilePleyfair(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, key, marker, mod)) {
        cout << "Файл успешно зашифрован!" << endl;
        cout << "Зашифрованный файл находится по пути: " << ENCR_DIR + pathFileEncr << endl;
    }
    else {
        cout << "Ошибка при шифровании файла!" << endl;
    }
}

void CrossPlatform::enterFileToDecryptPleyfair(const string& key, unsigned char marker, int mod) {
    string pathFileToDecr = existFile("расшифровать", ENCR_DIR);
    string pathFileDecr = accessCreateDirForSaveFile("расшифрованному", DECR_DIR);

    if (decrFilePleyfair(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, key, marker, mod)) {
        cout << "Файл успешно расшифрован!" << endl;
        cout << "Расшифрованный файл находится по пути: " << DECR_DIR + pathFileDecr << endl;
    }
    else {
        cout << "Ошибка при расшифровании файла!" << endl;
    }
}

void CrossPlatform::choiceFuncOfTextPleyfair() {
    try {
        string key = checkKeyPleyfair();
        unsigned char marker = checkMarkerPleyfair();

        int choice = showTextOperations();
        switch (FunctionsOfText(choice)) {
        case FunctionsOfText::ENCRYPT_TEXT:
            enterTextToEncryptPleyfair(key, marker, MODULE);
            break;
        case FunctionsOfText::DECRYPT_TEXT:
            enterTextToDecryptPleyfair(key, marker, MODULE);
            break;
        default:
            cout << "ОШИБКА" << endl;
        }
    }
    catch (const bad_alloc& e) {
        cerr << "Ошибка выделения памяти: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void CrossPlatform::choiceFuncOfFilePleyfair() {
    try {
        string key = checkKeyPleyfair();
        unsigned char marker = checkMarkerPleyfair();

        int choice = showFileOperations();
        switch (FunctionsOfFile(choice)) {
        case FunctionsOfFile::ENCRYPT_FILE:
            enterFileToEncryptPleyfair(key, marker, MODULE);
            break;
        case FunctionsOfFile::DECRYPT_FILE:
            enterFileToDecryptPleyfair(key, marker, MODULE);
            break;
        default:
            cout << "ОШИБКА" << endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Ошибка файловой системы: " << e.what() << endl;
    }
    catch (const bad_alloc& e) {
        cerr << "Ошибка выделения памяти: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}
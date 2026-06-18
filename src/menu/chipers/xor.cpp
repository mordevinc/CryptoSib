#include "../menu.h"
#include "../../../crossPlatform/crypto/crossCrypto.h"

string Windows::checkKeyXOR() {
    string password;
    cout << "�������XOR��� ��� IDEA: " << endl;
    getline(cin, password);
    return password;
}

void Windows::enterTextToEncryptXOR(const string& password) {
    cout << "������� ����� ��� ����������" << endl;
    string text = checkText();

    // ����������� � HEX ����� �����������
    string hexText = strToHex(text);
    string encrypted = XOREncryptText(hexText, password);

    // ����������� ��������� � HEX ��� ������
    cout << "������������� ����� (HEX): ";
    for (unsigned char c : encrypted) {
        cout << hex << setw(2) << setfill('0') << (int)c;
    }
    cout << dec << endl;
}

void Windows::enterTextToDecryptXOR(const string& password) {
    cout << "������� HEX ����� ��� �������������" << endl;
    string hexInput = checkText();

    // ����������� HEX � �������� ������
    string clean;
    for (char c : hexInput) {
        if (isxdigit(c)) clean += c;
    }
    string data;
    for (size_t i = 0; i < clean.size(); i += 2) {
        data.push_back((char)stoi(clean.substr(i, 2), nullptr, 16));
    }

    string decrypted = XORDecryptText(data, password);
    string originalText = hexToStr(decrypted);

    cout << "�������������� �����: " << originalText << endl;
}

void Windows::enterFileToEncryptXOR(const string& password) {
    string pathFileToEncr = existFile("�����������", INPUT_DIR);
    string pathFileEncr = accessCreateDirForSaveFile("��������������", ENCR_DIR);
    if (XOREncryptFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, password)) {
        cout << "���� ������� ����������! ����: " << ENCR_DIR + pathFileEncr << endl;
    }
    else {
        cout << "������ ��� ����������!" << endl;
    }
}

void Windows::enterFileToDecryptXOR(const string& password) {
    string pathFileToDecr = existFile("������������", ENCR_DIR);
    string pathFileDecr = accessCreateDirForSaveFile("���������������", DECR_DIR);
    if (XORDecryptFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, password)) {
        cout << "���� ������� �����������! ����: " << DECR_DIR + pathFileDecr << endl;
    }
    else {
        cout << "������ ��� �������������!" << endl;
    }
}

void Windows::choiceFuncOfTextXOR() {
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
        default: cout << "������" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "������: " << e.what() << endl;
    }
}

void Windows::choiceFuncOfFileXOR() {
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
        default: cout << "������" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "������: " << e.what() << endl;
    }
}
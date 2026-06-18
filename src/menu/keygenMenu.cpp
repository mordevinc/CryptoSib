#include "menu.h"

void Windows::choiceKeyGen() {
    try {
        cout << "\n�������� �������� ��� ��������� �����" << endl;
        cout << "1) ������� ����" << endl;
        cout << "2) ���� ��������" << endl;
        cout << "3) ���� ������" << endl;
        cout << "4) RSA" << endl;
        cout << "5) ����� �� ASCII" << endl;
        cout << "6) XOR" << endl;
        cout << "7) RC4" << endl;
        cout << "8) ���������� ������������" << endl;
        cout << "��� ����� (1-8): ";

        int choice = getChoice(1, 8, "������� ��� ����� (1-8): ");

        switch (Algorithms(choice)) {
        case Algorithms::AFFINE: {
            pair<int, int> keys = genAfinKey(MODULE);
            cout << "���� 'a' = " << keys.first << ", ���� 'b' = " << keys.second << endl;
            break;
        }
        case Algorithms::PLAYFAIR: {
            cout << "����: " << genPleyfairKeyRead(MODULE) << endl;
            break;
        }
        case Algorithms::RSA: {
            choiceKeyGenRsa();
            break;
        }
        case Algorithms::CAESAR: {
            choiceKeyGenCaesar();
            break;
        }
        case Algorithms::ASCII: {
            choiceKeyGenAscii();
            break;
        }
        case Algorithms::XOR: {
            choiceKeyGenXOR();
            break;
        }
        case Algorithms::RC4: {
            choiceKeyGenRc4();
            break;
        }
        case Algorithms::PERMUTATION: {
            choiceKeyGenPermutation();
            break;
        }
        default:
            cout << "������\n";
        }
    }
    catch (const exception& e) {
        cerr << "������ ��������� �����: " << e.what() << endl;
    }
}

void Windows::choiceKeyGenCaesar() {
    int shift = genCaesarKey(MODULE);
    cout << "��������� �����: " << shift << endl;
}

void Windows::choiceKeyGenAscii() {
    int shift = genAsciiKey();
    cout << "��������� �����: " << shift << endl;
}

void Windows::choiceKeyGenXOR() {
    string key = genXORKey(16);
    cout << "������XOR������ IDEA: " << key << endl;
}

void Windows::choiceKeyGenRc4() {
    string key = genRc4Key(16);
    cout << "��������� ���� RC4: " << key << endl;
}

void Windows::choiceKeyGenPermutation() {
    cout << "������� ���������� ��������: ";
    int cols;
    cin >> cols;
    cin.ignore();
    vector<int> key = genPermutationKey(cols);
    cout << "��������� ���� ������������: ";
    for (int k : key) {
        cout << k << " ";
    }
    cout << endl;
}
#include "menu.h"

void Windows::choiceKeyGen() {
    try {
        cout << "\nВыберите алгоритм для генерации ключа" << endl;
        cout << "1) Афинный шифр" << endl;
        cout << "2) Шифр Плейфера" << endl;
        cout << "3) Шифр Цезаря" << endl;
        cout << "4) RSA" << endl;
        cout << "5) Сдвиг по ASCII" << endl;
        cout << "6) IDEA" << endl;
        cout << "7) RC4" << endl;
        cout << "8) Столбцовая перестановка" << endl;
        cout << "Ваш выбор (1-8): ";

        int choice = getChoice(1, 8, "Введите Ваш выбор (1-8): ");

        switch (Algorithms(choice)) {
        case Algorithms::AFFINE: {
            pair<int, int> keys = genAfinKey(MODULE);
            cout << "Ключ 'a' = " << keys.first << ", ключ 'b' = " << keys.second << endl;
            break;
        }
        case Algorithms::PLAYFAIR: {
            cout << "Ключ: " << genPleyfairKeyRead(MODULE) << endl;
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
        case Algorithms::IDEA: {
            choiceKeyGenIdea();
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
            cout << "ОШИБКА\n";
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка генерации ключа: " << e.what() << endl;
    }
}

void Windows::choiceKeyGenCaesar() {
    int shift = genCaesarKey(MODULE);
    cout << "Случайный сдвиг: " << shift << endl;
}

void Windows::choiceKeyGenAscii() {
    int shift = genAsciiKey();
    cout << "Случайный сдвиг: " << shift << endl;
}

void Windows::choiceKeyGenIdea() {
    string key = genIdeaKey(16);
    cout << "Случайный пароль IDEA: " << key << endl;
}

void Windows::choiceKeyGenRc4() {
    string key = genRc4Key(16);
    cout << "Случайный ключ RC4: " << key << endl;
}

void Windows::choiceKeyGenPermutation() {
    cout << "Введите количество столбцов: ";
    int cols;
    cin >> cols;
    cin.ignore();
    vector<int> key = genPermutationKey(cols);
    cout << "Случайный ключ перестановки: ";
    for (int k : key) {
        cout << k << " ";
    }
    cout << endl;
}
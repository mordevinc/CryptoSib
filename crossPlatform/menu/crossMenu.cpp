#include "crossMenu.h"

void CrossPlatform::crosspShowMenu() {
    while (true) {
        cout << "Выберите режим работы приложения" << endl;
        cout << "1) Шифрование/дешифрование текста" << endl;
        cout << "2) Шифрование/дешифрование файла" << endl;
        cout << "3) Генератор ключей" << endl;
        cout << "4) Выход из приложения" << endl;
        cout << "Ваш выбор: ";

        int choice = getChoice(1, 4, "Введите Ваш выбор (от 1 до 4): ");

        switch (FunctionsOfProgram(choice)) {
        case FunctionsOfProgram::TEXT:
            choiceFuncOfText();
            break;
        case FunctionsOfProgram::FILE:
            choiceFuncOfFile();
            break;
        case FunctionsOfProgram::KEY:
            choiceKeyGen();
            break;
        case FunctionsOfProgram::OFF:
            cout << "Выход из приложения...\n";
            return;
        default:
            cout << "ОШИБКА\n";
        }
    }
}

int CrossPlatform::showTextOperations() {
    cout << "\nВыбор операции:" << endl;
    cout << "1) Шифрование текста" << endl;
    cout << "2) Расшифрование текста" << endl;
    cout << "Введите Ваш выбор (1 или 2): ";
    return getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");
}

int CrossPlatform::showFileOperations() {
    cout << "\nВыбор операции:" << endl;
    cout << "1) Шифрование файла" << endl;
    cout << "2) Расшифрование файла" << endl;
    cout << "Введите Ваш выбор (1 или 2): ";
    return getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");
}

void CrossPlatform::choiceFuncOfText() {
    cout << "\nВыберите алгоритм для шифрования/дешифрования текста:" << endl;
    cout << "1) Афинный шифр" << endl;
    cout << "2) Шифр Плейфера" << endl;

    int choice = getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");

    switch (Algorithms(choice)) {
    case Algorithms::AFFINE:
        choiceFuncOfTextAffine();
        break;
    case Algorithms::PLAYFAIR:
        choiceFuncOfTextPleyfair();
        break;
    default:
        cout << "ERROR\n";
    }
}

void CrossPlatform::choiceFuncOfFile() {
    cout << "\nВыберите алгоритм для шифрования/дешифрования файла:" << endl;
    cout << "1) Афинный шифр" << endl;
    cout << "2) Шифр Плейфера" << endl;

    int choice = getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");

    switch (Algorithms(choice)) {
    case Algorithms::AFFINE:
        choiceFuncOfFileAffine();
        break;
    case Algorithms::PLAYFAIR:
        choiceFuncOfFilePleyfair();
        break;
    default:
        cout << "ОШИБКА\n";
    }
}
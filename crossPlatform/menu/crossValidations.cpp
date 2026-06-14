#include "crossMenu.h"

int CrossPlatform::getChoice(int min, int max, const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= min && val <= max) {
            cin.ignore();
            return val;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ошибка: введите число от " << min << " до " << max << endl;
    }
}

string CrossPlatform::checkText() {
    string text;
    while (true) {
        getline(cin, text);
        bool validText = true;
        for (unsigned char item : text) {
            if (item >= MODULE) {
                cout << "Символы, содержащиеся в тексте, не относятся к данному алфавиту" << endl;
                validText = false;
                break;
            }
        }
        if (validText) {
            return text;
        }
    }
}

string CrossPlatform::existFile(const string& operation, const string& dir) {
    string pathFile;
    while (true) {
        cout << "Введите путь до файла, который хотите " << operation << "." << endl;
        getline(cin, pathFile);
        ifstream file(dir + pathFile);
        if (file.good()) {
            file.close();
            return pathFile;
        }
        cout << "По указанному пути файл не найден! Попробуйте ввести существующий путь!" << endl;
    }
}

string CrossPlatform::accessCreateDirForSaveFile(const string& operation, const string& dir) {
    string pathFile;
    string choiceFile;
    while (true) {
        cout << "Введите путь для промежуточного " << operation << " файла." << endl;
        getline(cin, pathFile);
        fs::path p(dir + pathFile);
        if (fs::exists(p.parent_path()) || fs::create_directories(p.parent_path())) {
            return pathFile;
        }
        while (true) {
            cout << "Не удалось создать директорию! Хотите ввести другой путь? (да/нет):" << endl;
            getline(cin, choiceFile);
            if (choiceFile == "да") break;
            if (choiceFile == "нет") {
                cout << "Операция отменена!" << endl;
                return "";
            }
            cout << "Введите 'да' или 'нет'!" << endl;
        }
    }
}
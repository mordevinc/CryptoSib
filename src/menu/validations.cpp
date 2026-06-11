#include "menu.h"

int Windows::getChoice(int min, int max, const string& prompt) {
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

string Windows::checkText() {
	string text;
	while (true) {
		getline(cin, text);
		bool validText = 1;
		for (unsigned char item : text) {
			if (item < MODULE) {
				continue;
			}
			else {
				cout << "Символы, содержащиеся в тексте не относятся к данному алфавиту" << endl;
				validText = 0;
				break;
			}
		}
		if (validText) {
			return text;
		}
	}
}

string Windows::existFile(const string& operation) {
	string pathFile;
	while (true) {
		cout << "Введите путь до файла, который хотите " << operation << "." << endl;
		getline(cin, pathFile);
		ifstream file(INPUT_DIR + pathFile);
		if (file.good()) {
			file.close();
			return pathFile;
		}
		else {
			cout << "По указанному пути файл не найден! Попробуйте ввести существующий путь!" << endl;
		}
	}
}

string Windows::accessCreateDirForSaveFile(const string& operation, const string& dir) {
	string pathFile;
	string choiceFile;
	while (true) {
		cout << "Введите путь для промежуточного " << operation << " файла." << endl;
		getline(cin, pathFile);
		fs::path p(dir + pathFile);
		if (fs::exists(p.parent_path()) || fs::create_directories(p.parent_path())) {
			return pathFile;
		}
		else {
			while (true) {
				cout << "Не удалось создать директорию! Хотите ввести другой путь? (да/нет):" << endl;
				getline(cin, choiceFile);
				if (choiceFile == "да") {
					break;
				}
				else if (choiceFile == "нет") {
					cout << "Операция отменена!" << endl;
					return "Отмена";
				}
				else {
					cout << "Введите 'да' или 'нет'!" << endl;
				}
			}
			if (choiceFile == "да") {
				continue;
			}
		}
	}
}
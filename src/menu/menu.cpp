#include "menu.h"

// Установка кодировки консоли
void setConsoleEncoding() {
#ifdef _WIN32
	// Windows: устанавливаем кодировку 1251
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
#else
	setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
}

int getChoice(int min, int max, const string& prompt) {
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

void Windows::showMenu(){
	while (true) {

		cout << "Выберите режим работы приложения" << endl;
		cout << "1) Шифрование/дешифрование текста" << endl;
		cout << "2) Шифрование/дешифрование файла" << endl;
		cout << "3) Генератор ключей" << endl;
		cout << "Ваш выбор: ";

		int choice = getChoice(1, 4, " ");

		cout << endl;

		switch (FunctionsOfProgram(choice)) {
		case FunctionsOfProgram::TEXT:
			Windows::choiceFuncOfText();
			break;
		case FunctionsOfProgram::FILE:
			Windows::choiceFuncOfFile();
			break;
		case FunctionsOfProgram::KEY:
			Windows::choiceKeyGen();
			break;
		case FunctionsOfProgram::OFF:
			std::cout << "Выход из приложения...\n";
			return;
			break;
		default: cout << "ОШИБКА\n";
		}
	}
}

void Windows::choiceFuncOfTextAffine() {
	try {
		cout << "Введите ключ 'a'" << endl;
		uint64_t a;
		while (true) {
			cin >> a;
			if (isPrimeAM(a, MODULE)) {
				break;
			}
			else {
				cout << "Числа a и m не являются взаимно простыми! Попробуйте снова!" << endl;
			}
		}
		cout << "Введите ключ 'b'" << endl;
		uint64_t b;
		cin >> b;
		cin.ignore();
		cout << "\nВыбор операции:" << endl;
		cout << "1) Шифрование текста" << endl;
		cout << "2) Расшифрование текста" << endl;
		cout << "Введите Ваш выбор (1 или 2): ";
		int choice = getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");
		switch (FunctionsOfText(choice)) {
		case FunctionsOfText::ENCRYPT_TEXT: {
			cout << "Введите текст для шифрования" << endl;
			string text;
			getline(cin, text);
			cout << "Зашифрованный текст: " << endl;
			cout << encrAffineText(text, a, b, MODULE) << endl;
			break;
		}
		case FunctionsOfText::DECRYPT_TEXT: {
			cout << "Введите текст для расшифрования" << endl;
			string text;
			getline(cin, text);
			cout << "Расшифрованный текст: " << endl;
			cout << decrAffineText(text, a, b, MODULE) << endl;
			break;
		}
		default: cout << "ОШИБКА" << endl;
		}
	}
	catch (const exception& e) {
		cerr << "Ошибка: " << e.what() << endl;
	}
}
void Windows::choiceFuncOfTextPleyfair() {
	try {
		string key;
		unsigned char marker;
		while (true) {
			cout << "Введите ключ" << endl;
			getline(cin, key);
			bool validKey = 1;
			for (unsigned char item : key) {
				if (item < MODULE) {
					continue;
				}
				else {
					cout << "Символы, содержащиеся в ключе не относятся к данному алфавиту" << endl;
					validKey = 0;
					break;
				}
			}
			if (validKey) {
				break;
			}
		}
		while (true) {
			cout << "Введите маркер для склейки биграм" << endl;
			cin >> marker;
			cin.ignore();
			if (marker < MODULE) {
				break;
			}
			else {
				cout << "Символ для маркера не относятся к данному алфавиту" << endl;
			}

		}

		cout << "\nВыбор операции:" << endl;
		cout << "1) Шифрование текста" << endl;
		cout << "2) Расшифрование текста" << endl;
		cout << "Введите Ваш выбор (1 или 2): ";

		int choice = getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");

		switch (FunctionsOfText(choice)) {
		case FunctionsOfText::ENCRYPT_TEXT: {
			string text;
			while (true) {
				cout << "Введите текст для шифрования" << endl;
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
					break;
				}
			}
			unsigned char** pm = genMatrixPleyfair(key, MODULE);
			if (!pm) throw runtime_error("Не удалось создать матрицу");
			vector<string> bgr = genBigramsPleyfair(text, marker);
			vector<string> encrBgr = encrBigramsPleyfair(pm, bgr, MODULE);
			deleteMatrix(pm, MODULE);
			string encrTxt = encrTextPleyfair(encrBgr);
			cout << "Зашифрованный текст:" << endl;
			cout << encrTxt << endl;
			break;
		}
		case FunctionsOfText::DECRYPT_TEXT: {
			string text;
			while (true) {
				cout << "Введите текст для расшифрования" << endl;
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
					break;
				}
			}
			unsigned char** pm = genMatrixPleyfair(key, MODULE);
			if (!pm) throw runtime_error("Не удалось создать матрицу");
			vector<string> genEncrBgr = genEncrBigramsPleyfair(text, marker);
			vector<string> decrBgr = decrBigramsPleyfair(pm, genEncrBgr, MODULE);
			deleteMatrix(pm, MODULE);
			string decrTxt = decrTextPleyfair(decrBgr, marker);
			cout << "Расшифрованный text:" << endl;
			cout << decrTxt << endl;
			break;
		}
		default: cout << "ОШИБКА" << endl;
		}
	}
	catch (const bad_alloc& e) {
		cerr << "Ошибка выделения памяти: " << e.what() << endl;
	}
	catch (const exception& e) {
		cerr << "Ошибка: " << e.what() << endl;
	}
}
void Windows::choiceFuncOfFileAffine() {
	try {
		cout << "Введите ключ 'a'" << endl;
		uint64_t a;
		while (true) {
			cin >> a;
			if (isPrimeAM(a, MODULE)) {
				break;
			}
			else {
				cout << "Числа a и m не являются взаимно простыми! Попробуйте снова!" << endl;
			}
		}
		cout << "Введите ключ 'b'" << endl;
		uint64_t b;
		cin >> b;
		cin.ignore();

		cout << "\nВыбор операции:" << endl;
		cout << "1) Шифрование файла" << endl;
		cout << "2) Расшифрование файла" << endl;
		cout << "Введите Ваш выбор (1 или 2): ";

		int choice = getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");

		switch (FunctionsOfFile(choice)) {
		case FunctionsOfFile::ENCRYPT_FILE: {
			string pathFileToEncr;
			while (true) {
				cout << "Введите путь до файла, который хотите зашифровать." << endl;
				getline(cin, pathFileToEncr);
				ifstream file(INPUT_DIR + pathFileToEncr);
				if (file.good()) {
					file.close();
					break;
				}
				else {
					cout << "По указанному пути файл не найден! Попробуйте ввести существующий путь!" << endl;
				}
			}
			string pathFileEncr;
			string choiceFile;
			while (true) {
				cout << "Введите путь для промежуточного зашифрованного файла." << endl;
				getline(cin, pathFileEncr);
				fs::path p(ENCR_DIR + pathFileEncr);
				if (fs::exists(p.parent_path()) || fs::create_directories(p.parent_path())) {
					break;
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
							return;
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
			if (encrAffineFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, a, b, MODULE)) {
				cout << "Файл успешно зашифрован!" << endl;
				cout << "Зашифрованный файл находится по пути: " << ENCR_DIR + pathFileEncr << endl;
			}
			else {
				cout << "Ошибка при шифровании файла!" << endl;
			}
			break;
		}
		case FunctionsOfFile::DECRYPT_FILE: {
			string pathFileToDecr;
			while (true) {
				cout << "Введите путь до файла, который хотите расшифровать." << endl;
				getline(cin, pathFileToDecr);
				ifstream file(ENCR_DIR + pathFileToDecr);
				if (file.good()) {
					file.close();
					break;
				}
				else {
					cout << "По указанному пути файл не найден! Попробуйте ввести существующий путь!" << endl;
				}
			}
			string pathFileDecr;
			string choiceFile;
			while (true) {
				cout << "Введите путь для расшифрованного файла." << endl;
				getline(cin, pathFileDecr);
				fs::path p(DECR_DIR + pathFileDecr);
				if (fs::exists(p.parent_path()) || fs::create_directories(p.parent_path())) {
					break;
				}
				else {
					while (true) {
						cout << "Не удалось создать директорию! Хотите ввести другой путь? (да/нет): " << endl;
						getline(cin, choiceFile);
						if (choiceFile == "да") {
							break;
						}
						else if (choiceFile == "нет") {
							cout << "Операция отменена!" << endl;
							return;
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

			if (decrAffineFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, a, b, MODULE)) {
				cout << "Файл успешно расшифрован!" << endl;
				cout << "Расшифрованный файл находится по пути: " << DECR_DIR + pathFileDecr << endl;
			}
			else {
				cout << "Ошибка при расшифровании файла!" << endl;
			}
			break;
		}
		default: cout << "ERROR" << endl;
		}
	}
	catch (const fs::filesystem_error& e) {
		cerr << "Ошибка файловой системы: " << e.what() << endl;
	}
	catch (const exception& e) {
		cerr << "Ошибка: " << e.what() << endl;
	}
}

void Windows::choiceFuncOfFilePleyfair() {
	try {
		string key;
		unsigned char marker;
		while (true) {
			cout << "Enter the key" << endl;
			getline(cin, key);
			bool validKey = 1;
			for (unsigned char item : key) {
				if (item < MODULE) {
					continue;
				}
				else {
					cout << "Символы, содержащиеся в ключе не относятся к данному алфавиту" << endl;
					validKey = 0;
					break;
				}
			}
			if (validKey) {
				break;
			}
		}
		while (true) {
			cout << "Введите маркер для склейки биграм" << endl;
			cin >> marker;
			cin.ignore();
			if (marker < MODULE) {
				break;
			}
			else {
				cout << "Символ для маркера не относятся к данному алфавиту" << endl;
			}

		}

		cout << "\nВыбор операции:" << endl;
		cout << "1) Шифрование файла" << endl;
		cout << "2) Расшифрование файла" << endl;
		cout << "Введите Ваш выбор (1 или 2): ";

		int choice = getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");

		switch (FunctionsOfFile(choice)) {
		case FunctionsOfFile::ENCRYPT_FILE: {
			string pathFileToEncr;
			while (true) {
				cout << "Введите путь до файла, который хотите зашифровать." << endl;
				getline(cin, pathFileToEncr);
				ifstream file(INPUT_DIR + pathFileToEncr);
				if (file.good()) {
					file.close();
					break;
				}
				else {
					cout << "По указанному пути файл не найден! Попробуйте ввести существующий путь!" << endl;
				}
			}
			string pathFileEncr;
			string choiceFile;
			while (true) {
				cout << "Введите путь для промежуточного зашифрованного файла." << endl;
				getline(cin, pathFileEncr);
				fs::path p(ENCR_DIR + pathFileEncr);
				if (fs::exists(p.parent_path()) || fs::create_directories(p.parent_path())) {
					break;
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
							return;
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

			if (encrFilePleyfair(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, key, marker, MODULE)) {
				cout << "Файл успешно зашифрован!" << endl;
				cout << "Зашифрованный файл находится по пути: " << ENCR_DIR + pathFileEncr << endl;
			}
			else {
				cout << "Ошибка при шифровании файла!" << endl;
			}
			break;
		}
		case FunctionsOfFile::DECRYPT_FILE: {
			string pathFileToDecr;
			while (true) {
				cout << "Введите путь до файла, который хотите расшифровать." << endl;
				getline(cin, pathFileToDecr);
				ifstream file(ENCR_DIR + pathFileToDecr);
				if (file.good()) {
					file.close();
					break;
				}
				else {
					cout << "По указанному пути файл не найден! Попробуйте ввести существующий путь!" << endl;
				}
			}
			string pathFileDecr;
			string choiceFile;
			while (true) {
				cout << "Введите путь для расшифрованного файла." << endl;
				getline(cin, pathFileDecr);
				fs::path p(DECR_DIR + pathFileDecr);
				if (fs::exists(p.parent_path()) || fs::create_directories(p.parent_path())) {
					break;
				}
				else {
					while (true) {
						cout << "Не удалось создать директорию! Хотите ввести другой путь? (да/нет): " << endl;
						getline(cin, choiceFile);
						if (choiceFile == "да") {
							break;
						}
						else if (choiceFile == "нет") {
							cout << "Операция отменена!" << endl;
							return;
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

			if (decrFilePleyfair(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, key, marker, MODULE)) {
				cout << "Файл успешно расшифрован!" << endl;
				cout << "Расшифрованный файл находится по пути: " << DECR_DIR + pathFileDecr << endl;
			}
			else {
				cout << "Ошибка при расшифровании файла!" << endl;
			}
			break;
		}
		default: cout << "ОШИБКА" << endl;
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

void Windows::choiceFuncOfText() {

	cout << "\nВыберите алгоритм для шифрования/дешифрования текста:" << endl;
	cout << "1) Афинный шифр" << endl;
	cout << "2) Шифр Плейфера" << endl;

	int choice = getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");
	
	switch (Algorithms(choice)) {
	case Algorithms::AFFINE:
		Windows::choiceFuncOfTextAffine();
		break;
	case Algorithms::PLAYFAIR:
		Windows::choiceFuncOfTextPleyfair();
		break;
	default: std::cout << "ERROR\n";
	}
}
void Windows::choiceFuncOfFile() {

	cout << "\nВыберите алгоритм для шифрования/дешифрования файла:" << endl;
	cout << "1) Афинный шифр" << endl;
	cout << "2) Шифр Плейфера" << endl;
	cout << "Ваш выбор (1 или 2): ";

	int choice = getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");

	switch (Algorithms(choice)) {
	case Algorithms::AFFINE:
		Windows::choiceFuncOfFileAffine();
		break;
	case Algorithms::PLAYFAIR:
		Windows::choiceFuncOfFilePleyfair();
		break;
	default: std::cout << "ОШИБКА\n";
	}
}

void Windows::choiceKeyGen() {
	try {

		cout << "\nВыберите алгоритм для генерации ключа" << endl;
		cout << "1) Афинный шифр" << endl;
		cout << "2) Шифр Плейфера" << endl;
		cout << "Ваш выбор (1 или 2): ";

		int choice = getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");

		switch (Algorithms(choice)) {
		case Algorithms::AFFINE:
		{
			pair<int, int> keys = genAfinKey(MODULE);
			cout << "Ключ 'a' = " << keys.first << ", ключ 'b' = " << keys.second << endl;
			break;
		}
		case Algorithms::PLAYFAIR:
		{
			cout << "Ключ: " << genPleyfairKeyRead(MODULE) << endl;
			break;
		}
		default: std::cout << "ОШИБКА\n";
		}
	}
	catch (const exception& e) {
		cerr << "Ошибка генерации ключа: " << e.what() << endl;
	}
}

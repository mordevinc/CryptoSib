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
void showMenu(){
	int choice;

	do {
		cout << "Выберите режим работы приложения" << endl;
		cout << "1) Шифрование/дешифрование текста" << endl;
		cout << "2) Шифрование/дешифрование файла" << endl;
		cout << "3) Генератор ключей" << endl;
		cout << "Ваш выбор: ";

		if (!(cin >> choice)) {
			cout << "Ошибка: Введите число от 1 до 4!" << endl;
			cin.clear();  // Сбрасываем флаг ошибки
			cin.ignore(1000, '\n');  // Очищаем буфер
			continue;  // Повторяем ввод
		}
		cin.ignore();
		cout << endl;

		switch (FunctionsOfProgram(choice)) {
		case FunctionsOfProgram::TEXT:
			choiceFuncOfText();
			break;
		case FunctionsOfProgram::FILE:
			choiceFuncOfFile();
			break;
		case FunctionsOfProgram::KEY:

			break;
		case FunctionsOfProgram::OFF:
			std::cout << "Выход из приложения...\n";
			break;
		default: std::cout << "ОШИБКА\n";
		}
	} while (choice != 4);
}

void choiceFuncOfTextAffine() {
	int choice;
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
	while (true) {
		cout << "\nВыбор операции:" << endl;
		cout << "1) Шифрование текста" << endl;
		cout << "2) Расшифрование текста" << endl;
		cout << "Введите Ваш выбор (1 или 2): ";
		cin >> choice;
		cin.ignore();

		if (choice == 1 || choice == 2) {
			break;
		}
		cout << "Ошибка: пожалуйста, введите 1 или 2" << endl;
	}
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
void choiceFuncOfTextPleyfair() {
	int choice;
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
	while (true) {
		cout << "\nВыбор операции:" << endl;
		cout << "1) Шифрование текста" << endl;
		cout << "2) Расшифрование текста" << endl;
		cout << "Введите Ваш выбор (1 или 2): ";
		cin >> choice;
		cin.ignore();
		if (choice == 1 || choice == 2) {
			break;
		}
		cout << "Ошибка: пожалуйста, введите 1 или 2" << endl;
	}
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
		unsigned char** pm = genMatrixPleyf(key, MODULE);
		vector<string> bgr = genBigrams(text, marker);
		vector<string> encrBgr = encrBigrams(pm, bgr, MODULE);
		deleteMatrix(pm, MODULE);
		string encrTxt = encrText(encrBgr);
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
		unsigned char** pm = genMatrixPleyf(key, MODULE);
		vector<string> genEncrBgr = genEncrBigrams(text, marker);
		vector<string> decrBgr = decrBigrams(pm, genEncrBgr, MODULE);
		deleteMatrix(pm, MODULE);
		string decrTxt = decrText(decrBgr, marker);
		cout << "Расшифрованный text:" << endl;
		cout << decrTxt << endl;
		break;
	}
	default: cout << "ОШИБКА" << endl;
	}
}
void choiceFuncOfFileAffine() {
	int choice;
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
	while (true) {
		cout << "\nВыбор операции:" << endl;
		cout << "1) Шифрование файла" << endl;
		cout << "2) Расшифрование файла" << endl;
		cout << "Введите Ваш выбор (1 или 2): ";
		cin >> choice;
		cin.ignore();

		if (choice == 1 || choice == 2) {
			break;
		}
		cout << "Ошибка: пожалуйста, введите 1 или 2" << endl;
	}
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
		if (encrAfinFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, a, b, MODULE)) {
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

		if (decrAfinFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, a, b, MODULE)) {
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

void choiceFuncOfFilePleyfair() {
	int choice;
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
	while (true) {
		cout << "\nВыбор операции:" << endl;
		cout << "1) Шифрование файла" << endl;
		cout << "2) Расшифрование файла" << endl;
		cout << "Введите Ваш выбор (1 или 2): ";
		cin >> choice;
		cin.ignore();

		if (choice == 1 || choice == 2) {
			break;
		}
		cout << "Ошибка: пожалуйста, введите 1 или 2" << endl;
	}
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

		if (encrPleyfFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, key, marker, MODULE)) {
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

		if (decrPleyfFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, key, marker, MODULE)) {
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

void choiceFuncOfText() {
	int choice;
	while (true) {
		cout << "\nВыберите алгоритм для шифрования/дешифрования текста:" << endl;
		cout << "1) Афинный шифр" << endl;
		cout << "2) Шифр Плейфера" << endl;
		cout << "Ваш выбор (1 или 2): ";
		cin >> choice;
		cin.ignore();

		if (choice == 1 || choice == 2) {
			break;
		}
		cout << "Ошибка: Введите 1 или 2" << endl;
	}
	switch (Algorithms(choice)) {
	case Algorithms::AFFINE:
		choiceFuncOfTextAffine();
		break;
	case Algorithms::PLAYFAIR:
		choiceFuncOfTextPleyfair();
		break;
	default: std::cout << "ERROR\n";
	}
}
void choiceFuncOfFile() {
	int choice;
	while (true) {
		cout << "\nВыберите алгоритм для шифрования/дешифрования файла:" << endl;
		cout << "1) Афинный шифр" << endl;
		cout << "2) Шифр Плейфера" << endl;
		cout << "Ваш выбор (1 или 2): ";
		cin >> choice;
		cin.ignore();

		if (choice == 1 || choice == 2) {
			break;
		}
		cout << "Ошибка: Введите 1 или 2" << endl;
	}
	switch (Algorithms(choice)) {
	case Algorithms::AFFINE:
		choiceFuncOfFileAffine();
		break;
	case Algorithms::PLAYFAIR:
		choiceFuncOfFilePleyfair();
		break;
	default: std::cout << "ОШИБКА\n";
	}
}


#include "crossMenu.h"


void crosspShowMenu(){
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
			crosspChoiceFuncOfText();
			break;
		case FunctionsOfProgram::FILE:
			crosspChoiceFuncOfFile();
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

void crosspChoiceFuncOfTextAffine() {
    int choice;
    cout << "Введите ключ 'a'" << endl;
    uint64_t a;
    while (true) {
        cin >> a;
        if (isPrimeAM(a, MODULE)) break;
        cout << "Числа a и m не являются взаимно простыми! Попробуйте снова!" << endl;
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
        if (choice == 1 || choice == 2) break;
        cout << "Ошибка: пожалуйста, введите 1 или 2" << endl;
    }
    
    switch (FunctionsOfText(choice)) {
    case FunctionsOfText::ENCRYPT_TEXT: {
        cout << "Введите текст для шифрования" << endl;
    string text;
    getline(cin, text);
    
    // Текст -> HEX
    string hexText = strToHex(text);
    
    // Шифруем HEX строку -> получаем HEX строку зашифрованных данных
    string encryptedHex = encrAffineHex(hexText, a, b, MODULE);
    
    cout << "Зашифрованный текст: " << encryptedHex << endl;
    break;
}
case FunctionsOfText::DECRYPT_TEXT: {
    cout << "Введите текст для расшифрования" << endl;
    string hexInput;
    getline(cin, hexInput);
    
    // Очищаем от пробелов
    string clean;
    for (char c : hexInput) {
        if (isxdigit(c)) clean += c;
    }
    
    // Дешифруем -> получаем HEX строку исходного текста
    string decryptedHex = decrAffineHex(clean, a, b, MODULE);
    
    // HEX -> текст
    string original = hexToStr(decryptedHex);
    
    cout << "Расшифрованный текст: " << original << endl;
    break;
}
    default: cout << "ОШИБКА" << endl;
    }
}


void crosspChoiceFuncOfTextPleyfair() {
    int choice;
    string key;
    unsigned char marker;
    
    // Ввод ключа
    while (true) {
        cout << "Введите ключ." << endl;
        getline(cin, key);
        bool validKey = true;
        for (unsigned char item : key) {
            if (item >= MODULE) {
                cout << "Символы, содержащиеся в ключе, не относятся к данному алфавиту" << endl;
                validKey = false;
                break;
            }
        }
        if (validKey && !key.empty()) break;
        if (key.empty()) cout << "Ключ не может быть пустым!" << endl;
    }
    
    // Ввод маркера
    while (true) {
        cout << "Введите маркер для склейки биграм:" << endl;
        string markerStr;
        getline(cin, markerStr);
        
        if (markerStr.empty()) {
            cout << "Маркер не может быть пустым!" << endl;
            continue;
        }
        
        bool isNumber = true;
        for (char c : markerStr) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }
        
        int markerInt;
        if (isNumber) {
            markerInt = stoi(markerStr);
        } else {
            markerInt = (unsigned char)markerStr[0];
        }
        
        if (markerInt >= 0 && markerInt < MODULE) {
            marker = (unsigned char)markerInt;
            break;
        }
        cout << "Маркер должен быть в диапазоне алфавита ASCII" << endl;
    }
    
    // Выбор операции
    string choiceStr;
    while (true) {
        cout << "\nВыбор операции:" << endl;
        cout << "1) Шифрование текста" << endl;
        cout << "2) Расшифрование текста" << endl;
        cout << "Введите Ваш выбор (1 или 2): ";
        getline(cin, choiceStr);
        
        if (choiceStr == "1" || choiceStr == "2") {
            choice = stoi(choiceStr);
            break;
        }
        cout << "Ошибка: пожалуйста, введите 1 или 2" << endl;
    }
    
    switch (FunctionsOfText(choice)) {
    case FunctionsOfText::ENCRYPT_TEXT: {
        cout << "Введите текст для шифрования" << endl;
        string text;
        getline(cin, text);
        
        string hexText = strToHex(text);
        
        unsigned char** pm = genMatrixPleyf(key, MODULE);
        vector<string> bgr = genBigrams(hexText, marker);
        vector<string> encrBgr = encrBigrams(pm, bgr, MODULE);
        string encryptedData = encrText(encrBgr);
        deleteMatrix(pm, MODULE);
        
        cout << "Зашифрованный текст: ";
        for (unsigned char c : encryptedData) {
            cout << hex << setw(2) << setfill('0') << (int)c;
        }
        cout << dec << endl;
        break;
    }
    case FunctionsOfText::DECRYPT_TEXT: {
        cout << "Введите текст для расшифрования" << endl;
        string hexInput;
        getline(cin, hexInput);
        
        // Очищаем от пробелов и проверяем
        string cleanHex;
        for (char c : hexInput) {
            if (isxdigit(c)) {
                cleanHex += c;
            }
        }
        
        if (cleanHex.length() % 2 != 0) {
            cout << "Ошибка: нечётная длина HEX строки!" << endl;
            break;
        }
        
        string encryptedData = hexToStr(cleanHex);
        
        unsigned char** pm = genMatrixPleyf(key, MODULE);
        vector<string> encrBgr = genEncrBigrams(encryptedData, marker);
        vector<string> decrBgr = decrBigrams(pm, encrBgr, MODULE);
        string decryptedHex = decrText(decrBgr, marker);
        deleteMatrix(pm, MODULE);
        
        string originalText = hexToStr(decryptedHex);
        cout << "Расшифрованный текст: " << originalText << endl;
        break;
    }
    default: cout << "ОШИБКА" << endl;
    }
}

void crosspChoiceFuncOfFileAffine() {
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

void crosspChoiceFuncOfFilePleyfair() {
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

void crosspChoiceFuncOfText() {
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
		crosspChoiceFuncOfTextAffine();
		break;
	case Algorithms::PLAYFAIR:
		crosspChoiceFuncOfTextPleyfair();
		break;
	default: std::cout << "ERROR\n";
	}
}
void crosspChoiceFuncOfFile() {
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
		crosspChoiceFuncOfFileAffine();
		break;
	case Algorithms::PLAYFAIR:
		crosspChoiceFuncOfFilePleyfair();
		break;
	default: std::cout << "ОШИБКА\n";
	}
}

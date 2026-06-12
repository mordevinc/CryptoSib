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

int Windows::showTextOperations() {
	cout << "\nВыбор операции:" << endl;
	cout << "1) Шифрование текста" << endl;
	cout << "2) Расшифрование текста" << endl;
	cout << "Введите Ваш выбор (1 или 2): ";
	return Windows::getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");
}

int Windows::showFileOperations() {
	cout << "\nВыбор операции:" << endl;
	cout << "1) Шифрование файла" << endl;
	cout << "2) Расшифрование файла" << endl;
	cout << "Введите Ваш выбор (1 или 2): ";

	return Windows::getChoice(1, 2, "Введите Ваш выбор (1 или 2): ");
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

void Windows::choiceFuncOfText() {

	cout << "\nВыберите алгоритм для шифрования/дешифрования текста:" << endl;
	cout << "1) Афинный шифр" << endl;
	cout << "2) Шифр Плейфера" << endl;
	cout << "3) Шифр Цезаря" << endl;     
	cout << "4) RSA" << endl;
	cout << "Ваш выбор (1-8): ";

	int choice = getChoice(1, 8, "Введите Ваш выбор (1-8): ");
	
	switch (Algorithms(choice)) {
	case Algorithms::AFFINE:
		Windows::choiceFuncOfTextAffine();
		break;
	case Algorithms::PLAYFAIR:
		Windows::choiceFuncOfTextPleyfair();
		break;
	case Algorithms::CAESAR:   
		choiceFuncOfTextCaesar(); 
		break;
	case Algorithms::RSA:      
		choiceFuncOfTextRsa(); 
		break;
	default: std::cout << "ERROR\n";
	}
}
void Windows::choiceFuncOfFile() {

	cout << "\nВыберите алгоритм для шифрования/дешифрования файла:" << endl;
	cout << "1) Афинный шифр" << endl;
	cout << "2) Шифр Плейфера" << endl;
	cout << "3) Шифр Цезаря" << endl;     
	cout << "4) RSA" << endl;
	cout << "Ваш выбор (1-8): ";

	int choice = getChoice(1, 8, "Введите Ваш выбор (1-8): ");

	switch (Algorithms(choice)) {
	case Algorithms::AFFINE:
		Windows::choiceFuncOfFileAffine();
		break;
	case Algorithms::PLAYFAIR:
		Windows::choiceFuncOfFilePleyfair();
		break;
	case Algorithms::CAESAR:   
		choiceFuncOfFileCaesar(); 
		break;  
	case Algorithms::RSA:      
		choiceFuncOfFileRsa();
		break;
	default: std::cout << "ОШИБКА\n";
	}
}
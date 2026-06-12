#include "menu.h"

void Windows::choiceKeyGen() {
	try {

		cout << "\nВыберите алгоритм для генерации ключа" << endl;
		cout << "1) Афинный шифр" << endl;
		cout << "2) Шифр Плейфера" << endl;
		cout << "4) RSA" << endl;
		cout << "Ваш выбор (1-8): ";

		int choice = getChoice(1, 8, "Введите Ваш выбор (1-8): ");

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
		case Algorithms::RSA:
			choiceKeyGenRsa();
			break;
		default: std::cout << "ОШИБКА\n";
		}
	}
	catch (const exception& e) {
		cerr << "Ошибка генерации ключа: " << e.what() << endl;
	}
}

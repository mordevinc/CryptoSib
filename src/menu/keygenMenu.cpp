#include "menu.h"

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

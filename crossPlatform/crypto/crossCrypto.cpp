#include "crossCrypto.h"

string strToHex(const string& str) {
	stringstream ss;
	ss << hex << setfill('0');
	for (unsigned char c : str) {
		ss << setw(2) << (int)c;
	}
	return ss.str();
}

string hexToStr(const string& hex) {
    try {
        if (hex.empty()) return "";

        // Проверка, что строка содержит только HEX символы
        for (char c : hex) {
            if (!isxdigit(c)) {
                throw runtime_error(string("Не HEX символ: ") + c);
            }
        }

        if (hex.length() % 2 != 0) {
            throw runtime_error("Нечётная длина HEX строки");
        }

        string result;
        result.reserve(hex.length() / 2);

        for (size_t i = 0; i < hex.length(); i += 2) {
            string byteStr = hex.substr(i, 2);
            char byte = (char)stoi(byteStr, nullptr, 16);
            result.push_back(byte);
        }
        return result;

    }
    catch (const invalid_argument& e) {
        cerr << "Ошибка: неверный HEX символ в строке" << endl;
        throw;
    }
    catch (const out_of_range& e) {
        cerr << "Ошибка: HEX значение вне диапазона" << endl;
        throw;
    }
    catch (const exception& e) {
        cerr << "Ошибка при конвертации HEX в строку: " << e.what() << endl;
        throw;
    }
}

// Шифрование HEX строки -> возвращает HEX строку зашифрованных данных
string encrAffineHex(const string& hexText, int a, int b, int m) {
    try {
        string encrypted = encrAffineText(hexText, a, b, m);

        // Преобразуем бинарные данные в HEX строку
        string result;
        for (unsigned char c : encrypted) {
            char buf[3];
            #ifdef _WIN32
            #else
            sprintf(buf, "%02x", c);
            #endif
            result += buf;
        }
        return result;
    }
    catch (const exception& e) {
        cerr << "Ошибка при аффинном шифровании HEX: " << e.what() << endl;
        throw;
    }
}

// Дешифрование HEX строки зашифрованных данных -> возвращает HEX строку исходного текста
string decrAffineHex(const string& hexCipher, int a, int b, int m) {
    try {
        // hexCipher - это HEX строка (символы 0-9A-F)
        // Нужно преобразовать её в бинарные данные для дешифрования
        string binaryCipher = hexToStr(hexCipher);

        // Дешифруем бинарные данные
        string decrypted = decrAffineText(binaryCipher, a, b, m);

        // decrypted - это HEX строка исходного текста (например "d09fd183...")
        return decrypted;
    }
    catch (const exception& e) {
        cerr << "Ошибка при аффинном дешифровании HEX: " << e.what() << endl;
        throw;
    }
}
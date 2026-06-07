#include "crypto.h"

unsigned char encrAffineByte(int a, int b, int m, unsigned char x) {
	int E = (a * x + b) % m;
	return (unsigned char)E;
}

unsigned char decrAffineByte(int d, int b, int m, unsigned char y) {
	int D = (d * ((y - b + m) % m)) % m;
	return (unsigned char)D;
}

bool isPrimeAM(int a, int m) {
	return evk(a, m) == 1;
}

string encrAffineText(const string& text, int a, int b, int m) {

	string encrTextPleyfair;

	for (unsigned char item : text) {
		encrTextPleyfair.push_back(encrAffineByte(a, b, m, item));
	}
	
	return encrTextPleyfair;
}

string decrAffineText(const string& text, int a, int b, int m) {

	string decrTextPleyfair;
	int d = ObrEvk(a, m, 'u');

	for (unsigned char item : text) {
		decrTextPleyfair.push_back(decrAffineByte(d, b, m, item));
	}

	return decrTextPleyfair;
}
bool encrAffineFile(const string& input, const string& output, int a, int b, int m) {
	try {
		fs::path outPath(output);
		if (!outPath.parent_path().empty()) {
			if (!fs::exists(outPath.parent_path())) {
				if (!fs::create_directories(outPath.parent_path())) {
					throw runtime_error("Не удалось создать директорию: " + outPath.parent_path().string());
				}
			}
		}

		ifstream in(input, ios::binary);
		if (!in.is_open()) {
			throw runtime_error("Не удалось открыть входной файл: " + input);
		}

		ofstream out(output, ios::binary);
		if (!out.is_open()) {
			in.close();
			throw runtime_error("Не удалось создать выходной файл: " + output);
		}

		char byte;
		while (in.get(byte)) {
			out.put(encrAffineByte(a, b, m, (unsigned char)byte));
		}
		in.close();
		out.close();
		return true;

	}
	catch (const fs::filesystem_error& e) {
		cerr << "Ошибка файловой системы: " << e.what() << endl;
		return false;
	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
		return false;
	}
	catch (const exception& e) {
		cerr << "Непредвиденная ошибка при шифровании файла: " << e.what() << endl;
		return false;
	}
}
bool decrAffineFile(const string& input, const string& output, int a, int b, int m) {
	try {
		int d = ObrEvk(a, m, 'u');

		fs::path outPath(output);
		if (!outPath.parent_path().empty()) {
			if (!fs::exists(outPath.parent_path())) {
				if (!fs::create_directories(outPath.parent_path())) {
					throw runtime_error("Не удалось создать директорию: " + outPath.parent_path().string());
				}
			}
		}

		ifstream in(input, ios::binary);
		if (!in.is_open()) {
			throw runtime_error("Не удалось открыть входной файл: " + input);
		}

		ofstream out(output, ios::binary);
		if (!out.is_open()) {
			in.close();
			throw runtime_error("Не удалось создать выходной файл: " + output);
		}

		char byte;
		while (in.get(byte)) {
			out.put(decrAffineByte(d, b, m, (unsigned char)byte));
		}
		in.close();
		out.close();
		return true;

	}
	catch (const fs::filesystem_error& e) {
		cerr << "Ошибка файловой системы: " << e.what() << endl;
		return false;
	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
		return false;
	}
	catch (const exception& e) {
		cerr << "Непредвиденная ошибка при дешифровании файла: " << e.what() << endl;
		return false;
	}
}

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

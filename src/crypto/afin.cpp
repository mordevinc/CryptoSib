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
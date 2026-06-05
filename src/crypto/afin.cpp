#include "crypto.h"

unsigned char encrAfinByte(int a, int b, int m, unsigned char x) {
	int E = (a * x + b) % m;
	return (unsigned char)E;
}

unsigned char decrAfinByte(int d, int b, int m, unsigned char y) {
	int D = (d * ((y - b + m) % m)) % m;
	return (unsigned char)D;
}

bool isPrimeAM(int a, int m) {
	return evk(a, m) == 1;
}

string encrAffineText(const string& text, int a, int b, int m) {

	string encrText;

	for (unsigned char item : text) {
		encrText.push_back(encrAfinByte(a, b, m, item));
	}
	
	return encrText;
}

string decrAffineText(const string& text, int a, int b, int m) {

	string decrText;
	int d = ObrEvk(a, m, 'u');

	for (unsigned char item : text) {
		decrText.push_back(decrAfinByte(d, b, m, item));
	}

	return decrText;
}

bool encrAfinFile(const string& input, const string& output, int a, int b, int m) {
	fs::path outPath(output);
	if (!outPath.parent_path().empty()) {
		if (!fs::exists(outPath.parent_path())) {
			if (!fs::create_directories(outPath.parent_path())) {
				cerr << "Не удалось создать директорию: " << outPath.parent_path() << endl;
				return false;
			}
		}
	}

	ifstream in(input, ios::binary);
	if (!in.is_open()) {
		cerr << "Не удалось открыть входной файл: " << input << endl;
		return false;
	}

	ofstream out(output, ios::binary);
	if (!out.is_open()) {
		cerr << "Не удалось создать выходной файл: " << output << endl;
		in.close();
		return false;
	}
	if (!in || !out) return false;
	char byte;
	while (in.get(byte)) {
		out.put(encrAfinByte(a, b, m, (unsigned char)byte));
	}
	in.close();
	out.close();
	return 1;
}
bool decrAfinFile(const string& input, const string& output, int a, int b, int m) {

	int d = ObrEvk(a, m, 'u');

	fs::path outPath(output);
	if (!outPath.parent_path().empty()) {
		if (!fs::exists(outPath.parent_path())) {
			if (!fs::create_directories(outPath.parent_path())) {
				cerr << "Не удалось создать директорию: " << outPath.parent_path() << endl;
				return false;
			}
		}
	}

	ifstream in(input, ios::binary);
	if (!in.is_open()) {
		cerr << "Не удалось открыть входной файл: " << input << endl;
		return false;
	}

	ofstream out(output, ios::binary);
	if (!out.is_open()) {
		cerr << "Не удалось создать выходной файл: " << output << endl;
		in.close();
		return false;
	}
	if (!in || !out) return false;
	char byte;
	while (in.get(byte)) {
		out.put(decrAfinByte(d, b, m, (unsigned char)byte));
	}
	in.close();
	out.close();
	return 1;
}
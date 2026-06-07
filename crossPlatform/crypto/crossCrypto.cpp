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
    if (hex.empty()) return "";
    
    // Проверка, что строка содержит только HEX символы
    for (char c : hex) {
        if (!isxdigit(c)) {
            cerr << "Ошибка: не HEX символ: " << c << endl;
            return "";
        }
    }
    
    if (hex.length() % 2 != 0) {
        cerr << "Ошибка: нечётная длина HEX строки: " << hex << endl;
        return "";
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

// Шифрование HEX строки -> возвращает HEX строку зашифрованных данных
string encrAffineHex(const string& hexText, int a, int b, int m) {
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

// Дешифрование HEX строки зашифрованных данных -> возвращает HEX строку исходного текста
string decrAffineHex(const string& hexCipher, int a, int b, int m) {
    // hexCipher - это HEX строка (символы 0-9A-F)
    // Нужно преобразовать её в бинарные данные для дешифрования
    string binaryCipher = hexToStr(hexCipher);
    
    // Дешифруем бинарные данные
    string decrypted = decrAffineText(binaryCipher, a, b, m);
    
    // decrypted - это HEX строка исходного текста (например "d09fd183...")
    return decrypted;
}
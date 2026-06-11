#include "crypto.h"


// Генерация ключа для аффинного шифра
pair<int, int> genAfinKey(int m) {
    try {
        // Инициализация ГСЧ
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, m - 1);

        // Генерируем 'a' взаимно простое с m
        int a = 0;
        do {
            a = dist(gen);
        } while (evk(a, m) != 1);

        // Генерируем 'b' (любое)
        uniform_int_distribution<> distB(0, m - 1);
        int b = distB(gen);

        return { a, b };
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Ошибка генерации ключа Аффинного шифра: " + std::string(e.what()));
    }
}

// Генерация случайного ключа для Playfair 
string genPleyfairKey(int m) {
    try {
        int length = sqrtZ(m);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, m - 1);

        unordered_set<unsigned char> used;
        string key;

        while (key.size() < length) {
            unsigned char ch = dist(gen);
            if (used.find(ch) == used.end()) {
                used.insert(ch);
                key += ch;
            }
        }

        return key;
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Ошибка генерации ключа шифра Плейфера: " + std::string(e.what()));
    }
}

// Генерация читаемого ключа (только печатные символы ASCII 32-126)
string genPleyfairKeyRead(int m) {
    try {
        int length = sqrtZ(m);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(32, 126);  // печатные ASCII

        unordered_set<unsigned char> used;
        string key;

        while (key.size() < length) {
            unsigned char ch = dist(gen);
            if (used.find(ch) == used.end()) {
                used.insert(ch);
                key += ch;
            }
        }

        return key;
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Ошибка генерации ключа шифра Плейфера: " + std::string(e.what()));
    }
}
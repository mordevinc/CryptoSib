#include "keygen.h"
#include <random>
#include <unordered_set>
#include <stdexcept>

int sqrtZ(int m) {
    if (m < 0)
        return -1;
    if (m == 0 || m == 1)
        return m;

    for (int i = 1; i <= m / i; ++i)
    {
        if (i * i == m)
        {
            return i;
        }
    }
    return -1;
}

int evk(int base, int mod) {
    int a = base;
    int b = mod;
    int oldB = 0;
    while (b > 0)
    {
        oldB = b;
        b = a % b;
        a = oldB;
    }
    return a;
}


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
    catch (const exception& e) {
        throw runtime_error("Ошибка генерации ключа Аффинного шифра: " + string(e.what()));
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
    catch (const exception& e) {
        throw runtime_error("Ошибка генерации ключа шифра Плейфера: " + string(e.what()));
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
    catch (const exception& e) {
        throw runtime_error("Ошибка генерации ключа шифра Плейфера: " + string(e.what()));
    }
}
#ifndef PERMUT_H
#define PERMUT_H

#include <string> 
#include <vector>

class SimplePermutation {
    private:
        std::string key; // ключ для перестановки
        std::vector<int> order; // порядок столбцов
        void generateOrder(); // key -> order
        std::vector<int> stringKeyToOrder(const std::string& strKey);
    public:
        SimplePermutation(const std::string& key);
        std::string encryptString(const std::string& text);// шифрование строки для текста
        std::string decryptString(const std::string& ciphertext);// дешифрование строки для текста
        std::vector<char> encryptData(const std::vector<char>& data); // шифрование данных для файлов 
        std::vector<char> decryptData(const std::vector<char>& data); // дешифрование данных для файлов
        bool encryptFile(const std::string& inputFile, const std::string& outputFile);
        bool decryptFile(const std::string& inputFile, const std::string& outputFile);
        int getKeyLength() const { return order.size(); }
};

#endif
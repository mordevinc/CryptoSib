#include "permut.h"

string encrPermutationText(const string& text, const vector<int>& key) {
    int cols = key.size();
    int rows = (text.size() + cols - 1) / cols;
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));

    // Заполняем матрицу по строкам
    int idx = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (idx < text.size()) {
                matrix[row][col] = text[idx++];
            }
        }
    }

    // Читаем по столбцам в порядке ключа
    string result;
    for (int k : key) {
        for (int row = 0; row < rows; row++) {
            if (matrix[row][k] != ' ') {
                result.push_back(matrix[row][k]);
            }
        }
    }
    return result;
}

string decrPermutationText(const string& text, const vector<int>& key) {
    int cols = key.size();
    int rows = (text.size() + cols - 1) / cols;
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));

    // Заполняем матрицу по столбцам в порядке ключа
    int idx = 0;
    for (int k : key) {
        for (int row = 0; row < rows; row++) {
            if (idx < text.size()) {
                matrix[row][k] = text[idx++];
            }
        }
    }

    // Читаем по строкам
    string result;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (matrix[row][col] != ' ') {
                result.push_back(matrix[row][col]);
            }
        }
    }

    // Удаляем лишние пробелы в конце
    while (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

bool encrPermutationFile(const string& input, const string& output, const vector<int>& key) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty()) {
            if (!fs::exists(outPath.parent_path())) {
                fs::create_directories(outPath.parent_path());
            }
        }
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();
        string encrypted = encrPermutationText(data, key);
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        out.write(encrypted.c_str(), encrypted.size());
        return true;
    }
    catch (...) { return false; }
}

bool decrPermutationFile(const string& input, const string& output, const vector<int>& key) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty()) {
            if (!fs::exists(outPath.parent_path())) {
                fs::create_directories(outPath.parent_path());
            }
        }
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();
        string decrypted = decrPermutationText(data, key);
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        out.write(decrypted.c_str(), decrypted.size());
        return true;
    }
    catch (...) { return false; }
}
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

std::string longestCommonSubstring(const std::string& str1, const std::string& str2) {
    int m = str1.length();
    int n = str2.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    int maxLength = 0;
    int endPos = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endPos = i - 1;
                }
            }
        }
    }

    return maxLength == 0 ? "" : str1.substr(endPos - maxLength + 1, maxLength);
}

int main() {
    std::string input;
    std::cout << "Введите строку из 10 слов на латинице: ";
    std::getline(std::cin, input);

    std::vector<std::string> words;
    std::stringstream ss(input);
    std::string word;
    
    while (ss >> word) {
        words.push_back(word);
    }

    if (words.size() < 10) {
        std::cout << "Ошибка: нужно ввести минимум 10 слов!" << std::endl;
        return 1;
    }

    int countEndWithB = 0;
    int countDInLast = 0;
    size_t maxLength = 0;
    int countMatchingChars = 0;

    for (size_t i = 0; i < words.size(); i++) {
        const auto& w = words[i];
        
        if (!w.empty() && std::tolower(w.back()) == 'b') {
            countEndWithB++;
        }
        
        if (w.length() > maxLength) {
            maxLength = w.length();
        }
        
        if (w.length() >= 4 && w[1] == w[w.length() - 2]) {
            countMatchingChars++;
        }
        
        if (i == words.size() - 1) {
            for (char c : w) {
                if (std::tolower(c) == 'd') countDInLast++;
            }
        }
    }

    std::string upperCaseString = input;
    std::transform(upperCaseString.begin(), upperCaseString.end(), upperCaseString.begin(), ::toupper);

    std::string longestCommon = "";
    for (size_t i = 0; i < words.size(); i++) {
        for (size_t j = i + 1; j < words.size(); j++) {
            std::string common = longestCommonSubstring(words[i], words[j]);
            if (common.length() > longestCommon.length()) {
                longestCommon = common;
            }
        }
    }

    std::cout << "\nРезультаты:\n";
    std::cout << "1. Слова на 'b': " << countEndWithB << std::endl;
    std::cout << "2. Длина самого длинного слова: " << maxLength << std::endl;
    std::cout << "3. Букв 'd' в последнем слове: " << countDInLast << std::endl;
    std::cout << "4. В верхнем регистре: " << upperCaseString << std::endl;
    std::cout << "5. Совпадает второй и предпоследний: " << countMatchingChars << std::endl;
    std::cout << "6. Самая длинная общая подстрока: " << (longestCommon.empty() ? "нет" : longestCommon) << std::endl;

    return 0;
}

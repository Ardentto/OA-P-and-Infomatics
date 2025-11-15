#include <iostream>
#include <string>

std::string findCommonSubstring(const std::string& s1, const std::string& s2) {
    std::string longest = "";
    
    // Простой перебор всех возможных подстрок
    for (int i = 0; i < s1.length(); i++) {
        for (int j = 0; j < s2.length(); j++) {
            int k = 0;
            // Сравниваем символы пока они совпадают
            while (i + k < s1.length() && j + k < s2.length() && 
                   s1[i + k] == s2[j + k]) {
                k++;
            }
            // Если нашли более длинную подстроку
            if (k > longest.length()) {
                longest = s1.substr(i, k);
            }
        }
    }
    
    return longest;
}

int main() {
    std::string input;
    std::cout << "Введите 10 слов: ";
    std::getline(std::cin, input);

    std::string words[10];
    int wordCount = 0;
    std::string currentWord = "";
    
    for (char c : input) {
        if (c == ' ') {
            if (!currentWord.empty()) {
                words[wordCount] = currentWord;
                wordCount++;
                currentWord = "";
                if (wordCount >= 10) break;
            }
        } else {
            currentWord += c;
        }
    }
    if (!currentWord.empty() && wordCount < 10) {
        words[wordCount] = currentWord;
        wordCount++;
    }

    if (wordCount < 10) {
        std::cout << "Нужно 10 слов!" << std::endl;
        return 1;
    }

    int wordsWithB = 0;
    int maxWordLength = 0;
    int dInLastWord = 0;
    int matchingChars = 0;
    
    std::string upperString = "";
    for (char c : input) {
        if (c >= 'a' && c <= 'z') {
            upperString += c - 32;  // в верхний регистр
        } else {
            upperString += c;
        }
    }

    for (int i = 0; i < 10; i++) {
        const std::string& w = words[i];
        
        if (!w.empty() && (w.back() == 'b' || w.back() == 'B')) {
            wordsWithB++;
        }
        
        if (w.length() > maxWordLength) {
            maxWordLength = w.length();
        }
        
        if (w.length() >= 4 && w[1] == w[w.length() - 2]) {
            matchingChars++;
        }
        
        if (i == 9) {
            for (char c : w) {
                if (c == 'd' || c == 'D') {
                    dInLastWord++;
                }
            }
        }
    }

    std::string longestCommon = "";
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            std::string common = findCommonSubstring(words[i], words[j]);
            if (common.length() > longestCommon.length()) {
                longestCommon = common;
            }
        }
    }

    std::cout << "\nРезультаты:\n";
    std::cout << "1. Слова на 'b': " << wordsWithB << std::endl;
    std::cout << "2. Длина самого длинного слова: " << maxWordLength << std::endl;
    std::cout << "3. Букв 'd' в последнем слове: " << dInLastWord << std::endl;
    std::cout << "4. В верхнем регистре: " << upperString << std::endl;
    std::cout << "5. Совпадает второй и предпоследний: " << matchingChars << std::endl;
    std::cout << "6. Самая длинная общая подстрока: " << 
        (longestCommon.empty() ? "нет" : longestCommon) << std::endl;

    return 0;
}

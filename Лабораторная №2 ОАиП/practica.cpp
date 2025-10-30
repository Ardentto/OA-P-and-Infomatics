#include <iostream>
#include <cstring>
#include <cctype>

void task1() {
    char input[256];
    std::cout << "Введите строку: ";
    std::cin.getline(input, 256);
    
    char target;
    std::cout << "Введите букву для поиска: ";
    std::cin >> target;
    std::cin.ignore();
    
    int count = 0;
    char* word = strtok(input, " ");
    
    while (word != nullptr) {
        if (tolower(word[0]) == tolower(target)) {
            count++;
        }
        word = strtok(nullptr, " ");
    }
    
    std::cout << "Количество слов, начинающихся с '" << target << "': " << count << std::endl;
}

void task2() {
    char input[256];
    std::cout << "Введите строку: ";
    std::cin.getline(input, 256);
    
    int minLen = 256;
    int maxLen = 0;
    char* word = strtok(input, " ");
    
    while (word != nullptr) {
        int len = strlen(word);
        if (len < minLen) minLen = len;
        if (len > maxLen) maxLen = len;
        word = strtok(nullptr, " ");
    }
    
    std::cout << "Минимальная длина слова: " << minLen << std::endl;
    std::cout << "Максимальная длина слова: " << maxLen << std::endl;
}

void task3() {
    char input[256];
    std::cout << "Введите строку: ";
    std::cin.getline(input, 256);
    
    int wordNum;
    std::cout << "Введите номер слова (начиная с 1): ";
    std::cin >> wordNum;
    
    char target;
    std::cout << "Введите букву для подсчета: ";
    std::cin >> target;
    std::cin.ignore();
    
    char* word = strtok(input, " ");
    int current = 1;
    int count = 0;
    
    while (word != nullptr) {
        if (current == wordNum) {
            for (char* ptr = word; *ptr; ptr++) {
                if (tolower(*ptr) == tolower(target)) {
                    count++;
                }
            }
            break;
        }
        word = strtok(nullptr, " ");
        current++;
    }
    
    std::cout << "Буква '" << target << "' встречается " << count << " раз" << std::endl;
}

void task4() {
    char input[256];
    std::cout << "Введите строку: ";
    std::cin.getline(input, 256);
    
    for (char* ptr = input; *ptr; ptr++) {
        *ptr = tolower(*ptr);
    }
    
    std::cout << "Строка в нижнем регистре: " << input << std::endl;
}

void task5() {
    char input[256];
    std::cout << "Введите строку: ";
    std::cin.getline(input, 256);
    
    int pos1, pos2;
    std::cout << "Введите позиции символов для сравнения (через пробел): ";
    std::cin >> pos1 >> pos2;
    std::cin.ignore();
    
    int count = 0;
    char* word = strtok(input, " ");
    
    while (word != nullptr) {
        int len = strlen(word);
        if (pos1 < len && pos2 < len && word[pos1] == word[pos2]) {
            count++;
        }
        word = strtok(nullptr, " ");
    }
    
    std::cout << "Количество слов с совпадающими символами: " << count << std::endl;
}

int main() {
    int choice;
    
    do {
        std::cout << "\nВыберите задачу (1-5) или 0 для выхода: ";
        std::cin >> choice;
        std::cin.ignore();
        
        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 0: std::cout << "Выход..." << std::endl; break;
            default: std::cout << "Неверный выбор!" << std::endl;
        }
    } while (choice != 0);
    
    return 0;
}
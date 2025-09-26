#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    int vowelCount = 0;
    
    cout << "Введите строку: ";
    getline(cin, str);
    
    for (char c:str) {
        c = tolower(c);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            vowelCount++;
        }
    }
    
    cout << "Количество гласных букв: " << vowelCount << endl;
    
    return 0;
}
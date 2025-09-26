#include <iostream>
using namespace std;

int main() {
    int number;
    
    cout << "Введите число: ";
    cin >> number;
    
    if (number % 3 == 0 && number % 5 == 0) {
        cout << "Число делится на 3 и на 5" << endl;
    } else if (number % 3 == 0) {
        cout << "Число делится на 3" << endl;
    } else if (number % 5 == 0) {
        cout << "Число делится на 5" << endl;
    } else {
        cout << "Число не делится на 3 и на 5" << endl;
    }
    
    return 0;
}
#include <iostream>
using namespace std;

int main() {
    int age;
    
    cout << "Введите ваш возраст: ";
    cin >> age;
    
    if (age < 18) {
        cout << "Вам меньше 18 лет" << endl;
    } else if (age >= 18 && age <= 60) {
        cout << "Ваш возраст от 18 до 60 лет" << endl;
    } else {
        cout << "Вам больше 60 лет" << endl;
    }
    
    return 0;
}
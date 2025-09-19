#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Введите количество машин: ";
    cin >> n;
    
    if (n < 0) {
        cout << "Ошибка: введено отрицательное число." << endl;
        return 1;
    }
    
    unsigned long long factorial = 1;
    int i = 1;
    
    while (i <= n) {
        factorial *= i;
        i++;
    }
    
    cout << "Факториал числа " << n << " равен " << factorial << endl;
    
    return 0;
}
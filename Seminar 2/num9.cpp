#include <iostream>
using namespace std;

int main() {
    int n;
    int sum = 0;
    
    cout << "Введите число n: ";
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0 || i % 5 == 0) {
            sum += i;
        }
    }
    
    cout << "Сумма чисел от 1 до " << n << ", которые делятся на 2 или на 5: " << sum << endl;
    
    return 0;
}
#include <iostream>
using namespace std;

int main() {
    int n;
    
    cout << "Введите число n: ";
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        cout << i << " в квадрате = " << i * i << endl;
    }
    
    return 0;
}
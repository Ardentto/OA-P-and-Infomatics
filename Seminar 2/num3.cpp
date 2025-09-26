#include <iostream>
using namespace std;

int main() {
    double celsius;
    
    cout << "Введите температуру в градусах Цельсия: ";
    cin >> celsius;
    
    double fahrenheit = celsius * 9.0 / 5.0 + 32;
    
    cout << celsius << " °C = " << fahrenheit << " °F" << endl;
    
    return 0;
}
#include <iostream>
using namespace std;

int main() {
    int total_cm;
    
    cout << "Введите длину в сантиметрах: ";
    cin >> total_cm;
    
    if (total_cm < 0) {
        cout << "Ошибка: длина не может быть отрицательной!" << endl;
        return 1;
    }
    
    int meters = total_cm / 100;     
    int centimeters = total_cm % 100; 
    
    
    cout << total_cm << " см = " << meters << " м " << centimeters << " см" << endl;
    
    return 0;
}
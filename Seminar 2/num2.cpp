#include <iostream>
using namespace std;

int main() {
    double length, width;
    
    cout << "Введите длину прямоугольника: ";
    cin >> length;
    
    cout << "Введите ширину прямоугольника: ";
    cin >> width;
    
    if (length <= 0 || width <= 0) {
        cout << "Ошибка: длина и ширина должны быть положительными числами!" << endl;
        return 1;
    }
    
    double area = length * width;
    cout << "Площадь прямоугольника: " << area << endl;
    
    return 0;
}
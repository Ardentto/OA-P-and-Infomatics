#include <iostream>
using namespace std;

int main() {
    double x1, y1, x2, y2, x3, y3;
    
    cout << "Введите координаты трех вершин треугольника (x1 y1 x2 y2 x3 y3): ";
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    
    double center_x = (x1 + x2 + x3) / 3;
    double center_y = (y1 + y2 + y3) / 3;
    
    cout << "Координаты центра масс треугольника: (" 
         << center_x << ", " << center_y << ")" << endl;
    
    return 0;
}
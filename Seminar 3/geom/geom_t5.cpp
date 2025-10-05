#include <iostream>
using namespace std;

int main() {
    double x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    
    double cross_product = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    
    if (cross_product == 0) {
        cout << "Точки лежат на одной прямой" << endl;
    } else {
        cout << "Точки не лежат на одной прямой" << endl;
    }
    
    return 0;
}
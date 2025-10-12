#include <iostream>
using namespace std;

double det(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
    return a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
}

int main() {
    double d = det(1, 1, 1, 2, -1, 3, -1, 4, -1);
    double dx = det(6, 1, 1, 14, -1, 3, 2, 4, -1);
    double dy = det(1, 6, 1, 2, 14, 3, -1, 2, -1);
    double dz = det(1, 1, 6, 2, -1, 14, -1, 4, 2);
    
    cout << dx/d << " " << dy/d << " " << dz/d << endl;
    return 0;
}
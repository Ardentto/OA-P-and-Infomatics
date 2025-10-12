#include <iostream>
using namespace std;

double det(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
    return a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
}

int main() {
    double d = det(3, -1, 2, 2, 4, -1, 1, -3, 1);
    double dx = det(5, -1, 2, 6, 4, -1, 4, -3, 1);
    double dy = det(3, 5, 2, 2, 6, -1, 1, 4, 1);
    double dz = det(3, -1, 5, 2, 4, 6, 1, -3, 4);
    
    cout << dx/d << " " << dy/d << " " << dz/d << endl;
    return 0;
}
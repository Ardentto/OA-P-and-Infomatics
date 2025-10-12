#include <iostream>
using namespace std;

int main() {
    double a1 = 2, b1 = 3, c1 = 13;
    double a2 = 5, b2 = -1, c2 = 9;
    
    double det = a1 * b2 - a2 * b1;
    double x = (c1 * b2 - c2 * b1) / det;
    double y = (a1 * c2 - a2 * c1) / det;
    
    cout << x << " " << y << endl;
    return 0;
}
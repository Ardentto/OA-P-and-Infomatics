#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x[4], y[4];
    for (int i = 0; i < 4; i++) {
        cin >> x[i] >> y[i];
    }
    
    double dx = x[0] - x[2];
    double dy = y[0] - y[2];
    double diagonal = sqrt(dx * dx + dy * dy);
    
    cout << diagonal << endl;
    
    return 0;
}
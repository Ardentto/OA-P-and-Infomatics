#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x[4], y[4], p = 0;
    for(int i = 0; i < 4; i++) cin >> x[i] >> y[i];
    for(int i = 0; i < 4; i++) p += sqrt(pow(x[i]-x[(i+1)%4],2) + pow(y[i]-y[(i+1)%4],2));
    cout << p;
}
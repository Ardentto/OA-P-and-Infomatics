#include <iostream>
using namespace std;

double cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}

bool onSegment(double x, double y, double x1, double y1, double x2, double y2) {
    return (x >= min(x1, x2) && x <= max(x1, x2) && y >= min(y1, y2) && y <= max(y1, y2));
}

int main() {
    double x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    
    double v1 = cross(x4 - x3, y4 - y3, x1 - x3, y1 - y3);
    double v2 = cross(x4 - x3, y4 - y3, x2 - x3, y2 - y3);
    double v3 = cross(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
    double v4 = cross(x2 - x1, y2 - y1, x4 - x1, y4 - y1);
    
    if ((v1 * v2 < 0) && (v3 * v4 < 0)) {
        cout << "Отрезки пересекаются" << endl;
    } else if (v1 == 0 && onSegment(x1, y1, x3, y3, x4, y4)) {
        cout << "Отрезки пересекаются" << endl;
    } else if (v2 == 0 && onSegment(x2, y2, x3, y3, x4, y4)) {
        cout << "Отрезки пересекаются" << endl;
    } else if (v3 == 0 && onSegment(x3, y3, x1, y1, x2, y2)) {
        cout << "Отрезки пересекаются" << endl;
    } else if (v4 == 0 && onSegment(x4, y4, x1, y1, x2, y2)) {
        cout << "Отрезки пересекаются" << endl;
    } else {
        cout << "Отрезки не пересекаются" << endl;
    }
    
    return 0;
}   
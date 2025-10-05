#include <iostream>
using namespace std;

int main() {
    double arr[15];
    
    for (int i = 0; i < 15; i++) {
        cin >> arr[i];
    }
    
    double max_val = arr[0];
    double min_val = arr[0];
    int max_index = 0;
    int min_index = 0;
    
    for (int i = 1; i < 15; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_index = i;
        }
        if (arr[i] < min_val) {
            min_val = arr[i];
            min_index = i;
        }
    }
    
    if (min_index == 1 && max_index == 0) {
        for (int i = 0; i < 15; i++) {
            arr[i] /= 2.0;
        }
    }
    
    for (int i = 0; i < 15; i++) {
        cout << arr[i] << " ";
    }
    
    return 0;
}
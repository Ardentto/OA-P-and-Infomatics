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
    int min_cnt = 0;
    
    for (int i = 1; i < 15; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_index = i;
        }
        if (arr[i] < min_val) {
            min_val = arr[i];
            min_cnt = i;
        }
    }
    
    if (max_index < min_cnt) {
        double product = max_val * min_val;
        cout << product << endl;
    }
    
    return 0;
}
#include <iostream>
using namespace std;

int main() {
    int arr[10];
    
    for (int i = 0; i < 10; i++) {
        cin >> arr[i];
    }
    
    int min_val = arr[0];
    int max_val = arr[0];
    int min_index = 0;
    int max_index = 0;
    
    for (int i = 1; i < 10; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            min_index = i;
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_index = i;
        }
    }
    
    if (min_index == 4 && max_index == 9) {
        double average = (min_val + max_val) / 2.0;
        cout << average;
    }
    
    return 0;
}
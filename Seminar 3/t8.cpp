#include <iostream>
using namespace std;

int main() {
    int arr[10];
    
    for (int i = 0; i < 10; i++) {
        cin >> arr[i];
    }
    
    int max_val = arr[0];
    int min_val = arr[0];
    int max_index = 0;
    int min_index = 0;
    
    for (int i = 1; i < 10; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_index = i;
        }
        if (arr[i] < min_val) {
            min_val = arr[i];
            min_index = i;
        }
    }
    
    if (max_index == 1 && min_index == 4) {
        for (int i = min_index; i < 10; i++) {
            arr[i] = max_val;
        }
    }
    
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    
    return 0;
}
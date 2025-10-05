#include <iostream>

using namespace std;

int main(){
    int arr[15];

    int min_ind = 0;
    for (int i = 0; i < 15; i++){
        cin >> arr[i];
    }
    int max_val = arr[0];
    int min_val = arr[0];

    for (int i = 1; i < 15; i++){
        if (arr[i] > max_val){
            max_val = arr[i];
        }
        if (arr[i] < min_val){
            min_val = arr[i];
            min_ind = i;
        }
    }

    if (min_val == 0 || max_val == 0){
        for (int i = min_ind; i >= 0; i--){
            arr[i] = 0;
        }

    }

    for(int i = 0; i < 15; i++){
        cout << arr[i] << " ";
    }

}
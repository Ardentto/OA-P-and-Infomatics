#include <iostream>

using namespace std;

int main(){
    int arr[6];

    for(int i = 0; i < 6; i++){
        cin >> arr[i];
    }
    int square = 0.5*abs(arr[0]*(arr[3]-arr[5]) + arr[2]*(arr[5] - arr[1]) + arr[4]*(arr[1] - arr[3]));

    cout << square;

    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    int cnt = 0;
    cin >> n;
    int posled[n];
    for (int i = 0; i < n; i++){
        cin >> posled[i];
        
        if (posled[i] > pow(2, i)){
            cnt++;
        }
    }
    cout << cnt;
    return 0;

}
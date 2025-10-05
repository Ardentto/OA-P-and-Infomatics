#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    int cnt = 0;
    int maxx = 0;
    int A[n];
    for (int i = 0; i < n; i++){
        cin >> A[i];
        if (A[i] > maxx && A[i] % 2 != 0){
            maxx = A[i];
        }
        if (A[i] % 2 == 0){
            cnt ++;
        }

    }
    cout << maxx << endl;
    cout << cnt;
    return 0;
}
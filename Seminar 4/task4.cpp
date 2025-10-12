#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> m(n, vector<int>(n));
    int top = 0, bottom = n-1, left = 0, right = n-1;
    int num = 1;
    
    while (num <= n*n) {
        for (int j = left; j <= right; j++) m[top][j] = num++;
        top++;
        for (int i = top; i <= bottom; i++) m[i][right] = num++;
        right--;
        for (int j = right; j >= left; j--) m[bottom][j] = num++;
        bottom--;
        for (int i = bottom; i >= top; i--) m[i][left] = num++;
        left++;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
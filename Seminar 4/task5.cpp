#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mat[i][j];

    int top = 0, bottom = n - 1, left = 0, right = m - 1;
    
    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++)
            cout << mat[top][j] << " ";
        top++;
        
        for (int i = top; i <= bottom; i++)
            cout << mat[i][right] << " ";
        right--;
        
        if (top <= bottom) {
            for (int j = right; j >= left; j--)
                cout << mat[bottom][j] << " ";
            bottom--;
        }
        
        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                cout << mat[i][left] << " ";
            left++;
        }
    }
    
    return 0;
}
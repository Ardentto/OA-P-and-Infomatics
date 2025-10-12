#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> m(n, vector<int>(n));
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> m[i][j];
    
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += m[i][i];
    
    int t = 0;
    for (int i = 0; i < n; i++)
        t += m[i][n-1-i];
    if (t != sum) {
        cout << "NO" << endl;
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        t = 0;
        for (int j = 0; j < n; j++)
            t += m[i][j];
        if (t != sum) {
            cout << "NO" << endl;
            return 0;
        }
    }
    
    for (int j = 0; j < n; j++) {
        t = 0;
        for (int i = 0; i < n; i++)
            t += m[i][j];
        if (t != sum) {
            cout << "NO" << endl;
            return 0;
        }
    }
    
    cout << "YES" << endl << sum << endl;
    return 0;
}
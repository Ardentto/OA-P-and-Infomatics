#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(m));
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mat[i][j];
    
    vector<int> min_row(n, INT_MAX);
    vector<int> max_row(n, INT_MIN);
    vector<int> min_col(m, INT_MAX);
    vector<int> max_col(m, INT_MIN);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            min_row[i] = min(min_row[i], mat[i][j]);
            max_row[i] = max(max_row[i], mat[i][j]);
        }
    }
    
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            min_col[j] = min(min_col[j], mat[i][j]);
            max_col[j] = max(max_col[j], mat[i][j]);
        }
    }
    
    bool found = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == min_row[i] && mat[i][j] == max_col[j]) {
                cout << "A " << mat[i][j] << " " << i+1 << " " << j+1 << endl;
                found = true;
            }
            if (mat[i][j] == max_row[i] && mat[i][j] == min_col[j]) {
                cout << "B " << mat[i][j] << " " << i+1 << " " << j+1 << endl;
                found = true;
            }
        }
    }
    
    if (!found) cout << "NONE" << endl;
    return 0;
}
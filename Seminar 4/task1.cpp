#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> transpose(const vector<vector<int>>& mat) {
    int n = mat.size();
    vector<vector<int>> res(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[j][i] = mat[i][j];
        }
    }
    return res;
}

vector<vector<int>> antiTranspose(const vector<vector<int>>& mat) {
    int n = mat.size();
    vector<vector<int>> res(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[n-1-j][n-1-i] = mat[i][j];
        }
    }
    return res;
}

vector<vector<int>> flipVertical(const vector<vector<int>>& mat) {
    int n = mat.size();
    vector<vector<int>> res(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][n-1-j] = mat[i][j];
        }
    }
    return res;
}

vector<vector<int>> flipHorizontal(const vector<vector<int>>& mat) {
    int n = mat.size();
    vector<vector<int>> res(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[n-1-i][j] = mat[i][j];
        }
    }
    return res;
}

bool areEqual(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

void printMatrix(const vector<vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> original(n, vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> original[i][j];
        }
    }
    
    vector<vector<int>> mainDiag = transpose(original);
    vector<vector<int>> antiDiag = antiTranspose(original);
    vector<vector<int>> vertical = flipVertical(original);
    vector<vector<int>> horizontal = flipHorizontal(original);
    
    printMatrix(mainDiag);
    printMatrix(antiDiag);
    printMatrix(vertical);
    printMatrix(horizontal);
    
    vector<pair<int, int>> matches;
    
    if (areEqual(mainDiag, antiDiag)) matches.push_back({1, 2});
    if (areEqual(mainDiag, vertical)) matches.push_back({1, 3});
    if (areEqual(mainDiag, horizontal)) matches.push_back({1, 4});
    if (areEqual(antiDiag, vertical)) matches.push_back({2, 3});
    if (areEqual(antiDiag, horizontal)) matches.push_back({2, 4});
    if (areEqual(vertical, horizontal)) matches.push_back({3, 4});
    
    if (matches.empty()) {
        cout << "NONE" << endl;
    } else {
        for (auto& p : matches) {
            cout << "(" << p.first << ", " << p.second << ")" << endl;
        }
    }
    
    return 0;
}
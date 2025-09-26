#include <iostream>
using namespace std;

int main() {
    for (int i = 32; i <= 126; i++) {
        cout << "Код: " << i << " -> Символ: '" << char(i) << "'" << endl;
    }
    
    return 0;
}
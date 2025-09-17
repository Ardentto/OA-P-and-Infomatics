#include <iostream>
#include <string>
using namespace std;
//
int main(){
    double spd;
    cin >> spd;
    if(spd < 60){
        cout << "Скорость в пределах нормы";
    }else if (spd >= 60 and spd <= 80){
        cout << "Вы приближаетесь к превышению скорости";
    }else if (spd > 80){
        cout << "Превышение скорости!";
    }
}
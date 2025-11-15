#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Dish {
    string name;
    string type;
    double price;
};

class MenuManager {
private:
    vector<string> types = {"Закуски", "Основные блюда", "Десерты", "Напитки", "Для детей"};
    string menuFile = "menu.txt";
    
    vector<Dish> loadDishes() {
        vector<Dish> dishes;
        ifstream file(menuFile);
        if (!file) return dishes;
        
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            if (pos1 != string::npos && pos2 != string::npos) {
                Dish dish;
                dish.name = line.substr(0, pos1);
                dish.type = line.substr(pos1 + 1, pos2 - pos1 - 1);
                dish.price = stod(line.substr(pos2 + 1));
                dishes.push_back(dish);
            }
        }
        return dishes;
    }
    
    void saveDishes(const vector<Dish>& dishes) {
        ofstream file(menuFile);
        for (const auto& dish : dishes) {
            file << dish.name << "," << dish.type << "," << dish.price << "\n";
        }
    }
    
    void showMenu() {
        cout << "\n=== Меню ресторана ===" << endl;
        cout << "1. Создать новое меню" << endl;
        cout << "2. Добавить блюдо" << endl;
        cout << "3. Найти блюдо" << endl;
        cout << "4. Сортировать блюда" << endl;
        cout << "5. Блюда по цене" << endl;
        cout << "6. Выйти" << endl;
        cout << "Выберите действие: ";
    }
    
    void showTypes() {
        cout << "Типы блюд: ";
        for (int i = 0; i < types.size(); i++) {
            cout << i + 1 << "." << types[i] << " ";
        }
        cout << endl;
    }
    
    Dish createDish() {
        Dish dish;
        
        cout << "Название блюда: ";
        getline(cin, dish.name);
        
        showTypes();
        cout << "Выберите тип: ";
        int typeChoice;
        cin >> typeChoice;
        cin.ignore();
        dish.type = types[typeChoice - 1];
        
        cout << "Цена: ";
        cin >> dish.price;
        cin.ignore();
        
        return dish;
    }

public:
    void createNewMenu() {
        ofstream file(menuFile);
        cout << "Создаем новое меню..." << endl;
        
        while (true) {
            Dish dish = createDish();
            addDish(dish);
            cout << "Блюдо добавлено! Добавить еще? (y/n): ";
            
            string answer;
            getline(cin, answer);
            if (answer != "y") break;
        }
    }
    
    void addDish(const Dish& dish) {
        ofstream file(menuFile, ios::app);
        file << dish.name << "," << dish.type << "," << dish.price << "\n";
        cout << "Блюдо '" << dish.name << "' добавлено!" << endl;
    }
    
    void findDish() {
        cout << "Введите название блюда: ";
        string name;
        getline(cin, name);
        
        vector<Dish> dishes = loadDishes();
        bool found = false;
        
        for (const auto& dish : dishes) {
            if (dish.name == name) {
                cout << "Найдено: " << dish.name << " | " 
                     << dish.type << " | " << dish.price << " руб." << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Блюдо не найдено!" << endl;
        }
    }
    
    void sortMenu() {
        cout << "Сортировать по: 1-типу, 2-цене: ";
        int choice;
        cin >> choice;
        cin.ignore();
        
        vector<Dish> dishes = loadDishes();
        
        if (choice == 1) {
            sort(dishes.begin(), dishes.end(), 
                [](const Dish& a, const Dish& b) { return a.type < b.type; });
            cout << "Отсортировано по типу!" << endl;
        } else {
            sort(dishes.begin(), dishes.end(), 
                [](const Dish& a, const Dish& b) { return a.price < b.price; });
            cout << "Отсортировано по цене!" << endl;
        }
        
        saveDishes(dishes);
    }
    
    void showByPrice() {
        cout << "Максимальная цена: ";
        double maxPrice;
        cin >> maxPrice;
        cin.ignore();
        
        vector<Dish> dishes = loadDishes();
        bool found = false;
        
        cout << "Блюда до " << maxPrice << " руб.:" << endl;
        for (const auto& dish : dishes) {
            if (dish.price <= maxPrice) {
                cout << "- " << dish.name << " | " << dish.type 
                     << " | " << dish.price << " руб." << endl;
                found = true;
            }
        }
        
        if (!found) {
            cout << "Блюд не найдено!" << endl;
        }
    }
    
    void showAllDishes() {
        vector<Dish> dishes = loadDishes();
        
        if (dishes.empty()) {
            cout << "Меню пустое!" << endl;
            return;
        }
        
        cout << "\n=== Все блюда ===" << endl;
        for (const auto& dish : dishes) {
            cout << "- " << dish.name << " | " << dish.type 
                 << " | " << dish.price << " руб." << endl;
        }
    }
    
    void run() {
        cout << "Добро пожаловать в систему управления меню!" << endl;
        
        while (true) {
            showMenu();
            int choice;
            cin >> choice;
            cin.ignore();
            
            switch (choice) {
                case 1: createNewMenu(); break;
                case 2: {
                    Dish dish = createDish();
                    addDish(dish);
                    break;
                }
                case 3: findDish(); break;
                case 4: sortMenu(); break;
                case 5: showByPrice(); break;
                case 6: 
                    cout << "Выход из программы..." << endl;
                    return;
                default:
                    cout << "Неверный выбор!" << endl;
            }
            
            showAllDishes();
        }
    }
};

int main() {
    MenuManager manager;
    manager.run();
    return 0;
}

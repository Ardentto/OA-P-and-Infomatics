#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

class MenuManager {
private:
    std::vector<std::string> types = {"Закуски", "Основные блюда", "Десерты", "Напитки", "Для детей"};
    std::string menuFile = "menu.txt";
    std::string outputFile = "output.txt";
    
    struct Dish {
        std::string name;
        std::string type;
        double price;
    };

    std::vector<Dish> loadDishes() {
        std::vector<Dish> dishes;
        std::ifstream in(menuFile);
        if (!in) return dishes;
        
        std::string line;
        while (std::getline(in, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                dishes.push_back({
                    line.substr(0, pos1),
                    line.substr(pos1 + 1, pos2 - pos1 - 1),
                    std::stod(line.substr(pos2 + 1))
                });
            }
        }
        return dishes;
    }

    void saveDishes(const std::vector<Dish>& dishes) {
        std::ofstream out(menuFile);
        for (const auto& dish : dishes) {
            out << dish.name << "," << dish.type << "," << dish.price << "\n";
        }
    }

    void logOperation(const std::string& operation, const std::string& result) {
        std::ofstream out(outputFile, std::ios::app);
        out << "=== " << operation << " ===\n" << result << "\n\n";
    }

public:
    void createMenu() {
        std::ofstream(menuFile).close();
        std::ofstream(outputFile).close();
        
        while (true) {
            std::string name;
            std::cout << "Название: ";
            std::getline(std::cin, name);
            if (name.empty()) break;

            std::cout << "Тип (1-5): ";
            for (size_t i = 0; i < types.size(); ++i) {
                std::cout << i + 1 << "." << types[i] << " ";
            }
            std::cout << "\n";
            
            int typeIdx;
            std::cin >> typeIdx;
            std::cin.ignore();
            
            double price;
            std::cout << "Цена: ";
            std::cin >> price;
            std::cin.ignore();

            addDish({name, types[typeIdx - 1], price});
            std::cout << "Добавлено!\n";
        }
    }

    void addDish(const Dish& dish) {
        std::ofstream file(menuFile, std::ios::app);
        file << dish.name << "," << dish.type << "," << dish.price << "\n";
        logOperation("Добавление", dish.name + "," + dish.type + "," + std::to_string(dish.price));
    }

    void searchDish() {
        std::string target;
        std::cout << "Название: ";
        std::getline(std::cin, target);
        
        auto dishes = loadDishes();
        std::string result = "Не найдено";
        
        for (const auto& dish : dishes) {
            if (dish.name == target) {
                result = dish.name + " | " + dish.type + " | " + std::to_string(dish.price);
                break;
            }
        }
        
        std::cout << result << "\n";
        logOperation("Поиск", result);
    }

    void sortDishes() {
        std::cout << "1.Тип 2.Цена: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        auto dishes = loadDishes();
        
        if (choice == 1) {
            std::sort(dishes.begin(), dishes.end(), 
                [](const Dish& a, const Dish& b) { return a.type < b.type; });
            logOperation("Сортировка", "По типу");
        } else {
            std::sort(dishes.begin(), dishes.end(), 
                [](const Dish& a, const Dish& b) { return a.price < b.price; });
            logOperation("Сортировка", "По цене");
        }
        
        saveDishes(dishes);
    }

    void filterByPrice() {
        double maxPrice;
        std::cout << "Макс.цена: ";
        std::cin >> maxPrice;
        std::cin.ignore();
        
        auto dishes = loadDishes();
        std::string result;
        
        for (const auto& dish : dishes) {
            if (dish.price <= maxPrice) {
                result += dish.name + " | " + dish.type + " | " + std::to_string(dish.price) + "\n";
            }
        }
        
        std::cout << (result.empty() ? "Нет результатов\n" : result);
        logOperation("Фильтр по цене", result.empty() ? "Нет результатов" : result);
    }

    void run() {
        while (true) {
            std::cout << "\n1.Создать 2.Добавить 3.Найти 4.Сортировать 5.Фильтр 6.Выход\nВыбор: ";
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: createMenu(); break;
                case 2: {
                    Dish d;
                    std::cout << "Название: ";
                    std::getline(std::cin, d.name);
                    std::cout << "Тип (1-5): ";
                    int t;
                    std::cin >> t;
                    std::cin.ignore();
                    d.type = types[t-1];
                    std::cout << "Цена: ";
                    std::cin >> d.price;
                    std::cin.ignore();
                    addDish(d);
                    break;
                }
                case 3: searchDish(); break;
                case 4: sortDishes(); break;
                case 5: filterByPrice(); break;
                case 6: return;
            }
        }
    }
};

int main() {
    MenuManager manager;
    manager.run();
    return 0;
}
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <pqxx/pqxx>
#include <chrono>
#include <sstream>
#include <typeinfo>
#include <algorithm>

// ================================
// Класс для логгирования
// ================================
class Logger {
private:
    std::ofstream logFile;
    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        char timeStr[20];
        std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
        return std::string(timeStr);
    }

public:
    Logger(const std::string& filename = "log.txt") {
        logFile.open(filename, std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Не удалось открыть файл лога!" << std::endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(const std::string& message, const std::string& type = "INFO") {
        if (logFile.is_open()) {
            logFile << "[" << getCurrentTime() << "] [" << type << "] " << message << std::endl;
        }
        // Также выводим в консоль
        std::cout << message << std::endl;
    }

    void error(const std::string& message) {
        log("ОШИБКА: " + message, "ERROR");
    }

    void success(const std::string& message) {
        log("УСПЕХ: " + message, "SUCCESS");
    }
};

// ================================
// Шаблонный класс Pair
// ================================
template<typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    Pair(T1 f, T2 s) : first(f), second(s) {}

    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }

    void setFirst(T1 f) { first = f; }
    void setSecond(T2 s) { second = s; }

    void display() const {
        std::cout << first << ": " << second << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pair<T1, T2>& pair) {
        os << pair.first << ": " << pair.second;
        return os;
    }
};

// ================================
// Базовый класс для работы с БД
// ================================
class DatabaseEntity {
protected:
    static std::shared_ptr<pqxx::connection> conn;
    static Logger logger;

    static void initializeConnection() {
        if (!conn) {
            try {
                conn = std::make_shared<pqxx::connection>(
                    "host=localhost "
                    "port=5432 "
                    "dbname=restaurant_db "
                    "user=postgres "
                    "password=1830"
                );

                if (conn->is_open()) {
                    logger.success("Подключение к базе данных установлено");
                } else {
                    logger.error("Не удалось подключиться к базе данных");
                }
            } catch (const std::exception& e) {
                logger.error("Ошибка подключения: " + std::string(e.what()));
                throw;
            }
        }
    }

public:
    DatabaseEntity() {
        initializeConnection();
    }

    static bool isConnected() {
        return conn && conn->is_open();
    }
};

// Инициализация статических членов
std::shared_ptr<pqxx::connection> DatabaseEntity::conn = nullptr;
Logger DatabaseEntity::logger;

// ================================
// Класс Category
// ================================
class Category : public DatabaseEntity {
private:
    int id;
    std::string name;

public:
    Category() : id(0) {}
    Category(const std::string& name) : id(0), name(name) {}
    Category(int id, const std::string& name) : id(id), name(name) {}

    // Добавление категории
    bool addToDatabase() {
        try {
            pqxx::work txn(*conn);
            txn.exec_params(
                "INSERT INTO categories (category_name) VALUES ($1)",
                name
            );
            txn.commit();
            logger.success("Добавлена категория: " + name);
            return true;
        } catch (const std::exception& e) {
            logger.error("Ошибка при добавлении категории: " + std::string(e.what()));
            return false;
        }
    }

    // Получение всех категорий
    static std::vector<Category> getAll() {
        std::vector<Category> categories;
        try {
            pqxx::work txn(*conn);
            pqxx::result res = txn.exec("SELECT * FROM categories ORDER BY id");

            for (const auto& row : res) {
                categories.emplace_back(
                    row["id"].as<int>(),
                    row["category_name"].c_str()
                );
            }
            logger.success("Загружены все категории");
        } catch (const std::exception& e) {
            logger.error("Ошибка при загрузке категорий: " + std::string(e.what()));
        }
        return categories;
    }

    // Геттеры
    int getId() const { return id; }
    std::string getName() const { return name; }

    void display() const {
        std::cout << "ID: " << id << ", Название: " << name << std::endl;
    }
};

// ================================
// Базовый класс Dish и производные
// ================================
class Dish : public DatabaseEntity {
protected:
    int id;
    std::string name;
    int categoryId;
    double price;

public:
    Dish() : id(0), categoryId(0), price(0.0) {}
    Dish(const std::string& name, int categoryId, double price)
        : id(0), name(name), categoryId(categoryId), price(price) {}

    virtual ~Dish() {}

    // Виртуальный метод для отображения информации
    virtual void display() const {
        std::cout << "ID: " << id << ", Название: " << name
                  << ", Категория ID: " << categoryId
                  << ", Цена: " << price << " руб." << std::endl;
    }

    // Добавление блюда
    virtual bool addToDatabase() {
        try {
            pqxx::work txn(*conn);
            txn.exec_params(
                "INSERT INTO dishes (name, category_id, price) VALUES ($1, $2, $3)",
                name, categoryId, price
            );
            txn.commit();
            logger.success("Добавлено блюдо: " + name);
            return true;
        } catch (const std::exception& e) {
            logger.error("Ошибка при добавлении блюда: " + std::string(e.what()));
            return false;
        }
    }

    // Геттеры
    int getId() const { return id; }
    std::string getName() const { return name; }
    int getCategoryId() const { return categoryId; }
    double getPrice() const { return price; }

    // Сеттеры
    void setId(int id) { this->id = id; }
    void setName(const std::string& name) { this->name = name; }
    void setCategoryId(int categoryId) { this->categoryId = categoryId; }
    void setPrice(double price) { this->price = price; }
};

// Основные блюда
class MainCourse : public Dish {
private:
    std::string cookingTime;

public:
    MainCourse() : Dish(), cookingTime("") {}
    MainCourse(const std::string& name, int categoryId, double price, const std::string& cookingTime)
        : Dish(name, categoryId, price), cookingTime(cookingTime) {}

    void display() const override {
        Dish::display();
        std::cout << "  Время приготовления: " << cookingTime << " мин." << std::endl;
    }

    std::string getCookingTime() const { return cookingTime; }
    void setCookingTime(const std::string& time) { cookingTime = time; }
};

// Десерты
class Dessert : public Dish {
private:
    bool containsSugar;

public:
    Dessert() : Dish(), containsSugar(true) {}
    Dessert(const std::string& name, int categoryId, double price, bool containsSugar)
        : Dish(name, categoryId, price), containsSugar(containsSugar) {}

    void display() const override {
        Dish::display();
        std::cout << "  Содержит сахар: " << (containsSugar ? "Да" : "Нет") << std::endl;
    }

    bool getContainsSugar() const { return containsSugar; }
    void setContainsSugar(bool sugar) { containsSugar = sugar; }
};

// ================================
// Класс Order
// ================================
class Order : public DatabaseEntity {
private:
    int orderId;
    int dishId;
    std::string orderDate;
    int quantity;
    double totalPrice;

public:
    Order() : orderId(0), dishId(0), quantity(0), totalPrice(0.0) {}
    Order(int dishId, int quantity, const std::string& date = "")
        : orderId(0), dishId(dishId), quantity(quantity), totalPrice(0.0) {
        if (date.empty()) {
            // Текущая дата
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            char buffer[20];
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&time));
            orderDate = buffer;
        } else {
            orderDate = date;
        }
    }

    // Добавление заказа с расчетом общей цены
    bool addToDatabase() {
        try {
            // Получаем цену блюда
            double dishPrice = 0.0;
            {
                pqxx::work txn(*conn);
                pqxx::result res = txn.exec_params(
                    "SELECT price FROM dishes WHERE id = $1",
                    dishId
                );
                if (!res.empty()) {
                    dishPrice = res[0]["price"].as<double>();
                }
                txn.commit();
            }

            if (dishPrice == 0.0) {
                logger.error("Блюдо с ID " + std::to_string(dishId) + " не найдено");
                return false;
            }

            totalPrice = dishPrice * quantity;

            // Добавляем заказ
            pqxx::work txn(*conn);
            txn.exec_params(
                "INSERT INTO orders (dish_id, order_date, quantity, total_price) "
                "VALUES ($1, $2, $3, $4)",
                dishId, orderDate, quantity, totalPrice
            );
            txn.commit();

            logger.success("Добавлен заказ для блюда ID: " + std::to_string(dishId));
            return true;
        } catch (const std::exception& e) {
            logger.error("Ошибка при добавлении заказа: " + std::string(e.what()));
            return false;
        }
    }

    // Получение всех заказов
    static std::vector<Order> getAll() {
        std::vector<Order> orders;
        try {
            pqxx::work txn(*conn);
            pqxx::result res = txn.exec(
                "SELECT * FROM orders ORDER BY order_date DESC"
            );

            for (const auto& row : res) {
                Order order;
                order.orderId = row["order_id"].as<int>();
                order.dishId = row["dish_id"].as<int>();
                order.orderDate = row["order_date"].as<std::string>();
                order.quantity = row["quantity"].as<int>();
                order.totalPrice = row["total_price"].as<double>();
                orders.push_back(order);
            }
            logger.success("Загружены все заказы");
        } catch (const std::exception& e) {
            logger.error("Ошибка при загрузке заказов: " + std::string(e.what()));
        }
        return orders;
    }

    // Геттеры
    int getOrderId() const { return orderId; }
    int getDishId() const { return dishId; }
    std::string getOrderDate() const { return orderDate; }
    int getQuantity() const { return quantity; }
    double getTotalPrice() const { return totalPrice; }

    void display() const {
        std::cout << "Заказ ID: " << orderId
                  << ", Блюдо ID: " << dishId
                  << ", Дата: " << orderDate
                  << ", Количество: " << quantity
                  << ", Итого: " << totalPrice << " руб." << std::endl;
    }
};

// ================================
// Класс для аналитических запросов
// ================================
class Analytics : public DatabaseEntity {
public:
    // Общая выручка по категориям
    static void getRevenueByCategory() {
        try {
            pqxx::work txn(*conn);
            pqxx::result res = txn.exec(
                "SELECT c.category_name, SUM(o.total_price) as total_revenue "
                "FROM orders o "
                "JOIN dishes d ON o.dish_id = d.id "
                "JOIN categories c ON d.category_id = c.id "
                "GROUP BY c.category_name "
                "ORDER BY total_revenue DESC"
            );

            std::cout << "\n=== Выручка по категориям ===" << std::endl;
            std::cout << std::setw(20) << std::left << "Категория"
                      << std::setw(15) << std::right << "Выручка" << std::endl;
            std::cout << std::string(40, '-') << std::endl;

            double totalAll = 0.0;
            for (const auto& row : res) {
                double revenue = row["total_revenue"].as<double>();
                totalAll += revenue;
                std::cout << std::setw(20) << std::left << row["category_name"].c_str()
                          << std::setw(15) << std::right << std::fixed << std::setprecision(2)
                          << revenue << std::endl;
            }
            std::cout << std::string(40, '-') << std::endl;
            std::cout << std::setw(20) << std::left << "Всего"
                      << std::setw(15) << std::right << totalAll << std::endl;

            logger.success("Выполнен запрос: Выручка по категориям");
        } catch (const std::exception& e) {
            logger.error("Ошибка при запросе выручки: " + std::string(e.what()));
        }
    }

    // Топ-3 самых продаваемых блюд
    static void getTopSellingDishes() {
        try {
            pqxx::work txn(*conn);
            pqxx::result res = txn.exec(
                "SELECT d.name, SUM(o.quantity) as total_quantity, "
                "SUM(o.total_price) as total_revenue "
                "FROM orders o "
                "JOIN dishes d ON o.dish_id = d.id "
                "GROUP BY d.name "
                "ORDER BY total_quantity DESC "
                "LIMIT 3"
            );

            std::cout << "\n=== Топ-3 самых продаваемых блюд ===" << std::endl;
            std::cout << std::setw(25) << std::left << "Блюдо"
                      << std::setw(15) << std::right << "Кол-во"
                      << std::setw(15) << std::right << "Выручка" << std::endl;
            std::cout << std::string(60, '-') << std::endl;

            for (const auto& row : res) {
                std::cout << std::setw(25) << std::left << row["name"].c_str()
                          << std::setw(15) << std::right << row["total_quantity"].as<int>()
                          << std::setw(15) << std::right << std::fixed << std::setprecision(2)
                          << row["total_revenue"].as<double>() << std::endl;
            }

            logger.success("Выполнен запрос: Топ-3 самых продаваемых блюд");
        } catch (const std::exception& e) {
            logger.error("Ошибка при запросе топ-3 блюд: " + std::string(e.what()));
        }
    }

    // Средняя стоимость заказа
    static void getAverageOrderValue() {
        try {
            pqxx::work txn(*conn);
            pqxx::result res = txn.exec(
                "SELECT AVG(total_price) as avg_order_value, "
                "COUNT(*) as total_orders FROM orders"
            );

            std::cout << "\n=== Средняя стоимость заказа ===" << std::endl;
            if (!res.empty()) {
                double avg = res[0]["avg_order_value"].as<double>();
                int count = res[0]["total_orders"].as<int>();
                std::cout << "Всего заказов: " << count << std::endl;
                std::cout << "Средний чек: " << std::fixed << std::setprecision(2)
                          << avg << " руб." << std::endl;
            } else {
                std::cout << "Нет данных о заказах" << std::endl;
            }

            logger.success("Выполнен запрос: Средняя стоимость заказа");
        } catch (const std::exception& e) {
            logger.error("Ошибка при запросе средней стоимости: " + std::string(e.what()));
        }
    }

    // Количество заказов по каждому блюду
    static void getOrderCountPerDish() {
        try {
            pqxx::work txn(*conn);
            pqxx::result res = txn.exec(
                "SELECT d.name, COUNT(o.order_id) as order_count, "
                "SUM(o.quantity) as total_quantity "
                "FROM dishes d "
                "LEFT JOIN orders o ON d.id = o.dish_id "
                "GROUP BY d.name "
                "ORDER BY order_count DESC"
            );

            std::cout << "\n=== Количество заказов по каждому блюду ===" << std::endl;
            std::cout << std::setw(25) << std::left << "Блюдо"
                      << std::setw(15) << std::right << "Заказов"
                      << std::setw(15) << std::right << "Порций" << std::endl;
            std::cout << std::string(60, '-') << std::endl;

            for (const auto& row : res) {
                std::cout << std::setw(25) << std::left << row["name"].c_str()
                          << std::setw(15) << std::right << row["order_count"].as<int>()
                          << std::setw(15) << std::right << row["total_quantity"].as<int>()
                          << std::endl;
            }

            logger.success("Выполнен запрос: Количество заказов по каждому блюду");
        } catch (const std::exception& e) {
            logger.error("Ошибка при запросе количества заказов: " + std::string(e.what()));
        }
    }
};

// ================================
// Класс для работы с меню
// ================================
class MenuManager {
private:
    Logger logger;

public:
    MenuManager() : logger() {}

    void displayMainMenu() {
        std::cout << "\n==========================================" << std::endl;
        std::cout << "     СИСТЕМА УЧЕТА РЕСТОРАНА" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "1. Добавить категорию" << std::endl;
        std::cout << "2. Добавить блюдо" << std::endl;
        std::cout << "3. Добавить заказ" << std::endl;
        std::cout << "4. Просмотреть все категории" << std::endl;
        std::cout << "5. Просмотреть все блюда" << std::endl;
        std::cout << "6. Просмотреть все заказы" << std::endl;
        std::cout << "7. Аналитические запросы" << std::endl;
        std::cout << "8. Пример работы шаблонного класса Pair" << std::endl;
        std::cout << "9. Пример полиморфизма блюд" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "Выберите действие: ";
    }

    void displayAnalyticsMenu() {
        std::cout << "\n=== Аналитические запросы ===" << std::endl;
        std::cout << "1. Выручка по категориям" << std::endl;
        std::cout << "2. Топ-3 самых продаваемых блюд" << std::endl;
        std::cout << "3. Средняя стоимость заказа" << std::endl;
        std::cout << "4. Количество заказов по каждому блюду" << std::endl;
        std::cout << "5. Назад в главное меню" << std::endl;
        std::cout << "Выберите запрос: ";
    }

    void handleAddCategory() {
        std::string name;
        std::cout << "Введите название категории: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        if (!name.empty()) {
            Category category(name);
            category.addToDatabase();
        } else {
            logger.error("Название категории не может быть пустым!");
        }
    }

    void handleAddDish() {
        std::cout << "Выберите тип блюда:" << std::endl;
        std::cout << "1. Основное блюдо" << std::endl;
        std::cout << "2. Десерт" << std::endl;
        std::cout << "Выбор: ";

        int dishType;
        std::cin >> dishType;
        std::cin.ignore();

        std::string name;
        int categoryId;
        double price;

        std::cout << "Введите название блюда: ";
        std::getline(std::cin, name);

        // Показываем доступные категории
        auto categories = Category::getAll();
        if (categories.empty()) {
            logger.error("Нет доступных категорий. Сначала добавьте категории.");
            return;
        }

        std::cout << "\nДоступные категории:" << std::endl;
        for (const auto& cat : categories) {
            cat.display();
        }

        std::cout << "Введите ID категории: ";
        std::cin >> categoryId;
        std::cout << "Введите цену блюда: ";
        std::cin >> price;
        std::cin.ignore();

        if (dishType == 1) {
            // Основное блюдо
            std::string cookingTime;
            std::cout << "Введите время приготовления (в минутах): ";
            std::getline(std::cin, cookingTime);

            MainCourse mainCourse(name, categoryId, price, cookingTime);
            mainCourse.addToDatabase();
        } else if (dishType == 2) {
            // Десерт
            char sugarChoice;
            std::cout << "Содержит сахар? (y/n): ";
            std::cin >> sugarChoice;
            std::cin.ignore();

            bool containsSugar = (sugarChoice == 'y' || sugarChoice == 'Y');
            Dessert dessert(name, categoryId, price, containsSugar);
            dessert.addToDatabase();
        } else {
            logger.error("Неверный выбор типа блюда");
        }
    }

    void handleAddOrder() {
        // Показываем доступные блюда
        try {
            pqxx::connection conn(
                "host=localhost "
                "port=5432 "
                "dbname=restaurant_db "
                "user=postgres "
                "password=1830"
            );

            pqxx::work txn(conn);
            pqxx::result dishes = txn.exec(
                "SELECT d.id, d.name, c.category_name, d.price "
                "FROM dishes d "
                "JOIN categories c ON d.category_id = c.id "
                "ORDER BY d.id"
            );

            if (dishes.empty()) {
                logger.error("Нет доступных блюд. Сначала добавьте блюда.");
                return;
            }

            std::cout << "\nДоступные блюда:" << std::endl;
            std::cout << std::setw(5) << "ID"
                      << std::setw(20) << "Название"
                      << std::setw(15) << "Категория"
                      << std::setw(10) << "Цена" << std::endl;
            std::cout << std::string(60, '-') << std::endl;

            for (const auto& row : dishes) {
                std::cout << std::setw(5) << row["id"].as<int>()
                          << std::setw(20) << row["name"].c_str()
                          << std::setw(15) << row["category_name"].c_str()
                          << std::setw(10) << row["price"].as<double>()
                          << std::endl;
            }

            int dishId, quantity;
            std::string date;

            std::cout << "\nВведите ID блюда: ";
            std::cin >> dishId;
            std::cout << "Введите количество: ";
            std::cin >> quantity;
            std::cin.ignore();

            std::cout << "Введите дату заказа (YYYY-MM-DD или оставьте пустым для текущей): ";
            std::getline(std::cin, date);

            if (quantity <= 0) {
                logger.error("Количество должно быть больше 0!");
                return;
            }

            Order order(dishId, quantity, date);
            order.addToDatabase();

        } catch (const std::exception& e) {
            logger.error("Ошибка: " + std::string(e.what()));
        }
    }

    void handleViewCategories() {
        auto categories = Category::getAll();

        if (categories.empty()) {
            std::cout << "Категории не найдены." << std::endl;
            return;
        }

        std::cout << "\n=== Список категорий ===" << std::endl;
        std::cout << std::setw(5) << "ID"
                  << std::setw(20) << "Название" << std::endl;
        std::cout << std::string(30, '-') << std::endl;

        for (const auto& category : categories) {
            std::cout << std::setw(5) << category.getId()
                      << std::setw(20) << category.getName() << std::endl;
        }
    }

    void handleViewDishes() {
        try {
            pqxx::connection conn(
                "host=localhost "
                "port=5432 "
                "dbname=restaurant_db "
                "user=postgres "
                "password=1830"
            );

            pqxx::work txn(conn);
            pqxx::result res = txn.exec(
                "SELECT d.id, d.name, c.category_name, d.price "
                "FROM dishes d "
                "JOIN categories c ON d.category_id = c.id "
                "ORDER BY d.id"
            );

            if (res.empty()) {
                std::cout << "Блюда не найдены." << std::endl;
                return;
            }

            std::cout << "\n=== Список всех блюд ===" << std::endl;
            std::cout << std::setw(5) << "ID"
                      << std::setw(25) << "Название"
                      << std::setw(20) << "Категория"
                      << std::setw(10) << "Цена" << std::endl;
            std::cout << std::string(70, '-') << std::endl;

            for (const auto& row : res) {
                std::cout << std::setw(5) << row["id"].as<int>()
                          << std::setw(25) << row["name"].c_str()
                          << std::setw(20) << row["category_name"].c_str()
                          << std::setw(10) << row["price"].as<double>()
                          << std::endl;
            }

        } catch (const std::exception& e) {
            logger.error("Ошибка: " + std::string(e.what()));
        }
    }

    void handleViewOrders() {
        auto orders = Order::getAll();

        if (orders.empty()) {
            std::cout << "Заказы не найдены." << std::endl;
            return;
        }

        std::cout << "\n=== Список всех заказов ===" << std::endl;
        std::cout << std::setw(10) << "Order ID"
                  << std::setw(10) << "Dish ID"
                  << std::setw(15) << "Дата"
                  << std::setw(10) << "Кол-во"
                  << std::setw(15) << "Сумма" << std::endl;
        std::cout << std::string(70, '-') << std::endl;

        for (const auto& order : orders) {
            std::cout << std::setw(10) << order.getOrderId()
                      << std::setw(10) << order.getDishId()
                      << std::setw(15) << order.getOrderDate()
                      << std::setw(10) << order.getQuantity()
                      << std::setw(15) << std::fixed << std::setprecision(2)
                      << order.getTotalPrice() << std::endl;
        }
    }

    void handleAnalytics() {
        int choice;
        do {
            displayAnalyticsMenu();
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
                case 1:
                    Analytics::getRevenueByCategory();
                    break;
                case 2:
                    Analytics::getTopSellingDishes();
                    break;
                case 3:
                    Analytics::getAverageOrderValue();
                    break;
                case 4:
                    Analytics::getOrderCountPerDish();
                    break;
                case 5:
                    return;
                default:
                    logger.error("Неверный выбор!");
            }
        } while (choice != 5);
    }

    void demonstratePairClass() {
        std::cout << "\n=== Демонстрация шаблонного класса Pair ===" << std::endl;

        // Пример 1: Pair<string, int>
        Pair<std::string, int> dishOrder("Цезарь", 15);
        std::cout << "Блюдо и количество заказов: ";
        dishOrder.display();

        // Пример 2: Pair<string, double>
        Pair<std::string, double> dishRevenue("Стейк", 15000.50);
        std::cout << "Блюдо и выручка: ";
        dishRevenue.display();

        // Пример 3: Вектор Pair объектов
        std::cout << "\nВектор пар:" << std::endl;
        std::vector<Pair<std::string, int>> dishPairs;
        dishPairs.emplace_back("Борщ", 25);
        dishPairs.emplace_back("Тирамису", 18);
        dishPairs.emplace_back("Кофе", 42);

        for (const auto& pair : dishPairs) {
            std::cout << "  ";
            pair.display();
        }
    }

    void demonstratePolymorphism() {
        std::cout << "\n=== Демонстрация полиморфизма блюд ===" << std::endl;

        // Создаем вектор указателей на базовый класс Dish
        std::vector<std::shared_ptr<Dish>> dishes;

        // Добавляем различные типы блюд
        dishes.push_back(std::make_shared<MainCourse>(
            "Стейк рибай", 3, 1800.00, "25"
        ));

        dishes.push_back(std::make_shared<Dessert>(
            "Шоколадный торт", 4, 450.00, true
        ));

        dishes.push_back(std::make_shared<MainCourse>(
            "Лосось на гриле", 3, 1200.00, "20"
        ));

        dishes.push_back(std::make_shared<Dessert>(
            "Фруктовый салат", 4, 300.00, false
        ));

        // Демонстрируем полиморфизм - вызов виртуального метода display()
        std::cout << "Различные типы блюд:" << std::endl;
        for (const auto& dish : dishes) {
            dish->display();
            std::cout << "  Тип: " << typeid(*dish).name() << std::endl;
            std::cout << std::endl;
        }
    }
};

// ================================
// Главная функция
// ================================
int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  ЛАБОРАТОРНАЯ РАБОТА №4, ВАРИАНТ 3" << std::endl;
    std::cout << "  Система учета блюд, их категорий и заказов" << std::endl;
    std::cout << "  С++ и PostgreSQL" << std::endl;
    std::cout << "==========================================" << std::endl;

    // Проверяем подключение к базе данных
    try {
        DatabaseEntity entity; // Это инициализирует подключение
        if (!DatabaseEntity::isConnected()) {
            std::cerr << "Не удалось подключиться к базе данных!" << std::endl;
            std::cerr << "Проверьте:\n";
            std::cerr << "1. Запущен ли PostgreSQL\n";
            std::cerr << "2. Правильность данных подключения\n";
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }

    MenuManager menuManager;
    int choice;

    do {
        menuManager.displayMainMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                menuManager.handleAddCategory();
                break;
            case 2:
                menuManager.handleAddDish();
                break;
            case 3:
                menuManager.handleAddOrder();
                break;
            case 4:
                menuManager.handleViewCategories();
                break;
            case 5:
                menuManager.handleViewDishes();
                break;
            case 6:
                menuManager.handleViewOrders();
                break;
            case 7:
                menuManager.handleAnalytics();
                break;
            case 8:
                menuManager.demonstratePairClass();
                break;
            case 9:
                menuManager.demonstratePolymorphism();
                break;
            case 0:
                std::cout << "\nВыход из программы..." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
        }

    } while (choice != 0);

    std::cout << "\nЛабораторная работа завершена!" << std::endl;
    std::cout << "Все операции записаны в файл log.txt" << std::endl;

    return 0;
}
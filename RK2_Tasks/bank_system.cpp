#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <stdexcept>

// Базовый класс BankAccount
class BankAccount {
protected:
    std::string accountNumber;
    std::string ownerName;
    double balance;

public:
    // Конструктор
    BankAccount(const std::string& accNum, const std::string& name, double initialBalance = 0.0)
        : accountNumber(accNum), ownerName(name), balance(initialBalance) {
        if (initialBalance < 0) {
            throw std::invalid_argument("Начальный баланс не может быть отрицательным");
        }
    }

    // Виртуальный деструктор
    virtual ~BankAccount() {}

    // Метод для пополнения счета
    virtual void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма пополнения должна быть положительной");
        }
        balance += amount;
        std::cout << "✅ На счет " << accountNumber << " зачислено: "
                  << std::fixed << std::setprecision(2) << amount
                  << " руб. Новый баланс: " << balance << " руб." << std::endl;
    }

    // Метод для снятия средств
    virtual bool withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Сумма снятия должна быть положительной");
        }

        if (amount > balance) {
            std::cout << "❌ Недостаточно средств на счете " << accountNumber
                      << ". Запрошено: " << amount << " руб., доступно: "
                      << balance << " руб." << std::endl;
            return false;
        }

        balance -= amount;
        std::cout << "✅ Со счета " << accountNumber << " снято: "
                  << amount << " руб. Остаток: " << balance << " руб." << std::endl;
        return true;
    }

    // Виртуальный метод для отображения информации
    virtual void displayInfo() const {
        std::cout << "\n=== Информация о счете ===" << std::endl;
        std::cout << "Номер счета: " << accountNumber << std::endl;
        std::cout << "Владелец: " << ownerName << std::endl;
        std::cout << "Баланс: " << std::fixed << std::setprecision(2)
                  << balance << " руб." << std::endl;
    }

    // Геттеры
    std::string getAccountNumber() const { return accountNumber; }
    std::string getOwnerName() const { return ownerName; }
    double getBalance() const { return balance; }

    // Сеттеры
    void setOwnerName(const std::string& name) { ownerName = name; }
};

// Производный класс SavingsAccount (сберегательный счет)
class SavingsAccount : public BankAccount {
private:
    double interestRate; // Процентная ставка в процентах
    double accruedInterest; // Начисленные проценты

public:
    // Конструктор
    SavingsAccount(const std::string& accNum, const std::string& name,
                   double initialBalance = 0.0, double rate = 5.0)
        : BankAccount(accNum, name, initialBalance),
          interestRate(rate), accruedInterest(0.0) {
        if (rate < 0) {
            throw std::invalid_argument("Процентная ставка не может быть отрицательной");
        }
    }

    // Метод для начисления процентов
    void accrueInterest() {
        double interest = balance * (interestRate / 100.0);
        accruedInterest += interest;
        balance += interest;

        std::cout << "\n💵 Начисление процентов по сберегательному счету "
                  << accountNumber << ":" << std::endl;
        std::cout << "Ставка: " << interestRate << "%" << std::endl;
        std::cout << "Начислено процентов: " << std::fixed << std::setprecision(2)
                  << interest << " руб." << std::endl;
        std::cout << "Всего начислено процентов: " << accruedInterest << " руб." << std::endl;
        std::cout << "Новый баланс: " << balance << " руб." << std::endl;
    }

    // Переопределенный метод для отображения информации
    void displayInfo() const override {
        BankAccount::displayInfo();
        std::cout << "Тип счета: Сберегательный" << std::endl;
        std::cout << "Процентная ставка: " << interestRate << "%" << std::endl;
        std::cout << "Всего начислено процентов: " << std::fixed << std::setprecision(2)
                  << accruedInterest << " руб." << std::endl;
    }

    // Геттер для процентной ставки
    double getInterestRate() const { return interestRate; }

    // Сеттер для процентной ставки
    void setInterestRate(double rate) {
        if (rate < 0) {
            throw std::invalid_argument("Процентная ставка не может быть отрицательной");
        }
        interestRate = rate;
        std::cout << "Процентная ставка изменена на " << rate << "%" << std::endl;
    }
};

// Дополнительный класс для управления счетами
class Bank {
private:
    std::vector<std::shared_ptr<BankAccount>> accounts;

public:
    // Добавить счет
    void addAccount(const std::shared_ptr<BankAccount>& account) {
        accounts.push_back(account);
        std::cout << "\n✅ Счет добавлен в банковскую систему" << std::endl;
    }

    // Найти счет по номеру
    std::shared_ptr<BankAccount> findAccount(const std::string& accountNumber) {
        for (const auto& account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                return account;
            }
        }
        return nullptr;
    }

    // Показать все счета
    void displayAllAccounts() const {
        std::cout << "\n=== ВСЕ СЧЕТА В БАНКЕ ===" << std::endl;
        std::cout << "Всего счетов: " << accounts.size() << std::endl;

        for (const auto& account : accounts) {
            account->displayInfo();
            std::cout << "----------------------" << std::endl;
        }
    }

    // Начислить проценты по всем сберегательным счетам
    void accrueInterestForAllSavings() {
        std::cout << "\n💰 Начисление процентов по всем сберегательным счетам:" << std::endl;
        int count = 0;

        for (const auto& account : accounts) {
            if (auto savings = std::dynamic_pointer_cast<SavingsAccount>(account)) {
                savings->accrueInterest();
                count++;
            }
        }

        std::cout << "Проценты начислены на " << count << " сберегательных счетов" << std::endl;
    }

    // Общая сумма всех счетов
    double getTotalBankBalance() const {
        double total = 0.0;
        for (const auto& account : accounts) {
            total += account->getBalance();
        }
        return total;
    }
};

// Функция для демонстрации полиморфизма
void demonstratePolymorphism() {
    std::cout << "\n=== Демонстрация полиморфизма ===" << std::endl;

    std::vector<std::shared_ptr<BankAccount>> accounts;

    // Создаем разные типы счетов
    accounts.push_back(std::make_shared<BankAccount>("4070281010001", "Иванов И.И.", 10000.00));
    accounts.push_back(std::make_shared<SavingsAccount>("4081781020002", "Петров П.П.", 50000.00, 7.5));
    accounts.push_back(std::make_shared<BankAccount>("4070281030003", "Сидорова А.В.", 25000.00));
    accounts.push_back(std::make_shared<SavingsAccount>("4081781040004", "Кузнецова М.С.", 100000.00, 6.0));

    // Демонстрируем полиморфизм
    for (const auto& account : accounts) {
        account->displayInfo(); // Вызывается соответствующая реализация
        std::cout << std::endl;
    }
}

// Главная функция
int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "   БАНКОВСКАЯ СИСТЕМА - C++" << std::endl;
    std::cout << "   Лабораторная работа МГТУ им. Баумана" << std::endl;
    std::cout << "==========================================" << std::endl;

    try {
        // Создаем объекты счетов
        std::cout << "\n1. Создание счетов:" << std::endl;

        BankAccount regularAccount("4070281050005", "Александров А.А.", 15000.00);
        SavingsAccount savingsAccount("4081781060006", "Борисова Е.К.", 75000.00, 5.5);

        // Отображаем информацию о счетах
        regularAccount.displayInfo();
        savingsAccount.displayInfo();

        // Операции со счетами
        std::cout << "\n2. Операции со счетами:" << std::endl;

        // Пополнение счета
        regularAccount.deposit(5000.00);
        savingsAccount.deposit(25000.00);

        // Снятие средств
        regularAccount.withdraw(3000.00);
        savingsAccount.withdraw(10000.00);

        // Попытка снять больше, чем есть на счете
        regularAccount.withdraw(50000.00);

        // Начисление процентов на сберегательный счет
        std::cout << "\n3. Начисление процентов:" << std::endl;
        savingsAccount.accrueInterest();

        // Создаем банк и управляем счетами
        std::cout << "\n4. Работа с банковской системой:" << std::endl;

        Bank bank;

        // Добавляем счета в банк
        bank.addAccount(std::make_shared<BankAccount>(regularAccount));
        bank.addAccount(std::make_shared<SavingsAccount>(savingsAccount));

        // Создаем еще несколько счетов
        bank.addAccount(std::make_shared<BankAccount>("4070281070007", "Васильев В.В.", 30000.00));
        bank.addAccount(std::make_shared<SavingsAccount>("4081781080008", "Григорьева О.П.", 120000.00, 8.0));

        // Показываем все счета
        bank.displayAllAccounts();

        // Начисляем проценты по всем сберегательным счетам
        bank.accrueInterestForAllSavings();

        // Показываем общий баланс банка
        std::cout << "\n📊 Общий баланс всех счетов в банке: "
                  << std::fixed << std::setprecision(2)
                  << bank.getTotalBankBalance() << " руб." << std::endl;

        // Демонстрация полиморфизма
        demonstratePolymorphism();

        // Дополнительные операции
        std::cout << "\n5. Дополнительные операции:" << std::endl;

        // Поиск счета
        auto foundAccount = bank.findAccount("4081781060006");
        if (foundAccount) {
            std::cout << "Найден счет: " << foundAccount->getAccountNumber() << std::endl;
            foundAccount->displayInfo();
        }

        // Изменение процентной ставки
        if (auto savings = std::dynamic_pointer_cast<SavingsAccount>(foundAccount)) {
            savings->setInterestRate(6.5);
            savings->accrueInterest();
        }

    } catch (const std::exception& e) {
        std::cerr << "❌ Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\n==========================================" << std::endl;
    std::cout << "   Лабораторная работа выполнена успешно!" << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}
#pragma once
#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <memory>

template<typename T>
class DatabaseConnection {
private:
    std::unique_ptr<pqxx::connection> conn;
    std::unique_ptr<pqxx::work> transaction;
    bool inTransaction = false;

public:
    explicit DatabaseConnection(const T& connectionString) {
        conn = std::make_unique<pqxx::connection>(connectionString);
    }

    std::vector<std::vector<std::string>> executeQuery(const std::string& sql) {
        pqxx::nontransaction ntx(*conn);
        auto result = ntx.exec(sql);

        std::vector<std::vector<std::string>> data;
        for (const auto& row : result) {
            std::vector<std::string> rowData;
            for (const auto& field : row)
                rowData.push_back(field.c_str());
            data.push_back(rowData);
        }
        return data;
    }

    void executeNonQuery(const std::string& sql) {
        if (inTransaction)
            transaction->exec(sql);
        else {
            pqxx::work w(*conn);
            w.exec(sql);
            w.commit();
        }
    }

    void beginTransaction() {
        transaction = std::make_unique<pqxx::work>(*conn);
        inTransaction = true;
    }

    void commitTransaction() {
        if (transaction) {
            transaction->commit();
            transaction.reset();
            inTransaction = false;
        }
    }

    void rollbackTransaction() {
        transaction.reset();
        inTransaction = false;
    }

    bool getTransactionStatus() const {
        return inTransaction;
    }

    void createFunction(const std::string& sql) {
        executeNonQuery(sql);
    }

    void createTrigger(const std::string& sql) {
        executeNonQuery(sql);
    }

    ~DatabaseConnection() {
        if (conn && conn->is_open())
            conn->disconnect();
    }
};

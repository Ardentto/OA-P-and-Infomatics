#pragma once
#include <vector>
#include <memory>
#include "OrderItem.h"
#include "Payment.h"

class Order {
private:
    std::vector<OrderItem> items;
    std::unique_ptr<Payment> payment;
public:
    void addItem(const OrderItem& item) {
        items.push_back(item);
    }
};

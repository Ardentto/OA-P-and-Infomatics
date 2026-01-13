#pragma once
#include <memory>

class User {
protected:
    int userId;
public:
    virtual void createOrder() = 0;
    virtual void viewOrderStatus(int orderId) = 0;
    virtual ~User() = default;
};

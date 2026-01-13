#pragma once
#include "User.h"

class Admin : public User {
public:
    void createOrder() override;
    void viewOrderStatus(int) override;
    void addProduct();
};

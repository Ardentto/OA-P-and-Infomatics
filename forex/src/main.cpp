#include <memory>
#include "Admin.h"

int main() {
    std::shared_ptr<User> admin = std::make_shared<Admin>();
    admin->createOrder();
    return 0;
}

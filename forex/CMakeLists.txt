cmake_minimum_required(VERSION 3.15)
project(forex)

set(CMAKE_CXX_STANDARD 17)

# УКАЗЫВАЕМ ГДЕ ИСКАТЬ pqxx
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/libpqxx")  # ← ИЗМЕНИ ПРИ НЕОБХОДИМОСТИ

find_package(pqxx REQUIRED)

include_directories(include)

add_executable(forex
        src/main.cpp
        src/User.cpp
        src/Admin.cpp
        src/Manager.cpp
        src/Customer.cpp
        src/Order.cpp
        src/Payment.cpp
        src/PaymentStrategies.cpp
        src/Order.cpp
)

target_link_libraries(forex pqxx)

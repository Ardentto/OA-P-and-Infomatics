cmake_minimum_required(VERSION 3.10)
project(RK2_Tasks)

set(CMAKE_CXX_STANDARD 17)

# Сначала создаем цель (исполняемый файл)
add_executable(RK2_Tasks bank_system.cpp)

# Затем настраиваем опции компиляции ДЛЯ ЭТОЙ ЦЕЛИ
if(APPLE)
    # Для MacOS добавляем флаги компиляции
    target_compile_options(RK2_Tasks PRIVATE -Wall -Wextra -Wpedantic)
    # Или можно установить глобальные флаги:
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Если нужно подключать библиотеки (например, для PostgreSQL)
# find_package(PostgreSQL REQUIRED)
# target_link_libraries(BankSystem PRIVATE pqxx pq)
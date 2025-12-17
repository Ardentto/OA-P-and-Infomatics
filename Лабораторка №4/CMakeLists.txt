cmake_minimum_required(VERSION 3.16)
project(Lab4)

set(CMAKE_CXX_STANDARD 17)

# Все в одной строке для компиляции
add_executable(lab4 main.cpp)

target_include_directories(lab4 PRIVATE
        /opt/homebrew/opt/postgresql@15/include
        /opt/homebrew/include
)

target_link_directories(lab4 PRIVATE
        /opt/homebrew/opt/postgresql@15/lib
        /opt/homebrew/lib
)

target_link_libraries(lab4
        pqxx
        pq
        pthread
)
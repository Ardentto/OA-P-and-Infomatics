ROLLBACK;
DROP TABLE IF EXISTS categories;
DROP TABLE IF EXISTS dishes;
DROP TABLE IF EXISTS orders;


CREATE TABLE categories (
    id SERIAL PRIMARY KEY,
    name VARCHAR(50)
);

CREATE TABLE dishes (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    category_id INT REFERENCES categories(id),
    price DECIMAL(10,2)
);

CREATE TABLE orders (
    id SERIAL PRIMARY KEY,
    dish_id INT REFERENCES dishes(id),
    date DATE,
    quantity INT,
    total DECIMAL(10,2)
);

INSERT INTO categories (name) VALUES 
('Супы'), ('Основные'), ('Закуски'), ('Десерты'), ('Напитки');

INSERT INTO dishes (name, category_id, price) VALUES 
('Борщ', 1, 250),
('Стейк', 2, 800),
('Цезарь', 3, 350),
('Тирамису', 4, 300),
('Кофе', 5, 150);

INSERT INTO orders (dish_id, date, quantity, total) VALUES 
(1, '2024-01-15', 2, 500),
(2, '2024-01-15', 1, 800),
(3, '2024-01-16', 3, 1050);

-- Запросы
SELECT * FROM dishes WHERE category_id = 2;
SELECT * FROM orders WHERE date BETWEEN '2024-01-15' AND '2024-01-16';
SELECT SUM(total) FROM orders WHERE date = '2024-01-15';
SELECT dish_id, SUM(quantity) FROM orders GROUP BY dish_id ORDER BY SUM(quantity) DESC;
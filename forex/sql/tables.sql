CREATE TABLE users (
                       user_id SERIAL PRIMARY KEY,
                       name VARCHAR,
                       email VARCHAR UNIQUE,
                       role VARCHAR CHECK (role IN ('admin','manager','customer')),
                       password_hash VARCHAR,
                       loyalty_level INTEGER CHECK (loyalty_level IN (0,1))
);

CREATE TABLE products (
                          product_id SERIAL PRIMARY KEY,
                          name VARCHAR,
                          price DECIMAL CHECK (price > 0),
                          stock_quantity INTEGER CHECK (stock_quantity >= 0)
);

CREATE TABLE orders (
                        order_id SERIAL PRIMARY KEY,
                        user_id INTEGER REFERENCES users(user_id),
                        status VARCHAR CHECK (status IN ('pending','completed','canceled','returned')),
                        total_price DECIMAL,
                        order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE order_items (
                             order_item_id SERIAL PRIMARY KEY,
                             order_id INTEGER REFERENCES orders(order_id) ON DELETE CASCADE,
                             product_id INTEGER REFERENCES products(product_id),
                             quantity INTEGER,
                             price DECIMAL
);

CREATE TABLE order_status_history (
                                      history_id SERIAL PRIMARY KEY,
                                      order_id INTEGER REFERENCES orders(order_id),
                                      old_status VARCHAR,
                                      new_status VARCHAR,
                                      changed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                                      changed_by INTEGER REFERENCES users(user_id)
);

CREATE TABLE audit_log (
                           log_id SERIAL PRIMARY KEY,
                           entity_type VARCHAR,
                           entity_id INTEGER,
                           operation VARCHAR,
                           performed_by INTEGER,
                           performed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

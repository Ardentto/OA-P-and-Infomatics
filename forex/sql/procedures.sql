-- Процедура создания заказа с транзакцией
CREATE OR REPLACE PROCEDURE create_order(p_user_id INTEGER)
LANGUAGE plpgsql
AS $$
BEGIN
INSERT INTO orders(user_id, status, total_price)
VALUES (p_user_id, 'pending', 0);
END;
$$;

-- Процедура изменения статуса заказа
CREATE OR REPLACE PROCEDURE update_order_status(
    p_order_id INTEGER,
    p_new_status VARCHAR,
    p_user_id INTEGER
)
LANGUAGE plpgsql
AS $$
BEGIN
UPDATE orders
SET status = p_new_status
WHERE order_id = p_order_id;
END;
$$;

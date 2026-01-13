-- Получить статус заказа
CREATE OR REPLACE FUNCTION getOrderStatus(p_order_id INTEGER)
RETURNS VARCHAR AS $$
SELECT status FROM orders WHERE order_id = p_order_id;
$$ LANGUAGE SQL;

-- Количество заказов пользователя
CREATE OR REPLACE FUNCTION getUserOrderCount(p_user_id INTEGER)
RETURNS INTEGER AS $$
SELECT COUNT(*) FROM orders WHERE user_id = p_user_id;
$$ LANGUAGE SQL;

-- Общая сумма заказов пользователя
CREATE OR REPLACE FUNCTION getTotalSpentByUser(p_user_id INTEGER)
RETURNS NUMERIC AS $$
SELECT COALESCE(SUM(total_price),0)
FROM orders
WHERE user_id = p_user_id AND status = 'completed';
$$ LANGUAGE SQL;

-- Можно ли вернуть заказ
CREATE OR REPLACE FUNCTION canReturnOrder(p_order_id INTEGER)
RETURNS BOOLEAN AS $$
SELECT
    status = 'completed'
        AND CURRENT_TIMESTAMP - order_date <= INTERVAL '30 days'
FROM orders WHERE order_id = p_order_id;
$$ LANGUAGE SQL;

-- История статусов заказа
CREATE OR REPLACE FUNCTION getOrderStatusHistory(p_order_id INTEGER)
RETURNS TABLE (
    old_status VARCHAR,
    new_status VARCHAR,
    changed_at TIMESTAMP,
    changed_by INTEGER
) AS $$
SELECT old_status, new_status, changed_at, changed_by
FROM order_status_history
WHERE order_id = p_order_id
ORDER BY changed_at;
$$ LANGUAGE SQL;

-- Логирование изменения статуса заказа
CREATE OR REPLACE FUNCTION log_order_status_change()
RETURNS TRIGGER AS $$
BEGIN
INSERT INTO order_status_history(
    order_id, old_status, new_status, changed_by
)
VALUES (
           OLD.order_id,
           OLD.status,
           NEW.status,
           NEW.user_id
       );
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_order_status
    AFTER UPDATE OF status ON orders
    FOR EACH ROW
    EXECUTE FUNCTION log_order_status_change();

-- Аудит операций с заказами
CREATE OR REPLACE FUNCTION audit_orders()
RETURNS TRIGGER AS $$
BEGIN
INSERT INTO audit_log(
    entity_type, entity_id, operation, performed_by
)
VALUES (
           'order',
           NEW.order_id,
           TG_OP,
           NEW.user_id
       );
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_audit_orders
    AFTER INSERT OR UPDATE OR DELETE ON orders
    FOR EACH ROW
    EXECUTE FUNCTION audit_orders();

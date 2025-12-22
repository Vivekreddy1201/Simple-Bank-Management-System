-- ==========================================
-- 3_triggers.sql
-- Purpose: Auto-generate 5-digit Account Number
-- ==========================================

USE smartbank;

DELIMITER $$
CREATE TRIGGER before_insert_account
BEFORE INSERT ON accounts
FOR EACH ROW
BEGIN
    DECLARE last_acc_no INT;
    SELECT IFNULL(MAX(account_no), 10000) INTO last_acc_no FROM accounts;
    SET NEW.account_no = last_acc_no + 1;
END$$
DELIMITER ;

DROP TRIGGER IF EXISTS after_transactions_insert_txnref;
DELIMITER //
CREATE TRIGGER after_transactions_insert_txnref
AFTER INSERT ON transactions
FOR EACH ROW
BEGIN
  -- Format: TXN + YYYYMMDD + 6-digit txn_id e.g. TXN20251105000123
  SET @ref := CONCAT('TXN', DATE_FORMAT(NEW.timestamp, '%Y%m%d'), LPAD(NEW.txn_id, 6, '0'));
  UPDATE transactions SET txn_ref = @ref WHERE txn_id = NEW.txn_id;
END;
//

DELIMITER ;
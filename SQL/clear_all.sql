USE smartbank;
-- Disable foreign key checks temporarily
SET FOREIGN_KEY_CHECKS = 0;

-- Clear all tables
TRUNCATE TABLE transactions;
TRUNCATE TABLE accounts;
TRUNCATE TABLE users;

-- Reset auto-increment counters
ALTER TABLE users AUTO_INCREMENT = 100;
ALTER TABLE accounts AUTO_INCREMENT = 1;
ALTER TABLE transactions AUTO_INCREMENT = 1;

-- Re-enable foreign key checks
SET FOREIGN_KEY_CHECKS = 1;
  

USE smartbank;

-- 1. Ensure users auto-increment starts from 100
ALTER TABLE users AUTO_INCREMENT = 100;

-- 2. Add account_no (5-digit) column (unique) if not present
ALTER TABLE accounts
  ADD COLUMN account_no INT UNIQUE NULL AFTER account_id;

-- 3. Add txn_ref column to transactions for formatted transaction id
ALTER TABLE transactions
  ADD COLUMN txn_ref VARCHAR(30) NULL AFTER txn_id;

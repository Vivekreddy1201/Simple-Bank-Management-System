-- ==========================================
-- 4_stored_procedures.sql
-- Purpose: Define Deposit, Withdraw, and Transfer procedures
-- ==========================================

USE smartbank;

-- Deposit Procedure
DELIMITER $$
CREATE PROCEDURE deposit(IN acc_id INT, IN amt DECIMAL(15,2))
BEGIN
    UPDATE accounts 
    SET balance = balance + amt
    WHERE account_id = acc_id;

    INSERT INTO transactions (account_id, type, amount, remarks)
    VALUES (acc_id, 'DEPOSIT', amt, CONCAT('Deposit of ₹', amt));
END$$
DELIMITER ;

-- Withdraw Procedure
DELIMITER $$
CREATE PROCEDURE withdraw(IN acc_id INT, IN amt DECIMAL(15,2))
BEGIN
    DECLARE current_bal DECIMAL(15,2);
    SELECT balance INTO current_bal FROM accounts WHERE account_id = acc_id;

    IF current_bal >= amt THEN
        UPDATE accounts 
        SET balance = balance - amt
        WHERE account_id = acc_id;

        INSERT INTO transactions (account_id, type, amount, remarks)
        VALUES (acc_id, 'WITHDRAW', amt, CONCAT('Withdrawal of ₹', amt));
    ELSE
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Insufficient balance for withdrawal';
    END IF;
END$$
DELIMITER ;

-- Transfer Procedure
DELIMITER $$
CREATE PROCEDURE transfer_money(IN from_acc INT, IN to_acc INT, IN amt DECIMAL(15,2))
BEGIN
    DECLARE from_bal DECIMAL(15,2);
    SELECT balance INTO from_bal FROM accounts WHERE account_id = from_acc;

    IF from_bal >= amt THEN
        UPDATE accounts SET balance = balance - amt WHERE account_id = from_acc;
        UPDATE accounts SET balance = balance + amt WHERE account_id = to_acc;

        INSERT INTO transactions (account_id, type, amount, remarks)
        VALUES (from_acc, 'TRANSFER-OUT', amt, CONCAT('Transferred ₹', amt, ' to account ', to_acc));

        INSERT INTO transactions (account_id, type, amount, remarks)
        VALUES (to_acc, 'TRANSFER-IN', amt, CONCAT('Received ₹', amt, ' from account ', from_acc));
    ELSE
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Insufficient balance for transfer';
    END IF;
END$$
DELIMITER ;

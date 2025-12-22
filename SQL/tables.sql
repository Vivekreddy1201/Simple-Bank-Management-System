-- ==========================================
-- 1_create_database.sql
-- Purpose: Create SmartBank database
-- ==========================================

CREATE DATABASE IF NOT EXISTS smartbank;
USE smartbank;
-- ==========================================
-- 2_create_tables.sql
-- Purpose: Define Users, Accounts, Transactions tables
-- ==========================================

USE smartbank;

-- Users Table
CREATE TABLE users (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    password VARCHAR(100) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Accounts Table
CREATE TABLE accounts (
    account_id INT AUTO_INCREMENT PRIMARY KEY,
    account_no INT UNIQUE,
    user_id INT NOT NULL,
    type ENUM('Savings', 'Current') DEFAULT 'Savings',
    balance DECIMAL(15,2) DEFAULT 0.00,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE
);

-- Transactions Table
CREATE TABLE transactions (
    txn_id INT AUTO_INCREMENT PRIMARY KEY,
    account_id INT,
    type ENUM('DEPOSIT', 'WITHDRAW', 'TRANSFER-IN', 'TRANSFER-OUT'),
    amount DECIMAL(15,2),
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    remarks VARCHAR(255),
    FOREIGN KEY (account_id) REFERENCES accounts(account_id) ON DELETE CASCADE
);

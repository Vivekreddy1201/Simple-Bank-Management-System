SmartBank – Online Banking Management System (Flask + MySQL)

SmartBank is a web-based banking management system developed using **Flask (Python)** and **MySQL**.  
The application allows users to securely manage bank accounts, perform transactions, apply for loans, and view transaction history through a user-friendly web interface.

This project demonstrates full-stack web development concepts including authentication, database integration, server-side validation, and transactional consistency using stored procedures.

---

## 🚀 Features

### 🔐 User Authentication
- User registration with email validation
- Strong password validation
- Secure login & logout using Flask sessions

### 🏦 Account Management
- Create multiple bank accounts (Savings / Current)
- View account details and balances
- Delete accounts with safety checks

### 💰 Transactions
- Deposit money
- Withdraw money
- Transfer money between accounts
- Transaction history with timestamps

### 📄 Loans
- Apply for loans linked to user accounts
- View loan details and history

### 🛡️ Security & Validation
- Email format validation
- Password strength enforcement
- Ownership checks for all transactions
- Prevention of unauthorized access
- Database integrity using MySQL stored procedures

---

## 🧰 Tech Stack

- **Backend:** Python (Flask)
- **Database:** MySQL
- **Frontend:** HTML, CSS, Jinja2 Templates
- **Database Connector:** PyMySQL
- **Session Management:** Flask Sessions

---

## 🗂️ Project Structure
smartbank/
│
├── app.py # Main Flask application
├── templates/ # HTML templates
│ ├── login.html
│ ├── register.html
│ ├── dashboard.html
│ ├── deposit.html
│ ├── withdraw.html
│ ├── transfer.html
│ ├── loans.html
│ ├── message.html
│ └── ...
│
├── static/ # CSS / assets (if any)
├── database.sql # MySQL schema & stored procedures
└── README.md

---

## 🛠️ Database Design

### Tables Used
- `users` – stores user credentials
- `accounts` – stores bank account details
- `transactions` – stores transaction history
- `loans` – stores loan details

### Stored Procedures
- `deposit(account_id, amount)`
- `withdraw(account_id, amount)`
- `transfer_money(from_account, to_account, amount)`

Stored procedures ensure **atomicity and consistency** during financial transactions.

---

## ⚙️ Setup Instructions

### 1️⃣ Clone the Repository
git clone https://github.com/your-username/smartbank.git
cd smartbank
2️⃣ Install Dependencies
pip install flask pymysql

3️⃣ Configure MySQL
Create a database named smartbank

Import the SQL schema:

SOURCE database.sql;


Update database credentials in app.py if required:

host="127.0.0.1"
user="root"
password=""
database="smartbank"

4️⃣ Run the Application
python app.py

5️⃣ Open in Browser
http://127.0.0.1:5000/

📌 Key Highlights

Uses Flask sessions for authentication

Uses MySQL stored procedures for secure transactions

Prevents unauthorized account access

Clean separation of backend logic and frontend templates

Designed as an academic full-stack project

📄 Disclaimer

This project is developed for educational purposes to demonstrate web application development and database-driven systems.
It is not intended for real-world banking use.

👨‍💻 Author

M. Vivek Reddy
B.Tech – Computer Science and Engineering
Indian Institute of Information Technology, Nagpur

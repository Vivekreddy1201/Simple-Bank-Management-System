# 🚖 Ride Sharing System (C++)

A **console-based Ride Sharing System** built using **C++**, demonstrating core
**Object-Oriented Programming (OOPS)** concepts and **file handling**.
The project simulates basic features of ride-hailing applications like
user/driver registration, login, ride booking, and ride history management.

---

## ✨ Features

### 👤 User
- Register and login
- View profile information
- Book a ride
- View personal ride history

### 🚗 Driver
- Register and login
- View profile information
- View rides assigned to the driver

### ⚙️ System
- Nearest driver allocation based on distance
- Fare calculation using distance
- Persistent data storage using files
- Robust input validation (prevents infinite loops)

---

## 🛠️ Technologies Used
- **Language:** C++
- **Concepts:**
  - Object-Oriented Programming (Inheritance, Encapsulation, Abstraction)
  - File Handling
  - Menu-driven programming
  - Input validation
- **Compiler:** GCC / MinGW (C++17 compatible)

---

## 📂 Project Structure
RideSharingSystem/
│
├── main.cpp # Complete source code
├── users.txt # Registered users data
├── drivers.txt # Registered drivers data
├── rides.txt # Ride history
└── README.md # Project documentation

yaml
Copy code

---

## 📄 Data Format

### users.txt
username,password,name,age,phone

shell
Copy code

### drivers.txt
username,password,name,age,phone,vehicleNumber,vehicleType,location,distance

shell
Copy code

### rides.txt
rideID,userID,driverID,pickup,drop,fare,vehicleType

yaml
Copy code

---

## ▶️ How to Run

1. Clone the repository:
```bash
git clone https://github.com/your-username/ride-sharing-system.git
cd ride-sharing-system
Compile the program:

bash
Copy code
g++ main.cpp -o ride_app
Run the application:

bash
Copy code
./ride_app
🧠 OOPS Concepts Used
Inheritance: Human → User, Driver

Encapsulation: Data hiding with public interfaces

Abstraction: Clear separation of system entities

Modularity: Separate functions for registration, login, booking, and menus

🛡️ Input Validation
Handles invalid and non-numeric input safely

Prevents infinite loops

Ensures valid menu selections and age constraints

🔮 Future Enhancements
Driver availability (online/offline)

Ride acceptance and rejection

Earnings calculation for drivers

Password hashing for security

Database integration (MySQL)

GUI or web-based interface

🎓 Academic Use
This project is suitable for:

C++ OOPS mini-project

Lab/practical examinations

Viva and demonstrations

Resume and placement portfolios

👨‍💻 Author
Vivek
B.Tech – Computer Science Engineering

📜 License
This project is developed for educational purposes only.

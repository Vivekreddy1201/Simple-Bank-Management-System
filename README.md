 🚖 Ride Sharing System (C++)

This is a **console-based Ride Sharing System** implemented in **C++** using
**Object-Oriented Programming (OOPS)** and **file handling**.
The project simulates a basic ride-sharing workflow where users can book rides
and drivers can view their ride history and profile information.

This project is developed as an **academic mini-project** to demonstrate
OOPS concepts, menu-driven programming, and persistent data storage.

---

## ✨ Features

### 👤 User
- Register with validation (age, phone number, unique username)
- Login using username and password
- View personal profile information
- Book a ride by selecting:
  - Pickup location
  - Drop location
  - Vehicle type
- View previous rides booked by the user

### 🚗 Driver
- Register with vehicle and location details
- Login using username and password
- View driver profile information
- View previous rides assigned to the driver

### ⚙️ System
- Menu-driven interface
- Nearest driver selection based on location distance
- Fare calculation based on distance
- Data persistence using text files
- Input validation for age, phone number, and menu options

---

## 🛠️ Technologies Used
- **Language:** C++
- **Concepts Used:**
  - Object-Oriented Programming (Inheritance, Encapsulation)
  - File Handling
  - Menu-Driven Programming
  - Basic Input Validation
- **Compiler:** GCC / MinGW (C++17 compatible)

---

## 📂 Project Structure
RideSharingSystem/
│
├── main.cpp # Complete source code
├── users.txt # Stores registered users
├── drivers.txt # Stores registered drivers
├── rides.txt # Stores ride details
└── README.md # Project documentation

---

## 📄 Data Storage Format

### users.txt
username,password,name,age,phoneNumber

### drivers.txt
username,password,name,age,phoneNumber,vehicleNumber,vehicleType,location

### rides.txt
rideID,userID,driverID,pickupLocation,dropLocation,fare,vehicleType

---

## ▶️ How to Run

1. Compile the program:
```bash
g++ main.cpp -o ride_app
Run the application:

bash
Copy code
./ride_app
🧠 OOPS Concepts Implemented
Inheritance

Human → User, Driver

Encapsulation

Private data members with public getter methods

Abstraction

Separate classes for User, Driver, Vehicle, Ride, and Place

🛡️ Input Validation
Age validation (minimum age requirement)

Phone number validation (10 digits)

Menu input validation

Username uniqueness check during registration

🎓 Academic Use
This project is suitable for:

C++ OOPS mini-project

Lab/practical examinations

Viva and project demonstrations

👨‍💻 Author
Vivek
B.Tech – Computer Science Engineering

📜 Declaration
This project is developed purely for educational purposes and demonstrates
the use of C++ programming concepts.

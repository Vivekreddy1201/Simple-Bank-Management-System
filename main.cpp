#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime> 
#include <cstdlib> 
#include <algorithm>
#include <limits> // For std::numeric_limits

using namespace std;

// Structure to represent a place
struct Place
{
    string name;
    double latitude;
    double longitude;
    double distance; // Distance from the origin (0, 0)

    Place(string n, double lat, double lon, double dist) : name(n), latitude(lat), longitude(lon), distance(dist) {}
};

// Structure to represent a ride
struct Ride
{
    string rideID;
    string userID;
    string driverID;
    Place pickupLocation;
    Place dropoffLocation;
    double fare;
    string vehicleType; // Changed to string

    Ride(string id, string user, string driver, Place pickup, Place dropoff, double fareAmount, string vType)
        : rideID(id), userID(user), driverID(driver), pickupLocation(pickup), dropoffLocation(dropoff), fare(fareAmount), vehicleType(vType) {}
};

// Parent class for Human
class Human
{
protected:
    string name;
    int age;
    string phoneNumber;

public:
    // Constructor
    Human(string n, int a, string phone) : name(n), age(a), phoneNumber(phone) {}

    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getPhoneNumber() const { return phoneNumber; }
};

// Parent class for Vehicle
class Vehicle
{
protected:
    string vehicleNumber;
    string type; // Changed to string

public:
    // Constructor
    Vehicle(string vNum, string t) : vehicleNumber(vNum), type(t) {}

    // Getters
    string getVehicleNumber() const { return vehicleNumber; }
    string getType() const { return type; }
};

// Child class for User
class User : public Human
{
private:
    string username;
    string password;

public:
    // Constructor
    User(string n, int a, string phone, string user, string pass)
        : Human(n, a, phone), username(user), password(pass) {}

    // Getters
    string getUsername() const { return username; }
    string getPassword() const { return password; }

    // Function to display user information
    void displayUserInfo() const
    {
        cout << "----------------------------------------" << endl;
        cout << "User  Information:" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Age: " << getAge() << endl;
        cout << "Phone Number: " << getPhoneNumber() << endl;
        cout << "Username: " << getUsername() << endl;
        cout << "----------------------------------------" << endl;
    }

    // Function to view previous rides
    void viewPreviousRides() const
    {
        ifstream rideFile("rides.txt");
        string line;
        cout << "Previous Rides:" << endl;

        // Check if the file is open
        if (!rideFile.is_open())
        {
            cout << "No previous rides found." << endl;
            return;
        }

        while (getline(rideFile, line))
        {
            // Split the line into components
            size_t pos = 0;
            vector<string> rideDetails;
            while ((pos = line.find(",")) != string::npos)
            {
                rideDetails.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            rideDetails.push_back(line); // Add the last part

            // Ensure we have the expected number of details
            if (rideDetails.size() != 7)
            {
                cout << "Error reading ride details." << endl;
                continue;
            }

            // Extract ride details
            string rideID = rideDetails[0];
            string userID = rideDetails[1];
            string driverID = rideDetails[2];
            string pickupLocation = rideDetails[3];
            string dropoffLocation = rideDetails[4];
            double fare = stod(rideDetails[5]);
            string vehicleType = rideDetails[6]; // Changed to string

            // Display the ride details in a formatted manner
            cout << "----------------------------------------" << endl;
            cout << " Ride ID: " << rideID << endl;
            cout << "Driver: " << driverID << endl; // Assuming driverID is the driver's username
            cout << "You traveled from: " << pickupLocation << " to " << dropoffLocation << endl;
            cout << "Total Fare: $" << fare << endl;
            cout << "Vehicle Type: " << vehicleType << endl; // Changed to string
            cout << "----------------------------------------" << endl;
        }
        rideFile.close();
    }
};

// Child class for Driver
class Driver : public Human
{
private:
    string username;
    string password;
    Vehicle *vehicle; // Pointer to a Vehicle object
    Place *location;  // Pointer to a Place object

public:
    // Constructor
    Driver(string n, int a, string phone, string user, string pass, Vehicle *v, Place *loc)
        : Human(n, a, phone), username(user), password(pass), vehicle(v), location(loc) {}

    // Getters
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    Vehicle *getVehicle() const { return vehicle; }
    Place *getLocation() const { return location; }

    // Function to display driver information
    void displayDriverInfo() const
    {
        cout << "Driver Information:" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Age: " << getAge() << endl;
        cout << "Phone Number: " << getPhoneNumber() << endl;
        cout << "Username: " << getUsername() << endl;
        cout << "Vehicle Number: " << vehicle->getVehicleNumber() << endl;
        cout << "Vehicle Type: " << vehicle->getType() << endl; // Changed to string
        cout << "Location: " << (location ? location->name : "Not assigned") << endl;
    }

    // Function to view previous rides
    void viewPreviousRides() const
    {
        ifstream rideFile("rides.txt");
        string line;
        cout << "Previous Rides:" << endl;

        // Check if the file is open
        if (!rideFile.is_open())
        {
            cout << "No previous rides found." << endl;
            return;
        }

        while (getline(rideFile, line))
        {
            // Split the line into components
            size_t pos = 0;
            vector<string> rideDetails;
            while ((pos = line.find(",")) != string::npos)
            {
                rideDetails.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            rideDetails.push_back(line); // Add the last part

            // Ensure we have the expected number of details
            if (rideDetails.size() != 7)
            {
                cout << "Error reading ride details." << endl;
                continue;
            }

            // Extract ride details
            string rideID = rideDetails[0];
            string userID = rideDetails[1];
            string driverID = rideDetails[2];
            string pickupLocation = rideDetails[3];
            string dropoffLocation = rideDetails[4];
            double fare = stod(rideDetails[5]);
            string vehicleType = rideDetails[6]; // Changed to string

            // Display the ride details in a formatted manner
            cout << "----------------------------------------" << endl;
            cout << "Ride ID: " << rideID << endl;
            cout << "Driver: " << driverID << endl; // Assuming driverID is the driver's username
            cout << "You traveled from: " << pickupLocation << " to " << dropoffLocation << endl;
            cout << "Total Fare: $" << fare << endl;
            cout << "Vehicle Type: " << vehicleType << endl; // Changed to string
            cout << "----------------------------------------" << endl;
        }
        rideFile.close();
    }

    // Function to update driver's location
    void updateLocation(Place *newLocation)
    {
        location = newLocation;
    }
};
// Function to check if a username already exists in a given file
bool usernameExists(const string &username, const string &filename)
{
    ifstream file(filename);
    string line, existingUsername;

    while (getline(file, line))
    {
        // Split the line to extract the username
        stringstream ss(line);
        getline(ss, existingUsername, ','); // The username is the first field in each line

        if (existingUsername == username)
        {
            return true; // Username already exists in the specified file
        }
    }

    file.close();
    return false; // Username does not exist in the specified file
}

// Function to register a user
void registerUser()
{
    string name, username, password, phoneNumber;
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your age: ";
    int age;
    int count = 1;
    while (count)
    {
        cin >> age;
        if (age < 18)
        {
            cout << "Enter valid age :";
            count = 1;
        }
        else
        {
            count = 0;
        }
    }
    cin.ignore();

    bool Validnum = false;
    while (!Validnum)
    {
        cout << "Enter your phone number: ";
        getline(cin, phoneNumber);

        // Check if phone number has exactly 10 digits
        if (phoneNumber.length() == 10 &&
            all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit))
        {
            Validnum = true;
        }
        else
        {
            cout << "Invalid phone number. It should be exactly 10 digits. Try again." << endl;
        }
    }

    bool validUsername = false;
    while (!validUsername)
    {
        cout << "Enter your username: ";
        getline(cin, username);

        if (usernameExists(username, "users.txt"))
        {
            cout << "Username already exists. Please choose a different one." << endl;
        }
        else
        {
            validUsername = true;
        }
    }
    cout << "Enter your password: ";
    getline(cin, password);

    User user(name, age, phoneNumber, username, password);

    ofstream userFile("users.txt", ios::app);
    userFile << username << "," << password << "," << name << "," << age << "," << phoneNumber << endl;
    userFile.close();

    cout << "User  registered successfully!" << endl;
}

// Function to initialize default places
vector<Place> initializePlaces()
{
    vector<Place> places;
    places.emplace_back("Downtown", 40.7128, -74.0060, 5.0);
    places.emplace_back("Airport", 40.6413, -73.7781, 15.0);
    places.emplace_back("Train Station", 40.7506, -73.9935, 10.0);
    places.emplace_back("Mall", 40.7580, -73.9855, 8.0);
    return places;
}

// Function to register a driver
void registerDriver()
{
    string name, username, password, phoneNumber, vehicleNumber, vehicleType;
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your age: ";
    int age;
    int count = 1;
    while (count)
    {
        cin >> age;
        if (age < 18)
        {
            cout << "You don't have minimum age to register as a driver";
            cout << "Enter valid age :";
            count = 1;
        }
        else
        {
            count = 0;
        }
    }
    cin.ignore();
    bool Validnum = false;
    while (!Validnum)
    {
        cout << "Enter your phone number: ";
        getline(cin, phoneNumber);

        if (phoneNumber.length() == 10 &&
            all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit))
        {
            Validnum = true;
        }
        else
        {
            cout << "Invalid phone number. It should be exactly 10 digits. Try again." << endl;
        }
    }

    bool validUsername = false;
    while (!validUsername)
    {
        cout << "Enter your username: ";
        getline(cin, username);

        if (usernameExists(username, "drivers.txt"))
        {
            cout << "Username already exists for a driver. Please choose a different one." << endl;
        }
        else
        {
            validUsername = true;
        }
    }

    cout << "Enter your password: ";
    getline(cin, password);
    cout << "Enter your vehicle number: ";
    getline(cin, vehicleNumber);
    cout << "Enter your vehicle type (Car/Auto/Bike): ";
    getline(cin, vehicleType);

    // Display available places for driver location
    vector<Place> places = initializePlaces();
    cout << "Select your location from the following places:" << endl;
    for (size_t i = 0; i < places.size(); ++i)
    {
        cout << i + 1 << ". " << places[i].name << " (Distance: " << places[i].distance << " km)" << endl;
    }

    int locationChoice;
    cout << "Select your location (1-" << places.size() << "): ";
    cin >> locationChoice;
    cin.ignore();

    if (locationChoice < 1 || locationChoice > places.size())
    {
        cout << "Invalid choice. Registration failed." << endl;
        return;
    }

    Place *location = new Place(places[locationChoice - 1]);
    Vehicle *vehicle = new Vehicle(vehicleNumber, vehicleType);
    Driver driver(name, age, phoneNumber, username, password, vehicle, location);

    ofstream driverFile("drivers.txt", ios::app);
    driverFile << username << "," << password << "," << name << "," << age << "," << phoneNumber << "," << vehicleNumber << "," << vehicleType << "," << location->name << endl;
    driverFile.close();

    cout << "Driver registered successfully!" << endl;
}

// Function to find the nearest driver of a specific vehicle type
Driver *findNearestDriver(const Place &pickupPlace, const string &vehicleType)
{
    ifstream driverFile("drivers.txt");
    string line;
    vector<Driver *> matchingDrivers; // Vector to store matching drivers

    while (getline(driverFile, line))
    {
        size_t pos = 0;
        string fileUsername, filePassword, name, phoneNumber, vehicleNumber, fileVehicleType, location;

        // Extracting the fields from the line
        fileUsername = line.substr(0, line.find(","));
        line.erase(0, line.find(",") + 1);

        filePassword = line.substr(0, line.find(","));
        line.erase(0, line.find(",") + 1);

        name = line.substr(0, line.find(","));
        line.erase(0, line.find(",") + 1);

        int age = stoi(line.substr(0, line.find(",")));
        line.erase(0, line.find(",") + 1);

        phoneNumber = line.substr(0, line.find(","));
        line.erase(0, line.find(",") + 1);

        vehicleNumber = line.substr(0, line.find(","));
        line.erase(0, line.find(",") + 1);

        // Now the next part is the vehicle type
        fileVehicleType = line.substr(0, line.find(",")); // Get vehicle type
        line.erase(0, line.find(",") + 1);                // Remove vehicle type from line

        // The remaining part of the line is the location
        location = line; // This should be the last part, which is the driver's location

        // Check if the vehicle type matches
        if (fileVehicleType == vehicleType)
        {
            // Create a temporary Driver object
            Driver *tempDriver = new Driver(name, age, phoneNumber, fileUsername, filePassword, new Vehicle(vehicleNumber, fileVehicleType), new Place(location, 0, 0, 0)); // Assuming location is a string
            matchingDrivers.push_back(tempDriver);                                                                                                                          // Add to matching drivers
        }
    }
    driverFile.close();

    // Now find the nearest driver from the matching drivers
    Driver *nearestDriver = nullptr;
    double minDistance = numeric_limits<double>::max();

    for (Driver *driver : matchingDrivers)
    {
        // Assuming driver's location is the same as their vehicle's location for simplicity
        Place driverLocation("Driver Location", 0, 0, 0); // Replace with actual driver location logic
        double distance = pickupPlace.distance;           // Replace with actual distance calculation

        if (distance < minDistance)
        {
            minDistance = distance;
            nearestDriver = driver; // Update nearest driver
        }
        else
        {
            delete driver; // Clean up if not the nearest
        }
    }

    // Clean up remaining drivers in the vector
    for (Driver *driver : matchingDrivers)
    {
        if (driver != nearestDriver)
        {
            delete driver; // Clean up if not the nearest
        }
    }

    return nearestDriver; // Return the nearest driver
}

// Function to book a ride
void bookRide(User *user, vector<Place> &places)
{
    cout << "Available Pickup Places:" << endl;
    for (size_t i = 0; i < places.size(); ++i)
    {
        cout << i + 1 << ". " << places[i].name << " (Distance: " << places[i].distance << " km)" << endl;
    }

    int pickupChoice;
    cout << "Select your pickup place (1-" << places.size() << "): ";
    cin >> pickupChoice;
    cin.ignore();

    if (pickupChoice < 1 || pickupChoice > places.size())
    {
        cout << "Invalid choice. Returning to menu." << endl;
        return;
    }

    Place pickupPlace = places[pickupChoice - 1];

    cout << "Select vehicle type (Car/Auto/Bike): ";
    string vehicleType;
    getline(cin, vehicleType);

    cout << "Available Drop Places:" << endl;
    for (size_t i = 0; i < places.size(); ++i)
    {
        cout << i + 1 << ". " << places[i].name << " (Distance: " << places[i].distance << " km)" << endl;
    }

    int dropChoice;
    cout << "Select your drop place (1-" << places.size() << "): ";
    cin >> dropChoice;
    cin.ignore();

    if (dropChoice < 1 || dropChoice > places.size())
    {
        cout << "Invalid choice. Returning to menu." << endl;
        return;
    }

    Place dropPlace = places[dropChoice - 1];

    // Calculate fare based on distance (for simplicity, assume fare is $1 per km)
    double fare = dropPlace.distance * 1.0; // $1 per km
    cout << "Your ride from " << pickupPlace.name << " to " << dropPlace.name << " will cost: $" << fare << endl;

    // Find the nearest driver of the selected vehicle type
    Driver *nearestDriver = findNearestDriver(pickupPlace, vehicleType);
    if (nearestDriver)
    {
        cout << "Driver " << nearestDriver->getName() << " has been allocated to your ride." << endl;

        // Generate a unique rideID using timestamp and random number
        srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
        int randomNum = rand() % 1000; // Random number between 0 and 999
        long timestamp = static_cast<long>(time(0)); // Current timestamp
        string rideID = to_string(timestamp) + to_string(randomNum);

        // Store ride details
        Ride ride(rideID, user->getUsername(), nearestDriver->getUsername(), pickupPlace, dropPlace, fare, vehicleType);
        ofstream rideFile("rides.txt", ios::app);
        rideFile << ride.rideID << "," << ride.userID << "," << ride.driverID << ","
                 << ride.pickupLocation.name << "," << ride.dropoffLocation.name << ","
                 << ride.fare << "," << ride.vehicleType << endl;
        rideFile.close();

        // Update driver's location to drop location
        nearestDriver->updateLocation(&dropPlace);

        // Update the driver's location in the drivers.txt file
        ifstream driverFile("drivers.txt");
        vector<string> drivers; // To store all drivers
        string line;

        // Read all drivers into memory
        while (getline(driverFile, line))
        {
            if (line.find(nearestDriver->getUsername()) != string::npos)
            {
                // Update the line for the allocated driver
                line = line.substr(0, line.rfind(",")) + "," + dropPlace.name; // Update location
            }
            drivers.push_back(line); // Store the line
        }
        driverFile.close();

        // Write the updated drivers back to the file
        ofstream outFile("drivers.txt");
        for (const auto &driverLine : drivers)
        {
            outFile << driverLine << endl;
        }
        outFile.close();

        delete nearestDriver; // Clean up after use
    }
    else
    {
        cout << "No available drivers of the selected type at the moment." << endl;
    }
}

// Function to login as a user
User *loginUser()
{
    string username, password;
    cout << "Enter your username: ";
    getline(cin, username);
    cout << "Enter your password: ";
    getline(cin, password);

    ifstream userFile("users.txt");
    string line;
    bool loginSuccess = false;
    User *loggedInUser = nullptr;

    while (getline(userFile, line))
    {
        size_t pos = line.find(",");
        string fileUsername = line.substr(0, pos);
        string filePassword = line.substr(pos + 1, line.find(",", pos + 1) - pos - 1);

        if (fileUsername == username && filePassword == password)
        {
            loginSuccess = true;
            string name = line.substr(pos + 1 + filePassword.length() + 1, line.find(",", pos + 1 + filePassword.length() + 1) - (pos + 1 + filePassword.length() + 1));
            int age = stoi(line.substr(line.find(",", pos + 1 + filePassword.length() + 1) + 1, line.find(",", line.find(",", pos + 1 + filePassword.length() + 1) + 1) - (line.find(",", pos + 1 + filePassword.length() + 1))));
            string phoneNumber = line.substr(line.find(",", line.find(",", pos + 1 + filePassword.length() + 1) + 1) + 1);
            loggedInUser = new User(name, age, phoneNumber, username, password);
            break;
        }
    }
    userFile.close();

    if (loginSuccess)
    {
        cout << "Login successful!" << endl;
        return loggedInUser;
    }
    else
    {
        cout << "Invalid credentials. Please try again." << endl;
        return nullptr;
    }
}

// Function to login as a driver
Driver *loginDriver()
{
    string username, password;
    cout << "Enter your username: ";
    getline(cin, username);
    cout << "Enter your password: ";
    getline(cin, password);

    ifstream driverFile("drivers.txt");
    string line;
    bool loginSuccess = false;
    Driver *loggedInDriver = nullptr;

    while (getline(driverFile, line))
    {
        size_t pos = line.find(",");
        string fileUsername = line.substr(0, pos);
        string filePassword = line.substr(pos + 1, line.find(",", pos + 1) - pos - 1);

        if (fileUsername == username && filePassword == password)
        {
            loginSuccess = true;
            string name = line.substr(pos + 1 + filePassword.length() + 1, line.find(",", pos + 1 + filePassword.length() + 1) - (pos + 1 + filePassword.length() + 1));
            int age = stoi(line.substr(line.find(",", pos + 1 + filePassword.length() + 1) + 1, line.find(",", line.find(",", pos + 1 + filePassword.length() + 1) + 1) - (line.find(",", pos + 1 + filePassword.length() + 1) + 1)));
            string phoneNumber = line.substr(line.find(",", line.find(",", pos + 1 + filePassword.length() + 1) + 1) + 1);
            string vehicleNumber = line.substr(line.find(",", line.find(",", line.find(",", pos + 1 + filePassword.length() + 1) + 1) + 1) + 1);
            string vehicleType = line.substr(line.find(",", line.find(",", line.find(",", line.find(",", pos + 1 + filePassword.length() + 1) + 1) + 1) + 1) + 1);
            loggedInDriver = new Driver(name, age, phoneNumber, username, password, new Vehicle(vehicleNumber, vehicleType), nullptr);
            break;
        }
    }
    driverFile.close();

    if (loginSuccess)
    {
        cout << "Login successful!" << endl;
        return loggedInDriver;
    }
    else
    {
        cout << "Invalid credentials. Please try again." << endl;
        return nullptr;
    }
}

// Function to display user menu after login
void userMenu(User *user, vector<Place> &places)
{
    int choice;
    do
    {
        cout << "User  Menu:" << endl;
        cout << "1. View Information" << endl;
        cout << "2. Book Ride" << endl;
        cout << "3. View Previous Rides" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character after the choice input

        switch (choice)
        {
        case 1:
            user->displayUserInfo();
            break;
        case 2:
            bookRide(user, places);
            break;
        case 3:
            user->viewPreviousRides();
            break;
        case 4:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}

// Function to display driver menu after login
void driverMenu(Driver *driver)
{
    int choice;
    do
    {
        cout << "Driver Menu:" << endl;
        cout << "1. View Information" << endl;
        cout << "2. View Previous Rides" << endl;
        cout << "3. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character after the choice input

        switch (choice)
        {
        case 1:
            driver->displayDriverInfo();
            break;
        case 2:
            driver->viewPreviousRides();
            break;
        case 3:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
}

// Main menu function
void mainMenu()
{
    vector<Place> places = initializePlaces();
    int choice;
    do
    {
        cout << "Welcome to the Ride Sharing System!" << endl;
        cout << "1. Register as User" << endl;
        cout << "2. Register as Driver" << endl;
        cout << "3. Login as User" << endl;
        cout << "4. Login as Driver" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character after the choice input

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            registerDriver();
            break;
        case 3:
        {
            User *user = loginUser();
            if (user)
            {
                userMenu(user, places);
                delete user; // Clean up after use
            }
            break;
        }
        case 4:
        {
            Driver *driver = loginDriver();
            if (driver)
            {
                driverMenu(driver);
                delete driver; // Clean up after use
            }
            break;
        }
        case 5:
            cout << "Exiting the system. Thank you!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}

// Main function
int main()
{
    mainMenu();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

// --- Interface for Room (IRoom) ---
class IRoom {
public:
    // Pure virtual function to display room information
    virtual void displayInfo() = 0;

    // Pure virtual function to check room availability
    virtual bool isAvailable() const = 0;

    // Virtual destructor
    virtual ~IRoom() {}
};

// --- Room Class ---
class Room : public IRoom {
protected:
    int ID;              // Room ID
    int capacity;        // Room capacity
    string client;       // Client's name who reserved the room
    string phone;        // Client's phone number
    bool available;      // Availability status of the room

public:
    // Constructor with default capacity set to 50
    Room(int ID, int capacity = 50) 
        : ID(ID), capacity(capacity), available(true) {}

    // Function to display room information
    virtual void displayInfo() {
        cout << "Room ID: " << ID 
             << ", Capacity: " << capacity
             << ", Available: " << (available ? "Yes" : "No") << endl;
    }

    // Function to check if the room is available
    bool isAvailable() const {
        return available;
    }

    // Getter for Room ID
    int getID() const {
        return ID;
    }

    // Getter for client's name
    string getClientName() const { 
        return client; 
    }

    // Getter for client's phone number
    string getClientPhone() const { 
        return phone; 
    }

    // Getter for room capacity
    int getCapacity() const {
        return capacity;
    }

    // Function to reserve the room
    void reserveRoom(const string& clientName, const string& clientPhone) {
        client = clientName;
        phone = clientPhone;
        available = false;
    }

    // Function to cancel a reservation
    void cancelReservation() {
        client = "";
        phone = "";
        available = true;
    }

    // Virtual destructor
    virtual ~Room() {}
};

// --- Derived Classes for Specific Room Types ---

// General Room class (inherits from Room)
class GeneralRoom : public Room {
public:
    // Constructor with default capacity set to 50
    GeneralRoom(int ID, int capacity = 50) : Room(ID, capacity) {
        if (capacity > 50)
        {
            capacity = 50;
        }
        
    }
};

// Meeting Room class (inherits from Room)
class MeetingRoom : public Room {
public:
    // Constructor with default capacity set to 20
    MeetingRoom(int ID, int capacity = 20) : Room(ID, capacity) {
        if (capacity > 20)
        {
            capacity = 20;
        }
    }
};

// Teaching Room class (inherits from Room)
class TeachingRoom : public Room {
public:
    // Constructor with default capacity set to 100
    TeachingRoom(int ID, int capacity = 100) : Room(ID, capacity) {
        if (capacity > 100)
        {
            capacity = 100;
        }
    }
};

// --- Reservation Class ---
// Represents a reservation for a specific room with details such as client name, date, time, and phone number
class Reservation {
private:
    int roomID;          // ID of the room being reserved
    string clientName;   // Name of the client making the reservation
    string date;         // Date of the reservation (in YYYY-MM-DD format)
    string time;         // Time of the reservation (in HH:MM format)
    string phone;        // Phone number of the client
    bool isActive;       // Status of the reservation (true for active, false for cancelled)

public:
    // Constructor to initialize reservation details
    Reservation(int roomID, const string& clientName, const string& date, const string& time, const string& phone)
        : roomID(roomID), clientName(clientName), date(date), time(time), phone(phone), isActive(true) {}

    // Function to display reservation details
    void displayReservation() const {
        cout << "Room ID: " << roomID << ", Client: " << clientName
             << ", Date: " << date << ", Time: " << time
             << ", Phone: " << phone
             << ", Status: " << (isActive ? "Active" : "Cancelled") << endl;
    }

    // Function to update the reservation date and time
    void updateReservation(const string& newDate, const string& newTime) {
        if (newDate[4]=='-' && newDate[7]=='-'  && newTime[2] == ':') {
            date = newDate; // Update date
            time = newTime; // Update time
            cout << "Reservation updated successfully!" << endl;
        } else {
            cout << "Invalid date or time!" << endl; // Error message for invalid input
        }
    }

    // Function to cancel the reservation
    void cancelReservation() {
        isActive = false; // Mark reservation as inactive
        cout << "Reservation cancelled successfully!" << endl;
    }

    // Getter for room ID
    int getRoomID() const { return roomID; }

    // Getter for client's name
    string getClientName() const { return clientName; }

    // Getter for reservation date
    string getDate() const { return date; }

    // Getter for reservation time
    string getTime() const { return time; }

    // Getter for client's phone number
    string getPhone() const { return phone; }

    // Setter to update the reservation date
    void setDate(const string& newDate) { date = newDate; }

    // Setter to update the reservation time
    void setTime(const string& newTime) { time = newTime; }

    // Setter to update the client's name
    void setClientName(const string& newClientName) { clientName = newClientName; }

    // Setter to update the client's phone number
    void setPhone(const string& newPhone) { phone = newPhone; }
};

// --- User Class ---
class User {
protected:
    string name;      // User's name (protected)
    string password;  // User's password (protected)
public:
    // Default constructor: initializes the object without setting values
    User() {}

    // Parameterized constructor: initializes the object with a name and password
    User(string name, string password) : name(name), password(password) {}

    // Virtual function for registering a user
    virtual void registerUser() {
        cout << "Registering user: " << name << endl;
    }

    // Virtual function for logging in
    virtual bool login(string username, string pass) {
        // Check if the provided login credentials match
        if (username == name && pass == password) {
            cout << "Login successful!" << endl;
            return true; // Login successful
        }
        // Login failed if credentials do not match
        cout << "Login failed!" << endl;
        return false;
    }

    // Virtual destructor: allows proper cleanup when the class is inherited
    virtual ~User() {}
};

// --- فئة Admin (مدير النظام) ---
// The Admin class inherits from User and is responsible for managing rooms and reservations.
class Admin : public User {
private:
    static map<string, string> users; // A shared map to store all user credentials (username, password).
    vector<Room*> rooms; // A list of pointers to Room objects managed by the admin.
    vector<Reservation> reservations; // A list of reservations managed by the admin.

public:
    Admin() {}
    Admin(string name, string password) : User(name, password) {}

    // Method to register a new user.
    static void registerUser(string username, string password) {
        if (users.find(username) != users.end()) {
            cout << "Username already exists!" << endl;
            return;
        }
        users[username] = password;
        cout << "User registered successfully!" << endl;
    }

    // Override the login method to validate username and password.
    bool login(string username, string password) override {
        if (users.find(username) != users.end() && users[username] == password) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Invalid username or password!" << endl;
            return false;
        }
    }

    // Method to add a new room.
    void addRoom() {
        cout << "Enter Room Type (1: General, 2: Meeting, 3: Teaching): ";
        int type;
        cin >> type;
        cout << "Enter Room ID: ";
        int roomID;
        cin >> roomID;
        cout << "Enter Room Capacity: ";
        int capacity;
        cin >> capacity;

        Room* newRoom = nullptr;
        if (type == 1)
            newRoom = new GeneralRoom(roomID, capacity);
        else if (type == 2)
            newRoom = new MeetingRoom(roomID, capacity);
        else if (type == 3)
            newRoom = new TeachingRoom(roomID, capacity);

        if (newRoom) {
            rooms.push_back(newRoom);
            cout << "Room added successfully!" << endl;
        } else {
            cout << "Invalid room type!" << endl;
        }
    }

    // Method to display all rooms.
    void displayRooms() {
        if (rooms.empty()) {
            cout << "No rooms available." << endl;
            return;
        }

        for (Room* room : rooms) {
            room->displayInfo();
        }
    }

    // Method to remove a room by its ID.
    void removeRoom() {
        cout << "Enter Room ID to delete: ";
        int roomID;
        cin >> roomID;

        auto it = find_if(rooms.begin(), rooms.end(), [roomID](Room* room) { return room->getID() == roomID; });
        if (it != rooms.end()) {
            delete *it; // Delete the room from memory.
            rooms.erase(it); // Remove the room from the list.
            cout << "Room deleted successfully!" << endl;
        } else {
            cout << "Room not found!" << endl;
        }
    }

    // Method to create a new reservation.
    void makeReservation() {
        cout << "Enter Room ID: ";
        int roomID;
        cin >> roomID;

        Room* room = nullptr;
        for (Room* r : rooms) {
            if (r->isAvailable() && r->getID() == roomID) {
                room = r;
                break;
            }
        }

        if (!room) {
            cout << "Room is not available!" << endl;
            return;
        }

        string date, time;
        cout << "Enter Date (YYYY-MM-DD): ";
        cin >> date;
        cout << "Enter Time (HH:MM): ";
        cin >> time;

        // Check for existing reservations with the same date and time.
        for (const Reservation& res : reservations) {
            if (res.getRoomID() == roomID && res.getDate() == date && res.getTime() == time) {
                cout << "This room is already reserved at this time!" << endl;
                return;
            }
        }

        cout << "Enter Client Name: ";
        string clientName;
        cin.ignore();
        getline(cin, clientName);
        cout << "Enter Client Phone: ";
        string phone;
        cin >> phone;

        room->reserveRoom(clientName, phone);
        reservations.emplace_back(roomID, clientName, date, time, phone);
        cout << "Reservation successful!" << endl;
    }

    // Method to remove a reservation by room ID, date, and time.
    void removeReservation() {
        cout << "Enter Room ID: ";
        int roomID;
        cin >> roomID;

        cout << "Enter Reservation Date (YYYY-MM-DD): ";
        string date;
        cin >> date;

        cout << "Enter Reservation Time (HH:MM): ";
        string time;
        cin >> time;

        auto it = remove_if(reservations.begin(), reservations.end(), [roomID, date, time](const Reservation& res) {
            return res.getRoomID() == roomID && res.getDate() == date && res.getTime() == time;
        });

        if (it != reservations.end()) {
            reservations.erase(it, reservations.end());
            cout << "Reservation deleted successfully!" << endl;
        } else {
            cout << "Reservation not found!" << endl;
        }
    }

    // تحميل معلومات الحجوزات من ملف
    void saveReservationsToFile(const string& filename) {
    ofstream outFile(filename, ios::out | ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for saving reservations." << endl;
        return;
    }

    for (const Reservation& res : reservations) {
        outFile << res.getRoomID() << ","
                << res.getClientName() << ","
                << res.getDate() << ","
                << res.getTime() << ","
                << res.getPhone() << "\n";
    }

    outFile.close();
    cout << "Reservations saved successfully to file." << endl;
}

// تعديل على طريقة حفظ الغرف


    // حفظ معلومات الحجوزات إلى ملف
    void loadReservationsFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "File not found. Starting with an empty list of reservations." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string roomIDStr, clientName, date, time, phone;
        getline(ss, roomIDStr, ',');
        getline(ss, clientName, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        getline(ss, phone, ',');

        int roomID = stoi(roomIDStr);
        reservations.emplace_back(roomID, clientName, date, time, phone);
    }
    inFile.close();
    cout << "Reservations loaded successfully from file." << endl;
}

    void loadRoomsFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cout << "File not found. Starting with an empty list of rooms." << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string idStr, capacityStr, availableStr, clientName, phone;
            getline(ss, idStr, ',');
            getline(ss, capacityStr, ',');
            getline(ss, availableStr, ',');
            getline(ss, clientName, ',');
            getline(ss, phone, ',');

            int id = stoi(idStr);
            int capacity = stoi(capacityStr);
            bool available = (availableStr == "1");

            Room* room = new GeneralRoom(id, capacity);
            if (!available) {
                room->reserveRoom(clientName, phone);
            }
            rooms.push_back(room);
        }
        inFile.close();
        cout << "Rooms loaded from file successfully." << endl;
    }


    // Method to save rooms to a file.
void saveRoomsToFile(const string& filename) {
    ofstream outFile(filename, ios::out | ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for saving rooms." << endl;
        return;
    }

    for (Room* room : rooms) {
        outFile << room->getID() << ","
                << room->getCapacity() << ","
                << (room->isAvailable() ? "1" : "0") << ","
                << (room->isAvailable() ? "" : room->getClientName()) << ","
                << (room->isAvailable() ? "" : room->getClientPhone()) << "\n";
    }

    outFile.close();
    cout << "Rooms saved successfully to file." << endl;
}


    // Method to modify an existing reservation.
    void modifyReservation() {
        cout << "Enter Room ID: ";
        int roomID;
        cin >> roomID;

        cout << "Enter Reservation Date (YYYY-MM-DD): ";
        string date;
        cin >> date;

        cout << "Enter Reservation Time (HH:MM): ";
        string time;
        cin >> time;

        // Find the reservation with matching details.
        auto it = find_if(reservations.begin(), reservations.end(), [roomID, date, time](const Reservation& res) {
            return res.getRoomID() == roomID && res.getDate() == date && res.getTime() == time;
        });

        if (it != reservations.end()) {
            Reservation& reservation = *it;
            cout << "Reservation found!" << endl;

            // Provide modification options to the user.
            cout << "What would you like to modify?" << endl;
            cout << "1. Modify Date" << endl;
            cout << "2. Modify Time" << endl;
            cout << "3. Modify Client Name" << endl;
            cout << "4. Modify Client Phone" << endl;
            cout << "5. Cancel" << endl;
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1: {
                    string newDate;
                    cout << "Enter new Date (YYYY-MM-DD): ";
                    cin >> newDate;
                    if (newDate[4] == '-' && newDate[7] == '-') { // Simple validation for date format.
                        reservation.setDate(newDate);
                        cout << "Date updated successfully!" << endl;
                    } else {
                        cout << "Invalid date!" << endl;
                    }
                    break;
                }
                case 2: {
                    string newTime;
                    cout << "Enter new Time (HH:MM): ";
                    cin >> newTime;
                    if (newTime[2] == ':') { // Simple validation for time format.
                        reservation.setTime(newTime);
                        cout << "Time updated successfully!" << endl;
                    } else {
                        cout << "Invalid time!" << endl;
                    }
                    break;
                }
                case 3: {
                    string newClientName;
                    cout << "Enter new Client Name: ";
                    cin.ignore();
                    getline(cin, newClientName);
                    reservation.setClientName(newClientName);
                    cout << "Client name updated successfully!" << endl;
                    break;
                }
                case 4: {
                    string newPhone;
                    cout << "Enter new Client Phone: ";
                    cin >> newPhone;
                    reservation.setPhone(newPhone);
                    cout << "Client phone updated successfully!" << endl;
                    break;
                }
                case 5:
                    cout << "Operation canceled." << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }
        } else {
            cout << "Reservation not found!" << endl;
        }
    }

    // Method to display all reservations.
    void displayReservations() {
        if (reservations.empty()) {
            cout << "No reservations available." << endl;
            return;
        }

        for (const Reservation& res : reservations) {
            res.displayReservation(); // Display reservation details.
        }
    }

    // Destructor to clean up dynamically allocated rooms.
    ~Admin() {
        for (Room* room : rooms) {
            delete room;
        }
    }
};

// Static member initialization for the users map.
map<string, string> Admin::users;


// Function to print a line of a specific character and length
void printLine(char ch = '=', int length = 50) {
    cout << string(length, ch) << endl;
}

// Function to clear the screen based on the operating system
void clearScreen() {
#ifdef _WIN32
    system("cls"); // Command to clear the screen on Windows
#else
    system("clear"); // Command to clear the screen on Linux/Unix
#endif
}

// Function to display the main menu
void displayMainMenu() {
    printLine();
    cout << "Welcome to the Reservation System\n";
    printLine();
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    printLine();
    cout << "Enter your choice: ";
}

// Function to display the admin menu
void displayAdminMenu() {
    printLine();
    cout << "Admin Menu:\n";
    printLine();
    cout << "1. Add Room\n";
    cout << "2. Display Rooms\n";
    cout << "3. Make Reservation\n";
    cout << "4. Display Reservations\n";
    cout << "5. Delete Room\n";
    cout << "6. Delete Reservation\n";
    cout << "7. Modify Reservation\n";
    cout << "8. Logout\n";
    printLine();
    cout << "Enter your choice: ";
}

// Function to display the user menu
void displayUserMenu() {
    printLine();
    cout << "User Menu:\n";
    printLine();
    cout << "1. Display Rooms\n";
    cout << "2. Make Reservation\n";
    cout << "3. Display Reservations\n";
    cout << "4. Logout\n";
    printLine();
    cout << "Enter your choice: ";
}

int main() {
    Admin admin;
    Admin::registerUser("admin", "admin");

    while (true) {
        clearScreen();
        displayMainMenu();

        int mainChoice;
        cin >> mainChoice;

        if (mainChoice == 3) {
            cout << "Exiting the system. Goodbye!" << endl;
            admin.saveRoomsToFile("rooms.txt");
            admin.saveReservationsToFile("reservations.txt");
            break;
        }

        if (mainChoice == 1) {
            clearScreen();
            printLine();
            cout << "Register a New Account\n";
            printLine();
            cout << "Enter username: ";
            string username;
            cin >> username;
            cout << "Enter password: ";
            string password;
            cin >> password;

            Admin::registerUser(username, password);
            cout << "Registration successful!\n";
            cin.ignore();
            cin.get();
        } else if (mainChoice == 2) {
            clearScreen();
            printLine();
            cout << "Login\n";
            printLine();
            cout << "Enter username: ";
            string username;
            cin >> username;
            cout << "Enter password: ";
            string password;
            cin >> password;

            if (admin.login(username, password)) {
                admin.loadRoomsFromFile("rooms.txt");
                admin.loadReservationsFromFile("reservations.txt");

                bool isAdmin = (username == "admin");
                while (true) {
                    clearScreen();
                    if (isAdmin) {
                        displayAdminMenu();
                    } else {
                        displayUserMenu();
                    }

                    int userChoice;
                    cin >> userChoice;

                    if (isAdmin) {
                        switch (userChoice) {
                            case 1:
                                admin.addRoom();
                                admin.saveRoomsToFile("rooms.txt");
                                break;
                            case 2:
                                admin.displayRooms();
                                break;
                            case 3:
                                admin.displayRooms();
                                admin.makeReservation();
                                admin.saveReservationsToFile("reservations.txt");
                                break;
                            case 4:
                                admin.displayReservations();
                                break;
                            case 5:
                                admin.displayRooms();
                                admin.removeRoom();
                                admin.saveRoomsToFile("rooms.txt");
                                break;
                            case 6:
                                admin.displayReservations();
                                admin.removeReservation();
                                admin.saveReservationsToFile("reservations.txt");
                                break;
                            case 7:
                                admin.displayReservations();
                                admin.modifyReservation();
                                admin.saveReservationsToFile("reservations.txt");
                                break;
                            case 8:
                                admin.saveRoomsToFile("rooms.txt");
                                admin.saveReservationsToFile("reservations.txt");
                                goto logout;
                            default:
                                cout << "Invalid choice!" << endl;
                        }
                    } else {
                        switch (userChoice) {
                            case 1:
                                admin.displayRooms();
                                break;
                            case 2:
                                admin.makeReservation();
                                admin.saveReservationsToFile("reservations.txt");
                                break;
                            case 3:
                                admin.displayReservations();
                                break;
                            case 4:
                                admin.saveReservationsToFile("reservations.txt");
                                goto logout;
                            default:
                                cout << "Invalid choice!" << endl;
                        }
                    }
                    cin.ignore();
                    cin.get();
                }
            logout:
                continue;
            } else {
                cout << "Invalid username or password!" << endl;
                cin.ignore();
                cin.get();
            }
        } else {
            cout << "Invalid choice! Please try again.\n";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}
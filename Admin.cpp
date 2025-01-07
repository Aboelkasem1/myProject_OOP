#pragma once

#include <bits/stdc++.h>
#include "User.cpp"
#include "Room.cpp"
#include "Reservation.cpp"

using namespace std;

// --- فئة Admin (مدير النظام) ---
// The Admin class inherits from User and is responsible for managing rooms and reservations.
class Admin : public User {
private:
    static map<string, string> users; // A shared map to store all user credentials (username, password).
    static vector<Room*> rooms; // A list of pointers to Room objects managed by the admin.
    static vector<Reservation> reservations; // A list of reservations managed by the admin.

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

        saveRoomsToFile("rooms.txt");
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

    // Load rooms from file
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

    // Save rooms to file
    void saveRoomsToFile(const string& filename) {
        ofstream outFile(filename, ios::out);
        if (!outFile.is_open()) {
            cerr << "Error: Unable to open file for saving rooms." << endl;
            return;
        }

        // Write room data
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

    // Destructor to clean up dynamically allocated rooms.
    ~Admin() {
        for (Room* room : rooms) {
            delete room;
        }
    }
};

// Static member initialization for the users map.
map<string, string> Admin::users;
vector<Room*> Admin::rooms;
vector<Reservation> Admin::reservations;

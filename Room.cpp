#pragma once

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
    string Type;       // Client's name who reserved the room
    string phone;       // Client's name who reserved the room
    string client;       // Client's name who reserved the room
    bool available;      // Availability status of the room

public:
    // Constructor with default capacity set to 50
    Room(int ID, int capacity, string Type) 
        : ID(ID),capacity(capacity),  Type(Type), available(true) {}

    // Function to display room information
    virtual void displayInfo() {
        cout << "Room ID: " << ID 
             << ", Type Room: " << Type
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

    string getType() const { 
        return Type; 
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
    GeneralRoom(int ID, int capacity = 50) : Room(ID, capacity, "General") {
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
    MeetingRoom(int ID, int capacity = 20) : Room(ID, capacity, "Meeting") {
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
    TeachingRoom(int ID, int capacity = 100) : Room(ID, capacity, "Teaching") {
        if (capacity > 100)
        {
            capacity = 100;
        }
    }
};

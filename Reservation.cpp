#pragma once

#include <bits/stdc++.h> // Includes standard libraries for I/O, regex, etc.
using namespace std;

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

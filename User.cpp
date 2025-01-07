#pragma once

#include <bits/stdc++.h>

using namespace std;

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



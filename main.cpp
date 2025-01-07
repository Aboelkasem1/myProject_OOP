#include <bits/stdc++.h>
#include "Admin.cpp" // Include the Admin class header

using namespace std;

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
    // Register the default admin account
    Admin::registerUser("admin", "admin");

    // Main program loop
    while (true) {
        clearScreen(); // Clear the screen
        displayMainMenu(); // Show the main menu

        int mainChoice;
        cin >> mainChoice;

        // Exit the program
        if (mainChoice == 3) {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        }

        // Register a new user
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

            Admin::registerUser(username, password); // Call Admin's register method
            cout << "Registration successful!\n";
            cin.ignore();
            cin.get(); // Pause for user acknowledgment
        } 
        // User login
        else if (mainChoice == 2) {
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

            Admin admin; // Create an Admin object
            if (admin.login(username, password)) { // Authenticate user
                // Load data from files
                fstream fileRoom("rooms.txt", ios::in|ios::out|ios::trunc);
                fstream fileReservations("reservations.txt", ios::in|ios::out|ios::trunc);

                bool isAdmin = (username == "admin"); // Check if the user is the admin
                while (true) {
                    clearScreen();
                    if (isAdmin) {
                        displayAdminMenu(); // Show admin menu
                    } else {
                        displayUserMenu(); // Show user menu
                    }

                    int userChoice;
                    cin >> userChoice;

                    // Handle admin choices
                    if (isAdmin) {
                        switch (userChoice) {
                            case 1: 
                                admin.addRoom(); // Add a room
                                break;
                            case 2: admin.displayRooms(); break; // Display all rooms
                            case 3: 
                                admin.displayRooms();
                                admin.makeReservation(); // Make a reservation
                                break;
                            case 4: break; // Display all reservations
                            case 5: 
                                admin.displayRooms();
                                admin.removeRoom(); // Delete a room
                                break;
                            case 6:  
                                   
                                admin.removeReservation(); // Delete a reservation
                                break;
                            case 7: 
                                 // Modify a reservation
                                break;
                            case 8: goto logout; // Logout
                            default: cout << "Invalid choice!" << endl;
                        }
                    } 
                    // Handle user choices
                    else {
                        switch (userChoice) {
                            case 1: 
                                admin.displayRooms(); 
                                break; // Display all rooms
                            case 2:
                                admin.makeReservation(); // Make a reservation
                                break;
                            case 3: 
                                 // Display all reservations
                                break;
                            case 4: goto logout; // Logout
                            default: cout << "Invalid choice!" << endl;
                        }

                    }
                    cin.ignore();
                    cin.get(); // Pause for user acknowledgment
                }
            logout:
                continue;
            } else {
                // Invalid login credentials
                cout << "Invalid username or password!" << endl;
                cin.ignore();
                cin.get(); // Pause for user acknowledgment
            }
        } else {
            // Handle invalid main menu choice
            cout << "Invalid choice! Please try again.\n";
            cin.ignore();
            cin.get(); // Pause for user acknowledgment
        }
    }

    return 0;
}

#include <iostream>
#include <string>
#include "database.h"
#include "auth.h"




int main() {
    // We are going to ask the user if they want to register or login.
    std::cout << "Would you like to register or login? (r/l): ";
    char choice;
    std::cin >> choice;
    if(choice == 'r') {
        registerUser();
        std::cout << "Registration successful!" << std::endl;
        std::cout << "You can now login with your new credentials." << std::endl;
        choice = 'l'; // Automatically switch to login after registration
    }
    if(choice == 'l') {
        std::string username = getUsername();
        std::string password = getPassword();
        checkCredentials(username, password);
    }
    else{
        std::cout << "Invalid choice!" << std::endl;
    }
    return 0;
}

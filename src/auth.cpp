#include "auth.h"



std::string getUsername() {
    // We are going to ask the user for their username and return it.
    int usernameLength = 5;
    std::cout << "Enter your username: ";
    std::string username;
    std::cin >> username;
    // We ensure that the username is at least 5 characters long
    while(username.length() < usernameLength) {
        std::cout << "Please enter a username thats at least 5 characters long: ";
        std::cin >> username;
        if(username.length() >= usernameLength) {
            std::cout << "Username accepted :" << std::endl;
            return username;
        }
        else {
            std::cout << "Please try again: " << std::endl; 
        }
    }
    return username;
}

std::string getPassword() {
    // We are going to ask the user for their password and return it.
    std::cout << "Enter your password with at least 2 uppercase characters: ";
    std::string password;
    std::cin >> password;
    while(!isUpper(password)) {
        std::cout << "Please enter another password with at least 2 uppercase characters: " << std::endl;
        std::cin >> password;
        if(isUpper(password)) {
            return password;
        }
    }
    return password;
}

void registerUser() {
    // We are going to register a new user by asking for their username and password and storing it in a database.
    std::cout << "Registering a new user... " << std::endl;
    std::string username = getUsername();
    std::string password = getPassword();
    // Store the username and password in a database (in this case, a text file).
    std::ofstream database("database.txt", std::ios::app);//edit this for sql
    // This line controls the format of the database. Each line will contain a username and password separated by a space.
    database << username << " " << password << std::endl; //edit this for sql
}

void checkCredentials(const std::string& username, const std::string& password) {
    // We are going to check the credentials against the database. 
    std::ifstream database("database.txt");
    enum statusCode {
        SUCCESS,
        WRONG_PASSWORD,
        USER_NOT_FOUND,
        DEFAULT
    };
    enum statusCode status = DEFAULT;
    std::string storedUsername;
    std::string storedPassword;
    // We are going to read the database line by line and check if the username and password match.
    while(database >> storedUsername >> storedPassword) {
        if(storedUsername == username && storedPassword == password) {
            status = SUCCESS;
            break;
        }
        else if(storedUsername == username && storedPassword != password) {
            status = WRONG_PASSWORD;
            break;
        }
    }

    if(status != SUCCESS && status != WRONG_PASSWORD) {

        status = USER_NOT_FOUND;
    }

    switch (status) {
        case SUCCESS: 
            std::cout << "Login Successful. " << std::endl;
            break;
        case WRONG_PASSWORD:
            std::cout << "The password is incorrect. Please try again: " << std::endl;
            break;
        case USER_NOT_FOUND: 
            std::cout << "Username was not found. " << std::endl;
            break;
    }
}

bool isUpper(const std::string& password) {
    // This function is going to take in a string and return true if the string has at least 2 uppercase characters.
    int upperCount = 0;
    for(int a = 0; a < password.length(); a++) {
        if(std::isupper(password[a])) {
            upperCount++;
        }
    }
    if(upperCount >= 2) {
        return true;
    }
    else {
        return false;
    }
}
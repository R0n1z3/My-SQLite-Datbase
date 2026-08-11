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

RegisterStatus registerUser(sqlite3* db) {
    // We check to see if the database handle is null and if it is we return REGISTER_DB_ERROR. So we don't continue.
    if(db == nullptr) {
        std::cout << "Database handle is null" << std::endl;
        return REGISTER_DB_ERROR;
    }
    sqlite3_stmt* stmt = nullptr;
    const char* sql = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
    // We are going to register a new user by asking for their username and password and storing it in a database.
    std::cout << "Registering a new user... " << std::endl;
    std::string username = getUsername();
    std::string password = getPassword();
    // Next we will prepare the staments and bind the users inputs into the dataslots. If sqlite3_prepare() returns anything other than SQLITE_OK we print the error and return REGISTER_DB_ERROR. 
    int preprc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if(preprc != SQLITE_OK) {

        std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
        return REGISTER_DB_ERROR;

    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    // We check to see what sqlite3_step() returned so understand what happened so we can return the correct enum.
    switch(rc) {
        
        case SQLITE_DONE:    
            return REGISTER_SUCCESS;
        
        case SQLITE_CONSTRAINT:
            std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
            return REGISTER_DUPLICATE;
    
        default:
            std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
            return REGISTER_DB_ERROR;

    }
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
#include <iostream>
#include <string>
#include <cctype>
#include <sqlite3.h>

std::string getUsername();
std::string getPassword();
enum RegisterStatus {
    REGISTER_SUCCESS, 
    REGISTER_DUPLICATE, 
    REGISTER_DB_ERROR
};

enum LoginStatus {
    LOGIN_SUCCESS,
    LOGIN_ERROR,
    LOGIN_USER_NOT_FOUND,
    LOGIN_WRONG_PASSWORD
};
RegisterStatus registerUser(sqlite3* db);
LoginStatus loginUser(sqlite3* db, const std::string& username, const std::string& password);
bool isUpper(const std::string& password);
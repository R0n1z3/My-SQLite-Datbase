#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <sqlite3.h>

std::string getUsername();
std::string getPassword();
enum RegisterStatus {
    REGISTER_SUCCESS, 
    REGISTER_DUPLICATE, 
    REGISTER_DB_ERROR
};
RegisterStatus registerUser(sqlite3* db);
void checkCredentials(const std::string& username, const std::string& password);
bool isUpper(const std::string& password);
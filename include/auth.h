#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cctype>

std::string getUsername();
std::string getPassword();
void registerUser();
void checkCredentials(const std::string& username, const std::string& password);
bool isUpper(const std::string& password);
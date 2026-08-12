#include <iostream>
#include <string>
#include "database.h"
#include "auth.h"

int main() {

     std::string dbPath = "src/database/users.db";
     sqlite3* db =  nullptr;
    
    bool openDB = openConnection(&db,dbPath);
    if(openDB != true) {

        std::cout << "Failed to open database! See error above. " << std::endl;
        return 1;
    } 

    bool schemaRC = schemaInit(db);
    if(schemaRC != true) {
        
        std::cout << "Failed to initliaze schema. See error above. " << std::endl;
        return 1;
    }

    int choice = 0;
    std::cout << "Would you like to register or login? Please type 1 for register or 2 for login " << std::endl;
    std::cin >> choice;

    switch(choice) {

        case 1: {

            RegisterStatus registerUserRC = registerUser(db);
            if(registerUserRC == REGISTER_SUCCESS) {
                std::cout << "Please login now. " << std::endl;
                std::cout << "Enter your username: " << std::endl;
                std::string username;
                std::cin >> username;
                std::cout << "Enter your password: " << std::endl;
                std::string password; 
                std::cin >> password;
                LoginStatus loginUserRC = loginUser(db, username, password);
                
                while (loginUserRC != LOGIN_SUCCESS) {
                    
                    if(loginUserRC == LOGIN_ERROR) {
                        std::cout << "An error has an occured. See below. " << std::endl;
                        break;
                    }
                    else if(loginUserRC == LOGIN_WRONG_PASSWORD) {
                        std::cout << "Wrong username or password " << std::endl;
                    }
                    
                    else {
                        std::cout << "Wrong username or password " << std::endl;
                    }
                    
                    std::cout << "Please try again: " << std::endl;
                    std::cout << "Enter your username: " << std::endl;
                    std::cin >> username;
                    std::cout << "Enter your password: " << std::endl;
                    std::cin >> password;
                    loginUserRC = loginUser(db, username, password);
                }
                if(loginUserRC == LOGIN_SUCCESS) {
                    std::cout << "Login Success!" << std::endl; 
                    break;
                }
                
                break;
            }
            
            else if(registerUserRC == REGISTER_DUPLICATE) {
                std::cout << "Duplicate username. Please choose another username. " << std::endl;
            }
            
            else if(registerUserRC == REGISTER_DB_ERROR) {
                std::cout << "An error has occured. See below. " << std::endl;
                break;
            }
            break;
        }
            
            case 2: {

                std::cout << "Please login now. " << std::endl;
                std::cout << "Enter your username: " << std::endl;
                std::string username;
                std::cin >> username;
                std::cout << "Enter your password: " << std::endl;
                std::string password; 
                std::cin >> password;
                LoginStatus loginUserRC = loginUser(db, username, password);
                
                while (loginUserRC != LOGIN_SUCCESS) {
                    
                    if(loginUserRC == LOGIN_ERROR) {
                        std::cout << "An error has an occured. See below. " << std::endl;
                        break;
                    }
                    else if(loginUserRC == LOGIN_WRONG_PASSWORD) {
                        std::cout << "Wrong username or password " << std::endl;
                    }
                    
                    else {
                        std::cout << "Wrong username or password " << std::endl;
                    }
                    
                    std::cout << "Please try again: " << std::endl;
                    std::cout << "Enter your username: " << std::endl;
                    std::cin >> username;
                    std::cout << "Enter your password: " << std::endl;
                    std::cin >> password;
                    loginUserRC = loginUser(db, username, password);
                }
                if(loginUserRC == LOGIN_SUCCESS) {
                    std::cout << "Login Success!" << std::endl;
                    break;
                }
                
                break;
            }

            default:
                std::cout << "Invalid Choice" << std::endl;
        }
        closeConnection(&db);
        return 0;

    }
    
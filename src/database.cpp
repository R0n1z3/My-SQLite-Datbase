#include "database.h"


bool openConnection(sqlite3** db, const std::string& dbPath) {
    
    sqlite3* myDb = nullptr; // This is the pointer to the database connection handle. 
    int rc = sqlite3_open(dbPath.c_str(), &myDb); // RC holds the status of the connection to the database.
    // We check the return code  of sqlite3_open() to see what happened.
    if(rc != SQLITE_OK) {
        // Since the return code failed we simply print and error message telling what happened and close the attemped connection to the database.
        std::cout << "Connection Failed: " << sqlite3_errmsg(myDb) << " " << std::endl;
        int cc = sqlite3_close(myDb);
        // We check to see if sqlite3_close() closed the database connection.
        if(cc != SQLITE_OK) {
            std::cout << "Not closed yet: " << cc << std::endl;   
        }
        return false;
    }

    *db = myDb;
    // Once the connection is open we attempt to turn on foreign keys.
    int pragmaResult = sqlite3_exec(*db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
    // If enabling foreign keys fails we close the connection to the database.
    if(pragmaResult != SQLITE_OK) {
        std::cout << "Failed to enable foreign keys: " << sqlite3_errmsg(myDb) << std::endl;
        closeConnection(db);
        return false;
    }
    return true;
}

bool schemaInit(sqlite3* db) {
    // This function is going to initalize the schema once the database connection has been opened and established.
    // We verify that db is not a nullptr before beginning, if it is we stop the function.
    if (db == nullptr) {
        
        std::cout << "Database handle is null! " << std::endl;
        return false;

    }

    const char* sqlCMD = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL UNIQUE, password_hash TEXT NOT NULL, created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP);";
    int rc = sqlite3_exec(db, sqlCMD, nullptr, nullptr, nullptr);
    // We initilaze schema here and check to ensure schema init properly if it dosent we return false
    if(rc != SQLITE_OK) {

        std::cout << "Schema failed to init: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    return true;

}

bool closeConnection(sqlite3** db) {
    // We verify that our database is active and not null. If it is then we simply just return true because there is nothing left to close.
    if(db == nullptr || *db == nullptr) {

        return true;

    }
    // We attempt to close the database connection and if it fails we print whhy it failed.
    int cc = sqlite3_close(*db);

    if(cc != SQLITE_OK) {

        std::cout << "Failed to Close: " << sqlite3_errmsg(*db) << std::endl;
        return false;

    }

    // If database connection closed then we set the database handle back to null and return true. Letting everybody know the close was successful.
    *db = nullptr;
    return true;
}
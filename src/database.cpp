#include "database.h"


bool openConnection(sqlite3** db, const std::string& dbPath) {
    
    sqlite3* myDb = nullptr; // This is the pointer to the database connection handle.
    sqlite3* errmsg = nullptr; // This pointer is for the error message that gets returned if the database connection fails.
    sqlite3* closeCode = nullptr; // This pointer is for the close connection status. 
    int rc = sqlite3_open(u8"dbPath", &myDb); // RC holds the status of the connection to the database.

    if(rc != SQLITE_OK) {

        std::cout << "Connection Failed: " << sqlite3_errmsg(errmsg) << " " << std::endl;
        int cc = sqlite3_close(closeCode);

        if(cc != SQLITE_OK) {
            std::cout << "Connection closed! " << std::endl;
            return false;
        }
    }
    
    




}
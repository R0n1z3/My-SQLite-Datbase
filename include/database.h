#include <iostream>
#include <string>
#include <sqlite3.h>

bool openConnection(sqlite3** db, const std::string& dbPath);
void closeConnection();
void schemaInit();

#include <iostream>
#include <string>
#include <sqlite3.h>

bool openConnection(sqlite3** db, const std::string& dbPath);
bool closeConnection(sqlite3** db);
bool schemaInit(sqlite3* db);

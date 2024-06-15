#include <iostream>
#include "sqlite3.h"
#include "laczenie_z_sql.h"



int openDatabase(const std::string& dbName, sqlite3** db) {
    int rc = sqlite3_open(dbName.c_str(), db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(*db) << std::endl;
        return rc;
    } else {
        std::cerr << "Opened database successfully" << std::endl;
    }
    return SQLITE_OK;
}

void closeDatabase(sqlite3* db) {
    if (db) {
        sqlite3_close(db);
    }
}

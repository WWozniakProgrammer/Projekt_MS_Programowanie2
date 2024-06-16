#include <iostream>
#include "sqlite3.h"
#include "laczenie_z_sql.h"


static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}


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

int executeSQL(sqlite3* db, const std::string& sql, int (*callback)(void*, int, char**, char**)) {
    char* zErrMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "SQL executed successfully" << std::endl;
    }
    return rc;
}

int displayData(const std::string& dbName, const std::string& sql) {
    sqlite3* db;
    int rc;

    // Otwarcie połączenia z bazą danych
    rc = openDatabase(dbName, &db);
    if (rc != SQLITE_OK) {
        return rc;
    }

    // Wykonanie zapytania SQL i wyświetlenie wyników
    rc = executeSQL(db, sql, callback);
    if (rc != SQLITE_OK) {
        closeDatabase(db);
        return rc;
    }

    // Zamknięcie połączenia z bazą danych
    closeDatabase(db);
    return SQLITE_OK;
}



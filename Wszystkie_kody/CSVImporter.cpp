#include "CSVImporter.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "sqlite3.h"
#include <vector>

CSVImporter::CSVImporter(const std::string& dbPath) {
    if (!openDatabase(dbPath)) {
        std::cerr << "Failed to open database." << std::endl;
    }
}

CSVImporter::~CSVImporter() {
    closeDatabase();
}

bool CSVImporter::openDatabase(const std::string& dbPath) {
    return sqlite3_open(dbPath.c_str(), &db) == SQLITE_OK;
}

void CSVImporter::closeDatabase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

void CSVImporter::importCSV(const std::string& csvPath, const std::string& tableName) {
    readCSV(csvPath, tableName);
}

void CSVImporter::readCSV(const std::string& csvPath, const std::string& tableName) {
    std::ifstream file(csvPath);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << csvPath << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Pomijamy pierwszą linię (nagłówki)

    std::string sql = "INSERT INTO " + tableName + " VALUES (";
    bool firstLine = true;

    while (std::getline(file, line)) {
        auto values = split(line);
        std::string valuesStr;

        valuesStr.pop_back(); // Usuwamy ostatni przecinek

        if (!firstLine) {
            sql += "),(";
        }


        firstLine = false;
    }
    sql += ");";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Data imported successfully." << std::endl;
    }
}

std::vector<std::string> CSVImporter::split(const std::string& s) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token)) {
        tokens.push_back(token);
    }
    return tokens;
}



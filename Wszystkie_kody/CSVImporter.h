#ifndef PROJEKT_MS_PROGRAMOWANIE2_CSVIMPORTER_H
#define PROJEKT_MS_PROGRAMOWANIE2_CSVIMPORTER_H
#include "sqlite3.h"
#include <string>
#include <vector>

class CSVImporter {
    public:
        CSVImporter(const std::string& dbPath);
        ~CSVImporter();
        void importCSV(const std::string& csvPath, const std::string& tableName);

    private:
        sqlite3* db;
        bool openDatabase(const std::string& dbPath);
        void closeDatabase();
        void readCSV(const std::string& csvPath, const std::string& tableName);
        std::vector<std::string> split(const std::string& s, char delimiter);

    std::vector<std::string> split(const std::string &s);
};




#endif //PROJEKT_MS_PROGRAMOWANIE2_CSVIMPORTER_H

//#ifndef PROJEKT_MS_PROGRAMOWANIE2_LACZENIE_Z_SQL_H
#define PROJEKT_MS_PROGRAMOWANIE2_LACZENIE_Z_SQL_H


#include "sqlite3.h"
#include <string>

// Funkcja do otwierania połączenia z bazą danych
int openDatabase(const std::string& dbName, sqlite3** db);

// Funkcja do zamykania połączenia z bazą danych
void closeDatabase(sqlite3* db);

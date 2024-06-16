#include "DB.h"
#include <iostream>


DB::DB()
{
	int rc = sqlite3_open("baza.db", &this->db);

	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "Opened database successfully" << std::endl;
	}


}

void DB::close()
{
	sqlite3_close(this->db);
}

bool DB::executeQuery(const char* sql)
{
	char* errMsg = 0;
	int rc = sqlite3_exec(this->db, sql, nullptr, 0, &errMsg);

	if (rc != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return false;
	}
	else {
		std::cout << "Query executed successfully" << std::endl;
		return true;
	}
}

// Function to select data from a table
bool DB::selectData(const char* sql) {

	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, nullptr);

	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(this->db) << std::endl;
		return true;
	}

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* id = sqlite3_column_text(stmt, 0);
		const unsigned char* name = sqlite3_column_text(stmt, 1);
		int score = sqlite3_column_int(stmt, 2);

		std::cout << "ID: " << id << ", Name: " << name << ", Score: " << score << std::endl;
	}

	if (rc != SQLITE_DONE) {
		std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
	}

	sqlite3_finalize(stmt);

	return true;
}


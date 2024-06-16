#include <iostream>
#include "sqlite3.h"
#include "laczenie_z_sql.h"


BAZA::BAZA()
{
    int rc = sqlite3_open("baza.db", &this->db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Opened database successfully" << std::endl;
    }


}

void BAZA::close()
{
    sqlite3_close(this->db);
}




bool BAZA::executeSQL(const char* sql) {
    char *errMsg = 0;
    int rc = sqlite3_exec(this->db, sql, nullptr, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    } else {
        std::cout << "Query executed successfully" << std::endl;
        return true;
    }


}



CompanyData* BAZA::getCompanies(const char* sql) {       //pobieranie  i wysłyłanie spolek

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(this->db) << std::endl;
        return nullptr;
    }

    CompanyData* first_company;
    CompanyData* current_company;
    first_company = current_company;


    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* id = sqlite3_column_text(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        auto* company = new CompanyData;
        company->next = nullptr;
        current_company->next = company;
        current_company = company;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    return first_company;
}





QuartersData* BAZA::getQuarters(const char* sql) {        //pobieranie notowan kwartalnych

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(this->db) << std::endl;
        return nullptr;
    }

    QuartersData* first_quarters;
    QuartersData* current_quarters;
    first_quarters = current_quarters;


    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* id = sqlite3_column_text(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        int score = sqlite3_column_int(stmt, 2);
        auto* quarter = new QuartersData;
        quarter->next = nullptr;
        current_quarters->next = quarter;
        current_quarters = quarter;
        std::cout << "ID: " << id << ", Name: " << name << ", Score: " << score << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    return first_quarters;
}



QuoteData* BAZA::getQuotes(const char* sql) { // pobieranie notowan

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(this->db) << std::endl;
        return nullptr;
    }

    QuoteData* first_quote;
    QuoteData* current_quote;
    first_quote = current_quote;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* id = sqlite3_column_text(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        int score = sqlite3_column_int(stmt, 2);
        auto* quote = new QuoteData;
        quote->next = nullptr;
        current_quote->next = quote;
        current_quote = quote;

        std::cout << "ID: " << id << ", Name: " << name << ", Score: " << score << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    return first_quote;
}


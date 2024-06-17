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
CompanyData* BAZA::getCompanies(const char* sql) {
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(this->db) << std::endl;
        return nullptr;
    }

    CompanyData* first_company = nullptr;
    CompanyData* current_company = nullptr;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* id = sqlite3_column_text(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        auto* company = new CompanyData;
        company->id_firmy = reinterpret_cast<const char*>(id);
        company->nazwa_spolki = reinterpret_cast<const char*>(name);
        company->next = nullptr;

        if (first_company == nullptr) {
            first_company = company;
            current_company = company;
        } else {
            current_company->next = company;
            current_company = company;
        }
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    return first_company;
}




QuartersData* BAZA::getQuarters(const char* sql) {
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(this->db) << std::endl;
        return nullptr;
    }

    QuartersData* first_quarters = nullptr;
    QuartersData* current_quarters = nullptr;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* id = sqlite3_column_text(stmt, 0);
        int rok = sqlite3_column_int(stmt, 1);
        int kwartal = sqlite3_column_int(stmt, 3);
        double cena = sqlite3_column_double(stmt, 4);
        auto* quarter = new QuartersData;
        quarter->id_firmy = reinterpret_cast<const char*>(id);
        quarter->rok = rok;
        quarter->kwartal = kwartal;
        quarter->cena = cena;
        quarter->next = nullptr;

        if (first_quarters == nullptr) {
            first_quarters = quarter;
            current_quarters = quarter;
        } else {
            current_quarters->next = quarter;
            current_quarters = quarter;
        }

    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    return first_quarters;
}



QuoteData* BAZA::getQuotes(const char* sql) {
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(this->db) << std::endl;
        return nullptr;
    }

    QuoteData* first_quote = nullptr;
    QuoteData* current_quote = nullptr;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* id = sqlite3_column_text(stmt, 0);
        const unsigned char* time = sqlite3_column_text(stmt, 1);
        double cena = sqlite3_column_int(stmt, 2);
        auto* quote = new QuoteData;
        quote->id_firmy = reinterpret_cast<const char*>(id);
        quote->data_czas = reinterpret_cast<const char*>(time);
        quote->cena = cena;
        quote->next = nullptr;

        if (first_quote == nullptr) {
            first_quote = quote;
            current_quote = quote;
        } else {
            current_quote->next = quote;
            current_quote = quote;
        }

    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    return first_quote;
}


void BAZA::printCompanyList(CompanyData *head) {
    CompanyData* current = head;
    while (current != nullptr) {
        std::cout << "ID: " << current->id_firmy << ", Nazwa Spolki: " << current->nazwa_spolki << std::endl;
        current = current->next;
    }
}


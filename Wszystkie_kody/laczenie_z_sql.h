//#ifndef PROJEKT_MS_PROGRAMOWANIE2_LACZENIE_Z_SQL_H
#define PROJEKT_MS_PROGRAMOWANIE2_LACZENIE_Z_SQL_H


#include "sqlite3.h"
#include <string>

struct CompanyData {
    std::string nazwa_spolki ;
    std::string id_firmy;
    CompanyData* next;
};


struct QuartersData {
    std::string id_firmy ;
    int rok;
    int kwartal;
    double cena;
    QuartersData* next;
};


struct QuoteData {
    std::string id_firmy ;
    std::string data_czas;
    double cena;
    QuoteData* next;
};


class BAZA
{
public:
    BAZA();
    void close();
    bool executeSQL(const char* sql);
    CompanyData* getCompanies(const char* sql);
    QuartersData* getQuarters(const char* sql);
    QuoteData*  getQuotes(const char* sql);
    void printCompanyList(CompanyData* head);

private:
    sqlite3* db{};

};









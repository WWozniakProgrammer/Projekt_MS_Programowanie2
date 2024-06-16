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
    float cena;
    QuartersData* next;
};


struct QuoteData {
    std::string id_firmy ;
    int data_czas;
    float cena;
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


private:
    sqlite3* db{};

};









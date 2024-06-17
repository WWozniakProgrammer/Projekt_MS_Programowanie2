#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <memory>
#include "laczenie_z_sql.h"


using namespace std;
// ta funkcja zwraca ścieżkę z pythonem (nawet jak ma się ich kilka to zwraca tą która działa ;)
string get_first_python_path() {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen("where python", "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Usunięcie nowej linii na końcu
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    // Pobranie pierwszej ścieżki
    size_t pos = result.find('\n');
    if (pos != string::npos) {
        result = result.substr(0, pos);
    }
    return result;
}




int main() {


    BAZA db;
    std::string sql = "SELECT * FROM Spolki";

    CompanyData* companyList = db.getCompanies(sql.c_str());
    db.getCompanies("SELECT * FROM Spolki");
    db.printCompanyList(companyList);





    try {
        string python_path = get_first_python_path();
        string spolka;
        cout << "Podaj nazwe spolki: ";
        cin >> spolka;

        // Konstruowanie komendy do uruchomienia skryptu Python
        string command = python_path + " D:\\GitHub\\Projekt_MS_Programowanie2\\Wszystkie_kody\\scrapowanie.py " + spolka;

        // Uruchomienie skryptu Python z nazwą spółki jako argumentem
        int result = system(command.c_str());

        if (result != 0) {
            cerr << "Wystapil blad podczas uruchamiania skryptu Python" << endl;
        }
    } catch (const exception& ex) {
        cerr << "Wystapił wyjatek: " << ex.what() << endl;
    }




    return 0;
}

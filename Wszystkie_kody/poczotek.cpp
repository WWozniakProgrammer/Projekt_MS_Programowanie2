#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <memory>

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
    cout << "Python path: " << result << endl;
    return result;
}

int main() {
    try {
        string python_path = get_first_python_path();
        string spolka;
        cout << "Podaj nazwę spółki: ";
        cin >> spolka;

        // Konstruowanie komendy do uruchomienia skryptu Python
        string command = python_path + "C:\\Python_Scripts\\Repozytoria_Git\\Projekt_MS_Programowanie2\\Wszystkie_kody\\scrapowanie.py " + spolka;

        // Uruchomienie skryptu Python z nazwą spółki jako argumentem
        int result = system(command.c_str());

        if (result != 0) {
            cerr << "Wystąpił błąd podczas uruchamiania skryptu Python" << endl;
        }
    } catch (const exception& ex) {
        cerr << "Wystąpił wyjątek: " << ex.what() << endl;
    }

    return 0;
}

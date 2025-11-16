// Michał Lusa

#include <fstream>
#include <list>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string zad2 = "../zalaczniki-2025/symbole.txt";

bool czy_palindrom(string tekst) {
    int ile_znakow = tekst.length();
    for (int i = 0; i < ile_znakow / 2; i++) {
        if (tekst[i] != tekst[ile_znakow - i - 1])
            return false;
    }
    return true;
}

void Zadanie2_1() {
    ifstream plik(zad2);
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
    }

    ofstream wynik("wynik2_1.txt");
    string linia;

    while (plik >> linia) {
        if (czy_palindrom(linia)) {
            wynik << linia << endl;
        }
    }
}

void Zadanie2_2(){
    ifstream plik(zad2);
    if(!plik.is_open()){
        cerr << "Nie mozna otworzyc pliku" << endl;
        return;
    }

    vector<string> wiersze;
    string linia;
    while(getline(plik, linia)){
        wiersze.push_back(linia);
    }
    plik.close();

    ofstream wynik("wynik2_2.txt");

    int liczba_wierszy = wiersze.size();
    int licznik_kwadratow = 0;

    string odp = "";

    for(int i = 1; i < liczba_wierszy - 1; i++){
        int dlugosc = wiersze[i].length();
        for(int j = 1; j < dlugosc - 1; j++){
            char znak = wiersze[i][j];

            bool kwadrat = true;
            for(int di = -1; di <= 1 && kwadrat; di++){
                for(int dj = -1; dj <= 1; dj++){
                    if(i+di < 0 || i+di >= liczba_wierszy) { kwadrat = false; break; }
                    if(j+dj < 0 || j+dj >= wiersze[i+di].length()) { kwadrat = false; break; }
                    if(wiersze[i+di][j+dj] != znak){ kwadrat = false; break; }
                }
            }

            if(kwadrat){
                licznik_kwadratow++;
                cout << i+1 << " " << j+1 << endl;
                wynik << i+1 << " " << j+1 << endl;
                odp += to_string(i+1) + " " + to_string(j+1) + " ";
            }
        }
    }

    cout << "Liczba kwadratow: " << licznik_kwadratow << endl;
    odp = to_string(licznik_kwadratow) + " " + odp;

    wynik << odp;

    wynik.close();
}

int main()
{
    Zadanie2_1();
    Zadanie2_2();
}

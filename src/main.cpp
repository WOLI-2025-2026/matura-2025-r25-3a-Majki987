// Michał Lusa

#include <fstream>
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

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
                    if(wiersze[i+di][j+dj] != znak){ kwadrat = false; break; }
                }
            }

            if(kwadrat){
                licznik_kwadratow++;
                odp += to_string(i+1) + " " + to_string(j+1) + " ";
            }
        }
    }

    cout << "Liczba kwadratow: " << licznik_kwadratow << endl;
    odp = to_string(licznik_kwadratow) + " " + odp;

    wynik << odp;

    wynik.close();
}

// mnozy decimal (string, least significant digit at end) przez 3 i dodaje add (0..2)
void mul3_add(string &dec, int add) {
    int carry = add;
    for (int i = (int)dec.size() - 1; i >= 0; --i) {
        int d = dec[i] - '0';
        long long prod = 1LL * d * 3 + carry;
        dec[i] = char('0' + (prod % 10));
        carry = int(prod / 10);
    }
    while (carry > 0) {
        char digit = char('0' + (carry % 10));
        dec.insert(dec.begin(), digit);
        carry /= 10;
    }
}

// zwraca true gdy a < b (obie reprezentowane jako normalne napisy dziesiętne bez wiodących zer,
// ale dopuszczamy "0" jako jedyny przypadek z zerami)
bool decimal_less(const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

int Zadanie2_3() {
    const string inputFile = "symbole.txt";   // plik wejściowy
    const string outputFile = "wynik2_3.txt";

    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cerr << "Nie mozna otworzyc pliku: " << inputFile << '\n';
        return 1;
    }
    ofstream fout(outputFile);
    if (!fout.is_open()) {
        cerr << "Nie mozna utworzyc pliku wynikowego: " << outputFile << '\n';
        return 1;
    }

    string line;
    string bestDec = "0";
    string bestLine = "";

    while (getline(fin, line)) {
        // pomijamy ewentualne puste linie
        if (line.empty()) continue;

        string dec = "0";
        for (char c : line) {
            int digit;
            if (c == 'o') digit = 0;
            else if (c == '+') digit = 1;
            else digit = 2;
            mul3_add(dec, digit);
        }

        // usuniecie wiodacych zer
        size_t firstNonZero = dec.find_first_not_of('0');
        if (firstNonZero == string::npos) dec = "0";
        else dec = dec.substr(firstNonZero);

        if (decimal_less(bestDec, dec)) {
            bestDec = dec;
            bestLine = line;
        }
    }

    // wypisz wynik
    cout << bestDec << " " << bestLine << '\n';
    fout << bestDec << " " << bestLine << '\n';

    fin.close();
    fout.close();
    return 0;
}



void Zadanie2_4() {
    ifstream fin(zad2);
    if (!fin.is_open()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        return;
    }
    ofstream fout("wynik2_4.txt");
    if (!fout.is_open()) {
        cerr << "Nie mozna utworzyc pliku wynikowego" << endl;
        return;
    }

    string suma = "0";  // suma jako napis dziesiętny

    string linia;
    while (getline(fin, linia)) {
        if (linia.empty()) continue;

        string dec = "0";  // aktualna liczba w dziesiętnym zapisie jako string
        for (char c : linia) {
            int digit;
            if (c == 'o') digit = 0;
            else if (c == '+') digit = 1;
            else /* '*' */ digit = 2;

            mul3_add(dec, digit);  // mnożymy przez 3 i dodajemy digit
        }

        // dodanie dec do sumy
        string newSum = "";
        int n1 = dec.size();
        int n2 = suma.size();
        int i1 = n1 - 1;
        int i2 = n2 - 1;
        int carryInt = 0;

        while (i1 >= 0 || i2 >= 0 || carryInt > 0) {
            int d1 = (i1 >= 0) ? dec[i1] - '0' : 0;
            int d2 = (i2 >= 0) ? suma[i2] - '0' : 0;
            int sumDigit = d1 + d2 + carryInt;
            carryInt = sumDigit / 10;
            sumDigit = sumDigit % 10;
            newSum = char('0' + sumDigit) + newSum;
            i1--; i2--;
        }
        suma = newSum;
    }

    // wypisanie wyniku dziesiętnego
    cout << suma << " ";

    // konwersja sumy na zapis trójkowy z symbolami o,+,*
    string trójkowy = "";
    string tmp = suma;
    if (tmp == "0") trójkowy = "o";
    else {
        while (tmp != "0") {
            // dzielimy tmp przez 3
            int remainder = 0;
            string next = "";
            
            for (int i = 0; i < (int)tmp.size(); i++) {
                int digit = tmp[i] - '0';
                int current = remainder * 10 + digit;
                next += char('0' + (current / 3));
                remainder = current % 3;
            }
            
            // usuń wiodące zera
            while (!next.empty() && next[0] == '0') {
                next = next.substr(1);
            }
            if (next.empty()) next = "0";

            // reszta to cyfra w systemie trójkowym
            if (remainder == 0) trójkowy = "o" + trójkowy;
            else if (remainder == 1) trójkowy = "+" + trójkowy;
            else trójkowy = "*" + trójkowy;

            tmp = next;
        }
    }

    cout << trójkowy << endl;
    fout << suma << " " << trójkowy << endl;

    fin.close();
    fout.close();
}




int main()
{
    // Zadanie2_1();
    // Zadanie2_2();
    // Zadanie2_3();
    Zadanie2_4();
}

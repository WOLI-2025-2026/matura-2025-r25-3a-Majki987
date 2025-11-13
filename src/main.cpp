//imie i nazwisko
#include <fstream>
#include <iostream>
using namespace std;



string zad3 ="../zalaczniki-2025/symbole.txt";
bool czy_palindrom(string tekst){
    int ile_znakow = tekst.length();
    for(int i=0; i< ile_znakow/2 ; i++){
        if(tekst[i] != tekst[ile_znakow-i-1])
            return false;
    }
    return true;

}
void Zadanie3_1(){
    ifstream plik(zad3);
    if(!plik.is_open()){
        cerr << "Nie mozna otworzyc pliku"<< endl;
    }
    ofstream wynik("wynik3_1.txt");
    string linia ;
    while(plik >> linia){
        if(czy_palindrom(linia)){
            wynik << linia <<endl;
        }
    }
    plik.close();
    wynik.close();
}
int main() {
    Zadanie3_1();
    return 0;
}

#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include "Walka.h"

using namespace std;

//deklaracje funkcji

void czekaj(int);		 //funckja s³u¿y do zatrzymania programu na 'n' sekund
void wypisz_walki(std::list<int> walki_gracza, std::map<int, Walka*> wszystkie_walki);


//funkcja main

int main() {
	std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiejestosci;		//dla uproszczenia: zapis bêdzie: baza_umiejetnosci[rodzaj][poziom][id] => baza_umiejetnosci[z][y][x]
	std::map<int, Karta_gracza*> baza_gracze;	
	//std::set<int> zalogowani_gracze;	-> na przysz³oœæ
	std::map<int, Walka*> baza_walki;
	int ostatni_gracz = 0, ostatnia_walka = 0;
	string dane_tekstowe;
	fstream plik_umiejetnosci, plik_gracze, plik_walki;
	plik_umiejetnosci.open("baza umiejetnosci.txt", ios::in);		//do odczytu
	if (plik_umiejetnosci.good()) {
		//odczytywanie informacji z plików
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"baza umiejetnosci.txt\".";
		int odcz_ID, odcz_lvl, odcz_rodzaj, odcz_dmg, odcz_os, odcz_of, odcz_om, od_mod, od_czas;
		string odcz_nazwa, odcz_opis, odcz_nazwa_efekt, odcz_opis_efekt;
		Efekty* pocz_listy_efektow, *tmp = nullptr;
		bool brak, cel;
		char kod_mod, rodzaj_um;
		if (plik_umiejetnosci.eof())
			cout << "\nPUSTY PLIK";
		while (plik_umiejetnosci.eof() != true) {
			getline(plik_umiejetnosci, odcz_nazwa);
			getline(plik_umiejetnosci, odcz_opis);
			getline(plik_umiejetnosci, dane_tekstowe);
			odcz_ID = atoi(dane_tekstowe.c_str());
			getline(plik_umiejetnosci, dane_tekstowe);
			odcz_lvl = atoi(dane_tekstowe.c_str());
			getline(plik_umiejetnosci, dane_tekstowe);
			odcz_rodzaj = atoi(dane_tekstowe.c_str());
			getline(plik_umiejetnosci, dane_tekstowe);
			if (dane_tekstowe == "O") {
				getline(plik_umiejetnosci, dane_tekstowe);
				odcz_dmg = atoi(dane_tekstowe.c_str());
				rodzaj_um = 'O';
			}
			else if (dane_tekstowe == "D") {
				getline(plik_umiejetnosci, dane_tekstowe);
				odcz_os = atoi(dane_tekstowe.c_str());
				getline(plik_umiejetnosci, dane_tekstowe);
				odcz_of = atoi(dane_tekstowe.c_str());
				getline(plik_umiejetnosci, dane_tekstowe);
				odcz_om = atoi(dane_tekstowe.c_str());
				rodzaj_um = 'D';
			}
			else {
				//specjalne
				rodzaj_um = 'S';
			}
			//Efekty						kolejnoœæ jak dla konstuktora
			getline(plik_umiejetnosci, dane_tekstowe);
			if (dane_tekstowe == "BRAK") {
				pocz_listy_efektow = nullptr;
				brak = true;
			}
			else {
				brak = false;
				odcz_nazwa_efekt = dane_tekstowe;
				getline(plik_umiejetnosci, odcz_opis_efekt);			
				getline(plik_umiejetnosci, dane_tekstowe);
				od_mod = atoi(dane_tekstowe.c_str());
				getline(plik_umiejetnosci, dane_tekstowe);
				od_czas = atoi(dane_tekstowe.c_str());
				getline(plik_umiejetnosci, dane_tekstowe);
				kod_mod = dane_tekstowe[0];
				getline(plik_umiejetnosci, dane_tekstowe);
				if (dane_tekstowe == "TAK")
					cel = true;
				else
					cel = false;
				Efekty* nowy_efekt = new Efekty(odcz_nazwa_efekt, odcz_opis_efekt, od_mod, od_czas, kod_mod, cel);
				pocz_listy_efektow = nowy_efekt;
				tmp = nowy_efekt;
			}
			while (brak != true) {
				getline(plik_umiejetnosci, dane_tekstowe);
				if (dane_tekstowe == "BRAK") {
					brak = true;
					tmp->nast = nullptr;		//zabezpieczenie
				}
				else {
					odcz_nazwa_efekt = dane_tekstowe;
					getline(plik_umiejetnosci, odcz_opis_efekt);
					getline(plik_umiejetnosci, dane_tekstowe);
					od_mod = atoi(dane_tekstowe.c_str());
					getline(plik_umiejetnosci, dane_tekstowe);
					od_czas = atoi(dane_tekstowe.c_str());
					getline(plik_umiejetnosci, dane_tekstowe);
					kod_mod = dane_tekstowe[0];
					getline(plik_umiejetnosci, dane_tekstowe);
					if (dane_tekstowe == "TAK")
						cel = true;
					else
						cel = false;
					Efekty* nowy_efekt2 = new Efekty(odcz_nazwa_efekt, odcz_opis_efekt, od_mod, od_czas, kod_mod, cel);
					tmp->nast = nowy_efekt2;
					tmp = nowy_efekt2;
				}
			}
			brak = false;
			//posiadamy teraz listê efektów -> ostatni element konstruktora
			if (rodzaj_um == 'O') {
				Umiejetnosci_ofensywne* nowa_off = new Umiejetnosci_ofensywne(odcz_ID, odcz_lvl, odcz_rodzaj, odcz_nazwa, odcz_opis, pocz_listy_efektow, odcz_dmg);
				baza_umiejestosci[odcz_rodzaj][odcz_lvl].push_back(nowa_off);
			}
			else if (rodzaj_um == 'D') {
				Umiejetnosci_defensywne* nowa_def = new Umiejetnosci_defensywne(odcz_ID, odcz_lvl, odcz_rodzaj, odcz_nazwa, odcz_opis, pocz_listy_efektow, odcz_os, odcz_of, odcz_om);
				baza_umiejestosci[odcz_rodzaj][odcz_lvl].push_back(nowa_def);
			}
			else {
				//um_spiecjalna
			}
		}
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"baza umiejetnosci.txt\".";
	}
	plik_umiejetnosci.close();
	plik_gracze.open("baza gracze.txt", ios::in);					//do odczytu
	if (plik_gracze.good()) {
		//odczytywanie informacji z plików
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"baza gracze.txt\".";
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"baza gracze.txt\".";
	}
	plik_gracze.close();

	plik_walki.open("baza walki.txt", ios::in);					//do odczytu
	if (plik_walki.good()) {
		//odczytywanie informacji z plików
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"baza walki.txt\".";
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"baza walki.txt\".";
	}
	plik_walki.close();
	
	czekaj(5);




	baza_umiejestosci.clear();
	baza_gracze.clear();
	baza_walki.clear();
}


//definicje funkcji


void czekaj(int sekundy) {
	typedef long clock_t;
	clock_t koniec = clock() + sekundy * CLOCKS_PER_SEC;
	while (clock() < koniec)
	continue;
}

void wypisz_walki(std::list<int> walki_gracza, std::map<int, Walka*> wszystkie_walki) {
	std::list<int>::iterator it;
	std::map<int, Walka*>::iterator it_walki;
	for (it = walki_gracza.begin(); it != walki_gracza.end(); it++) {
		it_walki = wszystkie_walki.begin();
		while (it_walki->second->zwroc_numer_walki() != *it && it_walki != wszystkie_walki.end()) {
			it_walki++;
		}
		if (it_walki == wszystkie_walki.end()) {
		std::cout << "\nBLAD! BRAK WALKI NUMER: " << it_walki->first;
		}
		else {
			it_walki->second->wypisz_informacje();
			std::cout << "\n=========================================\n";
		}
	}
}


//ŒMIETNIK:
/*
string opis;
Efekty* lista_ef;
Umiejetnosci_ofensywne test(20, 2, 1, "ciosII", opis, nullptr, 5);
Umiejetnosci test2();
baza_umiejestosci[0][0].push_back(&test);



delete &baza_gracze;
//delete &zalogowani_gracze;
delete &baza_walki;
delete &baza_umiejestosci;





*/
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include "Walka.h"

using namespace std;

//deklaracje funkcji

void czekaj(int);		 //funckja s³u¿y do zatrzymania programu na 'n' sekund
void wypisz_walki(std::list<int> walki_gracza, std::map<int, Walka*> wszystkie_walki);
void odczyt_umiejetnosci(string nazwa_pliku, std::vector<std::vector<std::vector<Umiejetnosci*>>> &baza_um);
void odczyt_gracze(string nazwa_pliku, map<int, Karta_gracza*> &baza_gr, int &licz_gracz);
void odczyt_walki(string nazwa_pliku, map<int, Walka*> &baza_wal, int &licz_walk);


//funkcja main

int main() {
	std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiejestosci; 		//dla uproszczenia: zapis bêdzie: baza_umiejetnosci[rodzaj][poziom][id] => baza_umiejetnosci[z][y][x]
	std::map<int, Karta_gracza*> baza_gracze;	
	//std::set<int> zalogowani_gracze;	-> na przysz³oœæ
	std::map<int, Walka*> baza_walki;
	int ostatni_gracz = 0, ostatnia_walka = 0;
	//ustawianie bazowego rozmiaru vetora umeijêtnoœci [0-6][0-4][n]
	baza_umiejestosci.resize(7);
	for (int i = 0; i < 7; i++){
		baza_umiejestosci[i].resize(5);		//zapamiêtaæ -> patrzeæ, czy zamiast resize nei pojawi³o siê 'reserve' -.-
		}
	//odczyt umiejêtnosci:
	odczyt_umiejetnosci("baza umiejetnosci.txt", baza_umiejestosci);
	//odczyt gracze:
	odczyt_gracze("baza gracze.txt", baza_gracze, ostatni_gracz);
	//odczyt walki:
	odczyt_walki("baza walki.txt", baza_walki, ostatnia_walka);
	
	czekaj(5);

	//
	vector<Umiejetnosci*>::iterator it;
	Umiejetnosci* tmp;
	if (baza_umiejestosci.empty() == false) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 5; j++) {
				for (it = baza_umiejestosci[i][j].begin(); it < baza_umiejestosci[i][j].end(); it++) {
					tmp = *it;
					tmp->wypisz_informacje();
					cout << "\n\n";
					czekaj(4);
				}
			}
		}
	}
	else {
		std::cout << "\nBRAK UMIEJETNOSCI";
	}
	czekaj(10);
	//



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

void odczyt_umiejetnosci(string nazwa_pliku, std::vector<std::vector<std::vector<Umiejetnosci*>>> &baza_um) {
	fstream plik;
	//
	plik.open(nazwa_pliku, ios::in);		//do odczytu
	//
	/*
	Organizacja pliku z umiejêtnosciami:
	-ka¿da nowa umiejêtnoœæ zaczyna siê od kilkunastu znaków '=' -> symbolizuje niepustoœæ pliku
	-w ka¿dej linii znajduj¹ siê dane potrzebne do konstruktora (int numer, int lvl, int typ, std::string nazwa_um, std::string opis_um, Efekty* lista_ef, dodatkowe)
	-po opisie nale¿y umieœciæ znak D, O lub S dla odpowiedniego rodzaju umeijêtnoœci -> decyduje ile kolejnych linii zawiera potrzebne dla konstruktora informacje
	-póŸniej nastêpuje utworzenie listy efektów:
	a)kolejnoœæ danych (nazwa,opis,modyfikator, czas, typ_modyfikatora(tak samo jak dla konstruktora))
	b)jeœli nie ma dalszych umiejêtnoœci (czyli jesli ich nie ma w ogóle tak¿e) to piszemy liniê zawieraj¹c¹ "BRAK"
	c)otrzymujemy listê efektów, któr¹ wykorzystujemy przy konstruktorze
	*/
	//
	if (plik.good()) {
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \""<< nazwa_pliku <<"\"";
		//odczytywanie informacji z plików
		int odcz_ID, odcz_lvl, odcz_rodzaj, odcz_dmg, odcz_os, odcz_of, odcz_om, od_mod, od_czas;
		string odcz_nazwa, odcz_opis, odcz_nazwa_efekt, odcz_opis_efekt;
		Efekty* pocz_listy_efektow, *tmp = nullptr;
		bool brak, cel;
		char kod_mod, rodzaj_um;
		string dane_tekstowe;
		getline(plik, dane_tekstowe);	//->musimy mieæ chocia¿ jedn¹ operacjê odczytu
		if (plik.eof())
			cout << "\nPUSTY PLIK";
		while (plik.eof() != true) {
			getline(plik, dane_tekstowe);
			odcz_ID = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			odcz_lvl = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			odcz_rodzaj = atoi(dane_tekstowe.c_str());
			getline(plik, odcz_nazwa);
			getline(plik, odcz_opis);
			getline(plik, dane_tekstowe);
			if (dane_tekstowe == "O") {
				getline(plik, dane_tekstowe);
				odcz_dmg = atoi(dane_tekstowe.c_str());
				rodzaj_um = 'O';
			}
			else if (dane_tekstowe == "D") {
				getline(plik, dane_tekstowe);
				odcz_os = atoi(dane_tekstowe.c_str());
				getline(plik, dane_tekstowe);
				odcz_of = atoi(dane_tekstowe.c_str());
				getline(plik, dane_tekstowe);
				odcz_om = atoi(dane_tekstowe.c_str());
				rodzaj_um = 'D';
			}
			else {
				//specjalne
				rodzaj_um = 'S';
			}
			//Efekty						kolejnoœæ jak dla konstuktora
			getline(plik, dane_tekstowe);
			if (dane_tekstowe == "BRAK") {
				pocz_listy_efektow = nullptr;
				brak = true;
			}
			else {
				brak = false;
				odcz_nazwa_efekt = dane_tekstowe;
				getline(plik, odcz_opis_efekt);
				getline(plik, dane_tekstowe);
				od_mod = atoi(dane_tekstowe.c_str());
				getline(plik, dane_tekstowe);
				od_czas = atoi(dane_tekstowe.c_str());
				getline(plik, dane_tekstowe);
				kod_mod = dane_tekstowe[0];
				getline(plik, dane_tekstowe);
				if (dane_tekstowe == "TAK")
					cel = true;
				else
					cel = false;
				Efekty* nowy_efekt = new Efekty(odcz_nazwa_efekt, odcz_opis_efekt, od_mod, od_czas, kod_mod, cel);
				pocz_listy_efektow = nowy_efekt;
				tmp = nowy_efekt;
			}
			while (brak != true) {
				getline(plik, dane_tekstowe);
				if (dane_tekstowe == "BRAK") {
					brak = true;
					tmp->nast = nullptr;		//zabezpieczenie
				}
				else {
					odcz_nazwa_efekt = dane_tekstowe;
					getline(plik, odcz_opis_efekt);
					getline(plik, dane_tekstowe);
					od_mod = atoi(dane_tekstowe.c_str());
					getline(plik, dane_tekstowe);
					od_czas = atoi(dane_tekstowe.c_str());
					getline(plik, dane_tekstowe);
					kod_mod = dane_tekstowe[0];
					getline(plik, dane_tekstowe);
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
			//cout << odcz_ID << " " << odcz_lvl << " " << odcz_rodzaj;
			if (rodzaj_um == 'O') {
				Umiejetnosci_ofensywne* nowa_off = new Umiejetnosci_ofensywne(odcz_ID, odcz_lvl, odcz_rodzaj, odcz_nazwa, odcz_opis, pocz_listy_efektow, odcz_dmg);
				baza_um[odcz_rodzaj][odcz_lvl].push_back(nowa_off);
			}
			else if (rodzaj_um == 'D') {
				Umiejetnosci_defensywne* nowa_def = new Umiejetnosci_defensywne(odcz_ID, odcz_lvl, odcz_rodzaj, odcz_nazwa, odcz_opis, pocz_listy_efektow, odcz_os, odcz_of, odcz_om);
				baza_um[odcz_rodzaj][odcz_lvl].push_back(nowa_def);
			}
			else {
				//um_spiecjalna
			}
			getline(plik, dane_tekstowe);
		}
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"" << nazwa_pliku << "\"";
	}
	plik.close();
}

void odczyt_gracze(string nazwa_pliku, map<int, Karta_gracza*> &baza_gr, int &licz_gracz) {
	fstream plik;
	plik.open(nazwa_pliku, ios::in);					//do odczytu
	if (plik.good()) {
		//odczytywanie informacji z plików
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"" << nazwa_pliku << "\"";
		//zmienne:

		//
		string dane_tekstowe;
		getline(plik, dane_tekstowe);	//->musimy mieæ chocia¿ jedn¹ operacjê odczytu
		if (plik.eof())
			cout << "\nPUSTY PLIK";
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"" << nazwa_pliku << "\"";
	}
	plik.close();
}

void odczyt_walki(string nazwa_pliku, map<int, Walka*> &baza_wal, int &licz_walk) {
	fstream plik;
	plik.open(nazwa_pliku, ios::in);					//do odczytu
	if (plik.good()) {
		//odczytywanie informacji z plików
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"" << nazwa_pliku << "\"";
		//zmienne:

		//
		string dane_tekstowe;
		getline(plik, dane_tekstowe);	//->musimy mieæ chocia¿ jedn¹ operacjê odczytu
		if (plik.eof())
			cout << "\nPUSTY PLIK";
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"" << nazwa_pliku << "\"";
	}
	plik.close();
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
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include "Walka.h"

using namespace std;

//deklaracje funkcji

void czekaj(int);		 //funckja s�u�y do zatrzymania programu na 'n' sekund
void wypisz_walki(std::list<int> walki_gracza, std::map<int, Walka*> wszystkie_walki);
void odczyt_umiejetnosci(string nazwa_pliku, std::vector<std::vector<std::vector<Umiejetnosci*>>> &baza_um);
void odczyt_gracze(string nazwa_pliku, map<int, Karta_gracza*> &baza_gr, int &licz_gracz);
void odczyt_walki(string nazwa_pliku, map<int, Walka*> &baza_wal, int &licz_walk, map<int, Karta_gracza*> &baza_gr);
std::string szyfruj(std::string tekst, int klucz, string klucz2);
std::string deszyfruj(std::string szyfrowana, int klucz, string klucz2);
std::string DecnaBin(int liczbaDec);
int BinnaDec(std::string liczbaBin);
Karta_gracza* znajdz_gracza(int numer_gracza, map<int, Karta_gracza*> baza_gr);
//funkcja main

int main() {
	std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiejestosci; 		//dla uproszczenia: zapis b�dzie: baza_umiejetnosci[rodzaj][poziom][id] => baza_umiejetnosci[z][y][x]
	std::map<int, Karta_gracza*> baza_gracze;	
	//std::set<int> zalogowani_gracze;	-> na przysz�o��
	std::map<int, Walka*> baza_walki;
	int ostatni_gracz = 0, ostatnia_walka = 0;
	//ustawianie bazowego rozmiaru vetora umeij�tno�ci [0-6][0-4][n]
	baza_umiejestosci.resize(7);
	for (int i = 0; i < 7; i++){
		baza_umiejestosci[i].resize(5);		//zapami�ta� -> patrze�, czy zamiast resize nei pojawi�o si� 'reserve' -.-
		}
	//odczyt umiej�tnosci:
	odczyt_umiejetnosci("baza umiejetnosci.txt", baza_umiejestosci);
	czekaj(2);
	//odczyt gracze:
	odczyt_gracze("baza gracze.txt", baza_gracze, ostatni_gracz);
	czekaj(2);
	//odczyt walki:
	odczyt_walki("baza walki.txt", baza_walki, ostatnia_walka, baza_gracze);
	czekaj(2);
	
	//odczytywanie zawarto�ci bazy_umiej�tno�ci po dodaniu wszystkich plik�w
	vector<Umiejetnosci*>::iterator it;
	Umiejetnosci* tmp;
	if (baza_umiejestosci.empty() == false) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 5; j++) {
				for (it = baza_umiejestosci[i][j].begin(); it < baza_umiejestosci[i][j].end(); it++) {
					tmp = *it;
					tmp->wypisz_informacje();
					cout << "\n\n";
					//czekaj(2);
				}
			}
		}
	}
	else {
		std::cout << "\nBRAK UMIEJETNOSCI";
	}
	czekaj(20);
	//system("pause");
	//



	baza_umiejestosci.clear();
	baza_gracze.clear();
	baza_walki.clear();
}


//definicje funkcji




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
	Organizacja pliku z umiej�tnosciami:
	-ka�da nowa umiej�tno�� zaczyna si� od kilkunastu znak�w '=' -> symbolizuje niepusto�� pliku
	-w ka�dej linii znajduj� si� dane potrzebne do konstruktora (int numer, int lvl, int typ, std::string nazwa_um, std::string opis_um, Efekty* lista_ef, dodatkowe)
	-po opisie nale�y umie�ci� znak D, O lub S dla odpowiedniego rodzaju umeij�tno�ci -> decyduje ile kolejnych linii zawiera potrzebne dla konstruktora informacje
	-p�niej nast�puje utworzenie listy efekt�w:
	a)kolejno�� danych (nazwa,opis,modyfikator, czas, typ_modyfikatora(tak samo jak dla konstruktora))
	b)je�li nie ma dalszych umiej�tno�ci (czyli jesli ich nie ma w og�le tak�e) to piszemy lini� zawieraj�c� "BRAK"
	c)otrzymujemy list� efekt�w, kt�r� wykorzystujemy przy konstruktorze
	*/
	//
	if (plik.good()) {
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \""<< nazwa_pliku <<"\"";
		//odczytywanie informacji z plik�w
		int odcz_ID, odcz_lvl, odcz_rodzaj, odcz_dmg, odcz_os, odcz_of, odcz_om, od_mod, od_czas;
		string odcz_nazwa, odcz_opis, odcz_nazwa_efekt, odcz_opis_efekt;
		Efekty* pocz_listy_efektow, *tmp = nullptr;
		bool brak, cel;
		char kod_mod, rodzaj_um;
		string dane_tekstowe;
		getline(plik, dane_tekstowe);	//->musimy mie� chocia� jedn� operacj� odczytu
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
			//Efekty						kolejno�� jak dla konstuktora
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
			//posiadamy teraz list� efekt�w -> ostatni element konstruktora
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
	/*
	Organizacja pliku baza gracze.txt:
	-ka�dy nowy gracz zaczyna si� ci�giem kilkunastu dowolnych znak�w
	-nazwa
	-has�o (szyfrowane!)
	-numerID
	-max_P�
	-max_mana
	-poziom
	-PD
	-umiej�tno�ci
	-walki
	-efekty

	a)umiej�tno�ci:
	X1
	Y1
	Z1
	X2
	Y2
	Z2
	BRAK

	b)walki:
	numerwalki1
	numerwalki2
	numerwalki3
	BRAK

	c)efekty: to samo co przy umiej�tnosciach
	*/
	
	fstream plik;
	plik.open(nazwa_pliku, ios::in);					//do odczytu
	if (plik.good()) {
		//odczytywanie informacji z plik�w
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"" << nazwa_pliku << "\"";
		//zmienne:
		string nazwa, haslo, odcz_nazwa_efekt, odcz_opis_efekt;
		int id, pz, max_mana, lvl, EXP, ox, oy, oz, owalka, od_mod, od_czas;
		std::list<Umiejetnosci_skrot*> odcz_umiej;
		std::list<int> odcz_walki;
		Efekty* lista_ef_gracza, *tmp = nullptr;
		bool koniec, cel;
		Umiejetnosci_skrot* nowa;
		char kod_mod;
		Karta_gracza* nowy_gracz;
		//
		string dane_tekstowe;
		getline(plik, dane_tekstowe);	//->musimy mie� chocia� jedn� operacj� odczytu
		if (plik.eof())
			cout << "\nPUSTY PLIK";
		while (plik.eof() != true) {
			getline(plik, dane_tekstowe);
			nazwa = dane_tekstowe;
			getline(plik, dane_tekstowe);
			haslo = deszyfruj(dane_tekstowe, 8, "0110");
			getline(plik, dane_tekstowe);
			id = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			pz = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			max_mana = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			lvl = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			EXP = atoi(dane_tekstowe.c_str());
			//umiejetnosci
			odcz_umiej.clear();
			koniec = false;
			while (koniec != true) {
				getline(plik, dane_tekstowe);
				if (dane_tekstowe == "BRAK")
					koniec = true;
				else {
					ox = atoi(dane_tekstowe.c_str());
					getline(plik, dane_tekstowe);
					oy = atoi(dane_tekstowe.c_str());
					getline(plik, dane_tekstowe);
					oz = atoi(dane_tekstowe.c_str());
					nowa = new Umiejetnosci_skrot(ox, oy, oz);
					odcz_umiej.push_back(nowa);
				}
			}
			//walki
			odcz_walki.clear();
			koniec = false;
			while (koniec != true) {
				getline(plik, dane_tekstowe);
				if (dane_tekstowe == "BRAK")
					koniec = true;
				else
					odcz_walki.push_back(atoi(dane_tekstowe.c_str()));
			}
			//efekty
			getline(plik, dane_tekstowe);
			if (dane_tekstowe == "BRAK") {
				lista_ef_gracza = nullptr;
				koniec = true;
			}
			else {
				koniec = false;
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
				lista_ef_gracza = nowy_efekt;
				tmp = nowy_efekt;
			}
			while (koniec != true) {
				getline(plik, dane_tekstowe);
				if (dane_tekstowe == "BRAK") {
					koniec = true;
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

			nowy_gracz = new Karta_gracza(nazwa, haslo, pz, max_mana, lvl, EXP, lista_ef_gracza, odcz_umiej, licz_gracz, baza_gr, odcz_walki);	//wewn�trz konstruktora element jest juz dodawany do bazy graczy
			getline(plik, dane_tekstowe);
		}
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"" << nazwa_pliku << "\"";
	}
	plik.close();
}

void odczyt_walki(string nazwa_pliku, map<int, Walka*> &baza_wal, int &licz_walk, map<int, Karta_gracza*> &baza_gr) {
	/*
	Spos�b uporzatkowania pliku wej�ciowego:
	-linia z kilkanastoma znakami
	-numer_walki
	-id_gracz_atakujacy
	-id_gracz_broniacy
	-czy_zaakceptowana
	-tabela umiej�tno�ci 

	a)tabela umiejetno�ci:
	-odczytywana w podw�jnym for'ze
	-wszystkei umiejetno�ci:
	X1
	Y1
	Z1
	X2
	Y2
	Z2
	...
	BRAK
	*/
	
	fstream plik;
	plik.open(nazwa_pliku, ios::in);					//do odczytu
	if (plik.good()) {
		//odczytywanie informacji z plik�w
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"" << nazwa_pliku << "\"";
		//zmienne:
		Karta_gracza *atak, *obronca;
		int ID_walki, ID_atak, ID_obrona, oX, oY, oZ;
		bool czy_zaakceptowana;
		Umiejetnosci_skrot tabelaU[4][6];
		Walka* nowa_walka;
		//
		string dane_tekstowe;
		getline(plik, dane_tekstowe);	//->musimy mie� chocia� jedn� operacj� odczytu
		if (plik.eof())
			cout << "\nPUSTY PLIK";
		while (plik.eof() != true) {
			getline(plik, dane_tekstowe);
			ID_walki = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			ID_atak = atoi(dane_tekstowe.c_str());
			atak = znajdz_gracza(ID_atak, baza_gr);
			getline(plik, dane_tekstowe);
			ID_obrona = atoi(dane_tekstowe.c_str());
			obronca = znajdz_gracza(ID_obrona, baza_gr);
			getline(plik, dane_tekstowe);
			if (dane_tekstowe == "TAK")
				czy_zaakceptowana = true;
			else
				czy_zaakceptowana = false;
			//tablica umiejetnosci
			//mo�liwe s� dwie opcje: tylko gracz atakujacy ustawi� swoje umiejetno�ci, lub obaj gracze ustawili umiej�tnosci
			if (czy_zaakceptowana == true) {	//obaj gracze 
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 6; j++) {
						getline(plik, dane_tekstowe);
						oX = atoi(dane_tekstowe.c_str());
						getline(plik, dane_tekstowe);
						oY = atoi(dane_tekstowe.c_str());
						getline(plik, dane_tekstowe);
						oZ = atoi(dane_tekstowe.c_str());
						tabelaU[i][j] = Umiejetnosci_skrot(oX, oY, oZ);
					}
				}
			}
			else {								//zaakceptowa� tylko atakujacy -> dla obro�cy wpisujemy pierwsz� mo�liw� umiej�tno�� wsz�dzie
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 6; j++) {
						getline(plik, dane_tekstowe);
						oX = atoi(dane_tekstowe.c_str());
						getline(plik, dane_tekstowe);
						oY = atoi(dane_tekstowe.c_str());
						getline(plik, dane_tekstowe);
						oZ = atoi(dane_tekstowe.c_str());
						tabelaU[i][j] = Umiejetnosci_skrot(oX, oY, oZ);
					}
				}
				for (int i = 2; i < 4; i++) {
					for (int j = 0; j < 6; j++) {
						tabelaU[i][j] = Umiejetnosci_skrot(0,0,0);		//wpisujemy dowolne umiej�tno�ci
					}
				}
			}
			nowa_walka = new Walka(*atak, *obronca, licz_walk, baza_wal, tabelaU);
			getline(plik, dane_tekstowe);
		}
	}
	else{
		cout << "\nBRAK DOSTEPU DO PLIKU \"" << nazwa_pliku << "\"";
	}
	plik.close();
}

Karta_gracza* znajdz_gracza(int numer_gracza, map<int, Karta_gracza*> baza_gr) {
	bool znaleziony = false;
	map<int, Karta_gracza*>::iterator it;
	it = baza_gr.begin();
	while (znaleziony != true) {
		if (it->second->zwroc_ID() == numer_gracza) {
			znaleziony = true;
		}
		else {
			it++;
		}
	} 
	return it->second;
}

//funkcje -> do zapisania na p�niej
void czekaj(int sekundy) {
	typedef long clock_t;
	clock_t koniec = clock() + sekundy * CLOCKS_PER_SEC;
	while (clock() < koniec)
		continue;
}
std::string szyfruj(std::string tekst, int klucz, string klucz2) {
	string zaszyfrowane = "", pomocnicza = "", koncowka = "", bit_row, prefiks;
	int znak;
	for (int i = 0; i < tekst.length(); i++) {
		znak = tekst[i] + klucz;						//kodowanie ka�dego znaku szyfrem cezara
		bit_row = DecnaBin(znak);						//zamiana 'tekst' na ci�g znak�w binarnych
		if (bit_row.length() < 8) {
			prefiks = "";
			for (int j = bit_row.length(); j < 8; j++) {
				prefiks = "0" + prefiks;
			}
			bit_row = prefiks + bit_row;				//dopisanie tylu zer na pocz�tku, aby ka�dy znak by� zapisany na 8 bitach
		}
		zaszyfrowane = zaszyfrowane + bit_row;
	}
		//przyk�ad klucza2: 1011 -> 4 cyfry.
		//szyfrowanie XOR -> 1010 + 1011 = 0001
		//podzia� tekstu na czlony 4-literowe.

		//szyfrowanie XOR
	znak = zaszyfrowane.length() % 4;
	for (int i = zaszyfrowane.length() - znak; i < zaszyfrowane.length(); i++) {
		koncowka = koncowka + zaszyfrowane[i];			//po dodaniu podzia�u na 8 bit�w ka�de s�owo nie jest to ju� wymagane... ale zostawiam, bo mo�e kiedy� b�dzie trzeba przerobi� na np. 9 bit�w.
	}
	for (int i = 0; i < (zaszyfrowane.length() / 4); i++) {
		if (zaszyfrowane[4 * i] == klucz2[0])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (zaszyfrowane[4 * i + 1] == klucz2[1])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (zaszyfrowane[4 * i + 2] == klucz2[2])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (zaszyfrowane[4 * i + 3] == klucz2[3])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
	}
	zaszyfrowane = pomocnicza + koncowka;

	//szyfrowanie XOR - koniec

	return zaszyfrowane;
}
std::string deszyfruj(std::string szyfrowana, int klucz, string klucz2) {	//do doko�czenia
	string odszyfrowane = "", koncowka = "", pomocnicza = "";
	int znak;
	char znakch;
	//deszyfracja XOR
	znak = szyfrowana.length() % 4;
	for (int i = szyfrowana.length() - znak; i < szyfrowana.length(); i++) {
		koncowka = koncowka + szyfrowana[i];			//po dodaniu podzia�u na 8 bit�w ka�de s�owo nie jest to ju� wymagane... ale zostawiam, bo mo�e kiedy� b�dzie trzeba przerobi� na np. 9 bit�w.
	}
	for (int i = 0; i < (szyfrowana.length() / 4); i++) {
		if (szyfrowana[4 * i] == klucz2[0])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (szyfrowana[4 * i + 1] == klucz2[1])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (szyfrowana[4 * i + 2] == klucz2[2])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (szyfrowana[4 * i + 3] == klucz2[3])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
	}
	szyfrowana = pomocnicza + koncowka;

	//deszyfracja XOR - koniec

	//szyfr sk��da si� z pewnej liczby znak�w zaszyfrowanych kodem ACII na binarnym po 8 bit�w ka�dy.

	try {
		if ((szyfrowana.length() % 8) != 0)
			throw "\nBLAD SZYFROWANIA!";
		for (int i = 0; i < (szyfrowana.length() / 8); i++) {		//jest podzielne przez 8
			pomocnicza = "";
			for (int j = 0; j < 8; j++) {
				pomocnicza = pomocnicza + szyfrowana[8 * i + j];
			}
			znak = BinnaDec(pomocnicza);
			znak = znak - klucz;
			znakch = znak;
			odszyfrowane = odszyfrowane + znakch;
			//znak = szyfrowana[i] - klucz;
		}

	}
	catch (string w) {
		cout << w;
		return "BLAD";
	}

	return odszyfrowane;
}
std::string DecnaBin(int liczbaDec) {
	if (liczbaDec == 0) 
		return "0";
	if (liczbaDec == 1) 
		return "1";

	if (liczbaDec % 2 == 0)
		return DecnaBin(liczbaDec / 2) + "0";
	else
		return DecnaBin(liczbaDec / 2) + "1";
}
int BinnaDec(std::string liczbaBin) {
	int result = 0, pow = 1;
	for (int i = liczbaBin.length() - 1; i >= 0; --i, pow <<= 1)
		result += (liczbaBin[i] - '0') * pow;

	return result;
}

//�MIETNIK:
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


string testowa = "Aa15@", pom;
pom = szyfruj(testowa, 8, "1011");
cout << pom << "\n" << deszyfruj(pom, 8, "1011");

czekaj(20);



*/
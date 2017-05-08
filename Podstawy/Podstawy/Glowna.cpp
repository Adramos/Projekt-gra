#include <iostream>
#include <ctime>
#include <fstream>
#include "Walka.h"

using namespace std;

//deklaracje funkcji

void czekaj(int);		 //funckja s�u�y do zatrzymania programu na 'n' sekund
void wypisz_walki(std::list<int> walki_gracza, std::map<int, Walka*> wszystkie_walki);


//funkcja main

int main() {
	std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiejestosci;
	std::map<int, Karta_gracza*> baza_gracze;	
	//std::set<int> zalogowani_gracze;	-> na przysz�o��
	std::map<int, Walka*> baza_walki;
	int ostatni_gracz = 0, ostatnia_walka = 0;
	fstream plik_umiejetnosci, plik_gracze, plik_walki;
	plik_umiejetnosci.open("baza umiejetnosci.txt", ios::out);		//do odczytu
	if (plik_umiejetnosci.good()) {
		//odczytywanie informacji z plik�w
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"baza umiejetnosci.txt\".";
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"baza umiejetnosci.txt\".";
	}
	plik_umiejetnosci.close();
	plik_gracze.open("baza gracze.txt", ios::out);					//do odczytu
	if (plik_gracze.good()) {
		//odczytywanie informacji z plik�w
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"baza gracze.txt\".";
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"baza gracze.txt\".";
	}
	plik_gracze.close();

	plik_walki.open("baza walki.txt", ios::out);					//do odczytu
	if (plik_walki.good()) {
		//odczytywanie informacji z plik�w
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





*/
#ifndef Karta_gracza_h
#define Karta_gracza_h
#include "Umiejetnosci.h"
#include <map>



class Karta_gracza {
private:
	std::string nick;
	int max_pz, mana, akt_lvl, PD;
	std::list<Umiejetnosci_skrot> umiejetnosci_gracza;		//jest to wskaŸnik na pocz¹tek listy umiejêtnoœci gracza -> bêd¹ tu przechowywane 
	Efekty* lista_efektow_gracza;
	int numer_identyfikacyjny;
	std::list<int> walki_gracza;						//lista numerów ID trwajacych walk gracza

public:
	void dodaj_umiej(Umiejetnosci dodawana);	//wstawia now¹ umiejêstnoœæ (Umiejetnosci_skrot) w odpowiednim miejscu (sortowanie przy wstawianiu) na liœcie umiejestoœci gracza (umiejetnosci_gracza)
	Umiejetnosci zwroc_umiej(Umiejetnosci_skrot szukana, std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej);	//UWAGA: BY£A MODYFIKOWANA
																																								//	karta gracza jest tworzona dla ka¿dej postaci w dwóch formach:
	Karta_gracza(std::string nazwa, std::list<Umiejetnosci_skrot> bazowe_umiej, int& ostatni_numer, std::map<int, Karta_gracza*> &baza_gracze);																				//	a)pocz¹tkowa (tylko nick, reszta bazowe wartoœci),
	Karta_gracza(std::string nazwa, int max_hp, int akt_mana, int akt_poziom, int akt_PD, Efekty* lista_gracza, std::list<Umiejetnosci_skrot> umiej_gracza, int& ostatni_numer, std::map<int, Karta_gracza*> &baza_gracze, std::list<int> wczesniejsze_walki_gracza);	//  b)z bazy danych (potrzebne wszystkei dane),
	Karta_gracza(Karta_gracza &kopiowana);																														//	c)jako kopia istniej¹cego elementu (konstruktor kopiuj¹cy).
	Karta_gracza() {}
	~Karta_gracza();

	void wypisz_wszystkie_umiejetnosci(std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej);
	bool czy_posiada(int id_x, int poziom_y, int rodzaj_z);		//gracz posiada do oko³o 20 umiejetnosci -> wyszukiwanie w czasie liniowym nie jest problemem
	void dodaj_walke(int id_walki);
	std::list<int> zwroc_liste_walk();
	std::string zwroc_nick();
};

#endif

//Z powodu korelacji obu plików (Karta_gracza + Walka) obie klasy zostaj¹ w³o¿one do jednego pliku (Karta_gracza) =?wrong idea
//Walka* odszukaj_walke(int numer_walki, std::map<int, Walka*> baza_walki);	//definicja w pliku: "Walka.cpp"		//trzeba to przerobiæ
//void dodaj_walke(Walka* nowa_walka);
//void test();
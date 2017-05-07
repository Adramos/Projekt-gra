#ifndef Umiejetnosci_h
#define Umiejetnosci_h
#include "Efekty.h"
#include <vector>
#include <list>
#include <iterator>

/*
Obiekty klasy Umiejêtnoœci bêd¹ zawiera³y ca³¹ masê pól odpowiedzialnych za parametry. Bêd¹ one przechowywane w tablicy dwuwymairowej{UWAGA! TRÓJWYMIAROWEJ} (wekrot dwuwymiarowy{TRÓJWYMIAROWY}). 
Ka¿da umiejêtnoœæ bêdzie posaida³a numer ID, który bêdzie definiowa³ kolumne, oraz POZIOM definiuj¹cy wiersz. {KA¯DA "G£ÊBOKOŒÆ" BÊDZIE OZNACZA£A INNY RODZAJ UMIEJÊTNOŒCI -> OKREŒLANY PRZEZ PARAMETR "RODZAJ}
Taki zbiór danych NIE BÊDZIE podlega³ modyfikacji z poziomu gry -> na pocz¹tku bêdzie tworzona w funkcji main jedna wspólna struktura, do której bêd¹ wpisywane z pliku/bazy danych umiejêtnoœci w odpowiednich miejscach. 
W trakcie gry ka¿dy gracz bêdzie posaida³ prywatn¹ listê umiejêtnoœci wraz z ich poziomami -> to bêdzie okreœlaæ co jest dostêpne. W trakcie walki zostan¹ spisane odpowiednie parametry i 
zostanie utworzona lista ustawionych przez ka¿dego gracza umiejêtnoœci -> kopia umiejêtnoœci z g³ównej struktury.

Rodzaje umiejêtnoœci: 
0-SILNY ATAK
1-SZYBKI ATAK
2-MAGICZNY ATAK
3-SILNA OBRONA
4-SZYBKA OBRONA
5-MAGICZNA OBRONA
6-SPECJALNE ->bêd¹ dopiero dodawane

baza_umiejetnosci[ID][poziom][rodzaj]

*/

class Umiejetnosci {
protected:
	int ID;
	std::string nazwa, opis;
	int rodzaj, poziom;
	//char typ_umiejetnosci;		//S-silny, F-szybki, M-magiczny
	//int wartosc;					//ile obra¿eñ/ile ochrony
public:
	Efekty* lista_efektow;			//lista efektów aktywowanych w trakcie u¿ycia umiejêtnoœci
	Umiejetnosci(int numer, int typ, int lvl, std::string nazwa_um, std::string opis_um, Efekty* lista_ef);
	~Umiejetnosci();
	int zwroc_ID();
	int zwroc_poziom();
	int zwroc_rodzaj();
	virtual void wypisz_informacje();
};

class Umiejetnosci_ofensywne : public Umiejetnosci{
private:
	int obrazenia;
public:
	Umiejetnosci_ofensywne(int numer, int typ, int lvl, std::string nazwa_um, std::string opis_um, Efekty* lista_ef, int dmg);
	int zwroc_obazenia();
	void wypisz_informacje();
};

class Umiejetnosci_defensywne : public Umiejetnosci {
private:
	int obrona_S, obrona_F, obrona_M;
public:
	Umiejetnosci_defensywne(int numer, int typ, int lvl, std::string nazwa_um, std::string opis_um, Efekty* lista_ef, int obrona_silna, int obrona_szybka, int obrona_magiczna);
	void wypisz_informacje();
};

class Umiejetnosci_skrot {
private:
	int ID, rodzaj, poziom;
public:
	Umiejetnosci_skrot(int numerID, int lvl, int typ);		//kolejnoœæ: x, y, z
	Umiejetnosci_skrot(){}
	int zwroc_ID();
	int zwroc_poziom();
	int zwroc_rodzaj();
	void wypisz_pojedyncza(std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej);
};

#endif

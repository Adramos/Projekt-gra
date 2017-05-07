#ifndef Umiejetnosci_h
#define Umiejetnosci_h
#include "Efekty.h"
#include <vector>
#include <list>
#include <iterator>

/*
Obiekty klasy Umiej�tno�ci b�d� zawiera�y ca�� mas� p�l odpowiedzialnych za parametry. B�d� one przechowywane w tablicy dwuwymairowej{UWAGA! TR�JWYMIAROWEJ} (wekrot dwuwymiarowy{TR�JWYMIAROWY}). 
Ka�da umiej�tno�� b�dzie posaida�a numer ID, kt�ry b�dzie definiowa� kolumne, oraz POZIOM definiuj�cy wiersz. {KA�DA "G��BOKO��" B�DZIE OZNACZA�A INNY RODZAJ UMIEJ�TNO�CI -> OKRE�LANY PRZEZ PARAMETR "RODZAJ}
Taki zbi�r danych NIE B�DZIE podlega� modyfikacji z poziomu gry -> na pocz�tku b�dzie tworzona w funkcji main jedna wsp�lna struktura, do kt�rej b�d� wpisywane z pliku/bazy danych umiej�tno�ci w odpowiednich miejscach. 
W trakcie gry ka�dy gracz b�dzie posaida� prywatn� list� umiej�tno�ci wraz z ich poziomami -> to b�dzie okre�la� co jest dost�pne. W trakcie walki zostan� spisane odpowiednie parametry i 
zostanie utworzona lista ustawionych przez ka�dego gracza umiej�tno�ci -> kopia umiej�tno�ci z g��wnej struktury.

Rodzaje umiej�tno�ci: 
0-SILNY ATAK
1-SZYBKI ATAK
2-MAGICZNY ATAK
3-SILNA OBRONA
4-SZYBKA OBRONA
5-MAGICZNA OBRONA
6-SPECJALNE ->b�d� dopiero dodawane

baza_umiejetnosci[ID][poziom][rodzaj]

*/

class Umiejetnosci {
protected:
	int ID;
	std::string nazwa, opis;
	int rodzaj, poziom;
	//char typ_umiejetnosci;		//S-silny, F-szybki, M-magiczny
	//int wartosc;					//ile obra�e�/ile ochrony
public:
	Efekty* lista_efektow;			//lista efekt�w aktywowanych w trakcie u�ycia umiej�tno�ci
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
	Umiejetnosci_skrot(int numerID, int lvl, int typ);		//kolejno��: x, y, z
	Umiejetnosci_skrot(){}
	int zwroc_ID();
	int zwroc_poziom();
	int zwroc_rodzaj();
	void wypisz_pojedyncza(std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej);
};

#endif

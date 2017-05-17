#ifndef Efekty_h
#define Efekty_h
#include <iostream>
#include <string>

//Efekty bêd¹ przechowywane w liœcie podczepianej do odpowiedniego gracza. Gdy jakiœ efekt zostaje wykorzystany dekrementuje siê jego licznik (o ile nie jest to efekt sta³y -> licznik = 8)
//Efekt, którego czas_trwania = 0 zostaje usuniety z listy. Je¿eli efekt ma np. odj¹æ 5 ptk pancerza, to wartosc bêdzie ujemna (-5)

class Efekty {
private:
	std::string nazwa, tekst;			//nazwa - nazwa efektu; tekst - opis s³owny dzia³ania efektu
	int wartosc, czas_trwania;			//wartoœæ - iloœæ punktów dopisywanych/odejmowanych od odpowiedniej akcji; czas_trwania - okreœla ile czasu trwa dany efekt -> ile tur (8=efekt trwa³y)
	char typ;							//typ - dziêki niemu mo¿na zczytaj jakiego rodzaju jest effekt (np: O -> dodaj "wartosc" do obra¿eñ ataku)

										/*LISTA TYPÓW EFEKTÓW		(wartosc bêdzie dalej jako "modyfikator")
										O-dodaj modyfikator do obra¿eñ ataku
										D-dodaj modyfikator do wartoœci obrony celu
										P-dodaj wartosc do pancerza
										K-dodaj wartosc do szansy na trafienie krytyczne 
										B-dodaj wartosc do obrony krytycznej celu
										T-zadaj pod koniec tury obrazenia równe modyfikatorowi
										//X-wszystkie efekty (np. "Zwiêksza czas trwania WSZYSKICH aktywnych efektów o 1 turê")//pomys³ chwilowo wyrzucony
										*/
	bool cel_wrog;						//cel = true->efekt zostaje przypisany wrogowi, cel = false->efekt zostaje przypisany graczowi
public:
	Efekty* nast;
	Efekty();
	Efekty(std::string nazwa_ef, std::string tekst_ef, int wart, int czas, char rodzaj, bool cel);
	int modyfikuj(int& wart_pierw);
	void sktoc_trwanie();
	void sktoc_trwanie(int czas);
	int aktywuj_efekty(Efekty* pocz, char rodzaj);
	void skasuj_liste();
	bool jaki_cel();
	~Efekty();					//usuwa POJEDYNCZY element z listy -> BEZ jej kontynualcji
	void wypisz_informacje();
	char zwroc_typ();
	int zwroc_modyfikator();
	void wypisz_liste_efektow(Efekty* pocz_listy);
	void badaj_trwanie(Efekty* pocz_listy);
	int zwroc_czas();
	std::string zwroc_nazwa();
	std::string zwroc_opis();
};

#endif

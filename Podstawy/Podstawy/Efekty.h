#ifndef Efekty_h
#define Efekty_h
#include <iostream>
#include <string>

//Efekty b�d� przechowywane w li�cie podczepianej do odpowiedniego gracza. Gdy jaki� efekt zostaje wykorzystany dekrementuje si� jego licznik (o ile nie jest to efekt sta�y -> licznik = 8)
//Efekt, kt�rego czas_trwania = 0 zostaje usuniety z listy. Je�eli efekt ma np. odj�� 5 ptk pancerza, to wartosc b�dzie ujemna (-5)

class Efekty {
private:
	std::string nazwa, tekst;			//nazwa - nazwa efektu; tekst - opis s�owny dzia�ania efektu
	int wartosc, czas_trwania;			//warto�� - ilo�� punkt�w dopisywanych/odejmowanych od odpowiedniej akcji; czas_trwania - okre�la ile czasu trwa dany efekt -> ile tur (8=efekt trwa�y)
	char typ;							//typ - dzi�ki niemu mo�na zczytaj jakiego rodzaju jest effekt (np: O -> dodaj "wartosc" do obra�e� ataku)

										/*LISTA TYP�W EFEKT�W		(wartosc b�dzie dalej jako "modyfikator")
										O-dodaj modyfikator do obra�e� ataku
										P-dodaj wartosc do pancerza
										K-dodaj wartosc do szansy na trafienie krytyczne 
										B-dodaj wartosc do obrony krytycznej celu
										T-zadaj pod koniec tury obrazenia r�wne modyfikatorowi
										//X-wszystkie efekty (np. "Zwi�ksza czas trwania WSZYSKICH aktywnych efekt�w o 1 tur�")//pomys� chwilowo wyrzucony
										*/
public:
	Efekty* nast;
	Efekty();
	Efekty(std::string nazwa_ef, std::string tekst_ef, int wart, int czas, char rodzaj);
	int modyfikuj(int wart_pierw);
	void sktoc_trwanie();
	void sktoc_trwanie(int czas);
	int aktywuj_efekty(Efekty* pocz, char rodzaj);
	void skasuj_liste();
	~Efekty();
};

#endif

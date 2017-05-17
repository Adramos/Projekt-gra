#include "Efekty.h"

Efekty::Efekty():
nazwa("BRAK"), tekst("BRAK OPISU"), wartosc(0), czas_trwania(0), typ('X'), nast(nullptr), cel_wrog(false)
{}

Efekty::Efekty(std::string nazwa_ef, std::string tekst_ef, int wart, int czas, char rodzaj, bool cel) {
	nazwa = nazwa_ef;
	tekst = tekst_ef;
	wartosc = wart;
	czas_trwania = czas;
	typ = rodzaj;
	cel_wrog = cel;
	nast = nullptr;
}

Efekty::~Efekty() {
}

int Efekty::modyfikuj(int& wart_pierw) {
	wart_pierw = wart_pierw + this->wartosc;
	this->sktoc_trwanie();
	return wart_pierw;
}

void Efekty::sktoc_trwanie() {
	if(this->czas_trwania!=8)
		this->czas_trwania--;
}

void Efekty::sktoc_trwanie(int czas) {
	if (this->czas_trwania != 8)
		this->czas_trwania = this->czas_trwania + czas;		//w przypadku dodatniego "czas" wartosc siê wyd³u¿y
}

int Efekty::aktywuj_efekty(Efekty* pocz, char rodzaj) {		//pocz->pocz¹tek listy efektów; rodzaj->typ szukanego modyfikatora; Zwraca modyfikator danego rodzaju z ca³ej listy Efektów
	int modyfikator = 0;
	Efekty* tmp = pocz, *tmp2;
	while (tmp!=nullptr) {
		if (tmp->typ == rodzaj) {
			modyfikator = tmp->modyfikuj(modyfikator);
			tmp2 = tmp;
			tmp = tmp->nast;
			tmp2->badaj_trwanie(pocz);
		}
		else {
			tmp = tmp->nast;
		}
	}

	return modyfikator;
}

void Efekty::skasuj_liste() {
	if (this != nullptr) {
		if (this->nast != nullptr)
			this->nast->skasuj_liste();
		delete this;
	}
}

bool Efekty::jaki_cel() {
	return this->cel_wrog;
}

void Efekty::wypisz_informacje() {
	std::cout << "\n" << this->nazwa << "\n" << this->tekst;
	std::cout << "\nCEL: ";
	if (this->jaki_cel())
		std::cout << "WROG";
	else
		std::cout << "GRACZ";
}
char Efekty::zwroc_typ() {
	return this->typ;
}

int Efekty::zwroc_modyfikator() {
	return this->wartosc;
}

void Efekty::wypisz_liste_efektow(Efekty* pocz_listy) {
	if (pocz_listy) {
		Efekty* tmp = pocz_listy;
		while (tmp != nullptr) {
			tmp->wypisz_informacje();
			tmp = tmp->nast;
		}
	}
	else{
		std::cout << "\nBRAK EFEKTOW";
	}
}

int Efekty::zwroc_czas() {
	return this->czas_trwania;
}

void Efekty::badaj_trwanie(Efekty* pocz_listy) {
	if (this->zwroc_czas() <= 0) {
		Efekty* tmp = pocz_listy;
		if (tmp == this) {
			pocz_listy = tmp->nast;
			delete this;
		}
		else {
			while (tmp->nast != this) {
				tmp = tmp->nast;
			}
			tmp->nast = this->nast;
			delete this;
		}
	}
}

std::string Efekty::zwroc_nazwa() {
	return this->nazwa;
}

std::string Efekty::zwroc_opis() {
	return this->tekst;
}
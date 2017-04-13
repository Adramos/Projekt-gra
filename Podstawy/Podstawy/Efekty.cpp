#include "Efekty.h"

Efekty::Efekty():
nazwa("BRAK"), tekst("BRAK OPISU"), wartosc(0), czas_trwania(0), typ('X'), nast(nullptr)
{}

Efekty::Efekty(std::string nazwa_ef, std::string tekst_ef, int wart, int czas, char rodzaj) {
	nazwa = nazwa_ef;
	tekst = tekst_ef;
	wartosc = wart;
	czas_trwania = czas;
	typ = rodzaj;
	nast = nullptr;
}

Efekty::~Efekty() {
}

int Efekty::modyfikuj(int wart_pierw) {
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

int Efekty::aktywuj_efekty(Efekty* pocz, char rodzaj) {
	int modyfikator = 0;
	Efekty* tmp = pocz;
	while (tmp!=nullptr) {
		if (tmp->typ == rodzaj)
			modyfikator = tmp->modyfikuj(modyfikator);
	}

	return modyfikator;
}

void Efekty::skasuj_liste() {
	if (this->nast != nullptr)
		this->nast->skasuj_liste();
	delete this;
}
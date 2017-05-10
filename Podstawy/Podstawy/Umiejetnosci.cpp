#include "Umiejetnosci.h"

Umiejetnosci::Umiejetnosci(int numer, int lvl, int typ, std::string nazwa_um, std::string opis_um, Efekty* lista_ef) :
	ID(numer),
	poziom(lvl),
	rodzaj(typ),
	nazwa(nazwa_um),
	opis(opis_um),
	lista_efektow(lista_ef)
{}

Umiejetnosci_ofensywne::Umiejetnosci_ofensywne(int numer, int lvl, int typ, std::string nazwa_um, std::string opis_um, Efekty* lista_ef, int dmg):
	Umiejetnosci(numer, lvl, typ, nazwa_um, opis_um, lista_ef),
	obrazenia(dmg)
{}

Umiejetnosci_defensywne::Umiejetnosci_defensywne(int numer, int lvl, int typ, std::string nazwa_um, std::string opis_um, Efekty* lista_ef, int obrona_silna, int obrona_szybka, int obrona_magiczna):
	Umiejetnosci(numer, lvl, typ, nazwa_um, opis_um, lista_ef),
	obrona_S(obrona_silna),
	obrona_F(obrona_szybka),
	obrona_M(obrona_magiczna)
{}

Umiejetnosci::~Umiejetnosci() {
	this->lista_efektow->skasuj_liste();		//podaj¹c pierwszy element z listy usuwamy ca³¹ listê poprzez rekurencyjn¹ metodê "skasuj_liste()"
}

Umiejetnosci_skrot::Umiejetnosci_skrot(int numerID, int lvl, int typ) {
	ID = numerID;
	poziom = lvl;
	rodzaj = typ;
}

int Umiejetnosci::zwroc_ID() {
	return this->ID;
}
int Umiejetnosci::zwroc_poziom() {
	return this->poziom;
}
int Umiejetnosci::zwroc_rodzaj() {
	return this->rodzaj;
}

int Umiejetnosci_skrot::zwroc_ID() {
	return this->ID;
}
int Umiejetnosci_skrot::zwroc_poziom() {
	return this->poziom;
}
int Umiejetnosci_skrot::zwroc_rodzaj() {
	return this->rodzaj;
}

void Umiejetnosci::wypisz_informacje() {
	std::cout << "\n" << this->nazwa << "\nID: " << this->zwroc_ID() << "\nRODZAJ: ";
	switch (this->rodzaj) {
	case 0:
		std::cout << "SILNY - ATAK";
		break;
	case 1:
		std::cout << "SZYBKI - ATAK";
		break;
	case 2:
		std::cout << "MAGICZNY - ATAK";
		break;
	case 3:
		std::cout << "SILNY - OBRONA";
		break;
	case 4:
		std::cout << "SZYBKI - OBRONA";
		break;
	case 5:
		std::cout << "MAGICZNY - OBRONA";
		break;
	case 6:
		std::cout << "SPECJALNE";
		break;
	default:
		std::cout << "NIEWLASCIWY RODZAJ";
	}
	std::cout << "\nPOZIOM: " << this->poziom + 1 << "\n" << this->opis;
	std::cout << "\n=====\n"; 
	this->lista_efektow->wypisz_liste_efektow(this->lista_efektow);
}
void Umiejetnosci_ofensywne::wypisz_informacje() {	
		std::cout << "\n" << this->nazwa << "\nID: " << this->zwroc_ID()  << "\nRODZAJ: ";
		switch (this->rodzaj) {
		case 0:
			std::cout << "SILNY - ATAK";
			break;
		case 1:
			std::cout << "SZYBKI - ATAK";
			break;
		case 2:
			std::cout << "MAGICZNY - ATAK";
			break;
		case 3:
			std::cout << "SILNY - OBRONA";
			break;
		case 4:
			std::cout << "SZYBKI - OBRONA";
			break;
		case 5:
			std::cout << "MAGICZNY - OBRONA";
			break;
		case 6:
			std::cout << "SPECJALNE";
			break;
		default:
			std::cout << "NIEWLASCIWY RODZAJ";
		}
		std::cout << "\nPOZIOM: " << this->poziom + 1 << "\n" << this->opis;
		std::cout << "\nOBRAZENIA:\t" << this->obrazenia;
		std::cout << "\n=====\n";
		this->lista_efektow->wypisz_liste_efektow(this->lista_efektow);
}
void Umiejetnosci_defensywne::wypisz_informacje() {
	std::cout << "\n" << this->nazwa << "\nID: " << this->zwroc_ID()  << "\nRODZAJ: ";
	switch (this->rodzaj) {
	case 0:
		std::cout << "SILNY - ATAK";
		break;
	case 1:
		std::cout << "SZYBKI - ATAK";
		break;
	case 2:
		std::cout << "MAGICZNY - ATAK";
		break;
	case 3:
		std::cout << "SILNY - OBRONA";
		break;
	case 4:
		std::cout << "SZYBKI - OBRONA";
		break;
	case 5:
		std::cout << "MAGICZNY - OBRONA";
		break;
	case 6:
		std::cout << "SPECJALNE";
		break;
	default:
		std::cout << "NIEWLASCIWY RODZAJ";
	}
	std::cout << "\nPOZIOM: " << this->poziom + 1 << "\n" << this->opis;
	std::cout << "\nOBRONA SILNY:\t\t" << this->obrona_S;
	std::cout << "\nOBRONA SZYBKI:\t\t" << this->obrona_F;
	std::cout << "\nOBRONA MAGICZNY:\t" << this->obrona_M;
	std::cout << "\n=====\n";
	this->lista_efektow->wypisz_liste_efektow(this->lista_efektow);
}
void Umiejetnosci_skrot::wypisz_pojedyncza(std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej) {
	baza_umiej[this->zwroc_ID()][this->zwroc_poziom()][this->zwroc_rodzaj()]->wypisz_informacje();
}

int Umiejetnosci_ofensywne::zwroc_obazenia() {
	return this->obrazenia;
}
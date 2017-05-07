#include "Karta_gracza.h"

//KARTA GRACZA

void Karta_gracza::dodaj_umiej(Umiejetnosci dodawana) {
	int x, y, z;			//warto�ci odpowiadaj�po�o�eniu danej umiej�tno�ci w wektorze tr�jwymiarowym -> x = ID, y = poziom, z = rodzaj
	x = dodawana.zwroc_ID();
	y = dodawana.zwroc_poziom();
	z = dodawana.zwroc_rodzaj();
	Umiejetnosci_skrot nowa = Umiejetnosci_skrot(x, y, z);
	//this->umiejetnosci_gracza.push_back(nowa);			//tak wygl�da dodawanie elementu NIEPOSORTOWANEGO
	//mo�naby tu dokona� sortowania element�w w celu ich p�niejszej, prostszej obs�ugi
	//dlaczego nie 'sort'? Bo nie trzeba sortowa� ka�dorazowo ca�ej listy, je�li tylko jeden element jest nie na swoim miejscu
	/*
	-Ka�dy gracz mo�e posiada� umiej�tno�� o tym samym ID oraz rodzaju tylko na jednym poziomie, tak�e sortowanie ze wzgl�du na Y nie ma sensu
	-G��wnym parametrem sortowania jest Z -> przypominam:
	0-SILNY ATAK
	1-SZYBKI ATAK
	2-MAGICZNY ATAK
	3-SILNA OBRONA
	4-SZYBKA OBRONA
	5-MAGICZNA OBRONA
	6-SPECJALNE
		a wi�c im mneijszy rodzaj tym bli�ej do pocz�tku listy
	-Im mniejsze ID tym bli�ej pocz�tku listy 
	Przyka�dy:
	a)(10,2,3) , (10,2,1)		-> pierwsze b�dzie (10,2,1)
	b)(2,4,5) , (4,4,5)			-> pierwsze b�dzie (2,4,5)
	c)(1,3,2) , (1,1,2)			-> sytuacja niedopuszczalna! Gracz nei mo�e mie� na raz tej samej umiejetno�ci pierwszego i trzeciego poziomu!
	*/
	std::list<Umiejetnosci_skrot>::iterator it;
	
	if (this->umiejetnosci_gracza.empty()) {
		this->umiejetnosci_gracza.push_front(nowa);
	}
	else {
		it = this->umiejetnosci_gracza.begin();
		while (it->zwroc_rodzaj() < z && it != this->umiejetnosci_gracza.end()) {
			it++;
		}
		//w tym miejscu iterator wskazuje na pierwszy element o r�wnym, lub wi�kszym rodzaju, ALBO na koniec listy
		if (it == this->umiejetnosci_gracza.end()) {
			this->umiejetnosci_gracza.push_back(nowa);	//je�li itereator pokazuje na koniec -> nie istnieje jeszcze element o takim rodzaju, ani �adnym wi�kszym rodzaju -> dodajemy na koniec listy
		}
		else if (it->zwroc_rodzaj() > z) {		//rodzaj iteratora jest wi�kszy <=> nie istnieje jeszcze �aden element o podanym rodzaju -> musimy doda� nasz nowy element przed iterator -> 'insert'
			this->umiejetnosci_gracza.insert(it, nowa);		//dwuargumentowy insert wstawia element (drugi parametr) PRZED wskazany element (pierwszy element) -> (a, b, c, IT, d, e) + insert(it, nowa) = a, b, c, nowa, IT, d, e)
		}
		else {		//element ma ten sam rodzaj -> teraz sortujemy po x
			while (it->zwroc_ID() > x && it->zwroc_rodzaj() == z && it != this->umiejetnosci_gracza.end() ) {	//moz�iwe przypadki: wstawiamy na pocz�tek listy ID, w �rodek listy ID, na ko�cu listy ID (albo wi�kszy rodzaj, albo koniec listy)
				it++;
			}
			//tutaj mamy ustawiony iterator w miejscu, kt�re przed kt�rym powinni�my wstawi� nowy element -> znowu insert, ale ju�bez rozpatrywania przypadk�w
			this->umiejetnosci_gracza.insert(it, nowa);
		}
	}
	/*
	Uwagi ko�cowe: mo�e si� wydawa�, i� metoda wykonuje si� d�ugo. Po cz�ci jest to prawda, lecz teraz musimy si� nam�czy� wstawiaj�c nowe elementy (pocz�tek i RZADKO p�niej),
	aby p�niej szybciej m�c wyszukiwa� odpowiednie elementy (do�� cz�sto)
	*/
}

Umiejetnosci Karta_gracza::zwroc_umiej(Umiejetnosci_skrot szukana, std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej) {
	return *baza_umiej[szukana.zwroc_ID()][szukana.zwroc_poziom()][szukana.zwroc_rodzaj()];
}

Karta_gracza::Karta_gracza(std::string nazwa, std::list<Umiejetnosci_skrot> bazowe_umiej, int& ostatni_numer, std::map<int, Karta_gracza*> &baza_gracze) {
	nick = nazwa;
	akt_lvl = 1;
	max_pz = 20;
	mana = 5;
	lista_efektow_gracza = nullptr;
	umiejetnosci_gracza = bazowe_umiej;
	ostatni_numer++;
	numer_identyfikacyjny = ostatni_numer;
	baza_gracze.emplace(ostatni_numer, this);
}

Karta_gracza::Karta_gracza(std::string nazwa, int max_hp, int akt_mana, int akt_poziom, int akt_PD, Efekty* lista_gracza, std::list<Umiejetnosci_skrot> umiej_gracza, int& ostatni_numer, std::map<int, Karta_gracza*> &baza_gracze, std::list<int> wczesniejsze_walki_gracza) {
	nick = nazwa;
	max_pz = max_hp;
	mana = akt_mana;
	akt_lvl = akt_poziom;
	PD = akt_PD;
	lista_efektow_gracza = lista_gracza;
	umiejetnosci_gracza = umiej_gracza;
	ostatni_numer++;
	numer_identyfikacyjny = ostatni_numer;	
	walki_gracza = wczesniejsze_walki_gracza;
	baza_gracze.emplace(ostatni_numer, this);
}

Karta_gracza::Karta_gracza(Karta_gracza &kopiowana) {
	nick = kopiowana.nick;
	max_pz = kopiowana.max_pz;
	mana = kopiowana.mana;
	akt_lvl = kopiowana.akt_lvl;
	PD = kopiowana.PD;
	lista_efektow_gracza = kopiowana.lista_efektow_gracza;
	umiejetnosci_gracza = kopiowana.umiejetnosci_gracza;
	numer_identyfikacyjny = kopiowana.numer_identyfikacyjny;
}

void Karta_gracza::wypisz_wszystkie_umiejetnosci(std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej) {
	//Umiejetnosci_skrot* tmp = this->umiejetnosci_gracza;
	if (this->umiejetnosci_gracza.empty() != false) {
		std::list<Umiejetnosci_skrot>::iterator it;
		it = this->umiejetnosci_gracza.begin();
		while (it != this->umiejetnosci_gracza.end()) {
			it->wypisz_pojedyncza(baza_umiej);
			std::cout << "\n\n********************";
		}
	}
	else {
		std::cout << "\nBRAK UMIEJETNOSCI";
	}
}

bool Karta_gracza::czy_posiada(int id_x, int poziom_y, int rodzaj_z) {
	std::list<Umiejetnosci_skrot>::iterator it;
	if (this->umiejetnosci_gracza.empty() != false) {
		it = this->umiejetnosci_gracza.begin();
		while (it != this->umiejetnosci_gracza.end()) {
			if (it->zwroc_rodzaj() == rodzaj_z)
				if (it->zwroc_ID() == id_x)
					if (it->zwroc_poziom() == poziom_y)
						return true;
					else
						return false;	//gracz mo�e posaida� tylko jeden poziom danej umiejetnosci (je�li x i z sie zgadza, to y te� si� musi zgadza�, albo od razu mamy nieprawid�owo��
				else {
					if (it->zwroc_ID() > id_x)
						return false;	//umiej�tnosci s� posortowane, abyu wewnatrz jednego rodzaju by�y uporz�dkowane wzgl�dem ID -> je�li otrzymamy wi�ksze ID, to znaczy, i� do tej pory nie znale�li�my szukanego -> fa�sz
				}
			else{
				if (it->zwroc_rodzaj() > rodzaj_z)
					return false;		//je�li nie znale�li�my danej umiej�tnos�i do momentu, gdy przechodzimy na wy�szy rodzaj, to znaczy, �e jej nie znajdziemy
			}
		}
	}
	else {
		return false;
	}
}

void Karta_gracza::dodaj_walke(int id_walki) {
	this->walki_gracza.push_back(id_walki);
}

std::list<int> Karta_gracza::zwroc_liste_walk() {
	return this->walki_gracza;
}

std::string Karta_gracza::zwroc_nick() {
	return this->nick;
}

/*
void Karta_gracza::dodaj_walke(Walka* nowa_walka) {
	this->walki_gracza.push_back(nowa_walka);
}

*/

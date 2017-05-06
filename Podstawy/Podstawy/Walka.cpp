#include "Walka.h"

//Notatka numer 1 zawiera bardzo ogólne opisanie zasad walki -> aktualne informacje w pliku "Walka.h"

//NOTATKA 1: WALKI
/*
Walki odbywaj¹ siê na nastêpuj¹cej zasadzie:
-gracze ustawiaj¹ swoje kolejki atak-obrony w funkcji (nazwa funkcji)
-do funkcji 'pojedynek' wprowadzane s¹ punkty ¿ycia obu walcz¹cych oraz wskaŸnik na listê atak-obrona
-funkcja 'pojedynek' wykonuje pierwsz¹ wymianê: wyzywaj¹cy (A-atakuj¹cy) uderza, a wyzwany (O-obroñca) próbuje siê broniæ
-nastêpnie funkcja 'obrazenia' wylicza zadane obra¿enia, a {!!!funkcja 'ustaw_PZ' odejmuje({póŸniej}/dodaje) punkty ¿ycia!!!} nastêpnie odpowiednio ustawia siê lokalne wartoœci PZ
-funkcja 'pojedynek' sprawdza, czy wyzwany posiada jeszcze jakieœ punkty ¿ycia, czy przegrywa przez 'eliminacje'
-jeœli zostaje wyeliminowany walka koñczy siê zwyciêstwem wyzywaj¹cego
-jeœli nie nastêpuje zmiana miejsc (punkty 3-6 s¹ wykonywane ponownie z odwróconymi rolami)
-walka toczy sie do momentu, gdy ktoœ zostanie wyeliminowany, lub te¿ obaj walcz¹cy wykonaj¹ swoje kolejki atak-obrony
-w przypadku braku eliminacji obu graczom wyliczany jest procentowy wynik pozosta³ych punktów zdrowia (max_PZ*100/obecne_PZ) 
-funkcja 'ustaw_PZ' ustawia koñcowe pozosta³e punkty ¿ycia obu walcz¹cym
-funkcja 'pojedynek' zwraca zwyciêzcê: A-wygrywa wyzywaj¹cy (atakuj¹cy), O-wygrywa wyzwany (obroñca), R-walka koñczy siê remisem (oboje graczy ma tyle samo procent (w zaokr¹gleniu do jednoœci) zdrowia)



/*	Nieaktualne
struct umiejetnosc {
	string nazwa_umiejetnosci;
	char typ_umiejetnosci;      //S-silny, Z-zrêczny, M-magiczny

};

struct atak_obrona {
	atak_obrona* nastepne = nullptr;
	umiejetnosc* urzyta_umiejetnosc;
};


char pojedynek(int PZ_A, atak_obrona* lista_atak, int PZ_O, atak_obrona* lista_obro ) {
	char wynik_pojedynku;


	return wynik_pojedynku;
}

void ustaw_PZ() {


}
*/



Walka::Walka(Karta_gracza &atakujacy, Karta_gracza &broniacy, int& numer_ostatniej_walki, std::map<int, Walka*> &baza_walki){
	gracz_wyzywajacy = Karta_gracza(atakujacy);
	gracz_wyzwany = Karta_gracza(broniacy);
	zaakceptowana = false;
	numer_ostatniej_walki++;
	numer_walki = numer_ostatniej_walki;
	baza_walki.emplace(numer_ostatniej_walki, this);
	atakujacy.dodaj_walke(numer_ostatniej_walki);
	broniacy.dodaj_walke(numer_ostatniej_walki);
}

void Walka::wybor_umiejetnosci(bool czy_atakujacy, Karta_gracza gracz, std::vector<std::vector<std::vector<Umiejetnosci>>> baza_umiej) {
	int atak, obrona;
	int x, y, z;
	char wybor;
	bool posiada = false, potwierdzenie = false, potwierdzenie2 = false;
	if (czy_atakujacy) {
		atak = 0;
		obrona = 1;
	}
	else {
		atak = 2;
		obrona = 3;
	}
	while (potwierdzenie != true) {		//umo¿liwia anulowanie wprowadzonych umiejêtnoœci

	gracz.wypisz_wszystkie_umiejetnosci(baza_umiej);
	
		for (int i = 0; i < 6; i++) {
			while (posiada != true) {
				std::cout << "\nWybierz atak numer: " << i + 1;
				std::cin >> x;
				std::cin >> y;
				std::cin >> z;
				if (gracz.czy_posiada(x, y, z)) {
					//je¿eli gracz posiada jak¹œ umiejetnoœæ, to mo¿emy wpisaæ do tablicy nowo utworzony obiekt klasy Umiejetnosci_skrot o podanych parametrach
					this->tabela_umiej[atak][i] = Umiejetnosci_skrot(x, y, z);
					posiada = true;
				}
				else {
					std::cout << "\nBRAK PODANEJ UMEIJETNOSCI";
					//posiada = false;	-> to ju¿ jest zapewnione
				}
			}
			posiada = false;
		}
		posiada = false;
		for (int i = 0; i < 6; i++) {
			while (posiada != true) {
				std::cout << "\nWybierz obrone numer: " << i + 1;
				std::cin >> x;
				std::cin >> y;
				std::cin >> z;
				if (gracz.czy_posiada(x, y, z)) {
					//je¿eli gracz posiada jak¹œ umiejetnoœæ, to mo¿emy wpisaæ do tablicy nowo utworzony obiekt klasy Umiejetnosci_skrot o podanych parametrach
					this->tabela_umiej[obrona][i] = Umiejetnosci_skrot(x, y, z);
					posiada = true;
				}
				else {
					std::cout << "\nBRAK PODANEJ UMEIJETNOSCI";
					//posiada = false;	-> to ju¿ jest zapewnione
				}
			}
			posiada = false;
		}
		potwierdzenie2 = false;
		while (potwierdzenie2 != true) {
			std::cout << "\n\n==================\nCzy chcesz potwierdzic te umiejetnosci? (T/N)";
			std::cin >> wybor;
			if (wybor == 't' || wybor == 'T') {
				potwierdzenie = true;
				potwierdzenie2 = true;
			}
			else if (wybor == 'n' || wybor == 'N') {
				potwierdzenie = false;
				potwierdzenie2 = true;
			}
			else {
				std::cout << "\nNIEPRAWIDLOWA OPCJA";
				potwierdzenie2 = false;
			}

		}
	}
}

void Walka::wypisz_informacje() {
	std::cout << "\nNUMER WALKI: " << this->numer_walki << "\nGRACZ WYZYWAJACY:\t" << this->gracz_wyzywajacy.zwroc_nick() << "\nGRACZ WYZWANY:\t" << this->gracz_wyzwany.zwroc_nick() << "\nSTATUS WALKI:\t";
	if (this->zaakceptowana)
		std::cout << "\nROZSTRZYGNIETA";
	else
		std::cout << "\nCZEKA NA ZAAKCEPTOWANIE";
}

int Walka::zwroc_numer_walki() {
	return this->numer_walki;
}

/*
void Karta_gracza::test() {
	Walka* tmp;
}
*/
/*
Walka* Karta_gracza::odszukaj_walke(int numer_walki, std::map<int, Walka*> baza_walki) {
	Walka* tmp;
	std::map<int, Walka*>::iterator it;
	if (baza_walki.empty() != true) {
		//tutaj dokoñczyæ
	}
	else {
		return nullptr;
	}
}
*/



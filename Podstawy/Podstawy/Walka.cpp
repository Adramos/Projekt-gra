#include "Walka.h"

//Notatka numer 1 zawiera bardzo ogólne opisanie zasad walki -> aktualne informacje w pliku "Walka.h"
//Okreœlenie "w nastêpnej turze" oznacza, i¿ dodawane s¹ dwa efekty: jeden z czasem 2 oraz drugi PRZECIWNY do niego z czasem 1 -> Dziêki temu w najbli¿szej rundzie nic siê nie stanie, a w przysz³ej stanie siê to co staæ siê mia³o.

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
	rozegrana = false;
	numer_ostatniej_walki++;
	numer_walki = numer_ostatniej_walki;
	baza_walki.emplace(numer_ostatniej_walki, this);
	atakujacy.dodaj_walke(numer_ostatniej_walki);
	broniacy.dodaj_walke(numer_ostatniej_walki);
}

Walka::Walka(Karta_gracza &atakujacy, Karta_gracza &broniacy, int& numer_ostatniej_walki, std::map<int, Walka*> &baza_walki, Umiejetnosci_skrot tabelaU[4][6], bool zak, bool roz) {
	gracz_wyzywajacy = Karta_gracza(atakujacy);
	gracz_wyzwany = Karta_gracza(broniacy);
	zaakceptowana = zak;
	rozegrana = roz;
	numer_ostatniej_walki++;
	numer_walki = numer_ostatniej_walki;
	baza_walki.emplace(numer_ostatniej_walki, this);
	atakujacy.dodaj_walke(numer_ostatniej_walki);
	broniacy.dodaj_walke(numer_ostatniej_walki);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			tabela_umiej[i][j] = tabelaU[i][j];
		}
	}
}

Walka::~Walka() {
	delete &gracz_wyzwany;			//to s¹ KOPIE obiektów, a wiêc mozemy je bezpiecznie usun¹æ
	delete &gracz_wyzywajacy;
	//delete[] &tabela_umiej;		-> czy jest sens usuwaæ statyczna tablicê?
	Umiejetnosci_skrot tmp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			tmp = this->tabela_umiej[i][j];
			delete &tmp;
		}
	}
}

void Walka::wybor_umiejetnosci(bool czy_atakujacy, Karta_gracza gracz, std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej) {
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
	
	std::cout << "Rodzaje umiejetnosci :\n\t0 - SILNY ATAK\n\t1 - SZYBKI ATAK\n\t2 - MAGICZNY ATAK\n\t3 - SILNA OBRONA\n\t4 - SZYBKA OBRONA\n\t5 - MAGICZNA OBRONA";
		
		for (int i = 0; i < 6; i++) {
			while (posiada != true) {
				std::cout << "\n\nWybierz atak numer: " << i + 1;
				std::cout << "\nPodaj ID umiejetnosci:\t\t";
				std::cin >> x;
				std::cout << "\nPodaj poziom umiejetnosci:\t";
				std::cin >> y;
				y--;
				std::cout << "\nPodaj rodzaj umiejetnosci:\t";
				std::cin >> z;
				if (z >= 0 && z <= 2) {
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
				else {
					std::cout << "\n\tTo mial byc atak...";
				}
			}
			posiada = false;
		}
		posiada = false;
		for (int i = 0; i < 6; i++) {
			while (posiada != true) {
				std::cout << "\n\nWybierz obrone numer: " << i + 1;
				std::cout << "\nPodaj ID umiejetnosci:\t\t";
				std::cin >> x;
				std::cout << "\nPodaj poziom umiejetnosci:\t";
				std::cin >> y;
				y--;
				std::cout << "\nPodaj rodzaj umiejetnosci:\t";
				std::cin >> z;
				if (z >= 3 && z <= 5) {
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
				else {
					std::cout << "\n\tTo miala byc obrona...";
				}
			}
			posiada = false;
		}
		potwierdzenie2 = false;
		while (potwierdzenie2 != true) {
			std::cout << "\n\n==================\nCzy chcesz potwierdzic te umiejetnosci? (T/N)\n\t\t";
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
	std::cout << "\nNUMER WALKI: " << this->numer_walki << "\nGRACZ WYZYWAJACY:\t" << this->gracz_wyzywajacy.zwroc_nick() << "\nGRACZ WYZWANY:\t\t" << this->gracz_wyzwany.zwroc_nick() << "\nSTATUS WALKI:\t";
	if (this->rozegrana) {
		std::cout << "\nROZSTRZYGNIETA";
		if (this->zaakceptowana) 
			std::cout << "\nPRZECIWNIK PRZYJAL WYZWANIE";		
		else
			std::cout << "\nPRZECIWNIK ODRZUCIL WYZWANIE";
	}
	else
		std::cout << "\nCZEKA NA ZAAKCEPTOWANIE";
}

int Walka::zwroc_numer_walki() {
	return this->numer_walki;
}

Karta_gracza Walka::zwoc_gracza(char ktory) {
	if (ktory == 'A')
		return this->gracz_wyzywajacy;
	else
		return this->gracz_wyzwany;
}

bool Walka::czy_zaakceptowana() {
	return this->zaakceptowana;
}

bool Walka::czy_rozegrana() {
	return this->rozegrana;
}

Umiejetnosci_skrot Walka::zwroc_wart_tab(int i, int j){
	return this->tabela_umiej[i][j];
}

void Walka::ustaw_zaakceptowanie(bool wybor) {
	this->zaakceptowana = wybor;
}
void Walka::ustaw_rozegranie(bool wybor, std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej) {
	this->rozegrana = wybor;
	if (this->czy_zaakceptowana()) {
		this->wyswietl_walke(baza_umiej);
		//zwroc nagrody za walke
	}
}

void Walka::wyswietl_walke(std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej) {
	srand(time(NULL));
	system("cls");
	//char znak_czekaj = 0;
	//int licznik = 0;
	bool trafienie_krytyczne, skuteczna_blokada;
	int pz_atak = this->gracz_wyzywajacy.zwroc_pz();
	int pz_obro = this->gracz_wyzwany.zwroc_pz();
	double proc_pz_atak = 0, proc_pz_obro = 0;
	int obrazenia, obrona, krytyk;
	Umiejetnosci_ofensywne* ofens;
	Umiejetnosci_defensywne* defens;
	std::string smieci;
	std::cout << "Czas rozpoczac walke, aby kontynuowac uzywaj klawisza \"ENTER\".";
	getline(std::cin, smieci);
		while (getchar() != '\n') {
			//continue;
		}
		//while (pz_atak>0 && pz_obro>0 && licznik <12) {
			
		//}
		//schemat walki: (rozwijane o efekty)
		/*
		-zczytujemy obra¿enia od ataku
		-zczytujemy obronê celu
		-sprawdzamy czy obrona by³a skuteczna
		-odejmujemy od siebie wartoœci (nie mo¿e byæ mniejsze od zera)
		-testujemy trafienie krytyczne
		*/
		for (int i = 0; i < 6; i++) {
			std::cout << "\n====================\n\n\tRUNDA " << i+1;
			krytyk = 0;
			//obliczamy bazow¹ wartoœæ obra¿eñ
			//ofens = tabela_umiej[0][i].zwroc_umiej(baza_umiej);
			//defens = tabela_umiej[3][i].zwroc_umiej(baza_umiej);
			//obrazenia = ofens->zwroc_obrazenia();
			obrazenia = this->tabela_umiej[0][i].zwroc_umiej(baza_umiej)->zwroc_obrazenia();
			//zczytujemy rodzaj ataku (by odczytaæ jak¹ wartoœæ obrony powinniœmy badaæ)
			obrona = this->tabela_umiej[0][i].zwroc_umiej(baza_umiej)->zwroc_rodzaj();
			//obrona = ofens->zwroc_rodzaj();
			switch (obrona) {	//zczytujemy wartoœæ odpowiedniej obrony
			case 0:
				obrona = this->tabela_umiej[3][i].zwroc_umiej(baza_umiej)->zwroc_os();
				//obrona = defens->zwroc_os();
				break;
			case 1:
				obrona = this->tabela_umiej[3][i].zwroc_umiej(baza_umiej)->zwroc_of();
				//obrona = defens->zwroc_of();
				break;
			case 2:
				obrona = this->tabela_umiej[3][i].zwroc_umiej(baza_umiej)->zwroc_om();
				//obrona = defens->zwroc_om();
				break;
			default:
				obrona = 0;	//sytuacja niemo¿liwa
			}
			if (this->tabela_umiej[0][i].zwroc_rodzaj() == (this->tabela_umiej[3][i].zwroc_rodzaj()) + 3) {	//np silny atak = 0, silna obrona = 3
				skuteczna_blokada = true;
			}
			else {
				skuteczna_blokada = false;
			}
			//obliczamy wartoœæ obra¿eñ po odjêciu obrony
			obrazenia = obrazenia - obrona;
			if (obrazenia < 0)
				obrazenia = 0;
			//testujemy trafienie krytyczne;
			if (krytyk != 0) {
				if (krytyk <= rand() % 100) {
					trafienie_krytyczne = true;
					obrazenia = obrazenia + obrazenia;		//minimalnie szybsze od mno¿enia *2
				}
				else
					trafienie_krytyczne = false;
			}
			else {
				trafienie_krytyczne = false;
			}
			pz_obro = pz_obro - obrazenia;
			std::cout << "\n\n" << this->gracz_wyzywajacy.zwroc_nick() << " atakuje " << this->gracz_wyzwany.zwroc_nick();
			std::cout << " przy pomocy\n" << this->tabela_umiej[0][i].zwroc_umiej(baza_umiej)->zwroc_nazwe();
			std::cout << ".\n" << this->gracz_wyzwany.zwroc_nick() << " uzywa\n" << this->tabela_umiej[3][i].zwroc_umiej(baza_umiej)->zwroc_nazwe();
			if (skuteczna_blokada)
				std::cout << "\nUdalo sie zablokowac atak.";
			else
				std::cout << "\nNieskuteczna obrona.";
			if (trafienie_krytyczne)
				std::cout << "\nUdalo sie trafic w czuly punkt! Obrazenia x2!";
			std::cout << "\nOstatecznie " << this->gracz_wyzwany.zwroc_nick() << " otrzymuje " << obrazenia << " obrazen i pozostalo mu " << pz_obro << " punktow zycia.";
			//oczekujemy a¿ gracz naciœnie enter
			while (getchar() != '\n') {
				//std::cin >> znak_czekaj;
			}
			//znak_czekaj = '#';
			//je¿eli obroñca (lub atakuj¹cy) straci³ resztê zdrowia -> przerywamy walkê
			if (pz_obro <= 0 || pz_atak <= 0)
				break;

			std::cout << "\n\n";
			//teraz role siê odwracaj¹;
			krytyk = 0;
			//obliczamy bazow¹ wartoœæ obra¿eñ
			obrazenia = this->tabela_umiej[2][i].zwroc_umiej(baza_umiej)->zwroc_obrazenia();
			//zczytujemy rodzaj ataku (by odczytaæ jak¹ wartoœæ obrony powinniœmy badaæ)
			obrona = this->tabela_umiej[2][i].zwroc_umiej(baza_umiej)->zwroc_rodzaj();
			switch (obrona) {	//zczytujemy wartoœæ odpowiedniej obrony
			case 0:
				obrona = this->tabela_umiej[1][i].zwroc_umiej(baza_umiej)->zwroc_os();
				break;
			case 1:
				obrona = this->tabela_umiej[1][i].zwroc_umiej(baza_umiej)->zwroc_of();
				break;
			case 2:
				obrona = this->tabela_umiej[1][i].zwroc_umiej(baza_umiej)->zwroc_om();
				break;
			default:
				obrona = 0;	//sytuacja niemo¿liwa
			}
			if (this->tabela_umiej[2][i].zwroc_rodzaj() == (this->tabela_umiej[1][i].zwroc_rodzaj()) + 3) {	//np silny atak = 0, silna obrona = 3
				skuteczna_blokada = true;
			}
			else {
				skuteczna_blokada = false;
			}
			//obliczamy wartoœæ obra¿eñ po odjêciu obrony
			obrazenia = obrazenia - obrona;
			if (obrazenia < 0)
				obrazenia = 0;
			//testujemy trafienie krytyczne;
			if (krytyk != 0) {
				if (krytyk <= rand() % 100) {
					trafienie_krytyczne = true;
					obrazenia = obrazenia + obrazenia;		//minimalnie szybsze od mno¿enia *2
				}
				else
					trafienie_krytyczne = false;
			}
			else {
				trafienie_krytyczne = false;
			}
			pz_atak = pz_atak - obrazenia;
			std::cout << "\n\n" << this->gracz_wyzwany.zwroc_nick() << " atakuje " << this->gracz_wyzywajacy.zwroc_nick();
			std::cout << " przy pomocy\n" << this->tabela_umiej[2][i].zwroc_umiej(baza_umiej)->zwroc_nazwe();
			std::cout << ".\n" << this->gracz_wyzywajacy.zwroc_nick() << " uzywa\n" << this->tabela_umiej[1][i].zwroc_umiej(baza_umiej)->zwroc_nazwe();
			if (skuteczna_blokada)
				std::cout << "\nUdalo sie zablokowac atak.";
			else
				std::cout << "\nNieskuteczna obrona.";
			if (trafienie_krytyczne)
				std::cout << "\nUdalo sie trafic w czuly punkt! Obrazenia x2!";
			std::cout << "\nOstatecznie " << this->gracz_wyzywajacy.zwroc_nick() << " otrzymuje " << obrazenia << " obrazen i pozostalo mu " << pz_atak << " punktow zycia.";
			//oczekujemy a¿ gracz naciœnie enter
			while (getchar() != '\n') {
				//std::cin >> znak_czekaj;
				}
			//znak_czekaj = '#';
			//je¿eli obroñca (lub atakuj¹cy) straci³ resztê zdrowia -> przerywamy walkê
			if (pz_obro <= 0 || pz_atak <= 0)
				break;
			//i tak do koñca -> do momentu wyczerpania wszystkich par atak-obrona
		}
		//tutaj jesteœmy po walce -> wypisujemy kto wygra³
		std::cout << "\n\n=========================\n\n";
		if (pz_obro <= 0) {
			if (pz_atak <= 0) {
				std::cout << "\tPODWOJNE K.O.! Remis";
			}
			else {
				std::cout << "\t" << this->gracz_wyzwany.zwroc_nick() << " lezy nieprzytomny -> zwycieza: " << this->gracz_wyzywajacy.zwroc_nick();
			}
		}
		else if (pz_atak <= 0) {
			std::cout << "\t" << this->gracz_wyzywajacy.zwroc_nick() << " lezy nieprzytomny -> zwycieza: " << this->gracz_wyzwany.zwroc_nick();
		}
		else {
			std::cout << "\tPo zazartej walce obaj walczacy stoja na wlasnych nogach...";
			proc_pz_atak = pz_atak / this->gracz_wyzywajacy.zwroc_pz();
			proc_pz_obro = pz_obro / this->gracz_wyzwany.zwroc_pz();
			if (proc_pz_atak > proc_pz_obro) {
				//wygra³ atakuj¹cy
				std::cout << "\n\tJednakze to " << this->gracz_wyzywajacy.zwroc_nick() << " zwycieza!";
			}
			else if(proc_pz_obro > proc_pz_atak) {
				//wygra³ obroñca
				std::cout << "\n\tJednakze to " << this->gracz_wyzwany.zwroc_nick() << " zwycieza!";
			}
			else {
				//remis
				std::cout << "\n\tTym bardziej szokujacym jest, iz ostatecznie mamy... remis!";
			}
		}
		while (getchar() != '\n') {
			//std::cin >> znak_czekaj;
		}
		//znak_czekaj = '#';
		//no i to wszyztko
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



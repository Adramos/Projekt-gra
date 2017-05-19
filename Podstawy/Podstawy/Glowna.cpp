#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include "Walka.h"
#include <regex>

using namespace std;

//deklaracje funkcji

void czekaj(int);		 //funckja s³u¿y do zatrzymania programu na 'n' sekund
void wypisz_walki(std::list<int> walki_gracza, std::map<int, Walka*> wszystkie_walki);
void odczyt_umiejetnosci(string nazwa_pliku, std::vector<std::vector<std::vector<Umiejetnosci*>>> &baza_um);
void odczyt_gracze(string nazwa_pliku, map<int, Karta_gracza*> &baza_gr, int &licz_gracz);
void odczyt_walki(string nazwa_pliku, map<int, Walka*> &baza_wal, int &licz_walk, map<int, Karta_gracza*> &baza_gr);
void zapis_gracze(string nazwa_pliku, map<int, Karta_gracza*> &baza_gr);
void zapis_walki(string nazwa_pliku, map<int, Walka*> &baza_wal);
std::string szyfruj(std::string tekst, int klucz, string klucz2);
std::string deszyfruj(std::string szyfrowana, int klucz, string klucz2);
std::string DecnaBin(int liczbaDec);
int BinnaDec(std::string liczbaBin);
Karta_gracza* znajdz_gracza(int numer_gracza, map<int, Karta_gracza*> baza_gr);
//funkcja main

int main() {
	std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiejestosci; 		//dla uproszczenia: zapis bêdzie: baza_umiejetnosci[rodzaj][poziom][id] => baza_umiejetnosci[z][y][x]
	std::map<int, Karta_gracza*> baza_gracze;	
	//std::set<int> zalogowani_gracze;	-> na przysz³oœæ
	std::map<int, Walka*> baza_walki;
	int ostatni_gracz = 0, ostatnia_walka = 0;
	std::list<Umiejetnosci_skrot*> startowe_umiejetnosci_gracza;
	//ustawianie bazowego rozmiaru vetora umeijêtnoœci [0-6][0-4][n]
	baza_umiejestosci.resize(7);
	for (int i = 0; i < 7; i++){
		baza_umiejestosci[i].resize(5);		//zapamiêtaæ -> patrzeæ, czy zamiast resize nei pojawi³o siê 'reserve' -.-
		}
	//tworzenie bazowej listy umiejêtnoœci -> dla nowych graczy
	for (int i = 0; i < 6; i++) {
		Umiejetnosci_skrot* tmp_umiej_skrot = new Umiejetnosci_skrot(0, 0, i);
		startowe_umiejetnosci_gracza.push_back(tmp_umiej_skrot);
	}
	//==============================================================================================================================================================
	//ODCZYTYWANIE BAZ DANYCH
	//==============================================================================================================================================================
	//odczyt umiejêtnosci:
	odczyt_umiejetnosci("baza umiejetnosci.txt", baza_umiejestosci);
	//odczyt gracze:
	odczyt_gracze("baza gracze.txt", baza_gracze, ostatni_gracz);
	//odczyt walki:
	odczyt_walki("baza walki.txt", baza_walki, ostatnia_walka, baza_gracze);
	czekaj(2);
	//==============================================================================================================================================================
	//FUNKCJA W£AŒCIWA
	//==============================================================================================================================================================	
	char znak_nawigacji;
	bool koniec, wyjscie;
	string nick, haslo, smieci;;
	regex wzorzec("\\w* to \\w*");
	regex nick_wzor("[A-Z](.){4,19}"); 
	regex haslo_wzor("(.){8,20}");
	Karta_gracza* pomocnicza_karta = nullptr;
	map<int, Karta_gracza*>::iterator it;
	Karta_gracza* aktualny_gracz;

	koniec = false;
	while (koniec != true) {
		system("cls");
		cout << "Witaj wedrowcze!\nWybierz jedna z opcji:\nZ-aloguj\nR-ejestracja\nW-yjscie\n\t";
		cin >> znak_nawigacji;
		switch (znak_nawigacji) {
			//==============================================================================================================================================================
			//==============================================================================================================================================================
			//==============================================================================================================================================================
		case 'Z':
			getline(cin, smieci);
			system("cls");
			cout << "Aha! Oczekiwalismy Cie!";
			czekaj(2);
			cout << "\n\n\tChyba Ty, ja juz nawet nie pamietam ktory to...";
			czekaj(2);
			cout << "\n\nPodaj nam swoje imie,\t\t\t";
			getline(cin, nick);
			koniec = false;
			wyjscie = false;
			try {
				if (baza_gracze.empty())
					throw(1);
				it = baza_gracze.begin();
				while (koniec != true) {				
					if(it == baza_gracze.end()) {
						throw(2);
					}
					else if (it->second->zwroc_nick() == nick) {
						cout << "\nA teraz nasze tajne haslo.\t\t";
						getline(cin, haslo);
						if (it->second->porownaj_haslo(haslo)) {
							cout << "\n\nA to Ty! Cieszymy sie, ze Cie tu widzimy bohaterze numer " << it->second->zwroc_ID();
							aktualny_gracz = it->second;
							koniec = true;
							czekaj(2);
						}
						else {
							cout << "\n\n\tEj, ej! Tego hasla nie pamietam!\n";
							czekaj(2);
						}
					}
					else {
						it++;
					}
				}
			}
			catch (int a) {
				cout << "\n\nEj! Nie oszukuj! Ciebie na pewno nie znamy!";
				czekaj(3);
				wyjscie = true;
			}
			koniec = false;
			if (wyjscie != true) {
			//Na tym etapie gracz jest ju¿ zalogowany i gotowy do podejmowania akcji
			//==============================================================================================================================================================
				while (koniec != true) {
					system("cls");
					cout << "\nNo dobrze bohaterze. Jakie sa twoje nastepne kroki?";
					cout << "\n\n\tP-rzejrzyj swoje walki\n\tR-zuc wyzwanie\n\tI-nformacje\n\tN-auka nowych umiejetnosci\n\tW-ygoluj\n\n\t";
					cin >> znak_nawigacji;
					switch (znak_nawigacji) {
						//==============================================================================================================================================================
					case 'P':
						break;
						//==============================================================================================================================================================
					case 'R':
						break;
						//==============================================================================================================================================================
					case 'I':
						//Mo¿liwe informacje: 
						/*
						M-mechanika walki
						H-historia œwiata
						U-umiejêtnoœci
						@-ukryta opcja maj¹ca przedstawiæ autora :P 
						*/
						while (koniec != true) {
							system("cls");
							cout << "Wiedza to wyjatkowo silne narzedzie... O czym chcesz sie dowiedzeic?";
							cout << "\n\n\tM-echanika walki\n\tH-istoria swiata\n\tU-miejetnosci\n\tW-wyjscie\n\n\t";
							cin >> znak_nawigacji;
							switch (znak_nawigacji) {
							case 'M':
								system("cls");
								break;
							case 'H':
								system("cls");
								break;
							case 'U':
								system("cls");
								break;
							case '@':
								system("cls");
								czekaj(5);
								cout << "\tBracie";
								czekaj(1);
								cout << " chyba to odkryli...";
								czekaj(2);
								cout << "\n\nEhhh... Komus musialo sie udac. Gratulacje.";
								czekaj(2);
								cout <<	"\nJesli podoba Ci sie gra, to wiedz, ze jest to dzielo\nPawla \"TYP'a\" Jurczyka\n\nUdanej zabawy i nie zdradz tego innym, niech sami odszukaja ;)";
								czekaj(7);
								break;
							case 'W':
								cout << "\n\nNo dobrze, pamietaj, ze zawsze mozesz tu wrocic.";
								koniec = true;
								czekaj(2);
								break;
							default:
								cout << "\n\n\tWiedza i ignorancja nie powinny chodzic ze soba w parze...";
								czekaj(2);
								break;
							}
						}
						koniec = false;
						break;
						//==============================================================================================================================================================
					case 'N':
						break;
						//==============================================================================================================================================================
					case 'W':
						system("cls");
						cout << "Naprawde nas opuszczasz? (T/N)\n\n\t";
						cin >> znak_nawigacji;
						if (znak_nawigacji == 'T') {
							cout << "\nSzkoda...";
							czekaj(1);
							cout << "\n\n\t...Wcale nie...";
							czekaj(1);
							cout << "\n\nDo nastepnego spotkania";
							czekaj(2);
							koniec = true;
						}
						else if (znak_nawigacji == 'N') {
							cout << "\tSzkoda...";
							czekaj(1);
							cout << "\n\nWcale nie";
							czekaj(2);
						}
						else {
							cout << "\n\nBrak odpowiedzi nie zwolni Cie z konsekwencji...";
							czekaj(2);
						}
						break;
						//==============================================================================================================================================================
					default:
						cout << "\n\n\tWybierz poprawna opcje... \"bohaterze\"";
						czekaj(2);
						break;
					}
					//==============================================================================================================================================================
					getline(cin, smieci);
				}

			}
			aktualny_gracz = nullptr;
			koniec = false;
			break;
			//==============================================================================================================================================================
			//==============================================================================================================================================================
			//==============================================================================================================================================================
		case 'R':
			system("cls");
			cout << "A wiec postanawiasz dolaczyc do konfliktu?";
			czekaj(3);
			cout << "\n\n\tJak to zwykle Ty: zapomniales wspomniec co to za konfkilt...";
			czekaj(4);
			cout << "\n\nCoz... Na pelna historie czas jeszcze nadejdzie.";
			czekaj(3);
			cout << "\n\nMusisz jednak wiedziec, ze wojna miedzy Bestiami i Sojuszem\ntrwa juz od wielu pokolen.";
			czekaj(5);
			cout << "\n\nObie strony utnkely w martwym punkcie.\nI to byc moze TY dasz rade poprowadzic\nktoras z nich do zwyciestwa.";
			czekaj(5);
			cout << "\n\n\tA moze od razu wspomnisz jeszcze, ze spelnia\n\tjakas.. albo lepiej, WSZYSTKIE przepowiednie, hm?\n\tNie przeginaj...";
			czekaj(5);
			cout << "\n\nEhh... No i caly nastroj poszedl kopulowac...\nDobra posluchaj, zanim zaczniesz musisz sie przedstawic.";
			czekaj(5);
			cout << "\n\n\tTylu was jest, ze nie pamietamy wszystkich imion... \n\tA wiec jak mamy Cie zapowiedziec?";
			czekaj(4);
			getline(cin, smieci);
			koniec = false;
			while (koniec != true) {
				system("cls");
				cout << "\tPsss... Twoj nick powinien zaczynac sie z wielkiej lietry,\n\tmiec co najmniej 5 i co najwyzej 20 znakow!\n\tAby wyjsc wpisz \"EXIT\"";
				cout << "\n\n\t\t(Podaj swoj nick:) ";
				getline(cin, nick);
				if (nick != "EXIT") {
					if (regex_match(nick, nick_wzor)) {
						try {
							if (!baza_gracze.empty()) {
								for (it = baza_gracze.begin(); it != baza_gracze.end(); it++) {
									if (it->second->zwroc_nick() == nick)
										throw(1);
								}
							}
							cout << "\n\n\nHa! Wiedzialem, ze Twoje imie brzmi jak powinno!\nTo teraz jeszcze musimy ustalic tajne haslo,\npo ktorego podaniu bedziemy mieli pewnosc, iz Ty to Ty...";
							czekaj(3);
							cout << "\n\n\tA tu niespodzianka: haslo moze byc dowolnym ciagiem\n\tliczacym od 8 do 20 znakow.";
							cout << "\n\n\t\t(Podaj swoje haslo:) ";
							getline(cin, haslo);
							if (regex_match(haslo, haslo_wzor)) {
								system("cls");
								cout << "No i to rozumiem!";
								czekaj(2);
								Karta_gracza* calkiem_nowy_gracz = new Karta_gracza(nick, haslo, startowe_umiejetnosci_gracza, ostatni_gracz, baza_gracze);
								pomocnicza_karta = calkiem_nowy_gracz;
								cout << "\n\n\tWitaj randomowy bohaterze numer: " << ostatni_gracz;
								czekaj(3);
								cout << "\n\n\tA teraz zmykaj i wroc za chwile\n\tjakbysmy sie wczesniej nie widzieli.";
								czekaj(4);
								koniec = true;
							}
							else {
								cout << "\n\nEj! My to mamy zapamietac!\nZa kare jeszcze raz!";
								czekaj(2);
							}
						}
						catch (int w) {
							cout << "\n\nHola, hola! Znam juz kogos o tym imieniu!";
							czekaj(3);
						}
					}
					else {
						cout << "\nEjze! Tak sie nie mozesz nazywac!";
						czekaj(2);
						koniec = false;
					}
				}
				else{
					cout << "\n\n\tDobra, dobra. Jak nie teraz to pozniej.";
					czekaj(2);
					koniec = true;
				}
			}
			koniec = false;
			break;
			//==============================================================================================================================================================
			//==============================================================================================================================================================
			//==============================================================================================================================================================
		case 'W':
			system("cls");
			koniec = true;
			cout << "\n\tKiedys wrocisz, wiem o tym...";
			czekaj(3);
			cout << "\n\nWez ich nie strasz! Nie sluchaj go, wcale tego nie wie.";
			czekaj(3);
			cout << "\n\n\tJeszcze zobaczymy czyje gora... muaha buahaha!";
			break;
			//==============================================================================================================================================================
		default:
			cout << "\nNiewlasciwa opcja!";
			czekaj(2);
			system("cls");
			break;
		}
	}
	czekaj(3);
	//==============================================================================================================================================================
	//ZAPIS BAZ DANYCH DO PLIKÓW + ZAKOÑZENIE DZIA£ANIA PROGRAMU
	//==============================================================================================================================================================
	zapis_gracze("baza gracze.txt", baza_gracze);
	zapis_walki("baza walki.txt", baza_walki);
	baza_umiejestosci.clear();
	baza_gracze.clear();
	baza_walki.clear();
	startowe_umiejetnosci_gracza.clear();
}


//definicje funkcji




void wypisz_walki(std::list<int> walki_gracza, std::map<int, Walka*> wszystkie_walki) {
	std::list<int>::iterator it;
	std::map<int, Walka*>::iterator it_walki;
	for (it = walki_gracza.begin(); it != walki_gracza.end(); it++) {
		it_walki = wszystkie_walki.begin();
		while (it_walki->second->zwroc_numer_walki() != *it && it_walki != wszystkie_walki.end()) {
			it_walki++;
		}
		if (it_walki == wszystkie_walki.end()) {
		std::cout << "\nBLAD! BRAK WALKI NUMER: " << it_walki->first;
		}
		else {
			it_walki->second->wypisz_informacje();
			std::cout << "\n=========================================\n";
		}
	}
}

void odczyt_umiejetnosci(string nazwa_pliku, std::vector<std::vector<std::vector<Umiejetnosci*>>> &baza_um) {
	fstream plik;
	//
	plik.open(nazwa_pliku, ios::in);		//do odczytu
	//
	/*
	Organizacja pliku z umiejêtnosciami:
	-ka¿da nowa umiejêtnoœæ zaczyna siê od kilkunastu znaków '=' -> symbolizuje niepustoœæ pliku
	-w ka¿dej linii znajduj¹ siê dane potrzebne do konstruktora (int numer, int lvl, int typ, std::string nazwa_um, std::string opis_um, Efekty* lista_ef, dodatkowe)
	-po opisie nale¿y umieœciæ znak D, O lub S dla odpowiedniego rodzaju umeijêtnoœci -> decyduje ile kolejnych linii zawiera potrzebne dla konstruktora informacje
	-póŸniej nastêpuje utworzenie listy efektów:
	a)kolejnoœæ danych (nazwa,opis,modyfikator, czas, typ_modyfikatora(tak samo jak dla konstruktora))
	b)jeœli nie ma dalszych umiejêtnoœci (czyli jesli ich nie ma w ogóle tak¿e) to piszemy liniê zawieraj¹c¹ "BRAK"
	c)otrzymujemy listê efektów, któr¹ wykorzystujemy przy konstruktorze
	*/
	//
	if (plik.good()) {
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \""<< nazwa_pliku <<"\"";
		//odczytywanie informacji z plików
		int odcz_ID, odcz_lvl, odcz_rodzaj, odcz_dmg, odcz_os, odcz_of, odcz_om, od_mod, od_czas;
		string odcz_nazwa, odcz_opis, odcz_nazwa_efekt, odcz_opis_efekt;
		Efekty* pocz_listy_efektow, *tmp = nullptr;
		bool brak, cel;
		char kod_mod, rodzaj_um;
		string dane_tekstowe;
		getline(plik, dane_tekstowe);	//->musimy mieæ chocia¿ jedn¹ operacjê odczytu
		if (plik.eof())
			cout << "\nPUSTY PLIK";
		while (plik.eof() != true) {
			getline(plik, dane_tekstowe);
			odcz_ID = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			odcz_lvl = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			odcz_rodzaj = atoi(dane_tekstowe.c_str());
			getline(plik, odcz_nazwa);
			getline(plik, odcz_opis);
			getline(plik, dane_tekstowe);
			if (dane_tekstowe == "O") {
				getline(plik, dane_tekstowe);
				odcz_dmg = atoi(dane_tekstowe.c_str());
				rodzaj_um = 'O';
			}
			else if (dane_tekstowe == "D") {
				getline(plik, dane_tekstowe);
				odcz_os = atoi(dane_tekstowe.c_str());
				getline(plik, dane_tekstowe);
				odcz_of = atoi(dane_tekstowe.c_str());
				getline(plik, dane_tekstowe);
				odcz_om = atoi(dane_tekstowe.c_str());
				rodzaj_um = 'D';
			}
			else {
				//specjalne
				rodzaj_um = 'S';
			}
			//Efekty						kolejnoœæ jak dla konstuktora
			getline(plik, dane_tekstowe);
			if (dane_tekstowe == "BRAK") {
				pocz_listy_efektow = nullptr;
				brak = true;
			}
			else {
				brak = false;
				odcz_nazwa_efekt = dane_tekstowe;
				getline(plik, odcz_opis_efekt);
				getline(plik, dane_tekstowe);
				od_mod = atoi(dane_tekstowe.c_str());
				getline(plik, dane_tekstowe);
				od_czas = atoi(dane_tekstowe.c_str());
				getline(plik, dane_tekstowe);
				kod_mod = dane_tekstowe[0];
				getline(plik, dane_tekstowe);
				if (dane_tekstowe == "TAK")
					cel = true;
				else
					cel = false;
				Efekty* nowy_efekt = new Efekty(odcz_nazwa_efekt, odcz_opis_efekt, od_mod, od_czas, kod_mod, cel);
				pocz_listy_efektow = nowy_efekt;
				tmp = nowy_efekt;
			}
			while (brak != true) {
				getline(plik, dane_tekstowe);
				if (dane_tekstowe == "BRAK") {
					brak = true;
					tmp->nast = nullptr;		//zabezpieczenie
				}
				else {
					odcz_nazwa_efekt = dane_tekstowe;
					getline(plik, odcz_opis_efekt);
					getline(plik, dane_tekstowe);
					od_mod = atoi(dane_tekstowe.c_str());
					getline(plik, dane_tekstowe);
					od_czas = atoi(dane_tekstowe.c_str());
					getline(plik, dane_tekstowe);
					kod_mod = dane_tekstowe[0];
					getline(plik, dane_tekstowe);
					if (dane_tekstowe == "TAK")
						cel = true;
					else
						cel = false;
					Efekty* nowy_efekt2 = new Efekty(odcz_nazwa_efekt, odcz_opis_efekt, od_mod, od_czas, kod_mod, cel);
					tmp->nast = nowy_efekt2;
					tmp = nowy_efekt2;
				}
			}
			brak = false;
			//posiadamy teraz listê efektów -> ostatni element konstruktora
			//cout << odcz_ID << " " << odcz_lvl << " " << odcz_rodzaj;
			if (rodzaj_um == 'O') {
				Umiejetnosci_ofensywne* nowa_off = new Umiejetnosci_ofensywne(odcz_ID, odcz_lvl, odcz_rodzaj, odcz_nazwa, odcz_opis, pocz_listy_efektow, odcz_dmg);
				baza_um[odcz_rodzaj][odcz_lvl].push_back(nowa_off);
			}
			else if (rodzaj_um == 'D') {
				Umiejetnosci_defensywne* nowa_def = new Umiejetnosci_defensywne(odcz_ID, odcz_lvl, odcz_rodzaj, odcz_nazwa, odcz_opis, pocz_listy_efektow, odcz_os, odcz_of, odcz_om);
				baza_um[odcz_rodzaj][odcz_lvl].push_back(nowa_def);
			}
			else {
				//um_spiecjalna
			}
			getline(plik, dane_tekstowe);
		}
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"" << nazwa_pliku << "\"";
	}
	plik.close();
}

void odczyt_gracze(string nazwa_pliku, map<int, Karta_gracza*> &baza_gr, int &licz_gracz) {
	/*
	Organizacja pliku baza gracze.txt:
	-ka¿dy nowy gracz zaczyna siê ci¹giem kilkunastu dowolnych znaków
	-nazwa
	-has³o (szyfrowane!)
	-numerID
	-max_P¯
	-max_mana
	-poziom
	-PD
	-umiejêtnoœci
	-walki
	-efekty

	a)umiejêtnoœci:
	X1
	Y1
	Z1
	X2
	Y2
	Z2
	BRAK

	b)walki:
	numerwalki1
	numerwalki2
	numerwalki3
	BRAK

	c)efekty: to samo co przy umiejêtnosciach
	*/
	
	fstream plik;
	plik.open(nazwa_pliku, ios::in);					//do odczytu
	if (plik.good()) {
		//odczytywanie informacji z plików
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"" << nazwa_pliku << "\"";
		//zmienne:
		string nazwa, haslo, odcz_nazwa_efekt, odcz_opis_efekt;
		int id, pz, max_mana, lvl, EXP, ox, oy, oz, owalka, od_mod, od_czas;
		std::list<Umiejetnosci_skrot*> odcz_umiej;
		std::list<int> odcz_walki;
		Efekty* lista_ef_gracza, *tmp = nullptr;
		bool koniec, cel;
		Umiejetnosci_skrot* nowa;
		char kod_mod;
		Karta_gracza* nowy_gracz;
		//
		string dane_tekstowe;
		getline(plik, dane_tekstowe);	//->musimy mieæ chocia¿ jedn¹ operacjê odczytu
		if (plik.eof())
			cout << "\nPUSTY PLIK";
		while (plik.eof() != true) {
			getline(plik, dane_tekstowe);
			nazwa = dane_tekstowe;
			getline(plik, dane_tekstowe);
			haslo = deszyfruj(dane_tekstowe, 8, "0110");
			getline(plik, dane_tekstowe);
			id = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			pz = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			max_mana = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			lvl = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			EXP = atoi(dane_tekstowe.c_str());
			//umiejetnosci
			odcz_umiej.clear();
			koniec = false;
			while (koniec != true) {
				getline(plik, dane_tekstowe);
				if (dane_tekstowe == "BRAK")
					koniec = true;
				else {
					ox = atoi(dane_tekstowe.c_str());
					getline(plik, dane_tekstowe);
					oy = atoi(dane_tekstowe.c_str());
					getline(plik, dane_tekstowe);
					oz = atoi(dane_tekstowe.c_str());
					nowa = new Umiejetnosci_skrot(ox, oy, oz);
					odcz_umiej.push_back(nowa);
				}
			}
			//walki
			odcz_walki.clear();
			koniec = false;
			while (koniec != true) {
				getline(plik, dane_tekstowe);
				if (dane_tekstowe == "BRAK")
					koniec = true;
				else
					odcz_walki.push_back(atoi(dane_tekstowe.c_str()));
			}
			//efekty
			getline(plik, dane_tekstowe);
			if (dane_tekstowe == "BRAK") {
				lista_ef_gracza = nullptr;
				koniec = true;
			}
			else {
				koniec = false;
				odcz_nazwa_efekt = dane_tekstowe;
				getline(plik, odcz_opis_efekt);
				getline(plik, dane_tekstowe);
				od_mod = atoi(dane_tekstowe.c_str());
				getline(plik, dane_tekstowe);
				od_czas = atoi(dane_tekstowe.c_str());
				getline(plik, dane_tekstowe);
				kod_mod = dane_tekstowe[0];
				getline(plik, dane_tekstowe);
				if (dane_tekstowe == "TAK")
					cel = true;
				else
					cel = false;
				Efekty* nowy_efekt = new Efekty(odcz_nazwa_efekt, odcz_opis_efekt, od_mod, od_czas, kod_mod, cel);
				lista_ef_gracza = nowy_efekt;
				tmp = nowy_efekt;
			}
			while (koniec != true) {
				getline(plik, dane_tekstowe);
				if (dane_tekstowe == "BRAK") {
					koniec = true;
					tmp->nast = nullptr;		//zabezpieczenie
				}
				else {
					odcz_nazwa_efekt = dane_tekstowe;
					getline(plik, odcz_opis_efekt);
					getline(plik, dane_tekstowe);
					od_mod = atoi(dane_tekstowe.c_str());
					getline(plik, dane_tekstowe);
					od_czas = atoi(dane_tekstowe.c_str());
					getline(plik, dane_tekstowe);
					kod_mod = dane_tekstowe[0];
					getline(plik, dane_tekstowe);
					if (dane_tekstowe == "TAK")
						cel = true;
					else
						cel = false;
					Efekty* nowy_efekt2 = new Efekty(odcz_nazwa_efekt, odcz_opis_efekt, od_mod, od_czas, kod_mod, cel);
					tmp->nast = nowy_efekt2;
					tmp = nowy_efekt2;
				}
			}

			nowy_gracz = new Karta_gracza(nazwa, haslo, pz, max_mana, lvl, EXP, lista_ef_gracza, odcz_umiej, licz_gracz, baza_gr, odcz_walki);	//wewn¹trz konstruktora element jest juz dodawany do bazy graczy
			getline(plik, dane_tekstowe);
		}
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"" << nazwa_pliku << "\"";
	}
	plik.close();
}

void odczyt_walki(string nazwa_pliku, map<int, Walka*> &baza_wal, int &licz_walk, map<int, Karta_gracza*> &baza_gr) {
	/*
	Sposób uporzatkowania pliku wejœciowego:
	-linia z kilkanastoma znakami
	-numer_walki
	-id_gracz_atakujacy
	-id_gracz_broniacy
	-czy_zaakceptowana
	-tabela umiejêtnoœci 

	a)tabela umiejetnoœci:
	-odczytywana w podwójnym for'ze
	-wszystkei umiejetnoœci:
	X1
	Y1
	Z1
	X2
	Y2
	Z2
	...
	*/
	
	fstream plik;
	plik.open(nazwa_pliku, ios::in);					//do odczytu
	if (plik.good()) {
		//odczytywanie informacji z plików
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"" << nazwa_pliku << "\"";
		//zmienne:
		Karta_gracza *atak, *obronca;
		int ID_walki, ID_atak, ID_obrona, oX, oY, oZ;
		bool czy_zaakceptowana;
		Umiejetnosci_skrot tabelaU[4][6];
		Walka* nowa_walka;
		//
		string dane_tekstowe;
		getline(plik, dane_tekstowe);	//->musimy mieæ chocia¿ jedn¹ operacjê odczytu
		if (plik.eof())
			cout << "\nPUSTY PLIK";
		while (plik.eof() != true) {
			getline(plik, dane_tekstowe);
			ID_walki = atoi(dane_tekstowe.c_str());
			getline(plik, dane_tekstowe);
			ID_atak = atoi(dane_tekstowe.c_str());
			atak = znajdz_gracza(ID_atak, baza_gr);
			getline(plik, dane_tekstowe);
			ID_obrona = atoi(dane_tekstowe.c_str());
			obronca = znajdz_gracza(ID_obrona, baza_gr);
			getline(plik, dane_tekstowe);
			if (dane_tekstowe == "TAK")
				czy_zaakceptowana = true;
			else
				czy_zaakceptowana = false;
			//tablica umiejetnosci
			//mo¿liwe s¹ dwie opcje: tylko gracz atakujacy ustawi³ swoje umiejetnoœci, lub obaj gracze ustawili umiejêtnosci
			if (czy_zaakceptowana == true) {	//obaj gracze 
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 6; j++) {
						getline(plik, dane_tekstowe);
						oX = atoi(dane_tekstowe.c_str());
						getline(plik, dane_tekstowe);
						oY = atoi(dane_tekstowe.c_str());
						getline(plik, dane_tekstowe);
						oZ = atoi(dane_tekstowe.c_str());
						tabelaU[i][j] = Umiejetnosci_skrot(oX, oY, oZ);
					}
				}
			}
			else {								//zaakceptowa³ tylko atakujacy -> dla obroñcy wpisujemy pierwsz¹ mo¿liw¹ umiejêtnoœæ wszêdzie
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 6; j++) {
						getline(plik, dane_tekstowe);
						oX = atoi(dane_tekstowe.c_str());
						getline(plik, dane_tekstowe);
						oY = atoi(dane_tekstowe.c_str());
						getline(plik, dane_tekstowe);
						oZ = atoi(dane_tekstowe.c_str());
						tabelaU[i][j] = Umiejetnosci_skrot(oX, oY, oZ);
					}
				}
				for (int i = 2; i < 4; i++) {
					for (int j = 0; j < 6; j++) {
						tabelaU[i][j] = Umiejetnosci_skrot(0,0,0);		//wpisujemy dowolne umiejêtnoœci
					}
				}
			}
			nowa_walka = new Walka(*atak, *obronca, licz_walk, baza_wal, tabelaU);
			getline(plik, dane_tekstowe);
		}
	}
	else{
		cout << "\nBRAK DOSTEPU DO PLIKU \"" << nazwa_pliku << "\"";
	}
	plik.close();
}

Karta_gracza* znajdz_gracza(int numer_gracza, map<int, Karta_gracza*> baza_gr) {
	bool znaleziony = false;
	map<int, Karta_gracza*>::iterator it;
	it = baza_gr.begin();
	while (znaleziony != true) {
		if (it->second->zwroc_ID() == numer_gracza) {
			znaleziony = true;
		}
		else {
			it++;
		}
	} 
	return it->second;
}

void zapis_gracze(string nazwa_pliku, map<int, Karta_gracza*> &baza_gr) {
	/*
	Organizacja pliku baza gracze.txt:
	-ka¿dy nowy gracz zaczyna siê ci¹giem kilkunastu dowolnych znaków
	-nazwa
	-has³o (szyfrowane!)
	-numerID
	-max_P¯
	-max_mana
	-poziom
	-PD
	-umiejêtnoœci
	-walki
	-efekty

	a)umiejêtnoœci:
	X1
	Y1
	Z1
	X2
	Y2
	Z2
	BRAK

	b)walki:
	numerwalki1
	numerwalki2
	numerwalki3
	BRAK

	c)efekty: to samo co przy umiejêtnosciach
	*/
	
	fstream plik;
	plik.open(nazwa_pliku, ios::out);
	if (plik.good()) {
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"" << nazwa_pliku << "\"";
		//zmienne:
		map<int, Karta_gracza*>::iterator it;
		list<Umiejetnosci_skrot*>::iterator it_um;
		list<int>::iterator it_wal;
		Karta_gracza* pomocniczy;
		Efekty* tmp;
		//
		try {
			bool test = baza_gr.empty();
			if (baza_gr.empty() == true) {
				string wyjatek = "\nBAZA GRACZY JEST PUSTA";
				throw wyjatek;
			}
			for (it = baza_gr.begin(); it != baza_gr.end(); it++) {
				pomocniczy = it->second;
				plik << "=====================" << endl;
				plik << pomocniczy->zwroc_nick() << endl;
				plik << szyfruj(pomocniczy->zwroc_haslo(), 8, "0110") << endl;
				plik << pomocniczy->zwroc_ID() << endl;
				plik << pomocniczy->zwroc_pz() << endl;
				plik << pomocniczy->zwroc_mana() << endl;
				plik << pomocniczy->zwroc_lvl() << endl;
				plik << pomocniczy->zwroc_PD() << endl;
				//umiejêtnoœci
				for (it_um = (pomocniczy->zwroc_liste_um()).begin(); it_um != (pomocniczy->zwroc_liste_um()).end(); it_um++) {					
					plik << (*it_um)->zwroc_ID() <<endl;
					plik << (*it_um)->zwroc_poziom() << endl;
					plik << (*it_um)->zwroc_rodzaj() << endl;
				}
				plik << "BRAK" << endl;
				//walki
				for (it_wal = pomocniczy->zwroc_liste_walk().begin(); it_wal != pomocniczy->zwroc_liste_walk().end(); it_wal++) {
					plik << *it_wal << endl;
				}
				plik << "BRAK" << endl;
				//efekty
				tmp = pomocniczy->zwroc_efekty_gracza();
				if (tmp != nullptr) {
					while (tmp != nullptr) {
						plik << tmp->zwroc_nazwa() << endl;
						plik << tmp->zwroc_opis() << endl;
						plik << tmp->zwroc_modyfikator() << endl;
						plik << tmp->zwroc_czas() << endl;
						plik << tmp->zwroc_typ() << endl;
						if (tmp->jaki_cel() == true) {
							plik << "TAK" << endl;
						}
						else {
							plik << "NIE" << endl;
						}
					}
				}
				plik << "BRAK" << endl;
			}
		}
		catch (string w) {
			cout << w << "\n";
		}
	}
	else{
		cout << "\nBRAK DOSTEPU DO PLIKU \"" << nazwa_pliku << "\"";
	}
	plik.close();
}

void zapis_walki(string nazwa_pliku, map<int, Walka*> &baza_wal) {
	/*
	Sposób uporzatkowania pliku wejœciowego:
	-linia z kilkanastoma znakami
	-numer_walki
	-id_gracz_atakujacy
	-id_gracz_broniacy
	-czy_zaakceptowana
	-tabela umiejêtnoœci

	a)tabela umiejetnoœci:
	-odczytywana w podwójnym for'ze
	-wszystkei umiejetnoœci:
	X1
	Y1
	Z1
	X2
	Y2
	Z2
	...
	
	*/
	
	fstream plik;
	plik.open(nazwa_pliku, ios::out);
	if (plik.good()) {
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"" << nazwa_pliku << "\"";
		//zmienne:
		map<int, Walka*>::iterator it;
		Walka* pom;
		Umiejetnosci_skrot tmp;
		//
		try {
			if (baza_wal.empty()) {
				string wyjatek = "\nPUSTA BAZA WALKI";
				throw wyjatek;
			}
			for (it = baza_wal.begin(); it != baza_wal.end(); it++) {
				pom = it->second;
				plik << "=====================" << endl;
				plik << pom->zwroc_numer_walki() << endl;
				plik << pom->zwoc_gracza('A').zwroc_ID() << endl;
				plik << pom->zwoc_gracza('B').zwroc_ID() << endl;
				if (pom->czy_rozegrana()) {
					plik << "TAK" << endl;
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 6; j++) {
							tmp = pom->zwroc_wart_tab(i,j);
							plik << tmp.zwroc_ID() << endl;
							plik << tmp.zwroc_poziom() << endl;
							plik << tmp.zwroc_rodzaj() << endl;
						}
					}
				}
				else {
					plik << "NIE" << endl;
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < 6; j++) {
							tmp = pom->zwroc_wart_tab(i, j);
							plik << tmp.zwroc_ID() << endl;
							plik << tmp.zwroc_poziom() << endl;
							plik << tmp.zwroc_rodzaj() << endl;
						}
					}
				}
				
			}
		}
		catch (string w) {
			cout << w << "\n";
		}
	}
	else {
		cout << "\nBRAK DOSTEPU DO PLIKU \"" << nazwa_pliku << "\"";
	}
	plik.close();
}


//funkcje -> do zapisania na póŸniej
void czekaj(int sekundy) {
	typedef long clock_t;
	clock_t koniec = clock() + sekundy * CLOCKS_PER_SEC;
	while (clock() < koniec)
		continue;
}
std::string szyfruj(std::string tekst, int klucz, string klucz2) {
	string zaszyfrowane = "", pomocnicza = "", koncowka = "", bit_row, prefiks;
	int znak;
	for (int i = 0; i < tekst.length(); i++) {
		znak = tekst[i] + klucz;						//kodowanie ka¿dego znaku szyfrem cezara
		bit_row = DecnaBin(znak);						//zamiana 'tekst' na ci¹g znaków binarnych
		if (bit_row.length() < 8) {
			prefiks = "";
			for (int j = bit_row.length(); j < 8; j++) {
				prefiks = "0" + prefiks;
			}
			bit_row = prefiks + bit_row;				//dopisanie tylu zer na pocz¹tku, aby ka¿dy znak by³ zapisany na 8 bitach
		}
		zaszyfrowane = zaszyfrowane + bit_row;
	}
		//przyk³ad klucza2: 1011 -> 4 cyfry.
		//szyfrowanie XOR -> 1010 + 1011 = 0001
		//podzia³ tekstu na czlony 4-literowe.

		//szyfrowanie XOR
	znak = zaszyfrowane.length() % 4;
	for (int i = zaszyfrowane.length() - znak; i < zaszyfrowane.length(); i++) {
		koncowka = koncowka + zaszyfrowane[i];			//po dodaniu podzia³u na 8 bitów ka¿de s³owo nie jest to ju¿ wymagane... ale zostawiam, bo mo¿e kiedyœ bêdzie trzeba przerobiæ na np. 9 bitów.
	}
	for (int i = 0; i < (zaszyfrowane.length() / 4); i++) {
		if (zaszyfrowane[4 * i] == klucz2[0])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (zaszyfrowane[4 * i + 1] == klucz2[1])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (zaszyfrowane[4 * i + 2] == klucz2[2])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (zaszyfrowane[4 * i + 3] == klucz2[3])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
	}
	zaszyfrowane = pomocnicza + koncowka;

	//szyfrowanie XOR - koniec

	return zaszyfrowane;
}
std::string deszyfruj(std::string szyfrowana, int klucz, string klucz2) {	//do dokoñczenia
	string odszyfrowane = "", koncowka = "", pomocnicza = "";
	int znak;
	char znakch;
	//deszyfracja XOR
	znak = szyfrowana.length() % 4;
	for (int i = szyfrowana.length() - znak; i < szyfrowana.length(); i++) {
		koncowka = koncowka + szyfrowana[i];			//po dodaniu podzia³u na 8 bitów ka¿de s³owo nie jest to ju¿ wymagane... ale zostawiam, bo mo¿e kiedyœ bêdzie trzeba przerobiæ na np. 9 bitów.
	}
	for (int i = 0; i < (szyfrowana.length() / 4); i++) {
		if (szyfrowana[4 * i] == klucz2[0])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (szyfrowana[4 * i + 1] == klucz2[1])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (szyfrowana[4 * i + 2] == klucz2[2])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
		if (szyfrowana[4 * i + 3] == klucz2[3])
			pomocnicza = pomocnicza + "0";
		else
			pomocnicza = pomocnicza + "1";
	}
	szyfrowana = pomocnicza + koncowka;

	//deszyfracja XOR - koniec

	//szyfr sk³¹da siê z pewnej liczby znaków zaszyfrowanych kodem ACII na binarnym po 8 bitów ka¿dy.

	try {
		if ((szyfrowana.length() % 8) != 0) {
			string wyjatek = "\nBLAD SZYFROWANIA!";
			throw wyjatek;
		}
		for (int i = 0; i < (szyfrowana.length() / 8); i++) {		//jest podzielne przez 8
			pomocnicza = "";
			for (int j = 0; j < 8; j++) {
				pomocnicza = pomocnicza + szyfrowana[8 * i + j];
			}
			znak = BinnaDec(pomocnicza);
			znak = znak - klucz;
			znakch = znak;
			odszyfrowane = odszyfrowane + znakch;
			//znak = szyfrowana[i] - klucz;
		}

	}
	catch (string w) {
		cout << w;
		return "BLAD";
	}

	return odszyfrowane;
}
std::string DecnaBin(int liczbaDec) {
	if (liczbaDec == 0) 
		return "0";
	if (liczbaDec == 1) 
		return "1";

	if (liczbaDec % 2 == 0)
		return DecnaBin(liczbaDec / 2) + "0";
	else
		return DecnaBin(liczbaDec / 2) + "1";
}
int BinnaDec(std::string liczbaBin) {
	int result = 0, pow = 1;
	for (int i = liczbaBin.length() - 1; i >= 0; --i, pow <<= 1)
		result += (liczbaBin[i] - '0') * pow;

	return result;
}

//ŒMIETNIK:
/*
string opis;
Efekty* lista_ef;
Umiejetnosci_ofensywne test(20, 2, 1, "ciosII", opis, nullptr, 5);
Umiejetnosci test2();
baza_umiejestosci[0][0].push_back(&test);



delete &baza_gracze;
//delete &zalogowani_gracze;
delete &baza_walki;
delete &baza_umiejestosci;


string testowa = "Aa15@", pom;
pom = szyfruj(testowa, 8, "1011");
cout << pom << "\n" << deszyfruj(pom, 8, "1011");

czekaj(20);


//odczytywanie zawartoœci bazy_umiejêtnoœci po dodaniu wszystkich plików
vector<Umiejetnosci*>::iterator it;
Umiejetnosci* tmp;
if (baza_umiejestosci.empty() == false) {
for (int i = 0; i < 7; i++) {
for (int j = 0; j < 5; j++) {
for (it = baza_umiejestosci[i][j].begin(); it < baza_umiejestosci[i][j].end(); it++) {
tmp = *it;
tmp->wypisz_informacje();
cout << "\n\n";
//czekaj(2);
}
}
}
}
else {
std::cout << "\nBRAK UMIEJETNOSCI";
}
//czekaj(20);
//system("pause");



*/
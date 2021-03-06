#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Walka.h"
#include <regex>

using namespace std;

//deklaracje funkcji

void czekaj(int);		 //funckja s�u�y do zatrzymania programu na 'n' sekund
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
	srand(time(NULL));
	std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiejestosci; 		//dla uproszczenia: zapis b�dzie: baza_umiejetnosci[rodzaj][poziom][id] => baza_umiejetnosci[z][y][x]
	std::map<int, Karta_gracza*> baza_gracze;	
	//std::set<int> zalogowani_gracze;	-> na przysz�o��
	std::map<int, Walka*> baza_walki;
	int ostatni_gracz = 0, ostatnia_walka = 0;
	std::list<Umiejetnosci_skrot*> startowe_umiejetnosci_gracza;
	//ustawianie bazowego rozmiaru vetora umeij�tno�ci [0-6][0-4][n]
	baza_umiejestosci.resize(7);
	for (int i = 0; i < 7; i++){
		baza_umiejestosci[i].resize(5);		//zapami�ta� -> patrze�, czy zamiast resize nei pojawi�o si� 'reserve' -.-
		}
	//tworzenie bazowej listy umiej�tno�ci -> dla nowych graczy
	for (int i = 0; i < 6; i++) {
		Umiejetnosci_skrot* tmp_umiej_skrot = new Umiejetnosci_skrot(0, 0, i);
		startowe_umiejetnosci_gracza.push_back(tmp_umiej_skrot);
	}
	//==============================================================================================================================================================
	//ODCZYTYWANIE BAZ DANYCH
	//==============================================================================================================================================================
	//odczyt umiej�tnosci:
	odczyt_umiejetnosci("baza umiejetnosci.txt", baza_umiejestosci);
	//odczyt gracze:
	odczyt_gracze("baza gracze.txt", baza_gracze, ostatni_gracz);
	//odczyt walki:
	odczyt_walki("baza walki.txt", baza_walki, ostatnia_walka, baza_gracze);
	czekaj(2);
	
	//==============================================================================================================================================================
	//FUNKCJA W�A�CIWA
	//==============================================================================================================================================================	
	char znak_nawigacji;
	bool koniec, wyjscie, znaleziono;
	string nick, haslo, smieci;
	regex wzorzec("\\w* to \\w*");
	regex nick_wzor("[A-Z](.){4,19}"); 
	regex haslo_wzor("(.){8,20}");
	Karta_gracza* pomocnicza_karta = nullptr;
	map<int, Karta_gracza*>::iterator it;
	Karta_gracza* aktualny_gracz = nullptr;
	int licz_ID = 0;
	int licz_rodzaj = 0;
	int ID_gracz;
	int licznik_prob = 0;
	string imie_gracz;
	Walka* aktualna_walka = nullptr;
	list<int>::iterator it_walki_gracza;
	map<int, Walka*>::iterator it_walka;

	koniec = false;
	while (koniec != true) {
		system("cls");
		cout << "Witaj wedrowcze!\nWybierz jedna z opcji:\nZ-aloguj\nR-ejestracja\nW-yjscie\n\t";
		cin >> znak_nawigacji;
		switch (znak_nawigacji) {
			//==============================================================================================================================================================
			//==============================================================================================================================================================
			//==============================================================================================================================================================
		case 'z':
		case 'Z':			//zaloguj
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
			//Na tym etapie gracz jest ju� zalogowany i gotowy do podejmowania akcji
			//==============================================================================================================================================================
				while (koniec != true) {
					system("cls");
					cout << "\nNo dobrze bohaterze. Jakie sa twoje nastepne kroki?";
					cout << "\n\n\tP-rzejrzyj swoje walki\n\tR-zuc wyzwanie\n\tI-nformacje\n\tN-auka nowych umiejetnosci\n\tW-yloguj\n\n\t";
					cin >> znak_nawigacji;
					switch (znak_nawigacji) {
						//==============================================================================================================================================================
						//==============================================================================================================================================================
					case 'p':
					case 'P':	//przegladanie walk + mo�liwa akceptacja/odrzucenie
						/*
						-najpierw mo�emy przegl�da� rzucone przez nas (i nam) walki -> podobnie jak z umeij�tno�ciami
						-je�eli walki zosta�y rozstrzygni�te to mo�liwe b�dzie obejrzenie ich  rezultat�w
						-je�eli kto� rzuci� wyzwanie nam (priorytet) a my�my jeszcze nie zaakceptowali to mo�emy je rozegra�
						*/
						system("cls");
						cout << "\nNawigacja:\n\n\tK-olejna walka\n\tP-oprzednia walka\n\tO-dpowiedz na wyzwanie (tam gdzie to mozliwe)\n\tZ-obacz walke (tam gdzie to mozliwe)\n\tW-roc do wczesniejszych opcji";
						czekaj(2);
						if (aktualny_gracz->zwroc_liste_walk().empty() != true) {
							it_walki_gracza = aktualny_gracz->zwroc_liste_walk().begin();

							while (znak_nawigacji != 'W' && znak_nawigacji != 'w') {
								system("cls");
								cout << "\nNawigacja:\n\n\tK-olejna walka\n\tP-oprzednia walka\n\tO-dpowiedz na wyzwanie (tam gdzie to mozliwe)\n\tZ-obacz walke (tam gdzie to mozliwe)\n\tW-roc do wczesniejszych opcji";
								aktualna_walka = baza_walki[*it_walki_gracza];
								//znaleziono = false;	//przyjmujemy, i� walka o podanym numerze znajduje si� w�r�d baz walki
								//while (znaleziono != true) {

								//}
								//znaleziono = false;
								aktualna_walka->wypisz_informacje();
								cout << "\n\n\t";
								cin >> znak_nawigacji;
								switch (znak_nawigacji) {
								case 'k':
								case 'K':	//kolejna walka
									it_walki_gracza++;
									if (it_walki_gracza == aktualny_gracz->zwroc_liste_walk().end()) {
										cout << "\n\nTo juz Twoja ostatnia walka.";
										it_walki_gracza--;
										czekaj(2);
									}
									break;
								case 'p':
								case 'P':	//poprzednia walka
									if (it_walki_gracza == aktualny_gracz->zwroc_liste_walk().begin()) {
										cout << "\n\nNie masz wczesniejszych walk.";
										czekaj(2);
									}
									else {
										it_walki_gracza--;
									}
									break;
								case 'o':
								case 'O':	//odpowiadanie na wyzwaie (jeszcze nie zaakceptowana)
									if (aktualna_walka->czy_rozegrana()) {	//walka jest ju� rozegrana
										cout << "\nTa walka jest juz rozegrana";	
										czekaj(2);
									}
									else {
										if (aktualna_walka->zwoc_gracza('A').zwroc_ID() == aktualny_gracz->zwroc_ID()) {	//aktualny gracz by� wyzywaj�cym -> to ten drugi gracz ma odpowiedzie� na wyzwanie
											cout << "\n\tNo nie mozesz sobie samemu odpowiedziec na wyzwanie...";
											czekaj(2);
										}
										else {		//odpowiadamy na wyzwanie
											system("cls");
											cout << "\nZostales wyzwany przez: " << aktualna_walka->zwoc_gracza('A').zwroc_nick();
											cout << "\n\nCzy chcesz podjac wyzwanie? (T/N)\n\t";
											cin >> znak_nawigacji;
											if (znak_nawigacji == 'T' || znak_nawigacji == 't') {
												aktualna_walka->ustaw_zaakceptowanie(true);
												aktualna_walka->wybor_umiejetnosci(false, *aktualny_gracz, baza_umiejestosci);
												aktualna_walka->ustaw_rozegranie(true, baza_umiejestosci);
											}
											else if (znak_nawigacji == 'N' || znak_nawigacji == 'n') {
												aktualna_walka->ustaw_zaakceptowanie(false);
												aktualna_walka->ustaw_rozegranie(true, baza_umiejestosci);
											}
											else {
												cout << "\n\tNiepoprawna opcja";
												czekaj(2);
											}
										}
										znak_nawigacji = 'O';
									}
									break;
								case 'z':
								case 'Z':	//zobaczenie walki (ju� rozegranej)
									//poziom--!
									if (aktualna_walka->czy_rozegrana()) {
										if (aktualna_walka->czy_zaakceptowana()) {
											//zosta�a ju� zaakceptowana i rozegrana -> wy�wietlamy walk�
											cout << "\n\nNoo.. To teraz sie zacznie!";
											czekaj(2);
											aktualna_walka->wyswietl_walke(baza_umiejestosci);
										}
										else {
											//przeciwnik odrzuci� wyzwanie
											cout << "\n\n\tNie wierze, ze to mowie, ale przeciwnik\n\tuciekl z podkulonym ogonem...";
											czekaj(2);
										}
									}
									else {
										cout << "\n\nTa walka nie zostala jeszcze zaakceptowana.";
										czekaj(2);
									}
									break;
								case 'w':
								case 'W':	//wyj�cie
									cout << "\nOdpocznij sobie...";
									czekaj(2);
									break;
								default:
									cout << "\n\tNie, to nie jest prawidlowa opcja...";
									czekaj(2);
									break;
								}
							}
						}
						else {
							cout << "\n\nNie posiadasz zadnych walk.";
							czekaj(3);
						}
						break;
						//==============================================================================================================================================================
						//==============================================================================================================================================================
					case 'r':
					case 'R':	//rzucanie wyzwa� konkretnemu (numer/nick) albo losowemu przeciwnikowi
						//W jaki spos�b b�dziemy wy�wietlali graczy do wyzwania? 
						//Mo�liwo�� wyzwania gracza z imienia/numeru
						//Mo�liwo�� wyzwania losowego przeciwnika 

						//UWAGA: je�eli gracz wyzwie wszystkich graczy to nie mo�e wyzwa� nowych p�ki oni nie zaakceptuj�/odrzuc� walk
						//UWAGA2: p�ki co nie ma �ADNYCH algorytm�w do wybierania przeciwnik�w z pewnego przedzia�u poziomowego
						znaleziono = false;
						while (znak_nawigacji != 'W' && znaleziono != true) {
							system("cls");
							cout << "\n\tNareszcie! Teraz pozostaje tylko zdecydowac z kim chcesz walczyc.\n\tWpisz w jaki sposob chcesz wybrac swojego przeciwnika:\n\n\tI-wpisz imie przeciwnika\n\tN-podaj numer przeciwnika\n\tL-osowy przeciwnik\n\tW-ybiegnij z krzykiem (wyjscie)\n\n\t";
							cin >> znak_nawigacji;
							getline(cin, smieci);
							switch (znak_nawigacji) {
							case 'i':
							case 'I':	//wyzywamy przeciwnika poprzez podanie jego imienia
								system("cls");
								cout << "\nPodaj imie swojego przeciwnika:\t";
								getline(cin, imie_gracz);
								it = baza_gracze.begin();
								znaleziono = false;
								koniec = false;
								try {
									while (koniec != true && znaleziono != true) {

										if (it->second->zwroc_nick() == imie_gracz) {
											//trzeba sprawdzi�, czy gracz nie posaida juz takiej walki
											//zaczynamy sprawdzac, czy walczacy nie wyzywa siebie lub kogo� innego po raz drugi
											it_walki_gracza = aktualny_gracz->zwroc_liste_walk().begin();
											koniec = false;
											if (aktualny_gracz->zwroc_ID() == it->second->zwroc_ID()) {
												string w2 = "\n\n\tJesli chesz popelnic samobojstwo to nie tedy droga...";
												throw (w2);
											}
											while (koniec != true) {
												if (it_walki_gracza == aktualny_gracz->zwroc_liste_walk().end()) {
													koniec = true;
												}
												else if (baza_walki[*it_walki_gracza]->zwoc_gracza('A').zwroc_ID() == it->second->zwroc_ID() || baza_walki[*it_walki_gracza]->zwoc_gracza('B').zwroc_ID() == it->second->zwroc_ID()) {
													string w1 = "\n\nCierpliwosci, ta postac juz wyzwales!";
													throw (w1);
												}
												else {
													it_walki_gracza++;
												}
											}
											koniec = false;
											//koniec sprawdzania
											cout << "\nCzy na pewno chcesz wyzwac " << imie_gracz << "?  (T/N)\n\t";
											cin >> znak_nawigacji;
											if (znak_nawigacji == 'T') {
												pomocnicza_karta = it->second;
												cout << "\nOho! zawsze sie ekscytuje w tym momencie!";
												czekaj(2);
												znaleziono = true;
											}
											else if (znak_nawigacji == 'N') {
												cout << "\nNie ma problemu, nie spiesz sie.";
												czekaj(2);
												koniec = true;
											}
											else {
												cout << "\n\tNaucz sie wybierac poprawne opcje!";
												czekaj(2);
											}
										}
										else {
											it++;
											if (it == baza_gracze.end()) {
												cout << "\n\nNie pamietam tej postaci...";
												czekaj(2);
												koniec = true;
											}
										}
									}
								}
								catch (string wyjatek) {
									cout << wyjatek;
									czekaj(2);
								}
								koniec = false;
								break;
							case 'n':
							case 'N':		//wybieramy przeciwnika poprzez podanie jego ID
								system("cls");
								cout << "\nPodaj numer swojego przeciwnika:\t";
								getline(cin, imie_gracz);
								ID_gracz = atoi(imie_gracz.c_str());
								if (ID_gracz == 0) {
									cout << "\n\n\t...Naprawde... czego nie rozumiesz w slowie \"numer\"?";
									czekaj(2);
								}
								else {
									try {
										//zaczynamy sprawdzac, czy walczacy nie wyzywa siebie lub kogo� innego po raz drugi
										it_walki_gracza = aktualny_gracz->zwroc_liste_walk().begin();
										koniec = false;
										if (aktualny_gracz->zwroc_ID() == ID_gracz) {
											string w2 = "\n\n\tJesli chesz popelnic samobojstwo to nie tedy droga...";
											throw (w2);
										}
										while (koniec != true) {
											if (it_walki_gracza == aktualny_gracz->zwroc_liste_walk().end()) {
												koniec = true;
											}
											else if (baza_walki[*it_walki_gracza]->zwoc_gracza('A').zwroc_ID() == ID_gracz || baza_walki[*it_walki_gracza]->zwoc_gracza('B').zwroc_ID() == ID_gracz) {
												string w1 = "\n\nCierpliwosci, ta postac juz wyzwales!";
												throw (w1);
											}
											else {
												it_walki_gracza++;
											}
										}
										//koniec sprawdzania
										znaleziono = false;
										koniec = false;
										while (znaleziono != true && koniec != true) {
											znaleziono = false;

											cout << "\nCzy na pewno chcesz wyzwac " << baza_gracze[ID_gracz]->zwroc_nick() << "?  (T/N)\n\t";
											cin >> znak_nawigacji;
											if (znak_nawigacji == 'T') {
												pomocnicza_karta = baza_gracze[ID_gracz];
												cout << "\nOho! zawsze sie ekscytuje w tym momencie!";
												czekaj(2);
												znaleziono = true;
											}
											else if (znak_nawigacji == 'N') {
												cout << "\nNie ma problemu, nie spiesz sie.";
												czekaj(2);
												koniec = true;
											}
											else {
												cout << "\n\tNaucz sie wybierac poprawne opcje!";
												czekaj(2);
											}
										}
									}
									catch (string wyjatek) {
										cout << wyjatek;
										czekaj(2);
									}
									}
								koniec = false;
								break;
							case 'l':
							case 'L':	//wyzywamy losowego przeciwnika
								ID_gracz = (rand()%ostatni_gracz) + 1;
								//trzeba sprawdzi�, czy gracz nie posaida juz takiej walki
								system("cls");
								znaleziono = false;
								koniec = false;
								//zaczynamy sprawdzac, czy walczacy nie wyzywa siebie lub kogo� innego po raz drugi
								it_walki_gracza = aktualny_gracz->zwroc_liste_walk().begin();
								licznik_prob = 0;
								try {
									while (koniec != true) {
										if (licznik_prob > 30) {
											string w3 = "\n\nOjc! Widocznie nikt wiecej nie chce Cie wyzwac... Wroc pozniej.";
											throw w3;
										}
										if (aktualny_gracz->zwroc_ID() == ID_gracz) {
											ID_gracz = (rand() % ostatni_gracz) + 1;
											it_walki_gracza = aktualny_gracz->zwroc_liste_walk().begin();
											licznik_prob++;
										}
										if (it_walki_gracza == aktualny_gracz->zwroc_liste_walk().end()) {
											koniec = true;
										}
										else if (baza_walki[*it_walki_gracza]->zwoc_gracza('A').zwroc_ID() == ID_gracz || baza_walki[*it_walki_gracza]->zwoc_gracza('B').zwroc_ID() == ID_gracz) {
											ID_gracz = (rand() % ostatni_gracz) + 1;
											it_walki_gracza = aktualny_gracz->zwroc_liste_walk().begin();
											licznik_prob++;
										}
										else {
											it_walki_gracza++;
										}
									}
									koniec = false;
									znaleziono = false;
									//koniec sprawdzania
									while (znaleziono != true && koniec != true) {

										cout << "\nCzy na pewno chcesz wyzwac " << baza_gracze[ID_gracz]->zwroc_nick() << "?  (T/N)\n\t";
										cin >> znak_nawigacji;
										if (znak_nawigacji == 'T') {
											pomocnicza_karta = baza_gracze[ID_gracz];
											cout << "\nOho! zawsze sie ekscytuje w tym momencie!";
											czekaj(2);
											znaleziono = true;
										}
										else if (znak_nawigacji == 'N') {
											cout << "\nNie ma problemu, nie spiesz sie.";
											czekaj(2);
											koniec = true;
										}
										else {
											cout << "\n\tNaucz sie wybierac poprawne opcje!";
											czekaj(2);
										}
									}
								}
								catch (string wyjatek) {
									cout << wyjatek;
									czekaj(2);
								}
								koniec = false;
								break;
							case 'w':
							case 'W':	//wyj�cie z rzucania wyzwa�
								system("cls");
								cout << "\n\tHa! To bylo ciekawe! Ja chce jeszcze raz!";
								czekaj(2);
								znaleziono = false;
								znak_nawigacji = 'W';
								break;
							default:
								cout << "\n\n\tPrzyznaj sie: specjalnie wybierasz niepoprawna opcje...";
								czekaj(2);
								znaleziono = false;
								break;
							}
						}
						if (znaleziono == true) {
							//wyzwanie gracza;
							aktualna_walka = new Walka(*aktualny_gracz, *pomocnicza_karta, ostatnia_walka, baza_walki);
							aktualna_walka->wybor_umiejetnosci(true, *aktualny_gracz, baza_umiejestosci);
							//zako�czenie
							cout << "\n\nTeraz pozostaje tylko czekac, az przeciwnik rozpatrzy wyzwanie.";
							czekaj(3);
						}
						pomocnicza_karta = nullptr;
						aktualna_walka = nullptr;
						znak_nawigacji = 'R';
						break;
						//==============================================================================================================================================================
						//==============================================================================================================================================================
					case 'i':
					case 'I':	//informacje
						//Mo�liwe informacje: 
						/*
						M-mechanika walki
						H-historia �wiata
						U-umiej�tno�ci
						@-ukryta opcja maj�ca przedstawi� autora :P 
						*/
						while (koniec != true) {
							system("cls");
							cout << "Wiedza to wyjatkowo silne narzedzie... O czym chcesz sie dowiedzeic?";
							cout << "\n\n\tM-echanika walki\n\tH-istoria swiata\n\tU-miejetnosci\n\tW-wyjscie\n\n\t";
							cin >> znak_nawigacji;
							switch (znak_nawigacji) {
								//==============================================================================================================================================================
							case 'm':
							case 'M':	//informacje o mechanice walki
								znak_nawigacji = 'O';
								while (znak_nawigacji != 'W' && znak_nawigacji != 'w') {
									system("cls");
									cout << "Kiedy dochodzi do starcia naprzeciw siebie staje dwoje postaci: wyzywajacy\n(atakujacy) i wyzwany (broniacy sie). Kazdy z nich musi za wczasu przygotowac\n";
									cout << "swoja strategie na walke. W tym celu oboje ustalaja w tajemnicy przed\nprzeciwnikiem strategie walki, to znaczy, ktorych atakow, a ktorych obron uzyje\n";
									cout << "kiedy.\n\nCzesc atakow jest SILNA, przez co ciezko zablokowac uderzenia a jedynie\nmozna przed nimu uskoczyc. Inne z kolei sa SZYBKIE, przez co odskok jest\n";
									cout << "zbyt wolny do wykonania, ale mozna zablokowac nadchodzace uderzenia.\nPozostaja jeszcze ataki MAGICZNE przed ktorymi jedyna ochrona jest odpowiednia\n";
									cout << "koncentracja, kontrzaklecie i tym podobne. Mozna stwierdzic, iz istnieja\ntrzy style walki, wedlug ktorych pogrupowane sa umiejetnosci ofensywne.\n";
									cout << "i defensywne. I tak aby obronic sie przed atakiem z jednego stylu najlepiej\nuzyc obronyz tego samego stylu.\n\nCelem walczacych jest przewidzenie czego i kiedy moze probowac\n";
									cout << "uzyc i odpowiedziec odpowiednia obrona. Oczywiscie czesc umiejetnosci\ndefensywnych umozliwia unikniecie czesci obrazen z innych stylow. Jednakze to\nnie";
									cout << "wystarczy aby uniknac wywolania dodatkowych EFEKTOW.\n\nEfekty to rozne dodatkowe modyfikatory wplywajace przez pewien okreslony\nczas na pechowego";
									cout << "(albo szczesliwego, gdyz istnieja pozytywne efekty)\nwalczacego. Dla przykladu jeden z efektow oslabia na dwie tury obrazenia\nprzeciwnika o pewna wartosc.";
									cout << " Czesc umiejetnosci moze przypisac komus efekt.\nAby tak sie stalo umiejetnosc musi byc innego stylu niz umiejetnosc defensywna\nprzeciwnika. Jednak uwazaj,";
									cout << " bo jesli broniacy sie przewidzi twoje zagranie\ni odpowiednio zablokuje twoj atak sam aktywuje efekt umiejetnosci defensywnej!\nTo dziala w obie strony.\n\n";
									cout << "Walka konczy sie w momencie, gdy ktorys z walczacych padnie nieprzytomny\n(straci wszystkie punkty zycia), albo minie okreslona ilosc tur. W drugim\n";
									cout << "przypadku wygrywa walczacy, ktory procentowo utracil mniej zdrowia.";
									cout << "\n\n\tKiedy poczujesz sie juz dosc pewnie wpisz: \"W\"\n\n\t";
									cin >> znak_nawigacji;
									}
								znak_nawigacji = 'M';
								break;
								//==============================================================================================================================================================
							case 'h':
							case 'H':	//informacje o historii
								znak_nawigacji = 'O';
								while (znak_nawigacji != 'W') {
								system("cls");
								cout << "\n\tA, a, aaa! Jeszcze nie wszsytko jest gotowe.\n\n\tAle nie martw sie, bo to alternatywna historia, ktora sami tworzycie.\n\tBo widzisz... zastanawialismy sie, co by bylo, gdyby dac obu strona\n\tjeszcze jedna szanse. Streszczajac:";
								cout << "\n\n\t-Jestesmy na archipelagu \"Slotwa\",\n\t-Archipelag sklada sie z 10 dosc sporych wysp,\n\t-W konflikcie biora udzial dwie strony: Bestie i Sojusz,\n\n\n\tA prawdziwa historie bedzie mozna poznac pozniej.";
								cout << "\n\nAby powrocic wpisz: \"W\"\n\t";
									cin >> znak_nawigacji;
								}
								znak_nawigacji = 'H';
								break;
								//==============================================================================================================================================================
							case 'u':
							case 'U':		//informacje o wszystkich dost�pnych umiej�tno�ciach
								znak_nawigacji = 'O';	
								licz_ID = 0;
								licz_rodzaj = 0;
									system("cls");
									cout << "Nawigacja:\n\tK-olejna\n\tP-oprzednia\n\tW-yscie";
									czekaj(3);
									while (znak_nawigacji != 'W') {
										system("cls");
										cout << "Nawigacja:\n\tK-olejna\n\tP-oprzednia\n\tW-yscie";
										cout << "\n\n\n";
										for (int y = 0; y < 5; y++) {
											baza_umiejestosci[licz_rodzaj][y][licz_ID]->wypisz_informacje();
											cout << "\n\n";
										}
											cout << "\n\n\t";
											cin >> znak_nawigacji;
											switch (znak_nawigacji) {
											case 'k':
											case 'K':		//przej�cie do kolejnej umiej�tno�ci
												if (licz_ID == baza_umiejestosci[licz_rodzaj][0].size() -1 ) {
													if (licz_rodzaj == 5) {	//jeszcze nie uwzgledaniamy specjalnych!
														cout << "\n\tTo juz ostatnie umiejetnosci...";
														czekaj(2);
													}
													else {
														licz_rodzaj++;
														licz_ID = 0;
													}
												}
												else {
													licz_ID++;
												}
												break;
											case 'p':
											case 'P':	//przej�cie do poprzednich umeij�tno�ci
												if (licz_ID == 0) {
													if (licz_rodzaj == 0) {
														cout << "\n\tWczesniej juz nic nie ma...";
														czekaj(2);
													}
													else {
														licz_rodzaj--;
														licz_ID = baza_umiejestosci[licz_rodzaj][0].size() - 1;
													}
												}
												else {
													licz_ID--;
												}

												break;
											case 'w':
											case 'W':	//wyj�cie z informacji o umiej�tno�ciach
												cout << "\n\tCzas wrocic do walki!";
												czekaj(2);
												cout << "\nZyjemy by sluzyc";
												break;
											default:
												cout << "\nNiepoprawna opcja";
												czekaj(2);
												break;
											}
										}
								znak_nawigacji = 'U';
								break;
								//==============================================================================================================================================================
							case '@':		//secret
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
								//==============================================================================================================================================================
							case 'w':
							case 'W':	//wyj�cie z informacji
								cout << "\n\nNo dobrze, pamietaj, ze zawsze mozesz tu wrocic.";
								koniec = true;
								czekaj(2);
								break;
								//==============================================================================================================================================================
							default:
								cout << "\n\n\tWiedza i ignorancja nie powinny chodzic ze soba w parze...";
								czekaj(2);
								break;
								//==============================================================================================================================================================
							}
						}
						koniec = false;
						break;
						//==============================================================================================================================================================
						//==============================================================================================================================================================
					case 'n':
					case 'N':	//nauka nowych umiej�tno�ci
						cout << "\n\n\tChwilowo out of orded";
						czekaj(2);
						break;
						//==============================================================================================================================================================
						//==============================================================================================================================================================
					case 'w':
					case 'W':	//wylogowanie
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
						//==============================================================================================================================================================
					default:
						cout << "\n\n\tWybierz poprawna opcje... \"bohaterze\"";
						czekaj(2);
						break;
					}
					//==============================================================================================================================================================
					//==============================================================================================================================================================
					//getline(cin, smieci);
				}

			}
			aktualny_gracz = nullptr;
			koniec = false;
			break;
			//==============================================================================================================================================================
			//==============================================================================================================================================================
			//==============================================================================================================================================================
		case 'r':
		case 'R':	//rejestracja
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
		case 'w':
		case 'W':		//wyjscie z programu
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
	//ZAPIS BAZ DANYCH DO PLIK�W + ZAKO�ZENIE DZIA�ANIA PROGRAMU
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
	Organizacja pliku z umiej�tnosciami:
	-ka�da nowa umiej�tno�� zaczyna si� od kilkunastu znak�w '=' -> symbolizuje niepusto�� pliku
	-w ka�dej linii znajduj� si� dane potrzebne do konstruktora (int numer, int lvl, int typ, std::string nazwa_um, std::string opis_um, Efekty* lista_ef, dodatkowe)
	-po opisie nale�y umie�ci� znak D, O lub S dla odpowiedniego rodzaju umeij�tno�ci -> decyduje ile kolejnych linii zawiera potrzebne dla konstruktora informacje
	-p�niej nast�puje utworzenie listy efekt�w:
	a)kolejno�� danych (nazwa,opis,modyfikator, czas, typ_modyfikatora(tak samo jak dla konstruktora))
	b)je�li nie ma dalszych umiej�tno�ci (czyli jesli ich nie ma w og�le tak�e) to piszemy lini� zawieraj�c� "BRAK"
	c)otrzymujemy list� efekt�w, kt�r� wykorzystujemy przy konstruktorze
	*/
	//
	if (plik.good()) {
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \""<< nazwa_pliku <<"\"";
		//odczytywanie informacji z plik�w
		int odcz_ID, odcz_lvl, odcz_rodzaj, odcz_dmg, odcz_os, odcz_of, odcz_om, od_mod, od_czas;
		string odcz_nazwa, odcz_opis, odcz_nazwa_efekt, odcz_opis_efekt;
		Efekty* pocz_listy_efektow, *tmp = nullptr;
		bool brak, cel;
		char kod_mod, rodzaj_um;
		string dane_tekstowe;
		getline(plik, dane_tekstowe);	//->musimy mie� chocia� jedn� operacj� odczytu
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
			//Efekty						kolejno�� jak dla konstuktora
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
			//posiadamy teraz list� efekt�w -> ostatni element konstruktora
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
	-ka�dy nowy gracz zaczyna si� ci�giem kilkunastu dowolnych znak�w
	-nazwa
	-has�o (szyfrowane!)
	-numerID
	-max_P�
	-max_mana
	-poziom
	-PD
	-umiej�tno�ci
	-walki
	-efekty

	a)umiej�tno�ci:
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

	c)efekty: to samo co przy umiej�tnosciach
	*/
	
	fstream plik;
	plik.open(nazwa_pliku, ios::in);					//do odczytu
	if (plik.good()) {
		//odczytywanie informacji z plik�w
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
		getline(plik, dane_tekstowe);	//->musimy mie� chocia� jedn� operacj� odczytu
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

			nowy_gracz = new Karta_gracza(nazwa, haslo, pz, max_mana, lvl, EXP, lista_ef_gracza, odcz_umiej, licz_gracz, baza_gr, odcz_walki);	//wewn�trz konstruktora element jest juz dodawany do bazy graczy
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
	Spos�b uporzatkowania pliku wej�ciowego:
	-linia z kilkanastoma znakami
	-numer_walki
	-id_gracz_atakujacy
	-id_gracz_broniacy
	-czy_zaakceptowana
	-tabela umiej�tno�ci 

	a)tabela umiejetno�ci:
	-odczytywana w podw�jnym for'ze
	-wszystkei umiejetno�ci:
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
		//odczytywanie informacji z plik�w
		cout << "\nPRZYZNANO DOSTEP DO PLIKU \"" << nazwa_pliku << "\"";
		//zmienne:
		Karta_gracza *atak, *obronca;
		int ID_walki, ID_atak, ID_obrona, oX, oY, oZ;
		bool czy_zaakceptowana, czy_rozegrana;
		Umiejetnosci_skrot tabelaU[4][6];
		Walka* nowa_walka;
		//
		string dane_tekstowe;
		getline(plik, dane_tekstowe);	//->musimy mie� chocia� jedn� operacj� odczytu
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
			getline(plik, dane_tekstowe);
			if (dane_tekstowe == "TAK")
				czy_rozegrana = true;
			else
				czy_rozegrana = false;

			//tablica umiejetnosci
			//mo�liwe s� dwie opcje: tylko gracz atakujacy ustawi� swoje umiejetno�ci, lub obaj gracze ustawili umiej�tnosci
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
			else {								//zaakceptowa� tylko atakujacy -> dla obro�cy wpisujemy pierwsz� mo�liw� umiej�tno�� wsz�dzie
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
						tabelaU[i][j] = Umiejetnosci_skrot(0,0,0);		//wpisujemy dowolne umiej�tno�ci
					}
				}
			}
			nowa_walka = new Walka(*atak, *obronca, licz_walk, baza_wal, tabelaU, czy_zaakceptowana, czy_rozegrana);
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
	-ka�dy nowy gracz zaczyna si� ci�giem kilkunastu dowolnych znak�w
	-nazwa
	-has�o (szyfrowane!)
	-numerID
	-max_P�
	-max_mana
	-poziom
	-PD
	-umiej�tno�ci
	-walki
	-efekty

	a)umiej�tno�ci:
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

	c)efekty: to samo co przy umiej�tnosciach
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
				//umiej�tno�ci
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
	Spos�b uporzatkowania pliku wej�ciowego:
	-linia z kilkanastoma znakami
	-numer_walki
	-id_gracz_atakujacy
	-id_gracz_broniacy
	-czy_zaakceptowana
	-czy_rozegrana
	-tabela umiej�tno�ci

	a)tabela umiejetno�ci:
	-odczytywana w podw�jnym for'ze
	-wszystkei umiejetno�ci:
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
				if (pom->czy_zaakceptowana())					//zaakceptowana idzie pierwsze
					plik << "TAK" << endl;	
				else
					plik << "NIE" << endl;
				if (pom->czy_rozegrana()) {						//rozegrana jest kolejne i od niego zale�y ile umiej�tno�ci jest zapisanych
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


//funkcje -> do zapisania na p�niej
void czekaj(int sekundy) {
	typedef long clock_t;
	clock_t koniec = clock() + sekundy * CLOCKS_PER_SEC;
	while (clock() < koniec)
		continue;
	//tu mo�na doda� warunek wyj�cia -> przy wci�ni�tym enterze wychodzi z p�tli
}
std::string szyfruj(std::string tekst, int klucz, string klucz2) {
	string zaszyfrowane = "", pomocnicza = "", koncowka = "", bit_row, prefiks;
	int znak;
	for (int i = 0; i < tekst.length(); i++) {
		znak = tekst[i] + klucz;						//kodowanie ka�dego znaku szyfrem cezara
		bit_row = DecnaBin(znak);						//zamiana 'tekst' na ci�g znak�w binarnych
		if (bit_row.length() < 8) {
			prefiks = "";
			for (int j = bit_row.length(); j < 8; j++) {
				prefiks = "0" + prefiks;
			}
			bit_row = prefiks + bit_row;				//dopisanie tylu zer na pocz�tku, aby ka�dy znak by� zapisany na 8 bitach
		}
		zaszyfrowane = zaszyfrowane + bit_row;
	}
		//przyk�ad klucza2: 1011 -> 4 cyfry.
		//szyfrowanie XOR -> 1010 + 1011 = 0001
		//podzia� tekstu na czlony 4-literowe.

		//szyfrowanie XOR
	znak = zaszyfrowane.length() % 4;
	for (int i = zaszyfrowane.length() - znak; i < zaszyfrowane.length(); i++) {
		koncowka = koncowka + zaszyfrowane[i];			//po dodaniu podzia�u na 8 bit�w ka�de s�owo nie jest to ju� wymagane... ale zostawiam, bo mo�e kiedy� b�dzie trzeba przerobi� na np. 9 bit�w.
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
std::string deszyfruj(std::string szyfrowana, int klucz, string klucz2) {	//do doko�czenia
	string odszyfrowane = "", koncowka = "", pomocnicza = "";
	int znak;
	char znakch;
	//deszyfracja XOR
	znak = szyfrowana.length() % 4;
	for (int i = szyfrowana.length() - znak; i < szyfrowana.length(); i++) {
		koncowka = koncowka + szyfrowana[i];			//po dodaniu podzia�u na 8 bit�w ka�de s�owo nie jest to ju� wymagane... ale zostawiam, bo mo�e kiedy� b�dzie trzeba przerobi� na np. 9 bit�w.
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

	//szyfr sk��da si� z pewnej liczby znak�w zaszyfrowanych kodem ACII na binarnym po 8 bit�w ka�dy.

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

//�MIETNIK:
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


//odczytywanie zawarto�ci bazy_umiej�tno�ci po dodaniu wszystkich plik�w
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

//char znak_czekaj = '0';
while (getchar() != '\n') {
//std::cin >> znak_czekaj;
}



cout << "\n";
Umiejetnosci_skrot*  testowa = new Umiejetnosci_skrot(0, 0, 0);
testowa->wypisz_pojedyncza(baza_umiejestosci);
cout << "\n";
baza_umiejestosci[0][0][0]->wypisz_informacje();
cout << "\n";
testowa->zwroc_umiej(baza_umiejestosci)->wypisz_informacje();	//widzi o ktory typ umiej�tno�ci chodzi =>liter�wka -.-
int obrazenia = testowa->zwroc_umiej(baza_umiejestosci)->zwroc_obrazenia(); //czyta umiej�tno�� jako Umiejetnosci*->zwroc_obrazenia() =>liter�wka -.-
cout << "\n" << obrazenia;
obrazenia = baza_umiejestosci[testowa->zwroc_rodzaj()][testowa->zwroc_poziom()][testowa->zwroc_ID()]->zwroc_obrazenia();
cout << "\n" << obrazenia;

czekaj(20);
*/
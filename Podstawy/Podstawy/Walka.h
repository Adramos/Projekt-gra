#ifndef walka_hpp
#define walka_hpp
#include "Karta_gracza.h"


class Walka {
private:
	Karta_gracza gracz_wyzywajacy, gracz_wyzwany;
	Umiejetnosci_skrot tabela_umiej[4][6];		//gracz atakuj�cy (gracz_wyzywajacy) posiada pola [0-1][0-5], a broni�cy si� (gracz_wyzwany) pola [2-3][0-5]
	bool zaakceptowana;
	int numer_walki;
public:
	Walka(Karta_gracza &atakujacy, Karta_gracza &broniacy, int& numer_ostatniej_walki, std::map<int, Walka*> &baza_walki);
	void wybor_umiejetnosci(bool czy_atakujacy, Karta_gracza gracz, std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej);
	void wypisz_informacje();
	int zwroc_numer_walki();

	//do wykonania: odczytywanie umiej�tnosci (do bazy umeij�tno�ci), kart graczy z pliku i walk z pliku + zapis tych informacji do pliku
	//do wykonania: ko�c�wka walki
	//zwalnianie niepotrzebnych element�w i pami�ci
	//do wykonania: TESTY_1
};


#endif

//do wykonania: wypisanie inforamacji o efekcie + (umiej�tnosci + wszystkie efekty) + wszystkie umiej�tnosci	=>DONE
//do wykonania na p�niej: wyb�r umiej�tno�ci + wpisanie ich do tabeli "tabela_umiej"	=>DONE
//do wykonania: stworzy� drzewo wszsytkich kart graczy, wszystkich walk {,zalogowanych graczy -> p�ki co nie ma sensu}		=>DONE -> b�dzei trzeba p�niej poprawi�, bo mamy ograniczenie do wielko�ci int'a
//do wykonania: do�aczy� spis trwajacych walk (id+odszukanie walki w drzewie?) do karty ka�dego gracza		=>DONE

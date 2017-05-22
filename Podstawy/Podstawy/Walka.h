#ifndef walka_hpp
#define walka_hpp
#include "Karta_gracza.h"


class Walka {
private:
	Karta_gracza gracz_wyzywajacy, gracz_wyzwany;
	Umiejetnosci_skrot tabela_umiej[4][6];		//gracz atakuj¹cy (gracz_wyzywajacy) posiada pola [0-1][0-5], a broni¹cy siê (gracz_wyzwany) pola [2-3][0-5]
	bool zaakceptowana, rozegrana;
	int numer_walki;
public:
	Walka(Karta_gracza &atakujacy, Karta_gracza &broniacy, int& numer_ostatniej_walki, std::map<int, Walka*> &baza_walki);
	Walka(Karta_gracza &atakujacy, Karta_gracza &broniacy, int& numer_ostatniej_walki, std::map<int, Walka*> &baza_walki, Umiejetnosci_skrot tabelaU[4][6], bool zak, bool roz);
	~Walka();
	void wybor_umiejetnosci(bool czy_atakujacy, Karta_gracza gracz, std::vector<std::vector<std::vector<Umiejetnosci*>>> baza_umiej);
	void wypisz_informacje();
	int zwroc_numer_walki();
	Karta_gracza zwoc_gracza(char ktory);		//'A' = atakuj¹cy (wyzywaj¹cy), 'B' = broni¹cy siê (wyzwany)
	bool czy_zaakceptowana();
	bool czy_rozegrana();
	Umiejetnosci_skrot zwroc_wart_tab(int i, int j);
	void ustaw_zaakceptowanie(bool wybor);
	void ustaw_rozegranie(bool wybor);
	void wyswietl_walke();
	//do wykonania: koñcówka walki
	//do wykonania: TESTY_1
};


#endif

//do wykonania: wypisanie inforamacji o efekcie + (umiejêtnosci + wszystkie efekty) + wszystkie umiejêtnosci	=>DONE
//do wykonania na póŸniej: wybór umiejêtnoœci + wpisanie ich do tabeli "tabela_umiej"	=>DONE
//do wykonania: stworzyæ drzewo wszsytkich kart graczy, wszystkich walk {,zalogowanych graczy -> póki co nie ma sensu}		=>DONE -> bêdzei trzeba póŸniej poprawiæ, bo mamy ograniczenie do wielkoœci int'a
//do wykonania: do³aczyæ spis trwajacych walk (id+odszukanie walki w drzewie?) do karty ka¿dego gracza		=>DONE
//do wykonania: odczytywanie umiejêtnosci (do bazy umeijêtnoœci), kart graczy z pliku i walk z pliku + zapis tych informacji do pliku =>DONE
//do wykonania: interfejs =>DONE
//do wykonania: sprawdzenie czy dany gracz nie doty ju¿ jakiejœ walki z innym graczem =>DONE
//zwalnianie niepotrzebnych elementów i pamiêci0 => DONE

#include "walka.h"

//NOTATKA 1: WALKI
/*
Walki odbywaj� si� na nast�puj�cej zasadzie:
-gracze ustawiaj� swoje kolejki atak-obrony w funkcji (nazwa funkcji)
-do funkcji 'pojedynek' wprowadzane s� punkty �ycia obu walcz�cych oraz wska�nik na list� atak-obrona
-funkcja 'pojedynek' wykonuje pierwsz� wymian�: wyzywaj�cy (A-atakuj�cy) uderza, a wyzwany (O-obro�ca) pr�buje si� broni�
-nast�pnie funkcja 'obrazenia' wylicza zadane obra�enia, a {!!!funkcja 'ustaw_PZ' odejmuje({p�niej}/dodaje) punkty �ycia!!!} nast�pnie odpowiednio ustawia si� lokalne warto�ci PZ
-funkcja 'pojedynek' sprawdza, czy wyzwany posiada jeszcze jakie� punkty �ycia, czy przegrywa przez 'eliminacje'
-je�li zostaje wyeliminowany walka ko�czy si� zwyci�stwem wyzywaj�cego
-je�li nie nast�puje zmiana miejsc (punkty 3-6 s� wykonywane ponownie z odwr�conymi rolami)
-walka toczy sie do momentu, gdy kto� zostanie wyeliminowany, lub te� obaj walcz�cy wykonaj� swoje kolejki atak-obrony
-w przypadku braku eliminacji obu graczom wyliczany jest procentowy wynik pozosta�ych punkt�w zdrowia (max_PZ*100/obecne_PZ) 
-funkcja 'ustaw_PZ' ustawia ko�cowe pozosta�e punkty �ycia obu walcz�cym
-funkcja 'pojedynek' zwraca zwyci�zc�: A-wygrywa wyzywaj�cy (atakuj�cy), O-wygrywa wyzwany (obro�ca), R-walka ko�czy si� remisem (oboje graczy ma tyle samo procent (w zaokr�gleniu do jedno�ci) zdrowia)
*/

//NOTATKA 2: UMIEJ�TNO�CI
/*

*/
/*
struct umiejetnosc {
	string nazwa_umiejetnosci;
	char typ_umiejetnosci;      //S-silny, Z-zr�czny, M-magiczny

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
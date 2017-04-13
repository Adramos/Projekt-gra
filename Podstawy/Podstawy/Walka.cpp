#include "walka.h"

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
*/

//NOTATKA 2: UMIEJÊTNOŒCI
/*

*/
/*
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
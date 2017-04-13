#include <iostream>
#include <ctime>
#include "walka.h"

using namespace std;

//deklaracje funkcji

void czekaj(int);

int main() {


}


//funckja s³u¿y do zatrzymania programu na 'n' sekund

void czekaj(int sekundy) {
	typedef long clock_t;
	clock_t koniec = clock() + sekundy * CLOCKS_PER_SEC;
	while (clock() < koniec)
	continue;
}
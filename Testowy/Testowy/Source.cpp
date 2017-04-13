#include <iostream>
#include <string>

class testowa {
public:
	testowa(std::string tekstowo);
	testowa();
	std::string operator+(testowa &klasa) {
		return (this->tekst + klasa.tekst);
	}
	void operator=(testowa &klasa);
	std::string wroc_tekst() {
		return this->tekst;
	}
	~testowa() {};
	testowa(const testowa &cos) {
		tekst = cos.tekst;
	}
private:
	std::string tekst;
};

void testowa::operator=(testowa &klasa) {
	if (this != &klasa) {
		this->tekst = klasa.wroc_tekst();
	}
}
testowa::testowa() :
tekst("brak")
{}
testowa::testowa(std::string tekstowo)
{
	tekst = tekstowo;
}

int main() {
	int proba;
/*	
		for (int i = 1; i < 20; i++) {
			std::cin >> proba;
			try {
				if (proba == 0)
					throw 'a';
			}
			catch (char tekst) {
				std::cout << "\nWpisana wartosc to zero!\n";
			}
		}
*/	
	testowa* klasaA = new testowa("Ala");
	testowa* klasaB = new testowa("Ola");
	testowa* klasaC = new testowa(*klasaA);
	std::cout << klasaA->wroc_tekst();
	std::cout << "\n\n";
	std::cout << klasaB->wroc_tekst();
	std::cout << "\n\n";
	std::cout << klasaC->wroc_tekst();
	std::cout << "\n\n";
	std::cout << *klasaA + *klasaB;
	klasaA = klasaB;
	std::cout << klasaA->wroc_tekst();
	
	
		std::cin >> proba;
		int *tab = new int[proba];
		for (int i = 0; i < proba; i++) {
			std::cin >> tab[i];
		}
		for (int i = 0; i < proba; i++) {
			std::cout << tab[i];
		}
		delete [] tab;
}
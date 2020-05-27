#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

enum Znak {Karo = 0, Pik = 1, Herc = 2, Tref = 3}; //baklava, list, srce, djetelina

struct Karta
{
	char vrijednost;
	Znak znak;
};

class Spil 
{
	std::vector<Karta> spil;
	
public:
	void popuniSpil();
	Karta vuci();
};
Znak dajVrijednost(int a)
{
	switch (a)
	{
	case 0: return Karo; break;
	case 1: return Pik; break;
	case 2: return Herc; break;
	case 3: return Tref; break;
	default:
		throw std::logic_error("Nevazeci broj");
	}
}

void Spil::popuniSpil()
{
	Znak znak;
	for (int i = 0; i < 4; i++)
	{
		znak = dajVrijednost(i);
		for (int i = 1; i <= 13; i++)
		{
			char vrijednost;
			if (i == 1)
				vrijednost = 'A';
			else if (i == 11)
				vrijednost = 'B';
			else if (i == 12)
				vrijednost = 'Q';
			else if (i == 13)
				vrijednost = 'K';
			else 
				vrijednost = '0'+ i;
			spil.push_back({ vrijednost, znak });
		}
	}
}

Karta Spil::vuci()
{

}

int main()
{
    std::cout << "Hello World!\n"; 
}

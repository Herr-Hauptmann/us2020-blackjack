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
Znak dajZnak(int a)
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
		znak = dajZnak(i);
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
	srand(time(NULL));
	int broj = rand() % 52;
	Karta povratna = spil.at(broj);
	spil.erase(spil.begin()+broj);
	return povratna;
}

int Izracunaj(std::vector<Karta> karte)
{
	int kecevi = 0;
	int vrijednost = 0;
	for (Karta karta : karte)
	{
		if (karta.vrijednost == 'A')
		{
			vrijednost += 10;
			kecevi++;
		}
		else if (karta.vrijednost == 'Q' || karta.vrijednost == 'K' || karta.vrijednost == 'B')
		{
			vrijednost += 10;
		}
		else vrijednost += karta.vrijednost - '0';

		if (vrijednost > 21 && kecevi > 0)
		{
			kecevi--;
			vrijednost -= 9;
		}
	}
	return vrijednost;
}

char dajZadnju(const std::vector<Karta>& karte)
{
	return (karte.end() - 1)->vrijednost;
}

int main()
{
	//Treba uvesti sistem s parama (igra zavrsava kada igrac ostane bez novca)
	while (true)
	{
		Spil Spil;
		Spil.popuniSpil();
		//Moramo pamtiti karte jer kec moze imati vrijednost 1 ili 10 sto bitno utice na rezultat
		std::vector<Karta> igraceve; //Karte koje je izvukao igrac
		std::vector<Karta> kasinove; //Karte koje je izvukao kasino
		int igrac = 0, kasino = 0;
		int unos = 1;
		while (unos != 0)
		{
			//Igrac vuce dok ne kaze obrnuto ili predje 21
			std::cout << "1 ukoliko zelis da vuces, 0 ukoliko ne zelis da vuces" << std::endl;
			std::cin >> unos;
			if (!std::cin || (unos != 1 && unos != 0))
			{
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Nemoj se igrati s unosom, fasovati ces" << std::endl;
				continue;
			}
			if (unos == 0) break;
			igraceve.push_back(Spil.vuci());
			std::cout << dajZadnju(igraceve) << std::endl;
			//Dodati metodu koja crta posljednju izvucenu kartu
			igrac = Izracunaj(igraceve);

			std::cout << "Player: " << igrac << std::endl;
						
			if (igrac > 21)
			{
				std::cout << "Izgubili ste!" << std::endl;
				break;
			}
		}
		if (unos == 0)
		{
			//Tek sad kasino vuce sve dok ne dobije bolje karte od igraca ili dok ne predje 21
			kasinove.push_back(Spil.vuci());
			std::cout << dajZadnju(kasinove) << std::endl;
			//Dodati metodu koja crta posljednju izvucenu kartu
			kasino = Izracunaj(kasinove);
			//Preci u novi red i simbolizirati da kasino vuce
			while (kasino < 21 && kasino <= igrac)
			{
				kasinove.push_back(Spil.vuci());
				std::cout << dajZadnju(kasinove) << std::endl;
				kasino = Izracunaj(kasinove);
				std::cout << "House: " << kasino << std::endl;
			}

			if (igrac == kasino)
			{
				std::cout << "Nerijeseno!" << std::endl;
				std::cout << "Player: " << igrac << std::endl;
				std::cout << "House: " << kasino << std::endl;
			}
			else if (kasino > igrac && kasino <= 21)
			{
				std::cout << "Izgubili ste!" << std::endl;
				std::cout << "Player: " << igrac << std::endl;
				std::cout << "House: " << kasino << std::endl;	
			}
			else
			{
				std::cout << "Pobjedili ste!" << std::endl;
				std::cout << "Player: " << igrac << std::endl;
				std::cout << "House: " << kasino << std::endl;
			}
		}
		std::cout << std::endl << "Unesite 0 za prekid, any key za novu igru: ";
		int ulaz;
		std::cin >> ulaz;
		if (ulaz == 0)
			break;
	}
	return 0;
}

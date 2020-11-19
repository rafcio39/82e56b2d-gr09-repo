// ZawodyBiegowe.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>


using namespace std;


struct argumenty {

	string sciezka_do_pliku = "0";
	int wartosc_L = 0;

};
struct biegacz {
	string nr_telefonu;
	string nicq;
	int czas;
};

void pokaz_argumenty(argumenty& arg);
void wczytaj_argumenty(argumenty& arg, int N, char* tab[]);
void pokaz_pomoc();
void pokaz_biegaczy(biegacz tab[], int N);
void sortuj_zawodnikow(biegacz tab[], int N);
void generuj_wiadomosci(string bieg,biegacz tab[], int N, int L);

int main(int liczba_argumentow, char* tablica_argumentow[])
{
	argumenty argumenty_programu;
	wczytaj_argumenty(argumenty_programu, liczba_argumentow, tablica_argumentow);
	if (argumenty_programu.wartosc_L == 0 or argumenty_programu.sciezka_do_pliku == "0")
	{
		//ten fragment wykonuje sie, jezeli argumenty maja wartosci domyslne- czyli nie zostaly podane
		pokaz_pomoc();
		return 0;
	}
	else
	{
		//ten fragment wykonuje sie, jezeli zostaly podane jakies arguemtny, nie jest tutaj sprawdzana ich poprawnosc
		pokaz_argumenty(argumenty_programu);


		ifstream plik(argumenty_programu.sciezka_do_pliku);
		if (plik.is_open() == 1)
		{
			int liczba_zawodnikow = 0;
			string nazwa_biegu;
			string linia;

			cout << "Udalo sie otworzyc plik" << endl;
			getline(plik, linia);
			liczba_zawodnikow = stoi(linia);
			cout << "Liczba zawodnikow to:\t " << liczba_zawodnikow << endl;
			getline(plik, linia);
			nazwa_biegu = linia;
		    cout << "Nazwa tego biegu to: \t " << nazwa_biegu << endl;

			biegacz* TablicaZawodnikow = new biegacz[liczba_zawodnikow]; //stworzenie tablicy rozmiarem odpowiadajacej liczbie zawodnikow, wedle pliku
			for (int i = 0; i < liczba_zawodnikow; i++) {
				plik >> TablicaZawodnikow[i].czas;
				plik >> TablicaZawodnikow[i].nicq;
				plik >> TablicaZawodnikow[i].nr_telefonu;
			}
			plik.close();
			//pokaz_biegaczy(TablicaZawodnikow, liczba_zawodnikow);
			sortuj_zawodnikow(TablicaZawodnikow, liczba_zawodnikow);
			cout << "===============Zawodnicy po sortowaniu============" << endl;

			//pokaz_biegaczy(TablicaZawodnikow, liczba_zawodnikow);

			generuj_wiadomosci(nazwa_biegu,TablicaZawodnikow, liczba_zawodnikow, argumenty_programu.wartosc_L);
		}
		else
		{
			cout << "Nie udalo sie otworzyc pliku" << endl;
		}
		return 0;

	}

}

void wczytaj_argumenty(argumenty& arg, int N, char* tab[]) {

	for (int i = 0; i < N; i++)
	{
		if (string(tab[i]) == "-w")
			arg.sciezka_do_pliku = string(tab[i + 1]);
		if (string(tab[i]) == "-l")
			arg.wartosc_L = stoi(tab[i + 1]);
	}
};
void pokaz_pomoc()
{
	cout << "Program uruchamiac nalezy z nastepujacymi przelacznikami: \n";
	cout << "-w <sciezka do pliku> \n";
	cout << "-l <liczba calkowita> \n";
}
void pokaz_argumenty(argumenty& arg)
{
	cout << "Sciezka do pliku to: \n \t \t \t" << arg.sciezka_do_pliku << endl;
	cout << "Lartosc liczby L to: \n \t \t \t" << arg.wartosc_L << endl;
	cout << "===================================================================" << endl;

}

void pokaz_biegaczy(biegacz tab[], int N)
{
	for (int i = 0; i < N; i++)
		cout << "Biegacz " << setw(12) << tab[i].nicq << " \t uzyskal czas \t:" << tab[i].czas << endl;

}


void sortuj_zawodnikow(biegacz tab[], int N) {

	biegacz pom;
	for (int i = 0; i < N; i++)
	{
		for (int j = i; j < N; j++)
		{
			if (tab[i].czas > tab[j].czas)
			{
				pom = tab[i];
				tab[i] = tab[j];
				tab[j] = pom;
			}

		}
	}



};

void generuj_wiadomosci(string bieg,biegacz tab[], int N, int L)
{
	int pom_time;

	for (int i = 0; i < L and i < N; i++)
	{
		ofstream plik_do_zapisu("wiadomosci/"+tab[i].nr_telefonu + ".txt");
		if (plik_do_zapisu.is_open() == 1)
		{
			plik_do_zapisu << tab[i].nicq << ", GRATULUJEMY!!!!" << endl;
			plik_do_zapisu << "W zawodach "<< bieg<<" udało Ci sie zajac " << i + 1 << " miejsce";
			plik_do_zapisu.close();
		}
		else
			cout << "dla nr " << tab[i].nr_telefonu << " nie udalo sie utworzyc wiadomosci" << endl;

	}

}
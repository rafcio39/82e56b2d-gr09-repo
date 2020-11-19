#include <iostream>
#include <math.h>
#include <iomanip>
#include <ctime>

#define tabSize 1000 //definicja stalej wartosci, pozwalajacej modyfikowac maksymalna liczbe elementow K
using namespace std;

int main()
{
	int X, Y, K; //deklaracja zmiennych X, Y okrelajácych wspolrzedne pkt O, oraz liczby losowanych punktow K.

	int pXY[tabSize][2]; // deklaracja tablicy, w ktorej w kolejnych wierszach beda przechowywane wspolrzedne K losowanych pkt
	double Dist2O[tabSize]; // deklaracja tablicy, w ktorej beda przechowywane dystansy losowanych pktow do pkt O.
	int sickPositiv[tabSize]; //2- NoPositiv, 1- Positiv, 0 -NoRisk, deklaracja tablicy, w ktorej bedzie przechowywana informacja o tym czy pkt zachorowal czy nie lub czy byl niezagrozony choroba
	int NonRiskCounter = 0; // deklaracja i inicjalizacja wartosci licznika, ktory liczy ile osob nie bylo narazonych na chorobe
	int SickCounter = 0; // deklaracja i inicjalizacja licznika pkt ktore sie zarazily


	srand(time(NULL)); // ta linijka powoduje że liczby będą losowe, bez niej za każdym razem losowanie byłoby identyczne.


	// Prosba o wprowadzenie wspolrzednych pkt O
	cout << "Prosze podac wspolzedne X oraz Y punktu O, oddzielone spacja:" << endl;
	cin >> X >> Y;

	//Prosba o wprowadzenie wartosci K, oraz ograniczeniczenie wartosci K do 1 lub 1000 na wypadek podania za malej
	// lub za duzej wartosci.
	cout << "Prosze podac ile punktow ma zostac wylosowanych:";
	cin >> K;
	if (K < 1)
		K = 1;
	if (K > tabSize)
		K = tabSize;


	cout << endl << endl << endl;

	// Wyswietlenie wprowadzonych wartosci X,Y oraz K
	cout << "O(" << X << "," << Y << ")" << endl;
	cout << "Teraz zostana wylosowane wspolrzedne X oraz Y " << K << " punktow" << endl;

	//zapelnienie pierwszych K elementow tablicy ze wspolrzednymi losowymi wartosciami z przedzialu <0,100>
	for (int i = 0; i < K; i++)
	{
		pXY[i][0] = rand() % 101;
		pXY[i][1] = rand() % 101;

	}

	// obliczenie odleglosci i-tych punktow do punktu O i wrzucenie tego do tablicy z tymi odleglosciami
	for (int i = 0; i < K; i++)
	{
		//mozna tak:
		//Dist2O[i] = sqrt((X - pXY[i][0])* (X - pXY[i][0]) + (Y - pXY[i][1])* (Y - pXY[i][1]));
		//lub tak, pow(x,n) to podniesienie wartosci x do potégi n
		Dist2O[i] = sqrt(pow(X - pXY[i][0], 2) + pow(Y - pXY[i][1], 2));
	}

	// wyswietlenie wspolrzednych i-tych pktow wraz z ich odleglosciami do pkt O
	for (int i = 0; i < K; i++)
	{
		cout << "P[" << i + 1 << "] \t x: " << setw(5) << pXY[i][0] << "\t" << " y:" << setw(5) << pXY[i][1];
		// wyswietlenie i+1 by wyswietlalo bardziej intuicyjnie nr punktu a nie indeks tablicy
		// setw() powoduje ustawienie ile znakow ma zajmowac wyswietlana wartosc
		// \t powoduje wyswietlenie tabulatora

		cout << "\t dystans wynosi: \t" << Dist2O[i]; //ta linijka wyswietla pomocniczo dystans
		cout << endl;
	}


	// w zaleznosci od dystansu pkt i-tego do pkt O(X,Y) losujemy czy jest chory
	// rand()%101 losuje liczbe calkowita z przedzialu <0,100>, 
	// jezeli mamy 90% szans na zachorowanie to 
	//		jezeli wylosujemi liczbe <=90  (90/100 szans powodzenia) to pkt zachorowal
	//		jezeli wylosujemy liczbe >90 (10/100 szans powodzenia ) to pkt zostal zdrowy
	// jezeli pkt poza strefa ryzyka- ustawiamy odpowiedni znaczki
	//
	for (int i = 0; i < K; i++)
	{
		if (Dist2O[i] <= 2)
			if (rand() % 101 <= 90) {
				sickPositiv[i] = 1; // wylosowano ze pkt i-ty jest chory
			}
			else
				sickPositiv[i] = 2; // wylosowano ze pkt i-ty zostal zdrowy mimo ze byl zagrozony


		if (Dist2O[i] > 2 and Dist2O[i] <= 10)
			if (rand() % 101 <= 50) {
				sickPositiv[i] = 1;
			}
			else
				sickPositiv[i] = 2;


		if (Dist2O[i] > 10 and Dist2O[i] <= 100)
			if (rand() % 101 <= 30) {
				sickPositiv[i] = 1;
			}
			else
				sickPositiv[i] = 2;


		if (Dist2O[i] > 100) {
			sickPositiv[i] = 0; //pkt i-ty nie ma ryzyka choroby
		}
	}

	cout << endl;
	cout << endl;
	cout << endl;


	//wypisanie pktow, ktore nie byly zagrozone choroba na podstawie sprawdzenia flagi choroby
	// oraz zliczenie ich liczby
	cout << "Te punkty nie byly zagrozone choroba" << endl;

	int line_counter = 0;
	for (int i = 0; i < K; i++)
	{

		if (sickPositiv[i] == 0) {
			cout << setw(6) << i + 1;
			NonRiskCounter++;
			line_counter++;
			if ((line_counter % 10) == 0) //dzieki line_counter wiemy ile liczb zostalo wypisanych w linijce, i po 10 liczbie mozemy przejsc do nastepnej linijki, wyglada to estetycznie ;)
			{
				cout << endl;
			}
		}



	}
	cout << endl;
	cout << endl;
	cout << endl;


	//wypisanie pktow, ktore zachorowaly na podstawie sprawdzenia flagi choroby
	// oraz zliczenie ich liczby
	cout << "Punkty o nastepujacych indeksach zachorowaly:" << endl;
	line_counter = 0;

	for (int i = 0; i < K; i++)
	{

		if (sickPositiv[i] == 1) {
			cout << setw(6) << i + 1;
			SickCounter++;
			line_counter++;
			if ((line_counter % 10) == 0) //dzieki line_counter wiemy ile liczb zostalo wypisanych w linijce, i po 10 liczbie mozemy przejsc do nastepnej linijki, wyglada to estetycznie ;)
			{
				cout << endl;
			}
		}

	}

	cout << endl;
	cout << endl;
	cout << endl;

	// wypisanie podsumowania.
	cout << endl << endl;
	cout << "=============================" << endl;
	cout << "Bylo   na  poczatku: \t" << K << endl;
	cout << "Z czego zachorowalo: \t" << SickCounter << endl;
	cout << "Niezagrozonych bylo: \t" << NonRiskCounter << endl;

}

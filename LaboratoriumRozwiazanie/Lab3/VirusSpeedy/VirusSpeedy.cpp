

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "Structs.h"
#include "Functions.h"


using namespace std;
int main(int argv, char * argch[] )
{
    srand(time(NULL));
    
    string nazwa_biegu;
    int ile_uczestnikow;
    int ile_chorych;
    string nazwa_pliku;
    runner tmp_biegacz;
    cout << "Teraz zostanie wygenerowany plik z uczestnikami biegu." << endl;
    cout << "Nazwa biegu to:";
    getline(cin, nazwa_biegu);
    cout << "Liczba uczestnikow biegu to:";
    cin >> ile_uczestnikow;
    cout << "Liczba chorych to:";
    cin >> ile_chorych;
    cout << "Nazwa pliku to:";
    cin >> nazwa_pliku;
    nazwa_pliku = nazwa_pliku + ".txt";
    ofstream plik;
    plik.open( nazwa_pliku);

    plik << ile_uczestnikow << endl;
    plik << nazwa_biegu << endl;
    for (int i = 0; i < ile_uczestnikow; i++)
    {
        
        tmp_biegacz.nicq = randomName(rand() % 10 + 5);
        if (ile_chorych > 0)
        {
            if (rand() % 100 > 90) 
            {
                tmp_biegacz.nicq = "VIRUS";
                ile_chorych--;
            }
            

        }


        tmp_biegacz.phone_number=  to_string(rand() % 9 + 1);
        for (int j = 0; j < 8; j++)
            tmp_biegacz.phone_number = tmp_biegacz.phone_number + to_string(rand() % 10 );

        tmp_biegacz.time = 60 * 60 + rand() % (1000 * 60);

        //cout << "Biegacz " << tmp_biegacz.nicq << " uzyskal czas: " << tmp_biegacz.time << endl;
        //cout << "jego nr telefonu to : \t " << tmp_biegacz.phone_number << endl << endl;

        plik << tmp_biegacz.time << " " << tmp_biegacz.nicq << " " << tmp_biegacz.phone_number << endl;
    

    }
    plik.close();


}


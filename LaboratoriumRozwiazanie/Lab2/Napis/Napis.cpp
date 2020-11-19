
#include <iostream>
#include <iomanip>


using namespace std;

void show_parameters(int n, char** tab); // pokazanie parametrow wejsciowych programu
string make_copy_change_char(string napis, char litera,  char znak);
char histo(string napis);
string infect_text(string napis, char litera );
void write_line(int n, char znak);
void sort_char_tab(int tab[25][2]);



int main(int argc, char* argv[])
{
    show_parameters(argc, argv);
    char litera = *argv[1];
    char znak = *argv[2];
    char ktora_litera;
    string napis = "Ala ma kota i kot ma Ale ale ale nie ma psa i pies to Reksio";
    cout << endl << endl;
    cout << "Napis w pierwotnej formie:"<<endl<<napis << endl;
    cout << "Napis po zamianie znakow :" << endl << make_copy_change_char(napis,litera,znak) << endl;

    cout << endl << endl;
    cout << "Wyswietlenie histogramu:"<<endl;
    ktora_litera=histo(napis);

    cout << "Szukana litera to: \t" << ktora_litera << endl;


    cout << infect_text(napis, ktora_litera) << endl;
}


void show_parameters(int n, char** tab) {
    for (int i = 0; i < n; i++) {
        cout << "Parametr " << setw(3) << i + 1 << ": \t" ;
        cout << tab[i] << endl;
    }
}

string make_copy_change_char(string napis, char litera, char znak)
{
    string napis_copy=napis;
    int length = napis.length();
    litera = toupper(litera);
    for (int i = 0; i < length; i++)
    {
        if (toupper(napis_copy[i]) == litera)
            napis_copy[i] = znak;
    }
    return napis_copy;
}

void write_line(int n, char znak) 
{
    for (int j = 0; j < n; j++)
    {
        cout << znak;

    }
    cout << endl;
};

char histo(string napis)
{
    
    int chartab[25][2];
    int tmp;
    for (int i = 0; i < 25; i++)
    {
        chartab[i][0] = 0;
        chartab[i][1] = i+97;
    }
    int length = napis.length();
    for (int i = 0; i < length; i++)
    {
        if(tolower(napis[i])>=97 and tolower(napis[i])<=122)
        chartab[tolower(napis[i])-97][0]++;
    }

    sort_char_tab(chartab);
    for (int i = 0; i < 25; i++)
    {
        if (chartab[i][0] > 0) {
            write_line(chartab[i][0], chartab[i][1]);
            tmp = chartab[i][1];
        }
    }

    return tmp;
}

string  infect_text(string napis, char litera) {
    string napis_infected;
    for (int i = 0; i < napis.length(); i++)
    {
        if (tolower( napis[i] )!= litera)
            napis_infected = napis_infected + napis[i];
        else
            napis_infected = napis_infected + "VIRUS";
    }
    return napis_infected;
};

void sort_char_tab(int tab[25][2])
{
    int tmp;
    for (int i = 0; i < 25; i++)
    {
        for (int j = i; j < 25; j++)
        {
            if (tab[i][0] < tab[j][0])
            {
                tmp = tab[i][0];
                tab[i][0] = tab[j][0];
                tab[j][0] = tmp;

                tmp = tab[i][1];
                tab[i][1] = tab[j][1];
                tab[j][1] = tmp;
            }
        };


    };

};
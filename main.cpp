#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

vector<int> dlugosci;
vector<int> dlugosci_kopia;
vector<int> mapa;

void szukaj(int ind, int maxind, int *jest, int l, int p);

int main() {

    ifstream file;
    file.open("C:/Users/Administrator/CLionProjects/algorytmy_kombinatoryczne__4/11a.txt",
                   fstream::in);
    if(!file) {
        cout << "Blad otwierania pliku." << endl;
        exit(1);
    }

    string dlugosc_str;
    int dlugosc;

    // odczyt pliku

    while(!file.eof()) {
        getline(file, dlugosc_str, ' ');
        dlugosc = stoi(dlugosc_str);
        dlugosci.push_back(dlugosc);
    }

    for (auto& n : dlugosci) {
        cout << n << ' ';
    }
    cout << endl;

    // konstrukcja mapy restrykcyjnej

    int maxi;
    int maxi_second;

    for (auto& n : dlugosci) {
        if (maxi < n) {
            maxi_second = maxi;
            maxi = n;
        }
    }

    double delta = 1 + 8 * dlugosci.size();
    double delta_sqrt = sqrt(delta);

  //  cout << "Delta: " << delta << endl;

    if (delta_sqrt * delta_sqrt != delta) {
        cout << "Brak mapy dla podanej liczby elementow.";
        exit(0);
    }

    int liczba_ciec = (delta_sqrt - 3) / 2;

   // cout << "liczba ciec: " << liczba_ciec << endl;

    int odleglosc_od_prawej;

  //  cout << "maxi: " << maxi << endl;
   // cout << "maxi_second: " << maxi_second << endl;
    mapa.push_back(maxi - maxi_second); // dodawanie pierwszego elementu do mapy

    //cout << mapa[0] << endl;

    odleglosc_od_prawej = maxi_second;
    int odleglosc_od_lewej = 0;

    dlugosci_kopia = dlugosci;

    for( vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter )
    {
        if( *iter == maxi )
        {
            dlugosci_kopia.erase( iter );
            break;
        }
    }

    for( vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter )
    {
        if( *iter == maxi_second )
        {
            dlugosci_kopia.erase( iter );
            break;
        }
    }

    for( vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter )
    {
        if( *iter == maxi - maxi_second )
        {
            dlugosci_kopia.erase( iter );
            break;
        }
    }

    /*
    for (auto& n : dlugosci_kopia) {
        cout << n << ' ';
    } */

    // szukanie mapy

    int is = 0;
    int *jest;
    jest = &is;

    dlugosci_kopia = dlugosci;

    szukaj(1, liczba_ciec, jest, odleglosc_od_lewej, odleglosc_od_prawej);

    if (jest == 0) {
        cout << "Nie znaleziono rozwiazania.";
    }
    else {
        cout << "\nWynik: " << endl;
        for (auto& n : mapa) {
            cout << n << ' ';
        }
    }

    return 0;
}


void szukaj(int ind, int maxind, int *jest, int l, int p) {

    if (ind == maxind) {
        cout << "Wynik: " << endl;
        for (auto& n : mapa) {
            cout << n << ' ';
        }
        *jest = 1;
    }

    
    for (int i = 0; i < dlugosci_kopia.size(); i++) {

        int x = p - dlugosci_kopia[i];
        int y = dlugosci_kopia[i] - l;

        cout << "p: " << p << " l: " << l << " dlugosci_kopia[i]: " << dlugosci_kopia[i] << " x: " << x << " y: " << y << endl;

        if(find(dlugosci_kopia.begin(), dlugosci_kopia.end(), x) != dlugosci_kopia.end()) {
            if(find(dlugosci_kopia.begin(), dlugosci_kopia.end(), y) != dlugosci_kopia.end()) {
                mapa.push_back(dlugosci_kopia[i]);
                for( vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter )
                {
                    if( *iter == dlugosci_kopia[i] )
                    {
                        dlugosci_kopia.erase( iter );
                        break;
                    }
                }
                for( vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter )
                {
                    if( *iter == x )
                    {
                        dlugosci_kopia.erase( iter );
                        break;
                    }
                }
                for( vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter )
                {
                    if( *iter == y )
                    {
                        dlugosci_kopia.erase( iter );
                        break;
                    }
                }
                ind++;
                szukaj(ind, maxind, jest, l, p);
            }
        }

        if (*jest == 1 || ind < 1) {
            break;
        }

    }

}
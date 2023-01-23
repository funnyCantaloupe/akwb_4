#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

vector<int> dlugosci;
vector<int> dlugosci_kopia;
vector<int> mapa;
vector<pair<int, int>> pozycje; // <dlugosc, pozycja>
vector<pair<int, vector<int>>> usuniete; // <ind, <usuniete_dlugosci>>
vector <pair<int,int>> l_temp; // <ind, l>
vector <pair<int, int>> p_temp; // <ind, p>

void szukaj(int ind, int maxind, int *jest, int l, int p, int maxi);

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
    pozycje.emplace_back(maxi - maxi_second, maxi_second);

    //cout << mapa[0] << endl;

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

    cout << "Pozostale dlugosci: ";
    for (auto& m : dlugosci_kopia) {
        cout << m << ' ';
    }
    cout << endl;

    /*
    for (auto& n : dlugosci_kopia) {
        cout << n << ' ';
    } */

    // szukanie mapy

    int is = 0;
    int *jest;
    jest = &is;

    odleglosc_od_prawej = maxi_second;
    int odleglosc_od_lewej = 0;

    p_temp.emplace_back(0, maxi_second);
    l_temp.emplace_back(0, 0);

    szukaj(1, liczba_ciec+1, jest, odleglosc_od_lewej, odleglosc_od_prawej, maxi);

    if (jest == 0) {
        cout << "Nie znaleziono rozwiazania.";
    }
    else {
        cout << "\nWynik: " << endl;
        for (auto& n : mapa) {
            cout << n << ' ';
        }
        cout << endl << "Pozycje w mapie: " << endl;
        for (auto& n : pozycje) {
            cout << n.first << ' ' << n.second << "    ";
        }
    }

    return 0;
}


void szukaj(int ind, int maxind, int *jest, int l, int p, int maxi) {

    int zostaw_w_spokoju;

    int max_dlugosc = 0;

    for (auto& n : dlugosci) {
        if (n > max_dlugosc)
            max_dlugosc = n;
    }


    if (ind == maxind) {
        *jest = 1;
        cout << "\nWynik: " << endl;
        for (auto& n : mapa) {
            cout << n << ' ';
        }
        cout << endl << "Pozycje w mapie: " << endl;
        for (auto& n : pozycje) {
            cout << n.first << ' ' << n.second << "    ";
        }
    }

    if (ind < 1) {
        cout << "Brak rozwiazania - indeks 0";
        exit(0);
    }
    
    for (int i = 0; i < dlugosci.size(); i++) {

        int l_position = l;
        int r_position = p;

        int x = p - dlugosci[i];
        int y = dlugosci[i] - l;

        int sum_of_elems = accumulate(mapa.begin(), mapa.end(), 0);

        if (sum_of_elems > maxi) {
            mapa.pop_back();
            pozycje.pop_back();
            ind--;
            cout << "Za duza suma, cofam sie, nowy ind: " << ind << endl;
            szukaj(ind, maxind, jest, l, p, maxi);
        }

        cout << "i: " << i << " p: " << p << " l: " << l << " dlugosci_kopia[i]: " << dlugosci_kopia[i] << " x: " << x << " y: " << y << endl;

//if (dlugosci[i] != zostaw_w_spokoju) {

    if(find(dlugosci_kopia.begin(), dlugosci_kopia.end(), x) != dlugosci_kopia.end()) {

        for( vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter )
        {
            if( *iter == x )
            {
                dlugosci_kopia.erase( iter );
                break;
            }
        }

            if (find(dlugosci_kopia.begin(), dlugosci_kopia.end(), dlugosci[i]) != dlugosci_kopia.end()) {

                if (p - l >= dlugosci[i]) {
                    p = x;
                    pozycje.emplace_back(dlugosci[i], p);
                    cout << "czy_prawa" << "    " << dlugosci[i] << ' ' << p << endl;
                    p_temp.emplace_back(ind, p);
                    l_temp.emplace_back(ind, l);
                } else if (p - l <= dlugosci[i]) {
                    pozycje.emplace_back(dlugosci[i], l);
                    cout << "czy_lewa" << "    " << dlugosci[i] << ' ' << l << endl;
                    l = y + l;
                    p_temp.emplace_back(ind, p);
                    l_temp.emplace_back(ind, l);
                } else {
                    dlugosci_kopia.push_back(x);
                    continue;
                }

           } else {
                dlugosci_kopia.push_back(x);
                continue;
            }

            mapa.push_back(dlugosci[i]);
            if (find(dlugosci_kopia.begin(), dlugosci_kopia.end(), dlugosci[i]) != dlugosci_kopia.end()) {
            }
            else {
                dlugosci_kopia.push_back(x);
                break;
            }
            for( vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter )
            {
                if( *iter == dlugosci[i] )
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

            int suma = max_dlugosc;

            for (auto& n : p_temp) {
                if (suma > n.second) {
                    suma = n.second;
                }
            }

            for( vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter )
            {
                if( *iter == suma)
                {
                    dlugosci_kopia.erase( iter );
                    break;
                }
            }
            int adj = 0;

                for (auto& m : p_temp) {
                    if (m.first == ind - 1) {
                        adj = m.second;
                    }
                }

            vector<int> temp = {suma, max_dlugosc - p, dlugosci[i]};
            usuniete.emplace_back(make_pair(ind, temp));

            cout << endl << endl << "suma = " << suma << " y = " << y << " dlugosci[i] = " << dlugosci[i] << endl << endl;
            temp.clear();
            ind++;

            cout << "Pozostale dlugosci: ";
            for (auto& m : dlugosci_kopia) {
                cout << m << ' ';
            }
            cout << endl;
            cout << "Szukam, nowy ind: " << ind <<  endl << endl;
            cout << "usuniete: " << endl;
            for (auto& n : usuniete) {
                for (auto& m : n.second) {
                    cout << m << ' ';
                }
            }
            cout << endl << endl;
            szukaj(ind, maxind, jest, l, p, maxi);

    }
//}






        if (*jest == 1 || ind < 1) {
            break;
        }
        zostaw_w_spokoju = mapa[ind]; // zeby nie probowal tego samego rozwiazania co w tej iteracji
    }


cout << "292" <<endl;
    for (auto& n : usuniete) {
        if (n.first == ind) {
            for (auto& m : n.second) {
                dlugosci_kopia.push_back(m);
            }
        }
    }

    cout << endl;

    vector <int> d_k = usuniete.back().second;

    for (auto& n : d_k) {
        dlugosci_kopia.push_back(n);
    }
    
    usuniete.erase(usuniete.end());

    cout << "\nDlugosci: " << endl;
    for (auto& n : dlugosci_kopia) {
        cout << n << ' ';
    }

    cout << "usuniete: " << endl;
    for (auto& n : usuniete) {

        for (auto& m : n.second) {
            cout << m << ' ';
        }
    }

    cout << endl;
    ind--;
    cout << "Cofam sie, nowy ind: " << ind << endl;
    cout << endl << "l_temp: " << endl;
    for (auto& n : l_temp) {
        cout << "ind: " << n.first << " l: " << n.second << "    ";
    }
    cout << endl;
    cout << endl << "p_temp: " << endl;
    for (auto& n : p_temp) {
        cout << "ind: " << n.first << " p: " << n.second << "    ";
    }
    cout << endl;
    for (auto& n : l_temp) {
        if (n.first == ind - 1) {
            l = n.second;
        }
    }
    cout << "nowe l: " << l  << endl;
    for (auto& n : p_temp) {
        if (n.first == ind - 1) {
            p = n.second;
            n.first = ind;
            n.second = p;
            break;
        }
    }
    cout << "nowe p: " << p << endl;
    szukaj(ind, maxind, jest, l, p, maxi);
}
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <ctime>

using namespace std;

vector<int> dlugosci;
vector<int> dlugosci_kopia;
vector<int> mapa;
vector<pair<int, int>> pozycje; // <dlugosc, pozycja>
vector<pair<int, vector<int>>> usuniete; // <ind, <usuniete_dlugosci>>
vector <pair<int,int>> l_temp; // <ind, l>
vector <pair<int, int>> p_temp; // <ind, p>
vector<int> temp;

void szukaj(int ind, int maxind, int *jest, int l, int p, int maxi, int liczba_fragmentow);

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

 /*  cout << "Pozostale dlugosci: ";
    for (auto& m : dlugosci_kopia) {
        cout << m << ' ';
    }
    cout << endl;
*/
    /*
    for (auto& n : dlugosci_kopia) {
        cout << n << ' ';
    } */

    // szukanie mapy

    srand(time(nullptr));

    int is = 0;
    int *jest;
    jest = &is;

    odleglosc_od_prawej = maxi_second;
    int odleglosc_od_lewej = 0;

    p_temp.emplace_back(0, maxi_second);
    l_temp.emplace_back(0, 0);

    szukaj(1, liczba_ciec+1, jest, odleglosc_od_lewej, odleglosc_od_prawej, maxi, liczba_ciec + 1);

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


void szukaj(int ind, int maxind, int *jest, int l, int p, int maxi, int liczba_fragmentow) {

    int max_dlugosc = 0;

    for (auto &n: dlugosci) {
        if (n > max_dlugosc)
            max_dlugosc = n;
    }


    if (ind == maxind && liczba_fragmentow == pozycje.size()) {
        *jest = 1;
        cout << "\nWynik: " << endl;
        for (auto &n: mapa) {
            cout << n << ' ';
        }
        cout << endl << "Pozycje w mapie: " << endl;
        for (auto &n: pozycje) {
            cout << n.first << ' ' << n.second << "    ";
        }
        exit(0);
    }


    if (ind < 1) {

        szukaj(1, maxind, jest, l, p, maxi, liczba_fragmentow);

    }


    int sum_of_elems = 0;
    for (auto &n: pozycje) {
        sum_of_elems = sum_of_elems + n.first;
    }

    cout << "sum of elems: " << sum_of_elems << " maxi: " << maxi << endl;
    if (sum_of_elems > maxi) {
        pozycje.pop_back();
        mapa.pop_back();
        ind--;
        cout << "nowy ind: " << ind << endl;
        for (auto &n: mapa) {
            cout << n << ' ';
        }
        cout << endl << "^mapa" << endl;
        //  cout << "Za duza suma, cofam sie, nowy ind: " << ind << endl;
        cout << endl << "Pozycje w mapie: " << endl;
        for (auto &n: pozycje) {
            cout << n.first << ' ' << n.second << "    ";
        }
        for (auto &n: l_temp) {
            if (n.first == ind - 1) {
                l = n.second;
                break;
            }
        }
        //     cout << "nowe l: " << l  << endl;
        for (auto &n: p_temp) {
            if (n.first == ind - 1) {
                p = n.second;
                break;
            }
        }
        //  cout << "nowe p: " << p << endl;
        szukaj(ind, maxind, jest, l, p, maxi, liczba_fragmentow);
    }

    random_shuffle(dlugosci_kopia.begin(), dlugosci_kopia.end());
    random_shuffle(dlugosci.begin(), dlugosci.end());


    for (int i = 0; i < dlugosci.size(); i++) {

        if (*jest == 1 || ind < 1) {
            break;
        }

        if (ind == maxind - 1 && liczba_fragmentow == pozycje.size() - dlugosci[i]) {
            mapa.push_back(dlugosci[i]);
            pozycje.emplace_back(dlugosci[i], l + dlugosci[i]);
            ind++;
            l = l + dlugosci[i];
            p = p - dlugosci[i];
            szukaj(ind, maxind, jest, l, p, maxi, liczba_fragmentow);
        }

        int x = p - dlugosci[i];
        int y = dlugosci[i] - l;


        cout << "i: " << i << " p: " << p << " l: " << l << " dlugosci[i]: " << dlugosci[i] << " x: " << x << " y: "
             << y << endl;

//if (dlugosci[i] != zostaw_w_spokoju) {

        if (find(dlugosci_kopia.begin(), dlugosci_kopia.end(), dlugosci[i]) != dlugosci_kopia.end()) {
            for (vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter) {
                if (*iter == dlugosci[i]) {
                    dlugosci_kopia.erase(iter);
                    break;
                }
            }


            if (find(dlugosci_kopia.begin(), dlugosci_kopia.end(), p - dlugosci[i]) != dlugosci_kopia.end()) {
                int stare;
                for (vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter) {
                    if (*iter == p - dlugosci[i]) {
                        dlugosci_kopia.erase(iter);
                        stare = p - dlugosci[i]; // bo pozniej aktualizuje p
                        break;
                    }
                }

                int pdm = maxi + dlugosci[i] - p; //p + dlugosci[i] == maxi
                cout << "pdm: " << pdm << endl;
                if (find(dlugosci_kopia.begin(), dlugosci_kopia.end(), pdm) != dlugosci_kopia.end()) {
                    for (vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter) {
                        if (*iter == pdm) {
                            dlugosci_kopia.erase(iter);
                            break;
                        }
                    }

                    p = x;
                    pozycje.emplace_back(dlugosci[i], p);
                    cout << "prawa" << "    " << dlugosci[i] << ' ' << p << endl;
                    p_temp.emplace_back(ind, p);
                    l_temp.emplace_back(ind, l);
                    int suma = max_dlugosc;

                    for (auto &n: p_temp) {
                        if (suma > n.second) {
                            suma = n.second;
                        }
                    }
                    temp = {suma, max_dlugosc - p, dlugosci[i]};
                } else {
                    dlugosci_kopia.push_back(stare);
                    dlugosci_kopia.push_back(p - dlugosci[i]);
                }
            } else if (find(dlugosci_kopia.begin(), dlugosci_kopia.end(), l + dlugosci[i]) != dlugosci_kopia.end() &&
                       l + dlugosci[i] <= p) {

                int suma = 0;

                for (auto &n: l_temp) {
                    if (suma > n.second) {
                        suma = n.second;
                    }
                }
                if (l != 0 ) {
                    temp = {suma, l + dlugosci[i], dlugosci[i]};
                }
                else {
                    temp = {0, 0, dlugosci[i]};
                }
                pozycje.emplace_back(dlugosci[i], l);
                cout << "lewa" << "    " << dlugosci[i] << ' ' << l << endl;
                l = y + l;
                p_temp.emplace_back(ind, p);
                l_temp.emplace_back(ind, l);
                for (vector<int>::iterator iter = dlugosci_kopia.begin(); iter != dlugosci_kopia.end(); ++iter) {
                    if (*iter == l + dlugosci[i]) {
                        dlugosci_kopia.erase(iter);
                        break;
                    }
                }

            } else {
                dlugosci_kopia.push_back(dlugosci[i]);
                continue;
            }

            usuniete.emplace_back(make_pair(ind, temp));
            mapa.push_back(dlugosci[i]);
            //      cout << endl << endl << "suma = " << suma << " y = " << y << " dlugosci[i] = " << dlugosci[i] << endl << endl;

            ind++;
            cout << "nowy ind: " << ind << endl;


            cout << "Pozostale dlugosci: ";
            for (auto &m: dlugosci_kopia) {
                cout << m << ' ';
            }
            cout << endl;

            cout << "usuniete: " << endl;
            for (auto &n: usuniete) {
                for (auto &m: n.second) {
                    cout << m << ' ';
                }
            }
            cout << endl << endl;
            cout << "Szukam, nowy ind: " << ind << endl << endl;
            szukaj(ind, maxind, jest, l, p, maxi, liczba_fragmentow);

        }









        /*
            } */



        for (auto &n: usuniete) {
            if (n.first == ind) {
                for (auto &m: n.second) {
                    dlugosci_kopia.push_back(m);
                }
            }
        }

        cout << endl;

        vector<int> d_k = usuniete.back().second;

        for (auto &n: d_k) {
            dlugosci_kopia.push_back(n);
        }

        usuniete.erase(usuniete.end());

        // cout << "\nDlugosci: " << endl;
        // for (auto& n : dlugosci_kopia) {
        //      cout << n << ' ';
        //  }

        //  cout << "usuniete: " << endl;
        //  for (auto& n : usuniete) {
//
        //      for (auto& m : n.second) {
        //          cout << m << ' ';
        //     }
        //  }

        cout << endl;
        ind--;
        cout << "nowy ind: " << ind << endl;
        //   cout << "Cofam sie, nowy ind: " << ind << endl;
//    cout << endl << "l_temp: " << endl;
        //   for (auto& n : l_temp) {
        //      cout << "ind: " << n.first << " l: " << n.second << "    ";
        //   }
        cout << endl;
        //   cout << endl << "p_temp: " << endl;
        // for (auto& n : p_temp) {
        //      cout << "ind: " << n.first << " p: " << n.second << "    ";
        //   }
        cout << endl;
        for (auto &n: l_temp) {
            if (n.first == ind - 1) {
                l = n.second;
                break;
            }
        }
        //  cout << "nowe l: " << l  << endl;
        for (auto &n: p_temp) {
            if (n.first == ind - 1) {
                p = n.second;
                break;
            }
        }
        //  cout << "nowe p: " << p << endl;
        szukaj(ind, maxind, jest, l, p, maxi, liczba_fragmentow);
    }
}
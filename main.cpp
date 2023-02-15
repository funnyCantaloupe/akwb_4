#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <map>

using namespace std;

vector<int> dlugosci;

map<int, int> mapa(int min_value, int max_value, int i) {
    map<int, int> zwracana_mapa = {};
    for (int j = min_value; j <= max_value; j = j + i) {
        int k = ((j + 1) * (j + 2)) / 2;
        zwracana_mapa[k] = j;
    }
    return zwracana_mapa;
}

int sprawdzenie(vector<int> DL, vector<int> mapa) {
    vector<int> temp = {};
    int zmienna = 0;
    for (int i = 0; i < mapa.size(); i++) {
        for (int j = i; j < mapa.size(); j++) {
            zmienna = zmienna + mapa[j];
            temp.push_back(zmienna);
        }
        zmienna = 0;
    }
    for (int i = 0; i < DL.size(); i++) {
        if (temp.empty()) {
            break;
        } else if (count(temp.begin(), temp.end(), DL[i])) {
            temp.erase(find(temp.begin(), temp.end(), DL[i]));
        }
    }
    if (temp.empty()) {
        return 1;
    }
    return 0;
}

void szukaj(int pierwszaDL, int ind, int max, vector<int>& dlugosci, vector<int>& mapa, vector<int>& uzyte, vector<int>& koncowa_mapa)
{
    int spr;
    if (mapa.size() == 0)
    {
        mapa.push_back(pierwszaDL);
        uzyte[ind] = 1;
    }
    if (mapa.size() == max)
    {
        koncowa_mapa = mapa;
        return;
    }
    for (int i = 0; i < dlugosci.size(); i++)
    {
        if (i == ind)
        {
            continue;
        }
        else
        {
            if (uzyte[i] == 1)
            {
                continue;
            }
            mapa.push_back(dlugosci[i]);
            spr = sprawdzenie(dlugosci, mapa);
            uzyte[i] = 1;
            if (spr == 1)
            {
                szukaj(pierwszaDL, ind, max, dlugosci, mapa, uzyte, koncowa_mapa);
            }
            mapa.pop_back();
            uzyte[i] = 0;
            if (koncowa_mapa.size() != 0)
            {
                return;
            }
        }
    }
}

int main() {

    ifstream file;
    file.open("C:/Users/Administrator/CLionProjects/algorytmy_kombinatoryczne__4/11a.txt",
              fstream::in);
    if (!file) {
        cout << "Blad otwierania pliku." << endl;
        exit(1);
    }

    string dlugosc_str;
    int dlugosc;

    // odczyt pliku

    while (!file.eof()) {
        getline(file, dlugosc_str, ' ');
        dlugosc = stoi(dlugosc_str);
        dlugosci.push_back(dlugosc);
    }

    // sprawdzanie, czy mapa istnieje

    double delta = 1 + 8 * dlugosci.size();
    double delta_sqrt = sqrt(delta);

    if (delta_sqrt * delta_sqrt != delta) {
        cout << "Brak mapy dla podanej liczby elementow.";
        exit(0);
    }

    // konstrukcja mapy restrykcyjnej

    int maxi;
    int maxi_second;

    for (int n: dlugosci) {
        if (maxi < n) {
            maxi_second = maxi;
            maxi = n;
        }
    }

    int pierwszy_element = maxi - maxi_second;
    int index;

    clock_t begin, end;
    double time = 0.0;

    vector<int> koncowa_mapa = {};
    map<int, int> mapa_l;
    vector<int> mapa_szukaj = {};
    vector<int> DL = dlugosci;

    int max;

    mapa_l = mapa(1, 20, 1);
    max = mapa_l[dlugosci.size()] + 1;

    index = 0;
    for (int i = 0; i < dlugosci.size(); i++) {
        if (dlugosci[i] == pierwszy_element) {
            index = i;
            break;
        }
    }
    vector<int> uzyte(dlugosci.size());

    begin = clock();

    szukaj(pierwszy_element, index, max, dlugosci, mapa_szukaj, uzyte, koncowa_mapa);

    end = clock();
    time = (double) (end - begin) / (double) CLOCKS_PER_SEC;

    if (koncowa_mapa.empty()) {
        cout << "Mapa nie istnieje.";
        exit(0);
    }
    cout << "Mapa: ";
    for (int n: koncowa_mapa) {
        cout << n << " ";
    }
    cout << endl << "Czas: " << time << " sekund.";

    return 0;
}
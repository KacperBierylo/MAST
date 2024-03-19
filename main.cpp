#include <iostream>
#include<string>
using namespace std;
struct Wezel
{
    Wezel* syn, * brat, * rodzic;
    short key;
    Wezel() : syn(NULL), brat(NULL), rodzic(NULL), key(0)
    {

    }
};
void ZbudujDrzewa(short n, string* wejscia, Wezel* korzenie, short* ilosci_wezlow);
void etykietuj(Wezel* root, short& wierzcholki);
short potega(short a, short b);
void naglowki(short** naglowki_wezlow, short** naglowki_werzcholkow, Wezel* korzenie, short n);
Wezel* szukaj(Wezel* start, short szukana); //szukanie wezla o okreslonym kluczu
void uzupelnijTablice(short** tab1, short** tab2, short** tab3, short* ilosci_wezlow, short** naglowki_wezlow, short* ilosci_wierzcholkow, short** naglowki_wierzcholkow, Wezel* korzenie, int a, int b);
short szukajIndeksu(short* tab, short dlugosc, short szukana);
short szukajWTablicy(short x, short y, short** tab1, short** tab2, short** tab3, short** tab4, short* naglowki_wezlow1, short* naglowki_wezlow2, short ilosc_wezlow1, short ilosc_wezlow2);
short liczDzieci(Wezel* korzen, short wartosc); //liczy dzieci danego wezla
void tablicaDzieci(Wezel* korzen, short wartosc, short* tab);   //wypelnia tablice dziecmi danego wezla
bool sprawdzCzySpelniaWarunek(short** tablica_pozycji, short rzad, short kolumna);
bool wyznaczSume(short** tablica_pozycji, short kolumna, short wysokosc, short szerokosc, short** tabpom, short przestawienie, short* maks);
void zacznijSzukac(short** tabpom, short wysokosc, short szerokosc, short przestawienie, short* maks, short** tablica_pozycji);
short najwiekszy(short** tabpom, short x, short y, short* maks);    //szukanie najwiekszej sumy z nienachodzacych na siebie wspolrzednymi wartosci z tablicy



int main()
{   //wprowadzanie danych dotyczacych drzew, ich konstrukcja i oznaczenie elementow
    short iloscDrzew;
    cin >> iloscDrzew;
    short* ilosci = new short[iloscDrzew]();
    short* ilosci_wezlow = new short[iloscDrzew]();
    short* ilosci_wierzcholkow = new short[iloscDrzew]();
    string* wejscia = new string[iloscDrzew];
    Wezel* korzenie = new Wezel[iloscDrzew];
    for (short i = 0; i < iloscDrzew; i++) {
        cin >> wejscia[i];
    }

    ZbudujDrzewa(iloscDrzew, wejscia, korzenie, ilosci_wezlow);

    delete[] wejscia;
    for (short i = 0; i < iloscDrzew; i++) {
        etykietuj(&korzenie[i], ilosci_wierzcholkow[i]);
    }

    short** naglowki_wezlow = new short* [iloscDrzew];
    short** naglowki_wierzcholkow = new short* [iloscDrzew];
    for (short i = 0; i < iloscDrzew; i++) {

        for (short j = 0; j < iloscDrzew; j++) {
            naglowki_wezlow[i] = new short[ilosci_wezlow[i]];
        }

        for (short j = 0; j < iloscDrzew; j++) {
            naglowki_wierzcholkow[i] = new short[ilosci_wierzcholkow[i]];
        }
    }
    naglowki(naglowki_wezlow, naglowki_wierzcholkow, korzenie, iloscDrzew);
    //tworzenie i uzupelnianie tablic

    for (short a = 0; a < iloscDrzew; a++) {
        for (short b = a + 1; b < iloscDrzew; b++) {
            short** tab1 = new short* [ilosci_wezlow[a]];
            short** tab2 = new short* [ilosci_wezlow[a]];
            short** tab3 = new short* [ilosci_wierzcholkow[a]];
            short** tab4 = new short* [ilosci_wierzcholkow[a]];

            for (short i = 0; i < ilosci_wezlow[a]; i++) {
                tab1[i] = new short[ilosci_wezlow[b]]();
            }

            for (short i = 0; i < ilosci_wezlow[a]; i++) {
                tab2[i] = new short[ilosci_wierzcholkow[b]]();
            }

            for (short i = 0; i < ilosci_wierzcholkow[a]; i++) {
                tab3[i] = new short[ilosci_wezlow[b]]();
            }

            for (short i = 0; i < ilosci_wierzcholkow[a]; i++) {
                tab4[i] = new short[ilosci_wierzcholkow[b]]();
            }
            uzupelnijTablice(tab1, tab2, tab3, ilosci_wezlow, naglowki_wezlow, ilosci_wierzcholkow,
                naglowki_wierzcholkow, korzenie, a, b);
            //uzupelnianie ostatniej tablicy
            for (short i = ilosci_wierzcholkow[a] - 1; i >= 0; i--) {

                for (short j = ilosci_wierzcholkow[b] - 1; j >= 0; j--) {

                    short ilosc_dzieci1 = liczDzieci(&korzenie[a], -i);
                    short ilosc_dzieci2 = liczDzieci(&korzenie[b], -j);
                    short* dzieci1 = new short[ilosc_dzieci1];
                    short* dzieci2 = new short[ilosc_dzieci2];
                    tablicaDzieci(&korzenie[a], -i, dzieci1);
                    tablicaDzieci(&korzenie[b], -j, dzieci2);
                    short** tabpom = new short* [ilosc_dzieci1];

                    for (short k = 0; k < ilosc_dzieci1; k++) {
                        tabpom[k] = new short[ilosc_dzieci2];

                    }
                    for (short k = 0; k < ilosc_dzieci1; k++) {

                        for (short l = 0; l < ilosc_dzieci2; l++) {

                            tabpom[k][l] = szukajWTablicy(dzieci1[k], dzieci2[l], tab1, tab2, tab3, tab4, naglowki_wezlow[a], naglowki_wezlow[b],
                                ilosci_wezlow[a], ilosci_wezlow[b]);
                        }
                    }
                    short maks = 0;
                    maks = najwiekszy(tabpom, ilosc_dzieci1, ilosc_dzieci2, &maks);

                    for (short k = 0; k < ilosc_dzieci1; k++) {
                        short z = szukajWTablicy(dzieci1[k], -j, tab1, tab2, tab3, tab4, naglowki_wezlow[a], naglowki_wezlow[b],
                            ilosci_wezlow[a], ilosci_wezlow[b]);
                        if (z > maks) maks = z;
                    }

                    for (short k = 0; k < ilosc_dzieci2; k++) {
                        short z = szukajWTablicy(-i, dzieci2[k], tab1, tab2, tab3, tab4, naglowki_wezlow[a], naglowki_wezlow[b],
                            ilosci_wezlow[a], ilosci_wezlow[b]);
                        if (z > maks) maks = z;
                    }
                    tab4[i][j] = maks;
                    delete[] dzieci1;
                    delete[] dzieci2;
                    delete[] tabpom;
                }
            }
            //wyznaczenie i wypisanie odpowiedzi 

            cout << ilosci_wezlow[a] - tab4[0][0] << endl;
            //czyszczenie pamieci
            for (short i = 0; i < ilosci_wezlow[a]; i++) {
                delete[] tab1[i];
            }

            for (short i = 0; i < ilosci_wezlow[a]; i++) {
                delete[] tab2[i];
            }

            for (short i = 0; i < ilosci_wierzcholkow[a]; i++) {
                delete[] tab3[i];
            }

            for (short i = 0; i < ilosci_wierzcholkow[a]; i++) {
                delete[] tab4[i];
            }
            delete[] tab1;
            delete[] tab2;
            delete[] tab3;
            delete[] tab4;
        }
    }
    for (short i = 0; i < iloscDrzew; i++) {
        delete[] naglowki_wezlow[i];
        delete[] naglowki_wierzcholkow[i];
    }
    delete[] korzenie;
    delete[] ilosci_wezlow;
    delete[] ilosci_wierzcholkow;
    delete[] ilosci;
    delete[] naglowki_wezlow;
    delete[] naglowki_wierzcholkow;
}

void ZbudujDrzewa(short n, string* wejscia, Wezel* korzenie, short* ilosci_wezlow) {
    for (short i = 0; i < n; i++) {
        Wezel* temp = &korzenie[i];
        Wezel* rodzic = &korzenie[i];
        for (unsigned short j = 0; j < wejscia[i].length();) {
            if ((wejscia[i][j] >= '0') && (wejscia[i][j] <= '9')) {
                short k = 0;
                short l = 0;
                short licznik = 0;
                while ((wejscia[i][j] >= '0') && (wejscia[i][j] <= '9')) {
                    short a = j;
                    while ((wejscia[i][a] >= '0') && (wejscia[i][a] <= '9')) {
                        licznik++; a++;
                    }
                    k += (wejscia[i][j] - '0') * potega(10, licznik - 1 - l);
                    l++;
                    j++;
                }
                ilosci_wezlow[i]++;
                temp->key = k;
            }
            else if (wejscia[i][j] == '(') {
                rodzic = temp;
                temp->syn = new Wezel;
                temp = temp->syn;
                temp->rodzic = rodzic;
                j++;
            }
            else if (wejscia[i][j] == ',') {
                temp->brat = new Wezel;
                temp = temp->brat;
                temp->rodzic = rodzic;
                j++;
            }
            else if (wejscia[i][j] == ')') {
                temp = temp->rodzic;
                rodzic = temp->rodzic;
                j++;
            }
            else if (wejscia[i][j] == ';') {
                break;
            }
        }
    }
}

void etykietuj(Wezel* root, short& wierzcholki) {
    wierzcholki = 0;
    Wezel* tmp = root;
    short etykieta = 0;
    if (tmp->key == 0) {
        tmp->key = etykieta;
        etykieta--;
        wierzcholki++;
    }
    tmp = tmp->syn;
    if (tmp->key == 0) {
        tmp->key = etykieta;
        etykieta--;
        wierzcholki++;
    }
    while (tmp != root) {

        if (tmp->syn != nullptr) {
            tmp = tmp->syn;
            if (tmp->key == 0) {
                tmp->key = etykieta;
                etykieta--;
                wierzcholki++;
            }
        }
        else if (tmp->brat != nullptr) {
            tmp = tmp->brat;
            if (tmp->key == 0) {
                tmp->key = etykieta;
                etykieta--;
                wierzcholki++;
            }
        }
        else {
            while (tmp->rodzic->brat == nullptr) {
                tmp = tmp->rodzic;
                if (tmp == root) break;
            }
            if (tmp == root) break;
            tmp = tmp->rodzic;
            tmp = tmp->brat;
            if (tmp->key == 0) {
                tmp->key = etykieta;
                etykieta--;
                wierzcholki++;
            }
        }
    }
}
short potega(short a, short b) {
    short wynik = 1;
    for (short i = 0; i < b; i++) {
        wynik = wynik * a;
    }
    return wynik;
}

void naglowki(short** naglowki_wezlow, short** naglowki_werzcholkow, Wezel* korzenie, short n) {
    for (short i = 0; i < n; i++) {
        short j = 0;
        short k = 0;
        Wezel* tmp = &korzenie[i];
        if (tmp->key > 0) {
            naglowki_wezlow[i][j] = tmp->key;
            j++;
        }
        else {
            naglowki_werzcholkow[i][k] = tmp->key;
            k++;
        }
        tmp = tmp->syn;
        if (tmp->key > 0) {
            naglowki_wezlow[i][j] = tmp->key;
            j++;
        }
        else {
            naglowki_werzcholkow[i][k] = tmp->key;
            k++;
        }
        while (tmp != &korzenie[i]) {

            if (tmp->syn != nullptr) {
                tmp = tmp->syn;
                if (tmp->key > 0) {
                    naglowki_wezlow[i][j] = tmp->key;
                    j++;
                }
                else {
                    naglowki_werzcholkow[i][k] = tmp->key;
                    k++;
                }
            }
            else if (tmp->brat != nullptr) {
                tmp = tmp->brat;
                if (tmp->key > 0) {
                    naglowki_wezlow[i][j] = tmp->key;
                    j++;
                }
                else {
                    naglowki_werzcholkow[i][k] = tmp->key;
                    k++;
                }
            }
            else {
                while ((tmp->brat == nullptr) && (tmp != &korzenie[i])) {
                    tmp = tmp->rodzic;
                }
                if (tmp == &korzenie[i]) break;
                tmp = tmp->brat;
                if (tmp->key > 0) {
                    naglowki_wezlow[i][j] = tmp->key;
                    j++;
                }
                else {
                    naglowki_werzcholkow[i][k] = tmp->key;
                    k++;
                }
            }
        }
    }
}
void uzupelnijTablice(short** tab1, short** tab2, short** tab3, short* ilosci_wezlow, short** naglowki_wezlow, short* ilosci_wierzcholkow,
    short** naglowki_wierzcholkow, Wezel* korzenie, int a, int b) {
    for (short i = 0; i < ilosci_wezlow[a]; i++) {

        for (short j = 0; j < ilosci_wezlow[b]; j++) {
            if (naglowki_wezlow[a][i] == naglowki_wezlow[b][j])
                tab1[i][j] = 1;
        }
    }
    for (short i = 0; i < ilosci_wezlow[a]; i++) {

        for (short j = 0; j < ilosci_wierzcholkow[b]; j++) {
            if (szukaj(szukaj(&korzenie[b], naglowki_wierzcholkow[b][j]), naglowki_wezlow[a][i]) != NULL)
                tab2[i][j] = 1;
        }
    }
    for (short i = 0; i < ilosci_wierzcholkow[a]; i++) {

        for (short j = 0; j < ilosci_wezlow[b]; j++) {
            if (szukaj(szukaj(&korzenie[a], naglowki_wierzcholkow[a][i]), naglowki_wezlow[b][j]) != NULL)
                tab3[i][j] = 1;
        }
    }
}
Wezel* szukaj(Wezel* start, short szukana) {
    Wezel* tmp = start;
    if (tmp->key == szukana) return tmp;
    tmp = tmp->syn;
    if (tmp->key == szukana) return tmp;
    while (tmp != start) {

        if (tmp->syn != nullptr) {
            tmp = tmp->syn;
            if (tmp->key == szukana) return tmp;
        }
        else if (tmp->brat != nullptr) {
            tmp = tmp->brat;
            if (tmp->key == szukana) return tmp;
        }
        else {
            while ((tmp->brat == nullptr) && (tmp != start)) {
                tmp = tmp->rodzic;
            }
            if (tmp == start) {
                break;
            }
            tmp = tmp->brat;
            if (tmp->key == szukana) return tmp;
        }
    }
    return NULL;
}

short szukajIndeksu(short* tab, short dlugosc, short szukana) {
    for (short i = 0; i < dlugosc; i++) {
        if (tab[i] == szukana) return i;
    }
    return -1;
}
short szukajWTablicy(short x, short y, short** tab1, short** tab2, short** tab3, short** tab4, short* naglowki_wezlow1, short* naglowki_wezlow2,
    short ilosc_wezlow1, short ilosc_wezlow2) {

    if ((x > 0) && (y > 0)) {
        return tab1[szukajIndeksu(naglowki_wezlow1, ilosc_wezlow1, x)][szukajIndeksu(naglowki_wezlow2, ilosc_wezlow2, y)];
    }
    else if ((x > 0) && (y <= 0)) {
        return tab2[szukajIndeksu(naglowki_wezlow1, ilosc_wezlow1, x)][-y];
    }
    else if ((x <= 0) && (y > 0)) {
        return tab3[-x][szukajIndeksu(naglowki_wezlow2, ilosc_wezlow2, y)];
    }
    else if ((x <= 0) && (y <= 0)) {
        return tab4[-x][-y];
    }
    return -1;
}

short liczDzieci(Wezel* korzen, short wartosc) {
    Wezel* tmp = szukaj(korzen, wartosc);
    short licznik = 0;
    if (tmp->syn != nullptr) {
        tmp = tmp->syn;
        licznik++;
        while (tmp->brat != nullptr) {
            tmp = tmp->brat;
            licznik++;

        }
    }
    return licznik;
}

void tablicaDzieci(Wezel* korzen, short wartosc, short* tab) {
    Wezel* tmp = szukaj(korzen, wartosc);
    if (tmp->syn != nullptr) {
        short i = 0;
        tmp = tmp->syn;
        tab[i] = tmp->key;
        i++;
        while (tmp->brat != nullptr) {
            tmp = tmp->brat;
            tab[i] = tmp->key;
            i++;
        }
    }
    return;
}

bool sprawdzCzySpelniaWarunek(short** tablica_pozycji, short rzad, short kolumna) {

    for (short i = 0; i < kolumna; i++) {
        if (tablica_pozycji[rzad][i])  return false;
    }
    return true;
}

bool wyznaczSume(short** tablica_pozycji, short kolumna, short wysokosc, short szerokosc, short** tabpom, short przestawienie, short* maks) {
    if (kolumna == szerokosc) {
        short wynik = 0;
        for (short i = 0; i < wysokosc; i++) {
            for (short j = 0; j < szerokosc; j++) {
                if (przestawienie == 0) {
                    if (tablica_pozycji[i][j] == 1) wynik += tabpom[i][j];
                }
                else {
                    if (tablica_pozycji[i][j] == 1) wynik += tabpom[j][i];
                }
            }
        }
        if (wynik > *maks) *maks = wynik;
        return true;
    }

    bool rezultat = false;
    for (short i = 0; i < wysokosc; i++) {
        if (sprawdzCzySpelniaWarunek(tablica_pozycji, i, kolumna)) {
            tablica_pozycji[i][kolumna] = 1;
            rezultat = wyznaczSume(tablica_pozycji, kolumna + 1, wysokosc, szerokosc, tabpom, przestawienie, maks);
            tablica_pozycji[i][kolumna] = 0;

        }
    }
    return rezultat;
}

void zacznijSzukac(short** tabpom, short wysokosc, short szerokosc, short przestawienie, short* maks, short** tablica_pozycji) {

    for (short i = 0; i < wysokosc; i++) {
        for (short j = 0; j < szerokosc; j++) {
            tablica_pozycji[i][j] = 0;
        }
    }

    if (wyznaczSume(tablica_pozycji, 0, wysokosc, szerokosc, tabpom, przestawienie, maks) == false) {
        return;
    }
}

short najwiekszy(short** tabpom, short x, short y, short* maks) {
    *maks = 0;
    short przestawienie = 0;
    short wiersze;
    short kolumny;
    wiersze = x;
    kolumny = y;
    short** tablica_pozycji;
    if (wiersze >= kolumny) {
        tablica_pozycji = new short* [wiersze];
        for (short i = 0; i < wiersze; i++) {
            tablica_pozycji[i] = new short[kolumny];
        }
        zacznijSzukac(tabpom, wiersze, kolumny, przestawienie, maks, tablica_pozycji);
    }
    else {
        tablica_pozycji = new short* [kolumny];
        for (short i = 0; i < kolumny; i++) {
            tablica_pozycji[i] = new short[wiersze];
        }
        przestawienie = 1;
        zacznijSzukac(tabpom, kolumny, wiersze, przestawienie, maks, tablica_pozycji);
    }
    short wynik = *maks;
    if (przestawienie == 0) {
        for (short i = 0; i < wiersze; i++) {
            delete[] tablica_pozycji[i];
        }
        delete[] tablica_pozycji;
    }
    else {
        for (short i = 0; i < kolumny; i++) {
            delete[] tablica_pozycji[i];
        }
        delete[] tablica_pozycji;
    }
    return wynik;
}

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

const int N = 100000;

// POMIAR CZASU

using zegar = chrono::high_resolution_clock;

double czasWykonania(zegar::time_point start, zegar::time_point koniec)
{
    return chrono::duration<double, milli>(koniec - start).count();
}


// LOSOWANIE LICZB

vector<int> losujLiczby(int ile)
{
    vector<int> liczby;

    liczby.reserve(ile);

    random_device rd;
    mt19937 generator(rd());

    uniform_int_distribution<int> zakres(1, 1000000);

    for (int i = 0; i < ile; i++)
    {
        liczby.push_back(zakres(generator));
    }

    return liczby;
}


// 1. ZWYKLA TABLICA

void testTablica(const vector<int>& liczby)
{
    cout << endl;
    cout << "1. ZWYKLA TABLICA" << endl;

    int* tablica = new int[2 * N];


    // WSTAWIANIE 100000

    auto start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        tablica[i] = liczby[i];
    }

    auto koniec = zegar::now();

    cout << "Wstawianie 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // SORTOWANIE 100000

    start = zegar::now();

    sort(tablica, tablica + N);

    koniec = zegar::now();

    cout << "Sortowanie 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // DODAWANIE KOLEJNYCH 100000

    start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        tablica[N + i] = liczby[i];
    }

    koniec = zegar::now();

    cout << "Dodawanie kolejnych 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    delete[] tablica;
}


// 2. VECTOR

void testVector(const vector<int>& liczby)
{
    cout << endl;
    cout << "2. VECTOR" << endl;

    vector<int> dane;

    dane.reserve(2 * N);


    // WSTAWIANIE 100000

    auto start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        dane.push_back(liczby[i]);
    }

    auto koniec = zegar::now();

    cout << "Wstawianie 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // SORTOWANIE 100000

    start = zegar::now();

    sort(dane.begin(), dane.end());

    koniec = zegar::now();

    cout << "Sortowanie 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // DODAWANIE KOLEJNYCH 100000

    start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        dane.push_back(liczby[i]);
    }

    koniec = zegar::now();

    cout << "Dodawanie kolejnych 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;
}


// 3. LISTA FIFO

void testListaFIFO(const vector<int>& liczby)
{
    cout << endl;
    cout << "3. LISTA FIFO" << endl;

    list<int> kolejka;


    // WSTAWIANIE 100000

    auto start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        kolejka.push_back(liczby[i]);
    }

    auto koniec = zegar::now();

    cout << "Wstawianie 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // SORTOWANIE 100000

    start = zegar::now();

    kolejka.sort();

    koniec = zegar::now();

    cout << "Sortowanie 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // DODAWANIE KOLEJNYCH 100000

    start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        kolejka.push_back(liczby[i]);
    }

    koniec = zegar::now();

    cout << "Dodawanie kolejnych 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;
}


// 4. STACK LIFO

void testStackLIFO(const vector<int>& liczby)
{
    cout << endl;
    cout << "4. STACK LIFO" << endl;

    stack<int> stos;


    // WSTAWIANIE 100000

    auto start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        stos.push(liczby[i]);
    }

    auto koniec = zegar::now();

    cout << "Wstawianie 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // SORTOWANIE 100000

    start = zegar::now();

    vector<int> dane;

    dane.reserve(N);

    while (!stos.empty())
    {
        dane.push_back(stos.top());
        stos.pop();
    }

    sort(dane.begin(), dane.end());

    koniec = zegar::now();

    cout << "Sortowanie 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // ODBUDOWANIE STOSU

    for (int i = 0; i < N; i++)
    {
        stos.push(dane[i]);
    }


    // DODAWANIE KOLEJNYCH 100000

    start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        stos.push(liczby[i]);
    }

    koniec = zegar::now();

    cout << "Dodawanie kolejnych 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;
}


// 5. NASZA KOLEJKA

struct Element
{
    int liczba;
    Element* nastepny;
};


class Kolejka
{
private:

    Element* poczatek;
    Element* koniec;

public:

    Kolejka()
    {
        poczatek = nullptr;
        koniec = nullptr;
    }


    ~Kolejka()
    {
        while (poczatek != nullptr)
        {
            Element* temp = poczatek;

            poczatek = poczatek->nastepny;

            delete temp;
        }
    }


    void dodaj(int liczba)
    {
        Element* nowy = new Element;

        nowy->liczba = liczba;
        nowy->nastepny = nullptr;

        if (poczatek == nullptr)
        {
            poczatek = nowy;
            koniec = nowy;
        }
        else
        {
            koniec->nastepny = nowy;
            koniec = nowy;
        }
    }


    // SORTOWANIE BABELKOWE

    void sortuj()
    {
        if (poczatek == nullptr ||
            poczatek->nastepny == nullptr)
        {
            return;
        }

        bool zmiana;

        do
        {
            zmiana = false;

            Element* aktualny = poczatek;

            while (aktualny->nastepny != nullptr)
            {
                Element* nastepny = aktualny->nastepny;

                if (aktualny->liczba > nastepny->liczba)
                {
                    int temp = aktualny->liczba;

                    aktualny->liczba = nastepny->liczba;

                    nastepny->liczba = temp;

                    zmiana = true;
                }

                aktualny = aktualny->nastepny;
            }

        } while (zmiana);
    }
};


// TEST NASZEJ KOLEJKI

void testNaszaKolejka(const vector<int>& liczby)
{
    cout << endl;
    cout << "5. NASZA KOLEJKA" << endl;

    Kolejka kolejka;


    // WSTAWIANIE 100000

    auto start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        kolejka.dodaj(liczby[i]);
    }

    auto koniec = zegar::now();

    cout << "Wstawianie 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // SORTOWANIE BABELKOWE 100000

    start = zegar::now();

    kolejka.sortuj();

    koniec = zegar::now();

    cout << "Sortowanie 100000 (babelkowe): "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // DODAWANIE KOLEJNYCH 100000

    start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        kolejka.dodaj(liczby[i]);
    }

    koniec = zegar::now();

    cout << "Dodawanie kolejnych 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;
}


// 6. DRZEWO BINARNE BST

struct Drzewo
{
    int wartosc;
    Drzewo* lewy;
    Drzewo* prawy;
};


// WSTAWIANIE DO DRZEWA

void wstaw(Drzewo*& korzen, int wartosc)
{
    if (korzen == nullptr)
    {
        korzen = new Drzewo;

        korzen->wartosc = wartosc;
        korzen->lewy = nullptr;
        korzen->prawy = nullptr;

        return;
    }

    if (wartosc < korzen->wartosc)
    {
        wstaw(korzen->lewy, wartosc);
    }
    else
    {
        wstaw(korzen->prawy, wartosc);
    }
}


// PRZEJSCIE INORDER
//
// Przejscie inorder:
// lewe poddrzewo -> korzen -> prawe poddrzewo
//
// Dla BST daje elementy w kolejnosci rosnace.

void inorder(Drzewo* korzen, vector<int>& wynik)
{
    if (korzen == nullptr)
    {
        return;
    }

    inorder(korzen->lewy, wynik);

    wynik.push_back(korzen->wartosc);

    inorder(korzen->prawy, wynik);
}


// USUWANIE DRZEWA

void usunDrzewo(Drzewo* korzen)
{
    if (korzen == nullptr)
    {
        return;
    }

    usunDrzewo(korzen->lewy);

    usunDrzewo(korzen->prawy);

    delete korzen;
}


// TEST DRZEWA

void testDrzewo(const vector<int>& liczby)
{
    cout << endl;
    cout << "6. DRZEWO BINARNE BST" << endl;

    Drzewo* korzen = nullptr;


    // WSTAWIANIE 100000

    auto start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        wstaw(korzen, liczby[i]);
    }

    auto koniec = zegar::now();

    cout << "Wstawianie 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // SORTOWANIE 100000
    //
    // W BST sortowanie wykonujemy poprzez inorder.
    // Wynik zapisujemy do vectora.

    start = zegar::now();

    vector<int> posortowane;
    posortowane.reserve(N);

    inorder(korzen, posortowane);

    koniec = zegar::now();

    cout << "Sortowanie 100000 (inorder): "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // DODAWANIE KOLEJNYCH 100000

    start = zegar::now();

    for (int i = 0; i < N; i++)
    {
        wstaw(korzen, liczby[i]);
    }

    koniec = zegar::now();

    cout << "Dodawanie kolejnych 100000: "
         << czasWykonania(start, koniec)
         << " ms" << endl;


    // Usuwamy cale drzewo.

    usunDrzewo(korzen);
}


// MAIN

int main()
{
    cout << "POROWNANIE CZASU STRUKTUR DANYCH" << endl;


    // LOSOWANIE 100000 LICZB

    cout << endl;
    cout << "Losowanie 100000 liczb..." << endl;

    auto startLosowania = zegar::now();

    vector<int> liczby = losujLiczby(N);

    auto koniecLosowania = zegar::now();

    cout << "Czas losowania 100000 liczb: "
         << czasWykonania(startLosowania, koniecLosowania)
         << " ms" << endl;


    // ROZPOCZECIE TESTOW

    cout << endl;
    cout << "Rozpoczynam testy..." << endl;


    // 1. ZWYKLA TABLICA

    testTablica(liczby);


    // 2. VECTOR

    testVector(liczby);


    // 3. LISTA FIFO

    testListaFIFO(liczby);


    // 4. STACK LIFO

    testStackLIFO(liczby);


    // 5. NASZA KOLEJKA

    testNaszaKolejka(liczby);


    // 6. DRZEWO BINARNE

    testDrzewo(liczby);


    // KONIEC

    cout << endl;
    cout << "KONIEC" << endl;

    return 0;
}

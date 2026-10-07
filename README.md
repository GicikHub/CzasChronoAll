Porównanie czasu struktur danych w C++
Opis projektu

Program służy do porównania czasu wykonywania podstawowych operacji na różnych strukturach danych w języku C++.

Dla każdej struktury wykonywane są trzy główne operacje:

wstawienie 100 000 elementów,

posortowanie 100 000 elementów,

dodanie kolejnych 100 000 elementów.

Program generuje losowo 100 000 liczb całkowitych z zakresu od 1 do 1 000 000, a następnie wykorzystuje ten sam zestaw danych podczas wszystkich testów.

Czas każdej operacji mierzony jest w milisekundach (ms) za pomocą biblioteki <chrono>.

Testowane struktury danych

Program porównuje 6 różnych struktur:

Zwykła tablica dynamiczna

vector

Lista FIFO (std::list)

Stos LIFO (std::stack)

Własnoręcznie zaimplementowana kolejka

Drzewo binarne BST

1. Zwykła tablica

W programie tworzona jest dynamiczna tablica typu int o rozmiarze:

2 * N


czyli dla N = 100000 tablica może przechowywać 200 000 elementów.

Testowane operacje

zapisanie pierwszych 100 000 liczb,

sortowanie pierwszych 100 000 liczb za pomocą std::sort,

zapisanie kolejnych 100 000 liczb.

Do zarządzania pamięcią wykorzystywane są:

new[]
delete[]

2. Vector

Wykorzystywany jest kontener:

vector<int>


Przed rozpoczęciem testów program rezerwuje miejsce na 200 000 elementów:

dane.reserve(2 * N);


Dzięki temu podczas dodawania elementów nie powinno dochodzić do ponownego zwiększania pojemności kontenera.

Testowane operacje

dodanie 100 000 elementów za pomocą push_back,

sortowanie za pomocą std::sort,

dodanie kolejnych 100 000 elementów.

3. Lista FIFO

Do testu wykorzystywany jest:

list<int>


Elementy są dodawane na koniec listy za pomocą:

push_back()


Sortowanie wykonywane jest przy użyciu metody:

list.sort()

Testowane operacje

dodanie 100 000 elementów,

sortowanie listy,

dodanie kolejnych 100 000 elementów.

Lista jest strukturą połączoną, dlatego przechowywanie elementów odbywa się w osobnych węzłach połączonych wskaźnikami.

4. Stack LIFO

Wykorzystywany jest kontener:

stack<int>


Stos działa zgodnie z zasadą LIFO (Last In, First Out), czyli:

ostatni dodany element jest usuwany jako pierwszy.

Wstawianie

Elementy są dodawane za pomocą:

stos.push()

Sortowanie

std::stack nie udostępnia bezpośredniego sortowania.

Dlatego program:

pobiera elementy ze stosu za pomocą top() i pop(),

zapisuje je do vector<int>,

sortuje wektor za pomocą std::sort,

odbudowuje stos.

Czas przenoszenia elementów i sortowania jest uwzględniony w pomiarze opisanym jako:

Sortowanie 100000

Dodawanie

Po odbudowaniu stosu dodawane jest kolejnych 100 000 elementów.

5. Własna kolejka

Program zawiera również własną implementację kolejki.

Każdy element kolejki reprezentowany jest przez strukturę:

struct Element
{
    int liczba;
    Element* nastepny;
};


Kolejka posiada dwa wskaźniki:

poczatek — wskazuje pierwszy element,

koniec — wskazuje ostatni element.

Dodawanie elementu

Nowy element jest tworzony dynamicznie za pomocą:

new Element


Następnie zostaje dodany na koniec kolejki.

Sortowanie

Własna kolejka wykorzystuje sortowanie bąbelkowe (Bubble Sort).

Algorytm porównuje sąsiednie elementy i zamienia ich wartości, jeśli są w niewłaściwej kolejności.

Sortowanie bąbelkowe ma złożoność czasową:

O(n²)


Dlatego dla 100 000 elementów może być zdecydowanie wolniejsze od std::sort.

6. Drzewo binarne BST

Ostatnią testowaną strukturą jest Binary Search Tree (BST).

Każdy węzeł zawiera:

struct Drzewo
{
    int wartosc;
    Drzewo* lewy;
    Drzewo* prawy;
};


Dla każdego elementu:

wartości mniejsze od wartości w węźle trafiają do lewego poddrzewa,

wartości większe lub równe trafiają do prawego poddrzewa.

Wstawianie

Elementy są dodawane za pomocą funkcji:

wstaw()


Funkcja działa rekurencyjnie i umieszcza element w odpowiednim miejscu drzewa.

Sortowanie

BST nie jest sortowane za pomocą klasycznego algorytmu sortującego.

Program wykorzystuje przejście inorder:

lewe poddrzewo → korzeń → prawe poddrzewo


W przypadku prawidłowego BST przejście inorder zwraca elementy w kolejności rosnącej.

Wynik zapisywany jest do:

vector<int> posortowane;

Pomiar czasu

Do pomiaru czasu wykorzystywana jest biblioteka:

#include <chrono>


Program definiuje zegar:

using zegar = chrono::high_resolution_clock;


Pomiar wykonywany jest poprzez zapisanie czasu przed i po wykonaniu operacji:

auto start = zegar::now();

// operacja

auto koniec = zegar::now();


Następnie różnica jest przeliczana na milisekundy:

chrono::duration<double, milli>


Wynik jest wyświetlany w konsoli.

Generowanie danych

Przed rozpoczęciem testów program losuje 100 000 liczb.

Liczby są generowane z zakresu:

1 – 1 000 000


Wykorzystywane są:

random_device,

mt19937,

uniform_int_distribution.

Za generowanie danych odpowiada funkcja:

losujLiczby()


Wszystkie struktury otrzymują ten sam zestaw liczb, dzięki czemu wyniki można ze sobą porównywać.

Przykładowy wynik

Po uruchomieniu program wyświetla wyniki w podobnej formie:

POROWNANIE CZASU STRUKTUR DANYCH

Losowanie 100000 liczb...
Czas losowania 100000 liczb: 5.23 ms

Rozpoczynam testy...

1. ZWYKLA TABLICA
Wstawianie 100000: 0.45 ms
Sortowanie 100000: 7.82 ms
Dodawanie kolejnych 100000: 0.41 ms

2. VECTOR
Wstawianie 100000: 0.52 ms
Sortowanie 100000: 7.91 ms
Dodawanie kolejnych 100000: 0.48 ms

...

KONIEC


Dokładne wartości będą się różnić w zależności od komputera, kompilatora, konfiguracji programu oraz aktualnego obciążenia systemu.

Złożoność obliczeniowa

Orientacyjne złożoności operacji:

Struktura	Wstawianie	Sortowanie	Dodawanie
Tablica	O(n)	O(n log n)	O(n)
vector	O(n)	O(n log n)	O(n)
list	O(n)	O(n log n)	O(n)
stack	O(n)	O(n log n)	O(n)
Własna kolejka	O(n)	O(n²)	O(n)
BST	O(n log n)*	O(n)	O(n log n)*

* Dla BST średnia złożoność wstawiania wynosi O(log n) na element, czyli około O(n log n) dla n elementów. W najgorszym przypadku, gdy drzewo stanie się mocno niezrównoważone, może wynosić O(n) na element.

Ważne uwagi dotyczące testu

Wyniki nie powinny być traktowane jako absolutny ranking struktur danych. Czas działania zależy m.in. od:

procesora,

pamięci RAM,

kompilatora,

poziomu optymalizacji,

obciążenia systemu,

sposobu implementacji danej struktury,

rodzaju danych wejściowych.

Szczególnie istotne jest to w przypadku BST. Losowe dane zazwyczaj tworzą bardziej zrównoważone drzewo, natomiast dane uporządkowane mogą spowodować powstanie drzewa przypominającego listę.

Wymagania

Do skompilowania programu potrzebny jest kompilator obsługujący standard C++11 lub nowszy.

Program wykorzystuje standardowe biblioteki C++:

<iostream>
<vector>
<list>
<stack>
<algorithm>
<random>
<chrono>


Nie są wymagane żadne dodatkowe biblioteki zewnętrzne.

Kompilacja
G++

Przykładowa komenda:

g++ -std=c++11 -O2 main.cpp -o program


Następnie uruchomienie:

./program

Windows / MinGW
g++ -std=c++11 -O2 main.cpp -o program.exe


Uruchomienie:

program.exe

Cel projektu

Celem projektu jest praktyczne porównanie wydajności różnych struktur danych oraz obserwacja, jak sposób organizacji danych wpływa na czas wykonywania operacji.

Projekt pozwala porównać zarówno gotowe kontenery biblioteki standardowej C++, jak i własnoręcznie zaimplementowane struktury danych.

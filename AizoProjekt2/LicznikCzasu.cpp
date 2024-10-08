#include"LicznikCzasu.h"
#include"windows.h"
using namespace std;
#include<iostream>
void LicznikCzasu::start()//rozpoczêcie liczenia
{
    LARGE_INTEGER licznik;
    if (!QueryPerformanceFrequency(&licznik))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(licznik.QuadPart) / 1000.0;

    QueryPerformanceCounter(&licznik);
    CounterStart = licznik.QuadPart;
}
double LicznikCzasu::stop()//zakonczenie liczenia
{
    LARGE_INTEGER licznik;
    QueryPerformanceCounter(&licznik);
    return double(licznik.QuadPart - CounterStart) / PCFreq;//wynik w milisekundach
}
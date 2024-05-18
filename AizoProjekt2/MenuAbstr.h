#ifndef MENUABSTR_H
#define MENUABSTR_H
#include<iostream>

using namespace std;
class MenuAbstr {
public:
	int** wsk = nullptr;
	int* wagi = nullptr;
	int liczba_kraw = 0;
	int liczba_wierzcholkow = 0;
	int obecna_liczba_krawedzi = 0;
	void menu(MenuAbstr& obj);
	 virtual void wygeneruj(int liczba_wierzcholkow, int gestosc)=0;
	void wyswietlanie();
	virtual void algorytm1() = 0;
	virtual void generowanie_wag() = 0;
};
#endif // MENUABSTR_H
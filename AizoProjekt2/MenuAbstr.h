#ifndef MENUABSTR_H
#define MENUABSTR_H
#include<iostream>
#include<vector>


using namespace std;
class MenuAbstr {
public:
	int** wsk = nullptr;
	int* wagi = nullptr;
	vector<vector<pair<int, int>>> lista_sasiedztwa;//lista nastpenikow/poprzednikow z wagami
	
	int liczba_kraw = 0;
	int liczba_wierzcholkow = 0;
	int obecna_liczba_krawedzi = 0;
	void menu(MenuAbstr& obj);
	virtual void wygeneruj()=0;
	virtual void generowanie_listy() = 0;
	void wyswietlanie();
	virtual void algorytm1v1() = 0;
	virtual void algorytm1v2() = 0;
	virtual void algorytm2v1() = 0;
	virtual void generowanie_wag() = 0;
};
#endif // MENUABSTR_H
#ifndef MENUABSTR_H
#define MENUABSTR_H
#include<iostream>
#include<vector>
//v1 macierzowo
//v2 listowo

using namespace std;
class MenuAbstr {
public:
	int** wsk = nullptr;
	int* wagi = nullptr;
	vector<vector<pair<int, int>>> lista_sasiedztwa;//lista nastpenikow/poprzednikow z wagami
	
	int liczba_kraw = 0;
	int liczba_wierzcholkow = 0;
	int obecna_liczba_krawedzi = 0;
	virtual void menu(MenuAbstr& obj)=0;
	virtual void wygeneruj(int rozmiar, int gest)=0;
	virtual void generowanie_listy() = 0;
	virtual void wczytywanie() = 0;
	void wyswietlanie();
	virtual double algorytm1v1(int w1,int w2) = 0;//dla algorytmow mst drugi arguemnt nie ma znaczenia
	virtual double algorytm1v2(int w1,int w2) = 0;
	virtual double algorytm2v1(int w1,int w2) = 0;
	virtual double algorytm2v2(int w1,int w2) = 0;
	virtual void generowanie_wag();
};
#endif // MENUABSTR_H
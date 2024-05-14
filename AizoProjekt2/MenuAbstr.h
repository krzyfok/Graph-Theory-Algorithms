#include<iostream>

using namespace std;
class MenuAbstr {
public:
	
	void menu(MenuAbstr& obj);
	void wygeneruj(int liczba_wierzcholkow, int gestosc);
	void wyswietlanie();
	void generowanie_krawedzi();
};
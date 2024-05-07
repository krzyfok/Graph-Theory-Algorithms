#include<iostream>

using namespace std;
class MenuAbstr {
public:
	static int** wsk;
	void menu(MenuAbstr& obj);
	void wygeneruj(int liczba_wierzcholkow, int gestosc);
};
#include<iostream>
#include"MenuAbstr.h"

using namespace std;

int** MenuAbstr::wsk = nullptr;
void MenuAbstr::menu(MenuAbstr& obj)//menu g³owne
{

	while (true)
	{
		printf("MENU\n");
		printf("1.WCZYTAJ DANE Z PLIKU\n");
		printf("2.WYGENERUJ GRAF LOSOWO\n");
		printf("3.WYSWIETL GRAF\n");
		printf("4.ALGORYTM 1\n");
		printf("5.ALGORYTM 2\n");
		printf("6.ZMIANA TYPU\n");

		int x;
		cin >> x;
		switch (x)
		{
		

		default:
			break;
		}

	}

}
void MenuAbstr::wygeneruj(int liczba_wierzcholkow,int gestosc)
{
	int** wsk = new int* [liczba_wierzcholkow];
	int liczba_kraw = (liczba_wierzcholkow * (liczba_wierzcholkow - 1))/2 * gestosc / 100;//skierowany czy nie??
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		wsk[i] = new int[liczba_kraw];
	}
}
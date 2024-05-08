#include<iostream>
#include"MenuAbstr.h"

using namespace std;

int** wsk = nullptr;
int liczba_kraw = 0;
int liczba_wierzcholkow = 0;
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
		case 2: wygeneruj(10, 50);
			break;
		case 3: wyswietlanie();
			break;
		default:
			break;
		}

	}

}
void MenuAbstr::wygeneruj(int liczba_wierzcholkow1, int gestosc)
{
	liczba_wierzcholkow = liczba_wierzcholkow1;
	wsk = new int* [liczba_wierzcholkow];
	int obecna_liczba_krawedzi=0;
	liczba_kraw = (liczba_wierzcholkow * (liczba_wierzcholkow - 1)) / 2 * gestosc / 100;//skierowany czy nie?? dla mst NIESKIEROWANA
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		wsk[i] = new int[liczba_kraw];
	}

	//wypelnienie zerami
	for (int i = 0; i < liczba_wierzcholkow; ++i) {
		for (int j = 0; j < liczba_kraw; ++j) {
			wsk[i][j] = 0;
		}

	}

	//generacja spojnego
	for (int i = 1; i < liczba_wierzcholkow; i++)
	{
		int wybrany_wierzcholek = rand() % (i);
		wsk[i][i - 1] = 1;
		wsk[wybrany_wierzcholek][i - 1] = 1;
		obecna_liczba_krawedzi++;
	}
	//generacja pozosta³ych 
	for (int i = liczba_wierzcholkow; i < liczba_kraw; i++)
	{
		int wylosowany_wierzch1 = rand() % liczba_wierzcholkow;
		int wylosowany_wierzch2 = rand() % liczba_wierzcholkow;
		//sprawdzenie czy krawedz nie istnieje
		for (int j = 0; j < obecna_liczba_krawedzi; j++)
		{

		}
	}

	//usunac wyswietlanie potem
	for (int i = 0; i < liczba_wierzcholkow; ++i) {
		for (int j = 0; j < liczba_kraw; ++j) {
			printf("%3d", wsk[i][j]);
		}
		cout << endl;
	}
	
}

void MenuAbstr::wyswietlanie()
{

	//wyswietlanie
	for (int i = 0; i < liczba_wierzcholkow; ++i) {
		for (int j = 0; j < liczba_kraw; ++j) {
			printf("%3d", wsk[i][j]);
		}
		cout << endl;
	}
	
}


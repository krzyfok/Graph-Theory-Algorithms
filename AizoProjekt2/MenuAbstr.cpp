#include<iostream>
#include"MenuAbstr.h"

using namespace std;

int** wsk = nullptr;
int liczba_kraw = 0;
int liczba_wierzcholkow = 0;
int obecna_liczba_krawedzi = 0;
void MenuAbstr::menu(MenuAbstr& obj)//menu g�owne
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
		case 2: wygeneruj(5, 100);
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
	liczba_kraw = 0;
	liczba_wierzcholkow = 0;
	obecna_liczba_krawedzi = 0;
	liczba_wierzcholkow = liczba_wierzcholkow1;
	wsk = new int* [liczba_wierzcholkow];

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
	for (int k = obecna_liczba_krawedzi; k < liczba_kraw; k++) {
	generowanie_krawedzi();
	}
	

	printf("\nWYGENEROWANO\n");
	
}
void MenuAbstr::generowanie_krawedzi()
{	//dodac sprawdzenie czy wierzcholek nie ma juz wszystkich krawedzi??
	int wylosowany_wierzch1 = rand() % liczba_wierzcholkow;
	cout << wylosowany_wierzch1 << endl;
	//generacja i wypelnienie 0
	int* dostepne_wierz = new int[liczba_wierzcholkow];
	for (int i = 0; i < liczba_wierzcholkow; i++) 
	{
		dostepne_wierz[i]=0;
	}
	
	//szukanie dostepnych wierzchohlkow 0=dostpeny

	for (int i = 0; i < obecna_liczba_krawedzi;i++)
	{
		if (wsk[wylosowany_wierzch1][i] == 1)
		{
			for (int k = 0; k < liczba_wierzcholkow; k++)
			{
				if (wsk[k][i] == 1)
				{
					dostepne_wierz[k] = 1;
				}
			}
		}
	}
	

//losowanie z puli dost�pnych
	//liczenie ile dostepnych wierzch
	int liczba_dostepnych = 0;
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		if (dostepne_wierz[i] == 0)
		{
			liczba_dostepnych++;
		}
	}
	if (liczba_dostepnych == 0)return;
	
	int wylosowany_wierzch2 = rand() % liczba_dostepnych;

	//zapisywanie wierzcho�ka do macierzy
	int licznik = 0;
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		if (dostepne_wierz[i] == 0)
		{
			if (licznik == wylosowany_wierzch2)
			{
				wsk[wylosowany_wierzch1][obecna_liczba_krawedzi] = 1;
				wsk[wylosowany_wierzch2][obecna_liczba_krawedzi] = 1;
				obecna_liczba_krawedzi++;
				
			}
			licznik++;
			
		}
	}
	delete[] dostepne_wierz;
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


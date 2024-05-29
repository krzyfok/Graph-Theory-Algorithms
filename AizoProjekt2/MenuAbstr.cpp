#include<iostream>
#include"MenuAbstr.h"

using namespace std;


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
		case 2: obj.wygeneruj();
			break;
		case 3: wyswietlanie();
			break;
		case 4: obj.algorytm1v1();
			obj.algorytm1v2();
			break;
		case 5: obj.algorytm2v1();
			obj.algorytm2v2();
			break;
		case 6:
			return;
		default:
			break;
		}

	}

}



void MenuAbstr::wyswietlanie()
{
	for (int j = 0; j < liczba_kraw; ++j) {
		printf("%3d", wagi[j]);
	}
	cout << endl;
	//wyswietlanie
	for (int i = 0; i < liczba_wierzcholkow; ++i) {
		
		for (int j = 0; j < liczba_kraw; ++j) {
			printf("%3d", wsk[j][i]);
		}
		cout << endl;
	}

	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		cout << i << " ";
		for (int j = 0; j < lista_sasiedztwa[i].size(); j++) {
			
			cout<< "(" << lista_sasiedztwa[i][j].first << ", " << lista_sasiedztwa[i][j].second << ")";
		}
		cout << endl;
	}
	
}
void MenuAbstr::generowanie_wag()
{
	wagi = new int[liczba_kraw];
	for (int i = 0; i < liczba_kraw; i++)
	{
		wagi[i] = (rand() % 100) + 1;

	}


	printf("\nWYGENEROWANO_WAGI\n");

}


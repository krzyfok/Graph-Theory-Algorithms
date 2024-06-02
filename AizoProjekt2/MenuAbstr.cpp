#include<iostream>
#include"MenuAbstr.h"
#include"LicznikCzasu.h"
using namespace std;


LicznikCzasu licznik;



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


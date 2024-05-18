#include"MenuAbstr.h"
#include"MenuMst.h"
#include<queue>
using namespace std;


#define inf INT_MAX

void MenuMst::wygeneruj()
{
	int gestosc;
	cout << "PODAJ LICZBE WIERZCHOLKOW: " ;
	cin >> liczba_wierzcholkow;
	cout << endl << "PODAJ GESTOSC: ";
	cin >> gestosc;
	liczba_kraw = 0;
	obecna_liczba_krawedzi = 0;
	vector<vector<int>>lista_nastepnikow(liczba_wierzcholkow);
	int dostepna_liczba_krawedzi = 0;
	wsk = new int* [liczba_wierzcholkow];
	
	int** tab_pom = new int* [2];
	liczba_kraw = (liczba_wierzcholkow * (liczba_wierzcholkow - 1)) / 2 * gestosc / 100;//skierowany czy nie?? dla mst NIESKIEROWANA
	int liczba_kraw_wszystkich = (liczba_wierzcholkow * (liczba_wierzcholkow - 1)) / 2;
	dostepna_liczba_krawedzi = liczba_kraw_wszystkich;
	//generacja macierzy
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
	//geenracja tablicy pomocniczej do losowania krawedzi
	for (int i = 0; i < 2; i++)
	{
		tab_pom[i] = new int[liczba_kraw_wszystkich];
	}
	//generacja wszystkich mozliwych wierzcholkow
	int indeks = 0;
	int pom = 0;
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{

		for (int k = pom + 1; k < liczba_wierzcholkow; k++)
		{
			tab_pom[0][indeks] = pom;
			tab_pom[1][indeks] = k;
			indeks++;
		}
		pom++;
	}



	//generacja spojnego
	for (int i = 1; i < liczba_wierzcholkow; i++)
	{
		int wybrany_wierzcholek = rand() % (i);
		wsk[i][i - 1] = 1;
		wsk[wybrany_wierzcholek][i - 1] = 1;
		obecna_liczba_krawedzi++;
		dostepna_liczba_krawedzi--;
	}
	//usuwanie wierzcholkow spojnych z tab_pom --rozpoznanie usuniêtego przez 0 0 w tabeli pom
	for (int i = 0; i < obecna_liczba_krawedzi; i++)
	{
		int wierzch[2];
		int indeks = 0;
		for (int k = 0; k < liczba_wierzcholkow; k++)
		{
			if (wsk[k][i] == 1)
			{
				wierzch[indeks] = k;
				indeks++;
			}

		}

		for (int j = 0; j < liczba_kraw_wszystkich; j++)
		{
			if ((tab_pom[0][j] == wierzch[0] && tab_pom[1][j] == wierzch[1]) || (tab_pom[0][j] == wierzch[1] && tab_pom[1][j] == wierzch[0]))
			{
				lista_nastepnikow[tab_pom[0][j]].push_back(tab_pom[1][j]);
				lista_nastepnikow[tab_pom[1][j]].push_back(tab_pom[0][j]);
				tab_pom[0][j] = 0;
				tab_pom[1][j] = 0;
			}
		}


	}

	//losowanie wierzcholkow z tab_pom az do uzyskania zadanej gestosci
	for (int i = obecna_liczba_krawedzi; i < liczba_kraw; i++)
	{
		int wylosowany_ideks = rand() % dostepna_liczba_krawedzi;
		int indeks_dostepnych = 0;

		for (int k = 0; k < liczba_kraw_wszystkich; k++)
		{

			if ((tab_pom[0][k] != 0) || (tab_pom[1][k] != 0))
			{

				if (indeks_dostepnych == wylosowany_ideks)
				{
					wsk[tab_pom[0][k]][i] = 1;
					wsk[tab_pom[1][k]][i] = 1;
					lista_nastepnikow[tab_pom[0][k]].push_back(tab_pom[1][k]);
					lista_nastepnikow[tab_pom[1][k]].push_back(tab_pom[0][k]);
					tab_pom[0][k] = 0;
					tab_pom[1][k] = 0;
					dostepna_liczba_krawedzi--;
					obecna_liczba_krawedzi++;
					
				
				}
				indeks_dostepnych++;

			}
		}
	}
	delete[] tab_pom[0];
	delete[] tab_pom[1];
	delete[] tab_pom;
	
	for (size_t i = 0; i < liczba_wierzcholkow; ++i) {
		cout << i << ": ";
		for (size_t j = 0; j < lista_nastepnikow[i].size(); ++j) {
			cout << lista_nastepnikow[i][j] << " ";
		}
		cout << std::endl;
	}

	printf("\nWYGENEROWANO_GRAF\n");
	generowanie_wag();
}
void MenuMst::generowanie_wag()
{
	wagi = new int[liczba_kraw];
	for (int i = 0; i < liczba_kraw; i++)
	{
		wagi[i] = rand() % 100;
	}


	printf("\nWYGENEROWANO_WAGI\n");

}

void MenuMst::algorytm1v1()// koniec?????
{
	int start;
	cout << "PODAJ WIERZCHOLEK STARTOWY:";
	cin >> start;
	cout << endl;
	#define nieskon INT_MAX
	vector<int>waga_minimalna_wierzcholka(liczba_wierzcholkow, nieskon);
	vector<int>rodzic_wierzcholka(liczba_wierzcholkow, 0);
	typedef pair<int, int>krawedzie;//waga , poczatek, koniec
	priority_queue<krawedzie,vector<krawedzie>,greater<krawedzie>> kolejka;
	vector<bool> odwiedzone(liczba_wierzcholkow, false);
	int minimalna_waga_drzewa = 0;
	kolejka.push({ 0,start });
	waga_minimalna_wierzcholka[start] = 0;
	while (!kolejka.empty())
	{
		int waga = kolejka.top().first;//pobranie wierzcholka o najmnijeszej wadze
		int wierzcholek = kolejka.top().second;
		
		kolejka.pop();
		if (odwiedzone[wierzcholek] == true)
		{
			
			continue;
		}//sprawdzenie czy wierzcholek zosta³ odwiedzony
		
		minimalna_waga_drzewa = minimalna_waga_drzewa + waga;//zwiekszenia wagi mst
		odwiedzone[wierzcholek] = true;//zaznaczenie ¿e wierzcho³ke zosta³ odwiedzony

	
		;
		int waga_nowego;
		int nowy_wierzcholek=-1;
		for (int i = 0; i < liczba_kraw; i++)//przegl¹danie krawedzi wychodz¹cych z obecnego wierzchokla i dodawanie jezeli nie zosta³y jeszcze odwiedzone
		{
			//wsk[wierzcholke][krawedz]
			if (wsk[wierzcholek][i] == 1)
			{
				for (int k = 0; k < liczba_wierzcholkow; k++)
				{
					if (wierzcholek != k && wsk[k][i] == 1)
					{
						nowy_wierzcholek = k;
						waga_nowego = wagi[i];
					}
				}
			}
			//teraz w wierzch[] s¹ 2 wierzcholki kraawedzi ³¹czacej z pocz¹kowym wierzcholkiem
			
			if (nowy_wierzcholek != -1) {
				if (odwiedzone[nowy_wierzcholek] == false && waga_minimalna_wierzcholka[nowy_wierzcholek]>waga_nowego)
				{
					kolejka.push({ waga_nowego,nowy_wierzcholek });
					waga_minimalna_wierzcholka[nowy_wierzcholek] = waga_nowego;
					rodzic_wierzcholka[nowy_wierzcholek] = wierzcholek;
				}
			}
		}
	}
	cout <<"MINIMALNA WAGA: " << minimalna_waga_drzewa <<endl;
	for (int i = 1; i < liczba_wierzcholkow; ++i) {
		if (i == start) { printf("%d - %d : %d\n", rodzic_wierzcholka[i], i, waga_minimalna_wierzcholka[rodzic_wierzcholka[i]]); }
		else printf("%d - %d : %d\n", rodzic_wierzcholka[i], i, waga_minimalna_wierzcholka[i]);
	}
	
}
void MenuMst::algorytm1v2()//lista nastepnikow/poprzednikow
{
	
}
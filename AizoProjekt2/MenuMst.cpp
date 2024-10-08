#include"MenuAbstr.h"
#include"MenuMst.h"
#include<queue>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"LicznikCzasu.h"
using namespace std;


//dodac wczytwanie z pliku

void MenuMst::wygeneruj(int rozmiar, int gest)
{
	int gestosc;
	
	gestosc = gest;
	liczba_wierzcholkow = rozmiar;
	liczba_kraw = 0;
	obecna_liczba_krawedzi = 0;
	liczba_kraw = (liczba_wierzcholkow * (liczba_wierzcholkow - 1)) / 2 * gestosc / 100;
	int dostepna_liczba_krawedzi = 0;
	wsk = new int* [liczba_kraw];
	
	int** tab_pom = new int* [2];
	
	int liczba_kraw_wszystkich = (liczba_wierzcholkow * (liczba_wierzcholkow - 1)) / 2;
	dostepna_liczba_krawedzi = liczba_kraw_wszystkich;



	//generacja macierzy
	for (int i = 0; i < liczba_kraw; i++)
	{
		wsk[i] = new int[liczba_wierzcholkow];
	}
	//wypelnienie zerami
	for (int i = 0; i < liczba_kraw; ++i) {
		for (int j = 0; j < liczba_wierzcholkow; ++j) {
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



	//generacja spojnego grafu
	for (int i = 1; i < liczba_wierzcholkow; i++)
	{
		int wybrany_wierzcholek = rand() % (i);
		wsk[i-1][i] = 1;
		wsk[i-1][wybrany_wierzcholek] = 1;
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
			if (wsk[i][k] == 1)
			{
				wierzch[indeks] = k;
				indeks++;
			}
		}

		for (int j = 0; j < liczba_kraw_wszystkich; j++)
		{
			if ((tab_pom[0][j] == wierzch[0] && tab_pom[1][j] == wierzch[1]) || (tab_pom[0][j] == wierzch[1] && tab_pom[1][j] == wierzch[0]))
			{
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
					wsk[i][tab_pom[0][k]] = 1;
					wsk[i][tab_pom[1][k]] = 1;
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
	
	
	
	printf("\nWYGENEROWANO_GRAF\n");
	generowanie_wag();//generacja wag
	
	generowanie_listy();
	printf("\nWYGENEROWANO_LISTE\n");
	
}
void MenuMst::generowanie_listy()
{
	lista_sasiedztwa.clear();
	lista_sasiedztwa.resize(liczba_wierzcholkow);

	for (int i = 0; i < liczba_kraw; i++)
	{
		int wierzch[2];
		int indeks = 0;
		for(int k=0;k<liczba_wierzcholkow;k++)
		{
			if (wsk[i][k] == 1)
			{
				wierzch[indeks] = k;
				
				indeks++;
			}
			
		}
		
		lista_sasiedztwa[wierzch[0]].push_back(make_pair(wierzch[1], wagi[i]));//indeks,waga
		lista_sasiedztwa[wierzch[1]].push_back(make_pair(wierzch[0], wagi[i]));
		
	}

}

void MenuMst::wczytywanie()
{
	string nazwa;

	string wiersz;
	int w1, w2, waga;
	cout << "PODAJ NAZWE PLIKU: ";
	cin >> nazwa;
	ifstream plik(nazwa);
	int i = -1;
	if (plik.is_open())
	{
		while (getline(plik, wiersz, '\n'))
		{
			if (i == -1)
			{

				istringstream iss(wiersz);
				iss >> liczba_kraw >> liczba_wierzcholkow;
				
				wsk = new int* [liczba_kraw];

				//generacja macierzy
				for (int i = 0; i < liczba_kraw; i++)
				{
					wsk[i] = new int[liczba_wierzcholkow];
				}
				//wypelnienie zerami
				for (int i = 0; i < liczba_kraw; ++i) {
					for (int j = 0; j < liczba_wierzcholkow; ++j) {
						wsk[i][j] = 0;
					}

				}
				generowanie_wag();

			}
			else
			{
				istringstream iss(wiersz);
				iss >> w1 >> w2 >> waga;
				wagi[i] = waga;
				wsk[i][w1] = 1;
				wsk[i][w2] = 1;
			}
			i++;


		}
	}
	else(cout << "BRAK PLIKU\n");
	plik.close();
	generowanie_listy();
}



double MenuMst::algorytm1v1(int w1, int w2)
{
	licznik.start();
	int start=0;
	#define nieskon INT_MAX
	vector<int>waga_minimalna_wierzcholka(liczba_wierzcholkow, nieskon);
	vector<int>rodzic_wierzcholka(liczba_wierzcholkow, 0);
	typedef pair<int, int>krawedzie;//waga ,koniec
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
			
			if (wsk[i][wierzcholek] == 1)
			{
				for (int k = 0; k < liczba_wierzcholkow; k++)
				{
					if (wierzcholek != k && wsk[i][k] == 1)
					{
						nowy_wierzcholek = k;
						waga_nowego = wagi[i];
					}
				}
			}
			
			
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
	
	for (int i = 1; i < liczba_wierzcholkow; ++i) {
		if (i == start) { printf("%d - %d : %d\n", rodzic_wierzcholka[i], i, waga_minimalna_wierzcholka[rodzic_wierzcholka[i]]); }
		else printf("%d - %d : %d\n", rodzic_wierzcholka[i], i, waga_minimalna_wierzcholka[i]);
	}
	cout << "MINIMALNA WAGA: " << minimalna_waga_drzewa << endl;
	return licznik.stop();
}
double MenuMst::algorytm1v2(int w1, int w2)//lista nastepnikow/poprzednikow
{
	licznik.start();
	int start=0;
	
	#define nieskon INT_MAX
	vector<int>waga_minimalna_wierzcholka(liczba_wierzcholkow, nieskon);
	vector<int>rodzic_wierzcholka(liczba_wierzcholkow, 0);
	typedef pair<int, int>krawedzie;//waga , koniec
	priority_queue<krawedzie, vector<krawedzie>, greater<krawedzie>> kolejka;

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

		int waga_nowego;
		int nowy_wierzcholek = -1;
		for (int i = 0; i < lista_sasiedztwa[wierzcholek].size(); i++)//przegl¹danie krawedzi wychodz¹cych z obecnego wierzchokla i dodawanie jezeli nie zosta³y jeszcze odwiedzone
		{
			nowy_wierzcholek = lista_sasiedztwa[wierzcholek][i].first;
			waga_nowego= lista_sasiedztwa[wierzcholek][i].second;


			if (nowy_wierzcholek != -1) {
				if (odwiedzone[nowy_wierzcholek] == false && waga_minimalna_wierzcholka[nowy_wierzcholek] > waga_nowego)
				{
					kolejka.push({ waga_nowego,nowy_wierzcholek });
					waga_minimalna_wierzcholka[nowy_wierzcholek] = waga_nowego;
					rodzic_wierzcholka[nowy_wierzcholek] = wierzcholek;
				}
			}
		}
	}
	
	for (int i = 1; i < liczba_wierzcholkow; ++i) {
		if (i == start) { printf("%d - %d : %d\n", rodzic_wierzcholka[i], i, waga_minimalna_wierzcholka[rodzic_wierzcholka[i]]); }
		else printf("%d - %d : %d\n", rodzic_wierzcholka[i], i, waga_minimalna_wierzcholka[i]);
	}
	cout << "MINIMALNA WAGA: " << minimalna_waga_drzewa << endl;
	return licznik.stop();

}
double MenuMst::algorytm2v1(int w1, int w2)
{
	licznik.start();
	int minimalna_waga_drzewa = 0;
	int* parent = new int[liczba_wierzcholkow];
	int* rank = new int[liczba_wierzcholkow];
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		rank[i] = 0;
	}
	MakeSet(parent);
	quick_sort_macierz(0, liczba_kraw - 1);
	for (int i = 0; i < liczba_kraw; i++)
	{
		//szukanie wierzcholkow krawdedzi w macierzy incydencji
		int wierzch[2];
			int indeks = 0;
			for (int w = 0; w < liczba_wierzcholkow; w++)
			{
				if (wsk[i][w] == 1)
				{
					wierzch[indeks] = w;
					indeks++;
				}
			}

			//znalezione wierzcholki
			int w1 = wierzch[0];
			int w2 = wierzch[1];
			int r_w1 = FindSet(parent, w1);
			int r_w2 = FindSet(parent, w2);
			if (r_w1 != r_w2)
			{
				cout << w1 << " - " << w2 <<" : "<<wagi[i] << endl;
				minimalna_waga_drzewa = minimalna_waga_drzewa + wagi[i];
				Union(parent, rank, r_w1, r_w2);
			}
	}
	
	
	cout << "MINIMALNA WAGA: " << minimalna_waga_drzewa << endl;
	delete[] parent;
	delete[] rank;
	return licznik.stop();
}
double MenuMst::algorytm2v2(int w1, int w2)
{
	licznik.start();
	int minimalna_waga_drzewa = 0;
	int* parent = new int[liczba_wierzcholkow];
	int* rank = new int[liczba_wierzcholkow];
	
	//tworzenie listy krawedzi
	int** lista= new int* [liczba_kraw];
	for (int i = 0; i < liczba_kraw; i++)
	{
		lista[i] = new int[3];//waga pocztek koniec//nieskierowany wiec tylko raz kazda para
	}
	//wypelnienie zerami
	for (int i = 0; i < liczba_kraw; ++i) {
		for (int j = 0; j < 3; ++j) {
			lista[i][j] = 0;
		}

	}
	int indeks = 0;
	bool znaleziono = false;
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		//pobranie krwaedzi z listy sasiedztwa i sprawdzenie czy jest w liscie krawedzi
		for (int k = 0; k < lista_sasiedztwa[i].size(); k++) {
			int poczatek = i;
			int koniec = lista_sasiedztwa[i][k].first;
			for (int j = 0; j < liczba_kraw; j++)
			{
				if ((lista[j][1] == poczatek && lista[j][2] == koniec) || (lista[j][1] == koniec && lista[j][2] == poczatek))
				{
					znaleziono = true;
					break;
				}
				
			}
			if (znaleziono == false)
			{
				lista[indeks][0] = lista_sasiedztwa[i][k].second;
				lista[indeks][1] = poczatek;
				lista[indeks][2] = koniec;
				indeks++;
			}
			znaleziono = false;
			
		}
	}
	//lista utworzona
	

	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		rank[i] = 0;
	}
	MakeSet(parent);

	quick_sort_lista(0, liczba_kraw - 1, lista);

	for (int i = 0; i < liczba_kraw; i++)
	{
	
		int w1 = lista[i][1];
		int w2 = lista[i][2];
		int r_w1 = FindSet(parent, w1);
		int r_w2 = FindSet(parent, w2);
		if (r_w1 != r_w2)
		{
			cout << w1 << " - " << w2 << " : " << lista[i][0] << endl;
			minimalna_waga_drzewa = minimalna_waga_drzewa + lista[i][0];
			Union(parent, rank, r_w1, r_w2);
		}
	}



	cout << "MINIMALNA WAGA: " << minimalna_waga_drzewa << endl;
	delete[] parent;
	delete[] rank;
	delete[] lista;


	return licznik.stop();
}



void MenuMst::MakeSet(int * parent)
{
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		parent[i] = i;
	}
} 

int MenuMst::FindSet(int* parent,int x)
{
	if (parent[x] != x)
	{
		parent[x] = FindSet(parent, parent[x]);
	}
	return  parent[x];
}
void MenuMst::Union(int* parent,int * rank,int x,int y)
{
	int a = FindSet(parent, x);
	int b = FindSet(parent, y);
	if (rank[a] > rank[b])
	{
		parent[b] = a;
	}
	else
	{
		parent[a] = b;
	}
	if (rank[a] == rank[b])
	{
		rank[b] = rank[b] + 1;
	}

}
void MenuMst::quick_sort_macierz(int poczatek, int koniec)
{
	if (poczatek >= koniec)
	{
		return;
	}
	int polowa = quick_sort_podzial_macierz( poczatek, koniec);
	quick_sort_macierz( poczatek, polowa);
	quick_sort_macierz( polowa + 1, koniec);
}
int MenuMst::quick_sort_podzial_macierz(int poczatek, int koniec)
{

	int pivot = wagi[poczatek];
	int l = poczatek;
	int r = koniec;
	while (true)
	{
		while (wagi[l] < pivot)l++;
		while (wagi[r] > pivot)r--;
		if (r > l)
		{
			swap(wagi[l], wagi[r]);
			swap(wsk[l], wsk[r]);
			r--;
			l++;
		}
		else {
			if (r == koniec)r--;
			return r;
		}
	}
}

void MenuMst::quick_sort_lista(int poczatek, int koniec,int **tab)
{
	if (poczatek >= koniec)
	{
		return;
	}
	int polowa = quick_sort_podzial_lista(poczatek, koniec,tab);
	quick_sort_lista(poczatek, polowa,tab);
	quick_sort_lista(polowa + 1, koniec,tab);
}
int MenuMst::quick_sort_podzial_lista(int poczatek, int koniec,int **tab)
{

	int pivot = tab[poczatek][0];
	int l = poczatek;
	int r = koniec;
	while (true)
	{
		while (tab[l][0] < pivot)l++;
		while (tab[r][0] > pivot)r--;
		if (r > l)
		{
			swap(tab[l], tab[r]);
			
			r--;
			l++;
		}
		else {
			if (r == koniec)r--;
			return r;
		}
	}
}

void MenuMst::menu(MenuAbstr& obj)
{

	while (true)
	{
		printf("MENU\n");
		printf("1.WCZYTAJ DANE Z PLIKU\n");
		printf("2.WYGENERUJ GRAF LOSOWO\n");
		printf("3.WYSWIETL GRAF\n");
		printf("4.ALGORYTM PRIMA\n");
		printf("5.ALGORYTM KRUSKALA\n");
		printf("6.ZMIANA TYPU\n");

		int x;
		cin >> x;
		switch (x)
		{
		case 1:
			wczytywanie();
			break;
		case 2: 
			int l, g;
			cout << "PODAJ LICZBE WIERZCHOLKOW: ";
			cin >> l;
			cout << "\n";
			cout << "PODAJ GESTOSC: ";
			cin >> g;
			cout << "\n";
			obj.wygeneruj(l,g);
			break;
		case 3: wyswietlanie();
			break;
		case 4:
			if (wsk != nullptr) {
				cout << obj.algorytm1v1(0, 0) << "milisekund" << endl;
				cout << obj.algorytm1v2(0, 0) << "milisekund" << endl;
			}
			else
			{
				printf("BRAK DANYCH\n");
			}
			break;
		case 5:
			if (wsk != nullptr) {
				cout << obj.algorytm2v1(0, 0) << "milisekund" << endl;
				cout << obj.algorytm2v2(0, 0) << "milisekund" << endl;
			}
			else
			{
				printf("BRAK DANYCH\n");
			}
			break;
		case 6:
			delete[] wsk;
			delete[] wagi;

			return;
		default:
			break;
		}

	}

}

#include"MenuAbstr.h"
#include"MenuSciezka.h"
#include<queue>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"LicznikCzasu.h"
using namespace std;

void MenuSciezka::wygeneruj(int rozmiar,int gest)
{
	int gestosc;
	gestosc = gest;
	liczba_wierzcholkow = rozmiar;
	liczba_kraw = 0;
	obecna_liczba_krawedzi = 0;
	liczba_kraw = (liczba_wierzcholkow * (liczba_wierzcholkow - 1)) * gestosc / 100;
	int dostepna_liczba_krawedzi = 0;
	wsk = new int* [liczba_kraw];

	int** tab_pom = new int* [2];

	int liczba_kraw_wszystkich = (liczba_wierzcholkow * (liczba_wierzcholkow - 1)) ;
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
			tab_pom[0][indeks] = k;
			tab_pom[1][indeks] = pom;
			indeks++;

		}
		pom++;
	}

	

	//generacja spojnego
	for (int i = 1; i < liczba_wierzcholkow; i++)
	{
		//losowanie czy poczatek czy koniec kraweddzi
		bool poczatek = false;
		int losowa = rand();
		if (losowa % 2 == 0)
		{
			poczatek = true;
		}
		int wybrany_wierzcholek = rand() % (i);
		if (poczatek) {
			wsk[i - 1][i] = 1;
			wsk[i - 1][wybrany_wierzcholek] = -1;
		}
		else if (!poczatek)
		{
			wsk[i - 1][i] = -1;
			wsk[i - 1][wybrany_wierzcholek] = 1;
		}
		obecna_liczba_krawedzi++;
		dostepna_liczba_krawedzi--;
	}
	//usuwanie wierzcholkow spojnych z tab_pom --rozpoznanie usuniêtego przez 0 0 w tabeli pom
	for (int i = 0; i < obecna_liczba_krawedzi; i++)
	{
		int wierzch[2];
		
		for (int k = 0; k < liczba_wierzcholkow; k++)
		{
			if (wsk[i][k] == 1)//indesk 0 poczatek, 1 koniec krawedzi
			{
				wierzch[0] = k;
				
			}
			if (wsk[i][k] == -1)
			{
				wierzch[1] = k;
				
			}

		}

		for (int j = 0; j < liczba_kraw_wszystkich; j++)
		{
			if (tab_pom[0][j] == wierzch[0] && tab_pom[1][j] == wierzch[1])
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
					wsk[i][tab_pom[1][k]] = -1;

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

void MenuSciezka::generowanie_listy()
{
	lista_sasiedztwa.clear();
	lista_sasiedztwa.resize(liczba_wierzcholkow);

	for (int i = 0; i < liczba_kraw; i++)
	{
		int wierzch[2];

		for (int k = 0; k < liczba_wierzcholkow; k++)
		{
			if (wsk[i][k] == 1)
			{
				wierzch[0] = k;

				
			}
			if (wsk[i][k] == -1)
			{
				wierzch[1] = k;


			}

		}

		lista_sasiedztwa[wierzch[0]].push_back(make_pair(wierzch[1], wagi[i]));//indeks,waga
		
	}
}

void MenuSciezka::wczytywanie()
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
				wsk[i][w2] = -1;
			}
			i++;


		}
	}
	else(cout << "BRAK PLIKU\n");
	plik.close();
	generowanie_listy();

}
double MenuSciezka::algorytm1v1(int w1, int w2)
{
	licznik.start();
	int start = 0, koniec = 0;
	#define nieskon INT_MAX
	start = w1;
	koniec = w2;
	vector<int>odleglosc_od_wierzcholka(liczba_wierzcholkow, nieskon);
	vector<int>wierzcholek_poprzedzajacy(liczba_wierzcholkow, NULL);
	typedef pair<int, int>krawedzie;//waga ,koniec
	priority_queue<krawedzie, vector<krawedzie>, greater<krawedzie>> kolejka;

	vector<bool> odwiedzone(liczba_wierzcholkow, false);
	int minimalna_waga_drzewa = 0;
	kolejka.push({ 0,start });
	odleglosc_od_wierzcholka[start] = 0;
	while (!kolejka.empty())
	{
		//int waga = kolejka.top().first;//pobranie wierzcholka o najmnijeszej wadze
		int wierzcholek = kolejka.top().second;

		kolejka.pop();
		for (int i = 0; i < liczba_kraw; i++)//przegl¹danie krawedzi wychodz¹cych z obecnego wierzchokla 
		{
			int nowy_wierzcholek=-1;
			int waga_nowego;
			//wsk[wierzcholke][krawedz]
			if (wsk[i][wierzcholek] == 1)
			{
				for (int k = 0; k < liczba_wierzcholkow; k++)
				{
					if (wierzcholek != k && wsk[i][k] == -1)
					{
						nowy_wierzcholek = k;
						waga_nowego = wagi[i];
					}
				}
			}
			if(nowy_wierzcholek!=-1){
			if (odleglosc_od_wierzcholka[nowy_wierzcholek] > odleglosc_od_wierzcholka[wierzcholek] + waga_nowego)
			{
				odleglosc_od_wierzcholka[nowy_wierzcholek] = odleglosc_od_wierzcholka[wierzcholek] + waga_nowego;
				kolejka.push({ odleglosc_od_wierzcholka[nowy_wierzcholek],nowy_wierzcholek});
				wierzcholek_poprzedzajacy[nowy_wierzcholek] = wierzcholek;
			}
			}
		}

	}


	printf("KOSZT SCIEZKI= %d \n",odleglosc_od_wierzcholka[koniec]);
	int wierzch=koniec;
	while (wierzch != start)
	{
		cout << wierzch << " " ;
	
		wierzch = wierzcholek_poprzedzajacy[wierzch];
	}
	cout << wierzch<<endl;
	return licznik.stop();
}

double MenuSciezka::algorytm1v2(int w1, int w2)
{
	licznik.start();
	int start = 0, koniec = 0;
#define nieskon INT_MAX
	start = w1;
	koniec = w2;
	vector<int>odleglosc_od_wierzcholka(liczba_wierzcholkow, nieskon);
	vector<int>wierzcholek_poprzedzajacy(liczba_wierzcholkow, NULL);
	typedef pair<int, int>krawedzie;//waga ,koniec
	priority_queue<krawedzie, vector<krawedzie>, greater<krawedzie>> kolejka;

	vector<bool> odwiedzone(liczba_wierzcholkow, false);
	int minimalna_waga_drzewa = 0;
	kolejka.push({ 0,start });
	odleglosc_od_wierzcholka[start] = 0;
	while (!kolejka.empty())
	{
		
		int wierzcholek = kolejka.top().second;

		kolejka.pop();
		int nowy_wierzcholek = -1;
		int waga_nowego;
		for (int i = 0; i < lista_sasiedztwa[wierzcholek].size(); i++)//przegl¹danie krawedzi wychodz¹cych z obecnego wierzchokla i dodawanie jezeli nie zosta³y jeszcze odwiedzone
		{
			nowy_wierzcholek = lista_sasiedztwa[wierzcholek][i].first;
			waga_nowego = lista_sasiedztwa[wierzcholek][i].second;


			if (nowy_wierzcholek != -1) {
				if (odleglosc_od_wierzcholka[nowy_wierzcholek] > odleglosc_od_wierzcholka[wierzcholek] + waga_nowego)
				{
					odleglosc_od_wierzcholka[nowy_wierzcholek] = odleglosc_od_wierzcholka[wierzcholek] + waga_nowego;
					kolejka.push({ odleglosc_od_wierzcholka[nowy_wierzcholek],nowy_wierzcholek });
					wierzcholek_poprzedzajacy[nowy_wierzcholek] = wierzcholek;
				}
			}
		}

	}


	printf("KOSZT SCIEZKI= %d \n", odleglosc_od_wierzcholka[koniec]);
	int wierzch = koniec;
	while (wierzch != start)
	{
		cout << wierzch << " ";

		wierzch = wierzcholek_poprzedzajacy[wierzch];
	}
	cout << wierzch << endl;
	return licznik.stop();
}
double MenuSciezka::algorytm2v1(int w1, int w2)
{
	licznik.start();
	int start = 0, koniec = 0;
	#define nieskon INT_MAX
	start = w1;
	koniec = w2;
	vector<int>odleglosc_od_wierzcholka(liczba_wierzcholkow, nieskon);
	vector<int>wierzcholek_poprzedzajacy(liczba_wierzcholkow, NULL);
	odleglosc_od_wierzcholka[start] = 0;
	typedef pair<int, int>krawedzie;//waga ,koniec
	for (int i = 1; i <= liczba_wierzcholkow - 1; i++)
	{
		for (int j = 0; j < liczba_kraw; j++)
		{
			int u;
			int v;
			int waga;
			//szuaknie wierzcholkow krawdzie w macierzy incydencji
			for (int w = 0; w < liczba_wierzcholkow; w++)
			{
				if (wsk[j][w] == 1)
				{
					u = w;
				}
				if (wsk[j][w] == -1)
				{
					v = w;
				}
			}
			waga = wagi[j];
			if (odleglosc_od_wierzcholka[u] != nieskon && odleglosc_od_wierzcholka[u] + waga < odleglosc_od_wierzcholka[v])
			{
				odleglosc_od_wierzcholka[v] = odleglosc_od_wierzcholka[u] + waga;
				wierzcholek_poprzedzajacy[v] = u;
			}
			
		}
	}
	
	printf("KOSZT SCIEZKI= %d \n", odleglosc_od_wierzcholka[koniec]);
	int wierzch = koniec;
	while (wierzch != start)
	{
		cout << wierzch << " ";

		wierzch = wierzcholek_poprzedzajacy[wierzch];
	}
	cout << wierzch << endl;
	return licznik.stop();
}

double MenuSciezka::algorytm2v2(int w1, int w2)
{
	licznik.start();
	int start = 0, koniec = 0;
	#define nieskon INT_MAX
	start = w1;
	koniec = w2;
	vector<int>odleglosc_od_wierzcholka(liczba_wierzcholkow, nieskon);
	vector<int>wierzcholek_poprzedzajacy(liczba_wierzcholkow, NULL);
	odleglosc_od_wierzcholka[start] = 0;
	typedef pair<int, int>krawedzie;//waga ,koniec
	for (int i = 1; i <= liczba_wierzcholkow - 1; i++)
	{
		for (int j = 0; j < lista_sasiedztwa.size(); j++)
		{
			int u = j;
			
			for (int k = 0; k < lista_sasiedztwa[j].size(); k++)
			{
				int v = lista_sasiedztwa[j][k].first;
				int waga = lista_sasiedztwa[j][k].second;
				if (odleglosc_od_wierzcholka[u] != nieskon && odleglosc_od_wierzcholka[u] + waga < odleglosc_od_wierzcholka[v])
				{
					odleglosc_od_wierzcholka[v] = odleglosc_od_wierzcholka[u] + waga;
					wierzcholek_poprzedzajacy[v] = u;
				}
			}
		}



	}
	
	printf("KOSZT SCIEZKI= %d \n", odleglosc_od_wierzcholka[koniec]);
	int wierzch = koniec;
	while (wierzch != start)
	{
		cout << wierzch << " ";

		wierzch = wierzcholek_poprzedzajacy[wierzch];
	}
	cout << wierzch << endl;
	return licznik.stop();
}


void MenuSciezka::menu(MenuAbstr& obj)//menu g³owne
{
	int start = 0, koniec = 0;
	while (true)
	{
		printf("MENU\n");
		printf("1.WCZYTAJ DANE Z PLIKU\n");
		printf("2.WYGENERUJ GRAF LOSOWO\n");
		printf("3.WYSWIETL GRAF\n");
		printf("4.ALGORYTM DIJKSTRY\n");
		printf("5.ALGORYTM FORDA-BELLMANA\n");
		printf("6.ZMIANA TYPU\n");

		int x;
		cin >> x;
		switch (x)
		{
		case 1:
			
			obj.wczytywanie();
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
				cout << "PODAJ WIERZCHOLEK STARTOWY: ";
				cin >> start;
				cout << endl << "PODAJ WIERZCHOLEK KONCOWY: ";
				cin >> koniec;
				cout << obj.algorytm1v1(start, koniec) << "milisekund" << endl;
				cout << obj.algorytm1v2(start, koniec) << "milisekund" << endl;
			}
			else
			{
				printf("BRAK DANYCH\n");
			}
			break;
		case 5:
			if (wsk != nullptr) {
				cout << "PODAJ WIERZCHOLEK STARTOWY: ";
				cin >> start;
				cout << endl << "PODAJ WIERZCHOLEK KONCOWY: ";
				cin >> koniec;
				cout << obj.algorytm2v1(start, koniec) << "milisekund" << endl;
				cout << obj.algorytm2v2(start, koniec) << "milisekund" << endl;
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
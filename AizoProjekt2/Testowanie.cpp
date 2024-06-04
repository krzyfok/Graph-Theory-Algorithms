#include<iostream>
#include"MenuMst.h"
#include"MenuSciezka.h"
#include"Testowanie.h"
#include <fstream>
#include <cstdlib>
#include<string>
//7 wielksosc 50 100 150 200 250 300 350 
//gestosci: 25 50 99
//powtorzyc 50
void Testowanie::testowanie()
{
	MenuMst mst;
	MenuSciezka sciezka;
	szablon_testu(mst,"MST");
	szablon_testu(sciezka, "SCIEZKA");
}
void Testowanie::szablon_testu(MenuAbstr& obj,string nazwa)
{
	string linia;
	fstream plik;
	double czas = 0;
	/////////////
	int ge = 25;
	int rozmiar = 50;//zwiekszana o 50 do 350
	plik.open("wyniki.txt", ios::out | ios::app);
	if (plik.good() == true)
	{	
		rozmiar = 50;
		plik << nazwa<<": \n";
		plik << "      gestosc: 25 \n";
		//1v1
		plik << "1v1  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{
				system("cls");
				cout << "1v1 " << k << " " << i <<" " <<ge<< endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm1v1(0, (rand()%(rozmiar-1)+1));//0 jako pocz¹tkowy wierzcholek, koncowy losowy od 1 do liczba wierzcholkow - 1

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}


		//1v2
		rozmiar = 50;
		plik << "1v2  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{

				system("cls");
				cout << "1v2 " << k << " " << i << " " << ge << endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm1v2(0, (rand() % (rozmiar - 1) + 1));//0 jako pocz¹tkowy wierzcholek

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}


		//2v1
		rozmiar = 50;
		plik << "2v1  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{

				system("cls");
				cout << "2v1 " << k << " " << i << " " << ge << endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm2v1(0, (rand() % (rozmiar - 1) + 1));//0 jako pocz¹tkowy wierzcholek

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}
		//2v2
		rozmiar = 50;
		plik << "2v2  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{

				system("cls");
				cout << "2v2 " << k << " " << i << " " << ge << endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm2v2(0, (rand() % (rozmiar - 1) + 1));//0 jako pocz¹tkowy wierzcholek

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}

		////////
		ge = 50;
		rozmiar = 50;
		
		plik << "      gestosc: 50 \n";
		//1v1
		plik << "1v1  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{

				system("cls");
				cout << "1v1 " << k << " " << i << " " << ge << endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm1v1(0, (rand() % (rozmiar - 1) + 1));//0 jako pocz¹tkowy wierzcholek

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}


		//1v2
		rozmiar = 50;
		plik << "1v2  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{
				system("cls");
				cout << "1v2 " << k << " " << i << " " << ge << endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm1v2(0, (rand() % (rozmiar - 1) + 1));//0 jako pocz¹tkowy wierzcholek

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}


		//2v1
		rozmiar = 50;
		plik << "2v1  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{
				system("cls");
				cout << "2v1 " << k << " " << i << " " << ge << endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm2v1(0, (rand() % (rozmiar - 1) + 1));//0 jako pocz¹tkowy wierzcholek

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}
		//2v2
		rozmiar = 50;
		plik << "2v2  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{
				system("cls");
				cout << "2v2 " << k << " " << i << " " << ge << endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm2v2(0, (rand() % (rozmiar - 1) + 1));//0 jako pocz¹tkowy wierzcholek

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}

		///////////////////
		ge = 99;
		rozmiar = 50;
		
		plik << "      gestosc: 99 \n";
		//1v1
		plik << "1v1  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{
				system("cls");
				cout << "1v1 " << k << " " << i << " " << ge << endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm1v1(0, (rand() % (rozmiar - 1) + 1));//0 jako pocz¹tkowy wierzcholek

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}


		//1v2
		rozmiar = 50;
		plik << "1v2  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{
				system("cls");
				cout << "1v2 " << k << " " << i << " " << ge << endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm1v2(0, (rand() % (rozmiar - 1) + 1));//0 jako pocz¹tkowy wierzcholek

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}


		//2v1
		rozmiar = 50;
		plik << "2v1  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{
				system("cls");
				cout << "2v1 " << k << " " << i << " " << ge << endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm2v1(0, (rand() % (rozmiar - 1) + 1));//0 jako pocz¹tkowy wierzcholek

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}
		//2v2
		rozmiar = 50;
		plik << "2v2  \n";
		for (int k = 0; k < 6; k++) {
			czas = 0;
			for (int i = 0; i < 50; i++)
			{
				system("cls");
				cout << "2v2 " << k << " " << i << " " << ge << endl;
				obj.wygeneruj(rozmiar, ge);

				czas = czas + obj.algorytm2v2(0, (rand() % (rozmiar - 1) + 1));//0 jako pocz¹tkowy wierzcholek

			}
			czas = czas / 50;
			plik << to_string(czas) << " milisekund\n";
			rozmiar = rozmiar + 50;
		}

		plik.close();
	}
	
}
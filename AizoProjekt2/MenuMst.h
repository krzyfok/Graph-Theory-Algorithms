#include"MenuAbstr.h"
class MenuMst : public MenuAbstr {

	void algorytm1v1() override;
	void algorytm1v2() override;
	void algorytm2v1() override;
	void algorytm2v2()override;
	void wygeneruj() override;
	void generowanie_listy() override;
	void generowanie_wag() override;
	void MakeSet(int *parent);
	int FindSet(int* parent,int x);
	void Union(int* parent, int* rank, int x, int y);
	void quick_sort_macierz(int poczatek, int koniec);
	int quick_sort_podzial_macierz(int poczatek, int koniec);
	void quick_sort_lista(int poczatek, int koniec,int **tab);
	int quick_sort_podzial_lista(int poczatek, int koniec, int **tab);
};

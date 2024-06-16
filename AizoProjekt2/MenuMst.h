#include"MenuAbstr.h"
class MenuMst : public MenuAbstr {

	double algorytm1v1(int w1,int w2) override;
	double algorytm1v2(int w1, int w2) override;
	double algorytm2v1(int w1, int w2) override;
	double algorytm2v2(int w1, int w2)override;
	void wygeneruj(int rozmiar, int gest) override;
	void generowanie_listy() override;
	void wczytywanie() override;
	void MakeSet(int *parent);
	int FindSet(int* parent,int x);
	void Union(int* parent, int* rank, int x, int y);
	void quick_sort_macierz(int poczatek, int koniec);
	int quick_sort_podzial_macierz(int poczatek, int koniec);
	void quick_sort_lista(int poczatek, int koniec,int **tab);
	int quick_sort_podzial_lista(int poczatek, int koniec, int **tab);


public:
	void menu(MenuAbstr& obj) override;

};

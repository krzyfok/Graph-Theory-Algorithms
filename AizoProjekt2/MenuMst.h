#include"MenuAbstr.h"
class MenuMst : public MenuAbstr {

	void algorytm1v1() override;
	void algorytm1v2() override;
	void algorytm2v1() override;
	void wygeneruj() override;
	void generowanie_listy() override;
	void generowanie_wag() override;
	void MakeSet(int *parent);
	int FindSet(int* parent,int x);
	void Union(int* parent, int* rank, int x, int y);
};

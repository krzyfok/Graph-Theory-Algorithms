#include"MenuAbstr.h"
class MenuSciezka : public MenuAbstr {

	double algorytm1v1(int w1, int w2) override;
	double algorytm1v2(int w1, int w2) override;
	double algorytm2v1(int w1, int w2) override;
	double algorytm2v2(int w1, int w2)override;
	void wygeneruj(int rozmiar, int gest) override;
	void wczytywanie() override;
	void generowanie_listy() override;
public:
	void menu(MenuAbstr& obj) override;
	
};
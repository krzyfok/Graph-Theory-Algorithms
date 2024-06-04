#include<iostream>
#include"Menu.h"
#include"MenuMst.h"
#include"MenuSciezka.h"
#include"Testowanie.h"
using namespace std;

void Menu::main_menu() {
	while (true)
	{
		printf("WYBIERZ PROBLEM DO ROZWIAZANIA\n");
		printf("1.MST\n");
		printf("2.NAJKROTSZA SCIEZKA W GRAFIE\n");
		printf("3.TESTOWANIE\n");
		printf("4.WYJSCIE\n");


		int x;
		cin >> x;
		switch (x)
		{
		case 1:
		{
			MenuMst menu_1;
			menu_1.menu(menu_1);
		}
			break;
		case 2:
		{
			MenuSciezka menu_2;
			menu_2.menu(menu_2);
		}
			break;
		case 3:
			Testowanie test;
			test.testowanie();
			break;
		case 4:
			exit(0);
		}

	}


}
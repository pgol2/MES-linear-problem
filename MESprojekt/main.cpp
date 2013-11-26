#include <iostream>
#include "Grid.h"
using namespace std;

int main() 
{
	int n=3;			//ilosc wezlow																//TO DO tutaj zrobic funkcje podawania wartosci i wpisywania rowaniez z pliku !
	double k=75;		// wspolczynnik k [W/mk]
	double L=7.5;		//dlugosc preta
	double S=1;			//pole przekroju preta
	double alfa=10;		//wspolczynnik konwekcji [W/m^2k]
	double tOut=40;		//temperatura zewnetrzna
	double q=-150;		//strumien ciepla


	Grid *MES;

	//(int n_preta, double k_preta, double L_preta, double S_preta, double alfa_preta, double tOut_preta, double q_preta )
	MES = new Grid(n,k,L,S,alfa, tOut,q);
	MES->insert_to_H();

	cout << "macierz globalna H:\n";
	MES->print_H();

	cout << endl;
	cout << endl;

	cout << "macierz globalna P:\n";
	MES->insert_to_P();
	MES->print_P();

	MES->matrixInverse();
	MES->print_invertedH();
	cout << endl;
	MES->count_result();
	MES->print_result();

	system("pause");
	return 0;
}
#include <iostream>
#include "Grid.h"
using namespace std;


int main() 
{
	Grid *MES;
	MES =  new Grid(3,		//ilosc wezlow		
					75,		// wspolczynnik k [W/mk]
					7.5,	//dlugosc preta
					1,		//pole przekroju preta
					10,		//wspolczynnik konwekcji [W/m^2k]
					40,		//temperatura zewnetrzna
					-150);	//strumien ciepla
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
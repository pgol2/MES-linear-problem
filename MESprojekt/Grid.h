#pragma once
//////////////////////////////////////////////////////////////////////////
// Grid - siatka MES skladajaca sie z Itemow - czyli 2 wezlow
// tu bedzie najwiecej kodu..
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Item.h"
#include <iomanip>
#include <cmath>
using namespace std;


class Grid
{
private: 
	int n;				//ilosc wezlow
	double k;			// wspolczynnik k - przewodzenia ciepla
	double L;			//dlugosc preta
	double S;			//pole przekroju preta
	double alfa;		//wspolczynnik konwekcji 
	double tOut;		//temperatura zewnetrzna
	double q;			//strumien ciepla
	bool inverted;		//czy macierz zostala poprawnie odwrocona

	//gloabalne tablice H P i T do ukladu rownan
	double **tab_H;
	double *tab_P;
	double *tab_T;

	//tablica grupujaca Elementy i wezly
	Item **tabItems;
	Node **tabNodes;

	//tablica H po odwroceniu i wostateczny wynik
	double **inverted_H;
	double **result;
	bool ludist(int n, double ** A);
	bool lusolve(int k, int n, double ** A, double ** X);
	
public:
	
	Grid(void);
	Grid(int n_preta, double k_preta, double L_preta, double S_preta, double alfa_preta, double tOut_preta, double q_preta );
	~Grid(void);

	void insert_to_H();
	void print_H();

	void insert_to_P();
	void print_P();

	
	void matrixInverse();
	void print_invertedH();
	void count_result();
	void print_result();
};


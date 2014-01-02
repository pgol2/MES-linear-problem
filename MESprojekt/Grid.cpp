#include "Grid.h"


Grid::Grid(void)
{
}
Grid::Grid(int n_preta, double k_preta, double L_preta, double S_preta, double alfa_preta, double tOut_preta, double q_preta ) {
	n = n_preta;
	k = k_preta;
	L = L_preta;
	S = S_preta;
	alfa = alfa_preta;
	tOut = tOut_preta;
	q = q_preta;

	//stworzenie globalnej tablicy P i T, wyzerowanie 
	tab_P = new double [n];
	tab_T = new double [n];
	for(int i=0; i<n; i++){
		tab_P[i] = 0;
		tab_T[i] = 0;
	}


	//stworzenie globalnej tablicy H i wyzerowanie 
	tab_H= new double* [n];
	for(int i=0; i<n; i++)
		tab_H[i] = new double[n];

	for(int i=0; i<n; i++) 
		for(int j=0; j<n; j++) 
			tab_H[i][j] = 0;

	
	//tworzymy tablice naszych wezlow 
	//potem na podstawie wezlow stworzymy elementy
	//kazda kolejna para elemetow to nowy wezel
	//dzieki elementom zbudujemy uklad
	tabNodes = new Node* [n];
	double dist = 0;			//odleglosc od poczatku ukladu 
	for(int i=0; i<n ; i++) {
		if( i == 0)
			tabNodes[i] = new Node(dist,0,1);
		else if (i == n - 1)
			tabNodes[i] = new Node(dist,0,2);
		else
			tabNodes[i] = new Node(dist,0,0);
		dist += L/(n-1);
	}

	tabItems = new Item* [n];
	for(int i=0; i<n-1; i++){
		tabItems[i] = new Item(tabNodes[i], tabNodes[i+1]);
		tabItems[i]->create_H_P(S,k,q,alfa,tOut);
	}
	
}
Grid::~Grid(void)
{
}
void Grid::insert_to_H() {
	//wypelniam globalna H
																										//TO DO tutaj poprawic wstawienie do tej macierzy
	for(int i = 0; i < n-1; i++) {
		tab_H[i][i] += tabItems[i]->tab_local_h[0][0];
		tab_H[i][i+1] += tabItems[i]->tab_local_h[0][1];
		tab_H[i+1][i] += tabItems[i]->tab_local_h[1][0];
		tab_H[i+1][i+1] += tabItems[i]->tab_local_h[1][1];
	}
	tab_H[n-1][n-1] = tab_H[n-1][n-1] + alfa * S;
}

void Grid::print_H() {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++)
			cout  << tab_H[i][j] << "\t";
		cout << endl;
	}
	cout << endl;
}
void Grid::insert_to_P() {
	//wypelniam globalna P
	for(int i = 0; i < n-1; i++) {
		tab_P[i] += tabItems[i]->tab_local_p[0];
		tab_P[i+1] += tabItems[i]->tab_local_p[1];
	}
}

void Grid::print_P() {
	//wypisuje tablice globalna P
	for(int i=0 ; i <n; i++)
		cout  << tab_P[i]  << " ";
	cout << endl;
}


bool Grid::ludist(int n, double ** A) {
	const double eps = 1e-12;
	int i,j,k;
	for(k = 0; k < n - 1; k++)
	{
		if(fabs(A[k][k]) < eps) return false;

		for(i = k + 1; i < n; i++)
			A[i][k] /= A[k][k];

		for(i = k + 1; i < n; i++)
			for(j = k + 1; j < n; j++)
				A[i][j] -= A[i][k] * A[k][j];
	}
	return true;
}
bool Grid::lusolve(int k, int n, double ** A, double ** X)
{
	int    i,j;
	double s;
	const double eps = 1e-12;
	for(i = 1; i < n; i++){
		s = 0;
		for(j = 0; j < i; j++) s += A[i][j] * X[j][k];
		X[i][k] -= s;
	}

	if(fabs(A[n-1][n-1]) < eps) return false;
	X[n-1][k] /= A[n-1][n-1];
	for(i = n - 2; i >= 0; i--){
		s = 0;
		for(j = i + 1; j < n; j++) s += A[i][j] * X[j][k];
		if(fabs(A[i][i]) < eps) return false;
		X[i][k] = (X[i][k] - s) / A[i][i];
	}
	return true;
}

void Grid::matrixInverse() {

	bool inverted;
	inverted_H = new double * [n];
	for(int i=0; i<n; i++) {
		inverted_H[i] = new double[n];
	}

	if(ludist(n,tab_H)) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++)
				inverted_H[i][j] = 0;
			inverted_H[i][i] = 1;
		}

		inverted = true;
		for(int i=0; i<n; i++)
			if(!lusolve(i,n,tab_H,inverted_H)) {
				inverted = false;
				break;
			}
	}
	else inverted = false;
}
void Grid::print_invertedH() {
	if(inverted) {
		cout << endl;
		cout << "odwrocona macierz H\n";
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++)
				cout << inverted_H[i][j] << "\t";
			cout << endl;
		}
	}
	else {
		cout << "odwracanie nie powiod³o sie\n";
	}
}
void Grid::count_result() {
	// teraz musze pomnozyc odwrocona macierz globalna H
	// przez wektor P
	// kolejnosc w monozeniu macierzy ma znaczenie !
	
	//double **inverted_H; o rozmiare nxn
	//double *tab_P; o rozmiarze nx1
	//double **result

	double **tmp_P = new double* [n];
	for(int i =0; i<n; i++) {
		tmp_P[i] = new double [1];
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<1; j++) {
			tmp_P[i][j] = tab_P[i];
		}
	}


	result = new double * [n];
	for(int i=0; i<n; i++)
		result[i] = new double[1];




	int i,j,k;
	int s = 0;
	for(i=0; i<n; i++) {
		for(j=0; j<1; j++) {
			s = 0;
			for(k =0; k<n; k++)
				s += inverted_H[i][k] * tmp_P[k][j];
			result[i][j] = s;
		}
	}
	for(int i=0; i<n; i++)
		delete [] tmp_P[i] ;
	delete tmp_P;
	
}


void Grid::print_result() {
	cout <<endl << "wynik: \n";
	for(int i=0; i<n; i++) {
		for(int j=0; j<1; j++)
			cout << result[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}
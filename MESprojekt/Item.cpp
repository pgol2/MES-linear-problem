#include "Item.h"

Item::Item(void)
{
}
Item::Item(Node *&FirstNode, Node *&SecondNode) {

	First = FirstNode;
	Second = SecondNode;

	for(int i=0; i<2; i++) {		//zeruje lokalne tablice H i P
		tab_local_p[i] = 0;
		for(int j=0; j<2; j++) {
			tab_local_h[i][j] = 0;
		}
	}

	for(int i=0; i<2; i++) {
		tab_local_p[i] = 0;
	}

	//okreslamy dlugosc elemetnu naszej siatki MES
	l = Second->getX() - First->getX();

}

Item::~Item(void)
{
}


void Item::create_H_P(double S, double k, double q, double alfa, double tOut) {
	double C = S*k/l;

	//tworze macierz H							 //C1	-C1
	tab_local_h[0][0] = C;						//-C1	 C1
	tab_local_h[0][1] = -C;
	tab_local_h[1][0] = -C;
	tab_local_h[1][1] = C;

	//brzegowe
	tab_local_p[0] = (First->getBc() == 1) ? -q * S : 0;												//TO DO - tuaj wprowadzanie tych warunkow zrobic tak zeby bylo to niezalezne od kolejnosci
	tab_local_p[1] = (Second->getBc() == 2) ? alfa * S * tOut : 0;
}
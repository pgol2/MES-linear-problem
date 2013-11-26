#pragma once
#include "Node.h"
//////////////////////////////////////////////////////////////////////////
// Item - Pojedynczy element, skladajacy sie z dwoch puntkow
//////////////////////////////////////////////////////////////////////////
class Item
{
private:
	double l;					// dlugosc naszego elementu

	Node *First;
	Node *Second;



public:
	double tab_local_h[2][2];	// tablica lokalnych wartosci C
	double tab_local_p[2];		//nasz wektor obciazen - warunki brzegowe
	Item(void);
	Item(Node *&First, Node *&Second);
	~Item(void);

	double getL(void) {return l;}
	void create_H_P(double S, double k, double q, double alfa, double tOut);
};


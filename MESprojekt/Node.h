#pragma once
//////////////////////////////////////////////////////////////////////////
// Node - jest to pojedynczy punkt naszej siatki
//////////////////////////////////////////////////////////////////////////
class Node
{
private:
	double x;		//odleglosc miedzy wezlami
	double t;		//temperatura w danym wezle
	int bc;			//okreslnie warunkow brzegowych
					//0 - brak
					//1 - strumien (-qS)
					//2-  konwekcja (alfa*S*tOut)
public:
	Node(void);
	Node(double l, double NodeTemp, int NodeBc);
	//metody dostepowe
	double getX() {return x;}
	void setX(double l) {l = x;}

	double getT() {return t;}
	void setT(double NodeTemp) {NodeTemp = t;}

	int getBc() {return bc;}
	void setBc( int NodeBc) {NodeBc=bc;}

	~Node(void);
};


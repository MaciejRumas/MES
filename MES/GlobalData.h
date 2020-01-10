#pragma once

struct GlobalData
{
	double H;		// wysokoœæ
	double W;		// szerokoœæ
	int nH;			// iloœæ wêz³ów w pionie
	int nW;			// iloœæ wêz³ów w poziomie
	int nE;			// liczba elementów
	int nN;         // liczba wêz³ów

	double alfa;
	double c;
	double t_am;
	double t_in;
	double d;
	
	GlobalData(double H, double W, int nH, int nW, double alfa, double c, double t_am, double t_in, double d) {

		this->H = H;
		this->W = W;
		this->nH = nH;
		this->nW = nW;
		this->alfa = alfa;
		this->c = c;
		this->t_am = t_am;
		this->t_in = t_in;
		this->d = d;

		nE = (nH - 1) * (nW - 1);
		nN = nH * nW;
	}

};


	
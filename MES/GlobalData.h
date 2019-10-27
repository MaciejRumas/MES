#pragma once

struct GlobalData
{
	double H;		// wysokoœæ
	double W;		// szerokoœæ
	int nH;			// iloœæ wêz³ów w pionie
	int nW;			// iloœæ wêz³ów w poziomie
	int nE;			// liczba elementów
	int nN;			// liczba wêz³ów

	
	GlobalData(double H, double W, int nH, int nW) {

		this->H = H;
		this->W = W;
		this->nH = nH;
		this->nW = nW;

		nE = (nH - 1) * (nW - 1);
		nN = nH * nW;
	}

};


	
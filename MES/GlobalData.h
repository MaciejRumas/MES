#pragma once

struct GlobalData
{
	double H;		// wysoko��
	double W;		// szeroko��
	int nH;			// ilo�� w�z��w w pionie
	int nW;			// ilo�� w�z��w w poziomie
	int nE;			// liczba element�w
	int nN;			// liczba w�z��w

	
	GlobalData(double H, double W, int nH, int nW) {

		this->H = H;
		this->W = W;
		this->nH = nH;
		this->nW = nW;

		nE = (nH - 1) * (nW - 1);
		nN = nH * nW;
	}

};


	
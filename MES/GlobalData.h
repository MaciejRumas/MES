#pragma once

struct GlobalData
{
	double H;		// wysoko��
	double W;		// szeroko��
	int nH;			// ilo�� w�z��w w pionie
	int nW;			// ilo�� w�z��w w poziomie
	int nE;			// liczba element�w
	int nN;         // liczba w�z��w

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


	
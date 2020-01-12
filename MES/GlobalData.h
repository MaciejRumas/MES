#pragma once

struct GlobalData
{
	double H;			// height
	double W;			// width
	int nH;				// nodes vertical
	int nW;				// nodes horizontal
	int nE;				// elements
	int nN;				// nodes

	double alfa;		//convection
	double capacity;	//specific heat capacity
	double conductivity;//conductivity
	double t_am;		//ambient temp
	double t_in;		//initial temp
	double d;			//density
	
	GlobalData(double H, double W, int nH, int nW, double alfa, double capacity, double conductivity, double t_am, double t_in, double d) {

		this->H = H;
		this->W = W;
		this->nH = nH;
		this->nW = nW;
		this->alfa = alfa;
		this->capacity = capacity;
		this->conductivity = conductivity;
		this->t_am = t_am;
		this->t_in = t_in;
		this->d = d;
		this->nE = (nH - 1) * (nW - 1);
		this->nN = nH * nW;
	}

};


	
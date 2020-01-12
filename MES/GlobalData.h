#pragma once

#include<fstream>
#include<sstream>
using namespace std;

struct GlobalData
{
	double H;			// height
	double W;			// width
	int nH;				// nodes vertical
	int nW;				// nodes horizontal
	int nE;				// elements
	int nN;				// nodes

	double time;
	double step_time;
	double alfa;		//convection
	double capacity;	//specific heat capacity
	double conductivity;//conductivity
	double t_am;		//ambient temp
	double t_in;		//initial temp
	double d;			//density
	
	GlobalData(double H, double W, int nH, int nW, double alfa, double capacity, double conductivity, double t_am, double t_in, double d, double time, double step_time) {

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
		this->time = time;
		this->step_time = step_time;
		this->nE = (nH - 1) * (nW - 1);
		this->nN = nH * nW;
	}

	GlobalData(string fileName) {

		fstream file;

		file.open(fileName, ios::in);
		if (file.good()) {
			while (!file.eof()) {
				string line;
				istringstream s;
				getline(file, line);
				s.str(line);
				s >> this->t_in;
				getline(file, line);
				s.str(line);
				s >> this->time;
				getline(file, line);
				s.str(line);
				s >> this->step_time;
				getline(file, line);
				s.str(line);
				s >> this->t_am;
				getline(file, line);
				s.str(line);
				s >> this->alfa;
				getline(file, line);
				s.str(line);
				s >> this->H;
				getline(file, line);
				s.str(line);
				s >> this->W;
				getline(file, line);
				s.str(line);
				s >> this->nH;
				getline(file, line);
				s.str(line);
				s >> this->nW;
				getline(file, line);
				s.str(line);
				s >> this->capacity;
				getline(file, line);
				s.str(line);
				s >> this->conductivity;
				getline(file, line);
				s.str(line);
				s >> this->d;
				this->nE = (nH - 1) * (nW - 1);
				this->nN = nH * nW;
			}
			file.close();
		}
	}
};


	
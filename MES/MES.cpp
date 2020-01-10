#include <iostream>
#include <cmath>
#include "GlobalData.h"
#include "Grid.h"
#include "Point.h"
#include "UniversalElement.h"

using namespace std;

int main()
{

	double height = 0.1; // [m]
	double width = 0.1;	 // [m]
	int nH = 4;
	int nW = 4;
	double alfa = 300;
	double c = 25;
	double t_am = 1200;
	double t_in = 100;
	double d = 7800;

	GlobalData globalData(height, width, nH, nW, alfa, c, t_am, t_in, d);
	Grid* grid = new Grid(globalData);

	grid->printGrid();

	cout << endl;

	grid->setMatrixes();
	grid->agregate();

	cout << " Matrix H" << endl;
	double** H = grid->CG;
	for (int i = 0; i < nH * nW; i++) {
		for (int j = 0; j < nH * nW; j++) {
			cout << H[i][j] << " ";
		}
		cout << endl;
	}

	

	delete grid;


	/*
	double height = 1.5; // [m]
	double width = 0.5;	 // [m]
	int nH = 6;
	int nW = 4;

	GlobalData globalData(height, width, nH, nW);
	Grid* grid = new Grid(globalData);

	//grid->printGrid();
	//std::cout << std::endl;
	grid->getInfo(15);

	
	

	UniversalElement element;
	element.printTabEta();
	element.printTabKsi();
	element.printTabN();

	Node* selectedNodes = grid->getElementNodes(15);
	cout << element.detJ(selectedNodes, -1.0 / sqrt(3), -1.0 / sqrt(3)) << endl;

	double** jacobian = element.jacobian(selectedNodes, -1.0 / sqrt(3), -1.0 / sqrt(3));

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << jacobian[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "H w 1 pkc" << endl;

	double** h = element.HL(selectedNodes);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << h[i][j] << "\t";
		}
		cout << endl;
	}

	for (int i = 0; i < 4; i++) {
		delete[] h[i];
	}
	delete h;

	for (int i = 0; i < 2; i++) {
		delete[] jacobian[i];
	}
	delete jacobian;
	
	delete selectedNodes;
	delete grid;
	*/

	system("pause");
	return 0;
}



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
	double** H = grid->HG;
	for (int i = 0; i < nH * nW; i++) {
		for (int j = 0; j < nH * nW; j++) {
			cout << H[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < nH * nW; i++) {
		delete[] H[i];
	}
	delete H;

	delete grid;

	system("pause");
	return 0;
}



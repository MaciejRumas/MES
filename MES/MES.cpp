#include <iostream>
#include <cmath>
#include "GlobalData.h"
#include "Grid.h"
#include "Point.h"
#include "UniversalElement.h"

using namespace std;

int main()
{
	
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

	Point* points = grid->getElementNodes(15);
	cout << element.detJ(points, -1.0 / sqrt(3), -1.0 / sqrt(3)) << endl;

	double** jacobian = element.jacobian(points, -1.0 / sqrt(3), -1.0 / sqrt(3));

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << jacobian[i][j] << "\t";
		}
		cout << endl;
	}


	for (int i = 0; i < 2; i++) {
		delete[] jacobian[i];
	}
	delete jacobian;
	
	delete points;
	delete grid;

	system("pause");
	return 0;
}



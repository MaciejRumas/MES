#include <iostream>
#include "GlobalData.h"
#include "Grid.h"

using namespace std;

int main()
{
	double height = 1.5; // [m]
	double width = 0.5;	 // [m]
	int nH = 6;
	int nW = 4;

	GlobalData globalData(height, width, nH, nW);
	Grid* grid = new Grid(globalData);

	grid->printGrid();
	std::cout << std::endl;
	grid->getInfo(15);

	delete grid;

	system("pause");
	return 0;
}


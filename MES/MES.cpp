#include <iostream>
#include <cmath>
#include "GlobalData.h"
#include "Grid.h"
#include "Point.h"
#include "UniversalElement.h"

using namespace std;

int main()
{
	GlobalData globalData("mes.txt");
	Grid* grid = new Grid(globalData);

	
	grid->setMatrixes();
	grid->agregate();

	std::cout << "Time[s]" << "\t" << "MinTemps[s]" << "\t" << "MaxTemps[s]" << std::endl;
	for (int i = 0; i <= globalData.time; i += globalData.step_time) {
		std::cout << i << "\t";
		grid->printMinMaxTemp();
		grid->nextStep();
	}

	delete grid;


	system("pause");
	return 0;
}



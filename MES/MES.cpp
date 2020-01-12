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

	for (int i = 0; i <= globalData.time; i += globalData.step_time) {
		cout << "Time[s]" << "\t" << "MinTemps[C]" << "\t" << "MaxTemps[C]" << endl;
		cout << i << "\t";
		grid->printMinMaxTemp();
		cout << endl;
		grid->printTempMatrix();
		cout << endl;
		grid->nextStep();
	}

	delete grid;


	system("pause");
	return 0;
}



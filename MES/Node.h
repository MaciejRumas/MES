#pragma once
#include<iomanip>

struct Node {

	double x;
	double y;
	double t;		// temp
	bool BC;		// binary condition

	 void setBC(double H, double W) {
		if (x == 0 || x == W || y == 0 || y == H)
			BC = true;
		else
			BC = false;
	 }

	 void setX(double x) {
		 this->x = x;
	 }

	 void setY(double y) {
		 this->y = y;
	 }

	 void printNode(int i) {
		 std::cout << std::setprecision(2) << "nodes[" << i + 1 << "] - x = " << x << ", y = " << y << ", BC = " << BC << std::endl;
	 }

};
#pragma once

#include "Node.h"
#include "Element.h"
#include "GlobalData.h"

struct Grid {

	Node* nodes;
	Element* elements;

	double height;
	double width;

	int nH;
	int nW;

	int elementAmount;
	int nodeAmount;



	Grid(GlobalData globalData) {

		this->height = globalData.H;
		this->width = globalData.W;

		this->nH = globalData.nH;
		this->nW = globalData.nW;

		this->elementAmount = globalData.nE;
		this->nodeAmount = globalData.nN;

		this->elements = new Element[elementAmount];
		this->nodes = new Node[nodeAmount];

			// Set NODES

		double deltaX = width / ((double)nW - 1.0);
		double deltaY = height / ((double)nH - 1.0);

		int n = 0;
			for (int i = 1; i <= nW; i++) {
				for (int j = 1; j <= nH; j++) {
					nodes[n].setX((double)(i - 1) * deltaX);
					nodes[n].setY((double)(j - 1) * deltaY);
					nodes[n].setBC(height, width);
					n++;
				}
			}

			// Set ELEMENTS

			int e = 1;
			for (int i = 0; i < elementAmount; i++) {
				elements[i].setID(e, nH);
				e++;
				if (e % nH == 0)
					e++;
			}
		

	}

	~Grid() {
		delete nodes;
		delete elements;
	}

	void printGrid() {
		for (int i = 0; i < nodeAmount; i++) {
			nodes[i].printNode(i);
		}

		for (int i = 0; i < elementAmount; i++) {
			elements[i].printElement(i);
		}

	}

	void getInfo(int n) {
		if (n > elementAmount) {
			std::cout << "There's no such element" << std::endl;
			return;
		}

		//elements[n - 1].printElement(n - 1);
		int ID1 = elements[n - 1].ID[0];
		int ID2 = elements[n - 1].ID[1];
		int ID3 = elements[n - 1].ID[2];
		int ID4 = elements[n - 1].ID[3];

		std::cout << "ID1 = " << ID1 << ", x = " << nodes[ID1 - 1].x << ", y = " << nodes[ID1 - 1].y << std::endl;
		std::cout << "ID2 = " << ID2 << ", x = " << nodes[ID2 - 1].x << ", y = " << nodes[ID2 - 1].y << std::endl;
		std::cout << "ID3 = " << ID3 << ", x = " << nodes[ID3 - 1].x << ", y = " << nodes[ID3 - 1].y << std::endl;
		std::cout << "ID4 = " << ID4 << ", x = " << nodes[ID4 - 1].x << ", y = " << nodes[ID4 - 1].y << std::endl;
	}

	

};
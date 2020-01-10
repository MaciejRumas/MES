#pragma once

#include "Node.h"
#include "Element.h"
#include "GlobalData.h"
#include "Point.h"
#include "UniversalElement.h"

struct Grid {

	Node* nodes;
	Element* elements;

	double* PG;
	double** CG;
	double** HG;

	double height;
	double width;

	int nH;
	int nW;

	int elementAmount;
	int nodeAmount;

	double alfa;
	double c;
	double t_am;
	double t_in;
	double d;

	UniversalElement* universalElement;

	Grid(GlobalData globalData) {

		this->universalElement = new UniversalElement();
		
		this->height = globalData.H;
		this->width = globalData.W;

		this->nH = globalData.nH;
		this->nW = globalData.nW;

		this->elementAmount = globalData.nE;
		this->nodeAmount = globalData.nN;

		this->alfa = globalData.alfa;
		this->c = globalData.c;
		this->t_am = globalData.t_am;
		this->t_in = globalData.t_in;
		this->d = globalData.d;

		this->elements = new Element[elementAmount];
		this->nodes = new Node[nodeAmount];

		this->HG = new double* [nodeAmount];
		for (int i = 0; i < nodeAmount; i++) {
			this->HG[i] = new double[nodeAmount];
		}

		this->CG = new double* [nodeAmount];
		for (int i = 0; i < nodeAmount; i++) {
			this->CG[i] = new double[nodeAmount];
		}

		this->PG = new double[nodeAmount];

		//set values to 0
		for (int i = 0; i < nodeAmount; i++) {
			PG[i] = 0;
			for (int j = 0; j < nodeAmount; j++) {
				HG[i][j] = 0;
				CG[i][j] = 0;
			}
		}

			// Set NODES

		double deltaX = width / ((double)nW - 1.0);
		double deltaY = height / ((double)nH - 1.0);

		int n = 0;
			for (int i = 1; i <= nW; i++) {
				for (int j = 1; j <= nH; j++) {
					nodes[n].setX((double)(i - 1) * deltaX);
					nodes[n].setY((double)(j - 1) * deltaY);
					nodes[n].setBC(height, width);
					nodes[n].t = t_in;
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

		for (int i = 0; i < nodeAmount; i++) {
			delete[] HG[i];
			delete[] CG[i];
		}
		delete HG;
		delete CG;
		delete PG;
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

	Node* getElementNodes(int n) {
		int ID1 = elements[n - 1].ID[0];
		int ID2 = elements[n - 1].ID[1];
		int ID3 = elements[n - 1].ID[2];
		int ID4 = elements[n - 1].ID[3];

		Node* selectedNodes = new Node[4];

		selectedNodes[0] = nodes[ID1 - 1];
		selectedNodes[1] = nodes[ID2 - 1];
		selectedNodes[2] = nodes[ID3 - 1];
		selectedNodes[3] = nodes[ID4 - 1];

		return selectedNodes;
	}
	
	void setMatrixes(){
		for(int i = 0;i < elementAmount;i++) {
			Node* nodes = getElementNodes(i + 1);
			elements[i].HL = universalElement->H(nodes, alfa);
			elements[i].CL = universalElement->C(nodes, c * d);
			elements[i].PL = universalElement->P(nodes, alfa, t_am);
		}
		//delete nodes;
	}
	

	void agregate(){
		for(int i=0;i<elementAmount;i++) {
			int ID[4];
			for(int j = 0;j < 4;j++) {
				ID[j] = elements[i].ID[j];
			}
	
			for(int j=0;j<4;j++) {
				PG[ID[j] - 1] += elements[i].PL[j];
				for(int k = 0;k < 4;k++) {
					HG[ID[j] - 1][ID[k] - 1] += elements[i].HL[j][k];
					CG[ID[j] - 1][ID[k] - 1] += elements[i].CL[j][k];
				}
			}
		}
	}

};
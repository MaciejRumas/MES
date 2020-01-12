#pragma once
#include<cmath>
#include<iostream>
#include"Point.h"

struct UniversalElement {

	Point points[4];
	double tabKsi[4][4];
	double tabEta[4][4];
	double tabN[4][4];

	UniversalElement() {
		Point pkt1(-1.0 / sqrt(3), -1.0 / sqrt(3));
		Point pkt2(1.0 / sqrt(3), -1.0 / sqrt(3));
		Point pkt3(1.0 / sqrt(3), 1.0 / sqrt(3));
		Point pkt4(-1.0 / sqrt(3), 1.0 / sqrt(3));

		points[0] = pkt1;
		points[1] = pkt2;
		points[2] = pkt3;
		points[3] = pkt4;

		fillTabEta();
		fillTabKsi();
		fillTabN();
	}

	void fillTabKsi() {
		for (int i = 0; i < 4; i++) {
			tabKsi[i][0] = dN1dKsi(points[i].eta);
			tabKsi[i][1] = dN2dKsi(points[i].eta);
			tabKsi[i][2] = dN3dKsi(points[i].eta);
			tabKsi[i][3] = dN4dKsi(points[i].eta);
		}
	}

	void fillTabEta() {
		for (int i = 0; i < 4; i++) {
			tabEta[i][0] = dN1dEta(points[i].ksi);
			tabEta[i][1] = dN2dEta(points[i].ksi);
			tabEta[i][2] = dN3dEta(points[i].ksi);
			tabEta[i][3] = dN4dEta(points[i].ksi);
		}
	}

	void fillTabN() {
		for (int i = 0; i < 4; i++) {
			tabN[i][0] = N1(points[i]);
			tabN[i][1] = N2(points[i]);
			tabN[i][2] = N3(points[i]);
			tabN[i][3] = N4(points[i]);
		}
	}

	void printTabKsi() {
		std::cout << "Ksi" << std::endl;
		printTab(tabKsi);
	}

	void printTabEta() {
		std::cout << "Eta" << std::endl;
		printTab(tabEta);
	}

	void printTabN() {
		std::cout << "tabN" << std::endl;
		printTab(tabN);
	}

	void printTab(double tab[4][4]) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << tab[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}

	double detJ(Node* nodes, double ksi, double eta) {
		return dXdKsi(nodes, ksi, eta) * dYdEta(nodes, ksi, eta) - dYdKsi(nodes, ksi, eta) * dXdEta(nodes, ksi, eta);
	}

	double detJ(Node* nodes, int intergrationPoint) {
		Point p = points[intergrationPoint - 1];
		return dXdKsi(nodes, p.ksi, p.eta) * dYdEta(nodes, p.ksi, p.eta) - dYdKsi(nodes, p.ksi, p.eta) * dXdEta(nodes, p.ksi, p.eta);
	}

	double** jacobian(Node* nodes, double ksi, double eta) {
		double** jacob = new double*[2];
		jacob[0] = new double[2];
		jacob[1] = new double[2];

		jacob[0][0] = dXdKsi(nodes, ksi, eta);
		jacob[1][0] = dYdKsi(nodes, ksi, eta);
		jacob[0][1] = dXdEta(nodes, ksi, eta);
		jacob[1][1] = dYdEta(nodes, ksi, eta);

		return jacob;
	}

	double dNidX(Node* nodes, int integrationPoint, int shapeFunction) {
		Point p = points[integrationPoint - 1];
		return 1.0 / detJ(nodes, integrationPoint) * ((dYdEta(nodes, p.ksi, p.eta) * tabKsi[integrationPoint - 1][shapeFunction - 1]) - (dYdKsi(nodes, p.ksi, p.eta) * tabEta[integrationPoint - 1][shapeFunction - 1]));
	}

	double dNidY(Node* nodes, int integrationPoint, int shapeFunction) {
		Point p = points[integrationPoint - 1];
		return 1.0 / detJ(nodes, integrationPoint) * ((dXdKsi(nodes, p.ksi, p.eta) * tabEta[integrationPoint - 1][shapeFunction - 1]) - (dXdEta(nodes, p.ksi, p.eta) * tabKsi[integrationPoint - 1][shapeFunction - 1]));
	}

	double** Hi(Node* nodes, int integrationPoint) {
		double** tab = new double* [4];
		for (int i = 0; i < 4; i++)
			tab[i] = new double[4];

		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				tab[i - 1][j - 1] = dNidX(nodes, integrationPoint, j) * dNidX(nodes, integrationPoint, i) + dNidY(nodes, integrationPoint, j) * dNidY(nodes, integrationPoint, i);
			}
		}
		return tab;
	}

	void H_P(Node* nodes, Element& element, double alfa, double conductivity, double temp) {
		HL(nodes, element, conductivity);
		HPbc(nodes, element, alfa, temp);
	}

	void HL(Node* nodes, Element& element, double conductivity) {
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 4; k++) {
					element.HL[i - 1][j - 1] += (dNidX(nodes, k, j) * dNidX(nodes, k, i) + dNidY(nodes, k, j) * dNidY(nodes, k, i)) * detJ(nodes, k);
				}
				element.HL[i - 1][j - 1] *= conductivity;
			}
		}
	}
	
	void HPbc(Node* nodes, Element& element, double alfa, double temp) {
		double tabH[4][4];
		double tabP[4];

		for (int i = 0; i < 4; i++) {
			tabP[i] = 0;
			for (int j = 0; j < 4; j++) {
				tabH[i][j] = 0;
			}
		}

		//down
		if (nodes[0].BC && nodes[1].BC) {
			Point p1(-1.0 / sqrt(3), -1);
			Point p2(1.0 / sqrt(3), -1);
			double tab1[4];
			tab1[0] = N1(p1);
			tab1[1] = N2(p1);
			tab1[2] = N3(p1);
			tab1[3] = N4(p1);
			double tab2[4];
			tab2[0] = N1(p2);
			tab2[1] = N2(p2);
			tab2[2] = N3(p2);
			tab2[3] = N4(p2);

			double detJ = 0.5 * (nodes[1].x - nodes[0].x);

			for (int i = 0; i < 4; i++) {
				tabP[i] += (tab1[i] + tab2[i]) * detJ;
				for (int j = 0; j < 4; j++) {
					tabH[i][j] += ((tab1[i] * tab1[j]) + (tab2[i] * tab2[j])) * detJ;
				}
			}

		}
		//right
		if (nodes[1].BC && nodes[2].BC) {
			Point p1(1, -1.0 / sqrt(3));
			Point p2(1, 1.0 / sqrt(3));
			double tab1[4];
			tab1[0] = N1(p1);
			tab1[1] = N2(p1);
			tab1[2] = N3(p1);
			tab1[3] = N4(p1);
			double tab2[4];
			tab2[0] = N1(p2);
			tab2[1] = N2(p2);
			tab2[2] = N3(p2);
			tab2[3] = N4(p2);

			double detJ = 0.5 * (nodes[2].y - nodes[1].y);

			for (int i = 0; i < 4; i++) {
				tabP[i] += (tab1[i] + tab2[i]) * detJ;
				for (int j = 0; j < 4; j++) {
					tabH[i][j] += ((tab1[i] * tab1[j]) + (tab2[i] * tab2[j])) * detJ;
				}
			}
		}
		//up
		if (nodes[2].BC && nodes[3].BC) {
			Point p1(1.0 / sqrt(3), 1);
			Point p2(-1.0 / sqrt(3), 1);
			double tab1[4];
			tab1[0] = N1(p1);
			tab1[1] = N2(p1);
			tab1[2] = N3(p1);
			tab1[3] = N4(p1);
			double tab2[4];
			tab2[0] = N1(p2);
			tab2[1] = N2(p2);
			tab2[2] = N3(p2);
			tab2[3] = N4(p2);

			double detJ = 0.5 * (nodes[2].x - nodes[3].x);

			for (int i = 0; i < 4; i++) {
				tabP[i] += (tab1[i] + tab2[i]) * detJ;
				for (int j = 0; j < 4; j++) {
					tabH[i][j] += ((tab1[i] * tab1[j]) + (tab2[i] * tab2[j])) * detJ;
				}
			}
		}
		//left
		if (nodes[3].BC && nodes[0].BC) {
			Point p1(-1, 1.0 / sqrt(3));
			Point p2(-1, -1.0 / sqrt(3));
			double tab1[4];
			tab1[0] = N1(p1);
			tab1[1] = N2(p1);
			tab1[2] = N3(p1);
			tab1[3] = N4(p1);
			double tab2[4];
			tab2[0] = N1(p2);
			tab2[1] = N2(p2);
			tab2[2] = N3(p2);
			tab2[3] = N4(p2);

			double detJ = 0.5 * (nodes[3].y - nodes[0].y);

			for (int i = 0; i < 4; i++) {
				tabP[i] += (tab1[i] + tab2[i]) * detJ;
				for (int j = 0; j < 4; j++) {
					tabH[i][j] += ((tab1[i] * tab1[j]) + (tab2[i] * tab2[j])) * detJ;
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			tabP[i] *= -(alfa * temp);
			element.PL[i] = tabP[i];
			for (int j = 0; j < 4; j++) {
				tabH[i][j] *= alfa;
				element.HL[i][j] += tabH[i][j];
			}
		}
	}

	void C(Node* nodes, Element& element, double capacity, double density) {
		double scalar = capacity * density;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 1; k <= 4; k++) {
					element.CL[i][j] +=  tabN[k - 1][i] * tabN[k - 1][j] * detJ(nodes, k);
				}
				element.CL[i][j] *= scalar;
			}
		}
	}
	

private:
	double dXdKsi(Node* nodes, double ksi, double eta) {
		return 0.25 * (eta - 1) * nodes[0].x + 0.25 * (1 - eta) * nodes[1].x + 0.25 * (1 + eta) * nodes[2].x - 0.25 * (1 + eta) * nodes[3].x;
	}
	double dXdEta(Node* nodes, double ksi, double eta) {
		return 0.25 * (ksi - 1) * nodes[0].x - 0.25 * (1 + ksi) * nodes[1].x + 0.25 * (1 + ksi) * nodes[2].x + 0.25 * (1 - ksi) * nodes[3].x;
	}
	double dYdKsi(Node* nodes, double ksi, double eta) {
		return 0.25 * (eta - 1) * nodes[0].y + 0.25 * (1 - eta) * nodes[1].y + 0.25 * (1 + eta) * nodes[2].y - 0.25 * (1 + eta) * nodes[3].y;
	}
	double dYdEta(Node* nodes, double ksi, double eta) {
		return 0.25 * (ksi - 1) * nodes[0].y - 0.25 * (1 + ksi) * nodes[1].y + 0.25 * (1 + ksi) * nodes[2].y + 0.25 * (1 - ksi) * nodes[3].y;
	}
	double dN1dKsi(double eta) {
		return -0.25 * (1.0 - eta);
	}
	double dN2dKsi(double eta) {
		return 0.25 * (1.0 - eta);
	}
	double dN3dKsi(double eta) {
		return 0.25 * (1.0 + eta);
	}
	double dN4dKsi(double eta) {
		return -0.25 * (1.0 + eta);
	}
	double dN1dEta(double ksi) {
		return -0.25 * (1.0 - ksi);
	}
	double dN2dEta(double ksi) {
		return -0.25 * (1.0 + ksi);
	}
	double dN3dEta(double ksi) {
		return 0.25 * (1.0 + ksi);
	}
	double dN4dEta(double ksi) {
		return 0.25 * (1.0 - ksi);
	}
	double N1(Point pkt) {
		return 0.25 * (1.0 - pkt.ksi) * (1.0 - pkt.eta);
	}
	double N2(Point pkt) {
		return 0.25 * (1.0 + pkt.ksi) * (1.0 - pkt.eta);
	}
	double N3(Point pkt) {
		return 0.25 * (1.0 + pkt.ksi) * (1.0 + pkt.eta);
	}
	double N4(Point pkt) {
		return 0.25 * (1.0 - pkt.ksi) * (1.0 + pkt.eta);
	}
};
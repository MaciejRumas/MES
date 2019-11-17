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
			tabKsi[0][i] = dN1dKsi(points[i].eta);
			tabKsi[1][i] = dN2dKsi(points[i].eta);
			tabKsi[2][i] = dN3dKsi(points[i].eta);
			tabKsi[3][i] = dN4dKsi(points[i].eta);
		}
	}

	void fillTabEta() {
		for (int i = 0; i < 4; i++) {
			tabEta[0][i] = dN1dEta(points[i].ksi);
			tabEta[1][i] = dN2dEta(points[i].ksi);
			tabEta[2][i] = dN3dEta(points[i].ksi);
			tabEta[3][i] = dN4dEta(points[i].ksi);
		}
	}

	void fillTabN() {
		for (int i = 0; i < 4; i++) {
			tabN[0][i] = N1(points[i]);
			tabN[1][i] = N2(points[i]);
			tabN[2][i] = N3(points[i]);
			tabN[3][i] = N4(points[i]);
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

	double detJ(Point* points, double ksi, double eta) {
		return dXdKsi(points, ksi, eta) * dYdEta(points, ksi, eta) - dYdKsi(points, ksi, eta) * dXdEta(points, ksi, eta);
	}

	double** jacobian(Point* points, double ksi, double eta) {
		double** jacob = new double*[2];
		jacob[0] = new double[2];
		jacob[1] = new double[2];

		jacob[0][0] = dXdKsi(points, ksi, eta);
		jacob[1][0] = dYdKsi(points, ksi, eta);
		jacob[0][1] = dXdEta(points, ksi, eta);
		jacob[1][1] = dYdEta(points, ksi, eta);

		return jacob;
	}

private:
	double dXdKsi(Point* points, double ksi, double eta) {
		return 0.25 * (eta - 1) * points[0].ksi + 0.25 * (1 - eta) * points[1].ksi + 0.25 * (1 + eta) * points[2].ksi - 0.25 * (1 + eta) * points[3].ksi;
	}
	double dXdEta(Point* points, double ksi, double eta) {
		return 0.25 * (ksi - 1) * points[0].ksi - 0.25 * (1 + ksi) * points[1].ksi + 0.25 * (1 + ksi) * points[2].ksi + 0.25 * (1 - ksi) * points[3].ksi;
	}
	double dYdKsi(Point* points, double ksi, double eta) {
		return 0.25 * (eta - 1) * points[0].eta + 0.25 * (1 - eta) * points[1].eta + 0.25 * (1 + eta) * points[2].eta - 0.25 * (1 + eta) * points[3].eta;
	}
	double dYdEta(Point* points, double ksi, double eta) {
		return 0.25 * (ksi - 1) * points[0].eta - 0.25 * (1 + ksi) * points[1].eta + 0.25 * (1 + ksi) * points[2].eta + 0.25 * (1 - ksi) * points[3].eta;
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
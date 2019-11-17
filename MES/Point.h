#pragma once

struct Point {

	double ksi;
	double eta;

	Point(double ksi, double eta) {
		this->ksi = ksi;
		this->eta = eta;
	}

	Point();
};
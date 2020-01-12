#pragma once
#include<iostream>
using namespace std;

struct Gauss {

	double** createUpperMatrix(double**& matrix, unsigned n) {
		for (unsigned i = 0; i < n; i++) {

			for (unsigned j = n - 1; j > i; j--) {
				if (matrix[j][i] > matrix[j - 1][i]) {	//	Pivot	//
					swap(matrix[j], matrix[j - 1]);
				}
			}

			for (unsigned j = i + 1; j < n; j++) {
				double diff = matrix[j][i] / matrix[i][i];
				for (unsigned k = 0; k < n + 1; k++) {
					matrix[j][k] -= matrix[i][k] * diff;
				}
			}
		}
		return matrix;
	}

	double* solve(double** matrix, unsigned n) {
		double w = 0;
		double* x = new double[n];

		for (signed i = n - 1; i > -1; i--) {
			w = matrix[i][n];
			for (signed j = n - 1; j >= i + 1; j--) {
				w = w - matrix[i][j] * x[j];
			}
			w = w / matrix[i][i];
			x[i] = w;
		}
		return x;
	}
	
};
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include "TDMA.h"

using namespace std;

double Crank_Nicholson(double** numerical, double dx, double dt, double time, int nodes, double r) {
	
	ofstream ofs("crank.csv");
	
	for (int n = 0; n <= (time / dt); n++) {
		numerical[0][n] = 149.0;
		numerical[nodes - 1][n] = 149.0;
	}

	for (int i = 1; i < (nodes - 1); i++) {
		numerical[i][0] = 38.0;
	}

	double* lower_diagnol;
	double* main_diagnol;
	double* upper_diagnol;
	double* b;

	lower_diagnol = new double[nodes - 2];
	main_diagnol = new double[nodes - 2];
	upper_diagnol = new double[nodes - 2];
	b = new double[nodes - 2];

	for (int k = 0; k < nodes - 2; k++) {
		lower_diagnol[k] = 0;
		main_diagnol[k] = 0;
		upper_diagnol[k] = 0;
		b[k] = 0;
	}

	for (int k = 1; k < nodes - 2; k++) {
		lower_diagnol[k] = -(r / 2);
	}

	for (int k = 0; k < nodes - 2; k++) {
		main_diagnol[k] = 1 + r;
	}

	double d = r / 2;
	double e = 1 - r;
	double f = r / 2;

	double* numerical_old;
	numerical_old = new double[nodes - 2];

	for (int n = 0; n < time / dt; n++) {
		for (int k = 0; k < nodes - 3; k++) {
			upper_diagnol[k] = -(r / 2);
		}

		for (int k = 0; k < nodes - 2; k++) {
			if (k == 0) {
				b[k] = d * numerical[k][n] + e * numerical[k + 1][n] + f * numerical[k + 2][n] + (r / 2) * 149;
			}
			else if (k == nodes - 3) {
				b[k] = d * numerical[k][n] + e * numerical[k + 1][n] + f * numerical[k + 2][n] + (r / 2) * 149;
			}
			else {
				b[k] = d * numerical[k][n] + e * numerical[k + 1][n] + f * numerical[k + 2][n];
			}
		}

		TDMA(lower_diagnol, main_diagnol, upper_diagnol, b, nodes);
		for (int i = 0; i < nodes - 2; i++) {
			numerical[i + 1][n + 1] = b[i];
		}
	}

	cout << "The solution for Crank Nocholson equation is: " << endl;
	ofs << "The solution for Crank Nocholson equation is: " << endl;
	cout << "At Time = " << time << " :" << endl;
	ofs << "At Time = " << time << " :" << endl;
	int n = time / dt;
	for (int i = 0; i < nodes; i++) {
		cout << fixed << setprecision(4) << "Node #" << i << " at x =, " << (i * dx) << " ,= " << numerical[i][n] << endl;
		ofs << fixed << setprecision(4) << "Node #" << i << " at x =, " << (i * dx) << " ,= " << numerical[i][n] << endl;
	}
	return 0;
}

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

#ifndef FILE_FOO_SEEN //To be able to use the TDMA header file twice, once in Laasonen and once in Crank_Nicholson
#define FILE_FOO_SEEN

int TDMA(double* lower_diagonal, double* main_diagonal, double* upper_diagonal, double* b, int nodes) {
	nodes = nodes - 2;
	nodes--;
	upper_diagonal[0] /= main_diagonal[0];
	b[0] /= main_diagonal[0];

	for (int i = 1; i < nodes; i++) {
		upper_diagonal[i] /= main_diagonal[i] - lower_diagonal[i] * upper_diagonal[i - 1];
		b[i] = (b[i] - lower_diagonal[i] * b[i - 1]) / (main_diagonal[i] - lower_diagonal[i] * upper_diagonal[i - 1]);
	}

	b[nodes] = (b[nodes] - lower_diagonal[nodes] * b[nodes - 1]) / (main_diagonal[nodes] - lower_diagonal[nodes] * upper_diagonal[nodes - 1]);

	for (int i = nodes; i-- > 0;) {
		b[i] -= upper_diagonal[i] * b[i + 1];
	}
	return 0;
}
#endif 
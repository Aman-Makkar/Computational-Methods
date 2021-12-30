#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

double duFort(double** numerical, double dx, double dt, double time, int nodes, double r) {

	ofstream ofs("duFort.csv");

	for (int n = 0; n <= (time / dt); n++) {
		numerical[0][n] = 149.0;   //Boundary Condition at -40 and all n (node #0)
		numerical[nodes - 1][n] = 149.0; //Boundary Condition at +40 and all n (node #100)
	}

	//Initial Conditions #1
	for (int i = 1; i < (nodes - 1); i++) {
		numerical[i][0] = 38.0; // Initial condition at n = 0
	}

	//Initial Conditions #2
	for (int i = 1; i < (nodes - 1); i++) {
		numerical[i][1] = r * numerical[i - 1][0] + (1.0 - (2.0 * r)) * numerical[i][0] + r * numerical[i + 1][0]; //Initial Conditon at n = 1
	}

	for (int n = 1; n < (time / dt); n++) {
		for (int i = 1; i < (nodes - 1); i++) {
			numerical[i][n + 1] = ((2.0 * r) / (1.0 + 2.0 * r)) * numerical[i - 1][n] + ((2.0 * r) / (1.0 + 2.0 * r)) * numerical[i + 1][n] + ((1.0 - 2.0 * r) / (1.0 + 2.0 * r)) * numerical[i][n - 1];
		}
	}
	cout << "The solution for the duFort Frankel scheme is: " << endl;
	cout << "At Time = " << time << endl;

	int n = time / dt;
	for (int i = 0; i < nodes; i++) {
		cout << fixed << setprecision(4) << "Node #" << i << " at x =, " << (i * dx) << " ,= " << numerical[i][n] << endl;
		ofs << fixed << setprecision(4) << "Node #" << i << " at x =, " << (i * dx) << " ,= " << numerical[i][n] << endl;
	}
	return 0;
}

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

double Richardson(double** numerical, double dx, double dt, double time, int nodes, double r) {

	ofstream ofs("Richardson.csv");

	for (int n = 0; n <= (time / dt); n++) {
		numerical[0][n] = 149.0;   //Boundary Condition at -40 and all n at node# 0
		numerical[nodes - 1][n] = 149.0; //Boundary Condition at +40 and all n at node# 100
	}
	//Initial Conditions #1
	for (int i = 1; i < (nodes - 1); i++) {
		numerical[i][0] = 38.0; //Initial Condition at n = 0, for all i, except node i = 0 and i = nodes
	}
	//Initial Condition #2
	for (int i = 1; i < (nodes - 1); i++) {
		numerical[i][1] = r * numerical[i - 1][0] + (1.0 - (2.0 * r)) * numerical[i][0] + r * numerical[i + 1][0]; //Initial Condition at n = 1, for all i, except node node i = 0 and i = nodes
	}
	for (int n = 1; n < (time / dt); n++) {
		for (int i = 1; i < (nodes - 1); i++) {
			numerical[i][n + 1] = 2 * r * numerical[i - 1][n] - 4 * r * numerical[i][n] + 2 * r * numerical[i + 1][n] + numerical[i][n - 1];
		}
	}
	cout << "The solution for Richardson scheme is: " << endl;
	cout << "At Time = " << time<< endl;
	int n = time / dt;
	for (int i = 0; i < nodes; i++) {
		cout << fixed << setprecision(4) << "Node #" << i << " at x =, " << (i * dx) << " = " << numerical[i][n] << endl;
		ofs << fixed << setprecision(4) << "Node #" << i << " at x =, " << (i * dx) << " = " << numerical[i][n] << endl;
	}
	return 0;
}

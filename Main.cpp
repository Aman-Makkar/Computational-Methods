#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include "Analytical.h"
#include "duFort.h"
#include "Richardson.h"
#include "Laasonen.h"
#include "Crank_Nicholson.h"
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {

	auto start = high_resolution_clock::now();

	double L = 31.0; //setting the length
	double dx = 0.05; //setting delta x
	int nodes = L / dx + 1;
	double dt; //delta t, to be entered by the user
	double time; //to be entered by the user
	double* real; //dynamic memory

	cout << "Enter a value for delta t: " << endl;
	cin >> dt;
	cout << "Enter the time for output:" << endl;
	cin >> time;

	real = new double[nodes];
	double r = (93.0 * dt) / (pow(dx, 2));

	double** numerical = new double* [nodes];
	for (int i = 0; i < nodes; i++) numerical[i] = new double[int((time / dt) + 1)];

	analytical_solution(real, dx, dt, nodes, time);

	duFort(numerical, dx, dt, time, nodes, r);

	Richardson(numerical, dx, dt, time, nodes, r);

	Laasonen(numerical, dx, dt, time, nodes, r);

	Crank_Nicholson(numerical, dx, dt, time, nodes, r);

	for (int i = 0; i < nodes; i++) delete[] numerical[i];
	delete[] numerical; //deleting the matrix set above to free up memory

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
	cout << duration.count();

	return 0;
}

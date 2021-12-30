#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

const double pi = 3.1415;

double analytical_solution(double exact[], double dx, double dt, int nodes, double time) {
	
	ofstream ofs("analytical.csv");

	double series;
	int acc = 100;

	for (int i = 0; i < nodes; i++) {
		series = 0;
		for (int m = 1; m <= acc; m++) {
			series += (exp(-93.0 * time * pow((m * pi) / 31.0, 2)) * ((1.0 - pow(-1.0, m)) / (m * pi)) * sin((m * pi * i * dx) / 31.0));
		}
		exact[i] = 149.0 - 222.0 * series;
	}
	cout << "The analytical solution is: " << endl;
	ofs << "The analytical solution is: " << endl; 
	cout << "\n"<<endl;
	cout << "At Time = " << fixed << setprecision(4) << time << " :" << endl;
	ofs << "At Time = " << fixed << setprecision(4) << time << " :" << endl;
	cout << "\n" << endl;
	cout << "--------------------" << endl;
	ofs << "--------------------" << endl;
	cout << "\n" << endl;
	for (int i = 0; i < nodes; i++) {
		cout << fixed << setprecision(4) << "Node #" << i << " at x =, " << (i * dx) << " ,= " << exact[i] << endl;
		ofs << fixed << setprecision(4) << "Node #" << i << " at x =, " << (i * dx) << " ,= " << exact[i] << endl;
	}
	return 0;
}

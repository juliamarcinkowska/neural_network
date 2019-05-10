#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <chrono>
#include <random>
#include <fstream>
#include <vector>
#include "Network.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>

#define GNUPLOT_PATH "C:\\gnuplot\\bin"

using namespace std;

void showVectorValues(vector<double> &v);
void plot(vector<double> Ox, vector<double> Ox1, vector<double> Oy, vector<double> Oy1);
void getData(string name, vector<vector<double>> &x, vector<vector<double>> &y, int lines);
vector<int> train (vector<vector<double>> &input, vector<double> &result, vector<vector<double>> &desired, Network &net, double &err);
vector<int> test (vector<vector<double>> &input, vector<double> &result, vector<vector<double>> &desired, Network &net, double &err);

#endif // HEADER_H

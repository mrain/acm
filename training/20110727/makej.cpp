#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const double pi = acos(-1.);
int step = 50000;

int main() {
	double t = 2 * pi / step;
	printf("1\n%d\n", step);
	for (int i = 0; i < step; ++ i)
		printf("%.10f %.10f\n", 100 * cos(- t * i), 100 * sin(-t * i));
	return 0;
}


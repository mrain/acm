#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;

const double pi = acos(-1.);
int A, B;
double theta;

int main() {
	while (scanf("%d%d%lf", &A, &B, &theta) == 3) {
		if (A == 0 && B == 0 && fabs(theta) < 1e-8) break;
		printf("%d\n", A - 1);
	}
	return 0;
}


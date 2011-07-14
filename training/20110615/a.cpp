#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const double pi = acos(-1.);
double d, l, times;
int revolutions;
const double k = 12 * 5280;

int main() {
	int ca = 0;
	while (cin >> d >> revolutions >> times) {
		if (!revolutions) break;
		l = pi * d * revolutions;
		printf("Trip #%d: %.2f %.2f\n", ++ ca, l / k, l / k / times * 3600);
	}
	return 0;
}


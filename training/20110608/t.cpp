#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

double a, b, c, d;

int main() {
	cin >> a >> b >> c >> d;
	cout << sqrt((a-c)*(a-c) + (b-d)*(b-d)) << endl;
	return 0;
}

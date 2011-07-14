#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int a, A, b, B, P;

bool check() {
	if (B > P) return false;
	if (A + B <= P) return true;
	if (A > b) return false;
	return true;
}

int main() {
	cin >> A >> a >> B >> b >> P;
	if (B < A) swap(B, A), swap(a, b);
	puts(check() ? "Yes" : "No");
	return 0;
}


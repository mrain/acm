#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int reg[300];
int ram[10000], m, pc, ans;

int main() {
	while (scanf("%d", ram + m) == 1) ++ m;
	while (1) {
		++ ans;
		if (ram[pc] == 100) break;
		int a = ram[pc] / 100, d = (ram[pc] % 100) / 10, n = ram[pc] % 10;
		++ pc;
		if (a == 2) {
			reg[d] = n;
		} else if (a == 3) {
			reg[d] += n;
			reg[d] %= 1000;
		} else if (a == 4) {
			reg[d] *= n;
			reg[d] %= 1000;
		} else if (a == 5) {
			reg[d] = reg[n];
		} else if (a == 6) {
			reg[d] += reg[n];
			reg[d] %= 1000;
		} else if (a == 7) {
			reg[d] *= reg[n];
			reg[d] %= 1000;
		} else if (a == 8) {
			reg[d] = ram[reg[n]];
		} else if (a == 9) {
			ram[reg[n]] = reg[d];
		} else if (a == 0) {
			if (reg[n] != 0) pc = reg[d];
		}
	}
	cout << ans << endl;
	return 0;
}

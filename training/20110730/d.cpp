#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int f[100][100];

int main() {
	memset(f, 0, sizeof(f));
	for (int i = 1; i < 20; ++ i) {
		for (int j = 1; j < 20; ++ j) {
			for (int k = 1; k < 20; ++ k) {
				if (i - k * j >= 0)
					f[i][j] |= !f[i - k * j][j];
				if (j - k * i >= 0)
					f[i][j] |= f[i][j - k * i];
			}
			cout << f[i][j];
		}
		cout << endl;
	}
	return 0;
}

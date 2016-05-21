#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

string ind[10];
int n;
string a[1000];

int check(int mask, int start) {
	int now = start;
	for (int cc = 0; cc < n; ++ cc) {
		for (int i = 0; i < 7; ++ i) {
			if ((mask & (1 << i))) {
				if (a[cc][i] != '0') return -1;
			} else {
				if (a[cc][i] != ind[now][i]) return -1;
			}
		}
		-- now;
		if (now == -1) now = 9;
	}
	return now;
}

int main() {
	ind[0] = "1111110";
	ind[1] = "0110000";
	ind[2] = "1101101";
	ind[3] = "1111001";
	ind[4] = "0110011";
	ind[5] = "1011011";
	ind[6] = "1011111";
	ind[7] = "1110000";
	ind[8] = "1111111";
	ind[9] = "1111011";

	int tests;
	cin >> tests;
	for (int cases = 1; cases <= tests; ++ cases) {
		cin >> n;
		for (int i = 0; i < n; ++ i)
			cin >> a[i];

		int conclusion = -1, cm = -1;
		for (int mask = 0; mask < (1 << 7); ++ mask) {
			if (conclusion == -2) break;
			for (int start = 0; start < 10; ++ start) {
				int res = check(mask, start);
				if (res != -1) {
					if (conclusion != -1) {
						conclusion = -2;
						break;
					}
					conclusion = res;
					cm = mask;
				}
			}
		}
		//cout << conclusion << endl;
		cout << "Case #" << cases << ": ";
		if (conclusion < 0) cout << "ERROR!";
		else {
			for (int i = 0; i < 7; ++ i) {
				if ((cm & (1 << i)))
					cout << '0';
				else
					cout << ind[conclusion][i];
			}
		}
		cout << endl;
	}
    return 0;
}

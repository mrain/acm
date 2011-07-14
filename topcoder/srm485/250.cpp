#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <map>
#include <bitset>
#include <algorithm>
#include <sstream>
using namespace std;

int a[100], n;

bool check(long long p) {
	long long now = a[0];
	for (int i = 2; i < n; ++ i) {
		now += p;
		long long b = a[i];
		while (b < now) b *= 2;
		if (b != now) return false;
	}
	return true;
}

class AfraidOfEven{
	public:
		vector <int> restoreProgression(vector <int> seq) {
			n = seq.size();
			for (int i = 0; i < n; ++ i) a[i] = seq[i];
			vector <int> ans;
			/*for (int step = 0; ; ++ step, a[0] *= 2) {
				for (int p = -100000; p < 100000; ++ p) {
					if (abs((long long)p * (n - 1) + a[0]) > 2147483647) continue;
					if (check(p)) {
						int now = a[0];
						for (int i = 0; i < n; ++ i) {
							ans.push_back(now);
							now += p;
						}
						return ans;
					}
				}
			}*/
			int t = a[1];
			for (; ; a[0] *= 2) {
				for (; ; a[1] *= 2) {
					long long p = a[1] - a[0];
					if (check(p)) {
						int now = a[0];
						for (int i = 0; i < n; ++ i) {
							ans.push_back(now);
							now += p;
						}
						return ans;
					}
					if (abs((long long)a[1] * 2) > 2147483647) break;
				}
				a[1] = t;
				if (abs((long long)a[0] * 2) > 2147483647) break;
			}
		}
};

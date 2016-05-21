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

int T, n, m;
int x[1010], y[1010], w[1010], pos[1010];
bool cover[1010];
double f[1010], ans;

vector <pair<int, int> > event;

int main() {
	cin >> T;
	for (int t = 1; t <= T; ++ t) {
		cin >> n;
		for (int i = 0; i < n; ++ i) {
			cin >> x[i] >> y[i] >> w[i];
		}

		memset(cover, 0, sizeof(cover));
		for (int i = 0; i < n; ++ i) {
			if (w[i] == 0) {
				cover[i] = true;
				continue;
			}
			if (cover[i]) continue;
			for (int j = 0; j < n; ++ j) {
				if (!cover[j] && i != j) {
					if (x[i] - y[i] <= x[j] - y[j] && x[i] + y[i] >= x[j] + y[j]) {
						cover[j] = true;
						w[i] += max(w[j], 0);
					}
				}
			}
		}

		m = 0;
		for (int i = 0; i < n; ++ i) {
			if (!cover[i]) {
				x[m] = x[i];
				y[m] = y[i];
				w[m] = w[i];
				++ m;
			}
		}
		n = m;
		//cout << n << ' ' << w[0] <<endl;


		printf("Case #%d: %.2f\n", t, ans);
	}
    return 0;
}

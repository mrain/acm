#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;


const double eps = 1e-8;
int tests, n;
double V, H;
double r[110], c[110];

int main() {
	cin >> tests;
	for (int T = 1; T <= tests; ++ T) {
		cin >> n >> V >> H;
		for (int i = 0; i < n; ++ i) {
			cin >> r[i] >> c[i];
		}
		bool flag = false;
		for (int i = 0; i < n; ++ i)
			if (r[i] >= H) {
				flag = true;
				break;
			}

		/*if (!flag) {
			printf("Case #%d: IMPOSSIBLE\n", T);
			continue;
		}
		flag = false;
		for (int i = 0; i < n; ++ i)
			if (r[i] <= H) {
				flag = true;
				break;
			}
		if (!flag) {
			printf("Case #%d: IMPOSSIBLE\n", T);
			continue;
		}*/

		/*H *= V;
		for (int i = 0; i < n; ++ i)
			c[i] *= r[i];*/

		if (n == 1) {
			if (abs(c[0] - H) < eps) {
				printf("Case #%d: %.8f\n", T, V / r[0]);
			} else printf("Case #%d: IMPOSSIBLE\n", T);
		} else if (n == 2) {
			/*H *= V;
			double R1 = r[0], R2 = r[1], C1 = r[0] * c[0], C2 = r[1] * c[1];
			double x, y;
			C2 = C2 - R2 * c[0];
			H = H - V * c[0];
				


			if (abs(C2) < eps) {
				if (abs(H) < eps) {
					printf("Case #%d: %.8f\n", T, V / (r[0] + r[1]));
				} else printf("Case #%d: IMPOSSIBLE\n", T);
			} else {
				y = H / C2;
				x = (V - R2 * y) / R1;
				if (x < -eps || y < -eps) printf("Case #%d: IMPOSSIBLE\n", T);
				else printf("Case #%d: %.8f\n", T, x < y ? y : x);
			}*/


			if (abs(c[0] - H) < eps) {
				if (abs(c[1] - H) < eps)
					printf("Case #%d: %.8f\n", T, V / (r[0] + r[1]));
				else
					printf("Case #%d: %.8f\n", T, V / r[0]);
			} else if (abs(c[1] - H) < eps) {
				printf("Case #%d: %.8f\n", T, V / r[1]);
			} else if (abs(c[0] - c[1]) < eps) {
				printf("Case #%d: IMPOSSIBLE\n", T);
			} else {
				double C2 = r[1] * c[1] - r[1] * c[0];
				H = V * H - V * c[0];
				double y = H / C2;
				double x = (V - r[1] * y) / r[0];
				//cout << C2 << ' ' << H << endl;
				//cout << x << ' ' << y << endl;
				if (x < -eps || y < -eps) printf("Case #%d: IMPOSSIBLE\n", T);
				else printf("Case #%d: %.8f\n", T, x < y ? y : x);

			}
		}
	}
    return 0;
}

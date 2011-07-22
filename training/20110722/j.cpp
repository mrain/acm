#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

const double pi = acos(-1.);
const double k[3] = {2 * pi / 60, 2 * pi / 3600, 2 * pi / 43200};
double l[3], m[3];
int A, B;
char buf[300];

int parse(char *s) {
	int H = (s[0] - '0') * 10 + (s[1] - '0');
	int M = (s[3] - '0') * 10 + (s[4] - '0');
	int S = (s[6] - '0') * 10 + (s[7] - '0');
	return ((H * 60) + M) * 60 + S;
}

int main() {
	while (scanf("%lf", &l[0]) == 1 && l[0] > 0) {
		for (int i = 1; i < 3; ++ i) scanf("%lf", l + i);
		for (int i = 0; i < 3; ++ i) scanf("%lf", m + i);
		scanf("%s", buf); A = parse(buf);
		scanf("%s", buf); B = parse(buf);
		double v = 0, tmp = 0;
		for (int i = 0; i < 3; ++ i) {
			v += (l[i] / 2) * m[i] * k[i];
			tmp += m[i];
		}
		v /= tmp;
		printf("%.2f\n", v * ((double)B - A));
	}
	return 0;
}

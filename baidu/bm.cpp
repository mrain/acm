#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

#define MP make_pair
#define PB push_back
#define LB lower_bound
#define UB upper_bound

const double eps = 1e-8;
const double pi = acos(-1.0);

int bh[100000];
int main()
{
	srand(time(0));
	freopen("b.in", "w", stdout);
	for (int ca = 1; ca < 15; ca++) {
		puts("100 100");
		for (int i = 0; i < 10000; i++)
			bh[i] = i;
		random_shuffle(bh, bh + 10000);
		puts("5000");
		for (int i = 0; i < 5000; i++)
			printf("%d %d\n", bh[i] / 100, bh[i] % 100);
	}
	puts("0 0");
}

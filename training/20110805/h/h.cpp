#include <cstdio>
#include <iostream>
using namespace std;

int tests, n;
long long a[30];

int main() {
a[1]=1ll;
a[2]=9ll;
a[3]=89ll;
a[4]=89ll;
a[5]=589ll;
a[6]=3089ll;
a[7]=3089ll;
a[8]=3089ll;
a[9]=315589ll;
a[10]=315589ll;
a[11]=8128089ll;
a[12]=164378089ll;
a[13]=945628089ll;
a[14]=1922190589ll;
a[15]=11687815589ll;
a[16]=109344065589ll;
a[17]=231414378089ll;
a[18]=1452117503089ll;
a[19]=4503875315589ll;
a[20]=65539031565589ll;

	cin >> tests;
	int ca = 0;
	while (tests --) {
		cin >> n;
		cout << ++ ca << ' ' << n << ' ' << a[n] << endl;
	}
	return 0;
}


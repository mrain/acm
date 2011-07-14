#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

int n, a[2000], res;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i)
		scanf("%d", a + i);
	sort(a, a + n);
	int tmp = n;
	while (tmp) {
		if (tmp <= 2) {
			res += a[tmp - 1];
			tmp = 0;
		} else if (tmp == 3) {
			for (int i = 0; i < tmp; ++ i)
				res += a[i];
			tmp = 0;
		} else {
			if (2 * a[1] > a[tmp - 2] + a[0])
				res += (a[tmp - 2] + a[tmp - 1]) + 2 * a[0];
			else
				res += (a[1] + a[0] + a[tmp - 1] + a[1]);
			tmp -= 2;
		}
	}
	cout << res << endl;
	tmp = n;
	while (tmp) {
		if (tmp == 1) {
			cout << a[0] << endl;
			tmp = 0;
		} else if (tmp == 2) {
			cout << a[0] << ' ' << a[1] << endl;
			tmp = 0;
		} else if (tmp == 3) {
			cout << a[0] << ' ' << a[1] << endl;
			cout << a[0] << endl;
			cout << a[0] << ' ' << a[2] << endl;
			tmp = 0;
		} else {
			if (2 * a[1] > a[tmp - 2] + a[0]) {
				cout << a[0] << ' ' << a[tmp - 1] << endl;
				cout << a[0] << endl;
				tmp -= 1;
			} else {
				cout << a[0] << ' ' << a[1] << endl;
				cout << a[0] << endl;
				cout << a[tmp - 2] << ' ' << a[tmp - 1] << endl;
				cout << a[1] << endl;
				tmp -= 2;
			}
		}
	}
	return 0;
}

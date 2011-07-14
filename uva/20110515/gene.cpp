#include <cstdio>
#include <iostream>
using namespace std;

int main() {
	freopen("e.in", "w", stdout);
	int cnt = 0;
	for (int i = 1; i < 101; ++ i)
		for (int j = 1; j < 101; ++ j)
			cnt ++;
	cout << cnt << endl;
	for (int i = 1; i < 101; ++ i)
		for (int j = 1; j < 101; ++ j)
			cout << i << ' ' << j << endl;
	return 0;
}

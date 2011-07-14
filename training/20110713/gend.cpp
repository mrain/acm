#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <ctime>
using namespace std;

int main() {
	srand(time(0));
	freopen("d.in", "w", stdout);
	cout << 100 << endl;
	for (int i = 0; i < 100; ++ i)
		cout << rand() % 450 << endl;
	return 0;
}

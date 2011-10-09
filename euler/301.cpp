#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
	int cnt = 0;
	for (int i = 1; i <= (1<<30); ++ i)
		if ((i ^ (i << 1)) == i + (i << 1))
			++ cnt;
	cout << cnt << endl;
	return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

char command[1000];

int main() {
	for (int i = 1; i <= 37; ++ i) {
		printf("Test Case #%d:\n", i);
		if (i < 10) sprintf(command, "./main <0%d", i);
		else sprintf(command, "./main <%d", i);
		system(command);
		if (i < 10) sprintf(command, "cat 0%d.a", i);
		else sprintf(command, "cat %d.a", i);
		system(command);
		cout << endl;
	}
	return 0;
}

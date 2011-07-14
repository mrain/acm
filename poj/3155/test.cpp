#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

char command[1000];

int main() {
	for (int i = 1; i < 61; ++ i) {
		printf("Test Case #%d:\n", i);
		if (i < 10) sprintf(command, "./work <0%d", i);
		else sprintf(command, "./work <%d", i);
		system(command);
		if (i < 10) sprintf(command, "./analysis 0%d 0%d.res", i, i);
		else sprintf(command, "./analysis %d %d.res", i, i);
		system(command);
		if (i < 10) sprintf(command, "./analysis 0%d 0%d.a", i, i);
		else sprintf(command, "./analysis %d %d.a", i, i);
		system(command);
	}
	return 0;
}

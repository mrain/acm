#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

char buf[1000];

int main() {
	while (1) {
		gets(buf);
		int n = strlen(buf);
		for (int i = 0; i < n; ++ i) {
			if (buf[i] == 'E' && buf[i + 1] == 'O' && buf[i + 2] == 'F') {
				return 0;
			}
			if (buf[i] == 'd' && buf[i + 1] == 'd') {
				++ i;
				putchar('p');
			} else if (buf[i] == 'e' && buf[i + 1] == 'i' && (!i || buf[i - 1] != 'c')) {
				++ i;
				putchar('i'); putchar('e');
			} else if (buf[i] == 'p' && buf[i + 1] == 'i' && buf[i + 2] == 'n' && buf[i + 3] == 'k') {
				i += 3;
				printf("floyd");
			} else if (islower(buf[i]) || buf[i] == ' ')
				putchar(buf[i]);
		}
		puts("");
	}
	return 0;
}


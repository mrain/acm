#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 1000000007;
char s[1003];
int f[1003][1003], n;

int main(){
	while(scanf("%s",s) == 1) {
//		memset(f, 0, sizeof(f));
		n = strlen(s) + 1;
		for (int i = 0; i < n; ++ i)
			f[1][i] = 1;
		for (int i = 2; i <= n; ++ i) {
			if (s[i - 2] == 'D') {
				int sum = f[i - 1][n - i + 1];
				for (int j = n - i; j >= 0; -- j) {
					f[i][j] = sum;
					sum += f[i - 1][j]; sum %= mod;
				}
			} else if (s[i - 2] == 'I') {
				int sum = 0;
				for (int j = 0; j < n - i + 1; ++ j) {
					sum += f[i - 1][j]; sum %= mod;
					f[i][j] = sum;
				}
			} else {
				int sum = 0;
				for (int j = 0; j < n - i + 2; ++ j)
					sum = (sum + f[i - 1][j]) % mod;
				for (int j = 0; j < n - i + 1; ++ j)
					f[i][j] = sum;
			}
		}
		cout << f[n][0] << endl;
	}
	return 0;
}

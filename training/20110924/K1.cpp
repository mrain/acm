#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

#define maxn (1005)

int Next[maxn];
int f[maxn][maxn];
int ans;
string a, b;

void calcNext(const string& b) {
	memset(Next, -1, sizeof(Next));
	
	for (int i = 1, k = -1; i < b.length(); ++i) {
		while (k != -1 && b[k + 1] != b[i]) k = Next[k];
		if (b[k + 1] == b[i]) k++;
		Next[i] = k;
	}
}
/*
void transfer(const string& a, const string& b, int init, int v) {
	for (int i = 0, k = -1; i < a.length(); ++i) {
		//cout << i << " : ";
	
		while (k != -1 && k < b.length() && b[k + 1] != a[i] && a[i] != '?') k = Next[k];
		if (b[k + 1] == a[i] || a[i] == '?') k++;
		
		//cout << k << endl;
		
		while (k > (int)b.length() - 1) k--;
		
		if (k == (int)b.length() - 1) f[init + i] = max(f[init + i], v + 1);
	}
}
*/

void update(int i, int j, char x, int v) {
	j--;
	
	while (j != -1 && b[j + 1] != x) j = Next[j];
	if (b[j + 1] == x) j++;
	if (j + 1 == b.length()) v++;
	
	f[i + 1][j + 1] = max(f[i + 1][j + 1], v);
	ans = max(ans, v);
}

int main() {
	cin >> a >> b;
	
	calcNext(b);
/*	
	for (int i = 0; i < a.length(); ++i) {
		//cout << i << " -> " << f[i] << endl;
	
		string str = b.substr(1) + a.substr(i + 1);
		//cout << str << endl;
		transfer(str, b, i - (int)b.length() + 2, f[i]);
	}
	
	int ans = 0;
	for (int i = 0; i < a.length(); ++i) ans = max(ans, f[i]);
*/	
	memset(f, -1, sizeof(f));
	ans = f[0][0] = 0;
	
	for (int i = 0; i < a.length(); ++i) {
		char x = a[i];
		
		for (int j = 0; j <= b.length(); ++j) if (f[i][j] >= 0) {
			if (x == '?') {
				for (char k = 'a'; k <= 'z'; ++k) update(i, j, k, f[i][j]);
				for (char k = 'A'; k <= 'Z'; ++k) update(i, j, k, f[i][j]);
			}
			else update(i, j, x, f[i][j]);
		}
	}

	cout << ans << endl;

	return 0;
}

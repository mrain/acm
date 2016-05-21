#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

int tests;
string s;
int c[100][300], f[300];
int ans[10];

int main() {
	cin >> tests;
	for (int cases = 1; cases <= tests; ++ cases) {
		cin >> s;
		memset(f, 0, sizeof(f));
		memset(ans, 0, sizeof(ans));
		for (int i = 0; i < s.length(); ++ i)
			f[s[i]] ++;
		// ROUND 1
		ans[2] = f['W']; f['T'] -= ans[2]; f['W'] -= ans[2]; f['O'] -= ans[2];
		ans[0] = f['Z']; f['Z'] -= ans[0]; f['E'] -= ans[0]; f['R'] -= ans[0]; f['O'] -= ans[0]; 
		ans[6] = f['X']; f['S'] -= ans[6]; f['I'] -= ans[6]; f['X'] -= ans[6]; 
		ans[4] = f['U']; f['F'] -= ans[4]; f['O'] -= ans[4]; f['U'] -= ans[4]; f['R'] -= ans[4]; 
		// ROUND 2
		ans[1] = f['O']; f['O'] -= ans[1]; f['N'] -= ans[1]; f['E'] -= ans[1]; 
		ans[3] = f['R']; f['T'] -= ans[3]; f['H'] -= ans[3]; f['R'] -= ans[3]; f['E'] -= ans[3]; f['E'] -= ans[3]; 
		// ROUND 3
		ans[8] = f['T']; f['E'] -= ans[8]; f['I'] -= ans[8]; f['G'] -= ans[8]; f['H'] -= ans[8]; f['T'] -= ans[8]; 
		ans[5] = f['F']; f['F'] -= ans[5]; f['I'] -= ans[5]; f['V'] -= ans[5]; f['E'] -= ans[5]; 
		// ROUND 4
		ans[7] = f['S']; f['S'] -= ans[7]; f['E'] -= ans[7]; f['V'] -= ans[7]; f['E'] -= ans[7]; f['N'] -= ans[7];
		ans[9] = f['I']; f['N'] -= ans[9]; f['I'] -= ans[9]; f['N'] -= ans[9]; f['E'] -= ans[9];  

		cout << "Case #" << cases << ": ";
		for (int i = 0; i <= 9; ++ i) {
			for (int cnt = 0; cnt < ans[i]; ++ cnt)
				cout << char('0' + i);
		}
		cout << endl;
 	}
    return 0;
}

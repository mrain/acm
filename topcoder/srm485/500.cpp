#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <map>
#include <bitset>
#include <algorithm>
#include <sstream>
using namespace std;

char t[10];
int cnt[50][50][50][50];
bool B[50][50][50][50], W[50][50][50][50];
class RectangleAvoidingColoring{
	public:
		void calc(int a, int b, int c, int d) {
			bool tB = false, tW = false;
			int cc = 0;
			for (int i = 0; i < 4; ++ i) {
				if (t[i] == 'B') tB = true;
				if (t[i] == 'W') tW = true;
				if (t[i] == '?') ++ cc;
			}
			cnt[a][b][c][d] = cc;
			B[a][b][c][d] = tB;
			W[a][b][c][d] = tW;
		}
		long long count(vector <string> board) {
			int n = board.size(), m = board[0].length();
			long long ans = 0;
			string tmp;
			int totcnt = 0;
			for (int a = 0; a < n; ++ a)
				for (int b = 0; b < m; ++ b)
					for (int c = a + 1; c < n; ++ c)
						for (int d = b + 1; d < m; ++ d) {
							t[0] = board[a][b];
							t[1] = board[a][d];
							t[2] = board[c][d];
							t[3] = board[c][b];
							calc(a, b, c, d);
							totcnt += cnt[a][b][c][d];
						}
			return ans;
		}
};

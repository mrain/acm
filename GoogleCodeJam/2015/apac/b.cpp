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

string dir;
int tests;
int n;
int board[22][22];
vector <int> proc;

int main() {
	cin >> tests;
	for (int cases = 1; cases <= tests; ++ cases) {
		cin >> n >> dir;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j)
				cin >> board[i][j];

		if (dir[0] == 'l') {
			for (int i = 0; i < n; ++ i) {
			int buf = -1;
				proc.clear();
				for (int j = 0; j < n; ++ j) {
					if (board[i][j] == 0) continue;
					if (buf == -1) buf = board[i][j];
					else if (buf == board[i][j]) {
						proc.push_back(buf + buf);
						buf = -1;
					} else {
						proc.push_back(buf);
						buf = board[i][j];
					}
				}
				if (buf != -1) proc.push_back(buf);
				for (int j = 0; j < n; ++ j) {
					board[i][j] = j >= proc.size() ? 0 : proc[j];
				}
			}
		} else if (dir[0] == 'r') {
			for (int i = 0; i < n; ++ i) {
			int buf = -1;
				proc.clear();
				for (int j = n - 1; j >= 0; -- j) {
					if (board[i][j] == 0) continue;
					if (buf == -1) buf = board[i][j];
					else if (buf == board[i][j]) {
						proc.push_back(buf + buf);
						buf = -1;
					} else {
						proc.push_back(buf);
						buf = board[i][j];
					}
				}
				if (buf != -1) proc.push_back(buf);
				for (int j = 0; j < n; ++ j) {
					board[i][n - j - 1] = j >= proc.size() ? 0 : proc[j];
				}
			}
		} else if (dir[0] == 'u') {
			for (int j = 0; j < n; ++ j) {
			int buf = -1;
				proc.clear();
				for (int i = 0; i < n; ++ i) {
					if (board[i][j] == 0) continue;
					if (buf == -1) buf = board[i][j];
					else if (buf == board[i][j]) {
						proc.push_back(buf + buf);
						buf = -1;
					} else {
						proc.push_back(buf);
						buf = board[i][j];
					}
				}
				if (buf != -1) proc.push_back(buf);
				for (int i = 0; i < n; ++ i) {
					board[i][j] = i >= proc.size() ? 0 : proc[i];
				}
			}
		} else {
			for (int j = 0; j < n; ++ j) {
			int buf = -1;
				proc.clear();
				for (int i = n - 1; i >= 0; -- i) {
					if (board[i][j] == 0) continue;
					if (buf == -1) buf = board[i][j];
					else if (buf == board[i][j]) {
						proc.push_back(buf + buf);
						buf = -1;
					} else {
						proc.push_back(buf);
						buf = board[i][j];
					}
				}
				if (buf != -1) proc.push_back(buf);
				for (int i = 0; i < n; ++ i) {
					board[n - i - 1][j] = i >= proc.size() ? 0 : proc[i];
				}
			}
		}
		printf("Case #%d:\n", cases);
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j) {
				printf("%d", board[i][j]);
				if (j != n - 1) putchar(' ');
				else puts("");
			}
	}
    return 0;
}

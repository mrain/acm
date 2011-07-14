/*
 * 解法: 只要对于没行用一个单调队列维护转移即可.
*/
#include <iostream>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#define Max(a, b)			(a > b ? a : b)
using namespace std;

const int MaxN = 110, MaxM = 10010, inf = 1000000000;

int n, m, k, s[MaxN][MaxM], t[MaxN][MaxM], f[MaxN][MaxM], QHead, QTail, Queue[MaxM], Ans;

void Init()
{
	scanf("%d%d%d", &n, &m, &k);
	memset(f, 192, sizeof(f));
	memset(f[0], 0, sizeof(f[0]));
	Ans = -inf;
	memset(s, 0, sizeof(s));
	memset(t, 0, sizeof(t));
	++n;
	for (int i = 1, j, x; i <= n; ++i)
	{
		for (j = 1; j <= m; ++j)
		{
			scanf("%d", &x);
			s[i][j] = s[i][j-1]+x;
		}
		for (j = 1; j <= m; ++j)
		{
			scanf("%d", &x);
			t[i][j] = t[i][j-1]+x;
		}
	}
}

int main()
{
	Init();
	for (int i = 1, j; i <= n; ++i)
	{
		QHead = QTail = 0;
		Queue[++QTail] = 0;
		for (j = 0; j <= m; ++j)
		{
			for (; QHead < QTail && f[i-1][j]-s[i][j] >= f[i-1][Queue[QTail]]-s[i][Queue[QTail]]; --QTail);
			Queue[++QTail] = j;
			for (; QHead < QTail && t[i][j]-t[i][Queue[QHead+1]] > k; ++QHead);
			f[i][j] = Max(f[i][j], f[i-1][Queue[QHead+1]]-s[i][Queue[QHead+1]]+s[i][j]);
		}
		QHead = QTail = 0;
		Queue[++QTail] = m;
		for (j = m; j >= 0; --j)
		{
			for (; QHead < QTail && f[i-1][j]+s[i][j] >= f[i-1][Queue[QTail]]+s[i][Queue[QTail]]; --QTail);
			Queue[++QTail] = j;
			for (; QHead < QTail && t[i][Queue[QHead+1]]-t[i][j] > k; ++QHead);
			f[i][j] = Max(f[i][j], f[i-1][Queue[QHead+1]]+s[i][Queue[QHead+1]]-s[i][j]);
		}
	}
	for (int j = 0; j <= m; ++j)
		Ans = Max(Ans, f[n][j]);
	cout << Ans << endl;
	return 0;
}


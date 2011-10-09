#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (1100015)

char s[maxn];
int pos[maxn], stack[maxn], a[maxn], b[maxn];
int n;

bool ok() {
	int top = 0;
	
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'a' || s[i] == 'i') pos[i] = -1, stack[++top] = i;
		else {
			if (top == 0 || s[i] == 'e' && s[stack[top]] == 'i' || s[i] == 'o' && s[stack[top]] == 'a') return false;
			
			pos[i] = stack[top--]; a[pos[i]] = i;
		}
	}
	
	return top == 0;
}
/*
int change(int st, int ed, int last) {
	if (st > ed) return -1;

	if (last != -1 && s[ed] == 'e') {
		s[ed] = 'i', s[ed + 1] = 'o', s[ed + 2] = 'e';
		
		for (int i = ed + 3, j = last; i < j; ++i, --j) s[i] = 'a', s[j] = 'e';
		
		return last;
	}
	
	if (pos[ed] == st) {
		int t = change(st + 1, ed - 1, -1);
		
		if (t == -1) {
			if (s[st] == 'a') {
				if (s[ed + 1] == 'e') {
					s[st] = 'e';
					for (int i = st + 1, j = ed + 1; i < j; ++i, --j) s[i] = 'a', s[j] = 'e';
					
					return ed + 1;
				}
				else {
					s[st] = 'i', s[ed] = 'o';
					return ed;
				}
			}
			if (s[st] == 'i' && ed > st + 1) {
				s[ed - 2] = 'o';
				for (int i = ed - 1, j = last; i < j; ++i, --j) s[i] = 'a', s[j] = 'e';
				return last; 
			}
		}
		else return ed;
	}
	else {
		int k = ed; 
		while (k > st) {
			int x = pos[k];
			if (x == k - 1 && s[x] == 'i') {
				if (last == -1) last = k;
			} 
			else {
				int t = change(x, k, last);
				if (t < last) {
					for (int i = t + 1, j = ed; i < j; ++i, --j) s[i] = 'a', s[j] = 'e';
				
					return last; 
				}
				else return t; 
			}
		
			k = x - 1;
		}
	}
	
	return -1;
}
*/

inline void update(int& x, const int& v) {
	if (x < v) x = v;
}

int find() {
	bool flag = false; int x = -1;

	for (int i = n - 1; i >= 0; --i) {
		if (s[i] == 'e') {
			if (flag) {
				b[i] = 0; update(x, i);
				
				continue;
			}
			if (s[i + 1] == 'e') {
				b[pos[i]] = 1; update(x, pos[i]);
				
				continue;
			}
			b[pos[i]] = 2; update(x, pos[i]);
		}
		
		if (s[i] == 'o') {
			if (pos[i] < i - 1 && pos[i - 1] == i - 2 && s[i - 1] == 'o') {
				b[i - 2] = 3;  update(x, i - 2);
				
				continue;
			}
		}
		
		if (s[i] == 'i' && s[i + 1] == 'o') flag = true; 
	}
	
	return x;
}

void work() {
	gets(s);
	
	for (n = 0; s[n]; ++n) ;
	
	if (!ok()) {
		puts("INVALID"); return ;
	}
	
	int x = find();
	if (x == -1) {
		puts("ULTIMATE"); return ;
	}
	
	int t = b[x];
	switch (t) {
		case 0 : {
			s[x] = 'i', s[x + 1] = 'o', s[x + 2] = 'e';
		
			break;		
		}
		case 1 : {
			s[x] = 'e', s[a[x]] = 'a';
		
			break;		
		}
		case 2 : {
			s[x] = 'i', s[a[x]] = 'o';
		
			break;		
		}
		case 3 : {
			s[x] = 'o', s[x + 1] = 'i';
			
			break;		
		}
	}
	
	ok();
	x += 1;
//	printf("%d\n",x);
	int top = 0;
//	for (int i = x - 1; i >= 0; --i)
	for (int i = 0; i < x; ++i)  
		if ((s[i] == 'a' || s[i] == 'i') && a[i] >= x) stack[++top] = i;
	
	for (int i = x, j = n - 1 - top; i < j; ++i, --j) s[i] = 'a', s[j] = 'e';
	for (int i = top; i >= 1; -- i) s[n - i] = (s[stack[i]] == 'a' ? 'e' : 'o');
	puts(s);
}

int main() {
	int T; scanf("%d", &T); gets(s);
	
	while (T--) work();	

	return 0;
}

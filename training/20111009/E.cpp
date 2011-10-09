#include<set>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,t[1000003],an[1000003],last[1000003];
bool man[1000003];
set<int> h;
void input(int &x){
	x=0;
	char ch=' ';
	while(ch<'0'||ch>'9')ch=getchar();
	for(;ch>='0'&&ch<='9';ch=getchar())
		x=(x<<1)+(x<<3)+ch-'0';
}
int main(){
	int _;
	for(input(_);_--;){
		input(n),input(m);
		for(int i=1;i<=m;++i)input(t[i]);
		memset(man,1,sizeof(man));
		memset(last,0,sizeof(last));
		h.clear();
		for(int i=1;i<=m;++i)
			if(!t[i])
				h.insert(i);
		bool ans=1;
		for(int i=1;i<=m;++i)
			if(t[i]&&man[t[i]]){
				set<int>::iterator it=h.upper_bound(last[t[i]]);
				if(it==h.end()||*it>i){
					ans=false;
					break;
				}
				last[t[i]]=i;
				an[*it]=t[i];
				h.erase(it);
			}
		if(!ans){
			puts("NO");
			continue;
		}
		for(set<int>::iterator it=h.begin();it!=h.end();++it)
			an[*it]=0;
		puts("YES");
		for(int i=1,j=0;i<=m;++i)
			if(!t[i]){
				if(j)putchar(' ');
				++j;
				printf("%d",an[i]);
			}
		puts("");
	}
	return 0;
}

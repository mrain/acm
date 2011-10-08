#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char s[1003],t[1003];
int main(){
	scanf("%s%s",s,t);
	int l1=strlen(s);
	int l2=strlen(t);
	int cnt=0;
	for(int i=0;i<l1;++i){
		if(i+l2>l1)break;
		bool OK=1;
		for(int j=0;j<l2&&OK;++j)
			if(s[i+j]!=t[j]&&s[i+j]!='?')
				OK=0;
		if(OK)++cnt;
	}
	printf("%d\n",cnt);
	return 0;
}

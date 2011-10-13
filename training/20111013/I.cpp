#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int cnt=0;
struct list{
	bool type;//0 orgin 1 insert
	long long r,dx;
	int nt,prev;
	char s[11];
	list(){}
}a[100003];
int cur_b,cur_p;
void Move(int k){
	if(k>=a[cur_b].r-cur_p){
		k-=a[cur_b].r-cur_p;
		cur_b=a[cur_b].nt;
		cur_p=0;
		k-=a[cur_b].r-cur_p;
		Move(k);
	}
	else cur_p+=k;
}
void del(int len){
	if(len>=a[cur_b].r-cur_p){
		if(cur_p==0){
			a[a[cur_b].prev].nt=a[cur_b].nt;
			a[a[cur_b].nt].prev=a[cur_b].prev;
			cur_b=a[cur_b].nt;
		}
		else
			a[cur_b].r=cur_p;
		len-=a[cur_b].r-cur_p;
		cur_b=a[cur_b].nt;
		cur_p=0;
		del(len);
	}
	else{
		if(a[cur_b].type){
			int pp=cur_p+len+1;
			++cnt;
			a[cnt].type=1;
			a[cnt].r=a[cur_b].r-pp+1;
			a[cnt].nt=a[cur_b].nt;
			a[cnt].prev=cur_b;
			memcpy(a[cnt].s,a[cur_b].s+pp,a[cnt].r);
			a[cur_b].r=cur_p-1;
			a[cur_b].nt=cnt;
			cur_b=cnt;
			cur_p=0;
		}
		else{
			int pp=cur_p+len;
			++cnt;
			a[cnt].type=0;
			a[cnt].r=a[cur_b].r-pp;
			a[cnt].nt=a[cur_b].nt;
			a[cnt].prev=cur_b;
			a[cnt].dx=a[cur_b].dx+pp;
			cur_p=cnt;
			cur_p=0;
		}
	}
}
char tmp[11];
void insert(){
		if(a[cur_b].type){
			int pp=cur_p+1;
			++cnt;
			a[cnt].type=1;
			a[cnt].r=a[cur_b].r-pp+1;
			a[cnt].nt=a[cur_b].nt;
			a[cnt].prev=cur_b;
			memcpy(a[cnt].s,a[cur_b].s+pp,a[cnt].r);
			a[cur_b].r=cur_p-1;
			a[cur_b].nt=cnt;
		}
		else{
			int pp=cur_p+1;
			++cnt;
			a[cnt].type=0;
			a[cnt].r=a[cur_b].r-pp;
			a[cnt].nt=a[cur_b].nt;
			a[cnt].prev=cur_b;
			a[cnt].dx=a[cur_b].dx+pp;
		}
		++cnt;
		a[cnt].type=1;
		scanf("%s",tmp);
		a[cnt].r=strlen(tmp);
		a[cnt].nt=cnt-1;
		a[cnt].prev=cur_b;
		memcpy(a[cnt].s,tmp,a[cnt].r);
		a[cur_b].nt=cnt;
		cur_b=cnt-1;
		cur_p=0;
}
int main(){
	int _;
	for(scanf("%d",&_);_--;){
		int n;
		
		for(scanf("%d",&n);n--;){
			int m;
			a[1].type=0;
			a[1].r=100000000;
			a[1].dx=0;
			a[1].nt=0;
			cur_b=1;
			cur_p=0;
			for(scanf("%d",&m);m--;){
				char cmd[4];
				scanf("%s",cmd);
				if(cmd[0]=='R'){
					int x;
					scanf("%d",&x);
					Move(x);
				}		
				if(cmd[0]=='C')insert();
				if(cmd[0]=='D'){
					int x;
					scanf("%d",&x);
					del(x);
				}
			}
			//printf("%d %d\n",cur_b,cur_p);
		}
		int now=1;
		for(;now=a[now].nt;)
			if(a[now].type)
				printf("%s\n",a[now].s);
			else printf("%lld %lld\n",a[now].dx+1,a[now].dx+a[now].r);
	}
	return 0;
}

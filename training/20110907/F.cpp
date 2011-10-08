#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<algorithm>
#define LL(x) (x<<1)
#define RR(x) (x<<1|1)
using namespace std;
const int maxnode=600003;
const int N=200003;
struct node{
	int v,mv,mvl;
	node(){}
	node operator +(int d){
		node ret=*this;
		ret.v+=d;
		ret.mv+=d;
		return ret;
	}
	node operator +(const node &x){
		node ret;
		ret.v=0;
		ret.mv=min(mv,x.mv);
		ret.mvl=(mv==x.mv)?(mvl+x.mvl):(mv<x.mv?mvl:x.mvl);
		return ret;
	}
};
node T[maxnode];
void push(int u){
	T[LL(u)]=T[LL(u)]+T[u].v;
	T[RR(u)]=T[RR(u)]+T[u].v;
	T[u].v=0;
}
void insert(int u,int l,int r,int ll,int rr,int d){
	if(l==ll&&r==rr){
		T[u]=T[u]+d;
		return;
	}
	if(T[u].v)push(u);
	int mid=l+r>>1;
	if(rr<=mid)
		insert(LL(u),l,mid,ll,rr,d);
	else if(ll>mid)
		insert(RR(u),mid+1,r,ll,rr,d);
	else{
		insert(LL(u),l,mid,ll,mid,d);
		insert(RR(u),mid+1,r,mid+1,rr,d);
	}
	T[u]=T[LL(u)]+T[RR(u)];
}
vector<int> hy;
int L[N];
struct que{
	int x,y1,y2,d;
	que(){}
	que(int x,int y1,int y2,int d):x(x),y1(y1),y2(y2),d(d){}
	bool operator <(const que &a)const{
		return x<a.x;
	}
};
int findElement(int x){
	int id=lower_bound(hy.begin(),hy.end(),x)-hy.begin();
	return id+1;
}
void initTree(int u,int l,int r){
	if(l==r){
		T[u].mv=0;
		T[u].mvl=L[l];
		//cout<<"!"<<l<<' '<<L[l]<<endl;
		T[u].v=0;
		return;
	}
	int mid=l+r>>1;
	initTree(LL(u),l,mid);
	initTree(RR(u),mid+1,r);
	T[u]=T[LL(u)]+T[RR(u)];
	//cout << "!!" << u << " " << T[u].mvl << endl;
}
long long work(vector<que> &a){
	hy.clear();
	for(int i=0;i<a.size();++i){
		hy.push_back(a[i].y1);
		hy.push_back(a[i].y2);
	}
	stable_sort(hy.begin(),hy.end());
	hy.erase(unique(hy.begin(),hy.end()),hy.end());
	int len=hy.size();
	for(int i=0;i<len-1;++i)
		L[i+1]=hy[i+1]-hy[i];
	initTree(1,1,len-1);
	int totalLen=hy[len-1]-hy[0];
	int lastX=-1000003;
	long long ret=0;
	//cout << T[1].mvl << ' ' << totalLen << '!' << endl;
	//printf("!!!%d %d\n", T[1].mvl, totalLen);
	stable_sort(a.begin(),a.end());
	//cout<<"=========="<<endl;
	for(int i=0;i<a.size();++i){
		ret+=1LL*(totalLen-(T[1].mv==0?T[1].mvl:0))*(a[i].x-lastX);
		insert(1,1,len-1,findElement(a[i].y1),findElement(a[i].y2)-1,a[i].d);
		/*cout<<T[1].v<<" "<<T[1].mv<<" "<<T[1].mvl<<endl;
		cout<<T[2].v<<" "<<T[2].mv<<" "<<T[2].mvl<<endl;
		cout<<T[3].v<<" "<<T[3].mv<<" "<<T[3].mvl<<endl;
		cout<<endl;
		*/
		lastX=a[i].x;
	}
	return ret;
}
int n,m,p[30],r[30],ra[30];
bool cmp(int x,int y){
	return p[x]<p[y];
}
struct mat{
	int x1,y1,x2,y2;
	short id;
	mat(){}
	mat(int x1,int y1,int x2,int y2,short id):x1(x1),y1(y1),x2(x2),y2(y2),id(id){}
	bool operator <(const mat &a)const{
		return id>a.id;
	}
};
mat a[N];
vector<que> s;
int main(){
	int _,cas=0;
	for(scanf("%d",&_);_--;){
		scanf("%d%d",&n,&m);
		for(int i=0;i<m;++i){
			scanf("%d",p+i);
			r[i]=i;
		}
		stable_sort(r,r+m,cmp);
		for(int i=0;i<m;++i)
			ra[r[i]]=i;
		stable_sort(p,p+m);
		for(int i=1;i<=n;++i){
			int x1,y1,x2,y2,d;
			scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&d);
			d=ra[d-1];
			a[i]=mat(x1,y1,x2,y2,d);
		}
		stable_sort(a+1,a+n+1);
		s.clear();
		long long ans=0;
		for(int i=1;i<=n;++i){
			if(i>1&&a[i].id!=a[i-1].id) {
				//printf("%d %lld\n", a[i].id, work(s));
				ans+=work(s)*(p[a[i-1].id]-p[a[i-1].id-1]);
			}
			s.push_back(que(a[i].x1,a[i].y1,a[i].y2,1));
			s.push_back(que(a[i].x2,a[i].y1,a[i].y2,-1));
		}
				//printf("%d %lld\n", a[0].id, work(s));
		ans+=work(s)*p[0];
		cout<<"Case " << ++ cas << ": " <<ans<<endl;
	}
	return 0;
}

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<iostream>
using namespace std;
struct node
{
	int v,size;
	node *l,*r;
	node(){}
}*null;
node* init(int v)
{
	node* ret=new node();
	ret->v=v;
	ret->size=1;
	ret->l=ret->r=null;
	return ret;
}
node* merge(node *a,node *b)
{
	if(a==null)return b;
	if(b==null)return a;
	if(a->v<b->v)
		swap(a,b);
//	if(rand()&1)a->r=merge(a->r,b);
//	else a->l=merge(a->l,b);
	a->r = merge(a->r, b);
	if (a->l->size < a->r->size) swap(a->l, a->r);
	a->size=a->l->size+a->r->size+1;
	return a;
}
node* deletemin(node *a)
{
	node *left=a->l;
	node *right=a->r;
	delete a;
	node* ret=merge(left,right);
	return ret;
}
int testdepth(node *a, int d) {
	if (a == null) return d;
	return max(testdepth(a->l, d + 1), testdepth(a->r, d + 1));
}
int n,a[50003],value[50003],len[50003];
node* f[50003];
int main()
{
	srand(unsigned(time(0)));
	null=new node();
	null->v=-2147483647; null->size = 0;
	while(scanf("%d",&n),n)
	{
		int cnt=0;
		for(int i=1;i<=n;++i)
		{
			scanf("%d",a+i);
			node* tmp=init(a[i]);
			f[++cnt]=tmp;
			value[cnt]=a[i];
			len[cnt]=1;
			while(cnt>1&&value[cnt] < value[cnt - 1])
			{
				f[cnt-1]=merge(f[cnt-1],f[cnt]);
				len[cnt-1]+=len[cnt];
				--cnt;
				//cout << "!" << i << ' ' << cnt << ' ' << len[cnt] << ' ' << f[cnt]->size<< endl;
				for(int k=0;k<f[cnt]->size - (len[cnt]/2+1);++k)
					f[cnt]=deletemin(f[cnt]);
				//cout << "!" << i << ' ' << cnt << ' ' << len[cnt] << ' ' << f[cnt]->size << endl;
				if((~len[cnt])&1)
				{
					int val=(cnt==1)?0:value[cnt - 1];
					//cout << cnt << ' ' << value[cnt - 1] << ' ' << f[cnt]->v << ' ' << max(f[cnt]->l->v, f[cnt]->r->v) << endl;
					value[cnt]=min(f[cnt]->v,max(val, max(f[cnt]->l->v, f[cnt]->r->v)));
				}
				else
					value[cnt]=f[cnt]->v;
			}
			//cout << cnt << ' ' << value[cnt] << endl;
		}
		cout << testdepth(f[1], 0) << endl;
		int j=0;
		long long ans=0;
		for(int i=1;i<=cnt;++i)
		{
			int v=value[i];
			for(int k=0;k<len[i];++k)
			{
				++j;
				ans+=abs((long long)a[j]-v);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}

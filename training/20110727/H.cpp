#include<cstdio>
#include<map>
#include<vector>
using namespace std;
const char suit[]={'C','D','H','S'};
struct face
{
	int r,s;
	face(){}
	face(int _r,int _s):r(_r),s(_s){}
	face(int _r,char ch):r(_r)
	{
		for(int i=0;i<4;++i)
			if(suit[i]==ch)
				s=i;
	}
	bool operator <(const face &x){
		if(x.r!=r)return r<x.r;
		else return 0;
	}
	bool operator >(const face &x){
		if(x.r!=r)return r>x.r;
		else return 0;
	}
	bool operator ==(const face &x){
		return r==x.r;
	}
};
struct hand
{
	face l[5];
	hand(){}
	hand(face a,face b,face c,face d,face e):l[0](a),l[1](b),l[2](c),l[3](d),l[4](e){}
};
bool is1(hand x)
{
	return true;
}
bool is2(hand x)
{
	int cnt[31]={0};
	for(int i=0;i<5;++i)
			++cnt[x.l[i].r];
	for(int i=1;i<14;++i)
		if(cnt[i]>=2)
			return true;
	return false;
}
bool is3(hand x)
{
	int cnt[31]={0};
	for(int i=0;i<5;++i)
			++cnt[x.l[i].r];
	int ret=0;
	for(int i=1;i<14;++i)
		if(cnt[i]>=2)
			++ret;
	return ret>=2;
}
bool is4(hand x)
{
	int cnt[31]={0};
	for(int i=0;i<5;++i)
			++cnt[x.l[i].r];
	for(int i=1;i<14;++i)
		if(cnt[i]>=3)
			return true;
	return false;
}
bool is5(hand x)
{
	bool cnt[31]={0};
	for(int i=0;i<5;++i)
		if(x.l[i].r!=1)
			cnt[x.l[i].r]=1;
		else
			cnt[1]=cnt[14]=1;
	for(int i=1;i<=14;++i)
		if(cnt[i]&&cnt[i+1]&&cnt[i+2]&&cnt[i+3]&&cnt[i+4])
			return true;
	return false;
}
bool is6(hand x)
{
	for(int i=1;i<5;++i)
		if(x.l[i].s!=x.l[0].s)
			return false;
	return true;
}
bool is7(hand x)
{
	int cnt[4]={0};
	for(int i=0;i<5;++i)
		++cnt[x.l[i].s];
	for(int i=0;i<4;++i)
		for(int j=0;j<4;++j)
			if(cnt[i]==3&&cnt[j]==2)
				return true;
	return false;
}
bool is8(hand x)
{
	int cnt[4]={0};
	for(int i=0;i<5;++i)
		++cnt[x.l[i].s];
	for(int i=0;i<4;++i)
		if(cnt[i]==4)
			return true;
	return false;
}
bool is9(hand x)
{
	return is5(x)&&is6(x);
}
int count(hand x)
{
	if(is9(x))return 9;
	if(is8(x))return 8;
	if(is7(x))return 7;
	if(is6(x))return 6;
	if(is5(x))return 5;
	if(is4(x))return 4;
	if(is3(x))return 3;
	if(is2(x))return 2;
	if(is1(x))return 1;
}
int main()
{
	for(int x1=1;x1<=14;++x1)
		for(int y1=0;y1<4;++y1)
		{
			face a(x1,y1);
			for(int x2=1;x2<=14;++x2)
				for(int y2=0;y2<4;++y2)
				{
					face b(x2,y2);
					for(int x3=1;x3<=14;++x3)
						for(int y3=0;y3<4;++y3)
						{
							face c(x3,y3);
							for(int x4=1;x4<=14;++x4)
								for(int y4=0;y4<4;++y4)
								{
									face d(x4,y4);
									for(int x5=1;x5<=14;++x5)
										for(int y5=0;y5<4;++y5)
										{
											face e(x5,y5);
											hand t(a,b,c,d,e);
											int tmp=count(t);
											
}

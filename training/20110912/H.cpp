#include<cstdio>
#include<cstring>
#include<set>
#include<map>
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
#define pb push_back
#define ck(ss) if(x=="ss")
using namespace std;
string c1,c2,n1,n2,s1,s2;
vector<string> a1,a2;
vector<int> work(string s1,vector<string> s2){
	vector<int> ret;
	ret.clear();
	for(int i=0;i<s2.size();++i){
		string x=s2[i];
		if(s1=="cs")
		{
			if(x=="Kamen")ret.pb(1);
			if(x=="Nuzky")ret.pb(2);
			if(x=="Papir")ret.pb(3);
		}
		else if(s1=="en")
		{
			if(x=="Rock")ret.pb(1);
			if(x=="Scissors")ret.pb(2);
			if(x=="Paper")ret.pb(3);
		}
		else if(s1=="fr")
		{
			if(x=="Pierre")ret.pb(1);
			if(x=="Ciseaux")ret.pb(2);
			if(x=="Feuille")ret.pb(3);
		}
		else if(s1=="de")
		{
			if(x=="Stein")ret.pb(1);
			if(x=="Schere")ret.pb(2);
			if(x=="Papier")ret.pb(3);
		}
		else if(s1=="hu")
		{
			if(x=="Ko")ret.pb(1);
			if(x=="Koe")ret.pb(1);
			if(x=="Ollo")ret.pb(2);
			if(x=="Olloo")ret.pb(2);
			if(x=="Papir")ret.pb(3);
		}
		else if(s1=="it")
		{
			if(x=="Sasso")ret.pb(1);
			if(x=="Roccia")ret.pb(1);
			if(x=="Forbice")ret.pb(2);
			if(x=="Carta")ret.pb(3);
			if(x=="Rete")ret.pb(3);
		}
		else if(s1=="jp")
		{
			if(x=="Guu")ret.pb(1);
			if(x=="Choki")ret.pb(2);
			if(x=="Paa")ret.pb(3);
		}
		else if(s1=="pl")
		{
			if(x=="Kamien")ret.pb(1);
			if(x=="Nozyce")ret.pb(2);
			if(x=="Papier")ret.pb(3);
		}
		else if(s1=="es")
		{
			if(x=="Piedra")ret.pb(1);
			if(x=="Tijera")ret.pb(2);
			if(x=="Papel")ret.pb(3);
		}
	}
	return ret;
}
bool Win(int x,int y){
	if(x==1&&y==2)return 1;
	if(x==2&&y==3)return 1;
	if(x==3&&y==1)return 1;
	return 0;
}
int main(){
	int cas=0;
	for(;;){
		cin>>c1>>n1;
		cin>>c2>>n2;
		a1.clear();a2.clear();
		while(cin>>s1,s1!="-"&&s1!="."){
			cin>>s2;
			a1.push_back(s1);
			a2.push_back(s2);
		}
		vector<int> a=work(c1,a1);
		vector<int> b=work(c2,a2);
		int p1=0,p2=0;
		for(int i=0;i<a.size();++i)
			p1+=Win(a[i],b[i]),p2+=Win(b[i],a[i]);
		cout<<"Game #"<<++cas<<":"<<endl;
		cout<<n1<<": "<<p1<<" point"<<(p1==1?"":"s")<<endl;
		cout<<n2<<": "<<p2<<" point"<<(p2==1?"":"s")<<endl;
		if(p1!=p2)cout<<"WINNER: "<<((p1>p2)?n1:n2)<<endl;
		else cout<<"TIED GAME"<<endl;
		cout<<endl;
		if(s1==".")break;
	}
	return 0;
}

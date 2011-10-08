#include<map>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
int n,opp[11];
string s[11];
map<string,int> h;
vector< vector<int> > hh;
bool use[11];

void search(int u,vector<int> now){
	if(u==n){
		hh.push_back(now);
		return;
	}
	for(int i=0;i<n;++i){
		if(use[i])continue;
		use[i]=1;
		now.push_back(i);
		search(u+1,now);
		now.erase(now.end()-1);
		use[i]=0;
	}
}

bool beat(vector<int> a,vector<int> b){
	for(int i=0,j=0;i<n;++i){
		while(j<n&&(~opp[b[j]]&(1<<a[i])))++j;
		if(j>=n)return 1;
	}
	return 0;
}

int main(){
	int _;
	cin>>_;
	for(int cas=1;cas<=_;++cas){
		cin>>n;
		h.clear();
		for(int i=0;i<n;++i){
			cin>>s[i];
			h[s[i]]=i;
		}
		for(int i=0;i<n;++i){
			opp[i]=0;
			int k;
			string t;
			for(cin>>k;k--;){
				cin>>t;
				opp[i]|=(1<<h[t]);
			}
		}
		hh.clear();
		vector<int> tmp;tmp.clear();
		search(0,tmp);
		//cout<<hh.size()<<endl;
		
		string ans="";
		for(int i=0;i<hh.size();++i)
		{
			bool OK=1;
			for(int j=0;j<hh.size();++j)
				if(!beat(hh[i],hh[j])){
					OK=0;
					break;
				}
			if(OK){
				string t;
				for(int j=0;j<n;++j)t+=s[hh[i][j]]+" ";
				if(ans==""||t<ans)ans=t;
			}
		}
		cout<<"Case "<<cas<<": "<<(ans==""?"No":"Yes")<<endl;
		if(ans!=""){
			ans[ans.size()-1]='\n';
			cout<<ans;
		}
	}
	return 0;
}

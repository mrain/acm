#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
char s1[1003],s3[1003];
int main(){
	while(scanf("%s %s",s1,s3)==2){
		int s2=0;
		for(int i=0;i<strlen(s1);++i)
			if(s1[i]=='-'){
				for(int j=i+1;j<strlen(s1);++j)
					s2=s2*10+s1[j]-'0';
				break;
			}
		//printf("%d\n",s2);
		if(s1[0]=='f'){
			int ans=0;
			for(int i=s3[0]=='-'?1:0;i<strlen(s3);++i)
				ans=ans*(-s2)+s3[i]-'0';
			if(s3[0]=='-')ans*=-1;
			printf("%d\n",ans);
		}
		else{
			int n=0;
			for(int i=s3[0]=='-'?1:0;i<strlen(s3);++i)
				n=(n<<1)+(n<<3)+s3[i]-'0';
			if(s3[0]=='-')n*=-1;
			string ans="";
			for(int j=-s2;n;){
				int shang=n/j;
				int yu=n%j;
				if(yu<0)yu+=s2,++shang;
				//printf("%d %d\n",shang,yu);
				n=shang;
				ans+=('0'+yu);
			}
			reverse(ans.begin(),ans.end());
			if(ans.size())cout<<ans<<endl;
			else cout<<'0'<<endl;
		}
	}
	return 0;
}

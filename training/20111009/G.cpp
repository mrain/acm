#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char s[11][11];
bool win(char ch){
	for(int i=0;i<5;++i)
		for(int j=0;j<5;++j){
			if(i+2<5)
				if(s[i][j]==ch&&s[i+1][j]==ch&&s[i+2][j]==ch)return true;
			if(j+2<5)
				if(s[i][j]==ch&&s[i][j+1]==ch&&s[i][j+2]==ch)return true;
			if(i+2<5&&j+2<5)
				if(s[i][j]==ch&&s[i+1][j+1]==ch&&s[i+2][j+2]==ch)return true;
			if(i-2>=0&&j+2<5)
				if(s[i][j]==ch&&s[i-1][j+1]==ch&&s[i-2][j+2]==ch)return true;
		}
	return false;
}
int main(){
	int _;
	for(scanf("%d",&_);_--;){
		for(int i=0;i<5;++i)
			scanf("%s",s[i]);
		bool winA=win('A');
		bool winB=win('B');
		if(winA&&winB)puts("draw");
		else if(winA)puts("A wins");
		else if(winB)puts("B wins");
		else puts("draw");
	}
	return 0;
}

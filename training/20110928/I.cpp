#include<cstdlib>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

int main() {
cout << ((rand() & 1) == 0 ? "No" : "Yes") << endl;
return 0;
}

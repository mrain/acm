#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
using namespace std;
const string ans[9][9] = 
{{"1","2","3","4","5","6","7","8","9"},
{"0","105263157894736842","157894736842105263","210526315789473684","263157894736842105","315789473684210526","368421052631578947","421052631578947368","473684210526315789"},
{"0","0","1034482758620689655172413793","1379310344827586206896551724","1724137931034482758620689655","2068965517241379310344827586","2413793103448275862068965517","2758620689655172413793103448","3103448275862068965517241379"},
{"0","0","0","102564","128205","153846","179487","205128","230769"},
{"0","0","0","0","102040816326530612244897959183673469387755","122448979591836734693877551020408163265306","142857","163265306122448979591836734693877551020408","183673469387755102040816326530612244897959"},
{"0","0","0","0","0","1016949152542372881355932203389830508474576271186440677966","1186440677966101694915254237288135593220338983050847457627","1355932203389830508474576271186440677966101694915254237288","1525423728813559322033898305084745762711864406779661016949"},
{"0","0","0","0","0","0","1014492753623188405797","1159420289855072463768","1304347826086956521739"},
{"0","0","0","0","0","0","0","1012658227848","1139240506329"},
{"0","0","0","0","0","0","0","0","10112359550561797752808988764044943820224719"}};

int tests, a, b;

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d%d", &a, &b);
		puts(ans[a-1][b-1].c_str());
	}
	return 0;
}

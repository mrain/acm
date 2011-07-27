#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <bitset>
#include <deque>
#include <cstring>
#include <iomanip>
#include <cctype>
using namespace std;
#define lowbit(x) ((x)&(-(x)))
const double eps = 1e-8;
const double pi = acos(-1.);

inline int sgn(double a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}

inline double sqr(double a) { return a * a; }

template <class T>
T abs(T a) { return a < 0 ? -a : a; }

template <class T>
T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }

const int mod = 1000000009;

class YetAnotherIncredibleMachine {
public:
	int calc(int x, int len, const vector <int> &balls) {
		int cnt = 0;
		for (int start = x - len; start <= x; ++ start) {
			bool flag = true;
			for (int i = 0; i < (int)balls.size(); ++ i)
				if (balls[i] >= start && balls[i] <= start + len) {
					flag = false;
					break;
				}
			if (flag) ++ cnt;
		}
		return cnt;
	}
   int countWays( vector <int> platformMount, vector <int> platformLength, vector <int> balls ) {
	   sort(balls.begin(), balls.end());
	   long long ans = 1;
	   for (int i = 0; i < (int)platformMount.size(); ++ i)
		   ans = (ans * calc(platformMount[i], platformLength[i], balls)) % mod;
	   return ans;
   }
};

// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if ( casenum != -1 ) {
			if ( run_test_case( casenum ) == -1 && !quiet )
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			return;
		}
		
		int correct = 0, total = 0;
		for ( int i=0;; ++i ) {
			int x = run_test_case(i);
			if ( x == -1 ) {
				if ( i >= 100 ) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if ( total == 0 ) {
			cerr << "No test cases run." << endl;
		} else if ( correct < total ) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if ( expected == received ) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;
		
		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl; 
			cerr << "    Received: " << received << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case( int casenum ) {
		switch( casenum ) {
		case 0: {
			int platformMount[]       = {7};
			int platformLength[]      = {10};
			int balls[]               = {3,4};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = YetAnotherIncredibleMachine().countWays( vector <int>( platformMount, platformMount + ( sizeof platformMount / sizeof platformMount[0] ) ), vector <int>( platformLength, platformLength + ( sizeof platformLength / sizeof platformLength[0] ) ), vector <int>( balls, balls + ( sizeof balls / sizeof balls[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int platformMount[]       = {1,4};
			int platformLength[]      = {3,3};
			int balls[]               = {2,7};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = YetAnotherIncredibleMachine().countWays( vector <int>( platformMount, platformMount + ( sizeof platformMount / sizeof platformMount[0] ) ), vector <int>( platformLength, platformLength + ( sizeof platformLength / sizeof platformLength[0] ) ), vector <int>( balls, balls + ( sizeof balls / sizeof balls[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int platformMount[]       = {4,4,4};
			int platformLength[]      = {10,9,8};
			int balls[]               = {1,100};
			int expected__            = 27;

			clock_t start__           = clock();
			int received__            = YetAnotherIncredibleMachine().countWays( vector <int>( platformMount, platformMount + ( sizeof platformMount / sizeof platformMount[0] ) ), vector <int>( platformLength, platformLength + ( sizeof platformLength / sizeof platformLength[0] ) ), vector <int>( balls, balls + ( sizeof balls / sizeof balls[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int platformMount[]       = {0};
			int platformLength[]      = {1};
			int balls[]               = {0};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = YetAnotherIncredibleMachine().countWays( vector <int>( platformMount, platformMount + ( sizeof platformMount / sizeof platformMount[0] ) ), vector <int>( platformLength, platformLength + ( sizeof platformLength / sizeof platformLength[0] ) ), vector <int>( balls, balls + ( sizeof balls / sizeof balls[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			int platformMount[]       = {100, -4215, 251};
			int platformLength[]      = {400, 10000, 2121};
			int balls[]               = {5000, 2270, 8512, 6122};
			int expected__            = 250379170;

			clock_t start__           = clock();
			int received__            = YetAnotherIncredibleMachine().countWays( vector <int>( platformMount, platformMount + ( sizeof platformMount / sizeof platformMount[0] ) ), vector <int>( platformLength, platformLength + ( sizeof platformLength / sizeof platformLength[0] ) ), vector <int>( balls, balls + ( sizeof balls / sizeof balls[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 5: {
			int platformMount[]       = ;
			int platformLength[]      = ;
			int balls[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = YetAnotherIncredibleMachine().countWays( vector <int>( platformMount, platformMount + ( sizeof platformMount / sizeof platformMount[0] ) ), vector <int>( platformLength, platformLength + ( sizeof platformLength / sizeof platformLength[0] ) ), vector <int>( balls, balls + ( sizeof balls / sizeof balls[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			int platformMount[]       = ;
			int platformLength[]      = ;
			int balls[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = YetAnotherIncredibleMachine().countWays( vector <int>( platformMount, platformMount + ( sizeof platformMount / sizeof platformMount[0] ) ), vector <int>( platformLength, platformLength + ( sizeof platformLength / sizeof platformLength[0] ) ), vector <int>( balls, balls + ( sizeof balls / sizeof balls[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			int platformMount[]       = ;
			int platformLength[]      = ;
			int balls[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = YetAnotherIncredibleMachine().countWays( vector <int>( platformMount, platformMount + ( sizeof platformMount / sizeof platformMount[0] ) ), vector <int>( platformLength, platformLength + ( sizeof platformLength / sizeof platformLength[0] ) ), vector <int>( balls, balls + ( sizeof balls / sizeof balls[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
		default:
			return -1;
		}
	}
}
 

int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE

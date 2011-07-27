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

typedef pair<int, int> PII;

map <PII, double> f;
class PerfectMemory {
public:
	int n, m;
	double dp(int i, int j) {
		PII t = make_pair(i, j);
		if (f.count(t)) return f[t];
		int rest = n * m - 2 * i - j;
		double res = 0.;
		double p = (double)j / (double)rest;
		if (fabs(p) > eps) res = (dp(i + 1, j - 1) + 1) * p;
		if (fabs(1 - p) > eps) {
			double p1 = (double)j / (double)(rest - 1);
			double p2 = (double)1. / (double)(rest - 1);
			double p3 = 1 - p1 - p2;
			if (fabs(p1) > eps) res += (dp(i + 1, j) + 2) * p1 * (1 - p);
			if (fabs(p2) > eps) res += (dp(i + 1, j) + 1) * p2 * (1 - p);
			if (fabs(p3) > eps) res += (dp(i, j + 2) + 1) * p3 * (1 - p);
		}
		return f[t] = res;
	}
   double getExpectation( int N, int M ) {
	   f.clear();
	   f[make_pair((N * M) / 2, 0)] = 0;
	   n = N, m = M;
	   return dp(0, 0);
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
	
	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ( double expected, double result ) { if ( isnan( expected ) ) { return isnan( result ); } else if ( isinf( expected ) ) { if ( expected > 0 ) { return result > 0 && isinf( result ); } else { return result < 0 && isinf( result ); } } else if ( isnan( result ) || isinf( result ) ) { return false; } else if ( fabs( result - expected ) < MAX_DOUBLE_ERROR ) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error( double expected, double result ) { if ( isnan( expected ) || isinf( expected ) || isnan( result ) || isinf( result ) || expected == 0 ) return 0; return fabs( result-expected ) / fabs( expected ); }
	
	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if ( topcoder_fequ( expected, received ) ) {
			verdict = "PASSED";
			double rerr = moj_relative_error( expected, received ); 
			if ( rerr > 0 ) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int N                     = 1;
			int M                     = 2;
			double expected__         = 1.0;

			clock_t start__           = clock();
			double received__         = PerfectMemory().getExpectation( N, M );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int N                     = 2;
			int M                     = 2;
			double expected__         = 2.6666666666666665;

			clock_t start__           = clock();
			double received__         = PerfectMemory().getExpectation( N, M );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int N                     = 2;
			int M                     = 3;
			double expected__         = 4.333333333333334;

			clock_t start__           = clock();
			double received__         = PerfectMemory().getExpectation( N, M );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int N                     = 4;
			int M                     = 4;
			double expected__         = 12.392984792984793;

			clock_t start__           = clock();
			double received__         = PerfectMemory().getExpectation( N, M );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 4: {
			int N                     = ;
			int M                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = PerfectMemory().getExpectation( N, M );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 5: {
			int N                     = ;
			int M                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = PerfectMemory().getExpectation( N, M );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			int N                     = ;
			int M                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = PerfectMemory().getExpectation( N, M );
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

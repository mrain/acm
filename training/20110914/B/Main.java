import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static int bound = 500000; 
	static int n, m, A, B;
	static BigInteger ZERO = BigInteger.ZERO;
	static BigInteger ONE = BigInteger.ONE;
	static int f[] = new int[bound + 5];
	static BigInteger a[] = new BigInteger[bound + 5];
	static BigInteger b[] = new BigInteger[bound + 5]; 
	static int sum[] = new int[bound + 5];

	public static void ready() {
		int cnt = 0;
	
		for (int i = 2; i < bound; ++i) if (f[i] == 0) {
			a[++cnt] = BigInteger.valueOf(i);
			
			for (int k = i; k <= bound; k += i) if (f[k] == 0) f[k] = i;
		}
		
		
		cnt = 0;
		for (int i = 2; i <= bound; ++i) {
			int last = -1, now = 1, x = i;
			sum[i] = 1;
			
			while (true) {
				if (last != f[x]) {
					sum[i] *= now; now = 2;
				}
				else now++;
				
				last = f[x];
				
				if (f[x] == 0) break;
				last = f[x]; x /= f[x];
			}
			
			if (sum[i] == 4 && f[i] != f[i / f[i]]) b[++cnt] = BigInteger.valueOf(i);
		}
		
		//System.out.println(cnt);
	}

	public static void main(String[] args) {
		ready();
		//System.out.println(sum[3]);
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		
		while (cin.hasNext()) {
			n = cin.nextInt(); m = cin.nextInt();
			
			if (sum[m] == 1) {
				System.out.println("1");
				continue;
			}
			
			//System.out.println(m + " " + sum[m]);
			
			if (sum[m] <= 2) {
				System.out.println(a[n].pow(m - 1));
				continue;
			}
			
			A = m - 1; B = f[m] - 1;
			BigInteger ans = ZERO;
/*			
			int i = 1, j = 1;
			for (int t = 1; t <= n; ++t) {
				BigInteger x = a[i].pow(A), y = b[j].pow(B);
				if (x.compareTo(y) <= 0) {
					i++;
					if (t == n) ans = x;
				}
				else {
					j++;
					if (t == n) ans = y;
				}
			} 
*/			
			if (n == 1) {
				BigInteger x = a[n].pow(A), y = b[n].pow(B);
				if (x.compareTo(y) < 0) ans = x;
				else ans = y;
			} else {
				int i = 1, j = n - 1;
				while (true) {
					BigInteger x = a[i].pow(A), y = b[j].pow(B);
				
					int tmp = x.compareTo(y);
			
					if (tmp == 1) {
						y = b[j + 1].pow(B);
					
						if (x.compareTo(y) < 0) ans = x;
						else ans = y;
					
						break;
					}
				
					i++; j--;
				}
			}

			System.out.println(ans);
		}
	}
}

import java.io.*;
import java.math.*;
import java.util.*;
import java.lang.*;

public class Main{
	static final int maxn = 40;
	static BigInteger f[][] = new BigInteger[maxn][maxn];
	static BigInteger A[] = new BigInteger[maxn];
	static BigInteger B[] = new BigInteger[maxn];
	static int ans[] = new int [maxn];
	static int t[] = new int [maxn];
	static int mark[] = new int [maxn];
	static int n,T;
	static boolean vis[] = new boolean [maxn];
	
	static final BigInteger ZERO = BigInteger.valueOf(0);
	static final BigInteger ONE = BigInteger.valueOf(1);
	static final BigInteger TEN = BigInteger.valueOf(10);
	
	public static int calc(BigInteger a, BigInteger b) {
		a = a.abs(); b = b.abs(); 
	
		a = a.mod(b);
		
		String str = b.toString();
		
		BigInteger tmp = a.multiply(TEN.pow(str.length())).divide(b); 
		
		str = tmp.toString(); 
		
		return str.charAt(0) - '0';
	}
	
	public static void main(String args[]) {
		Scanner Scan = new Scanner (new BufferedInputStream(System.in));
		
		T=Scan.nextInt();
			
		for (int cases = 0; cases < T; ++cases) {
		
			//Init()
			n = Scan.nextInt();
			for (int i = 1; i < n; ++i) t[i] = Scan.nextInt();
			
			for (int i = 1; i < n; ++i) {
				for (int j = 1; j <= n; ++j) {
					BigInteger tmp;
				
					tmp = BigInteger.valueOf(-t[i]);
					tmp = tmp.pow(j-1);
					f[i][j] = tmp.multiply(BigInteger.valueOf(j));
				}
			}
			
			//Gauss()
			for (int i = 1; i < n; ++i) vis[i] = false;
			for (int i = 1; i < n; ++i) {
				int x = -1;
				
				for (int j = 1; j < n; ++j) if (!vis[j] && f[j][i] != ZERO) {
					x = j; break;
				}
				
				BigInteger  a = f[x][i]; vis[x] = true;
				
				for (int j = 1; j < n; ++j) if (!vis[j] && f[j][i] != ZERO) {
					BigInteger b = f[j][i];
					
					BigInteger G = a.gcd(b);
					BigInteger X = a.divide(G), Y = b.divide(G);
					
					for (int k = i; k <= n; ++k) {
						BigInteger tmp = f[j][k];
						
						tmp = tmp.multiply(X);
						f[j][k] = tmp.subtract(f[x][k].multiply(Y));
					}
				}
				
				mark[i] = x;
			}
/*			
			for (int i = 1; i < n; ++i) {
				int x = mark[i];
				//System.out.printf("%d\n", x);
				for (int j = 1; j <= n; ++j) {
					System.out.print(f[x][j]); System.out.printf("  ");
				}
				
				System.out.println();
			}
*/		
			//Outit()
			A[n] = ONE; B[n] = BigInteger.valueOf(n);
			
			ans[n] = calc(A[n], B[n]);
			for (int i = n - 1; i > 0; --i) {
				int x=mark[i];
				A[i] = ZERO; B[i] = ONE; 
			
				for (int j = i + 1; j <= n; ++j) {
					A[i] = A[i].multiply(B[j]);
					A[i] = A[i].subtract(A[j].multiply(B[i].multiply(f[x][j])));
					B[i] = B[i].multiply(B[j]);
					
					BigInteger G = A[i].gcd(B[i]);
					if (G != ZERO && G != ONE) {
						A[i] = A[i].divide(G); B[i] = B[i].divide(G);
					}
				}
				
				B[i] = B[i].multiply(f[x][i]);
				
				BigInteger G = A[i].gcd(B[i]);
				if (G != ZERO && G != ONE) {
					A[i] = A[i].divide(G); B[i] = B[i].divide(G);
				}
		/*	
				System.out.printf("%d:\n",i);
				System.out.print(A[i]); System.out.printf("  "); System.out.print(B[i]); System.out.println();
		*/
				ans[i] = calc(A[i], B[i]);
			}
			
			for (int i = 1; i < n ; ++i) System.out.printf("%d ", ans[i]);
			System.out.printf("%d\n", ans[n]);
		}
	}
}


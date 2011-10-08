import java.io.*;
import java.math.*;
import java.util.*;
import java.lang.*;

public class Main{
	static final int maxn = 600, bound = 500;
	static BigInteger a[][] = new BigInteger[maxn][maxn];
	static BigInteger b[][] = new BigInteger[maxn][maxn];
	
	static final BigInteger ZERO = BigInteger.valueOf(0);
	static final BigInteger ONE = BigInteger.valueOf(1);
	static final BigInteger TEN = BigInteger.valueOf(10);
	
	public static void main(String args[]) {
		Scanner cin = new Scanner (new BufferedInputStream(System.in));
		
		//int T = cin.nextInt();
		for (int n = 1; n <= 500; ++ n) {
			//int n = cin.nextInt();
			
			for (int i = 0; i <= n; ++i)
				for (int j = 0; j <= n; ++j) {
					a[i][j] = ZERO; b[i][j] = ONE;				
				}
				
			a[0][0] = ONE; b[0][0] = ONE;
				
			for (int i = 0; i < n; ++i) {
				for (int j = i; j < n; ++j) {
					if (a[i][j].equals(ZERO)) continue;	

					BigInteger x = a[i][j];
					BigInteger y = b[i][j].multiply(BigInteger.valueOf(n + n - i - i));
					
					a[i + 1][j + 1] = a[i + 1][j + 1].multiply(y).add(x.multiply(b[i + 1][j + 1]));
					b[i + 1][j + 1] = b[i + 1][j + 1].multiply(y);
							
					BigInteger GCD = b[i + 1][j + 1].gcd(a[i + 1][j + 1]);
					a[i + 1][j + 1] = a[i + 1][j + 1].divide(GCD); 
					b[i + 1][j + 1] = b[i + 1][j + 1].divide(GCD);
				}
				
				for (int j = 1; j < n; ++j) {
					BigInteger x = a[i + 1][j];
					BigInteger y = b[i + 1][j];
					
					a[i + 1][j + 1] = a[i + 1][j + 1].multiply(y).add(x.multiply(b[i + 1][j + 1]));
					b[i + 1][j + 1] = b[i + 1][j + 1].multiply(y);
							
					BigInteger GCD = b[i + 1][j + 1].gcd(a[i + 1][j + 1]);
					a[i + 1][j + 1] = a[i + 1][j + 1].divide(GCD); 
					b[i + 1][j + 1] = b[i + 1][j + 1].divide(GCD);
				}
				
				for (int j = i + 1; j <= n; ++j) {
					if (a[i][j].equals(ZERO)) continue;	
					
					BigInteger y = b[i][j].multiply(BigInteger.valueOf(n - i));
					BigInteger x = a[i][j].multiply(BigInteger.valueOf(j - i));
						
					a[i + 1][j] = a[i + 1][j].multiply(y).add(x.multiply(b[i + 1][j]));
					b[i + 1][j] = b[i + 1][j].multiply(y);
						
					BigInteger GCD = b[i + 1][j].gcd(a[i + 1][j]);
					a[i + 1][j] = a[i + 1][j].divide(GCD); 
					b[i + 1][j] = b[i + 1][j].divide(GCD);					
				}
			}
				
			System.out.println("\"" + a[n][n] + "/" + b[n][n] + "\",");
		}
	}
}
/*
F[0][0] = 1/1
1/2
F[0][0] = 1/1
F[1][1] = 1/8
F[1][2] = 1/8
F[1][3] = 1/8
F[1][4] = 1/8
F[2][2] = 9/18
F[2][3] = 78/72
F[2][4] = 276/144
F[3][3] = 6/8
F[3][4] = 28/16
3/2
*/

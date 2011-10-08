import java.io.*;
import java.math.*;
import java.util.*;
import java.lang.*;

public class Main{
	static final int maxn = 600, bound = 500;
	
	static final BigInteger ZERO = BigInteger.valueOf(0);
	static final BigInteger ONE = BigInteger.valueOf(1);
	static final BigInteger TEN = BigInteger.valueOf(10);
	
	public static void main(String args[]) {
		Scanner cin = new Scanner (new BufferedInputStream(System.in));
		
		int T = cin.nextInt();
		while (T > 0) {
			T = T - 1;
			int n = cin.nextInt();
			BigInteger A = BigInteger.ONE;
			BigInteger B = BigInteger.valueOf(2).pow(2 * n);
			for (int i = 1; i <= n; ++ i) {
				B = B.multiply(BigInteger.valueOf(i));
				A = A.multiply(BigInteger.valueOf(n + i));
				BigInteger x = A.gcd(B);
				A = A.divide(x); B = B.divide(x);
			}

			System.out.println(A + "/" + B);
		}
	}
}


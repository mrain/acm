import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) throws Exception {
		int n, m, k;
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		n = cin.nextInt(); m = cin.nextInt(); k = cin.nextInt();
		BigInteger A = BigInteger.ZERO;
		BigInteger B = (BigInteger.valueOf(n)).pow(k);
		BigInteger N = BigInteger.valueOf(n - 1);
		BigInteger C = BigInteger.ONE;

		for (int a = 0; a <= k; ++ a) {
			if (a > 0) C = (C.multiply(BigInteger.valueOf(k - a + 1))).divide(BigInteger.valueOf(a));
			BigInteger tmp = (N.pow(k - a)).multiply(C);
			if ((a & 1) == 0) A = A.add(tmp.multiply(BigInteger.valueOf(m)));
			else A = A.add(tmp.multiply(BigInteger.valueOf(n - m)));
		}

		BigInteger p = A.gcd(B);
		A = A.divide(p); B = B.divide(p);
		System.out.print(A);
		System.out.print('/');
		System.out.println(B);
	}
}

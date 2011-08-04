import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) throws Exception {
		int N, M, K;
		BigInteger[] CM = new BigInteger[1010];
		BigInteger[] CNM = new BigInteger[1010];

		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		N = cin.nextInt(); M = cin.nextInt(); K = cin.nextInt();
		CM[0] = CNM[0] = BigInteger.ONE;
		for (int i = 1; i <= K; ++ i) {
			if (i <= M)
				CM[i] = (CM[i - 1].multiply(BigInteger.valueOf(M - i + 1))).divide(BigInteger.valueOf(i));
			if (i <= N - M)
				CNM[i] = (CNM[i - 1].multiply(BigInteger.valueOf(N - M - i + 1))).divide(BigInteger.valueOf(i));
		}
		BigInteger B = (BigInteger.valueOf(N)).pow(K);
		BigInteger A = BigInteger.ZERO;
		for (int i = 0; i <= K; ++ i)
			for (int j = 0; j <= K; ++ j)
				if (i <= M && j <= N - M && i + j <= K && (K - i - j) % 2 == 0) {
					BigInteger tmp = (CM[i].multiply(CNM[j])).multiply((BigInteger.valueOf(N)).pow((K - i - j) / 2));
//					A = A.add(tmp.multiply(BigInteger.valueOf(M - i + j)));
					System.out.print(i);
					System.out.print(' ');
					System.out.print(j);
					System.out.print(' ');
					System.out.println(tmp);
					A = A.add(tmp);
				}
		BigInteger k = A.gcd(B);
//		A = A.divide(k); B = B.divide(k);
		System.out.print(A);
		System.out.print('/');
		System.out.println(B);
	}
}

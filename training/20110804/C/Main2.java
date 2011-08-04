import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) throws Exception {
		int N, M, K;
		BigInteger f[][] = new BigInteger[2][2020];

		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		N = cin.nextInt(); M = cin.nextInt(); K = cin.nextInt();
		BigInteger A = BigInteger.ZERO;
		BigInteger B = (BigInteger.valueOf(N)).pow(K);


		int now = 0, next = 1;
		for (int j = 0; j < 2020; ++ j)
			f[now][j] = BigInteger.ZERO;
		f[0][1010] = BigInteger.ONE;
		for (int i = 0; i < K; ++ i) {
			for (int j = 0; j < 2020; ++ j)
				f[next][j] = BigInteger.ZERO;
			for (int j = 1010 - K - 1; j < 1010 + K + 1; ++ j)
				if (!f[now][j].equals(BigInteger.ZERO)) {
					int k = M + j - 1010;
					if (k < 0 || k > N) continue;
//					System.out.printf("%d %d\n", i, j);
					f[next][j - 1] = f[next][j - 1].add(f[now][j].multiply(BigInteger.valueOf(k)));
					f[next][j + 1] = f[next][j + 1].add(f[now][j].multiply(BigInteger.valueOf(N - k)));
				}
			now ^= 1; next ^= 1;
		}
		for (int j = 1010 - K - 1; j < 1010 + K + 1; ++ j) {
			int k = M + j - 1010;
			if (k < 0 || k > N) continue;
			A = A.add(f[now][j].multiply(BigInteger.valueOf(k)));
		}
		BigInteger k = A.gcd(B);
		A = A.divide(k); B = B.divide(k);
		System.out.print(A);
		System.out.print('/');
		System.out.println(B);
	}
}

import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
	public static int limit = 400000;
	public static int prime[] = new int[400010];
	public static int pn = 0;
	public static Boolean notprime[] = new Boolean[limit + 10];

	public static void genp() {
		for (int i = 0; i < limit; ++ i)
			notprime[i] = new Boolean(false);
		for (int i = 2; i < limit; ++ i) {
			if (!notprime[i]) prime[pn ++] = i;
			for (int j = 0; j < pn; ++ j) {
				if ((long)i * prime[j] >= limit) break;
				notprime[i * prime[j]] = true;
				if (i % prime[j] == 0) break;
			}
		}
	}
	public static void main(String[] args) {
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		genp();
		int n = cin.nextInt();
		BigInteger m = BigInteger.ONE, k = BigInteger.ONE;
		for (int i = 0; i < pn; ++ i) {
			int cnt = 0;
			while (n % prime[i] == 0) {
				n /= prime[i];
				++ cnt;
			}
			if (cnt % 2 == 1) {
				k = k.multiply(BigInteger.valueOf(prime[i]));
				for (int t = 0; t < (cnt + 3) / 2; ++ t)
					m = m.multiply(BigInteger.valueOf(prime[i]));
			} else {
				for (int t = 0; t < cnt / 2; ++ t)
					m = m.multiply(BigInteger.valueOf(prime[i]));
			}
		}
		if (n > 1) {
			k = k.multiply(BigInteger.valueOf(n));
			for (int t = 0; t < 2; ++ t)
				m = m.multiply(BigInteger.valueOf(n));
		}
		System.out.println(m);
		System.out.println(k);
	}
}

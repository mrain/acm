import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static boolean check(long n, int p) {
		BigInteger P = BigInteger.TEN.pow(p), Q = BigInteger.TEN.pow(p - 1);
		BigInteger N = BigInteger.ONE, tmp = BigInteger.valueOf(2);
		while (n > 0) {
			if ((n % 2) == 1) {
				N = N.multiply(tmp);
				N = N.mod(P);
			}
			tmp = tmp.multiply(tmp);
			tmp = tmp.mod(P);
			n >>= 1;
		}
		N = N.divide(Q);
		if (N.equals(BigInteger.ONE) || N.equals(BigInteger.valueOf(2))) return true;
		else return false;
	}
	public static void main(String[] args) throws Exception {
		long[] ans = new long[30];
		ans[1] = 1; ans[2] = 9; ans[3] = 89; ans[4] = 89;
		long step = 500;
		for (int i = 5; i <= 20; ++ i) {
			long now = ans[i - 1];
			while (!check(now, i)) now += step;
			ans[i] = now;
		//	System.out.println(ans[i]);
			step *= 5;
		}
		for (int i = 1; i <= 20; ++ i) {
			System.out.printf("a[%d]=%dll;\n", i, ans[i]);
		}
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		int tests = cin.nextInt();
		int ca = 0;
		while (tests -- > 0) {
			int n = cin.nextInt();
			System.out.printf("%d %d ", ++ ca, n);
			System.out.println(ans[n]);
		}
	}
}


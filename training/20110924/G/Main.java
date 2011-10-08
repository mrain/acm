import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static int n, m;
	public static int[] b = new int[10010];
	public static BigInteger ans = BigInteger.ZERO;
	public static BigInteger a = BigInteger.ZERO;
	public static BigInteger[] c = new BigInteger[10010];

	public static int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	}

	public static BigInteger calc(int n) {
		BigInteger ret = BigInteger.ZERO;
		for (int i = 1; i <= n; ++ i)
			ret = ret.add(a.pow(gcd(i, n)));
		ret = ret.divide(BigInteger.valueOf(n));
		return ret;
	}

	public static void dfs(int dep, int cur, int cnt) {
		if (dep == m) {

//			System.out.println(n / cur);
			if (cnt % 2 == 0) ans = ans.add(c[n / cur]);
			else ans = ans.subtract(c[n / cur]);

			return;
		}
		dfs(dep + 1, cur, cnt);
		dfs(dep + 1, cur / gcd(cur, b[dep]) * b[dep], cnt + 1);
	}

	public static void main(String[] args) {
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		a = BigInteger.valueOf(cin.nextInt()); n = cin.nextInt(); m = 0;

		int tmp = n; c[1] = a;
		for (int i = 2; i <= n; ++ i) {
			if (n % i == 0) c[i] = calc(i);
			while (tmp % i == 0) {
				b[m ++] = i;
				tmp /= i;
			}
		}

		dfs(0, 1, 0);

		System.out.println(ans);
	}
}

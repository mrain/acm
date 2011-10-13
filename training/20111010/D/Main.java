import java.io.*;
import java.util.*;
import java.math.*;

public class Main {

	public static void main(String[] args) {
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		int tests = cin.nextInt();
		BigInteger mod = BigInteger.valueOf(10).pow(15);
		for (int ca = 1; ca <= tests; ++ ca) {
			BigInteger ans = BigInteger.ZERO;
			int c = cin.nextInt();
			BigInteger C = BigInteger.valueOf(c);
			ans = ans.add(BigInteger.valueOf(6).multiply(C.pow(2)));
			ans = ans.add(BigInteger.valueOf(17).multiply(C.pow(4)));
			ans = ans.add(BigInteger.valueOf(1).multiply(C.pow(8)));
			ans = ans.divide(BigInteger.valueOf(24));
			Boolean flag = (ans.compareTo(mod) >= 0);
			ans = ans.mod(mod);
			System.out.printf("Case %d: ", ca);
			if (flag) {
				BigInteger tmp = ans.divide(BigInteger.TEN);
				int cnt = 14;
				while (!tmp.equals(BigInteger.ZERO)) {
					-- cnt;
					tmp = tmp.divide(BigInteger.TEN);
				}
				for (int i = 0; i < cnt; ++ i)
					System.out.print(0);
			}
			System.out.println(ans);
		}
	}
}

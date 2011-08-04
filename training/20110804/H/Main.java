import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) throws Exception {
		BigInteger ans[] = new BigInteger[201];
		ans[0] = ans[1] = BigInteger.ONE;
		for (int i = 2; i < 110; ++ i) {
			ans[i] = BigInteger.ZERO;
			for (int j = 0; j < i; ++ j)
				ans[i] = ans[i].add(ans[j].multiply(ans[i - j - 1]));
		}
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		int n = cin.nextInt();
		for (int i = 0; i < 2 * n - 1; ++ i) {
			if ((i & 1) == 1) System.out.println(0);
			else System.out.println(ans[i >> 1]);
		}
	}
}

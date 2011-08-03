import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) throws Exception {
		BigInteger c, ans = BigInteger.ZERO;
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		while (cin.hasNextBigInteger()) {
			c = cin.nextBigInteger();
			ans = ans.add(c);
		}
		System.out.println(ans);
	}
}

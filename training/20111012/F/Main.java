import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static BigInteger ten = BigInteger.TEN;
	public static BigInteger one = BigInteger.ONE;
	public static BigInteger zero = BigInteger.ZERO;
	public static void main(String[] args) {
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		int tests = cin.nextInt();
		for (int ca = 1; ca <= tests; ++ ca) {
			BigInteger a = new BigInteger(cin.next());
			BigInteger a2 = zero, a1 = zero, a3 = zero;
			BigInteger b = new BigInteger(cin.next());
			BigInteger h = one, t = one;
			while (b.compareTo(h) >= 0) h = h.multiply(ten);

			BigInteger tmp = one;
			while (a.compareTo(tmp) >= 0) tmp = tmp.multiply(ten);

			BigInteger ans = b.multiply(tmp).subtract(a);
			
			if (b.equals(zero)) {
				ans = ten.subtract(a.mod(ten));
				if (a.equals(zero)) ans = zero;
				while (!a.equals(zero)) {
					if (a.mod(ten).equals(zero)) {
						ans = zero;
						break;
					}
					a = a.divide(ten);
				}
			} else {
				if (b.compareTo(a) >= 0) ans = b.subtract(a);
				for (int time = 0; time < 11; ++ time) {
					a2 = a.mod(h); a1 = a.subtract(a2);
					a3 = a2.mod(t); a2 = a2.subtract(a3);
					int x = b.compareTo(a2);
					BigInteger res;
					if (x == 0) res = zero;
					else if (x == -1) res = (h.add(b)).subtract(a2.add(a3));
					else res = b.subtract(a2.add(a3));
					if (res.compareTo(ans) < 0) ans = res;
					h = h.multiply(ten); t = t.multiply(ten); b = b.multiply(ten);
				}
			}
			System.out.printf("Case #%d: ", ca);
			System.out.println(ans);
		}
	}
}


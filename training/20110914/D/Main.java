import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static int N;
	static BigInteger ZERO = BigInteger.ZERO;
	static BigInteger ONE = BigInteger.ONE;
	static BigInteger[][] a = new BigInteger[110][110];
	static BigInteger[] b = new BigInteger[110];
	static BigInteger ansA[] = new BigInteger[110];
	static BigInteger ansB[] = new BigInteger[110];
//	static int p[] = new int[110];

	public static void swapRows(int A, int B) {
		BigInteger tmp;
		for (int i = 0; i < N; ++ i) {
			tmp = a[A][i];
			a[A][i] = a[B][i];
			a[B][i] = tmp;
		}
		tmp = b[A]; b[A] = b[B]; b[B] = tmp;
//		int c = p[A]; p[A] = p[B]; p[B] = c;
	}

	public static Boolean AllZERO(int x) {
		for (int i = 0; i < N; ++ i)
			if (!a[x][i].equals(ZERO))
				return false;
		return true;
	}

	public static Boolean Gauss() {
//		for (int i = 0; i < N; ++ i) p[i] = i;

		for (int i = 0; i < N; ++ i) {
			if (AllZERO(i) && !b[i].equals(ZERO)) return false;
			if (a[i][i].equals(ZERO)) {
				for (int j = i + 1; j < N; ++ j)
					if (!a[j][i].equals(ZERO)) {
						swapRows(i, j);
						break;
					}
			}
			if (AllZERO(i) && !b[i].equals(ZERO)) return false;

			if (a[i][i].equals(ZERO)) continue;

			for (int j = i + 1; j < N; ++ j) {
				if (a[j][i].equals(ZERO)) continue;
				BigInteger LCM = (a[i][i].multiply(a[j][i])).divide(a[i][i].gcd(a[j][i]));
				BigInteger Mi = LCM.divide(a[i][i]);
				BigInteger Mj = LCM.divide(a[j][i]);
				for (int k = i; k < N; ++ k) {
					a[i][k] = a[i][k].multiply(Mi);
					a[j][k] = a[i][k].subtract(a[j][k].multiply(Mj));
				}
				b[i] = b[i].multiply(Mi); b[j] = b[i].subtract(b[j].multiply(Mj));
			}
		}

		for (int i = N - 1; i >= 0; -- i) {
			if (AllZERO(i)) {
				if (!b[i].equals(ZERO)) return false;
//				ansA[p[i]] = ONE; ansB[p[i]] = ONE;
				ansA[i] = ONE; ansB[i] = ONE;
				continue;
			}
			BigInteger x = b[i], y = ONE;
			for (int j = i + 1; j < N; ++ j)
				if (!a[i][j].equals(ZERO)) {
					BigInteger n = ansA[j].multiply(a[i][j]);
					BigInteger m = ansB[j];
					x = (x.multiply(m)).subtract(y.multiply(n));
					y = y.multiply(m);
					n = x.gcd(y); x = x.divide(n); y = y.divide(n);
				}

			if (a[i][i].equals(ZERO)) {
				if (!x.equals(ZERO)) return false;
				ansA[i] = ONE;
				ansB[i] = ONE;
				continue;
			}

			y = y.multiply(a[i][i]);
			BigInteger n = x.gcd(y); x = x.divide(n); y = y.divide(n);
			if (y.compareTo(ZERO) == -1) {
				y = ZERO.subtract(y);
				x =	ZERO.subtract(x);
			}
			ansA[i] = x; ansB[i] = y;
		}

		return true;
	}

	public static void main(String[] args) {
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		while (cin.hasNext()) {
			N = cin.nextInt();
			for (int i = 0; i < N; ++ i) {
				for (int j = 0; j < N; ++ j) {
					BigInteger tmp = new BigInteger(cin.next());
					a[i][j] = tmp;
				}
				BigInteger tmp = new BigInteger(cin.next());
				b[i] = tmp;
			}
			if (!Gauss()) System.out.println("No solution.");
			else {
				for (int i = 0; i < N; ++ i) {
					System.out.print(ansA[i]);
					if (!ansA[i].equals(ZERO) && !ansB[i].equals(ONE)) {
						System.out.print("/");
						System.out.print(ansB[i]);
					}
					System.out.println("");
				}
			}
			System.out.println("");
		}
	}
}


import java.io.*;
import java.util.*;
import java.math.*;

public class Main{
	public static void main(String[] args) throws Exception {
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		while (cin.hasNextInt()) {
			int n = cin.nextInt();
			if (n == -1) break;
			BigInteger ans = BigInteger.valueOf(2);
			for (int i = 2; i < n; ++ i)
				ans = ans.multiply(BigInteger.valueOf(i));
			System.out.print("N=");
			System.out.print(n);
			System.out.println(":");
			System.out.println(ans);
		}
	}
}

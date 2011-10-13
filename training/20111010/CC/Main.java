import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

public class Main{
	public static BigInteger f[] = new BigInteger[100];

    public static void main(String args[]) {
        Scanner cin = new Scanner(new BufferedInputStream(System.in));
        String s;

		for (int i = 0; i < 10; ++i) f[i] = BigInteger.ONE;

      	while (cin.hasNext()) {
      		s = cin.next();
      		
      		if (s.length() == 3) {
      			int x = s.charAt(0) - 'A', y = s.charAt(2) - 'A';
      			f[x] = f[y];
      		} 
      		else {
      			int x = s.charAt(0) - 'A', y = s.charAt(3) - 'A';
      			
      			if (s.charAt(1) == '+') f[x] = f[x].add(f[y]);
      			else f[x] = f[x].multiply(f[y]);
      		}
      	}
      	
      	for (int i = 0; i < 10; ++i) System.out.println(f[i]);
    }
}

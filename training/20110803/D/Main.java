import java.io.*;
import java.math.*;
import java.util.*;

public class Main{
	static final int maxn = 1000;
	static boolean flag[] = new boolean[maxn];
	
	static BigInteger TEN = BigInteger.valueOf(10);
	static BigInteger ONE = BigInteger.valueOf(1);
	
	static void check(int a,int b) {
		for (int i=1;i<=100;i++) flag[i]=false;
		
		BigInteger A=BigInteger.valueOf(a);
		BigInteger B=BigInteger.valueOf(b);
		
		int now=b%(10*a-1),cnt=0; 
		b=(b*a)%(10*a-1); a=10*a-1;
		flag[now]=true;
		while (true) {
			now=(now*10)%a; cnt++;
			if (flag[now]) {
				System.out.printf("0");	break;
			}
			
			flag[now]=true;
			
			if (now==b) {
				BigInteger x=(TEN.pow(cnt)).subtract(A);
				x=x.multiply(B);
				x=x.divide(BigInteger.valueOf(a));
				
				BigInteger y=TEN.pow(cnt-1);
				
				if (x.compareTo(y)>=0) {
					x=x.multiply(TEN);
					x=x.add(B);
				
					System.out.print(x);
				
					break;
				}
			}
		}
	}
	
	public static void main(String[] args){
		for (int i=1;i<=9;i++) {
			System.out.printf("{");
			
			for (int j=1;j<=9;j++) {
				System.out.printf("\""); check(i,j); System.out.printf("\"");	
				if (j<9) System.out.printf(",");
			}
			
			System.out.printf("},\n");
		}
	} 
	
}

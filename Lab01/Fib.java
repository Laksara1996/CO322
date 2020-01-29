
import java.util.concurrent.TimeUnit;


class Fib {

    public static int fib_r(int x) {
	if(x <= 2) return 1;
	return fib_r(x-1) + fib_r(x-2);
    }

    public static int fib_i(int x) {
	int a=1, b=1, fib=1, i=2;
	while(i<x) {
	    fib = a + b;
	    a = b;
	    b = fib;
	    i+=1;
	}
	return fib;
    }


    public static void main(String [] args) {
		
		long startTime = System.nanoTime();
		
		int x = 1;
		//System.out.println("Fib of " + x + " = " + fib_r(x));
		System.out.println("Fib of " + x + " = " + fib_i(x));
    
		long endTime = System.nanoTime();
		
		System.out.println((endTime-startTime));
    }
}

	

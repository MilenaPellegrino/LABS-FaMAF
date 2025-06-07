package subscription;

public final class Counter{
	static private int value = 0;
	
	public void increment(){
		value = value + 1;
	}
	public void printValue(){
		System.out.println(value);
	}

	public static void main(String[] args) {
	Counter c1 = new Counter();
	Counter c2 = new Counter();
	
	c1.increment();
	c2.printValue();
	}	
}

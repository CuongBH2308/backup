package item17;

import java.util.Date;

public class OverrideInConstructor {

	static class Base {
		public Base() {
			// Two things to notice:
			// 1. It is calling the function from derived class
			// 2. It is invalid as the derived class hasn't been initialized properly yet
			// In C++, it should calling the one in Base class as the vptr havn't yet setup
			this.overrideMe();
		}
		public void overrideMe() {
			System.out.println("Base::overrideMe");
		}
	}
	
	static class Derived extends Base {
		private final Date date;
		public Derived() {
			date = new Date();
		}
		public void overrideMe() {
			System.out.println("Derived::overrideMe");
			System.out.println(date);
		}
			
	}
	
	public static void main(String[] args) {
		Derived d = new Derived();
	}

}

package chapter2_jvm.mm;

// -XX:+PrintTLAB
public class TLAB {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Hello");
		
		new Thread(new Runnable() {
			public void run() {
				System.out.println("Hello");
			}
			
		}).start();
	}

}


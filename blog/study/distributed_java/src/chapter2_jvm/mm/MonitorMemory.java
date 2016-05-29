package chapter2_jvm.mm;

// -Xms40M -Xmx40M -Xmn16M -verbose:gc -XX:+PrintGCDetails  -XX:MaxPermSize=128m
// 1. use JConsole
// 2. use JVisualVM
public class MonitorMemory {

	public static void main(String[] args) throws InterruptedException {
		
		byte[] m = new byte[1024*1024];
		int i = 0;
		while(true) {
			System.out.println(String.format("%d M memory allocated", ++i));
			Thread.sleep(1000);
			byte[] x = new byte[1024*1024];
		}

	}

}

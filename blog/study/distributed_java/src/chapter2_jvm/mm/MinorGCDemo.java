package chapter2_jvm.mm;

// -Xms40M -Xmx40M -Xmn16M -verbose:gc -XX:+PrintGCDetails  -XX:MaxPermSize=128m
// -XX:+UseSerialGC -XX:+PrintGCApplicationStoppedTime -Xms40M -Xmx40M -Xmn16M -verbose:gc -XX:+PrintGCDetails  -XX:MaxPermSize=128m

/*
1 M memory allocated in young generation
2 M memory allocated in young generation
3 M memory allocated in young generation
4 M memory allocated in young generation
5 M memory allocated in young generation
6 M memory allocated in young generation
7 M memory allocated in young generation
8 M memory allocated in young generation
9 M memory allocated in young generation
10 M memory allocated in young generation
[GC (Allocation Failure) [PSYoungGen: 11525K->1712K(14336K)] 11525K->1720K(38912K), 0.0017023 secs] [Times: user=0.00 sys=0.00, real=0.00 secs] 
11 M memory allocated in young generation
12 M memory allocated in young generation
Heap
 PSYoungGen      total 14336K, used 5145K [0x00000000ff000000, 0x0000000100000000, 0x0000000100000000)
  eden space 12288K, 27% used [0x00000000ff000000,0x00000000ff35a4d0,0x00000000ffc00000)
  from space 2048K, 83% used [0x00000000ffc00000,0x00000000ffdac050,0x00000000ffe00000)
  to   space 2048K, 0% used [0x00000000ffe00000,0x00000000ffe00000,0x0000000100000000)
 ParOldGen       total 24576K, used 8K [0x00000000fd800000, 0x00000000ff000000, 0x00000000ff000000)
  object space 24576K, 0% used [0x00000000fd800000,0x00000000fd802000,0x00000000ff000000)
 Metaspace       used 2660K, capacity 4486K, committed 4864K, reserved 1056768K
  class space    used 293K, capacity 386K, committed 512K, reserved 1048576K
Java HotSpot(TM) 64-Bit Server VM warning: ignoring option MaxPermSize=128m; support was removed in 8.0
*/


public class MinorGCDemo {
	public static void main(String[] args) throws Exception {
		MemoryOject object = new MemoryOject(1);
		
		for(int i = 2; i < 15; i++) {
        	System.out.println(String.format("%d M memory allocated in young generation", i));
			new MemoryOject(1);
			Thread.sleep(1000);
		}
	}
	
	static class MemoryOject {
		private byte[] bytes;
		public MemoryOject(int nMeta) {
			this.bytes = new byte[nMeta*1024*1024];
		}
	}
}
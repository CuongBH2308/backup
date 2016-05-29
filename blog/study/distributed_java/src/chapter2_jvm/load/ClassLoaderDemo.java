/*
 * 1. ClassLoaders are organized in a tree-like structure, whenever you load a class, jvm will try 
 * to load it first in its parent classloader
 * 2. User-Defined ClassLoader -> System ClassLoader -> ExtClassLoader -> Bootstrap ClassLoader (null, as it is native)
 * 
 * Output:
 * sun.misc.Launcher$AppClassLoader@73d16e93
 * sun.misc.Launcher$ExtClassLoader@15db9742
 * null
 */
package chapter2_jvm.load;

public class ClassLoaderDemo {
	public static void main(String[] args) throws Exception {
		System.out.println(ClassLoaderDemo.class.getClassLoader());
		System.out.println(ClassLoaderDemo.class.getClassLoader().getParent());
		System.out.println(ClassLoaderDemo.class.getClassLoader().getParent().getParent());
		
		System.out.println(String.class.getClassLoader());
		System.out.println(com.sun.nio.zipfs.ZipDirectoryStream.class.getClassLoader()); // jar tf *.jar to list contents in a jar file, or you can view it from eclipse explorer
	}

}

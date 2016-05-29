##Conclusion:
* ant's javac task support incremental build out of the box
* but it only rebuild files if it is .java file has been updated
* It doesn't know the dependencies between class files, hence can't automatically recompile dependent java files.
* javac command will always recompile the files, it is javac ant task does the check

## Try it
> ant compile
> 	[javac] Compiling 3 source files to D:\Source\GitHub\blog\arena\ant\incrementalbuild\build

> touch src\Utils.java
> ant compile
> 	[javac] Compiling 1 source file to D:\Source\GitHub\blog\arena\ant\incrementalbuild\build


In theory, Hello.java uses Utils.java, recompile Utils.java should cause recompile of Hello.java, but it havn't. The reason is probably they are not enough information in class file to detertime the dependency, while in C++, you have header include and .d dependency file for gmake to decide.
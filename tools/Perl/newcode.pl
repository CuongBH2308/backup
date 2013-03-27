#
# This script is to create startup code for different languages
# so you can quickly start your programming.
#

use strict;
use warnings;
use Getopt::Long;

sub help()
{
print <<EOF;
Usage:
	newcode.pl <filename> [-type|t filetype]
Examples:
	newcode.pl examples.cpp
	newcode.pl examples.java
	newcode.pl examples.xml -type ant
	newcode.pl makefile -type mk
EOF
exit;
}

sub createCpp($$)
{
my $fileHandle = $_[0];
print $fileHandle <<EOF;
#include <iostream>
using namespace std;
int main(int argc, const char* argv[])
{
	cout << "Hello, World" << endl;
	return 0;
}
EOF
}

sub createJava($$)
{
my ($fileHandle, $className) = @_;
print $fileHandle <<EOF;
import java.lang.Math;
class $className
{
	public static void main(String[] args)
	{
		System.out.println("Hello, World!");
	}
}
EOF
}

sub createCSharp($$)
{
my ($fileHandle, $className) = @_;
print $fileHandle <<EOF;
using System;
class $className
{
	public static void Main(string[] args)
	{
		System.Console.WriteLine("Hello, World!");
	}
}
EOF
}

sub createPerl($$)
{
my $fileHandle = $_[0];
print $fileHandle <<EOF;
use strict;
use warnings;

sub main()
{
	printf "Hello, World!\\n";
}

main();
EOF
}

sub createBatch($$)
{
my $fileHandle = $_[0];
print $fileHandle <<EOF;
\@echo off
echo Hello, World
EOF
}

sub createBash($$)
{
my $fileHandle = $_[0];
print $fileHandle <<EOF;
echo Hello, World
EOF
}

sub createMake($$)
{
my $fileHandle = $_[0];
print $fileHandle <<EOF;
# macro defintions
CC = cl
CFLAGS = /nologo /EHsc /Zi
INCLUDEPATH = \$(OPENCV_SDK_DIR)\\include
LIBPATH = \$(OPENCV_SDK_DIR)\\x86\\vc10\\lib
LIBS = opencv_core231.lib opencv_highgui231.lib opencv_imgproc231.lib opencv_objdetect231.lib
#CFLAGS = /nologo /EHsc 

# target definitions
default: BlurCanny.exe

all: BlurCanny.exe FaceDetect.exe

BlurCanny.exe: BlurCanny.cpp
	cl BlurCanny.cpp \$(CFLAGS) /I \$(INCLUDEPATH) /link /LIBPATH:\$(LIBPATH) \$(LIBS)
	
FaceDetect.exe: FaceDetect.cpp
	cl FaceDetect.cpp \$(CFLAGS) /I \$(INCLUDEPATH) /link /LIBPATH:\$(LIBPATH) \$(LIBS)
	
clean: 
	echo "clean"
	
EOF
}

sub createAnt($$)
{
my ($fileHandle, $fileNameNoExt) = @_;
print $fileHandle <<EOF;
<?xml version="1.0" encoding="ISO-8859-1"?>
<project name="$fileNameNoExt" basedir="." default="jar">
    <property name="src.dir" value="src"/>
    <property name="classes.dir" value="classes"/>
	
    <target name="clean" description="Delete all generated files">
        <delete failonerror="false" includeEmptyDirs="true">
            <fileset dir="." includes="\${ant.project.name}.jar"/>
            <fileset dir="\${classes.dir}"/>
        </delete>
    </target>

    <target name="compile" description="Compiles the Task">
        <mkdir dir="\${classes.dir}"/>
        <javac srcdir="\${src.dir}" destdir="\${classes.dir}" classpath="ant-testutil.jar"/>
    </target>

    <target name="jar" description="JARs the Task" depends="compile">
        <jar destfile="\${ant.project.name}.jar" basedir="\${classes.dir}"/>
    </target>
	
</project>
EOF
}


sub initCreators()
{
	my %mapType2Creator;
	
	$mapType2Creator{"cpp"} = \&createCpp;
	$mapType2Creator{"java"} = \&createJava;
	$mapType2Creator{"cs"} = \&createCSharp;
	$mapType2Creator{"bat"} = \&createBatch;
	$mapType2Creator{"sh"} = \&createBash;
	$mapType2Creator{"mk"} = \&createMake;
	$mapType2Creator{"ant"} = \&createAnt;
	$mapType2Creator{"xml"} = \&createAnt; # xml default to ant for now
	
	return %mapType2Creator;
}

sub main()
{
	help() if(@ARGV == 0);
	
	my $help=0;
	my $fileType;
	GetOptions ('type|t' => \$fileType, 'help|?' => \$help);
	help() if($help == 1);
	
	my $fileName = $ARGV[0];
	if(!defined $fileType)
	{
		$fileName =~ /.*\.([^.]*)/;
		$fileType = $1;
		if(!defined $fileType)
		{
			print "Error: File type unknown, please either provide a file name extension, or specify it use -type option\n";
			help();
		}
	}
	
	#print $fileType, "\n";
		
	my %mapType2Creator = initCreators();
	if(!exists $mapType2Creator{$fileType})
	{
		print "Error: File type: \"$fileType\" not supported yet\n";
		exit;
	}
	
	(my $fileNameNoExt = $fileName) =~ s/\.[^.]*//;
	#print $fileNameNoExt, "\n";
	
	my $fileHandle;
	open $fileHandle, ">", $fileName;
	$mapType2Creator{$fileType}->($fileHandle, $fileNameNoExt);
	close $fileHandle;
	
	print "$fileName was created with type $fileType\n";
	
}


main();

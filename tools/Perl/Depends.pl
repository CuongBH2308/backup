#####
#
# Depends.pl
# Show a dll's dependents and dependencies modules. Dependents modules are from the same folder (15s for Inventor DLLs)
#
# Depends.pl <DLLName>
#
# Author: Baiyan Huang
# Date: 4/2/2010
#
# Note: You need to have vs2008 installed
#
#####

use strict;
use Cwd;
use File::Basename;
use File::Spec;


my $Dll = $ARGV[0];

# 1. Get DLL name and dir
my $DllName = &basename($Dll);
my $DirName;
if($Dll =~ /^\s*[A-Za-z]:/)
{
	$DirName = &dirname($Dll);
	#print $DirName, "\n";
}
else
{
	$DirName = cwd;
}

die "DLL not exist!!!\n" if(! -e ($DirName . "\\" . $DllName)) ;


# 2. Get Dependencies
my $CommonTools = $ENV{"VS90COMNTOOLS"};
my $DumpBin = File::Spec->catfile($CommonTools, "../../VC/bin", "dumpbin.exe");
my $DependInfo = `"$DumpBin" /dependents "$Dll"`;
my ($DirectDependencies, $DelayLoadedDependencies) = split /Image has the following delay load dependencies:/, $DependInfo;
my (undef, $DirectDependencies) = split /Image has the following dependencies:/, $DirectDependencies;
my @DirectDependencies = $DirectDependencies =~ /\w+\.dll/ig;
my @DelayLoadedDependencies = $DelayLoadedDependencies =~ /\b\w+\.dll\b/ig;

# 3. Get Dependents
my @DirectDependents;
my @DelayLoadedDependents;
my $DirCmd = "dir /s /b " . '"' . $DirName . "\\*.dll" . '"' . " " . '"' . $DirName . "\\*.exe" . '"';
#print $DirCmd;
my @AllDLLs = `$DirCmd`;
#print @AllDLLs;
chomp @AllDLLs;
my $DllNamePattern = $DllName;
$DllNamePattern =~ s/\./\\\./;
foreach my $EachDLL (@AllDLLs)
{
	next if($EachDLL =~ /$DllNamePattern$/i);
	$DependInfo = `"$DumpBin" /dependents "$EachDLL"`;
	($DirectDependencies, $DelayLoadedDependencies) = split /Image has the following delay load dependencies:/, $DependInfo;
	if($DirectDependencies =~ /\b$DllNamePattern\b/i)
	{
		push @DirectDependents, &basename($EachDLL);
	}
	elsif($DelayLoadedDependencies =~ /\b$DllNamePattern\b/i)
	{
		push @DelayLoadedDependents, &basename($EachDLL);
	}
}

# 4 Compose the output
sub case_insensitive { "\L$a" cmp "\L$b" }

my @LeftColumn;
push @LeftColumn, "Direct";
push @LeftColumn, "----------";
push @LeftColumn, sort case_insensitive @DirectDependents;

if(@DelayLoadedDependents)
{
	push @LeftColumn, "     ";
	push @LeftColumn, "Delayload";
	push @LeftColumn, "----------";
	push @LeftColumn, sort case_insensitive @DelayLoadedDependents;
}


my @RightColumn;
push @RightColumn, "Direct";
push @RightColumn, "----------";
push @RightColumn, sort case_insensitive @DirectDependencies;

if(@DelayLoadedDependencies)
{
	push @RightColumn, "     ";
	push @RightColumn, "Delayload";
	push @RightColumn, "----------";
	push @RightColumn, sort case_insensitive @DelayLoadedDependencies;
}

my $Min = $#LeftColumn < $#RightColumn ? $#LeftColumn : $#RightColumn;
my $Pos = int($Min/2);

print "\n";
my $i = 0;
while(1)
{
	$i++;
	my $left = shift @LeftColumn;
	my $right = shift @RightColumn;
	last unless($left || $right);
	
	if($left && $right)
	{
		if($i == $Pos)
		{
			printf "%-25s" . "%-25s" . "%-25s" . "\n", $left, "=== " . $DllName . " ===>", $right;
		}
		else
		{
			printf "%-25s" . " " x 25 . "%-25s" . "\n", $left, $right;
		}
	}
	if($left && !$right)
	{
		printf "%-25s" . " " x 25  . "\n", $left;
	}
	if(!$left && $right)
	{
		printf " " x 25 . " " x 25 . "%-25s" . "\n", $right;
	}
}



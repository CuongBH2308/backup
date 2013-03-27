#####
#
# Make the target script independent of the various costom modules it used - identify the subroutines and classes used and copy them into a single script
#
# Author; Baiyan Huang
# Date: 1/23/2009
#
# Usage:
# PublishScript.pl <ScriptName>
# 
# Steps:
# 1. Get the custom modules and parse its symbols, recusively
# 2. Collect variables and subs that used in the script, recursively.
# 3. Copy the sub and variables that used from the modules to the script
#
# Notes:
# 1. Assumptions:
# 	a. Target script and custom modules are in the same directory of this script
#	b.  Each function call start with & and has "()"
#	c.  Global variables are declared by "my"
#	d. If a module has a subroutine named "new", it is a class
#	e. Custom modules always "use" after standard modules.
# 2. If a class is used, we will copy the entire class.
#
# TODO:
# 1. Pragma: use strict, use diagnostics, use warning....
#
#####

use strict;
use File::Basename;
# Custom modules
BEGIN{push @INC, &dirname($0);}
use Utils::Basic;

# Get full script name
my $ScriptName = $ARGV[0];
my $CurDir = &dirname($0);
my $Script = $CurDir . "\\" . $ScriptName;

# 1. Get the custom modules and parse its symbols, recusively
&Report("\n>>>1. Get the custom modules and parse its symbols...\n");
my %StandardModules;
my %CustomModules;

&GetUsedModules($Script);

&Report("Standard Modules:\n\t");
&Report(join "\n\t", keys %StandardModules);
&Report("\nCustom Modules:\n\t");
&Report(join "\n\t", keys %CustomModules);
&Report("\n");


# Get Symbols from modules
my %PackageSymbols; # <PackageName, @( <Var, @Variables(Variable, used)>, <SubName, @Subs(Sub, Used)>, IsClass)>
$PackageSymbols{"main"} = &NewSymbols(); # default main package

foreach my $EachModule (keys %CustomModules)
{
	open MODULE_FILE, $EachModule or die "Can't open file $EachModule: $!";
	my $PackageName = "main";
	my @FileContents = <MODULE_FILE>;
	my $CurlLevel = 0;
	for(my $i = 0; $i <= $#FileContents; $i++)
	{
		$_ = $FileContents[$i];
		
		if(/^\s*?package\s*?(\w+);/)
		{
			$PackageName = $1;
			$PackageSymbols{$PackageName} = &NewSymbols();
			next;
		}
		# Variables
		if(/^\s*?my\s+[\$\@\%](\w+)\s*(=\s*(.*))?;/)
		{
			#print "\n$1\n";
			if($CurlLevel == 0)
			{
				my @Vars = ($_, 0);
				${@{$PackageSymbols{$PackageName}}[0]}{$1} = \@Vars;
			}
		}
		# Subs
		if(/^\s*?sub\s+(\w+)(\((.*?)\))?/)
		{
			#print "$1($3)\n";
			my $SubName = $1;
			#print "$1\n";
			my $Paras = $3;
			my $SubDef = $_;
			
			if($SubName eq "new") # It is a class if the module includes a sub routine named "new"
			{
				@{$PackageSymbols{$PackageName}}[2] = 1;
			}
			
			my $StartNum = /{/g;	
			my $EndNum = /}/g;
			$CurlLevel = $StartNum - $EndNum;
			if($CurlLevel == 0 && $StartNum != 0) # End function;
			{
				my @Vars = ($SubDef, 0);
				${@{$PackageSymbols{$PackageName}}[1]}{$SubName} = \@Vars;
				next;
			}
			
			# Get the first curl
			while($CurlLevel == 0)
			{
				my $Line = $FileContents[++$i];
				$SubDef .= $Line;
				
				my $StartNum = $Line =~ /{/g;
				my $EndNum = $Line =~ /}/g;
				$CurlLevel = $StartNum - $EndNum;
			}
			
			# Get the last curl
			while($CurlLevel != 0)
			{
				my $Line = $FileContents[++$i];
				$SubDef .= $Line;
				
				my $StartNum = $Line =~ /{/g;
				my $EndNum = $Line =~ /}/g;
				$CurlLevel = $CurlLevel + $StartNum - $EndNum;
			}
			
			my @Vars = ($SubDef, 0);
			${@{$PackageSymbols{$PackageName}}[1]}{$SubName} = \@Vars;
		}
	}
	close MODULE_FILE;
}
#&DumpSymbolMap(0);

# 2. Parse global variables and subs that used in the script
&Report("\n>>>2. Parse global variables and subs that used in the script...\n");
open THIS_SCRIPT, $Script or die "Can't open file $Script: $!";
my @ScriptCode = <THIS_SCRIPT>;
close THIS_SCRIPT;

my $Code = join "", @ScriptCode;
&GetUsedSymbols($Code, "main"); # Recursively

# We treat class in different ways:
foreach my $EachPackage (keys %PackageSymbols)
{
	if(@{$PackageSymbols{$EachPackage}}[2]) # Is a class
	{
		my $ClassCode;
		foreach my $SubName (keys %{@{$PackageSymbols{$EachPackage}}[1]})
		{
			$ClassCode .= @{${@{$PackageSymbols{$EachPackage}}[1]}{$SubName}}[0];
		}
		&GetUsedSymbols($ClassCode, $EachPackage); # Recursively
	}
}

&DumpSymbolMap(1);

# 3. Copy the sub and variables that used from the modules to the script
&Report("\n>>>3. Copy the sub and variables that used from the modules to the script...\n");
my $ScriptCodeStr;
my $FirstUse = 0;
for(my $i = 0; $i <= $#ScriptCode; $i++)
{
	# Remove the use of custom modules.
	my $CurLine = $ScriptCode[$i];
	if($CurLine =~ /^\s*use\s+[\w:]+\s*;/)
	{
		$CurLine = undef;
		$FirstUse++;
	}
	# First use statement
	if($FirstUse == 1)
	{
		delete $StandardModules{"strict"};
		$ScriptCodeStr = $ScriptCodeStr . "use strict;\n";
		foreach (keys %StandardModules)
		{
			$ScriptCodeStr = $ScriptCodeStr . "use $_;\n";
		}
		$FirstUse++;
	}
	# Remove:
	# BEGIN{push @INC, &dirname($0);}
	if($CurLine =~ /^\s*BEGIN\s*\{\s*push\s*\@INC\s*,\s*/)
	{
		$CurLine = undef;
	}
	$ScriptCodeStr .= $CurLine;
}

# Main package should go first
&GetFromPackage("main");
delete $PackageSymbols{"main"};
foreach my $EachPackage (keys %PackageSymbols)
{
	&GetFromPackage($EachPackage);
}

#print $ScriptCodeStr;
my $PublishedDir = $CurDir . "\\" . "Published";
unless(-e $PublishedDir)
{
	mkdir $PublishedDir or die "Can't create directory $PublishedDir";
}
my $Script = $PublishedDir . "\\" . $ScriptName;
open OUTPUT_SCRIPT, ">", $Script or die "Can't Create file $Script: $!";
print OUTPUT_SCRIPT $ScriptCodeStr;
close OUTPUT_SCRIPT;
&Report("\t$Script\n");

#**********************************************************************Functions*********************************************************************
sub NewSymbols()
{
	my %Vars;
	my %Subs;
	
	my @Symbols;
	push @Symbols, \%Vars;
	push @Symbols, \%Subs;
	
	# Not a class as default.
	push @Symbols, 0;
	
	return \@Symbols;
}

# Recursively get modules
sub GetUsedModules($)
{
	my $File = $_[0];
	open THIS_FILE, $File or "Can't open file $File: $!";
	my $StartCustomModule = 0;
	foreach(<THIS_FILE>)
	{
		# BEGIN{push @INC, &dirname($0);}
		if(/^\s*BEGIN\s*?{/)
		{
			$StartCustomModule = 1;
		}
		if(/^\s*use\s+(.*?);/)
		{
			my $ModlueName = $1;
			if($StartCustomModule)
			{
				$ModlueName =~ s/::/\\/g;
				$ModlueName = $CurDir . "\\". $ModlueName . ".pm";
				if(-f $ModlueName)
				{
					if(!exists $CustomModules{$ModlueName})
					{
						$CustomModules{$ModlueName} = 1;
						&GetUsedModules($ModlueName);
					}
				}
			}
			else
			{
				$StandardModules{$ModlueName} = 1;
			}
		}
	}
	close THIS_FILE;
}

# Get symbols that used in this script
sub GetUsedSymbols($$)
{
	my $Code = $_[0];
	my $Package = $_[1];
	my @Subs = $Code =~ /(?<=&)((?:\w*::)?\w+)(?=\s*\()/g;
	@Subs = &UniquelizeList(@Subs);
	#print join "\n", @Subs;
	foreach my $EachSub (@Subs)
	{
		my ($PackageName, $SubName);
		my @SubElements = split /::/, $EachSub;
		if(@SubElements == 2)
		{
			if("" eq $SubElements[0]) # No package name before ::, it belongs to main
			{
				$SubElements[0] = "main";
			}
			($PackageName, $SubName) = @SubElements;
		}
		else
		{
			($PackageName, $SubName) = ($Package, @SubElements[0]);
		}
		if(exists ${@{$PackageSymbols{$PackageName}}[1]}{$SubName})
		{
			#&Trace($SubName);
			if(@{${@{$PackageSymbols{$PackageName}}[1]}{$SubName}}[1] == 0)
			{
				@{${@{$PackageSymbols{$PackageName}}[1]}{$SubName}}[1] = 1;
				&GetUsedSymbols(@{${@{$PackageSymbols{$PackageName}}[1]}{$SubName}}[0], $PackageName);
			}
		}
	}
	my @Vars = $Code =~ /(?<=[\$\@\%])\w+/g;
	@Vars = &UniquelizeList(@Vars);
	foreach my $Var (@Vars)
	{
		#&Trace($Package, "::", $Var);
		if(exists ${@{$PackageSymbols{$Package}}[0]}{$Var})
		{
			@{${@{$PackageSymbols{$Package}}[0]}{$Var}}[1] = 1;
		}
	}
	#print join "\n", @Vars;
}

sub GetFromPackage($)
{
	my $EachPackage = $_[0];
	$ScriptCodeStr .= "\n";
	my $Comment = "#" . "*" x 40 . $EachPackage . "*" x 40 . "\n";
	$ScriptCodeStr .= $Comment;
	$ScriptCodeStr .= "package $EachPackage;\n" unless($EachPackage eq "main");
	my $IsClass = @{$PackageSymbols{$EachPackage}}[2];
	foreach(sort keys %{@{$PackageSymbols{$EachPackage}}[0]})
	{
		if($IsClass || @{${@{$PackageSymbols{$EachPackage}}[0]}{$_}}[1])
		{
			$ScriptCodeStr .= @{${@{$PackageSymbols{$EachPackage}}[0]}{$_}}[0];
			$ScriptCodeStr .= "\n";
		}
	}
	
	foreach(sort keys %{@{$PackageSymbols{$EachPackage}}[1]})
	{
		if($IsClass || @{${@{$PackageSymbols{$EachPackage}}[1]}{$_}}[1])
		{
			$ScriptCodeStr .= @{${@{$PackageSymbols{$EachPackage}}[1]}{$_}}[0];
			$ScriptCodeStr .= "\n";
		}
	}
}
sub DumpSymbolMap($)
{
	print "\n";
	my $ShowUsedOnly = $_[0];
	foreach my $EachPackage (keys %PackageSymbols)
	{
		my $IsClass = @{$PackageSymbols{$EachPackage}}[2];
		print $EachPackage, "\n";
		print "*" x 40, "\n";
		print "Vars:\n";
		foreach(sort keys %{@{$PackageSymbols{$EachPackage}}[0]})
		{
			if($ShowUsedOnly)
			{
				print "\t", @{${@{$PackageSymbols{$EachPackage}}[0]}{$_}}[0] if($IsClass || @{${@{$PackageSymbols{$EachPackage}}[0]}{$_}}[1])
			}
			else
			{
				print "\t", @{${@{$PackageSymbols{$EachPackage}}[0]}{$_}}[0];
			}
		}
		print "Subs:\n";
		foreach(sort keys %{@{$PackageSymbols{$EachPackage}}[1]})
		{
			if($ShowUsedOnly)
			{
				print "\t", $_, "\n"  if($IsClass || @{${@{$PackageSymbols{$EachPackage}}[1]}{$_}}[1])
			}
			else
			{
				print "\t", $_, "\n";
			}
		}
		
		print "\n";
	}
}
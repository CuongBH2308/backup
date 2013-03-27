#####
# 
# Find out problematic static interfaces used in InvSrc
# (IFxTearOffInterface need to be considered as well)
#
# Steps
# 1. Go through R:\ and find out all static/tearoff interfaces. (public RSeStaticInterface; public IFxStaticInterface)
# 2. Go through R:\ again, and find out the interface's implementation and usages.
#    Interface(Name), Implementation(Module), Usage(Module)
#    Also add source files for them.
# 
# 3. Go through R:\ again, find out if the implementation has derived classes?
#
# Notes:
# Comments are removed
# 
#####

use strict;

#===========================================Main===========================================

my %DependencyMap; #Interface->(Declaration, Implementation, Usages)
my @FirstLevelImps;

# 1. Get all source files
my @InvSrcFiles = GetInvSrcFiles();
#my @InvSrcFiles = ("R:\\Server\\Support\\include\\IFx\\pattern.h", "R:\\Server\\CoreApps\\CmSrv\\Request\\RectPatternData.h");
print "Totally " . $#InvSrcFiles . "files", "\n";

# 2. 1st round: Search all static and tearoff interfaces
&GetAllInterfaces();

# 3. 2nd round: Search all interfaces' implementation and usage
&BuildDependencyMap();

# 4. Analyze and Output the final result
#    IFxVirtualComponentUtil (Need Move; UcSrv->AmSrv, ..)
#    * Declared in server, implemented in Application. 
#    * Usage->Implemented map
&OutputResult();

CheckMultiLevelInheritance();



#===========================================Functions===========================================
# Get all InvSrc files
sub GetInvSrcFiles() 
{
	#*.c;*.cpp;*.cxx;*.cc;*.tli;*.tlh;*.h;*.hpp;*.hxx;*.hh;*.inl;*.rc;*.resx;*.idl;*.asm;*.inc
	my @Dirs = ("r:\\server\\", "R:\\XLayer\\", "R:\\AppFw\\", "R:\\Application\\", "R:\\AppSupport\\", "R:\\Compatibility\\", "R:\\Environment\\", "R:\\shellext\\", "R:\\XInterface\\");
	#my @Dirs = ("r:\\server\\");
	my @Extensions = ("*.c", "*.cpp", "*.cxx", "*.cc", "*.h", "*.hpp", "*.hh", "*.inl");
	my $Filters;
	foreach my $dir (@Dirs)
	{
		foreach my $ext (@Extensions)
		{
			$Filters .= ($dir . $ext . " ");
		}
	}
	#print $Filters, "\n";
	my $DirCmd = "dir /b /s $Filters";
	my @Files = `$DirCmd`;
	return @Files;
}

# Get all interfaces (TearOff and Static)
# "public RSeStaticInterface" & "public IFxStaticInterface"
sub GetAllInterfaces()
{
	my (%TearOff, %Static1, %Static2);
	foreach my $EachFile (@InvSrcFiles)
	{
		my $FileContent = &GetFileContent($EachFile);
		# Remove comments
		# http://faq.perl.org/perlfaq6.html#How_do_I_use_a_regul
		$FileContent =~ s#/\*[^*]*\*+([^/*][^*]*\*+)*/|//([^\\]|[^\n][\n]?)*?\n|("(\\.|[^"\\])*"|'(\\.|[^'\\])*'|.[^/"'\\]*)#defined $3 ? $3 : ""#gse;
		my @Matches;
		
		
		# classname: start with an underscore or letter, can only contain letter, underscore, and digit
		my $classname = "[A-Za-z_][\\w]*";
		my $classmodifier = "(?:$classname\\s+|__declspec\\s*\\(\\s*dllexport\\s*\\)\\s*)";
		
		# 1. TearOff Interface: public IFxTearOffInterface
		@Matches = $FileContent =~ /class\s+(?:$classmodifier)?($classname)\s*:\s*public\s+IFxTearOffInterface/g;
		#print join("\n", @Matches);
		foreach my $Match (@Matches) 
		{
			$TearOff{$Match} = $EachFile;
			my @Usages;
			my @Impls;
			my @Dependences = ($EachFile, \@Impls, \@Usages);
			$DependencyMap{$Match} = \@Dependences;
		}
		
		
		# 2. Static Interface1: public IFxStaticInterface
		@Matches = $FileContent =~ /class\s+(?:$classmodifier)?($classname)\s*:\s*public\s+IFxStaticInterface/g;
		#print join("\n", @Matches);
		 foreach my $Match (@Matches) 
		 {
			$Static1{$Match} = $EachFile;
			my @Usages;
			my @Impls;
			my @Dependences = ($EachFile, \@Impls, \@Usages);
			$DependencyMap{$Match} = \@Dependences;
		 }
		
		# 3. Static Interface2: public RSeStaticInterface
		@Matches = $FileContent =~ /class\s+(?:$classmodifier)?$classname\s*:\s*public\s+($classname)\s*,\s*public\s+RSeStaticInterface/g;
		my @Matches2 = $FileContent =~ /class\s+(?:$classmodifier)?$classname\s*:\s*public\s+RSeStaticInterface\s*,\s*public\s+($classname)\s*/g;
		push @Matches, @Matches2;
		#print join("\n", @Matches);
		foreach my $Match (@Matches)
		{
			next if("IFxInterface" eq $Match); #Ignore class RSeStaticToIFxConvertor : public IFxInterface, public RSeStaticInterface 
			$Static2{$Match} = $EachFile;
			# my @Usages;
			# my @Impls;
			# my @Dependences = ($EachFile, \@Impls, \@Usages);
			# $DependencyMap{$Match} = \@Dependences;
		}
	}
	
	# Ideally, they should be same
	my @StaticInterfaces1 = sort keys %Static1;
	my @StaticInterfaces2 = sort keys %Static2;
	
	&SetFileContent_Array("c:\\IFxStatic.txt", \@StaticInterfaces1);
	&SetFileContent_Array("c:\\RSeStatic.txt", \@StaticInterfaces2);
}

# Interface -> (Declaration, Implementation, Usages)
sub BuildDependencyMap
{
	foreach my $EachFile (@InvSrcFiles)
	{
		my $FileContent = &GetFileContent($EachFile);
		# Remove comments
		# http://faq.perl.org/perlfaq6.html#How_do_I_use_a_regul
		$FileContent =~ s#/\*[^*]*\*+([^/*][^*]*\*+)*/|//([^\\]|[^\n][\n]?)*?\n|("(\\.|[^"\\])*"|'(\\.|[^'\\])*'|.[^/"'\\]*)#defined $3 ? $3 : ""#gse;
		my @Matches;
		
		
		foreach my $Interface (keys %DependencyMap)
		{
			# classname: start with an underscore or letter, can only contain letter, underscore, and digit
			my $classname = "[A-Za-z_][\\w]*";
			my $classmodifier = "(?:$classname\\s+|__declspec\\s*\\(\\s*dllexport\\s*\\)\\s*)";
			
			# Find implementation
			@Matches = $FileContent =~ /class\s+(?:$classmodifier)?($classname)\s*:\s*public\s+$Interface\b/g;
			#print join "\n", @Matches, "\n";
			#print "\n*****************\n$Interface\n**************************\n"; 
			if(@Matches)
			{
				my $DependsRef = $DependencyMap{$Interface};
				push @{@{$DependsRef}[1]}, $EachFile;
				
				my @ImpName = @Matches;
				push @{@{$DependsRef}[1]}, \@ImpName;
				
				#
				push @FirstLevelImps, @ImpName;
			}
			
			# Find usage
			# RSe::Interface<IFxAssemblyPathUtil>()
			# Here let's just use the interface name: 
			# If that interface name is ever appeared in a source file, we consider it is a "usage", it is not that strict, but in this way we could catch all cases.
			if($FileContent =~ /\b$Interface\b/)
			{
				my $DependsRef = $DependencyMap{$Interface};
				push @{@{$DependsRef}[2]}, $EachFile;
			}
		}
		
	}
}

sub OutputResult()
{
	my $Output;
	my $Output_NoImplementation;
	my $Output_WrongDeclaration;
	foreach my $Interface (keys %DependencyMap)
	{
		my $DependsRef = $DependencyMap{$Interface};
		my $Declaration = @{$DependsRef}[0];
		my $Implementation = @{@{$DependsRef}[1]}[0];
		
		my $InterfaceInfo;
		my $DetailedInfo;
		
		
		$InterfaceInfo .= $Interface;
		$InterfaceInfo .= "(";
		
		
		# Declaration
		$DetailedInfo .= "\nDeclaration:\n";
		$DetailedInfo .= ("\t" . @{$DependsRef}[0]);
		
		# Implemenation
		$DetailedInfo .= "Implementation:\n";
		my $count = 0;
		foreach my $Imp (@{@{$DependsRef}[1]})
		{
			if($count % 2 == 0)
			{
				chomp $Imp;
				$DetailedInfo .= ("\t" . $Imp);
				
			}
			else
			{
				$DetailedInfo .= "(" . join("," ,@{$Imp}) . ")\n";
			}
			$count++;
		}
		
		# Usage
		my $ImpDLL = &GetDLLName($Implementation);
		my %DllMap;
		$DetailedInfo .= "Usage:\n";
		foreach my $Usage (@{@{$DependsRef}[2]})
		{
			next if($Usage =~ /UTxInterfaces\.cpp/i);
		
			$DetailedInfo .= ("\t" . $Usage);
			
			my $UsageDLL = &GetDLLName($Usage);
			if($UsageDLL && ($UsageDLL ne $ImpDLL))
			{
				$DllMap{$UsageDLL . "->" . $ImpDLL} = 1;
			}
		}
		
		foreach my $DllPair (sort keys %DllMap) 
		{
			$InterfaceInfo .= (" " . $DllPair);
		}
		
		$InterfaceInfo .= ")\n";
		
		my $EachInterface;
		
		$EachInterface .= $InterfaceInfo;
		$EachInterface .= "-" x 80;
		$EachInterface .= $DetailedInfo;
		$EachInterface .= "\n";
		
		$Output .= $EachInterface;
		
		# ....
		if(!$Implementation)
		{
			$Output_NoImplementation .= $EachInterface;
		}
		elsif(&IsInServer($Declaration) && !&IsInServer($Implementation))
		{
			$Output_WrongDeclaration .= $EachInterface;
		}
		elsif(!&IsInServer($Declaration) && &IsInServer($Implementation))
		{
			$Output_WrongDeclaration .= $EachInterface;
		}
	}

	&SetFileContent("c:\\Output_All.txt", $Output);
	&SetFileContent("c:\\Output_NoImplementation.txt", $Output_NoImplementation);
	&SetFileContent("c:\\Output_WrongDeclaration.txt", $Output_WrongDeclaration);
}

# We need to check multi-level inhertance. for example:
# Derived2->Derived1->Interface
#  AM          PM        support
# The modules we got would be different
sub CheckMultiLevelInheritance()
{
	my $Output_MultiLevelInheritance;
	foreach my $EachFile (@InvSrcFiles)
	{
		my $FileContent = &GetFileContent($EachFile);
		# Remove comments
		# http://faq.perl.org/perlfaq6.html#How_do_I_use_a_regul
		$FileContent =~ s#/\*[^*]*\*+([^/*][^*]*\*+)*/|//([^\\]|[^\n][\n]?)*?\n|("(\\.|[^"\\])*"|'(\\.|[^'\\])*'|.[^/"'\\]*)#defined $3 ? $3 : ""#gse;
		my @Matches;
		
		
		foreach my $EachImp (@FirstLevelImps)
		{
			# classname: start with an underscore or letter, can only contain letter, underscore, and digit
			my $classname = "[A-Za-z_][\\w]*";
			my $classmodifier = "(?:$classname\\s+|__declspec\\s*\\(\\s*dllexport\\s*\\)\\s*)";
			
			# Find implementation
			@Matches = $FileContent =~ /class\s+(?:$classmodifier)?($classname)\s*:\s*public\s+$EachImp\b/g;

			if(@Matches)
			{
				my $temp = join " ", @Matches;
				$Output_MultiLevelInheritance .= ($EachImp . "->" . $EachFile . "->" . $temp . "\n");
			}
		}
	}
	
	&SetFileContent("c:\\Output_MultiLevelInheritance.txt", $Output_MultiLevelInheritance);
}


sub GetDLLName($)
{
	my $filename = $_[0];
	return "" if($filename =~ /R:\\AppSupport\\include\\/i); # include
	return "" if($filename =~ /r:\\server\\Support\\include\\/i); # include
	return $1 if($filename =~ /r:\\server\\Objects\\\w+\\(\w+)\\/i); # server, objects
	return $1 if($filename =~ /r:\\server\\\w+\\(\w+)\\/i); # server
	return $1 if($filename =~ /r:\\xlayer\\apisrv\\(\w+)\\/i); # apisrv
	return $1 if($filename =~ /r:\\xlayer\\apiapp\\(\w+)\\/i); # apisrv
	return $1 if($filename =~ /r:\\\w+\\(\w+)\\/i); # Application side
}

sub IsInServer($)
{
	return $_[0] =~ /(r:\\server\\)|(r:\\xlayer\\apisrv\\)/i;
}

sub GetFileContent($)
{
	my $FileName = $_[0];
	my @FileContentArray = &GetFileContent_Array($FileName);
	return join "", @FileContentArray;
}

sub GetFileContent_Array($)
{
	my $FileName = $_[0];
	open THIS_FILE, $FileName or die "Can't open $FileName: $!";
	my @FileContentArray = <THIS_FILE>;
	close THIS_FILE;
	return @FileContentArray;
}

sub SetFileContent($$)
{
	my ($FileName, $FileContent) = @_;
	open THIS_FILE, ">$FileName" or die "Can't create $FileName: $!";
	print THIS_FILE $FileContent;
	close THIS_FILE;
}
sub SetFileContent_Array($\@)
{
	my ($FileName, $FileContentRef) = @_;
	my $FileContent = join "\n", @{$FileContentRef};
	&SetFileContent($FileName,$FileContent);
}


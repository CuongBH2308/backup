use strict;
use File::Basename;
BEGIN{push @INC, &dirname($0);}
use Utils::Basic;
use Utils::VS;

package VSProject;
###############################Directories##########################
# See #include directive in MSDN, generally, Compiler find files in directories in following sequence:
# 1.  Including file's directory
# 2. Previously opened file's directory. (in reversed order)
# 3. Project's AdditionalIncludeDirectories, /I
# 4. INCLUDE Env variables
# Here:
# Inherited Dir = 1 + 2
# Standard Dir = 3 + 4
#

sub new($)
{
    my $classname  = shift;           # What class are we constructing?
    my $this = {  };            # Allocate new memory
    bless($this, $classname);         # Mark it of the right type
	
	
	my $ProjectName = shift;
	
	my $ProjectDirectory = &::dirname($ProjectName);
	
	my @IncludeDirs = &VS::GetIncludeDirs($ProjectName);
	#print join "\n", @IncludeDirs;
	my $i = 0; 
	foreach my $EachDir (@IncludeDirs)
	{
		# Parse $ProjectDir
		@IncludeDirs[$i] =~ s/\$\(ProjectDir\)/$ProjectDirectory/ if($EachDir =~ /\$\(ProjectDir\)/);

		# Relative to Absolute
		@IncludeDirs[$i] = &::GetAbsPath($ProjectDirectory, $EachDir) unless ($EachDir =~ /^[a-zA-Z]:/);
		$i++;
		
		#&::Trace($EachDir);
	}
	#print join "\n", @IncludeDirs;
	my @InheritedDirs;
    $this->{INCLUDEDIRS}  = \@IncludeDirs;       # init data fields
    $this->{INHERITEDDIRS}  = \@InheritedDirs;
    return $this;                     # And give it back
	
}

sub GetIncludeDirs()
{
	 my $this = shift;
	 return @{$this->{INCLUDEDIRS}};
}

sub DESTROY 
{
    my $this = shift;
}

# Each time we opened a file, we should add that file's dir
sub AddInheritedDir($)
{
	my $this = shift;
	my $InheritedDir = shift;
	foreach my $Dir (@{$this->{INHERITEDDIRS}})
	{
		return if($Dir eq $InheritedDir);
	}
	push @{$this->{INHERITEDDIRS}}, $InheritedDir;
	# unshift @InheritedDirs, $InheritedDir;
}


sub ClearInheritedDir()
{
	my $this = shift;
	my @EmptyArray;
	@{$this->{INHERITEDDIRS}} = @EmptyArray;
}

# Get abs path in standard directories
sub GetAbsPath_Standard($)
{
	my $this = shift;
	my $RelPath = shift;
	my @AbsPaths;
	foreach my $EachDir (@{$this->{INCLUDEDIRS}})
	{
		my $EachAbsPath = &::GetAbsPath($EachDir, $RelPath);
		if(-f $EachAbsPath)
		{
			$EachAbsPath =~ s/^([A-Za-z]:)(?!\\)/\1\\/; # R:Application\UcRes\Resource.h -> R:\Application\UcRes\Resource.h
			push @AbsPaths, $EachAbsPath; 
		}
	}
	
	return @AbsPaths;
}

# Get abs path in inherited  directories
sub GetAbsPath_Inherited($)
{
	my $this = shift;
	my $RelPath = shift;
	my $AbsPath;
	foreach my $EachDir (@{$this->{INHERITEDDIRS}})
	{
		$AbsPath = &::GetAbsPath($EachDir, $RelPath);
		last if(-f $AbsPath);
	}
	$AbsPath = undef unless(-f $AbsPath);
	$AbsPath =~ s/^([A-Za-z]:)(?!\\)/\1\\/; # R:Application\UcRes\Resource.h -> R:\Application\UcRes\Resource.h
	return $AbsPath;
}

#******************************************************************************************************
return 1;
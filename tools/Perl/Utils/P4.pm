#####
#
# P4 operation utilities.
#
# Author: Baiyan Huang
# Date: 12/26/2008
#
#####
use strict;
BEGIN{push @INC, &dirname($0);}
use Utils::Basic;

package P4;

my $IsP4On;
my %VirtualDrivers; # Map virtual drive to the real path

my $View;# = "//inventor/streams/Hopper/dev/InventorServer4/sources";

#******************************* P4 Configurations*****************************************
sub P4On
{
	$IsP4On = 1;
}
sub P4Off
{
	$IsP4On = 0;
}

# You need specify the full path if your P4 root is not R:
sub Subst($$)
{
	my ($VDriver, $FullPath) = @_;
	
	$VirtualDrivers{uc $VDriver} = $FullPath;
}

# Expand the path: replace virtual drive with its actual path.
sub ExpandPath($)
{
	my $FilePath = $_[0];
	my $Driver = uc substr($FilePath, 0, 2);
	if(exists $VirtualDrivers{$Driver})
	{
		$FilePath =~ s/^$Driver/$VirtualDrivers{$Driver}/i;
		#&::Trace("ExpandPath:", $FilePath);
	}
	return $FilePath;
}

# Settings for intergartion
sub SetView($)
{
	# "//inventor/Main/sources";
	$View = $_[0];
}
sub Client2View($)
{
	my $Filename = @_[0];
	$Filename =~ s/\\/\//g;
	return $View . substr($Filename, 2);
}

#******************************************************P4 Operations***********************************************
sub P4Rename($$)
{
	return unless($IsP4On);
	my ($OriginalName, $DestName) = @_;
	&P4Integrate($OriginalName, $DestName, "-v");
	&P4Delete(&OriginalName);
}

sub P4Edit($)
{
	return unless($IsP4On);
	my $exec = "p4 edit @_[0]";
	&::Log(`$exec`);
}

# Integrate files - usually used when copy or split a file
# (SourceFile, DestFile, Options)
# &P4Integrate("R:\Ampm.sln", "R:\AmpmNew.sln", "-Dt -v");
sub P4Integrate($$$)
{
	return unless($IsP4On);
	my $sourcefile = &Client2View($_[0]);
	my $destfile = &Client2View($_[1]);
	my $Options = $_[2];
	my $exec = "p4 integrate $Options \"$sourcefile\" \"$destfile\"";
	&::Log(`$exec`);
}

sub P4Add($)
{
	return unless($IsP4On);
}

sub P4Delete($)
{
	return unless($IsP4On);
	my $exec = "p4 delete @_[0]";
	&::Log(`$exec`);
}

sub P4BatchEdit(@)
{
	return unless($IsP4On);
	my $TempFile = "C:\\TempFileList.txt";
	open TEMP_FILE, ">", $TempFile or "Can't open $TempFile for write: $!";
	foreach(@_)
	{
		print TEMP_FILE &ExpandPath($_), "\n";
	}
	close TEMP_FILE;
	
	my $exec = "p4 -x $TempFile edit";
	&::Log(`$exec`);
	unlink $TempFile;
}

# (Files, Options)
# -a means revert unchanged files
sub P4BatchRevert(\@$)
{
	return unless($IsP4On);
	my $Options = pop @_;
	my @Files = @{shift @_};
	my $TempFile = "C:\\TempFileList.txt";
	open TEMP_FILE, ">", $TempFile or "Can't open $TempFile for write: $!";
	foreach(@Files)
	{
		print TEMP_FILE &ExpandPath($_), "\n";
	}
	close TEMP_FILE;
	
	my $exec = "p4 -x $TempFile revert $Options";
	&::Log(`$exec`);
	unlink $TempFile;
}

#***************************************P4 Query******************************************************
# p1: CL Num
# return: @(@(File, Rev, Type)...)
sub GetAffectedFiles($)
{
	my $CL = $_[0];
	
	my $Exec = "p4 describe -s $CL";
	my @CLInfo = `$Exec`;
	my $Start = 0;
	my @AffectedFiles;
	foreach my $Line (@CLInfo)
	{
		$Start = 1 if($Line =~ /^Affected files \.\.\.$/);
		if($Start == 1)
		{
			if($Line =~ /\.\.\. (.+?)#(\d+) (\w+)$/)
			{
				my @FileInfo = ($1, $2, $3); #($File, $Rev, $Type)
				#&::Trace(@FileInfo);
				push @AffectedFiles, \@FileInfo;
			}
		}
	}
	return @AffectedFiles;
}
#******************************************************************************************************
return 1;
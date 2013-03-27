###
#
# Delegate command to p4, if the input file is from virtual drive "R:", translate the virtual path to its physcial path.
# Thus we could call p4 commands correctly without your p4 client spec rooted in "R:"
#
# Usage:
# P4.pl  ItemPath IsTranslate
# P4.pl edit R:\Server\Framework\FwSrv\FwSrv.vcproj
# P4.pl revert R:\Server\Framework\FwSrv\FwSrv.vcproj
# P4.pl edit R:\Server\Framework\FwSrv\FwSrv.vcproj 0
# P4.pl revert R:\Server\Framework\FwSrv\FwSrv.vcproj 1
#
# Author: Baiyan Huang
# History
# 12/8/2008 	Created
# 09/29/2009  	Updated 	Get the physical path of "R:" automatically.
#
##
use strict;

# 1. Get the inputs from command line
my $P4Cmd = @ARGV[0];
my $InputFile = @ARGV[1];
my $IsTranslate = 1; # If your client spec is rooted in "R:", just set $IsTranslate to 0
if(defined $ARGV[2])
{
	$IsTranslate = $ARGV[2];
}


# 2. Translate the file path to its physical path if required
if($IsTranslate)
{
	my $PhysicalPath = &GetPhysicalPath("R:");
	$InputFile =~ s/\//\\/g;
	$InputFile =~ s/^R:/$PhysicalPath/i;
	#print $InputFile;
}

# 3. Delegate to p4
my $Exec;
$InputFile = "\"" . $InputFile . "\""; # quote the file in case there are spaces in the path
if($P4Cmd =~ /^diff$/i)
{
	$Exec = "p4win.exe -D $InputFile";
}
elsif($P4Cmd =~ /^find$/i)
{
	$Exec = "p4win.exe -s $InputFile";
}
else
{
	$Exec = "p4.exe $P4Cmd $InputFile";
}
print `$Exec`;


#=======================================================Functions=========================================================#
# Get the physical path of a virtual drive.
# Usage: GetPhysicalPath("r:")
sub GetPhysicalPath($)
{
	my $VirtualDrive = $_[0];
	my $PhsicalPath = $VirtualDrive;
	my @Substs = `subst`;
	chomp @Substs;
	foreach my $subst (@Substs)
	{
		# Find the substed R: virtual driver, get its physical path
		if($subst =~ /^$VirtualDrive/i)
		{
			# R:\: => C:\Disk\Inventor\Main\sources
			my @pair = split(" => ", $subst);
			$PhsicalPath = $pair[1];
			last;
		}
	}
	
	return $PhsicalPath;
}
#####
#
# This script would rename all jpg files in a folder to its creation date, for example: 20101009
# For a photo, the real creation date = modified date
#
# Usage:
# BatchRenaming.pl <Folder>
# BatchRenaming.pl C:\MyPhotoes\
#
# Author: Baiyan Huang
# Date: 10/9/2010
#
#####

use strict;
if(@ARGV != 1)
{
	print "The syntax should be:\n\tBatchRenaming.pl <Folder> \n";
}

my $Folder = $ARGV[0]; 
$Folder =~ s/^\s*//;
$Folder =~ s/\s*$//;
$Folder =~ s/\\/\//g;
$Folder .= "/" if($Folder !~ /\/$/);
###print $Folder, "\n";

chdir $Folder;
my @AllFiles = glob "*.jpg";
###print @AllFiles, "\n";

foreach my $File (@AllFiles)
{
	chomp $File;
	
	# Get modified timestamp
	my $mtime;
	my(undef, undef, undef, undef, undef, undef, undef, undef, undef, $mtime) = stat($File);
	
	# Get relative date
	my ($day, $mon, $year);
	my(undef, undef, undef, $day, $mon, $year) = localtime($mtime);
	 
	# Tranform to human-readable date
	$year = 1900 + $year;
	$mon += 1;
	$mon = "0" . $mon if($mon < 10);
	$day = "0" . $day if($day < 10);
	
    my $date = $year . $mon . $day;
	###print "$date\n";
	
	my $NewFileName = $date . ".jpg";
	
	# Backup the file if there is already one exist of the same date
	if (-e $NewFileName and lc($NewFileName) ne lc($File))
	{
		my $Backup = "backup";
		mkdir $Backup if(! -e $Backup);
		rename $File, $Backup . "/" . $File;
		next;
	}
	
	# rename
	print $NewFileName, "\n";
    rename $File, $NewFileName;
}

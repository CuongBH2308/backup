#
# Move files in a specified folder into subfolders by months
#
use strict;  	# variables must be declared before used
use sigtrap; 	# signal handling, provide a stack trace
use warnings;	# show warnings (runtime)
use diagnostics;# produce verbose warning diagnostics (compile time)

use File::Spec; 	# concat path
use File::Basename; # get base name of a full path

my $targetDir = $ARGV[0];
$targetDir =~ s/[\\\/]$//;

sub help()
{
	my $scriptName = basename($0);
	print "Move all files in specified folder into sub folders by file creation month.\n";
	print "Usage:\n";
	print "\t$scriptName <targetDir>\n";
	exit;
}

sub getDestination($)
{
	my $file = $_[0];
	my @stats = stat($file); # seconds since ...
	my @times = localtime($stats[9]); # group into years, months...
	
	my $year = $times[5] + 1900;
	my $month = $times[4] + 1;
	$month = "0" . $month if($month < 10);
	
	return $year . "-" . $month;
}

sub quote($)
{
	return '"' . $_[0] . '"';
}
sub main()
{
	help() if(!defined($targetDir));
	
	my @allFiles = glob "$targetDir/*";
	
	my $count = 0;
	foreach my $file (@allFiles)
	{
		next if(! -f $file); # skip folders
		
		my $subDir = File::Spec->catfile($targetDir, getDestination($file));
		#print $subDir;
		mkdir $subDir if(! -e $subDir);
		
		$count++;
		my $destFile = File::Spec->catfile($subDir, basename($file));
		print "$count: Moving $file to $destFile\n";
		
		rename $file, $destFile;
	}
}

main();


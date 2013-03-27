#
use strict;
use XML::Simple;
use Data::Dumper;
use File::Basename;
use File::spec;

my $CL = "434707";
my $ClientSpec = "R:\\";
my $View = "//inventor/streams/Hopper/dev/InventorServer4/sources/";
my $ViewPattern = $View;
$ViewPattern =~ s/\//\\\//g;
print $ViewPattern;
my @ChangeSpec = `p4 change -o $CL`;
print @ChangeSpec;
print @ChangeSpec;
my @Files;
open THIS_FILE, ">C:\\$CL.txt";
foreach(@ChangeSpec)
{
	
	if(/\s*$ViewPattern(.*?)\s*#/i)
	{
		my $File = $1;
		
		$File =~ s/\//\\/g;
		$File = $ClientSpec . $File;
		print "$File\n";
		print THIS_FILE "$File\n";
		
		push @Files, $File;
	}
	
}
print scalar @Files;	
print THIS_FILE scalar @Files;
close 	THIS_FILE;
	
<STDIN>;

		

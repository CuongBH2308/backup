use strict;
use warnings;

my @dirs = `dir /AD /s /b| grep \.svn\$`;

foreach my $dir ( @dirs )
{
	chomp $dir;
	my $cmd = "rd /s /q $dir"; # it is wield that when I use rmdir, it doesn't work.
	print "Executing: " . $cmd . "\n";
	`$cmd`;
}
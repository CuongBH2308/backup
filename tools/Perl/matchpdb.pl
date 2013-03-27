######
# Description:
# Force match pdbs with its executables (build on different server, but of the same version)
#
# Usage
# matchpdb.pl <Dir>
#
#####
use strict;
sub getAllPDBs($)
{
	my $dir = shift @_;
	#print $dir;
	$dir .= "\\*.pdb";
	# print $dir, "\n";
	my @pdbs = `dir "$dir" /b /s`;
	chomp @pdbs;
	return @pdbs;
	# print @pdbs, "\n";
}

sub forceMatch($$)
{
	my ($exeutable, $pdb) = ($_[0], $_[1]);
	$pdb = '"' . $pdb . '"';
	$exeutable = '"' . $exeutable . '"';
	print ">>>matching $pdb ";
	my $res = `chkmatch.exe -m $exeutable $pdb`;
	#print $res;
	my $output = "success!";
	$output = "fail!" if($res =~ /^Error:/im);
	print "\n\t", $output, "\n";
}

#----------Main---------
my @pdbs = getAllPDBs($ARGV[0]);
foreach my $pdb (@pdbs)
{
	my $executable = $pdb;
	$executable =~ s/\.pdb\s*$/\.dll/i;
	#print $executable, "\n";
	
	$executable =~ s/\.dll\s*"/\.exe/i if !(-f $executable);
	
	if(-f $executable)
	{
		forceMatch($executable, $pdb);
	}
}

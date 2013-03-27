#
# rename D:\Study\Ó¢Óï\Friends, work for both folders and files.
#
use strict;

use File::Spec; 	# concat path
use File::Basename; # get base name of a full path

use File::Find qw(finddepth); # recursive get files

my $targetDir = $ARGV[0];

sub listFiles()
{
	#return glob "$targetDir/*";
	my @allFiles;
	finddepth(sub{
			return if($_ eq '.' or $_ eq '..');
			push @allFiles, $File::Find::name;
		}, $targetDir);
	return @allFiles;
}

sub main()
{
	print $targetDir, "\n";
	my @allFiles = listFiles();
	
	foreach my $file (@allFiles)
	{
		print $file, "\n";
		if($file =~ /\[(Friends\.\w+)\]/)
		{
			my $name = $1;
			$name .= ".rmvb" if($file =~ /\.rmvb/i);
			my $newFile = File::Spec->catfile(dirname($file), $name);
			print $newFile, "\n";
			
			rename $file, $newFile;
		}
	}
}

main();
#####
#
# Author: Baiyan Huang
# Date: 9/12/2011
#
# Knowledge:
# 1. Print out colored text to shell with Term::ANSIColor
# 2. Get long option with GetOpt::Long
# 3. How to write header comments
# 4. How to write help information
# 5. Constant
# 6. require modules on demand, not use.
# 7. Access environment variable
#
# TODO:
# 1. Test in linux
# 2. Performance problem when there are many files in a folder.
# 3. Handle hidden files...
#
#####

use strict;
use warnings;

use GetOpt::Long;
use File::Spec;
use File::Basename;
require Win32::Console::ANSI if ($^O eq 'MSWin32'); # windows-only
use Term::ANSIColor;
use Cwd;

# 0. constants
use constant
{
	kFile => 0,
	kFolder => 1,
};

use constant
{
	kFileColor => 'white',
	kFolderColor => 'yellow',
	kErrorColor => 'red',
};

use constant INT_MAX => 2147483647;

# 1. Get options & parameter
my $targetDir = getcwd; 

my $optLevel = INT_MAX; # default to unlimited level
my $optFolderOnly = 0; # default to list both files and folders
my $optHelp = 0;
my $optNoColor = 0;

Getopt::Long::Configure("prefix_pattern=(-|\/)");
my $retOpt = Getopt::Long::GetOptions("help|h|?"=>\$optHelp, "l|level=i"=>\$optLevel, 
	"fo|folder-only!"=>\$optFolderOnly, "nocolor"=>\$optNoColor);
if($optHelp)
{
	&Help();
	exit;
}

$ENV{'ANSI_COLORS_DISABLED'}=1 if($optNoColor);


# If dir is provided
$targetDir = $ARGV[0] if(@ARGV == 1);

# 2. Depth first traversal and print the item
my @arrLastTag;
print colored (basename($targetDir) . "\n", kFolderColor);
&DepthFirstTraverse($targetDir, \@arrLastTag);


# ============= functions =========================

# sub DepthFirstTraverse($dir, \@arrLastTag)
sub DepthFirstTraverse($$)
{
	my ($curDir, $arrLastTag) = @_;

	# level
	return if($#$arrLastTag + 1 >= $optLevel);
	
	chdir $curDir;
	
	# fold only
	my @allItems;
	if($optFolderOnly)
	{
		@allItems = grep { -d $_ } glob "*";
	}
	else
	{
		@allItems = glob "*";
	}
	
	for(my $i = 0; $i <= $#allItems; $i++)
	{
		my $item = $allItems[$i];
		
		my $isLast = ($i == $#allItems);
		push @$arrLastTag, $isLast;
		
		my $fullItem = File::Spec->catfile($curDir, $item);
		if(-f $fullItem)
		{
			&PrintItem($item, $arrLastTag, kFile);
		}
		elsif(-d $fullItem)
		{
			&PrintItem($item, $arrLastTag, kFolder);
			&DepthFirstTraverse($fullItem, $arrLastTag);
		}
		
		pop @$arrLastTag;
	}
	
	chdir ".."; # back off

}

# (name, \@hasnext, $type)
# console colored output
sub PrintItem($$$) 
{
	my ($name, $arrLastTag, $type) = @_;
	
	my $prefix;
	for(my $i = 0; $i <= $#$arrLastTag; $i++)
	{
		my $isLast = @$arrLastTag[$i];
		if($i != $#$arrLastTag) 
		{
			if($isLast) { $prefix .= "  "; }
			else {$prefix .= "©¦ ";}
		}
		else # the deepest level needs special treatment
		{
			if($isLast) { $prefix .= "©¸©¤"; }
			else {$prefix .= "©À©¤";}
		}
	}
	
	print $prefix;
	my $color = (kFolder == $type ? kFolderColor : kFileColor);
	print colored ($name, $color);
	print "\n";

}


sub Help()
{
    my ($Script) = ( $0 =~ /([^\\\/]*?)$/ );
    my ($Line)   = "-" x length($Script);

    print	<<EOT;

$Script
$Line
Print out the tree structure of a directory, recursively.

Syntax:
tree.pl [directory] [-l|level=i] [-fo|folder-only]

Example:
tree.pl
tree.pl c:\\windows -fo
tree.pl c:\\windows -l 3 -fo
tree.pl c:\\windows -l 3 -fo -nocolor

Contact Baiyan Huang for support

EOT
}

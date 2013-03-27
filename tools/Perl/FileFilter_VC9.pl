# FileFilter_VC9.pl <SrcDir> <PrjDir>
# 
# 1. DFS
#
use File::Spec;
use File::Basename;
use XML::LibXML;
use Data::UUID;
use strict;

my $srcDir = "F:\\Source\\baiyanhuang\\Design"; #@ARGV[0];
my $prjDir = "F:\\Source\\baiyanhuang\\Design\\Debug"; # @ARGV[1];
my $domFiles;

sub ToRel($)
{
	my $file = $_[0];
	#print $file . "\n";
	#my $baseName = basename($file);
	my $relDir = File::Spec->abs2rel($file, $prjDir);
	return $relDir;
}

sub appendFilter($$)
{
	my ($parent, $filterName) = @_;
	
	my $filterNode = $domFiles->createElement("Filter");
	$parent->appendChild($filterNode);
	
	$filterNode->setAttribute("Name", basename($filterName));
	
	my $ug = new Data::UUID;
	my $uuid1 = $ug->create();
	my $uniqueID = "{" . $ug->to_string($uuid1) . "}";
	$filterNode->setAttribute("UniqueIdentifier", $uniqueID);
	
	return $filterNode;
}	

sub appendFile($$)
{
	my ($parent, $file) = @_;
	#print $file . "\n";
	
	my $fileNode = $domFiles->createElement("File");
	$parent->appendChild($fileNode );
	
	$fileNode->setAttribute("RelativePath", &ToRel($file));
	
	return $fileNode;
}

sub RecurDir($$) # parent, dir
{	
	my ($parent, $srcDir) = @_;
	
	my $srcDirFilter = appendFilter($parent, $srcDir);
	
	chdir $srcDir;
	my @allItems = glob "*";
	chomp @allItems;
	foreach my $item (@allItems)
	{
		my $fullPath = $srcDir . "/" . $item;
		#print $fullPath . "\n";
		if (-f $item)
		{
			appendFile($srcDirFilter, $fullPath);
		}
		elsif(-d $item)
		{
			&RecurDir($srcDirFilter, $fullPath)
		}
	}
	
	chdir "..";
}


#==============main=====================
my $FILES_XML_STRING = "<Files></Files>";

# Create the DOM
my $parser = XML::LibXML->new;
$domFiles = $parser->parse_string($FILES_XML_STRING);
my $root = $domFiles->documentElement;

&RecurDir($root, $srcDir);

print $domFiles->toString(1);

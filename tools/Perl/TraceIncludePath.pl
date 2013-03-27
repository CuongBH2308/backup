#####
#
# How a specified file is included in a file, output a path. and and check cycle-include...
#
# Author: Baiyan Huang
# Date: 12/08/2008
#
# Usage:
# TraceIncludePath.pl <ProjectFile> <SourceFile> <TargetFile>
# 
# Note:
# Run from Inventor CMD line and call "%VS90COMNTOOLS%vsvars32.bat" first to get the necessary env variables
#
# TODO:
# 1. only include files #ifdef _WIN32
# 
#####
use strict;
use File::Basename;
BEGIN{push @INC, &dirname($0);}
use Utils::IncludeGraph;
#*******************************************Main****************************************
my ($ProjPath, $SourceFile, $TargetFile) = @ARGV;

# Build the graph by parsing all the includes
&IncludeGraph::BuildGraph($ProjPath,$SourceFile);

# We may just input the target file name, which is probably has more than one match of in all the files.
my @TargetFileList = &IncludeGraph::MatchVertice($TargetFile);

if(0 == @TargetFileList)
{
	print "$TargetFile can't be found!!!\n";
}

# Find path for each target
foreach (@TargetFileList)
{
	print "Target: $_\n";
	print "*" x 80;
	&IncludeGraph::SearchPaths($SourceFile, $_);
}

<STDIN>;

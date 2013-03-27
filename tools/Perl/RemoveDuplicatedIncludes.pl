#####
#
# Perl Script to remove duplicate include statement in both cpp and header files
# 
# Author: Baiyan Huang
# Date: 12/14/2008
#
# Usage
# RemoveDuplicateIncludes.pl <ProjectName>
# RemoveDuplicateIncludes.pl R:\Server\Framework\Fw\Fw.vcproj
#
# TODO: 
# 1. Build one graph for a project, merge graphs
# 2. Non-Direct duplicate in header files not removed
#
#####
use strict;
use File::Basename;
BEGIN{push @INC, &dirname($0);}
use Utils::IncludeGraph;

#************************************************Main**********************************************
my $ProjectPath = @ARGV[0];
my $PrjDir = &dirname($ProjectPath);

my @MissingFiles;
my %RemovedIncludesMap;
open PROJECT_FILE, $ProjectPath or die "Unable to open $ProjectPath for read\n $!";
foreach(<PROJECT_FILE>)
{
	# 	RelativePath=".\MFCDlgDlg.cpp"
	if(/^\s*RelativePath=\"((.*?)\.[Cc][Pp]{2})\"/)
	{
		my $CppFile = &IncludeGraph::GetAbsPath($PrjDir,$1);
		# It is possible that a source file is listed in project but not exist.
		if(! -e $CppFile)
		{
			push @MissingFiles, $CppFile; 
		}
		else
		{
			&RemoveDuplicateIncludesForFile($CppFile);
		}
	}
}
close PROJECT_FILE;

foreach (keys %RemovedIncludesMap)
{
	print $_, "\n";
	foreach(@{$RemovedIncludesMap{$_}})
	{
		print "\t$_";
	}
}

<STDIN>;

#*****************************************Functions******************************************************
sub RemoveDuplicateIncludesForFile($)
{
	my $FileName = $_[0];
	# Build the graph by parsing all the includes
	&IncludeGraph::BuildGraph($ProjectPath,$FileName);

	# Get files this file includes
	my @AdjacentVertice = &IncludeGraph::GetAdjacentVertice($FileName);

	# Included files has more than 1 path means duplicated
	my %DuplicateIncludes;
	foreach my $Include (@AdjacentVertice)
	{
		my $Number = &IncludeGraph::SearchPaths($FileName, $Include);
		if($Number > 1)
		{
			$DuplicateIncludes{$Include} = 1;
			&IncludeGraph::RemoveEdge($FileName, $Include);
		}
	}

	open THIS_FILE, $FileName or die "Unable to open $FileName: $!";
	my $FileContentStr;
	my $HasDuplicate = 0;
	foreach my $Line (<THIS_FILE>)
	{
		my $IncludedFile;
		if($Line =~ /^\s*#\s*include\s*\"(.*?)\s*\"/)
		{
			$IncludedFile = &IncludeGraph::GetAbsPath_Inherited($1);
		}
		elsif($Line =~ /^\s*#\s*include\s*<(.*?)\s*>/)
		{
			$IncludedFile = &IncludeGraph::GetAbsPath_Standard($1);
		}
		if($IncludedFile)
		{
			if(exists $DuplicateIncludes{lc $IncludedFile})
			{
				$HasDuplicate = 1;
				if(! exists $RemovedIncludesMap{$FileName})
				{
					my @RemovedIncludes;
					$RemovedIncludesMap{$FileName} = \@RemovedIncludes;
				}
				push @{$RemovedIncludesMap{$FileName}}, $Line;
				next;
			}
		}
		$FileContentStr .= $Line;
	}
	close THIS_FILE;

	if($HasDuplicate)
	{
		open THIS_FILE, ">", $FileName or die "Unable to create $FileName: $!";
		print THIS_FILE $FileContentStr;
		close THIS_FILE;
	}

}
sub Trace
{
	print "Trace->", @_, "\n";
}
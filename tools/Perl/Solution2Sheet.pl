#####
#
# Generate solution information in a format that can be copied to excel sheet
# Solution	Project	DLL	Size	Action	Comments
# ===================================================================
# 
# Author: Baiyan Huang
# Date: 02/12/2008
#
# Usage:
# Solution2Sheet.pl <SolutionName|SolutionList>
#
#
##
use strict;
use File::Basename;
BEGIN{push @INC, &dirname($0);}
use Utils::Basic;
use Utils::VS;
use Utils::P4;
use Utils::VSProject;

my $InputFile = $ARGV[0];
my $SolutionName = &::FileNameNoExt($InputFile);
&VS::SetConfig("Debug|Win32", "Debug");

# 1. Get projects
my @Projects;
if($InputFile =~ /\.txt$/i) # if txt file
{
	@Projects = &::GetFileContent_Array($InputFile);
}
elsif(&VS::IsSolutionFile($InputFile))
{
	@Projects = &VS::GetSolutionProjects($InputFile);
}

# 2. Form the format
my @ProjectsInfo;
foreach my $EachPrj (@Projects)
{
	next if($EachPrj =~ /res\.vcproj$/i);
	chomp $EachPrj;
	#&Trace($EachPrj);
	my $ProjectName = &::FileNameNoExt($EachPrj);
	my $DLL = &VS::GetProjectOutput($EachPrj);
	#&Trace($DLL);
	my $DLLName = &basename($DLL);
	
	my $DLLSize = "0.00M";
	$DLL =~ s/^r:[\\\/]lib[\\\/]debug/Z:\//i; # Change to Z: for release dll size;
	
	if(-f $DLL)
	{
		$DLLSize = &::GetFileSize($DLL) . "M";
	}
	my $ProjectInfo = $SolutionName . "\t" . $EachPrj . "\t" . $DLLName . "\t" . $DLLSize . "\t" . "0\t" . "0\t";
	push @ProjectsInfo, $ProjectInfo;
}

my $OutputDir = &::GetTempDir() . "\\Solution2Sheet";
mkdir $OutputDir unless(-d $OutputDir);
my $OutputFile = $OutputDir . "\\" . $SolutionName . "_Sheet.txt";
&::SetFileContent_Array($OutputFile, \@ProjectsInfo);
`notepad $OutputFile`;
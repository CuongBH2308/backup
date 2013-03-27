#####
#
# Perl Script to get all the projects by known solutions, output the result in following format so that we can 
# copy it to spread sheet:
# SolutionName	ProjectName	ProjectPath
# 
# Usage:
# GetInventorProjects.pl <Old/New>
# GetInventorProjects.pl Old
#
#####
use strict;
use File::Basename;
use File::Spec;
#*****************************************Main***********************************************
my @InventorSolutions;

if (@ARGV[0] eq "New")
{

}
else
{
    @InventorSolutions = ("R:\\InventorInterface.sln",
						  "R:\\Framework.sln",
						  "R:\\InventorCore.sln",
						  "R:\\AMPM.sln",
						  "R:\\Drawing.sln",
						  "R:\\Extra.sln",
						  "R:\\XLayer.sln",
						  "R:\\Compatibility.sln",
						  "R:\\Compatibility_DWG.sln"
						);
}

my $ProjectListFile = ">R:\\InventorProjectLists.txt";
open PROJECTLIST_FILE, $ProjectListFile or die "Unable to open $ProjectListFile for write: $!";
foreach my $Solution (@InventorSolutions)
{
	my @Projects = &GetSlnProjects($Solution);
	my $SolutionNameNoExt = &FileNameNoExt($Solution);
	foreach my $Project (@Projects)
	{
		my $ProjectNameNoExt = &FileNameNoExt($Project);
		print PROJECTLIST_FILE $SolutionNameNoExt, "\t", $ProjectNameNoExt, "\t", $Project, "\n";
	}
}
close PROJECTLIST_FILE;
#***************************************Functions**********************************************
# Get all vcproj project file in the solution
# @p1: Solution file
sub GetSlnProjects($)
{
	my @VcProjs;
	my $SlnFile = $_[0];
	my $SlnDir = &dirname($SlnFile);
	open CUR_SLNFILE, $SlnFile or die "Can't open solution $SlnFile: $!";
	foreach(<CUR_SLNFILE>)
	{
		# Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "RegisterTLB Tool", "XInterface\src\RegisterTLB\RegisterTLB.vcproj", "{2EFCC20E-F827-4FA5-A2E7-319B6514416F}"
		# ProjectSection(ProjectDependencies) = postProject
			# {05AA961A-8760-4ED7-ADF0-DC94394089A0} = {05AA961A-8760-4ED7-ADF0-DC94394089A0}
			# {244805E6-D245-47D4-894E-D0B0936C15D7} = {244805E6-D245-47D4-894E-D0B0936C15D7}
		# EndProjectSection
		# EndProject
		if(/Project\(\"(.*)\"\).*?,\s*\"(.*?)\"/)
		{
			my $PrjPath = $2;
			next if($PrjPath =~ /Res\./i); # Exclude the resource projects.
			if($PrjPath =~ /^[a-zA-Z]:\\/i) # Absolute path
			{
				push @VcProjs, $PrjPath;
			}
			else # Relative path
			{
				push @VcProjs, &GetAbsPath($SlnDir, $PrjPath);
			}
		}
		
	}
	close CUR_SLNFILE;
	
	return @VcProjs;
}

sub FileNameNoExt($)
{
	my $FileName = &basename($_[0]);
	return substr($FileName, 0, rindex($FileName, "."));
}

sub GetAbsPath($$)
{
	my $Dir = $_[0];
	my $RelPath = $_[1];
	
	# Process the file's relative path, remove prefix ".\" if there is.
	$RelPath = substr($RelPath, 2) if(substr($RelPath, 0, 2) eq "\.\\");
	
	# Get file's absolute path based on project location and relative path
	my $AbsPath = File::Spec->rel2abs($RelPath, $Dir);
	
	return $AbsPath;
}
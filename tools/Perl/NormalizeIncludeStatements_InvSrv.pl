#####
#
# Normalize include statement for all Inventor Source code
#
# Author: Baiyan Huang
# Date: 1/12/2009
#
# Dry Run:
# Total Solution	Total Project	Executed Project	 Total Source	Total Time
#  	9		    327			231	                21709		 3:42:52
#
#
#####
use strict;
use File::Basename;
BEGIN{push @INC, &dirname($0);}
use Utils::Basic;
use Utils::VS;
use Utils::P4;

#***********************************************Main*************************************************
my  @InventorSolutions = ("R:\\InventorInterface.sln",
						  "R:\\Framework.sln",
						  "R:\\InventorCore.sln",
						  "R:\\AMPM.sln",
						  "R:\\Drawing.sln",
						  "R:\\Extra.sln",
						  "R:\\Compatibility.sln",
						  "R:\\Compatibility_DWG.sln",
						  "R:\\XLayer.sln"
						);
		
#my  @InventorSolutions = ("R:\\AMPM.sln");

my $RootForR = "C:\\Disk\\Inventor\\Main\\Sources";
my $Count = 0;
my $TotalCount = 0;

&StartTiming();	

my $OutputDir = &::GetTempDir() . "\\NormalizeIncludeStatements";
mkdir $OutputDir unless(-d $OutputDir);
my $FileName = &FileNameNoExt($0);
&StartReport("$OutputDir\\$FileName.txt");
&Redirect_STDERR("$OutputDir\\$FileName.err");

&Report(">>>Start Processing\n");
foreach my $EachSolution (@InventorSolutions)
{
	&Report("\t$EachSolution\n");
	my @Projects = &VS::GetSolutionProjects($EachSolution);
	foreach my $EachProject (@Projects)
	{
		$TotalCount++;
		if(&IsQualifiedProject($EachProject))
		{
			#&Trace($EachProject);
			my $Exec = "NormalizeIncludeStatements.pl $EachProject -p4 $RootForR";
			&Report("\t->", $Exec, "\n");
			(`$Exec`);
			$Count++;
		}
	}
	&Report("\n");
}
&Report("\n>>>Total Project Count: $TotalCount\n");
&Report("\n>>>VS Code Project Count: $Count\n");

my $ElapsedTime = &EndTiming();
&Report("\n>>>Elapsed Time: $ElapsedTime\n");

# Let's build the Inventor
&StartTiming();	
my $BuildCommand = "\"R:\\Tools\\Build Tools\\InventorBuilder.pl\" /c debug";

&Report(`$BuildCommand`);

my $BuildTime = &EndTiming();
&Report("\n>>>Build Time: $BuildTime\n");

&EndReport();
#********************************************Functions***************************************************
sub IsQualifiedProject($)
{
	my $Project = $_[0];
	if($Project =~ /(?<!res)\.vcproj$/i)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}
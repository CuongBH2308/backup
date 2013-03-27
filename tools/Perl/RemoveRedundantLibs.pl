#####
#
# Perl Scripts used to remove redundant libs in project's "AdditionalDepdendencies", thus reduce the link time.
#
# Author: Baiyan Huang
# Date: 12/03/2008
#
# Usage:
#  RemoveRedundantLibs.pl <ProjectPath>
#  RemoveRedundantLibs.pl  R:\Server\Framework\Fw\Fw.vcproj
#
# Steps:
# 1. USe DllTool to get a list of lib that is redundant.
# 2. Remove the libs in project's AdditionalDepdendencies section (Based on debug, others configuration should be similiar)
#
# Note:
# The Debug | Win32 Version of the dll must be there, we just analyze the redundancies of this version, but  will update other version  accordingly.
#  After run this script:
#	1. Link Fw to see if some libs are wrongly removed, if so, add them for all configurations
#	2. Check the warning file, to see if some more lib need to be removed in other configurations. (Different Lib name in different configuration)
# TODO
#
# 1. More clear report, hide the error report of dll tool
#
#####
use strict;
use File::Basename;
BEGIN{push @INC, &dirname($0);}
use Utils::Refactor_Utils;


#*************************************************Main*************************************************
# Write the project to a file first ---- DllTool only support read from a file list
my %ConfigWarnings;
my $ProjectPath = @ARGV[0];
my $TempPrjLst = "C:\\TempProjectListFile.txt";
open TEMP_PRJLIST_FILE, "> $TempPrjLst" or die "Can't create file $TempPrjLst: $!";
print TEMP_PRJLIST_FILE $ProjectPath;
close TEMP_PRJLIST_FILE;

# Run DllTool to get the redundant Libs
&ShowProgress("Get Redundant libs using DllTool...\n");
my @RawLibRedundancies = `dlltool -checkimp Win32  -f $TempPrjLst`;
unlink $TempPrjLst;

my $DebugHeader = shift @RawLibRedundancies;
if($DebugHeader !~ "Debug\|Win32") 
{
	die "Please make sure your Debug|Win32 version DLL generated!!!"
}

my @Debug32LibRedundancies;
foreach(@RawLibRedundancies)
{
	last if(/^\s+$/);

	$_ =~ s/\s+//g; # Remove the spaces
	push @Debug32LibRedundancies, $_;
}

# Update the project file
&ShowProgress("Update the project's AdditionalDependencies Section...\n")
&P4Edit($ProjectPath);
&OverwriteFile($ProjectPath, \&RemoveRedundancies);

# Output the warning files, which give us clues to correct configurations (Other than the Debug|Win32)
&ShowProgress("Output warning which is useful to correct Non_Debug|Win32 version settings...\n");
&OutputWarnings();
<STDIN>;

#**********************************************Functions*******************************************
# OverwriteFile handler, remove the redundant libs we found in @Debug32LibRedundancies
# @Params: project file content
# @Return: updated file content as a string
sub RemoveRedundancies()
{
	my @FileContent = @{$_[0]};
	my $FileContentStr;
	my $Config;
	foreach my $CurLine (@FileContent)
	{
		# 	Name="Debug|Win32"
		if($CurLine =~ /^\s*Name=\"(\w+\|\w+)\"/)
		{
			$Config = $1;
			my @Warnings;
			$ConfigWarnings{$Config} = \@Warnings;
		}
		# 	AdditionalDependencies="smdata.lib fb.lib rse.lib utx.lib Em.lib psapi.lib GR.lib GRData.lib acge.lib acgex.lib shell32.lib shlwapi.lib htmlhelp.lib Hooks.lib persist.lib BR.lib iop.lib mc3.lib vbc32.lib pdh.lib IAFxAppFrame.lib rm.lib InvTaskDialog.lib gdiplus.lib msi32.lib"
		if($CurLine =~ /^\s*AdditionalDependencies=\"(.*)\"/)
		{
			foreach my $Lib (@Debug32LibRedundancies)
			{
				if($CurLine =~ /$Lib/)
				{
					$CurLine =~ s/$Lib//i;
				}
				else
				{
					push @{$ConfigWarnings{$Config}}, $Lib;
				}
			}
			$CurLine =~ s/\b\s+/ /gi; # Remove extra spaces.
		}
		
		$FileContentStr .= $CurLine;
	}
	
	return $FileContentStr;
}

# Output the warning
sub OutputWarnings()
{
	my $ProjectName = &FileNameNoExt($ProjectPath);
	my $WarningFile = "R:\\Server\\RemoveRedundantLibs_${ProjectName}_Warnings.txt";
	open WARNING_FILE, ">", $WarningFile or die "Can't create file $WarningFile:$!";
	foreach my $Config (keys %ConfigWarnings)
	{
		print WARNING_FILE $Config, "\n";
		foreach (@{$ConfigWarnings{$Config}})
		{
			print WARNING_FILE "\t$_ n";
		}
	}
	close WARNING_FILE;
	
	`notepad $WarningFile`;
}

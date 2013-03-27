#####
#
# Problem: 
# We have change the location of a file in IS4 branch, and when we bring it back to Main, we simply delete the orginal one and copy the new one, thus miss the changes that has been made 
# on Main.
#
# Solution:
# Re-Integrate the deleted files to IS4 branch, and then integrate them back to Main
#
# Author: Baiyan Huang
# Date: 02/04/2009
#
# Steps:
# 1. Get "deleted" files from the CLs (The CL that bring IS4 back to Main, 439996, 440128)
# 2. Get the source file(deleted file) rev range and target file(from the branch mapping), to form a "p4 integrate" command
# 3. Run these commands.
# 4. Manually resolve the changes and submit and bring back to Main.
#
#####
use strict;
use File::Basename;
BEGIN{push @INC, &dirname($0);}
use Utils::Basic;
use Utils::P4;

Redirect_STDERR("C:\\ReIntroductMissingChanges.err");

my $BranchMappingFile = "R:\\Tools\\Development Tools\\CodeRestructure\\CodeRestructure\\SampleData\\IS Phase 5\\BranchMapping.txt";
my %FileMapping;
my %DirMapping;
my @DanglingFile;

# 1. Get "deleted" files from the CLs (The CL that bring IS4 back to Main, 439996, 440128)
my @AffectedFiles = &P4::GetAffectedFiles(439996);
&Trace(scalar @AffectedFiles);
push @AffectedFiles, &P4::GetAffectedFiles(440128);
&Trace(scalar @AffectedFiles);

# 2. Get the source file(deleted file) rev range and target file(from the branch mapping), to form a "p4 integrate" command
open BRANCHMAPPING_FILE, $BranchMappingFile or die "Can't open $BranchMappingFile for read: $!";
my $MappingStart = 0;
foreach(<BRANCHMAPPING_FILE>)
{
	$MappingStart = 1 if(/^View:$/);
	if($MappingStart == 1)
	{
		if(/^\s+(\/\/.+) (\/\/.+)$/)
		{
			my ($Source, $Target) = (lc $1, $2);
			if($Source =~ /.*\.\.\./ && $Target =~ /.*\.\.\./)
			{
				$Source =~ s/\.\.\.$//;
				$Target =~ s/\.\.\.$//;
				#&Trace($Source);
				#&Trace($Target);
				$DirMapping{$Source} = $Target;
			}
			else
			{
				$FileMapping{$Source} = $Target;
			}
		}
	}
}
close BRANCHMAPPING_FILE;

my @IntergrationCmds;
my $DeleteFileNum = 0;
foreach my $FileInfoRef (@AffectedFiles)
{
	my ($SourceFile, $Rev, $Type) = @{$FileInfoRef};
	if($Type eq "delete") #&& $SourceFile =~ /CH\.rc2/i)
	{
		$DeleteFileNum++;
		my $TargetFile = &GetMappingFile($SourceFile);
		
		if($Rev > 2) # First revision should be aready integrated and the last revision(delete) don't need to be integrated
		{
			$Rev -= 1;
			my $RevRange = "#1,#$Rev";
			$RevRange = "#1" if($Rev == 1);
			
			if($TargetFile eq "")
			{
				push @DanglingFile, $SourceFile;
				next;
			}
			my $IntegrateCmd = "p4 integrate $SourceFile$RevRange $TargetFile";
			push @IntergrationCmds, $IntegrateCmd;
			#&Trace($IntegrateCmd);
			#`$IntegrateCmd`;
		}
		#&Trace($File);
	}
}
#&Trace($DeleteFileNum);
# foreach (sort @DanglingFile)
# {
	# print $_, "\n" unless(/\.wst$/i);
# }

# 3. Run these commands.
print scalar @IntergrationCmds, "Files to integrate\n";
foreach my $IntegrationCmd (@IntergrationCmds)
{
	print "$IntegrationCmd\n";
	`$IntegrationCmd`;
}
#************************************************Functions*******************************************************
sub GetMappingFile($)
{
	my $SourceFile = lc $_[0];
	my $TargetFile = "";
	if(exists $FileMapping{$SourceFile})
	{
		$TargetFile = $FileMapping{$SourceFile};
	}
	else
	{
		# Search in Source Directories.
		foreach my $SourceDir (keys %DirMapping)
		{
			#&Trace($SourceDir);
			if($SourceFile =~ /^$SourceDir/i && length $SourceDir > 30) # Hard code to remove the first 3 dirs
			{
				#&Trace($SourceFile);
				my $TargetDir = $DirMapping{$SourceDir};
				($TargetFile = $SourceFile) =~ s/^$SourceDir/$TargetDir/i;
				#&Trace($TargetFile);
				if($TargetFile =~ /AutoCamRes/i) # Hard code to ignore the AutoCamRes check
				{
					last;
				}
				my $CmdOutput = `p4 sizes $TargetFile`;
				if($CmdOutput =~ /\d+ bytes$/)
				{
					#&Trace($TargetFile);
					last;
				}
				else
				{
					$TargetFile = "";
				}
			}
		}
	}
	return $TargetFile;
}
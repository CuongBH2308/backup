#####
#
# Restore changes from a backuped changelist.
#
# Author: Baiyan Huang
# Date: 12/07/2009
# 
# Usage:
# p4restore.pl <hbkfile>
# 
# Notes:
# 1. You need to set your target p4 clientspec as default correctly first by:
# p4 set <clientspec>
# 2. Files that already checked out in your target client spec will be overwirtten.
#
#
#####

use strict;
use File::Basename;

my $bkfile = $ARGV[0];
my $BackupFolder = &dirname($bkfile);
my $CLNum = &basename($bkfile);
$CLNum =~ s/\.hbk$//;


# Get replacement string
my $res ;
open BKFILE, $bkfile or die "Failed to open $bkfile: $!";
my @AllFiles = <BKFILE>;
my @ReplaceStr = &GetReplaceString(@AllFiles);
if(!@ReplaceStr) 
{
	print "Can't get your clients' directory\n";
	die;
}

# Parse and restore files one by one
foreach my $FileInfo (@AllFiles)
{
	chomp $FileInfo;
	#//inventor/main/sources/Application/Ag/Ag.cpp,7,edit
	my ($FileURL, $Revision, $Operation, $RelativeBkPath) = split(/,/, $FileInfo);
	
	print "Restore: $FileURL\n";
	
	# 1. Copy from backup folder to client
	# Source
	my $SourcePath = $BackupFolder . "\\" . $RelativeBkPath;
	# Target
	my $TargetPath = $FileURL;
	$TargetPath =~ s/$ReplaceStr[0]/$ReplaceStr[1]/i;
	$TargetPath =~ s/\//\\/g;
	my $TargetDir = &dirname($TargetPath);
	$TargetDir .= "\\";
	unless($Operation eq "delete")
	{
		#xcopy C:\Temp\Backup\sources\Server\Framework\FwSrv\FwSrv.vcproj  R:\Server\Framework\FwSrv\  /y
		$res = `xcopy "$SourcePath" "$TargetDir" /y /R`;
	}
	
	# 2. edit it, delete it or add it.
	#  need to flush to the correct version first if "edit"
	if($Operation eq "edit")
	{
		my $have_res = `p4 have "$TargetPath"`;
		$have_res =~ /#(\d+)/;
		if($1 != $Revision)
		{
			my $TargetArgument = $TargetPath . "#" . $Revision;
			my $p4flush = "p4 flush $TargetArgument";
			$res = `$p4flush`;
		}
	}
	
	my $p4cmd = "p4 $Operation \"$TargetPath\"";
	$res = `$p4cmd`;
	
}

print "Restore Done!";
#=======================================================Functions=========================================================#
# In order to map a perforce URL into a file path.
#            //inventor/Main/sources/Server/Framework/FwSrv/32bitHost/64bit/FWxExcelReaderHandler64.cpp
# C:\Disk\Inventor\Main\sources\Server\Framework\FwSrv\32bitHost\64bit\FWxExcelReaderHandler64.cpp
# return an array: (original, replacement)
sub GetReplaceString(@)
{
	foreach my $FileInfo (@_)
	{
		my ($FileURL, $Revision, $Operation) = split(/,/, $FileInfo);
		if($Operation ne "add")
		{
			my $p4have = `p4 have $FileURL`;
			if($p4have)
			{
				$p4have =~ /^.*#\d+ - (.*)$/;
				my $FileDir = $1;
				my @FileURLArr = split(/\//, $FileURL);
				my @FileDirArr = split(/\\/, $FileDir);
				
				my $Limits = -($#FileURLArr > $#FileDirArr ? $#FileDirArr : $#FileURLArr) - 1;
				
				my $i = -1;
				for($i = -1; $i >= $Limits; $i--)
				{
					last if(uc($FileURLArr[$i]) ne uc($FileDirArr[$i]));
				}
				if($i < $Limits) 
				{
					print "ERROR! Problem with your path:\n$FileURL\n $FileDir\n";
					return;
				}
				
				# Truncate the arraies to leave only the differences.
				$#FileURLArr = $#FileURLArr + 1 + $i;
				$#FileDirArr = $#FileDirArr + 1 + $i;
				
				#(/, C:\Disk)
				my $Original = join("/", @FileURLArr);
				my $Replacement = join("\\", @FileDirArr);
				
				return ($Original, $Replacement);
			}
		}
	}
	return;
}



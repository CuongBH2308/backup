#####
#
# Backup a pending changelist to a specified folder. The output would be a .hbk file and the bakcuped files:
#	changelist.hbk - description of the backuped file, include the backup path
#	changelist - folder with backuped files
#
# Author: Baiyan Huang
# Date: 12/07/2009
# 
# Usage:
# p4backup.pl <changelist> [Backup Folder]
# if the [Backup Folder] is not specified, it will use the default one: C:\Temp\P4backup
#  
# Notes:
# You need to set your target p4 clientspec as default correctly first by:
# p4 set <clientspec>
#
#
#####
use strict;
use File::Basename;
#if($#ARGV != 1) {die "Wrong parameters!";}
my $CLNum = $ARGV[0];
my $BackupFolder = "C:\\Temp\\P4Backup";
if($#ARGV > 0)
{
	$BackupFolder = $ARGV[1];
}

# Get description of a CL
my $CLDescription = `p4 describe $CLNum`;

# Trim the content before "Affected files"
$CLDescription =~ s/(.|\n)*Affected files \.\.\.//;

# Trim space at the two ends of the string
$CLDescription =~ s/^\s*//;
$CLDescription =~ s/\s*$//;

# Format the file information
my $bkoutput;
my @AllFiles = split /\n/, $CLDescription;
my @AllFiles2;
foreach my $EachFile (@AllFiles)
{
	# Source
	# //inventor/Main/sources/Server/Framework/FwSrv/32bitHost/64bit/FWxExcelReaderHandler64.cpp#2 edit ->
	# R:\Server\Framework\FwSrv\32bitHost\64bit\FWxExcelReaderHandler64.cpp
	$EachFile =~ /^\.\.\. (.*)#(\d+) (.*)/;
	my ($FileURL, $Revision, $Operation) = ($1, $2, $3);
	my $Line = join(",", $FileURL, $Revision, $Operation);
	push @AllFiles2, $Line;
}

# Get replacement string
my @ReplaceStr = &GetReplaceString(@AllFiles2);
if(!@ReplaceStr) 
{
	print "Can't get your clients' directory\n";
	die;
}

foreach my $EachFile (@AllFiles2)
{
	# Source
	my ($FileURL, $Revision, $Operation) = split(/,/, $EachFile);

	$bkoutput .= $EachFile;
	# No need for backup if the file is deleted.
	unless($Operation eq "delete")
	{
		#Source
		my $SourcePath = $FileURL;
		$SourcePath =~ s/$ReplaceStr[0]/$ReplaceStr[1]/i;
		$SourcePath =~ s/\//\\/g;
		
		# Target
		my $FilePath = $SourcePath;
		$FilePath =~ s/^\w:\\//;
		my $BackupPath = $BackupFolder . "\\" . "$CLNum\\" . $FilePath;
		my $TargetDir = &dirname($BackupPath);
		$TargetDir .= "\\";
		$bkoutput .= ",$CLNum\\$FilePath";
		
		#xcopy R:\Server\Framework\FwSrv\FwSrv.vcproj C:\Temp\Backup\sources\Server\Framework\FwSrv\  /y
		my $res = `xcopy "$SourcePath" "$TargetDir" /y`;
	}
	$bkoutput .= "\n";
	print "Backup: $FileURL\n";

}

# Save backup file
my $bkfile = $BackupFolder . "\\" . $CLNum . ".hbk";
open BKFILE, ">", $bkfile or die "Failed to create $bkfile $!";
print BKFILE $bkoutput;
close BKFILE;
print "\nBackup Done: $bkfile\n";

#========================================================Functions================================================
# In order to map a perforce URL into a client file path.
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

use strict;
use File::Basename;
use Time::HiRes qw(gettimeofday tv_interval);

my $t0 = [gettimeofday];

# 1. Back up using ZIP
# Back up Disk\CoreData and Disk\Tools to SHACNG8420TV6
my @SrcDir = ("C:\\Disk\\CoreData",
			  "C:\\Disk\\Tools"
			  );
			  
my $SHACNG8420TV6 = "\\\\SHACNG8420TV6\\C\$\\Disk";
my $BackupDir = $SHACNG8420TV6 . "\\Backup";
foreach (@SrcDir)
{
	my $ZipFileNoExt = $BackupDir . "\\" . &basename($_);
	my $ZipFileTmp = $ZipFileNoExt . "_tmp" . ".zip" ;
	my $ZipFile = $ZipFileNoExt . ".zip";
	#print $ZipFileNoExt, "\n", $ZipFileTmp, "\n", $ZipFile;
	
	#1. Zip to a tmp zip file
	#2. Delete the previous backup file.
	#3. Rename the tmp zip file to backup file.
	# We zip first and delete later to avoid data lose in case there is an exception when we zip files
	print "Zip $_ to $ZipFile\n";
	my $Zipexec = "wzzip -rp $ZipFileTmp $_\\*.*";
	`$Zipexec`;
	unlink $ZipFile;
	rename $ZipFileTmp, $ZipFile;
}

# 2. Copy Disk\Tools to SHACNG8420TV6 and SHACNG82702MB
my $ToolsDir = "C:\\Disk\\Tools";
my $SHACNG82702MB = "\\\\SHACNG82702MB\\C\$\\Disk";
my $DestDir1 = $SHACNG8420TV6 . "\\Tools";
my $DestDir2 = $SHACNG82702MB . "\\Tools";

print `xcopy /d /e /r /y $ToolsDir $DestDir1`;
print `xcopy /d /e /r /y $ToolsDir $DestDir2`;


my $ti = Time::HiRes::tv_interval $t0;
my $ElapsedTime = (sprintf "%u:%02u:%02u", $ti/3600, ($ti%3600)/60, ($ti%3600)%60);
print "Backup Time: " . $ElapsedTime . "\n";

<STDIN>;
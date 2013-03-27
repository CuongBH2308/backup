#####
#
# Most common utilities like log, report, file operation...
#
# Author: Baiyan Huang
# Date: 11/20/2008
#
#####
use strict;
use File::Copy;
use File::Basename;
use File::Spec;
use Time::HiRes qw(gettimeofday tv_interval);
#*************************************Log functions*******************************************
sub StartLog($){ open LOGFILE, ">", $_[0] or die "Can't  Create log file $_[0]: $!";}
sub Log { print LOGFILE @_;}
sub EndLog(){ close LOGFILE;}

#*************************************Output functions*****************************************
sub ShowProgress { print STDOUT @_;} # Show current status of the script execution, don't use print directly
sub Trace { print STDOUT  "TRACE-------->", @_, "\n";} # Trace dianostic information, don't use print directly
sub Pause{print STDOUT "Press anykey to continue..."; <STDIN>;}

sub StartReport($){ open REPORT_FILE, ">", $_[0] or die "Can't  Create log file $_[0]: $!";}
sub Report {print REPORT_FILE @_; print STDOUT @_; }#
sub EndReport(){ close REPORT_FILE;}

sub Redirect_STDERR($){open STDERR, ">", $_[0] or die "Can't Create log file $_[0]: $!";}
#**********************************Files & Dirs*******************************************************************
sub GetTempDir()
{
	my $TempDir = "C:\\Temp";
	mkdir $TempDir unless (-d $TempDir);
	return $TempDir;
}

# Return file size in "M" unit
sub GetFileSize($)
{
	my $FileName = $_[0];
	my($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, $atime, $mtime, $ctime, $blksize, $blocks) = stat($FileName);
	return sprintf("%.2f", $size/1024/1024);
}

sub GetFileContent($)
{
	my $FileName = $_[0];
	my @FileContentArray = &GetFileContent_Array($FileName);
	return join "", @FileContentArray;
}

sub GetFileContent_Array($)
{
	my $FileName = $_[0];
	open THIS_FILE, $FileName or die "Can't open $FileName: $!";
	my @FileContentArray = <THIS_FILE>;
	close THIS_FILE;
	return @FileContentArray;
}

sub SetFileContent($$)
{
	my ($FileName, $FileContent) = @_;
	open THIS_FILE, ">$FileName" or die "Can't create $FileName: $!";
	print THIS_FILE $FileContent;
	close THIS_FILE;
}
sub SetFileContent_Array($\@)
{
	my ($FileName, $FileContentRef) = @_;
	my $FileContent = join "\n", @{$FileContentRef};
	&SetFileContent($FileName,$FileContent);
}
#**********************************Timing*******************************************************************
my $t0;
sub StartTiming
{
	$t0 = [gettimeofday];
}

sub EndTiming
{
	my $ti = Time::HiRes::tv_interval $t0;
	my $ElapsedTime = (sprintf "%u:%02u:%02u", $ti/3600, ($ti%3600)/60, ($ti%3600)%60);
	return $ElapsedTime;
}
#********************************Project File Functions***********************************************************
sub MakeNewRelPath($$$)
{
	my $NewDir = $_[0];
	my $OldDir = $_[1];
	my $OldRelPath = $_[2];
	
	# Get file's relative path base on the new project' s location
	return File::Spec->abs2rel(&GetAbsPath($OldDir, $OldRelPath), $NewDir);
}

# @p1: Dir
# @P2: abs path
sub GetRelPath($$)
{
	my ($NewDir, $AbsPath) = @_;
	return File::Spec->abs2rel($AbsPath, $NewDir);
}

# Get abs path by a dir and a relative path
# @p1: Dir
# @p2: Relative path
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

#******************************************File Operation****************************************************************
#Wrap the read and write file process, so we just need to provide a handler function which focus on update the file
# User need to checkout the file themselves
# param1: File name
#param2: handler sub Handler($){return } 
sub OverwriteFile($$) 
{
	my $fileName = @_[0];
	my $Handler = @_[1];
	my $FileContentStr;
	open CUR_FILE_READ, $fileName or die "Can't open file: $fileName, $!";
	my @FileContentArray = <CUR_FILE_READ>;
	$FileContentStr = &$Handler(\@FileContentArray, $fileName);
	close CUR_FILE_READ;
	
	open CUR_FILE_WRITE, ">", $fileName or die "Can't open file: $fileName, $!";
	print CUR_FILE_WRITE $FileContentStr;
	close CUR_FILE_WRITE;
}

#Wrap the read and write file process, so we just need to provide a handler function which focus on update the file
# It will check out the file automatically if really updated.
# param1: File name
# param2: handler, return 1 if file need update
sub OverwriteFileEx($$) 
{
	my $fileName = @_[0];
	my $Handler = @_[1];
	my $FileContentStr;
	open CUR_FILE_READ, $fileName or die "Can't open file: $fileName, $!";
	my @FileContentArray = <CUR_FILE_READ>;
	my $Changed = &$Handler(\@FileContentArray, \$FileContentStr, $fileName);
	close CUR_FILE_READ;
	
	if(1 == $Changed)
	{
		&P4Edit($fileName);
		open CUR_FILE_WRITE, ">", $fileName or die "Can't open file: $fileName, $!";
		print CUR_FILE_WRITE $FileContentStr;
		close CUR_FILE_WRITE;
	}
}

sub FileNameNoExt($)
{
	my $FileName = &basename($_[0]);
	return substr($FileName, 0, rindex($FileName, "."));
}

#*********************************************Others*********************************************
sub GetCurTime
{
	my ($secS,$minS,$hourS,$mdayS,$monS,$yearS,undef,undef,undef) = localtime(time());
	$yearS += 1900;
	$monS  += 1;
	return "$monS/$mdayS/$yearS $hourS:$minS:$secS";
}

sub DumpSimpleMap($)
{
	print "Dumping Map...";
	my $MapRef = $_[0];
	foreach (keys %$MapRef)
	{
		print $_, "=>", ${$MapRef}{$_}, "\n";
	}
}
#*******************************************************Array, Maps***********************************
sub UniquelizeList()
{
	my %TmpMap;
	foreach(@_)
	{
		$TmpMap{$_} = 1;
	}
	return keys %TmpMap;
}
#****************************Main*******************************************
return 1; #Utils script, simply return 1.
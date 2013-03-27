#####
#
#  Install and Quick Test a InventorServer build.
#
# Author: Baiyan Huang
# Date: 01/12/2010
#
# Usage: InventorServerQuickTest.pl <InstallerPath> <InstallationDir>
# 
#
#
#####
use strict;
use Win32;
use IO::File;
use Cwd;
use Encode;

# The result log file would be like: (0 means failed)
# Succeeded:1
# Log: 
# <log result>
#
my $ResultFile = "C:\\automation\\ISQuickTest.log";
`mkdir "C:\\automation"` if(! -e "C:\\automation");


#---------------------------------------------------Main------------------------------------------------------------------------

# ==============Step 0: Check input: installer, installation path...==================
if(@ARGV != 2)
{
	print Syntax();
	exit(1);
}

my $ServerInstaller = $ARGV[0];
my $ServerInstallDir = $ARGV[1];
$ServerInstallDir .= "\\";

my $WorkflowTestExeName = "ServerWorkflowTest.exe";
my $WorkflowTestCmdline = "--gtest_output=xml:" . '"' . $ServerInstallDir . "ServerWorkflowTest.xml" . '"';
my $TempDir = Win32::GetLongPathName($ENV{"TEMP"});


# Get the install log file name from setup.ini
my $ServerIni = $ServerInstaller;
$ServerIni =~ s/Setup[.]exe\s*$/Setup.ini/i;
##print $ServerIni;
my @arrIniContent = &GetFileContent_UTF_16LE($ServerIni);
my $iniContent = join "", @arrIniContent;
##print $iniContent;
my $ServerInstallLogName;
$iniContent =~ /LOG=%tmp%(.*?)\r\n/; # make sure \r won't be captured!
$ServerInstallLogName = $1;
my $ServerInstallLog = $TempDir . $ServerInstallLogName;
##print "$ServerInstallLog exists" if(-e $ServerInstallLog);

# Get workflow testing log file
my $WorkflowTestingLog = $ServerInstallDir . "ServerWorkflowTest.xml";
##print $WorkflowTestingLog;

# Check if the installer exists
if(!-e $ServerInstaller)
{
	my $Error = "The Installer:$ServerInstaller doesn't exist";
	print $Error . "\n";
	&Failed($Error);
}

# ==============Step 1: Uninstall Inventor Server if already installed - ignored currently==============
print "Uninstall InventorServer if already installed...\n";
&UnInstallInventorServer();
if(-e $ServerInstallLog)
{
	print "\tDelete Obsolete installation log file:\n\t ";
	print `del /Q "$ServerInstallLog"`; # delete the old log file before a new installation starts.
}

# ============= Step 2: Install InventorServer========================================================
print "\nInstall InventorServer...\n";
&InstallInventorServer($ServerInstaller, $ServerInstallDir);
my $Res = &IsInstallSucceeded();
if($Res == 0)
{
	print "\tInstall Failed\n";
	
	# Write out the result
	my @FileContent = &GetFileContent_UTF_16LE($ServerInstallLog);
	my $LogContent = "Install Failed!\n";
	$LogContent .= join "\n", @FileContent;
	&Failed($LogContent);
}
elsif($Res == 2)
{
	print "\tInstall Failed\n";
	&Failed("\tThis version is already installed\n");
}
else # $Res = 1
{
	print "\tInstall succeeded!\n";
}

# ================= Steps 3: Run workflow test ========================================================
print "Run workflow Test...\n";
# Set the output as failed with timeout in case the workflow testing is time out.
# If workflow testing finished in time, the output will be overwritten.
&Log("Workflow Test Timeout!\n"); 
my $ErrorCode = &RunWorkflowTest();
if($ErrorCode != 0)
{
	print "\tWorkflow Test failed\n";
	
	# Write out the result
	my @FileContent = &GetFileContent($WorkflowTestingLog);
	my $LogContent = "Workflow Test Failed!\n";
	$LogContent .= join "\n", @FileContent;
	&Failed($LogContent);
}
else
{
	print "\tWorkflow Test succeeded!\n";
}


# =====================Step 4: Return successfully===============================================================
my $Result = "Succeeded:1\n";
&SetFileContent($ResultFile, $Result);
print "InventorServer Quick Test succeeded!\n";
exit 0;





#---------------------------------------------------Function Definitions---------------------------------------------------------
sub Log($)
{
	my $Result = "Succeeded:0\n";
	$Result .= "Log:\n";
	$Result .= $_[0];
	&SetFileContent($ResultFile, $Result);
}
sub Failed($)
{
	Log($_[0]);
	exit(1);
}

# Install InventorServer, using command:
#  Setup.exe /t /qb /c INVENTORSERVER:INSTALLDIR="C:\PROGRAM FILES\AUTODESK\" INSTALLLEVEL=5
sub InstallInventorServer($$)
{
	my $Installer = $_[0];
	my $InstallDir = $_[1];
	my $LogFile = $ServerInstallLog;
	my $CmdLine = $Installer . " /t /qb /c INVENTORSERVER:INSTALLDIR=\"$InstallDir\" INSTALLLEVEL=5";
	#print $CmdLine;

	`$CmdLine`;
	
	# Since there are more than one "setup.exe" processes started to execute the installation, the installation doesn't
	# finish when previous command exits. Here I use a loop to check the log file until there are 2 "=== Setup ended ==="
	# in the log file, then I consider the installation finished.
	my $Finished = 0;
	while($Finished == 0)
	{
		# Read in file conent (this log file is encoded as unicode)
		my @FileContent = &GetFileContent_UTF_16LE($LogFile);
		
		# Parse the content to see if build succeeded or not
		my $NumOfEnds = 0;
		foreach my $Line (@FileContent)
		{
			if($Line =~ /\s+=== Setup ended ===\s*$/)
			{
				$NumOfEnds++;
				if($NumOfEnds == 2) { last;}
			}
		}
		last if($NumOfEnds == 2);
		
		# In case the installation is time out, we output the result as installation failed when installation is in process
		# If installation succeeded later, this information will be overwritten.
		my $LogContent = "Install Failed!\n";
		$LogContent .= join "\n", @FileContent;
		&Log($LogContent);
		
		# Not ready, let's wait 3 seconds
		sleep(3);
	}
}

sub UnInstallInventorServer()
{
	#Qucik Test will always run on a clean machine, this step is not necessary.
	#`msiexec /x {D8D951A6-0132-4337-B0F7-7B5923881CAE} /qb`;
}

#%Temp%\\Autodesk Inventor Server 2011 Setup.log
sub IsInstallSucceeded()
{
	my $LogFile = $ServerInstallLog;
	# Read in file conent (this log file is encoded as unicode)
	my @FileContent = &GetFileContent_UTF_16LE($LogFile);
	
	# Parse the content to see if build succeeded or not
	my $StartToMonitor = 0;
	my @ErrorInfor;
	foreach my $Line (@FileContent)
	{
		if($Line =~ /\s+=== Setup started/)
		{
			$StartToMonitor++;
			next;
		}
		if($StartToMonitor == 2)
		{
			last if($Line =~ /\s+=== Setup ended ===\s*$/);
			push @ErrorInfor, $Line;
		}
	}
	
	#print @ErrorInfor;
	
	return 2 unless(@ErrorInfor); # already installed
	
	foreach my $Line (@ErrorInfor)
	{
		if($Line !~ /.*\sSucceeded\s*$/)
		{
			return 0; # Failed
		}
	}
	return 1; #Succeeded
}
#set INVENTOR_NO_ERROR_DIALOG=1
sub RunWorkflowTest()
{
	# Copy the ServerWorkflowTest.exe to Server's installation folder.
	my $WorkingDir = getcwd();
	print "\t";
	my $WorkflowTestExeFullPath =  $WorkingDir . "/" . $WorkflowTestExeName ;
	my $FileDepot = $WorkingDir . "/" . "FileDepot";
	$WorkflowTestExeFullPath =~ s/\//\\/g;
	$ServerInstallDir =~ s/\//\\/g;
	$FileDepot =~ s/\//\\/g;
	
	#print $WorkflowTestExeFullPath . "\n";
	#print $FileDepot . "\n";
	if((!-f $WorkflowTestExeFullPath) || (! -e $FileDepot))
	{
		my $Error = "Workflow test exe or file depot not exist!";
		print $Error . "\n";
		&Failed($Error);
	}
	
	#Copy files to install dir
	my $copyExe = "xcopy /y $WorkflowTestExeFullPath \"$ServerInstallDir\"";
	print $copyExe . "\n";
	print `$copyExe`;

	my $copyFileDepot = "xcopy /s /y $FileDepot" . "\\*.*" . " \"$ServerInstallDir" . "FileDepot\\\"";
	print $copyFileDepot . "\n";
	print `$copyFileDepot`;
	
	# Run Test
	my $TestCmdExe =  '"' . $ServerInstallDir . $WorkflowTestExeName . '"';
	my $CmdTest = $TestCmdExe . " " . $WorkflowTestCmdline;
	my $Result = system($CmdTest);
	my $ReturnValue = $Result >> 8;

	# Remove the copied ServerWorkflowTest.exe
	#print `del /Q $TestCmdExe`;
	
	return $ReturnValue;
	
}
# return the array of the file contents
# use IO:File, not open, or else you won't handle with unicode successfully.
sub GetFileContentX($) 
{
	my $LogFile = $_[0];
	
	# Read in file conent (this log file is encoded as unicode)
	my $logfilebuffer;
	my $fh = new IO::File;
	if ($fh->open("<". $LogFile))
	{
		until ($fh->eof)
		{
			my $newtext,;
			$fh ->read($newtext,1);
			if ($newtext !~ /\x{00}/) # strip unicode byte
			{
				$logfilebuffer .= $newtext; 
			}      		
		}
	}
	$fh->close;
	my @FileContent = split /\n/, $logfilebuffer;
	return @FileContent;
}


sub GetFileContent_UTF_16LE($) 
{
	return &GetFileContent($_[0], "UTF-16LE");
}

sub GetFileContent(@) 
{
	my $LogFile = $_[0];
	my $op = defined $_[1] ? "<:encoding($_[1])" : "<";
	open CUR_FILE, $op, $LogFile;
	my @FileContent = <CUR_FILE>;
	close CUR_FILE;
	
	return @FileContent;
}

sub SetFileContent($$)
{
	my ($FileName, $FileContent) = @_;
	my $fh = new IO::File;
	if ($fh->open(">". $FileName))
	{
		$fh ->write($FileContent);
	}
	$fh->close;
}
sub SetFileContent_Array($\@)
{
	my ($FileName, $FileContentRef) = @_;
	my $FileContent = join "\n", @{$FileContentRef};
	&SetFileContent($FileName,$FileContent);
}



sub Syntax
{
    my ($Script) = ( $0 =~ /([^\\\/]*?)$/ );
    my ($Line)   = "-" x length($Script);

    print <<EOT;

InventorServer Quick Test
$Line
Usage:
$Script <InstallerPath> <InstallationDir>
					 
Example:
$Script "\\\\shanetapp01b\\MSD_Products\\Inventor\\R15\\M15_214_x86_Beta3_srv\\Server\\Setup.exe" "C:\\PROGRAM FILES\\AUTODESK"
EOT
}
#####
#
# Perl Script to remove redundant include statement in each cpp file of a project,  or  you can give a list of files you want to clean in the project.
# The main priciple of doing this is:  Remove-Compile-Check.( Thanks Scott for this great idea, and his advice on improving this script)
#
# Author: Baiyan Huang
# Date: 12/07/2008
#
# Usage:
# RemoveRedundantIncludes.pl <ProjectFile> [-f FileList] [-vs] [-p4 ClientView]
# <ProjectFile>: VC Project you want to clean
# [-f FileList] : optional, provide a file list you want to clean, it must belong to <ProjectFile>
# [-vs]: optional, as default, we will build with IncrediBuild,  with this option, we build with Visual Studio
#[-p4 ClientView]: optional, P4 is on as default with your client view as "R:", you can turn it off by "p4 off" or change the client view by "p4 C:\Disc\Inventor\Main\Sources"
# RemoveRedundantIncludes.pl R:\Server\Framework\Fw\Fw.vcproj		
# RemoveRedundantIncludes.pl R:\Server\Framework\Fw\Fw.vcproj	-p4 off			
# RemoveRedundantIncludes.pl R:\Server\Framework\Fw\Fw.vcproj	-p4 C:\Disc\Inventor\Main\Sources		
# RemoveRedundantIncludes.pl R:\Server\Framework\Fw\Fw.vcproj -f R:\FwFileList.txt
# RemoveRedundantIncludes.pl R:\Server\Framework\Fw\Fw.vcproj  -vs
# RemoveRedundantIncludes.pl R:\Server\Framework\Fw\Fw.vcproj -f R:\FwFileList.txt -vs
# 
# Note:
# 1. Your project should have no build errors before run this script - The script will check it for you as the first step (The script will stop after build 500 times, then you can solve the build error after that)
# 2. You project might have link errors after running this script, since we remove the include which import the lib by "progma comment", anyway, it should not be much and easy to fix.
# 3. To be safter, it would be better to check other configuration yourself after clean, such as AILT.
# 4. Please Run it from "Start CMD with Debug Inventor Environment", we build the project with "Debug|Win32"
# 5. If your perfoce's root is not R:, you should provide your full path of your R: as the client view of -p4, 
#     for example, my perforce Root is: C:\Disk\Inventor, so my ClientView = C:\Disk\Inventor\Main\Sources
# 6. Report and Log file are located at: 
#     C:\RemoveRedundantIncludes_<ProjectName>.log: P4 and Compiler output.
#     C:\RemoveRedundantIncludes_<ProjectName>.txt: same report show on the CMD output
# 7. Check the warnings manually, check the typeid, which is not safe
#
# Details:
# Header files redundancies are not processed. (There might be lots of Cpps to check among multiple projects when we remove an in include in a header file)
# We use IncrediBuild to process multiple Cpp files simutaneously
# We edit and revert files in single p4 command
# Includes end with stdafx.h afxdllx.h dlldefs.h ystem.h pch.h initguid.h .c are protected, they won't be removed during processing, include has the same name of cpp file is protected as well
# Cpp files end with stdafx.cppis omitted.
#
# Example:
# Machine: Hp7800, 4G, due core, xp32
# Project: Uc
# Build Round: 140
# Total Cpp Files: 788
# Cleaned Cpp Files: 618
# Removed Includes: 5135
# Time: 01:35:59
#
#####
use strict;
use File::Spec;
use File::Basename;
use Getopt::Long;
use Time::HiRes qw( gettimeofday tv_interval );
#*************************************Main*****************************************
my $ProjectFile = @ARGV[0];
my $ProjectName = &basename($ProjectFile);
my $ProjectNameNoExt = substr($ProjectName, 0, rindex($ProjectName, "."));

Getopt::Long::Configure("prefix_pattern=(-|\/)");
# Get file list from command line, if exist.
my ($options) ={};
GetOptions($options, "-f=s", "-p4=s", "-vs");
my $FileList = $options->{f};
my $BuildByVS = $options->{vs};
my $P4On = 1;
my $P4ClientView = "r:";
my $P4Option = lc $options->{p4};
if($P4Option eq "off")
{
	$P4On = 0;
}
else
{
	$P4ClientView = $P4Option;
	
}
# &Trace("P4 On = ", $P4On);
# &Trace("ClientView = ", $P4ClientView);


# Global variables for statistic
my $t0 = [gettimeofday];
my @MissingFiles;
my $TotalFilesNo = 0;
my $UpdatedFilesNo = 0;
my $TotalRemovedIncludesNo = 0;

# if after build for 500 hundred times, we consider this project has build errors originally
# It is not possible that a cpp file include more than 500  headers
my $MaxBuildRound = 500; 

my %CppFiles; # <FileName, (\@FileContents, CurIndex, CompileSuccess, CurInclude, \@Warnings)>
my %Cpp_InitialWarnings; # <FileName, \@Warnings>
my %Cpp_IncludesMap; # <FileName, \@RemovedIncludes>
my %FileAccessExceptionMap; # <FileName, ExceptionInfor> 

# Log file
&StartLog("C:\\RemoveRedundantIncludes_$ProjectNameNoExt.log");
&StartReport("C:\\RemoveRedundantIncludes_$ProjectNameNoExt.txt");

# 1. Get the cpp files to clean and open for edit
&Report(">>>Get all cpp files\n");
&GetCppFiles($ProjectFile, $FileList);

# Batch P4 Edit: faster then edit one by one
my @EditFiles = keys %CppFiles;
$TotalFilesNo = @EditFiles;
&P4BatchEdit(\@EditFiles);
&Report("\t->$TotalFilesNo files need process\n\n");

# Save removed Includes for each cpp file
foreach(keys %CppFiles)
{
	my @RemovedIncludes;
	$Cpp_IncludesMap{$_} = \@RemovedIncludes;
}

# 2. First, Rebuild the project to see if there are any existing errors, and collect the initial warnings
&Report(">>>Rebuild to check the project\n");
my $BuildExec = "BuildConsole.exe $ProjectFile /rebuild \"Debug|Win32\"";
if($BuildByVS)
{
	$BuildExec = "\"%VS90COMNTOOLS%vsvars32.bat\" & devenv $ProjectFile /rebuild \"Debug|Win32\"";
}
my @BuildErrors = `$BuildExec`;
my $InitialRebuild = "*" x 80 . "\n". " " x 30 . "Initial Rebuild" . "\n" . "*" x 80 . "\n\n";
&Log($InitialRebuild);
&Log(@BuildErrors);

# There might be multiple compile errors when compile one cpp file, including errors in header file, we need ascribe the error to the cpp file, like:
#
# FWxFindVersionFileDlg.cpp
# r:\appfw\fwui\controls\FWxFindVersionFileDlg.h(21) : error C2065: 'IDD_FIND_VERSION_FILE_DLG' : undeclared identifier
my $CurCompilingFile; 
foreach(@BuildErrors)
{
	# There are 2 difference between the output of VS and Incredibuild
	# 1. VS error report has a 1> prefix while IncrediBuild doesn't
	# 2. VS error report use relative path while IncrediBuild use absolute path
	if($BuildByVS)
	{
		s/1>//; # Remove the "1>" prefix for errors generated by VS
	}
	
	# Save the cpp file name if the error or warning comes from a header file.
	if(/^(\w+\.[Cc][Pp]{2})\s*$/)
	{
		$CurCompilingFile = $1;
	}
	
	# 1>.\main\VBCxDocumentProject.cpp(349) : error C3861: 'GetCodeText': identifier not found
	# TODO: Take link error into consideration: LINK : 
	# fatal error LNK1104: cannot open file 'r:\lib\Debug\vbc32.dll'
	if(/^(.*?)\((\d*)\) : error (\w*?):/)
	{
		&Report("\tThe project has compile errors->Please check it first\n");
		&EndLog;
		&EndReport;
		exit;
	}
	# R:\AppSupport\AutoCam\AutoCam\AcChangingInTimeValue.cpp(15) : warning C4244: 'initializing' : conversion from 'double' to 'int', possible loss of data
	elsif(/^(.*?)\((\d*)\) : warning (\w*?):/)
	{
		#print join "->", ($1,$2, $3, "\n");
		my $CppFile = $1;
		my $Warning = $3;
		# If current compile error is of a header file (Not .cpp and .c, it is possible that a header file don't have extension), set it to the cpp file which cause the error.
		# No path information for this cpp file
		$CppFile = $CurCompilingFile if($CppFile !~ /(\.cpp)|(\.c)$/i);
		
		$CppFile = lc &basename($CppFile);
		
		# Mark Build error for each file - We assume there is no cpp file with same name in a project. (It should be, or else there will obj file with same name)
		foreach (keys %CppFiles)
		{
			my $FullCppFile = $_;
			if($CppFile eq &basename($FullCppFile))
			{
				if(! $Cpp_InitialWarnings{$FullCppFile})
				{
					my @Warnings;
					$Cpp_InitialWarnings{$FullCppFile} = \@Warnings;
				}
				push @{$Cpp_InitialWarnings{$FullCppFile}}, $Warning;
			}
		}
	}
}
&Report("\tThe project has no build errors, continue...\n");
&DumpWarning;
# 3. Each loop: Comment out one include in all cpp files and build to see if it is safe:
#     1) If no build errors, keep it commented out
#     2) If has build error, revert the comment
#     3) If no build errors and no more includes, this file is finished processing, delete it from the map.
#  Util all the cpp files are processed.
&Report(">>>Update all includes and Build\n");
my $Round = 1;
while((keys %CppFiles) != 0 && $Round <= $MaxBuildRound) # If all the cpp files are processed.
{
	my $RoundRemovedIncludesNo = 0;
	my %SavedIncludeMap;
	foreach my $CppFile (keys %CppFiles)
	{
		my $FileContentsRef = @{$CppFiles{$CppFile}}[0];
		my $CurIndex = @{$CppFiles{$CppFile}}[1];
		my $CompileSuccess = @{$CppFiles{$CppFile}}[2];
		my $CurInclude = @{$CppFiles{$CppFile}}[3];
		
		# If there are build errors, we need to revert the change.
		if(! $CompileSuccess)
		{
			# Add the include we removed before back
			@{$FileContentsRef}[$CurIndex] = $CurInclude;
			#&Trace($CurInclude);
			pop @{$Cpp_IncludesMap{$CppFile}};
		}
		# Comment out next #include (From bottom up)
		my $CommentOutInclude = 0;
		my $InIfDefBlock = 0;
		for(my $i = $CurIndex-1; $i >= 0; $i--)
		{
			$InIfDefBlock++ if(@$FileContentsRef[$i] =~ /\s*#endif/);
			$InIfDefBlock-- if(@$FileContentsRef[$i] =~ /\s*#ifdef /);
			# Next Include not inside a ifdef block, to avoid removing include in other build configurations. (#ifdef _WIN64)
			if($InIfDefBlock == 0 && @$FileContentsRef[$i] =~ /^\s*\#\s*include\s*[\"\<](.*?)\s*[\"\>]/)
			{
				my $IncludeFile = $1;
				if(! &IsProtectedInclude($CppFile, $IncludeFile)) # We won't remove protext files like stdafx.h, system.h...
				{
					# Remove the index and inlcude  in case we need undo the remove
					@{$CppFiles{$CppFile}}[1] = $i; # CurIndex
					@{$CppFiles{$CppFile}}[3] = @$FileContentsRef[$i]; # CurInclude
					
					$CommentOutInclude = 1;
					$RoundRemovedIncludesNo++;

					push @{$Cpp_IncludesMap{$CppFile}}, @$FileContentsRef[$i];
					
					@$FileContentsRef[$i] = undef; # Remove current include
					
					last;
				}
			}
		}
		# if previous compile passes and no more include commented out, this file is finished processing
		# Remove it from the map
		if($CompileSuccess && $CommentOutInclude == 0)
		{
			delete $CppFiles{$CppFile};
			next;
		}
		
		#Write the modified @FileContents back into the file.
		&Log(`attrib $CppFile -r`) if(!$P4On);
		unless (open (CUR_CPP_FILE, ">$CppFile"))
		{
			&FileAccessException($CppFile, $!);
			next;
		}
		foreach my $CurLine (@$FileContentsRef) 
		{
			print CUR_CPP_FILE $CurLine;
		}
		close (CUR_CPP_FILE);
	}
	
	#Compile
	&BuildProject($ProjectFile, $Round);
	my $CompileFailedFilesCount = &GetCompileFailedFilesCount();
	my $RemovedIncludes = $RoundRemovedIncludesNo-$CompileFailedFilesCount;
	my $LeftFilesNo = keys %CppFiles;
	$TotalRemovedIncludesNo += $RemovedIncludes;
	#print "\tRound $Round: $RoundRemovedIncludesNo includes removing; $CompileFailedFilesCount files compile failed; $RemovedIncludes includes Removed.\n";
	&Report("\tRound $Round: Files Left: $LeftFilesNo; Remove: $RoundRemovedIncludesNo ($RemovedIncludes success); Compile Failed Files: $CompileFailedFilesCount\n");
	$Round++;
	
}

# 4. Report
&Report("\t->$TotalRemovedIncludesNo Includes Removed Totally\n");

# Timing
my $ti = Time::HiRes::tv_interval $t0;
my $ElapsedTime = (sprintf "%u:%02u:%02u", $ti/3600, ($ti%3600)/60, ($ti%3600)%60);
&Report("\t->ElapsedTime: $ElapsedTime \n");

# Print the file access exceptions
if(keys %FileAccessExceptionMap)
{
	&Report("\n>>>File Access Exceptions:\n");
	foreach (keys %FileAccessExceptionMap)
	{
		my $ExceptionInfo = $FileAccessExceptionMap{$_};
		&Report("\t$_=>$ExceptionInfo\n");
	}
}
# Print Detailed information
&Report("\n>>>Details\n");
my @RevertedFiles;
foreach (keys %Cpp_IncludesMap)
{
	if(0 == @{$Cpp_IncludesMap{$_}})
	{
		# Revert if no includes removed
		push @RevertedFiles, $_;
	}
	else
	{
		$UpdatedFilesNo++;
		&Report($_, "\n");
		foreach (@{$Cpp_IncludesMap{$_}})
		{
			&Report("\t$_");
		}
	}
}


if(@RevertedFiles > 0)
{
	# Revert unchanged files
	&P4BatchRevert(\@RevertedFiles);
}

# Final Report:
# Project	Total Cpp Files	Cleaned Cpp Files		Removed Includes 	Total Time
my $Titles = sprintf "%-16s" x 5, "ProjectName", "TotalCppFiles", "CleanedCppFiles", "RemovedIncludes", "TotalTime";
my $Values = sprintf "%-16s" x 5, $ProjectNameNoExt, $TotalFilesNo, $UpdatedFilesNo, $TotalRemovedIncludesNo, $ElapsedTime;
&Report(">>>Report\n");
&Report($Titles, "\n");
&Report($Values, "\n");

if($Round == $MaxBuildRound)
{
	&Report(">>>Warnings\n");
	&Report("Build round exceed 500 times, it is most probally that your project has build errors before! ");
	&Report("Build yourself and solve the build errors would be OK!\n");
}
&EndLog();
&EndReport();
#*************************************Functions********************************
# Fill map: %CppFiles (<FileName, (\@FileContents, CurIndex, CompileSuccess)>)
# @p1: project file name
# @p2:optional, a list of file names in a txt file.
sub GetCppFiles($$)
{
	my $PrjPath = $_[0];
	my %FileListMap;
	my $HaveFileList = 0;
	if (defined($_[1]))
	{
		my $FileList = $_[1];
		open FILELIST_FILE, $FileList or die "Unable to open $FileList: $!";
		$HaveFileList = 1;
		foreach(<FILELIST_FILE>)
		{
			chomp;
			$FileListMap{lc $_} = 0;
		}
		close FILELIST_FILE;
	}
	my $PrjDir = &dirname($PrjPath);
	open PROJECT_FILE, $PrjPath or die "Unable to open $PrjPath for read\n $!";
	foreach(<PROJECT_FILE>)
	{
		# 	RelativePath=".\MFCDlgDlg.cpp"
		if(/^\s*RelativePath=\"((.*?)\.[Cc][Pp]{2})\"/)
		{
			my $CppFile = &GetAbsPath($PrjDir,$1);
			next if(&IsOmittedCpp($CppFile));
			
			$CppFile = lc $CppFile;
			
			# First, This file must exist
			if(-e $CppFile)
			{
				# If we provide a file list, we need to ignore it if the file doesn't exist in our list
				if($HaveFileList)
				{
					if(exists $FileListMap{$CppFile})
					{
						#  A file reference in project, listed in the file and really exist in your folder
						# Then this file is really need processed
						$FileListMap{$CppFile} = 1;
					}
					else
					{
						
						next;
					}
				}
				&Report("\t$CppFile\n");
				# Handle both cases with and without file list
				#print $CppFile, "\n";
				my @FileInfo;
				$CppFiles{$CppFile} = \@FileInfo;
				unless (open CPP_FILE, $CppFile)
				{
					&FileAccessException($CppFile, $!);
					next;
				}
				
				my @FileContents = <CPP_FILE>;
				close CPP_FILE;
				push @FileInfo, \@FileContents; # Contents
				push @FileInfo, $#FileContents; # Last Index
				push @FileInfo, 1; # Build Status
				push @FileInfo, undef; # Last Include
				
				#print join " ", @FileInfo, "\n";
			}
			else
			{
				if($HaveFileList)
				{
					# File not exist, but in our list, it is a missing file:
					if(exists $FileListMap{$CppFile})
					{
						push @MissingFiles, $CppFile;
					}
				}
				else
				{
					# When there is no file list provided, a non-exist file is a missing file
					push @MissingFiles, $CppFile;
				}
				
			}
		}
	}
	close PROJECT_FILE;
}

sub GetAbsPath($$)
{
	my $Dir = $_[0];
	my $RelPath = $_[1];
	$RelPath =~ s/^\.\\//;
	return File::Spec->rel2abs($RelPath, $Dir);
}
# Build and update map: %CppFiles
# @p1: project file name
# @p2: round number
sub BuildProject($$)
{
	my $PrjPath = $_[0];
	my $CurRound = $_[1];
	my $BuildExec = "BuildConsole.exe $PrjPath /build \"Debug|Win32\"";
	if($BuildByVS)
	{
		$BuildExec = "\"%VS90COMNTOOLS%vsvars32.bat\" & devenv $PrjPath /build \"Debug|Win32\"";
	}
	my @BuildErrors = `$BuildExec`;
	my $RoundLog = "*" x 80 . "\n". " " x 30 . $CurRound . "\n" . "*" x 80 . "\n\n";
	&Log($RoundLog);
	&Log(@BuildErrors);
	# set all to build pass
	foreach (keys %CppFiles)
	{
		@{$CppFiles{$_}}[2] = 1;
	}
	
	# There might be multiple compile errors when compile one cpp file, including errors in header file, we need ascribe the error to the cpp file, like:
	#
	# FWxFindVersionFileDlg.cpp
	# r:\appfw\fwui\controls\FWxFindVersionFileDlg.h(21) : error C2065: 'IDD_FIND_VERSION_FILE_DLG' : undeclared identifier
	my $CurCompilingFile; 
	
	foreach(@BuildErrors)
	{
		# There are 2 difference between the output of VS and Incredibuild
		# 1. VS error report has a 1> prefix while IncrediBuild doesn't
		# 2. VS error report use relative path while IncrediBuild use absolute path
		if($BuildByVS)
		{
			s/1>//; # Remove the "1>" prefix for errors generated by VS
		}
		
		# Save the cpp file name if the error or warning comes from a header file.
		if(/^(\w+\.[Cc][Pp]{2})\s*$/)
		{
			$CurCompilingFile = $1;
		}
		
		# 1>.\main\VBCxDocumentProject.cpp(349) : error C3861: 'GetCodeText': identifier not found
		if(/^(.*?)\((\d*)\) : error (\w*?):/)
		{
			#print join "->", ($1,$2, $3, "\n");
			my $CppFile = $1;
			
			# If current compile error is of a header file (Not .cpp and .c, it is possible that a header file don't have extension), set it to the cpp file which cause the error.
			# No path information for this cpp file
			$CppFile = $CurCompilingFile if($CppFile !~ /(\.cpp)|(\.c)$/i);
			
			$CppFile = lc &basename($CppFile);
			
			# Mark Build error for each file - We assume there is no cpp file with same name in a project. (It should be, or else there will obj file with same name)
			foreach (keys %CppFiles)
			{
				my $FullCppFile = $_;
				if($CppFile eq &basename($FullCppFile))
				{
					#print "Trace->", $CppFile, "\n";
					
					# Set Build Error
					@{$CppFiles{$FullCppFile}}[2] = 0;
				}
			}
		}
		# R:\AppSupport\AutoCam\AutoCam\AcChangingInTimeValue.cpp(15) : warning C4244: 'initializing' : conversion from 'double' to 'int', possible loss of data
		elsif(/^(.*?)\((\d*)\) : warning (\w*?):/)
		{
			#print join "->", ($1,$2, $3, "\n");
			my $CppFile = $1;
			my $Warning = $3;
			# If current compile error is of a header file (Not .cpp and .c, it is possible that a header file don't have extension), set it to the cpp file which cause the error.
			# No path information for this cpp file
			$CppFile = $CurCompilingFile if($CppFile !~ /(\.cpp)|(\.c)$/i);
			
			$CppFile = lc &basename($CppFile);
			
			# Mark Build error for each file - We assume there is no cpp file with same name in a project. (It should be, or else there will obj file with same name)
			foreach (keys %CppFiles)
			{
				my $FullCppFile = $_;
				if($CppFile eq &basename($FullCppFile))
				{
					if(! @{$CppFiles{$FullCppFile}}[4])
					{
						my @Warnings;
						@{$CppFiles{$FullCppFile}}[4] = \@Warnings;
					}
					push @{@{$CppFiles{$FullCppFile}}[4]}, $Warning;
				}
			}
		}
	}
	#print "Build Errors:\n", @BuildErrors;
	
	# If the file has more warnings than before, we treat it as error
	# TODO: Set the timestamp of the file has warnings, so it will re-compiled
	foreach (keys %CppFiles)
	{
		my $FullCppFile = $_;
		if(@{$CppFiles{$FullCppFile}}[4])
		{
			my $NewWarningNum = @{@{$CppFiles{$FullCppFile}}[4]};
			if(! $Cpp_InitialWarnings{$FullCppFile})
			{
				if( $NewWarningNum > 0)
				{
					# Set Build Error
					@{$CppFiles{$FullCppFile}}[2] = 0;
					#&Trace("$FullCppFile Generate New warnings");
				}
			}
			# compare warning number first, to be more strict, we need compare each element
			elsif($NewWarningNum > @{$Cpp_InitialWarnings{$FullCppFile}})
			{
				# Set Build Error
				#&Trace(scalar @{@{$CppFiles{$FullCppFile}}[4]});
				#&Trace(scalar @{$Cpp_InitialWarnings{$FullCppFile}});
				@{$CppFiles{$FullCppFile}}[2] = 0;
				#&Trace("$FullCppFile Warning Number doesn't match");
			}
			
			my @EmptyList;
			@{@{$CppFiles{$FullCppFile}}[4]} = @EmptyList;
		}
	}
}

sub IsProtectedInclude($$)
{
	my ($CppFile, $IncludedFile) = @_;
	# Following file are must needed and should not be removed.
	if($IncludedFile =~ /(stdafx\.h)|(afxdllx\.h)|(dlldefs\.h)|(system\.h)|(pch\.h)|(\.c)|(initguid\.h)/i)
	{
		return 1;
	}
	# If the header file is of the same name of cpp file, we need to keep it.
	if(lc &FileNameNoExt($CppFile) eq lc FileNameNoExt($IncludedFile))
	{
		return 1;
	}
	
	return 0;
	
}

sub IsOmittedCpp($)
{
	my $CppFile = $_[0];
	if($CppFile =~ /(stdafx\.cpp)/i)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
# Handling when file read or write failed.
sub FileAccessException($$)
{
	my $CppFile = $_[0];
	$FileAccessExceptionMap{$CppFile} = $_[1];
	
	# delete info for this exception file.
	delete $CppFiles{$CppFile};
	delete $Cpp_IncludesMap{$CppFile};
}

sub FileNameNoExt($)
{
	my $FileName = &basename($_[0]);
	return substr($FileName, 0, rindex($FileName, "."));
}
sub GetCompileFailedFilesCount
{
	my $CompileFailedFilesCount = 0;
	foreach (keys %CppFiles)
	{
		if(@{$CppFiles{$_}}[2] == 0)
		{
			$CompileFailedFilesCount++;
		}
	}
	return $CompileFailedFilesCount;
}

sub GetCurView
{
	#return "C:\\Disk\\Inventor\\streams\\Hopper\\dev\\InventorServer4\\sources";
	#return "r:"
	return $P4ClientView;
}
sub _P4LocalToServer($)
{
	my $CurView = &GetCurView();
	my @ServerFiles;
	foreach my $LocalFile (@{$_[0]})
	{
		$LocalFile =~ s/\//\\/g;
		$LocalFile =~ s/^r:/$CurView/i;
		#&Trace($LocalFile );
		push @ServerFiles, $LocalFile;
	}
	
	return @ServerFiles;
}
sub P4BatchEdit($)
{
	my @ServerFiles = &_P4LocalToServer($_[0]);
	
	# It seems when use p4 edit to check out multiple files, the file string we provided can't exceed: 32768
	# It seems it is safe to check out 300 hundred files a time, suppose one file name's length won't exceed 327.68...
	foreach (@ServerFiles)
	{
		my @PartServerFiles = splice (@ServerFiles, 0,100);
		my $ServerFilesStr = join " ", @PartServerFiles;
		my $exec = "p4 edit $ServerFilesStr";
		if($P4On)
		{
			&Log(`$exec`);
		}
		else
		{
			&Log($exec, "\n");
		}
	}
	
}

sub P4BatchRevert($)
{
	my @ServerFiles = &_P4LocalToServer($_[0]);
	
	# It seems when use p4 edit to check out multiple files, the file string we provided can't exceed: 32767
	foreach (@ServerFiles)
	{
		my @PartServerFiles = splice (@ServerFiles, 0,100);
		my $ServerFilesStr = join " ", @PartServerFiles;
		my $exec = "p4 revert $ServerFilesStr";
		if($P4On)
		{
			&Log(`$exec`);
		}
		else
		{
			&Log($exec, "\n");
		}
	}
}

sub Trace
{
	print STDOUT "Trace->", @_, "\n";
}
sub StartReport($){ open REPORT_FILE, ">", $_[0] or die "Can't open log file $_[0]: $!";}
sub Report {print REPORT_FILE @_; print STDOUT @_; }#
sub EndReport(){ close REPORT_FILE;}

sub StartLog($){ open LOGFILE, ">", $_[0] or die "Can't open log file $_[0]: $!";}
sub Log { print LOGFILE @_;}
sub EndLog(){ close LOGFILE;}

sub DumpWarning
{
	foreach(keys %Cpp_InitialWarnings)
	{
		&Trace($_);
		foreach(@{$Cpp_InitialWarnings{$_}})
		{
			&Trace("\t", $_);
		}
	}
}
<STDIN>;
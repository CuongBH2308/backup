#####
#
# Normalize the include statement to follow below rules:
# 	1. Include files in project cone by quoted form from including file to included file (#include "../Main/System.h")
#	2. Include files out of project cone by angle-bracket form through additonal include directories (#include <Include/IFx/Sketch.h>)
#	3. Use forwardslash (per C++ standard)  as  path delimiter (#include <Include/IFx/Sketch.h>)
# 	4. Well Capitalized to be consistent with the filename in filesystem. (#include "pmxselections.h" -> #include "PMxSelections.h")
#	    Note: Currently, we have lots of source files not well named, we will only let the include be consistent with file name if the file name is qualified:
#		    Starts with a capital and contains at least one other capital letter
#		    You can simply change IsQualifiedName return 1 once you want them to be totally consistent.
#	5. No absolute path include. (#include <#include <R:/Server/Framework/Utx/UTxVersionNumber.h> -> #include "UTxVersionNumber.h")
#	6.  No unnecessary spaces. (#@include@"@System.h", we can have space in the place that marks "@", but only the 2nd one is accepted)
#
# Author: Baiyan Huang
# Date: 12/22/2008
# 
# Usage:
# NormalizeIncludeStatements.pl <Project> [<File>] [-p4 <RootForR>]
# NormalizeIncludeStatements.pl R:\Application\Uc\Uc.vcproj
# NormalizeIncludeStatements.pl R:\Application\Uc\Uc.vcproj R:\Application\Uc\Main\UCxSceneDocUI.h
# NormalizeIncludeStatements.pl R:\Application\Uc\Uc.vcproj R:\Application\Uc\Main\UCxSceneDocUI.h -p4 "C:\Disk\Inventor\Main\Sources"
# 
# Note:
# To get the right include directories, you need to:
# 	1. Run from "Start CMD with Debug Inventor Environment"
#	2. Run "%VS90COMNTOOLS%\vsvars32.bat"
# For Inventor projects, make sure you project referenced by R: , not its real path.
#
# TODO:
# 
# 1. Reorder the Includes -- High Risk
#
#####
use strict;
use File::Basename;
use Getopt::Long;
BEGIN{push @INC, &dirname($0);}
use Utils::Basic;
use Utils::VS;
use Utils::P4;
use Utils::VSProject;

#**********************************************************Main********************************************************
&StartTiming();

# Get P4 options
&Getopt::Long::Configure("prefix_pattern=(-|\/)");
my ($options) ={};
&GetOptions($options, "-help|h|?", "-p4=s");

# Show help
if ($options->{help})
{
	Syntax();
	exit;
}

# Initialization:
&VS::SetConfig("Debug|Win32", "Debug");
my $OutputDir = &::GetTempDir() . "\\NormalizeIncludeStatements";
mkdir $OutputDir unless(-d $OutputDir);
my $ProjectPath = @ARGV[0];
my $ProjectNameNoExt = &FileNameNoExt(&basename($ProjectPath));
&StartReport("$OutputDir\\$ProjectNameNoExt.txt");
warn "\nYou are not include from R:, might cause problems!!!\n" if($ProjectPath !~ /^R:[\\\/]/i);
#Redirect_STDERR("$OutputDir\\$ProjectNameNoExt.err");

my @IncludeDirs;
my %StandardDirs;
{
	my @TempStandardDirs = &VS::GetStandardDirs();
	foreach(@TempStandardDirs)
	{
		#print $_, "\n";
		$StandardDirs{lc &Slashlize($_)} = 1;
	}
	
	# [IS: Temp Change]
	# High-Level directories should be considered as "standard" here
	$StandardDirs{"r:/appfw"} = 1;
	$StandardDirs{"r:/application"} = 1;
	$StandardDirs{"r:/appsupport"} = 1;
	$StandardDirs{"r:/shellext"} = 1;
	$StandardDirs{"r:/xlayer"} = 1;
}
my $ProjectDir = &dirname($ProjectPath);
my $File = @ARGV[1];
my %ProblematicInclude;
my @RealyOnlyFiles;


my $P4RootForR = $options->{p4};
if(defined $P4RootForR)
{
	&P4::P4On();
	if($P4RootForR !~ /^\s*r:/i)
	{
		# "C:\\Disk\\Inventor\\streams\\Hopper\\dev\\InventorServer4\\sources"
		&P4::Subst("R:", $P4RootForR);
	}
}
else
{
	&P4::P4Off();
}

# 1. Get source files to process
&Report("\n>>>Get source files to process\n");
my @ProjectFiles;
if($File)
{
	push @ProjectFiles, $File;
}
else
{
	@ProjectFiles = &VS::GetProjectFiles($ProjectPath, 0);
}

# Get valid source files.
my @ValidSrcFiles;
foreach (@ProjectFiles)
{
	if(-f $_)
	{
		if(&VS::IsVSSrcFile($_))
		{
			push @ValidSrcFiles, $_;
		}
	}
}

my $TotalNum = @ValidSrcFiles;
&Report("\t->Total Files: $TotalNum\n");

# 2 P4: Open Files for edit
&Report("\n>>>Open files for edit.\n");

&P4::P4BatchEdit(@ValidSrcFiles);

# 3. Normalize includes for each file
my $thisProject = VSProject->new($ProjectPath);
@IncludeDirs = $thisProject->GetIncludeDirs();
#print join "\n", @IncludeDirs;

&Report("\n>>>Normalize includes for each file\n");
foreach my $EachFile (@ValidSrcFiles)
{
	if(! &IsProtectedFile($EachFile))
	{
		&Report("\tNormalizing $EachFile\n");
		if(-w $EachFile) # If the file is writalbe
		{
			&OverwriteFile($EachFile, \&NormalizeIncludesHandler);
		}
		else
		{
			push @RealyOnlyFiles, $EachFile;
		}
	}
}

# 4. Revert unchanged files
&Report("\n>>>Revert unchagned files.\n");
&P4::P4BatchRevert(\@ValidSrcFiles, "-a");

# 5. Output readonly files that not updated 
&Report("\n>>>Readonly files that not updated.\n");
foreach(@RealyOnlyFiles)
{
	&Report("\t$_\n");
}
# 6. Output the includes that can't be located
&OutputUnSafeIncludes();

my $ElapsedTime = &EndTiming();
&Report("\n>>>Elapsed Time: $ElapsedTime\n");

&EndReport();
#&Pause();

#********************************************************Functions******************************************************
# Normailize include statment for a file content
# @p1: File Contents arrary
# @return: Updated file content string
sub NormalizeIncludesHandler($$)
{
	my @FileContent = @{$_[0]};
	my $FileName = $_[1];
	my $FileDir = &dirname($FileName);
	$thisProject->AddInheritedDir($FileDir);
	my $FileContentStr;
	our $IsQuotedForm = 1;
	foreach my $Line (@FileContent)
	{
		if(($Line =~ /^(\s*?)#\s*include\s*\"(.*?)\s*\"(.*)(?{$IsQuotedForm = 1})$/s) || 
		   ($Line =~ /^(\s*?)#\s*include\s*<(.*?)\s*>(.*)(?{$IsQuotedForm = 0})$/s)) # /s to keep the "\n"
		{
			my $Indent = $1;
			my $RelativePath = $2;
			my $Comments = $3;
			
			#&Trace("IsQuotedForm = ", $IsQuotedForm);
			
			my $Include;
			
			# If it is an absolute include, translate it to relative 
			if(&IsAbsoluteInclude($RelativePath))
			{
				$RelativePath = &GetRelPath($FileDir, $RelativePath);
				$IsQuotedForm = 1; # We don't want this file to be included by "<>", it might be unsafe
			}
			
			if(&IsProtectedInclude($RelativePath))
			{
				# Currently, Just handle StdAfx.h, you may can't locate it because of PCH.
				$RelativePath =~ s/stdafx\.h$/StdAfx\.h/i;
				$Include = "#include \"$RelativePath\"";
			}
			else
			{
				# Get Absolute Path
				my $IncludeFromInheritedDir;
				my $AbsPath;
				if($IsQuotedForm)
				{
					$AbsPath = $thisProject->GetAbsPath_Inherited($RelativePath);
					if($AbsPath)
					{
						$IncludeFromInheritedDir = 1;
					}
					else
					{
						$IncludeFromInheritedDir = 0;
						$AbsPath = &GetAbsPath_Standard($RelativePath, $FileName);
					}
				}
				else
				{
					$AbsPath = &GetAbsPath_Standard($RelativePath, $FileName);
					#&Trace($AbsPath);
					if($AbsPath)
					{
						$IncludeFromInheritedDir = 0;
					}
					else
					{
						$IncludeFromInheritedDir = 1;
						$AbsPath = $thisProject->GetAbsPath_Inherited($RelativePath);
					}
				}
				
				# If the included file can be located
				if($AbsPath)
				{
					my $TmpAbsPath = &Capitalize($AbsPath);
					#$AbsPath = $TmpAbsPath if(&IsQualifiedName($TmpAbsPath)); # If it is not the qualified name, we will simply keep the orginal one.
					
					# Compare the 2 and adopt the better one
					$AbsPath = &BeautifyAbsPath($TmpAbsPath, $RelativePath);
				
					# If the file is inside the project cone
					if(&IsInProjectCone($AbsPath, $FileName)) # ""
					{
						my $NewRelPath = &GetRelPath($FileDir, $AbsPath); # Calculate the relative path
						$Include = "#include \"$NewRelPath\"";
					}
					# If the file is outside of project cone, there are 2 cases:
					# 1. The file is included from inherit directories by long relative path, such as: "../../FwUIRes/Resource.h"
					# 2. The file is included from standard directories
					else # <>
					{
						my $TmpRelPath = &SyncCapWithAbsPath($RelativePath, $AbsPath);
						$RelativePath  = $TmpRelPath if(&IsSamePath($TmpRelPath, $RelativePath)); # If we sync the path correctly
						
						# Case 1: 
						# Relative: "../../FwUIRes/Resource.h"
						# Abs:         "R:/AppFw/FwUIRes/Resource.h"
						# Standard: <FwUIRes/Resource.h>
						if($IncludeFromInheritedDir)
						{
							$Include = &IncludeFromBestDir($RelativePath, $AbsPath, $FileName, 1);
						}
						# Case 2:
						else
						{
							# It is possible that we include a file like following:
							# #include <../../FwUIRes/Resource.h>
							# Let correct it here
							if($RelativePath =~ /^\.\./)
							{
								$Include = &IncludeFromBestDir($RelativePath, $AbsPath, $FileName, 0);
							}
							else
							{
								$Include = "#include <$RelativePath>";
							}
						}
					}
				}
				else
				{
					# Files from 3rd party and VS standard might not be found if we don't run: we usually use angle brankets here "<>"
					# 1. Start CMD with Debug Inventor Environment
					# 2. "%VS90COMNTOOLS%vsvars32.bat"
					$Include = $IsQuotedForm ? "#include \"$RelativePath\"" : "#include <$RelativePath>";
					# Just ignore it if we can't locate the file
					if(! exists $ProblematicInclude{$FileName})
					{
						my @Includes;
						$ProblematicInclude{$FileName} = \@Includes;
					}
					push @{$ProblematicInclude{$FileName}}, $Line;
				}
			}
			
			$Include = &Slashlize($Include);
			$Line = $Indent . $Include . $Comments; # let's keep the indent because it might be indented for #ifdef
		}
		$FileContentStr .= $Line;
	}
	
	$thisProject->ClearInheritedDir();
	return $FileContentStr;
}

# Include a file outside project cone using the Best include directory.
#	1. The file is included using relative path: "../../FwUIRes/Resource.h"
#	2. The file is included using "<>", but has "../" at the begining: <../../FwUIRes/Resource.h>
# use the original one if failed to include from the longest include directory
#	1. Don't have a dir 
#	2. Have a dir but not in standard dir
#	3. The result path still start with "../"
sub IncludeFromBestDir($$$$)
{
	my($RelativePath, $AbsPath, $IncludingFile, $IsQuotedForm) = @_;
	my $ResultInclude = $IsQuotedForm ? "#include \"$RelativePath\"" : "#include <$RelativePath>"; # Default include
	my @CandidateDirs;
	foreach my $IncludeDir (@IncludeDirs)
	{
		push @CandidateDirs, $IncludeDir if(&IsStartWith($AbsPath, $IncludeDir));
	}
	@CandidateDirs = sort {length $b <=> length $a} @CandidateDirs; # Sort the array so the longest string is at the begining;
	if(@CandidateDirs >= 1)
	{
		# The desired Dir should be the longest candidate which is also in @StandardIncludes
		# Longest one is not always the best one, it might end up with include statement: <../UcRes/Resouce.h>
		my $SelectedDir;
		foreach my $EachDir (@CandidateDirs)
		{
			if(exists $StandardDirs{lc &Slashlize($EachDir)})
			{
				$SelectedDir = $EachDir;
				last;
			}
		}
		if(defined ($SelectedDir))
		{
			my $StandardRelPath = &::GetRelPath($SelectedDir, $AbsPath);
			if($StandardRelPath !~ /^\.\./) # make sure the refined include path doesn't start with "..", or else let use the default.
			{
				$ResultInclude = "#include <$StandardRelPath>";
			}
		}
	}
	
	return $ResultInclude;
}
sub BeautifyAbsPath($$)
{
	my ($AbsPath, $RelativePath) = @_;
	$RelativePath = &PurifyRelativePath($RelativePath);
	my @RelFolders = split /\\|\//, $RelativePath;
	#Trace("RelFolders: ", join " ", @RelFolders);
	my $RelCount = @RelFolders ;
	my @AbsFolders = split /\\|\//, $AbsPath;
	#Trace("AbsFolders: ", join " ", @AbsFolders);
	my $AbsCount = @AbsFolders;
	my $Num = 0;
	for(my $i = $RelCount - 1; $i >= 0; $i--)
	{
		$Num++;
		#Trace(@RelFolders[$i], "	", @AbsFolders[$AbsCount - $Num]);
		if(lc @RelFolders[$i] eq lc @AbsFolders[$AbsCount - $Num])
		{
			# If the the one in relative path is more beautiful than the one in abs path, let's use it
			if(&IsQualifiedName(@RelFolders[$i] ) && (! &IsQualifiedName(@AbsFolders[$AbsCount - $Num])))
			{
				
				@AbsFolders[$AbsCount - $Num] = @RelFolders[$i];
				#Trace(@RelFolders[$i], "	", @AbsFolders[$AbsCount - $Num]);
			}
		}
	}
	
	$AbsPath = join "\\", @AbsFolders;
	return $AbsPath;
}

# Qualified name should be well captalized
# Currently, we have file names that all with lowercase and uppercase, we need to ignore these cases.
# Here a qualified name should be: starts with a capital and contains at least one lowercase character
sub IsQualifiedName($)
{
	my $AbsPath = $_[0];
	my $PureFileName = &basename($AbsPath);
	# Not all upper case and all lowercase means qualified
	if($PureFileName =~ /^[A-Z]/ && $PureFileName =~ /^[^.]+[a-z]/)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

sub PurifyRelativePath($)
{
	my $RelativePath = $_[0];
	
	$RelativePath =~ s/\.\.\\//g;
	$RelativePath =~ s/\.\.\///g;
	$RelativePath =~ s/\.\\//g;
	$RelativePath =~ s/\.\///g;
	
	return $RelativePath;
}

sub IsAbsoluteInclude($)
{
	my $FileName = $_[0];
	if($FileName =~ /^\s*?[A-Za-z]:/)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
# Get the exact match of the result abs path according to VS's rule
sub GetAbsPath_Standard($$)
{
	my $RelativePath = $_[0];
	my @AbsPaths = $thisProject->GetAbsPath_Standard($RelativePath);
	if(@AbsPaths == 1)
	{
		return @AbsPaths[0];
	}
	else
	{
		my $InlcudingFile = $_[1];
		my $Count = @AbsPaths;
		my (@InCone, @OutCone);
		foreach(@AbsPaths)
		{
			if(&IsInProjectCone($_, $InlcudingFile))
			{
				push @InCone, $_
			}
			else
			{
				push @OutCone, $_;
			}
		}
		# When include using "<>", files out of project cone is of high priority
		if(@OutCone >= 1)
		{
			#&Trace("OutCone");
			return @OutCone[0];
		}
		else
		{
			return @InCone[0];
		}
	}
}

sub OutputUnSafeIncludes()
{
	&Report("\n>>>Following Inlcudes might be unsafe:\n");
	for my $EachFile (keys %ProblematicInclude)
	{
		&Report($EachFile, "\n");
		foreach my $MyInclude (@{$ProblematicInclude{$EachFile}})
		{
			&Report("\t$MyInclude");
		}
		&Report("\n");
	}
}

# regardless of capitalization and slash
sub IsSamePath($$)
{
	my ($Path1, $Path2) = @_;
	$Path1 = &Slashlize($Path1);
	$Path2 = &Slashlize($Path2);
	if(lc $Path1 eq lc $Path2)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

sub IsStartWith($$)
{
	my ($AbsPath, $IncludeDir) = @_;
	$AbsPath = &Slashlize($AbsPath);
	$IncludeDir = &Slashlize($IncludeDir);
	if($AbsPath =~ /^$IncludeDir/i)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
# Update the relative path to be same capitalization of the abspath.
sub SyncCapWithAbsPath($$)
{
	my ($RelativePath, $AbsPath) = @_;
	$RelativePath = &Slashlize($RelativePath);
	
	my $OriginRelativePath = $RelativePath;
	
	# Remove the ../ prefix
	$RelativePath =~ s/\.\.//g;
	$RelativePath =~ s/\/(?=\/)//g;
	
	# Make it a pattern because of the the "/"
	my $RelativePathPattern = $RelativePath;
	$RelativePathPattern =~ s/\//\\\//g;
	
	my $CapitalizedRelativePath = &Slashlize($AbsPath);
	
	# Get the relative path in the abs path
	$CapitalizedRelativePath =~ s/.*?(?=$RelativePathPattern)//i;
	
	$OriginRelativePath =~ s/$RelativePathPattern$/$CapitalizedRelativePath/i;
	
	return $OriginRelativePath;
	
}
# Change all backslash("\") to forwardslash ("/")
sub Slashlize($)
{
	my $Path = $_[0];
	$Path =~ s/\\/\//g;
	return $Path;
}

# Change the case of the path to be consistent with the real filename in filesystem
sub Capitalize($)
{
	# R:/Server/CoreApps/UcSrv/Uc.cpp
	my $AbsPath = &Slashlize($_[0]);
	
	my @Paths = split /\//, $AbsPath;
	my $Driver = shift @Paths;
	my $FileName = pop @Paths;
	
	my $ResultPath = uc $Driver;
	
	# We have to use "\" when dir in windows
	$ResultPath .= "\\";

	# Dir to get each folder name that well captalized
	foreach my $Path (@Paths)
	{
		my @Dirs = `dir \"$ResultPath\" /b /ad-h-s`;
		chomp @Dirs;
		foreach my $Dir (@Dirs)
		{
			if(lc $Dir eq lc $Path)
			{
				$Path = $Dir;
			}
		}
		
		$ResultPath .= $Path;
		$ResultPath .= "\\" ;
	}
	
	# Dir to get the file name that well captalized
	my $FullName = $ResultPath . $FileName;
	$FileName = `dir /b \"$FullName\"`; 
	$ResultPath .= $FileName;

	chomp $ResultPath;
	#&Trace($ResultPath);
	return $ResultPath;
}

sub IsInProjectCone($$)
{
	my $AbsPath = $_[0];
	my $IncludingFile = $_[1];
	# &::Trace($AbsPath);
	# &::Trace($IncludingFile);
	# [IS: Temp Change]
	# Drawing Projecct special treatement
	if($AbsPath =~       /^R:[\\\/]Server[\\\/]CoreApps[\\\/](?=Dl|DlAc|DlDim|DlRequests|DlSym|DlView|DxSrv)/i &&
	   $IncludingFile =~ /^R:[\\\/]Server[\\\/]CoreApps[\\\/](?=Dl|DlAc|DlDim|DlRequests|DlSym|DlView|DxSrv)/i)
	{
		my @Folders = split /[\\\/]/, $AbsPath;
		my $Proj1 = @Folders[3];
		@Folders = split /[\\\/]/, $IncludingFile;
		my $Proj2 = @Folders[3];
		if(lc $Proj1 eq lc $Proj2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	 # Agm special treatement
	elsif($AbsPath =~       /^R:[\\\/]Server[\\\/]Framework[\\\/]Agm[\\\/]/i &&
	      $IncludingFile =~ /^R:[\\\/]Server[\\\/]Framework[\\\/]Agm[\\\/]/i)
	 {
		return 1;
	 }
	# Gr  & GrData Special treatment
	elsif($AbsPath =~       /^R:[\\\/]Server[\\\/]Framework[\\\/]Gr[\\\/]/i &&
	      $IncludingFile =~ /^R:[\\\/]Server[\\\/]Framework[\\\/]Gr[\\\/]/i)
	 {
		return 1;
	 }
	#Sm  & SmViewer Special treatment - TODO
	 
	# Fix a defect:
	# Project Dir = R:/AppFw/FwUI
	# AbsPath      = R:/AppFw/FwUIRes/Resource.h
	# It is outside the project cone, but we treated it as inside....
	# Add a slash at the end of the project dir to avoid such situation.
	return IsStartWith($AbsPath, $ProjectDir . "/");

}

sub IsProtectedInclude($)
{
	my $RelPath = $_[0];
	if($RelPath =~ /stdafx\.h/i || $RelPath =~ /pch\.h/i)  # stddckernelpch.h; stdrdpch.h
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

# We don't need to process this file
sub IsProtectedFile($)
{
	return 0;
}

sub Syntax()
{
    my ($Script) = ( $0 =~ /([^\\\/]*?)$/ );
    my ($Line)   = "-" x length($Script);

    print <<EOT;

$Script
$Line
Normalize Include Statements.

Syntax:
$Script <Project> [<File>] [-p4 <RootForR>]
<RootForR>: The real path of you "R:" driver, simply provide "R:" if your P4 root is "R:".

Example:
$Script R:\\Application\\Uc\\Uc.vcproj
$Script R:\\Application\\Uc\\Uc.vcproj R:\\Application\\Uc\Main\\UCxSceneDocUI.h
$Script R:\\Application\\Uc\\Uc.vcproj R:\\Application\\Uc\Main\\UCxSceneDocUI.h -p4 "C:\\InvSrc"
$Script R:\\Application\\Uc\\Uc.vcproj R:\\Application\\Uc\Main\\UCxSceneDocUI.h -p4 "R:"

Contact Baiyan Huang for defect/support
EOT
}
#####
#
# Visual Studio operations utilities.
#
# Author: Baiyan Huang
# Date: 12/26/2008
#
#####

use strict;
use File::Basename;
use XML::Simple;
BEGIN{push @INC, &dirname($0);}
use Utils::Basic;

package VS;

my $Config; # = "Debug|Win32";
my $ConfigName; # = "Debug";

sub SetConfig($$)
{
	$Config = $_[0];
	$ConfigName = $_[1];
}

sub IsVSSrcFile($)
{
	$_ = $_[0];
	if(/\.h$/i || /\.cpp$/i || /\.rc/i || /\.rc2/i || /\.c$/i ||/\.hpp$/i || /\.hh$/i || /\.hxx$/i || /\.cc$/i || /\.cxx$/i)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
sub IsHeaderFile($)
{
	$_ = $_[0];
	if(/\.h$/i || /\.hpp$/i || /\.hh$/i || /\.hxx$/i)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
sub IsCppFile($)
{
	$_ = $_[0];
	if(/\.cpp$/i || /\.c$/i || /\.cc$/i || /\.cxx$/i)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
# *.sln
sub IsSolutionFile($)
{
	my $FileName = $_[0];
	return 1 if($FileName =~ /\.sln$/i);
	return 0;
}

#*.vcproj
sub IsProjectFile($)
{
	my $FileName = $_[0];
	return 1 if($FileName =~ /\.vcproj$/i);
	return 0;
}

#*.dll, *.exe
sub IsImageFile($)
{
	my $FileName = $_[0];
	return 1 if($FileName =~ /\.exe$/i || $FileName =~ /\.dll$/i );
	return 0;
}

# Get files a project referenced
# @p1: Project file name
sub GetProjectFiles($)
{
	my @ProjectFiles;
	my $ProjectPath  = $_[0];
	my $ProjectDir = &::dirname($ProjectPath);
	open PROJECT_FILE, $ProjectPath or die "Can't open $ProjectPath for read: $!";
	foreach my $Line (<PROJECT_FILE>)
	{
		# RelativePath="..\..\Server\CoreApps\Cm\Browser\AliasLinkEntry.cpp"
		if($Line =~ /^\s*RelativePath=\"(.*?)\"/)
		{
			my $RelativePath = $1;
			my $AbsPath = &::GetAbsPath($ProjectDir, $RelativePath);
			#&Report("\t$AbsPath\n");
			push @ProjectFiles, $AbsPath;
		}
	}
	close PROJECT_FILE;
	return @ProjectFiles;
}

sub GetSolutionProjects($)
{
	my @VsProjs;
	my $SlnFile = $_[0];
	my $SlnDir = &::dirname($SlnFile);
	open CUR_SLNFILE, $SlnFile or die "Can't open solution $SlnFile: $!";
	foreach(<CUR_SLNFILE>)
	{
		# Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "RegisterTLB Tool", "XInterface\src\RegisterTLB\RegisterTLB.vcproj", "{2EFCC20E-F827-4FA5-A2E7-319B6514416F}"
		# ProjectSection(ProjectDependencies) = postProject
			# {05AA961A-8760-4ED7-ADF0-DC94394089A0} = {05AA961A-8760-4ED7-ADF0-DC94394089A0}
			# {244805E6-D245-47D4-894E-D0B0936C15D7} = {244805E6-D245-47D4-894E-D0B0936C15D7}
		# EndProjectSection
		# EndProject
		if(/Project\(\"(.*)\"\).*?,\s*\"(.*?)\"/)
		{
			my $PrjPath = $2;
			if($PrjPath =~ /^[a-zA-Z]:\\/i) # Absolute path
			{
				push @VsProjs, $PrjPath;
			}
			else # Relative path
			{
				push @VsProjs, &::GetAbsPath($SlnDir, $PrjPath);
			}
		}
		
	}
	close CUR_SLNFILE;
	
	return @VsProjs;
}

# @p1: Project name
# @p2: Configuration
sub GetProjectOutput($)
{
	my $Project = $_[0];
	my $PrjNameNoExt = &::FileNameNoExt($Project);
	my $PrjDir = &::dirname($Project);
	my $OutputFile;
	my $OutputDir;
	my $InConfig = 0;
	my $AfterConfig = 0;
	open PROJECT_FILE, $Project or die "Can't open $Project: $!";
	foreach(<PROJECT_FILE>)
	{
		# Name="Optimize|Win32"
		if(/^\s*Name=\"([\w\d]+\|[\w\d]+)\"/)
		{
			if(lc $1 eq lc $Config)
			{
				$InConfig = 1;
			}
			else
			{
				if($InConfig)
				{
					$InConfig = 0;
					$AfterConfig = 1;
				}
			}
			next;
		}
		
		if($InConfig)
		{
			# OutputDirectory="r:\lib\debug"
			if(/^\s*OutputDirectory=\"(.*?)\"/)
			{
				$OutputDir = $1;
				#&::Trace("OutputDir = $OutputDir");
			}
			# OutputFile="r:\lib\Optimize\Ag.dll"
			if(/^\s*OutputFile=\"(.*?)\"/)
			{
				$OutputFile = $1;
			}
		}
		
		if($AfterConfig)
		{
			$OutputFile = "\$(OutDir)\\\$(ProjectName).dll" unless(defined ($OutputFile));
			
			#&Trace($OutputFile);
			$OutputFile =~ s/\//\\/g; # "/" -> "\"
			$OutputFile =~ s/\$\(OutDir\)/$OutputDir/; # translate macro: $(OutDir), it should be handled first.
			$OutputFile =~ s/\$\(ProjectName\)/$PrjNameNoExt/; # translate macro: $(ProjectName) - project name
			$OutputFile =~ s/\$\(ConfigurationName\)/$ConfigName/; # translate macro: $(ConfigurationName)
			
			unless ($OutputFile =~ /^[A-Za-z]:/)
			{
				$OutputFile = &::GetAbsPath($PrjDir, $OutputFile); # Relative to Absolute
			}
			last;
		}
	}
	close PROJECT_FILE;
	$OutputFile =~ s/\\/\//g;
	return $OutputFile;
}

# Param1: the old project file
# Param2: the new project file
sub MoveProjectFile($$)
{
	my $OldProjectFile = @_[0];
	my $NewProjectFile = @_[1];

	# the source file must exist.
	die "File $OldProjectFile doesn't exist!!!\n" unless (-f $OldProjectFile);

	# Can't move project file across drivers.
	my ($OldVolume,undef,undef) = File::Spec->splitpath($OldProjectFile);
	my ($NewVolume,undef,undef) = File::Spec->splitpath($NewProjectFile);
	die "Can't move project file to another driver!!!\n" if($OldVolume != $NewVolume) ;

	# Get directory and Move the file
	my $OldDir = &dirname($OldProjectFile);
	my $NewDir = &dirname($NewProjectFile);

	# Copy, but not move for convenience
	#rename $OldProjectFile, $NewProjectFile or die "Can't move file $OldProjectFile to $NewProjectFile: $!";
	&copy( $OldProjectFile, $NewProjectFile) or die "Can't copy file $OldProjectFile to $NewProjectFile: $!"; 

	#Operator on $NewProjectFile
	my @BackupARGV = @ARGV;
	@ARGV = ($NewProjectFile);
	$^I = "*.bak";
	while(<>)
	{
		#$_ =" 			ModuleDefinitionFile=\"GRData.def\"";
		#$_ = "		RelativePath=\"linestyle.h\"";
		my $OldRelPath;
		if(/^\s*RelativePath=\"(.*)\"\s*$/) {$OldRelPath = $1;} #referenced file's relative path
		elsif(/^\s*ModuleDefinitionFile=\"(.*)\"\s*$/) {$OldRelPath = $1;} #ModuleDefinitionFile's relative path
		if($OldRelPath)
		{
			#replace the old relative path with new relative path.
			my $i = rindex($_, $1);
			substr($_, $i, length($1)) = &MakeNewRelPath($NewDir, $OldDir, $1);
		}
		
		print;
		
		# if($ARGV=~/vbc/)
		# {
			# print STDOUT $_, "\n";
		# }
	}
	# Restore ARGV
	@ARGV = @BackupARGV;
	
	return;
}

# Translate the env variables into its value in the input string
sub TranslatePath($)
{
	my $PathWithEnvVar = @_[0];
	#print $PathWithEnvVar;
	my @Macros = $PathWithEnvVar =~ /\$\((.*?)\)/;

	foreach(@Macros)
	{
		$ENV{uc $_} = "\$" . "(". $_ . ")" unless(exists $ENV{uc $_});
	}
	$PathWithEnvVar =~ s/\$\((.*?)\)/$ENV{uc($1)}/g;
	return $PathWithEnvVar;
}
# Get the  Include Dir, it comes from:
# 	1. Project's AdditionalIncludeDirectories for Debug|Win32 version
#	2. INCLUDE env variables
# @P1: Project file.
# @Return: A arrary of standard include dirs
sub GetIncludeDirs($)
{
	my $ProjFile = $_[0];
	my @IncludeDirs;
	
	# 1. Insert user macros in server props to %ENV
	my $ServerVsProps = "R:\\Server\\ServerProperties.vsprops";
	if(-f $ServerVsProps)
	{
		my $config = XML::Simple::XMLin($ServerVsProps);
		foreach my $MapRef (@{$config->{UserMacro}})
		{
			$ENV{$MapRef->{Name}} = $MapRef->{Value}
		}
	}
	
	# 2. Get AdditionalIncludeDirectories from project setting.
	open CUR_PROJFILE, $ProjFile or die "Can't open project $ProjFile: $!";
	my $DebugWin32 = 0;
	my $VCCLCompilerTool = 0;
	foreach(<CUR_PROJFILE>)
	{
		#	Name="Debug|Win32"
		if(/^\s*Name=\"$Config\"\s*$/)
		{
			$DebugWin32 = 1;
		}
		if(1 == $DebugWin32)
		{
			# Name="VCCLCompilerTool"
			if(/^\s*Name=\"(.*?)\"\s*$/)
			{
				if($1 eq "VCCLCompilerTool")
				{
					$VCCLCompilerTool = 1;
				}
				else
				{
					# make sure we won't read-in resource compiler's additional include dir
					$VCCLCompilerTool = 0;
				}
				
			}
			if($VCCLCompilerTool == 1)
			{
				# AdditionalIncludeDirectories="R:\Environment\DevStudio\VC.Net\include;r:\;R:\Server\Framework;r:\xinterface\bin;R:\Server\Support\Vba\Include;R:\Server\Support\Include;R:\Server\Support;R:\AppFw\VBCUI"
				if(/^\s*AdditionalIncludeDirectories=\"(.*)\"\s*$/)
				{
					my $PrjIncludeDirStr = $1;
					&::Trace($PrjIncludeDirStr);
					$PrjIncludeDirStr =~ s/&quot;//g;
					$PrjIncludeDirStr = &TranslatePath($PrjIncludeDirStr);
					#&::Trace($PrjIncludeDirStr);
					@IncludeDirs = split /;|,/, $PrjIncludeDirStr;
					print join "\n", @IncludeDirs;
					s/\s+//g; # Remove unnecessary spaces.
					last;
				}
			}
		}
	}
	close CUR_PROJFILE;
	
	# 3. Get INCLUDE
	my $VSIncludeDirStr = $ENV{"INCLUDE"};
	my @VSIncludeDirs = split /;/, $VSIncludeDirStr;
	push @IncludeDirs, @VSIncludeDirs;
	
	return @IncludeDirs;
	
}

# Standard Include Dirs: VSInlclude + RequiredIncludes + ServerIncludes
sub GetStandardDirs()
{
	my @StandardDirs;
	
	# VSIncludes
	my $VSIncludeDirStr = $ENV{"INCLUDE"};
	my @VSIncludeDirs = split /;/, $VSIncludeDirStr;
	push @StandardDirs, @VSIncludeDirs;
	
	my $ServerVsProps = "R:\\Server\\ServerProperties.vsprops";
	if(-f $ServerVsProps)
	{
		my $config = XML::Simple::XMLin($ServerVsProps);
		foreach my $MapRef (@{$config->{UserMacro}})
		{
			# RequiredIncludes
			if($MapRef->{Name} eq "RequiredIncludes")
			{
				my @RequiredIncludes = split /;/, $MapRef->{Value};
				push @StandardDirs, @RequiredIncludes;
			}
			# ServerIncludes
			elsif($MapRef->{Name} eq "ServerIncludes")
			{
				my @ServerIncludes = split /;/, $MapRef->{Value};
				push @StandardDirs, @ServerIncludes;
			}
		}
	}
	return @StandardDirs;
}
#****************************************************************************************************

return 1;
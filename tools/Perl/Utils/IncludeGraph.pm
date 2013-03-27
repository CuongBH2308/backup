#####
#
# A directed graph representation of VS's include relation: each file is a vertex, and each include relation is edge
#
# Author: Baiyan Huang
# Date: 12/26/2008
#
#####

use strict;
use File::Basename;
use File::Spec;
use XML::Simple;
use Data::Dumper;

BEGIN{push @INC, &dirname($0);}
use Utils::VS;

#********************************************************************************************************
#*****************************************Include Graph***************************************************
#********************************************************************************************************
#####
#
# The included files of a source in fact is a directed graph.
# Vertex = Included File
# Edge = Include Relation. (Directed)
# For example, file A.cpp include B.h:
#  (A.cpp)---->(B.h)
#
#####
package IncludeGraph;
###############################Data Memembers##########################
my %VerticesMap; #<FileName, Visited>, value type: <string, bool>
my @VerticesList;

my @Edges; #Each element is another Array, value type: int

my @AllPaths;

my @CurPath;
my %CurPathMap; # For performace

my @StandardDirs; # Directories to locate those included files
my @InheritedDirs;

###############################Graph Public Members##########################
# Build the graph of the included files of current file
# @p1: Project File
# @p2: source file name
sub BuildGraph($$)
{
	# Get standard include dirs. /I and INCLUDE
	@StandardDirs = &GetIncludeDirs($_[0]);
	
	# Insert current file as the first vertex
	&InsertVertex($_[1]);
	
	# Recursively Parse Inclucded files and build the graph.
	&ParseIncludedFiles($_[1]);
	
	#&DumpVerticesNum();
	#&DumpVertices();
}

# Get all included files in this file, and build the graph
# @p1: Source file name
sub ParseIncludedFiles($)
{
	my $FilePath = $_[0];
	my $InheritedDir = &File::Basename::dirname($FilePath);
	&AddInheritedDir($InheritedDir);
	open THIS_FILE, $FilePath or die "Unable to open $FilePath: $!";
	my $FileContentStr;
	my %LocalIncludeMap;
	my $HasDuplicate = 0;
	foreach my $Line (<THIS_FILE>)
	{
		my $AbsPath = undef;
		# Quoted form
		if($Line =~ /^\s*\#\s*include\s*\"(.*?)\s*\"/)
		{
			#&Trace("Quoted form");
			my $RelPath = $1;
			$AbsPath = GetAbsPath_Inherited($RelPath);
			if($AbsPath)
			{
				&AddIncludeFile($FilePath, $AbsPath);
			}
			else
			{
				$AbsPath = GetAbsPath_Standard($RelPath);
				if($AbsPath)
				{
					&AddIncludeFile($FilePath, $AbsPath);	
				}
			}
		}
		# Angle-bracket form
		elsif($Line =~ /^\s*\#\s*include\s*<(.*?)\s*>/)
		{
			#&Trace("Angle-bracket form");
			my $RelPath = $1;
			$AbsPath = GetAbsPath_Standard($RelPath);
			if($AbsPath)
			{
				&AddIncludeFile($FilePath, $AbsPath);
			}
		}
		# Remove Includes that duplicate on same file
		if($AbsPath)
		{
			if(exists $LocalIncludeMap{$AbsPath})
			{
				$HasDuplicate = 1;
				# if(! exists $RemovedIncludesMap{$FilePath})
				# {
					# my @RemovedIncludes;
					# $RemovedIncludesMap{$FilePath} = \@RemovedIncludes;
				# }
				# push @{$RemovedIncludesMap{$FilePath}}, $Line;
			}
			else
			{
				$FileContentStr .= $Line;
				$LocalIncludeMap{$AbsPath} = 1;
			}
		}
		else
		{
			$FileContentStr .= $Line;
		}
		
	}
	close THIS_FILE;
	
	# if($HasDuplicate)
	# {
		# &Trace("$FilePath has duplication");
		# # Remove Includes that duplicate on same file
		# open THIS_FILE, ">", $FilePath or die "Unable to write $FilePath: $!";
		# print THIS_FILE $FileContentStr;
		# close THIS_FILE;
	# }
}
# Process a new include file
# @p1: Including file
# @p2: Included file
sub AddIncludeFile($$)
{
	my ($Source, $Target) = @_;
	if(&IsVertexExist($Target)) # If the file already exist in the vertice list
	{
		&InsertEdge($Source, $Target);
	}
	else
	{
		&InsertVertex($Target);
		&InsertEdge($Source, $Target);
		&ParseIncludedFiles($Target);
	}
}

# Get all possible paths from source to target
# @p1: Source file
# @p2: Target file
sub SearchPaths($$)
{
	# Clear the paths before searching
	&ClearPaths();
	
	my $Source = $_[0];
	&AppendPath($Source); # First file into path
	
	my $Target = $_[1];
	# Depth First Search all the possible paths
	&DFSPaths($Source, $Target);
	#&BFSPaths($Source, $Target);
	
	# Output all the possible paths, the first one should be the one compiler used.
	my $Num = 0;
	foreach (@AllPaths)
	{
		my @EachPath = @{$_};
		$Num++;
		print "Path $Num:\n";
		print join "->\n", @EachPath;
		print "\n\n\n";
	}
	
	#&DumpEdges();
	
	return scalar @AllPaths;
}

# Recursively search the path from source to target
# @p1: Source file
# @p2: Target file
sub DFSPaths($$)
{
	# RemoveDuplicateIncludes
	#return if(@AllPaths > 1);
	my ($Source, $Target) = @_;
	$Source = lc $Source;
	$Target = lc $Target;
	
	# Get index of the vertex.
	my $v1 = &GetIndex($Source);
	my $v2 = &GetIndex($Target);
	
	#  If have adjacent vertices
	if(@Edges[$v1])
	{
		my $Num = scalar @{@Edges[$v1]}; # Number of adjacent vertex
		
		for(my $i = 0; $i <= $Num; $i++)
		{
			if(@{@Edges[$v1]}[$i] == 1)
			{
				my $Vertex = &GetVertex($i);
				if(&AppendPath($Vertex)) # Append adjacent vertex to the path. return 0 if already in the path.
				{
					if($Vertex eq $Target)
					{
						# Find one path, save it and pop to process next vertex.
						my @ThisPath = @CurPath;
						push @AllPaths, \@ThisPath;
						&PopPath();
						
						# RemoveDuplicateIncludes
						# return if(@AllPaths > 1);
					}
					else
					{
						# This adjacent vertex not match, DFS it
						&DFSPaths($Vertex, $Target);
					}
				}
			}
		}
	}
	# Current vertex finished,  back one step.
	&PopPath();
}

# Search the path from source to target by loops
# @p1: Source file
# @p2: Target file
sub BFSPaths($$)
{
	# Not implemented
}

# Append a vertex to the current path, return 0 if the input vertex already exists
# @P1: Vertex append to the path
sub AppendPath($)
{
	my $Element = $_[0];
	if(exists $CurPathMap{$Element})
	{
		return 0;
	}
	else
	{
		# append to the end of the path
		$CurPathMap{$Element} = 1;
		push @CurPath, $Element;
		#&Trace(join "->\n", @CurPath);
		return 1;
	}
}
sub PopPath()
{
	my $Element = pop @CurPath;
	delete $CurPathMap{$Element};
}

sub ClearPaths
{
	# Clear the paths
	pop @AllPaths while(@AllPaths);
	pop @CurPath while(@CurPath);
	delete $CurPathMap{$_} while(%CurPathMap);
}
###############################Vertex, Edge operations##########################
# Add a vertex to the list
# @p1: file name
sub InsertVertex($)
{
	my $Vertex = lc $_[0];
	if(! exists $VerticesMap{$Vertex})
	{
		$VerticesMap{$Vertex} = 0;
		push @VerticesList, $Vertex;
	}
}

# Remove a vertex to the list
# @p1: file name
sub RemoveVertex($)
{
	# my $Vertex = lc $_[0];
	# delete $VerticesList{$Vertex};
}

sub GetVertex($)
{
	return @VerticesList[$_[0]];
}
sub GetIndex($)
{
	my $Vertex = lc $_[0];
	for(my $i = 0; $i <= $#VerticesList; $i++)
	{
		if($Vertex eq @VerticesList[$i])
		{
			return $i;
		}
	}
	return -1;
}
sub IsVertexExist($)
{
	my $Vertex = lc $_[0];
	return exists $VerticesMap{$Vertex};
}

# Get all the vertice that match the input file name. (Not full path)
# @p1: file name without path
sub MatchVertice($)
{
	my @Vetices;
	my $Filename = lc $_[0];
	$Filename =~ s/\\/\\\\/g; #Path Patterns;
	foreach my $Vertex (@VerticesList)
	{
		push @Vetices, $Vertex if($Vertex =~ /$Filename$/);
	}
	return @Vetices;
}

sub GetAdjacentVertice($)
{
	my $Filename = lc $_[0];
	my $rowIndex = &GetIndex($Filename);
	#&Trace($rowIndex);
	#&Trace($Filename);
	my @AdjacentVertice;
	if(@Edges[$rowIndex])
	{
		my @Row = @{@Edges[$rowIndex]};
		foreach(my $i = 0; $i <= $#Row; $i++)
		{
			if(@Row[$i])
			{
				push @AdjacentVertice, &GetVertex($i);
			}
		}
	}
	return @AdjacentVertice;
}
# Insert edge by vertex index
sub InsertEdgeByIndex($$)
{
	my ($v1, $v2) = @_;
	if(! @Edges[$v1])
	{
		my @Row;
		@Edges[$v1] = \@Row;
	}
	@{@Edges[$v1]}[$v2] = 1;
}

# Insert edge by vertex
sub InsertEdge($$)
{
	my $v1 = &GetIndex($_[0]);
	my $v2 = &GetIndex($_[1]);
	if($v1 != -1 && $v2 != -1)
	{
		#&Trace("<$v1, $v2> \n");
		InsertEdgeByIndex($v1, $v2);
	}
	else
	{
		#&Trace("Failed To insert edge!");
	}
}

# Remove edge by vertex index
sub RemoveEdgeByIndex($$)
{
	my ($v1, $v2) = @_;
	@{@Edges[$v1]}[$v2] = 0;
}

# Remove edge by vertex
sub RemoveEdge($$)
{
	my $v1 = &GetIndex($_[0]);
	my $v2 = &GetIndex($_[1]);
	
	if($v1 != -1 && $v2 != -1)
	{
		#&Trace("<$v1, $v2> \n");
		RemoveEdgeByIndex($v1, $v2);
	}
	else
	{
		#&Trace("Failed To remove edge!");
	}
	
}

###############################Directories##########################
# See #include directive in MSDN, generally, Compiler find files in directories in following sequence:
# 1.  Including file's directory
# 2. Previously opened file's directory. (in reversed order)
# 3. Project's AdditionalIncludeDirectories, /I
# 4. INCLUDE Env variables
# Here:
# Inherited Dir = 1 + 2
# Standard Dir = 3 + 4
#

# # Each time we opened a file, we should add that file's dir
# sub AddInheritedDir($)
# {
	# my $InheritedDir = $_[0];
	# foreach my $Dir (@InheritedDirs)
	# {
		# return if($Dir eq $InheritedDir);
	# }
	# push @InheritedDirs, $InheritedDir;
	# # unshift @InheritedDirs, $InheritedDir;
# }

# # Get abs path by a dir and a relative path
# # @p1: Dir
# # @p2: Relative path
# sub GetAbsPath($$)
# {
	# my $Dir = $_[0];
	# my $RelPath = $_[1];
	
	# # Process the file's relative path, remove prefix ".\" if there is.
	# $RelPath = substr($RelPath, 2) if(substr($RelPath, 0, 2) eq "\.\\");
	
	# # Get file's absolute path based on project location and relative path
	# my $AbsPath = File::Spec->rel2abs($RelPath, $Dir);
	
	# return $AbsPath;
# }

# # Get abs path in standard directories
# sub GetAbsPath_Standard($)
# {
	# my $RelPath = $_[0];
	# my $AbsPath;
	# foreach my $EachDir (@StandardDirs)
	# {
		# $AbsPath = GetAbsPath($EachDir, $RelPath);
		# if(-f $AbsPath)
		# {
			# return $AbsPath;
		# }
	# }
# }

# # Get abs path in inherited  directories
# sub GetAbsPath_Inherited($)
# {
	# my $RelPath = $_[0];
	# my $AbsPath;
	# foreach my $EachDir (@InheritedDirs)
	# {
		# $AbsPath = GetAbsPath($EachDir, $RelPath);
		# if(-f $AbsPath)
		# {
			# return $AbsPath;
		# }
	# }
# }

# # Translate the env variables into its value in the input string
# sub TranslatePath($)
# {
	# my $PathWithEnvVar = @_[0];
	# #print $PathWithEnvVar;
	# $PathWithEnvVar =~ s/\$\((.*?)\)/$ENV{uc($1)}/g;
	# return $PathWithEnvVar;
# }
# # Get the standard Include Dir, it comes from:
# # 	1. Project's AdditionalIncludeDirectories for Debug|Win32 version
# #	2. INCLUDE env variables
# # @P1: Project file.
# # @Return: A arrary of standard include dirs
# sub GetStdIncludeDirs($)
# {
	# my $ProjFile = $_[0];
	# my @StdIncludeDirs;
	
	# # 1. Insert user macros in server props to %ENV
	# my $ServerVsProps = "R:\\Server\\ServerProperties.vsprops";
	# if(-f $ServerVsProps)
	# {
		# my $config = XML::Simple::XMLin($ServerVsProps);
		# foreach my $MapRef (@{$config->{UserMacro}})
		# {
			# $ENV{$MapRef->{Name}} = $MapRef->{Value}
		# }
	# }
	
	# # 2. Get AdditionalIncludeDirectories from project setting.
	# open CUR_PROJFILE, $ProjFile or die "Can't open project $ProjFile: $!";
	# my $DebugWin32;
	# foreach(<CUR_PROJFILE>)
	# {
		# #	Name="Debug|Win32"
		# if(/^\s*Name=\"Debug\|Win32\"\s*$/)
		# {
			# $DebugWin32 = 1;
		# }
		# if(1 == $DebugWin32)
		# {
			# # AdditionalIncludeDirectories="R:\Environment\DevStudio\VC.Net\include;r:\;R:\Server\Framework;r:\xinterface\bin;R:\Server\Support\Vba\Include;R:\Server\Support\Include;R:\Server\Support;R:\AppFw\VBCUI"
			# if(/^\s*AdditionalIncludeDirectories=\"(.*)\"\s*$/)
			# {
				# my $IncludeDirStr = $1;
				# $IncludeDirStr =~ s/&quot;//g;
				# $IncludeDirStr = &TranslatePath($IncludeDirStr);
				# @StdIncludeDirs = split /;|,/, $IncludeDirStr;
				# s/\s+//g; # Remove unnecessary spaces.
				# last;
			# }
		# }
	# }
	# close CUR_PROJFILE;
	
	# # 3. Get INCLUDE
	# my $IncludeDirStr = $ENV{"INCLUDE"};
	# my @IncludeDirs = split /;/, $IncludeDirStr;
	# push @StdIncludeDirs, @IncludeDirs;
	
	
	# return @StdIncludeDirs;
	
# }

###############################Dump & Trace##########################
my $ExeCount = 0;
sub DumpCurPath
{
	my @SimplePath;
	foreach(@CurPath)
	{
		push @SimplePath, &File::Basename::basename($_);
	}
	print join "->", @SimplePath;
	print "\n";
	if($ExeCount++ >= 10)  {return;}
}

sub DumpVertices
{
	print join "\n", @VerticesList;
	print "\n";
}

sub DumpEdges
{
	for(my $i = 0; $i<=$#Edges; $i++)
	{
		print &GetVertex($i), "\n";
		my $RowRef = @Edges[$i];
		my $Length = $RowRef ? scalar @{$RowRef} : -1;
		for(my $j = 0; $j <= $Length; $j++)
		{
			if(@{@Edges[$i]}[$j] == 1)
			{
				print "\t", &GetVertex($j), "\n";
			}
		}
		print "\n";
	}
}

sub DumpVerticesNum
{
	my $TotalNum = scalar @VerticesList;
	print "Total Files: $TotalNum\n";
}

sub Trace
{
	#print "Trace->", @_, "\n";
}

#*****************************************************************************************************************************
return 1;
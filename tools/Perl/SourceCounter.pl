#####
#
# Perl Script that output the comment rate of your C++, C#, Perl code
# 
# Author: Baiyan Huang
# Date: 12/06/2008
#
# Usage:
# SourceCounter.pl <Parameter> (File name, Folder, Project name)
# SourceCounter.pl R:\\Server\\Framework\\Fw\\Fw.vcproj
#
#####
use strict;
use File::Basename;
use File::Spec;
#*********************************************Main****************************************************
my $InCommentGroup = 0;
my $CurLine = 0;
my $Input = @ARGV[0];
my $InputName = &basename($Input);
&StartReport("C:\\SourceCounter_${InputName}_.txt");
if($Input =~ /(\.cpp)|(\.h)|(\.cs)|(\.hpp)|(\.c)$/i)
{
	my @FileStat = &CountFile($Input);
	
	&ShowSummary($Input, \@FileStat);
}
else
{
	
	my %PrjStat;
	if($Input =~ /(\.vcproj)|(\.csproj)$/i)
	{	
		%PrjStat = &CountProject($Input);
	}
	else
	{
		%PrjStat = &CountFolder($Input);
	}
	
	my ($code, $comment, $mix, $blank) = (0,0,0,0);
	foreach(keys %PrjStat)
	{
		my @FileStat = @{$PrjStat{$_}};
		$code += @FileStat[0];
		$comment += @FileStat[1];
		$mix += @FileStat[2];
		$blank += @FileStat[3];
	}
	my @ProjStat = ($code, $comment, $mix, $blank);
	
	&ShowSummary($Input, \@ProjStat);
	
	&Report("Press anykey to show the details:\n");
	<STDIN>;
	my $FileNum = keys %PrjStat; 
	&Report("Detailed List: (Totally $FileNum Files)\n");
	&Report("=" x 72, "\n");
	my $Titles = sprintf "%-50s%-11s%-11s", "FileName", "Total", "CommentRate";
	&Report($Titles);
	&Report("\n", "=" x 72, "\n");
	my @Rates;
	foreach(keys %PrjStat)
	{
		my ($code, $comment, $mix, $blank) = @{$PrjStat{$_}};
		my $total = $code + $mix + $comment + $blank;
		my $nonblank = $code + $mix + $comment;
		my $commentrate = 0;
		$commentrate = ( $comment + $mix ) * 100 / $nonblank if($nonblank);
		$commentrate = sprintf "%2.2f%", $commentrate;
		my @Rate = ($_, $total, $commentrate);
		push @Rates, \@Rate;
	}
	# Print in the ascent order of comment rate
	foreach(sort By_CommentRate @Rates)
	{
		my $Filename = &basename(@{$_}[0]);
		my $total = @{$_}[1];
		my $commentrate = @{$_}[2];
		my $Values = sprintf "%-50s%-11s%-11s", $Filename, $total, $commentrate;
		&Report($Values, "\n");
	}
}

&EndReport();
<STDIN>;
#******************************************************Funcctions**********************************************
sub ShowSummary($$)
{
	my $Input = $_[0];
	my ($code, $comment, $mix, $blank) = @{$_[1]};
	# Total		Code		Mixed	Comment	Blank		CommentRate
	my $Titles = sprintf "%-12s" x 6, "Total", "Code", "Mixed", "Comment", "Blank", "CommentRate";
	my $total = $code + $mix + $comment + $blank;
	my $nonblank = $code + $mix + $comment;
	my $commentrate = 0;
	$commentrate = ( $comment + $mix ) * 100 / $nonblank if($nonblank);
	$commentrate = sprintf "%2.2f%", $commentrate;
	my $Values = sprintf "%-12s" x 6, $total, $code, $mix, $comment, $blank, $commentrate;

	&Report("$Input\n");
	&Report("=" x 72, "\n");
	&Report($Titles, "\n");
	&Report("=" x 72, "\n");
	&Report($Values, "\n");
}
sub By_CommentRate()
{
	@{$a}[2] <=> @{$b}[2];
}

sub CountFile($)
{
	my ( $code, $comment, $mix, $blank ) = ( 0, 0, 0, 0 );
	
	my $FileName = $_[0];
	open THIS_FILE, $FileName or die "Unable to open file $FileName : $!";
	foreach(<THIS_FILE>)
	{
		chomp;
		$CurLine++; # Used for trace;
	    #must judge in following order: Mix->Comment->Blank->Code
	    if    ( &IsMix($_) )     { $mix++; }
	    elsif ( &IsComment($_) ) { $comment++; }
	    elsif ( &IsBlank($_) )   { $blank++; }
	    else                     { $code++; }
	}
	close THIS_FILE;
	
	return ($code, $comment, $mix, $blank);
}

sub CountProject($)
{
	my %PrjStat;
	my $ProjectPath = $_[0];
	my $ProjectDir = dirname($ProjectPath);
	open THIS_PROJECT, $ProjectPath or die "Unable to open project $ProjectPath: $!";
	foreach(<THIS_PROJECT>)
	{
		#	RelativePath=".\Resource.h"
		if(/^\s*RelativePath=\"(.*?)\"\s*$/)
		{
			my $RelName = $1;
			$RelName =~ s/\.\\//;
			my $AbsName = File::Spec->rel2abs($RelName, $ProjectDir);
			if(-f $AbsName)
			{
				my @FileStat = &CountFile($AbsName);
				$PrjStat{$AbsName} = \@FileStat;
			}
		}
	}
	close THIS_PROJECT;
	
	return %PrjStat;
}

sub CountFolder($)
{
	my %PrjStat;
	my $Folder = $_[0];
	chdir $Folder;
	my @Files = `dir *.h,*.cpp,*.c,*.hpp,*.rc,*.idl,*.cs /b /s`;
	foreach my $File (@Files)
	{
		my @FileStat = &CountFile($File);
		$PrjStat{$File} = \@FileStat;
	}
	return %PrjStat;
}
sub IsComment($) 
{
	my $Line = $_[0];
	
	# Begin group comment on multiple line
	if($Line =~ /^\s*\/\*/)
	{
		if($Line !~ /\*\/\s*$/)
		{
			&Trace("Comment-3");
			$InCommentGroup = 1;
			return 1;
		}
	}
	# End of groud comment
	elsif($Line =~ /\*\/\s*$/)
	{
		&Trace("Comment-1");
		$InCommentGroup = 0; 
		return 1;
	}
	
	# If in comment group
	if($InCommentGroup)
	{
		&Trace("Comment-2");
		return 1;
	}
	
	
	# // Comment Start with "//"
	if($Line =~ /^\s*\/\//)
	{
		&Trace("Comment-4");
		return 1;
	}
	# Comment group in single line /* comments *//*comments*/
	elsif($Line =~ /^(\s*\/\*(.*?)\*\/\s*)+$/)
	{
		&Trace("Comment-5");
		return 1;
	}
	
	# If none of the above, it is not a comment
	return 0;
}

sub IsMix($) 
{
	my $Line = $_[0];
	
	# int Count; // It is mixed comment
    if ($Line =~ /^(.*?\S+.*?)\/\//) 
    {
		# Avoid /*Comments*//*Comments*/ and // //comments
		if($1 !~ /\/\*/ && $1 !~ /\/\//)
		{
			&Trace("Mixed-1");
	        return 1;
		}
    }
	# int Count; /* It is mixed comment*/ ; group comment embeded in the code won't treated as mix, but code.
	elsif($Line =~ /^(.*?\S+.*?)\/\*.*?\*\/\s*$/)
	{
		if($1 !~ /\/\*/)
		{
			&Trace("Mixed-2");
			return 1;
		}
	}
	# int Count /* It is a 
	elsif($Line =~ /^.*?\S+.*?\/\*/)
	{
		if($Line !~ /\*\//)
		{
			&Trace("Mixed-3");
			$InCommentGroup = 1;
			return 1;
		}
	}
	# mixed Comment */ int Count;
	elsif($Line =~ /^\s*.*?\*\/.*?\S+.*?$/)
	{
		if($Line !~ /\/\*/)
		{
			&Trace("Mixed-4");
			$InCommentGroup = 0;
			return 1;
		}
	}
	# /* It is a mixed comment*/ int count;
	elsif($Line =~ /^\/\*.*?\*\/(.*?\S+.*?)$/)
	{
		if($1 !~ /\/\*/)
		{
			&Trace("Mixed-5");
			return 1;
		}
	}
	
	# If non of the above, it is not a mixed comment
	return 0;
}

sub IsBlank($) 
{
	my $Line = $_[0];
    if ($InCommentGroup == 1) 
	{
        return 0;
    }    
	#blank line in comment group treated as comment
    if   ($Line =~ /^\s*$/) 
	{ return 1; }
    else
	{ return 0; }
}

sub Trace
{
	#print STDOUT "Trace->", "Line $CurLine : 	", @_, "\n";
}
sub StartReport($){ open REPORT_FILE, ">", $_[0] or die "Can't open log file $_[0]: $!";}
sub Report {print REPORT_FILE @_; print STDOUT @_; }#
sub EndReport(){ close REPORT_FILE;}

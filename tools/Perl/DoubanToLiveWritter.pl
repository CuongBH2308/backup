#####
#
# Translate a douban diary to the format that suitable for live writter.
# 
# Author: Baiyan Huang
# Date: 1/16/2009
# 
# Usage: DoubanToLiveWritter.pl <YouDiaryFile>
# 
# Note:
# 1. Copy your published douban diary to LiveWritter (In Edit mode)
# 2. Switch to "source" mode in Live Writter and copy the source and save as a txt
# 3. Translate the txt with this script, copy the result to the "source" pane of Live Writter
# 4. Just Publish it with your Live Writter.
#
#####
use strict;
use IO::File;
use Win32;

my $InputFile = $ARGV[0];

# 1. Replace the global <pre> </pre> with <p> </p>
my $FileContent = &GetFileContent($InputFile);
my $Text = $FileContent;
if($FileContent =~ /^\s*<pre>(.*)<\/pre>\s*$/s)
{
	$Text = $1;
}
$Text = "<p>" . $Text . "</p>";

# 2. Check the number of "\n", if
#    1: <br/>
#    2 or more: </p><br/><p>

# Remove spaces between 2 "\n"
$Text =~ s/\n[\t ]+\n/\n\n/g;

# Replace single "\n" with <br/>
$Text =~ s/(?<!\n)\n(?!\n)/<br\/>/g;

# replace muliple "\n" with </p><p>
$Text =~ s/(?<!\n)\n/<\/p>/g; #</p>
$Text =~ s/\n(?=\n)/<br\/>/g; #<br/>
$Text =~ s/\n(?!\n)/<p>/g;    #<p>


# Output the result
my $TmpDir = Win32::GetLongPathName($ENV{"TEMP"});
my $tmpfilename = $TmpDir . "\\" . time . ".txt";
print $tmpfilename;
my $fh = new IO::File;
if ($fh->open(">". $tmpfilename))
{
	$fh->write($Text);
}
$fh->close;
	
`notepad $tmpfilename`;

#-----------------------------------functions-----------------------------------------
# return the array of the file contents
# use IO:File, not open, or else you won't handle with unicode successfully.
sub GetFileContent($) 
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
	return $logfilebuffer;
}

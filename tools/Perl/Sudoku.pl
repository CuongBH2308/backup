use strict;

my $sudoku = Sudoku->new("D:\\Share\\Perl\\Sudoku.txt");

$sudoku->Build();

<STDIN>;

#********************************************
package Sudoku;
our $StartIndex = 1;
our $EndIndex = 81;

sub new($$)
{
	# Bind the variable to the class
	my $ClassName = shift;
	my $this = {};
	bless($this, $ClassName);
	
	my $InputFile = shift;
	# Initialize
	&Initialize($this, $InputFile);
	
	# Return
	return $this;
}

sub Initialize($)
{
	my $this = shift;
	my $InputFile = shift;
	
	# Initialize values
	my @Rows;
	$this->{MATRIX} = \@Rows;
	my @CRows;
	$this->{CMATRIX} = \@CRows;
	open THIS_FILE, $InputFile or die "Can't open the $InputFile: $!";
	my $i = 0;
	foreach(<THIS_FILE>)
	{
		my @Row = SplitByTab($_);
		chomp @Row;
		@{$this->{MATRIX}}[$i] = \@Row;
		
		my @CRow;
		@{$this->{CMATRIX}}[$i] = \@CRow;
		$i++;
	}
	$this->{CURINDEX} = 1;
	
	
	# Initialize candidates
	# Initialize indexs that has initial value
	foreach(my $i = 0; $i < 9; $i++)
	{
		foreach(my $j = 0; $j < 9; $j++)
		{
			my @Candidates;
			my $index = &Array2Index($i, $j);
			if(@{@{$this->{MATRIX}}[$i]}[$j] == 0)
			{
				@Candidates = &FindCandidates($this, $i, $j);
				
			}
			else
			{
				#&Trace($index);
				${$this->{INDEXS}}{$index} = 1;
			}
			
			@{@{$this->{CMATRIX}}[$i]}[$j]  = \@Candidates;
			&Trace1($index, "->" ,@Candidates);
			
		}
	}
	
	$StartIndex = 1;
	$EndIndex = 81;

	close THIS_FILE;
}


sub SplitByTab($)
{
	my $Line = $_[0];
	$Line =~ s/ //g;
	$Line =~ s/\t(?!\d)/\t0/g; #replace none with 0
	$Line =~ s/^\t/0\t/g; #replace none with 0
	my @Row = split /\t/, $Line;
	return @Row ;
}

sub Trace()
{
	#print "Trace--->", @_, "\n";
}
sub Trace1()
{
	#print "Trace--->", @_, "\n";
}

#********************************************
sub Build()
{
	my $this = shift;
	my $Error = 0;
	my $First = 1;
	&Trace1("Initial");
	#$this->Output();
	while($this->GetIndex() != $StartIndex || $First)
	{
		if(! $Error)
		{
			if($this->GetIndex() == $EndIndex)
			{
				$this->Output();
				$this->BackTrace();
			}
			else
			{
				&Trace1("Extend");
				$this->Extend();
				#$this->Output();
			}
		}
		else
		{
			&Trace1("BackTrace");
			$this->BackTrace();
			#$this->Output();
		}
		
		$Error = $this->Validate();
		$First = 0;
	}
}

sub FindCandidates($$$)
{
	my $this = shift;
	my $i = shift;
	my $j = shift;
	my %ForbiddenNum;
	
	foreach(my $k = 0; $k < 9; $k++)
	{
		my $Value = $this->GetElement($k, $j);
		$ForbiddenNum{$Value} = 1;
		
		$Value = $this->GetElement($i, $k);
		$ForbiddenNum{$Value} = 1;
	}
	
	if($i < 3 && $j < 3)
	{
		$this->SearchRegion($i, $j, 0, 2, 0, 2, \%ForbiddenNum);
	}
	elsif($i < 3 && $j < 6)
	{
		$this->SearchRegion($i, $j, 0, 2, 3, 5, \%ForbiddenNum);
	}
	elsif($i < 3 && $j < 9)
	{
		$this->SearchRegion($i, $j, 0, 2, 6, 8, \%ForbiddenNum);
	}
	elsif($i < 6 && $j < 3)
	{
		$this->SearchRegion($i, $j, 3, 5, 0, 2, \%ForbiddenNum);
	}
	elsif($i < 6 && $j < 6)
	{
		$this->SearchRegion($i, $j, 3, 5, 3, 5, \%ForbiddenNum);
	}
	elsif($i < 6 && $j < 9)
	{
		$this->SearchRegion($i, $j, 3, 5, 6, 8, \%ForbiddenNum);
	}
	elsif($i < 9 && $j < 3)
	{
		$this->SearchRegion($i, $j, 6, 8, 0, 2, \%ForbiddenNum);
	}
	elsif($i < 9 && $j < 6)
	{
		$this->SearchRegion($i, $j, 6, 8, 3, 5, \%ForbiddenNum);
	}
	elsif($i < 9 && $j < 9)
	{
		$this->SearchRegion($i, $j, 6, 8, 6, 8, \%ForbiddenNum);
	}
	
	my @CandidatesNum;
	foreach(1..9)
	{
		push @CandidatesNum, $_ if(! exists $ForbiddenNum{$_});
	}
	
	return @CandidatesNum;
		
}

my $Count = 0;
sub SearchRegion($$$$$$$$)
{
	$Count++;
	#&Trace("SearchRegion, $Count");
	my $this = shift;
	my $oi = shift;
	my $oj = shift;
	my ($rs, $re, $cs, $ce, $MapRef) = @_;
	
	for(my $i = $rs; $i <= $re; $i++)
	{
		for(my $j = $cs; $j <= $ce; $j++)
		{
			next if($i == $oi && $j == $oj);
			my $Value = $this->GetElement($i, $j);
			${$MapRef}{$Value} = 1;
		}
	}
}

#***********************************************************
sub GetIndex()
{
	my $this = shift;
	
	return $this->{CURINDEX};
}

sub SetIndex($)
{
	my $this = shift;
	
	$this->{CURINDEX} = shift;
}


sub DESTROY 
{
    my $this = shift;
}


sub SetElement($$$)
{
	my $this = shift;
	my $i = shift;
	my $j = shift;
	my $value = shift;
	@{@{$this->{MATRIX}}[$i]}[$j] = $value;
}

sub GetElement($$)
{
	my $this = shift;
	my $i = shift;
	my $j = shift;
	return @{@{$this->{MATRIX}}[$i]}[$j];
}

sub GetCandidates($$$)
{
	my $this = shift;
	my $i = shift;
	my $j = shift;
	
	return @{@{$this->{CMATRIX}}[$i]}[$j];
}
sub Index2Array($)
{
	my $index = shift;
	my $i = int(($index-1) / 9);
	my $j = (($index-1) % 9);
	return ($i, $j);
}

sub IsFixedIndex($)
{
	my $this = shift;
	my $index = shift;
	my $IndexMapRef = $this->{INDEXS};
	if(exists ${$IndexMapRef}{$index})
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
sub Array2Index($$)
{
	my ($i, $j) = @_;
	return ($i * 9 + $j) + 1;
}
sub GetNextCandidate($)
{
	my $this = shift;
	my $CandidatesRef = shift;
	my $Count = scalar @{$CandidatesRef};
	&Trace("GetNextCandidate", $Count);
	for(my $i = 0; $i < $Count; $i++)
	{
		if(@{$CandidatesRef}[$i] < 10)
		{
			my $Value = @{$CandidatesRef}[$i]; 
			@{$CandidatesRef}[$i] += 10;
			
			return $Value;
		}
	}
	return 0; # No answer
}
sub Output($)
{
	print "Answer:\n";
	my $this = shift;
	foreach(my $i = 0; $i < 9; $i++)
	{
		foreach(my $j = 0; $j < 9; $j++)
		{
			print $this->GetElement($i, $j);
			print " ";
		}
		print "\n";
	}
	print "\n";
}

sub GetNextIndex()
{
	my $this = shift;
	
	my $index = $this->GetIndex() + 1;
	&Trace($index);
	&Trace($EndIndex);
	while($index <= $EndIndex)
	{
		&Trace($index);
		unless ($this->IsFixedIndex($index))
		{
			&Trace("Not IsFixedIndex");
			return $index;
		}
		$index++;
	}
	return 0;
}

sub GetPreviousIndex()
{
	my $this = shift;
	
	my $index = $this->GetIndex() - 1;
	while($index >= $StartIndex)
	{
		unless($this->IsFixedIndex($index))
		{
			&Trace("Not IsFixedIndex");
			return $index;
		}
		$index--;
	}
	return 0;
}

sub Extend($)
{
	my $this = shift;
	
	my $index = $this->GetNextIndex();
	if($index != 0)
	{
		my ($i, $j) = &Index2Array($index);
		my $CandidatesRef = $this->GetCandidates($i, $j);
		
		my $Value = $this->GetNextCandidate($CandidatesRef);
		
		$this->SetElement($i, $j, $Value);
		
		$this->SetIndex($index);
	}
	else
	{
		$this->SetIndex($EndIndex);
	}
}

sub RestoreCandidates($$$)
{
	#&Trace1("RestoreCandidates");
	my $this = shift;
	my ($i, $j) = @_;
	my $CandidatesRef = $this->GetCandidates($i, $j);
	my $Count = scalar @{$CandidatesRef};
	for(my $i = 0; $i <= $Count; $i++)
	{
		if(@{$CandidatesRef}[$i] >= 10)
		{
			@{$CandidatesRef}[$i] -= 10;
		}
	}
	
	$this->SetElement($i, $j, 0);
}
sub BackTrace()
{
	my $this = shift;
	
	# Try next avaible num
	my $index = $this->GetIndex();
	#&Trace1($index);
	
	my ($i, $j) = &Index2Array($index);
	my $CandidatesRef = $this->GetCandidates($i, $j);
	#&Trace1(scalar @{$CandidatesRef});
	
	my $Value = $this->GetNextCandidate($CandidatesRef);
	#&Trace1($Value);
	# if not work, find previous one
	if($Value == 0)
	{
		$this->RestoreCandidates(&Index2Array($index));
		$index = $this->GetPreviousIndex();
		if($index != 0)
		{
			$this->SetIndex($index);
			
			&Trace1("BackTrace");
			$this->BackTrace();
		}
		else
		{
			$this->SetIndex($StartIndex);
		}

	}
	else
	{
		$this->SetElement($i, $j, $Value);
		$this->SetIndex($index);
	}
}

# 1 = row
# 2 = column
# 3 = region
sub Validate()
{
	my $this = shift;
	my $index = $this->GetIndex();
	my ($i, $j) = &Index2Array($index);
	
	# Row
	my $Value = $this->GetElement($i, $j);
	for(my $k = 0; $k < 9; $k++)
	{
		next if($k == $j);
		return 1 if($Value == $this->GetElement($i, $k))
	}
	
	# Region
	for(my $k = 0; $k < 9; $k++)
	{
		next if($k == $i);
		return 2 if($Value == $this->GetElement($k, $j))
	}
	
	# Region
	my %ForbiddenNum;
	if($i < 3 && $j < 3)
	{
		$this->SearchRegion($i, $j, 0, 2, 0, 2, \%ForbiddenNum);
	}
	elsif($i < 3 && $j < 6)
	{
		$this->SearchRegion($i, $j, 0, 2, 3, 5, \%ForbiddenNum);
	}
	elsif($i < 3 && $j < 9)
	{
		$this->SearchRegion($i, $j, 0, 2, 6, 8, \%ForbiddenNum);
	}
	elsif($i < 6 && $j < 3)
	{
		$this->SearchRegion($i, $j, 3, 5, 0, 2, \%ForbiddenNum);
	}
	elsif($i < 6 && $j < 6)
	{
		$this->SearchRegion($i, $j, 3, 5, 3, 5, \%ForbiddenNum);
	}
	elsif($i < 6 && $j < 9)
	{
		$this->SearchRegion($i, $j, 3, 5, 6, 8, \%ForbiddenNum);
	}
	elsif($i < 9 && $j < 3)
	{
		$this->SearchRegion($i, $j, 6, 8, 0, 2, \%ForbiddenNum);
	}
	elsif($i < 9 && $j < 6)
	{
		$this->SearchRegion($i, $j, 6, 8, 3, 5, \%ForbiddenNum);
	}
	elsif($i < 9 && $j < 9)
	{
		$this->SearchRegion($i, $j, 6, 8, 6, 8, \%ForbiddenNum);
	}
	
	return 3 if(exists $ForbiddenNum{$Value});
	
	return 0;
	
}
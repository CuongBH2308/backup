# Monty Hall Problem
use strict;
my $Goat = 0;
my $Car = 1;

my $bHostKnown = 0;
my $LuckySamplingNum = 0;

my $SamplingNum = 900;

my $NonSwitch = 0;
my $Switch = 0;

for(my $i = 0; $i < $SamplingNum; $i++)
{
	# Setup Doors
	my @Doors;
	$Doors[0] = int(rand(2));
	if($Doors[0] == $Car)
	{
		$Doors[1] = $Goat;
		$Doors[2] = $Goat;
	}
	else
	{
		$Doors[1] = int(rand(2));
		if($Doors[1] == $Car)
		{
			$Doors[2] = $Goat;
		}
		else
		{
			$Doors[2] = $Car;
		}
	}

	print join " ", @Doors;
	print "\n";

	# Let's choose
	my $Choose1 = int(rand(3));
	my $Choose2;
	my $a1 = ($Choose1 + 1) % 3;
	my $a2 = ($Choose1 + 2) % 3;

	if($bHostKnown)
	{
		$Choose2 = ($Doors[$a1] == $Goat ? $a2 : $a1);
	}
	else
	{
		$Choose2 = $a1;
		if($Doors[$a2] == $Goat) # Host is lucky enough to open a door with goat
		{
			$LuckySamplingNum++;
		}
		else
		{
			next;
		}
	}
	
	
	print $Choose1, " ", $Choose2, "\n";
	
	if($Doors[$Choose1] == $Car)
	{
		$NonSwitch++;
	}
	
	if($Doors[$Choose2] == $Car)
	{
		$Switch++;
	}

}

if($bHostKnown)
{
	print $NonSwitch, "+", $Switch, "=", $SamplingNum, "\n";
}
else
{
	print $NonSwitch, "+", $Switch, "=", $LuckySamplingNum, "\n";
}
# for(my $i = 0; $i<100; $i++)
# {
	# my $id = int(rand(100));
	# print $id, "\n";
# }
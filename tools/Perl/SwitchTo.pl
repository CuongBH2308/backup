######
#
#SwitchTo.pl <ClientSpec> <Branch>
#SwitchTo.pl Baiyan-SHACNG8420TV6-InvSrc1 Main
#SwitchTo.pl Baiyan-SHACNG8420TV6-InvSrc2 InventorServer
#
#
#####
use strict;
my $ClientSpec = $ARGV[0];
my $Branch = $ARGV[1];

#1. Map R and N
my $RootForR;
if($Branch eq "Main")
{
	$RootForR = "D:\\InvSrc\\Main\\sources";
}
# elsif($Branch eq "InventorServer")
# {
	# $RootForR = "D:\\InvSrc\\streams\\Sikorsky\\dev\\InventorServer\\sources";
# }
elsif($Branch eq "ModularPlatform")
{
	$RootForR = "D:\\InvSrc\\streams\\Brunel\\dev\\ModularPlatform\\sources";
}
else
{
	die "Incorrect Branch parameter: $Branch. must be 'Main' or 'InventorServer'";
}

my $TargetDir = "InvSrc";
my $Index = substr($ClientSpec, length($ClientSpec)-1, 1);
unless($Index eq "1" or $Index eq "2" or $Index eq "3")
{
	die "Incorrect ClientSpec parameter: $ClientSpec";
}
$TargetDir .= $Index;

$RootForR =~ s/InvSrc/$TargetDir/i;
#print $RootForR;
print "Step1: Subst R and N\n\n";
print `subst N: /d`;
print `subst R: /d`;
print `subst R: $RootForR`;
print `subst N: "R:\\Application\\App"`;


#2. Set default ClientSpec
print "\nStep2: Set default p4 ClientSpec\n\n";
`p4 set P4CLIENT=$ClientSpec`;

#3. Update 3rd parties
print "\nStep3: Updating 3rd parties...\n\n";
print `call R:\\build\\versions.bat`;
`call R:\\build\\CheckDebugLinkPaths.bat`;
`call R:\\build\\SetDebugLinkPaths.bat`;

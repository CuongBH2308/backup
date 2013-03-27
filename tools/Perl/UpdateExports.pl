######
#
# Perl scripts export the functions in Server project  that used in Application project
# (We didn't because they used to be in the same project.)
#
# Author: Baiyan Huang
# Date: 12/02/2008
#
# Usage
# UpdateExports.pl <ApplicationProject> <ServerProject> <ExportTag>
# UpdateExports.pl R:\AppFw\FwUI\FwUI.vcproj R:\Server\Framework\Fw\Fw.vcproj FWEXPORT
#
# Steps
# 1. Link the application project and get link errors
# 2. Parse the link error to collect functions that need to be exported
# 3. Go through the source code, add FWEXPORT before the function declaration. (Open For Edit)
#
# Note:
# 1. You need to run this script from "Start CMD with Debug Inventor Environment"
# 2. If 2 function has the same name and parameter number, we consider it as one.
# 3. It won't work if there are nested class and namespace.
#
#####

use strict;
use File::Basename;
BEGIN{push @INC, &dirname($0);}
use Utils::Refactor_Utils;

#*********************************************Main*******************************************************
#Global variables
#<Classname::Functionname, @>
my %FunctionPrototypes; 
my $AppProject = @ARGV[0];
my $SrvProject = @ARGV[1];
my $ExportTag = @ARGV[2];
my $TotalExports;
my $RealExports;
my $FileName = &FileNameNoExt($AppProject);
&StartLog("C:\\UpdateExports_$FileName.log");
&StartReport("C:\\UpdateExports_$FileName.txt");

# 1. Link Application Project and get the link errors
&Report("Link $FileName and Get the link errors...\n");
my $BuildTool = '"vcbuild.exe"';
my $configuration = '"DEBUG|Win32"';
my @LinkErrors = `\"%VS90COMNTOOLS%vsvars32.bat\" & $BuildTool /link  $AppProject $configuration`;
print "=" x 80, "\n";
print "Link Error Numbers: ",scalar @LinkErrors, "\n";
print "=" x 80, "\n";
# 2. Parse link errors to get functions that need to be exported.
&Report("Parse link errors and get the prototype of the functions that need to be exported...\n");
foreach(@LinkErrors)
{
	# Just get link error 2019
	#FWxGripSnapOptionsDlg.obj : error LNK2019: unresolved external symbol "public: void __thiscall FWxGripSnapPreferences::SetShowStaticReferenceGeom(bool)" (?SetShowStaticReferenceGeom@FWxGripSnapPreferences@@QAEX_N@Z) referenced in function "protected: void __thiscall FWxGripSnapOptionsDlg::OnOk(void)" (?OnOk@FWxGripSnapOptionsDlg@@IAEXXZ)
	if(/error LNK2019.*?\".*?(\w+)::(~?\w+)\((.*?)\)[\s|\w]*\"/)
	{
		my $fullName = $1 . "::" . $2;
		my $ParamStr = $3;
		
		# UCxMeasurement::GetDecimals(void)const 
		# remove the last const
		#&Trace($ParamStr);

		if(!defined($FunctionPrototypes{$fullName}))
		{
			my @ParamsArray;
			$FunctionPrototypes{$fullName} = \@ParamsArray;
		}
		# (FWxDesignViewVisitor*, bool bVisitChildModifiers = true)
		my @Params = &GetParameterTypes($ParamStr);
		push @{$FunctionPrototypes{$fullName}}, \@Params;
		$TotalExports++;
		
		&Report( "\t", $fullName, "(", scalar @Params, ")\n");
	}

}

# 3. Update each source file to export functions.
&Report("Export functions for each server files...\n");
chdir &dirname($SrvProject);

my @ServerFiles = `dir /s /b *.h`;

#my @ServerFiles = ("r:\\Server\\CoreApps\\uc\\Main\\UCxMeasurement.h\n");
foreach my $ServerFile (@ServerFiles)
{
	&P4Edit($ServerFile);
	&Report($ServerFile);
	chomp $ServerFile;
	# open CURFILE, $ServerFile;
	# my @FileCons = <CURFILE>;
	# UpdateExportForEachFile(@FileCons);
	# close CURFILE;
	
	# if (++$Num > 10)  
	# {
		# &EndReport;
		# exit;
	# }
	&OverwriteFile($ServerFile, \&UpdateExportForEachFile);
}

&Report("Done!\n")
&Report("Total Exports: $TotalExports; Real Exports: $RealExports \n");
&EndLog();
&EndReport();
<STDIN>;

#**************************Functions**************************************************************
# Get the types of parameter declaration
# CString str -> CString
# Can't deal with complex case like: std::vector< CString > vecStr;
sub GetParameterTypes($)
{
	my @ParameterTypes;
	my $ParamStr = $_[0];
	#&Trace($ParamStr);
	$ParamStr = "" if($ParamStr =~ /^\s*void\s*$/); # If parameter is void, it has no paramter

	# Remove "," # Remove the "<>" pair of a type
	# class ATL::CStringT<wchar_t,class StrTraitMFC_DLL<wchar_t,class ATL::ChTraitsCRT<wchar_t> > > const & ->
	# class ATL::CStringT  const &
	while($ParamStr =~ /<[^<>]*?>/) 
	{
		$ParamStr =~ s/<[^<>]*?>//g;
	}
	
	my @RawParams  = split /,/, $ParamStr;
	# Following transform is very important
	# We use "space" as the spliter.
	@ParameterTypes = map {/\s*(.+?)($|(\s+))/; $_ = $1;} @RawParams;
	if(@RawParams != @ParameterTypes)
	{
		print "Doesn't match\n";
	}
	
	return @ParameterTypes;
}
# Return the function's prototype if current line is a function declaration (or inline implementation inside the class)
# 	FWEXPORT void Accept(FWxDesignViewVisitor*, bool bVisitChildModifiers = true);
#@p1: Current class name
#@p2: Current line
# @return: A array with first element as the full function name(class::functionname), and the rest are parameter types.
sub GetFunctionPrototype($$)
{
	my $ClassName = $_[0];
	my $CurLine = $_[1];
	my @Prototype;
	if($CurLine =~ /(~?\w+)\((.*)\)/s)
	{
		my $fullName = $ClassName . "::" . $1;
		#print "----->", $1, "\n";
		my $ParamStr = $2;
		#&Trace($ParamStr);
		@Prototype = &GetParameterTypes($ParamStr);
		#&Trace(join "->",@Prototype);
		unshift @Prototype, $fullName;
	}
	
	return @Prototype;
}

# Exporting functions in a file
# @params: all the content of a source file.
sub UpdateExportForEachFile()
{
	my $ResultContent;
	my @FileContent = @{$_[0]};
	my $CurClassName;
	my $FileLine = $#FileContent;
	foreach(my $i = 0; $i <= $FileLine; $i++)
	{
		my $CurLine = @FileContent[$i];
		# Comment
		if($CurLine =~ /^\s*\/\//)
		{
			$ResultContent .= $CurLine;
			next;
		}
		# Class, Nested class may not work.
		elsif($CurLine =~ /\s*class\s+(\w+)\s*[\n\:\{]/)
		{
			$CurClassName = $1;
			$ResultContent .= $CurLine;
			next;
		}
		# Namespace, nested namespace won't work
		elsif($CurLine =~ /\s*namespace\s+(\w+)?\s*{?/)
		{
			$CurClassName = "" if(!defined($1));

			$CurClassName = $1;
			$ResultContent .= $CurLine;
			next;
		}
		
		# If In a class or namespace
		if(defined($CurClassName))
		{
			# if there is a "( "and a ",", we consider it as a mulitple line function declaration.
			# 	UCxCompositeCompInterfaceSelection(	RSeRef<UCxCompInterfaceNode>		rCompInterfaceNode,
			#							const BRxAbsPath&					brPath );
			my $BackupCurLine = $CurLine;
			if($CurLine =~ /^(.*?)\((.*?),\s*$/)
			{
				my $EndDeclare = 0;
				
				while(! $EndDeclare)
				{
					$i++;
					my $SubLine = @FileContent[$i];
					$BackupCurLine .= $SubLine;
					next if($SubLine =~ /(^\s*\/\/)|(^\s+$)/);
					chomp $CurLine;
					$SubLine =~ s/\/\/.*?$//;
					$CurLine .= $SubLine;
					# End with ); we consider it as end function declaration.
					$EndDeclare = 1 if($SubLine =~ /\)\s*;\s*$/);
					$EndDeclare = 1 if($i >= $FileLine);
					
				}
				#&Report($CurLine);
			}
			# Deal with comments
			my @funcPrototype = &GetFunctionPrototype($CurClassName, $CurLine);
			
			$CurLine = $BackupCurLine;
			
			# It is not a function declaration
			if(@funcPrototype == 0)
			{
				$ResultContent .= $BackupCurLine;
				next;
			}
			
			# Get function full name
			my $fullName = shift @funcPrototype;
			
			# Is it a link error?
			if(exists $FunctionPrototypes{$fullName})
			{
				my $ParamNo = @funcPrototype;
				#&Trace($fullName, $ParamNo);
			
				foreach(@{$FunctionPrototypes{$fullName}})
				{
					# if 2 functions has same paramter number, we treat it as one.
					if($ParamNo == @{$_})
					{
						&Report("\tExports->", "$fullName($ParamNo)\n");
						if($CurLine !~ /^\s*$ExportTag/)
						{
							$CurLine =~ /^(\s*)(.*)$/s; # Deal with multiline
							$CurLine = $1 . $ExportTag . " ". $2;
							$RealExports++;
						}
					}
				}
			}
			$ResultContent .= $CurLine;
			next;
		}
		
		$ResultContent .= $CurLine;
	}
	return $ResultContent;
}

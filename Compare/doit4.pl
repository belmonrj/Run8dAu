#!/usr/bin/perl



$diagnostic = 0;



open(LISTPP,"<newlist_plusplus") or die "cannot open file \n";
@filename = <LISTPP>;
chomp(@filename);



open(LISTPPA,"<runlistApp.txt") or die "cannot open file \n";
@runlistppa = <LISTPPA>;
chomp(@runlistppa);

open(LISTPPB,"<runlistBpp.txt") or die "cannot open file \n";
@runlistppb = <LISTPPB>;
chomp(@runlistppb);

open(LISTPPC,"<runlistCpp.txt") or die "cannot open file \n";
@runlistppc = <LISTPPC>;
chomp(@runlistppc);

open(LISTPPD,"<runlistDpp.txt") or die "cannot open file \n";
@runlistppd = <LISTPPD>;
chomp(@runlistppd);



open(OUTPPA,">outApp.txt") or die "cannot open file \n";

open(OUTPPB,">outBpp.txt") or die "cannot open file \n";

open(OUTPPC,">outCpp.txt") or die "cannot open file \n";

open(OUTPPD,">outDpp.txt") or die "cannot open file \n";


for($i=0; $i<$#filename+1; $i++)
{

    $name = $filename[$i];
    @tokens = split(/_/,$name);
    $run = $tokens[1];
    $segment = $tokens[2];

    $nextname = $filename[$i+1];
    @nexttokens = split(/_/,$nextname);
    $nextrun = $nexttokens[1];
    $nextsegment = $nexttokens[2];

    print "filename is $name \n" if $diagnostic;

    if($run==$runlistppa[0])
    {
	print "filename to print to file for ppa is $name \n" if $diagnostic;
	print OUTPPA $name."\n";
	if($nextrun!=$run)
	{
	    print "last one for run $run, next run is $nextrun \n" if $diagnostic;
	    shift @runlistppa;
	}
    }

    if($run==$runlistppb[0])
    {
	print "filename to print to file for ppb is $name \n" if $diagnostic;
	print OUTPPB $name."\n";
	if($nextrun!=$run)
	{
	    print "last one for run $run, next run is $nextrun \n" if $diagnostic;
	    shift @runlistppb;
	}
    }

    if($run==$runlistppc[0])
    {
	print "filename to print to file for ppc is $name \n" if $diagnostic;
	print OUTPPC $name."\n";
	if($nextrun!=$run)
	{
	    print "last one for run $run, next run is $nextrun \n" if $diagnostic;
	    shift @runlistppc;
	}
    }

    if($run==$runlistppd[0])
    {
	print "filename to print to file for ppd is $name \n" if $diagnostic;
	print OUTPPD $name."\n";
	if($nextrun!=$run)
	{
	    print "last one for run $run, next run is $nextrun \n" if $diagnostic;
	    shift @runlistppd;
	}
    }


}

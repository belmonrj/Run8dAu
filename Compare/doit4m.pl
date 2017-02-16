#!/usr/bin/perl



$diagnostic = 0;



open(LISTMM,"<newlist_minusminus") or die "cannot open file \n";
@filename = <LISTMM>;
chomp(@filename);



open(LISTMMA,"<runlistAmm.txt") or die "cannot open file \n";
@runlistmma = <LISTMMA>;
chomp(@runlistmma);

open(LISTMMB,"<runlistBmm.txt") or die "cannot open file \n";
@runlistmmb = <LISTMMB>;
chomp(@runlistmmb);

open(LISTMMC,"<runlistCmm.txt") or die "cannot open file \n";
@runlistmmc = <LISTMMC>;
chomp(@runlistmmc);

open(LISTMMD,"<runlistDmm.txt") or die "cannot open file \n";
@runlistmmd = <LISTMMD>;
chomp(@runlistmmd);



open(OUTMMA,">outAmm.txt") or die "cannot open file \n";

open(OUTMMB,">outBmm.txt") or die "cannot open file \n";

open(OUTMMC,">outCmm.txt") or die "cannot open file \n";

open(OUTMMD,">outDmm.txt") or die "cannot open file \n";


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

    if($run==$runlistmma[0])
    {
	print "filename to print to file for mma is $name \n" if $diagnostic;
	print OUTMMA $name."\n";
	if($nextrun!=$run)
	{
	    print "last one for run $run, next run is $nextrun \n" if $diagnostic;
	    shift @runlistmma;
	}
    }

    if($run==$runlistmmb[0])
    {
	print "filename to print to file for mmb is $name \n" if $diagnostic;
	print OUTMMB $name."\n";
	if($nextrun!=$run)
	{
	    print "last one for run $run, next run is $nextrun \n" if $diagnostic;
	    shift @runlistmmb;
	}
    }

    if($run==$runlistmmc[0])
    {
	print "filename to print to file for mmc is $name \n" if $diagnostic;
	print OUTMMC $name."\n";
	if($nextrun!=$run)
	{
	    print "last one for run $run, next run is $nextrun \n" if $diagnostic;
	    shift @runlistmmc;
	}
    }

    if($run==$runlistmmd[0])
    {
	print "filename to print to file for mmd is $name \n" if $diagnostic;
	print OUTMMD $name."\n";
	if($nextrun!=$run)
	{
	    print "last one for run $run, next run is $nextrun \n" if $diagnostic;
	    shift @runlistmmd;
	}
    }


}

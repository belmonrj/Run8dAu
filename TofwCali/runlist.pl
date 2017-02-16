#!/usr/local/bin/perl


@lines = qx(ls pDST);

@found = ();

foreach $line (@lines)
{

    chomp($line);

    @data = split /_/,$line;

    $duplicate = 0;

    foreach $n (@found)
    {

	if($n==$data[1])
	{
	    $duplicate = 1;
	}

    }

    if($duplicate==0)
    {
	push(@found,$data[1]);
	print $data[1] . "\n";
    }



}




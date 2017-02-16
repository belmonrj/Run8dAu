void runlists()
{



  ifstream fin("runs.txt");
  ofstream foutApp("runlistApp.txt");
  ofstream foutBpp("runlistBpp.txt");
  ofstream foutCpp("runlistCpp.txt");
  ofstream foutDpp("runlistDpp.txt");
  ofstream foutAmm("runlistAmm.txt");
  ofstream foutBmm("runlistBmm.txt");
  ofstream foutCmm("runlistCmm.txt");
  ofstream foutDmm("runlistDmm.txt");

  int run;
  float bbcll1;
  float zdcoff;

  for(int i=0; i<848; i++)
    {
      fin>>run>>bbcll1>>zdcoff;
      if(run<250593)
	{
	  if(bbcll1<50000) foutApp<<run<<endl;
	  else if(bbcll1<100000) foutBpp<<run<<endl;
	  else if(bbcll1<200000) foutCpp<<run<<endl;
	  else if(bbcll1>=200000) foutDpp<<run<<endl;
	}
      else if(run>250484)
	{
	  if(bbcll1<50000) foutAmm<<run<<endl;
	  else if(bbcll1<100000) foutBmm<<run<<endl;
	  else if(bbcll1<200000) foutCmm<<run<<endl;
	  else if(bbcll1>=200000) foutDmm<<run<<endl;
	}
      else cout<<"unknown runnumber"<<endl;
    }


}

void rbr()
{

  int runindex, run;
  float offset = 0.0;

  ifstream fin("runs.list");
  ofstream fout("run-by-run-pass0.dat");
  for(int i=0; i<848; i++)
    {
      fin>>run;
      runindex = i;
      fout<<runindex<<"\t"<<run<<"\t"<<offset<<endl;
    }

}

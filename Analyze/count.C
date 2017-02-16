void count(char *filelist = "lowlist_plusplus")
{

  int ifile=0;
  Long64_t nevents = 0;
  //Long64_t nentries = 0;
  char filename[100];

  ifstream fin(filelist);
  while(fin.getline(filename,100))
    {
      //ifile++; 
      //cout<<ifile<<" "<<filename<<endl;

      TFile *f = TFile::Open(filename);
      if(!f) {cout<<"pDST input error: file does not exist "<<endl; continue;}
      nevents += (Long64_t)((TH1F *)f->Get("hcent"))->GetEntries();
      //TTree *t = (TTree *)f->Get("hadrontree");
      //if(!t) {cout<<"pDST input error: tree does not exist "<<endl; continue;}
      //nentries += t->GetEntries();
      //t->Delete();
      f->Close();
      f->Delete();

    }
  fin.close();

  cout<<"Number of events: "<<nevents<<endl;
  //cout<<"nentries = "<<nentries<<endl;

}

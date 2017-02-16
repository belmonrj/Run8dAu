void neg_zerothree(int start=5, int end=30, float low=-1.0, float high=1.0)
{

  cout<<"we're going to look at the 0-3 GeV region of the "<<endl
      <<"pid distribution in different centrality bins"<<endl;

  TFile *file = TFile::Open("outnew_pp.root");

  if(file==NULL){cerr<<"histogram file not found"<<endl; return;}

  TH2F *hhnegpi_cent0020 = (TH2F *)file->Get("isPi_dis_neg_cent0020");
  TH2F *hhnegpi_cent2040 = (TH2F *)file->Get("isPi_dis_neg_cent2040");
  TH2F *hhnegpi_cent4060 = (TH2F *)file->Get("isPi_dis_neg_cent4060");
  TH2F *hhnegpi_cent6088 = (TH2F *)file->Get("isPi_dis_neg_cent6088");

  TH2F *hhnegk_cent0020 = (TH2F *)file->Get("isK_dis_neg_cent0020");
  TH2F *hhnegk_cent2040 = (TH2F *)file->Get("isK_dis_neg_cent2040");
  TH2F *hhnegk_cent4060 = (TH2F *)file->Get("isK_dis_neg_cent4060");
  TH2F *hhnegk_cent6088 = (TH2F *)file->Get("isK_dis_neg_cent6088");

  TH2F *hhnegp_cent0020 = (TH2F *)file->Get("isP_dis_neg_cent0020");
  TH2F *hhnegp_cent2040 = (TH2F *)file->Get("isP_dis_neg_cent2040");
  TH2F *hhnegp_cent4060 = (TH2F *)file->Get("isP_dis_neg_cent4060");
  TH2F *hhnegp_cent6088 = (TH2F *)file->Get("isP_dis_neg_cent6088");

  TF1 *fun = new TF1("fun","gaus",-10,10);

  char figname[100];
  char datname[100];
  ofstream fpi;
  ofstream fk;
  ofstream fp;
  float pT;






  // ------------ //
  // --- 0020 --- //
  // ------------ //

  if(hhnegpi_cent0020==NULL||
     hhnegk_cent0020==NULL||
     hhnegp_cent0020==NULL)
    cerr<<"0020 centrality histogram not found, skipping"<<endl;
  else
    {
      sprintf(datname,"ZeroThree/negpi_cent0020.dat");
      fpi.open(datname);
      sprintf(datname,"ZeroThree/negk_cent0020.dat");
      fk.open(datname);
      sprintf(datname,"ZeroThree/negp_cent0020.dat");
      fp.open(datname);
      for(int i=start; i<end; i++)
	{
	  pT = i/10.0+0.05;
	  //pi
	  hhnegpi_cent0020->ProjectionY("hpi",i+1,i+1);
	  hpi->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negpi_cent0020_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negpi_cent0020_%d.eps",i+1);
	  c1->Print(figname);
	  fpi<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	  //k
	  hhnegk_cent0020->ProjectionY("hk",i+1,i+1);
	  hk->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negk_cent0020_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negk_cent0020_%d.eps",i+1);
	  c1->Print(figname);
	  fk<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	  //p
	  hhnegp_cent0020->ProjectionY("hp",i+1,i+1);
	  hp->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negp_cent0020_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negp_cent0020_%d.eps",i+1);
	  c1->Print(figname);
	  fp<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	}
      fpi.close();
      fk.close();
      fp.close();
    }



  // ------------ //
  // --- 2040 --- //
  // ------------ //

  if(hhnegpi_cent2040==NULL||
     hhnegk_cent2040==NULL||
     hhnegp_cent2040==NULL)
    cerr<<"2040 centrality histogram not found, skipping"<<endl;
  else
    {
      sprintf(datname,"ZeroThree/negpi_cent2040.dat");
      fpi.open(datname);
      sprintf(datname,"ZeroThree/negk_cent2040.dat");
      fk.open(datname);
      sprintf(datname,"ZeroThree/negp_cent2040.dat");
      fp.open(datname);
      for(int i=start; i<end; i++)
	{
	  pT = i/10.0+0.05;
	  //pi
	  hhnegpi_cent2040->ProjectionY("hpi",i+1,i+1);
	  hpi->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negpi_cent2040_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negpi_cent2040_%d.eps",i+1);
	  c1->Print(figname);
	  fpi<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	  //k
	  hhnegk_cent2040->ProjectionY("hk",i+1,i+1);
	  hk->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negk_cent2040_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negk_cent2040_%d.eps",i+1);
	  c1->Print(figname);
	  fk<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	  //p
	  hhnegp_cent2040->ProjectionY("hp",i+1,i+1);
	  hp->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negp_cent2040_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negp_cent2040_%d.eps",i+1);
	  c1->Print(figname);
	  fp<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	}
      fpi.close();
      fk.close();
      fp.close();
    }



  // ------------ //
  // --- 4060 --- //
  // ------------ //

  if(hhnegpi_cent4060==NULL||
     hhnegk_cent4060==NULL||
     hhnegp_cent4060==NULL)
    cerr<<"4060 centrality histogram not found, skipping"<<endl;
  else
    {
      sprintf(datname,"ZeroThree/negpi_cent4060.dat");
      fpi.open(datname);
      sprintf(datname,"ZeroThree/negk_cent4060.dat");
      fk.open(datname);
      sprintf(datname,"ZeroThree/negp_cent4060.dat");
      fp.open(datname);
      for(int i=start; i<end; i++)
	{
	  pT = i/10.0+0.05;
	  //pi
	  hhnegpi_cent4060->ProjectionY("hpi",i+1,i+1);
	  hpi->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negpi_cent4060_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negpi_cent4060_%d.eps",i+1);
	  c1->Print(figname);
	  fpi<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	  //k
	  hhnegk_cent4060->ProjectionY("hk",i+1,i+1);
	  hk->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negk_cent4060_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negk_cent4060_%d.eps",i+1);
	  c1->Print(figname);
	  fk<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	  //p
	  hhnegp_cent4060->ProjectionY("hp",i+1,i+1);
	  hp->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negp_cent4060_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negp_cent4060_%d.eps",i+1);
	  c1->Print(figname);
	  fp<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	}
      fpi.close();
      fk.close();
      fp.close();
    }



  // ------------ //
  // --- 6088 --- //
  // ------------ //

  if(hhnegpi_cent6088==NULL||
     hhnegk_cent6088==NULL||
     hhnegp_cent6088==NULL)
    cerr<<"6088 centrality histogram not found, skipping"<<endl;
  else
    {
      sprintf(datname,"ZeroThree/negpi_cent6088.dat");
      fpi.open(datname);
      sprintf(datname,"ZeroThree/negk_cent6088.dat");
      fk.open(datname);
      sprintf(datname,"ZeroThree/negp_cent6088.dat");
      fp.open(datname);
      for(int i=start; i<end; i++)
	{
	  pT = i/10.0+0.05;
	  //pi
	  hhnegpi_cent6088->ProjectionY("hpi",i+1,i+1);
	  hpi->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negpi_cent6088_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negpi_cent6088_%d.eps",i+1);
	  c1->Print(figname);
	  fpi<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	  //k
	  hhnegk_cent6088->ProjectionY("hk",i+1,i+1);
	  hk->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negk_cent6088_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negk_cent6088_%d.eps",i+1);
	  c1->Print(figname);
	  fk<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	  //p
	  hhnegp_cent6088->ProjectionY("hp",i+1,i+1);
	  hp->Fit(fun,"","",low,high);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negp_cent6088_%d.gif",i+1);
	  c1->Print(figname);
	  sprintf(figname,"ZeroThree/FitFigs/fit_negp_cent6088_%d.eps",i+1);
	  c1->Print(figname);
	  fp<<pT<<"\t"<<fun->GetParameter(1)<<"\t"<<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"<<fun->GetParError(2)<<"\t"<<endl;
	}
      fpi.close();
      fk.close();
      fp.close();
    }





  cout<<"Done!  Have a nice day!"<<endl;

  return;

}

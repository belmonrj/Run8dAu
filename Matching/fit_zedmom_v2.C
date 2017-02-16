void fit_zedmom_v2(
		   char *field="minusminus",
		   char *sector="sector2",
		   char *type="posmom_poszed4"
		   )
{

  cout<<"starting!"<<endl;

  char rootname[20];
  sprintf(rootname,"out_%s.root",field);
  cout<<"root file name is "<<rootname<<endl;

  char histnamedz[50];
  sprintf(histnamedz,"hh_%s_tofwdz_%s",sector,type);
  cout<<"name of tofwdz histogram is "<<histnamedz<<endl;

  char histnamedphi[50];
  sprintf(histnamedphi,"hh_%s_tofwdphi_%s",sector,type);
  cout<<"name of tofwdphi histogram is "<<histnamedphi<<endl;

  char filenamedz[80];
  sprintf(filenamedz,"ZedMom/hh_%s_tofwdz_%s_%s.dat",sector,type,field);
  cout<<"name of tofwdz output file is "<<filenamedz<<endl;

  char filenamedphi[80];
  sprintf(filenamedphi,"ZedMom/hh_%s_tofwdphi_%s_%s.dat",sector,type,field);
  cout<<"name of tofwdphi output file is "<<filenamedphi<<endl;

  TFile *f = TFile::Open(rootname);
  TH2F *histdz = (TH2F *)f->Get(histnamedz);
  TH2F *histdphi = (TH2F *)f->Get(histnamedphi);
  ofstream foutdz(filenamedz);
  ofstream foutdphi(filenamedphi);

  TF1 *fun = new TF1("fun","gaus",-20,20);

  char figname[110];

  TCanvas *c1 = new TCanvas();

  for(int i=0; i<50; i++)
    {
      float mom = i/10.0+0.05;
      histdz->ProjectionY("hhdz",i+1,i+1);
      float maximum = hhdz->GetBinCenter(hhdz->GetMaximumBin());
      hhdz->Fit("fun","","",maximum-3,maximum+3);
      sprintf(figname,"ZedMom/figs/hh_%s_tofwdz_%s_%s_%d.gif",sector,type,field,i);
      c1->Print(figname);
      foutdz<<mom<<"\t"
	    <<maximum<<"\t"
	    <<fun->GetParameter(1)<<"\t"
	    <<fun->GetParError(1)<<"\t"
	    <<fun->GetParameter(2)<<"\t"
	    <<fun->GetParError(2)<<endl;

      histdphi->ProjectionY("hhdphi",i+1,i+1);
      maximum = hhdphi->GetBinCenter(hhdphi->GetMaximumBin());
      hhdphi->Fit("fun","","",maximum-0.003,maximum+0.003);
      sprintf(figname,"ZedMom/figs/hh_%s_tofwdphi_%s_%s_%d.gif",sector,type,field,i);
      c1->Print(figname);
      foutdphi<<mom<<"\t"
	      <<maximum<<"\t"
	      <<fun->GetParameter(1)<<"\t"
	      <<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"
	      <<fun->GetParError(2)<<endl;
    }



}

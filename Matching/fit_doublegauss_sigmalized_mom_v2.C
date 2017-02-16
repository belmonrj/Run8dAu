void fit_doublegauss_sigmalized_mom_v2(
				       char *field="minusminus",
				       char *type="neg"
				       )
{
  
  gStyle->SetOptTitle(0);
  
  cout<<"starting!"<<endl;

  char rootname[20];
  sprintf(rootname,"out_%s.root",field);
  cout<<"root file name is "<<rootname<<endl;

  char histnamedz[50];
  sprintf(histnamedz,"hh_%s_mom_tofwsdz",type);
  cout<<"name of tofwdz histogram is "<<histnamedz<<endl;

  char histnamedphi[50];
  sprintf(histnamedphi,"hh_%s_mom_tofwsdphi",type);
  cout<<"name of tofwdphi histogram is "<<histnamedphi<<endl;

  char filenamedz[80];
  sprintf(filenamedz,"DoubleGauss_SigmaMom/hh_%s_mom_tofwsdz_%s.dat",type,field);
  cout<<"name of tofwdz output file is "<<filenamedz<<endl;

  char filenamedphi[80];
  sprintf(filenamedphi,"DoubleGauss_SigmaMom/hh_%s_mom_tofwsdphi_%s.dat",type,field);
  cout<<"name of tofwdphi output file is "<<filenamedphi<<endl;

  TFile *f = TFile::Open(rootname);
  TH2F *histdz = (TH2F *)f->Get(histnamedz);
  TH2F *histdphi = (TH2F *)f->Get(histnamedphi);
  ofstream foutdz(filenamedz);
  ofstream foutdphi(filenamedphi);

  TF1 *fun = new TF1("fun","gaus(0)+gaus(3)",-10,10);

  char figname[110];

  TCanvas *c1 = new TCanvas("c1","c1",800,600);

  for(int i=0; i<50; i++)
    {
      fun->SetParameter(1,0.0);
      fun->SetParameter(2,1.0);
      fun->SetParameter(4,0.0);
      fun->SetParameter(5,5.0);

      float mom = i/10.0+0.05;
      histdz->ProjectionY("hhdz",i+1,i+1);
      float maximum = hhdz->GetBinCenter(hhdz->GetMaximumBin());
      //hhdz->Fit("fun","","",maximum-2,maximum+2);
      hhdz->Fit("fun","R");
      sprintf(figname,"DoubleGauss_SigmaMom/figs/hh_%s_mom_tofwsdz_%s_%d.gif",type,field,i);
      c1->Print(figname);
      foutdz<<mom<<"\t"
	    <<maximum<<"\t"
	    <<fun->GetParameter(1)<<"\t"
	    <<fun->GetParError(1)<<"\t"
	    <<fun->GetParameter(2)<<"\t"
	    <<fun->GetParError(2)<<endl;

      histdphi->ProjectionY("hhdphi",i+1,i+1);
      maximum = hhdphi->GetBinCenter(hhdphi->GetMaximumBin());
      //hhdphi->Fit("fun","","",maximum-2.0,maximum+2.0);
      hhdphi->Fit("fun","R");
      sprintf(figname,"DoubleGauss_SigmaMom/figs/hh_%s_mom_tofwsdphi_%s_%d.gif",type,field,i);
      c1->Print(figname);
      foutdphi<<mom<<"\t"
	      <<maximum<<"\t"
	      <<fun->GetParameter(1)<<"\t"
	      <<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"
	      <<fun->GetParError(2)<<endl;
    }



}

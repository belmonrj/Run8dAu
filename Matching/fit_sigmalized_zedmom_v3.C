void fit_sigmalized_zedmom_v3(
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
  sprintf(histnamedz,"hh_%s_tofwsdz_%s",sector,type);
  cout<<"name of tofwdz histogram is "<<histnamedz<<endl;

  char histnamedphi[50];
  sprintf(histnamedphi,"hh_%s_tofwsdphi_%s",sector,type);
  cout<<"name of tofwdphi histogram is "<<histnamedphi<<endl;

  char filenamedz[80];
  sprintf(filenamedz,"SigmaliZedMom/hh_%s_tofwsdz_%s_%s.dat",sector,type,field);
  cout<<"name of tofwdz output file is "<<filenamedz<<endl;

  char filenamedphi[80];
  sprintf(filenamedphi,"SigmaliZedMom/hh_%s_tofwsdphi_%s_%s.dat",sector,type,field);
  cout<<"name of tofwdphi output file is "<<filenamedphi<<endl;

  TFile *f = TFile::Open(rootname);
  TH2F *histdz = (TH2F *)f->Get(histnamedz);
  TH2F *histdphi = (TH2F *)f->Get(histnamedphi);
  ofstream foutdz(filenamedz);
  ofstream foutdphi(filenamedphi);

  TF1 *fun = new TF1("fun","gaus",-10,10);

  char figname[110];

  TCanvas *c1 = new TCanvas("c1","c1",800,600);

  for(int i=0; i<40; i++)
    {
      float mom = i/10.0+0.05;
      histdz->ProjectionY("hhdz",i+1,i+1);
      float maximum = hhdz->GetBinCenter(hhdz->GetMaximumBin());
      //hhdz->Fit("fun","","",maximum-2,maximum+2);
      hhdz->Fit("fun","","",-2.0,2.0);
      sprintf(figname,"SigmaliZedMom/figs/hh_%s_tofwsdz_%s_%s_%d.gif",sector,type,field,i);
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
      hhdphi->Fit("fun","","",-2.0,2.0);
      sprintf(figname,"SigmaliZedMom/figs/hh_%s_tofwsdphi_%s_%s_%d.gif",sector,type,field,i);
      c1->Print(figname);
      foutdphi<<mom<<"\t"
	      <<maximum<<"\t"
	      <<fun->GetParameter(1)<<"\t"
	      <<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"
	      <<fun->GetParError(2)<<endl;
    }

  for(int i=8; i<10; i++)
    {
      float mom = i/2.0+0.25;
      int j = i*5;

      histdz->ProjectionY("hhhdz",j+1,j+5);
      float maximum = hhhdz->GetBinCenter(hhhdz->GetMaximumBin());
      //hhhdz->Fit("fun","","",maximum-2,maximum+2);
      hhhdz->Fit("fun","","",-2.0,2.0);
      sprintf(figname,"SigmaliZedMom/figs/hh_%s_tofwsdz_%s_%s_%d.gif",sector,type,field,j);
      c1->Print(figname);
      foutdz<<mom<<"\t"
	    <<maximum<<"\t"
	    <<fun->GetParameter(1)<<"\t"
	    <<fun->GetParError(1)<<"\t"
	    <<fun->GetParameter(2)<<"\t"
	    <<fun->GetParError(2)<<endl;

      histdphi->ProjectionY("hhhdphi",j+1,j+5);
      maximum = hhhdphi->GetBinCenter(hhhdphi->GetMaximumBin());
      //hhhdphi->Fit("fun","","",maximum-2.0,maximum+2.0);
      hhhdphi->Fit("fun","","",-2.0,2.0);
      sprintf(figname,"SigmaliZedMom/figs/hh_%s_tofwsdphi_%s_%s_%d.gif",sector,type,field,j);
      c1->Print(figname);
      foutdphi<<mom<<"\t"
	      <<maximum<<"\t"
	      <<fun->GetParameter(1)<<"\t"
	      <<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"
	      <<fun->GetParError(2)<<endl;
    }


}

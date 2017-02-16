void fit_zedmom_v2R(
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

  for(int i=0; i<40; i++)
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
      cout<<endl<<"mom is "<<mom<<endl<<endl;
    }

  for(int i=8; i<10; i++)
    {
      float mom = i/2.0+0.25;
      int j = i*5;

      float MWdz1, MWdz2, MWdz3, MWdz4, MWdz5;
      float momdz1, momdz2, momdz3, momdz4, momdz5;
      histdz->ProjectionY("hmomdz",j+1,j+1);
      MWdz1 = hmomdz->GetEntries();
      histdz->ProjectionY("hmomdz",j+2,j+2);
      MWdz2 = hmomdz->GetEntries();
      histdz->ProjectionY("hmomdz",j+3,j+3);
      MWdz3 = hmomdz->GetEntries();
      histdz->ProjectionY("hmomdz",j+4,j+4);
      MWdz4 = hmomdz->GetEntries();
      histdz->ProjectionY("hmomdz",j+5,j+5);
      MWdz5 = hmomdz->GetEntries();

      momdz1 = mom-0.2;
      momdz2 = mom-0.1;
      momdz3 = mom;
      momdz4 = mom+0.1;
      momdz5 = mom+0.2;

      float MOMDZ = (MWdz1*momdz1+MWdz2*momdz2+MWdz3*momdz3+MWdz4*momdz4+MWdz5*momdz5)/(MWdz1+MWdz2+MWdz3+MWdz4+MWdz5);


      histdz->ProjectionY("hhhdz",j+1,j+5);
      float maximum = hhhdz->GetBinCenter(hhdz->GetMaximumBin());
      hhhdz->Fit("fun","","",maximum-3,maximum+3);
      sprintf(figname,"ZedMom/figs/hh_%s_tofwdz_%s_%s_%d.gif",sector,type,field,j);
      c1->Print(figname);
      foutdz<<mom<<"\t"
	    <<maximum<<"\t"
	    <<fun->GetParameter(1)<<"\t"
	    <<fun->GetParError(1)<<"\t"
	    <<fun->GetParameter(2)<<"\t"
	    <<fun->GetParError(2)<<endl;
      
      histdphi->ProjectionY("hhhdphi",j+1,j+5);
      maximum = hhhdphi->GetBinCenter(hhdphi->GetMaximumBin());
      hhhdphi->Fit("fun","","",maximum-0.003,maximum+0.003);
      sprintf(figname,"ZedMom/figs/hh_%s_tofwdphi_%s_%s_%d.gif",sector,type,field,j);
      c1->Print(figname);
      foutdphi<<mom<<"\t"
	      <<maximum<<"\t"
	      <<fun->GetParameter(1)<<"\t"
	      <<fun->GetParError(1)<<"\t"
	      <<fun->GetParameter(2)<<"\t"
	      <<fun->GetParError(2)<<endl;
      cout<<endl<<"mom is "<<mom<<endl<<endl;
      cout<<endl<<"momdz is "<<MOMDZ<<endl<<endl;
      cout<<"MWdz1 is "<<MWdz1<<" and momdz1 is "<<momdz1<<endl;
      cout<<"MWdz2 is "<<MWdz2<<" and momdz2 is "<<momdz2<<endl;
      cout<<"MWdz3 is "<<MWdz3<<" and momdz3 is "<<momdz3<<endl;
      cout<<"MWdz4 is "<<MWdz4<<" and momdz4 is "<<momdz4<<endl;
      cout<<"MWdz5 is "<<MWdz5<<" and momdz5 is "<<momdz5<<endl;

    }


}

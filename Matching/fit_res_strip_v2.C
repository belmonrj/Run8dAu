void fit_res_strip_v2()
{

  //gStyle->SetOptStat(0);
  //gStyle->SetOptFit(1);

  TCanvas *c1 = new TCanvas();
  char figname[70];

  // ---

  TFile *f = TFile::Open("out_plusplus.root");
  TF1 *fun_gaus = new TF1("fun_gaus","gaus",-5,5);

  TH2F *hh_posdz = (TH2F *)f->Get("hh_pos_strip_tofwdz");
  ofstream foutposdz("residual/res_strip_posdz_plusplus.dat");
  for(int i=0; i<512; i++)
    {
      int striptofw = i;
      hh_posdz->ProjectionY("h_posdz",i+1,i+1);
      float maximum = h_posdz->GetBinCenter(h_posdz->GetMaximumBin());    
      h_posdz->Fit("fun_gaus","","",maximum-2,maximum+2);
      sprintf(figname,"residual/figs/res_strip_posdz_%d_plusplus.gif",i);
      c1->Print(figname);
      foutposdz<<striptofw<<"\t"
	       <<maximum<<"\t"
	       <<fun_gaus->GetParameter(1)<<"\t"
	       <<fun_gaus->GetParError(1)<<"\t"
	       <<fun_gaus->GetParameter(2)<<"\t"
	       <<fun_gaus->GetParError(2)<<endl;
    }

  TH2F *hh_negdz = (TH2F *)f->Get("hh_neg_strip_tofwdz");
  ofstream foutnegdz("residual/res_strip_negdz_plusplus.dat");
  for(int i=0; i<512; i++)
    {
      int striptofw = i;
      hh_negdz->ProjectionY("h_negdz",i+1,i+1);
      float maximum = h_negdz->GetBinCenter(h_negdz->GetMaximumBin());    
      h_negdz->Fit("fun_gaus","","",maximum-2,maximum+2);
      sprintf(figname,"residual/figs/res_strip_negdz_%d_plusplus.gif",i);
      c1->Print(figname);
      foutnegdz<<striptofw<<"\t"
	       <<maximum<<"\t"
	       <<fun_gaus->GetParameter(1)<<"\t"
	       <<fun_gaus->GetParError(1)<<"\t"
	       <<fun_gaus->GetParameter(2)<<"\t"
	       <<fun_gaus->GetParError(2)<<endl;
    }

  // ---

  TH2F *hh_posdphi = (TH2F *)f->Get("hh_pos_strip_tofwdphi");
  ofstream foutposdphi("residual/res_strip_posdphi_plusplus.dat");
  for(int i=0; i<512; i++)
    {
      int striptofw = i;
      hh_posdphi->ProjectionY("h_posdphi",i+1,i+1);
      float maximum = h_posdphi->GetBinCenter(h_posdphi->GetMaximumBin());    
      h_posdphi->Fit("fun_gaus","","",maximum-0.003,maximum+0.003);
      sprintf(figname,"residual/figs/res_strip_posdphi_%d_plusplus.gif",i);
      c1->Print(figname);
      foutposdphi<<striptofw<<"\t"
		 <<maximum<<"\t"
		 <<fun_gaus->GetParameter(1)<<"\t"
		 <<fun_gaus->GetParError(1)<<"\t"
		 <<fun_gaus->GetParameter(2)<<"\t"
		 <<fun_gaus->GetParError(2)<<endl;
    }

  TH2F *hh_negdphi = (TH2F *)f->Get("hh_neg_strip_tofwdphi");
  ofstream foutnegdphi("residual/res_strip_negdphi_plusplus.dat");
  for(int i=0; i<512; i++)
    {
      int striptofw = i;
      hh_negdphi->ProjectionY("h_negdphi",i+1,i+1);
      float maximum = h_negdphi->GetBinCenter(h_negdphi->GetMaximumBin());    
      h_negdphi->Fit("fun_gaus","","",maximum-0.003,maximum+0.003);
      sprintf(figname,"residual/figs/res_strip_negdphi_%d_plusplus.gif",i);
      c1->Print(figname);
      foutnegdphi<<striptofw<<"\t"
		 <<maximum<<"\t"
		 <<fun_gaus->GetParameter(1)<<"\t"
		 <<fun_gaus->GetParError(1)<<"\t"
		 <<fun_gaus->GetParameter(2)<<"\t"
		 <<fun_gaus->GetParError(2)<<endl;
    }

  // --- BREAK!!!

  TFile *fnew = TFile::Open("out_minusminus.root");
  TF1 *fun_gaus = new TF1("fun_gaus","gaus",-5,5);

  TH2F *hh_new_posdz = (TH2F *)fnew->Get("hh_pos_strip_tofwdz");
  ofstream foutposdz("residual/res_strip_posdz_minusminus.dat");
  for(int i=0; i<512; i++)
    {
      int striptofw = i;
      hh_new_posdz->ProjectionY("h_new_posdz",i+1,i+1);
      float maximum = h_new_posdz->GetBinCenter(h_new_posdz->GetMaximumBin());    
      h_new_posdz->Fit("fun_gaus","","",maximum-2,maximum+2);
      sprintf(figname,"residual/figs/res_strip_posdz_%d_minusminus.gif",i);
      c1->Print(figname);
      foutposdz<<striptofw<<"\t"
	       <<maximum<<"\t"
	       <<fun_gaus->GetParameter(1)<<"\t"
	       <<fun_gaus->GetParError(1)<<"\t"
	       <<fun_gaus->GetParameter(2)<<"\t"
	       <<fun_gaus->GetParError(2)<<endl;
    }

  TH2F *hh_new_negdz = (TH2F *)fnew->Get("hh_neg_strip_tofwdz");
  ofstream foutnegdz("residual/res_strip_negdz_minusminus.dat");
  for(int i=0; i<512; i++)
    {
      int striptofw = i;
      hh_new_negdz->ProjectionY("h_new_negdz",i+1,i+1);
      float maximum = h_new_negdz->GetBinCenter(h_new_negdz->GetMaximumBin());    
      h_new_negdz->Fit("fun_gaus","","",maximum-2,maximum+2);
      sprintf(figname,"residual/figs/res_strip_negdz_%d_minusminus.gif",i);
      c1->Print(figname);
      foutnegdz<<striptofw<<"\t"
	       <<maximum<<"\t"
	       <<fun_gaus->GetParameter(1)<<"\t"
	       <<fun_gaus->GetParError(1)<<"\t"
	       <<fun_gaus->GetParameter(2)<<"\t"
	       <<fun_gaus->GetParError(2)<<endl;
    }

  // ---

  TH2F *hh_new_posdphi = (TH2F *)fnew->Get("hh_pos_strip_tofwdphi");
  ofstream foutposdphi("residual/res_strip_posdphi_minusminus.dat");
  for(int i=0; i<512; i++)
    {
      int striptofw = i;
      hh_new_posdphi->ProjectionY("h_new_posdphi",i+1,i+1);
      float maximum = h_new_posdphi->GetBinCenter(h_new_posdphi->GetMaximumBin());    
      h_new_posdphi->Fit("fun_gaus","","",maximum-0.003,maximum+0.003);
      sprintf(figname,"residual/figs/res_strip_posdphi_%d_minusminus.gif",i);
      c1->Print(figname);
      foutposdphi<<striptofw<<"\t"
		 <<maximum<<"\t"
		 <<fun_gaus->GetParameter(1)<<"\t"
		 <<fun_gaus->GetParError(1)<<"\t"
		 <<fun_gaus->GetParameter(2)<<"\t"
		 <<fun_gaus->GetParError(2)<<endl;
    }

  TH2F *hh_new_negdphi = (TH2F *)fnew->Get("hh_neg_strip_tofwdphi");
  ofstream foutnegdphi("residual/res_strip_negdphi_minusminus.dat");
  for(int i=0; i<512; i++)
    {
      int striptofw = i;
      hh_new_negdphi->ProjectionY("h_new_negdphi",i+1,i+1);
      float maximum = h_new_negdphi->GetBinCenter(h_new_negdphi->GetMaximumBin());    
      h_new_negdphi->Fit("fun_gaus","","",maximum-0.003,maximum+0.003);
      sprintf(figname,"residual/figs/res_strip_negdphi_%d_minusminus.gif",i);
      c1->Print(figname);
      foutnegdphi<<striptofw<<"\t"
		 <<maximum<<"\t"
		 <<fun_gaus->GetParameter(1)<<"\t"
		 <<fun_gaus->GetParError(1)<<"\t"
		 <<fun_gaus->GetParameter(2)<<"\t"
		 <<fun_gaus->GetParError(2)<<endl;
    }



}

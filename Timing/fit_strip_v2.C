void fit_strip_v2()
{

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  TFile *f = TFile::Open("outsum.root");

  TH2F *hh = (TH2F *)f->Get("deltatstriptofwdis");

  TF1 *fun_gaus = new TF1("fun_gaus","gaus",-2,2);
  //fun_gaus->SetLineColor(kRed);

  ofstream foutgaus("striptofw/striptofw_gaus.dat");

  TCanvas *c1 = new TCanvas();

  char figname[70];
  for(int i=0; i<512; i++)
    {
      int striptofw = i;
      hh->ProjectionY("h",i+1,i+1);
      float maximum = h->GetBinCenter(h->GetMaximumBin());    
      h->Fit("fun_gaus","","",maximum-0.2,maximum+0.2);
      sprintf(figname,"striptofw/figs/striptofw_gaus_%d.gif",i);
      c1->Print(figname);
      foutgaus<<striptofw<<"\t"
	      <<maximum<<"\t"
	      <<fun_gaus->GetParameter(1)<<"\t"
	      <<fun_gaus->GetParError(1)<<"\t"
	      <<fun_gaus->GetParameter(2)<<"\t"
	      <<fun_gaus->GetParError(2)<<endl;
    }


}

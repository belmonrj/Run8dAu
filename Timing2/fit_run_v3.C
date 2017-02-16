void fit_run_v3()
{

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  TFile *f = TFile::Open("outsum.root");

  TH2F *hh = (TH2F *)f->Get("deltatrundis");

  TF1 *fun_gaus = new TF1("fun_gaus","gaus",-2,2);
  //fun_gaus->SetLineColor(kRed);

  ofstream foutgaus("run/run_gaus.dat");

  TCanvas *c1 = new TCanvas();

  char figname[70];
  for(int i=0; i<848; i++)
    {
      int run = i;
      hh->ProjectionY("h",i+1,i+1);
      //h->SetAxisRange(-2,4,"X");
      float maximum = h->GetBinCenter(h->GetMaximumBin());    
      //h->Fit("fun_gaus","","",maximum-0.1,maximum+0.1);
      h->Fit("fun_gaus","","",-0.12,0.12);
      sprintf(figname,"run/figs/run_gaus_%d.gif",i);
      c1->Print(figname);
      foutgaus<<run<<"\t"
	      <<maximum<<"\t"
	      <<fun_gaus->GetParameter(1)<<"\t"
	      <<fun_gaus->GetParError(1)<<"\t"
	      <<fun_gaus->GetParameter(2)<<"\t"
	      <<fun_gaus->GetParError(2)<<endl;
    }


}

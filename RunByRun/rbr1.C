void rbr1()
{

  TCanvas *c1 = new TCanvas("c1","",800,600);

  TFile *fpp = TFile::Open("outnew_pp.root");
  TFile *fmm = TFile::Open("outnew_mm.root");

  TH1F *hnumpospp = (TH1F *)fpp->Get("h_numpos");
  TH1F *hnumnegpp = (TH1F *)fpp->Get("h_numneg");
  TH1F *hnevepp = (TH1F *)fpp->Get("h_neve");
  TH1F *hnumposmm = (TH1F *)fmm->Get("h_numpos");
  TH1F *hnumnegmm = (TH1F *)fmm->Get("h_numneg");
  TH1F *hnevemm = (TH1F *)fmm->Get("h_neve");

  hnevepp->Sumw2();
  hnumpospp->Sumw2();
  hnumnegpp->Sumw2();
  hnevemm->Sumw2();
  hnumposmm->Sumw2();
  hnumnegmm->Sumw2();

  hnumpospp->Add(hnumposmm);
  hnumnegpp->Add(hnumnegmm);
  hnevepp->Add(hnevemm);

  TH1F *hpos = (TH1F *)hnumpospp->Clone();
  TH1F *hneg = (TH1F *)hnumnegpp->Clone();

  hnumpospp->Add(hnumnegpp);
  hnumpospp->Divide(hnevepp);


  // draw

  TH2F *hhhh = new TH2F("hhhh","",1,0,850,1,0,1.5);
  hhhh->GetXaxis()->SetTitle("run index");
  hhhh->GetYaxis()->SetTitle("mean multiplicity");
  hhhh->GetXaxis()->CenterTitle();
  hhhh->GetYaxis()->CenterTitle();
  hhhh->Draw();

  hnumpospp->SetLineColor(kWhite);
  hnumpospp->SetMarkerColor(kBlack);
  hnumpospp->SetMarkerStyle(kFullCircle);
  hnumpospp->Draw("same");

  c1->Print("meanmult.gif");
  c1->Print("meanmult.png");
  c1->Print("meanmult.eps");

  hneg->Divide(hpos);
  hneg->SetLineColor(kWhite);
  hneg->SetMarkerColor(kBlack);
  hneg->SetMarkerStyle(kFullCircle);
  hneg->Draw("same");

  hhhh->GetYaxis()->SetTitle("charge ratio");
  hhhh->Draw();
  hneg->Draw("same");

  c1->Print("chargera.gif");
  c1->Print("chargera.png");
  c1->Print("chargera.eps");


  //TH1F *hcharge = new TH1F("hcharge","",200,0,2);
  TH1F *hcharge = new TH1F("hcharge","",100,0.6,1.2);
  for(int i=0; i<848; i++)
    {
      float charge = hneg->GetBinContent(i+1);
      hcharge->Fill(charge);
    }
  //hcharge->Fit("gaus","","",0.6,1.2);
  //hcharge->Fit("gaus","","",0.9,1.0);

  float max = hcharge->GetBinContent(hcharge->GetMaximumBin());
  float height = max*1.1;
  float xmin = 0.9;
  float xmax = 1.0;
  int bmin = hcharge->FindBin(xmin);
  int bmax = hcharge->FindBin(xmax);
  float numer = hcharge->Integral(bmin,bmax);
  float denom = hcharge->Integral(0,101);
  float ratio = numer/denom;
  hcharge->SetMaximum(height);
  hcharge->Draw();
  TLine *line1 = new TLine(xmin,0.0,xmin,height);
  TLine *line2 = new TLine(xmax,0.0,xmax,height);
  line1->Draw();
  line2->Draw();
  float x1 = 0.65;
  float x2 = 0.85;
  float y1 = 0.75*height;
  float y2 = 0.85*height;
  TPaveText *tpt = new TPaveText(x1,y1,x2,y2);
  tpt->SetFillColor(kWhite);
  tpt->SetBorderSize(0);
  char text[100];
  //sprintf(text,"ratio of runs passing cut is %f",ratio);
  //sprintf(text,"percentage passing cut is %2.1f %%",ratio*100);
  sprintf(text,"%2.1f%% of runs pass cut",ratio*100);
  tpt->AddText(text);
  tpt->Draw();

  c1->Print("cut_charge.gif");
  c1->Print("cut_charge.png");
  c1->Print("cut_charge.eps");




  //TH1F *hmeanmult = new TH1F("hmeanmult","",200,0,2);
  TH1F *hmeanmult = new TH1F("hmeanmult","",100,1.0,1.2);
  for(int i=0; i<848; i++)
    {
      float meanmult = hnumpospp->GetBinContent(i+1);
      hmeanmult->Fill(meanmult);
    }
  //hmeanmult->Fit("gaus","","",0.6,1.2);
  //hmeanmult->Fit("gaus","","",0.9,1.0);

  max = hmeanmult->GetBinContent(hmeanmult->GetMaximumBin());
  height = max*1.1;
  xmin = 1.100;
  xmax = 1.125;
  bmin = hmeanmult->FindBin(xmin);
  bmax = hmeanmult->FindBin(xmax);
  numer = hmeanmult->Integral(bmin,bmax);
  denom = hmeanmult->Integral(0,101);
  ratio = numer/denom;
  hmeanmult->SetMaximum(height);
  hmeanmult->Draw();
  line1 = new TLine(xmin,0.0,xmin,height);
  line2 = new TLine(xmax,0.0,xmax,height);
  line1->Draw();
  line2->Draw();
  x1 = 1.01;
  x2 = 1.09;
  y1 = 0.75*height;
  y2 = 0.85*height;
  tpt = new TPaveText(x1,y1,x2,y2);
  tpt->SetFillColor(kWhite);
  tpt->SetBorderSize(0);
  //sprintf(text,"ratio of runs passing cut is %f",ratio);
  //sprintf(text,"percentage passing cut is %2.1f %%",ratio*100);
  sprintf(text,"%2.1f%% of runs pass cut",ratio*100);
  tpt->AddText(text);
  tpt->Draw();

  c1->Print("cut_meanmult.gif");
  c1->Print("cut_meanmult.png");
  c1->Print("cut_meanmult.eps");



}

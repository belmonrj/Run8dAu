void plotm2_SRT_78()
{

  TF1 *shenglisigmapi = new TF1("shenglisigmapi","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *shenglisigmaka = new TF1("shenglisigmaka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.3,4.0);
  TF1 *shenglisigmapr = new TF1("shenglisigmapr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,4.0);

  shenglisigmapr->SetParameter(0,-6.19317e-03);  
  shenglisigmapr->SetParameter(1, 9.01921e-03);
  shenglisigmapr->SetParameter(2, 6.82347e-04);
  shenglisigmapr->SetParameter(3, 6.07866e-02);
  shenglisigmapr->SetParameter(4,-1.32903e-01);

  //shenglisigmapr->SetLineStyle(2);
  shenglisigmapr->SetLineColor(kBlue);


  TF1 *realsigmapi = new TF1("realsigmapi","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *realsigmaka = new TF1("realsigmaka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.3,4.0);
  TF1 *realsigmapr = new TF1("realsigmapr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,4.0);

  realsigmapr->SetParameter(0,-6.19317e-03);  
  realsigmapr->SetParameter(1, 9.01921e-03);
  realsigmapr->SetParameter(2, 6.82347e-04);
  realsigmapr->SetParameter(3, 6.07866e-02);
  realsigmapr->SetParameter(4,-1.32903e-01);

  TF1 *simsigmapi = new TF1("simsigmapi","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *simsigmaka = new TF1("simsigmaka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.3,4.0);
  TF1 *simsigmapr = new TF1("simsigmapr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,4.0);


  simsigmapr->SetParameter(0, 6.83419e-02);  
  simsigmapr->SetParameter(1,-4.58652e-02);
  simsigmapr->SetParameter(2, 1.26251e-02);
  simsigmapr->SetParameter(3, 6.65539e-02);
  simsigmapr->SetParameter(4,-1.89322e-01);

  simsigmapi->SetLineColor(kRed);
  //simsigmapi->SetLineStyle(2);
  simsigmaka->SetLineColor(kRed);
  //simsigmaka->SetLineStyle(2);
  simsigmapr->SetLineColor(kRed);
  //simsigmapr->SetLineStyle(2);






  TF1 *pdgmasspi = new TF1("pdgmasspi","pol0",0.0,4.2);
  pdgmasspi->SetParameter(0,0.01948);
  TF1 *pdgmasska = new TF1("pdgmasska","pol0",0.0,4.2);
  pdgmasska->SetParameter(0,0.24332);
  TF1 *pdgmasspr = new TF1("pdgmasspr","pol0",0.0,4.2);
  pdgmasspr->SetParameter(0,0.88035);

  pdgmasspi->SetLineWidth(0);
  pdgmasska->SetLineWidth(0);
  pdgmasspr->SetLineWidth(0);

  //funpion->FixParameter(1,0.01948);
  //funkaon->FixParameter(1,0.24332);
  //pr0.88035

  gStyle->SetOptFit(0);

  //TCanvas *c1 = new TCanvas("c1","",800,600);
  TCanvas *c1 = new TCanvas();
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);



  float pt[40], ept[40], mean[40], emean[40], sigma[40], esigma[40];


  TF1 *funmean = new TF1("funmean","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *funmeanpi = new TF1("funmeanpi","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *funmeanka = new TF1("funmeanka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *funmeanpr = new TF1("funmeanpr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,4.0);
  //TF1 *funmeanpr = new TF1("funmeanpr","[0]+[1]/x+[2]/x/x+[3]*sqrt(x)",0.4,4.0);

  TF1 *funsigma = new TF1("funsigma","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *funsigmapi = new TF1("funsigmapi","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *funsigmaka = new TF1("funsigmaka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *funsigmapr = new TF1("funsigmapr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,4.0);

  TF1 *funline = new TF1("funline","pol0",0.2,4.0);
  TF1 *funlinepi = new TF1("funlinepi","pol0",0.2,4.0);
  TF1 *funlineka = new TF1("funlineka","pol0",0.3,4.0);
  TF1 *funlinepr = new TF1("funlinepr","pol0",0.5,4.0);









  // --- proton

  ifstream finprotonreal("m2pT_both_proton_par.txt");
  for(int i=0; i<40; i++)
    {
      finprotonreal>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<5)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_protonrealmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_protonrealmean->SetMarkerColor(kBlack);
  tge_protonrealmean->SetMarkerStyle(21);

  TGraphErrors *tge_protonrealsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_protonrealsigma->SetMarkerColor(kBlack);
  tge_protonrealsigma->SetMarkerStyle(21);

  ifstream finprotonreal("m2pT_both_proton_par.txt");
  for(int i=0; i<40; i++)
    {
      finprotonreal>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<5)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_protonrealmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_protonrealmean->SetMarkerColor(kBlack);
  tge_protonrealmean->SetMarkerStyle(21);

  TGraphErrors *tge_protonrealsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_protonrealsigma->SetMarkerColor(kBlack);
  tge_protonrealsigma->SetMarkerStyle(21);



  ifstream finprotonsim("m2pT_both_proton_par_sim.txt");
  for(int i=0; i<40; i++)
    {
      finprotonsim>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<5)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_protonsimmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_protonsimmean->SetMarkerColor(kRed);
  tge_protonsimmean->SetMarkerStyle(25);

  TGraphErrors *tge_protonsimsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_protonsimsigma->SetMarkerColor(kRed);
  tge_protonsimsigma->SetMarkerStyle(25);



  // ------------------------------------------------------------------------------ //

  ifstream finprotonreal2("m2pT_both_proton_par_run7.txt");                         //
  for(int i=0; i<40; i++)
    {
      finprotonreal2>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];                 //
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<5)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}                     //
    }

  TGraphErrors *tge_protonrealmeanrun7 = new TGraphErrors(40,pt,mean,ept,emean);    //
  tge_protonrealmeanrun7->SetMarkerColor(kRed);
  tge_protonrealmeanrun7->SetMarkerStyle(21);

  TGraphErrors *tge_protonrealsigmarun7 = new TGraphErrors(40,pt,sigma,ept,esigma); //
  tge_protonrealsigmarun7->SetMarkerColor(kRed);
  tge_protonrealsigmarun7->SetMarkerStyle(21);

  // ------------------------------------------------------------------------------ //




  // now proton both

  TMultiGraph *tmg1_mean = new TMultiGraph();
  tmg1_mean->Add(tge_protonrealmean);
  //tmg1_mean->Add(tge_protonsimmean);
  tmg1_mean->Draw("ap");
  //funmeanpi->Draw("same");
  pdgmasspr->Draw("same");
  tmg1_mean->SetMinimum(0.6);
  tmg1_mean->SetMaximum(1.1);
  tmg1_mean->GetXaxis()->SetLimits(0.0,4.2);
  tmg1_mean->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg1_mean->GetXaxis()->CenterTitle();
  tmg1_mean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tmg1_mean->GetYaxis()->CenterTitle();

  TLegend *leg1mean = new TLegend(0.18,0.68,0.38,0.88);
  leg1mean->SetFillColor(kWhite);
  leg1mean->SetBorderSize(0);
  leg1mean->AddEntry(tge_protonrealmean,"real","p");
  //leg1mean->AddEntry(tge_protonsimmean,"sim","p");
  //leg1mean->AddEntry(funmeanpi,"fit","l");
  leg1mean->AddEntry(pdgmasspi,"PDG","l");
  leg1mean->Draw();

  //c1->Print("m2pT_protonSRT_mean_run7.gif");
  //c1->Print("m2pT_protonSRT_mean_run7.eps");

  c1->Clear();

  tge_protonrealsigma->SetMarkerStyle(25);

  TMultiGraph *tmg1_sigma = new TMultiGraph();
  tmg1_sigma->Add(tge_protonrealsigma);
  //tmg1_sigma->Add(tge_protonrealsigmarun7);
  tmg1_sigma->Add(tge_protonsimsigma);
  tmg1_sigma->Draw("ap");
  tge_protonrealsigma->Fit(realsigmapr,"","",0.5,3.5);
  realsigmapr->Draw("same");
  simsigmapr->Draw("same");
  shenglisigmapr->Draw("same");
  tmg1_sigma->SetMinimum(0.0);
  tmg1_sigma->SetMaximum(0.3);
  tmg1_sigma->GetXaxis()->SetLimits(0.0,4.2);
  tmg1_sigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg1_sigma->GetXaxis()->CenterTitle();
  tmg1_sigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tmg1_sigma->GetYaxis()->CenterTitle();

  TLegend *leg1sigma = new TLegend(0.18,0.62,0.38,0.88);
  leg1sigma->SetFillColor(kWhite);
  leg1sigma->SetBorderSize(0);
  leg1sigma->AddEntry(tge_protonrealsigma,"real Run8","p");
  leg1sigma->AddEntry(realsigmapi,"real Run8","l");
  leg1sigma->AddEntry(tge_protonsimsigma,"sim Run8","p");
  leg1sigma->AddEntry(simsigmapr,"sim Run8","l");
  //leg1sigma->AddEntry(tge_protonrealsigmarun7,"real Run7","p");
  leg1sigma->AddEntry(shenglisigmapr,"sim Run7","l");
  leg1sigma->Draw();

  c1->Print("m2pT_protonSRT_sigma_run7.gif");
  c1->Print("m2pT_protonSRT_sigma_run7.eps");

  c1->Clear();






}






//REAK
float isPionLow(float mom, float m2tofw)
{
float x = mom;
float a0 = 0.0237135;
float a1 = -0.00142172;
float a2 = 0.000159483;
float a3 = -0.00327739;
float a4 = 0.00678504;
float mean = a0+a1/x+a2/x/x+a3*exp(sqrt(x))+a4*sqrt(x);
float b0 = -0.110849  ;
float b1 =  0.0327198 ;
float b2 = -0.00363226;
float b3 = -0.0113338 ;
float b4 =  0.124956  ;
float sigma = b0+b1/x+b2/x/x+b3*exp(sqrt(x))+b4*sqrt(x);
return (m2tofw - mean)/sigma;
}



//SIM
float isPionLow(float mom, float m2tofw)
{
float x = mom;
float a0 = 0.0184867;
float a1 = 0.00104217;
float a2 = -0.000155555;
float a3 = -0.00489161;
float a4 = 0.0126445;
float mean = a0+a1/x+a2/x/x+a3*exp(sqrt(x))+a4*sqrt(x);
float b0 = -0.0241301   ;
float b1 = -0.0011061   ;
float b2 =  1.77837e-06 ;
float b3 =  0.0551144   ;
float b4 = -0.114053    ;
float sigma = b0+b1/x+b2/x/x+b3*exp(sqrt(x))+b4*sqrt(x);
return (m2tofw - mean)/sigma;
}






float pion()
{
  //mean
  a0    =       2.54773e-02;
  a1    =      -1.85488e-03;
  a2    =       1.86134e-04;
  a3    =      -3.04155e-04;
  a4    =      -4.27865e-03;
  //sigma
  b0    =      -1.42202e-02;
  b1    =      -5.10216e-03;
  b2    =       6.10146e-04;
  b3    =       5.78670e-02;
  b4    =      -1.28145e-01;
}


float kaon()
{
  //mean
  a0    =       2.41163e-01;
  a1    =      -2.05724e-04;
  a2    =       1.35541e-03;
  a3    =      -6.44528e-03;
  a4    =       1.90780e-02;
  //sigma
  b0    =       8.59413e-03;
  b1    =      -1.58493e-02;
  b2    =       2.71696e-03;
  b3    =       6.33548e-02;
  b4    =      -1.54920e-01;
}



float proton()
{
  //mean
  a0    =       8.29367e-01;
  a1    =       1.75405e-02;
  a2    =       6.97152e-03;
  a3    =      -1.01457e-02;
  a4    =       5.87214e-02;
  //sigma
  b0    =       6.83419e-02;
  b1    =      -4.58652e-02;
  b2    =       1.26251e-02;
  b3    =       6.65539e-02;
  b4    =      -1.89322e-01;
}

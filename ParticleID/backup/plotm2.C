void plotm2()
{

  TF1 *shenglisigmapi = new TF1("shenglisigmapi","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *shenglisigmaka = new TF1("shenglisigmaka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.3,4.0);
  TF1 *shenglisigmapr = new TF1("shenglisigmapr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,4.0);

  shenglisigmapi->SetParameter(0, 1.03401e-02);
  shenglisigmapi->SetParameter(1,-1.76120e-02);
  shenglisigmapi->SetParameter(2, 2.91334e-03);
  shenglisigmapi->SetParameter(3, 6.48013e-02);
  shenglisigmapi->SetParameter(4,-1.60995e-01);
  
  shenglisigmaka->SetParameter(0, 1.75872e-02);  
  shenglisigmaka->SetParameter(1,-2.08889e-02);
  shenglisigmaka->SetParameter(2, 4.16566e-03);
  shenglisigmaka->SetParameter(3, 6.34606e-02); 
  shenglisigmaka->SetParameter(4,-1.58898e-01); 

  shenglisigmapr->SetParameter(0,-6.19317e-03);  
  shenglisigmapr->SetParameter(1, 9.01921e-03);
  shenglisigmapr->SetParameter(2, 6.82347e-04);
  shenglisigmapr->SetParameter(3, 6.07866e-02);
  shenglisigmapr->SetParameter(4,-1.32903e-01);

  shenglisigmapi->SetLineStyle(2);
  shenglisigmaka->SetLineStyle(2);
  shenglisigmapr->SetLineStyle(2);

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
  TF1 *funmeanka = new TF1("funmeanka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.3,4.0);
  TF1 *funmeanpr = new TF1("funmeanpr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,4.0);
  //TF1 *funmeanpr = new TF1("funmeanpr","[0]+[1]/x+[2]/x/x+[3]*sqrt(x)",0.4,4.0);

  TF1 *funsigma = new TF1("funsigma","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *funsigmapi = new TF1("funsigmapi","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,3.0);
  TF1 *funsigmaka = new TF1("funsigmaka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.3,3.0);
  TF1 *funsigmapr = new TF1("funsigmapr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,4.0);

  TF1 *funline = new TF1("funline","pol0",0.2,4.0);
  TF1 *funlinepi = new TF1("funlinepi","pol0",0.2,4.0);
  TF1 *funlineka = new TF1("funlineka","pol0",0.3,4.0);
  TF1 *funlinepr = new TF1("funlinepr","pol0",0.5,4.0);




  // ----------------------------
  // --- now do both charges together

  // --- pion

  ifstream finbothpion("m2pT_both_pion_par.txt");
  for(int i=0; i<40; i++)
    {
      finbothpion>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      //if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      //if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<2)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_bothpionmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_bothpionmean->SetMarkerColor(kBlue);
  tge_bothpionmean->SetMarkerStyle(20);
  tge_bothpionmean->Draw("ap");
  //tge_bothpionmean->Fit(funmeanpi,"R");
  tge_bothpionmean->SetMinimum(0.0);
  tge_bothpionmean->SetMaximum(0.025);
  tge_bothpionmean->GetXaxis()->SetLimits(0.0,3.2);
  tge_bothpionmean->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_bothpionmean->GetXaxis()->CenterTitle();
  tge_bothpionmean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tge_bothpionmean->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_pion_mean.png");
  c1->Print("m2pT_both_pion_mean.gif");
  c1->Print("m2pT_both_pion_mean.eps");

  TGraphErrors *tge_bothpionsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_bothpionsigma->SetMarkerColor(kBlue);
  tge_bothpionsigma->SetMarkerStyle(20);
  tge_bothpionsigma->Draw("ap");
  //tge_bothpionsigma->Fit(funsigmapi,"R");
  tge_bothpionsigma->Fit(funsigmapi,"","",0.2,2.7);
  tge_bothpionsigma->SetMinimum(0.0);
  tge_bothpionsigma->SetMaximum(0.2);
  tge_bothpionsigma->GetXaxis()->SetLimits(0.0,3.2);
  tge_bothpionsigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_bothpionsigma->GetXaxis()->CenterTitle();
  tge_bothpionsigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tge_bothpionsigma->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_pion_sigma.png");
  c1->Print("m2pT_both_pion_sigma.gif");
  c1->Print("m2pT_both_pion_sigma.eps");



  // --- kaon

  ifstream finbothkaon("m2pT_both_kaon_par.txt");
  for(int i=0; i<40; i++)
    {
      finbothkaon>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      //if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      //if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<3)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_bothkaonmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_bothkaonmean->SetMarkerColor(kGreen+2);
  tge_bothkaonmean->SetMarkerStyle(22);
  tge_bothkaonmean->Draw("ap");
  //tge_bothkaonmean->Fit(funlineka,"R");
  //tge_bothkaonmean->Fit(funlineka,"R");
  tge_bothkaonmean->SetMinimum(0.1);
  tge_bothkaonmean->SetMaximum(0.3);
  tge_bothkaonmean->GetXaxis()->SetLimits(0.0,3.2);
  tge_bothkaonmean->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_bothkaonmean->GetXaxis()->CenterTitle();
  tge_bothkaonmean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tge_bothkaonmean->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_kaon_mean.png");
  c1->Print("m2pT_both_kaon_mean.gif");
  c1->Print("m2pT_both_kaon_mean.eps");

  TGraphErrors *tge_bothkaonsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_bothkaonsigma->SetMarkerColor(kGreen+2);
  tge_bothkaonsigma->SetMarkerStyle(22);
  tge_bothkaonsigma->Draw("ap");
  //tge_bothkaonsigma->Fit(funsigmaka,"","",0.3,3.8);
  tge_bothkaonsigma->Fit(funsigmaka,"","",0.3,2.7);
  tge_bothkaonsigma->SetMinimum(0.0);
  tge_bothkaonsigma->SetMaximum(0.2);
  tge_bothkaonsigma->GetXaxis()->SetLimits(0.0,3.2);
  tge_bothkaonsigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_bothkaonsigma->GetXaxis()->CenterTitle();
  tge_bothkaonsigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tge_bothkaonsigma->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_kaon_sigma.png");
  c1->Print("m2pT_both_kaon_sigma.gif");
  c1->Print("m2pT_both_kaon_sigma.eps");


  // --- proton

  ifstream finbothproton("m2pT_both_proton_par.txt");
  for(int i=0; i<40; i++)
    {
      finbothproton>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      //if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      //if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<5)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_bothprotonmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_bothprotonmean->SetMarkerColor(kRed);
  tge_bothprotonmean->SetMarkerStyle(21);
  tge_bothprotonmean->Draw("ap");
  //tge_bothprotonmean->Fit(funmeanpr,"R");
  tge_bothprotonmean->SetMinimum(0.8);
  tge_bothprotonmean->SetMaximum(1.0);
  tge_bothprotonmean->GetXaxis()->SetLimits(0.0,4.2);
  tge_bothprotonmean->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_bothprotonmean->GetXaxis()->CenterTitle();
  tge_bothprotonmean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tge_bothprotonmean->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_proton_mean.png");
  c1->Print("m2pT_both_proton_mean.gif");
  c1->Print("m2pT_both_proton_mean.eps");

  TGraphErrors *tge_bothprotonsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_bothprotonsigma->SetMarkerColor(kRed);
  tge_bothprotonsigma->SetMarkerStyle(21);
  tge_bothprotonsigma->Draw("ap");
  tge_bothprotonsigma->Fit(funsigmapr,"R");
  //tge_bothprotonsigma->Fit(funsigma,"R");
  //tge_bothprotonsigma->Fit(funsigma,"","",0.3,4.0);
  //tge_bothprotonsigma->Fit(funsigma,"","",0.4,3.0);
  tge_bothprotonsigma->Fit(funsigmapr,"","",0.5,3.5);
  tge_bothprotonsigma->SetMinimum(0.0);
  tge_bothprotonsigma->SetMaximum(0.3);
  tge_bothprotonsigma->GetXaxis()->SetLimits(0.0,4.2);
  tge_bothprotonsigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_bothprotonsigma->GetXaxis()->CenterTitle();
  tge_bothprotonsigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tge_bothprotonsigma->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_proton_sigma.png");
  c1->Print("m2pT_both_proton_sigma.gif");
  c1->Print("m2pT_both_proton_sigma.eps");









  // --- pion

  ifstream finpospion("m2pT_pos_pion_par.txt");
  for(int i=0; i<40; i++)
    {
      finpospion>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      //if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      //if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<2)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_pospionmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_pospionmean->SetMarkerColor(kBlue);
  tge_pospionmean->SetMarkerStyle(21);

  TGraphErrors *tge_pospionsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_pospionsigma->SetMarkerColor(kBlue);
  tge_pospionsigma->SetMarkerStyle(21);

  ifstream finnegpion("m2pT_neg_pion_par.txt");
  for(int i=0; i<40; i++)
    {
      finnegpion>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      //if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      //if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<2)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_negpionmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_negpionmean->SetMarkerColor(kBlue);
  //tge_negpionmean->SetMarkerStyle(24);
  //tge_negpionmean->SetMarkerStyle(4);
  //tge_negpionmean->SetMarkerStyle(kOpenCircle);  // never works correctly for bitmaps
  tge_negpionmean->SetMarkerStyle(25);

  TGraphErrors *tge_negpionsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_negpionsigma->SetMarkerColor(kBlue);
  //tge_negpionsigma->SetMarkerStyle(24);
  //tge_negpionsigma->SetMarkerStyle(4);
  //tge_negpionsigma->SetMarkerStyle(kOpenCircle);
  tge_negpionsigma->SetMarkerStyle(25);



  // --- kaon

  ifstream finposkaon("m2pT_pos_kaon_par.txt");
  for(int i=0; i<40; i++)
    {
      finposkaon>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      //if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      //if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<3)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_poskaonmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_poskaonmean->SetMarkerColor(kGreen+2);
  tge_poskaonmean->SetMarkerStyle(21);

  TGraphErrors *tge_poskaonsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_poskaonsigma->SetMarkerColor(kGreen+2);
  tge_poskaonsigma->SetMarkerStyle(21);

  ifstream finnegkaon("m2pT_neg_kaon_par.txt");
  for(int i=0; i<40; i++)
    {
      finnegkaon>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      //if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      //if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<3)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_negkaonmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_negkaonmean->SetMarkerColor(kGreen+2);
  tge_negkaonmean->SetMarkerStyle(25);

  TGraphErrors *tge_negkaonsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_negkaonsigma->SetMarkerColor(kGreen+2);
  tge_negkaonsigma->SetMarkerStyle(25);



  // --- proton

  ifstream finposproton("m2pT_pos_proton_par.txt");
  for(int i=0; i<40; i++)
    {
      finposproton>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      //if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      //if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<5)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_posprotonmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_posprotonmean->SetMarkerColor(kRed);
  tge_posprotonmean->SetMarkerStyle(21);

  TGraphErrors *tge_posprotonsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_posprotonsigma->SetMarkerColor(kRed);
  tge_posprotonsigma->SetMarkerStyle(21);

  ifstream finnegproton("m2pT_neg_proton_par.txt");
  for(int i=0; i<40; i++)
    {
      finnegproton>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      //if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      //if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<5)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_negprotonmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_negprotonmean->SetMarkerColor(kRed);
  tge_negprotonmean->SetMarkerStyle(25);

  TGraphErrors *tge_negprotonsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_negprotonsigma->SetMarkerColor(kRed);
  tge_negprotonsigma->SetMarkerStyle(25);


  // ---


  // --- drawn together :)

  c1->Clear();

  TMultiGraph *tmg_mean = new TMultiGraph();
  tmg_mean->Add(tge_bothpionmean);
  tmg_mean->Add(tge_bothkaonmean);
  tmg_mean->Add(tge_bothprotonmean);
  tmg_mean->Draw("ap");
  tmg_mean->SetMinimum(-0.1);
  tmg_mean->SetMaximum(1.1);
  tmg_mean->GetXaxis()->SetLimits(0.0,4.2);
  tmg_mean->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_mean->GetXaxis()->CenterTitle();
  tmg_mean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tmg_mean->GetYaxis()->CenterTitle();

  c1->Print("m2pT_together_mean.png");
  c1->Print("m2pT_together_mean.gif");
  c1->Print("m2pT_together_mean.eps");

  c1->Clear();

  TMultiGraph *tmg_sigma = new TMultiGraph();
  tmg_sigma->Add(tge_bothpionsigma);
  tmg_sigma->Add(tge_bothkaonsigma);
  tmg_sigma->Add(tge_bothprotonsigma);
  tmg_sigma->Draw("ap");
  tmg_sigma->SetMinimum(0.0);
  tmg_sigma->SetMaximum(0.3);
  tmg_sigma->GetXaxis()->SetLimits(0.0,4.2);
  tmg_sigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_sigma->GetXaxis()->CenterTitle();
  tmg_sigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tmg_sigma->GetYaxis()->CenterTitle();

  c1->Print("m2pT_together_sigma.png");
  c1->Print("m2pT_together_sigma.gif");
  c1->Print("m2pT_together_sigma.eps");

  c1->Clear();



  // now pion both charges

  TMultiGraph *tmg1_mean = new TMultiGraph();
  tmg1_mean->Add(tge_pospionmean);
  tmg1_mean->Add(tge_negpionmean);
  tmg1_mean->Draw("ap");
  //funmeanpi->Draw("same");
  pdgmasspi->Draw("same");
  tmg1_mean->SetMinimum(-0.1);
  tmg1_mean->SetMaximum(0.1);
  tmg1_mean->GetXaxis()->SetLimits(0.0,3.2);
  tmg1_mean->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg1_mean->GetXaxis()->CenterTitle();
  tmg1_mean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tmg1_mean->GetYaxis()->CenterTitle();

  TLegend *leg1mean = new TLegend(0.18,0.68,0.38,0.88);
  leg1mean->SetFillColor(kWhite);
  leg1mean->SetBorderSize(0);
  leg1mean->AddEntry(tge_pospionmean,"#pi^{+}","p");
  leg1mean->AddEntry(tge_negpionmean,"#pi^{-}","p");
  leg1mean->AddEntry(funmeanpi,"fit","l");
  //leg1mean->AddEntry(pdgmasspi,"PDG","l");
  leg1mean->Draw();

  c1->Print("m2pT_piontogether_mean.png");
  c1->Print("m2pT_piontogether_mean.gif");
  c1->Print("m2pT_piontogether_mean.eps");

  c1->Clear();

  TMultiGraph *tmg1_sigma = new TMultiGraph();
  tmg1_sigma->Add(tge_pospionsigma);
  tmg1_sigma->Add(tge_negpionsigma);
  tmg1_sigma->Draw("ap");
  funsigmapi->Draw("same");
  //shenglisigmapi->Draw("same");
  tmg1_sigma->SetMinimum(0.0);
  tmg1_sigma->SetMaximum(0.2);
  tmg1_sigma->GetXaxis()->SetLimits(0.0,3.2);
  tmg1_sigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg1_sigma->GetXaxis()->CenterTitle();
  tmg1_sigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tmg1_sigma->GetYaxis()->CenterTitle();

  TLegend *leg1sigma = new TLegend(0.18,0.68,0.38,0.88);
  leg1sigma->SetFillColor(kWhite);
  leg1sigma->SetBorderSize(0);
  leg1sigma->AddEntry(tge_pospionsigma,"#pi^{+}","p");
  leg1sigma->AddEntry(tge_negpionsigma,"#pi^{-}","p");
  leg1sigma->AddEntry(funsigmapi,"fit","l");
  //leg1sigma->AddEntry(funsigmapi,"new","l");
  //leg1sigma->AddEntry(shenglisigmapi,"old","l");
  leg1sigma->Draw();

  c1->Print("m2pT_piontogether_sigma.png");
  c1->Print("m2pT_piontogether_sigma.gif");
  c1->Print("m2pT_piontogether_sigma.eps");

  c1->Clear();



  // now kaon both charges

  TMultiGraph *tmg2_mean = new TMultiGraph();
  tmg2_mean->Add(tge_poskaonmean);
  tmg2_mean->Add(tge_negkaonmean);
  tmg2_mean->Draw("ap");
  //funlineka->Draw("same");
  pdgmasska->Draw("same");
  tmg2_mean->SetMinimum(0.1);
  tmg2_mean->SetMaximum(0.4);
  tmg2_mean->GetXaxis()->SetLimits(0.0,3.2);
  tmg2_mean->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg2_mean->GetXaxis()->CenterTitle();
  tmg2_mean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tmg2_mean->GetYaxis()->CenterTitle();

  TLegend *leg2mean = new TLegend(0.18,0.68,0.38,0.88);
  leg2mean->SetFillColor(kWhite);
  leg2mean->SetBorderSize(0);
  leg2mean->AddEntry(tge_poskaonmean,"K^{+}","p");
  leg2mean->AddEntry(tge_negkaonmean,"K^{-}","p");
  //leg2mean->AddEntry(funmeanka,"fit","l");
  leg2mean->AddEntry(pdgmasska,"PDG","l");
  leg2mean->Draw();

  c1->Print("m2pT_kaontogether_mean.png");
  c1->Print("m2pT_kaontogether_mean.gif");
  c1->Print("m2pT_kaontogether_mean.eps");

  c1->Clear();

  TMultiGraph *tmg2_sigma = new TMultiGraph();
  tmg2_sigma->Add(tge_poskaonsigma);
  tmg2_sigma->Add(tge_negkaonsigma);
  tmg2_sigma->Draw("ap");
  funsigmaka->Draw("same");
  //shenglisigmaka->Draw("same");
  tmg2_sigma->SetMinimum(0.0);
  tmg2_sigma->SetMaximum(0.2);
  tmg2_sigma->GetXaxis()->SetLimits(0.0,3.2);
  tmg2_sigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg2_sigma->GetXaxis()->CenterTitle();
  tmg2_sigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tmg2_sigma->GetYaxis()->CenterTitle();

  TLegend *leg2sigma = new TLegend(0.18,0.68,0.38,0.88);
  leg2sigma->SetFillColor(kWhite);
  leg2sigma->SetBorderSize(0);
  leg2sigma->AddEntry(tge_poskaonsigma,"K^{+}","p");
  leg2sigma->AddEntry(tge_negkaonsigma,"K^{-}","p");
  leg2sigma->AddEntry(funsigmaka,"fit","l");
  //leg2sigma->AddEntry(funsigmaka,"new","l");
  //leg2sigma->AddEntry(shenglisigmaka,"old","l");
  leg2sigma->Draw();

  c1->Print("m2pT_kaontogether_sigma.png");
  c1->Print("m2pT_kaontogether_sigma.gif");
  c1->Print("m2pT_kaontogether_sigma.eps");



  // now proton both charges

  c1->Clear();

  TMultiGraph *tmg3_mean = new TMultiGraph();
  tmg3_mean->Add(tge_posprotonmean);
  tmg3_mean->Add(tge_negprotonmean);
  tmg3_mean->Draw("ap");
  funmeanpr->Draw("same");
  pdgmasspr->Draw("same");
  tmg3_mean->SetMinimum(0.6);
  tmg3_mean->SetMaximum(1.2);
  tmg3_mean->GetXaxis()->SetLimits(0.0,4.2);
  tmg3_mean->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg3_mean->GetXaxis()->CenterTitle();
  tmg3_mean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tmg3_mean->GetYaxis()->CenterTitle();

  TLegend *leg3mean = new TLegend(0.18,0.68,0.38,0.88);
  leg3mean->SetFillColor(kWhite);
  leg3mean->SetBorderSize(0);
  leg3mean->AddEntry(tge_posprotonmean,"p","p");
  leg3mean->AddEntry(tge_negprotonmean,"#bar{p}","p");
  //leg3mean->AddEntry(funmeanpr,"fit","l");
  leg3mean->AddEntry(pdgmasspr,"PDG","l");
  leg3mean->Draw();

  c1->Print("m2pT_protontogether_mean.png");
  c1->Print("m2pT_protontogether_mean.gif");
  c1->Print("m2pT_protontogether_mean.eps");

  c1->Clear();

  TMultiGraph *tmg3_sigma = new TMultiGraph();
  tmg3_sigma->Add(tge_posprotonsigma);
  tmg3_sigma->Add(tge_negprotonsigma);
  tmg3_sigma->Draw("ap");
  funsigmapr->Draw("same");
  //shenglisigmapr->Draw("same");
  tmg3_sigma->SetMinimum(0.0);
  tmg3_sigma->SetMaximum(0.3);
  tmg3_sigma->GetXaxis()->SetLimits(0.0,4.2);
  tmg3_sigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg3_sigma->GetXaxis()->CenterTitle();
  tmg3_sigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tmg3_sigma->GetYaxis()->CenterTitle();

  TLegend *leg3sigma = new TLegend(0.18,0.68,0.38,0.88);
  leg3sigma->SetFillColor(kWhite);
  leg3sigma->SetBorderSize(0);
  leg3sigma->AddEntry(tge_posprotonsigma,"p","p");
  leg3sigma->AddEntry(tge_negprotonsigma,"#bar{p}","p");
  leg3sigma->AddEntry(funsigmapr,"fit","l");
  //leg3sigma->AddEntry(funsigmapr,"new","l");
  //leg3sigma->AddEntry(shenglisigmapr,"old","l");
  leg3sigma->Draw();

  c1->Print("m2pT_protontogether_sigma.png");
  c1->Print("m2pT_protontogether_sigma.gif");
  c1->Print("m2pT_protontogether_sigma.eps");







  // ------------------------------------- //
  // --- now to tie up some loose ends --- //
  // ------------------------------------- //



  // ----------------------------------------------------------------------

  // ---  now write to file

  cout<<endl<<endl;

  cout<<"now writing output file for pion pid function pion_pid.C "<<endl;

  ofstream foutpionpid("pion_pid.C");
  foutpionpid<<"float isPionLow(float pT, float m2tofw)\n{\n"
	     <<"float x = pT;\n"
	     <<"float a0 = "<<funmeanpi->GetParameter(0)<<";\n"
	     <<"float a1 = "<<funmeanpi->GetParameter(1)<<";\n"
	     <<"float a2 = "<<funmeanpi->GetParameter(2)<<";\n"
	     <<"float a3 = "<<funmeanpi->GetParameter(3)<<";\n"
	     <<"float a4 = "<<funmeanpi->GetParameter(4)<<";\n"
	     <<"float mean = a0+a1/x+a2/x/x+a3*exp(sqrt(x))+a4*sqrt(x);\n"
	     <<"float b0 = "<<funsigmapi->GetParameter(0)<<";\n"
	     <<"float b1 = "<<funsigmapi->GetParameter(1)<<";\n"
	     <<"float b2 = "<<funsigmapi->GetParameter(2)<<";\n"
	     <<"float b3 = "<<funsigmapi->GetParameter(3)<<";\n"
	     <<"float b4 = "<<funsigmapi->GetParameter(4)<<";\n"
	     <<"float sigma = b0+b1/x+b2/x/x+b3*exp(sqrt(x))+b4*sqrt(x);\n"
	     <<"return (m2tofw - mean)/sigma;\n}\n"<<endl;

  cout<<"done writing out pion pid function"<<endl;

  // ----------------------------------------------------------------------





}



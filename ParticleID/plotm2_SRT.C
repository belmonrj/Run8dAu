void plotm2_SRT()
{

  TF1 *shenglisigmapi = new TF1("shenglisigmapi","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,5.0);
  TF1 *shenglisigmaka = new TF1("shenglisigmaka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.3,5.0);
  TF1 *shenglisigmapr = new TF1("shenglisigmapr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,5.0);

  // shenglisigmapi->SetParameter(0, 1.03401e-02);
  // shenglisigmapi->SetParameter(1,-1.76120e-02);
  // shenglisigmapi->SetParameter(2, 2.91334e-03);
  // shenglisigmapi->SetParameter(3, 6.48013e-02);
  // shenglisigmapi->SetParameter(4,-1.60995e-01);
  
  shenglisigmapi->SetParameter(0,-2.32986e-02);
  shenglisigmapi->SetParameter(1,-1.30028e-03);
  shenglisigmapi->SetParameter(2,-8.26991e-06);
  shenglisigmapi->SetParameter(3, 5.56826e-02);
  shenglisigmapi->SetParameter(4,-1.16173e-01);
  
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





  TF1 *realsigmapi = new TF1("realsigmapi","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,5.0);
  TF1 *realsigmaka = new TF1("realsigmaka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.3,5.0);
  TF1 *realsigmapr = new TF1("realsigmapr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,5.0);




  realsigmapi->SetParameter(0,-0.0432359  );
  realsigmapi->SetParameter(1, 0.00644942 );
  realsigmapi->SetParameter(2,-0.000809058);
  realsigmapi->SetParameter(3, 0.0391918  );
  realsigmapi->SetParameter(4,-0.0568094  );
  
  realsigmaka->SetParameter(0, 1.75872e-02);  
  realsigmaka->SetParameter(1,-2.08889e-02);
  realsigmaka->SetParameter(2, 4.16566e-03);
  realsigmaka->SetParameter(3, 6.34606e-02); 
  realsigmaka->SetParameter(4,-1.58898e-01); 

  realsigmapr->SetParameter(0,-6.19317e-03);  
  realsigmapr->SetParameter(1, 9.01921e-03);
  realsigmapr->SetParameter(2, 6.82347e-04);
  realsigmapr->SetParameter(3, 6.07866e-02);
  realsigmapr->SetParameter(4,-1.32903e-01);

  //realsigmapi->SetLineStyle(2);
  //realsigmaka->SetLineStyle(2);
  //realsigmapr->SetLineStyle(2);









  TF1 *simsigmapi = new TF1("simsigmapi","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,5.0);
  TF1 *simsigmaka = new TF1("simsigmaka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.3,5.0);
  TF1 *simsigmapr = new TF1("simsigmapr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,5.0);

  simsigmapi->SetParameter(0,-1.42202e-02);
  simsigmapi->SetParameter(1,-5.10216e-03);
  simsigmapi->SetParameter(2, 6.10146e-04);
  simsigmapi->SetParameter(3, 5.78670e-02);
  simsigmapi->SetParameter(4,-1.28145e-01);
  
  simsigmaka->SetParameter(0, 8.59413e-03);  
  simsigmaka->SetParameter(1,-1.58493e-02);
  simsigmaka->SetParameter(2, 2.71696e-03);
  simsigmaka->SetParameter(3, 6.33548e-02); 
  simsigmaka->SetParameter(4,-1.54920e-01); 

  simsigmapr->SetParameter(0, 6.83419e-02);  
  simsigmapr->SetParameter(1,-4.58652e-02);
  simsigmapr->SetParameter(2, 1.26251e-02);
  simsigmapr->SetParameter(3, 6.65539e-02);
  simsigmapr->SetParameter(4,-1.89322e-01);

  simsigmapi->SetLineColor(kRed);
  simsigmapi->SetLineStyle(2);
  simsigmaka->SetLineColor(kRed);
  simsigmaka->SetLineStyle(2);
  simsigmapr->SetLineColor(kRed);
  simsigmapr->SetLineStyle(2);
  //simsigmaka->SetLineStyle(2);
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



  float pt[50], ept[50], mean[50], emean[50], sigma[50], esigma[50];


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







  // --- pion

  ifstream finpionreal("m2pT_both_pion_par.txt");
  for(int i=0; i<40; i++)
    {
      finpionreal>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<2)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_pionrealmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_pionrealmean->SetMarkerColor(kBlack);
  tge_pionrealmean->SetMarkerStyle(21);

  //TGraphErrors *tge_pionrealsigma = new TGraphErrors(27,pt,sigma,ept,esigma);
  TGraphErrors *tge_pionrealsigma = new TGraphErrors(29,pt,sigma,ept,esigma);
  tge_pionrealsigma->SetMarkerColor(kBlack);
  tge_pionrealsigma->SetMarkerStyle(21);

  ifstream finpionsim("m2pT_both_pion_par_sim.txt");
  for(int i=0; i<50; i++)
    {
      finpionsim>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<2)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_pionsimmean = new TGraphErrors(50,pt,mean,ept,emean);
  tge_pionsimmean->SetMarkerColor(kRed);
  tge_pionsimmean->SetMarkerStyle(25);

  TGraphErrors *tge_pionsimsigma = new TGraphErrors(50,pt,sigma,ept,esigma);
  tge_pionsimsigma->SetMarkerColor(kRed);
  tge_pionsimsigma->SetMarkerStyle(25);





  // now pion both

  TMultiGraph *tmg1_mean = new TMultiGraph();
  tmg1_mean->Add(tge_pionrealmean);
  tmg1_mean->Add(tge_pionsimmean);
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
  leg1mean->AddEntry(tge_pionrealmean,"real","p");
  leg1mean->AddEntry(tge_pionsimmean,"sim","p");
  //leg1mean->AddEntry(funmeanpi,"fit","l");
  leg1mean->AddEntry(pdgmasspi,"PDG","l");
  leg1mean->Draw();

  c1->Print("m2pT_pionSRT_mean.gif");
  c1->Print("m2pT_pionSRT_mean.eps");

  c1->Clear();

  TMultiGraph *tmg1_sigma = new TMultiGraph();
  tmg1_sigma->Add(tge_pionrealsigma);
  //tmg1_sigma->Add(tge_pionsimsigma);
  tmg1_sigma->Draw("ap");
  //tge_pionrealsigma->Fit(realsigmapi,"R");
  //tge_pionsimsigma->Fit(simsigmapi,"R");
  tge_pionrealsigma->Fit(realsigmapi,"","",0.2,2.7);
  realsigmapi->SetLineColor(kBlack);
  realsigmapi->Draw("same");
  shenglisigmapi->Draw("same");//Run7
  //simsigmapi->Draw("same");
  tmg1_sigma->SetMinimum(0.0);
  //tmg1_sigma->SetMaximum(0.2);
  tmg1_sigma->SetMaximum(0.4); // TEMP!
  //tmg1_sigma->GetXaxis()->SetLimits(0.0,3.2);
  tmg1_sigma->GetXaxis()->SetLimits(0.0,5.0); // TEMP!
  tmg1_sigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg1_sigma->GetXaxis()->CenterTitle();
  tmg1_sigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tmg1_sigma->GetYaxis()->CenterTitle();

  TLegend *leg1sigma = new TLegend(0.18,0.68,0.38,0.88);
  leg1sigma->SetFillColor(kWhite);
  leg1sigma->SetBorderSize(0);
  leg1sigma->AddEntry(tge_pionrealsigma,"real","p");
  //leg1sigma->AddEntry(tge_pionsimsigma,"sim","p");
  leg1sigma->AddEntry(realsigmapi,"real","l");
  leg1sigma->AddEntry(shenglisigmapi,"Run7","l");
  //leg1sigma->AddEntry(simsigmapi,"sim","l");
  leg1sigma->Draw();

  c1->Print("m2pT_pionSRT_sigma.gif");
  c1->Print("m2pT_pionSRT_sigma.eps");

  c1->Clear();









  // --- kaon

  ifstream finkaonreal("m2pT_both_kaon_par.txt");
  for(int i=0; i<40; i++)
    {
      finkaonreal>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<3)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_kaonrealmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_kaonrealmean->SetMarkerColor(kBlack);
  tge_kaonrealmean->SetMarkerStyle(21);

  //TGraphErrors *tge_kaonrealsigma = new TGraphErrors(27,pt,sigma,ept,esigma);
  TGraphErrors *tge_kaonrealsigma = new TGraphErrors(29,pt,sigma,ept,esigma);
  tge_kaonrealsigma->SetMarkerColor(kBlack);
  tge_kaonrealsigma->SetMarkerStyle(21);

  ifstream finkaonsim("m2pT_both_kaon_par_sim.txt");
  for(int i=0; i<50; i++)
    {
      finkaonsim>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<3)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_kaonsimmean = new TGraphErrors(50,pt,mean,ept,emean);
  tge_kaonsimmean->SetMarkerColor(kRed);
  tge_kaonsimmean->SetMarkerStyle(25);

  TGraphErrors *tge_kaonsimsigma = new TGraphErrors(50,pt,sigma,ept,esigma);
  tge_kaonsimsigma->SetMarkerColor(kRed);
  tge_kaonsimsigma->SetMarkerStyle(25);





  // now kaon both

  TMultiGraph *tmg1_mean = new TMultiGraph();
  tmg1_mean->Add(tge_kaonrealmean);
  tmg1_mean->Add(tge_kaonsimmean);
  tmg1_mean->Draw("ap");
  //funmeanpi->Draw("same");
  pdgmasska->Draw("same");
  tmg1_mean->SetMinimum(0.1);
  tmg1_mean->SetMaximum(0.4);
  tmg1_mean->GetXaxis()->SetLimits(0.0,3.2);
  tmg1_mean->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg1_mean->GetXaxis()->CenterTitle();
  tmg1_mean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tmg1_mean->GetYaxis()->CenterTitle();

  TLegend *leg1mean = new TLegend(0.18,0.68,0.38,0.88);
  leg1mean->SetFillColor(kWhite);
  leg1mean->SetBorderSize(0);
  leg1mean->AddEntry(tge_kaonrealmean,"real","p");
  leg1mean->AddEntry(tge_kaonsimmean,"sim","p");
  //leg1mean->AddEntry(funmeanpi,"fit","l");
  leg1mean->AddEntry(pdgmasspi,"PDG","l");
  leg1mean->Draw();

  c1->Print("m2pT_kaonSRT_mean.gif");
  c1->Print("m2pT_kaonSRT_mean.eps");

  c1->Clear();

  TMultiGraph *tmg1_sigma = new TMultiGraph();
  tmg1_sigma->Add(tge_kaonrealsigma);
  //tmg1_sigma->Add(tge_kaonsimsigma);
  tmg1_sigma->Draw("ap");
  //tge_kaonrealsigma->Fit(realsigmaka,"R");
  //tge_kaonsimsigma->Fit(simsigmaka,"R");
  //tge_kaonrealsigma->Fit(realsigmaka,"","",0.3,2.7);
  //tge_kaonrealsigma->Fit(realsigmaka,"W","",0.5,2.7);
  tge_kaonrealsigma->Fit(realsigmaka,"W","",0.5,2.7); // 0.4 much worse than 0.5
  realsigmaka->SetLineColor(kBlack);
  realsigmaka->Draw("same");
  //simsigmaka->Draw("same");
  shenglisigmaka->Draw("same");
  tmg1_sigma->SetMinimum(0.0);
  //tmg1_sigma->SetMaximum(0.2);
  tmg1_sigma->SetMaximum(0.4); // TEMP!
  //tmg1_sigma->GetXaxis()->SetLimits(0.0,3.2);
  tmg1_sigma->GetXaxis()->SetLimits(0.0,5.0); // TEMP!!
  tmg1_sigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg1_sigma->GetXaxis()->CenterTitle();
  tmg1_sigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tmg1_sigma->GetYaxis()->CenterTitle();

  TLegend *leg1sigma = new TLegend(0.18,0.68,0.38,0.88);
  leg1sigma->SetFillColor(kWhite);
  leg1sigma->SetBorderSize(0);
  leg1sigma->AddEntry(tge_kaonrealsigma,"real","p");
  //leg1sigma->AddEntry(tge_kaonsimsigma,"sim","p");
  leg1sigma->AddEntry(realsigmapi,"real","l");
  leg1sigma->AddEntry(shenglisigmapi,"Run7","l");
  //leg1sigma->AddEntry(simsigmapi,"sim","l");
  leg1sigma->Draw();

  c1->Print("m2pT_kaonSRT_sigma.gif");
  c1->Print("m2pT_kaonSRT_sigma.eps");

  c1->Clear();






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

  ifstream finprotonsim("m2pT_both_proton_par_sim.txt");
  for(int i=0; i<50; i++)
    {
      finprotonsim>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.1) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.1) {sigma[i]=-9;esigma[i]=0;}
      if(i<5)  {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_protonsimmean = new TGraphErrors(50,pt,mean,ept,emean);
  tge_protonsimmean->SetMarkerColor(kRed);
  tge_protonsimmean->SetMarkerStyle(25);

  TGraphErrors *tge_protonsimsigma = new TGraphErrors(50,pt,sigma,ept,esigma);
  tge_protonsimsigma->SetMarkerColor(kRed);
  tge_protonsimsigma->SetMarkerStyle(25);





  // now proton both

  TMultiGraph *tmg1_mean = new TMultiGraph();
  tmg1_mean->Add(tge_protonrealmean);
  tmg1_mean->Add(tge_protonsimmean);
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
  leg1mean->AddEntry(tge_protonsimmean,"sim","p");
  //leg1mean->AddEntry(funmeanpi,"fit","l");
  leg1mean->AddEntry(pdgmasspi,"PDG","l");
  leg1mean->Draw();

  c1->Print("m2pT_protonSRT_mean.gif");
  c1->Print("m2pT_protonSRT_mean.eps");

  c1->Clear();

  TMultiGraph *tmg1_sigma = new TMultiGraph();
  tmg1_sigma->Add(tge_protonrealsigma);
  //tmg1_sigma->Add(tge_protonsimsigma);
  tmg1_sigma->Draw("ap");
  //tge_protonrealsigma->Fit(realsigmapr,"R");
  //tge_protonrealsigma->Fit(realsigmapr,"","",0.5,3.5);
  tge_protonrealsigma->Fit(realsigmapr,"W","",0.5,3.0);
  //tge_protonsimsigma->Fit(simsigmapr,"R");
  realsigmapr->SetLineColor(kBlack);
  realsigmapr->Draw("same");
  //simsigmapr->Draw("same");
  shenglisigmapr->Draw("same");
  tmg1_sigma->SetMinimum(0.0);
  tmg1_sigma->SetMaximum(0.4);
  //tmg1_sigma->GetXaxis()->SetLimits(0.0,4.2);
  tmg1_sigma->GetXaxis()->SetLimits(0.0,5.0); // TEMP!
  tmg1_sigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg1_sigma->GetXaxis()->CenterTitle();
  tmg1_sigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tmg1_sigma->GetYaxis()->CenterTitle();

  TLegend *leg1sigma = new TLegend(0.18,0.68,0.38,0.88);
  leg1sigma->SetFillColor(kWhite);
  leg1sigma->SetBorderSize(0);
  leg1sigma->AddEntry(tge_protonrealsigma,"real","p");
  //leg1sigma->AddEntry(tge_protonsimsigma,"sim","p");
  leg1sigma->AddEntry(realsigmapi,"real","l");
  //leg1sigma->AddEntry(simsigmapi,"sim","l");
  leg1sigma->AddEntry(shenglisigmapi,"Run7","l");
  leg1sigma->Draw();

  c1->Print("m2pT_protonSRT_sigma.gif");
  c1->Print("m2pT_protonSRT_sigma.eps");

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

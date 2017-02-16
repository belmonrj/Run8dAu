void plotm2_sim()
{

  gStyle->SetOptFit(0);

  //TCanvas *c1 = new TCanvas("c1","",800,600);
  TCanvas *c1 = new TCanvas();
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);



  float pt[40], ept[40], mean[40], emean[40], sigma[40], esigma[40];

  TF1 *funmean = new TF1("funmean","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *funsigma = new TF1("funsigma","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,4.0);
  TF1 *funline = new TF1("funline","pol0",0.2,4.0);


  TF1 *pdgmasspi = new TF1("pdgmasspi","pol0",0.0,4.2);
  pdgmasspi->SetParameter(0,0.01948);
  TF1 *pdgmasska = new TF1("pdgmasska","pol0",0.0,4.2);
  pdgmasska->SetParameter(0,0.24332);
  TF1 *pdgmasspr = new TF1("pdgmasspr","pol0",0.0,4.2);
  pdgmasspr->SetParameter(0,0.88035);

  pdgmasspi->SetLineWidth(0);
  pdgmasska->SetLineWidth(0);
  pdgmasspr->SetLineWidth(0);



  // --- pion

  ifstream finbothpion("m2pT_both_pion_par_sim.txt");
  for(int i=0; i<40; i++)
    {
      finbothpion>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.2) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.2) {sigma[i]=-9;esigma[i]=0;}
      if(i<2) {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_bothpionmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_bothpionmean->SetMarkerColor(kBlue);
  tge_bothpionmean->SetMarkerStyle(20);
  tge_bothpionmean->Draw("ap");
  pdgmasspi->Draw("same");
  tge_bothpionmean->Fit(funmean,"R");
  tge_bothpionmean->SetMinimum(-0.1);
  tge_bothpionmean->SetMaximum(0.1);
  tge_bothpionmean->GetXaxis()->SetLimits(0.0,4.2);
  tge_bothpionmean->GetXaxis()->SetTitle("p (GeV/c)");
  tge_bothpionmean->GetXaxis()->CenterTitle();
  tge_bothpionmean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tge_bothpionmean->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_pion_mean_sim.gif");
  c1->Print("m2pT_both_pion_mean_sim.eps");

  TGraphErrors *tge_bothpionsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_bothpionsigma->SetMarkerColor(kBlue);
  tge_bothpionsigma->SetMarkerStyle(20);
  tge_bothpionsigma->Draw("ap");
  tge_bothpionsigma->Fit(funsigma,"R");
  tge_bothpionsigma->SetMinimum(0.0);
  tge_bothpionsigma->SetMaximum(0.2);
  tge_bothpionsigma->GetXaxis()->SetLimits(0.0,4.2);
  tge_bothpionsigma->GetXaxis()->SetTitle("p (GeV/c)");
  tge_bothpionsigma->GetXaxis()->CenterTitle();
  tge_bothpionsigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tge_bothpionsigma->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_pion_sigma_sim.gif");
  c1->Print("m2pT_both_pion_sigma_sim.eps");

  // ----------------------------------------------------------------------

  // ---  now write to file

  // cout<<"now writing output file for pion pid function pion_pid_sim.C "<<endl;

  // ofstream foutpionpid("pion_pid_sim.C");
  // foutpionpid<<"float isPionLow(float mom, float m2tofw)\n{\n"
  // 	     <<"float x = mom;\n"
  // 	     <<"float a0 = "<<funmean->GetParameter(0)<<";\n"
  // 	     <<"float a1 = "<<funmean->GetParameter(1)<<";\n"
  // 	     <<"float a2 = "<<funmean->GetParameter(2)<<";\n"
  // 	     <<"float a3 = "<<funmean->GetParameter(3)<<";\n"
  // 	     <<"float a4 = "<<funmean->GetParameter(4)<<";\n"
  // 	     <<"float mean = a0+a1/x+a2/x/x+a3*exp(sqrt(x))+a4*sqrt(x);\n"
  // 	     <<"float b0 = "<<funsigma->GetParameter(0)<<";\n"
  // 	     <<"float b1 = "<<funsigma->GetParameter(1)<<";\n"
  // 	     <<"float b2 = "<<funsigma->GetParameter(2)<<";\n"
  // 	     <<"float b3 = "<<funsigma->GetParameter(3)<<";\n"
  // 	     <<"float b4 = "<<funsigma->GetParameter(4)<<";\n"
  // 	     <<"float sigma = b0+b1/x+b2/x/x+b3*exp(sqrt(x))+b4*sqrt(x);\n"
  // 	     <<"return (m2tofw - mean)/sigma;\n}\n"<<endl;

  // cout<<"done writing out pion pid function"<<endl;

  // ----------------------------------------------------------------------





  // --- kaon

  ifstream finbothkaon("m2pT_both_kaon_par_sim.txt");
  for(int i=0; i<40; i++)
    {
      finbothkaon>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.2) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.2) {sigma[i]=-9;esigma[i]=0;}
      if(i<3) {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_bothkaonmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_bothkaonmean->SetMarkerColor(kBlue);
  tge_bothkaonmean->SetMarkerStyle(20);
  tge_bothkaonmean->Draw("ap");
  //tge_bothkaonmean->Fit(funmean,"R");
  pdgmasska->Draw("same");
  tge_bothkaonmean->Fit(funmean,"","",0.3,4.0);
  tge_bothkaonmean->SetMinimum(0.1);
  tge_bothkaonmean->SetMaximum(0.4);
  tge_bothkaonmean->GetXaxis()->SetLimits(0.0,4.2);
  tge_bothkaonmean->GetXaxis()->SetTitle("p (GeV/c)");
  tge_bothkaonmean->GetXaxis()->CenterTitle();
  tge_bothkaonmean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tge_bothkaonmean->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_kaon_mean_sim.gif");
  c1->Print("m2pT_both_kaon_mean_sim.eps");

  TGraphErrors *tge_bothkaonsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_bothkaonsigma->SetMarkerColor(kBlue);
  tge_bothkaonsigma->SetMarkerStyle(20);
  tge_bothkaonsigma->Draw("ap");
  //tge_bothkaonsigma->Fit(funsigma,"R");
  tge_bothkaonsigma->Fit(funsigma,"","",0.3,4.0);
  tge_bothkaonsigma->SetMinimum(0.0);
  tge_bothkaonsigma->SetMaximum(0.2);
  tge_bothkaonsigma->GetXaxis()->SetLimits(0.0,4.2);
  tge_bothkaonsigma->GetXaxis()->SetTitle("p (GeV/c)");
  tge_bothkaonsigma->GetXaxis()->CenterTitle();
  tge_bothkaonsigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tge_bothkaonsigma->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_kaon_sigma_sim.gif");
  c1->Print("m2pT_both_kaon_sigma_sim.eps");








  // --- proton

  ifstream finbothproton("m2pT_both_proton_par_sim.txt");
  for(int i=0; i<40; i++)
    {
      finbothproton>>pt[i]>>mean[i]>>emean[i]>>sigma[i]>>esigma[i];
      ept[i]=0;
      if(emean[i]>0.2) {mean[i]=-9;emean[i]=0;}
      if(esigma[i]>0.2) {sigma[i]=-9;esigma[i]=0;}
      if(i<4) {mean[i]=-9;emean[i]=0;sigma[i]=-9;esigma[i]=0;}
    }

  TGraphErrors *tge_bothprotonmean = new TGraphErrors(40,pt,mean,ept,emean);
  tge_bothprotonmean->SetMarkerColor(kBlue);
  tge_bothprotonmean->SetMarkerStyle(20);
  tge_bothprotonmean->Draw("ap");
  pdgmasspr->Draw("same");
  //tge_bothprotonmean->Fit(funmean,"R");
  tge_bothprotonmean->Fit(funmean,"","",0.4,4.0);
  tge_bothprotonmean->SetMinimum(0.6);
  tge_bothprotonmean->SetMaximum(1.1);
  tge_bothprotonmean->GetXaxis()->SetLimits(0.0,4.2);
  tge_bothprotonmean->GetXaxis()->SetTitle("p (GeV/c)");
  tge_bothprotonmean->GetXaxis()->CenterTitle();
  tge_bothprotonmean->GetYaxis()->SetTitle("#mu_{m^{2}}");
  tge_bothprotonmean->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_proton_mean_sim.gif");
  c1->Print("m2pT_both_proton_mean_sim.eps");

  TGraphErrors *tge_bothprotonsigma = new TGraphErrors(40,pt,sigma,ept,esigma);
  tge_bothprotonsigma->SetMarkerColor(kBlue);
  tge_bothprotonsigma->SetMarkerStyle(20);
  tge_bothprotonsigma->Draw("ap");
  //tge_bothprotonsigma->Fit(funsigma,"R");
  tge_bothprotonsigma->Fit(funsigma,"","",0.4,4.0);
  tge_bothprotonsigma->SetMinimum(0.0);
  tge_bothprotonsigma->SetMaximum(0.2);
  tge_bothprotonsigma->GetXaxis()->SetLimits(0.0,4.2);
  tge_bothprotonsigma->GetXaxis()->SetTitle("p (GeV/c)");
  tge_bothprotonsigma->GetXaxis()->CenterTitle();
  tge_bothprotonsigma->GetYaxis()->SetTitle("#sigma_{m^{2}}");
  tge_bothprotonsigma->GetYaxis()->CenterTitle();

  c1->Print("m2pT_both_proton_sigma_sim.gif");
  c1->Print("m2pT_both_proton_sigma_sim.eps");





}

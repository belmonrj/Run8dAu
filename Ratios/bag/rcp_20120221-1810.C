void rcp()
{

  doit_hist(0,6);
  doit_file(0,6);

}


void doit_hist(int pionid=0, int protonid=6)
{

  TLine *line = new TLine(0.0,1.0,6.0,1.0);

  TCanvas *c1 = new TCanvas("c1","",800,600);

  TF1 *fun = new TF1("fun","pol0",0,10);
  fun->SetParameter(0,1);

  float tmp;

  // char centstring[5];
  // if(centid==0) sprintf(centstring,"0010");
  // else if(centid==1) sprintf(centstring,"1020");
  // else if(centid==2) sprintf(centstring,"2040");
  // else if(centid==3) sprintf(centstring,"4060");
  // else if(centid==4) sprintf(centstring,"6092");
  // else {cout<<"you gonna die"<<endl; return;}

  TFile *flopm = TFile::Open("outlowpm.root");
  TFile *fhipm = TFile::Open("outhighpm.root");
  TFile *flomp = TFile::Open("outlowmp.root");
  TFile *fhimp = TFile::Open("outhighmp.root");

  char histname[100];

  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",pionid,"0010");
  TH1F *hlo_pospion_pm_CENT = (TH1F *)flopm->Get(histname);
  TH1F *hhi_pospion_pm_CENT = (TH1F *)fhipm->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",protonid,"0010");
  TH1F *hlo_posproton_pm_CENT = (TH1F *)flopm->Get(histname);
  TH1F *hhi_posproton_pm_CENT = (TH1F *)fhipm->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",pionid,"6092");
  TH1F *hlo_pospion_pm_PERI = (TH1F *)flopm->Get(histname);
  TH1F *hhi_pospion_pm_PERI = (TH1F *)fhipm->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",protonid,"6092");
  TH1F *hlo_posproton_pm_PERI = (TH1F *)flopm->Get(histname);
  TH1F *hhi_posproton_pm_PERI = (TH1F *)fhipm->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",pionid,"0010");
  TH1F *hlo_negpion_pm_CENT = (TH1F *)flopm->Get(histname);
  TH1F *hhi_negpion_pm_CENT = (TH1F *)fhipm->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",protonid,"0010");
  TH1F *hlo_negproton_pm_CENT = (TH1F *)flopm->Get(histname);
  TH1F *hhi_negproton_pm_CENT = (TH1F *)fhipm->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",pionid,"6092");
  TH1F *hlo_negpion_pm_PERI = (TH1F *)flopm->Get(histname);
  TH1F *hhi_negpion_pm_PERI = (TH1F *)fhipm->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",protonid,"6092");
  TH1F *hlo_negproton_pm_PERI = (TH1F *)flopm->Get(histname);
  TH1F *hhi_negproton_pm_PERI = (TH1F *)fhipm->Get(histname);

  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",pionid,"0010");
  TH1F *hlo_pospion_mp_CENT = (TH1F *)flomp->Get(histname);
  TH1F *hhi_pospion_mp_CENT = (TH1F *)fhimp->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",protonid,"0010");
  TH1F *hlo_posproton_mp_CENT = (TH1F *)flomp->Get(histname);
  TH1F *hhi_posproton_mp_CENT = (TH1F *)fhimp->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",pionid,"6092");
  TH1F *hlo_pospion_mp_PERI = (TH1F *)flomp->Get(histname);
  TH1F *hhi_pospion_mp_PERI = (TH1F *)fhimp->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",protonid,"6092");
  TH1F *hlo_posproton_mp_PERI = (TH1F *)flomp->Get(histname);
  TH1F *hhi_posproton_mp_PERI = (TH1F *)fhimp->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",pionid,"0010");
  TH1F *hlo_negpion_mp_CENT = (TH1F *)flomp->Get(histname);
  TH1F *hhi_negpion_mp_CENT = (TH1F *)fhimp->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",protonid,"0010");
  TH1F *hlo_negproton_mp_CENT = (TH1F *)flomp->Get(histname);
  TH1F *hhi_negproton_mp_CENT = (TH1F *)fhimp->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",pionid,"6092");
  TH1F *hlo_negpion_mp_PERI = (TH1F *)flomp->Get(histname);
  TH1F *hhi_negpion_mp_PERI = (TH1F *)fhimp->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",protonid,"6092");
  TH1F *hlo_negproton_mp_PERI = (TH1F *)flomp->Get(histname);
  TH1F *hhi_negproton_mp_PERI = (TH1F *)fhimp->Get(histname);

  //sumw2
  hlo_pospion_pm_CENT->Sumw2();
  hlo_negpion_pm_CENT->Sumw2();
  hlo_pospion_mp_CENT->Sumw2();
  hlo_negpion_mp_CENT->Sumw2();
  hlo_posproton_pm_CENT->Sumw2();
  hlo_negproton_pm_CENT->Sumw2();
  hlo_posproton_mp_CENT->Sumw2();
  hlo_negproton_mp_CENT->Sumw2();
  hlo_pospion_pm_PERI->Sumw2();
  hlo_negpion_pm_PERI->Sumw2();
  hlo_pospion_mp_PERI->Sumw2();
  hlo_negpion_mp_PERI->Sumw2();
  hlo_posproton_pm_PERI->Sumw2();
  hlo_negproton_pm_PERI->Sumw2();
  hlo_posproton_mp_PERI->Sumw2();
  hlo_negproton_mp_PERI->Sumw2();

  //cent/peri
  hlo_pospion_pm_CENT->Divide(hlo_pospion_pm_PERI);
  hlo_negpion_pm_CENT->Divide(hlo_negpion_pm_PERI);
  hlo_pospion_mp_CENT->Divide(hlo_pospion_mp_PERI);
  hlo_negpion_mp_CENT->Divide(hlo_negpion_mp_PERI);
  hlo_posproton_pm_CENT->Divide(hlo_posproton_pm_PERI);
  hlo_negproton_pm_CENT->Divide(hlo_negproton_pm_PERI);
  hlo_posproton_mp_CENT->Divide(hlo_posproton_mp_PERI);
  hlo_negproton_mp_CENT->Divide(hlo_negproton_mp_PERI);

  //normalization
  hlo_pospion_pm_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hlo_negpion_pm_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hlo_pospion_mp_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hlo_negpion_mp_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hlo_posproton_pm_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hlo_negproton_pm_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hlo_posproton_mp_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hlo_negproton_mp_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));

  // add fields, then divide by 2
  hlo_pospion_pm_CENT->Add(hlo_pospion_mp_CENT);
  hlo_negpion_pm_CENT->Add(hlo_negpion_mp_CENT);
  hlo_posproton_pm_CENT->Add(hlo_posproton_mp_CENT);
  hlo_negproton_pm_CENT->Add(hlo_negproton_mp_CENT);
  hlo_pospion_pm_CENT->Divide(fun,2.0);
  hlo_negpion_pm_CENT->Divide(fun,2.0);
  hlo_posproton_pm_CENT->Divide(fun,2.0);
  hlo_negproton_pm_CENT->Divide(fun,2.0);



  //sumw2
  hhi_pospion_pm_CENT->Sumw2();
  hhi_negpion_pm_CENT->Sumw2();
  hhi_pospion_mp_CENT->Sumw2();
  hhi_negpion_mp_CENT->Sumw2();
  hhi_posproton_pm_CENT->Sumw2();
  hhi_negproton_pm_CENT->Sumw2();
  hhi_posproton_mp_CENT->Sumw2();
  hhi_negproton_mp_CENT->Sumw2();
  hhi_pospion_pm_PERI->Sumw2();
  hhi_negpion_pm_PERI->Sumw2();
  hhi_pospion_mp_PERI->Sumw2();
  hhi_negpion_mp_PERI->Sumw2();
  hhi_posproton_pm_PERI->Sumw2();
  hhi_negproton_pm_PERI->Sumw2();
  hhi_posproton_mp_PERI->Sumw2();
  hhi_negproton_mp_PERI->Sumw2();

  //cent/peri
  hhi_pospion_pm_CENT->Divide(hhi_pospion_pm_PERI);
  hhi_negpion_pm_CENT->Divide(hhi_negpion_pm_PERI);
  hhi_pospion_mp_CENT->Divide(hhi_pospion_mp_PERI);
  hhi_negpion_mp_CENT->Divide(hhi_negpion_mp_PERI);
  hhi_posproton_pm_CENT->Divide(hhi_posproton_pm_PERI);
  hhi_negproton_pm_CENT->Divide(hhi_negproton_pm_PERI);
  hhi_posproton_mp_CENT->Divide(hhi_posproton_mp_PERI);
  hhi_negproton_mp_CENT->Divide(hhi_negproton_mp_PERI);

  //normalization
  hhi_pospion_pm_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hhi_negpion_pm_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hhi_pospion_mp_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hhi_negpion_mp_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hhi_posproton_pm_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hhi_negproton_pm_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hhi_posproton_mp_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));
  hhi_negproton_mp_CENT->Divide(fun,(955/14.5)*(0.1/0.32)*(0.54/0.98));

  // add fields, then divide by 2
  hhi_pospion_pm_CENT->Add(hhi_pospion_mp_CENT);
  hhi_negpion_pm_CENT->Add(hhi_negpion_mp_CENT);
  hhi_posproton_pm_CENT->Add(hhi_posproton_mp_CENT);
  hhi_negproton_pm_CENT->Add(hhi_negproton_mp_CENT);
  hhi_pospion_pm_CENT->Divide(fun,2.0);
  hhi_negpion_pm_CENT->Divide(fun,2.0);
  hhi_posproton_pm_CENT->Divide(fun,2.0);
  hhi_negproton_pm_CENT->Divide(fun,2.0);

  // rebin by 5
  hhi_pospion_pm_CENT->Rebin(5);
  hhi_negpion_pm_CENT->Rebin(5);
  hhi_posproton_pm_CENT->Rebin(5);
  hhi_negproton_pm_CENT->Rebin(5);
  hhi_pospion_pm_CENT->Divide(fun,5.0);
  hhi_negpion_pm_CENT->Divide(fun,5.0);
  hhi_posproton_pm_CENT->Divide(fun,5.0);
  hhi_negproton_pm_CENT->Divide(fun,5.0);




  float pt[36], ept[36];
  float posratio[36], negratio[36];
  float eposratio[36], enegratio[36];
  float esysposratio[36], esysnegratio[36];

  for(int i=0; i<30; i++)
    {
      pt[i] = hlo_pospion_pm_CENT->GetBinCenter(i+1);
      ept[i] = 0;
      posratio[i] = hlo_pospion_pm_CENT->GetBinContent(i+1);
      eposratio[i] = hlo_pospion_pm_CENT->GetBinError(i+1);
      negratio[i] = hlo_negpion_pm_CENT->GetBinContent(i+1);
      enegratio[i] = hlo_negpion_pm_CENT->GetBinError(i+1);
      esysposratio[i] = posratio[i]*0.1; // 10% sys uncert
      esysnegratio[i] = negratio[i]*0.1; // 10% sys uncert
    }
  for(int i=0; i<6; i++)
    {
      pt[i+30] = hhi_pospion_pm_CENT->GetBinCenter(i+7);
      ept[i+30] = 0;
      posratio[i+30] = hhi_pospion_pm_CENT->GetBinContent(i+7);
      eposratio[i+30] = hhi_pospion_pm_CENT->GetBinError(i+7);
      negratio[i+30] = hhi_negpion_pm_CENT->GetBinContent(i+7);
      enegratio[i+30] = hhi_negpion_pm_CENT->GetBinError(i+7);
      esysposratio[i+30] = posratio[i+30]*0.1; // 10% sys uncert
      esysnegratio[i+30] = negratio[i+30]*0.1; // 10% sys uncert
    }
  for(int i=0; i<5; i++)
    {
      posratio[i]=-9;
      negratio[i]=-9;
    }

  TGraphErrors *tge_pospion = new TGraphErrors(36,pt,posratio,ept,eposratio);
  tge_pospion->SetMarkerColor(kRed);
  tge_pospion->SetMarkerStyle(kFullCircle);
  TGraphErrors *tge_negpion = new TGraphErrors(36,pt,negratio,ept,enegratio);
  tge_negpion->SetMarkerColor(kBlue);
  tge_negpion->SetMarkerStyle(kFullCircle);

  TGraphErrors *tge_syspospion = new TGraphErrors(36,pt,posratio,ept,esysposratio);
  tge_syspospion->SetMarkerColor(kRed);
  tge_syspospion->SetMarkerStyle(1);
  tge_syspospion->SetLineColor(kRed-10);
  tge_syspospion->SetLineWidth(15);
  TGraphErrors *tge_sysnegpion = new TGraphErrors(36,pt,negratio,ept,esysnegratio);
  tge_sysnegpion->SetMarkerColor(kBlue);
  tge_sysnegpion->SetMarkerStyle(1);
  tge_sysnegpion->SetLineColor(kBlue-10);
  tge_sysnegpion->SetLineWidth(15);

  // -------------------- //
  // -- now do proton --- //
  // -------------------- //

  for(int i=0; i<30; i++)
    {
      pt[i] = hlo_posproton_pm_CENT->GetBinCenter(i+1);
      ept[i] = 0;
      posratio[i] = hlo_posproton_pm_CENT->GetBinContent(i+1);
      eposratio[i] = hlo_posproton_pm_CENT->GetBinError(i+1);
      negratio[i] = hlo_negproton_pm_CENT->GetBinContent(i+1);
      enegratio[i] = hlo_negproton_pm_CENT->GetBinError(i+1);
      esysposratio[i] = posratio[i]*0.1; // 10% sys uncert
      esysnegratio[i] = negratio[i]*0.1; // 10% sys uncert
    }
  for(int i=0; i<6; i++)
    {
      pt[i+30] = hhi_posproton_pm_CENT->GetBinCenter(i+7);
      ept[i+30] = 0;
      posratio[i+30] = hhi_posproton_pm_CENT->GetBinContent(i+7);
      eposratio[i+30] = hhi_posproton_pm_CENT->GetBinError(i+7);
      negratio[i+30] = hhi_negproton_pm_CENT->GetBinContent(i+7);
      enegratio[i+30] = hhi_negproton_pm_CENT->GetBinError(i+7);
      esysposratio[i+30] = posratio[i+30]*0.1; // 10% sys uncert
      esysnegratio[i+30] = negratio[i+30]*0.1; // 10% sys uncert
    }
  for(int i=0; i<5; i++)
    {
      posratio[i]=-9;
      negratio[i]=-9;
    }

  TGraphErrors *tge_posproton = new TGraphErrors(36,pt,posratio,ept,eposratio);
  tge_posproton->SetMarkerColor(kRed);
  tge_posproton->SetMarkerStyle(kFullSquare);
  TGraphErrors *tge_negproton = new TGraphErrors(36,pt,negratio,ept,enegratio);
  tge_negproton->SetMarkerColor(kBlue);
  tge_negproton->SetMarkerStyle(kFullSquare);

  TGraphErrors *tge_sysposproton = new TGraphErrors(36,pt,posratio,ept,esysposratio);
  tge_sysposproton->SetMarkerColor(kRed);
  tge_sysposproton->SetMarkerStyle(1);
  tge_sysposproton->SetLineColor(kRed-10);
  tge_sysposproton->SetLineWidth(15);
  TGraphErrors *tge_sysnegproton = new TGraphErrors(36,pt,negratio,ept,esysnegratio);
  tge_sysnegproton->SetMarkerColor(kBlue);
  tge_sysnegproton->SetMarkerStyle(1);
  tge_sysnegproton->SetLineColor(kBlue-10);
  tge_sysnegproton->SetLineWidth(15);



  // ----------------------- //
  // --- do the plotting --- //
  // ----------------------- //

  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tge_syspospion);
  tmg->Add(tge_sysnegpion);
  tmg->Add(tge_sysposproton);
  tmg->Add(tge_sysnegproton);
  tmg->Add(tge_pospion);
  tmg->Add(tge_negpion);
  tmg->Add(tge_posproton);
  tmg->Add(tge_negproton);
  tmg->Draw("apz");
  line->Draw("same");
  tmg->SetMaximum(2.0);
  tmg->SetMinimum(0.0);
  tmg->GetXaxis()->SetLimits(0.0,6.0);
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetYaxis()->SetTitle("R_{CP}");
  tmg->GetXaxis()->CenterTitle();
  tmg->GetYaxis()->CenterTitle();

  TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->AddEntry(tge_pospion,"#pi^{+}","p");
  leg->AddEntry(tge_negpion,"#pi^{-}","p");
  leg->AddEntry(tge_posproton,"p","p");
  leg->AddEntry(tge_negproton,"#bar{p}","p");
  leg->Draw();

  char figname[100];
  sprintf(figname,"special/rcp_%d%d.gif",pionid,protonid);
  c1->Print(figname);
  sprintf(figname,"special/rcp_%d%d.eps",pionid,protonid);
  c1->Print(figname);


  c1->Clear();

  float pt[32];
  float ept[32]={0};
  float ratio[32], eratio[32];

  ifstream fpion1("../Spectra/ppg026/RCP/pion.dat");
  for(int i=0; i<28;i++)
    {
      fpion1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fpion1.close();
  TGraphErrors *ppgpion = new TGraphErrors(28, pt, ratio, ept, eratio);

  // ifstream fkaon1("ppg026/RCP/kaon.dat");
  // for(int i=0; i<16;i++)
  //   {
  //     fkaon1>>pt[i]>>ratio[i]>>eratio[i];
  //   }
  // fkaon1.close();
  // TGraphErrors *ppgkaon = new TGraphErrors(16, pt, ratio, ept, eratio);

  ifstream fproton1("../Spectra/ppg026/RCP/proton.dat");
  for(int i=0; i<22;i++)
    {
      fproton1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fproton1.close();
  TGraphErrors *ppgproton = new TGraphErrors(22, pt, ratio, ept, eratio);

  fpion1.open("../Spectra/ppg080/RCP/pion0.dat");
  for(int i=0; i<14;i++)
    {
      fpion1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fpion1.close();
  TGraphErrors *ppgpion0 = new TGraphErrors(14, pt, ratio, ept, eratio);

  ppgpion->SetMarkerStyle(kFullCircle);
  ppgpion->SetMarkerColor(kBlack);
  // ppgkaon->SetMarkerStyle(kFullTriangleUp);
  // ppgkaon->SetMarkerColor(kBlack);
  ppgproton->SetMarkerStyle(kFullSquare);
  ppgproton->SetMarkerColor(kBlack);
  ppgpion0->SetMarkerStyle(kOpenCircle);
  ppgpion0->SetMarkerColor(kBlack);



  TMultiGraph *tmg2 = new TMultiGraph();
  tmg2->Add(tge_syspospion);
  tmg2->Add(tge_sysnegpion);
  tmg2->Add(tge_sysposproton);
  tmg2->Add(tge_sysnegproton);
  tmg2->Add(tge_pospion);
  tmg2->Add(tge_negpion);
  tmg2->Add(tge_posproton);
  tmg2->Add(tge_negproton);
  tmg2->Add(ppgpion);
  tmg2->Add(ppgproton);
  tmg2->Add(ppgpion0);
  tmg2->Draw("apz");
  line->Draw("same");
  tmg2->SetMaximum(2.0);
  tmg2->SetMinimum(0.0);
  tmg2->GetXaxis()->SetLimits(0.0,6.0);
  tmg2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg2->GetYaxis()->SetTitle("R_{CP}");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->CenterTitle();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(kWhite);
  leg2->AddEntry(tge_pospion,"#pi^{+}","p");
  leg2->AddEntry(tge_negpion,"#pi^{-}","p");
  leg2->AddEntry(tge_posproton,"p","p");
  leg2->AddEntry(tge_negproton,"#bar{p}","p");
  leg2->Draw();

  TLegend *leg3 = new TLegend(0.18,0.68,0.38,0.88);
  leg3->SetBorderSize(0);
  leg3->SetFillColor(kWhite);
  leg3->AddEntry(ppgpion,"#pi Run2","p");
  leg3->AddEntry(ppgproton,"p Run2","p");
  leg3->AddEntry(ppgpion0,"#pi^{0} Run4","p");
  leg3->Draw();

  sprintf(figname,"special/rcp_ppg_%d%d.gif",pionid,protonid);
  c1->Print(figname);
  sprintf(figname,"special/rcp_ppg_%d%d.eps",pionid,protonid);
  c1->Print(figname);



  c1->Clear();
  delete c1;

}



void doit_file(int pionid=0, int protonid=6)
{

  const float normal = 955.4/14.5; // Run7 numbers, need to double check

  TLine *line = new TLine(0.0,1.0,6.0,1.0);

  TCanvas *c1 = new TCanvas("c1","",800,600);

  TF1 *fun = new TF1("fun","pol0",0,10);
  fun->SetParameter(0,1);

  float tmp;

  char centstring_C[10];
  sprintf(centstring_C,"0010");
  char centstring_P[10];
  sprintf(centstring_P,"6092");

  char fnameinposcb_C[100];
  char fnameinnegcb_C[100];
  char fnameinposcb_P[100];
  char fnameinnegcb_P[100];

  float ept[36]={0};

  // ----------------------- //
  // ----------------------- //
  // ---                 --- //
  // --- first the pions --- //
  // ---                 --- //
  // ----------------------- //
  // ----------------------- //

  // ---------------------- //
  // --- do the central --- //
  // ---------------------- //
  sprintf(fnameinposcb_C,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_C);
  ifstream finposcb_C;
  ifstream finnegcb_C;
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  float pT_poscb_C[36], yield_poscb_C[36], eyield_poscb_C[36];
  float pT_negcb_C[36], yield_negcb_C[36], eyield_negcb_C[36];
  for(int i=0; i<30; i++)
    {
      finposcb_C>>pT_poscb_C[i]>>yield_poscb_C[i]>>eyield_poscb_C[i];
      finnegcb_C>>pT_negcb_C[i]>>yield_negcb_C[i]>>eyield_negcb_C[i];
    }
  finposcb_C.close();
  finnegcb_C.close();
  sprintf(fnameinposcb_C,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_C);
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  for(int i=0; i<12; i++)
    {
      if(i<6)
	{
	  finposcb_C>>tmp>>tmp>>tmp;
	  finnegcb_C>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_C>>pT_poscb_C[i+24]>>yield_poscb_C[i+24]>>eyield_poscb_C[i+24];
	  finnegcb_C>>pT_negcb_C[i+24]>>yield_negcb_C[i+24]>>eyield_negcb_C[i+24];
	}
    }
  finposcb_C.close();
  finnegcb_C.close();

  // ---------------------- //
  // --- now peripheral --- //
  // ---------------------- //
  sprintf(fnameinposcb_P,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_P);
  ifstream finposcb_P;
  ifstream finnegcb_P;
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  float pT_poscb_P[36], yield_poscb_P[36], eyield_poscb_P[36];
  float pT_negcb_P[36], yield_negcb_P[36], eyield_negcb_P[36];
  for(int i=0; i<30; i++)
    {
      finposcb_P>>pT_poscb_P[i]>>yield_poscb_P[i]>>eyield_poscb_P[i];
      finnegcb_P>>pT_negcb_P[i]>>yield_negcb_P[i]>>eyield_negcb_P[i];
    }
  finposcb_P.close();
  finnegcb_P.close();
  sprintf(fnameinposcb_P,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_P);
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  for(int i=0; i<12; i++)
    {
      if(i<6)
	{
	  finposcb_P>>tmp>>tmp>>tmp;
	  finnegcb_P>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_P>>pT_poscb_P[i+24]>>yield_poscb_P[i+24]>>eyield_poscb_P[i+24];
	  finnegcb_P>>pT_negcb_P[i+24]>>yield_negcb_P[i+24]>>eyield_negcb_P[i+24];
	}
    }
  finposcb_P.close();
  finnegcb_P.close();

  float pTpos[36], ratiopos[36], eratiopos[36], esysratiopos[36];
  float pTneg[36], rationeg[36], erationeg[36], esysrationeg[36];

  float pTpos_pion_nq[36], epTpos_pion_nq[36];
  float pTneg_pion_nq[36], epTneg_pion_nq[36];
  float ratiopos_pion_nq[36], eratiopos_pion_nq[36], esysratiopos_pion_nq[36];
  float rationeg_pion_nq[36], erationeg_pion_nq[36], esysrationeg_pion_nq[36];
  for(int i=0; i<36; i++)
    {
      if(yield_poscb_P[i]>0&&yield_negcb_P[i]>0)
	{
	  pTpos[i] = pT_poscb_C[i];
	  ratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i];
	  eratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i]
	    *sqrt((eyield_poscb_C[i]/yield_poscb_C[i])**2+(eyield_poscb_P[i]/yield_poscb_P[i])**2);
	  pTneg[i] = pT_negcb_C[i];
	  rationeg[i] = yield_negcb_C[i]/yield_negcb_P[i];
	  erationeg[i] = yield_negcb_C[i]/yield_negcb_P[i]
	    *sqrt((eyield_negcb_C[i]/yield_negcb_C[i])**2+(eyield_negcb_P[i]/yield_negcb_P[i])**2);
	}
      else
	{
	  pTpos[i]=0;
	  pTneg[i]=0;
	  ratiopos[i]=-9;
	  rationeg[i]=-9;
	  eratiopos[i]=0;
	  erationeg[i]=0;
	}
      ratiopos[i] /= normal;
      rationeg[i] /= normal;
      eratiopos[i] /= normal;
      erationeg[i] /= normal;
      esysratiopos[i] = ratiopos[i]*0.1; // 10% sys uncert
      esysrationeg[i] = rationeg[i]*0.1; // 10% sys uncert
      // nq scaling?
      pTpos_pion_nq[i] = pTpos[i]/2.0;
      epTpos_pion_nq[i] = 0;
      ratiopos_pion_nq[i] = ratiopos[i]/2.0;
      eratiopos_pion_nq[i] = eratiopos[i]/2.0;
      esysratiopos_pion_nq[i] = esysratiopos[i]/2.0;
      pTneg_pion_nq[i] = pTneg[i]/2.0;
      epTneg_pion_nq[i] = 0;
      rationeg_pion_nq[i] = rationeg[i]/2.0;
      erationeg_pion_nq[i] = erationeg[i]/2.0;
      esysrationeg_pion_nq[i] = esysrationeg[i]/2.0;
    }

  TGraphErrors *tge_pospion = new TGraphErrors(36,pTpos,ratiopos,ept,eratiopos);
  TGraphErrors *tge_negpion = new TGraphErrors(36,pTneg,rationeg,ept,erationeg);
  TGraphErrors *tge_syspospion = new TGraphErrors(36,pTpos,ratiopos,ept,esysratiopos);
  TGraphErrors *tge_sysnegpion = new TGraphErrors(36,pTneg,rationeg,ept,esysrationeg);

  TGraphErrors *tge_pospion_nq = new TGraphErrors(36,pTpos_pion_nq,ratiopos,ept,eratiopos);
  TGraphErrors *tge_pospion_NQ = new TGraphErrors(36,pTpos_pion_nq,ratiopos_pion_nq,ept,eratiopos_pion_nq);
  TGraphErrors *tge_negpion_nq = new TGraphErrors(36,pTneg_pion_nq,rationeg,ept,erationeg);
  TGraphErrors *tge_negpion_NQ = new TGraphErrors(36,pTneg_pion_nq,rationeg_pion_nq,ept,erationeg_pion_nq);
  TGraphErrors *tge_syspospion_nq = new TGraphErrors(36,pTpos_pion_nq,ratiopos,ept,esysratiopos);
  TGraphErrors *tge_syspospion_NQ = new TGraphErrors(36,pTpos_pion_nq,ratiopos_pion_nq,ept,esysratiopos_pion_nq);
  TGraphErrors *tge_sysnegpion_nq = new TGraphErrors(36,pTneg_pion_nq,rationeg,ept,esysrationeg);
  TGraphErrors *tge_sysnegpion_NQ = new TGraphErrors(36,pTneg_pion_nq,rationeg_pion_nq,ept,esysrationeg_pion_nq);


  // ----------------------- //
  // ----------------------- //
  // ---                 --- //
  // --- now the protons --- //
  // ---                 --- //
  // ----------------------- //
  // ----------------------- //

  // ---------------------- //
  // --- do the central --- //
  // ---------------------- //
  sprintf(fnameinposcb_C,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring_C);
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  for(int i=0; i<30; i++)
    {
      finposcb_C>>pT_poscb_C[i]>>yield_poscb_C[i]>>eyield_poscb_C[i];
      finnegcb_C>>pT_negcb_C[i]>>yield_negcb_C[i]>>eyield_negcb_C[i];
    }
  finposcb_C.close();
  finnegcb_C.close();
  sprintf(fnameinposcb_C,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring_C);
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  for(int i=0; i<12; i++)
    {
      if(i<6)
	{
	  finposcb_C>>tmp>>tmp>>tmp;
	  finnegcb_C>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_C>>pT_poscb_C[i+24]>>yield_poscb_C[i+24]>>eyield_poscb_C[i+24];
	  finnegcb_C>>pT_negcb_C[i+24]>>yield_negcb_C[i+24]>>eyield_negcb_C[i+24];
	}
    }
  finposcb_C.close();
  finnegcb_C.close();

  // ---------------------- //
  // --- now peripheral --- //
  // ---------------------- //
  sprintf(fnameinposcb_P,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring_P);
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  for(int i=0; i<30; i++)
    {
      finposcb_P>>pT_poscb_P[i]>>yield_poscb_P[i]>>eyield_poscb_P[i];
      finnegcb_P>>pT_negcb_P[i]>>yield_negcb_P[i]>>eyield_negcb_P[i];
    }
  finposcb_P.close();
  finnegcb_P.close();
  sprintf(fnameinposcb_P,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring_P);
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  for(int i=0; i<12; i++)
    {
      if(i<6)
	{
	  finposcb_P>>tmp>>tmp>>tmp;
	  finnegcb_P>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_P>>pT_poscb_P[i+24]>>yield_poscb_P[i+24]>>eyield_poscb_P[i+24];
	  finnegcb_P>>pT_negcb_P[i+24]>>yield_negcb_P[i+24]>>eyield_negcb_P[i+24];
	}
    }
  finposcb_P.close();
  finnegcb_P.close();

  float pTpos_proton_nq[36], epTpos_proton_nq[36];
  float pTneg_proton_nq[36], epTneg_proton_nq[36];
  float ratiopos_proton_nq[36], eratiopos_proton_nq[36], esysratiopos_proton_nq[36];
  float rationeg_proton_nq[36], erationeg_proton_nq[36], esysrationeg_proton_nq[36];
  for(int i=0; i<36; i++)
    {
      if(yield_poscb_P[i]>0&&yield_negcb_P[i]>0)
	{
	  pTpos[i] = pT_poscb_C[i];
	  ratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i];
	  eratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i]
	    *sqrt((eyield_poscb_C[i]/yield_poscb_C[i])**2+(eyield_poscb_P[i]/yield_poscb_P[i])**2);
	  pTneg[i] = pT_negcb_C[i];
	  rationeg[i] = yield_negcb_C[i]/yield_negcb_P[i];
	  erationeg[i] = yield_negcb_C[i]/yield_negcb_P[i]
	    *sqrt((eyield_negcb_C[i]/yield_negcb_C[i])**2+(eyield_negcb_P[i]/yield_negcb_P[i])**2);
	}
      else
	{
	  pTpos[i]=0;
	  pTneg[i]=0;
	  ratiopos[i]=-9;
	  rationeg[i]=-9;
	  eratiopos[i]=0;
	  erationeg[i]=0;
	}
      ratiopos[i] /= normal;
      rationeg[i] /= normal;
      eratiopos[i] /= normal;
      erationeg[i] /= normal;
      esysratiopos[i] = ratiopos[i]*0.1; // 10% sys uncert
      esysrationeg[i] = rationeg[i]*0.1; // 10% sys uncert
      // nq scaling?
      pTpos_proton_nq[i] = pTpos[i]/3.0;
      epTpos_proton_nq[i] = 0;
      ratiopos_proton_nq[i] = ratiopos[i]/3.0;
      eratiopos_proton_nq[i] = eratiopos[i]/3.0;
      esysratiopos_proton_nq[i] = esysratiopos[i]/3.0;
      pTneg_proton_nq[i] = pTneg[i]/3.0;
      epTneg_proton_nq[i] = 0;
      rationeg_proton_nq[i] = rationeg[i]/3.0;
      erationeg_proton_nq[i] = erationeg[i]/3.0;
      esysrationeg_proton_nq[i] = esysrationeg[i]/3.0;
    }

  TGraphErrors *tge_posproton = new TGraphErrors(36,pTpos,ratiopos,ept,eratiopos);
  TGraphErrors *tge_negproton = new TGraphErrors(36,pTneg,rationeg,ept,erationeg);
  TGraphErrors *tge_sysposproton = new TGraphErrors(36,pTpos,ratiopos,ept,esysratiopos);
  TGraphErrors *tge_sysnegproton = new TGraphErrors(36,pTneg,rationeg,ept,esysrationeg);

  TGraphErrors *tge_posproton_nq = new TGraphErrors(36,pTpos_proton_nq,ratiopos,ept,eratiopos);
  TGraphErrors *tge_posproton_NQ = new TGraphErrors(36,pTpos_proton_nq,ratiopos_proton_nq,ept,eratiopos_proton_nq);
  TGraphErrors *tge_negproton_nq = new TGraphErrors(36,pTneg_proton_nq,rationeg,ept,erationeg);
  TGraphErrors *tge_negproton_NQ = new TGraphErrors(36,pTneg_proton_nq,rationeg_proton_nq,ept,erationeg_proton_nq);
  TGraphErrors *tge_sysposproton_nq = new TGraphErrors(36,pTpos_proton_nq,ratiopos,ept,esysratiopos);
  TGraphErrors *tge_sysposproton_NQ = new TGraphErrors(36,pTpos_proton_nq,ratiopos_proton_nq,ept,esysratiopos_proton_nq);
  TGraphErrors *tge_sysnegproton_nq = new TGraphErrors(36,pTneg_proton_nq,rationeg,ept,esysrationeg);
  TGraphErrors *tge_sysnegproton_NQ = new TGraphErrors(36,pTneg_proton_nq,rationeg_proton_nq,ept,esysrationeg_proton_nq);



  tge_pospion->SetMarkerColor(kRed);
  tge_negpion->SetMarkerColor(kBlue);
  tge_posproton->SetMarkerColor(kRed);
  tge_negproton->SetMarkerColor(kBlue);

  tge_pospion->SetMarkerStyle(kFullCircle);
  tge_negpion->SetMarkerStyle(kFullCircle);
  tge_posproton->SetMarkerStyle(kFullSquare);
  tge_negproton->SetMarkerStyle(kFullSquare);

  tge_syspospion->SetMarkerColor(kRed);
  tge_syspospion->SetMarkerStyle(1);
  tge_syspospion->SetLineColor(kRed-10);
  tge_syspospion->SetLineWidth(15);
  tge_sysnegpion->SetMarkerColor(kBlue);
  tge_sysnegpion->SetMarkerStyle(1);
  tge_sysnegpion->SetLineColor(kBlue-10);
  tge_sysnegpion->SetLineWidth(15);

  tge_sysposproton->SetMarkerColor(kRed);
  tge_sysposproton->SetMarkerStyle(1);
  tge_sysposproton->SetLineColor(kRed-10);
  tge_sysposproton->SetLineWidth(15);
  tge_sysnegproton->SetMarkerColor(kBlue);
  tge_sysnegproton->SetMarkerStyle(1);
  tge_sysnegproton->SetLineColor(kBlue-10);
  tge_sysnegproton->SetLineWidth(15);


  // ----------------------- //
  // --- do the plotting --- //
  // ----------------------- //

  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tge_syspospion);
  tmg->Add(tge_sysnegpion);
  tmg->Add(tge_sysposproton);
  tmg->Add(tge_sysnegproton);
  tmg->Add(tge_pospion);
  tmg->Add(tge_negpion);
  tmg->Add(tge_posproton);
  tmg->Add(tge_negproton);
  tmg->Draw("apz");
  line->Draw("same");
  tmg->SetMaximum(2.0);
  tmg->SetMinimum(0.0);
  tmg->GetXaxis()->SetLimits(0.0,6.0);
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetYaxis()->SetTitle("R_{CP}");
  tmg->GetXaxis()->CenterTitle();
  tmg->GetYaxis()->CenterTitle();

  TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->AddEntry(tge_pospion,"#pi^{+}","p");
  leg->AddEntry(tge_negpion,"#pi^{-}","p");
  leg->AddEntry(tge_posproton,"p","p");
  leg->AddEntry(tge_negproton,"#bar{p}","p");
  leg->Draw();

  char figname[100];
  sprintf(figname,"regular/rcp_%d%d.gif",pionid,protonid);
  c1->Print(figname);
  sprintf(figname,"regular/rcp_%d%d.eps",pionid,protonid);
  c1->Print(figname);

  c1->Clear();

  float pt[32];
  float ept[32]={0};
  float ratio[32], eratio[32];

  ifstream fpion1("../Spectra/ppg026/RCP/pion.dat");
  for(int i=0; i<28;i++)
    {
      fpion1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fpion1.close();
  TGraphErrors *ppgpion = new TGraphErrors(28, pt, ratio, ept, eratio);

  // ifstream fkaon1("ppg026/RCP/kaon.dat");
  // for(int i=0; i<16;i++)
  //   {
  //     fkaon1>>pt[i]>>ratio[i]>>eratio[i];
  //   }
  // fkaon1.close();
  // TGraphErrors *ppgkaon = new TGraphErrors(16, pt, ratio, ept, eratio);

  ifstream fproton1("../Spectra/ppg026/RCP/proton.dat");
  for(int i=0; i<22;i++)
    {
      fproton1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fproton1.close();
  TGraphErrors *ppgproton = new TGraphErrors(22, pt, ratio, ept, eratio);

  fpion1.open("../Spectra/ppg080/RCP/pion0.dat");
  for(int i=0; i<14;i++)
    {
      fpion1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fpion1.close();
  TGraphErrors *ppgpion0 = new TGraphErrors(14, pt, ratio, ept, eratio);

  ppgpion->SetMarkerStyle(kFullCircle);
  ppgpion->SetMarkerColor(kBlack);
  // ppgkaon->SetMarkerStyle(kFullTriangleUp);
  // ppgkaon->SetMarkerColor(kBlack);
  ppgproton->SetMarkerStyle(kFullSquare);
  ppgproton->SetMarkerColor(kBlack);
  ppgpion0->SetMarkerStyle(kOpenCircle);
  ppgpion0->SetMarkerColor(kBlack);



  TMultiGraph *tmg2 = new TMultiGraph();
  tmg2->Add(tge_syspospion);
  tmg2->Add(tge_sysnegpion);
  tmg2->Add(tge_sysposproton);
  tmg2->Add(tge_sysnegproton);
  tmg2->Add(tge_pospion);
  tmg2->Add(tge_negpion);
  tmg2->Add(tge_posproton);
  tmg2->Add(tge_negproton);
  tmg2->Add(ppgpion);
  tmg2->Add(ppgproton);
  tmg2->Add(ppgpion0);
  tmg2->Draw("apz");
  line->Draw("same");
  tmg2->SetMaximum(2.0);
  tmg2->SetMinimum(0.0);
  tmg2->GetXaxis()->SetLimits(0.0,6.0);
  tmg2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg2->GetYaxis()->SetTitle("R_{CP}");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->CenterTitle();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(kWhite);
  leg2->AddEntry(tge_pospion,"#pi^{+}","p");
  leg2->AddEntry(tge_negpion,"#pi^{-}","p");
  leg2->AddEntry(tge_posproton,"p","p");
  leg2->AddEntry(tge_negproton,"#bar{p}","p");
  leg2->Draw();

  TLegend *leg3 = new TLegend(0.18,0.68,0.38,0.88);
  leg3->SetBorderSize(0);
  leg3->SetFillColor(kWhite);
  leg3->AddEntry(ppgpion,"#pi Run2","p");
  leg3->AddEntry(ppgproton,"p Run2","p");
  leg3->AddEntry(ppgpion0,"#pi^{0} Run4","p");
  leg3->Draw();

  sprintf(figname,"regular/rcp_ppg_%d%d.gif",pionid,protonid);
  c1->Print(figname);
  sprintf(figname,"regular/rcp_ppg_%d%d.eps",pionid,protonid);
  c1->Print(figname);

  c1->Clear();

  tge_pospion_nq->SetMarkerColor(kRed);
  tge_negpion_nq->SetMarkerColor(kBlue);
  tge_posproton_nq->SetMarkerColor(kRed);
  tge_negproton_nq->SetMarkerColor(kBlue);

  tge_pospion_nq->SetMarkerStyle(kFullCircle);
  tge_negpion_nq->SetMarkerStyle(kFullCircle);
  tge_posproton_nq->SetMarkerStyle(kFullSquare);
  tge_negproton_nq->SetMarkerStyle(kFullSquare);

  tge_syspospion_nq->SetMarkerColor(kRed);
  tge_syspospion_nq->SetMarkerStyle(1);
  tge_syspospion_nq->SetLineColor(kRed-10);
  tge_syspospion_nq->SetLineWidth(15);
  tge_sysnegpion_nq->SetMarkerColor(kBlue);
  tge_sysnegpion_nq->SetMarkerStyle(1);
  tge_sysnegpion_nq->SetLineColor(kBlue-10);
  tge_sysnegpion_nq->SetLineWidth(15);

  tge_sysposproton_nq->SetMarkerColor(kRed);
  tge_sysposproton_nq->SetMarkerStyle(1);
  tge_sysposproton_nq->SetLineColor(kRed-10);
  tge_sysposproton_nq->SetLineWidth(15);
  tge_sysnegproton_nq->SetMarkerColor(kBlue);
  tge_sysnegproton_nq->SetMarkerStyle(1);
  tge_sysnegproton_nq->SetLineColor(kBlue-10);
  tge_sysnegproton_nq->SetLineWidth(15);

  TMultiGraph *tmg2 = new TMultiGraph();
  // tmg2->Add(tge_syspospion_nq);
  // tmg2->Add(tge_sysnegpion_nq);
  // tmg2->Add(tge_sysposproton_nq);
  // tmg2->Add(tge_sysnegproton_nq);
  tmg2->Add(tge_pospion_nq);
  //tmg2->Add(tge_negpion_nq);
  tmg2->Add(tge_posproton_nq);
  //tmg2->Add(tge_negproton_nq);
  tmg2->Draw("apz");
  tmg2->SetMaximum(2.0);
  tmg2->SetMinimum(0.0);
  tmg2->GetXaxis()->SetLimits(0.0,2.0);
  tmg2->GetXaxis()->SetTitle("p_{T}/n_{q} (GeV/c)");
  tmg2->GetYaxis()->SetTitle("R_{CP}");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->CenterTitle();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(kWhite);
  leg2->AddEntry(tge_pospion_nq,"#pi^{+}","p");
  //leg2->AddEntry(tge_negpion_nq,"#pi^{-}","p");
  leg2->AddEntry(tge_posproton_nq,"p","p");
  //leg2->AddEntry(tge_negproton_nq,"#bar{p}","p");
  leg2->Draw();

  sprintf(figname,"regular/rcp_nq_%d%d.gif",pionid,protonid);
  c1->Print(figname);
  sprintf(figname,"regular/rcp_nq_%d%d.eps",pionid,protonid);
  c1->Print(figname);



  c1->Clear();

  tge_pospion_NQ->SetMarkerColor(kRed);
  tge_negpion_NQ->SetMarkerColor(kBlue);
  tge_posproton_NQ->SetMarkerColor(kRed);
  tge_negproton_NQ->SetMarkerColor(kBlue);

  tge_pospion_NQ->SetMarkerStyle(kFullCircle);
  tge_negpion_NQ->SetMarkerStyle(kFullCircle);
  tge_posproton_NQ->SetMarkerStyle(kFullSquare);
  tge_negproton_NQ->SetMarkerStyle(kFullSquare);

  tge_syspospion_NQ->SetMarkerColor(kRed);
  tge_syspospion_NQ->SetMarkerStyle(1);
  tge_syspospion_NQ->SetLineColor(kRed-10);
  tge_syspospion_NQ->SetLineWidth(15);
  tge_sysnegpion_NQ->SetMarkerColor(kBlue);
  tge_sysnegpion_NQ->SetMarkerStyle(1);
  tge_sysnegpion_NQ->SetLineColor(kBlue-10);
  tge_sysnegpion_NQ->SetLineWidth(15);

  tge_sysposproton_NQ->SetMarkerColor(kRed);
  tge_sysposproton_NQ->SetMarkerStyle(1);
  tge_sysposproton_NQ->SetLineColor(kRed-10);
  tge_sysposproton_NQ->SetLineWidth(15);
  tge_sysnegproton_NQ->SetMarkerColor(kBlue);
  tge_sysnegproton_NQ->SetMarkerStyle(1);
  tge_sysnegproton_NQ->SetLineColor(kBlue-10);
  tge_sysnegproton_NQ->SetLineWidth(15);

  TMultiGraph *tmg2 = new TMultiGraph();
  // tmg2->Add(tge_syspospion_NQ);
  // tmg2->Add(tge_sysnegpion_NQ);
  // tmg2->Add(tge_sysposproton_NQ);
  // tmg2->Add(tge_sysnegproton_NQ);
  tmg2->Add(tge_pospion_NQ);
  //tmg2->Add(tge_negpion_NQ);
  tmg2->Add(tge_posproton_NQ);
  //tmg2->Add(tge_negproton_NQ);
  tmg2->Draw("apz");
  tmg2->SetMaximum(0.5);
  tmg2->SetMinimum(0.0);
  tmg2->GetXaxis()->SetLimits(0.0,2.0);
  tmg2->GetXaxis()->SetTitle("p_{T}/n_{q} (GeV/c)");
  tmg2->GetYaxis()->SetTitle("R_{CP}/n_{q}");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->CenterTitle();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(kWhite);
  leg2->AddEntry(tge_pospion_NQ,"#pi^{+}","p");
  //leg2->AddEntry(tge_negpion_NQ,"#pi^{-}","p");
  leg2->AddEntry(tge_posproton_NQ,"p","p");
  //leg2->AddEntry(tge_negproton_NQ,"#bar{p}","p");
  leg2->Draw();

  sprintf(figname,"regular/rcp_NQ_%d%d.gif",pionid,protonid);
  c1->Print(figname);
  sprintf(figname,"regular/rcp_NQ_%d%d.eps",pionid,protonid);
  c1->Print(figname);


  c1->Clear();
  delete c1;

}



void ppi()
{
  for(int i=0; i<5; i++)
    {
      doit(i,0,6);
      //doit(i,1,7); // 1 and 7 not available yet
    }
}

void doit(int centid=0, int pionid=0, int protonid=6)
{

  TCanvas *c1 = new TCanvas("c1","",800,600);

  char centstring[5];
  if(centid==0) sprintf(centstring,"0010");
  else if(centid==1) sprintf(centstring,"1020");
  else if(centid==2) sprintf(centstring,"2040");
  else if(centid==3) sprintf(centstring,"4060");
  else if(centid==4) sprintf(centstring,"6092");
  else {cout<<"you gonna die"<<endl; return;}

  TFile *flopm = TFile::Open("outlowpm.root");
  TFile *fhipm = TFile::Open("outhighpm.root");
  TFile *fpipm = TFile::Open("simpion_pm.root");
  TFile *fprpm = TFile::Open("simproton_pm.root");

  TFile *flomp = TFile::Open("outlowmp.root");
  TFile *fhimp = TFile::Open("outhighmp.root");
  TFile *fpimp = TFile::Open("simpion_mp.root");
  TFile *fprmp = TFile::Open("simproton_mp.root");

  char histname[100];

  // pos charge
  // pm field
  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",pionid,centstring);
  TH1F *hlo_pospion_pm = (TH1F *)flopm->Get(histname);
  TH1F *hhi_pospion_pm = (TH1F *)fhipm->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",protonid,centstring);
  TH1F *hlo_posproton_pm = (TH1F *)flopm->Get(histname);
  TH1F *hhi_posproton_pm = (TH1F *)fhipm->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis",pionid);
  TH1F *hss_pospion_pm = (TH1F *)fpipm->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis",protonid);
  TH1F *hss_posproton_pm = (TH1F *)fprpm->Get(histname);
  // mp field
  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",pionid,centstring);
  TH1F *hlo_pospion_mp = (TH1F *)flomp->Get(histname);
  TH1F *hhi_pospion_mp = (TH1F *)fhimp->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis_cent%s",protonid,centstring);
  TH1F *hlo_posproton_mp = (TH1F *)flomp->Get(histname);
  TH1F *hhi_posproton_mp = (TH1F *)fhimp->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis",pionid);
  TH1F *hss_pospion_mp = (TH1F *)fpimp->Get(histname);
  sprintf(histname,"ptpid_tofw_pos_%d_dis",protonid);
  TH1F *hss_posproton_mp = (TH1F *)fprmp->Get(histname);
  // neg charge
  // pm field
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",pionid,centstring);
  TH1F *hlo_negpion_pm = (TH1F *)flopm->Get(histname);
  TH1F *hhi_negpion_pm = (TH1F *)fhipm->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",protonid,centstring);
  TH1F *hlo_negproton_pm = (TH1F *)flopm->Get(histname);
  TH1F *hhi_negproton_pm = (TH1F *)fhipm->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis",pionid);
  TH1F *hss_negpion_pm = (TH1F *)fpipm->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis",protonid);
  TH1F *hss_negproton_pm = (TH1F *)fprpm->Get(histname);
  // mp field
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",pionid,centstring);
  TH1F *hlo_negpion_mp = (TH1F *)flomp->Get(histname);
  TH1F *hhi_negpion_mp = (TH1F *)fhimp->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis_cent%s",protonid,centstring);
  TH1F *hlo_negproton_mp = (TH1F *)flomp->Get(histname);
  TH1F *hhi_negproton_mp = (TH1F *)fhimp->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis",pionid);
  TH1F *hss_negpion_mp = (TH1F *)fpimp->Get(histname);
  sprintf(histname,"ptpid_tofw_neg_%d_dis",protonid);
  TH1F *hss_negproton_mp = (TH1F *)fprmp->Get(histname);

  // sumw2
  hlo_pospion_pm->Sumw2();
  hhi_pospion_pm->Sumw2();
  hss_pospion_pm->Sumw2();
  hlo_pospion_mp->Sumw2();
  hhi_pospion_mp->Sumw2();
  hss_pospion_mp->Sumw2();
  hlo_negpion_pm->Sumw2();
  hhi_negpion_pm->Sumw2();
  hss_negpion_pm->Sumw2();
  hlo_negpion_mp->Sumw2();
  hhi_negpion_mp->Sumw2();
  hss_negpion_mp->Sumw2();
  hlo_posproton_pm->Sumw2();
  hhi_posproton_pm->Sumw2();
  hss_posproton_pm->Sumw2();
  hlo_posproton_mp->Sumw2();
  hhi_posproton_mp->Sumw2();
  hss_posproton_mp->Sumw2();
  hlo_negproton_pm->Sumw2();
  hhi_negproton_pm->Sumw2();
  hss_negproton_pm->Sumw2();
  hlo_negproton_mp->Sumw2();
  hhi_negproton_mp->Sumw2();
  hss_negproton_mp->Sumw2();

  // add fields
  hlo_pospion_pm->Add(hlo_pospion_mp);
  hhi_pospion_pm->Add(hhi_pospion_mp);
  hss_pospion_pm->Add(hss_pospion_mp);
  hlo_negpion_pm->Add(hlo_negpion_mp);
  hhi_negpion_pm->Add(hhi_negpion_mp);
  hss_negpion_pm->Add(hss_negpion_mp);
  hlo_posproton_pm->Add(hlo_posproton_mp);
  hhi_posproton_pm->Add(hhi_posproton_mp);
  hss_posproton_pm->Add(hss_posproton_mp);
  hlo_negproton_pm->Add(hlo_negproton_mp);
  hhi_negproton_pm->Add(hhi_negproton_mp);
  hss_negproton_pm->Add(hss_negproton_mp);

  // real/sim division
  hlo_pospion_pm->Divide(hss_pospion_pm);
  hhi_pospion_pm->Divide(hss_pospion_pm);
  hlo_negpion_pm->Divide(hss_negpion_pm);
  hhi_negpion_pm->Divide(hss_negpion_pm);
  hlo_posproton_pm->Divide(hss_posproton_pm);
  hhi_posproton_pm->Divide(hss_posproton_pm);
  hlo_negproton_pm->Divide(hss_negproton_pm);
  hhi_negproton_pm->Divide(hss_negproton_pm);

  // feeddown correction for protons
  TF1 *funfeedpr = new TF1("funfeedpr","1.0-expo(0)+pol0(2)",0.0,10.0);
  funfeedpr->SetParameter(0,-0.84);
  funfeedpr->SetParameter(1,-0.74);
  funfeedpr->SetParameter(2, 0.08);
  TF1 *funfeedpb = new TF1("funfeedpb","1.0-expo(0)+pol0(2)",0.0,10.0); // make same for now
  funfeedpb->SetParameter(0,-0.84);
  funfeedpb->SetParameter(1,-0.74);
  funfeedpb->SetParameter(2, 0.08);
  hlo_posproton_pm->Multiply(funfeedpr,1.0);
  hhi_posproton_pm->Multiply(funfeedpr,1.0);
  hlo_negproton_pm->Multiply(funfeedpb,1.0);
  hhi_negproton_pm->Multiply(funfeedpb,1.0);

  // p/pi division
  hlo_posproton_pm->Divide(hlo_pospion_pm);
  hhi_posproton_pm->Divide(hhi_pospion_pm);
  hlo_negproton_pm->Divide(hlo_negpion_pm);
  hhi_negproton_pm->Divide(hhi_negpion_pm);

  // rebin by 5 for hi
  TF1 *fun = new TF1("fun","pol0",0,10);
  fun->SetParameter(0,1);
  hhi_posproton_pm->Rebin(5);
  hhi_posproton_pm->Divide(fun,5.0);
  hhi_negproton_pm->Rebin(5);
  hhi_negproton_pm->Divide(fun,5.0);




  // -------------------------------------- //
  // --- now do arrays and TGraphErrors --- //
  // -------------------------------------- //

  float pt[36], ept[36];
  float posratio[36], negratio[36];
  float eposratio[36], enegratio[36];
  float esysposratio[36], esysnegratio[36];

  for(int i=0; i<30; i++)
    {
      pt[i] = hlo_posproton_pm->GetBinCenter(i+1);
      ept[i] = 0;
      posratio[i] = hlo_posproton_pm->GetBinContent(i+1);
      eposratio[i] = hlo_posproton_pm->GetBinError(i+1);
      negratio[i] = hlo_negproton_pm->GetBinContent(i+1);
      enegratio[i] = hlo_negproton_pm->GetBinError(i+1);
      esysposratio[i] = posratio[i]*0.1; // 10% sys uncert
      esysnegratio[i] = negratio[i]*0.1; // 10% sys uncert
    }
  for(int i=0; i<6; i++)
    {
      pt[i+30] = hhi_posproton_pm->GetBinCenter(i+7);
      ept[i+30] = 0;
      posratio[i+30] = hhi_posproton_pm->GetBinContent(i+7);
      eposratio[i+30] = hhi_posproton_pm->GetBinError(i+7);
      negratio[i+30] = hhi_negproton_pm->GetBinContent(i+7);
      enegratio[i+30] = hhi_negproton_pm->GetBinError(i+7);
      esysposratio[i+30] = posratio[i+30]*0.1; // 10% sys uncert
      esysnegratio[i+30] = negratio[i+30]*0.1; // 10% sys uncert
    }
  for(int i=0; i<5; i++)
    {
      posratio[i]=-9;
      negratio[i]=-9;
    }

  TGraphErrors *tge_pos = new TGraphErrors(36,pt,posratio,ept,eposratio);
  tge_pos->SetMarkerColor(kRed);
  tge_pos->SetMarkerStyle(kFullSquare);
  TGraphErrors *tge_neg = new TGraphErrors(36,pt,negratio,ept,enegratio);
  tge_neg->SetMarkerColor(kBlue);
  tge_neg->SetMarkerStyle(kFullSquare);

  TGraphErrors *tge_syspos = new TGraphErrors(36,pt,posratio,ept,esysposratio);
  tge_syspos->SetMarkerColor(kRed);
  tge_syspos->SetMarkerStyle(1);
  tge_syspos->SetLineColor(kRed-10);
  tge_syspos->SetLineWidth(15);
  TGraphErrors *tge_sysneg = new TGraphErrors(36,pt,negratio,ept,esysnegratio);
  tge_sysneg->SetMarkerColor(kBlue);
  tge_sysneg->SetMarkerStyle(1);
  tge_sysneg->SetLineColor(kBlue-10);
  tge_sysneg->SetLineWidth(15);

  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tge_sysneg);
  tmg->Add(tge_syspos);
  tmg->Add(tge_neg);
  tmg->Add(tge_pos);
  tmg->Draw("apz");
  //tmg->SetMaximum(1.4);
  tmg->SetMaximum(1.6); // 1.4 is fine but this is for comparisons...
  tmg->SetMinimum(0.0);
  tmg->GetXaxis()->SetLimits(0.0,6.0);
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetXaxis()->CenterTitle();
  tmg->GetYaxis()->SetTitle("p/#pi ratio");
  tmg->GetYaxis()->CenterTitle();

  TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->AddEntry(tge_pos,"p/#pi^{+}","p");
  leg->AddEntry(tge_neg,"#bar{p}/#pi^{-}","p");
  leg->Draw();

  char figname[100];
  sprintf(figname,"special/ppi_%d%d_cent%s.gif",pionid,protonid,centstring);
  c1->Print(figname);
  sprintf(figname,"special/ppi_%d%d_cent%s.eps",pionid,protonid,centstring);
  c1->Print(figname);



  c1->Clear();
  //c1->Delete();
  delete c1;

}

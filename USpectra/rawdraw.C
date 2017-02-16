void rawdraw()
{

  cout<<"starting!"<<endl;

  TCanvas *c1 = new TCanvas();
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->SetLogy();

  TFile *file = TFile::Open("outsum_low.root");
  //TFile *fpp = TFile::Open("outlow_plusplus.root");
  //TFile *fmm = TFile::Open("outlow_minusminus.root");

  float pt[100], ept[100], yield[100], eyield[100];
  //Double_t pt[100], ept[100], yield[100], eyield[100];



  // --- pions --- //

  // --------
  // --- dis0 

  //TH1F *hposdis0 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis");
  TH1F *hposdis0cent0005 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis_cent0005");
  TH1F *hposdis0cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis_cent2040");
  TH1F *hposdis0cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis_cent4060");
  TH1F *hposdis0cent5088 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis_cent5088");

  //TH1F *hnegdis0 = (TH1F *)file->Get("ptpid_tofw_neg_0_dis");
  TH1F *hnegdis0cent0005 = (TH1F *)file->Get("ptpid_tofw_neg_0_dis_cent0005");
  TH1F *hnegdis0cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_0_dis_cent2040");
  TH1F *hnegdis0cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_0_dis_cent4060");
  TH1F *hnegdis0cent5088 = (TH1F *)file->Get("ptpid_tofw_neg_0_dis_cent5088");

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis0cent0005->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis0cent0005->GetBinContent(i+1);
      eyield[i] = hposdis0cent0005->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis0cent0005 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis0cent2040->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis0cent2040->GetBinContent(i+1);
      eyield[i] = hposdis0cent2040->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis0cent2040 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis0cent4060->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis0cent4060->GetBinContent(i+1);
      eyield[i] = hposdis0cent4060->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis0cent4060 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis0cent5088->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis0cent5088->GetBinContent(i+1);
      eyield[i] = hposdis0cent5088->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis0cent5088 = new TGraphErrors(100,pt,yield,ept,eyield);


  for(int i=0; i<100; i++)
    {
      pt[i] = hnegdis0cent0005->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hnegdis0cent0005->GetBinContent(i+1);
      eyield[i] = hnegdis0cent0005->GetBinError(i+1);
    }
  TGraphErrors *tge_negdis0cent0005 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hnegdis0cent2040->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hnegdis0cent2040->GetBinContent(i+1);
      eyield[i] = hnegdis0cent2040->GetBinError(i+1);
    }
  TGraphErrors *tge_negdis0cent2040 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hnegdis0cent4060->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hnegdis0cent4060->GetBinContent(i+1);
      eyield[i] = hnegdis0cent4060->GetBinError(i+1);
    }
  TGraphErrors *tge_negdis0cent4060 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hnegdis0cent5088->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hnegdis0cent5088->GetBinContent(i+1);
      eyield[i] = hnegdis0cent5088->GetBinError(i+1);
    }
  TGraphErrors *tge_negdis0cent5088 = new TGraphErrors(100,pt,yield,ept,eyield);





  // --------
  // --- dis1

  //TH1F *hposdis1 = (TH1F *)file->Get("ptpid_tofw_pos_1_dis");
  TH1F *hposdis1cent0005 = (TH1F *)file->Get("ptpid_tofw_pos_1_dis_cent0005");
  TH1F *hposdis1cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_1_dis_cent2040");
  TH1F *hposdis1cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_1_dis_cent4060");
  TH1F *hposdis1cent5088 = (TH1F *)file->Get("ptpid_tofw_pos_1_dis_cent5088");

  //TH1F *hnegdis1 = (TH1F *)file->Get("ptpid_tofw_neg_1_dis");
  TH1F *hnegdis1cent0005 = (TH1F *)file->Get("ptpid_tofw_neg_1_dis_cent0005");
  TH1F *hnegdis1cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_1_dis_cent2040");
  TH1F *hnegdis1cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_1_dis_cent4060");
  TH1F *hnegdis1cent5088 = (TH1F *)file->Get("ptpid_tofw_neg_1_dis_cent5088");

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis1cent0005->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis1cent0005->GetBinContent(i+1);
      eyield[i] = hposdis1cent0005->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis1cent0005 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis1cent2040->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis1cent2040->GetBinContent(i+1);
      eyield[i] = hposdis1cent2040->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis1cent2040 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis1cent4060->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis1cent4060->GetBinContent(i+1);
      eyield[i] = hposdis1cent4060->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis1cent4060 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis1cent5088->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis1cent5088->GetBinContent(i+1);
      eyield[i] = hposdis1cent5088->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis1cent5088 = new TGraphErrors(100,pt,yield,ept,eyield);

  // ---

  tge_posdis0cent0005->SetMarkerStyle(21);
  tge_posdis0cent0005->SetMarkerColor(kBlack);
  tge_posdis1cent0005->SetMarkerStyle(22);
  tge_posdis1cent0005->SetMarkerColor(kRed);

  TMultiGraph *tmg_pion_cent0005 = new TMultiGraph();
  tmg_pion_cent0005->Add(tge_posdis0cent0005);
  tmg_pion_cent0005->Add(tge_posdis1cent0005);
  tmg_pion_cent0005->Draw("ap");
  tmg_pion_cent0005->SetMaximum(5e6);
  tmg_pion_cent0005->SetMinimum(1e-1);
  tmg_pion_cent0005->GetXaxis()->SetLimits(0.0,7.0);
  tmg_pion_cent0005->GetXaxis()->SetTitle("p_{T} GeV/c");
  tmg_pion_cent0005->GetXaxis()->CenterTitle();
  tmg_pion_cent0005->GetYaxis()->SetTitle("Uncorrected Yield");
  tmg_pion_cent0005->GetYaxis()->CenterTitle();

  TLegend *leg_pion_cent0005 = new TLegend(0.68,0.68,0.88,0.88);
  leg_pion_cent0005->SetFillColor(kWhite);
  leg_pion_cent0005->SetBorderSize(0);
  leg_pion_cent0005->AddEntry(tge_posdis0cent0005,"sym","p");
  leg_pion_cent0005->AddEntry(tge_posdis1cent0005,"asym","p");
  leg_pion_cent0005->Draw();

  c1->Print("pioncent0005.gif");
  c1->Print("pioncent0005.eps");

  c1->Clear();

  tge_posdis0cent5088->SetMarkerStyle(21);
  tge_posdis0cent5088->SetMarkerColor(kBlack);
  tge_posdis1cent5088->SetMarkerStyle(22);
  tge_posdis1cent5088->SetMarkerColor(kRed);

  TMultiGraph *tmg_pion_cent5088 = new TMultiGraph();
  tmg_pion_cent5088->Add(tge_posdis0cent5088);
  tmg_pion_cent5088->Add(tge_posdis1cent5088);
  tmg_pion_cent5088->Draw("ap");
  tmg_pion_cent5088->SetMaximum(5e6);
  tmg_pion_cent5088->SetMinimum(1e-1);
  tmg_pion_cent5088->GetXaxis()->SetLimits(0.0,7.0);
  tmg_pion_cent5088->GetXaxis()->SetTitle("p_{T} GeV/c");
  tmg_pion_cent5088->GetXaxis()->CenterTitle();
  tmg_pion_cent5088->GetYaxis()->SetTitle("Uncorrected Yield");
  tmg_pion_cent5088->GetYaxis()->CenterTitle();

  TLegend *leg_pion_cent5088 = new TLegend(0.68,0.68,0.88,0.88);
  leg_pion_cent5088->SetFillColor(kWhite);
  leg_pion_cent5088->SetBorderSize(0);
  leg_pion_cent5088->AddEntry(tge_posdis0cent5088,"sym","p");
  leg_pion_cent5088->AddEntry(tge_posdis1cent5088,"asym","p");
  leg_pion_cent5088->Draw();

  c1->Print("pioncent5088.gif");
  c1->Print("pioncent5088.eps");

  c1->Clear();

  // --- kaons --- //

  // --------
  // --- dis2

  //TH1F *hposdis2 = (TH1F *)file->Get("ptpid_tofw_pos_2_dis");
  TH1F *hposdis2cent0005 = (TH1F *)file->Get("ptpid_tofw_pos_2_dis_cent0005");
  TH1F *hposdis2cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_2_dis_cent2040");
  TH1F *hposdis2cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_2_dis_cent4060");
  TH1F *hposdis2cent5088 = (TH1F *)file->Get("ptpid_tofw_pos_2_dis_cent5088");

  //TH1F *hnegdis2 = (TH1F *)file->Get("ptpid_tofw_neg_2_dis");
  TH1F *hnegdis2cent0005 = (TH1F *)file->Get("ptpid_tofw_neg_2_dis_cent0005");
  TH1F *hnegdis2cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_2_dis_cent2040");
  TH1F *hnegdis2cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_2_dis_cent4060");
  TH1F *hnegdis2cent5088 = (TH1F *)file->Get("ptpid_tofw_neg_2_dis_cent5088");

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis2cent0005->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis2cent0005->GetBinContent(i+1);
      eyield[i] = hposdis2cent0005->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis2cent0005 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis2cent2040->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis2cent2040->GetBinContent(i+1);
      eyield[i] = hposdis2cent2040->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis2cent2040 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis2cent4060->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis2cent4060->GetBinContent(i+1);
      eyield[i] = hposdis2cent4060->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis2cent4060 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis2cent5088->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis2cent5088->GetBinContent(i+1);
      eyield[i] = hposdis2cent5088->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis2cent5088 = new TGraphErrors(100,pt,yield,ept,eyield);



  // --------
  // --- dis3

  //TH1F *hposdis3 = (TH1F *)file->Get("ptpid_tofw_pos_3_dis");
  TH1F *hposdis3cent0005 = (TH1F *)file->Get("ptpid_tofw_pos_3_dis_cent0005");
  TH1F *hposw1dis3cent0005 = (TH1F *)file->Get("ptpid_tofw_w1_pos_3_dis_cent0005");
  TH1F *hposw2dis3cent0005 = (TH1F *)file->Get("ptpid_tofw_w2_pos_3_dis_cent0005");
  TH1F *hposdis3cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_3_dis_cent2040");
  TH1F *hposw1dis3cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_pos_3_dis_cent2040");
  TH1F *hposw2dis3cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_pos_3_dis_cent2040");
  TH1F *hposdis3cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_3_dis_cent4060");
  TH1F *hposw1dis3cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_pos_3_dis_cent4060");
  TH1F *hposw2dis3cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_pos_3_dis_cent4060");
  TH1F *hposdis3cent5088 = (TH1F *)file->Get("ptpid_tofw_pos_3_dis_cent5088");
  TH1F *hposw1dis3cent5088 = (TH1F *)file->Get("ptpid_tofw_w1_pos_3_dis_cent5088");
  TH1F *hposw2dis3cent5088 = (TH1F *)file->Get("ptpid_tofw_w2_pos_3_dis_cent5088");

  //TH1F *hnegdis3 = (TH1F *)file->Get("ptpid_tofw_neg_3_dis");
  TH1F *hnegdis3cent0005 = (TH1F *)file->Get("ptpid_tofw_neg_3_dis_cent0005");
  TH1F *hnegw1dis3cent0005 = (TH1F *)file->Get("ptpid_tofw_w1_neg_3_dis_cent0005");
  TH1F *hnegw2dis3cent0005 = (TH1F *)file->Get("ptpid_tofw_w2_neg_3_dis_cent0005");
  TH1F *hnegdis3cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_3_dis_cent2040");
  TH1F *hnegw1dis3cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_neg_3_dis_cent2040");
  TH1F *hnegw2dis3cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_neg_3_dis_cent2040");
  TH1F *hnegdis3cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_3_dis_cent4060");
  TH1F *hnegw1dis3cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_neg_3_dis_cent4060");
  TH1F *hnegw2dis3cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_neg_3_dis_cent4060");
  TH1F *hnegdis3cent5088 = (TH1F *)file->Get("ptpid_tofw_neg_3_dis_cent5088");
  TH1F *hnegw1dis3cent5088 = (TH1F *)file->Get("ptpid_tofw_w1_neg_3_dis_cent5088");
  TH1F *hnegw2dis3cent5088 = (TH1F *)file->Get("ptpid_tofw_w2_neg_3_dis_cent5088");

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis3cent0005->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis3cent0005->GetBinContent(i+1);
      eyield[i] = hposdis3cent0005->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis3cent0005 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis3cent2040->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis3cent2040->GetBinContent(i+1);
      eyield[i] = hposdis3cent2040->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis3cent2040 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis3cent4060->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis3cent4060->GetBinContent(i+1);
      eyield[i] = hposdis3cent4060->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis3cent4060 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis3cent5088->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis3cent5088->GetBinContent(i+1);
      eyield[i] = hposdis3cent5088->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis3cent5088 = new TGraphErrors(100,pt,yield,ept,eyield);



  tge_posdis2cent0005->SetMarkerStyle(21);
  tge_posdis2cent0005->SetMarkerColor(kBlack);
  tge_posdis3cent0005->SetMarkerStyle(22);
  tge_posdis3cent0005->SetMarkerColor(kRed);

  TMultiGraph *tmg_kaon_cent0005 = new TMultiGraph();
  tmg_kaon_cent0005->Add(tge_posdis2cent0005);
  tmg_kaon_cent0005->Add(tge_posdis3cent0005);
  tmg_kaon_cent0005->Draw("ap");
  tmg_kaon_cent0005->SetMaximum(5e6);
  tmg_kaon_cent0005->SetMinimum(1e-1);
  tmg_kaon_cent0005->GetXaxis()->SetLimits(0.0,7.0);
  tmg_kaon_cent0005->GetXaxis()->SetTitle("p_{T} GeV/c");
  tmg_kaon_cent0005->GetXaxis()->CenterTitle();
  tmg_kaon_cent0005->GetYaxis()->SetTitle("Uncorrected Yield");
  tmg_kaon_cent0005->GetYaxis()->CenterTitle();

  TLegend *leg_kaon_cent0005 = new TLegend(0.68,0.68,0.88,0.88);
  leg_kaon_cent0005->SetFillColor(kWhite);
  leg_kaon_cent0005->SetBorderSize(0);
  leg_kaon_cent0005->AddEntry(tge_posdis2cent0005,"sym","p");
  leg_kaon_cent0005->AddEntry(tge_posdis3cent0005,"asym","p");
  leg_kaon_cent0005->Draw();

  c1->Print("kaoncent0005.gif");
  c1->Print("kaoncent0005.eps");

  c1->Clear();

  tge_posdis2cent5088->SetMarkerStyle(21);
  tge_posdis2cent5088->SetMarkerColor(kBlack);
  tge_posdis3cent5088->SetMarkerStyle(22);
  tge_posdis3cent5088->SetMarkerColor(kRed);

  TMultiGraph *tmg_kaon_cent5088 = new TMultiGraph();
  tmg_kaon_cent5088->Add(tge_posdis2cent5088);
  tmg_kaon_cent5088->Add(tge_posdis3cent5088);
  tmg_kaon_cent5088->Draw("ap");
  tmg_kaon_cent5088->SetMaximum(5e6);
  tmg_kaon_cent5088->SetMinimum(1e-1);
  tmg_kaon_cent5088->GetXaxis()->SetLimits(0.0,7.0);
  tmg_kaon_cent5088->GetXaxis()->SetTitle("p_{T} GeV/c");
  tmg_kaon_cent5088->GetXaxis()->CenterTitle();
  tmg_kaon_cent5088->GetYaxis()->SetTitle("Uncorrected Yield");
  tmg_kaon_cent5088->GetYaxis()->CenterTitle();

  TLegend *leg_kaon_cent5088 = new TLegend(0.68,0.68,0.88,0.88);
  leg_kaon_cent5088->SetFillColor(kWhite);
  leg_kaon_cent5088->SetBorderSize(0);
  leg_kaon_cent5088->AddEntry(tge_posdis2cent5088,"sym","p");
  leg_kaon_cent5088->AddEntry(tge_posdis3cent5088,"asym","p");
  leg_kaon_cent5088->Draw();

  c1->Print("kaoncent5088.gif");
  c1->Print("kaoncent5088.eps");

  c1->Clear();



  // --- protons --- //

  // --------
  // --- dis4

  //TH1F *hposdis4 = (TH1F *)file->Get("ptpid_tofw_pos_4_dis");
  TH1F *hposdis4cent0005 = (TH1F *)file->Get("ptpid_tofw_pos_4_dis_cent0005");
  TH1F *hposdis4cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_4_dis_cent2040");
  TH1F *hposdis4cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_4_dis_cent4060");
  TH1F *hposdis4cent5088 = (TH1F *)file->Get("ptpid_tofw_pos_4_dis_cent5088");

  //TH1F *hnegdis4 = (TH1F *)file->Get("ptpid_tofw_neg_4_dis");
  TH1F *hnegdis4cent0005 = (TH1F *)file->Get("ptpid_tofw_neg_4_dis_cent0005");
  TH1F *hnegdis4cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_4_dis_cent2040");
  TH1F *hnegdis4cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_4_dis_cent4060");
  TH1F *hnegdis4cent5088 = (TH1F *)file->Get("ptpid_tofw_neg_4_dis_cent5088");

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis4cent0005->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis4cent0005->GetBinContent(i+1);
      eyield[i] = hposdis4cent0005->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis4cent0005 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis4cent2040->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis4cent2040->GetBinContent(i+1);
      eyield[i] = hposdis4cent2040->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis4cent2040 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis4cent4060->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis4cent4060->GetBinContent(i+1);
      eyield[i] = hposdis4cent4060->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis4cent4060 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis4cent5088->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis4cent5088->GetBinContent(i+1);
      eyield[i] = hposdis4cent5088->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis4cent5088 = new TGraphErrors(100,pt,yield,ept,eyield);



  // --------
  // --- dis5

  //TH1F *hposdis5 = (TH1F *)file->Get("ptpid_tofw_pos_5_dis");
  TH1F *hposdis5cent0005 = (TH1F *)file->Get("ptpid_tofw_pos_5_dis_cent0005");
  TH1F *hposdis5cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_5_dis_cent2040");
  TH1F *hposdis5cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_5_dis_cent4060");
  TH1F *hposdis5cent5088 = (TH1F *)file->Get("ptpid_tofw_pos_5_dis_cent5088");

  //TH1F *hnegdis5 = (TH1F *)file->Get("ptpid_tofw_neg_5_dis");
  TH1F *hnegdis5cent0005 = (TH1F *)file->Get("ptpid_tofw_neg_5_dis_cent0005");
  TH1F *hnegdis5cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_5_dis_cent2040");
  TH1F *hnegdis5cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_5_dis_cent4060");
  TH1F *hnegdis5cent5088 = (TH1F *)file->Get("ptpid_tofw_neg_5_dis_cent5088");

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis5cent0005->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis5cent0005->GetBinContent(i+1);
      eyield[i] = hposdis5cent0005->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis5cent0005 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis5cent2040->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis5cent2040->GetBinContent(i+1);
      eyield[i] = hposdis5cent2040->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis5cent2040 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis5cent4060->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis5cent4060->GetBinContent(i+1);
      eyield[i] = hposdis5cent4060->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis5cent4060 = new TGraphErrors(100,pt,yield,ept,eyield);

  for(int i=0; i<100; i++)
    {
      pt[i] = hposdis5cent5088->GetBinCenter(i+1);
      ept[i] = 0.0;
      yield[i] = hposdis5cent5088->GetBinContent(i+1);
      eyield[i] = hposdis5cent5088->GetBinError(i+1);
    }
  TGraphErrors *tge_posdis5cent5088 = new TGraphErrors(100,pt,yield,ept,eyield);




  tge_posdis4cent0005->SetMarkerStyle(21);
  tge_posdis4cent0005->SetMarkerColor(kBlack);
  tge_posdis5cent0005->SetMarkerStyle(22);
  tge_posdis5cent0005->SetMarkerColor(kRed);

  TMultiGraph *tmg_proton_cent0005 = new TMultiGraph();
  tmg_proton_cent0005->Add(tge_posdis4cent0005);
  tmg_proton_cent0005->Add(tge_posdis5cent0005);
  tmg_proton_cent0005->Draw("ap");
  tmg_proton_cent0005->SetMaximum(5e6);
  tmg_proton_cent0005->SetMinimum(1e-1);
  tmg_proton_cent0005->GetXaxis()->SetLimits(0.0,7.0);
  tmg_proton_cent0005->GetXaxis()->SetTitle("p_{T} GeV/c");
  tmg_proton_cent0005->GetXaxis()->CenterTitle();
  tmg_proton_cent0005->GetYaxis()->SetTitle("Uncorrected Yield");
  tmg_proton_cent0005->GetYaxis()->CenterTitle();

  TLegend *leg_proton_cent0005 = new TLegend(0.68,0.68,0.88,0.88);
  leg_proton_cent0005->SetFillColor(kWhite);
  leg_proton_cent0005->SetBorderSize(0);
  leg_proton_cent0005->AddEntry(tge_posdis4cent0005,"sym","p");
  leg_proton_cent0005->AddEntry(tge_posdis5cent0005,"asym","p");
  leg_proton_cent0005->Draw();

  c1->Print("protoncent0005.gif");
  c1->Print("protoncent0005.eps");

  c1->Clear();

  tge_posdis4cent5088->SetMarkerStyle(21);
  tge_posdis4cent5088->SetMarkerColor(kBlack);
  tge_posdis5cent5088->SetMarkerStyle(22);
  tge_posdis5cent5088->SetMarkerColor(kRed);

  TMultiGraph *tmg_proton_cent5088 = new TMultiGraph();
  tmg_proton_cent5088->Add(tge_posdis4cent5088);
  tmg_proton_cent5088->Add(tge_posdis5cent5088);
  tmg_proton_cent5088->Draw("ap");
  tmg_proton_cent5088->SetMaximum(5e6);
  tmg_proton_cent5088->SetMinimum(1e-1);
  tmg_proton_cent5088->GetXaxis()->SetLimits(0.0,7.0);
  tmg_proton_cent5088->GetXaxis()->SetTitle("p_{T} GeV/c");
  tmg_proton_cent5088->GetXaxis()->CenterTitle();
  tmg_proton_cent5088->GetYaxis()->SetTitle("Uncorrected Yield");
  tmg_proton_cent5088->GetYaxis()->CenterTitle();

  TLegend *leg_proton_cent5088 = new TLegend(0.68,0.68,0.88,0.88);
  leg_proton_cent5088->SetFillColor(kWhite);
  leg_proton_cent5088->SetBorderSize(0);
  leg_proton_cent5088->AddEntry(tge_posdis4cent5088,"sym","p");
  leg_proton_cent5088->AddEntry(tge_posdis5cent5088,"asym","p");
  leg_proton_cent5088->Draw();

  c1->Print("protoncent5088.gif");
  c1->Print("protoncent5088.eps");

  c1->Clear();



}



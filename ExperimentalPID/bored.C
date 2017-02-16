void bored()
{

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetLogy();

  TF1 *fun = new TF1("fun","pol1",0,10);
  fun->SetParameter(0,0);
  fun->SetParameter(1,1);

  TFile *freal = TFile::Open("outnew_pp.root");
  TFile *fsimpi =  TFile::Open("simpion_pp.root");
  TFile *fsimka =  TFile::Open("simkaon_pp.root");
  TFile *fsimpr =  TFile::Open("simproton_pp.root");

  TH1F *hreal_pion_0 = (TH1F *)freal->Get("testpid_tofw_pionpos_0_dis");
  TH1F *hreal_pion_1 = (TH1F *)freal->Get("testpid_tofw_pionpos_1_dis");
  TH1F *hreal_pion_2 = (TH1F *)freal->Get("testpid_tofw_pionpos_2_dis");
  TH1F *hreal_pion_3 = (TH1F *)freal->Get("testpid_tofw_pionpos_3_dis");
  TH1F *hreal_pion_4 = (TH1F *)freal->Get("testpid_tofw_pionpos_4_dis");
  //TH1F *hreal_pion_5 = (TH1F *)freal->Get("testpid_tofw_pionpos_5_dis");

  TH1F *hreal_kaon_0 = (TH1F *)freal->Get("testpid_tofw_kaonpos_0_dis");
  TH1F *hreal_kaon_1 = (TH1F *)freal->Get("testpid_tofw_kaonpos_1_dis");
  TH1F *hreal_kaon_2 = (TH1F *)freal->Get("testpid_tofw_kaonpos_2_dis");
  TH1F *hreal_kaon_3 = (TH1F *)freal->Get("testpid_tofw_kaonpos_3_dis");
  TH1F *hreal_kaon_4 = (TH1F *)freal->Get("testpid_tofw_kaonpos_4_dis");
  //TH1F *hreal_kaon_5 = (TH1F *)freal->Get("testpid_tofw_kaonpos_5_dis");

  TH1F *hreal_proton_0 = (TH1F *)freal->Get("testpid_tofw_protonpos_0_dis");
  TH1F *hreal_proton_1 = (TH1F *)freal->Get("testpid_tofw_protonpos_1_dis");
  TH1F *hreal_proton_2 = (TH1F *)freal->Get("testpid_tofw_protonpos_2_dis");
  TH1F *hreal_proton_3 = (TH1F *)freal->Get("testpid_tofw_protonpos_3_dis");
  TH1F *hreal_proton_4 = (TH1F *)freal->Get("testpid_tofw_protonpos_4_dis");
  //TH1F *hreal_proton_5 = (TH1F *)freal->Get("testpid_tofw_protonpos_5_dis");

  TH1F *hsim_pion_0 = (TH1F *)fsimpi->Get("testpid_tofw_pionpos_0_dis");
  TH1F *hsim_pion_1 = (TH1F *)fsimpi->Get("testpid_tofw_pionpos_1_dis");
  TH1F *hsim_pion_2 = (TH1F *)fsimpi->Get("testpid_tofw_pionpos_2_dis");
  TH1F *hsim_pion_3 = (TH1F *)fsimpi->Get("testpid_tofw_pionpos_3_dis");
  TH1F *hsim_pion_4 = (TH1F *)fsimpi->Get("testpid_tofw_pionpos_4_dis");
  //TH1F *hsim_pion_5 = (TH1F *)fsimpi->Get("testpid_tofw_pionpos_5_dis");

  TH1F *hsim_kaon_0 = (TH1F *)fsimka->Get("testpid_tofw_kaonpos_0_dis");
  TH1F *hsim_kaon_1 = (TH1F *)fsimka->Get("testpid_tofw_kaonpos_1_dis");
  TH1F *hsim_kaon_2 = (TH1F *)fsimka->Get("testpid_tofw_kaonpos_2_dis");
  TH1F *hsim_kaon_3 = (TH1F *)fsimka->Get("testpid_tofw_kaonpos_3_dis");
  TH1F *hsim_kaon_4 = (TH1F *)fsimka->Get("testpid_tofw_kaonpos_4_dis");
  //TH1F *hsim_kaon_5 = (TH1F *)fsimka->Get("testpid_tofw_kaonpos_5_dis");

  TH1F *hsim_proton_0 = (TH1F *)fsimpr->Get("testpid_tofw_protonpos_0_dis");
  TH1F *hsim_proton_1 = (TH1F *)fsimpr->Get("testpid_tofw_protonpos_1_dis");
  TH1F *hsim_proton_2 = (TH1F *)fsimpr->Get("testpid_tofw_protonpos_2_dis");
  TH1F *hsim_proton_3 = (TH1F *)fsimpr->Get("testpid_tofw_protonpos_3_dis");
  TH1F *hsim_proton_4 = (TH1F *)fsimpr->Get("testpid_tofw_protonpos_4_dis");
  //TH1F *hsim_proton_5 = (TH1F *)fsimpr->Get("testpid_tofw_protonpos_5_dis");

  hreal_pion_0->Sumw2();
  hreal_pion_1->Sumw2();
  hreal_pion_2->Sumw2();
  hreal_pion_3->Sumw2();
  hreal_pion_4->Sumw2();
  //hreal_pion_5->Sumw2();

  hreal_kaon_0->Sumw2();
  hreal_kaon_1->Sumw2();
  hreal_kaon_2->Sumw2();
  hreal_kaon_3->Sumw2();
  hreal_kaon_4->Sumw2();
  //hreal_kaon_5->Sumw2();

  hreal_proton_0->Sumw2();
  hreal_proton_1->Sumw2();
  hreal_proton_2->Sumw2();
  hreal_proton_3->Sumw2();
  hreal_proton_4->Sumw2();
  //hreal_proton_5->Sumw2();

  hsim_pion_0->Sumw2();
  hsim_pion_1->Sumw2();
  hsim_pion_2->Sumw2();
  hsim_pion_3->Sumw2();
  hsim_pion_4->Sumw2();
  //hsim_pion_5->Sumw2();

  hsim_kaon_0->Sumw2();
  hsim_kaon_1->Sumw2();
  hsim_kaon_2->Sumw2();
  hsim_kaon_3->Sumw2();
  hsim_kaon_4->Sumw2();
  //hsim_kaon_5->Sumw2();

  hsim_proton_0->Sumw2();
  hsim_proton_1->Sumw2();
  hsim_proton_2->Sumw2();
  hsim_proton_3->Sumw2();
  hsim_proton_4->Sumw2();
  //hsim_proton_5->Sumw2();

  hreal_pion_0->Divide(hsim_pion_0);
  hreal_pion_1->Divide(hsim_pion_1);
  hreal_pion_2->Divide(hsim_pion_2);
  hreal_pion_3->Divide(hsim_pion_3);
  hreal_pion_4->Divide(hsim_pion_4);
  //hreal_pion_5->Divide(hsim_pion_5);

  hreal_kaon_0->Divide(hsim_kaon_0);
  hreal_kaon_1->Divide(hsim_kaon_1);
  hreal_kaon_2->Divide(hsim_kaon_2);
  hreal_kaon_3->Divide(hsim_kaon_3);
  hreal_kaon_4->Divide(hsim_kaon_4);
  //hreal_kaon_5->Divide(hsim_kaon_5);

  hreal_proton_0->Divide(hsim_proton_0);
  hreal_proton_1->Divide(hsim_proton_1);
  hreal_proton_2->Divide(hsim_proton_2);
  hreal_proton_3->Divide(hsim_proton_3);
  hreal_proton_4->Divide(hsim_proton_4);
  //hreal_proton_5->Divide(hsim_proton_5);

  hreal_pion_0->Divide(fun,1.0);
  hreal_pion_1->Divide(fun,1.0);
  hreal_pion_2->Divide(fun,1.0);
  hreal_pion_3->Divide(fun,1.0);
  hreal_pion_4->Divide(fun,1.0);
  //hreal_pion_5->Divide(fun,1.0);

  hreal_kaon_0->Divide(fun,1.0);
  hreal_kaon_1->Divide(fun,1.0);
  hreal_kaon_2->Divide(fun,1.0);
  hreal_kaon_3->Divide(fun,1.0);
  hreal_kaon_4->Divide(fun,1.0);
  //hreal_kaon_5->Divide(fun,1.0);

  hreal_proton_0->Divide(fun,1.0);
  hreal_proton_1->Divide(fun,1.0);
  hreal_proton_2->Divide(fun,1.0);
  hreal_proton_3->Divide(fun,1.0);
  hreal_proton_4->Divide(fun,1.0);
  //hreal_proton_5->Divide(fun,1.0);


  hreal_pion_0->SetLineColor(kBlack);
  hreal_pion_1->SetLineColor(kRed);
  hreal_pion_2->SetLineColor(kBlue);
  hreal_pion_3->SetLineColor(kGreen+2);
  hreal_pion_4->SetLineColor(kMagenta+2);
  //hreal_pion_5->SetLineColor(kYellow+2);

  hreal_kaon_0->SetLineColor(kBlack);
  hreal_kaon_1->SetLineColor(kRed);
  hreal_kaon_2->SetLineColor(kBlue);
  hreal_kaon_3->SetLineColor(kGreen+2);
  hreal_kaon_4->SetLineColor(kMagenta+2);
  //hreal_kaon_5->SetLineColor(kYellow+2);

  hreal_proton_0->SetLineColor(kBlack);
  hreal_proton_1->SetLineColor(kRed);
  hreal_proton_2->SetLineColor(kBlue);
  hreal_proton_3->SetLineColor(kGreen+2);
  hreal_proton_4->SetLineColor(kMagenta+2);
  //hreal_proton_5->SetLineColor(kYellow+2);

  TH2F *hhhh = new TH2F("hhhh","",1,0.0,5.0,1,0.001,10000);
  hhhh->Draw();
  hreal_pion_0->Draw("same");
  hreal_pion_1->Draw("same");
  hreal_pion_2->Draw("same");
  hreal_pion_3->Draw("same");
  hreal_pion_4->Draw("same");
  //hreal_pion_5->Draw("same");
  TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->AddEntry(hreal_pion_0,"0","l");
  leg->AddEntry(hreal_pion_1,"1","l");
  leg->AddEntry(hreal_pion_2,"2","l");
  leg->AddEntry(hreal_pion_3,"3","l");
  leg->AddEntry(hreal_pion_4,"4","l");
  //leg->AddEntry(hreal_pion_5,"5","l");
  leg->Draw();

  c1->Print("pions.gif");

  gSystem->Sleep(2000);

  hhhh->Draw();
  hreal_kaon_0->Draw("same");
  hreal_kaon_1->Draw("same");
  hreal_kaon_2->Draw("same");
  hreal_kaon_3->Draw("same");
  hreal_kaon_4->Draw("same");
  //hreal_kaon_5->Draw("same");
  leg->Draw();

  c1->Print("kaons.gif");

  gSystem->Sleep(2000);

  hhhh->Draw();
  hreal_proton_0->Draw("same");
  hreal_proton_1->Draw("same");
  hreal_proton_2->Draw("same");
  hreal_proton_3->Draw("same");
  hreal_proton_4->Draw("same");
  //hreal_proton_5->Draw("same");
  leg->Draw();

  c1->Print("protons.gif");

  gSystem->Sleep(2000);

  c1->Clear();

  c1->SetLogy(0);

  TH1F *hreal_pion = (TH1F *)hreal_pion_1->Clone();
  TH1F *hreal_kaon = (TH1F *)hreal_kaon_1->Clone();
  TH1F *hreal_proton = (TH1F *)hreal_proton_1->Clone();

  hreal_pion_0->Divide(hreal_pion);
  hreal_pion_1->Divide(hreal_pion);
  hreal_pion_2->Divide(hreal_pion);
  hreal_pion_3->Divide(hreal_pion);
  hreal_pion_4->Divide(hreal_pion);
  //hreal_pion_5->Divide(hreal_pion);

  hreal_kaon_0->Divide(hreal_kaon);
  hreal_kaon_1->Divide(hreal_kaon);
  hreal_kaon_2->Divide(hreal_kaon);
  hreal_kaon_3->Divide(hreal_kaon);
  hreal_kaon_4->Divide(hreal_kaon);
  //hreal_kaon_5->Divide(hreal_kaon);

  hreal_proton_0->Divide(hreal_proton);
  hreal_proton_1->Divide(hreal_proton);
  hreal_proton_2->Divide(hreal_proton);
  hreal_proton_3->Divide(hreal_proton);
  hreal_proton_4->Divide(hreal_proton);
  //hreal_proton_5->Divide(hreal_proton);

  TH2F *hhh2 = new TH2F("hhh2","",1,0.0,5.0,1,0.0,2.0);
  hhh2->Draw();
  hreal_pion_0->Draw("same");
  hreal_pion_1->Draw("same");
  hreal_pion_2->Draw("same");
  hreal_pion_3->Draw("same");
  hreal_pion_4->Draw("same");
  //hreal_pion_5->Draw("same");
  leg->Draw();

  c1->Print("pions_ratio.gif");

  gSystem->Sleep(2000);

  hhh2->Draw();
  hreal_kaon_0->Draw("same");
  hreal_kaon_1->Draw("same");
  hreal_kaon_2->Draw("same");
  hreal_kaon_3->Draw("same");
  hreal_kaon_4->Draw("same");
  //hreal_kaon_5->Draw("same");
  leg->Draw();

  c1->Print("kaons_ratio.gif");

  gSystem->Sleep(2000);

  hhh2->Draw();
  hreal_proton_0->Draw("same");
  hreal_proton_1->Draw("same");
  hreal_proton_2->Draw("same");
  hreal_proton_3->Draw("same");
  hreal_proton_4->Draw("same");
  //hreal_proton_5->Draw("same");
  leg->Draw();

  c1->Print("protons_ratio.gif");

}

void physradraw()
{

  gStyle->SetOptTitle(0);

  rcp();

  exit(0);

  for(int isec=0; isec<3; isec++)
    {
      for(int ipid=0; ipid<3; ipid++)
	{
	  //rcp(ipid,isec);
	  //cout<<"rcp("<<ipid<<","<<isec<<");"<<endl;
	  for(int icent=0; icent<5; icent++)
	    {
	      pon(ipid,0,icent);
	      opi(ipid,0,icent);
	    }
	}
    }
  
}


void rcp()
{

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);

  TLine *line = new TLine(0.0,1.0,6.0,1.0);

  //const int NM = 44;


  float ept[44]={0};
  float pt_pion[44], rcp_pionpos[44], ercp_pionpos[44], rcp_pionneg[44], ercp_pionneg[44];
  float pt_kaon[44], rcp_kaonpos[44], ercp_kaonpos[44], rcp_kaonneg[44], ercp_kaonneg[44];
  float pt_prot[44], rcp_protpos[44], ercp_protpos[44], rcp_protneg[44], ercp_protneg[44];
  float esysrcp_pionpos[44];//NEW!
  float esysrcp_kaonpos[44];//NEW!
  float esysrcp_protpos[44];//NEW!
  float esysrcp_pionneg[44];//NEW!
  float esysrcp_kaonneg[44];//NEW!
  float esysrcp_protneg[44];//NEW!

  ifstream fpion("PhysRatios/RCP_tofw_0_dis.dat");
  ifstream fkaon("PhysRatios/RCP_tofw_4_dis.dat");
  ifstream fprot("PhysRatios/RCP_tofw_6_dis.dat");
  for(int i=0; i<44; i++)
    {
      fpion>>pt_pion[i]>>rcp_pionpos[i]>>ercp_pionpos[i]>>rcp_pionneg[i]>>ercp_pionneg[i];
      fkaon>>pt_kaon[i]>>rcp_kaonpos[i]>>ercp_kaonpos[i]>>rcp_kaonneg[i]>>ercp_kaonneg[i];
      fprot>>pt_prot[i]>>rcp_protpos[i]>>ercp_protpos[i]>>rcp_protneg[i]>>ercp_protneg[i];
      esysrcp_pionpos[i] = 0.05*rcp_pionpos[i];//NEW!  and temp, to be revised
      esysrcp_pionneg[i] = 0.05*rcp_pionneg[i];//NEW!  and temp, to be revised
      esysrcp_kaonpos[i] = 0.05*rcp_kaonpos[i];//NEW!  and temp, to be revised
      esysrcp_kaonneg[i] = 0.05*rcp_kaonneg[i];//NEW!  and temp, to be revised
      esysrcp_protpos[i] = 0.05*rcp_protpos[i];//NEW!  and temp, to be revised
      esysrcp_protneg[i] = 0.05*rcp_protneg[i];//NEW!  and temp, to be revised
      if(i<6) {rcp_protpos[i]=-9;rcp_protneg[i]=-9;ercp_protpos[i]=0;ercp_protneg[i]=0;esysrcp_protpos[i]=0;esysrcp_protneg[i]=0;}
      if(i<4) {rcp_kaonpos[i]=-9;rcp_kaonneg[i]=-9;ercp_kaonpos[i]=0;ercp_kaonneg[i]=0;esysrcp_kaonpos[i]=0;esysrcp_kaonneg[i]=0;}
    }



  TGraphErrors *tge_pospion = new TGraphErrors(44,pt_pion,rcp_pionpos,ept,ercp_pionpos);
  tge_pospion->SetMarkerStyle(kFullCircle);
  tge_pospion->SetMarkerColor(kRed);
  TGraphErrors *tge_negpion = new TGraphErrors(44,pt_pion,rcp_pionneg,ept,ercp_pionneg);
  tge_negpion->SetMarkerStyle(kFullCircle);
  tge_negpion->SetMarkerColor(kBlue);

  TGraphErrors *tge_poskaon = new TGraphErrors(44,pt_kaon,rcp_kaonpos,ept,ercp_kaonpos);
  tge_poskaon->SetMarkerStyle(kFullTriangleUp);
  tge_poskaon->SetMarkerColor(kRed);
  TGraphErrors *tge_negkaon = new TGraphErrors(44,pt_kaon,rcp_kaonneg,ept,ercp_kaonneg);
  tge_negkaon->SetMarkerStyle(kFullTriangleUp);
  tge_negkaon->SetMarkerColor(kBlue);

  TGraphErrors *tge_posprot = new TGraphErrors(44,pt_prot,rcp_protpos,ept,ercp_protpos);
  tge_posprot->SetMarkerStyle(kFullSquare);
  tge_posprot->SetMarkerColor(kRed);
  TGraphErrors *tge_negprot = new TGraphErrors(44,pt_prot,rcp_protneg,ept,ercp_protneg);
  tge_negprot->SetMarkerStyle(kFullSquare);
  tge_negprot->SetMarkerColor(kBlue);




  TGraphErrors *tge_pospionSYS = new TGraphErrors(44,pt_pion,rcp_pionpos,ept,esysrcp_pionpos);
  tge_pospionSYS->SetMarkerStyle(1);
  tge_pospionSYS->SetMarkerColor(kRed);
  tge_pospionSYS->SetLineColor(kRed-10);
  tge_pospionSYS->SetLineWidth(15);
  TGraphErrors *tge_negpionSYS = new TGraphErrors(44,pt_pion,rcp_pionneg,ept,esysrcp_pionneg);
  tge_negpionSYS->SetMarkerStyle(1);
  tge_negpionSYS->SetMarkerColor(kBlue);
  tge_negpionSYS->SetLineColor(kBlue-10);
  tge_negpionSYS->SetLineWidth(15);

  TGraphErrors *tge_poskaonSYS = new TGraphErrors(44,pt_kaon,rcp_kaonpos,ept,esysrcp_kaonpos);
  tge_poskaonSYS->SetMarkerStyle(1);
  tge_poskaonSYS->SetMarkerColor(kRed);
  tge_poskaonSYS->SetLineColor(kRed-10);
  tge_poskaonSYS->SetLineWidth(15);
  TGraphErrors *tge_negkaonSYS = new TGraphErrors(44,pt_kaon,rcp_kaonneg,ept,esysrcp_kaonneg);
  tge_negkaonSYS->SetMarkerStyle(1);
  tge_negkaonSYS->SetMarkerColor(kBlue);
  tge_negkaonSYS->SetLineColor(kBlue-10);
  tge_negkaonSYS->SetLineWidth(15);

  TGraphErrors *tge_posprotSYS = new TGraphErrors(44,pt_prot,rcp_protpos,ept,esysrcp_protpos);
  tge_posprotSYS->SetMarkerStyle(1);
  tge_posprotSYS->SetMarkerColor(kRed);
  tge_posprotSYS->SetLineColor(kRed-10);
  tge_posprotSYS->SetLineWidth(15);
  TGraphErrors *tge_negprotSYS = new TGraphErrors(44,pt_prot,rcp_protneg,ept,esysrcp_protneg);
  tge_negprotSYS->SetMarkerStyle(1);
  tge_negprotSYS->SetMarkerColor(kBlue);
  tge_negprotSYS->SetLineColor(kBlue-10);
  tge_negprotSYS->SetLineWidth(15);





  TMultiGraph *tmg_A = new TMultiGraph();
  tmg_A->Add(tge_pospionSYS);
  tmg_A->Add(tge_negpionSYS);
  tmg_A->Add(tge_poskaonSYS);
  tmg_A->Add(tge_negkaonSYS);
  tmg_A->Add(tge_posprotSYS);
  tmg_A->Add(tge_negprotSYS);
  tmg_A->Add(tge_pospion);
  tmg_A->Add(tge_negpion);
  tmg_A->Add(tge_poskaon);
  tmg_A->Add(tge_negkaon);
  tmg_A->Add(tge_posprot);
  tmg_A->Add(tge_negprot);
  tmg_A->Draw("apz");
  line->Draw("same");
  tmg_A->SetMaximum(2.0);
  tmg_A->SetMinimum(0.0);
  tmg_A->GetXaxis()->SetLimits(0.0,6.0);
  tmg_A->GetYaxis()->SetTitle("R_{CP} (0-10%%/60-92%%)");
  tmg_A->GetYaxis()->CenterTitle();
  tmg_A->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_A->GetXaxis()->CenterTitle();

  TLegend *leg_A = new TLegend(0.68,0.68,0.88,0.88);
  leg_A->SetFillColor(kWhite);
  leg_A->SetBorderSize(0);
  leg_A->AddEntry(tge_pospion,"#pi^{+}","p");
  leg_A->AddEntry(tge_negpion,"#pi^{-}","p");
  leg_A->AddEntry(tge_poskaon,"K^{+}","p");
  leg_A->AddEntry(tge_negkaon,"K^{-}","p");
  leg_A->AddEntry(tge_posprot,"p","p");
  leg_A->AddEntry(tge_negprot,"#bar{p}","p");
  leg_A->Draw();

  c1->Print("PhysRatios/Special/rcp.gif");
  c1->Print("PhysRatios/Special/rcp.eps");



  float pt[32];
  float ept[32]={0};
  float ratio[32], eratio[32];

  ifstream fpion1("ppg026/RCP/pion.dat");
  for(int i=0; i<28;i++)
    {
      fpion1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fpion1.close();
  TGraphErrors *ppgpion = new TGraphErrors(28, pt, ratio, ept, eratio);

  ifstream fkaon1("ppg026/RCP/kaon.dat");
  for(int i=0; i<16;i++)
    {
      fkaon1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fkaon1.close();
  TGraphErrors *ppgkaon = new TGraphErrors(16, pt, ratio, ept, eratio);

  ifstream fproton1("ppg026/RCP/proton.dat");
  for(int i=0; i<22;i++)
    {
      fproton1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fproton1.close();
  TGraphErrors *ppgproton = new TGraphErrors(22, pt, ratio, ept, eratio);

  fpion1.open("ppg080/RCP/pion0.dat");
  for(int i=0; i<14;i++)
    {
      fpion1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fpion1.close();
  TGraphErrors *ppgpion0 = new TGraphErrors(14, pt, ratio, ept, eratio);

  ppgpion->SetMarkerStyle(kFullCircle);
  ppgpion->SetMarkerColor(kBlack);
  ppgkaon->SetMarkerStyle(kFullTriangleUp);
  ppgkaon->SetMarkerColor(kBlack);
  ppgproton->SetMarkerStyle(kFullSquare);
  ppgproton->SetMarkerColor(kBlack);
  ppgpion0->SetMarkerStyle(kOpenCircle);
  ppgpion0->SetMarkerColor(kBlack);

  TMultiGraph *tmg_B = new TMultiGraph();
  tmg_B->Add(tge_pospionSYS);
  tmg_B->Add(tge_negpionSYS);
  tmg_B->Add(tge_poskaonSYS);
  tmg_B->Add(tge_negkaonSYS);
  tmg_B->Add(tge_posprotSYS);
  tmg_B->Add(tge_negprotSYS);
  tmg_B->Add(tge_pospion);
  tmg_B->Add(tge_negpion);
  tmg_B->Add(tge_poskaon);
  tmg_B->Add(tge_negkaon);
  tmg_B->Add(tge_posprot);
  tmg_B->Add(tge_negprot);
  tmg_B->Add(ppgpion);
  tmg_B->Add(ppgkaon);
  tmg_B->Add(ppgproton);
  tmg_B->Add(ppgpion0);
  tmg_B->Draw("apz");
  line->Draw("same");
  tmg_B->SetMaximum(2.0);
  tmg_B->SetMinimum(0.0);
  tmg_B->GetXaxis()->SetLimits(0.0,6.0);
  tmg_B->GetYaxis()->SetTitle("R_{CP} (0-10%%/60-92%%)");
  tmg_B->GetYaxis()->CenterTitle();
  tmg_B->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_B->GetXaxis()->CenterTitle();

  // TLegend *leg_B = new TLegend(0.68,0.68,0.88,0.88);
  // leg_B->SetFillColor(kWhite);
  // leg_B->SetBorderSize(0);
  // leg_B->AddEntry(tge_pospion,"#pi^{+}","p");
  // leg_B->AddEntry(tge_negpion,"#pi^{-}","p");
  // leg_B->AddEntry(tge_poskaon,"K^{+}","p");
  // leg_B->AddEntry(tge_negkaon,"K^{-}","p");
  // leg_B->AddEntry(tge_posprot,"p","p");
  // leg_B->AddEntry(tge_negprot,"#bar{p}","p");
  // leg_B->Draw();

  TPaveText *tptP_B = new TPaveText(1.5,2.01,4.5,2.19,"br");
  tptP_B->SetFillColor(10);
  tptP_B->SetBorderSize(0);
  TText *textP_B = tptP_B->AddText("Au+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_B->Draw();

  // TPaveText *tptP2 = new TPaveText(4.45,1.55,5.7,1.68,"br");
  // tptP2->SetFillColor(10);
  // tptP2->SetBorderSize(0);
  // TText *textP2 = tptP2->AddText("Preliminary");
  // tptP2->Draw();

  TLegend *leg_B = new TLegend(0.13,0.53,0.30,0.88);
  leg_B->SetFillColor(10);
  leg_B->SetBorderSize(0);
  leg_B->AddEntry(tge_pospion,"#pi^{+} Run7","p");
  leg_B->AddEntry(tge_negpion,"#pi^{-} Run7","p");
  leg_B->AddEntry(tge_poskaon,"K^{+} Run7","p");
  leg_B->AddEntry(tge_negkaon,"K^{-} Run7","p");
  leg_B->AddEntry(tge_posprot,"p Run7","p");
  leg_B->AddEntry(tge_negprot,"#bar{p} Run7","p");
  leg_B->Draw();

  TLegend *leg2_B = new TLegend(0.33,0.68,0.60,0.88);
  leg2_B->SetFillColor(10);
  leg2_B->SetBorderSize(0);
  leg2_B->AddEntry(ppgpion,"#pi^{+}+#pi^{-} Run2","p");
  leg2_B->AddEntry(ppgkaon,"K^{+}+K^{-} Run2","p");
  leg2_B->AddEntry(ppgproton,"p+#bar{p} Run2","p");
  leg2_B->AddEntry(ppgpion0,"#pi^{0} Run4","p");
  leg2_B->Draw();


  c1->Print("PhysRatios/Special/rcp_pub.gif");
  c1->Print("PhysRatios/Special/rcp_pub.eps");



  ppgpion0->SetMarkerStyle(24);
  ppgpion->SetMarkerStyle(20);
  ppgkaon->SetMarkerStyle(22);
  TMultiGraph *tmg_pak = new TMultiGraph();
  tmg_pak->Add(tge_pospionSYS);
  tmg_pak->Add(tge_negpionSYS);
  tmg_pak->Add(tge_poskaonSYS);
  tmg_pak->Add(tge_negkaonSYS);
  tmg_pak->Add(tge_pospion);
  tmg_pak->Add(tge_negpion);
  tmg_pak->Add(tge_poskaon);
  tmg_pak->Add(tge_negkaon);
  //tmg_pak->Add(tge_posprot);
  //tmg_pak->Add(tge_negprot);
  tmg_pak->Add(ppgpion);
  tmg_pak->Add(ppgkaon);
  //tmg_pak->Add(ppgproton);
  tmg_pak->Add(ppgpion0);
  tmg_pak->Draw("apz");
  line->Draw("same");
  tmg_pak->SetMaximum(2.0);
  tmg_pak->SetMinimum(0.0);
  tmg_pak->GetXaxis()->SetLimits(0.0,6.0);
  tmg_pak->GetYaxis()->SetTitle("R_{CP} (0-10%%/60-92%%)");
  tmg_pak->GetYaxis()->CenterTitle();
  tmg_pak->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pak->GetXaxis()->CenterTitle();

  TPaveText *tptP_pak = new TPaveText(1.5,2.01,4.5,2.19,"br");
  tptP_pak->SetFillColor(10);
  tptP_pak->SetBorderSize(0);
  TText *textP_pak = tptP_pak->AddText("Au+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_pak->Draw();

  TLegend *leg_pak = new TLegend(0.13,0.53,0.30,0.88);
  leg_pak->SetFillColor(10);
  leg_pak->SetBorderSize(0);
  leg_pak->AddEntry(tge_pospion,"#pi^{+} Run7","p");
  leg_pak->AddEntry(tge_negpion,"#pi^{-} Run7","p");
  leg_pak->AddEntry(tge_poskaon,"K^{+} Run7","p");
  leg_pak->AddEntry(tge_negkaon,"K^{-} Run7","p");
  //leg_pak->AddEntry(tge_posprot,"p","p");
  //leg_pak->AddEntry(tge_negprot,"#bar{p}","p");
  leg_pak->Draw();

  TLegend *leg2_pak = new TLegend(0.33,0.68,0.60,0.88);
  leg2_pak->SetFillColor(10);
  leg2_pak->SetBorderSize(0);
  leg2_pak->AddEntry(ppgpion,"#pi^{+}+#pi^{-} Run2","p");
  leg2_pak->AddEntry(ppgkaon,"K^{+}+K^{-} Run2","p");
  //leg2_pak->AddEntry(ppgproton,"p+#bar{p} PRC.69.034909","p");
  leg2_pak->AddEntry(ppgpion0,"#pi^{0} Run4","p");
  leg2_pak->Draw();


  c1->Print("PhysRatios/Special/rcp_pak_pub.gif");
  c1->Print("PhysRatios/Special/rcp_pak_pub.eps");








  ppgpion0->SetMarkerStyle(24);
  ppgpion->SetMarkerStyle(20);
  ppgproton->SetMarkerStyle(21);
  TMultiGraph *tmg_pap = new TMultiGraph();
  tmg_pap->Add(tge_pospionSYS);
  tmg_pap->Add(tge_negpionSYS);
  tmg_pap->Add(tge_posprotSYS);
  tmg_pap->Add(tge_negprotSYS);
  tmg_pap->Add(tge_pospion);
  tmg_pap->Add(tge_negpion);
  //tmg_pap->Add(tge_poskaon);
  //tmg_pap->Add(tge_negkaon);
  tmg_pap->Add(tge_posprot);
  tmg_pap->Add(tge_negprot);
  tmg_pap->Add(ppgpion);
  //tmg_pap->Add(ppgkaon);
  tmg_pap->Add(ppgproton);
  tmg_pap->Add(ppgpion0);
  tmg_pap->Draw("apz");
  line->Draw("same");
  tmg_pap->SetMaximum(2.0);
  tmg_pap->SetMinimum(0.0);
  tmg_pap->GetXaxis()->SetLimits(0.0,6.0);
  tmg_pap->GetYaxis()->SetTitle("R_{CP} (0-10%%/60-92%%)");
  tmg_pap->GetYaxis()->CenterTitle();
  tmg_pap->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pap->GetXaxis()->CenterTitle();

  TPaveText *tptP_pap = new TPaveText(1.5,2.01,4.5,2.19,"br");
  tptP_pap->SetFillColor(10);
  tptP_pap->SetBorderSize(0);
  TText *textP_pap = tptP_pap->AddText("Au+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_pap->Draw();

  TLegend *leg_pap = new TLegend(0.13,0.53,0.27,0.88);
  leg_pap->SetFillColor(10);
  leg_pap->SetBorderSize(0);
  leg_pap->AddEntry(tge_pospion,"#pi^{+} Run7","p");
  leg_pap->AddEntry(tge_negpion,"#pi^{-} Run7","p");
  //leg_pap->AddEntry(tge_poskaon,"K^{+}","p");
  //leg_pap->AddEntry(tge_negkaon,"K^{-}","p");
  leg_pap->AddEntry(tge_posprot,"p Run7","p");
  leg_pap->AddEntry(tge_negprot,"#bar{p} Run7","p");
  leg_pap->Draw();

  TLegend *leg2_pap = new TLegend(0.35,0.68,0.55,0.88);
  leg2_pap->SetFillColor(10);
  leg2_pap->SetBorderSize(0);
  leg2_pap->AddEntry(ppgpion,"#pi^{+}+#pi^{-} Run2","p");
  //leg2_pap->AddEntry(ppgkaon,"K^{+}+K^{-} Run2","p");
  leg2_pap->AddEntry(ppgproton,"p+#bar{p} Run2","p");
  leg2_pap->AddEntry(ppgpion0,"#pi^{0} Run4","p");
  leg2_pap->Draw();


  c1->Print("PhysRatios/Special/rcp_pap_pub.gif");
  c1->Print("PhysRatios/Special/rcp_pap_pub.eps");


}



void opi(int ipid=0, int sector=0, int centid=0)
{

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);



  int pid=0;
  if(ipid==0) pid=0;
  if(ipid==1) pid=4;
  if(ipid==2) pid=6;

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");

  char centstring[10];
  sprintf(centstring,"0092"); // "default"
  if(centid==0) sprintf(centstring,"0010");
  if(centid==1) sprintf(centstring,"1020");
  if(centid==2) sprintf(centstring,"2040");
  if(centid==3) sprintf(centstring,"4060");
  if(centid==4) sprintf(centstring,"6092");


  float pTpos[44], epTpos[44], ratiopos[44], eratiopos[44];
  float pTneg[44], epTneg[44], rationeg[44], erationeg[44];

  float pT[44];
  float epT[44]={0};

  char fnamein[100];
  sprintf(fnamein,"PhysRatios/opi_%s_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  ifstream finn;
  finn.open(fnamein);
  for(int i=0; i<44; i++)
    {
      finn>>pT[i]>>ratiopos[i]>>eratiopos[i]>>rationeg[i]>>erationeg[i];
    }
  finn.close();

  for(int i=0; i<6; i++)
    {
      if(ipid==2) {ratiopos[i]=-9; rationeg[i]=-9;eratiopos[i]=0; erationeg[i]=0;}
    }

  TGraphErrors *tge_pos = new TGraphErrors(44,pT,ratiopos,epT,eratiopos);
  tge_pos->SetMarkerColor(kRed);
  tge_pos->SetMarkerStyle(kFullCircle);
  TGraphErrors *tge_neg = new TGraphErrors(44,pT,rationeg,epT,erationeg);
  tge_neg->SetMarkerColor(kBlue);
  tge_neg->SetMarkerStyle(kFullCircle);

  TMultiGraph *tmg_A = new TMultiGraph();
  tmg_A->Add(tge_pos);
  tmg_A->Add(tge_neg);
  tmg_A->Draw("ap");
  tmg_A->SetMinimum(0.0);
  tmg_A->SetMaximum(1.0);
  if(ipid==0) tmg_A->SetMaximum(1.5);
  //if(ipid==1) tmg_A->SetMaximum(1.0);
  //if(ipid==2) tmg_A->SetMaximum(1.0);
  tmg_A->GetXaxis()->SetLimits(0.0,6.0);
  if(ipid==1) tmg_A->GetXaxis()->SetLimits(0.0,4.0);
  tmg_A->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_A->GetXaxis()->CenterTitle();
  tmg_A->GetYaxis()->SetTitle("Ratio");
  if(ipid==1) tmg_A->GetYaxis()->SetTitle("Ratio K/#pi");
  if(ipid==2) tmg_A->GetYaxis()->SetTitle("Ratio p/#pi");
  tmg_A->GetYaxis()->CenterTitle();

  TLegend *leg_A = new TLegend(0.68,0.68,0.88,0.88);
  leg_A->SetFillColor(kWhite);
  leg_A->SetBorderSize(0);
  if(ipid==1) leg_A->AddEntry(tge_pos,"K^{+}/#pi^{+}","p");
  if(ipid==1) leg_A->AddEntry(tge_neg,"K^{-}/#pi^{-}","p");
  if(ipid==2) leg_A->AddEntry(tge_pos,"p/#pi^{+}","p");
  if(ipid==2) leg_A->AddEntry(tge_neg,"#bar{p}/#pi^{-}","p");
  leg_A->Draw();

  char figname[100];
  sprintf(figname,"PhysRatios/opi_%s_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  if(pid>0) c1->Print(figname);
  sprintf(figname,"PhysRatios/opi_%s_%d_dis_cent%s.eps",sectorstring,pid,centstring);
  if(pid>0) c1->Print(figname);

  //c1->Clear();
  //tmg_A->Delete();
  //leg_A->Delete();


  /*

  float ptpion[34];
  float ptproton[34];
  float eptpion[34]={0};
  float eptproton[34]={0};
  float ptratio[34];
  float yieldpionpos[34],yieldpionneg[34];
  float eyieldpionpos[34],eyieldpionneg[34];
  float yieldprotonpos[34],yieldprotonneg[34];
  float eyieldprotonpos[34],eyieldprotonneg[34];

  ifstream fin1;
  ifstream fin2;

  char fin1name[100];
  char fin2name[100];

  sprintf(fin1name,"ppg026/pospion_%s.dat",centid);
  sprintf(fin2name,"ppg026/negpion_%s.dat",centid);

  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<28; i++)
    {
      fin1>>ptpion[i]>>yieldpionpos[i]>>eyieldpionpos[i];
      fin2>>ptpion[i]>>yieldpionneg[i]>>eyieldpionneg[i];
    }
  fin1.close();  
  fin2.close();

  if(ipid==1) sprintf(fin1name,"ppg026/poskaon_%s.dat",centid);
  if(ipid==1) sprintf(fin2name,"ppg026/negkaon_%s.dat",centid);
  if(ipid==2) sprintf(fin1name,"ppg026/posproton_%s.dat",centid);
  if(ipid==2) sprintf(fin2name,"ppg026/negproton_%s.dat",centid);

  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<34; i++)
    {
      fin1>>ptproton[i]>>yieldprotonpos[i]>>eyieldprotonpos[i];
      fin2>>ptproton[i]>>yieldprotonneg[i]>>eyieldprotonneg[i];
    }
  fin1.close();  
  fin2.close();

  float A,dA,B,dB;

  for(int i=0; i<24; i++)
    {
      //positive ratio
      A = yieldprotonpos[i];
      dA = eyieldprotonpos[i];
      B = yieldpionpos[i+4];
      dB = eyieldpionpos[i+4];
      //ratiopos[i] = A/B;
      //eratiopos[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
      if(A>0&&B>0)
	{
	  ratiopos[i] = A/B;
	  eratiopos[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
	}
      else
	{
	  ratiopos[i]=-9;
	  eratiopos[i]=-9;
	}
      //negative ratio
      A = yieldprotonneg[i];
      dA = eyieldprotonneg[i];
      B = yieldpionneg[i+4];
      dB = eyieldpionneg[i+4];
      //rationeg[i] = A/B;
      //erationeg[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
      if(A>0&&B>0)
	{
	  rationeg[i] = A/B;
	  erationeg[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
	}
      else
	{
	  rationeg[i]=-9;
	  erationeg[i]=-9;
	}
    }

  TGraphErrors *tposppg = new TGraphErrors(24,ptproton,ratiopos,eptproton,eratiopos);
  tposppg->SetMarkerStyle(25);
  tposppg->SetMarkerColor(2);

  TGraphErrors *tnegppg = new TGraphErrors(24,ptproton,rationeg,eptproton,erationeg);
  tnegppg->SetMarkerStyle(25);
  tnegppg->SetMarkerColor(4);

  TMultiGraph *tmg_B = new TMultiGraph();
  tmg_B->Add(tge_pos);
  tmg_B->Add(tge_neg);
  tmg_B->Add(tposppg);
  tmg_B->Add(tnegppg);
  tmg_B->Draw("ap");
  tmg_B->SetMinimum(0.0);
  tmg_B->SetMaximum(1.0);
  if(ipid==0) tmg_B->SetMaximum(1.5);
  //if(ipid==1) tmg_B->SetMaximum(1.0);
  //if(ipid==2) tmg_B->SetMaximum(1.0);
  tmg_B->GetXaxis()->SetLimits(0.0,6.0);
  if(ipid==1) tmg_B->GetXaxis()->SetLimits(0.0,4.0);
  tmg_B->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_B->GetXaxis()->CenterTitle();
  tmg_B->GetYaxis()->SetTitle("Ratio");
  if(ipid==1) tmg_B->GetYaxis()->SetTitle("Ratio K/#pi");
  if(ipid==2) tmg_B->GetYaxis()->SetTitle("Ratio p/#pi");
  tmg_B->GetYaxis()->CenterTitle();

  TLegend *leg_B = new TLegend(0.68,0.68,0.88,0.88);
  leg_B->SetFillColor(kWhite);
  leg_B->SetBorderSize(0);
  if(ipid==1) leg_B->AddEntry(tge_pos,"K^{+}/#pi^{+}","p");
  if(ipid==1) leg_B->AddEntry(tge_neg,"K^{-}/#pi^{-}","p");
  if(ipid==1) leg_B->AddEntry(tge_pos,"K^{+}/#pi^{+} PPG026","p");
  if(ipid==1) leg_B->AddEntry(tge_neg,"K^{-}/#pi^{-} PPG026","p");
  if(ipid==2) leg_B->AddEntry(tge_pos,"p/#pi^{+}","p");
  if(ipid==2) leg_B->AddEntry(tge_neg,"#bar{p}/#pi^{-}","p");
  if(ipid==2) leg_B->AddEntry(tge_pos,"p/#pi^{+} PPG026","p");
  if(ipid==2) leg_B->AddEntry(tge_neg,"#bar{p}/#pi^{-} PPG026","p");
  leg_B->Draw();

  char fignamepub[100];
  sprintf(fignamepub,"PhysRatios/opi_pub_%s_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  if(pid>0) c1->Print(fignamepub);
  sprintf(fignamepub,"PhysRatios/opi_pub_%s_%d_dis_cent%s.eps",sectorstring,pid,centstring);
  if(pid>0) c1->Print(fignamepub);


  //c1->Clear();
  // tmg_B->Delete();
  // leg_B->Delete();
  // tposppg->Delete();
  // tnegppg->Delete();
  // tge_pos->Delete();
  // tge_neg->Delete();

  */

}




void pon(int ipid=0, int sector=0, int centid=0)
{

  TLine *line0 = new TLine(0.0,1.0,6.0,1.0);
  TLine *line1 = new TLine(0.0,0.9,4.0,0.9);
  TLine *line2 = new TLine(0.0,0.74,6.0,0.74);

  int pid=0;
  if(ipid==0) pid=0;
  if(ipid==1) pid=4;
  if(ipid==2) pid=6;

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");

  char centstring[10];
  sprintf(centstring,"0092"); // "default"
  if(centid==0) sprintf(centstring,"0010");
  if(centid==1) sprintf(centstring,"1020");
  if(centid==2) sprintf(centstring,"2040");
  if(centid==3) sprintf(centstring,"4060");
  if(centid==4) sprintf(centstring,"6092");


  float pT[44], ratio[44], eratio[44];
  float epT[44]={0};

  char fnamein[100];

  sprintf(fnamein,"PhysRatios/pon_%s_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  ifstream fin;
  fin.open(fnamein);
  for(int i=0; i<44; i++)
    {
      fin>>pT[i]>>ratio[i]>>eratio[i];
    }
  fin.close();

  TGraphErrors *tge = new TGraphErrors(44,pT,ratio,epT,eratio);
  tge->SetMarkerStyle(kFullSquare);
  tge->SetMarkerColor(kBlack);

  tge->Draw("ap");
  if(ipid==0) line0->Draw("same");
  if(ipid==1) line1->Draw("same");
  if(ipid==2) line2->Draw("same");

  tge->SetMinimum(0.0);
  tge->SetMaximum(1.0);
  if(ipid==0) tge->SetMaximum(1.5);
  if(ipid==1) tge->SetMaximum(1.5);
  if(ipid==2) tge->SetMaximum(1.5);
  tge->GetXaxis()->SetLimits(0.0,6.0);
  if(ipid==1) tge->GetXaxis()->SetLimits(0.0,4.0);
  tge->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge->GetXaxis()->CenterTitle();
  tge->GetYaxis()->SetTitle("Ratio");
  if(ipid==0) tge->GetYaxis()->SetTitle("Ratio #pi^{-}/#pi^{+}");
  if(ipid==1) tge->GetYaxis()->SetTitle("Ratio K^{-}/K^{+}");
  if(ipid==2) tge->GetYaxis()->SetTitle("Ratio #bar{p}/p");
  tge->GetYaxis()->CenterTitle();

  //TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  TLegend *leg = new TLegend(0.68,0.18,0.88,0.38);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  if(ipid==0) leg->AddEntry(tge,"#pi^{-}/#pi^{+}","p");
  if(ipid==1) leg->AddEntry(tge,"K^{-}/K^{+}","p");
  if(ipid==2) leg->AddEntry(tge,"#bar{p}/p","p");
  leg->Draw();

  float pT1[44], ratio1[44], eratio1[44];
  float epT1[44]={0};

  char fnamein1[100];
  sprintf(fnamein1,"PhysRatios/ponfield_%s_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  ifstream fin1;
  fin1.open(fnamein1);
  for(int i=0; i<44; i++)
    {
      fin1>>pT1[i]>>ratio1[i]>>eratio1[i];
    }
  fin1.close();

  TGraphErrors *tgefield = new TGraphErrors(44,pT1,ratio1,epT1,eratio1);
  tgefield->SetMarkerStyle(kOpenSquare);
  tgefield->SetMarkerColor(kRed);

  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tge);
  tmg->Add(tgefield);
  tmg->Draw("ap");
  if(ipid==0) line0->Draw("same");
  if(ipid==1) line1->Draw("same");
  if(ipid==2) line2->Draw("same");
  tmg->SetMinimum(0.0);
  tmg->SetMaximum(1.0);
  if(ipid==0) tmg->SetMaximum(1.5);
  if(ipid==1) tmg->SetMaximum(1.5);
  if(ipid==2) tmg->SetMaximum(1.5);
  tmg->GetXaxis()->SetLimits(0.0,6.0);
  if(ipid==1) tmg->GetXaxis()->SetLimits(0.0,4.0);
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetXaxis()->CenterTitle();
  tmg->GetYaxis()->SetTitle("Ratio");
  if(ipid==0) tmg->GetYaxis()->SetTitle("Ratio #pi^{-}/#pi^{+}");
  if(ipid==1) tmg->GetYaxis()->SetTitle("Ratio K^{-}/K^{+}");
  if(ipid==2) tmg->GetYaxis()->SetTitle("Ratio #bar{p}/p");
  tmg->GetYaxis()->CenterTitle();

  //TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  TLegend *leg1 = new TLegend(0.68,0.18,0.88,0.38);
  leg1->SetFillColor(kWhite);
  leg1->SetBorderSize(0);
  if(ipid==0) leg1->AddEntry(tge,"#pi^{-}/#pi^{+}","p");
  if(ipid==1) leg1->AddEntry(tge,"K^{-}/K^{+}","p");
  if(ipid==2) leg1->AddEntry(tge,"#bar{p}/p","p");
  if(ipid==0) leg1->AddEntry(tgefield,"#pi^{-}/#pi^{+}, mixed","p");
  if(ipid==1) leg1->AddEntry(tgefield,"K^{-}/K^{+}, mixed","p");
  if(ipid==2) leg1->AddEntry(tgefield,"#bar{p}/p, mixed","p");
  leg1->Draw();

  char figname[100];
  sprintf(figname,"PhysRatios/ponfield_%s_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  c1->Print(figname);
  sprintf(figname,"PhysRatios/ponfield_%s_%d_dis_cent%s.eps",sectorstring,pid,centstring);
  c1->Print(figname);


}

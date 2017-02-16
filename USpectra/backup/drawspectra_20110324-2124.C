void drawspectra()
{

  cout<<"hello!  now drawing spectra!"<<endl;

  // for(int icent=0; icent<4; icent++)
  //   {
  //     for(int ipid=0; ipid<6; ipid++)
  // 	{
  // 	  for(int isec=0; isec<3; isec++)
  // 	    {
  // 	      doit(isec,ipid,icent);
  // 	      //cout<<"doit("<<isec<<","<<ipid<<","<<icent<<");"<<endl;
  // 	    }
  // 	}
  //   }


  for(int icent=0; icent<4; icent++)
    {
      pion(0,0,icent);
      kaon(0,3,icent);
      proton(0,4,icent);
    }

  cout<<"done!  have a nice day!"<<endl;

}

void pion(int sector=0, int pid=0, int centid=0)
{

  // --- beginning of code

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFillColor(kWhite);
  c1->SetFrameFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameBorderMode(0);
  c1->SetLogy();



  // --- strings for filenames

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");

  char centstring[10];
  sprintf(centstring,"0088"); // "default"
  if(centid==0) sprintf(centstring,"0020");
  if(centid==1) sprintf(centstring,"2040");
  if(centid==2) sprintf(centstring,"4060");
  if(centid==3) sprintf(centstring,"6088");
  if(centid==4) sprintf(centstring,"0088");

  char bigcentstring[50];
  sprintf(bigcentstring,"0088"); // "default"
  //if(centid==0) sprintf(bigcentstring,"0-20%% cent");
  //if(centid==1) sprintf(bigcentstring,"20-40%% cent");
  //if(centid==2) sprintf(bigcentstring,"40-60%% cent");
  //if(centid==3) sprintf(bigcentstring,"60-88%% cent");
  if(centid==0) sprintf(bigcentstring,"0-20%%");
  if(centid==1) sprintf(bigcentstring,"20-40%%");
  if(centid==2) sprintf(bigcentstring,"40-60%%");
  if(centid==3) sprintf(bigcentstring,"60-88%%");
  if(centid==4) sprintf(bigcentstring,"MinBias");

  // ---



  // --- ppg044 stuff

  float pT_ppg044[21], yield_ppg044[21], eyield_ppg044[21];
  float ept[21];
  char finname[30];
  sprintf(finname,"ppg030/pi0_%s.dat",centstring);
  ifstream fin44(finname);
  for(int i=0; i<21; i++)
    {
      ept[i]=0;
      fin44>>pT_ppg044[i]>>yield_ppg044[i]>>eyield_ppg044[i];
    }
  fin44.close();

  TGraphErrors *pion44 = new TGraphErrors(21,pT_ppg044,yield_ppg044,ept,eyield_ppg044);
  pion44->SetMarkerColor(kGreen+2);
  pion44->SetMarkerStyle(20);



  // --- ppg030 stuff

  float pTpos_ppg030[18], yieldpos_ppg030[18], eyieldpos_ppg030[18];
  float pTneg_ppg030[18], yieldneg_ppg030[18], eyieldneg_ppg030[18];
  float ept[18];

  char finposname[30];
  char finnegname[30];
  sprintf(finposname,"ppg030/pospion_%s.dat",centstring);
  sprintf(finnegname,"ppg030/negpion_%s.dat",centstring);

  ifstream finpos30(finposname);
  ifstream finneg30(finnegname);

  for(int i=0; i<18; i++)
    {
      ept[i]=0;
      finpos30>>pTpos_ppg030[i]>>yieldpos_ppg030[i]>>eyieldpos_ppg030[i];
      finneg30>>pTneg_ppg030[i]>>yieldneg_ppg030[i]>>eyieldneg_ppg030[i];
    }

  finpos30.close();
  finneg30.close();

  TGraphErrors *pionpos30 = new TGraphErrors(18,pTpos_ppg030,yieldpos_ppg030,ept,eyieldpos_ppg030);
  pionpos30->SetMarkerColor(kRed);
  pionpos30->SetMarkerStyle(20);

  TGraphErrors *pionneg30 = new TGraphErrors(18,pTneg_ppg030,yieldneg_ppg030,ept,eyieldneg_ppg030);
  pionneg30->SetMarkerColor(kRed);
  pionneg30->SetMarkerStyle(20);

  // ---



  // --- input data

  char fnameinpospp[100];
  char fnameinnegpp[100];
  char fnameinposmm[100];
  char fnameinnegmm[100];
  char fnameinposcb[100];
  char fnameinnegcb[100];

  sprintf(fnameinpospp,"Data/ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegpp,"Data/ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinposmm,"Data/ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegmm,"Data/ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinposcb,"Data/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  ifstream finpospp;
  ifstream finnegpp;
  ifstream finposmm;
  ifstream finnegmm;
  ifstream finposcb;
  ifstream finnegcb;

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pT_pospp[100], yield_pospp[100], eyield_pospp[100];
  float pT_negpp[100], yield_negpp[100], eyield_negpp[100];
  float pT_posmm[100], yield_posmm[100], eyield_posmm[100];
  float pT_negmm[100], yield_negmm[100], eyield_negmm[100];
  float pT_poscb[100], yield_poscb[100], eyield_poscb[100];
  float pT_negcb[100], yield_negcb[100], eyield_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pT_pospp[i]>>yield_pospp[i]>>eyield_pospp[i];
      // negpp
      finnegpp>>pT_negpp[i]>>yield_negpp[i]>>eyield_negpp[i];
      // posmm
      finposmm>>pT_posmm[i]>>yield_posmm[i]>>eyield_posmm[i];
      // negmm
      finnegmm>>pT_negmm[i]>>yield_negmm[i]>>eyield_negmm[i];
      // poscb
      finposcb>>pT_poscb[i]>>yield_poscb[i]>>eyield_poscb[i];
      // negcb
      finnegcb>>pT_negcb[i]>>yield_negcb[i]>>eyield_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();



  // --- now input the rebinned data

  sprintf(fnameinpospp,"Data/R5_ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegpp,"Data/R5_ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinposmm,"Data/R5_ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegmm,"Data/R5_ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinposcb,"Data/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pTR_pospp[100], yieldR_pospp[100], eyieldR_pospp[100];
  float pTR_negpp[100], yieldR_negpp[100], eyieldR_negpp[100];
  float pTR_posmm[100], yieldR_posmm[100], eyieldR_posmm[100];
  float pTR_negmm[100], yieldR_negmm[100], eyieldR_negmm[100];
  float pTR_poscb[100], yieldR_poscb[100], eyieldR_poscb[100];
  float pTR_negcb[100], yieldR_negcb[100], eyieldR_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pTR_pospp[i]>>yieldR_pospp[i]>>eyieldR_pospp[i];
      // negpp
      finnegpp>>pTR_negpp[i]>>yieldR_negpp[i]>>eyieldR_negpp[i];
      // posmm
      finposmm>>pTR_posmm[i]>>yieldR_posmm[i]>>eyieldR_posmm[i];
      // negmm
      finnegmm>>pTR_negmm[i]>>yieldR_negmm[i]>>eyieldR_negmm[i];
      // poscb
      finposcb>>pTR_poscb[i]>>yieldR_poscb[i]>>eyieldR_poscb[i];
      // negcb
      finnegcb>>pTR_negcb[i]>>yieldR_negcb[i]>>eyieldR_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();



  // --- now make tgrapherrorses

  float pT[36], epT[36], yield[36], eyield[36];

  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_pospp[i];
	  epT[i] = 0;
	  yield[i] = yield_pospp[i];
	  eyield[i] = eyield_pospp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_pospp[k];
	  epT[i] = 0;
	  yield[i] = yieldR_pospp[k];
	  eyield[i] = eyieldR_pospp[k];
	}

    }

  TGraphErrors *tge_pospp = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_pospp->SetMarkerColor(kBlack);
  tge_pospp->SetMarkerStyle(20);

  TMultiGraph *tmg_pospp = new TMultiGraph();
  tmg_pospp->Add(tge_pospp);
  tmg_pospp->Add(pionpos30);
  tmg_pospp->Add(pion44);
  tmg_pospp->Draw("ap");
  tmg_pospp->SetMaximum(1e1);
  tmg_pospp->SetMinimum(1e-7);
  tmg_pospp->GetXaxis()->SetLimits(0.0,6.0);
  tmg_pospp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pospp->GetXaxis()->CenterTitle();
  //tmg_pospp->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_pospp->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_pospp->GetYaxis()->CenterTitle();

  TPaveText *tptP_pospp = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_pospp->SetFillColor(10);
  tptP_pospp->SetBorderSize(0);
  TText *textP_pospp = tptP_pospp->AddText(bigcentstring);
  tptP_pospp->Draw();

  TPaveText *tptP_pospp2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_pospp2->SetFillColor(10);
  tptP_pospp2->SetBorderSize(0);
  TText *textP_pospp2 = tptP_pospp2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_pospp2->Draw();

  TLegend *leg _pospp = new TLegend(0.68,0.68,0.88,0.88);
  leg_pospp->SetFillColor(kWhite);
  leg_pospp->SetBorderSize(0);
  leg_pospp->AddEntry(tge_pospp,"#pi^{+}, ++ field","p");
  leg_pospp->AddEntry(pionpos30,"#pi^{+}, ppg030","p");
  leg_pospp->AddEntry(pion44,"#pi^{0}, ppg044","p");
  leg_pospp->Draw();

  char gifname_pospp[100];
  sprintf(gifname_pospp,"SpectraFigures/ptpid_%s_pospp_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_pospp[100];
  sprintf(epsname_pospp,"SpectraFigures/ptpid_%s_pospp_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_pospp);
  c1->Print(epsname_pospp);






  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_negpp[i];
	  epT[i] = 0;
	  yield[i] = yield_negpp[i];
	  eyield[i] = eyield_negpp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_negpp[k];
	  epT[i] = 0;
	  yield[i] = yieldR_negpp[k];
	  eyield[i] = eyieldR_negpp[k];
	}

    }

  TGraphErrors *tge_negpp = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_negpp->SetMarkerColor(kBlack);
  tge_negpp->SetMarkerStyle(20);

  TMultiGraph *tmg_negpp = new TMultiGraph();
  tmg_negpp->Add(tge_negpp);
  tmg_negpp->Add(pionneg30);
  tmg_negpp->Add(pion44);
  tmg_negpp->Draw("ap");
  tmg_negpp->SetMaximum(1e1);
  tmg_negpp->SetMinimum(1e-7);
  tmg_negpp->GetXaxis()->SetLimits(0.0,6.0);
  tmg_negpp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_negpp->GetXaxis()->CenterTitle();
  //tmg_negpp->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_negpp->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_negpp->GetYaxis()->CenterTitle();

  TPaveText *tptP_negpp = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_negpp->SetFillColor(10);
  tptP_negpp->SetBorderSize(0);
  TText *textP_negpp = tptP_negpp->AddText(bigcentstring);
  tptP_negpp->Draw();

  TPaveText *tptP_negpp2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_negpp2->SetFillColor(10);
  tptP_negpp2->SetBorderSize(0);
  TText *textP_negpp2 = tptP_negpp2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_negpp2->Draw();

  TLegend *leg _negpp = new TLegend(0.68,0.68,0.88,0.88);
  leg_negpp->SetFillColor(kWhite);
  leg_negpp->SetBorderSize(0);
  leg_negpp->AddEntry(tge_negpp,"#pi^{-}, ++ field","p");
  leg_negpp->AddEntry(pionneg30,"#pi^{-}, ppg030","p");
  leg_negpp->AddEntry(pion44,"#pi^{0}, ppg044","p");
  leg_negpp->Draw();

  char gifname_negpp[100];
  sprintf(gifname_negpp,"SpectraFigures/ptpid_%s_negpp_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_negpp[100];
  sprintf(epsname_negpp,"SpectraFigures/ptpid_%s_negpp_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_negpp);
  c1->Print(epsname_negpp);













  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_posmm[i];
	  epT[i] = 0;
	  yield[i] = yield_posmm[i];
	  eyield[i] = eyield_posmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_posmm[k];
	  epT[i] = 0;
	  yield[i] = yieldR_posmm[k];
	  eyield[i] = eyieldR_posmm[k];
	}

    }

  TGraphErrors *tge_posmm = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_posmm->SetMarkerColor(kBlack);
  tge_posmm->SetMarkerStyle(20);

  TMultiGraph *tmg_posmm = new TMultiGraph();
  tmg_posmm->Add(tge_posmm);
  tmg_posmm->Add(pionpos30);
  tmg_posmm->Add(pion44);
  tmg_posmm->Draw("ap");
  tmg_posmm->SetMaximum(1e1);
  tmg_posmm->SetMinimum(1e-7);
  tmg_posmm->GetXaxis()->SetLimits(0.0,6.0);
  tmg_posmm->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_posmm->GetXaxis()->CenterTitle();
  //tmg_posmm->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_posmm->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_posmm->GetYaxis()->CenterTitle();

  TPaveText *tptP_posmm = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_posmm->SetFillColor(10);
  tptP_posmm->SetBorderSize(0);
  TText *textP_posmm = tptP_posmm->AddText(bigcentstring);
  tptP_posmm->Draw();

  TPaveText *tptP_posmm2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_posmm2->SetFillColor(10);
  tptP_posmm2->SetBorderSize(0);
  TText *textP_posmm2 = tptP_posmm2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_posmm2->Draw();

  TLegend *leg _posmm = new TLegend(0.68,0.68,0.88,0.88);
  leg_posmm->SetFillColor(kWhite);
  leg_posmm->SetBorderSize(0);
  leg_posmm->AddEntry(tge_posmm,"#pi^{+}, -- field","p");
  leg_posmm->AddEntry(pionpos30,"#pi^{+}, ppg030","p");
  leg_posmm->AddEntry(pion44,"#pi^{0}, ppg044","p");
  leg_posmm->Draw();

  char gifname_posmm[100];
  sprintf(gifname_posmm,"SpectraFigures/ptpid_%s_posmm_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_posmm[100];
  sprintf(epsname_posmm,"SpectraFigures/ptpid_%s_posmm_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_posmm);
  c1->Print(epsname_posmm);






  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_negmm[i];
	  epT[i] = 0;
	  yield[i] = yield_negmm[i];
	  eyield[i] = eyield_negmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_negmm[k];
	  epT[i] = 0;
	  yield[i] = yieldR_negmm[k];
	  eyield[i] = eyieldR_negmm[k];
	}

    }

  TGraphErrors *tge_negmm = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_negmm->SetMarkerColor(kBlack);
  tge_negmm->SetMarkerStyle(20);

  TMultiGraph *tmg_negmm = new TMultiGraph();
  tmg_negmm->Add(tge_negmm);
  tmg_negmm->Add(pionneg30);
  tmg_negmm->Add(pion44);
  tmg_negmm->Draw("ap");
  tmg_negmm->SetMaximum(1e1);
  tmg_negmm->SetMinimum(1e-7);
  tmg_negmm->GetXaxis()->SetLimits(0.0,6.0);
  tmg_negmm->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_negmm->GetXaxis()->CenterTitle();
  //tmg_negmm->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_negmm->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_negmm->GetYaxis()->CenterTitle();

  TPaveText *tptP_negmm = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_negmm->SetFillColor(10);
  tptP_negmm->SetBorderSize(0);
  TText *textP_negmm = tptP_negmm->AddText(bigcentstring);
  tptP_negmm->Draw();

  TPaveText *tptP_negmm2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_negmm2->SetFillColor(10);
  tptP_negmm2->SetBorderSize(0);
  TText *textP_negmm2 = tptP_negmm2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_negmm2->Draw();

  TLegend *leg _negmm = new TLegend(0.68,0.68,0.88,0.88);
  leg_negmm->SetFillColor(kWhite);
  leg_negmm->SetBorderSize(0);
  leg_negmm->AddEntry(tge_negmm,"#pi^{-}, -- field","p");
  leg_negmm->AddEntry(pionneg30,"#pi^{-}, ppg030","p");
  leg_negmm->AddEntry(pion44,"#pi^{0}, ppg044","p");
  leg_negmm->Draw();

  char gifname_negmm[100];
  sprintf(gifname_negmm,"SpectraFigures/ptpid_%s_negmm_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_negmm[100];
  sprintf(epsname_negmm,"SpectraFigures/ptpid_%s_negmm_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_negmm);
  c1->Print(epsname_negmm);








}





void kaon(int sector=0, int pid=0, int centid=0)
{

  // --- beginning of code

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFillColor(kWhite);
  c1->SetFrameFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameBorderMode(0);
  c1->SetLogy();



  // --- strings for filenames

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");

  char centstring[10];
  sprintf(centstring,"0088"); // "default"
  if(centid==0) sprintf(centstring,"0020");
  if(centid==1) sprintf(centstring,"2040");
  if(centid==2) sprintf(centstring,"4060");
  if(centid==3) sprintf(centstring,"6088");
  if(centid==4) sprintf(centstring,"0088");

  char bigcentstring[50];
  sprintf(bigcentstring,"0088"); // "default"
  //if(centid==0) sprintf(bigcentstring,"0-20%% cent");
  //if(centid==1) sprintf(bigcentstring,"20-40%% cent");
  //if(centid==2) sprintf(bigcentstring,"40-60%% cent");
  //if(centid==3) sprintf(bigcentstring,"60-88%% cent");
  if(centid==0) sprintf(bigcentstring,"0-20%%");
  if(centid==1) sprintf(bigcentstring,"20-40%%");
  if(centid==2) sprintf(bigcentstring,"40-60%%");
  if(centid==3) sprintf(bigcentstring,"60-88%%");
  if(centid==4) sprintf(bigcentstring,"MinBias");

  // ---



  // --- ppg030 stuff

  float pTpos_ppg030[13], yieldpos_ppg030[13], eyieldpos_ppg030[13];
  float pTneg_ppg030[13], yieldneg_ppg030[13], eyieldneg_ppg030[13];
  float ept[13];

  char finposname[30];
  char finnegname[30];
  sprintf(finposname,"ppg030/poskaon_%s.dat",centstring);
  sprintf(finnegname,"ppg030/negkaon_%s.dat",centstring);

  ifstream finpos30(finposname);
  ifstream finneg30(finnegname);

  for(int i=0; i<13; i++)
    {
      ept[i]=0;
      finpos30>>pTpos_ppg030[i]>>yieldpos_ppg030[i]>>eyieldpos_ppg030[i];
      finneg30>>pTneg_ppg030[i]>>yieldneg_ppg030[i]>>eyieldneg_ppg030[i];
    }

  finpos30.close();
  finneg30.close();

  TGraphErrors *kaonpos30 = new TGraphErrors(13,pTpos_ppg030,yieldpos_ppg030,ept,eyieldpos_ppg030);
  kaonpos30->SetMarkerColor(kRed);
  kaonpos30->SetMarkerStyle(20);

  TGraphErrors *kaonneg30 = new TGraphErrors(13,pTneg_ppg030,yieldneg_ppg030,ept,eyieldneg_ppg030);
  kaonneg30->SetMarkerColor(kRed);
  kaonneg30->SetMarkerStyle(20);

  // ---



  // --- input data

  char fnameinpospp[100];
  char fnameinnegpp[100];
  char fnameinposmm[100];
  char fnameinnegmm[100];
  char fnameinposcb[100];
  char fnameinnegcb[100];

  sprintf(fnameinpospp,"Data/ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegpp,"Data/ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinposmm,"Data/ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegmm,"Data/ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinposcb,"Data/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  ifstream finpospp;
  ifstream finnegpp;
  ifstream finposmm;
  ifstream finnegmm;
  ifstream finposcb;
  ifstream finnegcb;

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pT_pospp[100], yield_pospp[100], eyield_pospp[100];
  float pT_negpp[100], yield_negpp[100], eyield_negpp[100];
  float pT_posmm[100], yield_posmm[100], eyield_posmm[100];
  float pT_negmm[100], yield_negmm[100], eyield_negmm[100];
  float pT_poscb[100], yield_poscb[100], eyield_poscb[100];
  float pT_negcb[100], yield_negcb[100], eyield_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pT_pospp[i]>>yield_pospp[i]>>eyield_pospp[i];
      // negpp
      finnegpp>>pT_negpp[i]>>yield_negpp[i]>>eyield_negpp[i];
      // posmm
      finposmm>>pT_posmm[i]>>yield_posmm[i]>>eyield_posmm[i];
      // negmm
      finnegmm>>pT_negmm[i]>>yield_negmm[i]>>eyield_negmm[i];
      // poscb
      finposcb>>pT_poscb[i]>>yield_poscb[i]>>eyield_poscb[i];
      // negcb
      finnegcb>>pT_negcb[i]>>yield_negcb[i]>>eyield_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();



  // --- now input the rebinned data

  sprintf(fnameinpospp,"Data/R5_ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegpp,"Data/R5_ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinposmm,"Data/R5_ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegmm,"Data/R5_ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinposcb,"Data/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pTR_pospp[100], yieldR_pospp[100], eyieldR_pospp[100];
  float pTR_negpp[100], yieldR_negpp[100], eyieldR_negpp[100];
  float pTR_posmm[100], yieldR_posmm[100], eyieldR_posmm[100];
  float pTR_negmm[100], yieldR_negmm[100], eyieldR_negmm[100];
  float pTR_poscb[100], yieldR_poscb[100], eyieldR_poscb[100];
  float pTR_negcb[100], yieldR_negcb[100], eyieldR_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pTR_pospp[i]>>yieldR_pospp[i]>>eyieldR_pospp[i];
      // negpp
      finnegpp>>pTR_negpp[i]>>yieldR_negpp[i]>>eyieldR_negpp[i];
      // posmm
      finposmm>>pTR_posmm[i]>>yieldR_posmm[i]>>eyieldR_posmm[i];
      // negmm
      finnegmm>>pTR_negmm[i]>>yieldR_negmm[i]>>eyieldR_negmm[i];
      // poscb
      finposcb>>pTR_poscb[i]>>yieldR_poscb[i]>>eyieldR_poscb[i];
      // negcb
      finnegcb>>pTR_negcb[i]>>yieldR_negcb[i]>>eyieldR_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();



  // --- now make tgrapherrorses

  float pT[36], epT[36], yield[36], eyield[36];

  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_pospp[i];
	  epT[i] = 0;
	  yield[i] = yield_pospp[i];
	  eyield[i] = eyield_pospp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_pospp[k];
	  epT[i] = 0;
	  yield[i] = yieldR_pospp[k];
	  eyield[i] = eyieldR_pospp[k];
	}

    }

  TGraphErrors *tge_pospp = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_pospp->SetMarkerColor(kBlack);
  tge_pospp->SetMarkerStyle(20);

  TMultiGraph *tmg_pospp = new TMultiGraph();
  tmg_pospp->Add(tge_pospp);
  tmg_pospp->Add(kaonpos30);
  tmg_pospp->Draw("ap");
  tmg_pospp->SetMaximum(1e1);
  tmg_pospp->SetMinimum(1e-7);
  tmg_pospp->GetXaxis()->SetLimits(0.0,6.0);
  tmg_pospp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pospp->GetXaxis()->CenterTitle();
  //tmg_pospp->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_pospp->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_pospp->GetYaxis()->CenterTitle();

  TPaveText *tptP_pospp = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_pospp->SetFillColor(10);
  tptP_pospp->SetBorderSize(0);
  TText *textP_pospp = tptP_pospp->AddText(bigcentstring);
  tptP_pospp->Draw();

  TPaveText *tptP_pospp2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_pospp2->SetFillColor(10);
  tptP_pospp2->SetBorderSize(0);
  TText *textP_pospp2 = tptP_pospp2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_pospp2->Draw();

  TLegend *leg _pospp = new TLegend(0.68,0.68,0.88,0.88);
  leg_pospp->SetFillColor(kWhite);
  leg_pospp->SetBorderSize(0);
  leg_pospp->AddEntry(tge_pospp,"K^{+}, ++ field","p");
  leg_pospp->AddEntry(kaonpos30,"K^{+}, ppg030","p");
  leg_pospp->Draw();

  char gifname_pospp[100];
  sprintf(gifname_pospp,"SpectraFigures/ptpid_%s_pospp_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_pospp[100];
  sprintf(epsname_pospp,"SpectraFigures/ptpid_%s_pospp_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_pospp);
  c1->Print(epsname_pospp);






  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_negpp[i];
	  epT[i] = 0;
	  yield[i] = yield_negpp[i];
	  eyield[i] = eyield_negpp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_negpp[k];
	  epT[i] = 0;
	  yield[i] = yieldR_negpp[k];
	  eyield[i] = eyieldR_negpp[k];
	}

    }

  TGraphErrors *tge_negpp = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_negpp->SetMarkerColor(kBlack);
  tge_negpp->SetMarkerStyle(20);

  TMultiGraph *tmg_negpp = new TMultiGraph();
  tmg_negpp->Add(tge_negpp);
  tmg_negpp->Add(kaonneg30);
  tmg_negpp->Draw("ap");
  tmg_negpp->SetMaximum(1e1);
  tmg_negpp->SetMinimum(1e-7);
  tmg_negpp->GetXaxis()->SetLimits(0.0,6.0);
  tmg_negpp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_negpp->GetXaxis()->CenterTitle();
  //tmg_negpp->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_negpp->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_negpp->GetYaxis()->CenterTitle();

  TPaveText *tptP_negpp = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_negpp->SetFillColor(10);
  tptP_negpp->SetBorderSize(0);
  TText *textP_negpp = tptP_negpp->AddText(bigcentstring);
  tptP_negpp->Draw();

  TPaveText *tptP_negpp2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_negpp2->SetFillColor(10);
  tptP_negpp2->SetBorderSize(0);
  TText *textP_negpp2 = tptP_negpp2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_negpp2->Draw();

  TLegend *leg _negpp = new TLegend(0.68,0.68,0.88,0.88);
  leg_negpp->SetFillColor(kWhite);
  leg_negpp->SetBorderSize(0);
  leg_negpp->AddEntry(tge_negpp,"K^{-}, ++ field","p");
  leg_negpp->AddEntry(kaonneg30,"K^{-}, ppg030","p");
  leg_negpp->Draw();

  char gifname_negpp[100];
  sprintf(gifname_negpp,"SpectraFigures/ptpid_%s_negpp_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_negpp[100];
  sprintf(epsname_negpp,"SpectraFigures/ptpid_%s_negpp_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_negpp);
  c1->Print(epsname_negpp);













  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_posmm[i];
	  epT[i] = 0;
	  yield[i] = yield_posmm[i];
	  eyield[i] = eyield_posmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_posmm[k];
	  epT[i] = 0;
	  yield[i] = yieldR_posmm[k];
	  eyield[i] = eyieldR_posmm[k];
	}

    }

  TGraphErrors *tge_posmm = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_posmm->SetMarkerColor(kBlack);
  tge_posmm->SetMarkerStyle(20);

  TMultiGraph *tmg_posmm = new TMultiGraph();
  tmg_posmm->Add(tge_posmm);
  tmg_posmm->Add(kaonpos30);
  tmg_posmm->Draw("ap");
  tmg_posmm->SetMaximum(1e1);
  tmg_posmm->SetMinimum(1e-7);
  tmg_posmm->GetXaxis()->SetLimits(0.0,6.0);
  tmg_posmm->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_posmm->GetXaxis()->CenterTitle();
  //tmg_posmm->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_posmm->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_posmm->GetYaxis()->CenterTitle();

  TPaveText *tptP_posmm = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_posmm->SetFillColor(10);
  tptP_posmm->SetBorderSize(0);
  TText *textP_posmm = tptP_posmm->AddText(bigcentstring);
  tptP_posmm->Draw();

  TPaveText *tptP_posmm2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_posmm2->SetFillColor(10);
  tptP_posmm2->SetBorderSize(0);
  TText *textP_posmm2 = tptP_posmm2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_posmm2->Draw();

  TLegend *leg _posmm = new TLegend(0.68,0.68,0.88,0.88);
  leg_posmm->SetFillColor(kWhite);
  leg_posmm->SetBorderSize(0);
  leg_posmm->AddEntry(tge_posmm,"K^{+}, -- field","p");
  leg_posmm->AddEntry(kaonpos30,"K^{+}, ppg030","p");
  leg_posmm->Draw();

  char gifname_posmm[100];
  sprintf(gifname_posmm,"SpectraFigures/ptpid_%s_posmm_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_posmm[100];
  sprintf(epsname_posmm,"SpectraFigures/ptpid_%s_posmm_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_posmm);
  c1->Print(epsname_posmm);






  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_negmm[i];
	  epT[i] = 0;
	  yield[i] = yield_negmm[i];
	  eyield[i] = eyield_negmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_negmm[k];
	  epT[i] = 0;
	  yield[i] = yieldR_negmm[k];
	  eyield[i] = eyieldR_negmm[k];
	}

    }

  TGraphErrors *tge_negmm = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_negmm->SetMarkerColor(kBlack);
  tge_negmm->SetMarkerStyle(20);

  TMultiGraph *tmg_negmm = new TMultiGraph();
  tmg_negmm->Add(tge_negmm);
  tmg_negmm->Add(kaonneg30);
  tmg_negmm->Draw("ap");
  tmg_negmm->SetMaximum(1e1);
  tmg_negmm->SetMinimum(1e-7);
  tmg_negmm->GetXaxis()->SetLimits(0.0,6.0);
  tmg_negmm->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_negmm->GetXaxis()->CenterTitle();
  //tmg_negmm->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_negmm->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_negmm->GetYaxis()->CenterTitle();

  TPaveText *tptP_negmm = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_negmm->SetFillColor(10);
  tptP_negmm->SetBorderSize(0);
  TText *textP_negmm = tptP_negmm->AddText(bigcentstring);
  tptP_negmm->Draw();

  TPaveText *tptP_negmm2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_negmm2->SetFillColor(10);
  tptP_negmm2->SetBorderSize(0);
  TText *textP_negmm2 = tptP_negmm2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_negmm2->Draw();

  TLegend *leg _negmm = new TLegend(0.68,0.68,0.88,0.88);
  leg_negmm->SetFillColor(kWhite);
  leg_negmm->SetBorderSize(0);
  leg_negmm->AddEntry(tge_negmm,"K^{-}, -- field","p");
  leg_negmm->AddEntry(kaonneg30,"K^{-}, ppg030","p");
  leg_negmm->Draw();

  char gifname_negmm[100];
  sprintf(gifname_negmm,"SpectraFigures/ptpid_%s_negmm_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_negmm[100];
  sprintf(epsname_negmm,"SpectraFigures/ptpid_%s_negmm_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_negmm);
  c1->Print(epsname_negmm);








}






void proton(int sector=0, int pid=0, int centid=0)
{

  // --- beginning of code

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFillColor(kWhite);
  c1->SetFrameFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameBorderMode(0);
  c1->SetLogy();



  // --- strings for filenames

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");

  char centstring[10];
  sprintf(centstring,"0088"); // "default"
  if(centid==0) sprintf(centstring,"0020");
  if(centid==1) sprintf(centstring,"2040");
  if(centid==2) sprintf(centstring,"4060");
  if(centid==3) sprintf(centstring,"6088");
  if(centid==4) sprintf(centstring,"0088");

  char bigcentstring[50];
  sprintf(bigcentstring,"0088"); // "default"
  //if(centid==0) sprintf(bigcentstring,"0-20%% cent");
  //if(centid==1) sprintf(bigcentstring,"20-40%% cent");
  //if(centid==2) sprintf(bigcentstring,"40-60%% cent");
  //if(centid==3) sprintf(bigcentstring,"60-88%% cent");
  if(centid==0) sprintf(bigcentstring,"0-20%%");
  if(centid==1) sprintf(bigcentstring,"20-40%%");
  if(centid==2) sprintf(bigcentstring,"40-60%%");
  if(centid==3) sprintf(bigcentstring,"60-88%%");
  if(centid==4) sprintf(bigcentstring,"MinBias");

  // ---



  // --- ppg030 stuff

  float pTpos_ppg030[13], yieldpos_ppg030[13], eyieldpos_ppg030[13];
  float pTneg_ppg030[13], yieldneg_ppg030[13], eyieldneg_ppg030[13];
  float ept[13];

  char finposname[30];
  char finnegname[30];
  sprintf(finposname,"ppg030/posproton_%s.dat",centstring);
  sprintf(finnegname,"ppg030/negproton_%s.dat",centstring);

  ifstream finpos30(finposname);
  ifstream finneg30(finnegname);

  for(int i=0; i<13; i++)
    {
      ept[i]=0;
      finpos30>>pTpos_ppg030[i]>>yieldpos_ppg030[i]>>eyieldpos_ppg030[i];
      finneg30>>pTneg_ppg030[i]>>yieldneg_ppg030[i]>>eyieldneg_ppg030[i];
    }

  finpos30.close();
  finneg30.close();

  TGraphErrors *protonpos30 = new TGraphErrors(13,pTpos_ppg030,yieldpos_ppg030,ept,eyieldpos_ppg030);
  protonpos30->SetMarkerColor(kRed);
  protonpos30->SetMarkerStyle(20);

  TGraphErrors *protonneg30 = new TGraphErrors(13,pTneg_ppg030,yieldneg_ppg030,ept,eyieldneg_ppg030);
  protonneg30->SetMarkerColor(kRed);
  protonneg30->SetMarkerStyle(20);

  // ---



  // --- input data

  char fnameinpospp[100];
  char fnameinnegpp[100];
  char fnameinposmm[100];
  char fnameinnegmm[100];
  char fnameinposcb[100];
  char fnameinnegcb[100];

  sprintf(fnameinpospp,"Data/ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegpp,"Data/ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinposmm,"Data/ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegmm,"Data/ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinposcb,"Data/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  ifstream finpospp;
  ifstream finnegpp;
  ifstream finposmm;
  ifstream finnegmm;
  ifstream finposcb;
  ifstream finnegcb;

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pT_pospp[100], yield_pospp[100], eyield_pospp[100];
  float pT_negpp[100], yield_negpp[100], eyield_negpp[100];
  float pT_posmm[100], yield_posmm[100], eyield_posmm[100];
  float pT_negmm[100], yield_negmm[100], eyield_negmm[100];
  float pT_poscb[100], yield_poscb[100], eyield_poscb[100];
  float pT_negcb[100], yield_negcb[100], eyield_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pT_pospp[i]>>yield_pospp[i]>>eyield_pospp[i];
      // negpp
      finnegpp>>pT_negpp[i]>>yield_negpp[i]>>eyield_negpp[i];
      // posmm
      finposmm>>pT_posmm[i]>>yield_posmm[i]>>eyield_posmm[i];
      // negmm
      finnegmm>>pT_negmm[i]>>yield_negmm[i]>>eyield_negmm[i];
      // poscb
      finposcb>>pT_poscb[i]>>yield_poscb[i]>>eyield_poscb[i];
      // negcb
      finnegcb>>pT_negcb[i]>>yield_negcb[i]>>eyield_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();



  // --- now input the rebinned data

  sprintf(fnameinpospp,"Data/R5_ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegpp,"Data/R5_ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinposmm,"Data/R5_ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegmm,"Data/R5_ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinposcb,"Data/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pTR_pospp[100], yieldR_pospp[100], eyieldR_pospp[100];
  float pTR_negpp[100], yieldR_negpp[100], eyieldR_negpp[100];
  float pTR_posmm[100], yieldR_posmm[100], eyieldR_posmm[100];
  float pTR_negmm[100], yieldR_negmm[100], eyieldR_negmm[100];
  float pTR_poscb[100], yieldR_poscb[100], eyieldR_poscb[100];
  float pTR_negcb[100], yieldR_negcb[100], eyieldR_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pTR_pospp[i]>>yieldR_pospp[i]>>eyieldR_pospp[i];
      // negpp
      finnegpp>>pTR_negpp[i]>>yieldR_negpp[i]>>eyieldR_negpp[i];
      // posmm
      finposmm>>pTR_posmm[i]>>yieldR_posmm[i]>>eyieldR_posmm[i];
      // negmm
      finnegmm>>pTR_negmm[i]>>yieldR_negmm[i]>>eyieldR_negmm[i];
      // poscb
      finposcb>>pTR_poscb[i]>>yieldR_poscb[i]>>eyieldR_poscb[i];
      // negcb
      finnegcb>>pTR_negcb[i]>>yieldR_negcb[i]>>eyieldR_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();



  // --- now make tgrapherrorses

  float pT[36], epT[36], yield[36], eyield[36];

  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_pospp[i];
	  epT[i] = 0;
	  yield[i] = yield_pospp[i];
	  eyield[i] = eyield_pospp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_pospp[k];
	  epT[i] = 0;
	  yield[i] = yieldR_pospp[k];
	  eyield[i] = eyieldR_pospp[k];
	}

    }

  TGraphErrors *tge_pospp = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_pospp->SetMarkerColor(kBlack);
  tge_pospp->SetMarkerStyle(20);

  TMultiGraph *tmg_pospp = new TMultiGraph();
  tmg_pospp->Add(tge_pospp);
  tmg_pospp->Add(protonpos30);
  tmg_pospp->Draw("ap");
  tmg_pospp->SetMaximum(1e1);
  tmg_pospp->SetMinimum(1e-7);
  tmg_pospp->GetXaxis()->SetLimits(0.0,6.0);
  tmg_pospp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pospp->GetXaxis()->CenterTitle();
  //tmg_pospp->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_pospp->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_pospp->GetYaxis()->CenterTitle();

  TPaveText *tptP_pospp = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_pospp->SetFillColor(10);
  tptP_pospp->SetBorderSize(0);
  TText *textP_pospp = tptP_pospp->AddText(bigcentstring);
  tptP_pospp->Draw();

  TPaveText *tptP_pospp2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_pospp2->SetFillColor(10);
  tptP_pospp2->SetBorderSize(0);
  TText *textP_pospp2 = tptP_pospp2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_pospp2->Draw();

  TLegend *leg _pospp = new TLegend(0.68,0.68,0.88,0.88);
  leg_pospp->SetFillColor(kWhite);
  leg_pospp->SetBorderSize(0);
  leg_pospp->AddEntry(tge_pospp,"p, ++ field","p");
  leg_pospp->AddEntry(protonpos30,"p, ppg030","p");
  leg_pospp->Draw();

  char gifname_pospp[100];
  sprintf(gifname_pospp,"SpectraFigures/ptpid_%s_pospp_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_pospp[100];
  sprintf(epsname_pospp,"SpectraFigures/ptpid_%s_pospp_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_pospp);
  c1->Print(epsname_pospp);






  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_negpp[i];
	  epT[i] = 0;
	  yield[i] = yield_negpp[i];
	  eyield[i] = eyield_negpp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_negpp[k];
	  epT[i] = 0;
	  yield[i] = yieldR_negpp[k];
	  eyield[i] = eyieldR_negpp[k];
	}

    }

  TGraphErrors *tge_negpp = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_negpp->SetMarkerColor(kBlack);
  tge_negpp->SetMarkerStyle(20);

  TMultiGraph *tmg_negpp = new TMultiGraph();
  tmg_negpp->Add(tge_negpp);
  tmg_negpp->Add(protonneg30);
  tmg_negpp->Draw("ap");
  tmg_negpp->SetMaximum(1e1);
  tmg_negpp->SetMinimum(1e-7);
  tmg_negpp->GetXaxis()->SetLimits(0.0,6.0);
  tmg_negpp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_negpp->GetXaxis()->CenterTitle();
  //tmg_negpp->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_negpp->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_negpp->GetYaxis()->CenterTitle();

  TPaveText *tptP_negpp = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_negpp->SetFillColor(10);
  tptP_negpp->SetBorderSize(0);
  TText *textP_negpp = tptP_negpp->AddText(bigcentstring);
  tptP_negpp->Draw();

  TPaveText *tptP_negpp2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_negpp2->SetFillColor(10);
  tptP_negpp2->SetBorderSize(0);
  TText *textP_negpp2 = tptP_negpp2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_negpp2->Draw();

  TLegend *leg _negpp = new TLegend(0.68,0.68,0.88,0.88);
  leg_negpp->SetFillColor(kWhite);
  leg_negpp->SetBorderSize(0);
  leg_negpp->AddEntry(tge_negpp,"#bar{p}, ++ field","p");
  leg_negpp->AddEntry(protonneg30,"#bar{p}, ppg030","p");
  leg_negpp->Draw();

  char gifname_negpp[100];
  sprintf(gifname_negpp,"SpectraFigures/ptpid_%s_negpp_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_negpp[100];
  sprintf(epsname_negpp,"SpectraFigures/ptpid_%s_negpp_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_negpp);
  c1->Print(epsname_negpp);













  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_posmm[i];
	  epT[i] = 0;
	  yield[i] = yield_posmm[i];
	  eyield[i] = eyield_posmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_posmm[k];
	  epT[i] = 0;
	  yield[i] = yieldR_posmm[k];
	  eyield[i] = eyieldR_posmm[k];
	}

    }

  TGraphErrors *tge_posmm = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_posmm->SetMarkerColor(kBlack);
  tge_posmm->SetMarkerStyle(20);

  TMultiGraph *tmg_posmm = new TMultiGraph();
  tmg_posmm->Add(tge_posmm);
  tmg_posmm->Add(protonpos30);
  tmg_posmm->Draw("ap");
  tmg_posmm->SetMaximum(1e1);
  tmg_posmm->SetMinimum(1e-7);
  tmg_posmm->GetXaxis()->SetLimits(0.0,6.0);
  tmg_posmm->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_posmm->GetXaxis()->CenterTitle();
  //tmg_posmm->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_posmm->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_posmm->GetYaxis()->CenterTitle();

  TPaveText *tptP_posmm = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_posmm->SetFillColor(10);
  tptP_posmm->SetBorderSize(0);
  TText *textP_posmm = tptP_posmm->AddText(bigcentstring);
  tptP_posmm->Draw();

  TPaveText *tptP_posmm2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_posmm2->SetFillColor(10);
  tptP_posmm2->SetBorderSize(0);
  TText *textP_posmm2 = tptP_posmm2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_posmm2->Draw();

  TLegend *leg _posmm = new TLegend(0.68,0.68,0.88,0.88);
  leg_posmm->SetFillColor(kWhite);
  leg_posmm->SetBorderSize(0);
  leg_posmm->AddEntry(tge_posmm,"p, -- field","p");
  leg_posmm->AddEntry(protonpos30,"p, ppg030","p");
  leg_posmm->Draw();

  char gifname_posmm[100];
  sprintf(gifname_posmm,"SpectraFigures/ptpid_%s_posmm_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_posmm[100];
  sprintf(epsname_posmm,"SpectraFigures/ptpid_%s_posmm_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_posmm);
  c1->Print(epsname_posmm);






  for(int i=0; i<36; i++)
    {
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<30)
	{
	  pT[i] = pT_negmm[i];
	  epT[i] = 0;
	  yield[i] = yield_negmm[i];
	  eyield[i] = eyield_negmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pT[i] = pTR_negmm[k];
	  epT[i] = 0;
	  yield[i] = yieldR_negmm[k];
	  eyield[i] = eyieldR_negmm[k];
	}

    }

  TGraphErrors *tge_negmm = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_negmm->SetMarkerColor(kBlack);
  tge_negmm->SetMarkerStyle(20);

  TMultiGraph *tmg_negmm = new TMultiGraph();
  tmg_negmm->Add(tge_negmm);
  tmg_negmm->Add(protonneg30);
  tmg_negmm->Draw("ap");
  tmg_negmm->SetMaximum(1e1);
  tmg_negmm->SetMinimum(1e-7);
  tmg_negmm->GetXaxis()->SetLimits(0.0,6.0);
  tmg_negmm->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_negmm->GetXaxis()->CenterTitle();
  //tmg_negmm->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_negmm->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_negmm->GetYaxis()->CenterTitle();

  TPaveText *tptP_negmm = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  tptP_negmm->SetFillColor(10);
  tptP_negmm->SetBorderSize(0);
  TText *textP_negmm = tptP_negmm->AddText(bigcentstring);
  tptP_negmm->Draw();

  TPaveText *tptP_negmm2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  tptP_negmm2->SetFillColor(10);
  tptP_negmm2->SetBorderSize(0);
  TText *textP_negmm2 = tptP_negmm2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_negmm2->Draw();

  TLegend *leg _negmm = new TLegend(0.68,0.68,0.88,0.88);
  leg_negmm->SetFillColor(kWhite);
  leg_negmm->SetBorderSize(0);
  leg_negmm->AddEntry(tge_negmm,"#bar{p}, -- field","p");
  leg_negmm->AddEntry(protonneg30,"#bar{p}, ppg030","p");
  leg_negmm->Draw();

  char gifname_negmm[100];
  sprintf(gifname_negmm,"SpectraFigures/ptpid_%s_negmm_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_negmm[100];
  sprintf(epsname_negmm,"SpectraFigures/ptpid_%s_negmm_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_negmm);
  c1->Print(epsname_negmm);








}

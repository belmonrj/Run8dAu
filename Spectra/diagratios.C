void diagratios()
{

  cout<<"hello!  now drawing diagnostic ratios!"<<endl;
  
  // for(int icent=0; icent<5; icent++)
  //   {
  //     for(int ipid=0; ipid<6; ipid++)
  //  	{
  // 	  doitS(ipid,icent);
  //  	  for(int isec=0; isec<3; isec++)
  //  	    {
  //  	      doitC(isec,ipid,icent);
  //  	      //cout<<"doit("<<isec<<","<<ipid<<","<<icent<<");"<<endl;
  //  	    }
  //  	}
  //   }
  

  // for(int ipid=0; ipid<6; ipid++)
  //   {
  //     doitS(ipid,4);
  //     for(int isec=0; isec<3; isec++)
  // 	{
  // 	  doitC(isec,ipid,4);
  // 	  //cout<<"doit("<<isec<<","<<ipid<<","<<icent<<");"<<endl;
  // 	}
  //   }
  

  for(int ipid=0; ipid<6; ipid++)
    {
      doitS(ipid,4);
      doitC(0,ipid,4);
    }
  

  // doitC(0,0,0);
  // doitC(0,2,0);
  // doitC(0,4,0);

  // doitS(0,0);
  // doitS(2,0);
  // doitS(4,0);

  cout<<"done!  have a nice day!"<<endl;

}

void doitC(int sector=0, int pid=0, int centid=0)
{

  // --- beginning of code

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFillColor(kWhite);
  c1->SetFrameFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameBorderMode(0);
  c1->SetGridx();
  c1->SetGridy();
  //c1->SetLogy();



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

  float pT[36], epT[36], ratio[36], eratio[36];
  float pTA[36], epTA[36], yieldA[36], eyieldA[36];
  float pTB[36], epTB[36], yieldB[36], eyieldB[36];

  for(int i=0; i<36; i++)
    {
      // A
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<30)
	{
	  pTA[i] = pT_posmm[i];
	  epTA[i] = 0;
	  yieldA[i] = yield_posmm[i];
	  eyieldA[i] = eyield_posmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTA[i] = pTR_posmm[k];
	  epTA[i] = 0;
	  yieldA[i] = yieldR_posmm[k];
	  eyieldA[i] = eyieldR_posmm[k];
	}
      // B
      pTB[i] = -9;
      epTB[i] = 0;
      yieldB[i] = -9;
      eyieldB[i] = 0;
      if(i<30)
	{
	  pTB[i] = pT_pospp[i];
	  epTB[i] = 0;
	  yieldB[i] = yield_pospp[i];
	  eyieldB[i] = eyield_pospp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTB[i] = pTR_pospp[k];
	  epTB[i] = 0;
	  yieldB[i] = yieldR_pospp[k];
	  eyieldB[i] = eyieldR_pospp[k];
	}
      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT[i] = pTA[i];
	  epT[i] = 0;
	  ratio[i] = -9;
	  eratio[i] = 0;
	}
    }

  TGraphErrors *tge_posratio = new TGraphErrors(36,pT,ratio,epT,eratio);
  tge_posratio->SetMarkerColor(kRed);
  tge_posratio->SetMarkerStyle(20);

  // ---

  for(int i=0; i<36; i++)
    {
      // A
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<30)
	{
	  pTA[i] = pT_negpp[i];
	  epTA[i] = 0;
	  yieldA[i] = yield_negpp[i];
	  eyieldA[i] = eyield_negpp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTA[i] = pTR_negpp[k];
	  epTA[i] = 0;
	  yieldA[i] = yieldR_negpp[k];
	  eyieldA[i] = eyieldR_negpp[k];
	}
      // B
      pTB[i] = -9;
      epTB[i] = 0;
      yieldB[i] = -9;
      eyieldB[i] = 0;
      if(i<30)
	{
	  pTB[i] = pT_negmm[i];
	  epTB[i] = 0;
	  yieldB[i] = yield_negmm[i];
	  eyieldB[i] = eyield_negmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTB[i] = pTR_negmm[k];
	  epTB[i] = 0;
	  yieldB[i] = yieldR_negmm[k];
	  eyieldB[i] = eyieldR_negmm[k];
	}
      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT[i] = pTA[i];
	  epT[i] = 0;
	  ratio[i] = -9;
	  eratio[i] = 0;
	}
    }

  TGraphErrors *tge_negratio = new TGraphErrors(36,pT,ratio,epT,eratio);
  tge_negratio->SetMarkerColor(kBlue);
  tge_negratio->SetMarkerStyle(21);

  // ---





  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tge_posratio);
  tmg->Add(tge_negratio);
  tmg->Draw("ap");
  tmg->SetMaximum(2.0);
  tmg->SetMinimum(0.0);
  tmg->GetXaxis()->SetLimits(0.0,6.0);
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetXaxis()->CenterTitle();
  tmg->GetYaxis()->SetTitle("Ratio");
  tmg->GetYaxis()->CenterTitle();

  TPaveText *tptP = new TPaveText(0.5, 0.1, 1.5, 0.3, "br");
  tptP->SetFillColor(10);
  tptP->SetBorderSize(0);
  TText *textP = tptP->AddText(bigcentstring);
  tptP->Draw();

  TPaveText *tptP2 = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  tptP2->SetFillColor(10);
  tptP2->SetBorderSize(0);
  TText *textP2 = tptP2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP2->Draw();

  TLegend *leg  = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      leg->AddEntry(tge_posratio,"#pi^{+}, --/++ field","p");
      leg->AddEntry(tge_negratio,"#pi^{-}, ++/-- field","p");
    }
  if(pid==2||pid==3)
    {
      leg->AddEntry(tge_posratio,"K^{+}, --/++ field","p");
      leg->AddEntry(tge_negratio,"K^{-}, ++/-- field","p");
    }
  if(pid==4||pid==5)
    {
      leg->AddEntry(tge_posratio,"p, --/++ field","p");
      leg->AddEntry(tge_negratio,"#bar{p}, ++/-- field","p");
    }
  leg->Draw();

  char gifname[100];
  sprintf(gifname,"RatioFigures/chargefield_%s_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname[100];
  sprintf(epsname,"RatioFigures/chargefield_%s_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname);
  c1->Print(epsname);



}




void doitS(int pid=0, int centid=0)
{

  // --- beginning of code

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFillColor(kWhite);
  c1->SetFrameFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameBorderMode(0);
  c1->SetGridx();
  c1->SetGridy();
  //c1->SetLogy();



  // --- strings for filenames

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






  // --- input data

  char fnameinpospp[100];
  char fnameinnegpp[100];
  char fnameinposmm[100];
  char fnameinnegmm[100];
  char fnameinposcb[100];
  char fnameinnegcb[100];

  ifstream finpospp;
  ifstream finnegpp;
  ifstream finposmm;
  ifstream finnegmm;
  ifstream finposcb;
  ifstream finnegcb;

  sprintf(fnameinpospp,"Data/ptpid_tofw_w1_pos_%d_dis_cent%s_pp.dat",pid,centstring);
  sprintf(fnameinnegpp,"Data/ptpid_tofw_w1_neg_%d_dis_cent%s_pp.dat",pid,centstring);
  sprintf(fnameinposmm,"Data/ptpid_tofw_w1_pos_%d_dis_cent%s_mm.dat",pid,centstring);
  sprintf(fnameinnegmm,"Data/ptpid_tofw_w1_neg_%d_dis_cent%s_mm.dat",pid,centstring);
  sprintf(fnameinposcb,"Data/ptpid_tofw_w1_pos_%d_dis_cent%s.dat",pid,centstring);
  sprintf(fnameinnegcb,"Data/ptpid_tofw_w1_neg_%d_dis_cent%s.dat",pid,centstring);

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pT_w1_pospp[100], yield_w1_pospp[100], eyield_w1_pospp[100];
  float pT_w1_negpp[100], yield_w1_negpp[100], eyield_w1_negpp[100];
  float pT_w1_posmm[100], yield_w1_posmm[100], eyield_w1_posmm[100];
  float pT_w1_negmm[100], yield_w1_negmm[100], eyield_w1_negmm[100];
  float pT_w1_poscb[100], yield_w1_poscb[100], eyield_w1_poscb[100];
  float pT_w1_negcb[100], yield_w1_negcb[100], eyield_w1_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pT_w1_pospp[i]>>yield_w1_pospp[i]>>eyield_w1_pospp[i];
      // negpp
      finnegpp>>pT_w1_negpp[i]>>yield_w1_negpp[i]>>eyield_w1_negpp[i];
      // posmm
      finposmm>>pT_w1_posmm[i]>>yield_w1_posmm[i]>>eyield_w1_posmm[i];
      // negmm
      finnegmm>>pT_w1_negmm[i]>>yield_w1_negmm[i]>>eyield_w1_negmm[i];
      // poscb
      finposcb>>pT_w1_poscb[i]>>yield_w1_poscb[i]>>eyield_w1_poscb[i];
      // negcb
      finnegcb>>pT_w1_negcb[i]>>yield_w1_negcb[i]>>eyield_w1_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();

  sprintf(fnameinpospp,"Data/ptpid_tofw_w2_pos_%d_dis_cent%s_pp.dat",pid,centstring);
  sprintf(fnameinnegpp,"Data/ptpid_tofw_w2_neg_%d_dis_cent%s_pp.dat",pid,centstring);
  sprintf(fnameinposmm,"Data/ptpid_tofw_w2_pos_%d_dis_cent%s_mm.dat",pid,centstring);
  sprintf(fnameinnegmm,"Data/ptpid_tofw_w2_neg_%d_dis_cent%s_mm.dat",pid,centstring);
  sprintf(fnameinposcb,"Data/ptpid_tofw_w2_pos_%d_dis_cent%s.dat",pid,centstring);
  sprintf(fnameinnegcb,"Data/ptpid_tofw_w2_neg_%d_dis_cent%s.dat",pid,centstring);

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pT_w2_pospp[100], yield_w2_pospp[100], eyield_w2_pospp[100];
  float pT_w2_negpp[100], yield_w2_negpp[100], eyield_w2_negpp[100];
  float pT_w2_posmm[100], yield_w2_posmm[100], eyield_w2_posmm[100];
  float pT_w2_negmm[100], yield_w2_negmm[100], eyield_w2_negmm[100];
  float pT_w2_poscb[100], yield_w2_poscb[100], eyield_w2_poscb[100];
  float pT_w2_negcb[100], yield_w2_negcb[100], eyield_w2_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pT_w2_pospp[i]>>yield_w2_pospp[i]>>eyield_w2_pospp[i];
      // negpp
      finnegpp>>pT_w2_negpp[i]>>yield_w2_negpp[i]>>eyield_w2_negpp[i];
      // posmm
      finposmm>>pT_w2_posmm[i]>>yield_w2_posmm[i]>>eyield_w2_posmm[i];
      // negmm
      finnegmm>>pT_w2_negmm[i]>>yield_w2_negmm[i]>>eyield_w2_negmm[i];
      // poscb
      finposcb>>pT_w2_poscb[i]>>yield_w2_poscb[i]>>eyield_w2_poscb[i];
      // negcb
      finnegcb>>pT_w2_negcb[i]>>yield_w2_negcb[i]>>eyield_w2_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();



  // --- now input the rebinned data

  sprintf(fnameinpospp,"Data/R5_ptpid_tofw_w1_pos_%d_dis_cent%s_pp.dat",pid,centstring);
  sprintf(fnameinnegpp,"Data/R5_ptpid_tofw_w1_neg_%d_dis_cent%s_pp.dat",pid,centstring);
  sprintf(fnameinposmm,"Data/R5_ptpid_tofw_w1_pos_%d_dis_cent%s_mm.dat",pid,centstring);
  sprintf(fnameinnegmm,"Data/R5_ptpid_tofw_w1_neg_%d_dis_cent%s_mm.dat",pid,centstring);
  sprintf(fnameinposcb,"Data/R5_ptpid_tofw_w1_pos_%d_dis_cent%s.dat",pid,centstring);
  sprintf(fnameinnegcb,"Data/R5_ptpid_tofw_w1_neg_%d_dis_cent%s.dat",pid,centstring);

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pTR_w1_pospp[100], yieldR_w1_pospp[100], eyieldR_w1_pospp[100];
  float pTR_w1_negpp[100], yieldR_w1_negpp[100], eyieldR_w1_negpp[100];
  float pTR_w1_posmm[100], yieldR_w1_posmm[100], eyieldR_w1_posmm[100];
  float pTR_w1_negmm[100], yieldR_w1_negmm[100], eyieldR_w1_negmm[100];
  float pTR_w1_poscb[100], yieldR_w1_poscb[100], eyieldR_w1_poscb[100];
  float pTR_w1_negcb[100], yieldR_w1_negcb[100], eyieldR_w1_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pTR_w1_pospp[i]>>yieldR_w1_pospp[i]>>eyieldR_w1_pospp[i];
      // negpp
      finnegpp>>pTR_w1_negpp[i]>>yieldR_w1_negpp[i]>>eyieldR_w1_negpp[i];
      // posmm
      finposmm>>pTR_w1_posmm[i]>>yieldR_w1_posmm[i]>>eyieldR_w1_posmm[i];
      // negmm
      finnegmm>>pTR_w1_negmm[i]>>yieldR_w1_negmm[i]>>eyieldR_w1_negmm[i];
      // poscb
      finposcb>>pTR_w1_poscb[i]>>yieldR_w1_poscb[i]>>eyieldR_w1_poscb[i];
      // negcb
      finnegcb>>pTR_w1_negcb[i]>>yieldR_w1_negcb[i]>>eyieldR_w1_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();

  sprintf(fnameinpospp,"Data/R5_ptpid_tofw_w2_pos_%d_dis_cent%s_pp.dat",pid,centstring);
  sprintf(fnameinnegpp,"Data/R5_ptpid_tofw_w2_neg_%d_dis_cent%s_pp.dat",pid,centstring);
  sprintf(fnameinposmm,"Data/R5_ptpid_tofw_w2_pos_%d_dis_cent%s_mm.dat",pid,centstring);
  sprintf(fnameinnegmm,"Data/R5_ptpid_tofw_w2_neg_%d_dis_cent%s_mm.dat",pid,centstring);
  sprintf(fnameinposcb,"Data/R5_ptpid_tofw_w2_pos_%d_dis_cent%s.dat",pid,centstring);
  sprintf(fnameinnegcb,"Data/R5_ptpid_tofw_w2_neg_%d_dis_cent%s.dat",pid,centstring);

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pTR_w2_pospp[100], yieldR_w2_pospp[100], eyieldR_w2_pospp[100];
  float pTR_w2_negpp[100], yieldR_w2_negpp[100], eyieldR_w2_negpp[100];
  float pTR_w2_posmm[100], yieldR_w2_posmm[100], eyieldR_w2_posmm[100];
  float pTR_w2_negmm[100], yieldR_w2_negmm[100], eyieldR_w2_negmm[100];
  float pTR_w2_poscb[100], yieldR_w2_poscb[100], eyieldR_w2_poscb[100];
  float pTR_w2_negcb[100], yieldR_w2_negcb[100], eyieldR_w2_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pTR_w2_pospp[i]>>yieldR_w2_pospp[i]>>eyieldR_w2_pospp[i];
      // negpp
      finnegpp>>pTR_w2_negpp[i]>>yieldR_w2_negpp[i]>>eyieldR_w2_negpp[i];
      // posmm
      finposmm>>pTR_w2_posmm[i]>>yieldR_w2_posmm[i]>>eyieldR_w2_posmm[i];
      // negmm
      finnegmm>>pTR_w2_negmm[i]>>yieldR_w2_negmm[i]>>eyieldR_w2_negmm[i];
      // poscb
      finposcb>>pTR_w2_poscb[i]>>yieldR_w2_poscb[i]>>eyieldR_w2_poscb[i];
      // negcb
      finnegcb>>pTR_w2_negcb[i]>>yieldR_w2_negcb[i]>>eyieldR_w2_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();



  // --- now make tgrapherrorses

  float pT[36], epT[36], ratio[36], eratio[36];
  float pTA[36], epTA[36], yieldA[36], eyieldA[36];
  float pTB[36], epTB[36], yieldB[36], eyieldB[36];

  for(int i=0; i<36; i++)
    {
      // A
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<30)
	{
	  pTA[i] = pT_w1_pospp[i];
	  epTA[i] = 0;
	  yieldA[i] = yield_w1_pospp[i];
	  eyieldA[i] = eyield_w1_pospp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTA[i] = pTR_w1_pospp[k];
	  epTA[i] = 0;
	  yieldA[i] = yieldR_w1_pospp[k];
	  eyieldA[i] = eyieldR_w1_pospp[k];
	}
      // B
      pTB[i] = -9;
      epTB[i] = 0;
      yieldB[i] = -9;
      eyieldB[i] = 0;
      if(i<30)
	{
	  pTB[i] = pT_w2_pospp[i];
	  epTB[i] = 0;
	  yieldB[i] = yield_w2_pospp[i];
	  eyieldB[i] = eyield_w2_pospp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTB[i] = pTR_w2_pospp[k];
	  epTB[i] = 0;
	  yieldB[i] = yieldR_w2_pospp[k];
	  eyieldB[i] = eyieldR_w2_pospp[k];
	}
      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT[i] = pTA[i];
	  epT[i] = 0;
	  ratio[i] = -9;
	  eratio[i] = 0;
	}
    }

  TGraphErrors *tge_posppratio = new TGraphErrors(36,pT,ratio,epT,eratio);
  tge_posppratio->SetMarkerColor(kRed);
  tge_posppratio->SetMarkerStyle(20);

  // ---

  for(int i=0; i<36; i++)
    {
      // A
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<30)
	{
	  pTA[i] = pT_w1_negpp[i];
	  epTA[i] = 0;
	  yieldA[i] = yield_w1_negpp[i];
	  eyieldA[i] = eyield_w1_negpp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTA[i] = pTR_w1_negpp[k];
	  epTA[i] = 0;
	  yieldA[i] = yieldR_w1_negpp[k];
	  eyieldA[i] = eyieldR_w1_negpp[k];
	}
      // B
      pTB[i] = -9;
      epTB[i] = 0;
      yieldB[i] = -9;
      eyieldB[i] = 0;
      if(i<30)
	{
	  pTB[i] = pT_w2_negpp[i];
	  epTB[i] = 0;
	  yieldB[i] = yield_w2_negpp[i];
	  eyieldB[i] = eyield_w2_negpp[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTB[i] = pTR_w2_negpp[k];
	  epTB[i] = 0;
	  yieldB[i] = yieldR_w2_negpp[k];
	  eyieldB[i] = eyieldR_w2_negpp[k];
	}
      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT[i] = pTA[i];
	  epT[i] = 0;
	  ratio[i] = -9;
	  eratio[i] = 0;
	}
    }

  TGraphErrors *tge_negppratio = new TGraphErrors(36,pT,ratio,epT,eratio);
  tge_negppratio->SetMarkerColor(kBlue);
  tge_negppratio->SetMarkerStyle(21);

  // ---





  TMultiGraph *tmg_pp = new TMultiGraph();
  tmg_pp->Add(tge_posppratio);
  tmg_pp->Add(tge_negppratio);
  tmg_pp->Draw("ap");
  tmg_pp->SetMaximum(2.0);
  tmg_pp->SetMinimum(0.0);
  tmg_pp->GetXaxis()->SetLimits(0.0,6.0);
  tmg_pp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pp->GetXaxis()->CenterTitle();
  tmg_pp->GetYaxis()->SetTitle("Ratio");
  tmg_pp->GetYaxis()->CenterTitle();

  TPaveText *tptP_pp = new TPaveText(0.5, 0.1, 1.5, 0.3, "br");
  tptP_pp->SetFillColor(10);
  tptP_pp->SetBorderSize(0);
  TText *textP_pp = tptP_pp->AddText(bigcentstring);
  tptP_pp->Draw();

  TPaveText *tptP_pp2 = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  tptP_pp2->SetFillColor(10);
  tptP_pp2->SetBorderSize(0);
  TText *textP_pp2 = tptP_pp2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_pp2->Draw();

  TLegend *leg_pp  = new TLegend(0.58,0.72,0.88,0.88);
  leg_pp->SetFillColor(kWhite);
  leg_pp->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      leg_pp->AddEntry(tge_posppratio,"#pi^{+}, w1/w2, ++ field","p");
      leg_pp->AddEntry(tge_negppratio,"#pi^{-}, w1/w2, ++ field","p");
    }
  if(pid==2||pid==3)
    {
      leg_pp->AddEntry(tge_posppratio,"K^{+}, w1/w2, ++ field","p");
      leg_pp->AddEntry(tge_negppratio,"K^{-}, w1/w2, ++ field","p");
    }
  if(pid==4||pid==5)
    {
      leg_pp->AddEntry(tge_posppratio,"p, w1/w2, ++ field","p");
      leg_pp->AddEntry(tge_negppratio,"#bar{p}, w1/w2, ++ field","p");
    }
  leg_pp->Draw();

  char gifname_pp[100];
  sprintf(gifname_pp,"RatioFigures/sector_pp_%d_dis_cent%s.gif",pid,centstring);
  char epsname_pp[100];
  sprintf(epsname_pp,"RatioFigures/sector_pp_%d_dis_cent%s.eps",pid,centstring);

  c1->Print(gifname_pp);
  c1->Print(epsname_pp);








  for(int i=0; i<36; i++)
    {
      // A
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<30)
	{
	  pTA[i] = pT_w1_posmm[i];
	  epTA[i] = 0;
	  yieldA[i] = yield_w1_posmm[i];
	  eyieldA[i] = eyield_w1_posmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTA[i] = pTR_w1_posmm[k];
	  epTA[i] = 0;
	  yieldA[i] = yieldR_w1_posmm[k];
	  eyieldA[i] = eyieldR_w1_posmm[k];
	}
      // B
      pTB[i] = -9;
      epTB[i] = 0;
      yieldB[i] = -9;
      eyieldB[i] = 0;
      if(i<30)
	{
	  pTB[i] = pT_w2_posmm[i];
	  epTB[i] = 0;
	  yieldB[i] = yield_w2_posmm[i];
	  eyieldB[i] = eyield_w2_posmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTB[i] = pTR_w2_posmm[k];
	  epTB[i] = 0;
	  yieldB[i] = yieldR_w2_posmm[k];
	  eyieldB[i] = eyieldR_w2_posmm[k];
	}
      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT[i] = pTA[i];
	  epT[i] = 0;
	  ratio[i] = -9;
	  eratio[i] = 0;
	}
    }

  TGraphErrors *tge_posmmratio = new TGraphErrors(36,pT,ratio,epT,eratio);
  tge_posmmratio->SetMarkerColor(kRed);
  tge_posmmratio->SetMarkerStyle(20);

  // ---

  for(int i=0; i<36; i++)
    {
      // A
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<30)
	{
	  pTA[i] = pT_w1_negmm[i];
	  epTA[i] = 0;
	  yieldA[i] = yield_w1_negmm[i];
	  eyieldA[i] = eyield_w1_negmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTA[i] = pTR_w1_negmm[k];
	  epTA[i] = 0;
	  yieldA[i] = yieldR_w1_negmm[k];
	  eyieldA[i] = eyieldR_w1_negmm[k];
	}
      // B
      pTB[i] = -9;
      epTB[i] = 0;
      yieldB[i] = -9;
      eyieldB[i] = 0;
      if(i<30)
	{
	  pTB[i] = pT_w2_negmm[i];
	  epTB[i] = 0;
	  yieldB[i] = yield_w2_negmm[i];
	  eyieldB[i] = eyield_w2_negmm[i];
	}
      int k=i-24;
      if(i>29)
	{
	  pTB[i] = pTR_w2_negmm[k];
	  epTB[i] = 0;
	  yieldB[i] = yieldR_w2_negmm[k];
	  eyieldB[i] = eyieldR_w2_negmm[k];
	}
      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT[i] = pTA[i];
	  epT[i] = 0;
	  ratio[i] = -9;
	  eratio[i] = 0;
	}
    }

  TGraphErrors *tge_negmmratio = new TGraphErrors(36,pT,ratio,epT,eratio);
  tge_negmmratio->SetMarkerColor(kBlue);
  tge_negmmratio->SetMarkerStyle(21);

  // ---





  TMultiGraph *tmg_mm = new TMultiGraph();
  tmg_mm->Add(tge_posmmratio);
  tmg_mm->Add(tge_negmmratio);
  tmg_mm->Draw("ap");
  tmg_mm->SetMaximum(2.0);
  tmg_mm->SetMinimum(0.0);
  tmg_mm->GetXaxis()->SetLimits(0.0,6.0);
  tmg_mm->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_mm->GetXaxis()->CenterTitle();
  tmg_mm->GetYaxis()->SetTitle("Ratio");
  tmg_mm->GetYaxis()->CenterTitle();

  TPaveText *tptP_mm = new TPaveText(0.5, 0.1, 1.5, 0.3, "br");
  tptP_mm->SetFillColor(10);
  tptP_mm->SetBorderSize(0);
  TText *textP_mm = tptP_mm->AddText(bigcentstring);
  tptP_mm->Draw();

  TPaveText *tptP_mm2 = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  tptP_mm2->SetFillColor(10);
  tptP_mm2->SetBorderSize(0);
  TText *textP_mm2 = tptP_mm2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_mm2->Draw();

  TLegend *leg_mm  = new TLegend(0.58,0.72,0.88,0.88);
  leg_mm->SetFillColor(kWhite);
  leg_mm->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      leg_mm->AddEntry(tge_posmmratio,"#pi^{+}, w1/w2, -- field","p");
      leg_mm->AddEntry(tge_negmmratio,"#pi^{-}, w1/w2, -- field","p");
    }
  if(pid==2||pid==3)
    {
      leg_mm->AddEntry(tge_posmmratio,"K^{+}, w1/w2, -- field","p");
      leg_mm->AddEntry(tge_negmmratio,"K^{-}, w1/w2, -- field","p");
    }
  if(pid==4||pid==5)
    {
      leg_mm->AddEntry(tge_posmmratio,"p, w1/w2, -- field","p");
      leg_mm->AddEntry(tge_negmmratio,"#bar{p}, w1/w2, -- field","p");
    }
  leg_mm->Draw();

  char gifname_mm[100]; 
  sprintf(gifname_mm,"RatioFigures/sector_mm_%d_dis_cent%s.gif",pid,centstring);
  char epsname_mm[100];
  sprintf(epsname_mm,"RatioFigures/sector_mm_%d_dis_cent%s.eps",pid,centstring);

  c1->Print(gifname_mm);
  c1->Print(epsname_mm);



}

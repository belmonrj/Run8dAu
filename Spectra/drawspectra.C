void drawspectra()
{

  cout<<"hello!  now drawing spectra!"<<endl;

  //doit();

  //exit(0);

  // for(int icent=0; icent<5; icent++)
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


  for(int icent=0; icent<5; icent++)
    {
      doit(0,0,icent);
      doit(0,1,icent);
      doit(0,2,icent);
      doit(0,3,icent);
      doit(0,4,icent);
      doit(0,5,icent);
    }
  
  cout<<"done!  have a nice day!"<<endl;

}

void doit(int sector=0, int pid=0, int centid=0)
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
  sprintf(finname,"ppg044/pi0_%s.dat",centstring);
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

  int number = 1;
  char finposname[30];
  char finnegname[30];
  if(pid==0||pid==1)
    {
      number = 18;
      sprintf(finposname,"ppg030/pospion_%s.dat",centstring);
      sprintf(finnegname,"ppg030/negpion_%s.dat",centstring);
    }
  else if(pid==2||pid==3)
    {
      number = 13;
      sprintf(finposname,"ppg030/poskaon_%s.dat",centstring);
      sprintf(finnegname,"ppg030/negkaon_%s.dat",centstring);
    }
  else if(pid==4||pid==5)
    {
      number = 17;
      sprintf(finposname,"ppg030/posproton_%s.dat",centstring);
      sprintf(finnegname,"ppg030/negproton_%s.dat",centstring);
    }
  else
    {
      cerr<<"unknown pid number, now dying a quick but horribly painful death"<<endl;
      exit(1);
    }

  ifstream finpos30(finposname);
  ifstream finneg30(finnegname);

  for(int i=0; i<number; i++)
    {
      ept[i]=0;
      finpos30>>pTpos_ppg030[i]>>yieldpos_ppg030[i]>>eyieldpos_ppg030[i];
      finneg30>>pTneg_ppg030[i]>>yieldneg_ppg030[i]>>eyieldneg_ppg030[i];
    }

  finpos30.close();
  finneg30.close();

  TGraphErrors *ppgpos30 = new TGraphErrors(number,pTpos_ppg030,yieldpos_ppg030,ept,eyieldpos_ppg030);
  ppgpos30->SetMarkerColor(kRed);
  ppgpos30->SetMarkerStyle(20);

  TGraphErrors *ppgneg30 = new TGraphErrors(number,pTneg_ppg030,yieldneg_ppg030,ept,eyieldneg_ppg030);
  ppgneg30->SetMarkerColor(kRed);
  ppgneg30->SetMarkerStyle(20);

  // ---



  // --- input data

  char fnameinposcb[100];
  char fnameinnegcb[100];
  sprintf(fnameinposcb,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  ifstream finposcb;
  ifstream finnegcb;
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pT_poscb[100], yield_poscb[100], eyield_poscb[100];
  float pT_negcb[100], yield_negcb[100], eyield_negcb[100];

  for(int i=0; i<100; i++)
    {
      // poscb
      finposcb>>pT_poscb[i]>>yield_poscb[i]>>eyield_poscb[i];
      // negcb
      finnegcb>>pT_negcb[i]>>yield_negcb[i]>>eyield_negcb[i];
    }
  finposcb.close();
  finnegcb.close();



  // --- now input the rebinned data

  sprintf(fnameinposcb,"Data/FinalFeed/R2_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/FinalFeed/R2_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pTR2_poscb[50], yieldR2_poscb[50], eyieldR2_poscb[50];
  float pTR2_negcb[50], yieldR2_negcb[50], eyieldR2_negcb[50];

  for(int i=0; i<50; i++)
    {
      // poscb
      finposcb>>pTR2_poscb[i]>>yieldR2_poscb[i]>>eyieldR2_poscb[i];
      // negcb
      finnegcb>>pTR2_negcb[i]>>yieldR2_negcb[i]>>eyieldR2_negcb[i];
      // if(i<1||((pid==4||pid==5)&&i>7))
      // 	{
      // 	  yieldR2_poscb[i] = -9;
      // 	  yieldR2_negcb[i] = -9;
      // 	}
    }
  finposcb.close();
  finnegcb.close();

  // --- now input the rebinned data

  sprintf(fnameinposcb,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pTR5_poscb[20], yieldR5_poscb[20], eyieldR5_poscb[20];
  float pTR5_negcb[20], yieldR5_negcb[20], eyieldR5_negcb[20];

  for(int i=0; i<20; i++)
    {
      // poscb
      finposcb>>pTR5_poscb[i]>>yieldR5_poscb[i]>>eyieldR5_poscb[i];
      // negcb
      finnegcb>>pTR5_negcb[i]>>yieldR5_negcb[i]>>eyieldR5_negcb[i];
      // if(i<1||((pid==4||pid==5)&&i>7))
      // 	{
      // 	  yieldR5_poscb[i] = -9;
      // 	  yieldR5_negcb[i] = -9;
      // 	}
    }
  finposcb.close();
  finnegcb.close();



  // --- now make tgrapherrorses

  float pT[36], epT[36], yield[36], eyield[36];

  // ----------------------- //
  // --- now do combined --- //
  // ----------------------- //


  char foutnamepos[100];
  sprintf(foutnamepos,"Text/ptpid_%s_poscb_%d_dis_cent%s.txt",sectorstring,pid,centstring);
  ofstream foutpos(foutnamepos);
  sprintf(foutnamepos,"Text/ptpid_%s_poscb_%d_dis_cent%s.text",sectorstring,pid,centstring);
  ofstream ftexpos(foutnamepos);

  //for(int i=0; i<36; i++)
  for(int i=0; i<31; i++)
    {
      // pT[i] = -9;
      // epT[i] = 0;
      // yield[i] = -9;
      // eyield[i] = 0;
      // if(i<30)
      // 	{
      // 	  pT[i] = pT_poscb[i];
      // 	  epT[i] = 0;
      // 	  yield[i] = yield_poscb[i];
      // 	  eyield[i] = eyield_poscb[i];
      // 	}
      // int k=i-24;
      // if(i>29)
      // 	{
      // 	  pT[i] = pTR_poscb[k];
      // 	  epT[i] = 0;
      // 	  yield[i] = yieldR_poscb[k];
      // 	  eyield[i] = eyieldR_poscb[k];
      // 	}

      // -----------------------
      // 100:0-2,200:2-3,500:3-6
      // -----------------------
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<20)
      	{
      	  pT[i] = pT_poscb[i];
      	  epT[i] = 0;
      	  yield[i] = yield_poscb[i];
      	  eyield[i] = eyield_poscb[i];
      	}
      int k;
      k=i-10;
      if(i>19&&i<25)
      	{
      	  pT[i] = pTR2_poscb[k];
      	  epT[i] = 0;
      	  yield[i] = yieldR2_poscb[k];
      	  eyield[i] = eyieldR2_poscb[k];
      	}
      k=i-19;
      if(i>24)
      	{
      	  pT[i] = pTR5_poscb[k];
      	  epT[i] = 0;
      	  yield[i] = yieldR5_poscb[k];
      	  eyield[i] = eyieldR5_poscb[k];
      	}

      // ---

      if((pid==2||pid==3)&&pT[i]>3.5) yield[i] = -9;
      if(yield[i]>9) yield[i] = -9;

      foutpos<<pT[i]<<"\t"<<yield[i]<<"\t"<<eyield[i]<<endl; // NEW
      if(pT[i]>0.5&&pT[i]<5) ftexpos<<pT[i]<<" "<<yield[i]<<" "<<eyield[i]<<endl; // NEW
    }
  foutpos.close();
  ftexpos.close();

  // YOU REALLY WANT TO KNOW ABOUT THIS
  //for(int i=0; i<5; i++)
  for(int i=0; i<36; i++)
    {
      if(i<5||i>33) yield[i]= -9;
    }

  TGraphErrors *tge_poscb = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_poscb->SetMarkerColor(kBlack);
  tge_poscb->SetMarkerStyle(20);

  c1->Clear();

  TMultiGraph *tmg_poscb = new TMultiGraph();
  tmg_poscb->Add(ppgpos30);
  if(pid==0||pid==1) tmg_poscb->Add(pion44);
  tmg_poscb->Add(tge_poscb);
  tmg_poscb->Draw("ap");
  tmg_poscb->SetMaximum(1e1);
  tmg_poscb->SetMinimum(1e-7);
  tmg_poscb->GetXaxis()->SetLimits(0.0,6.0);
  //tmg_poscb->GetXaxis()->SetLimits(0.0,5.0); // CHANGE
  tmg_poscb->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_poscb->GetXaxis()->CenterTitle();
  //tmg_poscb->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_poscb->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_poscb->GetYaxis()->CenterTitle();

  //TPaveText *tptP_poscb = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br");
  //TPaveText *tptP_poscb = new TPaveText(0.35, 5e-7, 1.1, 5e-6, "br");
  TPaveText *tptP_poscb = new TPaveText(0.35, 5e-7, 2.0, 5e-6, "br");
  tptP_poscb->SetFillColor(10);
  tptP_poscb->SetBorderSize(0);
  TText *textP_poscb = tptP_poscb->AddText(bigcentstring);
  tptP_poscb->Draw();

  TPaveText *tptP_poscb2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  //TPaveText *tptP_poscb2 = new TPaveText(0.5, 1.2e1, 4.5, 6e1, "br");
  tptP_poscb2->SetFillColor(10);
  tptP_poscb2->SetBorderSize(0);
  TText *textP_poscb2 = tptP_poscb2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_poscb2->Draw();

  //TLegend *leg _poscb = new TLegend(0.68,0.68,0.88,0.88);
  TLegend *leg _poscb = new TLegend(0.58,0.58,0.88,0.88);
  leg_poscb->SetFillColor(kWhite);
  leg_poscb->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      //leg_poscb->AddEntry(tge_poscb,"#pi^{+}, both fields","p");
      leg_poscb->AddEntry(tge_poscb,"#pi^{+}, Run8","p");
      leg_poscb->AddEntry(ppgpos30,"#pi^{+}, ppg030","p");
      leg_poscb->AddEntry(pion44,"#pi^{0}, ppg044","p");
    }
  if(pid==2||pid==3)
    {
      //leg_poscb->AddEntry(tge_poscb,"K^{+}, both fields","p");
      leg_poscb->AddEntry(tge_poscb,"K^{+}, Run8","p");
      leg_poscb->AddEntry(ppgpos30,"K^{+}, ppg030","p");
    }
  if(pid==4||pid==5)
    {
      //leg_poscb->AddEntry(tge_poscb,"p, both fields","p");
      leg_poscb->AddEntry(tge_poscb,"p, Run8","p");
      leg_poscb->AddEntry(ppgpos30,"p, ppg030","p");
    }
  leg_poscb->Draw();

  char gifname_poscb[100];
  sprintf(gifname_poscb,"SpectraFigures/ptpid_%s_poscb_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_poscb[100];
  sprintf(epsname_poscb,"SpectraFigures/ptpid_%s_poscb_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_poscb);
  c1->Print(epsname_poscb);


  c1->Clear();



  char foutnameneg[100];
  sprintf(foutnameneg,"Text/ptpid_%s_negcb_%d_dis_cent%s.txt",sectorstring,pid,centstring);
  ofstream foutneg(foutnameneg);
  sprintf(foutnameneg,"Text/ptpid_%s_negcb_%d_dis_cent%s.text",sectorstring,pid,centstring);
  ofstream ftexneg(foutnameneg);

  //for(int i=0; i<36; i++)
  for(int i=0; i<31; i++)
    {
      // pT[i] = -9;
      // epT[i] = 0;
      // yield[i] = -9;
      // eyield[i] = 0;
      // if(i<30)
      // 	{
      // 	  pT[i] = pT_negcb[i];
      // 	  epT[i] = 0;
      // 	  yield[i] = yield_negcb[i];
      // 	  eyield[i] = eyield_negcb[i];
      // 	}
      // int k=i-24;
      // if(i>29)
      // 	{
      // 	  pT[i] = pTR_negcb[k];
      // 	  epT[i] = 0;
      // 	  yield[i] = yieldR_negcb[k];
      // 	  eyield[i] = eyieldR_negcb[k];
      // 	}

      // -----------------------
      // 100:0-2,200:2-3,500:3-6
      // -----------------------
      pT[i] = -9;
      epT[i] = 0;
      yield[i] = -9;
      eyield[i] = 0;
      if(i<20)
      	{
      	  pT[i] = pT_negcb[i];
      	  epT[i] = 0;
      	  yield[i] = yield_negcb[i];
      	  eyield[i] = eyield_negcb[i];
      	}
      int k;
      k=i-10;
      if(i>19&&i<25)
      	{
      	  pT[i] = pTR2_negcb[k];
      	  epT[i] = 0;
      	  yield[i] = yieldR2_negcb[k];
      	  eyield[i] = eyieldR2_negcb[k];
      	}
      k=i-19;
      if(i>24)
      	{
      	  pT[i] = pTR5_negcb[k];
      	  epT[i] = 0;
      	  yield[i] = yieldR5_negcb[k];
      	  eyield[i] = eyieldR5_negcb[k];
      	}
      // ----



      if((pid==2||pid==3)&&pT[i]>3.5) yield[i] = -9;
      if(yield[i]>9) yield[i] = -9;
      foutneg<<pT[i]<<"\t"<<yield[i]<<"\t"<<eyield[i]<<endl; // NEW
      if(pT[i]>0.5&&pT[i]<5) ftexneg<<pT[i]<<" "<<yield[i]<<" "<<eyield[i]<<endl; // NEW
    }
  foutneg.close(); // NEW
  ftexneg.close(); // NEW

  // YOU REALLY WANT TO KNOW ABOUT THIS
  //for(int i=0; i<5; i++)
  for(int i=0; i<36; i++)
    {
      if(i<5||i>33) yield[i]= -9;
    }

  TGraphErrors *tge_negcb = new TGraphErrors(36,pT,yield,epT,eyield);
  tge_negcb->SetMarkerColor(kBlack);
  tge_negcb->SetMarkerStyle(20);

  TMultiGraph *tmg_negcb = new TMultiGraph();
  tmg_negcb->Add(ppgneg30);
  if(pid==0||pid==1) tmg_negcb->Add(pion44);
  tmg_negcb->Add(tge_negcb);
  tmg_negcb->Draw("ap");
  tmg_negcb->SetMaximum(1e1);
  tmg_negcb->SetMinimum(1e-7);
  tmg_negcb->GetXaxis()->SetLimits(0.0,6.0);
  //tmg_negcb->GetXaxis()->SetLimits(0.0,5.0);
  tmg_negcb->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_negcb->GetXaxis()->CenterTitle();
  //tmg_negcb->GetYaxis()->SetTitle("Corrected Invariant Yield");
  tmg_negcb->GetYaxis()->SetTitle("1/2#pip_{T} d^{2}N/dp_{T}dy (c^{2}/GeV^{2})");
  tmg_negcb->GetYaxis()->CenterTitle();

  //TPaveText *tptP_negcb = new TPaveText(0.5, 5e-7, 1.5, 5e-6, "br"); 
  //TPaveText *tptP_negcb = new TPaveText(0.35, 5e-7, 1.1, 5e-6, "br");
  TPaveText *tptP_negcb = new TPaveText(0.35, 5e-7, 2.0, 5e-6, "br");
  tptP_negcb->SetFillColor(10);
  tptP_negcb->SetBorderSize(0);
  TText *textP_negcb = tptP_negcb->AddText(bigcentstring);
  tptP_negcb->Draw();

  TPaveText *tptP_negcb2 = new TPaveText(0.5, 1.2e1, 5.5, 6e1, "br");
  //TPaveText *tptP_negcb2 = new TPaveText(0.5, 1.2e1, 4.5, 6e1, "br");
  tptP_negcb2->SetFillColor(10);
  tptP_negcb2->SetBorderSize(0);
  TText *textP_negcb2 = tptP_negcb2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP_negcb2->Draw();

  //TLegend *leg _negcb = new TLegend(0.68,0.68,0.88,0.88);
  TLegend *leg _negcb = new TLegend(0.58,0.58,0.88,0.88);
  leg_negcb->SetFillColor(kWhite);
  leg_negcb->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      //leg_negcb->AddEntry(tge_negcb,"#pi^{-}, both fields","p");
      leg_negcb->AddEntry(tge_negcb,"#pi^{-}, Run8","p");
      leg_negcb->AddEntry(ppgneg30,"#pi^{-}, ppg030","p");
      leg_negcb->AddEntry(pion44,"#pi^{0}, ppg044","p");
    }
  if(pid==2||pid==3)
    {
      //leg_negcb->AddEntry(tge_negcb,"K^{-}, both fields","p");
      leg_negcb->AddEntry(tge_negcb,"K^{-}, Run8","p");
      leg_negcb->AddEntry(ppgneg30,"K^{-}, ppg030","p");
    }
  if(pid==4||pid==5)
    {
      //leg_negcb->AddEntry(tge_negcb,"#bar{p}, both fields","p");
      leg_negcb->AddEntry(tge_negcb,"#bar{p}, Run8","p");
      leg_negcb->AddEntry(ppgneg30,"#bar{p}, ppg030","p");
    }
  leg_negcb->Draw();

  char gifname_negcb[100];
  sprintf(gifname_negcb,"SpectraFigures/ptpid_%s_negcb_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_negcb[100];
  sprintf(epsname_negcb,"SpectraFigures/ptpid_%s_negcb_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname_negcb);
  c1->Print(epsname_negcb);




}

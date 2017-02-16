void physkpippi()
{


  for(int icent=0; icent<5; icent++)
    {
      doitP(icent);
      doitK(icent);
    }


}



void doitP(int centid=0)
{


  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);


  //int pid=0;
  //if(ipid==0) pid=0;
  //if(ipid==1) pid=4;
  //if(ipid==2) pid=6;

  int pid=5;

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"

  char centstring[10];
  sprintf(centstring,"0088"); // "default"
  if(centid==0) sprintf(centstring,"0088");
  if(centid==1) sprintf(centstring,"0020");
  if(centid==2) sprintf(centstring,"2040");
  if(centid==3) sprintf(centstring,"4060");
  if(centid==4) sprintf(centstring,"6088");

  char bigcentstring[10];
  sprintf(bigcentstring,"MinBias"); // "default"
  if(centid==0) sprintf(bigcentstring,"MinBias");
  if(centid==1) sprintf(bigcentstring,"0-20%%");
  if(centid==2) sprintf(bigcentstring,"20-40%%");
  if(centid==3) sprintf(bigcentstring,"40-60%%");
  if(centid==4) sprintf(bigcentstring,"60-88%%");


  // ----------------- //
  // --- Run8 part --- //
  // ----------------- //

  float pTpos[36], epTpos[36], ratiopos[36], eratiopos[36];
  float pTneg[36], epTneg[36], rationeg[36], erationeg[36];
  float esysratiopos[36];//NEW!  and temp, to be revised
  float esysrationeg[36];//NEW!  and temp, to be revised

  float pT[36];
  float epT[36]={0};

  char fnamein[100];
  sprintf(fnamein,"PhysRatios/opi_%s_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  ifstream finn;
  finn.open(fnamein);
  for(int i=0; i<36; i++)
    {
      finn>>pT[i]>>ratiopos[i]>>eratiopos[i]>>rationeg[i]>>erationeg[i];
      esysratiopos[i] = 0.1*ratiopos[i];//NEW!  and temp, to be revised
      esysrationeg[i] = 0.1*rationeg[i];//NEW!  and temp, to be revised
    }
  finn.close();

  for(int i=0; i<6; i++)
    {
      if(pid==6) {ratiopos[i]=-9; rationeg[i]=-9; eratiopos[i]=0; erationeg[i]=0; esysratiopos[i]=0; esysrationeg[i]=0;}
    }

  TGraphErrors *tpos = new TGraphErrors(36,pT,ratiopos,epT,eratiopos);
  tpos->SetMarkerStyle(22);
  tpos->SetMarkerColor(kRed);
  TGraphErrors *tposSYS = new TGraphErrors(36,pT,ratiopos,epT,esysratiopos);
  tposSYS->SetMarkerStyle(1);
  tposSYS->SetMarkerColor(kRed);
  tposSYS->SetLineColor(kRed-10);
  tposSYS->SetLineWidth(15);

  TGraphErrors *tneg = new TGraphErrors(36,pT,rationeg,epT,erationeg);
  tneg->SetMarkerStyle(21);
  tneg->SetMarkerColor(kBlue);
  TGraphErrors *tnegSYS = new TGraphErrors(36,pT,rationeg,epT,esysrationeg);
  tnegSYS->SetMarkerStyle(1);
  tnegSYS->SetMarkerColor(kBlue);
  tnegSYS->SetLineColor(kBlue-10);
  tnegSYS->SetLineWidth(15);

  // ------------------------ //
  // --- end of Run8 part --- //
  // ------------------------ //



  // ----------------- //
  // --- Run3 part --- //
  // ----------------- //

  float ptpion[34];
  float ptproton[34];
  float eptpion[34]={0};
  float eptproton[34]={0};
  float ptratio[34];
  float eptratio[34]={0};
  float yieldpionpos[34],yieldpionneg[34];
  float eyieldpionpos[34],eyieldpionneg[34];
  float yieldprotonpos[34],yieldprotonneg[34];
  float eyieldprotonpos[34],eyieldprotonneg[34];
  float newratiopos[34],newrationeg[34];
  float enewratiopos[34],enewrationeg[34];

  float A, dA, B, dB;

  ifstream fin1;
  ifstream fin2;

  char fin1name[100];
  char fin2name[100];

  sprintf(fin1name,"ppg030/pospion_%s.dat",centstring);
  sprintf(fin2name,"ppg030/negpion_%s.dat",centstring);

  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<18; i++)
    {
      fin1>>ptpion[i]>>yieldpionpos[i]>>eyieldpionpos[i];
      fin2>>ptpion[i]>>yieldpionneg[i]>>eyieldpionneg[i];
    }
  fin1.close();  
  fin2.close();

  sprintf(fin1name,"ppg030/posproton_%s.dat",centstring);
  sprintf(fin2name,"ppg030/negproton_%s.dat",centstring);

  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<17; i++)
    {
      fin1>>ptproton[i]>>yieldprotonpos[i]>>eyieldprotonpos[i];
      fin2>>ptproton[i]>>yieldprotonneg[i]>>eyieldprotonneg[i];
    }
  fin1.close();  
  fin2.close();

  for(int i=0; i<13; i++)
    {
      //positive ratio
      A = yieldprotonpos[i];
      dA = eyieldprotonpos[i];
      B = yieldpionpos[i+3];
      dB = eyieldpionpos[i+3];
      //cout<<"A = "<<A<<" dA = "<<dA<<" B = "<<B<<" dB = "<<dB<<endl;
      //cout<<"ptproton is "<<ptproton[i]<<endl;
      //cout<<"ptpion is "<<ptpion[i+3]<<endl;
      newratiopos[i] = A/B;
      enewratiopos[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
      //negative ratio
      A = yieldprotonneg[i];
      dA = eyieldprotonneg[i];
      B = yieldpionneg[i+3];
      dB = eyieldpionneg[i+3];
      newrationeg[i] = A/B;
      enewrationeg[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
    }

  TGraphErrors *tposppg = new TGraphErrors(13,ptproton,newratiopos,eptproton,enewratiopos);
  tposppg->SetMarkerStyle(26);
  //tposppg->SetMarkerColor(2);
  tposppg->SetMarkerColor(1);

  TGraphErrors *tnegppg = new TGraphErrors(13,ptproton,newrationeg,eptproton,enewrationeg);
  tnegppg->SetMarkerStyle(25);
  //tnegppg->SetMarkerColor(4);
  tnegppg->SetMarkerColor(1);

  // ------------------------ //
  // --- end of Run3 part --- //
  // ------------------------ //

  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tposSYS);
  tmg->Add(tnegSYS);
  tmg->Add(tpos);
  tmg->Add(tneg);
  tmg->Add(tposppg);
  tmg->Add(tnegppg);
  tmg->Draw("apz");
  tmg->SetMinimum(0.0);
  tmg->SetMaximum(0.6);
  //tmg->GetXaxis()->SetLimits(0.0,6.0);
  tmg->GetXaxis()->SetLimits(0.0,5.0);
  tmg->GetYaxis()->SetTitle("Ratio");
  tmg->GetYaxis()->CenterTitle();
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetXaxis()->CenterTitle();

  //TPaveText *tptP = new TPaveText(1.5,1.01,4.5,1.75,"br");
  TPaveText *tptP = new TPaveText(0.5,0.61,4.5,0.66,"br");
  tptP->SetFillColor(10);
  tptP->SetBorderSize(0);
  TText *textP = tptP->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP->Draw();

  //TPaveText *tptP2 = new TPaveText(0.1,0.9,2.1,1.1,"br");
  TPaveText *tptP2 = new TPaveText(2.0,0.05,3.0,0.15,"br");
  tptP2->SetFillColor(10);
  tptP2->SetBorderSize(0);
  TText *textP2 = tptP2->AddText(bigcentstring);
  tptP2->Draw();


  //TLegend *leg = new TLegend(0.50,0.69,0.89,0.89); // original
  TLegend *leg = new TLegend(0.55,0.69,0.87,0.89); // modified
  leg->SetFillColor(10);
  leg->SetBorderSize(0);
  //leg->SetHeader("            Centrality 0-10%");
  //leg->AddEntry(tposppg,"p/#pi^{+} PRC.69.034909","p"); // original
  //leg->AddEntry(tnegppg,"#bar{p}/#pi^{-} PRC.69.034909","p"); // original
  leg->AddEntry(tposppg,"p/#pi^{+} Run3","p"); // modified
  leg->AddEntry(tnegppg,"#bar{p}/#pi^{-} Run3","p"); // modified
  leg->Draw();

  TLegend *leg2 = new TLegend(0.12,0.69,0.44,0.89);
  leg2->SetFillColor(10);
  leg2->SetBorderSize(0);
  leg2->AddEntry(tpos,"p/#pi^{+} Run8","p");
  leg2->AddEntry(tneg,"#bar{p}/#pi^{-} Run8","p");
  leg2->Draw();

  char figname[100];
  // sprintf(figname,"PhysRatios/opi_%s_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  // c1->Print(figname);
  // sprintf(figname,"PhysRatios/opi_%s_%d_dis_cent%s.eps",sectorstring,pid,centstring);
  // c1->Print(figname);
  sprintf(figname,"PhysRatios/Special/ppi_%s_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  c1->Print(figname);
  sprintf(figname,"PhysRatios/Special/ppi_%s_%d_dis_cent%s.eps",sectorstring,pid,centstring);
  c1->Print(figname);




}







void doitK(int centid=0)
{


  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);


  //int pid=0;
  //if(ipid==0) pid=0;
  //if(ipid==1) pid=4;
  //if(ipid==2) pid=6;

  int pid=3;

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"

  char centstring[10];
  sprintf(centstring,"0088"); // "default"
  if(centid==0) sprintf(centstring,"0088");
  if(centid==1) sprintf(centstring,"0020");
  if(centid==2) sprintf(centstring,"2040");
  if(centid==3) sprintf(centstring,"4060");
  if(centid==4) sprintf(centstring,"6088");

  char bigcentstring[10];
  sprintf(bigcentstring,"MinBias"); // "default"
  if(centid==0) sprintf(bigcentstring,"MinBias");
  if(centid==1) sprintf(bigcentstring,"0-20%%");
  if(centid==2) sprintf(bigcentstring,"20-40%%");
  if(centid==3) sprintf(bigcentstring,"40-60%%");
  if(centid==4) sprintf(bigcentstring,"60-88%%");


  // ----------------- //
  // --- Run8 part --- //
  // ----------------- //

  float pTpos[36], epTpos[36], ratiopos[36], eratiopos[36];
  float pTneg[36], epTneg[36], rationeg[36], erationeg[36];
  float esysratiopos[36];//NEW!  and temp, to be revised
  float esysrationeg[36];//NEW!  and temp, to be revised

  float pT[36];
  float epT[36]={0};

  char fnamein[100];
  sprintf(fnamein,"PhysRatios/opi_%s_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  ifstream finn;
  finn.open(fnamein);
  for(int i=0; i<36; i++)
    {
      finn>>pT[i]>>ratiopos[i]>>eratiopos[i]>>rationeg[i]>>erationeg[i];
      esysratiopos[i] = 0.05*ratiopos[i];//NEW!  and temp, to be revised
      esysrationeg[i] = 0.05*rationeg[i];//NEW!  and temp, to be revised
    }
  finn.close();

  for(int i=0; i<6; i++)
    {
      if(pid==6) {ratiopos[i]=-9; rationeg[i]=-9; eratiopos[i]=0; erationeg[i]=0; esysratiopos[i]=0; esysrationeg[i]=0;}
    }

  TGraphErrors *tpos = new TGraphErrors(36,pT,ratiopos,epT,eratiopos);
  tpos->SetMarkerStyle(22);
  tpos->SetMarkerColor(kRed);
  TGraphErrors *tposSYS = new TGraphErrors(36,pT,ratiopos,epT,esysratiopos);
  tposSYS->SetMarkerStyle(1);
  tposSYS->SetMarkerColor(kRed);
  tposSYS->SetLineColor(kRed-10);
  tposSYS->SetLineWidth(15);

  TGraphErrors *tneg = new TGraphErrors(36,pT,rationeg,epT,erationeg);
  tneg->SetMarkerStyle(21);
  tneg->SetMarkerColor(kBlue);
  TGraphErrors *tnegSYS = new TGraphErrors(36,pT,rationeg,epT,esysrationeg);
  tnegSYS->SetMarkerStyle(1);
  tnegSYS->SetMarkerColor(kBlue);
  tnegSYS->SetLineColor(kBlue-10);
  tnegSYS->SetLineWidth(15);

  // ------------------------ //
  // --- end of Run8 part --- //
  // ------------------------ //



  // ----------------- //
  // --- Run3 part --- //
  // ----------------- //

  float ptpion[34];
  float ptkaon[34];
  float eptpion[34]={0};
  float eptkaon[34]={0};
  float ptratio[34];
  float eptratio[34]={0};
  float yieldpionpos[34],yieldpionneg[34];
  float eyieldpionpos[34],eyieldpionneg[34];
  float yieldkaonpos[34],yieldkaonneg[34];
  float eyieldkaonpos[34],eyieldkaonneg[34];
  float newratiopos[34],newrationeg[34];
  float enewratiopos[34],enewrationeg[34];

  float A, dA, B, dB;

  ifstream fin1;
  ifstream fin2;

  char fin1name[100];
  char fin2name[100];

  sprintf(fin1name,"ppg030/pospion_%s.dat",centstring);
  sprintf(fin2name,"ppg030/negpion_%s.dat",centstring);

  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<18; i++)
    {
      fin1>>ptpion[i]>>yieldpionpos[i]>>eyieldpionpos[i];
      fin2>>ptpion[i]>>yieldpionneg[i]>>eyieldpionneg[i];
    }
  fin1.close();  
  fin2.close();

  sprintf(fin1name,"ppg030/poskaon_%s.dat",centstring);
  sprintf(fin2name,"ppg030/negkaon_%s.dat",centstring);

  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<13; i++)
    {
      fin1>>ptkaon[i]>>yieldkaonpos[i]>>eyieldkaonpos[i];
      fin2>>ptkaon[i]>>yieldkaonneg[i]>>eyieldkaonneg[i];
    }
  fin1.close();  
  fin2.close();

  for(int i=0; i<12; i++)
    {
      // if(i<2) continue;
      // if(i>5) break;
      //positive ratio
      A = yieldkaonpos[i];
      dA = eyieldkaonpos[i];
      B = yieldpionpos[i+1];
      dB = eyieldpionpos[i+1];
      if(A>0&&B>0)
	{
	  newratiopos[i] = A/B;
	  enewratiopos[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
	}
      else
	{
	  newratiopos[i] = -9;
	  enewratiopos[i] = 0;
	}
      //negative ratio
      A = yieldkaonneg[i];
      dA = eyieldkaonneg[i];
      B = yieldpionneg[i+1];
      dB = eyieldpionneg[i+1];
      //cout<<"A = "<<A<<" dA = "<<dA<<" B = "<<B<<" dB = "<<dB<<endl;
      //cout<<"ptkaon is "<<ptkaon[i]<<endl;
      //cout<<"ptpion is "<<ptpion[i+1]<<endl;
      if(A>0&&B>0)
	{
	  newrationeg[i] = A/B;
	  enewrationeg[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
	}
      else
	{
	  newrationeg[i] = -9;
	  enewrationeg[i] = 0;
	}
    }

  TGraphErrors *tposppg = new TGraphErrors(12,ptkaon,newratiopos,eptkaon,enewratiopos);
  tposppg->SetMarkerStyle(26);
  //tposppg->SetMarkerColor(2);
  tposppg->SetMarkerColor(1);

  TGraphErrors *tnegppg = new TGraphErrors(12,ptkaon,newrationeg,eptkaon,enewrationeg);
  tnegppg->SetMarkerStyle(25);
  //tnegppg->SetMarkerColor(4);
  tnegppg->SetMarkerColor(1);

  // ------------------------ //
  // --- end of Run3 part --- //
  // ------------------------ //

  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tposSYS);
  tmg->Add(tnegSYS);
  tmg->Add(tpos);
  tmg->Add(tneg);
  tmg->Add(tposppg);
  tmg->Add(tnegppg);
  tmg->Draw("apz");
  tmg->SetMinimum(0.0);
  tmg->SetMaximum(1.0);
  //tmg->GetXaxis()->SetLimits(0.0,4.0);
  tmg->GetXaxis()->SetLimits(0.0,3.5);
  tmg->GetYaxis()->SetTitle("Ratio");
  tmg->GetYaxis()->CenterTitle();
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetXaxis()->CenterTitle();

  // TLegend *leg = new TLegend(0.50,0.69,0.89,0.89);
  // leg->SetFillColor(10);
  // leg->SetBorderSize(0);
  // //leg->SetHeader("            Centrality 0-10%");
  // leg->AddEntry(tposppg,"K^{+}/#pi^{+} PRC.69.034909","p");
  // leg->AddEntry(tnegppg,"K^{-}/#pi^{-} PRC.69.034909","p");
  // leg->Draw();

  //TPaveText *tptP = new TPaveText(1.5,1.01,4.5,1.75,"br");
  TPaveText *tptP = new TPaveText(0.5,1.01,3.0,1.1,"br");
  tptP->SetFillColor(10);
  tptP->SetBorderSize(0);
  TText *textP = tptP->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP->Draw();

  //TPaveText *tptP2 = new TPaveText(0.1,0.9,2.1,1.1,"br");
  TPaveText *tptP2 = new TPaveText(2.0,0.1,3.0,0.22,"br");
  tptP2->SetFillColor(10);
  tptP2->SetBorderSize(0);
  TText *textP2 = tptP2->AddText(bigcentstring);
  tptP2->Draw();


  TLegend *leg = new TLegend(0.55,0.69,0.87,0.89); // modified
  leg->SetFillColor(10);
  leg->SetBorderSize(0);
  leg->AddEntry(tposppg,"K^{+}/#pi^{+} Run3","p"); // modified
  leg->AddEntry(tnegppg,"K^{-}/#pi^{-} Run3","p"); // modified
  leg->Draw();

  TLegend *leg2 = new TLegend(0.12,0.69,0.44,0.89);
  leg2->SetFillColor(10);
  leg2->SetBorderSize(0);
  leg2->AddEntry(tpos,"K^{+}/#pi^{+} Run8","p");
  leg2->AddEntry(tneg,"K^{-}/#pi^{-} Run8","p");
  leg2->Draw();

  char figname[100];
  sprintf(figname,"PhysRatios/Special/kpi_%s_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  c1->Print(figname);
  sprintf(figname,"PhysRatios/Special/kpi_%s_%d_dis_cent%s.eps",sectorstring,pid,centstring);
  c1->Print(figname);




}

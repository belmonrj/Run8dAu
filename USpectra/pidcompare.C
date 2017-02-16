void pidcompare()
{

  cout<<"well hello there!"<<endl;
  cout<<"this hasn't been setup to work for Run8 yet, now dying"<<endl;
  cout<<"have a nice day!"<<endl;
  exit(0);

  //doit();
  //exit();

  for(int icent=0; icent<5; icent++)
    {
      for(int ipid=0; ipid<3; ipid++)
	{
	  doit(0,ipid,icent);
	}
    }
  
  cout<<"done!  have a nice day!"<<endl;

}



void doit(int sector=0, int partid=0, int centid=0)
{

  // --- beginning of code

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFillColor(kWhite);
  c1->SetFrameFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameBorderMode(0);
  c1->SetGrid();
  //c1->SetLogy();



  // --- strings for filenames

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  else {cerr<<"uh oh "<<endl; exit(0);}
  
  char centstring[10];
  sprintf(centstring,"0092"); // "default"
  if(centid==0) sprintf(centstring,"0010");
  if(centid==1) sprintf(centstring,"1020");
  if(centid==2) sprintf(centstring,"2040");
  if(centid==3) sprintf(centstring,"4060");
  if(centid==4) sprintf(centstring,"6092");

  char bigcentstring[50];
  sprintf(bigcentstring,"MinBias"); // "default"
  if(centid==0) sprintf(bigcentstring,"0-10%%");
  if(centid==1) sprintf(bigcentstring,"10-20%%");
  if(centid==2) sprintf(bigcentstring,"20-40%%");
  if(centid==3) sprintf(bigcentstring,"40-60%%");
  if(centid==4) sprintf(bigcentstring,"60-92%%");



  bool pion = false;
  bool kaon = false;
  bool proton = false;
  if(partid==0) pion = true;
  if(partid==1) kaon = true;
  if(partid==2) proton = true;



  int pid = 0; // careful, may need to change value or revise code
  int pid1 = 0;
  int pid2 = 0;
  int pid3 = 0;

  if(pion)
    {
      pid = 0;
      pid1 = 0;
      pid2 = 1;
      pid3 = 2;
    }

  if(kaon)
    {
      pid = 4;
      pid1 = 4;
      pid2 = 5;
      pid3 = 4;
    }

  if(proton)
    {
      pid = 6;
      pid1 = 6;
      pid2 = 7;
      pid3 = 8;
    }






  // --- ppg080 stuff

  float pT_ppg080[23], yield_ppg080[23], eyield_ppg080[23];
  float ept[23];
  char finname[30];
  sprintf(finname,"ppg080/pi0_cent%s.dat",centstring);
  for(int i=0; i<23; i++)
    {
      pT_ppg080[i]=i/2.0+0.25;
      ept[i]=0;
      yield_ppg080[i]=0;
      eyield_ppg080[i]=0;
    }
  ifstream fin080(finname);
  for(int i=0; i<21; i++)
    {
      fin080>>pT_ppg080[i+2]>>yield_ppg080[i+2]>>eyield_ppg080[i+2];
    }
  fin080.close();
  TGraphErrors *pion080 = new TGraphErrors(21,pT_ppg080,yield_ppg080,ept,eyield_ppg080);
  pion080->SetMarkerColor(kGreen+2);
  pion080->SetMarkerStyle(20);

  // --- ppg026 stuff

  float pTpos_ppg026[45], yieldpos_ppg026[45], eyieldpos_ppg026[45];
  float pTneg_ppg026[45], yieldneg_ppg026[45], eyieldneg_ppg026[45];
  float EPT[45];

  for(int i=0; i<7; i++)
    {
      pTpos_ppg026[i] = i/10.0+0.05;
      //epTpos_ppg026[i] = 0;
      yieldpos_ppg026[i] = 0;
      eyieldpos_ppg026[i] = 0;
      pTneg_ppg026[i] = i/10.0+0.05;
      //epTneg_ppg026[i] = 0;
      yieldneg_ppg026[i] = 0;
      eyieldneg_ppg026[i] = 0;
      EPT[i]=0;
    }

  int number = 1;
  int offset = 0;
  char finposname[30];
  char finnegname[30];
  //if(pid<=3)
  if(pion)
    {
      number = 28;
      offset = 2;
      sprintf(finposname,"ppg026/pospion_%s.dat",centstring);
      sprintf(finnegname,"ppg026/negpion_%s.dat",centstring);
    }
  //else if(pid==4||pid==5)
  else if(kaon)
    {
      number = 18;
      offset = 2;
      sprintf(finposname,"ppg026/poskaon_%s.dat",centstring);
      sprintf(finnegname,"ppg026/negkaon_%s.dat",centstring);
    }
  //else if(pid>=6)
  else if(proton)
    {
      number = 39;
      offset = 6;
      sprintf(finposname,"ppg026/posproton_%s.dat",centstring);
      sprintf(finnegname,"ppg026/negproton_%s.dat",centstring);
    }
  else
    {
      cerr<<"unknown pid number, now dying a quick but horribly painful death"<<endl;
      exit(1);
    }

  ifstream finpos026(finposname);
  ifstream finneg026(finnegname);
  for(int i=0; i<number; i++)
    {
      EPT[i+offset]=0;
      finpos026>>pTpos_ppg026[i+offset]>>yieldpos_ppg026[i+offset]>>eyieldpos_ppg026[i+offset];
      finneg026>>pTneg_ppg026[i+offset]>>yieldneg_ppg026[i+offset]>>eyieldneg_ppg026[i+offset];
    }
  finpos026.close();
  finneg026.close();

  TGraphErrors *ppgpos026 = new TGraphErrors(number,pTpos_ppg026,yieldpos_ppg026,EPT,eyieldpos_ppg026);
  ppgpos026->SetMarkerColor(kRed);
  ppgpos026->SetMarkerStyle(20);

  TGraphErrors *ppgneg026 = new TGraphErrors(number,pTneg_ppg026,yieldneg_ppg026,EPT,eyieldneg_ppg026);
  ppgneg026->SetMarkerColor(kRed);
  ppgneg026->SetMarkerStyle(20);







  char fnameinpos1[100];
  char fnameinneg1[100];
  sprintf(fnameinpos1,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid1,centstring);
  sprintf(fnameinneg1,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid1,centstring);

  char fnameinpos2[100];
  char fnameinneg2[100];
  sprintf(fnameinpos2,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid2,centstring);
  sprintf(fnameinneg2,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid2,centstring);

  char fnameinpos3[100];
  char fnameinneg3[100];
  sprintf(fnameinpos3,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid3,centstring);
  sprintf(fnameinneg3,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid3,centstring);




  ifstream finposcb1;
  ifstream finnegcb1;
  ifstream finposcb2;
  ifstream finnegcb2;
  ifstream finposcb3;
  ifstream finnegcb3;

  finposcb1.open(fnameinpos1);
  finnegcb1.open(fnameinneg1);
  finposcb2.open(fnameinpos2);
  finnegcb2.open(fnameinneg2);
  finposcb3.open(fnameinpos3);
  finnegcb3.open(fnameinneg3);

  float pT_poscb1[100], yield_poscb1[100], eyield_poscb1[100];
  float pT_negcb1[100], yield_negcb1[100], eyield_negcb1[100];
  float pT_poscb2[100], yield_poscb2[100], eyield_poscb2[100];
  float pT_negcb2[100], yield_negcb2[100], eyield_negcb2[100];
  float pT_poscb3[100], yield_poscb3[100], eyield_poscb3[100];
  float pT_negcb3[100], yield_negcb3[100], eyield_negcb3[100];

  for(int i=0; i<100; i++)
    {
      // poscb1
      finposcb1>>pT_poscb1[i]>>yield_poscb1[i]>>eyield_poscb1[i];
      //cout<<pT_poscb1[i]<<"\t"<<yield_poscb1[i]<<"\t"<<eyield_poscb1[i]<<endl;
      // negcb1
      finnegcb1>>pT_negcb1[i]>>yield_negcb1[i]>>eyield_negcb1[i];
      // poscb2
      finposcb2>>pT_poscb2[i]>>yield_poscb2[i]>>eyield_poscb2[i];
      // negcb2
      finnegcb2>>pT_negcb2[i]>>yield_negcb2[i]>>eyield_negcb2[i];
      // poscb3
      finposcb3>>pT_poscb3[i]>>yield_poscb3[i]>>eyield_poscb3[i];
      // negcb3
      finnegcb3>>pT_negcb3[i]>>yield_negcb3[i]>>eyield_negcb3[i];
    }

  finposcb1.close();
  finnegcb1.close();
  finposcb2.close();
  finnegcb2.close();
  finposcb3.close();
  finnegcb3.close();

  // ---

  char fRnameinpos1[100];
  char fRnameinneg1[100];
  sprintf(fRnameinpos1,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid1,centstring);
  sprintf(fRnameinneg1,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid1,centstring);

  char fRnameinpos2[100];
  char fRnameinneg2[100];
  sprintf(fRnameinpos2,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid2,centstring);
  sprintf(fRnameinneg2,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid2,centstring);

  char fRnameinpos3[100];
  char fRnameinneg3[100];
  sprintf(fRnameinpos3,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid3,centstring);
  sprintf(fRnameinneg3,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid3,centstring);

  ifstream finRposcb1;
  ifstream finRnegcb1;
  ifstream finRposcb2;
  ifstream finRnegcb2;
  ifstream finRposcb3;
  ifstream finRnegcb3;

  finRposcb1.open(fRnameinpos1);
  finRnegcb1.open(fRnameinneg1);
  finRposcb2.open(fRnameinpos2);
  finRnegcb2.open(fRnameinneg2);
  finRposcb3.open(fRnameinpos3);
  finRnegcb3.open(fRnameinneg3);

  float pTR_poscb1[100], yieldR_poscb1[100], eyieldR_poscb1[100];
  float pTR_negcb1[100], yieldR_negcb1[100], eyieldR_negcb1[100];
  float pTR_poscb2[100], yieldR_poscb2[100], eyieldR_poscb2[100];
  float pTR_negcb2[100], yieldR_negcb2[100], eyieldR_negcb2[100];
  float pTR_poscb3[100], yieldR_poscb3[100], eyieldR_poscb3[100];
  float pTR_negcb3[100], yieldR_negcb3[100], eyieldR_negcb3[100];

  for(int i=0; i<100; i++)
    {
      // poscb1
      finRposcb1>>pTR_poscb1[i]>>yieldR_poscb1[i]>>eyieldR_poscb1[i];
      //cout<<pTR_poscb1[i]<<"\t"<<yieldR_poscb1[i]<<"\t"<<eyieldR_poscb1[i]<<endl;
      // negcb1
      finRnegcb1>>pTR_negcb1[i]>>yieldR_negcb1[i]>>eyieldR_negcb1[i];
      // poscb2
      finRposcb2>>pTR_poscb2[i]>>yieldR_poscb2[i]>>eyieldR_poscb2[i];
      // negcb2
      finRnegcb2>>pTR_negcb2[i]>>yieldR_negcb2[i]>>eyieldR_negcb2[i];
      // poscb3
      finRposcb3>>pTR_poscb3[i]>>yieldR_poscb3[i]>>eyieldR_poscb3[i];
      // negcb3
      finRnegcb3>>pTR_negcb3[i]>>yieldR_negcb3[i]>>eyieldR_negcb3[i];
    }

  finRposcb1.close();
  finRnegcb1.close();
  finRposcb2.close();
  finRnegcb2.close();
  finRposcb3.close();
  finRnegcb3.close();








  // ------------------------------------------ //
  // ------------------------------------------ //
  // ---                                    --- //
  // --- HERE STARTS THE RATIO CALCULATIONS --- //
  // ---                                    --- //
  // ------------------------------------------ //
  // ------------------------------------------ //

  float pT1[45], epT1[45], ratio1[45], eratio1[45];
  float pT2[45], epT2[45], ratio2[45], eratio2[45];
  float pT3[45], epT3[45], ratio3[45], eratio3[45];
  float pTA1[45], epTA1[45], yieldA1[45], eyieldA1[45];
  float pTA2[45], epTA2[45], yieldA2[45], eyieldA2[45];
  float pTA3[45], epTA3[45], yieldA3[45], eyieldA3[45];
  float pTB[45], epTB[45], yieldB[45], eyieldB[45];

  int j;

  // ------------------------------------------ //
  // ------------------------------------------ //
  // ---                                    --- //
  // ---                                    --- //
  // ---                                    --- //
  // ------------------------------------------ //
  // ------------------------------------------ //



  // ------------- //
  // --- poscb --- //
  // ------------- //

  for(int i=0; i<45; i++)
    {
      // A
      j=i;
      pTA1[i] = -9;
      epTA1[i] = 0;
      yieldA1[i] = -9;
      eyieldA1[i] = 0;
      j=i;
      pTA1[j] = pT_poscb1[i];
      epTA1[j] = 0;
      yieldA1[j] = yield_poscb1[i];
      eyieldA1[j] = eyield_poscb1[i];
      pT1[i] = pTA1[i];
      epT1[i] = 0;
      ratio1[i] = -9;
      eratio1[i] = 0;
      //
      pTB[i] = pTpos_ppg026[i];
      epTB[i] = 0;
      yieldB[i] = yieldpos_ppg026[i];
      eyieldB[i] = eyieldpos_ppg026[i];
      // now do ratio
      if(yieldA1[i]>0&&yieldB[i]>0)
	{
	  pT1[i] = (pTA1[i]+pTB[i])/2.0;
	  epT1[i] = 0;
	  ratio1[i] = yieldA1[i]/yieldB[i];
	  eratio1[i] = ratio1[i]*sqrt((eyieldA1[i]/yieldA1[i])**2+(eyieldB[i]/yieldB[i])**2);
	  //cout<<"pt="<<pT[i]<<"\t"<<"run7="<<yieldA[i]<<"\t"<<"run2="<<yieldB[i]<<"\t"<<"ratio="<<ratio[i]<<endl;
	}
      else
	{
	  pT1[i] = pTA1[i];
	  epT1[i] = 0;
	  ratio1[i] = -9;
	  eratio1[i] = 0;
	}
      // now 2
      // A
      j=i;
      pTA2[i] = -9;
      epTA2[i] = 0;
      yieldA2[i] = -9;
      eyieldA2[i] = 0;
      j=i;
      pTA2[j] = pT_poscb2[i];
      epTA2[j] = 0;
      yieldA2[j] = yield_poscb2[i];
      eyieldA2[j] = eyield_poscb2[i];
      pT2[i] = pTA2[i];
      epT2[i] = 0;
      ratio2[i] = -9;
      eratio2[i] = 0;
      //
      pTB[i] = pTpos_ppg026[i];
      epTB[i] = 0;
      yieldB[i] = yieldpos_ppg026[i];
      eyieldB[i] = eyieldpos_ppg026[i];
      // now do ratio
      if(yieldA2[i]>0&&yieldB[i]>0)
	{
	  pT2[i] = (pTA2[i]+pTB[i])/2.0;
	  epT2[i] = 0;
	  ratio2[i] = yieldA2[i]/yieldB[i];
	  eratio2[i] = ratio2[i]*sqrt((eyieldA2[i]/yieldA2[i])**2+(eyieldB[i]/yieldB[i])**2);
	  //cout<<"pt="<<pT[i]<<"\t"<<"run7="<<yieldA[i]<<"\t"<<"run2="<<yieldB[i]<<"\t"<<"ratio="<<ratio[i]<<endl;
	}
      else
	{
	  pT2[i] = pTA2[i];
	  epT2[i] = 0;
	  ratio2[i] = -9;
	  eratio2[i] = 0;
	}
      // now 3
      // A
      j=i;
      pTA3[i] = -9;
      epTA3[i] = 0;
      yieldA3[i] = -9;
      eyieldA3[i] = 0;
      j=i;
      pTA3[j] = pT_poscb3[i];
      epTA3[j] = 0;
      yieldA3[j] = yield_poscb3[i];
      eyieldA3[j] = eyield_poscb3[i];
      pT3[i] = pTA3[i];
      epT3[i] = 0;
      ratio3[i] = -9;
      eratio3[i] = 0;
      //
      pTB[i] = pTpos_ppg026[i];
      epTB[i] = 0;
      yieldB[i] = yieldpos_ppg026[i];
      eyieldB[i] = eyieldpos_ppg026[i];
      // now do ratio
      if(yieldA3[i]>0&&yieldB[i]>0)
	{
	  pT3[i] = (pTA3[i]+pTB[i])/2.0;
	  epT3[i] = 0;
	  ratio3[i] = yieldA3[i]/yieldB[i];
	  eratio3[i] = ratio3[i]*sqrt((eyieldA3[i]/yieldA3[i])**2+(eyieldB[i]/yieldB[i])**2);
	  //cout<<"pt="<<pT[i]<<"\t"<<"run7="<<yieldA[i]<<"\t"<<"run2="<<yieldB[i]<<"\t"<<"ratio="<<ratio[i]<<endl;
	}
      else
	{
	  pT3[i] = pTA3[i];
	  epT3[i] = 0;
	  ratio3[i] = -9;
	  eratio3[i] = 0;
	}
    }
  TGraphErrors *tge_poscb1 = new TGraphErrors(number+offset,pT1,ratio1,epT1,eratio1);
  tge_poscb1->SetMarkerColor(kBlack);
  tge_poscb1->SetMarkerStyle(20);
  TGraphErrors *tge_poscb2 = new TGraphErrors(number+offset,pT2,ratio2,epT2,eratio2);
  tge_poscb2->SetMarkerColor(kRed);
  tge_poscb2->SetMarkerStyle(20);
  TGraphErrors *tge_poscb3 = new TGraphErrors(number+offset,pT3,ratio3,epT3,eratio3);
  tge_poscb3->SetMarkerColor(kBlue);
  tge_poscb3->SetMarkerStyle(20);

  // ------------- //
  // --- negcb --- //
  // ------------- //

  for(int i=0; i<45; i++)
    {
      // A
      j=i;
      pTA1[i] = -9;
      epTA1[i] = 0;
      yieldA1[i] = -9;
      eyieldA1[i] = 0;
      j=i;
      pTA1[j] = pT_negcb1[i];
      epTA1[j] = 0;
      yieldA1[j] = yield_negcb1[i];
      eyieldA1[j] = eyield_negcb1[i];
      pT1[i] = pTA1[i];
      epT1[i] = 0;
      ratio1[i] = -9;
      eratio1[i] = 0;
      //
      pTB[i] = pTneg_ppg026[i];
      epTB[i] = 0;
      yieldB[i] = yieldneg_ppg026[i];
      eyieldB[i] = eyieldneg_ppg026[i];
      // now do ratio
      if(yieldA1[i]>0&&yieldB[i]>0)
	{
	  pT1[i] = (pTA1[i]+pTB[i])/2.0;
	  epT1[i] = 0;
	  ratio1[i] = yieldA1[i]/yieldB[i];
	  eratio1[i] = ratio1[i]*sqrt((eyieldA1[i]/yieldA1[i])**2+(eyieldB[i]/yieldB[i])**2);
	  //cout<<"pt="<<pT[i]<<"\t"<<"run7="<<yieldA[i]<<"\t"<<"run2="<<yieldB[i]<<"\t"<<"ratio="<<ratio[i]<<endl;
	}
      else
	{
	  pT1[i] = pTA1[i];
	  epT1[i] = 0;
	  ratio1[i] = -9;
	  eratio1[i] = 0;
	}
      // now 2
      // A
      j=i;
      pTA2[i] = -9;
      epTA2[i] = 0;
      yieldA2[i] = -9;
      eyieldA2[i] = 0;
      j=i;
      pTA2[j] = pT_negcb2[i];
      epTA2[j] = 0;
      yieldA2[j] = yield_negcb2[i];
      eyieldA2[j] = eyield_negcb2[i];
      pT2[i] = pTA2[i];
      epT2[i] = 0;
      ratio2[i] = -9;
      eratio2[i] = 0;
      //
      pTB[i] = pTneg_ppg026[i];
      epTB[i] = 0;
      yieldB[i] = yieldneg_ppg026[i];
      eyieldB[i] = eyieldneg_ppg026[i];
      // now do ratio
      if(yieldA2[i]>0&&yieldB[i]>0)
	{
	  pT2[i] = (pTA2[i]+pTB[i])/2.0;
	  epT2[i] = 0;
	  ratio2[i] = yieldA2[i]/yieldB[i];
	  eratio2[i] = ratio2[i]*sqrt((eyieldA2[i]/yieldA2[i])**2+(eyieldB[i]/yieldB[i])**2);
	  //cout<<"pt="<<pT[i]<<"\t"<<"run7="<<yieldA[i]<<"\t"<<"run2="<<yieldB[i]<<"\t"<<"ratio="<<ratio[i]<<endl;
	}
      else
	{
	  pT2[i] = pTA2[i];
	  epT2[i] = 0;
	  ratio2[i] = -9;
	  eratio2[i] = 0;
	}
      // now 3
      // A
      j=i;
      pTA3[i] = -9;
      epTA3[i] = 0;
      yieldA3[i] = -9;
      eyieldA3[i] = 0;
      j=i;
      pTA3[j] = pT_negcb3[i];
      epTA3[j] = 0;
      yieldA3[j] = yield_negcb3[i];
      eyieldA3[j] = eyield_negcb3[i];
      pT3[i] = pTA3[i];
      epT3[i] = 0;
      ratio3[i] = -9;
      eratio3[i] = 0;
      //
      pTB[i] = pTneg_ppg026[i];
      epTB[i] = 0;
      yieldB[i] = yieldneg_ppg026[i];
      eyieldB[i] = eyieldneg_ppg026[i];
      // now do ratio
      if(yieldA3[i]>0&&yieldB[i]>0)
	{
	  pT3[i] = (pTA3[i]+pTB[i])/2.0;
	  epT3[i] = 0;
	  ratio3[i] = yieldA3[i]/yieldB[i];
	  eratio3[i] = ratio3[i]*sqrt((eyieldA3[i]/yieldA3[i])**2+(eyieldB[i]/yieldB[i])**2);
	  //cout<<"pt="<<pT[i]<<"\t"<<"run7="<<yieldA[i]<<"\t"<<"run2="<<yieldB[i]<<"\t"<<"ratio="<<ratio[i]<<endl;
	}
      else
	{
	  pT3[i] = pTA3[i];
	  epT3[i] = 0;
	  ratio3[i] = -9;
	  eratio3[i] = 0;
	}
    }
  TGraphErrors *tge_negcb1 = new TGraphErrors(number+offset,pT1,ratio1,epT1,eratio1);
  tge_negcb1->SetMarkerColor(kBlack);
  tge_negcb1->SetMarkerStyle(20);
  TGraphErrors *tge_negcb2 = new TGraphErrors(number+offset,pT2,ratio2,epT2,eratio2);
  tge_negcb2->SetMarkerColor(kRed);
  tge_negcb2->SetMarkerStyle(20);
  TGraphErrors *tge_negcb3 = new TGraphErrors(number+offset,pT3,ratio3,epT3,eratio3);
  tge_negcb3->SetMarkerColor(kBlue);
  tge_negcb3->SetMarkerStyle(20);


  float pTR_poscb1[20], yieldR_poscb1[20], eyieldR_poscb1[20];
  float pTR_negcb1[20], yieldR_negcb1[20], eyieldR_negcb1[20];
  float pTR_poscb2[20], yieldR_poscb2[20], eyieldR_poscb2[20];
  float pTR_negcb2[20], yieldR_negcb2[20], eyieldR_negcb2[20];
  float pTR_poscb3[20], yieldR_poscb3[20], eyieldR_poscb3[20];
  float pTR_negcb3[20], yieldR_negcb3[20], eyieldR_negcb3[20];


  // --- poscb ---//
  
  for(int i=0; i<12; i++)
    {
      // now 1
      //pT1[i] = pTA1[i];
      epT1[i] = 0;
      ratio1[i] = -9;
      eratio1[i] = 0;
      //      
      pTA1[i] = pTR_poscb1[i];
      epTA1[i] = 0;
      yieldA1[i] = yieldR_poscb1[i];
      eyieldA1[i] = eyieldR_poscb1[i];
      //
      pTB[i] = pT_ppg080[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg080[i];
      eyieldB[i] = eyield_ppg080[i];
      // now do ratio
      if(yieldA1[i]>0&&yieldB[i]>0)
	{
	  pT1[i] = (pTA1[i]+pTB[i])/2.0;
	  epT1[i] = 0;
	  ratio1[i] = yieldA1[i]/yieldB[i];
	  eratio1[i] = ratio1[i]*sqrt((eyieldA1[i]/yieldA1[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT1[i] = pTA1[i];
	  epT1[i] = 0;
	  ratio1[i] = -9;
	  eratio1[i] = 0;
	}
      // now 2
      //pT2[i] = pTA2[i];
      epT2[i] = 0;
      ratio2[i] = -9;
      eratio2[i] = 0;
      //      
      pTA2[i] = pTR_poscb2[i];
      epTA2[i] = 0;
      yieldA2[i] = yieldR_poscb2[i];
      eyieldA2[i] = eyieldR_poscb2[i];
      //
      pTB[i] = pT_ppg080[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg080[i];
      eyieldB[i] = eyield_ppg080[i];
      // now do ratio
      if(yieldA2[i]>0&&yieldB[i]>0)
	{
	  pT2[i] = (pTA2[i]+pTB[i])/2.0;
	  epT2[i] = 0;
	  ratio2[i] = yieldA2[i]/yieldB[i];
	  eratio2[i] = ratio2[i]*sqrt((eyieldA2[i]/yieldA2[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT2[i] = pTA2[i];
	  epT2[i] = 0;
	  ratio2[i] = -9;
	  eratio2[i] = 0;
	}
      // now 3
      //pT3[i] = pTA3[i];
      epT3[i] = 0;
      ratio3[i] = -9;
      eratio3[i] = 0;
      //      
      pTA3[i] = pTR_poscb3[i];
      epTA3[i] = 0;
      yieldA3[i] = yieldR_poscb3[i];
      eyieldA3[i] = eyieldR_poscb3[i];
      //
      pTB[i] = pT_ppg080[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg080[i];
      eyieldB[i] = eyield_ppg080[i];
      // now do ratio
      if(yieldA3[i]>0&&yieldB[i]>0)
	{
	  pT3[i] = (pTA3[i]+pTB[i])/2.0;
	  epT3[i] = 0;
	  ratio3[i] = yieldA3[i]/yieldB[i];
	  eratio3[i] = ratio3[i]*sqrt((eyieldA3[i]/yieldA3[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT3[i] = pTA3[i];
	  epT3[i] = 0;
	  ratio3[i] = -9;
	  eratio3[i] = 0;
	}
    } // end of for loop to calculate ratio
  TGraphErrors *tge2_poscb1 = new TGraphErrors(12,pT1,ratio1,epT1,eratio1);
  tge2_poscb1->SetMarkerColor(kBlack);
  tge2_poscb1->SetMarkerStyle(25);
  TGraphErrors *tge2_poscb2 = new TGraphErrors(12,pT2,ratio2,epT2,eratio2);
  tge2_poscb2->SetMarkerColor(kRed);
  tge2_poscb2->SetMarkerStyle(25);
  TGraphErrors *tge2_poscb3 = new TGraphErrors(12,pT3,ratio3,epT3,eratio3);
  tge2_poscb3->SetMarkerColor(kBlue);
  tge2_poscb3->SetMarkerStyle(25);
  
  // --- negcb ---//
  
  for(int i=0; i<12; i++)
    {
      // now 1
      //pT1[i] = pTA1[i];
      epT1[i] = 0;
      ratio1[i] = -9;
      eratio1[i] = 0;
      //      
      pTA1[i] = pTR_negcb1[i];
      epTA1[i] = 0;
      yieldA1[i] = yieldR_negcb1[i];
      eyieldA1[i] = eyieldR_negcb1[i];
      //
      pTB[i] = pT_ppg080[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg080[i];
      eyieldB[i] = eyield_ppg080[i];
      // now do ratio
      if(yieldA1[i]>0&&yieldB[i]>0)
	{
	  pT1[i] = (pTA1[i]+pTB[i])/2.0;
	  epT1[i] = 0;
	  ratio1[i] = yieldA1[i]/yieldB[i];
	  eratio1[i] = ratio1[i]*sqrt((eyieldA1[i]/yieldA1[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT1[i] = pTA1[i];
	  epT1[i] = 0;
	  ratio1[i] = -9;
	  eratio1[i] = 0;
	}
      // now 2
      //pT2[i] = pTA2[i];
      epT2[i] = 0;
      ratio2[i] = -9;
      eratio2[i] = 0;
      //      
      pTA2[i] = pTR_negcb2[i];
      epTA2[i] = 0;
      yieldA2[i] = yieldR_negcb2[i];
      eyieldA2[i] = eyieldR_negcb2[i];
      //
      pTB[i] = pT_ppg080[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg080[i];
      eyieldB[i] = eyield_ppg080[i];
      // now do ratio
      if(yieldA2[i]>0&&yieldB[i]>0)
	{
	  pT2[i] = (pTA2[i]+pTB[i])/2.0;
	  epT2[i] = 0;
	  ratio2[i] = yieldA2[i]/yieldB[i];
	  eratio2[i] = ratio2[i]*sqrt((eyieldA2[i]/yieldA2[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT2[i] = pTA2[i];
	  epT2[i] = 0;
	  ratio2[i] = -9;
	  eratio2[i] = 0;
	}
      // now 3
      //pT3[i] = pTA3[i];
      epT3[i] = 0;
      ratio3[i] = -9;
      eratio3[i] = 0;
      //      
      pTA3[i] = pTR_negcb3[i];
      epTA3[i] = 0;
      yieldA3[i] = yieldR_negcb3[i];
      eyieldA3[i] = eyieldR_negcb3[i];
      //
      pTB[i] = pT_ppg080[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg080[i];
      eyieldB[i] = eyield_ppg080[i];
      // now do ratio
      if(yieldA3[i]>0&&yieldB[i]>0)
	{
	  pT3[i] = (pTA3[i]+pTB[i])/2.0;
	  epT3[i] = 0;
	  ratio3[i] = yieldA3[i]/yieldB[i];
	  eratio3[i] = ratio3[i]*sqrt((eyieldA3[i]/yieldA3[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
      else
	{
	  pT3[i] = pTA3[i];
	  epT3[i] = 0;
	  ratio3[i] = -9;
	  eratio3[i] = 0;
	}
    } // end of for loop to calculate ratio
  TGraphErrors *tge2_negcb1 = new TGraphErrors(12,pT1,ratio1,epT1,eratio1);
  tge2_negcb1->SetMarkerColor(kBlack);
  tge2_negcb1->SetMarkerStyle(25);
  TGraphErrors *tge2_negcb2 = new TGraphErrors(12,pT2,ratio2,epT2,eratio2);
  tge2_negcb2->SetMarkerColor(kRed);
  tge2_negcb2->SetMarkerStyle(25);
  TGraphErrors *tge2_negcb3 = new TGraphErrors(12,pT3,ratio3,epT3,eratio3);
  tge2_negcb3->SetMarkerColor(kBlue);
  tge2_negcb3->SetMarkerStyle(25);

  // ---------------------- //
  // --- now draw plots --- //
  // ---------------------- //

  // now pos

  TMultiGraph *tmg_pos_cb = new TMultiGraph();
  tmg_pos_cb->Add(tge_poscb1);
  if(pion) tmg_pos_cb->Add(tge2_poscb1);
  tmg_pos_cb->Add(tge_poscb2);
  if(pion) tmg_pos_cb->Add(tge2_poscb2);
  tmg_pos_cb->Add(tge_poscb3);
  if(pion) tmg_pos_cb->Add(tge2_poscb3);
  tmg_pos_cb->Draw("ap");
  tmg_pos_cb->SetMaximum(2.0);
  tmg_pos_cb->SetMinimum(0.0);
  tmg_pos_cb->GetXaxis()->SetLimits(0.0,6.0);
  //if(kaon) tmg_pos_cb->GetXaxis()->SetLimits(0.0,3.0);
  tmg_pos_cb->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pos_cb->GetXaxis()->CenterTitle();
  tmg_pos_cb->GetYaxis()->SetTitle("Ratio");
  tmg_pos_cb->GetYaxis()->CenterTitle();
  
  TPaveText *pave_pos_cb = new TPaveText(1.01, 0.1, 2.5, 0.3, "br");
  pave_pos_cb->SetFillColor(10);
  pave_pos_cb->SetBorderSize(0);
  TText *text_pos_cb = pave_pos_cb->AddText(bigcentstring);
  pave_pos_cb->Draw();
  
  TPaveText *pave2_pos_cb = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  pave2_pos_cb->SetFillColor(10);
  pave2_pos_cb->SetBorderSize(0);
  TText *text2_pos_cb = pave2_pos_cb->AddText("Au+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_pos_cb->Draw();
  
  TLegend *leg_pos_cb = new TLegend(0.68,0.18,0.88,0.38);
  leg_pos_cb->SetFillColor(kWhite);
  leg_pos_cb->SetBorderSize(0);
  leg_pos_cb->AddEntry(tge_poscb1,"#pi^{+}, asymm","p");
  if(pion) leg_pos_cb->AddEntry(tge2_poscb1,"#pi^{+}, asymm","p");
  leg_pos_cb->AddEntry(tge_poscb2,"#pi^{+}, ep cut","p");
  if(pion) leg_pos_cb->AddEntry(tge2_poscb2,"#pi^{+}, ep cut","p");
  leg_pos_cb->AddEntry(tge_poscb3,"#pi^{+}, n0 cut","p");
  if(pion) leg_pos_cb->AddEntry(tge2_poscb3,"#pi^{+}, n0 cut","p");
  leg_pos_cb->Draw();
  
  char gifname_pos_cb[100];
  sprintf(gifname_pos_cb,"RatioFigures/pidcompare_published_%s_pos_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_pos_cb[100];
  sprintf(epsname_pos_cb,"RatioFigures/pidcompare_published_%s_pos_%d_dis_cent%s.eps",sectorstring,pid,centstring);
  
  c1->Print(gifname_pos_cb);
  c1->Print(epsname_pos_cb);
  
  // now neg

  TMultiGraph *tmg_neg_cb = new TMultiGraph();
  tmg_neg_cb->Add(tge_negcb1);
  if(pion) tmg_neg_cb->Add(tge2_negcb1);
  tmg_neg_cb->Add(tge_negcb2);
  if(pion) tmg_neg_cb->Add(tge2_negcb2);
  tmg_neg_cb->Add(tge_negcb3);
  if(pion) tmg_neg_cb->Add(tge2_negcb3);
  tmg_neg_cb->Draw("ap");
  tmg_neg_cb->SetMaximum(2.0);
  tmg_neg_cb->SetMinimum(0.0);
  tmg_neg_cb->GetXaxis()->SetLimits(0.0,6.0);
  //if(kaon) tmg_pos_cb->GetXaxis()->SetLimits(0.0,3.0);//oops
  tmg_neg_cb->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_neg_cb->GetXaxis()->CenterTitle();
  tmg_neg_cb->GetYaxis()->SetTitle("Ratio");
  tmg_neg_cb->GetYaxis()->CenterTitle();
  
  TPaveText *pave_neg_cb = new TPaveText(1.01, 0.1, 2.5, 0.3, "br");
  pave_neg_cb->SetFillColor(10);
  pave_neg_cb->SetBorderSize(0);
  TText *text_neg_cb = pave_neg_cb->AddText(bigcentstring);
  pave_neg_cb->Draw();
  
  TPaveText *pave2_neg_cb = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  pave2_neg_cb->SetFillColor(10);
  pave2_neg_cb->SetBorderSize(0);
  TText *text2_neg_cb = pave2_neg_cb->AddText("Au+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_neg_cb->Draw();
  
  TLegend *leg_neg_cb = new TLegend(0.68,0.18,0.88,0.38);
  leg_neg_cb->SetFillColor(kWhite);
  leg_neg_cb->SetBorderSize(0);
  leg_neg_cb->AddEntry(tge_negcb1,"#pi^{+}, asymm","p");
  if(pion) leg_neg_cb->AddEntry(tge2_negcb1,"#pi^{+}, asymm","p");
  leg_neg_cb->AddEntry(tge_negcb2,"#pi^{+}, ep cut","p");
  if(pion) leg_neg_cb->AddEntry(tge2_negcb2,"#pi^{+}, ep cut","p");
  leg_neg_cb->AddEntry(tge_negcb3,"#pi^{+}, n0 cut","p");
  if(pion) leg_neg_cb->AddEntry(tge2_negcb3,"#pi^{+}, n0 cut","p");
  leg_neg_cb->Draw();
  
  char gifname_neg_cb[100];
  sprintf(gifname_neg_cb,"RatioFigures/pidcompare_published_%s_neg_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_neg_cb[100];
  sprintf(epsname_neg_cb,"RatioFigures/pidcompare_published_%s_neg_%d_dis_cent%s.eps",sectorstring,pid,centstring);
  
  c1->Print(gifname_neg_cb);
  c1->Print(epsname_neg_cb);
  
  
    
}

void pubratios()
{

  cout<<"hello! unfortunately, this is nowhere near as much fun "<<endl
      <<"as the name of the macro would suggest but it will make some"<<endl
      <<"nice plots of the ratios of the Run8 spectra to the"<<endl
      <<"published Run3 spectra for you."<<endl;

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
      for(int ipid=0; ipid<6; ipid++)
  	{
	  doit(0,ipid,icent);
  	}
    }
  
  
  cout<<"done!  have a nice day!"<<endl;

}

void doit(int sector=0, int pid=0, int centid=0)
{

  //if(pid==0||pid==2||pid==4) return; // TEMP!!!
  //if(pid==2||pid==4) return; // TEMP!!!

  // --- beginning of code

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
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

  float pT_ppg044[23], yield_ppg044[23], eyield_ppg044[23];
  float ept[23];
  char finname[30];
  sprintf(finname,"ppg044/pi0_%s.dat",centstring);
  for(int i=0; i<23; i++)
    {
      pT_ppg044[i]=i/2.0+0.25;
      ept[i]=0;
      yield_ppg044[i]=0;
      eyield_ppg044[i]=0;
    }
  ifstream fin44(finname);
  for(int i=0; i<21; i++)
    {
      fin44>>pT_ppg044[i+2]>>yield_ppg044[i+2]>>eyield_ppg044[i+2];
    }
  fin44.close();




  // --- ppg030 stuff

  float pTpos_ppg030[36], yieldpos_ppg030[36], eyieldpos_ppg030[36];
  float pTneg_ppg030[36], yieldneg_ppg030[36], eyieldneg_ppg030[36];
  float ept[36];

  for(int i=0; i<7; i++)
    {
      pTpos_ppg030[i] = i/10.0+0.05;
      //epTpos_ppg030[i] = 0;
      yieldpos_ppg030[i] = 0;
      eyieldpos_ppg030[i] = 0;
      pTneg_ppg030[i] = i/10.0+0.05;
      //epTneg_ppg030[i] = 0;
      yieldneg_ppg030[i] = 0;
      eyieldneg_ppg030[i] = 0;
      ept[i]=0;
    }

  int number = 1;
  int offset = 0;
  char finposname[30];
  char finnegname[30];
  if(pid==0||pid==1)
    {
      number = 18;
      offset = 3;
      sprintf(finposname,"ppg030/pospion_%s.dat",centstring);
      sprintf(finnegname,"ppg030/negpion_%s.dat",centstring);
    }
  else if(pid==2||pid==3)
    {
      number = 13;
      if(centid==1) number = 12;
      offset = 4;
      sprintf(finposname,"ppg030/poskaon_%s.dat",centstring);
      sprintf(finnegname,"ppg030/negkaon_%s.dat",centstring);
    }
  else if(pid==4||pid==5)
    {
      number = 17;
      offset = 6;
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
      ept[i+offset]=0;
      finpos30>>pTpos_ppg030[i+offset]>>yieldpos_ppg030[i+offset]>>eyieldpos_ppg030[i+offset];
      finneg30>>pTneg_ppg030[i+offset]>>yieldneg_ppg030[i+offset]>>eyieldneg_ppg030[i+offset];
    }
  finpos30.close();
  finneg30.close();
  


  // ---



  // --- input data

  char fnameinpospp[100];
  char fnameinnegpp[100];
  char fnameinposmm[100];
  char fnameinnegmm[100];
  char fnameinposcb[100];
  char fnameinnegcb[100];

  sprintf(fnameinpospp,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegpp,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinposmm,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegmm,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinposcb,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

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
      // NEW, TEMPORARY, SAME OLD STORY
      // YOU REALLY WANT TO KNOW ABOUT THIS
      //if(i<10){yield_pospp[i]=0;yield_posmm[i]=0;yield_poscb[i]=0;yield_negpp[i]=0;yield_negmm[i]=0;yield_negcb[i]=0;}
      if(i<5){yield_pospp[i]=0;yield_posmm[i]=0;yield_poscb[i]=0;yield_negpp[i]=0;yield_negmm[i]=0;yield_negcb[i]=0;}
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();



  // --- now input the rebinned data
  // --- perfect for the pi0

  sprintf(fnameinpospp,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegpp,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinposmm,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegmm,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinposcb,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pTR_pospp[20], yieldR_pospp[20], eyieldR_pospp[20];
  float pTR_negpp[20], yieldR_negpp[20], eyieldR_negpp[20];
  float pTR_posmm[20], yieldR_posmm[20], eyieldR_posmm[20];
  float pTR_negmm[20], yieldR_negmm[20], eyieldR_negmm[20];
  float pTR_poscb[20], yieldR_poscb[20], eyieldR_poscb[20];
  float pTR_negcb[20], yieldR_negcb[20], eyieldR_negcb[20];

  for(int i=0; i<20; i++)
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



  float esysratio[36]; // NEW!

  float pT[36], epT[36], ratio[36], eratio[36];
  float pTA[36], epTA[36], yieldA[36], eyieldA[36];
  float pTB[36], epTB[36], yieldB[36], eyieldB[36];

  int j;



  // ------------- //
  // --- pospp --- //
  // ------------- //

  for(int i=0; i<36; i++)
    {
      // A
      j=i;
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<15)
	{
	  j=i;
	  pTA[j] = pT_pospp[i];
	  epTA[j] = 0;
	  yieldA[j] = yield_pospp[i];
	  eyieldA[j] = eyield_pospp[i];
	}
      if(i>14&&i<27)
	{
	  if(i%2!=1) continue;
	  j=i/2+8;
	  pTA[j] = (pT_pospp[i]+pT_pospp[i+1])/2.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_pospp[i]+yield_pospp[i+1])/2.0;
	  eyieldA[j] = sqrt(eyield_pospp[i]**2+eyield_pospp[i+1]**2)/2.0;
	}
      if(i==27)
	{
	  j=21;
	  pTA[j] = (pT_pospp[i]+pT_pospp[i+1]+pT_pospp[i+2]+pT_pospp[i+3])/4.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_pospp[i]+yield_pospp[i+1]+yield_pospp[i+2]+yield_pospp[i+3])/4.0;
	  eyieldA[j] = sqrt(eyield_pospp[i]**2+eyield_pospp[i+1]**2+eyield_pospp[i+2]**2+eyield_pospp[i+3]**2)/4.0;
	}
      if(i>27)
	{
	  if(i%6!=1) continue;
	  j=i/6+17;
	  pTA[j] = (pT_pospp[i]+pT_pospp[i+1]+pT_pospp[i+2]+
		    pT_pospp[i+3]+pT_pospp[i+4]+pT_pospp[i+5])/6.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_pospp[i]+yield_pospp[i+1]+yield_pospp[i+2]+
		       yield_pospp[i+3]+yield_pospp[i+4]+yield_pospp[i+5])/6.0;
	  eyieldA[j] = sqrt(eyield_pospp[i]**2+eyield_pospp[i+1]**2+eyield_pospp[i+2]**2+
			    eyield_pospp[i+3]**2+eyield_pospp[i+4]**2+eyield_pospp[i+5]**2)/6.0;
	}

    } // end of for loop for rebinning

  for(int i=0; i<23; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      pTB[i] = pTpos_ppg030[i];
      epTB[i] = 0;
      yieldB[i] = yieldpos_ppg030[i];
      eyieldB[i] = eyieldpos_ppg030[i];

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
    } // end of for loop to calculate ratio
  TGraphErrors *tge_pospp = new TGraphErrors(number+offset,pT,ratio,epT,eratio);
  tge_pospp->SetMarkerColor(kBlue);
  tge_pospp->SetMarkerStyle(20);

  // ---

  // ------------- //
  // --- negpp --- //
  // ------------- //

  for(int i=0; i<36; i++)
    {
      // A
      j=i;
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<15)
	{
	  j=i;
	  pTA[j] = pT_negpp[i];
	  epTA[j] = 0;
	  yieldA[j] = yield_negpp[i];
	  eyieldA[j] = eyield_negpp[i];
	}
      if(i>14&&i<27)
	{
	  if(i%2!=1) continue;
	  j=i/2+8;
	  pTA[j] = (pT_negpp[i]+pT_negpp[i+1])/2.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_negpp[i]+yield_negpp[i+1])/2.0;
	  eyieldA[j] = sqrt(eyield_negpp[i]**2+eyield_negpp[i+1]**2)/2.0;
	}
      if(i==27)
	{
	  j=21;
	  pTA[j] = (pT_negpp[i]+pT_negpp[i+1]+pT_negpp[i+2]+pT_negpp[i+3])/4.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_negpp[i]+yield_negpp[i+1]+yield_negpp[i+2]+yield_negpp[i+3])/4.0;
	  eyieldA[j] = sqrt(eyield_negpp[i]**2+eyield_negpp[i+1]**2+eyield_negpp[i+2]**2+eyield_negpp[i+3]**2)/4.0;
	}
      if(i>27)
	{
	  if(i%6!=1) continue;
	  j=i/6+17;
	  pTA[j] = (pT_negpp[i]+pT_negpp[i+1]+pT_negpp[i+2]+
		    pT_negpp[i+3]+pT_negpp[i+4]+pT_negpp[i+5])/6.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_negpp[i]+yield_negpp[i+1]+yield_negpp[i+2]+
		       yield_negpp[i+3]+yield_negpp[i+4]+yield_negpp[i+5])/6.0;
	  eyieldA[j] = sqrt(eyield_negpp[i]**2+eyield_negpp[i+1]**2+eyield_negpp[i+2]**2+
			    eyield_negpp[i+3]**2+eyield_negpp[i+4]**2+eyield_negpp[i+5]**2)/6.0;
	}

    } // end of for loop for rebinning

  for(int i=0; i<23; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      // this is where the typo was
      pTB[i] = pTneg_ppg030[i];
      epTB[i] = 0;
      yieldB[i] = yieldneg_ppg030[i];
      eyieldB[i] = eyieldneg_ppg030[i];

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
    } // end of for loop to calculate ratio
  TGraphErrors *tge_negpp = new TGraphErrors(number+offset,pT,ratio,epT,eratio);
  tge_negpp->SetMarkerColor(kRed);
  tge_negpp->SetMarkerStyle(21);

  // ---

  // ------------- //
  // --- posmm --- //
  // ------------- //

  for(int i=0; i<36; i++)
    {
      // A
      j=i;
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<15)
	{
	  j=i;
	  pTA[j] = pT_posmm[i];
	  epTA[j] = 0;
	  yieldA[j] = yield_posmm[i];
	  eyieldA[j] = eyield_posmm[i];
	}
      if(i>14&&i<27)
	{
	  if(i%2!=1) continue;
	  j=i/2+8;
	  pTA[j] = (pT_posmm[i]+pT_posmm[i+1])/2.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_posmm[i]+yield_posmm[i+1])/2.0;
	  eyieldA[j] = sqrt(eyield_posmm[i]**2+eyield_posmm[i+1]**2)/2.0;
	}
      if(i==27)
	{
	  j=21;
	  pTA[j] = (pT_posmm[i]+pT_posmm[i+1]+pT_posmm[i+2]+pT_posmm[i+3])/4.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_posmm[i]+yield_posmm[i+1]+yield_posmm[i+2]+yield_posmm[i+3])/4.0;
	  eyieldA[j] = sqrt(eyield_posmm[i]**2+eyield_posmm[i+1]**2+eyield_posmm[i+2]**2+eyield_posmm[i+3]**2)/4.0;
	}
      if(i>27)
	{
	  if(i%6!=1) continue;
	  j=i/6+17;
	  pTA[j] = (pT_posmm[i]+pT_posmm[i+1]+pT_posmm[i+2]+
		    pT_posmm[i+3]+pT_posmm[i+4]+pT_posmm[i+5])/6.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_posmm[i]+yield_posmm[i+1]+yield_posmm[i+2]+
		       yield_posmm[i+3]+yield_posmm[i+4]+yield_posmm[i+5])/6.0;
	  eyieldA[j] = sqrt(eyield_posmm[i]**2+eyield_posmm[i+1]**2+eyield_posmm[i+2]**2+
			    eyield_posmm[i+3]**2+eyield_posmm[i+4]**2+eyield_posmm[i+5]**2)/6.0;
	}

    } // end of for loop for rebinning

  for(int i=0; i<23; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      pTB[i] = pTpos_ppg030[i];
      epTB[i] = 0;
      yieldB[i] = yieldpos_ppg030[i];
      eyieldB[i] = eyieldpos_ppg030[i];

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
    } // end of for loop to calculate ratio
  TGraphErrors *tge_posmm = new TGraphErrors(number+offset,pT,ratio,epT,eratio);
  tge_posmm->SetMarkerColor(kBlue);
  tge_posmm->SetMarkerStyle(20);

  // ---

  // ------------- //
  // --- negmm --- //
  // ------------- //

  for(int i=0; i<36; i++)
    {
      // A
      j=i;
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<15)
	{
	  j=i;
	  pTA[j] = pT_negmm[i];
	  epTA[j] = 0;
	  yieldA[j] = yield_negmm[i];
	  eyieldA[j] = eyield_negmm[i];
	}
      if(i>14&&i<27)
	{
	  if(i%2!=1) continue;
	  j=i/2+8;
	  pTA[j] = (pT_negmm[i]+pT_negmm[i+1])/2.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_negmm[i]+yield_negmm[i+1])/2.0;
	  eyieldA[j] = sqrt(eyield_negmm[i]**2+eyield_negmm[i+1]**2)/2.0;
	}
      if(i==27)
	{
	  j=21;
	  pTA[j] = (pT_negmm[i]+pT_negmm[i+1]+pT_negmm[i+2]+pT_negmm[i+3])/4.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_negmm[i]+yield_negmm[i+1]+yield_negmm[i+2]+yield_negmm[i+3])/4.0;
	  eyieldA[j] = sqrt(eyield_negmm[i]**2+eyield_negmm[i+1]**2+eyield_negmm[i+2]**2+eyield_negmm[i+3]**2)/4.0;
	}
      if(i>27)
	{
	  if(i%6!=1) continue;
	  j=i/6+17;
	  pTA[j] = (pT_negmm[i]+pT_negmm[i+1]+pT_negmm[i+2]+
		    pT_negmm[i+3]+pT_negmm[i+4]+pT_negmm[i+5])/6.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_negmm[i]+yield_negmm[i+1]+yield_negmm[i+2]+
		       yield_negmm[i+3]+yield_negmm[i+4]+yield_negmm[i+5])/6.0;
	  eyieldA[j] = sqrt(eyield_negmm[i]**2+eyield_negmm[i+1]**2+eyield_negmm[i+2]**2+
			    eyield_negmm[i+3]**2+eyield_negmm[i+4]**2+eyield_negmm[i+5]**2)/6.0;
	}

    } // end of for loop for rebinning

  for(int i=0; i<23; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      // this is where the typo was
      pTB[i] = pTneg_ppg030[i];
      epTB[i] = 0;
      yieldB[i] = yieldneg_ppg030[i];
      eyieldB[i] = eyieldneg_ppg030[i];

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
    } // end of for loop to calculate ratio
  TGraphErrors *tge_negmm = new TGraphErrors(number+offset,pT,ratio,epT,eratio);
  tge_negmm->SetMarkerColor(kRed);
  tge_negmm->SetMarkerStyle(21);

  // --- 












  // ---

  TMultiGraph *tmg_good = new TMultiGraph();
  tmg_good->Add(tge_pospp);
  tmg_good->Add(tge_negmm);
  tmg_good->Draw("ap");
  tmg_good->SetMaximum(2.0);
  tmg_good->SetMinimum(0.0);
  tmg_good->GetXaxis()->SetLimits(0.0,3.5);
  tmg_good->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_good->GetXaxis()->CenterTitle();
  tmg_good->GetYaxis()->SetTitle("Ratio");
  tmg_good->GetYaxis()->CenterTitle();

  TPaveText *pave_good = new TPaveText(0.51, 0.1, 1.49, 0.3, "br");
  pave_good->SetFillColor(10);
  pave_good->SetBorderSize(0);
  TText *text_good = pave_good->AddText(bigcentstring);
  pave_good->Draw();

  TPaveText *pave2_good = new TPaveText(0.25, 2.04, 2.75, 2.2, "br");
  pave2_good->SetFillColor(10);
  pave2_good->SetBorderSize(0);
  TText *text2_good = pave2_good->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_good->Draw();

  TLegend *leg_good = new TLegend(0.68,0.68,0.88,0.88);
  leg_good->SetFillColor(kWhite);
  leg_good->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      leg_good->AddEntry(tge_pospp,"#pi^{+}, ++ field","p");
      leg_good->AddEntry(tge_negmm,"#pi^{-}, -- field","p");
    }
  if(pid==2||pid==3)
    {
      leg_good->AddEntry(tge_pospp,"K^{+}, ++ field","p");
      leg_good->AddEntry(tge_negmm,"K^{-}, -- field","p");
    }
  if(pid==4||pid==5)
    {
      leg_good->AddEntry(tge_pospp,"p, ++ field","p");
      leg_good->AddEntry(tge_negmm,"#bar{p}, -- field","p");
    }
  leg_good->Draw();

  char gifname_good[100];
  sprintf(gifname_good,"RatioFigures/published_%s_goodchfi_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_good[100];
  sprintf(epsname_good,"RatioFigures/published_%s_goodchfi_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_good);
  //c1->Print(epsname_good);


  // ---

  TMultiGraph *tmg_bad = new TMultiGraph();
  tmg_bad->Add(tge_posmm);
  tmg_bad->Add(tge_negpp);
  tmg_bad->Draw("ap");
  tmg_bad->SetMaximum(2.0);
  tmg_bad->SetMinimum(0.0);
  tmg_bad->GetXaxis()->SetLimits(0.0,3.5);
  tmg_bad->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_bad->GetXaxis()->CenterTitle();
  tmg_bad->GetYaxis()->SetTitle("Ratio");
  tmg_bad->GetYaxis()->CenterTitle();

  TPaveText *pave_bad = new TPaveText(0.51, 0.1, 1.49, 0.3, "br");
  pave_bad->SetFillColor(10);
  pave_bad->SetBorderSize(0);
  TText *text_bad = pave_bad->AddText(bigcentstring);
  pave_bad->Draw();

  TPaveText *pave2_bad = new TPaveText(0.25, 2.04, 2.75, 2.2, "br");
  pave2_bad->SetFillColor(10);
  pave2_bad->SetBorderSize(0);
  TText *text2_bad = pave2_bad->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_bad->Draw();

  TLegend *leg_bad = new TLegend(0.68,0.68,0.88,0.88);
  leg_bad->SetFillColor(kWhite);
  leg_bad->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      leg_bad->AddEntry(tge_posmm,"#pi^{+}, -- field","p");
      leg_bad->AddEntry(tge_negpp,"#pi^{-}, ++ field","p");
    }
  if(pid==2||pid==3)
    {
      leg_bad->AddEntry(tge_posmm,"K^{+}, -- field","p");
      leg_bad->AddEntry(tge_negpp,"K^{-}, ++ field","p");
    }
  if(pid==4||pid==5)
    {
      leg_bad->AddEntry(tge_posmm,"p, -- field","p");
      leg_bad->AddEntry(tge_negpp,"#bar{p}, ++ field","p");
    }
  leg_bad->Draw();

  char gifname_bad[100];
  sprintf(gifname_bad,"RatioFigures/published_%s_badchfi_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_bad[100];
  sprintf(epsname_bad,"RatioFigures/published_%s_badchfi_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_bad);
  //c1->Print(epsname_bad);

  // ---
  // ---
  // ---

  // ---

  TMultiGraph *tmg_pp = new TMultiGraph();
  tmg_pp->Add(tge_pospp);
  tmg_pp->Add(tge_negpp);
  tmg_pp->Draw("ap");
  tmg_pp->SetMaximum(2.0);
  tmg_pp->SetMinimum(0.0);
  tmg_pp->GetXaxis()->SetLimits(0.0,3.5);
  tmg_pp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pp->GetXaxis()->CenterTitle();
  tmg_pp->GetYaxis()->SetTitle("Ratio");
  tmg_pp->GetYaxis()->CenterTitle();

  TPaveText *pave_pp = new TPaveText(0.51, 0.1, 1.49, 0.3, "br");
  pave_pp->SetFillColor(10);
  pave_pp->SetBorderSize(0);
  TText *text_pp = pave_pp->AddText(bigcentstring);
  pave_pp->Draw();

  TPaveText *pave2_pp = new TPaveText(0.25, 2.04, 2.75, 2.2, "br");
  pave2_pp->SetFillColor(10);
  pave2_pp->SetBorderSize(0);
  TText *text2_pp = pave2_pp->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_pp->Draw();

  TLegend *leg_pp = new TLegend(0.68,0.68,0.88,0.88);
  leg_pp->SetFillColor(kWhite);
  leg_pp->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      leg_pp->AddEntry(tge_pospp,"#pi^{+}, ++ field","p");
      leg_pp->AddEntry(tge_negpp,"#pi^{-}, ++ field","p");
    }
  if(pid==2||pid==3)
    {
      leg_pp->AddEntry(tge_pospp,"K^{+}, ++ field","p");
      leg_pp->AddEntry(tge_negpp,"K^{-}, ++ field","p");
    }
  if(pid==4||pid==5)
    {
      leg_pp->AddEntry(tge_pospp,"p, ++ field","p");
      leg_pp->AddEntry(tge_negpp,"#bar{p}, ++ field","p");
    }
  leg_pp->Draw();

  char gifname_pp[100];
  sprintf(gifname_pp,"RatioFigures/published_%s_pp_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_pp[100];
  sprintf(epsname_pp,"RatioFigures/published_%s_pp_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_pp);
  //c1->Print(epsname_pp);

  // ---

  TMultiGraph *tmg_mm = new TMultiGraph();
  tmg_mm->Add(tge_posmm);
  tmg_mm->Add(tge_negmm);
  tmg_mm->Draw("ap");
  tmg_mm->SetMaximum(2.0);
  tmg_mm->SetMinimum(0.0);
  tmg_mm->GetXaxis()->SetLimits(0.0,3.5);
  tmg_mm->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_mm->GetXaxis()->CenterTitle();
  tmg_mm->GetYaxis()->SetTitle("Ratio");
  tmg_mm->GetYaxis()->CenterTitle();

  TPaveText *pave_mm = new TPaveText(0.51, 0.1, 1.49, 0.3, "br");
  pave_mm->SetFillColor(10);
  pave_mm->SetBorderSize(0);
  TText *text_mm = pave_mm->AddText(bigcentstring);
  pave_mm->Draw();

  TPaveText *pave2_mm = new TPaveText(0.25, 2.04, 2.75, 2.2, "br");
  pave2_mm->SetFillColor(10);
  pave2_mm->SetBorderSize(0);
  TText *text2_mm = pave2_mm->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_mm->Draw();

  TLegend *leg_mm = new TLegend(0.68,0.68,0.88,0.88);
  leg_mm->SetFillColor(kWhite);
  leg_mm->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      leg_mm->AddEntry(tge_posmm,"#pi^{+}, -- field","p");
      leg_mm->AddEntry(tge_negmm,"#pi^{-}, -- field","p");
    }
  if(pid==2||pid==3)
    {
      leg_mm->AddEntry(tge_posmm,"K^{+}, -- field","p");
      leg_mm->AddEntry(tge_negmm,"K^{-}, -- field","p");
    }
  if(pid==4||pid==5)
    {
      leg_mm->AddEntry(tge_posmm,"p, -- field","p");
      leg_mm->AddEntry(tge_negmm,"#bar{p}, -- field","p");
    }
  leg_mm->Draw();

  char gifname_mm[100];
  sprintf(gifname_mm,"RatioFigures/published_%s_mm_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_mm[100];
  sprintf(epsname_mm,"RatioFigures/published_%s_mm_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_mm);
  //c1->Print(epsname_mm);



  // ---

  tge_pospp->SetMarkerColor(kBlack);
  tge_pospp->SetMarkerStyle(21);
  TMultiGraph *tmg_pos = new TMultiGraph();
  tmg_pos->Add(tge_pospp);
  tmg_pos->Add(tge_posmm);
  tmg_pos->Draw("ap");
  tmg_pos->SetMaximum(2.0);
  tmg_pos->SetMinimum(0.0);
  tmg_pos->GetXaxis()->SetLimits(0.0,3.5);
  tmg_pos->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pos->GetXaxis()->CenterTitle();
  tmg_pos->GetYaxis()->SetTitle("Ratio");
  tmg_pos->GetYaxis()->CenterTitle();

  TPaveText *pave_pos = new TPaveText(0.51, 0.1, 1.49, 0.3, "br");
  pave_pos->SetFillColor(10);
  pave_pos->SetBorderSize(0);
  TText *text_pos = pave_pos->AddText(bigcentstring);
  pave_pos->Draw();

  TPaveText *pave2_pos = new TPaveText(0.25, 2.04, 2.75, 2.2, "br");
  pave2_pos->SetFillColor(10);
  pave2_pos->SetBorderSize(0);
  TText *text2_pos = pave2_pos->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_pos->Draw();

  TLegend *leg_pos = new TLegend(0.68,0.68,0.88,0.88);
  leg_pos->SetFillColor(kWhite);
  leg_pos->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      leg_pos->AddEntry(tge_pospp,"#pi^{+}, ++ field","p");
      leg_pos->AddEntry(tge_posmm,"#pi^{+}, -- field","p");
    }
  if(pid==2||pid==3)
    {
      leg_pos->AddEntry(tge_pospp,"K^{+}, ++ field","p");
      leg_pos->AddEntry(tge_posmm,"K^{+}, -- field","p");
    }
  if(pid==4||pid==5)
    {
      leg_pos->AddEntry(tge_pospp,"p, ++ field","p");
      leg_pos->AddEntry(tge_posmm,"p, -- field","p");
    }
  leg_pos->Draw();

  char gifname_pos[100];
  sprintf(gifname_pos,"RatioFigures/published_%s_pos_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_pos[100];
  sprintf(epsname_pos,"RatioFigures/published_%s_pos_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_pos);
  //c1->Print(epsname_pos);


  tge_negpp->SetMarkerColor(kBlack);
  tge_negpp->SetMarkerStyle(21);
  TMultiGraph *tmg_neg = new TMultiGraph();
  tmg_neg->Add(tge_negpp);
  tmg_neg->Add(tge_negmm);
  tmg_neg->Draw("ap");
  tmg_neg->SetMaximum(2.0);
  tmg_neg->SetMinimum(0.0);
  tmg_neg->GetXaxis()->SetLimits(0.0,3.5);
  tmg_neg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_neg->GetXaxis()->CenterTitle();
  tmg_neg->GetYaxis()->SetTitle("Ratio");
  tmg_neg->GetYaxis()->CenterTitle();

  TPaveText *pave_neg = new TPaveText(0.51, 0.1, 1.49, 0.3, "br");
  pave_neg->SetFillColor(10);
  pave_neg->SetBorderSize(0);
  TText *text_neg = pave_neg->AddText(bigcentstring);
  pave_neg->Draw();

  TPaveText *pave2_neg = new TPaveText(0.25, 2.04, 2.75, 2.2, "br");
  pave2_neg->SetFillColor(10);
  pave2_neg->SetBorderSize(0);
  TText *text2_neg = pave2_neg->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_neg->Draw();

  TLegend *leg_neg = new TLegend(0.68,0.68,0.88,0.88);
  leg_neg->SetFillColor(kWhite);
  leg_neg->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      leg_neg->AddEntry(tge_negpp,"#pi^{-}, ++ field","p");
      leg_neg->AddEntry(tge_negmm,"#pi^{-}, -- field","p");
    }
  if(pid==2||pid==3)
    {
      leg_neg->AddEntry(tge_negpp,"K^{-}, ++ field","p");
      leg_neg->AddEntry(tge_negmm,"K^{-}, -- field","p");
    }
  if(pid==4||pid==5)
    {
      leg_neg->AddEntry(tge_negpp,"#bar{p}, ++ field","p");
      leg_neg->AddEntry(tge_negmm,"#bar{p}, -- field","p");
    }
  leg_neg->Draw();

  char gifname_neg[100];
  sprintf(gifname_neg,"RatioFigures/published_%s_neg_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_neg[100];
  sprintf(epsname_neg,"RatioFigures/published_%s_neg_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_neg);
  //c1->Print(epsname_neg);















  // -------------------------- //
  // --- now doing pi0 part --- //
  // -------------------------- //

  //if(pid>1) return;

  c1->Clear();

  // --- pospp ---//

  for(int i=0; i<12; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      pTA[i] = pTR_pospp[i];
      epTA[i] = 0;
      yieldA[i] = yieldR_pospp[i];
      eyieldA[i] = eyieldR_pospp[i];

      pTB[i] = pT_ppg044[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg044[i];
      eyieldB[i] = eyield_ppg044[i];

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

      //cout<<pT_ppg044[i]<<"\t"<<yield_ppg044[i]<<endl;
      //cout<<pTB[i]<<"\t"<<yieldB[i]<<"\t"<<pTA[i]<<"\t"<<yieldA[i]<<endl;

    } // end of for loop to calculate ratio
  TGraphErrors *tge2_pospp = new TGraphErrors(12,pT,ratio,epT,eratio);
  tge2_pospp->SetMarkerColor(kBlue);
  tge2_pospp->SetMarkerStyle(20);

  // --- negpp --- //

  for(int i=0; i<12; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      pTA[i] = pTR_negpp[i];
      epTA[i] = 0;
      yieldA[i] = yieldR_negpp[i];
      eyieldA[i] = eyieldR_negpp[i];

      pTB[i] = pT_ppg044[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg044[i];
      eyieldB[i] = eyield_ppg044[i];

      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
    } // end of for loop to calculate ratio
  TGraphErrors *tge2_negpp = new TGraphErrors(12,pT,ratio,epT,eratio);
  tge2_negpp->SetMarkerColor(kRed);
  tge2_negpp->SetMarkerStyle(21);

  // ---

  // --- posmm --- //

  for(int i=0; i<12; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      pTA[i] = pTR_posmm[i];
      epTA[i] = 0;
      yieldA[i] = yieldR_posmm[i];
      eyieldA[i] = eyieldR_posmm[i];

      pTB[i] = pT_ppg044[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg044[i];
      eyieldB[i] = eyield_ppg044[i];

      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
    } // end of for loop to calculate ratio
  TGraphErrors *tge2_posmm = new TGraphErrors(12,pT,ratio,epT,eratio);
  tge2_posmm->SetMarkerColor(kBlue);
  tge2_posmm->SetMarkerStyle(20);

  // --- negmm --- //

  for(int i=0; i<12; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      pTA[i] = pTR_negmm[i];
      epTA[i] = 0;
      yieldA[i] = yieldR_negmm[i];
      eyieldA[i] = eyieldR_negmm[i];

      pTB[i] = pT_ppg044[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg044[i];
      eyieldB[i] = eyield_ppg044[i];

      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	}
    } // end of for loop to calculate ratio
  TGraphErrors *tge2_negmm = new TGraphErrors(12,pT,ratio,epT,eratio);
  tge2_negmm->SetMarkerColor(kRed);
  tge2_negmm->SetMarkerStyle(21);

  // ---





  // ---

  TMultiGraph *tmg_good_pi0 = new TMultiGraph();
  tmg_good_pi0->Add(tge2_pospp);
  tmg_good_pi0->Add(tge2_negmm);
  tmg_good_pi0->Draw("ap");
  tmg_good_pi0->SetMaximum(2.0);
  tmg_good_pi0->SetMinimum(0.0);
  tmg_good_pi0->GetXaxis()->SetLimits(0.0,6.0);
  tmg_good_pi0->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_good_pi0->GetXaxis()->CenterTitle();
  tmg_good_pi0->GetYaxis()->SetTitle("Ratio");
  tmg_good_pi0->GetYaxis()->CenterTitle();

  TPaveText *pave_good_pi0 = new TPaveText(1.01, 0.1, 2.5, 0.3, "br");
  pave_good_pi0->SetFillColor(10);
  pave_good_pi0->SetBorderSize(0);
  TText *text_good_pi0 = pave_good_pi0->AddText(bigcentstring);
  pave_good_pi0->Draw();

  TPaveText *pave2_good_pi0 = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  pave2_good_pi0->SetFillColor(10);
  pave2_good_pi0->SetBorderSize(0);
  TText *text2_good_pi0 = pave2_good_pi0->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_good_pi0->Draw();

  TLegend *leg_good_pi0 = new TLegend(0.68,0.68,0.88,0.88);
  leg_good_pi0->SetFillColor(kWhite);
  leg_good_pi0->SetBorderSize(0);
  leg_good_pi0->AddEntry(tge2_pospp,"#pi^{+}, ++ field","p");
  leg_good_pi0->AddEntry(tge2_negmm,"#pi^{-}, -- field","p");
  leg_good_pi0->Draw();

  char gifname_good_pi0[100];
  sprintf(gifname_good_pi0,"RatioFigures/published_pi0_%s_goodchfi_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_good_pi0[100];
  sprintf(epsname_good_pi0,"RatioFigures/published_pi0_%s_goodchfi_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_good_pi0);
  //c1->Print(epsname_good_pi0);



  TMultiGraph *tmg_bad_pi0 = new TMultiGraph();
  tmg_bad_pi0->Add(tge2_posmm);
  tmg_bad_pi0->Add(tge2_negpp);
  tmg_bad_pi0->Draw("ap");
  tmg_bad_pi0->SetMaximum(2.0);
  tmg_bad_pi0->SetMinimum(0.0);
  tmg_bad_pi0->GetXaxis()->SetLimits(0.0,6.0);
  tmg_bad_pi0->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_bad_pi0->GetXaxis()->CenterTitle();
  tmg_bad_pi0->GetYaxis()->SetTitle("Ratio");
  tmg_bad_pi0->GetYaxis()->CenterTitle();

  TPaveText *pave_bad_pi0 = new TPaveText(1.01, 0.1, 2.5, 0.3, "br");
  pave_bad_pi0->SetFillColor(10);
  pave_bad_pi0->SetBorderSize(0);
  TText *text_bad_pi0 = pave_bad_pi0->AddText(bigcentstring);
  pave_bad_pi0->Draw();

  TPaveText *pave2_bad_pi0 = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  pave2_bad_pi0->SetFillColor(10);
  pave2_bad_pi0->SetBorderSize(0);
  TText *text2_bad_pi0 = pave2_bad_pi0->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_bad_pi0->Draw();

  TLegend *leg_bad_pi0 = new TLegend(0.68,0.68,0.88,0.88);
  leg_bad_pi0->SetFillColor(kWhite);
  leg_bad_pi0->SetBorderSize(0);
  leg_bad_pi0->AddEntry(tge2_posmm,"#pi^{+}, -- field","p");
  leg_bad_pi0->AddEntry(tge2_negpp,"#pi^{-}, ++ field","p");
  leg_bad_pi0->Draw();

  char gifname_bad_pi0[100];
  sprintf(gifname_bad_pi0,"RatioFigures/published_pi0_%s_badchfi_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_bad_pi0[100];
  sprintf(epsname_bad_pi0,"RatioFigures/published_pi0_%s_badchfi_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_bad_pi0);
  //c1->Print(epsname_bad_pi0);



  // ---

  TMultiGraph *tmg_pp_pi0 = new TMultiGraph();
  tmg_pp_pi0->Add(tge2_pospp);
  tmg_pp_pi0->Add(tge2_negpp);
  tmg_pp_pi0->Draw("ap");
  tmg_pp_pi0->SetMaximum(2.0);
  tmg_pp_pi0->SetMinimum(0.0);
  tmg_pp_pi0->GetXaxis()->SetLimits(0.0,6.0);
  tmg_pp_pi0->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pp_pi0->GetXaxis()->CenterTitle();
  tmg_pp_pi0->GetYaxis()->SetTitle("Ratio");
  tmg_pp_pi0->GetYaxis()->CenterTitle();

  TPaveText *pave_pp_pi0 = new TPaveText(1.01, 0.1, 2.5, 0.3, "br");
  pave_pp_pi0->SetFillColor(10);
  pave_pp_pi0->SetBorderSize(0);
  TText *text_pp_pi0 = pave_pp_pi0->AddText(bigcentstring);
  pave_pp_pi0->Draw();

  TPaveText *pave2_pp_pi0 = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  pave2_pp_pi0->SetFillColor(10);
  pave2_pp_pi0->SetBorderSize(0);
  TText *text2_pp_pi0 = pave2_pp_pi0->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_pp_pi0->Draw();

  TLegend *leg_pp_pi0 = new TLegend(0.68,0.68,0.88,0.88);
  leg_pp_pi0->SetFillColor(kWhite);
  leg_pp_pi0->SetBorderSize(0);
  leg_pp_pi0->AddEntry(tge2_pospp,"#pi^{+}, ++ field","p");
  leg_pp_pi0->AddEntry(tge2_negmm,"#pi^{-}, ++ field","p");
  leg_pp_pi0->Draw();

  char gifname_pp_pi0[100];
  sprintf(gifname_pp_pi0,"RatioFigures/published_pi0_%s_pp_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_pp_pi0[100];
  sprintf(epsname_pp_pi0,"RatioFigures/published_pi0_%s_pp_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_pp_pi0);
  //c1->Print(epsname_pp_pi0);



  TMultiGraph *tmg_mm_pi0 = new TMultiGraph();
  tmg_mm_pi0->Add(tge2_posmm);
  tmg_mm_pi0->Add(tge2_negmm);
  tmg_mm_pi0->Draw("ap");
  tmg_mm_pi0->SetMaximum(2.0);
  tmg_mm_pi0->SetMinimum(0.0);
  tmg_mm_pi0->GetXaxis()->SetLimits(0.0,6.0);
  tmg_mm_pi0->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_mm_pi0->GetXaxis()->CenterTitle();
  tmg_mm_pi0->GetYaxis()->SetTitle("Ratio");
  tmg_mm_pi0->GetYaxis()->CenterTitle();

  TPaveText *pave_mm_pi0 = new TPaveText(1.01, 0.1, 2.5, 0.3, "br");
  pave_mm_pi0->SetFillColor(10);
  pave_mm_pi0->SetBorderSize(0);
  TText *text_mm_pi0 = pave_mm_pi0->AddText(bigcentstring);
  pave_mm_pi0->Draw();

  TPaveText *pave2_mm_pi0 = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  pave2_mm_pi0->SetFillColor(10);
  pave2_mm_pi0->SetBorderSize(0);
  TText *text2_mm_pi0 = pave2_mm_pi0->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_mm_pi0->Draw();

  TLegend *leg_mm_pi0 = new TLegend(0.68,0.68,0.88,0.88);
  leg_mm_pi0->SetFillColor(kWhite);
  leg_mm_pi0->SetBorderSize(0);
  leg_mm_pi0->AddEntry(tge2_posmm,"#pi^{+}, -- field","p");
  leg_mm_pi0->AddEntry(tge2_negmm,"#pi^{-}, -- field","p");
  leg_mm_pi0->Draw();

  char gifname_mm_pi0[100];
  sprintf(gifname_mm_pi0,"RatioFigures/published_pi0_%s_mm_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_mm_pi0[100];
  sprintf(epsname_mm_pi0,"RatioFigures/published_pi0_%s_mm_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_mm_pi0);
  //c1->Print(epsname_mm_pi0);






  TMultiGraph *tmg_pos_pi0 = new TMultiGraph();
  tmg_pos_pi0->Add(tge2_pospp);
  tmg_pos_pi0->Add(tge2_posmm);
  tmg_pos_pi0->Draw("ap");
  tmg_pos_pi0->SetMaximum(2.0);
  tmg_pos_pi0->SetMinimum(0.0);
  tmg_pos_pi0->GetXaxis()->SetLimits(0.0,6.0);
  tmg_pos_pi0->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pos_pi0->GetXaxis()->CenterTitle();
  tmg_pos_pi0->GetYaxis()->SetTitle("Ratio");
  tmg_pos_pi0->GetYaxis()->CenterTitle();

  TPaveText *pave_pos_pi0 = new TPaveText(1.01, 0.1, 2.5, 0.3, "br");
  pave_pos_pi0->SetFillColor(10);
  pave_pos_pi0->SetBorderSize(0);
  TText *text_pos_pi0 = pave_pos_pi0->AddText(bigcentstring);
  pave_pos_pi0->Draw();

  TPaveText *pave2_pos_pi0 = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  pave2_pos_pi0->SetFillColor(10);
  pave2_pos_pi0->SetBorderSize(0);
  TText *text2_pos_pi0 = pave2_pos_pi0->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_pos_pi0->Draw();

  TLegend *leg_pos_pi0 = new TLegend(0.68,0.68,0.88,0.88);
  leg_pos_pi0->SetFillColor(kWhite);
  leg_pos_pi0->SetBorderSize(0);
  leg_pos_pi0->AddEntry(tge2_posmm,"#pi^{+}, ++ field","p");
  leg_pos_pi0->AddEntry(tge2_negmm,"#pi^{+}, -- field","p");
  leg_pos_pi0->Draw();

  char gifname_pos_pi0[100];
  sprintf(gifname_pos_pi0,"RatioFigures/published_pi0_%s_pos_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_pos_pi0[100];
  sprintf(epsname_pos_pi0,"RatioFigures/published_pi0_%s_pos_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_pos_pi0);
  //c1->Print(epsname_pos_pi0);



  TMultiGraph *tmg_neg_pi0 = new TMultiGraph();
  tmg_neg_pi0->Add(tge2_negpp);
  tmg_neg_pi0->Add(tge2_negmm);
  tmg_neg_pi0->Draw("ap");
  tmg_neg_pi0->SetMaximum(2.0);
  tmg_neg_pi0->SetMinimum(0.0);
  tmg_neg_pi0->GetXaxis()->SetLimits(0.0,6.0);
  tmg_neg_pi0->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_neg_pi0->GetXaxis()->CenterTitle();
  tmg_neg_pi0->GetYaxis()->SetTitle("Ratio");
  tmg_neg_pi0->GetYaxis()->CenterTitle();

  TPaveText *pave_neg_pi0 = new TPaveText(1.01, 0.1, 2.5, 0.3, "br");
  pave_neg_pi0->SetFillColor(10);
  pave_neg_pi0->SetBorderSize(0);
  TText *text_neg_pi0 = pave_neg_pi0->AddText(bigcentstring);
  pave_neg_pi0->Draw();

  TPaveText *pave2_neg_pi0 = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  pave2_neg_pi0->SetFillColor(10);
  pave2_neg_pi0->SetBorderSize(0);
  TText *text2_neg_pi0 = pave2_neg_pi0->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_neg_pi0->Draw();

  TLegend *leg_neg_pi0 = new TLegend(0.68,0.68,0.88,0.88);
  leg_neg_pi0->SetFillColor(kWhite);
  leg_neg_pi0->SetBorderSize(0);
  leg_neg_pi0->AddEntry(tge2_negmm,"#pi^{-}, ++ field","p");
  leg_neg_pi0->AddEntry(tge2_negmm,"#pi^{-}, -- field","p");
  leg_neg_pi0->Draw();

  char gifname_neg_pi0[100];
  sprintf(gifname_neg_pi0,"RatioFigures/published_pi0_%s_neg_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_neg_pi0[100];
  sprintf(epsname_neg_pi0,"RatioFigures/published_pi0_%s_neg_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  //c1->Print(gifname_neg_pi0);
  //c1->Print(epsname_neg_pi0);










  c1->Clear();

  // ---------------------------- //
  // --- now do combined part --- //
  // ---------------------------- //

  // ------------- //
  // --- poscb --- //
  // ------------- //

  for(int i=0; i<36; i++)
    {
      // A
      j=i;
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<15)
	{
	  j=i;
	  pTA[j] = pT_poscb[i];
	  epTA[j] = 0;
	  yieldA[j] = yield_poscb[i];
	  eyieldA[j] = eyield_poscb[i];
	}
      if(i>14&&i<27)
	{
	  if(i%2!=1) continue;
	  j=i/2+8;
	  pTA[j] = (pT_poscb[i]+pT_poscb[i+1])/2.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_poscb[i]+yield_poscb[i+1])/2.0;
	  eyieldA[j] = sqrt(eyield_poscb[i]**2+eyield_poscb[i+1]**2)/2.0;
	}
      if(i==27)
	{
	  j=21;
	  pTA[j] = (pT_poscb[i]+pT_poscb[i+1]+pT_poscb[i+2]+pT_poscb[i+3])/4.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_poscb[i]+yield_poscb[i+1]+yield_poscb[i+2]+yield_poscb[i+3])/4.0;
	  eyieldA[j] = sqrt(eyield_poscb[i]**2+eyield_poscb[i+1]**2+eyield_poscb[i+2]**2+eyield_poscb[i+3]**2)/4.0;
	}
      if(i>27)
	{
	  if(i%6!=1) continue;
	  j=i/6+17;
	  pTA[j] = (pT_poscb[i]+pT_poscb[i+1]+pT_poscb[i+2]+
		    pT_poscb[i+3]+pT_poscb[i+4]+pT_poscb[i+5])/6.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_poscb[i]+yield_poscb[i+1]+yield_poscb[i+2]+
		       yield_poscb[i+3]+yield_poscb[i+4]+yield_poscb[i+5])/6.0;
	  eyieldA[j] = sqrt(eyield_poscb[i]**2+eyield_poscb[i+1]**2+eyield_poscb[i+2]**2+
			    eyield_poscb[i+3]**2+eyield_poscb[i+4]**2+eyield_poscb[i+5]**2)/6.0;
	}

    } // end of for loop for rebinning

  for(int i=0; i<23; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      pTB[i] = pTpos_ppg030[i];
      epTB[i] = 0;
      yieldB[i] = yieldpos_ppg030[i];
      eyieldB[i] = eyieldpos_ppg030[i];

      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	  esysratio[i] = 0.1*ratio[i]; //NEW!  and temp, to be improved later
	}
      else
	{
	  pT[i] = pTA[i];
	  epT[i] = 0;
	  ratio[i] = -9;
	  eratio[i] = 0;
	  esysratio[i] = 0;
	}
    } // end of for loop to calculate ratio

  for(int i=0; i<5; i++)
    {
      ratio[i] = -9; // NEW
    }


  TGraphErrors *tge_poscb = new TGraphErrors(number+offset,pT,ratio,epT,eratio);
  TGraphErrors *tge_poscbSYS = new TGraphErrors(number+offset,pT,ratio,epT,esysratio);
  tge_poscbSYS->SetMarkerStyle(1);
  tge_poscbSYS->SetMarkerColor(kGray);
  tge_poscbSYS->SetLineWidth(15);
  tge_poscbSYS->SetLineColor(kGray);
  tge_poscb->SetMarkerColor(kBlack);
  tge_poscb->SetMarkerStyle(20);

  c1->Clear();//new
  TMultiGraph *tmgS_poscb = new TMultiGraph();
  tmgS_poscb->Add(tge_poscbSYS);
  tmgS_poscb->Add(tge_poscb);
  tmgS_poscb->Draw("apz");
  tmgS_poscb->SetMaximum(2.0);
  tmgS_poscb->SetMinimum(0.0);
  if(pid==2||pid==3) tmgS_poscb->GetXaxis()->SetLimits(0.0,3.0);
  //if(pid<=1||pid>=4) tmgS_poscb->GetXaxis()->SetLimits(0.0,5.0);
  if(pid<=1) tmgS_poscb->GetXaxis()->SetLimits(0.0,6.0);
  if(pid>=4) tmgS_poscb->GetXaxis()->SetLimits(0.0,5.0);
  tmgS_poscb->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmgS_poscb->GetXaxis()->CenterTitle();
  tmgS_poscb->GetYaxis()->SetTitle("Ratio");
  tmgS_poscb->GetYaxis()->CenterTitle();

  char gifname_poscb[100];
  sprintf(gifname_poscb,"RatioFigures/single_published_%s_pos_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_poscb[100];
  sprintf(epsname_poscb,"RatioFigures/single_published_%s_pos_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  if(pid>=2)
    {
      c1->Print(gifname_poscb);
      c1->Print(epsname_poscb);
    }

  // ---

  // ------------- //
  // --- negcb --- //
  // ------------- //

  for(int i=0; i<36; i++)
    {
      // A
      j=i;
      pTA[i] = -9;
      epTA[i] = 0;
      yieldA[i] = -9;
      eyieldA[i] = 0;
      if(i<15)
	{
	  j=i;
	  pTA[j] = pT_negcb[i];
	  epTA[j] = 0;
	  yieldA[j] = yield_negcb[i];
	  eyieldA[j] = eyield_negcb[i];
	}
      if(i>14&&i<27)
	{
	  if(i%2!=1) continue;
	  j=i/2+8;
	  pTA[j] = (pT_negcb[i]+pT_negcb[i+1])/2.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_negcb[i]+yield_negcb[i+1])/2.0;
	  eyieldA[j] = sqrt(eyield_negcb[i]**2+eyield_negcb[i+1]**2)/2.0;
	}
      if(i==27)
	{
	  j=21;
	  pTA[j] = (pT_negcb[i]+pT_negcb[i+1]+pT_negcb[i+2]+pT_negcb[i+3])/4.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_negcb[i]+yield_negcb[i+1]+yield_negcb[i+2]+yield_negcb[i+3])/4.0;
	  eyieldA[j] = sqrt(eyield_negcb[i]**2+eyield_negcb[i+1]**2+eyield_negcb[i+2]**2+eyield_negcb[i+3]**2)/4.0;
	}
      if(i>27)
	{
	  if(i%6!=1) continue;
	  j=i/6+17;
	  pTA[j] = (pT_negcb[i]+pT_negcb[i+1]+pT_negcb[i+2]+
		    pT_negcb[i+3]+pT_negcb[i+4]+pT_negcb[i+5])/6.0;
	  epTA[j] = 0;
	  yieldA[j] = (yield_negcb[i]+yield_negcb[i+1]+yield_negcb[i+2]+
		       yield_negcb[i+3]+yield_negcb[i+4]+yield_negcb[i+5])/6.0;
	  eyieldA[j] = sqrt(eyield_negcb[i]**2+eyield_negcb[i+1]**2+eyield_negcb[i+2]**2+
			    eyield_negcb[i+3]**2+eyield_negcb[i+4]**2+eyield_negcb[i+5]**2)/6.0;
	}

    } // end of for loop for rebinning

  for(int i=0; i<23; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      // this is where the typo was
      pTB[i] = pTneg_ppg030[i];
      epTB[i] = 0;
      yieldB[i] = yieldneg_ppg030[i];
      eyieldB[i] = eyieldneg_ppg030[i];

      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	  esysratio[i] = 0.1*ratio[i]; //NEW!  and temp, to be improved later
	}
      else
	{
	  pT[i] = pTA[i];
	  epT[i] = 0;
	  ratio[i] = -9;
	  eratio[i] = 0;
	  esysratio[i] = 0;
	}
    } // end of for loop to calculate ratio

  for(int i=0; i<5; i++)
    {
      ratio[i] = -9;
    }

  TGraphErrors *tge_negcb = new TGraphErrors(number+offset,pT,ratio,epT,eratio);
  TGraphErrors *tge_negcbSYS = new TGraphErrors(number+offset,pT,ratio,epT,esysratio);
  tge_negcbSYS->SetMarkerStyle(1);
  tge_negcbSYS->SetMarkerColor(kGray);
  tge_negcbSYS->SetLineWidth(15);
  tge_negcbSYS->SetLineColor(kGray);
  tge_negcb->SetMarkerColor(kBlack);
  tge_negcb->SetMarkerStyle(20);

  c1->Clear();//new
  TMultiGraph *tmgS_negcb = new TMultiGraph();
  tmgS_negcb->Add(tge_negcbSYS);
  tmgS_negcb->Add(tge_negcb);
  tmgS_negcb->Draw("apz");
  tmgS_negcb->SetMaximum(2.0);
  tmgS_negcb->SetMinimum(0.0);
  if(pid==2||pid==3) tmgS_negcb->GetXaxis()->SetLimits(0.0,3.0);
  //if(pid<=1||pid>=4) tmgS_negcb->GetXaxis()->SetLimits(0.0,5.0);
  if(pid<=1) tmgS_negcb->GetXaxis()->SetLimits(0.0,6.0);
  if(pid>=4) tmgS_negcb->GetXaxis()->SetLimits(0.0,5.0);
  tmgS_negcb->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmgS_negcb->GetXaxis()->CenterTitle();
  tmgS_negcb->GetYaxis()->SetTitle("Ratio");
  tmgS_negcb->GetYaxis()->CenterTitle();

  char gifname_negcb[100];
  sprintf(gifname_negcb,"RatioFigures/single_published_%s_neg_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_negcb[100];
  sprintf(epsname_negcb,"RatioFigures/single_published_%s_neg_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  if(pid>=2)
    {
      c1->Print(gifname_negcb);
      c1->Print(epsname_negcb);
    }






  c1->Clear();

  // --- poscb --- //

  for(int i=0; i<12; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      pTA[i] = pTR_poscb[i];
      epTA[i] = 0;
      yieldA[i] = yieldR_poscb[i];
      eyieldA[i] = eyieldR_poscb[i];

      pTB[i] = pT_ppg044[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg044[i];
      eyieldB[i] = eyield_ppg044[i];

      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	  esysratio[i] = 0.1*ratio[i]; //NEW!  and temp, to be improved later
	}
    } // end of for loop to calculate ratio
  for(int i=10; i<12; i++)
    {
      ratio[i] = -9; // NEWER
    }
  TGraphErrors *tge2_poscb = new TGraphErrors(12,pT,ratio,epT,eratio);
  tge2_poscb->SetMarkerColor(kBlue);
  tge2_poscb->SetMarkerStyle(20);
  TGraphErrors *tge2_poscbSYS = new TGraphErrors(12,pT,ratio,epT,esysratio);
  tge2_poscbSYS->SetMarkerColor(kBlue);
  tge2_poscbSYS->SetMarkerStyle(1);
  tge2_poscbSYS->SetLineColor(kBlue-10);
  tge2_poscbSYS->SetLineWidth(15);

  // --- negcb --- //

  for(int i=0; i<12; i++)
    {
      pT[i] = pTA[i];
      epT[i] = 0;
      ratio[i] = -9;
      eratio[i] = 0;

      pTA[i] = pTR_negcb[i];
      epTA[i] = 0;
      yieldA[i] = yieldR_negcb[i];
      eyieldA[i] = eyieldR_negcb[i];

      pTB[i] = pT_ppg044[i];
      epTB[i] = 0;
      yieldB[i] = yield_ppg044[i];
      eyieldB[i] = eyield_ppg044[i];

      // now do ratio
      if(yieldA[i]>0&&yieldB[i]>0)
	{
	  pT[i] = (pTA[i]+pTB[i])/2.0;
	  epT[i] = 0;
	  ratio[i] = yieldA[i]/yieldB[i];
	  eratio[i] = ratio[i]*sqrt((eyieldA[i]/yieldA[i])**2+(eyieldB[i]/yieldB[i])**2);
	  esysratio[i] = 0.1*ratio[i]; //NEW!  and temp, to be improved later
	}
    } // end of for loop to calculate ratio
  for(int i=10; i<12; i++)
    {
      ratio[i] = -9; // NEWER
    }
  TGraphErrors *tge2_negcb = new TGraphErrors(12,pT,ratio,epT,eratio);
  tge2_negcb->SetMarkerColor(kRed);
  tge2_negcb->SetMarkerStyle(21);
  TGraphErrors *tge2_negcbSYS = new TGraphErrors(12,pT,ratio,epT,esysratio);
  tge2_negcbSYS->SetMarkerColor(kRed);
  tge2_negcbSYS->SetMarkerStyle(1);
  tge2_negcbSYS->SetLineColor(kRed-10);
  tge2_negcbSYS->SetLineWidth(15);

  // ---


  tge_poscb->SetMarkerColor(kBlack);
  tge_poscb->SetMarkerStyle(20);
  tge2_poscb->SetMarkerColor(kRed);
  tge2_poscb->SetMarkerStyle(21);
  tge2_poscbSYS->SetLineColor(kRed-10);


  c1->Clear();//new
  TMultiGraph *tmg_pos_cb = new TMultiGraph();
  tmg_pos_cb->Add(tge_poscbSYS);
  tmg_pos_cb->Add(tge2_poscbSYS);
  tmg_pos_cb->Add(tge_poscb);
  tmg_pos_cb->Add(tge2_poscb);
  tmg_pos_cb->Draw("apz");
  tmg_pos_cb->SetMaximum(2.0);
  tmg_pos_cb->SetMinimum(0.0);
  tmg_pos_cb->GetXaxis()->SetLimits(0.0,6.0);
  //tmg_pos_cb->GetXaxis()->SetLimits(0.0,5.0);
  tmg_pos_cb->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pos_cb->GetXaxis()->CenterTitle();
  tmg_pos_cb->GetYaxis()->SetTitle("Ratio");
  tmg_pos_cb->GetYaxis()->CenterTitle();
  
  TPaveText *pave_pos_cb = new TPaveText(1.01, 0.1, 2.5, 0.3, "br");
  //TPaveText *pave_pos_cb = new TPaveText(1.01, 0.1, 1.9, 0.3, "br"); // for 5.0
  pave_pos_cb->SetFillColor(10);
  pave_pos_cb->SetBorderSize(0);
  TText *text_pos_cb = pave_pos_cb->AddText(bigcentstring);
  pave_pos_cb->Draw();
  
  TPaveText *pave2_pos_cb = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  //TPaveText *pave2_pos_cb = new TPaveText(0.5, 2.04, 4.5, 2.2, "br"); // for 5.0
  pave2_pos_cb->SetFillColor(10);
  pave2_pos_cb->SetBorderSize(0);
  TText *text2_pos_cb = pave2_pos_cb->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_pos_cb->Draw();
  
  //TLegend *leg_pos_cb = new TLegend(0.68,0.18,0.88,0.38);
  //TLegend *leg_pos_cb = new TLegend(0.18,0.68,0.38,0.88);
  TLegend *leg_pos_cb = new TLegend(0.12,0.68,0.52,0.88);
  leg_pos_cb->SetFillColor(kWhite);
  leg_pos_cb->SetBorderSize(0);
  leg_pos_cb->AddEntry(tge_poscb,"#pi^{+}, Run8/ppg030","p");
  leg_pos_cb->AddEntry(tge2_poscb,"#pi^{+}, Run8/ppg044","p");
  leg_pos_cb->Draw();
  
  char gifname_pos_cb[100];
  sprintf(gifname_pos_cb,"RatioFigures/single_published_%s_pos_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_pos_cb[100];
  sprintf(epsname_pos_cb,"RatioFigures/single_published_%s_pos_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  if(pid<=1)
    {  
      c1->Print(gifname_pos_cb);
      c1->Print(epsname_pos_cb);
    }
  
  // ---  

  
  tge_negcb->SetMarkerColor(kBlack);
  tge_negcb->SetMarkerStyle(20);
  tge2_negcb->SetMarkerColor(kRed);
  tge2_negcb->SetMarkerStyle(21);
  
  c1->Clear();//new
  TMultiGraph *tmg_neg_cb = new TMultiGraph();
  tmg_neg_cb->Add(tge_negcbSYS);
  tmg_neg_cb->Add(tge2_negcbSYS);
  tmg_neg_cb->Add(tge_negcb);
  tmg_neg_cb->Add(tge2_negcb);
  tmg_neg_cb->Draw("apz");
  tmg_neg_cb->SetMaximum(2.0);
  tmg_neg_cb->SetMinimum(0.0);
  tmg_neg_cb->GetXaxis()->SetLimits(0.0,6.0);
  //tmg_neg_cb->GetXaxis()->SetLimits(0.0,5.0);
  tmg_neg_cb->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_neg_cb->GetXaxis()->CenterTitle();
  tmg_neg_cb->GetYaxis()->SetTitle("Ratio");
  tmg_neg_cb->GetYaxis()->CenterTitle();
  
  TPaveText *pave_neg_cb = new TPaveText(1.01, 0.1, 2.5, 0.3, "br");
  //TPaveText *pave_neg_cb = new TPaveText(1.01, 0.1, 1.9, 0.3, "br"); // 5.0
  pave_neg_cb->SetFillColor(10);
  pave_neg_cb->SetBorderSize(0);
  TText *text_neg_cb = pave_neg_cb->AddText(bigcentstring);
  pave_neg_cb->Draw();
  
  TPaveText *pave2_neg_cb = new TPaveText(0.5, 2.04, 5.5, 2.2, "br");
  //TPaveText *pave2_neg_cb = new TPaveText(0.5, 2.04, 4.5, 2.2, "br"); // 5.0
  pave2_neg_cb->SetFillColor(10);
  pave2_neg_cb->SetBorderSize(0);
  TText *text2_neg_cb = pave2_neg_cb->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  pave2_neg_cb->Draw();
  
  //TLegend *leg_neg_cb = new TLegend(0.68,0.18,0.88,0.38);
  //TLegend *leg_neg_cb = new TLegend(0.18,0.68,0.38,0.88);
  TLegend *leg_neg_cb = new TLegend(0.12,0.68,0.52,0.88);
  leg_neg_cb->SetFillColor(kWhite);
  leg_neg_cb->SetBorderSize(0);
  leg_neg_cb->AddEntry(tge_negcb,"#pi^{-}, Run8/ppg030","p");
  leg_neg_cb->AddEntry(tge2_negcb,"#pi^{-}, Run8/ppg044","p");
  leg_neg_cb->Draw();
  
  char gifname_neg_cb[100];
  sprintf(gifname_neg_cb,"RatioFigures/single_published_%s_neg_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname_neg_cb[100];
  sprintf(epsname_neg_cb,"RatioFigures/single_published_%s_neg_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  if(pid<=1)
    {  
      c1->Print(gifname_neg_cb);
      c1->Print(epsname_neg_cb);
    }
  
  
  
  
  
  
}

void pubratios()
{

  cout<<"hello!  unfortunately, this is nowhere near as much fun "<<endl
      <<"as the name of the macro would suggest but it will make some"<<endl
      <<"nice plots of the ratios of the Run8 spectra to the"<<endl
      <<"published Run3 spectra for you."<<endl;

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


  // for(int icent=0; icent<4; icent++)
  //   {
  //     doit(0,0,icent);
  //     doit(0,2,icent);
  //     doit(0,4,icent);
  //   }

  doit(0,0,0);
  doit(0,2,0);
  doit(0,4,0);

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
  sprintf(finname,"ppg030/pi0_%s.dat",centstring);
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
  // --- perfect for the pi0

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





  float pT[36], epT[36], ratio[36], eratio[36];
  float pTA[36], epTA[36], yieldA[36], eyieldA[36];
  float pTB[36], epTB[36], yieldB[36], eyieldB[36];

  int j;

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

      //cout<<pTA[i]<<"\t"<<yieldA[i]<<"\t"<<eyieldA[i]<<endl;
      //cout<<pTA[i]<<"\t"<<yieldA[i]<<"\t"<<eyieldA[i]<<endl;

    } // end of for loop for rebinning

  //cout<<"quitting prematurely! bye!"<<endl;
  //exit(0);


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
      //cout<<i<<"\t"<<pTA[i]<<"\t"<<pTB[i]<<endl;

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





  TGraphErrors *tge_pospp = new TGraphErrors(32,pT,ratio,epT,eratio);
  tge_pospp->SetMarkerColor(kBlack);
  tge_pospp->SetMarkerStyle(20);

  TMultiGraph *tmg = new TMultiGraph();
  tmg_pospp->Add(tge_pospp);
  tmg->Draw("ap");
  tmg->SetMaximum(2.0);
  tmg->SetMinimum(0.0);
  tmg->GetXaxis()->SetLimits(0.0,3.6);
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetXaxis()->CenterTitle();
  tmg->GetYaxis()->SetTitle("Ratio");
  tmg->GetYaxis()->CenterTitle();

  TPaveText *tptP = new TPaveText(0.5, 0.1, 1.5, 0.3, "br");
  tptP->SetFillColor(10);
  tptP->SetBorderSize(0);
  TText *textP = tptP->AddText(bigcentstring);
  tptP->Draw();

  TPaveText *tptP2 = new TPaveText(0.25, 2.04, 2.75, 2.2, "br");
  tptP2->SetFillColor(10);
  tptP2->SetBorderSize(0);
  TText *textP2 = tptP2->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tptP2->Draw();

  TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  if(pid==0||pid==1)
    {
      leg->AddEntry(tge_pospp,"#pi^{-}, -- field","p");
    }
  if(pid==2||pid==3)
    {
      leg->AddEntry(tge_pospp,"K^{-}, -- field","p");
    }
  if(pid==4||pid==5)
    {
      leg->AddEntry(tge_pospp,"#bar{p}, -- field","p");
    }
  leg->Draw();

  char gifname[100];
  sprintf(gifname,"RatioFigures/published_%s_good_%d_dis_cent%s.gif",sectorstring,pid,centstring);
  char epsname[100];
  sprintf(epsname,"RatioFigures/published_%s_good_%d_dis_cent%s.eps",sectorstring,pid,centstring);

  c1->Print(gifname);
  c1->Print(epsname);



}

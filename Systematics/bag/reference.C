void reference()
{

  //doit(0,0,0);
  //doit(0,2,0);

  //exit(1);

  for(int ipid=0; ipid<3; ipid++)
    {
      doit(ipid,0,0);
      //cout<<"doit("<<isec<<","<<ipid<<","<<icent<<");"<<endl;
    }


  // for(int iswitch=0; iswitch<2; iswitch++)
  //   {
  //     for(int itype=0; itype<7; itype++)
  // 	{
  // 	  for(int ipid=0; ipid<3; ipid++)
  // 	    {
  // 	      doit(ipid,itype,iswitch);
  // 	      //cout<<"doit("<<isec<<","<<ipid<<","<<icent<<");"<<endl;
  // 	    }
  // 	}
  //   }




  cout<<"all done!  i hope you have a great day!"<<endl;

}

void doit(int ipid=0, int itype=0, int iswitch=0)
{




  TFile *f_real_pp = TFile::Open("RealFiles/outnew_plusplus.root");
  TFile *f_simpion_pp = TFile::Open("SimFiles/pion/simsum_pp.root");
  TFile *f_simkaon_pp = TFile::Open("SimFiles/kaon/simsum_pp.root");
  TFile *f_simproton_pp = TFile::Open("SimFiles/proton/simsum_pp.root");

  TFile *f_real_mm = TFile::Open("RealFiles/outnew_minusminus.root");
  TFile *f_simpion_mm = TFile::Open("SimFiles/pion/simsum_mm.root");
  TFile *f_simkaon_mm = TFile::Open("SimFiles/kaon/simsum_mm.root");
  TFile *f_simproton_mm = TFile::Open("SimFiles/proton/simsum_mm.root");

  // char sectorstring[10];
  // sprintf(sectorstring,"tofw"); // "default"
  // if(sector==0) sprintf(sectorstring,"tofw");
  // if(sector==1) sprintf(sectorstring,"tofw_w1");
  // if(sector==2) sprintf(sectorstring,"tofw_w2");

  char pidstring[5];
  sprintf(pidstring,"pion"); // "default"
  if(ipid==0) sprintf(pidstring,"pion");
  if(ipid==1) sprintf(pidstring,"kaon");
  if(ipid==2) sprintf(pidstring,"prot");

  int pidnumber = 0; // defaul
  if(ipid==0) pidnumber = 1;
  if(ipid==1) pidnumber = 3;
  if(ipid==2) pidnumber = 5;

  // char typestring[5];
  // sprintf(typestring,"tfwm"); // "default"
  // if(itype==0) sprintf(typestring,"tfwm");
  // if(itype==1) sprintf(typestring,"pc3m");
  // if(itype==2) sprintf(typestring,"pc3f");
  // if(itype==3) sprintf(typestring,"pc1f");
  // if(itype==4) sprintf(typestring,"dcfc");
  // if(itype==5) sprintf(typestring,"dzed");
  // if(itype==6) sprintf(typestring,"spid");

  // char switchstring[2];
  // sprintf(switchstring,"A"); // "default"
  // if(iswitch==0) sprintf(switchstring,"A");
  // if(iswitch==1) sprintf(switchstring,"B");




  char name_real_tofw_pos_pp[50];
  char name_sim_tofw_pos_pp[50];
  char name_real_tofw_neg_pp[50];
  char name_sim_tofw_neg_pp[50];

  char name_real_tofw_pos_mm[50];
  char name_sim_tofw_pos_mm[50];
  char name_real_tofw_neg_mm[50];
  char name_sim_tofw_neg_mm[50];

  sprintf(name_real_tofw_pos_pp,"ptpid_tofw_pos_%d_dis",pidnumber);
  sprintf(name_sim_tofw_pos_pp,"ptpid_tofw_pos_%d_dis",pidnumber);
  sprintf(name_real_tofw_neg_pp,"ptpid_tofw_neg_%d_dis",pidnumber);
  sprintf(name_sim_tofw_neg_pp,"ptpid_tofw_neg_%d_dis",pidnumber);

  sprintf(name_real_tofw_pos_mm,"ptpid_tofw_pos_%d_dis",pidnumber);
  sprintf(name_sim_tofw_pos_mm,"ptpid_tofw_pos_%d_dis",pidnumber);
  sprintf(name_real_tofw_neg_mm,"ptpid_tofw_neg_%d_dis",pidnumber);
  sprintf(name_sim_tofw_neg_mm,"ptpid_tofw_neg_%d_dis",pidnumber);

  TH1F *h_real_tofw_pos_pp = f_real_pp->Get(name_real_tofw_pos_pp);
  TH1F *h_real_tofw_neg_pp = f_real_pp->Get(name_real_tofw_neg_pp);
  TH1F *h_real_tofw_pos_mm = f_real_mm->Get(name_real_tofw_pos_mm);
  TH1F *h_real_tofw_neg_mm = f_real_mm->Get(name_real_tofw_neg_mm);

  if(ipid==0)
    {
      TH1F *h_sim_tofw_pos_pp = f_simpion_pp->Get(name_sim_tofw_pos_pp);
      TH1F *h_sim_tofw_neg_pp = f_simpion_pp->Get(name_sim_tofw_neg_pp);
      TH1F *h_sim_tofw_pos_mm = f_simpion_mm->Get(name_sim_tofw_pos_mm);
      TH1F *h_sim_tofw_neg_mm = f_simpion_mm->Get(name_sim_tofw_neg_mm);
    }
  else if(ipid==1)
    {
      TH1F *h_sim_tofw_pos_pp = f_simkaon_pp->Get(name_sim_tofw_pos_pp);
      TH1F *h_sim_tofw_neg_pp = f_simkaon_pp->Get(name_sim_tofw_neg_pp);
      TH1F *h_sim_tofw_pos_mm = f_simkaon_mm->Get(name_sim_tofw_pos_mm);
      TH1F *h_sim_tofw_neg_mm = f_simkaon_mm->Get(name_sim_tofw_neg_mm);
    }
  else if(ipid==2)
    {
      TH1F *h_sim_tofw_pos_pp = f_simproton_pp->Get(name_sim_tofw_pos_pp);
      TH1F *h_sim_tofw_neg_pp = f_simproton_pp->Get(name_sim_tofw_neg_pp);
      TH1F *h_sim_tofw_pos_mm = f_simproton_mm->Get(name_sim_tofw_pos_mm);
      TH1F *h_sim_tofw_neg_mm = f_simproton_mm->Get(name_sim_tofw_neg_mm);
    }
  else
    {
      cerr<<"unknown pid number, now dying a quick but horribly painful death"<<endl;
    }

  h_real_tofw_pos_pp->Sumw2();
  h_real_tofw_neg_pp->Sumw2();
  h_real_tofw_pos_mm->Sumw2();
  h_real_tofw_neg_mm->Sumw2();

  h_sim_tofw_pos_pp->Sumw2();
  h_sim_tofw_neg_pp->Sumw2();
  h_sim_tofw_pos_mm->Sumw2();
  h_sim_tofw_neg_mm->Sumw2();


  // divide Real histogram by Sim histogram
  
  h_real_tofw_pos_pp->Divide(h_sim_tofw_pos_pp);
  h_real_tofw_neg_pp->Divide(h_sim_tofw_neg_pp);
  h_real_tofw_pos_mm->Divide(h_sim_tofw_pos_mm);
  h_real_tofw_neg_mm->Divide(h_sim_tofw_neg_mm);

  // Multiplicative constants
  // Multiply by the simulation event numbes and acceptance windows
  //float simevents = 2.0e7; // 20M events for all types
  float simevents = 2.0e5; // 20M events for all types, divide by 100 to get per bin
  float window_azi = 0.5; // events are thrown in pi radians, divide by 2pi
  float window_rap = 1.2; // events are thrown in +/- 0.6 units of rapidity, divide by 1

  float simconst = simevents/window_azi/window_rap;

  //cout<<"simulation constant is "<<simconst<<endl;

  TF1 *dummy = new TF1("dummy","pol0",0,10);
  dummy->SetParameter(0,1.0);

  h_real_tofw_pos_pp->Multiply(dummy,simconst);
  h_real_tofw_neg_pp->Multiply(dummy,simconst);
  h_real_tofw_pos_mm->Multiply(dummy,simconst);
  h_real_tofw_neg_mm->Multiply(dummy,simconst);



  // Division constants
  // Divide by the number of real events, various efficiencies, and pT and cent bin-widths
  Long64_t nevents_pp = 1378825610; // 1.38 B
  Long64_t nevents_mm = 469047088; // 469 M
  float tofw_eff = 0.95; // cosmic ray studies show 95%, in situ studies show 90%
  float tofw_adc = 0.85; // in situ studies show 85%
  float dcqual = 0.9; // percentage of high-quality tracks is lower in real than in sim
  float binwidth_pT = 0.1; // 100 MeV bins
  //float binwidth_cent = 0.1; // 10% centrality bins, adjust as needed
  float binwidth_cent = 0.88; // using MB for systematics
  //if(centid==8) binwidth_cent = 0.12; // not using
  //float twopi = 6.28318531; // corrected spectra are 1/2pi 1/pT
  //int slem = 2;

  float centshift = 0.98;//MB

  //float konstant_pp = nevents_pp*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;
  //float konstant_mm = nevents_mm*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;
  //float konstant_H_pp = nevents_H_pp*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;
  //float konstant_H_mm = nevents_H_mm*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;
  float konstant_pp = nevents_pp*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent/centshift;
  float konstant_mm = nevents_mm*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent/centshift;

  TF1 *fun = new TF1("fun","pol1",0,10);
  fun->SetParameter(0,0);
  //fun->SetParameter(1,1);
  fun->SetParameter(1,6.28318531); // corrected spectra are 1/(2pipT)





  h_real_tofw_pos_pp->Divide(fun,konstant_pp);
  h_real_tofw_neg_pp->Divide(fun,konstant_pp);
  h_real_tofw_pos_mm->Divide(fun,konstant_mm);
  h_real_tofw_neg_mm->Divide(fun,konstant_mm);




  /*

  char fnameoutpospp[100];
  char fnameoutnegpp[100];
  char fnameoutposmm[100];
  char fnameoutnegmm[100];

  sprintf(fnameoutpospp,"Data/ptpid_tofw_pos_%d_dis_pp.dat",pidnumber);
  sprintf(fnameoutnegpp,"Data/ptpid_tofw_neg_%d_dis_pp.dat",pidnumber);
  sprintf(fnameoutposmm,"Data/ptpid_tofw_pos_%d_dis_mm.dat",pidnumber);
  sprintf(fnameoutnegmm,"Data/ptpid_tofw_neg_%d_dis_mm.dat",pidnumber);

  ofstream foutpospp;
  ofstream foutnegpp;
  ofstream foutposmm;
  ofstream foutnegmm;

  foutpospp.open(fnameoutpospp);
  foutnegpp.open(fnameoutnegpp);
  foutposmm.open(fnameoutposmm);
  foutnegmm.open(fnameoutnegmm);

  for(int i=0; i<100; i++)
    {
      float pT, yield, eyield;
      if(i<30)
	{
	  // pospp
	  pT = h_real_tofw_pos_pp->GetBinCenter(i+1);
	  yield = h_real_tofw_pos_pp->GetBinContent(i+1);
	  eyield = h_real_tofw_pos_pp->GetBinError(i+1);
	  foutpospp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negpp
	  pT = h_real_tofw_neg_pp->GetBinCenter(i+1);
	  yield = h_real_tofw_neg_pp->GetBinContent(i+1);
	  eyield = h_real_tofw_neg_pp->GetBinError(i+1);
	  foutnegpp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // posmm
	  pT = h_real_tofw_pos_mm->GetBinCenter(i+1);
	  yield = h_real_tofw_pos_mm->GetBinContent(i+1);
	  eyield = h_real_tofw_pos_mm->GetBinError(i+1);
	  foutposmm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negmm
	  pT = h_real_tofw_neg_mm->GetBinCenter(i+1);
	  yield = h_real_tofw_neg_mm->GetBinContent(i+1);
	  eyield = h_real_tofw_neg_mm->GetBinError(i+1);
	  foutnegmm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	}
      if(i>=30)
	{
	  // pospp
	  pT = h_real_H_tofw_pos_pp->GetBinCenter(i+1);
	  yield = h_real_H_tofw_pos_pp->GetBinContent(i+1);
	  eyield = h_real_H_tofw_pos_pp->GetBinError(i+1);
	  foutpospp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negpp
	  pT = h_real_H_tofw_neg_pp->GetBinCenter(i+1);
	  yield = h_real_H_tofw_neg_pp->GetBinContent(i+1);
	  eyield = h_real_H_tofw_neg_pp->GetBinError(i+1);
	  foutnegpp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // posmm
	  pT = h_real_H_tofw_pos_mm->GetBinCenter(i+1);
	  yield = h_real_H_tofw_pos_mm->GetBinContent(i+1);
	  eyield = h_real_H_tofw_pos_mm->GetBinError(i+1);
	  foutposmm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negmm
	  pT = h_real_H_tofw_neg_mm->GetBinCenter(i+1);
	  yield = h_real_H_tofw_neg_mm->GetBinContent(i+1);
	  eyield = h_real_H_tofw_neg_mm->GetBinError(i+1);
	  foutnegmm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	}
    }

  foutpospp.close();
  foutnegpp.close();
  foutposmm.close();
  foutnegmm.close();

  */

  // -------------------------- //
  // --- now combine fields --- //
  // -------------------------- //

  char fnameoutposcb[100];
  char fnameoutnegcb[100];

  sprintf(fnameoutposcb,"Data/ptpid_tofw_pos_%d_dis.dat",pidnumber);
  sprintf(fnameoutnegcb,"Data/ptpid_tofw_neg_%d_dis.dat",pidnumber);

  ofstream foutposcb;
  ofstream foutnegcb;

  foutposcb.open(fnameoutposcb);
  foutnegcb.open(fnameoutnegcb);

  for(int i=0; i<100; i++)
    {
      float pT, yield, eyield;
      float pT_A, yield_A, eyield_A;
      float pT_B, yield_B, eyield_B;

      // pospp
      pT_A = h_real_tofw_pos_pp->GetBinCenter(i+1);
      yield_A = h_real_tofw_pos_pp->GetBinContent(i+1);
      eyield_A = h_real_tofw_pos_pp->GetBinError(i+1);
      // posmm
      pT_B = h_real_tofw_pos_mm->GetBinCenter(i+1);
      yield_B = h_real_tofw_pos_mm->GetBinContent(i+1);
      eyield_B = h_real_tofw_pos_mm->GetBinError(i+1);

      pT = (pT_A+pT_B)/2.0;
      yield = (yield_A+yield_B)/2.0;
      eyield = sqrt(eyield_A**2+eyield_B**2)/2.0;
      foutposcb<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;



      // negpp
      pT_A = h_real_tofw_neg_pp->GetBinCenter(i+1);
      yield_A = h_real_tofw_neg_pp->GetBinContent(i+1);
      eyield_A = h_real_tofw_neg_pp->GetBinError(i+1);
      // negmm
      pT_B = h_real_tofw_neg_mm->GetBinCenter(i+1);
      yield_B = h_real_tofw_neg_mm->GetBinContent(i+1);
      eyield_B = h_real_tofw_neg_mm->GetBinError(i+1);
      
      pT = (pT_A+pT_B)/2.0;
      yield = (yield_A+yield_B)/2.0;
      eyield = sqrt(eyield_A**2+eyield_B**2)/2.0;
      foutnegcb<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
    }

  foutposcb.close();
  foutnegcb.close();

  /*

  // ---
  // ---
  // ---

  // ------------------ //
  // --- rebin by 5 --- //
  // ------------------ //

  h_real_tofw_pos_pp->Rebin(5);
  h_real_tofw_neg_pp->Rebin(5);
  h_real_tofw_pos_mm->Rebin(5);
  h_real_tofw_neg_mm->Rebin(5);

  h_real_tofw_pos_pp->Divide(dummy,5.0);
  h_real_tofw_neg_pp->Divide(dummy,5.0);
  h_real_tofw_pos_mm->Divide(dummy,5.0);
  h_real_tofw_neg_mm->Divide(dummy,5.0);

  h_real_H_tofw_pos_pp->Rebin(5);
  h_real_H_tofw_neg_pp->Rebin(5);
  h_real_H_tofw_pos_mm->Rebin(5);
  h_real_H_tofw_neg_mm->Rebin(5);

  h_real_H_tofw_pos_pp->Divide(dummy,5.0);
  h_real_H_tofw_neg_pp->Divide(dummy,5.0);
  h_real_H_tofw_pos_mm->Divide(dummy,5.0);
  h_real_H_tofw_neg_mm->Divide(dummy,5.0);

  // ------------------ //
  // ------------------ //
  // ------------------ //



  sprintf(fnameoutpospp,"Data/R5_ptpid_tofw_pos_%d_dis_pp.dat",pidnumber);
  sprintf(fnameoutnegpp,"Data/R5_ptpid_tofw_neg_%d_dis_pp.dat",pidnumber);
  sprintf(fnameoutposmm,"Data/R5_ptpid_tofw_pos_%d_dis_mm.dat",pidnumber);
  sprintf(fnameoutnegmm,"Data/R5_ptpid_tofw_neg_%d_dis_mm.dat",pidnumber);

  foutpospp.open(fnameoutpospp);
  foutnegpp.open(fnameoutnegpp);
  foutposmm.open(fnameoutposmm);
  foutnegmm.open(fnameoutnegmm);

  //for(int i=0; i<100; i++)
  for(int i=0; i<20; i++) // reduce by 5 :)
    {
      float pT, yield, eyield;
      //if(i<30)
      if(i<6)
	{
	  // pospp
	  pT = h_real_tofw_pos_pp->GetBinCenter(i+1);
	  yield = h_real_tofw_pos_pp->GetBinContent(i+1);
	  eyield = h_real_tofw_pos_pp->GetBinError(i+1);
	  foutpospp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negpp
	  pT = h_real_tofw_neg_pp->GetBinCenter(i+1);
	  yield = h_real_tofw_neg_pp->GetBinContent(i+1);
	  eyield = h_real_tofw_neg_pp->GetBinError(i+1);
	  foutnegpp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // posmm
	  pT = h_real_tofw_pos_mm->GetBinCenter(i+1);
	  yield = h_real_tofw_pos_mm->GetBinContent(i+1);
	  eyield = h_real_tofw_pos_mm->GetBinError(i+1);
	  foutposmm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negmm
	  pT = h_real_tofw_neg_mm->GetBinCenter(i+1);
	  yield = h_real_tofw_neg_mm->GetBinContent(i+1);
	  eyield = h_real_tofw_neg_mm->GetBinError(i+1);
	  foutnegmm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	}
      //if(i>=30)
      if(i>=6)
	{
	  // pospp
	  pT = h_real_H_tofw_pos_pp->GetBinCenter(i+1);
	  yield = h_real_H_tofw_pos_pp->GetBinContent(i+1);
	  eyield = h_real_H_tofw_pos_pp->GetBinError(i+1);
	  foutpospp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negpp
	  pT = h_real_H_tofw_neg_pp->GetBinCenter(i+1);
	  yield = h_real_H_tofw_neg_pp->GetBinContent(i+1);
	  eyield = h_real_H_tofw_neg_pp->GetBinError(i+1);
	  foutnegpp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // posmm
	  pT = h_real_H_tofw_pos_mm->GetBinCenter(i+1);
	  yield = h_real_H_tofw_pos_mm->GetBinContent(i+1);
	  eyield = h_real_H_tofw_pos_mm->GetBinError(i+1);
	  foutposmm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negmm
	  pT = h_real_H_tofw_neg_mm->GetBinCenter(i+1);
	  yield = h_real_H_tofw_neg_mm->GetBinContent(i+1);
	  eyield = h_real_H_tofw_neg_mm->GetBinError(i+1);
	  foutnegmm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	}
    }

  foutpospp.close();
  foutnegpp.close();
  foutposmm.close();
  foutnegmm.close();



  // -------------------------- //
  // --- now combine fields --- //
  // -------------------------- //

  sprintf(fnameoutposcb,"Data/R5_ptpid_tofw_pos_%d_dis.dat",pidnumber);
  sprintf(fnameoutnegcb,"Data/R5_ptpid_tofw_neg_%d_dis.dat",pidnumber);

  foutposcb.open(fnameoutposcb);
  foutnegcb.open(fnameoutnegcb);

  //for(int i=0; i<100; i++)
  for(int i=0; i<20; i++)
    {
      float pT, yield, eyield;
      float pT_A, yield_A, eyield_A;
      float pT_B, yield_B, eyield_B;

      //if(i<30)
      if(i<6)
	{
	  // pospp
	  pT_A = h_real_tofw_pos_pp->GetBinCenter(i+1);
	  yield_A = h_real_tofw_pos_pp->GetBinContent(i+1);
	  eyield_A = h_real_tofw_pos_pp->GetBinError(i+1);
	  // posmm
	  pT_B = h_real_tofw_pos_mm->GetBinCenter(i+1);
	  yield_B = h_real_tofw_pos_mm->GetBinContent(i+1);
	  eyield_B = h_real_tofw_pos_mm->GetBinError(i+1);
	}
      //if(i>=30)
      if(i>=6)
	{
	  // pospp
	  pT_A = h_real_H_tofw_pos_pp->GetBinCenter(i+1);
	  yield_A = h_real_H_tofw_pos_pp->GetBinContent(i+1);
	  eyield_A = h_real_H_tofw_pos_pp->GetBinError(i+1);
	  // posmm
	  pT_B = h_real_H_tofw_pos_mm->GetBinCenter(i+1);
	  yield_B = h_real_H_tofw_pos_mm->GetBinContent(i+1);
	  eyield_B = h_real_H_tofw_pos_mm->GetBinError(i+1);
	}

      pT = (pT_A+pT_B)/2.0;
      yield = (yield_A+yield_B)/2.0;
      eyield = sqrt(eyield_A**2+eyield_B**2)/2.0;
      foutposcb<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;

      //if(i<30)
      if(i<6)
	{
	  // negpp
	  pT_A = h_real_tofw_neg_pp->GetBinCenter(i+1);
	  yield_A = h_real_tofw_neg_pp->GetBinContent(i+1);
	  eyield_A = h_real_tofw_neg_pp->GetBinError(i+1);
	  // negmm
	  pT_B = h_real_tofw_neg_mm->GetBinCenter(i+1);
	  yield_B = h_real_tofw_neg_mm->GetBinContent(i+1);
	  eyield_B = h_real_tofw_neg_mm->GetBinError(i+1);
	}
      //if(i>=30)
      if(i>=6)
	{
	  // negpp
	  pT_A = h_real_H_tofw_neg_pp->GetBinCenter(i+1);
	  yield_A = h_real_H_tofw_neg_pp->GetBinContent(i+1);
	  eyield_A = h_real_H_tofw_neg_pp->GetBinError(i+1);
	  // negmm
	  pT_B = h_real_H_tofw_neg_mm->GetBinCenter(i+1);
	  yield_B = h_real_H_tofw_neg_mm->GetBinContent(i+1);
	  eyield_B = h_real_H_tofw_neg_mm->GetBinError(i+1);
	}

      pT = (pT_A+pT_B)/2.0;
      yield = (yield_A+yield_B)/2.0;
      eyield = sqrt(eyield_A**2+eyield_B**2);
      foutnegcb<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
    }

  foutposcb.close();
  foutnegcb.close();

  // ---
  // ---
  // ---

  // that's it!

  */

  //cout<<"done with routine, now deleting pointers"<<endl;

  h_real_tofw_pos_pp->Delete();
  h_real_tofw_neg_pp->Delete();
  h_real_tofw_pos_mm->Delete();
  h_real_tofw_neg_mm->Delete();

  h_sim_tofw_pos_pp->Delete();
  h_sim_tofw_neg_pp->Delete();
  h_sim_tofw_pos_mm->Delete();
  h_sim_tofw_neg_mm->Delete();

  // ---

  f_real_pp->Close();
  f_real_mm->Close();

  f_simpion_pp->Close();
  f_simkaon_pp->Close();
  f_simproton_pp->Close();

  f_simpion_mm->Close();
  f_simkaon_mm->Close();
  f_simproton_mm->Close();

  // ---

  f_real_pp->Delete();
  f_real_mm->Delete();

  f_simpion_pp->Delete();
  f_simkaon_pp->Delete();
  f_simproton_pp->Delete();

  f_simpion_mm->Delete();
  f_simkaon_mm->Delete();
  f_simproton_mm->Delete();

  // now it's over!

}


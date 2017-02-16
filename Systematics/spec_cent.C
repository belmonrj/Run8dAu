void spec_cent()
{

  // step 1
  cout<<"now doing step 1, calculating reference spectra"<<endl;
  for(int ipid=0; ipid<6; ipid++)
    {
      step1(ipid,0,0,0);
      step1(ipid,0,0,1);
      step1(ipid,0,0,2);
      step1(ipid,0,0,3);
      step1(ipid,0,0,4);
    }

  // step 2
  cout<<"now doing step2, calculating systematically varied sepctra"<<endl;
  for(int iswitch=0; iswitch<2; iswitch++)
    {
      for(int itype=0; itype<10; itype++)
	{
	  for(int ipid=0; ipid<3; ipid++)
	    {
	      for(int icent=0; icent<5; icent++)
		{
		  // UNROLL THOSE LOOPS!!!
		  step2(ipid,itype,iswitch,icent);
		}
	    }
	}
    }

  // step 3
  cout<<"now doing step 3, calculating systematic variation"<<endl;
  for(int itype=0; itype<10; itype++)
    {
      for(int ipid=0; ipid<3; ipid++)
	{
	  step3(ipid,itype,0,0);
	  step3(ipid,itype,1,0);
	  step3(ipid,itype,0,1);
	  step3(ipid,itype,1,1);
	  step3(ipid,itype,0,2);
	  step3(ipid,itype,1,2);
	  step3(ipid,itype,0,3);
	  step3(ipid,itype,1,3);
	  step3(ipid,itype,0,4);
	  step3(ipid,itype,1,4);
	}
    }

  // step 4
  cout<<"adding up all uncertainties"<<endl;
  for(int ipid=0; ipid<3; ipid++)
    {
      step4(ipid,0);
      step4(ipid,1);
      step4(ipid,2);
      step4(ipid,3);
      step4(ipid,4);
    }

}



void step1(int ipid=0, int itype=0, int iswitch=0, int centid=0)
{




  TFile *f_real_L_pp = TFile::Open("RealFiles/outnew_pp.root");
  TFile *f_real_H_pp = TFile::Open("RealFiles/outnew_pp.root");
  TFile *f_simpion_pp = TFile::Open("SimFiles/pion/simsum_pp.root");
  TFile *f_simkaon_pp = TFile::Open("SimFiles/kaon/simsum_pp.root");
  TFile *f_simproton_pp = TFile::Open("SimFiles/proton/simsum_pp.root");

  TFile *f_real_L_mm = TFile::Open("RealFiles/outnew_mm.root");
  TFile *f_real_H_mm = TFile::Open("RealFiles/outnew_mm.root");
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
  int pidnumber = 0; // defaul
  if(ipid==0) pidnumber = 1;
  if(ipid==1) pidnumber = 3;
  if(ipid==2) pidnumber = 5;
  // if(ipid==0) pidnumber = 0;
  // if(ipid==1) pidnumber = 4;
  // if(ipid==2) pidnumber = 6;
  // if(ipid==3) pidnumber = 2;
  // if(ipid==4) pidnumber = 4;
  // if(ipid==5) pidnumber = 8;

  // char centstring[5];
  // if(centid==0) sprintf(centstring,"0088");
  // else if(centid==1) sprintf(centstring,"0020");
  // else if(centid==2) sprintf(centstring,"2040");
  // else if(centid==3) sprintf(centstring,"4060");
  // else if(centid==4) sprintf(centstring,"6088");
  // else {cout<<"you gonna die"<<endl; return;}

  char centstring[10];
  if(centid==0) sprintf(centstring,"cent0088");
  else if(centid==1) sprintf(centstring,"cent0020");
  else if(centid==2) sprintf(centstring,"cent2040");
  else if(centid==3) sprintf(centstring,"cent4060");
  else if(centid==4) sprintf(centstring,"cent6088");
  else {cout<<"you gonna die"<<endl; return;}


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

  sprintf(name_real_tofw_pos_pp,"ptpid_tofw_pos_%d_dis_%s",pidnumber,centstring);
  sprintf(name_sim_tofw_pos_pp,"ptpid_tofw_pos_%d_dis",pidnumber);
  sprintf(name_real_tofw_neg_pp,"ptpid_tofw_neg_%d_dis_%s",pidnumber,centstring);
  sprintf(name_sim_tofw_neg_pp,"ptpid_tofw_neg_%d_dis",pidnumber);

  sprintf(name_real_tofw_pos_mm,"ptpid_tofw_pos_%d_dis_%s",pidnumber,centstring);
  sprintf(name_sim_tofw_pos_mm,"ptpid_tofw_pos_%d_dis",pidnumber);
  sprintf(name_real_tofw_neg_mm,"ptpid_tofw_neg_%d_dis_%s",pidnumber,centstring);
  sprintf(name_sim_tofw_neg_mm,"ptpid_tofw_neg_%d_dis",pidnumber);

  TH1F *h_real_L_tofw_pos_pp = f_real_L_pp->Get(name_real_tofw_pos_pp);
  TH1F *h_real_L_tofw_neg_pp = f_real_L_pp->Get(name_real_tofw_neg_pp);
  TH1F *h_real_L_tofw_pos_mm = f_real_L_mm->Get(name_real_tofw_pos_mm);
  TH1F *h_real_L_tofw_neg_mm = f_real_L_mm->Get(name_real_tofw_neg_mm);

  TH1F *h_real_H_tofw_pos_pp = f_real_H_pp->Get(name_real_tofw_pos_pp);
  TH1F *h_real_H_tofw_neg_pp = f_real_H_pp->Get(name_real_tofw_neg_pp);
  TH1F *h_real_H_tofw_pos_mm = f_real_H_mm->Get(name_real_tofw_pos_mm);
  TH1F *h_real_H_tofw_neg_mm = f_real_H_mm->Get(name_real_tofw_neg_mm);

  if(ipid==0||ipid==3)
    {
      TH1F *h_sim_tofw_pos_pp = f_simpion_pp->Get(name_sim_tofw_pos_pp);
      TH1F *h_sim_tofw_neg_pp = f_simpion_pp->Get(name_sim_tofw_neg_pp);
      TH1F *h_sim_tofw_pos_mm = f_simpion_mm->Get(name_sim_tofw_pos_mm);
      TH1F *h_sim_tofw_neg_mm = f_simpion_mm->Get(name_sim_tofw_neg_mm);
    }
  else if(ipid==1||ipid==4)
    {
      TH1F *h_sim_tofw_pos_pp = f_simkaon_pp->Get(name_sim_tofw_pos_pp);
      TH1F *h_sim_tofw_neg_pp = f_simkaon_pp->Get(name_sim_tofw_neg_pp);
      TH1F *h_sim_tofw_pos_mm = f_simkaon_mm->Get(name_sim_tofw_pos_mm);
      TH1F *h_sim_tofw_neg_mm = f_simkaon_mm->Get(name_sim_tofw_neg_mm);
    }
  else if(ipid==2||ipid==5)
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

  h_real_L_tofw_pos_pp->Sumw2();
  h_real_L_tofw_neg_pp->Sumw2();
  h_real_L_tofw_pos_mm->Sumw2();
  h_real_L_tofw_neg_mm->Sumw2();

  h_real_H_tofw_pos_pp->Sumw2();
  h_real_H_tofw_neg_pp->Sumw2();
  h_real_H_tofw_pos_mm->Sumw2();
  h_real_H_tofw_neg_mm->Sumw2();

  h_sim_tofw_pos_pp->Sumw2();
  h_sim_tofw_neg_pp->Sumw2();
  h_sim_tofw_pos_mm->Sumw2();
  h_sim_tofw_neg_mm->Sumw2();


  // divide Real histogram by Sim histogram
  
  h_real_L_tofw_pos_pp->Divide(h_sim_tofw_pos_pp);
  h_real_L_tofw_neg_pp->Divide(h_sim_tofw_neg_pp);
  h_real_L_tofw_pos_mm->Divide(h_sim_tofw_pos_mm);
  h_real_L_tofw_neg_mm->Divide(h_sim_tofw_neg_mm);

  h_real_H_tofw_pos_pp->Divide(h_sim_tofw_pos_pp);
  h_real_H_tofw_neg_pp->Divide(h_sim_tofw_neg_pp);
  h_real_H_tofw_pos_mm->Divide(h_sim_tofw_pos_mm);
  h_real_H_tofw_neg_mm->Divide(h_sim_tofw_neg_mm);

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

  h_real_L_tofw_pos_pp->Multiply(dummy,simconst);
  h_real_L_tofw_neg_pp->Multiply(dummy,simconst);
  h_real_L_tofw_pos_mm->Multiply(dummy,simconst);
  h_real_L_tofw_neg_mm->Multiply(dummy,simconst);

  h_real_H_tofw_pos_pp->Multiply(dummy,simconst);
  h_real_H_tofw_neg_pp->Multiply(dummy,simconst);
  h_real_H_tofw_pos_mm->Multiply(dummy,simconst);
  h_real_H_tofw_neg_mm->Multiply(dummy,simconst);


  // Division constants
  // Divide by the number of real events, various efficiencies, and pT and cent bin-widths
  //float embed[9] = {0.542065, 0.653215, 0.751339, 0.81413, 0.882178, 0.924843, 0.949757, 0.968341, 0.972655};
  float embed[3] = {0.542065, 0.653215, 0.751339};
  Long64_t nevents_L_pp = 39733831; // 39.7 M 
  Long64_t nevents_L_mm = 27794082; // 27.8 M
  Long64_t nevents_H_pp = 2136153235; // 2.14 B
  Long64_t nevents_H_mm = 2132453794; // 2.13 B
  float tofw_eff = 0.95; // cosmic ray studies show 95%, in situ studies show 90%
  float tofw_adc = 0.85; // in situ studies show 85%
  float dcqual = 0.9; // percentage of high-quality tracks is lower in real than in sim
  float binwidth_pT = 0.1; // 100 MeV bins
  //float binwidth_cent = 0.1; // 10% centrality bins, adjust as needed
  float binwidth_cent = 0.92; // using MB for systematics
  //if(centid==8) binwidth_cent = 0.12; // not using
  //float twopi = 6.28318531; // corrected spectra are 1/2pi 1/pT
  int slem = 2;

  float konstant_L_pp = nevents_L_pp*embed[slem]*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;
  float konstant_L_mm = nevents_L_mm*embed[slem]*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;
  float konstant_H_pp = nevents_H_pp*embed[slem]*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;
  float konstant_H_mm = nevents_H_mm*embed[slem]*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;

  TF1 *fun = new TF1("fun","pol1",0,10);
  fun->SetParameter(0,0);
  //fun->SetParameter(1,1);
  fun->SetParameter(1,6.28318531); // corrected spectra are 1/(2pipT)





  h_real_L_tofw_pos_pp->Divide(fun,konstant_L_pp);
  h_real_L_tofw_neg_pp->Divide(fun,konstant_L_pp);
  h_real_L_tofw_pos_mm->Divide(fun,konstant_L_mm);
  h_real_L_tofw_neg_mm->Divide(fun,konstant_L_mm);

  h_real_H_tofw_pos_pp->Divide(fun,konstant_H_pp);
  h_real_H_tofw_neg_pp->Divide(fun,konstant_H_pp);
  h_real_H_tofw_pos_mm->Divide(fun,konstant_H_mm);
  h_real_H_tofw_neg_mm->Divide(fun,konstant_H_mm);



  /*

  char fnameoutpospm[100];
  char fnameoutnegpm[100];
  char fnameoutposmp[100];
  char fnameoutnegmp[100];

  sprintf(fnameoutpospm,"Data/ptpid_tofw_pos_%d_dis_%s_pp.dat",pidnumber,centstring);
  sprintf(fnameoutnegpm,"Data/ptpid_tofw_neg_%d_dis_%s_pp.dat",pidnumber,centstring);
  sprintf(fnameoutposmp,"Data/ptpid_tofw_pos_%d_dis_%s_mm.dat",pidnumber,centstring);
  sprintf(fnameoutnegmp,"Data/ptpid_tofw_neg_%d_dis_%s_mm.dat",pidnumber,centstring);

  ofstream foutpospm;
  ofstream foutnegpm;
  ofstream foutposmp;
  ofstream foutnegmp;

  foutpospm.open(fnameoutpospm);
  foutnegpm.open(fnameoutnegpm);
  foutposmp.open(fnameoutposmp);
  foutnegmp.open(fnameoutnegmp);

  for(int i=0; i<100; i++)
    {
      float pT, yield, eyield;
      if(i<30)
	{
	  // pospm
	  pT = h_real_L_tofw_pos_pp->GetBinCenter(i+1);
	  yield = h_real_L_tofw_pos_pp->GetBinContent(i+1);
	  eyield = h_real_L_tofw_pos_pp->GetBinError(i+1);
	  foutpospm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negpm
	  pT = h_real_L_tofw_neg_pp->GetBinCenter(i+1);
	  yield = h_real_L_tofw_neg_pp->GetBinContent(i+1);
	  eyield = h_real_L_tofw_neg_pp->GetBinError(i+1);
	  foutnegpm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // posmp
	  pT = h_real_L_tofw_pos_mm->GetBinCenter(i+1);
	  yield = h_real_L_tofw_pos_mm->GetBinContent(i+1);
	  eyield = h_real_L_tofw_pos_mm->GetBinError(i+1);
	  foutposmp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negmp
	  pT = h_real_L_tofw_neg_mm->GetBinCenter(i+1);
	  yield = h_real_L_tofw_neg_mm->GetBinContent(i+1);
	  eyield = h_real_L_tofw_neg_mm->GetBinError(i+1);
	  foutnegmp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	}
      if(i>=30)
	{
	  // pospm
	  pT = h_real_H_tofw_pos_pp->GetBinCenter(i+1);
	  yield = h_real_H_tofw_pos_pp->GetBinContent(i+1);
	  eyield = h_real_H_tofw_pos_pp->GetBinError(i+1);
	  foutpospm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negpm
	  pT = h_real_H_tofw_neg_pp->GetBinCenter(i+1);
	  yield = h_real_H_tofw_neg_pp->GetBinContent(i+1);
	  eyield = h_real_H_tofw_neg_pp->GetBinError(i+1);
	  foutnegpm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // posmp
	  pT = h_real_H_tofw_pos_mm->GetBinCenter(i+1);
	  yield = h_real_H_tofw_pos_mm->GetBinContent(i+1);
	  eyield = h_real_H_tofw_pos_mm->GetBinError(i+1);
	  foutposmp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negmp
	  pT = h_real_H_tofw_neg_mm->GetBinCenter(i+1);
	  yield = h_real_H_tofw_neg_mm->GetBinContent(i+1);
	  eyield = h_real_H_tofw_neg_mm->GetBinError(i+1);
	  foutnegmp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	}
    }

  foutpospm.close();
  foutnegpm.close();
  foutposmp.close();
  foutnegmp.close();

  */

  // -------------------------- //
  // --- now combine fields --- //
  // -------------------------- //

  char fnameoutposcb[100];
  char fnameoutnegcb[100];

  sprintf(fnameoutposcb,"Data/ptpid_tofw_pos_%d_dis_%s.dat",pidnumber,centstring);
  sprintf(fnameoutnegcb,"Data/ptpid_tofw_neg_%d_dis_%s.dat",pidnumber,centstring);

  ofstream foutposcb;
  ofstream foutnegcb;

  foutposcb.open(fnameoutposcb);
  foutnegcb.open(fnameoutnegcb);

  for(int i=0; i<100; i++)
    {
      float pT, yield, eyield;
      float pT_A, yield_A, eyield_A;
      float pT_B, yield_B, eyield_B;

      if(i<30)
	{
	  // pospm
	  pT_A = h_real_L_tofw_pos_pp->GetBinCenter(i+1);
	  yield_A = h_real_L_tofw_pos_pp->GetBinContent(i+1);
	  eyield_A = h_real_L_tofw_pos_pp->GetBinError(i+1);
	  // posmp
	  pT_B = h_real_L_tofw_pos_mm->GetBinCenter(i+1);
	  yield_B = h_real_L_tofw_pos_mm->GetBinContent(i+1);
	  eyield_B = h_real_L_tofw_pos_mm->GetBinError(i+1);
	}
      if(i>=30)
	{
	  // pospm
	  pT_A = h_real_H_tofw_pos_pp->GetBinCenter(i+1);
	  yield_A = h_real_H_tofw_pos_pp->GetBinContent(i+1);
	  eyield_A = h_real_H_tofw_pos_pp->GetBinError(i+1);
	  // posmp
	  pT_B = h_real_H_tofw_pos_mm->GetBinCenter(i+1);
	  yield_B = h_real_H_tofw_pos_mm->GetBinContent(i+1);
	  eyield_B = h_real_H_tofw_pos_mm->GetBinError(i+1);
	}

      pT = (pT_A+pT_B)/2.0;
      yield = (yield_A+yield_B)/2.0;
      eyield = sqrt(eyield_A**2+eyield_B**2)/2.0;
      foutposcb<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;

      if(i<30)
	{
	  // negpm
	  pT_A = h_real_L_tofw_neg_pp->GetBinCenter(i+1);
	  yield_A = h_real_L_tofw_neg_pp->GetBinContent(i+1);
	  eyield_A = h_real_L_tofw_neg_pp->GetBinError(i+1);
	  // negmp
	  pT_B = h_real_L_tofw_neg_mm->GetBinCenter(i+1);
	  yield_B = h_real_L_tofw_neg_mm->GetBinContent(i+1);
	  eyield_B = h_real_L_tofw_neg_mm->GetBinError(i+1);
	}
      if(i>=30)
	{
	  // negpm
	  pT_A = h_real_H_tofw_neg_pp->GetBinCenter(i+1);
	  yield_A = h_real_H_tofw_neg_pp->GetBinContent(i+1);
	  eyield_A = h_real_H_tofw_neg_pp->GetBinError(i+1);
	  // negmp
	  pT_B = h_real_H_tofw_neg_mm->GetBinCenter(i+1);
	  yield_B = h_real_H_tofw_neg_mm->GetBinContent(i+1);
	  eyield_B = h_real_H_tofw_neg_mm->GetBinError(i+1);
	}

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

  h_real_L_tofw_pos_pp->Rebin(5);
  h_real_L_tofw_neg_pp->Rebin(5);
  h_real_L_tofw_pos_mm->Rebin(5);
  h_real_L_tofw_neg_mm->Rebin(5);

  h_real_L_tofw_pos_pp->Divide(dummy,5.0);
  h_real_L_tofw_neg_pp->Divide(dummy,5.0);
  h_real_L_tofw_pos_mm->Divide(dummy,5.0);
  h_real_L_tofw_neg_mm->Divide(dummy,5.0);

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



  sprintf(fnameoutpospm,"Data/R5_ptpid_tofw_pos_%d_dis_%s_pp.dat",pidnumber,centstring);
  sprintf(fnameoutnegpm,"Data/R5_ptpid_tofw_neg_%d_dis_%s_pp.dat",pidnumber,centstring);
  sprintf(fnameoutposmp,"Data/R5_ptpid_tofw_pos_%d_dis_%s_mm.dat",pidnumber,centstring);
  sprintf(fnameoutnegmp,"Data/R5_ptpid_tofw_neg_%d_dis_%s_mm.dat",pidnumber,centstring);

  foutpospm.open(fnameoutpospm);
  foutnegpm.open(fnameoutnegpm);
  foutposmp.open(fnameoutposmp);
  foutnegmp.open(fnameoutnegmp);

  //for(int i=0; i<100; i++)
  for(int i=0; i<20; i++) // reduce by 5 :)
    {
      float pT, yield, eyield;
      //if(i<30)
      if(i<6)
	{
	  // pospm
	  pT = h_real_L_tofw_pos_pp->GetBinCenter(i+1);
	  yield = h_real_L_tofw_pos_pp->GetBinContent(i+1);
	  eyield = h_real_L_tofw_pos_pp->GetBinError(i+1);
	  foutpospm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negpm
	  pT = h_real_L_tofw_neg_pp->GetBinCenter(i+1);
	  yield = h_real_L_tofw_neg_pp->GetBinContent(i+1);
	  eyield = h_real_L_tofw_neg_pp->GetBinError(i+1);
	  foutnegpm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // posmp
	  pT = h_real_L_tofw_pos_mm->GetBinCenter(i+1);
	  yield = h_real_L_tofw_pos_mm->GetBinContent(i+1);
	  eyield = h_real_L_tofw_pos_mm->GetBinError(i+1);
	  foutposmp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negmp
	  pT = h_real_L_tofw_neg_mm->GetBinCenter(i+1);
	  yield = h_real_L_tofw_neg_mm->GetBinContent(i+1);
	  eyield = h_real_L_tofw_neg_mm->GetBinError(i+1);
	  foutnegmp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	}
      //if(i>=30)
      if(i>=6)
	{
	  // pospm
	  pT = h_real_H_tofw_pos_pp->GetBinCenter(i+1);
	  yield = h_real_H_tofw_pos_pp->GetBinContent(i+1);
	  eyield = h_real_H_tofw_pos_pp->GetBinError(i+1);
	  foutpospm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negpm
	  pT = h_real_H_tofw_neg_pp->GetBinCenter(i+1);
	  yield = h_real_H_tofw_neg_pp->GetBinContent(i+1);
	  eyield = h_real_H_tofw_neg_pp->GetBinError(i+1);
	  foutnegpm<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // posmp
	  pT = h_real_H_tofw_pos_mm->GetBinCenter(i+1);
	  yield = h_real_H_tofw_pos_mm->GetBinContent(i+1);
	  eyield = h_real_H_tofw_pos_mm->GetBinError(i+1);
	  foutposmp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	  // negmp
	  pT = h_real_H_tofw_neg_mm->GetBinCenter(i+1);
	  yield = h_real_H_tofw_neg_mm->GetBinContent(i+1);
	  eyield = h_real_H_tofw_neg_mm->GetBinError(i+1);
	  foutnegmp<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
	}
    }

  foutpospm.close();
  foutnegpm.close();
  foutposmp.close();
  foutnegmp.close();



  // -------------------------- //
  // --- now combine fields --- //
  // -------------------------- //

  sprintf(fnameoutposcb,"Data/R5_ptpid_tofw_pos_%d_dis_%s.dat",pidnumber,centstring);
  sprintf(fnameoutnegcb,"Data/R5_ptpid_tofw_neg_%d_dis_%s.dat",pidnumber,centstring);

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
	  // pospm
	  pT_A = h_real_L_tofw_pos_pp->GetBinCenter(i+1);
	  yield_A = h_real_L_tofw_pos_pp->GetBinContent(i+1);
	  eyield_A = h_real_L_tofw_pos_pp->GetBinError(i+1);
	  // posmp
	  pT_B = h_real_L_tofw_pos_mm->GetBinCenter(i+1);
	  yield_B = h_real_L_tofw_pos_mm->GetBinContent(i+1);
	  eyield_B = h_real_L_tofw_pos_mm->GetBinError(i+1);
	}
      //if(i>=30)
      if(i>=6)
	{
	  // pospm
	  pT_A = h_real_H_tofw_pos_pp->GetBinCenter(i+1);
	  yield_A = h_real_H_tofw_pos_pp->GetBinContent(i+1);
	  eyield_A = h_real_H_tofw_pos_pp->GetBinError(i+1);
	  // posmp
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
	  // negpm
	  pT_A = h_real_L_tofw_neg_pp->GetBinCenter(i+1);
	  yield_A = h_real_L_tofw_neg_pp->GetBinContent(i+1);
	  eyield_A = h_real_L_tofw_neg_pp->GetBinError(i+1);
	  // negmp
	  pT_B = h_real_L_tofw_neg_mm->GetBinCenter(i+1);
	  yield_B = h_real_L_tofw_neg_mm->GetBinContent(i+1);
	  eyield_B = h_real_L_tofw_neg_mm->GetBinError(i+1);
	}
      //if(i>=30)
      if(i>=6)
	{
	  // negpm
	  pT_A = h_real_H_tofw_neg_pp->GetBinCenter(i+1);
	  yield_A = h_real_H_tofw_neg_pp->GetBinContent(i+1);
	  eyield_A = h_real_H_tofw_neg_pp->GetBinError(i+1);
	  // negmp
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

  h_real_L_tofw_pos_pp->Delete();
  h_real_L_tofw_neg_pp->Delete();
  h_real_L_tofw_pos_mm->Delete();
  h_real_L_tofw_neg_mm->Delete();

  h_real_H_tofw_pos_pp->Delete();
  h_real_H_tofw_neg_pp->Delete();
  h_real_H_tofw_pos_mm->Delete();
  h_real_H_tofw_neg_mm->Delete();

  h_sim_tofw_pos_pp->Delete();
  h_sim_tofw_neg_pp->Delete();
  h_sim_tofw_pos_mm->Delete();
  h_sim_tofw_neg_mm->Delete();

  // ---

  f_real_L_pp->Close();
  f_real_L_mm->Close();

  f_real_H_pp->Close();
  f_real_H_mm->Close();

  f_simpion_pp->Close();
  f_simkaon_pp->Close();
  f_simproton_pp->Close();

  f_simpion_mm->Close();
  f_simkaon_mm->Close();
  f_simproton_mm->Close();

  // ---

  f_real_L_pp->Delete();
  f_real_L_mm->Delete();

  f_real_H_pp->Delete();
  f_real_H_mm->Delete();

  f_simpion_pp->Delete();
  f_simkaon_pp->Delete();
  f_simproton_pp->Delete();

  f_simpion_mm->Delete();
  f_simkaon_mm->Delete();
  f_simproton_mm->Delete();

  // now it's over!

} // end step 1



void step2(int ipid=0, int itype=0, int iswitch=0, int centid=0)
{


  TFile *f_real_L_pp = TFile::Open("RealFiles/outnew_pp.root");
  TFile *f_real_H_pp = TFile::Open("RealFiles/outnew_pp.root");
  TFile *f_simpion_pp = TFile::Open("SimFiles/pion/simsum_pp.root");
  TFile *f_simkaon_pp = TFile::Open("SimFiles/kaon/simsum_pp.root");
  TFile *f_simproton_pp = TFile::Open("SimFiles/proton/simsum_pp.root");

  TFile *f_real_L_mm = TFile::Open("RealFiles/outnew_mm.root");
  TFile *f_real_H_mm = TFile::Open("RealFiles/outnew_mm.root");
  TFile *f_simpion_mm = TFile::Open("SimFiles/pion/simsum_mm.root");
  TFile *f_simkaon_mm = TFile::Open("SimFiles/kaon/simsum_mm.root");
  TFile *f_simproton_mm = TFile::Open("SimFiles/proton/simsum_mm.root");

  char pidstring[5];
  sprintf(pidstring,"pion"); // "default"
  if(ipid==0) sprintf(pidstring,"pion");
  if(ipid==1) sprintf(pidstring,"kaon");
  if(ipid==2) sprintf(pidstring,"prot");

  char typestring[5];
  sprintf(typestring,"tfwm"); // "default"
  if(itype==0) sprintf(typestring,"tfwm");
  if(itype==1) sprintf(typestring,"pc3m");
  if(itype==2) sprintf(typestring,"pc3f");
  if(itype==3) sprintf(typestring,"pc1f");
  if(itype==4) sprintf(typestring,"dcfc");
  if(itype==5) sprintf(typestring,"dzed");
  if(itype==6) sprintf(typestring,"spid");
  if(itype==7) sprintf(typestring,"tpid");
  if(itype==8) sprintf(typestring,"gadc");// forgot this one
  if(itype==9) sprintf(typestring,"tepc");// forgot this one

  char switchstring[2];
  sprintf(switchstring,"A"); // "default"
  if(iswitch==0) sprintf(switchstring,"A");
  if(iswitch==1) sprintf(switchstring,"B");

  // char centstring[5];
  // if(centid==0) sprintf(centstring,"0088");
  // else if(centid==1) sprintf(centstring,"0020");
  // else if(centid==2) sprintf(centstring,"2040");
  // else if(centid==3) sprintf(centstring,"4060");
  // else if(centid==4) sprintf(centstring,"6088");
  // else {cout<<"you gonna die"<<endl; return;}

  char centstring[11];
  if(centid==0) sprintf(centstring,"_cent0088");
  else if(centid==1) sprintf(centstring,"_cent0020");
  else if(centid==2) sprintf(centstring,"_cent2040");
  else if(centid==3) sprintf(centstring,"_cent4060");
  else if(centid==4) sprintf(centstring,"_cent6088");
  else {cout<<"you gonna die"<<endl; return;}



  char name_real_tofw_pos_pp[50];
  char name_sim_tofw_pos_pp[50];
  char name_real_tofw_neg_pp[50];
  char name_sim_tofw_neg_pp[50];

  char name_real_tofw_pos_mm[50];
  char name_sim_tofw_pos_mm[50];
  char name_real_tofw_neg_mm[50];
  char name_sim_tofw_neg_mm[50];

  sprintf(name_real_tofw_pos_pp,"ptsys_%s_pos_%s%s%s",pidstring,typestring,switchstring,centstring);
  sprintf(name_sim_tofw_pos_pp,"ptsys_%s_pos_%s%s",pidstring,typestring,switchstring);
  sprintf(name_real_tofw_neg_pp,"ptsys_%s_neg_%s%s%s",pidstring,typestring,switchstring,centstring);
  sprintf(name_sim_tofw_neg_pp,"ptsys_%s_neg_%s%s",pidstring,typestring,switchstring);

  sprintf(name_real_tofw_pos_mm,"ptsys_%s_pos_%s%s%s",pidstring,typestring,switchstring,centstring);
  sprintf(name_sim_tofw_pos_mm,"ptsys_%s_pos_%s%s",pidstring,typestring,switchstring);
  sprintf(name_real_tofw_neg_mm,"ptsys_%s_neg_%s%s%s",pidstring,typestring,switchstring,centstring);
  sprintf(name_sim_tofw_neg_mm,"ptsys_%s_neg_%s%s",pidstring,typestring,switchstring);

  TH1F *h_real_L_tofw_pos_pp = f_real_L_pp->Get(name_real_tofw_pos_pp);
  TH1F *h_real_L_tofw_neg_pp = f_real_L_pp->Get(name_real_tofw_neg_pp);
  TH1F *h_real_L_tofw_pos_mm = f_real_L_mm->Get(name_real_tofw_pos_mm);
  TH1F *h_real_L_tofw_neg_mm = f_real_L_mm->Get(name_real_tofw_neg_mm);

  TH1F *h_real_H_tofw_pos_pp = f_real_H_pp->Get(name_real_tofw_pos_pp);
  TH1F *h_real_H_tofw_neg_pp = f_real_H_pp->Get(name_real_tofw_neg_pp);
  TH1F *h_real_H_tofw_pos_mm = f_real_H_mm->Get(name_real_tofw_pos_mm);
  TH1F *h_real_H_tofw_neg_mm = f_real_H_mm->Get(name_real_tofw_neg_mm);

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

  h_real_L_tofw_pos_pp->Sumw2();
  h_real_L_tofw_neg_pp->Sumw2();
  h_real_L_tofw_pos_mm->Sumw2();
  h_real_L_tofw_neg_mm->Sumw2();

  h_real_H_tofw_pos_pp->Sumw2();
  h_real_H_tofw_neg_pp->Sumw2();
  h_real_H_tofw_pos_mm->Sumw2();
  h_real_H_tofw_neg_mm->Sumw2();

  h_sim_tofw_pos_pp->Sumw2();
  h_sim_tofw_neg_pp->Sumw2();
  h_sim_tofw_pos_mm->Sumw2();
  h_sim_tofw_neg_mm->Sumw2();


  // divide Real histogram by Sim histogram
  
  h_real_L_tofw_pos_pp->Divide(h_sim_tofw_pos_pp);
  h_real_L_tofw_neg_pp->Divide(h_sim_tofw_neg_pp);
  h_real_L_tofw_pos_mm->Divide(h_sim_tofw_pos_mm);
  h_real_L_tofw_neg_mm->Divide(h_sim_tofw_neg_mm);

  h_real_H_tofw_pos_pp->Divide(h_sim_tofw_pos_pp);
  h_real_H_tofw_neg_pp->Divide(h_sim_tofw_neg_pp);
  h_real_H_tofw_pos_mm->Divide(h_sim_tofw_pos_mm);
  h_real_H_tofw_neg_mm->Divide(h_sim_tofw_neg_mm);

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

  h_real_L_tofw_pos_pp->Multiply(dummy,simconst);
  h_real_L_tofw_neg_pp->Multiply(dummy,simconst);
  h_real_L_tofw_pos_mm->Multiply(dummy,simconst);
  h_real_L_tofw_neg_mm->Multiply(dummy,simconst);

  h_real_H_tofw_pos_pp->Multiply(dummy,simconst);
  h_real_H_tofw_neg_pp->Multiply(dummy,simconst);
  h_real_H_tofw_pos_mm->Multiply(dummy,simconst);
  h_real_H_tofw_neg_mm->Multiply(dummy,simconst);


  // Division constants
  // Divide by the number of real events, various efficiencies, and pT and cent bin-widths
  //float embed[9] = {0.542065, 0.653215, 0.751339, 0.81413, 0.882178, 0.924843, 0.949757, 0.968341, 0.972655};
  float embed[3] = {0.542065, 0.653215, 0.751339};
  Long64_t nevents_L_pp = 39733831; // 39.7 M 
  Long64_t nevents_L_mm = 27794082; // 27.8 M
  Long64_t nevents_H_pp = 2136153235; // 2.14 B
  Long64_t nevents_H_mm = 2132453794; // 2.13 B
  float tofw_eff = 0.95; // cosmic ray studies show 95%, in situ studies show 90%
  float tofw_adc = 0.85; // in situ studies show 85%
  float dcqual = 0.9; // percentage of high-quality tracks is lower in real than in sim
  float binwidth_pT = 0.1; // 100 MeV bins
  //float binwidth_cent = 0.1; // 10% centrality bins, adjust as needed
  float binwidth_cent = 0.92; // using MB for systematics
  //if(centid==8) binwidth_cent = 0.12; // not using
  //float twopi = 6.28318531; // corrected spectra are 1/2pi 1/pT
  int slem = 2;

  float konstant_L_pp = nevents_L_pp*embed[slem]*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;
  float konstant_L_mm = nevents_L_mm*embed[slem]*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;
  float konstant_H_pp = nevents_H_pp*embed[slem]*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;
  float konstant_H_mm = nevents_H_mm*embed[slem]*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;

  TF1 *fun = new TF1("fun","pol1",0,10);
  fun->SetParameter(0,0);
  //fun->SetParameter(1,1);
  fun->SetParameter(1,6.28318531); // corrected spectra are 1/(2pipT)





  h_real_L_tofw_pos_pp->Divide(fun,konstant_L_pp);
  h_real_L_tofw_neg_pp->Divide(fun,konstant_L_pp);
  h_real_L_tofw_pos_mm->Divide(fun,konstant_L_mm);
  h_real_L_tofw_neg_mm->Divide(fun,konstant_L_mm);

  h_real_H_tofw_pos_pp->Divide(fun,konstant_H_pp);
  h_real_H_tofw_neg_pp->Divide(fun,konstant_H_pp);
  h_real_H_tofw_pos_mm->Divide(fun,konstant_H_mm);
  h_real_H_tofw_neg_mm->Divide(fun,konstant_H_mm);




  // -------------------------- //
  // --- now combine fields --- //
  // -------------------------- //

  char fnameoutposcb[100];
  char fnameoutnegcb[100];

  sprintf(fnameoutposcb,"Data/ptsys_%s_pos_%s%s%s.dat",pidstring,typestring,switchstring,centstring);
  sprintf(fnameoutnegcb,"Data/ptsys_%s_neg_%s%s%s.dat",pidstring,typestring,switchstring,centstring);

  ofstream foutposcb;
  ofstream foutnegcb;

  foutposcb.open(fnameoutposcb);
  foutnegcb.open(fnameoutnegcb);

  for(int i=0; i<100; i++)
    {
      float pT, yield, eyield;
      float pT_A, yield_A, eyield_A;
      float pT_B, yield_B, eyield_B;

      if(i<30)
	{
	  // pospm
	  pT_A = h_real_L_tofw_pos_pp->GetBinCenter(i+1);
	  yield_A = h_real_L_tofw_pos_pp->GetBinContent(i+1);
	  eyield_A = h_real_L_tofw_pos_pp->GetBinError(i+1);
	  // posmp
	  pT_B = h_real_L_tofw_pos_mm->GetBinCenter(i+1);
	  yield_B = h_real_L_tofw_pos_mm->GetBinContent(i+1);
	  eyield_B = h_real_L_tofw_pos_mm->GetBinError(i+1);
	}
      if(i>=30)
	{
	  // pospm
	  pT_A = h_real_H_tofw_pos_pp->GetBinCenter(i+1);
	  yield_A = h_real_H_tofw_pos_pp->GetBinContent(i+1);
	  eyield_A = h_real_H_tofw_pos_pp->GetBinError(i+1);
	  // posmp
	  pT_B = h_real_H_tofw_pos_mm->GetBinCenter(i+1);
	  yield_B = h_real_H_tofw_pos_mm->GetBinContent(i+1);
	  eyield_B = h_real_H_tofw_pos_mm->GetBinError(i+1);
	}

      pT = (pT_A+pT_B)/2.0;
      yield = (yield_A+yield_B)/2.0;
      eyield = sqrt(eyield_A**2+eyield_B**2)/2.0;
      foutposcb<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;

      if(i<30)
	{
	  // negpm
	  pT_A = h_real_L_tofw_neg_pp->GetBinCenter(i+1);
	  yield_A = h_real_L_tofw_neg_pp->GetBinContent(i+1);
	  eyield_A = h_real_L_tofw_neg_pp->GetBinError(i+1);
	  // negmp
	  pT_B = h_real_L_tofw_neg_mm->GetBinCenter(i+1);
	  yield_B = h_real_L_tofw_neg_mm->GetBinContent(i+1);
	  eyield_B = h_real_L_tofw_neg_mm->GetBinError(i+1);
	}
      if(i>=30)
	{
	  // negpm
	  pT_A = h_real_H_tofw_neg_pp->GetBinCenter(i+1);
	  yield_A = h_real_H_tofw_neg_pp->GetBinContent(i+1);
	  eyield_A = h_real_H_tofw_neg_pp->GetBinError(i+1);
	  // negmp
	  pT_B = h_real_H_tofw_neg_mm->GetBinCenter(i+1);
	  yield_B = h_real_H_tofw_neg_mm->GetBinContent(i+1);
	  eyield_B = h_real_H_tofw_neg_mm->GetBinError(i+1);
	}

      pT = (pT_A+pT_B)/2.0;
      yield = (yield_A+yield_B)/2.0;
      eyield = sqrt(eyield_A**2+eyield_B**2)/2.0;
      foutnegcb<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
    }

  foutposcb.close();
  foutnegcb.close();


  //cout<<"done with routine, now deleting pointers"<<endl;

  h_real_L_tofw_pos_pp->Delete();
  h_real_L_tofw_neg_pp->Delete();
  h_real_L_tofw_pos_mm->Delete();
  h_real_L_tofw_neg_mm->Delete();

  h_real_H_tofw_pos_pp->Delete();
  h_real_H_tofw_neg_pp->Delete();
  h_real_H_tofw_pos_mm->Delete();
  h_real_H_tofw_neg_mm->Delete();

  h_sim_tofw_pos_pp->Delete();
  h_sim_tofw_neg_pp->Delete();
  h_sim_tofw_pos_mm->Delete();
  h_sim_tofw_neg_mm->Delete();

  // ---

  f_real_L_pp->Close();
  f_real_L_mm->Close();

  f_real_H_pp->Close();
  f_real_H_mm->Close();

  f_simpion_pp->Close();
  f_simkaon_pp->Close();
  f_simproton_pp->Close();

  f_simpion_mm->Close();
  f_simkaon_mm->Close();
  f_simproton_mm->Close();

  // ---

  f_real_L_pp->Delete();
  f_real_L_mm->Delete();

  f_real_H_pp->Delete();
  f_real_H_mm->Delete();

  f_simpion_pp->Delete();
  f_simkaon_pp->Delete();
  f_simproton_pp->Delete();

  f_simpion_mm->Delete();
  f_simkaon_mm->Delete();
  f_simproton_mm->Delete();

  // now it's over!

} // step2



void step3(int ipid=0, int itype=0, int iswitch=0, int centid=0)
{

  float errheight = 0.5; // new
  int number = 36; // new

  float ratiohigh = 1.5;
  float ratiolow =  0.5;

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->SetLogy(1);

  TLine *line = new TLine(0.0,1.0,6.0,1.0);
  TLine *line0 = new TLine(0.0,0.0,6.0,0.0);

  char gifname[100];
  char epsname[100];



  // char centstring[5];
  // if(centid==0) sprintf(centstring,"0088");
  // else if(centid==1) sprintf(centstring,"0020");
  // else if(centid==2) sprintf(centstring,"2040");
  // else if(centid==3) sprintf(centstring,"4060");
  // else if(centid==4) sprintf(centstring,"6088");
  // else {cout<<"you gonna die"<<endl; return;}

  char centstring[10];
  if(centid==0) sprintf(centstring,"cent0088");
  else if(centid==1) sprintf(centstring,"cent0020");
  else if(centid==2) sprintf(centstring,"cent2040");
  else if(centid==3) sprintf(centstring,"cent4060");
  else if(centid==4) sprintf(centstring,"cent6088");
  else {cout<<"you gonna die"<<endl; return;}


  int pidnumber = 0; // default
  int pidnumber = 0; // defaul
  if(ipid==0) pidnumber = 1;
  if(ipid==1) pidnumber = 3;
  if(ipid==2) pidnumber = 5;
  // if(itype<9)
  //   {
  //     if(ipid==0) pidnumber = 0;
  //     if(ipid==1) pidnumber = 4;
  //     if(ipid==2) pidnumber = 6;
  //   }
  // if(itype==9||itype==0||itype==1) //0,1 are new, temp?
  //   {
  //     if(ipid==0) pidnumber = 2;
  //     if(ipid==1) pidnumber = 4;
  //     if(ipid==2) pidnumber = 8;
  //   }

  char pidstring[5];
  sprintf(pidstring,"pion"); // "default"
  if(ipid==0) sprintf(pidstring,"pion");
  if(ipid==1) sprintf(pidstring,"kaon");
  if(ipid==2) sprintf(pidstring,"prot");

  char typestring[5];
  sprintf(typestring,"tfwm"); // "default"
  if(itype==0) sprintf(typestring,"tfwm");
  if(itype==1) sprintf(typestring,"pc3m");
  if(itype==2) sprintf(typestring,"pc3f");
  if(itype==3) sprintf(typestring,"pc1f");
  if(itype==4) sprintf(typestring,"dcfc");
  if(itype==5) sprintf(typestring,"dzed");
  if(itype==6) sprintf(typestring,"spid");
  if(itype==7) sprintf(typestring,"tpid");
  if(itype==8) sprintf(typestring,"gadc");
  if(itype==9) sprintf(typestring,"tepc");

  char typelongstring[50];
  sprintf(typelongstring,"tofw matching"); // "default"

  if(iswitch==0)
    {
      if(itype==0) sprintf(typelongstring,"TOFW matching (1.5#sigma)");
      if(itype==1) sprintf(typelongstring,"PC3 matching (1.5#sigma)");
      if(itype==2) sprintf(typelongstring,"PC3 fiducial (bigger)");
      if(itype==3) sprintf(typelongstring,"PC1 fiducial (bigger)");
      if(itype==4) sprintf(typelongstring,"DCh fiducial (tighter)");
      if(itype==5) sprintf(typelongstring,"DCh zed cut (|zed|<40)");
      if(itype==6) sprintf(typelongstring,"PID function (diff pars)");
      if(itype==7) sprintf(typelongstring,"PID function (1.5#sigma, 2#sigma veto)");
      if(itype==8) sprintf(typelongstring,"TOFW ADC cut (550>qtofw>65)");
      if(itype==9) sprintf(typelongstring,"ep cut (0.15)");
    }
  if(iswitch==1)
    {
      if(itype==0) sprintf(typelongstring,"TOFW matching (2.5#sigma)");
      if(itype==1) sprintf(typelongstring,"PC3 matching (2.5#sigma)");
      if(itype==2) sprintf(typelongstring,"PC3 fiducial (no cut)");
      if(itype==3) sprintf(typelongstring,"PC1 fiducial (no cut)");
      if(itype==4) sprintf(typelongstring,"DCh fiducial (no cut)");
      if(itype==5) sprintf(typelongstring,"DCh zed cut (|zed|>40)");
      if(itype==6) sprintf(typelongstring,"PID function (diff pars)");
      if(itype==7) sprintf(typelongstring,"PID function (2#sigma, 2.5#sigma veto)");
      if(itype==8) sprintf(typelongstring,"TOFW ADC cut (650>qtofw>55)");
      if(itype==9) sprintf(typelongstring,"ep cut (0.25)");
    }


  char switchstring[2];
  sprintf(switchstring,"A"); // "default"
  if(iswitch==0) sprintf(switchstring,"A");
  if(iswitch==1) sprintf(switchstring,"B");





  char fnameinposref[100];
  char fnameinnegref[100];
  sprintf(fnameinposref,"Data/ptpid_tofw_pos_%d_dis_%s.dat",pidnumber,centstring);
  sprintf(fnameinnegref,"Data/ptpid_tofw_neg_%d_dis_%s.dat",pidnumber,centstring);
  ifstream finposref;
  ifstream finnegref;
  finposref.open(fnameinposref);
  finnegref.open(fnameinnegref);

  char fnameinpossys[100];
  char fnameinnegsys[100];
  sprintf(fnameinpossys,"Data/ptsys_%s_pos_%s%s_%s.dat",pidstring,typestring,switchstring,centstring);
  sprintf(fnameinnegsys,"Data/ptsys_%s_neg_%s%s_%s.dat",pidstring,typestring,switchstring,centstring);
  ifstream finpossys;
  ifstream finnegsys;
  finpossys.open(fnameinpossys);
  finnegsys.open(fnameinnegsys);

  float pt_U_syspos[100], yield_U_syspos[100], eyield_U_syspos[100];
  float pt_U_sysneg[100], yield_U_sysneg[100], eyield_U_sysneg[100];
  float pt_U_refpos[100], yield_U_refpos[100], eyield_U_refpos[100];
  float pt_U_refneg[100], yield_U_refneg[100], eyield_U_refneg[100];

  float ept_U_syspos[100]={0};
  float ept_U_sysneg[100]={0};
  float ept_U_refpos[100]={0};
  float ept_U_refneg[100]={0};

  for(int i=0; i<100; i++)
    {
      // sys
      finpossys>>pt_U_syspos[i]>>yield_U_syspos[i]>>eyield_U_syspos[i];
      finnegsys>>pt_U_sysneg[i]>>yield_U_sysneg[i]>>eyield_U_sysneg[i];
      // ref
      finposref>>pt_U_refpos[i]>>yield_U_refpos[i]>>eyield_U_refpos[i];
      finnegref>>pt_U_refneg[i]>>yield_U_refneg[i]>>eyield_U_refneg[i];
    }

  finpossys.close();
  finnegsys.close();
  finposref.close();
  finnegref.close();

  // ------------- //
  // --- rebin --- //
  // ------------- //

  float pt_syspos[100], yield_syspos[100], eyield_syspos[100];
  float pt_sysneg[100], yield_sysneg[100], eyield_sysneg[100];
  float pt_refpos[100], yield_refpos[100], eyield_refpos[100];
  float pt_refneg[100], yield_refneg[100], eyield_refneg[100];

  float ept_syspos[100]={0};
  float ept_sysneg[100]={0};
  float ept_refpos[100]={0};
  float ept_refneg[100]={0};

  for(int i=0; i<100; i++)
    {
      int k;
      if(i<30)
	{
	  pt_syspos[i] = pt_U_syspos[i];
	  pt_sysneg[i] = pt_U_sysneg[i];
	  yield_syspos[i] = yield_U_syspos[i];
	  yield_sysneg[i] = yield_U_sysneg[i];
	  eyield_syspos[i] = eyield_U_syspos[i];
	  eyield_sysneg[i] = eyield_U_sysneg[i];
	  pt_refpos[i] = pt_U_refpos[i];
	  pt_refneg[i] = pt_U_refneg[i];
	  yield_refpos[i] = yield_U_refpos[i];
	  yield_refneg[i] = yield_U_refneg[i];
	  eyield_refpos[i] = eyield_U_refpos[i];
	  eyield_refneg[i] = eyield_U_refneg[i];
	}
      if(i>=30)
	{
	  k=i/5+24;
	  if(i%5!=0) continue;
	  // ---
	  pt_syspos[k] = (pt_U_syspos[i]+pt_U_syspos[i+1]+pt_U_syspos[i+2]+
			  pt_U_syspos[i+3]+pt_U_syspos[i+4])/5.0;
	  yield_syspos[k] = (yield_U_syspos[i]+yield_U_syspos[i+1]+yield_U_syspos[i+2]+
			     yield_U_syspos[i+3]+yield_U_syspos[i+4])/5.0;
	  eyield_syspos[k] = sqrt(eyield_U_syspos[i]**2+eyield_U_syspos[i+1]**2+eyield_U_syspos[i+2]**2+
				  eyield_U_syspos[i+3]**2+eyield_U_syspos[i+4]**2)/5.0;
	  pt_sysneg[k] = (pt_U_sysneg[i]+pt_U_sysneg[i+1]+ pt_U_sysneg[i+2]+
			  pt_U_sysneg[i+3]+pt_U_sysneg[i+4])/5.0;
	  yield_sysneg[k] = (yield_U_sysneg[i]+yield_U_sysneg[i+1]+yield_U_sysneg[i+2]+
			     yield_U_sysneg[i+3]+yield_U_sysneg[i+4])/5.0;
	  eyield_sysneg[k] = sqrt(eyield_U_sysneg[i]**2+eyield_U_sysneg[i+1]**2+eyield_U_sysneg[i+2]**2+
				  eyield_U_sysneg[i+3]**2+eyield_U_sysneg[i+4]**2)/5.0;
	  // ---
	  pt_refpos[k] = (pt_U_refpos[i]+pt_U_refpos[i+1]+ pt_U_refpos[i+2]+
			  pt_U_refpos[i+3]+pt_U_refpos[i+4])/5.0;
	  yield_refpos[k] = (yield_U_refpos[i]+yield_U_refpos[i+1]+yield_U_refpos[i+2]+
			     yield_U_refpos[i+3]+yield_U_refpos[i+4])/5.0;
	  eyield_refpos[k] = sqrt(eyield_U_refpos[i]**2+eyield_U_refpos[i+1]**2+eyield_U_refpos[i+2]**2+
				  eyield_U_refpos[i+3]**2+eyield_U_refpos[i+4]**2)/5.0;
	  pt_refneg[k] = (pt_U_refneg[i]+pt_U_refneg[i+1]+ pt_U_refneg[i+2]+
			  pt_U_refneg[i+3]+pt_U_refneg[i+4])/5.0;
	  yield_refneg[k] = (yield_U_refneg[i]+yield_U_refneg[i+1]+yield_U_refneg[i+2]+
			     yield_U_refneg[i+3]+yield_U_refneg[i+4])/5.0;
	  eyield_refneg[k] = sqrt(eyield_U_refneg[i]**2+eyield_U_refneg[i+1]**2+eyield_U_refneg[i+2]**2+
				  eyield_U_refneg[i+3]**2+eyield_U_refneg[i+4]**2)/5.0;
	  // ---
	  //cout<<"i is "<<i<<"\t k is "<<k<<"\t pt is "<<pt_syspos[k]<<endl;
	}
    }

  // ------------- //
  // --- rebin --- //
  // ------------- //

  TGraphErrors *tge_syspos = new TGraphErrors(number,pt_syspos,yield_syspos,ept_syspos,eyield_syspos);
  tge_syspos->SetMarkerStyle(kFullCircle);
  tge_syspos->SetMarkerColor(kBlack);
  TGraphErrors *tge_sysneg = new TGraphErrors(number,pt_sysneg,yield_sysneg,ept_sysneg,eyield_sysneg);
  tge_sysneg->SetMarkerStyle(kFullCircle);
  tge_sysneg->SetMarkerColor(kBlack);

  TGraphErrors *tge_refpos = new TGraphErrors(number,pt_refpos,yield_refpos,ept_refpos,eyield_refpos);
  tge_refpos->SetMarkerStyle(kFullCircle);
  tge_refpos->SetMarkerColor(kBlack);
  TGraphErrors *tge_refneg = new TGraphErrors(number,pt_refneg,yield_refneg,ept_refneg,eyield_refneg);
  tge_refneg->SetMarkerStyle(kFullCircle);
  tge_refneg->SetMarkerColor(kBlack);



  tge_syspos->SetMarkerColor(kRed);
  tge_syspos->SetMarkerStyle(kOpenSquare);
  TMultiGraph *tmg_pos = new TMultiGraph();
  tmg_pos->Add(tge_syspos);
  tmg_pos->Add(tge_refpos);
  tmg_pos->Draw("ap");
  tmg_pos->SetMaximum(1e3);
  tmg_pos->SetMinimum(1e-7);
  tmg_pos->GetXaxis()->SetLimits(0.0,6.0);
  tmg_pos->GetYaxis()->SetTitle("Invariant Yield (c^{2}/GeV^{2})");
  tmg_pos->GetYaxis()->CenterTitle();
  tmg_pos->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pos->GetXaxis()->CenterTitle();
  TLegend *leg_pos = new TLegend(0.58,0.68,0.88,0.88);
  leg_pos->SetFillColor(kWhite);
  leg_pos->SetBorderSize(0);
  leg_pos->AddEntry(tge_syspos,typelongstring,"p");
  leg_pos->AddEntry(tge_refpos,"standard","p");
  leg_pos->Draw();

  sprintf(gifname,"UFig/single_spectra_%s_pos_%s%s_%s.gif",pidstring,typestring,switchstring,centstring);
  sprintf(epsname,"UFig/single_spectra_%s_pos_%s%s_%s.eps",pidstring,typestring,switchstring,centstring);
  c1->Print(gifname);
  c1->Print(epsname);



  tge_sysneg->SetMarkerColor(kRed);
  tge_sysneg->SetMarkerStyle(kOpenSquare);
  TMultiGraph *tmg_neg = new TMultiGraph();
  tmg_neg->Add(tge_sysneg);
  tmg_neg->Add(tge_refneg);
  tmg_neg->Draw("ap");
  tmg_neg->SetMaximum(1e3);
  tmg_neg->SetMinimum(1e-7);
  tmg_neg->GetXaxis()->SetLimits(0.0,6.0);
  tmg_neg->GetYaxis()->SetTitle("Invariant Yield (c^{2}/GeV^{2})");
  tmg_neg->GetYaxis()->CenterTitle();
  tmg_neg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_neg->GetXaxis()->CenterTitle();
  TLegend *leg_neg = new TLegend(0.58,0.68,0.88,0.88);
  leg_neg->SetFillColor(kWhite);
  leg_neg->SetBorderSize(0);
  leg_neg->AddEntry(tge_sysneg,typelongstring,"p");
  leg_neg->AddEntry(tge_refneg,"standard","p");
  leg_neg->Draw();

  sprintf(gifname,"UFig/single_spectra_%s_neg_%s%s_%s.gif",pidstring,typestring,switchstring,centstring);
  sprintf(epsname,"UFig/single_spectra_%s_neg_%s%s_%s.eps",pidstring,typestring,switchstring,centstring);
  c1->Print(gifname);
  c1->Print(epsname);



  // -------------------------- //
  // --- now do some ratios --- //
  // -------------------------- //

  char textoutratioposname[100];
  sprintf(textoutratioposname,"Text/single_ratio_%s_pos_%s%s_%s.dat",pidstring,typestring,switchstring,centstring);
  ofstream foutratiopos(textoutratioposname);

  char textoutsuncertposname[100];
  sprintf(textoutsuncertposname,"Text/single_suncert_%s_pos_%s%s_%s.dat",pidstring,typestring,switchstring,centstring);
  ofstream foutsuncertpos(textoutsuncertposname);

  float ptr[100], ratio[100], eratio[100];
  float eptr[100]={0};
  float error[100], derror[100];

  for(int i=0; i<100; i++)
    {
      ptr[i]=pt_syspos[i];

      float A, dA, B, dB;
      A = yield_syspos[i];
      dA = eyield_syspos[i];
      B = yield_refpos[i];
      dB = eyield_refpos[i];

      if(A>0&&B>0)
	{
	  ratio[i]= A/B;
	  eratio[i] = ratio[i]*sqrt((dA/A)**2+(dB/B)**2);
	}
      else
	{
	  ratio[i]=10;
	  eratio[i]=0;
	}
      if((ipid==1&&i<3)||(ipid==2&&i<4)||(ipid==1&&i>31))
	{
	  ratio[i]=10;
	  eratio[i]=0;
	}

      error[i] = fabs(1.0-ratio[i]);
      derror[i] = eratio[i];
      foutratiopos<<ptr[i]<<"\t"<<ratio[i]<<"\t"<<eratio[i]<<endl;
      foutsuncertpos<<ptr[i]<<"\t"<<error[i]<<"\t"<<derror[i]<<endl;
    }
  TGraphErrors *tge_ratpos = new TGraphErrors(number,ptr,ratio,eptr,eratio);
  tge_ratpos->SetMarkerStyle(kFullCircle);
  tge_ratpos->SetMarkerColor(kBlack);
  TGraphErrors *tge_errpos = new TGraphErrors(number,ptr,error,eptr,derror);
  tge_errpos->SetMarkerStyle(kFullCircle);
  tge_errpos->SetMarkerColor(kBlack);



  c1->Clear();
  c1->SetLogy(0);
  tge_ratpos->Draw("ap");
  line->Draw("same");
  //tge_ratpos->SetMaximum(2.0);
  //tge_ratpos->SetMinimum(0.0);
  tge_ratpos->SetMaximum(ratiohigh);
  tge_ratpos->SetMinimum(ratiolow);
  tge_ratpos->GetXaxis()->SetLimits(0.0,6.0);
  tge_ratpos->GetYaxis()->SetTitle("Systematic Ratio");
  tge_ratpos->GetXaxis()->SetTitle("p_{T}");
  leg_pos = new TLegend(0.58,0.78,0.88,0.88);
  leg_pos->SetFillColor(kWhite);
  leg_pos->SetBorderSize(0);
  leg_pos->AddEntry(tge_ratpos,typelongstring,"p");
  leg_pos->Draw();

  sprintf(gifname,"UFig/single_ratio_%s_pos_%s%s_%s.gif",pidstring,typestring,switchstring,centstring);
  sprintf(epsname,"UFig/single_ratio_%s_pos_%s%s_%s.eps",pidstring,typestring,switchstring,centstring);
  c1->Print(gifname);
  c1->Print(epsname);

  c1->Clear();
  tge_errpos->Draw("ap");
  line0->Draw("same");
  tge_errpos->SetMaximum(errheight);
  tge_errpos->SetMinimum(-0.1);
  tge_errpos->GetXaxis()->SetLimits(0.0,6.0);
  tge_errpos->GetYaxis()->SetTitle("Systematic Uncertainty");
  tge_errpos->GetXaxis()->SetTitle("p_{T}");
  leg_pos = new TLegend(0.58,0.78,0.88,0.88);
  leg_pos->SetFillColor(kWhite);
  leg_pos->SetBorderSize(0);
  leg_pos->AddEntry(tge_errpos,typelongstring,"p");
  leg_pos->Draw();

  sprintf(gifname,"UFig/single_suncert_%s_pos_%s%s_%s.gif",pidstring,typestring,switchstring,centstring);
  sprintf(epsname,"UFig/single_suncert_%s_pos_%s%s_%s.eps",pidstring,typestring,switchstring,centstring);
  c1->Print(gifname);
  c1->Print(epsname);


  // -- neg


  char textoutrationegname[100];
  sprintf(textoutrationegname,"Text/single_ratio_%s_neg_%s%s_%s.dat",pidstring,typestring,switchstring,centstring);
  ofstream foutrationeg(textoutrationegname);

  char textoutsuncertnegname[100];
  sprintf(textoutsuncertnegname,"Text/single_suncert_%s_neg_%s%s_%s.dat",pidstring,typestring,switchstring,centstring);
  ofstream foutsuncertneg(textoutsuncertnegname);

  float ptr[100], ratio[100], eratio[100];
  float eptr[100]={0};
  float error[100], derror[100];

  for(int i=0; i<100; i++)
    {
      ptr[i]=pt_sysneg[i];

      float A, dA, B, dB;
      A = yield_sysneg[i];
      dA = eyield_sysneg[i];
      B = yield_refneg[i];
      dB = eyield_refneg[i];

      if(A>0&&B>0)
	{
	  ratio[i]= A/B;
	  eratio[i] = ratio[i]*sqrt((dA/A)**2+(dB/B)**2);
	}
      else
	{
	  ratio[i]=10;
	  eratio[i]=0;
	}
      if((ipid==1&&i<3)||(ipid==2&&i<4))
	{
	  ratio[i]=10;
	  eratio[i]=0;
	}

      error[i] = fabs(1.0-ratio[i]);
      derror[i] = eratio[i];
      foutrationeg<<ptr[i]<<"\t"<<ratio[i]<<"\t"<<eratio[i]<<endl;
      foutsuncertneg<<ptr[i]<<"\t"<<error[i]<<"\t"<<derror[i]<<endl;
    }
  TGraphErrors *tge_ratneg = new TGraphErrors(number,ptr,ratio,eptr,eratio);
  tge_ratneg->SetMarkerStyle(kFullCircle);
  tge_ratneg->SetMarkerColor(kBlack);
  TGraphErrors *tge_errneg = new TGraphErrors(number,ptr,error,eptr,derror);
  tge_errneg->SetMarkerStyle(kFullCircle);
  tge_errneg->SetMarkerColor(kBlack);



  c1->Clear();
  c1->SetLogy(0);
  tge_ratneg->Draw("ap");
  line->Draw("same");
  //tge_ratneg->SetMaximum(2.0);
  //tge_ratneg->SetMinimum(0.0);
  tge_ratneg->SetMaximum(ratiohigh);
  tge_ratneg->SetMinimum(ratiolow);
  tge_ratneg->GetXaxis()->SetLimits(0.0,6.0);
  tge_ratneg->GetYaxis()->SetTitle("Systematic Ratio");
  tge_ratneg->GetXaxis()->SetTitle("p_{T}");
  leg_neg = new TLegend(0.58,0.78,0.88,0.88);
  leg_neg->SetFillColor(kWhite);
  leg_neg->SetBorderSize(0);
  leg_neg->AddEntry(tge_ratneg,typelongstring,"p");
  leg_neg->Draw();

  sprintf(gifname,"UFig/single_ratio_%s_neg_%s%s_%s.gif",pidstring,typestring,switchstring,centstring);
  sprintf(epsname,"UFig/single_ratio_%s_neg_%s%s_%s.eps",pidstring,typestring,switchstring,centstring);
  c1->Print(gifname);
  c1->Print(epsname);

  c1->Clear();
  tge_errneg->Draw("ap");
  line0->Draw("same");
  tge_errneg->SetMaximum(errheight);
  tge_errneg->SetMinimum(-0.1);
  tge_errneg->GetXaxis()->SetLimits(0.0,6.0);
  tge_errneg->GetYaxis()->SetTitle("Systematic Uncertainty");
  tge_errneg->GetXaxis()->SetTitle("p_{T}");
  leg_neg = new TLegend(0.58,0.78,0.88,0.88);
  leg_neg->SetFillColor(kWhite);
  leg_neg->SetBorderSize(0);
  leg_neg->AddEntry(tge_errneg,typelongstring,"p");
  leg_neg->Draw();

  sprintf(gifname,"UFig/single_suncert_%s_neg_%s%s_%s.gif",pidstring,typestring,switchstring,centstring);
  sprintf(epsname,"UFig/single_suncert_%s_neg_%s%s_%s.eps",pidstring,typestring,switchstring,centstring);
  c1->Print(gifname);
  c1->Print(epsname);


} // step3



void step4(int ipid=0, int centid=0)
{

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetBorderMode(0);
  c1->SetFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->SetFrameFillColor(kWhite);

  TLine *line = new TLine(0.0,0.0,6.0,0.0);

  TF1 *fun = new TF1("fun","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,6.0);

  char pidstring[5];
  sprintf(pidstring,"pion"); // "default"
  if(ipid==0) sprintf(pidstring,"pion");
  if(ipid==1) sprintf(pidstring,"kaon");
  if(ipid==2) sprintf(pidstring,"prot");

  // char centstring[5];
  // if(centid==0) sprintf(centstring,"0088");
  // else if(centid==1) sprintf(centstring,"0020");
  // else if(centid==2) sprintf(centstring,"2040");
  // else if(centid==3) sprintf(centstring,"4060");
  // else if(centid==4) sprintf(centstring,"6088");
  // else {cout<<"you gonna die"<<endl; return;}

  char centstring[10];
  if(centid==0) sprintf(centstring,"cent0088");
  else if(centid==1) sprintf(centstring,"cent0020");
  else if(centid==2) sprintf(centstring,"cent2040");
  else if(centid==3) sprintf(centstring,"cent4060");
  else if(centid==4) sprintf(centstring,"cent6088");
  else {cout<<"you gonna die"<<endl; return;}



  char fnameinpossys_1a[100];
  char fnameinnegsys_1a[100];
  sprintf(fnameinpossys_1a,"Text/single_suncert_%s_pos_dcfcA_%s.dat",pidstring,centstring);
  sprintf(fnameinnegsys_1a,"Text/single_suncert_%s_neg_dcfcA_%s.dat",pidstring,centstring);
  ifstream finpossys_1a;
  ifstream finnegsys_1a;
  finpossys_1a.open(fnameinpossys_1a);
  finnegsys_1a.open(fnameinnegsys_1a);

  char fnameinpossys_2a[100];
  char fnameinnegsys_2a[100];
  sprintf(fnameinpossys_2a,"Text/single_suncert_%s_pos_dzedA_%s.dat",pidstring,centstring);
  sprintf(fnameinnegsys_2a,"Text/single_suncert_%s_neg_dzedA_%s.dat",pidstring,centstring);
  ifstream finpossys_2a;
  ifstream finnegsys_2a;
  finpossys_2a.open(fnameinpossys_2a);
  finnegsys_2a.open(fnameinnegsys_2a);

  char fnameinpossys_3a[100];
  char fnameinnegsys_3a[100];
  sprintf(fnameinpossys_3a,"Text/single_suncert_%s_pos_pc3mA_%s.dat",pidstring,centstring);
  sprintf(fnameinnegsys_3a,"Text/single_suncert_%s_neg_pc3mA_%s.dat",pidstring,centstring);
  ifstream finpossys_3a;
  ifstream finnegsys_3a;
  finpossys_3a.open(fnameinpossys_3a);
  finnegsys_3a.open(fnameinnegsys_3a);

  char fnameinpossys_4a[100];
  char fnameinnegsys_4a[100];
  sprintf(fnameinpossys_4a,"Text/single_suncert_%s_pos_tfwmA_%s.dat",pidstring,centstring);
  sprintf(fnameinnegsys_4a,"Text/single_suncert_%s_neg_tfwmA_%s.dat",pidstring,centstring);
  ifstream finpossys_4a;
  ifstream finnegsys_4a;
  finpossys_4a.open(fnameinpossys_4a);
  finnegsys_4a.open(fnameinnegsys_4a);

  char fnameinpossys_5a[100];
  char fnameinnegsys_5a[100];
  sprintf(fnameinpossys_5a,"Text/single_suncert_%s_pos_pc1fA_%s.dat",pidstring,centstring);
  sprintf(fnameinnegsys_5a,"Text/single_suncert_%s_neg_pc1fA_%s.dat",pidstring,centstring);
  ifstream finpossys_5a;
  ifstream finnegsys_5a;
  finpossys_5a.open(fnameinpossys_5a);
  finnegsys_5a.open(fnameinnegsys_5a);

  char fnameinpossys_6a[100];
  char fnameinnegsys_6a[100];
  sprintf(fnameinpossys_6a,"Text/single_suncert_%s_pos_pc3fA_%s.dat",pidstring,centstring);
  sprintf(fnameinnegsys_6a,"Text/single_suncert_%s_neg_pc3fA_%s.dat",pidstring,centstring);
  ifstream finpossys_6a;
  ifstream finnegsys_6a;
  finpossys_6a.open(fnameinpossys_6a);
  finnegsys_6a.open(fnameinnegsys_6a);

  char fnameinpossys_7a[100];
  char fnameinnegsys_7a[100];
  sprintf(fnameinpossys_7a,"Text/single_suncert_%s_pos_spidA_%s.dat",pidstring,centstring);
  sprintf(fnameinnegsys_7a,"Text/single_suncert_%s_neg_spidA_%s.dat",pidstring,centstring);
  ifstream finpossys_7a;
  ifstream finnegsys_7a;
  finpossys_7a.open(fnameinpossys_7a);
  finnegsys_7a.open(fnameinnegsys_7a);

  char fnameinpossys_1b[100];
  char fnameinnegsys_1b[100];
  sprintf(fnameinpossys_1b,"Text/single_suncert_%s_pos_dcfcB_%s.dat",pidstring,centstring);
  sprintf(fnameinnegsys_1b,"Text/single_suncert_%s_neg_dcfcB_%s.dat",pidstring,centstring);
  ifstream finpossys_1b;
  ifstream finnegsys_1b;
  finpossys_1b.open(fnameinpossys_1b);
  finnegsys_1b.open(fnameinnegsys_1b);

  char fnameinpossys_7b[100];
  char fnameinnegsys_7b[100];
  sprintf(fnameinpossys_7b,"Text/single_suncert_%s_pos_spidB_%s.dat",pidstring,centstring);
  sprintf(fnameinnegsys_7b,"Text/single_suncert_%s_neg_spidB_%s.dat",pidstring,centstring);
  ifstream finpossys_7b;
  ifstream finnegsys_7b;
  finpossys_7b.open(fnameinpossys_7b);
  finnegsys_7b.open(fnameinnegsys_7b);

  float pt_pos_1a[100],pt_pos_2a[100],pt_pos_3a[100],pt_pos_4a[100],pt_pos_5a[100],pt_pos_6a[100],pt_pos_7a[100],pt_pos_1b[100],pt_pos_7b[100];
  float un_pos_1a[100],un_pos_2a[100],un_pos_3a[100],un_pos_4a[100],un_pos_5a[100],un_pos_6a[100],un_pos_7a[100],un_pos_1b[100],un_pos_7b[100];
  float er_pos_1a[100],er_pos_2a[100],er_pos_3a[100],er_pos_4a[100],er_pos_5a[100],er_pos_6a[100],er_pos_7a[100],er_pos_1b[100],er_pos_7b[100];
  float pt_neg_1a[100],pt_neg_2a[100],pt_neg_3a[100],pt_neg_4a[100],pt_neg_5a[100],pt_neg_6a[100],pt_neg_7a[100],pt_neg_1b[100],pt_neg_7b[100];
  float un_neg_1a[100],un_neg_2a[100],un_neg_3a[100],un_neg_4a[100],un_neg_5a[100],un_neg_6a[100],un_neg_7a[100],un_neg_1b[100],un_neg_7b[100];
  float er_neg_1a[100],er_neg_2a[100],er_neg_3a[100],er_neg_4a[100],er_neg_5a[100],er_neg_6a[100],er_neg_7a[100],er_neg_1b[100],er_neg_7b[100];
  float ept[100]={0};



  for(int i=0; i<100; i++)
    {

      finpossys_1a>>pt_pos_1a[i]>>un_pos_1a[i]>>er_pos_1a[i];
      finpossys_2a>>pt_pos_2a[i]>>un_pos_2a[i]>>er_pos_2a[i];
      finpossys_3a>>pt_pos_3a[i]>>un_pos_3a[i]>>er_pos_3a[i];
      finpossys_4a>>pt_pos_4a[i]>>un_pos_4a[i]>>er_pos_4a[i];
      finpossys_5a>>pt_pos_5a[i]>>un_pos_5a[i]>>er_pos_5a[i];
      finpossys_6a>>pt_pos_6a[i]>>un_pos_6a[i]>>er_pos_6a[i];
      finpossys_7a>>pt_pos_7a[i]>>un_pos_7a[i]>>er_pos_7a[i];
      finpossys_1b>>pt_pos_1b[i]>>un_pos_1b[i]>>er_pos_1b[i];
      finpossys_7b>>pt_pos_7b[i]>>un_pos_7b[i]>>er_pos_7b[i];

      finnegsys_1a>>pt_neg_1a[i]>>un_neg_1a[i]>>er_neg_1a[i];
      finnegsys_2a>>pt_neg_2a[i]>>un_neg_2a[i]>>er_neg_2a[i];
      finnegsys_3a>>pt_neg_3a[i]>>un_neg_3a[i]>>er_neg_3a[i];
      finnegsys_4a>>pt_neg_4a[i]>>un_neg_4a[i]>>er_neg_4a[i];
      finnegsys_5a>>pt_neg_5a[i]>>un_neg_5a[i]>>er_neg_5a[i];
      finnegsys_6a>>pt_neg_6a[i]>>un_neg_6a[i]>>er_neg_6a[i];
      finnegsys_7a>>pt_neg_7a[i]>>un_neg_7a[i]>>er_neg_7a[i];
      finnegsys_1b>>pt_neg_1b[i]>>un_neg_1b[i]>>er_neg_1b[i];
      finnegsys_7b>>pt_neg_7b[i]>>un_neg_7b[i]>>er_neg_7b[i];

    }



  finpossys_1a.close();
  finpossys_2a.close();
  finpossys_3a.close();
  finpossys_4a.close();
  finpossys_5a.close();
  finpossys_6a.close();
  finpossys_7a.close();
  finpossys_1b.close();
  finpossys_7b.close();

  finnegsys_1a.close();
  finnegsys_2a.close();
  finnegsys_3a.close();
  finnegsys_4a.close();
  finnegsys_5a.close();
  finnegsys_6a.close();
  finnegsys_7a.close();
  finnegsys_1b.close();
  finnegsys_7b.close();



  // ---
  // ---
  // ---

  float pt_pos_sumA[100];
  float un_pos_sumA[100];
  float er_pos_sumA[100];
  float pt_neg_sumA[100];
  float un_neg_sumA[100];
  float er_neg_sumA[100];

  for(int i=0; i<100; i++)
    {
      pt_pos_sumA[i] = pt_pos_1a[i]; // arbitrary, all same
      un_pos_sumA[i] = sqrt(
			    un_pos_1a[i]**2 + 
			    un_pos_2a[i]**2 + 
			    un_pos_3a[i]**2 + 
			    un_pos_4a[i]**2 + 
			    un_pos_5a[i]**2 + 
			    un_pos_6a[i]**2 + 
			    un_pos_7a[i]**2);
      er_pos_sumA[i] = sqrt(
			    er_pos_1a[i]**2 + 
			    er_pos_2a[i]**2 + 
			    er_pos_3a[i]**2 + 
			    er_pos_4a[i]**2 + 
			    er_pos_5a[i]**2 + 
			    er_pos_6a[i]**2 + 
			    er_pos_7a[i]**2)/7.0;

    }

  TGraphErrors *tge_sumA = new TGraphErrors(100,pt_pos_sumA,un_pos_sumA,ept,er_pos_sumA);
  tge_sumA->SetMarkerStyle(kFullCircle);
  tge_sumA->SetMarkerColor(kBlack);
  tge_sumA->Draw("ap");
  line->Draw("same");
  // tge_sumA->Fit(fun,"R");
  // if(ipid==1) tge_sumA->Fit(fun,"","",0.3,4.5);
  // if(ipid==2) tge_sumA->Fit(fun,"","",0.4,6.0);
  tge_sumA->SetMaximum(0.5);
  tge_sumA->SetMinimum(-0.1);
  tge_sumA->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumA->GetXaxis()->SetTitle("p_{T}");
  tge_sumA->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameA[100];
  sprintf(fignameA,"AFig/sys_uncert_pos_%s_sumA_%s.png",pidstring,centstring);
  c1->Print(fignameA);
  sprintf(fignameA,"AFig/sys_uncert_pos_%s_sumA_%s.eps",pidstring,centstring);
  c1->Print(fignameA);

  //continue; // TEMP

  float pt_pos_sumB[100];
  float un_pos_sumB[100];
  float er_pos_sumB[100];
  float pt_neg_sumB[100];
  float un_neg_sumB[100];
  float er_neg_sumB[100];

  for(int i=0; i<100; i++)
    {
      pt_pos_sumB[i] = pt_pos_1a[i]; // arbitrary, all same
      un_pos_sumB[i] = sqrt(
			    un_pos_1b[i]**2 + 
			    un_pos_2a[i]**2 + 
			    un_pos_3a[i]**2 + 
			    un_pos_4a[i]**2 + 
			    un_pos_5a[i]**2 + 
			    un_pos_6a[i]**2 + 
			    un_pos_7a[i]**2);
      er_pos_sumB[i] = sqrt(
			    er_pos_1b[i]**2 + 
			    er_pos_2a[i]**2 + 
			    er_pos_3a[i]**2 + 
			    er_pos_4a[i]**2 + 
			    er_pos_5a[i]**2 + 
			    er_pos_6a[i]**2 + 
			    er_pos_7a[i]**2)/7.0;

    }

  TGraphErrors *tge_sumB = new TGraphErrors(100,pt_pos_sumB,un_pos_sumB,ept,er_pos_sumB);
  tge_sumB->SetMarkerStyle(kFullCircle);
  tge_sumB->SetMarkerColor(kBlack);
  tge_sumB->Draw("ap");
  line->Draw("same");
  // tge_sumB->Fit(fun,"R");
  // if(ipid==1) tge_sumB->Fit(fun,"","",0.3,4.5);
  // if(ipid==2) tge_sumB->Fit(fun,"","",0.4,6.0);
  tge_sumB->SetMaximum(0.5);
  tge_sumB->SetMinimum(-0.1);
  tge_sumB->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumB->GetXaxis()->SetTitle("p_{T}");
  tge_sumB->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameB[100];
  sprintf(fignameB,"AFig/sys_uncert_pos_%s_sumB_%s.png",pidstring,centstring);
  c1->Print(fignameB);
  sprintf(fignameB,"AFig/sys_uncert_pos_%s_sumB_%s.eps",pidstring,centstring);
  c1->Print(fignameB);



  float pt_pos_sumAa[100];
  float un_pos_sumAa[100];
  float er_pos_sumAa[100];
  float pt_neg_sumAa[100];
  float un_neg_sumAa[100];
  float er_neg_sumAa[100];

  for(int i=0; i<100; i++)
    {
      pt_pos_sumAa[i] = pt_pos_1a[i]; // arbitrary, all same
      un_pos_sumAa[i] = sqrt(
			    un_pos_1a[i]**2 + 
			    un_pos_2a[i]**2 + 
			    un_pos_3a[i]**2 + 
			    un_pos_4a[i]**2 + 
			    un_pos_5a[i]**2 + 
			    un_pos_6a[i]**2 + 
			    un_pos_7a[i]**2 + 
			    un_pos_7b[i]**2);
      er_pos_sumAa[i] = sqrt(
			    er_pos_1a[i]**2 + 
			    er_pos_2a[i]**2 + 
			    er_pos_3a[i]**2 + 
			    er_pos_4a[i]**2 + 
			    er_pos_5a[i]**2 + 
			    er_pos_6a[i]**2 + 
			    er_pos_7a[i]**2 + 
			    er_pos_7b[i]**2)/7.0;

    }

  TGraphErrors *tge_sumAa = new TGraphErrors(100,pt_pos_sumAa,un_pos_sumAa,ept,er_pos_sumAa);
  tge_sumAa->SetMarkerStyle(kFullCircle);
  tge_sumAa->SetMarkerColor(kBlack);
  tge_sumAa->Draw("ap");
  line->Draw("same");
  // tge_sumAa->Fit(fun,"R");
  // if(ipid==1) tge_sumAa->Fit(fun,"","",0.3,4.0);
  // if(ipid==2) tge_sumAa->Fit(fun,"","",0.4,6.0);
  tge_sumAa->SetMaximum(0.5);
  tge_sumAa->SetMinimum(-0.1);
  tge_sumAa->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumAa->GetXaxis()->SetTitle("p_{T}");
  tge_sumAa->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameAa[100];
  sprintf(fignameAa,"AFig/sys_uncert_pos_%s_sumAa_%s.png",pidstring,centstring);
  c1->Print(fignameAa);
  sprintf(fignameAa,"AFig/sys_uncert_pos_%s_sumAa_%s.eps",pidstring,centstring);
  c1->Print(fignameAa);



  float pt_pos_sumBb[100];
  float un_pos_sumBb[100];
  float er_pos_sumBb[100];
  float pt_neg_sumBb[100];
  float un_neg_sumBb[100];
  float er_neg_sumBb[100];

  for(int i=0; i<100; i++)
    {
      pt_pos_sumBb[i] = pt_pos_1a[i]; // arbitrary, all same
      un_pos_sumBb[i] = sqrt(
			    un_pos_1b[i]**2 + 
			    un_pos_2a[i]**2 + 
			    un_pos_3a[i]**2 + 
			    un_pos_4a[i]**2 + 
			    un_pos_5a[i]**2 + 
			    un_pos_6a[i]**2 + 
			    un_pos_7a[i]**2 + 
			    un_pos_7b[i]**2);
      er_pos_sumBb[i] = sqrt(
			    er_pos_1b[i]**2 + 
			    er_pos_2a[i]**2 + 
			    er_pos_3a[i]**2 + 
			    er_pos_4a[i]**2 + 
			    er_pos_5a[i]**2 + 
			    er_pos_6a[i]**2 + 
			    er_pos_7a[i]**2 + 
			    er_pos_7b[i]**2)/7.0;

    }

  TGraphErrors *tge_sumBb = new TGraphErrors(100,pt_pos_sumBb,un_pos_sumBb,ept,er_pos_sumBb);
  tge_sumBb->SetMarkerStyle(kFullCircle);
  tge_sumBb->SetMarkerColor(kBlack);
  tge_sumBb->Draw("ap");
  line->Draw("same");
  // tge_sumBb->Fit(fun,"R");
  // if(ipid==1) tge_sumBb->Fit(fun,"","",0.3,4.0);
  // if(ipid==2) tge_sumBb->Fit(fun,"","",0.4,6.0);
  tge_sumBb->SetMaximum(0.5);
  tge_sumBb->SetMinimum(-0.1);
  tge_sumBb->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumBb->GetXaxis()->SetTitle("p_{T}");
  tge_sumBb->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameBb[100];
  sprintf(fignameBb,"AFig/sys_uncert_pos_%s_sumBb_%s.png",pidstring,centstring);
  c1->Print(fignameBb);
  sprintf(fignameBb,"AFig/sys_uncert_pos_%s_sumBb_%s.eps",pidstring,centstring);
  c1->Print(fignameBb);





  // ---
  // ---
  // ---

  float pt_neg_sumA[100];
  float un_neg_sumA[100];
  float er_neg_sumA[100];
  float pt_neg_sumA[100];
  float un_neg_sumA[100];
  float er_neg_sumA[100];

  for(int i=0; i<100; i++)
    {
      pt_neg_sumA[i] = pt_neg_1a[i]; // arbitrary, all same
      un_neg_sumA[i] = sqrt(
			    un_neg_1a[i]**2 + 
			    un_neg_2a[i]**2 + 
			    un_neg_3a[i]**2 + 
			    un_neg_4a[i]**2 + 
			    un_neg_5a[i]**2 + 
			    un_neg_6a[i]**2 + 
			    un_neg_7a[i]**2);
      er_neg_sumA[i] = sqrt(
			    er_neg_1a[i]**2 + 
			    er_neg_2a[i]**2 + 
			    er_neg_3a[i]**2 + 
			    er_neg_4a[i]**2 + 
			    er_neg_5a[i]**2 + 
			    er_neg_6a[i]**2 + 
			    er_neg_7a[i]**2)/7.0;

    }

  TGraphErrors *tge_sumA = new TGraphErrors(100,pt_neg_sumA,un_neg_sumA,ept,er_neg_sumA);
  tge_sumA->SetMarkerStyle(kFullCircle);
  tge_sumA->SetMarkerColor(kBlack);
  tge_sumA->Draw("ap");
  line->Draw("same");
  // tge_sumA->Fit(fun,"R");
  // if(ipid==1) tge_sumA->Fit(fun,"","",0.3,4.5);
  // if(ipid==2) tge_sumA->Fit(fun,"","",0.4,6.0);
  tge_sumA->SetMaximum(0.5);
  tge_sumA->SetMinimum(-0.1);
  tge_sumA->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumA->GetXaxis()->SetTitle("p_{T}");
  tge_sumA->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameA[100];
  sprintf(fignameA,"AFig/sys_uncert_neg_%s_sumA_%s.png",pidstring,centstring);
  c1->Print(fignameA);
  sprintf(fignameA,"AFig/sys_uncert_neg_%s_sumA_%s.eps",pidstring,centstring);
  c1->Print(fignameA);



  float pt_neg_sumB[100];
  float un_neg_sumB[100];
  float er_neg_sumB[100];
  float pt_neg_sumB[100];
  float un_neg_sumB[100];
  float er_neg_sumB[100];

  for(int i=0; i<100; i++)
    {
      pt_neg_sumB[i] = pt_neg_1a[i]; // arbitrary, all same
      un_neg_sumB[i] = sqrt(
			    un_neg_1b[i]**2 + 
			    un_neg_2a[i]**2 + 
			    un_neg_3a[i]**2 + 
			    un_neg_4a[i]**2 + 
			    un_neg_5a[i]**2 + 
			    un_neg_6a[i]**2 + 
			    un_neg_7a[i]**2);
      er_neg_sumB[i] = sqrt(
			    er_neg_1b[i]**2 + 
			    er_neg_2a[i]**2 + 
			    er_neg_3a[i]**2 + 
			    er_neg_4a[i]**2 + 
			    er_neg_5a[i]**2 + 
			    er_neg_6a[i]**2 + 
			    er_neg_7a[i]**2)/7.0;

    }

  TGraphErrors *tge_sumB = new TGraphErrors(100,pt_neg_sumB,un_neg_sumB,ept,er_neg_sumB);
  tge_sumB->SetMarkerStyle(kFullCircle);
  tge_sumB->SetMarkerColor(kBlack);
  tge_sumB->Draw("ap");
  line->Draw("same");
  // tge_sumB->Fit(fun,"R");
  // if(ipid==1) tge_sumB->Fit(fun,"","",0.3,4.5);
  // if(ipid==2) tge_sumB->Fit(fun,"","",0.4,6.0);
  tge_sumB->SetMaximum(0.5);
  tge_sumB->SetMinimum(-0.1);
  tge_sumB->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumB->GetXaxis()->SetTitle("p_{T}");
  tge_sumB->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameB[100];
  sprintf(fignameB,"AFig/sys_uncert_neg_%s_sumB_%s.png",pidstring,centstring);
  c1->Print(fignameB);
  sprintf(fignameB,"AFig/sys_uncert_neg_%s_sumB_%s.eps",pidstring,centstring);
  c1->Print(fignameB);



  float pt_neg_sumAa[100];
  float un_neg_sumAa[100];
  float er_neg_sumAa[100];
  float pt_neg_sumAa[100];
  float un_neg_sumAa[100];
  float er_neg_sumAa[100];

  for(int i=0; i<100; i++)
    {
      pt_neg_sumAa[i] = pt_neg_1a[i]; // arbitrary, all same
      un_neg_sumAa[i] = sqrt(
			    un_neg_1a[i]**2 + 
			    un_neg_2a[i]**2 + 
			    un_neg_3a[i]**2 + 
			    un_neg_4a[i]**2 + 
			    un_neg_5a[i]**2 + 
			    un_neg_6a[i]**2 + 
			    un_neg_7a[i]**2 + 
			    un_neg_7b[i]**2);
      er_neg_sumAa[i] = sqrt(
			    er_neg_1a[i]**2 + 
			    er_neg_2a[i]**2 + 
			    er_neg_3a[i]**2 + 
			    er_neg_4a[i]**2 + 
			    er_neg_5a[i]**2 + 
			    er_neg_6a[i]**2 + 
			    er_neg_7a[i]**2 + 
			    er_neg_7b[i]**2)/7.0;

    }

  TGraphErrors *tge_sumAa = new TGraphErrors(100,pt_neg_sumAa,un_neg_sumAa,ept,er_neg_sumAa);
  tge_sumAa->SetMarkerStyle(kFullCircle);
  tge_sumAa->SetMarkerColor(kBlack);
  tge_sumAa->Draw("ap");
  line->Draw("same");
  // tge_sumAa->Fit(fun,"R");
  // if(ipid==1) tge_sumAa->Fit(fun,"","",0.3,4.0);
  // if(ipid==2) tge_sumAa->Fit(fun,"","",0.4,6.0);
  tge_sumAa->SetMaximum(0.5);
  tge_sumAa->SetMinimum(-0.1);
  tge_sumAa->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumAa->GetXaxis()->SetTitle("p_{T}");
  tge_sumAa->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameAa[100];
  sprintf(fignameAa,"AFig/sys_uncert_neg_%s_sumAa_%s.png",pidstring,centstring);
  c1->Print(fignameAa);
  sprintf(fignameAa,"AFig/sys_uncert_neg_%s_sumAa_%s.eps",pidstring,centstring);
  c1->Print(fignameAa);



  float pt_neg_sumBb[100];
  float un_neg_sumBb[100];
  float er_neg_sumBb[100];
  float pt_neg_sumBb[100];
  float un_neg_sumBb[100];
  float er_neg_sumBb[100];

  for(int i=0; i<100; i++)
    {
      pt_neg_sumBb[i] = pt_neg_1a[i]; // arbitrary, all same
      un_neg_sumBb[i] = sqrt(
			    un_neg_1b[i]**2 + 
			    un_neg_2a[i]**2 + 
			    un_neg_3a[i]**2 + 
			    un_neg_4a[i]**2 + 
			    un_neg_5a[i]**2 + 
			    un_neg_6a[i]**2 + 
			    un_neg_7a[i]**2 + 
			    un_neg_7b[i]**2);
      er_neg_sumBb[i] = sqrt(
			    er_neg_1b[i]**2 + 
			    er_neg_2a[i]**2 + 
			    er_neg_3a[i]**2 + 
			    er_neg_4a[i]**2 + 
			    er_neg_5a[i]**2 + 
			    er_neg_6a[i]**2 + 
			    er_neg_7a[i]**2 + 
			    er_neg_7b[i]**2)/7.0;

    }

  TGraphErrors *tge_sumBb = new TGraphErrors(100,pt_neg_sumBb,un_neg_sumBb,ept,er_neg_sumBb);
  tge_sumBb->SetMarkerStyle(kFullCircle);
  tge_sumBb->SetMarkerColor(kBlack);
  tge_sumBb->Draw("ap");
  line->Draw("same");
  // tge_sumBb->Fit(fun,"R");
  // if(ipid==1) tge_sumBb->Fit(fun,"","",0.3,4.0);
  // if(ipid==2) tge_sumBb->Fit(fun,"","",0.4,6.0);
  tge_sumBb->SetMaximum(0.5);
  tge_sumBb->SetMinimum(-0.1);
  tge_sumBb->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumBb->GetXaxis()->SetTitle("p_{T}");
  tge_sumBb->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameBb[100];
  sprintf(fignameBb,"AFig/sys_uncert_neg_%s_sumBb_%s.png",pidstring,centstring);
  c1->Print(fignameBb);
  sprintf(fignameBb,"AFig/sys_uncert_neg_%s_sumBb_%s.eps",pidstring,centstring);
  c1->Print(fignameBb);


} // step4


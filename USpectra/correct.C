void correct()
{

  cout<<"hello and welcome!"<<endl;
  cout<<"this is a new for Run8 spectra correction macro"<<endl;
  cout<<"based on the histogram division method."<<endl;
  cout<<"it also does the bin width correction, 1/pT correction,"<<endl;
  cout<<"and normalization constants."<<endl;

  //doit();

  //exit();

  for(int icent=0; icent<5; icent++)
    {
      for(int ipid=0; ipid<6; ipid++)
	{
	  for(int isec=0; isec<3; isec++)
	    {
	      doit(isec,ipid,icent);
	      //cout<<"doit("<<isec<<","<<ipid<<","<<icent<<");"<<endl;
	    }
	}
    }




  cout<<"all done!  i hope you have a great day!"<<endl;

}

void doit(int sector=0, int pid=0, int centid=0)
{

  // TCanvas used for printing diagnostic figures
  TCanvas *c1 = new TCanvas();



  //TFile *f_real_pp = TFile::Open("RealFiles/outlow_plusplus.root");
  TFile *f_real_pp = TFile::Open("RealFiles/outnew_plusplus.root");
  TFile *f_simpion_pp = TFile::Open("SimFiles/pion/simsum_pp.root");
  TFile *f_simkaon_pp = TFile::Open("SimFiles/kaon/simsum_pp.root");
  TFile *f_simproton_pp = TFile::Open("SimFiles/proton/simsum_pp.root");

  //TFile *f_real_mm = TFile::Open("RealFiles/outlow_minusminus.root");
  TFile *f_real_mm = TFile::Open("RealFiles/outnew_minusminus.root");
  TFile *f_simpion_mm = TFile::Open("SimFiles/pion/simsum_mm.root");
  TFile *f_simkaon_mm = TFile::Open("SimFiles/kaon/simsum_mm.root");
  TFile *f_simproton_mm = TFile::Open("SimFiles/proton/simsum_mm.root");

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");

  char centstring[10];
  sprintf(centstring,"0088"); // "default"
  if(centid==0) sprintf(centstring,"0005");
  if(centid==1) sprintf(centstring,"2040");
  if(centid==2) sprintf(centstring,"4060");
  if(centid==3) sprintf(centstring,"5088");
  if(centid==4) sprintf(centstring,"0088");

  char bigcentstring[50];
  sprintf(bigcentstring,"0088"); // "default"
  if(centid==0) sprintf(bigcentstring,"0-20%% cent");
  if(centid==1) sprintf(bigcentstring,"20-40%% cent");
  if(centid==2) sprintf(bigcentstring,"40-60%% cent");
  if(centid==3) sprintf(bigcentstring,"60-88%% cent");
  if(centid==4) sprintf(bigcentstring,"MinBias");


  char name_real_tofw_pos_pp[50];
  char name_sim_tofw_pos_pp[50];
  char name_real_tofw_neg_pp[50];
  char name_sim_tofw_neg_pp[50];

  char name_real_tofw_pos_mm[50];
  char name_sim_tofw_pos_mm[50];
  char name_real_tofw_neg_mm[50];
  char name_sim_tofw_neg_mm[50];

  sprintf(name_real_tofw_pos_pp,"ptpid_%s_pos_%d_dis_cent%s",sectorstring,pid,centstring);
  sprintf(name_sim_tofw_pos_pp,"ptpid_%s_pos_%d_dis",sectorstring,pid);
  sprintf(name_real_tofw_neg_pp,"ptpid_%s_neg_%d_dis_cent%s",sectorstring,pid,centstring);
  sprintf(name_sim_tofw_neg_pp,"ptpid_%s_neg_%d_dis",sectorstring,pid);

  sprintf(name_real_tofw_pos_mm,"ptpid_%s_pos_%d_dis_cent%s",sectorstring,pid,centstring);
  sprintf(name_sim_tofw_pos_mm,"ptpid_%s_pos_%d_dis",sectorstring,pid);
  sprintf(name_real_tofw_neg_mm,"ptpid_%s_neg_%d_dis_cent%s",sectorstring,pid,centstring);
  sprintf(name_sim_tofw_neg_mm,"ptpid_%s_neg_%d_dis",sectorstring,pid);

  TH1F *h_real_tofw_pos_pp = f_real_pp->Get(name_real_tofw_pos_pp);
  TH1F *h_real_tofw_neg_pp = f_real_pp->Get(name_real_tofw_neg_pp);
  TH1F *h_real_tofw_pos_mm = f_real_mm->Get(name_real_tofw_pos_mm);
  TH1F *h_real_tofw_neg_mm = f_real_mm->Get(name_real_tofw_neg_mm);

  if(pid==0||pid==1)
    {
      TH1F *h_sim_tofw_pos_pp = f_simpion_pp->Get(name_sim_tofw_pos_pp);
      TH1F *h_sim_tofw_neg_pp = f_simpion_pp->Get(name_sim_tofw_neg_pp);
      TH1F *h_sim_tofw_pos_mm = f_simpion_mm->Get(name_sim_tofw_pos_mm);
      TH1F *h_sim_tofw_neg_mm = f_simpion_mm->Get(name_sim_tofw_neg_mm);
    }
  else if(pid==2||pid==3)
    {
      TH1F *h_sim_tofw_pos_pp = f_simkaon_pp->Get(name_sim_tofw_pos_pp);
      TH1F *h_sim_tofw_neg_pp = f_simkaon_pp->Get(name_sim_tofw_neg_pp);
      TH1F *h_sim_tofw_pos_mm = f_simkaon_mm->Get(name_sim_tofw_pos_mm);
      TH1F *h_sim_tofw_neg_mm = f_simkaon_mm->Get(name_sim_tofw_neg_mm);
    }
  else if(pid==4||pid==5)
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
  h_sim_tofw_pos_pp->Sumw2();
  h_real_tofw_neg_pp->Sumw2();
  h_sim_tofw_neg_pp->Sumw2();

  h_real_tofw_pos_mm->Sumw2();
  h_sim_tofw_pos_mm->Sumw2();
  h_real_tofw_neg_mm->Sumw2();
  h_sim_tofw_neg_mm->Sumw2();


  // divide Real histogram by Sim histogram
  
  // h_real_tofw_pos_pp->Divide(h_sim_tofw_pos_pp);
  // h_real_tofw_neg_pp->Divide(h_sim_tofw_neg_pp);
  // h_real_tofw_pos_mm->Divide(h_sim_tofw_pos_mm);
  // h_real_tofw_neg_mm->Divide(h_sim_tofw_neg_mm);

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

  h_sim_tofw_pos_pp->Multiply(dummy,(1.0/simconst));
  h_sim_tofw_neg_pp->Multiply(dummy,(1.0/simconst));
  h_sim_tofw_pos_mm->Multiply(dummy,(1.0/simconst));
  h_sim_tofw_neg_mm->Multiply(dummy,(1.0/simconst));

  TH1F *hunit = new TH1F("hunit","",100,0,10);
  for(int i=0; i<100; i++)
    {
      hunit->SetBinContent(i+1,1.0);
      hunit->SetBinError(i+1,0.0);
    }

  TH1F *hh_sim_tofw_pos_pp = new TH1F("hh_sim_tofw_pos_pp","",100,0,10);
  TH1F *hh_sim_tofw_neg_pp = new TH1F("hh_sim_tofw_neg_pp","",100,0,10);
  TH1F *hh_sim_tofw_pos_mm = new TH1F("hh_sim_tofw_pos_mm","",100,0,10);
  TH1F *hh_sim_tofw_neg_mm = new TH1F("hh_sim_tofw_neg_mm","",100,0,10);

  hh_sim_tofw_pos_pp->Sumw2();
  hh_sim_tofw_neg_pp->Sumw2();
  hh_sim_tofw_pos_mm->Sumw2();
  hh_sim_tofw_neg_mm->Sumw2();
  hh_sim_tofw_pos_pp->Divide(hunit,h_sim_tofw_pos_pp);
  hh_sim_tofw_neg_pp->Divide(hunit,h_sim_tofw_neg_pp);
  hh_sim_tofw_pos_mm->Divide(hunit,h_sim_tofw_pos_mm);
  hh_sim_tofw_neg_mm->Divide(hunit,h_sim_tofw_neg_mm);

  // TF1 *fit_pos_pp = new TF1("fit_pos_pp","[0]+[1]/x+[2]/x/x+[3]/x/x/x+[4]*x+[5]*x*x+[6]*x*x*x",0.2,10);
  // TF1 *fit_neg_pp = new TF1("fit_neg_pp","[0]+[1]/x+[2]/x/x+[3]/x/x/x+[4]*x+[5]*x*x+[6]*x*x*x",0.2,10);
  // TF1 *fit_pos_mm = new TF1("fit_pos_mm","[0]+[1]/x+[2]/x/x+[3]/x/x/x+[4]*x+[5]*x*x+[6]*x*x*x",0.2,10);
  // TF1 *fit_neg_mm = new TF1("fit_neg_mm","[0]+[1]/x+[2]/x/x+[3]/x/x/x+[4]*x+[5]*x*x+[6]*x*x*x",0.2,10);
  TF1 *fit_pos_pp = new TF1("fit_pos_pp","[0]+[1]/x+[2]/x/x+[3]/x/x/x+[4]/x/x/x/x+[5]*x+[6]*x*x+[7]*x*x*x+[8]*x*x*x*x",0.2,10);
  TF1 *fit_neg_pp = new TF1("fit_neg_pp","[0]+[1]/x+[2]/x/x+[3]/x/x/x+[4]/x/x/x/x+[5]*x+[6]*x*x+[7]*x*x*x+[8]*x*x*x*x",0.2,10);
  TF1 *fit_pos_mm = new TF1("fit_pos_mm","[0]+[1]/x+[2]/x/x+[3]/x/x/x+[4]/x/x/x/x+[5]*x+[6]*x*x+[7]*x*x*x+[8]*x*x*x*x",0.2,10);
  TF1 *fit_neg_mm = new TF1("fit_neg_mm","[0]+[1]/x+[2]/x/x+[3]/x/x/x+[4]/x/x/x/x+[5]*x+[6]*x*x+[7]*x*x*x+[8]*x*x*x*x",0.2,10);


  char fignamepospp[100];
  char fignamenegpp[100];
  char fignameposmm[100];
  char fignamenegmm[100];

  sprintf(fignamepospp,"CorrectionFactors/ptpid_%s_pos_%d_dis_pp.gif",sectorstring,pid);
  sprintf(fignamenegpp,"CorrectionFactors/ptpid_%s_neg_%d_dis_pp.gif",sectorstring,pid);
  sprintf(fignameposmm,"CorrectionFactors/ptpid_%s_pos_%d_dis_mm.gif",sectorstring,pid);
  sprintf(fignamenegmm,"CorrectionFactors/ptpid_%s_neg_%d_dis_mm.gif",sectorstring,pid);

  float chi2; int NDF;
  char fitinfo[100];
  TLatex *tl;
  c1->SetLogy();
  //gStyle->SetOptFit(1100); // prints chi2 and prob
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  //pospp
  if(pid==2||pid==3) hh_sim_tofw_pos_pp->Fit(fit_pos_pp,"","",0.2,3.5);
  else hh_sim_tofw_pos_pp->Fit(fit_pos_pp,"","",0.2,5.0);
  hh_sim_tofw_pos_pp->SetMaximum(1e3);
  hh_sim_tofw_pos_pp->SetMinimum(1e1);
  hh_sim_tofw_pos_pp->GetXaxis()->SetRange(1,61);
  chi2 = fit_pos_pp->GetChisquare(); NDF = fit_pos_pp->GetNDF();
  sprintf(fitinfo,"#chi^{2}/ndf = %.2f/%d",chi2,NDF);
  tl = new TLatex(4.0,2e1,fitinfo);
  tl->SetTextSize(0.05);
  tl->Draw();
  if(sector==0&&centid==4) c1->Print(fignamepospp);
  //negpp
  if(pid==2||pid==3) hh_sim_tofw_neg_pp->Fit(fit_neg_pp,"","",0.2,3.5);
  else hh_sim_tofw_neg_pp->Fit(fit_neg_pp,"","",0.2,5.0);
  hh_sim_tofw_neg_pp->SetMaximum(1e3);
  hh_sim_tofw_neg_pp->SetMinimum(1e1);
  hh_sim_tofw_neg_pp->GetXaxis()->SetRange(1,61);
  chi2 = fit_neg_pp->GetChisquare(); NDF = fit_neg_pp->GetNDF();
  sprintf(fitinfo,"#chi^{2}/ndf = %.2f/%d",chi2,NDF);
  tl = new TLatex(4.0,2e1,fitinfo);
  tl->SetTextSize(0.05);
  tl->Draw();
  if(sector==0&&centid==4) c1->Print(fignamenegpp);
  //posmm
  if(pid==2||pid==3) hh_sim_tofw_pos_mm->Fit(fit_pos_mm,"","",0.2,3.5);
  else hh_sim_tofw_pos_mm->Fit(fit_pos_mm,"","",0.2,5.0);
  hh_sim_tofw_pos_mm->SetMaximum(1e3);
  hh_sim_tofw_pos_mm->SetMinimum(1e1);
  hh_sim_tofw_pos_mm->GetXaxis()->SetRange(1,61);
  chi2 = fit_pos_mm->GetChisquare(); NDF = fit_pos_mm->GetNDF();
  sprintf(fitinfo,"#chi^{2}/ndf = %.2f/%d",chi2,NDF);
  tl = new TLatex(4.0,2e1,fitinfo);
  tl->SetTextSize(0.05);
  tl->Draw();
  if(sector==0&&centid==4) c1->Print(fignameposmm);
  //negmm
  if(pid==2||pid==3) hh_sim_tofw_neg_mm->Fit(fit_neg_mm,"","",0.2,3.5);
  else hh_sim_tofw_neg_mm->Fit(fit_neg_mm,"","",0.2,5.0);
  hh_sim_tofw_neg_mm->SetMaximum(1e3);
  hh_sim_tofw_neg_mm->SetMinimum(1e1);
  hh_sim_tofw_neg_mm->GetXaxis()->SetRange(1,61);
  chi2 = fit_neg_mm->GetChisquare(); NDF = fit_neg_mm->GetNDF();
  sprintf(fitinfo,"#chi^{2}/ndf = %.2f/%d",chi2,NDF);
  tl = new TLatex(4.0,2e1,fitinfo);
  tl->SetTextSize(0.05);
  tl->Draw();
  if(sector==0&&centid==4) c1->Print(fignamenegmm);

  // DONT use fit
  // // use fit
  // for(int i=0; i<100; i++)
  //   {
  //     hh_sim_tofw_pos_pp->SetBinContent(i+1,fit_pos_pp->Eval(hh_sim_tofw_pos_pp->GetBinCenter(i+1)));
  //     hh_sim_tofw_neg_pp->SetBinContent(i+1,fit_neg_pp->Eval(hh_sim_tofw_neg_pp->GetBinCenter(i+1)));
  //     hh_sim_tofw_pos_mm->SetBinContent(i+1,fit_pos_mm->Eval(hh_sim_tofw_pos_mm->GetBinCenter(i+1)));
  //     hh_sim_tofw_neg_mm->SetBinContent(i+1,fit_neg_mm->Eval(hh_sim_tofw_neg_mm->GetBinCenter(i+1)));
  //   }

  sprintf(fignamepospp,"CorrectionFactors/ptpid_%s_pos_%d_dis_pp_POSTFIT.gif",sectorstring,pid);
  sprintf(fignamenegpp,"CorrectionFactors/ptpid_%s_neg_%d_dis_pp_POSTFIT.gif",sectorstring,pid);
  sprintf(fignameposmm,"CorrectionFactors/ptpid_%s_pos_%d_dis_mm_POSTFIT.gif",sectorstring,pid);
  sprintf(fignamenegmm,"CorrectionFactors/ptpid_%s_neg_%d_dis_mm_POSTFIT.gif",sectorstring,pid);

  //pospp
  if(pid==2||pid==3) hh_sim_tofw_pos_pp->Fit(fit_pos_pp,"","",0.2,3.5);
  else hh_sim_tofw_pos_pp->Fit(fit_pos_pp,"","",0.2,5.0);
  hh_sim_tofw_pos_pp->SetMaximum(1e3);
  hh_sim_tofw_pos_pp->SetMinimum(1e1);
  hh_sim_tofw_pos_pp->GetXaxis()->SetRange(1,61);
  chi2 = fit_pos_pp->GetChisquare(); NDF = fit_pos_pp->GetNDF();
  sprintf(fitinfo,"#chi^{2}/ndf = %.2f/%d",chi2,NDF);
  tl = new TLatex(4.0,2e1,fitinfo);
  tl->SetTextSize(0.05);
  tl->Draw();
  if(sector==0&&centid==4) c1->Print(fignamepospp);
  //negpp
  if(pid==2||pid==3) hh_sim_tofw_neg_pp->Fit(fit_neg_pp,"","",0.2,3.5);
  else hh_sim_tofw_neg_pp->Fit(fit_neg_pp,"","",0.2,5.0);
  hh_sim_tofw_neg_pp->SetMaximum(1e3);
  hh_sim_tofw_neg_pp->SetMinimum(1e1);
  hh_sim_tofw_neg_pp->GetXaxis()->SetRange(1,61);
  chi2 = fit_neg_pp->GetChisquare(); NDF = fit_neg_pp->GetNDF();
  sprintf(fitinfo,"#chi^{2}/ndf = %.2f/%d",chi2,NDF);
  tl = new TLatex(4.0,2e1,fitinfo);
  tl->SetTextSize(0.05);
  tl->Draw();
  if(sector==0&&centid==4) c1->Print(fignamenegpp);
  //posmm
  if(pid==2||pid==3) hh_sim_tofw_pos_mm->Fit(fit_pos_mm,"","",0.2,3.5);
  else hh_sim_tofw_pos_mm->Fit(fit_pos_mm,"","",0.2,5.0);
  hh_sim_tofw_pos_mm->SetMaximum(1e3);
  hh_sim_tofw_pos_mm->SetMinimum(1e1);
  hh_sim_tofw_pos_mm->GetXaxis()->SetRange(1,61);
  chi2 = fit_pos_mm->GetChisquare(); NDF = fit_pos_mm->GetNDF();
  sprintf(fitinfo,"#chi^{2}/ndf = %.2f/%d",chi2,NDF);
  tl = new TLatex(4.0,2e1,fitinfo);
  tl->SetTextSize(0.05);
  tl->Draw();
  if(sector==0&&centid==4) c1->Print(fignameposmm);
  //negmm
  if(pid==2||pid==3) hh_sim_tofw_neg_mm->Fit(fit_neg_mm,"","",0.2,3.5);
  else hh_sim_tofw_neg_mm->Fit(fit_neg_mm,"","",0.2,5.0);
  hh_sim_tofw_neg_mm->SetMaximum(1e3);
  hh_sim_tofw_neg_mm->SetMinimum(1e1);
  hh_sim_tofw_neg_mm->GetXaxis()->SetRange(1,61);
  chi2 = fit_neg_mm->GetChisquare(); NDF = fit_neg_mm->GetNDF();
  sprintf(fitinfo,"#chi^{2}/ndf = %.2f/%d",chi2,NDF);
  tl = new TLatex(4.0,2e1,fitinfo);
  tl->SetTextSize(0.05);
  tl->Draw();
  if(sector==0&&centid==4) c1->Print(fignamenegmm);




  h_real_tofw_pos_pp->Multiply(hh_sim_tofw_pos_pp);
  h_real_tofw_neg_pp->Multiply(hh_sim_tofw_neg_pp);
  h_real_tofw_pos_mm->Multiply(hh_sim_tofw_pos_mm);
  h_real_tofw_neg_mm->Multiply(hh_sim_tofw_neg_mm);


  //return;

  // Division constants
  // Divide by the number of real events, various efficiencies, and pT and cent bin-widths
  Long64_t nevents_pp = 1378825610; // 1.38 B
  Long64_t nevents_mm = 469047088; // 469 M
  //float tofw_eff = 0.95; // cosmic ray studies show 95%, in situ studies show 90%
  float tofw_eff = 0.90; // cosmic ray studies show 95%, in situ studies show 90%
  float tofw_adc = 0.85; // in situ studies show 85%
  // ------------------------------------------------------------------------------------
  //float dcqual = 0.9; // percentage of high-quality tracks is lower in real than in sim
  //float dcqual = 0.85; // percentage of high-quality tracks is lower in real than in sim
  //if(pid%2==1) dcqual = 0.8; // new, temp test
  // ------------------------------------------------------------------------------------
  float dcqual = 0.8;
  // ------------------------------------------------------------------------------------
  float binwidth_pT = 0.1; // 100 MeV bins
  float binwidth_cent = 0.2; // 20% centrality bins, adjust as needed
  if(centid==0) binwidth_cent = 0.05;
  if(centid==3) binwidth_cent = 0.38;
  if(centid==4) binwidth_cent = 0.88;
  // ---------------------------------------------------
  binwidth_cent /= 0.88; // THIS IS NEW AS OF 2012-02-14
  // ---------------------------------------------------
  //float twopi = 6.28318531; // corrected spectra are 1/2pi 1/pT
  float centshift = 1.0;
  if(centid==0) centshift = 0.95; //94, 95
  if(centid==1) centshift = 1.00; // 99
  if(centid==2) centshift = 1.03;
  if(centid==3) centshift = 1.03; // 104,103
  //if(centid==4) centshift = 0.98; //95
  if(centid==4) centshift = 0.89; //for 0-100, AN900

  //float konstant_pp = nevents_pp*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent*twopi;
  //float konstant_mm = nevents_mm*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent*twopi;
  //float konstant_pp = nevents_pp*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent*centshift;
  //float konstant_mm = nevents_mm*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent*centshift;
  float konstant_pp = nevents_pp*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent/centshift;
  float konstant_mm = nevents_mm*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent/centshift;

  TF1 *fun = new TF1("fun","pol1",0,10);
  fun->SetParameter(0,0);
  //fun->SetParameter(1,1);
  fun->SetParameter(1,6.28318531); // corrected spectra are 1/(2pipT)



  //cout<<"normalization constant is "<<konstant_pp<<endl;

  h_real_tofw_pos_pp->Divide(fun,konstant_pp);
  h_real_tofw_neg_pp->Divide(fun,konstant_pp);
  h_real_tofw_pos_mm->Divide(fun,konstant_mm);
  h_real_tofw_neg_mm->Divide(fun,konstant_mm);

  // come back here?

  char fnameoutpospp[100];
  char fnameoutnegpp[100];
  char fnameoutposmm[100];
  char fnameoutnegmm[100];

  sprintf(fnameoutpospp,"Data/ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegpp,"Data/ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameoutposmm,"Data/ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegmm,"Data/ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);

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

  foutpospp.close();
  foutnegpp.close();
  foutposmm.close();
  foutnegmm.close();



  // -------------------------- //
  // --- now combine fields --- //
  // -------------------------- //

  char fnameoutposcb[100];
  char fnameoutnegcb[100];

  sprintf(fnameoutposcb,"Data/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegcb,"Data/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

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

  // ---
  // ---
  // ---

  TH1F *HH_real_tofw_pos_pp = (TH1F *)h_real_tofw_pos_pp->Clone();
  TH1F *HH_real_tofw_neg_pp = (TH1F *)h_real_tofw_neg_pp->Clone();
  TH1F *HH_real_tofw_pos_mm = (TH1F *)h_real_tofw_pos_mm->Clone();
  TH1F *HH_real_tofw_neg_mm = (TH1F *)h_real_tofw_neg_mm->Clone();

  //


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

  // ------------------ //
  // ------------------ //
  // ------------------ //

  //char histotitle[100];
  //sprintf(histotitle,"corrected  #pi^{+}, rebinned, %s",bigcentstring);
  //h_real_tofw_pos_pp->SetTitle(histotitle);
  //h_real_tofw_pos_pp->Draw();

  //char figname[100];
  //sprintf(figname,"test_corrspec_R5_pid_%s_%d_cent_%s.gif",sectorstring,pid,centstring);
  //c1->Print("test_correctedspectra.gif");
  //c1->Print(figname);

  // now for the immortant part

  //cout<<"now doing the most immortant part"<<endl;

  sprintf(fnameoutpospp,"Data/R5_ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegpp,"Data/R5_ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameoutposmm,"Data/R5_ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegmm,"Data/R5_ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);

  foutpospp.open(fnameoutpospp);
  foutnegpp.open(fnameoutnegpp);
  foutposmm.open(fnameoutposmm);
  foutnegmm.open(fnameoutnegmm);

  //for(int i=0; i<100; i++)
  for(int i=0; i<20; i++) // reduce by 5 :)
    {
      float pT, yield, eyield;

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

  foutpospp.close();
  foutnegpp.close();
  foutposmm.close();
  foutnegmm.close();



  // -------------------------- //
  // --- now combine fields --- //
  // -------------------------- //

  sprintf(fnameoutposcb,"Data/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegcb,"Data/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  foutposcb.open(fnameoutposcb);
  foutnegcb.open(fnameoutnegcb);

  //for(int i=0; i<100; i++)
  for(int i=0; i<20; i++)
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

  // ---
  // ---
  // ---





  // ------------------ //
  // --- rebin by 2 --- //
  // ------------------ //

  HH_real_tofw_pos_pp->Rebin(2);
  HH_real_tofw_neg_pp->Rebin(2);
  HH_real_tofw_pos_mm->Rebin(2);
  HH_real_tofw_neg_mm->Rebin(2);

  HH_real_tofw_pos_pp->Divide(dummy,2.0);
  HH_real_tofw_neg_pp->Divide(dummy,2.0);
  HH_real_tofw_pos_mm->Divide(dummy,2.0);
  HH_real_tofw_neg_mm->Divide(dummy,2.0);




  // -------------------------- //
  // --- now combine fields --- //
  // -------------------------- //

  sprintf(fnameoutposcb,"Data/R2_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegcb,"Data/R2_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  foutposcb.open(fnameoutposcb);
  foutnegcb.open(fnameoutnegcb);

  for(int i=0; i<50; i++)
    {
      float pT, yield, eyield;
      float pT_A, yield_A, eyield_A;
      float pT_B, yield_B, eyield_B;

      // pospp
      pT_A = HH_real_tofw_pos_pp->GetBinCenter(i+1);
      yield_A = HH_real_tofw_pos_pp->GetBinContent(i+1);
      eyield_A = HH_real_tofw_pos_pp->GetBinError(i+1);
      // posmm
      pT_B = HH_real_tofw_pos_mm->GetBinCenter(i+1);
      yield_B = HH_real_tofw_pos_mm->GetBinContent(i+1);
      eyield_B = HH_real_tofw_pos_mm->GetBinError(i+1);


      pT = (pT_A+pT_B)/2.0;
      yield = (yield_A+yield_B)/2.0;
      eyield = sqrt(eyield_A**2+eyield_B**2)/2.0;
      foutposcb<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;

      // negpp
      pT_A = HH_real_tofw_neg_pp->GetBinCenter(i+1);
      yield_A = HH_real_tofw_neg_pp->GetBinContent(i+1);
      eyield_A = HH_real_tofw_neg_pp->GetBinError(i+1);
      // negmm
      pT_B = HH_real_tofw_neg_mm->GetBinCenter(i+1);
      yield_B = HH_real_tofw_neg_mm->GetBinContent(i+1);
      eyield_B = HH_real_tofw_neg_mm->GetBinError(i+1);

      pT = (pT_A+pT_B)/2.0;
      yield = (yield_A+yield_B)/2.0;
      eyield = sqrt(eyield_A**2+eyield_B**2)/2.0;
      foutnegcb<<pT<<"\t"<<yield<<"\t"<<eyield<<endl;
    }

  foutposcb.close();
  foutnegcb.close();



  // stop here?

  h_real_tofw_pos_pp->Delete();
  h_sim_tofw_pos_pp->Delete();
  h_real_tofw_neg_pp->Delete();
  h_sim_tofw_neg_pp->Delete();

  h_real_tofw_pos_mm->Delete();
  h_sim_tofw_pos_mm->Delete();
  h_real_tofw_neg_mm->Delete();
  h_sim_tofw_neg_mm->Delete();

  // ---

  f_real_pp->Close();
  f_simpion_pp->Close();
  f_simkaon_pp->Close();
  f_simproton_pp->Close();

  f_real_mm->Close();
  f_simpion_mm->Close();
  f_simkaon_mm->Close();
  f_simproton_mm->Close();

  // ---

  f_real_pp->Delete();
  f_simpion_pp->Delete();
  f_simkaon_pp->Delete();
  f_simproton_pp->Delete();

  f_real_mm->Delete();
  f_simpion_mm->Delete();
  f_simkaon_mm->Delete();
  f_simproton_mm->Delete();

  // now it's over!

  // delete hh_sim_tofw_pos_pp;
  // delete hh_sim_tofw_neg_pp;
  // delete hh_sim_tofw_pos_mm;
  // delete hh_sim_tofw_neg_mm;


}


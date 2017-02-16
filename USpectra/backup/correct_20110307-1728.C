void correct()
{

  cout<<"hello and welcome!"<<endl;
  cout<<"this is a new for Run8 spectra correction macro"<<endl;
  cout<<"based on the histogram division method."<<endl;
  cout<<"it also does the bin width correction, 1/pT correction,"<<endl;
  cout<<"and normalization constants."<<endl;





  TFile *f_real_pp = TFile::Open("outlow_plusplus.root");
  TFile *f_simpion_pp = TFile::Open("SimFiles/pion/simsum_pp.root");
  TFile *f_simkaon_pp = TFile::Open("SimFiles/kaon/simsum_pp.root");
  TFile *f_simproton_pp = TFile::Open("SimFiles/proton/simsum_pp.root");

  TFile *f_real_mm = TFile::Open("outlow_minusminus.root");
  TFile *f_simpion_mm = TFile::Open("SimFiles/pion/simsum_mm.root");
  TFile *f_simkaon_mm = TFile::Open("SimFiles/kaon/simsum_mm.root");
  TFile *f_simproton_mm = TFile::Open("SimFiles/proton/simsum_mm.root");



  TH1F *h_real_tofw_pos_0_cent0088_pp = f_real_pp->Get("ptpid_tofw_pos_0_dis_cent0088");
  TH1F *h_sim_tofw_pos_0_pp = f_simpion_pp->Get("ptpid_tofw_pos_0_dis");
  TH1F *h_real_tofw_neg_0_cent0088_pp = f_real_pp->Get("ptpid_tofw_neg_0_dis_cent0088");
  TH1F *h_sim_tofw_neg_0_pp = f_simpion_pp->Get("ptpid_tofw_neg_0_dis");

  TH1F *h_real_tofw_pos_0_cent0088_mm = f_real_mm->Get("ptpid_tofw_pos_0_dis_cent0088");
  TH1F *h_sim_tofw_pos_0_mm = f_simpion_mm->Get("ptpid_tofw_pos_0_dis");
  TH1F *h_real_tofw_neg_0_cent0088_mm = f_real_mm->Get("ptpid_tofw_neg_0_dis_cent0088");
  TH1F *h_sim_tofw_neg_0_mm = f_simpion_mm->Get("ptpid_tofw_neg_0_dis");



  // Multiplicative constants
  // Multiply by the simulation event numbes and acceptance windows
  //float simevents = 2.0e7; // 20M events for all types
  float simevents = 2.0e5; // 20M events for all types, divide by 100 to get per bin
  float window_azi = 0.5; // events are thrown in pi radians, divide by 2pi
  float window_rap = 1.2; // events are thrown in +/- 0.6 units of rapidity, divide by 1

  float simconst = simevents*window_azi*window_rap;

  cout<<"simulation constant is "<<simconst<<endl;

  TF1 *dummy = new TF1("dummy","pol0",0,10);
  dummy->SetParameter(0,1.0);

  h_real_tofw_pos_0_cent0088_pp->Multiply(dummy,simconst);
  h_real_tofw_neg_0_cent0088_pp->Multiply(dummy,simconst);
  h_real_tofw_pos_0_cent0088_mm->Multiply(dummy,simconst);
  h_real_tofw_neg_0_cent0088_mm->Multiply(dummy,simconst);


  // Division constants
  // Divide by the number of real events, various efficiencies, and pT and cent bin-widths
  Long64_t nevents_pp = 1378825610; // 1.38 B
  Long64_t nevents_mm = 469047088; // 469 M
  float tofw_eff = 0.95; // cosmic ray studies show 95%, in situ studies show 90%
  float tofw_adc = 0.85; // in situ studies show 85%
  float dcqual = 0.9; // percentage of high-quality tracks is lower in real than in sim
  float binwidth_pT = 0.1; // 100 MeV bins
  //float binwidth_cent = 0.2; // 20% centrality bins, adjust as needed
  float binwidth_cent = 0.88; // 20% centrality bins, adjust as needed
  //float twopi = 6.28318531; // corrected spectra are 1/2pi 1/pT

  //float konstant_pp = nevents_pp*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent*twopi;
  //float konstant_mm = nevents_mm*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent*twopi;
  float konstant_pp = nevents_pp*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;
  float konstant_mm = nevents_mm*tofw_eff*tofw_adc*dcqual*binwidth_pT*binwidth_cent;

  TF1 *fun = new TF1("fun","pol1",0,10);
  fun->SetParameter(0,0);
  //fun->SetParameter(1,1);
  fun->SetParameter(1,6.28318531); // corrected spectra are 1/(2pipT)



  cout<<"normalization constant is "<<konstant_pp<<endl;

  h_real_tofw_pos_0_cent0088_pp->Divide(fun,konstant_pp);
  h_real_tofw_neg_0_cent0088_pp->Divide(fun,konstant_pp);
  h_real_tofw_pos_0_cent0088_mm->Divide(fun,konstant_mm);
  h_real_tofw_neg_0_cent0088_mm->Divide(fun,konstant_mm);

  h_real_tofw_pos_0_cent0088_pp->Draw();


  cout<<"all done!  i hope you have a great day!"<<endl;


}

void cfdraw()
{

  cout<<"hello and welcome!"<<endl;

  //doit();

  //exit();

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

  for(int ipid=0; ipid<6; ipid++)
    {
      for(int isec=0; isec<3; isec++)
	{
	  doit(isec,ipid);
	  //cout<<"doit("<<isec<<","<<ipid<<","<<icent<<");"<<endl;
	}
    }
  



  cout<<"all done!  i hope you have a great day!"<<endl;

}

//void doit(int sector=0, int pid=0, int centid=0)
void doit(int sector=0, int pid=0)
{

  // TCanvas used for printing diagnostic figures
  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->SetFillColor(kWhite);
  c1->SetFrameFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameBorderMode(0);
  //c1->SetLogy();



  TFile *f_simpion_pp = TFile::Open("SimFiles/pion/simsum_pp.root");
  TFile *f_simkaon_pp = TFile::Open("SimFiles/kaon/simsum_pp.root");
  TFile *f_simproton_pp = TFile::Open("SimFiles/proton/simsum_pp.root");

  TFile *f_simpion_mm = TFile::Open("SimFiles/pion/simsum_mm.root");
  TFile *f_simkaon_mm = TFile::Open("SimFiles/kaon/simsum_mm.root");
  TFile *f_simproton_mm = TFile::Open("SimFiles/proton/simsum_mm.root");

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");



  char name_sim_tofw_pos_pp[50];
  char name_sim_tofw_neg_pp[50];

  char name_sim_tofw_pos_mm[50];
  char name_sim_tofw_neg_mm[50];

  sprintf(name_sim_tofw_pos_pp,"ptpid_%s_pos_%d_dis",sectorstring,pid);
  sprintf(name_sim_tofw_neg_pp,"ptpid_%s_neg_%d_dis",sectorstring,pid);

  sprintf(name_sim_tofw_pos_mm,"ptpid_%s_pos_%d_dis",sectorstring,pid);
  sprintf(name_sim_tofw_neg_mm,"ptpid_%s_neg_%d_dis",sectorstring,pid);

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

  h_sim_tofw_pos_pp->Sumw2();
  h_sim_tofw_neg_pp->Sumw2();

  h_sim_tofw_pos_mm->Sumw2();
  h_sim_tofw_neg_mm->Sumw2();



  

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

  h_sim_tofw_pos_pp->Divide(dummy,simconst);
  h_sim_tofw_neg_pp->Divide(dummy,simconst);
  h_sim_tofw_pos_mm->Divide(dummy,simconst);
  h_sim_tofw_neg_mm->Divide(dummy,simconst);




  float pt[100], value[100], evalue[100];
  float ept[100];
  float pt_pospp[100], value_pospp[100], evalue_pospp[100];
  float pt_negpp[100], value_negpp[100], evalue_negpp[100];
  float pt_posmm[100], value_posmm[100], evalue_posmm[100];
  float pt_negmm[100], value_negmm[100], evalue_negmm[100];
  float temp, etemp;
  for(int i=0; i<100; i++)
    {
      temp = h_sim_tofw_pos_pp->GetBinContent(i+1);
      etemp = h_sim_tofw_pos_pp->GetBinError(i+1);
      if(temp>0)
	{
	  value_pospp[i] = 1.0/temp;
	  evalue_pospp[i] = etemp/temp/temp;
	}
      else
	{
	  value_pospp[i] = -9;
	  evalue_pospp[i] = 0;
	}
      pt_pospp[i] = h_sim_tofw_pos_pp->GetBinCenter(i+1);
      ept[i]=0;

      temp = h_sim_tofw_neg_pp->GetBinContent(i+1);
      etemp = h_sim_tofw_neg_pp->GetBinError(i+1);
      if(temp>0)
	{
	  value_negpp[i] = 1.0/temp;
	  evalue_negpp[i] = etemp/temp/temp;
	}
      else
	{
	  value_negpp[i] = -9;
	  evalue_negpp[i] = 0;
	}
      pt_negpp[i] = h_sim_tofw_neg_pp->GetBinCenter(i+1);
      ept[i]=0;

      temp = h_sim_tofw_pos_mm->GetBinContent(i+1);
      etemp = h_sim_tofw_pos_mm->GetBinError(i+1);
      if(temp>0)
	{
	  value_posmm[i] = 1.0/temp;
	  evalue_posmm[i] = etemp/temp/temp;
	}
      else
	{
	  value_posmm[i] = -9;
	  evalue_posmm[i] = 0;
	}
      pt_posmm[i] = h_sim_tofw_pos_mm->GetBinCenter(i+1);
      ept[i]=0;

      temp = h_sim_tofw_neg_mm->GetBinContent(i+1);
      etemp = h_sim_tofw_neg_mm->GetBinError(i+1);
      if(temp>0)
	{
	  value_negmm[i] = 1.0/temp;
	  evalue_negmm[i] = etemp/temp/temp;
	}
      else
	{
	  value_negmm[i] = -9;
	  evalue_negmm[i] = 0;
	}
      pt_negmm[i] = h_sim_tofw_neg_mm->GetBinCenter(i+1);
      ept[i]=0;



    }


  char figname[50];


  TGraphErrors *tge_pospp = new TGraphErrors(100,pt_pospp,value_pospp,ept,evalue_pospp);
  tge_pospp->SetMarkerColor(kBlack);
  tge_pospp->SetMarkerStyle(20);
  tge_pospp->Draw("ap");
  tge_pospp->SetMaximum(1000);
  //tge_pospp->SetMaximum(200);
  tge_pospp->SetMinimum(0);
  tge_pospp->GetXaxis()->SetLimits(0.0,6.0);
  tge_pospp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_pospp->GetXaxis()->CenterTitle();
  tge_pospp->GetYaxis()->SetTitle("Correction Factor");
  tge_pospp->GetYaxis()->CenterTitle();

  sprintf(figname,"CorrectionFactors/cf_%s_pospp_%d_dis.gif",sectorstring,pid);
  c1->Print(figname);
  sprintf(figname,"CorrectionFactors/cf_%s_pospp_%d_dis.eps",sectorstring,pid);
  c1->Print(figname);





  TGraphErrors *tge_negpp = new TGraphErrors(100,pt_negpp,value_negpp,ept,evalue_negpp);
  tge_negpp->SetMarkerColor(kBlack);
  tge_negpp->SetMarkerStyle(20);
  tge_negpp->Draw("ap");
  tge_negpp->SetMaximum(1000);
  //tge_negpp->SetMaximum(200);
  tge_negpp->SetMinimum(0);
  tge_negpp->GetXaxis()->SetLimits(0.0,6.0);
  tge_negpp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_negpp->GetXaxis()->CenterTitle();
  tge_negpp->GetYaxis()->SetTitle("Correction Factor");
  tge_negpp->GetYaxis()->CenterTitle();

  sprintf(figname,"CorrectionFactors/cf_%s_negpp_%d_dis.gif",sectorstring,pid);
  c1->Print(figname);
  sprintf(figname,"CorrectionFactors/cf_%s_negpp_%d_dis.eps",sectorstring,pid);
  c1->Print(figname);





  TGraphErrors *tge_posmm = new TGraphErrors(100,pt_posmm,value_posmm,ept,evalue_posmm);
  tge_posmm->SetMarkerColor(kBlack);
  tge_posmm->SetMarkerStyle(20);
  tge_posmm->Draw("ap");
  tge_posmm->SetMaximum(1000);
  //tge_posmm->SetMaximum(200);
  tge_posmm->SetMinimum(0);
  tge_posmm->GetXaxis()->SetLimits(0.0,6.0);
  tge_posmm->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_posmm->GetXaxis()->CenterTitle();
  tge_posmm->GetYaxis()->SetTitle("Correction Factor");
  tge_posmm->GetYaxis()->CenterTitle();

  sprintf(figname,"CorrectionFactors/cf_%s_posmm_%d_dis.gif",sectorstring,pid);
  c1->Print(figname);
  sprintf(figname,"CorrectionFactors/cf_%s_posmm_%d_dis.eps",sectorstring,pid);
  c1->Print(figname);





  TGraphErrors *tge_negmm = new TGraphErrors(100,pt_negmm,value_negmm,ept,evalue_negmm);
  tge_negmm->SetMarkerColor(kBlack);
  tge_negmm->SetMarkerStyle(20);
  tge_negmm->Draw("ap");
  tge_negmm->SetMaximum(1000);
  //tge_negmm->SetMaximum(200);
  tge_negmm->SetMinimum(0);
  tge_negmm->GetXaxis()->SetLimits(0.0,6.0);
  tge_negmm->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_negmm->GetXaxis()->CenterTitle();
  tge_negmm->GetYaxis()->SetTitle("Correction Factor");
  tge_negmm->GetYaxis()->CenterTitle();

  sprintf(figname,"CorrectionFactors/cf_%s_negmm_%d_dis.gif",sectorstring,pid);
  c1->Print(figname);
  sprintf(figname,"CorrectionFactors/cf_%s_negmm_%d_dis.eps",sectorstring,pid);
  c1->Print(figname);


  c1->Clear();
  TMultiGraph *tmg_pp = new TMultiGraph();
  tge_pospp->SetMarkerStyle(21);
  tge_pospp->SetMarkerColor(kRed);
  tge_negpp->SetMarkerStyle(25);
  tge_negpp->SetMarkerColor(kBlue);
  tmg_pp->Add(tge_pospp);
  tmg_pp->Add(tge_negpp);
  tmg_pp->Draw("ap");
  tmg_pp->SetMaximum(1000);
  if(pid<2) tmg_pp->SetMaximum(300);
  tmg_pp->SetMinimum(0);
  tmg_pp->GetXaxis()->SetLimits(0.0,6.0);
  tmg_pp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pp->GetXaxis()->CenterTitle();
  tmg_pp->GetYaxis()->SetTitle("Correction Factor");
  tmg_pp->GetYaxis()->CenterTitle();
  TLegend *legpp = new TLegend(0.74,0.74,0.88,0.88);
  legpp->SetFillColor(kWhite);
  legpp->SetBorderSize(0);
  legpp->AddEntry(tge_pospp,"#pi^{+}","p");
  legpp->AddEntry(tge_negpp,"#pi^{-}","p");
  legpp->Draw();

  sprintf(figname,"CorrectionFactors/cf_%s_bothpp_%d_dis.gif",sectorstring,pid);
  c1->Print(figname);
  sprintf(figname,"CorrectionFactors/cf_%s_bothpp_%d_dis.eps",sectorstring,pid);
  c1->Print(figname);

  c1->Clear();
  TMultiGraph *tmg_mm = new TMultiGraph();
  tge_posmm->SetMarkerStyle(21);
  tge_posmm->SetMarkerColor(kRed);
  tge_negmm->SetMarkerStyle(25);
  tge_negmm->SetMarkerColor(kBlue);
  tmg_mm->Add(tge_posmm);
  tmg_mm->Add(tge_negmm);
  tmg_mm->Draw("ap");
  tmg_mm->SetMaximum(1000);
  if(pid<2) tmg_mm->SetMaximum(200);
  tmg_mm->SetMinimum(0);
  tmg_mm->GetXaxis()->SetLimits(0.0,6.0);
  tmg_mm->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_mm->GetXaxis()->CenterTitle();
  tmg_mm->GetYaxis()->SetTitle("Correction Factor");
  tmg_mm->GetYaxis()->CenterTitle();
  TLegend *legmm = new TLegend(0.74,0.74,0.88,0.88);
  legmm->SetFillColor(kWhite);
  legmm->SetBorderSize(0);
  legmm->AddEntry(tge_posmm,"#pi^{+}","p");
  legmm->AddEntry(tge_negmm,"#pi^{-}","p");
  legmm->Draw();

  sprintf(figname,"CorrectionFactors/cf_%s_bothmm_%d_dis.gif",sectorstring,pid);
  c1->Print(figname);
  sprintf(figname,"CorrectionFactors/cf_%s_bothmm_%d_dis.eps",sectorstring,pid);
  c1->Print(figname);




  // ---------------------------------------------------------- //
  // --- you don't have to go home, but you can't stay here --- //
  // ---------------------------------------------------------- //

  // ---

  h_sim_tofw_pos_pp->Delete();
  h_sim_tofw_neg_pp->Delete();

  h_sim_tofw_pos_mm->Delete();
  h_sim_tofw_neg_mm->Delete();

  // ---

  f_simpion_pp->Close();
  f_simkaon_pp->Close();
  f_simproton_pp->Close();

  f_simpion_mm->Close();
  f_simkaon_mm->Close();
  f_simproton_mm->Close();

  // ---

  f_simpion_pp->Delete();
  f_simkaon_pp->Delete();
  f_simproton_pp->Delete();

  f_simpion_mm->Delete();
  f_simkaon_mm->Delete();
  f_simproton_mm->Delete();

  // now it's over!

}


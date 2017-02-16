void comparecf()
{

  cout<<"hello and welcome!"<<endl;


  for(int isec=0; isec<3; isec++)
    {
      doit(isec);
    }
  



  cout<<"all done!  i hope you have a great day!"<<endl;

}

//void doit(int sector=0, int pid=0, int centid=0)
void doit(int sector=0)
{

  // TCanvas used for printing diagnostic figures
  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->SetFillColor(kWhite);
  c1->SetFrameFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameBorderMode(0);
  c1->SetLogy();



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


  // --- now pion

  int pid = 0;

  char name_simpion_tofw_pos_pp[50];
  char name_simpion_tofw_neg_pp[50];
  char name_simpion_tofw_pos_mm[50];
  char name_simpion_tofw_neg_mm[50];

  sprintf(name_simpion_tofw_pos_pp,"ptpid_%s_pos_%d_dis",sectorstring,pid);
  sprintf(name_simpion_tofw_neg_pp,"ptpid_%s_neg_%d_dis",sectorstring,pid);
  sprintf(name_simpion_tofw_pos_mm,"ptpid_%s_pos_%d_dis",sectorstring,pid);
  sprintf(name_simpion_tofw_neg_mm,"ptpid_%s_neg_%d_dis",sectorstring,pid);

  TH1F *h_simpion_tofw_pos_pp = f_simpion_pp->Get(name_simpion_tofw_pos_pp);
  TH1F *h_simpion_tofw_neg_pp = f_simpion_pp->Get(name_simpion_tofw_neg_pp);
  TH1F *h_simpion_tofw_pos_mm = f_simpion_mm->Get(name_simpion_tofw_pos_mm);
  TH1F *h_simpion_tofw_neg_mm = f_simpion_mm->Get(name_simpion_tofw_neg_mm);

  h_simpion_tofw_pos_pp->Sumw2();
  h_simpion_tofw_neg_pp->Sumw2();
  h_simpion_tofw_pos_mm->Sumw2();
  h_simpion_tofw_neg_mm->Sumw2();

  // --- now kaon

  pid = 2;

  char name_simkaon_tofw_pos_pp[50];
  char name_simkaon_tofw_neg_pp[50];
  char name_simkaon_tofw_pos_mm[50];
  char name_simkaon_tofw_neg_mm[50];

  sprintf(name_simkaon_tofw_pos_pp,"ptpid_%s_pos_%d_dis",sectorstring,pid);
  sprintf(name_simkaon_tofw_neg_pp,"ptpid_%s_neg_%d_dis",sectorstring,pid);
  sprintf(name_simkaon_tofw_pos_mm,"ptpid_%s_pos_%d_dis",sectorstring,pid);
  sprintf(name_simkaon_tofw_neg_mm,"ptpid_%s_neg_%d_dis",sectorstring,pid);

  TH1F *h_simkaon_tofw_pos_pp = f_simkaon_pp->Get(name_simkaon_tofw_pos_pp);
  TH1F *h_simkaon_tofw_neg_pp = f_simkaon_pp->Get(name_simkaon_tofw_neg_pp);
  TH1F *h_simkaon_tofw_pos_mm = f_simkaon_mm->Get(name_simkaon_tofw_pos_mm);
  TH1F *h_simkaon_tofw_neg_mm = f_simkaon_mm->Get(name_simkaon_tofw_neg_mm);

  h_simkaon_tofw_pos_pp->Sumw2();
  h_simkaon_tofw_neg_pp->Sumw2();
  h_simkaon_tofw_pos_mm->Sumw2();
  h_simkaon_tofw_neg_mm->Sumw2();

  // --- now proton

  pid = 4;

  char name_simproton_tofw_pos_pp[50];
  char name_simproton_tofw_neg_pp[50];
  char name_simproton_tofw_pos_mm[50];
  char name_simproton_tofw_neg_mm[50];

  sprintf(name_simproton_tofw_pos_pp,"ptpid_%s_pos_%d_dis",sectorstring,pid);
  sprintf(name_simproton_tofw_neg_pp,"ptpid_%s_neg_%d_dis",sectorstring,pid);
  sprintf(name_simproton_tofw_pos_mm,"ptpid_%s_pos_%d_dis",sectorstring,pid);
  sprintf(name_simproton_tofw_neg_mm,"ptpid_%s_neg_%d_dis",sectorstring,pid);

  TH1F *h_simproton_tofw_pos_pp = f_simproton_pp->Get(name_simproton_tofw_pos_pp);
  TH1F *h_simproton_tofw_neg_pp = f_simproton_pp->Get(name_simproton_tofw_neg_pp);
  TH1F *h_simproton_tofw_pos_mm = f_simproton_mm->Get(name_simproton_tofw_pos_mm);
  TH1F *h_simproton_tofw_neg_mm = f_simproton_mm->Get(name_simproton_tofw_neg_mm);

  h_simproton_tofw_pos_pp->Sumw2();
  h_simproton_tofw_neg_pp->Sumw2();
  h_simproton_tofw_pos_mm->Sumw2();
  h_simproton_tofw_neg_mm->Sumw2();




  

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

  h_simpion_tofw_pos_pp->Divide(dummy,simconst);
  h_simpion_tofw_neg_pp->Divide(dummy,simconst);
  h_simpion_tofw_pos_mm->Divide(dummy,simconst);
  h_simpion_tofw_neg_mm->Divide(dummy,simconst);

  h_simkaon_tofw_pos_pp->Divide(dummy,simconst);
  h_simkaon_tofw_neg_pp->Divide(dummy,simconst);
  h_simkaon_tofw_pos_mm->Divide(dummy,simconst);
  h_simkaon_tofw_neg_mm->Divide(dummy,simconst);

  h_simproton_tofw_pos_pp->Divide(dummy,simconst);
  h_simproton_tofw_neg_pp->Divide(dummy,simconst);
  h_simproton_tofw_pos_mm->Divide(dummy,simconst);
  h_simproton_tofw_neg_mm->Divide(dummy,simconst);




  float pt[100], value[100], evalue[100];
  float ept[100];
  float pt_pospp[100], value_pospp[100], evalue_pospp[100];
  float pt_negpp[100], value_negpp[100], evalue_negpp[100];
  float pt_posmm[100], value_posmm[100], evalue_posmm[100];
  float pt_negmm[100], value_negmm[100], evalue_negmm[100];
  float temp, etemp;
  // --- now pion
  for(int i=0; i<100; i++)
    {
      // --- now pospp
      temp = h_simpion_tofw_pos_pp->GetBinContent(i+1);
      etemp = h_simpion_tofw_pos_pp->GetBinError(i+1);
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
      pt_pospp[i] = h_simpion_tofw_pos_pp->GetBinCenter(i+1);
      ept[i]=0;
      // --- now negpp
      temp = h_simpion_tofw_neg_pp->GetBinContent(i+1);
      etemp = h_simpion_tofw_neg_pp->GetBinError(i+1);
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
      pt_negpp[i] = h_simpion_tofw_neg_pp->GetBinCenter(i+1);
      ept[i]=0;
      // --- now posmm
      temp = h_simpion_tofw_pos_mm->GetBinContent(i+1);
      etemp = h_simpion_tofw_pos_mm->GetBinError(i+1);
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
      pt_posmm[i] = h_simpion_tofw_pos_mm->GetBinCenter(i+1);
      ept[i]=0;
      // --- now negmm
      temp = h_simpion_tofw_neg_mm->GetBinContent(i+1);
      etemp = h_simpion_tofw_neg_mm->GetBinError(i+1);
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
      pt_negmm[i] = h_simpion_tofw_neg_mm->GetBinCenter(i+1);
      ept[i]=0;
    }
  TGraphErrors *tgepion_pospp = new TGraphErrors(100,pt_pospp,value_pospp,ept,evalue_pospp);
  tgepion_pospp->SetMarkerColor(kBlack);
  tgepion_pospp->SetMarkerStyle(20);
  TGraphErrors *tgepion_negpp = new TGraphErrors(100,pt_negpp,value_negpp,ept,evalue_negpp);
  tgepion_negpp->SetMarkerColor(kBlack);
  tgepion_negpp->SetMarkerStyle(20);
  TGraphErrors *tgepion_posmm = new TGraphErrors(100,pt_posmm,value_posmm,ept,evalue_posmm);
  tgepion_posmm->SetMarkerColor(kBlack);
  tgepion_posmm->SetMarkerStyle(20);
  TGraphErrors *tgepion_negmm = new TGraphErrors(100,pt_negmm,value_negmm,ept,evalue_negmm);
  tgepion_negmm->SetMarkerColor(kBlack);
  tgepion_negmm->SetMarkerStyle(20);
  // --- now kaon
  for(int i=0; i<100; i++)
    {
      // --- now pospp
      temp = h_simkaon_tofw_pos_pp->GetBinContent(i+1);
      etemp = h_simkaon_tofw_pos_pp->GetBinError(i+1);
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
      pt_pospp[i] = h_simkaon_tofw_pos_pp->GetBinCenter(i+1);
      ept[i]=0;
      // --- now negpp
      temp = h_simkaon_tofw_neg_pp->GetBinContent(i+1);
      etemp = h_simkaon_tofw_neg_pp->GetBinError(i+1);
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
      pt_negpp[i] = h_simkaon_tofw_neg_pp->GetBinCenter(i+1);
      ept[i]=0;
      // --- now posmm
      temp = h_simkaon_tofw_pos_mm->GetBinContent(i+1);
      etemp = h_simkaon_tofw_pos_mm->GetBinError(i+1);
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
      pt_posmm[i] = h_simkaon_tofw_pos_mm->GetBinCenter(i+1);
      ept[i]=0;
      // --- now negmm
      temp = h_simkaon_tofw_neg_mm->GetBinContent(i+1);
      etemp = h_simkaon_tofw_neg_mm->GetBinError(i+1);
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
      pt_negmm[i] = h_simkaon_tofw_neg_mm->GetBinCenter(i+1);
      ept[i]=0;
    }
  TGraphErrors *tgekaon_pospp = new TGraphErrors(100,pt_pospp,value_pospp,ept,evalue_pospp);
  tgekaon_pospp->SetMarkerColor(kBlack);
  tgekaon_pospp->SetMarkerStyle(20);
  TGraphErrors *tgekaon_negpp = new TGraphErrors(100,pt_negpp,value_negpp,ept,evalue_negpp);
  tgekaon_negpp->SetMarkerColor(kBlack);
  tgekaon_negpp->SetMarkerStyle(20);
  TGraphErrors *tgekaon_posmm = new TGraphErrors(100,pt_posmm,value_posmm,ept,evalue_posmm);
  tgekaon_posmm->SetMarkerColor(kBlack);
  tgekaon_posmm->SetMarkerStyle(20);
  TGraphErrors *tgekaon_negmm = new TGraphErrors(100,pt_negmm,value_negmm,ept,evalue_negmm);
  tgekaon_negmm->SetMarkerColor(kBlack);
  tgekaon_negmm->SetMarkerStyle(20);
  // --- now proton
  for(int i=0; i<100; i++)
    {
      // --- now pospp
      temp = h_simproton_tofw_pos_pp->GetBinContent(i+1);
      etemp = h_simproton_tofw_pos_pp->GetBinError(i+1);
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
      pt_pospp[i] = h_simproton_tofw_pos_pp->GetBinCenter(i+1);
      ept[i]=0;
      // --- now negpp
      temp = h_simproton_tofw_neg_pp->GetBinContent(i+1);
      etemp = h_simproton_tofw_neg_pp->GetBinError(i+1);
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
      pt_negpp[i] = h_simproton_tofw_neg_pp->GetBinCenter(i+1);
      ept[i]=0;
      // --- now posmm
      temp = h_simproton_tofw_pos_mm->GetBinContent(i+1);
      etemp = h_simproton_tofw_pos_mm->GetBinError(i+1);
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
      pt_posmm[i] = h_simproton_tofw_pos_mm->GetBinCenter(i+1);
      ept[i]=0;
      // --- now negmm
      temp = h_simproton_tofw_neg_mm->GetBinContent(i+1);
      etemp = h_simproton_tofw_neg_mm->GetBinError(i+1);
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
      pt_negmm[i] = h_simproton_tofw_neg_mm->GetBinCenter(i+1);
      ept[i]=0;
    }
  TGraphErrors *tgeproton_pospp = new TGraphErrors(100,pt_pospp,value_pospp,ept,evalue_pospp);
  tgeproton_pospp->SetMarkerColor(kBlack);
  tgeproton_pospp->SetMarkerStyle(20);
  TGraphErrors *tgeproton_negpp = new TGraphErrors(100,pt_negpp,value_negpp,ept,evalue_negpp);
  tgeproton_negpp->SetMarkerColor(kBlack);
  tgeproton_negpp->SetMarkerStyle(20);
  TGraphErrors *tgeproton_posmm = new TGraphErrors(100,pt_posmm,value_posmm,ept,evalue_posmm);
  tgeproton_posmm->SetMarkerColor(kBlack);
  tgeproton_posmm->SetMarkerStyle(20);
  TGraphErrors *tgeproton_negmm = new TGraphErrors(100,pt_negmm,value_negmm,ept,evalue_negmm);
  tgeproton_negmm->SetMarkerColor(kBlack);
  tgeproton_negmm->SetMarkerStyle(20);













  c1->Clear();
  TMultiGraph *tmg_pospp = new TMultiGraph();
  tgepion_pospp->SetMarkerStyle(20);
  tgepion_pospp->SetMarkerColor(kBlue);
  tgekaon_pospp->SetMarkerStyle(22);
  tgekaon_pospp->SetMarkerColor(kGreen+2);
  tgeproton_pospp->SetMarkerStyle(21);
  tgeproton_pospp->SetMarkerColor(kRed);
  tmg_pospp->Add(tgepion_pospp);
  tmg_pospp->Add(tgekaon_pospp);
  tmg_pospp->Add(tgeproton_pospp);
  tmg_pospp->Draw("ap");
  //tmg_pospp->SetMaximum(1000);
  //tmg_pospp->SetMinimum(0);
  tmg_pospp->SetMaximum(1e6);
  tmg_pospp->SetMinimum(1e1);
  tmg_pospp->GetXaxis()->SetLimits(0.0,6.0);
  tmg_pospp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pospp->GetXaxis()->CenterTitle();
  tmg_pospp->GetYaxis()->SetTitle("Correction Factor");
  tmg_pospp->GetYaxis()->CenterTitle();
  TLegend *legpospp = new TLegend(0.74,0.74,0.88,0.88);
  legpospp->SetFillColor(kWhite);
  legpospp->SetBorderSize(0);
  legpospp->AddEntry(tgepion_pospp,"#pi^{+}","p");
  legpospp->AddEntry(tgekaon_pospp,"K^{+}","p");
  legpospp->AddEntry(tgeproton_pospp,"p","p");
  legpospp->Draw();

  char figname[150];
  sprintf(figname,"CorrectionFactors/cf_pikp_%s_pospp_%d_dis_LOG.gif",sectorstring,pid);
  c1->Print(figname);
  sprintf(figname,"CorrectionFactors/cf_pikp_%s_pospp_%d_dis_LOG.eps",sectorstring,pid);
  c1->Print(figname);

  c1->Clear();
  c1->SetLogy(0);
  tmg_pospp->Draw("ap");
  tmg_pospp->SetMaximum(1000);
  tmg_pospp->SetMinimum(0);
  legpospp->Draw();

  char figname2[150];

  sprintf(figname2,"CorrectionFactors/cf_pikp_%s_pospp_%d_dis_LIN.gif",sectorstring,pid);
  c1->Print(figname2);
  sprintf(figname2,"CorrectionFactors/cf_pikp_%s_pospp_%d_dis_LIN.eps",sectorstring,pid);
  c1->Print(figname2);



  // ---------------------------------------------------------- //
  // --- you don't have to go home, but you can't stay here --- //
  // ---------------------------------------------------------- //

  // c1->Clear();
  // tmg_pospp->Delete();
  // legpospp->Delete();
  // //c1->Delete();

  // // ---

  // h_simpion_tofw_pos_pp->Delete();
  // h_simpion_tofw_neg_pp->Delete();
  // h_simpion_tofw_pos_mm->Delete();
  // h_simpion_tofw_neg_mm->Delete();

  // h_simkaon_tofw_pos_pp->Delete();
  // h_simkaon_tofw_neg_pp->Delete();
  // h_simkaon_tofw_pos_mm->Delete();
  // h_simkaon_tofw_neg_mm->Delete();

  // h_simproton_tofw_pos_pp->Delete();
  // h_simproton_tofw_neg_pp->Delete();
  // h_simproton_tofw_pos_mm->Delete();
  // h_simproton_tofw_neg_mm->Delete();

  // // ---

  // f_simpion_pp->Close();
  // f_simkaon_pp->Close();
  // f_simproton_pp->Close();

  // f_simpion_mm->Close();
  // f_simkaon_mm->Close();
  // f_simproton_mm->Close();

  // // ---

  // f_simpion_pp->Delete();
  // f_simkaon_pp->Delete();
  // f_simproton_pp->Delete();

  // f_simpion_mm->Delete();
  // f_simkaon_mm->Delete();
  // f_simproton_mm->Delete();

  // now it's over!

}


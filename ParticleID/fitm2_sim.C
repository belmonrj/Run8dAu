void fitm2_sim()
{

  TCanvas *c1 = new TCanvas();

  TFile *fpion = TFile::Open("simpion_pp.root");
  TFile *fkaon = TFile::Open("simkaon_pp.root");
  TFile *fproton = TFile::Open("simproton_pp.root");

  TH2F *bhfuil_pion_pos = (TH2F *)fpion->Get("m2pTdis_pos");
  TH2F *bhfuil_pion_neg = (TH2F *)fpion->Get("m2pTdis_neg");
  TH2F *bhfuil_kaon_pos = (TH2F *)fkaon->Get("m2pTdis_pos");
  TH2F *bhfuil_kaon_neg = (TH2F *)fkaon->Get("m2pTdis_neg");
  TH2F *bhfuil_proton_pos = (TH2F *)fproton->Get("m2pTdis_pos");
  TH2F *bhfuil_proton_neg = (TH2F *)fproton->Get("m2pTdis_neg");
  //TH2F *bhfuil_pion_pos = (TH2F *)fpion->Get("m2momdis_pos");
  //TH2F *bhfuil_pion_neg = (TH2F *)fpion->Get("m2momdis_neg");
  //TH2F *bhfuil_kaon_pos = (TH2F *)fkaon->Get("m2momdis_pos");
  //TH2F *bhfuil_kaon_neg = (TH2F *)fkaon->Get("m2momdis_neg");
  //TH2F *bhfuil_proton_pos = (TH2F *)fproton->Get("m2momdis_pos");
  //TH2F *bhfuil_proton_neg = (TH2F *)fproton->Get("m2momdis_neg");

  TF1 *funpion = new TF1("funpion","gaus",-5.0,5.0);
  TF1 *funkaon = new TF1("funkaon","gaus",-5.0,5.0);
  TF1 *funproton = new TF1("funproton","gaus",-5.0,5.0);

  char pionfigname[100];
  char kaonfigname[100];
  char protonfigname[100];

  ofstream fbothpionout("m2pT_both_pion_par_sim.txt");
  ofstream fbothkaonout("m2pT_both_kaon_par_sim.txt");
  ofstream fbothprotonout("m2pT_both_proton_par_sim.txt");

  ofstream fpospionout("m2pT_pos_pion_par_sim.txt");
  ofstream fposkaonout("m2pT_pos_kaon_par_sim.txt");
  ofstream fposprotonout("m2pT_pos_proton_par_sim.txt");

  ofstream fnegpionout("m2pT_neg_pion_par_sim.txt");
  ofstream fnegkaonout("m2pT_neg_kaon_par_sim.txt");
  ofstream fnegprotonout("m2pT_neg_proton_par_sim.txt");


  //TH1F *hdummy = new TH1F("hdummy","",1,-0.1,0.1);

  TH1F *h_pion;
  TH1F *h_kaon;
  TH1F *h_proton;




  for(int i=0; i<70; i++)
    {

      float mom = i/10.0+0.05;

      bhfuil_pion_pos->ProjectionY("hh_pion_pos",i+1,i+1);
      bhfuil_pion_neg->ProjectionY("hh_pion_neg",i+1,i+1);

      TH1F *hh_pion = (TH1F *)hh_pion_pos->Clone();
      hh_pion->Add(hh_pion_neg);

      h_pion = (TH1F *)hh_pion->Clone();
      float max = h_pion->GetBinContent(h_pion->GetMaximumBin());

      if(i<20) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(81,135);
	  h_pion->Fit("funpion","","",-0.1,0.1);
	}
      if(i>=20&&i<30) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(71,145);
	  h_pion->Fit("funpion","","",-0.2,0.2);
	}
      if(i>=30&&i<40) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(61,155);
	  h_pion->Fit("funpion","","",-0.3,0.3);
	}
      if(i>=40&&i<50) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(51,165);
	  h_pion->Fit("funpion","","",-0.4,0.4);
	}
      if(i>=50&&i<60) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(31,185);
	  h_pion->Fit("funpion","","",-0.6,0.6);
	}
      if(i>=60&&i<70) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(11,205);
	  h_pion->Fit("funpion","","",-0.8,0.8);
	}

      fbothpionout
	<<mom
	<<"\t"
	<<funpion->GetParameter(1)
	<<"\t"
	<<funpion->GetParError(1)
	<<"\t"
	<<funpion->GetParameter(2)
	<<"\t"
	<<funpion->GetParError(2)
	<<"\t"
	<<endl;
      
      sprintf(pionfigname,"sim_figs/m2pT_both_pion_%d_sim.gif",i);
      c1->Print(pionfigname);
      sprintf(pionfigname,"sim_figs/m2pT_both_pion_%d_sim.eps",i);
      c1->Print(pionfigname);
      


      // now kaons

      bhfuil_kaon_pos->ProjectionY("hh_kaon_pos",i+1,i+1);
      bhfuil_kaon_neg->ProjectionY("hh_kaon_neg",i+1,i+1);

      TH1F *hh_kaon = (TH1F *)hh_kaon_pos->Clone();
      hh_kaon->Add(hh_kaon_neg);

      h_kaon = (TH1F *)hh_kaon->Clone();
      float max = h_kaon->GetBinContent(h_kaon->GetMaximumBin());

      if(i<20) // allez-y
	{
	  h_kaon->GetXaxis()->SetRange(101,155);
	  h_kaon->Fit("funkaon","","",0.1,0.35);
	}
      if(i>=20&&i<30) // allez-y
	{
	  h_kaon->GetXaxis()->SetRange(91,165);
	  h_kaon->Fit("funkaon","","",0.0,0.45);
	}
      if(i>=30&&i<40) // allez-y
	{
	  h_kaon->GetXaxis()->SetRange(81,175);
	  h_kaon->Fit("funkaon","","",-0.1,0.6);
	}
      if(i>=40&&i<50) // allez-y
	{
	  h_kaon->GetXaxis()->SetRange(71,185);
	  h_kaon->Fit("funkaon","","",-0.2,0.7);
	}
      if(i>=50&&i<60) // allez-y
	{
	  h_kaon->GetXaxis()->SetRange(51,205);
	  h_kaon->Fit("funkaon","","",-0.4,0.8);
	}
      if(i>=60&&i<70) // allez-y
	{
	  h_kaon->GetXaxis()->SetRange(31,225);
	  h_kaon->Fit("funkaon","","",-0.6,1.0);
	}

      fbothkaonout
	<<mom
	<<"\t"
	<<funkaon->GetParameter(1)
	<<"\t"
	<<funkaon->GetParError(1)
	<<"\t"
	<<funkaon->GetParameter(2)
	<<"\t"
	<<funkaon->GetParError(2)
	<<"\t"
	<<endl;
      
      sprintf(kaonfigname,"sim_figs/m2pT_both_kaon_%d_sim.gif",i);
      c1->Print(kaonfigname);
      sprintf(kaonfigname,"sim_figs/m2pT_both_kaon_%d_sim.eps",i);
      c1->Print(kaonfigname);
      

      //cout<<"here i am, part 1"<<endl;

      // now protons

      bhfuil_proton_pos->ProjectionY("hh_proton_pos",i+1,i+1);
      bhfuil_proton_neg->ProjectionY("hh_proton_neg",i+1,i+1);

      TH1F *hh_proton = (TH1F *)hh_proton_pos->Clone();
      hh_proton->Add(hh_proton_neg);

      h_proton = (TH1F *)hh_proton->Clone();
      float max = h_proton->GetBinContent(h_proton->GetMaximumBin());

      //cout<<"here i am, part 2"<<endl;

      if(i<20) // allez-y
	{
	  h_proton->GetXaxis()->SetRange(161,225);
	  h_proton->Fit("funproton","","",0.8,1.0);
	}
      if(i>=20&&i<30) // allez-y
	{
	  h_proton->GetXaxis()->SetRange(151,235);
	  h_proton->Fit("funproton","","",0.7,1.1);
	}
      if(i>=30&&i<40) // allez-y
	{
	  h_proton->GetXaxis()->SetRange(141,245);
	  h_proton->Fit("funproton","","",0.6,1.2);
	}
      if(i>=40&&i<50) // allez-y
	{
	  h_proton->GetXaxis()->SetRange(131,255);
	  h_proton->Fit("funproton","","",0.5,1.3);
	}
      if(i>=50&&i<60) // allez-y
	{
	  h_proton->GetXaxis()->SetRange(121,265);
	  h_proton->Fit("funproton","","",0.4,1.4);
	}
      if(i>=60&&i<70) // allez-y
	{
	  h_proton->GetXaxis()->SetRange(111,275);
	  h_proton->Fit("funproton","","",0.3,1.5);
	}

      //cout<<"here i am, part 3"<<endl;

      fbothprotonout
	<<mom
	<<"\t"
	<<funproton->GetParameter(1)
	<<"\t"
	<<funproton->GetParError(1)
	<<"\t"
	<<funproton->GetParameter(2)
	<<"\t"
	<<funproton->GetParError(2)
	<<"\t"
	<<endl;
      
      //cout<<"here i am, part 4"<<endl;

      sprintf(protonfigname,"sim_figs/m2pT_both_proton_%d_sim.gif",i);
      c1->Print(protonfigname);
      sprintf(protonfigname,"sim_figs/m2pT_both_proton_%d_sim.eps",i);
      c1->Print(protonfigname);
      
      //cout<<"here i am, part 5"<<endl;

    } // for loop

  return;



  for(int i=0; i<70; i++)
    {

      float mom = i/10.0+0.05;

      bhfuil_pion_pos->ProjectionY("hh_pion_",i+1,i+1);

      h_pion = (TH1F *)hh_pion_->Clone();
      float max = h_pion->GetBinContent(h_pion->GetMaximumBin());

      if(i<20) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(81,135);
	  h_pion->Fit("funpion","","",-0.1,0.1);
	}
      if(i>=20&&i<30) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(71,145);
	  h_pion->Fit("funpion","","",-0.2,0.2);
	}
      if(i>=30&&i<40) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(61,155);
	  h_pion->Fit("funpion","","",-0.3,0.3);
	}
      if(i>=40&&i<50) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(51,165);
	  h_pion->Fit("funpion","","",-0.4,0.4);
	}
      if(i>=50&&i<60) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(31,185);
	  h_pion->Fit("funpion","","",-0.6,0.6);
	}
      if(i>=60&&i<70) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(11,205);
	  h_pion->Fit("funpion","","",-0.8,0.8);
	}

      fpospionout
	<<mom
	<<"\t"
	<<funpion->GetParameter(1)
	<<"\t"
	<<funpion->GetParError(1)
	<<"\t"
	<<funpion->GetParameter(2)
	<<"\t"
	<<funpion->GetParError(2)
	<<"\t"
	<<endl;
      
      sprintf(pionfigname,"sim_figs/m2pT_pos_pion_%d_sim.gif",i);
      c1->Print(pionfigname);
      sprintf(pionfigname,"sim_figs/m2pT_pos_pion_%d_sim.eps",i);
      c1->Print(pionfigname);
      
    } // for loop




  for(int i=0; i<70; i++)
    {

      float mom = i/10.0+0.05;

      bhfuil_pion_neg->ProjectionY("hh_pion_",i+1,i+1);

      h_pion = (TH1F *)hh_pion_->Clone();
      float max = h_pion->GetBinContent(h_pion->GetMaximumBin());


      if(i<20) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(81,135);
	  h_pion->Fit("funpion","","",-0.1,0.1);
	}
      if(i>=20&&i<30) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(71,145);
	  h_pion->Fit("funpion","","",-0.2,0.2);
	}
      if(i>=30&&i<40) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(61,155);
	  h_pion->Fit("funpion","","",-0.3,0.3);
	}
      if(i>=40&&i<50) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(51,165);
	  h_pion->Fit("funpion","","",-0.4,0.4);
	}
      if(i>=50&&i<60) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(31,185);
	  h_pion->Fit("funpion","","",-0.6,0.6);
	}
      if(i>=60&&i<70) // allez-y
	{
	  h_pion->GetXaxis()->SetRange(11,205);
	  h_pion->Fit("funpion","","",-0.8,0.8);
	}


      fnegpionout
	<<mom
	<<"\t"
	<<funpion->GetParameter(1)
	<<"\t"
	<<funpion->GetParError(1)
	<<"\t"
	<<funpion->GetParameter(2)
	<<"\t"
	<<funpion->GetParError(2)
	<<"\t"
	<<endl;
      
      sprintf(pionfigname,"sim_figs/m2pT_neg_pion_%d_sim.gif",i);
      c1->Print(pionfigname);
      sprintf(pionfigname,"sim_figs/m2pT_neg_pion_%d_sim.eps",i);
      c1->Print(pionfigname);


    } // for loop







} // void fitm2

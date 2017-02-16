void fitm2()
{

  TCanvas *c1 = new TCanvas();

  // TFile *flow = TFile::Open("outlowpm.root");
  // TFile *full = TFile::Open("outpm.root");

  // TH2F *hh_flow_pos = (TH2F *)flow->Get("m2pTdis_pos");
  // TH2F *hh_full_pos = (TH2F *)full->Get("m2pTdis_pos");
  // TH2F *hh_flow_neg = (TH2F *)flow->Get("m2pTdis_neg");
  // TH2F *hh_full_neg = (TH2F *)full->Get("m2pTdis_neg");

  // TFile *flow = TFile::Open("outlowpm.root");
  TFile *fall = TFile::Open("outsum_low.root");

  TH2F *hh_flow_pos = (TH2F *)fall->Get("m2mompos_dis");
  TH2F *hh_full_pos = (TH2F *)fall->Get("m2mompos_dis");
  TH2F *hh_flow_neg = (TH2F *)fall->Get("m2momneg_dis");
  TH2F *hh_full_neg = (TH2F *)fall->Get("m2momneg_dis");

  TF1 *funpion = new TF1("funpion","gaus",-5.0,5.0);
  TF1 *funkaon = new TF1("funkaon","gaus",-5.0,5.0);
  TF1 *superfun = new TF1("superfun","gaus(0)+gaus(3)",-5.0,5.0);
  TF1 *funproton = new TF1("funproton","gaus",-5.0,5.0);
  // fixing the mean makes the fits very bad
  //funpion->FixParameter(1,0.01948);
  //funkaon->FixParameter(1,0.24332);
  //superfun->FixParameter(1,0.01948);
  //superfun->FixParameter(4,0.24332);

  char pionfigname[100];
  char kaonfigname[100];
  char protonfigname[100];


  ofstream fbothpionout("m2pT_both_pion_par.txt");
  ofstream fbothkaonout("m2pT_both_kaon_par.txt");
  ofstream fbothprotonout("m2pT_both_proton_par.txt");
  ofstream fpospionout("m2pT_pos_pion_par.txt");
  ofstream fposkaonout("m2pT_pos_kaon_par.txt");
  ofstream fposprotonout("m2pT_pos_proton_par.txt");
  ofstream fnegpionout("m2pT_neg_pion_par.txt");
  ofstream fnegkaonout("m2pT_neg_kaon_par.txt");
  ofstream fnegprotonout("m2pT_neg_proton_par.txt");


  TH1F *hdummy = new TH1F("hdummy","",1,-0.1,0.1);

  TH1F *help;
  TH1F *helppos;
  TH1F *helpneg;


  //cout<<"now starting first loop"<<endl;

  for(int i=5; i<40; i++)
    {

      float mom = i/10.0+0.05;

      //cout<<"A"<<endl;

      if (i<10) hh_flow_pos->ProjectionY("hhpos",i+1,i+1);
      //if (i<40) hh_flow_pos->ProjectionY("hhpos",i+1,i+1);
      else hh_full_pos->ProjectionY("hhpos",i+1,i+1);
      if (i<10) hh_flow_neg->ProjectionY("hhneg",i+1,i+1);
      //if (i<40) hh_flow_neg->ProjectionY("hhneg",i+1,i+1);
      else hh_full_neg->ProjectionY("hhneg",i+1,i+1);

      //cout<<"B"<<endl;

      //cout<<"hhpos has "<<hhpos->GetEntries()<<endl;
      //cout<<"hhneg has "<<hhneg->GetEntries()<<endl;

      TH1F *hh = (TH1F *)hhpos->Clone();
      hh->Add(hhneg);

      //cout<<"hh has "<<hh->GetEntries()<<endl;

      help = (TH1F *)hh->Clone();
      float max = help->GetBinContent(help->GetMaximumBin());

      //cout<<"help has "<<help->GetEntries()<<endl;

      //cout<<"C"<<endl;

      if(i<20)
	{
	  help->GetXaxis()->SetRange(131,170);
	  help->Fit("funpion","","",-0.1,0.1); // failing here, but why???
	  cout<<"C3"<<endl;
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
	  cout<<"C4"<<endl;

	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pion_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pion_%d.eps",i);
	  c1->Print(pionfigname);

	  help->GetXaxis()->SetRange(161,190);
	  help->Fit("funkaon","","",0.2,0.3);
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
	  sprintf(kaonfigname,"m2pT_figs/m2pT_both_kaon_%d.gif",i);
	  c1->Print(kaonfigname);
	  sprintf(kaonfigname,"m2pT_figs/m2pT_both_kaon_%d.eps",i);
	  c1->Print(kaonfigname);
	}

      cout<<"D"<<endl;

      if(i>=20&&i<25)
	{
	  help->GetXaxis()->SetRange(131,190);
	  help->Fit("funpion","","",-0.07,0.07);
	  help->Fit("funkaon","","", 0.2,0.3);
	  superfun->SetParameter(0,funpion->GetParameter(0));
	  superfun->SetParameter(1,funpion->GetParameter(1));
	  superfun->SetParameter(2,funpion->GetParameter(2));
	  superfun->SetParameter(3,funkaon->GetParameter(0));
	  superfun->SetParameter(4,funkaon->GetParameter(1));
	  superfun->SetParameter(5,funkaon->GetParameter(2));
	  help->Fit("superfun","","",-0.1,0.35);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  funpion->Draw("same");
	  funkaon->Draw("same");
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
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}
      if(i>=25&&i<30)
	{
	  help->GetXaxis()->SetRange(121,190);
	  help->Fit("funpion","","",-0.07,0.07);
	  help->Fit("funkaon","","", 0.2,0.3);
	  superfun->SetParameter(0,funpion->GetParameter(0));
	  superfun->SetParameter(1,funpion->GetParameter(1));
	  superfun->SetParameter(2,funpion->GetParameter(2));
	  superfun->SetParameter(3,funkaon->GetParameter(0));
	  superfun->SetParameter(4,funkaon->GetParameter(1));
	  superfun->SetParameter(5,funkaon->GetParameter(2));
	  help->Fit("superfun","","",-0.1,0.35);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  funpion->SetParameter(0,superfun->GetParameter(0));
	  funpion->SetParameter(1,superfun->GetParameter(1));
	  funpion->SetParameter(2,superfun->GetParameter(2));
	  funkaon->SetParameter(0,superfun->GetParameter(3));
	  funkaon->SetParameter(1,superfun->GetParameter(4));
	  funkaon->SetParameter(2,superfun->GetParameter(5));
	  funpion->Draw("same");
	  funkaon->Draw("same");
	  fbothpionout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(1)
	    <<"\t"
	    <<superfun->GetParError(1)
	    <<"\t"
	    <<superfun->GetParameter(2)
	    <<"\t"
	    <<superfun->GetParError(2)
	    <<"\t"
	    <<endl;
	  fbothkaonout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(4)
	    <<"\t"
	    <<superfun->GetParError(4)
	    <<"\t"
	    <<superfun->GetParameter(5)
	    <<"\t"
	    <<superfun->GetParError(5)
	    <<"\t"
	    <<endl;
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}

      if(i>=30&&i<40)
	{
	  help->GetXaxis()->SetRange(71,150);
	  help->Fit("funpion","","",-0.15,0.1);
	  help->Fit("funkaon","","", 0.2,0.4);
	  superfun->SetParameter(0,funpion->GetParameter(0));
	  superfun->SetParameter(1,funpion->GetParameter(1));
	  superfun->SetParameter(2,funpion->GetParameter(2));
	  superfun->SetParameter(3,funkaon->GetParameter(0));
	  superfun->SetParameter(4,funkaon->GetParameter(1));
	  superfun->SetParameter(5,funkaon->GetParameter(2));
	  help->Fit("superfun","","",-0.2,0.4);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  funpion->SetParameter(0,superfun->GetParameter(0));
	  funpion->SetParameter(1,superfun->GetParameter(1));
	  funpion->SetParameter(2,superfun->GetParameter(2));
	  funkaon->SetParameter(0,superfun->GetParameter(3));
	  funkaon->SetParameter(1,superfun->GetParameter(4));
	  funkaon->SetParameter(2,superfun->GetParameter(5));
	  funpion->Draw("same");
	  funkaon->Draw("same");
	  fbothpionout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(1)
	    <<"\t"
	    <<superfun->GetParError(1)
	    <<"\t"
	    <<superfun->GetParameter(2)
	    <<"\t"
	    <<superfun->GetParError(2)
	    <<"\t"
	    <<endl;
	  fbothkaonout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(4)
	    <<"\t"
	    <<superfun->GetParError(4)
	    <<"\t"
	    <<superfun->GetParameter(5)
	    <<"\t"
	    <<superfun->GetParError(5)
	    <<"\t"
	    <<endl;
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}



      if(i<15)
	{
	  help->GetXaxis()->SetRange(160,220);
	  help->Fit("funproton","","",0.81,0.95);
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_both_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_both_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}

      if(i>=15&&i<20)
	{
	  help->GetXaxis()->SetRange(160,220);
	  help->Fit("funproton","","",0.81,0.97);
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_both_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_both_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}

      if(i>=20&&i<25)
	{
	  help->GetXaxis()->SetRange(160,220);
	  help->Fit("funproton","","",0.79,1.00);
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_both_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_both_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}

      if(i>=25&&i<30)
	{
	  help->GetXaxis()->SetRange(160,220);
	  help->Fit("funproton","","",0.76,1.05);
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_both_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_both_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}


      if(i>=30&&i<40)
	{
	  help->GetXaxis()->SetRange(150,230);
	  help->Fit("funproton","","",0.7,1.1);
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_both_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_both_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}






    } // for loop





  for(int i=0; i<40; i++)
    {

      float mom = i/10.0+0.05;

      if (i<10) hh_flow_pos->ProjectionY("hpos",i+1,i+1);
      //if (i<40) hh_flow_pos->ProjectionY("hpos",i+1,i+1);
      else hh_full_pos->ProjectionY("hpos",i+1,i+1);

      helppos = (TH1F *)hpos->Clone();
      float max = helppos->GetBinContent(helppos->GetMaximumBin());

      if(i<20)
	{
	  helppos->GetXaxis()->SetRange(86,130);
	  helppos->Fit("funpion","","",-0.1,0.1);
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

	  sprintf(pionfigname,"m2pT_figs/m2pT_pos_pion_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_pos_pion_%d.eps",i);
	  c1->Print(pionfigname);

	  helppos->GetXaxis()->SetRange(106,150);
	  helppos->Fit("funkaon","","",0.2,0.3);
	  fposkaonout
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
	  sprintf(kaonfigname,"m2pT_figs/m2pT_pos_kaon_%d.gif",i);
	  c1->Print(kaonfigname);
	  sprintf(kaonfigname,"m2pT_figs/m2pT_pos_kaon_%d.eps",i);
	  c1->Print(kaonfigname);
	}

      if(i>=20&&i<25)
	{
	  helppos->GetXaxis()->SetRange(81,140);
	  helppos->Fit("funpion","","",-0.07,0.07);
	  helppos->Fit("funkaon","","", 0.2,0.3);
	  superfun->SetParameter(0,funpion->GetParameter(0));
	  superfun->SetParameter(1,funpion->GetParameter(1));
	  superfun->SetParameter(2,funpion->GetParameter(2));
	  superfun->SetParameter(3,funkaon->GetParameter(0));
	  superfun->SetParameter(4,funkaon->GetParameter(1));
	  superfun->SetParameter(5,funkaon->GetParameter(2));
	  helppos->Fit("superfun","","",-0.1,0.35);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  funpion->Draw("same");
	  funkaon->Draw("same");
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
	  fposkaonout
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
	  sprintf(pionfigname,"m2pT_figs/m2pT_pos_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_pos_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}
      if(i>=25&&i<30)
	{
	  helppos->GetXaxis()->SetRange(81,140);
	  helppos->Fit("funpion","","",-0.07,0.07);
	  helppos->Fit("funkaon","","", 0.2,0.3);
	  superfun->SetParameter(0,funpion->GetParameter(0));
	  superfun->SetParameter(1,funpion->GetParameter(1));
	  superfun->SetParameter(2,funpion->GetParameter(2));
	  superfun->SetParameter(3,funkaon->GetParameter(0));
	  superfun->SetParameter(4,funkaon->GetParameter(1));
	  superfun->SetParameter(5,funkaon->GetParameter(2));
	  helppos->Fit("superfun","","",-0.1,0.35);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  funpion->SetParameter(0,superfun->GetParameter(0));
	  funpion->SetParameter(1,superfun->GetParameter(1));
	  funpion->SetParameter(2,superfun->GetParameter(2));
	  funkaon->SetParameter(0,superfun->GetParameter(3));
	  funkaon->SetParameter(1,superfun->GetParameter(4));
	  funkaon->SetParameter(2,superfun->GetParameter(5));
	  funpion->Draw("same");
	  funkaon->Draw("same");
	  fpospionout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(1)
	    <<"\t"
	    <<superfun->GetParError(1)
	    <<"\t"
	    <<superfun->GetParameter(2)
	    <<"\t"
	    <<superfun->GetParError(2)
	    <<"\t"
	    <<endl;
	  fposkaonout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(4)
	    <<"\t"
	    <<superfun->GetParError(4)
	    <<"\t"
	    <<superfun->GetParameter(5)
	    <<"\t"
	    <<superfun->GetParError(5)
	    <<"\t"
	    <<endl;
	  sprintf(pionfigname,"m2pT_figs/m2pT_pos_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_pos_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}

      if(i>=30&&i<40)
	{
	  helppos->GetXaxis()->SetRange(71,150);
	  helppos->Fit("funpion","","",-0.15,0.1);
	  helppos->Fit("funkaon","","", 0.2,0.4);
	  superfun->SetParameter(0,funpion->GetParameter(0));
	  superfun->SetParameter(1,funpion->GetParameter(1));
	  superfun->SetParameter(2,funpion->GetParameter(2));
	  superfun->SetParameter(3,funkaon->GetParameter(0));
	  superfun->SetParameter(4,funkaon->GetParameter(1));
	  superfun->SetParameter(5,funkaon->GetParameter(2));
	  helppos->Fit("superfun","","",-0.2,0.4);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  funpion->SetParameter(0,superfun->GetParameter(0));
	  funpion->SetParameter(1,superfun->GetParameter(1));
	  funpion->SetParameter(2,superfun->GetParameter(2));
	  funkaon->SetParameter(0,superfun->GetParameter(3));
	  funkaon->SetParameter(1,superfun->GetParameter(4));
	  funkaon->SetParameter(2,superfun->GetParameter(5));
	  funpion->Draw("same");
	  funkaon->Draw("same");
	  fpospionout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(1)
	    <<"\t"
	    <<superfun->GetParError(1)
	    <<"\t"
	    <<superfun->GetParameter(2)
	    <<"\t"
	    <<superfun->GetParError(2)
	    <<"\t"
	    <<endl;
	  fposkaonout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(4)
	    <<"\t"
	    <<superfun->GetParError(4)
	    <<"\t"
	    <<superfun->GetParameter(5)
	    <<"\t"
	    <<superfun->GetParError(5)
	    <<"\t"
	    <<endl;
	  sprintf(pionfigname,"m2pT_figs/m2pT_pos_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_pos_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}



      if(i<15)
	{
	  helppos->GetXaxis()->SetRange(160,220);
	  helppos->Fit("funproton","","",0.81,0.95);
	  fposprotonout
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_pos_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_pos_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}

      if(i>=15&&i<20)
	{
	  helppos->GetXaxis()->SetRange(160,220);
	  helppos->Fit("funproton","","",0.81,0.97);
	  fposprotonout
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_pos_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_pos_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}

      if(i>=20&&i<25)
	{
	  helppos->GetXaxis()->SetRange(160,220);
	  helppos->Fit("funproton","","",0.79,1.00);
	  fposprotonout
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_pos_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_pos_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}

      if(i>=25&&i<30)
	{
	  helppos->GetXaxis()->SetRange(160,220);
	  helppos->Fit("funproton","","",0.76,1.05);
	  fposprotonout
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_pos_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_pos_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}


      if(i>=30&&i<40)
	{
	  helppos->GetXaxis()->SetRange(150,230);
	  helppos->Fit("funproton","","",0.7,1.1);
	  fposprotonout
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_pos_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_pos_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}






    } // for loop




  for(int i=0; i<40; i++)
    {

      float mom = i/10.0+0.05;

      if (i<10) hh_flow_neg->ProjectionY("hneg",i+1,i+1);
      //if (i<40) hh_flow_neg->ProjectionY("hneg",i+1,i+1);
      else hh_full_neg->ProjectionY("hneg",i+1,i+1);

      helpneg = (TH1F *)hneg->Clone();
      float max = helpneg->GetBinContent(helpneg->GetMaximumBin());

      if(i<20)
	{
	  helpneg->GetXaxis()->SetRange(86,130);
	  helpneg->Fit("funpion","","",-0.1,0.1);
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

	  sprintf(pionfigname,"m2pT_figs/m2pT_neg_pion_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_neg_pion_%d.eps",i);
	  c1->Print(pionfigname);

	  helpneg->GetXaxis()->SetRange(106,150);
	  helpneg->Fit("funkaon","","",0.2,0.3);
	  fnegkaonout
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
	  sprintf(kaonfigname,"m2pT_figs/m2pT_neg_kaon_%d.gif",i);
	  c1->Print(kaonfigname);
	  sprintf(kaonfigname,"m2pT_figs/m2pT_neg_kaon_%d.eps",i);
	  c1->Print(kaonfigname);
	}

      if(i>=20&&i<25)
	{
	  helpneg->GetXaxis()->SetRange(81,140);
	  helpneg->Fit("funpion","","",-0.07,0.07);
	  helpneg->Fit("funkaon","","", 0.2,0.3);
	  superfun->SetParameter(0,funpion->GetParameter(0));
	  superfun->SetParameter(1,funpion->GetParameter(1));
	  superfun->SetParameter(2,funpion->GetParameter(2));
	  superfun->SetParameter(3,funkaon->GetParameter(0));
	  superfun->SetParameter(4,funkaon->GetParameter(1));
	  superfun->SetParameter(5,funkaon->GetParameter(2));
	  helpneg->Fit("superfun","","",-0.1,0.35);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  funpion->Draw("same");
	  funkaon->Draw("same");
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
	  fnegkaonout
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
	  sprintf(pionfigname,"m2pT_figs/m2pT_neg_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_neg_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}
      if(i>=25&&i<30)
	{
	  helpneg->GetXaxis()->SetRange(81,140);
	  helpneg->Fit("funpion","","",-0.07,0.07);
	  helpneg->Fit("funkaon","","", 0.2,0.3);
	  superfun->SetParameter(0,funpion->GetParameter(0));
	  superfun->SetParameter(1,funpion->GetParameter(1));
	  superfun->SetParameter(2,funpion->GetParameter(2));
	  superfun->SetParameter(3,funkaon->GetParameter(0));
	  superfun->SetParameter(4,funkaon->GetParameter(1));
	  superfun->SetParameter(5,funkaon->GetParameter(2));
	  helpneg->Fit("superfun","","",-0.1,0.35);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  funpion->SetParameter(0,superfun->GetParameter(0));
	  funpion->SetParameter(1,superfun->GetParameter(1));
	  funpion->SetParameter(2,superfun->GetParameter(2));
	  funkaon->SetParameter(0,superfun->GetParameter(3));
	  funkaon->SetParameter(1,superfun->GetParameter(4));
	  funkaon->SetParameter(2,superfun->GetParameter(5));
	  funpion->Draw("same");
	  funkaon->Draw("same");
	  fnegpionout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(1)
	    <<"\t"
	    <<superfun->GetParError(1)
	    <<"\t"
	    <<superfun->GetParameter(2)
	    <<"\t"
	    <<superfun->GetParError(2)
	    <<"\t"
	    <<endl;
	  fnegkaonout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(4)
	    <<"\t"
	    <<superfun->GetParError(4)
	    <<"\t"
	    <<superfun->GetParameter(5)
	    <<"\t"
	    <<superfun->GetParError(5)
	    <<"\t"
	    <<endl;
	  sprintf(pionfigname,"m2pT_figs/m2pT_neg_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_neg_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}

      if(i>=30&&i<40)
	{
	  helpneg->GetXaxis()->SetRange(81,140);
	  helpneg->Fit("funpion","","",-0.15,0.1);
	  helpneg->Fit("funkaon","","", 0.2,0.4);
	  superfun->SetParameter(0,funpion->GetParameter(0));
	  superfun->SetParameter(1,funpion->GetParameter(1));
	  superfun->SetParameter(2,funpion->GetParameter(2));
	  superfun->SetParameter(3,funkaon->GetParameter(0));
	  superfun->SetParameter(4,funkaon->GetParameter(1));
	  superfun->SetParameter(5,funkaon->GetParameter(2));
	  helpneg->Fit("superfun","","",-0.2,0.4);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  funpion->SetParameter(0,superfun->GetParameter(0));
	  funpion->SetParameter(1,superfun->GetParameter(1));
	  funpion->SetParameter(2,superfun->GetParameter(2));
	  funkaon->SetParameter(0,superfun->GetParameter(3));
	  funkaon->SetParameter(1,superfun->GetParameter(4));
	  funkaon->SetParameter(2,superfun->GetParameter(5));
	  funpion->Draw("same");
	  funkaon->Draw("same");
	  fnegpionout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(1)
	    <<"\t"
	    <<superfun->GetParError(1)
	    <<"\t"
	    <<superfun->GetParameter(2)
	    <<"\t"
	    <<superfun->GetParError(2)
	    <<"\t"
	    <<endl;
	  fnegkaonout
	    <<mom
	    <<"\t"
	    <<superfun->GetParameter(4)
	    <<"\t"
	    <<superfun->GetParError(4)
	    <<"\t"
	    <<superfun->GetParameter(5)
	    <<"\t"
	    <<superfun->GetParError(5)
	    <<"\t"
	    <<endl;
	  sprintf(pionfigname,"m2pT_figs/m2pT_neg_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_neg_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}


      if(i<15)
	{
	  helpneg->GetXaxis()->SetRange(160,220);
	  helpneg->Fit("funproton","","",0.81,0.95);
	  fnegprotonout
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_neg_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_neg_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}

      if(i>=15&&i<20)
	{
	  helpneg->GetXaxis()->SetRange(160,220);
	  helpneg->Fit("funproton","","",0.81,0.97);
	  fnegprotonout
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_neg_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_neg_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}

      if(i>=20&&i<25)
	{
	  helpneg->GetXaxis()->SetRange(160,220);
	  helpneg->Fit("funproton","","",0.79,1.00);
	  fnegprotonout
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_neg_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_neg_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}

      if(i>=25&&i<30)
	{
	  helpneg->GetXaxis()->SetRange(160,220);
	  helpneg->Fit("funproton","","",0.76,1.05);
	  fnegprotonout
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_neg_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_neg_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}


      if(i>=30&&i<40)
	{
	  helpneg->GetXaxis()->SetRange(150,230);
	  helpneg->Fit("funproton","","",0.7,1.1);
	  fnegprotonout
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

	  sprintf(protonfigname,"m2pT_figs/m2pT_neg_proton_%d.gif",i);
	  c1->Print(protonfigname);
	  sprintf(protonfigname,"m2pT_figs/m2pT_neg_proton_%d.eps",i);
	  c1->Print(protonfigname);

	}


    } // for loop




} // void fitm2


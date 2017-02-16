void fitm2()
{

  TCanvas *c1 = new TCanvas();

  //TFile *fall = TFile::Open("outsum_low.root");
  TFile *fall = TFile::Open("outnew_pp.root");

  //TH2F *hh_full_pos = (TH2F *)fall->Get("m2mompos_dis");
  //TH2F *hh_full_neg = (TH2F *)fall->Get("m2momneg_dis");
  TH2F *hh_full_pos = (TH2F *)fall->Get("m2pTdis_epc_pos");
  TH2F *hh_full_neg = (TH2F *)fall->Get("m2pTdis_epc_neg");

  TF1 *funpion = new TF1("funpion","gaus",-5.0,5.0);
  TF1 *funkaon = new TF1("funkaon","gaus",-5.0,5.0);
  TF1 *superfun = new TF1("superfun","gaus(0)+gaus(3)",-5.0,5.0);
  TF1 *funproton = new TF1("funproton","gaus",-5.0,5.0);
  //TF1 *helperfun = new TF1("helperfun","gaus",-5.0,5.0);
  //helperfun->SetLineColor(kBlack);
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


  TH1F *hdummy = new TH1F("hdummy","",1,-0.1,0.1);

  TH1F *help;
  TH1F *helppos;
  TH1F *helpneg;


  for(int i=0; i<40; i++)
    {

      float mom = i/10.0+0.05;

      hh_full_pos->ProjectionY("hhpos",i+1,i+1);
      hh_full_neg->ProjectionY("hhneg",i+1,i+1);

      TH1F *hh = (TH1F *)hhpos->Clone();
      hh->Add(hhneg);

      help = (TH1F *)hh->Clone();
      float max = help->GetBinContent(help->GetMaximumBin());

      if(i<15)
	{
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(86,130);
	  help->Fit("funpion","","",-0.02,0.05);//0.05 a little low, 0.06 a little high
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

	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pion_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pion_%d.eps",i);
	  c1->Print(pionfigname);

	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(106,150);
	  help->Fit("funkaon","","",0.21,0.28);
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

      if(i>=15&&i<20)
	{
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(86,130);
	  help->Fit("funpion","","",-0.04,0.075);//0.08 a little high...
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

	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pion_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pion_%d.eps",i);
	  c1->Print(pionfigname);

	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(106,150);
	  help->Fit("funkaon","","",0.19,0.31);
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

      if(i>=20&&i<22)
	{
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(81,140);
	  help->Fit("funpion","","",-0.07,0.07);
	  help->Fit("funkaon","","", 0.2,0.3);
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
      if(i>=22&&i<25)
	{
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(81,140);
	  help->Fit("funpion","","",-0.07,0.07);
	  help->Fit("funkaon","","", 0.2,0.3);
	  superfun->SetParameter(0,funpion->GetParameter(0));
	  superfun->SetParameter(1,funpion->GetParameter(1));
	  superfun->SetParameter(2,funpion->GetParameter(2));
	  superfun->SetParameter(3,funkaon->GetParameter(0));
	  superfun->SetParameter(4,funkaon->GetParameter(1));
	  superfun->SetParameter(5,funkaon->GetParameter(2));
	  superfun->SetLineColor(kBlack);//new
	  help->Fit("superfun","","",-0.1,0.35);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  funpion->SetParameter(0,superfun->GetParameter(0));//new here
	  funpion->SetParameter(1,superfun->GetParameter(1));//new here
	  funpion->SetParameter(2,superfun->GetParameter(2));//new here
	  funkaon->SetParameter(0,superfun->GetParameter(3));//new here
	  funkaon->SetParameter(1,superfun->GetParameter(4));//new here
	  funkaon->SetParameter(2,superfun->GetParameter(5));//new here
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
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(81,140);
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
	  help->SetMinimum(0);
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


      // COME BACK HERE FOR PROTONS!!!

      if(i<15)
	{
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(160,220);
	  //help->Fit("funproton","","",0.81,0.95);
	  help->Fit("funproton","","",0.80,0.95);
	  funproton->SetLineColor(kBlack);
	  funproton->Draw("same");
	  TF1 *helperfun1 = new TF1("helperfun1","gaus",0.80,0.95);
	  helperfun1->SetParameter(0,funproton->GetParameter(0));
	  helperfun1->SetParameter(1,funproton->GetParameter(1));
	  helperfun1->SetParameter(2,funproton->GetParameter(2));
	  helperfun1->Draw("same");
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
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(160,220);
	  //help->Fit("funproton","","",0.81,0.97);
	  help->Fit("funproton","","",0.79,0.98);
	  funproton->SetLineColor(kBlack);
	  funproton->Draw("same");
	  TF1 *helperfun2 = new TF1("helperfun2","gaus",0.79,0.98);
	  helperfun2->SetParameter(0,funproton->GetParameter(0));
	  helperfun2->SetParameter(1,funproton->GetParameter(1));
	  helperfun2->SetParameter(2,funproton->GetParameter(2));
	  helperfun2->Draw("same");
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
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(160,220);//CONSIDER REVISING
	  help->Fit("funproton","","",0.79,1.00);
	  funproton->SetLineColor(kBlack);
	  funproton->Draw("same");
	  TF1 *helperfun3 = new TF1("helperfun3","gaus",0.79,1.00);
	  helperfun3->SetParameter(0,funproton->GetParameter(0));
	  helperfun3->SetParameter(1,funproton->GetParameter(1));
	  helperfun3->SetParameter(2,funproton->GetParameter(2));
	  helperfun3->Draw("same");
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
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(141,240); // GOOD REVISION, MAYBE REDO ANYWAY
	  help->Fit("funproton","","",0.76,1.05);
	  funproton->SetLineColor(kBlack);
	  funproton->Draw("same");
	  TF1 *helperfun4 = new TF1("helperfun4","gaus",0.76,1.05);
	  helperfun4->SetParameter(0,funproton->GetParameter(0));
	  helperfun4->SetParameter(1,funproton->GetParameter(1));
	  helperfun4->SetParameter(2,funproton->GetParameter(2));
	  helperfun4->Draw("same");
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
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(51,250);
	  help->Fit("funproton","","",0.7,1.1);
	  funproton->SetLineColor(kBlack);
	  funproton->Draw("same");
	  TF1 *helperfun5 = new TF1("helperfun5","gaus",0.7,1.1);
	  helperfun5->SetParameter(0,funproton->GetParameter(0));
	  helperfun5->SetParameter(1,funproton->GetParameter(1));
	  helperfun5->SetParameter(2,funproton->GetParameter(2));
	  helperfun5->Draw("same");
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








} // void fitm2


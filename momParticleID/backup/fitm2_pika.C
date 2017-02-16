void fitm2()
{

  TCanvas *c1 = new TCanvas();

  TFile *flow = TFile::Open("outlowpm.root");
  TFile *full = TFile::Open("outpm.root");

  TH2F *hh_flow_pos = (TH2F *)flow->Get("m2momdis_pos");
  TH2F *hh_full_pos = (TH2F *)full->Get("m2momdis_pos");
  TH2F *hh_flow_neg = (TH2F *)flow->Get("m2momdis_neg");
  TH2F *hh_full_neg = (TH2F *)full->Get("m2momdis_neg");

  TF1 *funpion = new TF1("funpion","gaus",-5.0,5.0);
  TF1 *funkaon = new TF1("funkaon","gaus",-5.0,5.0);
  TF1 *superfun = new TF1("superfun","gaus(0)+gaus(3)",-5.0,5.0);
  // fixing the mean makes the fits very bad
  //funpion->FixParameter(1,0.01948);
  //funkaon->FixParameter(1,0.24332);
  //superfun->FixParameter(1,0.01948);
  //superfun->FixParameter(4,0.24332);

  char pionfigname[100];
  char kaonfigname[100];

  ofstream fpospionout("m2mom_pos_pion_par.txt");
  ofstream fposkaonout("m2mom_pos_kaon_par.txt");
  ofstream fnegpionout("m2mom_neg_pion_par.txt");
  ofstream fnegkaonout("m2mom_neg_kaon_par.txt");

  TH1F *hdummy = new TH1F("hdummy","",1,-0.1,0.1);

  TH1F *help;




  for(int i=0; i<40; i++)
    {

      float mom = i/10.0+0.05;

      //if (i<10) hh_flow_pos->ProjectionY("hh",i+1,i+1);
      if (i<40) hh_flow_pos->ProjectionY("hh",i+1,i+1);
      else hh_full_pos->ProjectionY("hh",i+1,i+1);

      help = (TH1F *)hh->Clone();
      float max = help->GetBinContent(help->GetMaximumBin());

      if(i<20)
	{
	  help->GetXaxis()->SetRange(86,130);
	  help->Fit("funpion","","",-0.1,0.1);
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

	  sprintf(pionfigname,"m2mom_figs/m2mom_pos_pion_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2mom_figs/m2mom_pos_pion_%d.eps",i);
	  c1->Print(pionfigname);

	  help->GetXaxis()->SetRange(106,150);
	  help->Fit("funkaon","","",0.2,0.3);
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
	  sprintf(kaonfigname,"m2mom_figs/m2mom_pos_kaon_%d.gif",i);
	  c1->Print(kaonfigname);
	  sprintf(kaonfigname,"m2mom_figs/m2mom_pos_kaon_%d.eps",i);
	  c1->Print(kaonfigname);
	}

      if(i>=20&&i<25)
	{
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
	  sprintf(pionfigname,"m2mom_figs/m2mom_pos_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2mom_figs/m2mom_pos_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}
      if(i>=25&&i<30)
	{
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
	  sprintf(pionfigname,"m2mom_figs/m2mom_pos_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2mom_figs/m2mom_pos_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}

      if(i>=30&&i<40)
	{
	  help->GetXaxis()->SetRange(81,140);
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
	  sprintf(pionfigname,"m2mom_figs/m2mom_pos_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2mom_figs/m2mom_pos_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}



      //sprintf(pionfigname,"m2mom_figs/m2mom_pos_pion_%d.gif",i);
      //c1->Print(pionfigname);
      //sprintf(pionfigname,"m2mom_figs/m2mom_pos_pion_%d.eps",i);
      //c1->Print(pionfigname);


    } // for loop




  for(int i=0; i<40; i++)
    {

      float mom = i/10.0+0.05;

      //if (i<10) hh_flow_neg->ProjectionY("hh",i+1,i+1);
      if (i<40) hh_flow_neg->ProjectionY("hh",i+1,i+1);
      else hh_full_neg->ProjectionY("hh",i+1,i+1);

      help = (TH1F *)hh->Clone();
      float max = help->GetBinContent(help->GetMaximumBin());

      if(i<20)
	{
	  help->GetXaxis()->SetRange(86,130);
	  help->Fit("funpion","","",-0.1,0.1);
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

	  sprintf(pionfigname,"m2mom_figs/m2mom_neg_pion_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2mom_figs/m2mom_neg_pion_%d.eps",i);
	  c1->Print(pionfigname);

	  help->GetXaxis()->SetRange(106,150);
	  help->Fit("funkaon","","",0.2,0.3);
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
	  sprintf(kaonfigname,"m2mom_figs/m2mom_neg_kaon_%d.gif",i);
	  c1->Print(kaonfigname);
	  sprintf(kaonfigname,"m2mom_figs/m2mom_neg_kaon_%d.eps",i);
	  c1->Print(kaonfigname);
	}

      if(i>=20&&i<25)
	{
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
	  sprintf(pionfigname,"m2mom_figs/m2mom_neg_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2mom_figs/m2mom_neg_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}
      if(i>=25&&i<30)
	{
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
	  sprintf(pionfigname,"m2mom_figs/m2mom_neg_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2mom_figs/m2mom_neg_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}

      if(i>=30&&i<40)
	{
	  help->GetXaxis()->SetRange(81,140);
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
	  sprintf(pionfigname,"m2mom_figs/m2mom_neg_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2mom_figs/m2mom_neg_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}



      //sprintf(pionfigname,"m2mom_figs/m2mom_neg_pion_%d.gif",i);
      //c1->Print(pionfigname);
      //sprintf(pionfigname,"m2mom_figs/m2mom_neg_pion_%d.eps",i);
      //c1->Print(pionfigname);


    } // for loop




} // void fitm2

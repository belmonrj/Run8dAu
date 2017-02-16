void fitm2_pika()
{

  TCanvas *c1 = new TCanvas();

  //TFile *fall = TFile::Open("outsum_low.root");
  TFile *fall = TFile::Open("outnew_pp.root");

  TH2F *hh_full_pos = (TH2F *)fall->Get("m2pTdis_pos");
  TH2F *hh_full_neg = (TH2F *)fall->Get("m2pTdis_neg");

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


  // ofstream fbothpionout("m2pT_both_pion_par.txt");
  // ofstream fbothkaonout("m2pT_both_kaon_par.txt");
  // ofstream fbothprotonout("m2pT_both_proton_par.txt");


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




      if(i<10)
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
	  // fbothpionout
	  //   <<mom
	  //   <<"\t"
	  //   <<funpion->GetParameter(1)
	  //   <<"\t"
	  //   <<funpion->GetParError(1)
	  //   <<"\t"
	  //   <<funpion->GetParameter(2)
	  //   <<"\t"
	  //   <<funpion->GetParError(2)
	  //   <<"\t"
	  //   <<endl;
	  // fbothkaonout
	  //   <<mom
	  //   <<"\t"
	  //   <<funkaon->GetParameter(1)
	  //   <<"\t"
	  //   <<funkaon->GetParError(1)
	  //   <<"\t"
	  //   <<funkaon->GetParameter(2)
	  //   <<"\t"
	  //   <<funkaon->GetParError(2)
	  //   <<"\t"
	  //   <<endl;
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}


      if(i>=10&&i<15)
	{
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(81,140);
	  help->Fit("funpion","","",-0.03,0.06);
	  help->Fit("funkaon","","", 0.2,0.3);
	  superfun->SetParameter(0,funpion->GetParameter(0));
	  superfun->SetParameter(1,funpion->GetParameter(1));
	  superfun->SetParameter(2,funpion->GetParameter(2));
	  superfun->SetParameter(3,funkaon->GetParameter(0));
	  superfun->SetParameter(4,funkaon->GetParameter(1));
	  superfun->SetParameter(5,funkaon->GetParameter(2));
	  superfun->SetLineColor(kBlack);//new
	  superfun->Draw("same");//experimental
	  // help->Fit("superfun","","",-0.05,0.35);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  // funpion->SetParameter(0,superfun->GetParameter(0));//new here
	  // funpion->SetParameter(1,superfun->GetParameter(1));//new here
	  // funpion->SetParameter(2,superfun->GetParameter(2));//new here
	  // funkaon->SetParameter(0,superfun->GetParameter(3));//new here
	  // funkaon->SetParameter(1,superfun->GetParameter(4));//new here
	  // funkaon->SetParameter(2,superfun->GetParameter(5));//new here
	  funpion->Draw("same");
	  funkaon->Draw("same");
	  //drawing it the second time makes funpion and funkaon flatten to 0... odd
	  //onsecond though, i think you just cant see the functions underneath
	  superfun->Draw("same");//experimental // doesn't appear to show up?
	  // fbothpionout
	  //   <<mom
	  //   <<"\t"
	  //   <<funpion->GetParameter(1)
	  //   <<"\t"
	  //   <<funpion->GetParError(1)
	  //   <<"\t"
	  //   <<funpion->GetParameter(2)
	  //   <<"\t"
	  //   <<funpion->GetParError(2)
	  //   <<"\t"
	  //   <<endl;
	  // fbothkaonout
	  //   <<mom
	  //   <<"\t"
	  //   <<funkaon->GetParameter(1)
	  //   <<"\t"
	  //   <<funkaon->GetParError(1)
	  //   <<"\t"
	  //   <<funkaon->GetParameter(2)
	  //   <<"\t"
	  //   <<funkaon->GetParError(2)
	  //   <<"\t"
	  //   <<endl;
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}



      if(i>=15&&i<22)
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
	  // help->Fit("superfun","","",-0.1,0.35);
	  funpion->SetLineColor(kBlue);
	  funkaon->SetLineColor(kGreen+2);
	  // funpion->SetParameter(0,superfun->GetParameter(0));//new here
	  // funpion->SetParameter(1,superfun->GetParameter(1));//new here
	  // funpion->SetParameter(2,superfun->GetParameter(2));//new here
	  // funkaon->SetParameter(0,superfun->GetParameter(3));//new here
	  // funkaon->SetParameter(1,superfun->GetParameter(4));//new here
	  // funkaon->SetParameter(2,superfun->GetParameter(5));//new here
	  funpion->Draw("same");
	  funkaon->Draw("same");
	  superfun->Draw("same"); // exp?
	  // fbothpionout
	  //   <<mom
	  //   <<"\t"
	  //   <<funpion->GetParameter(1)
	  //   <<"\t"
	  //   <<funpion->GetParError(1)
	  //   <<"\t"
	  //   <<funpion->GetParameter(2)
	  //   <<"\t"
	  //   <<funpion->GetParError(2)
	  //   <<"\t"
	  //   <<endl;
	  // fbothkaonout
	  //   <<mom
	  //   <<"\t"
	  //   <<funkaon->GetParameter(1)
	  //   <<"\t"
	  //   <<funkaon->GetParError(1)
	  //   <<"\t"
	  //   <<funkaon->GetParameter(2)
	  //   <<"\t"
	  //   <<funkaon->GetParError(2)
	  //   <<"\t"
	  //   <<endl;
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
	  // fbothpionout
	  //   <<mom
	  //   <<"\t"
	  //   <<funpion->GetParameter(1)
	  //   <<"\t"
	  //   <<funpion->GetParError(1)
	  //   <<"\t"
	  //   <<funpion->GetParameter(2)
	  //   <<"\t"
	  //   <<funpion->GetParError(2)
	  //   <<"\t"
	  //   <<endl;
	  // fbothkaonout
	  //   <<mom
	  //   <<"\t"
	  //   <<funkaon->GetParameter(1)
	  //   <<"\t"
	  //   <<funkaon->GetParError(1)
	  //   <<"\t"
	  //   <<funkaon->GetParameter(2)
	  //   <<"\t"
	  //   <<funkaon->GetParError(2)
	  //   <<"\t"
	  //   <<endl;
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
	  // fbothpionout
	  //   <<mom
	  //   <<"\t"
	  //   <<superfun->GetParameter(1)
	  //   <<"\t"
	  //   <<superfun->GetParError(1)
	  //   <<"\t"
	  //   <<superfun->GetParameter(2)
	  //   <<"\t"
	  //   <<superfun->GetParError(2)
	  //   <<"\t"
	  //   <<endl;
	  // fbothkaonout
	  //   <<mom
	  //   <<"\t"
	  //   <<superfun->GetParameter(4)
	  //   <<"\t"
	  //   <<superfun->GetParError(4)
	  //   <<"\t"
	  //   <<superfun->GetParameter(5)
	  //   <<"\t"
	  //   <<superfun->GetParError(5)
	  //   <<"\t"
	  //   <<endl;
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
	  // fbothpionout
	  //   <<mom
	  //   <<"\t"
	  //   <<superfun->GetParameter(1)
	  //   <<"\t"
	  //   <<superfun->GetParError(1)
	  //   <<"\t"
	  //   <<superfun->GetParameter(2)
	  //   <<"\t"
	  //   <<superfun->GetParError(2)
	  //   <<"\t"
	  //   <<endl;
	  // fbothkaonout
	  //   <<mom
	  //   <<"\t"
	  //   <<superfun->GetParameter(4)
	  //   <<"\t"
	  //   <<superfun->GetParError(4)
	  //   <<"\t"
	  //   <<superfun->GetParameter(5)
	  //   <<"\t"
	  //   <<superfun->GetParError(5)
	  //   <<"\t"
	  //   <<endl;
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.gif",i);
	  c1->Print(pionfigname);
	  sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_%d.eps",i);
	  c1->Print(pionfigname);
	}



    } // for loop








} // void fitm2


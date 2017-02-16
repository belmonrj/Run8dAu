void fitm2_pika4()
{

  TCanvas *c1 = new TCanvas();

  //TFile *fall = TFile::Open("outsum_low.root");
  TFile *fall = TFile::Open("outnew_pp.root");

  TH2F *hh_full_pos = (TH2F *)fall->Get("m2pTdis_pos");
  TH2F *hh_full_neg = (TH2F *)fall->Get("m2pTdis_neg");

  TF1 *funpion = new TF1("funpion","gaus",-5.0,5.0);
  TF1 *funkaon = new TF1("funkaon","gaus",-5.0,5.0);
  TF1 *funpionA = new TF1("funpionA","gaus",-5.0,5.0);
  TF1 *funkaonA = new TF1("funkaonA","gaus",-5.0,5.0);
  TF1 *superfun = new TF1("superfun","gaus(0)+gaus(3)",-5.0,5.0);
  TF1 *funproton = new TF1("funproton","gaus",-5.0,5.0);
  //TF1 *helperfun = new TF1("helperfun","gaus",-5.0,5.0);
  //helperfun->SetLineColor(kBlack);
  // fixing the mean makes the fits very bad
  //funpion->FixParameter(1,0.01948);
  //funkaon->FixParameter(1,0.24332);
  //superfun->FixParameter(1,0.01948);
  //superfun->FixParameter(4,0.24332);

  funpion->SetLineColor(kBlue);
  funkaon->SetLineColor(kGreen+2);
  funpionA->SetLineColor(kBlue);
  funkaonA->SetLineColor(kGreen+2);
  superfun->SetLineColor(kBlack);

  char pionfigname[100];
  char kaonfigname[100];
  char protonfigname[100];



  TF1 *sigmapi = new TF1("sigmapi","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,5.0);
  TF1 *sigmaka = new TF1("sigmaka","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.3,5.0);
  TF1 *sigmapr = new TF1("sigmapr","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.5,5.0);


  sigmapi->SetParameter(0, 5.99661e-02);
  sigmapi->SetParameter(1,-4.08485e-02);
  sigmapi->SetParameter(2, 6.99457e-03);
  sigmapi->SetParameter(3, 8.21363e-02);
  sigmapi->SetParameter(4,-2.34551e-01);
  
  sigmaka->SetParameter(0,0.00465694);  
  sigmaka->SetParameter(1,-0.0474435);
  sigmaka->SetParameter(2, 0.0180152);
  sigmaka->SetParameter(3, 0.0701986); 
  sigmaka->SetParameter(4, -0.148939); 

  sigmapr->SetParameter(0,-0.0505685);  
  sigmapr->SetParameter(1, 0.0231001);
  sigmapr->SetParameter(2,-0.0020908);
  sigmapr->SetParameter(3, 0.0777132);
  sigmapr->SetParameter(4, -0.144319);



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
	}
      if(i>=10&&i<15)
	{
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(81,140);
	  help->Fit("funpion","","",-0.03,0.06);
	  help->Fit("funkaon","","", 0.2,0.3);
	}
      if(i>=15&&i<22)
	{
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(81,140);
	  help->Fit("funpion","","",-0.07,0.07);
	  help->Fit("funkaon","","", 0.2,0.3);
	}
      if(i>=22&&i<25)
	{
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(81,140);
	  help->Fit("funpion","","",-0.07,0.07);
	  help->Fit("funkaon","","", 0.2,0.3);
	}
      if(i>=25&&i<30)
	{
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(81,140);
	  help->Fit("funpion","","",-0.07,0.07);
	  help->Fit("funkaon","","", 0.2,0.3);
	}
      if(i>=30&&i<40)
	{
	  help->SetMinimum(0);
	  help->GetXaxis()->SetRange(71,150);
	  help->Fit("funpion","","",-0.15,0.1);
	  help->Fit("funkaon","","", 0.2,0.4);
	}
	 

      superfun->SetParameter(0,funpion->GetParameter(0));
      //superfun->SetParameter(1,funpion->GetParameter(1));
      //superfun->SetParameter(2,funpion->GetParameter(2));
      superfun->SetParameter(3,funkaon->GetParameter(0));
      //superfun->SetParameter(4,funkaon->GetParameter(1));
      //superfun->SetParameter(5,funkaon->GetParameter(2));
      // now set the par limits for fitting
      //superfun->SetParLimits(0,0.9*funpion->GetParameter(0),1.1*funpion->GetParameter(0));
      superfun->SetParLimits(1,0.9*funpion->GetParameter(1),1.1*funpion->GetParameter(1));
      superfun->SetParLimits(2,0.9*sigmapi->Eval(mom),1.1*sigmapi->Eval(mom)); // sigma
      //superfun->SetParLimits(3,0.9*funkaon->GetParameter(0),1.1*funkaon->GetParameter(0));
      superfun->SetParLimits(4,0.9*funkaon->GetParameter(1),1.1*funkaon->GetParameter(1));
      superfun->SetParLimits(5,0.9*sigmaka->Eval(mom),1.1*sigmaka->Eval(mom)); // sigma
      // funpion->Draw("same");
      // funkaon->Draw("same");
      // superfun->Draw("same");
      // sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_method1_%d.gif",i);
      // c1->Print(pionfigname);
      // sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_method1_%d.eps",i);
      // c1->Print(pionfigname);
      help->Fit("superfun","","",-0.2,0.4);
      funpionA->SetParameter(0,superfun->GetParameter(0));
      funpionA->SetParameter(1,superfun->GetParameter(1));
      funpionA->SetParameter(2,superfun->GetParameter(2));
      funkaonA->SetParameter(0,superfun->GetParameter(3));
      funkaonA->SetParameter(1,superfun->GetParameter(4));
      funkaonA->SetParameter(2,superfun->GetParameter(5));
      funpionA->Draw("same");
      funkaonA->Draw("same");
      sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_method4_%d.gif",i);
      c1->Print(pionfigname);
      sprintf(pionfigname,"m2pT_figs/m2pT_both_pionkaon_method4_%d.eps",i);
      c1->Print(pionfigname);




    } // for loop












} // void fitm2


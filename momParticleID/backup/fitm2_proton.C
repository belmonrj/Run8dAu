void fitm2_proton()
{

  TCanvas *c1 = new TCanvas();

  TFile *flow = TFile::Open("outlowpm.root");
  TFile *full = TFile::Open("outpm.root");

  TH2F *hh_flow_pos = (TH2F *)flow->Get("m2pTdis_pos");
  TH2F *hh_full_pos = (TH2F *)full->Get("m2pTdis_pos");
  TH2F *hh_flow_neg = (TH2F *)flow->Get("m2pTdis_neg");
  TH2F *hh_full_neg = (TH2F *)full->Get("m2pTdis_neg");

  TF1 *funproton = new TF1("funproton","gaus",-5.0,5.0);

  char protonfigname[100];

  ofstream fbothprotonout("m2pT_both_proton_par.txt");
  //ofstream fposprotonout("m2pT_pos_proton_par.txt");
  //ofstream fnegprotonout("m2pT_neg_proton_par.txt");


  TH1F *hdummy = new TH1F("hdummy","",1,-0.1,0.1);

  TH1F *help;


  for(int i=0; i<50; i++)
    {

      float mom = i/10.0+0.05;

      if (i<10) hh_flow_pos->ProjectionY("hhpos",i+1,i+1);
      //if (i<40) hh_flow_pos->ProjectionY("hhpos",i+1,i+1);
      else hh_full_pos->ProjectionY("hhpos",i+1,i+1);
      if (i<10) hh_flow_neg->ProjectionY("hhneg",i+1,i+1);
      //if (i<40) hh_flow_neg->ProjectionY("hhneg",i+1,i+1);
      else hh_full_neg->ProjectionY("hhneg",i+1,i+1);

      TH1F *hh = (TH1F *)hhpos->Clone();
      hh->Add(hhneg);

      help = (TH1F *)hh->Clone();
      float max = help->GetBinContent(help->GetMaximumBin());


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


      if(i>=40&&i<50)
	{
	  help->GetXaxis()->SetRange(100,300);
	  help->Rebin(2);
	  help->Fit("funproton","","",0.6,1.2);
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

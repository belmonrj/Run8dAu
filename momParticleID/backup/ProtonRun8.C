void ProtonRun8()
{

  cout<<"starting!"<<endl;

  TCanvas *c1 = new TCanvas();

  TFile *frun8 = TFile::Open("../TofwCali/outall.root");

  TH2F *hh_run8_pos = frun8->Get("m2mompos_dis");
  TH2F *hh_run8_neg = frun8->Get("m2momneg_dis");

  TF1 *fun = new TF1("fun","gaus",-1,2);
  fun->SetLineColor(kRed);

  TF1 *funF = new TF1("funF","gaus",-1,2);
  funF->FixParameter(1,0.88035);
  funF->SetLineColor(kRed);

  float mom, mean, emean, sigma, esigma;

  char posfigname[50];
  char negfigname[50];

  ofstream fout_run8_pos("proton/protonrun8pos.dat");
  ofstream fout_run8_neg("proton/protonrun8neg.dat");

  for(int i=0; i<50; i++)
    {
      mom = i/10.0+0.05;

      sprintf(posfigname,"proton/figs/protonrun8pos_mom_%d.gif",i);
      hh_run8_pos->ProjectionY("hpos",i+1,i+1);
      hpos->Fit("fun","","",0.6,1.2);
      c1->Print(posfigname);
      mean = fun->GetParameter(1);
      emean = fun->GetParError(1);
      sigma = fun->GetParameter(2);
      esigma = fun->GetParError(2);
      fout_run8_pos<<mom<<"\t"<<mean<<"\t"<<emean<<"\t"<<sigma<<"\t"<<esigma<<endl;

      sprintf(negfigname,"proton/figs/protonrun8neg_mom_%d.gif",i);
      hh_run8_neg->ProjectionY("hneg",i+1,i+1);
      hneg->Fit("fun","","",0.6,1.2);
      c1->Print(negfigname);
      mean = fun->GetParameter(1);
      emean = fun->GetParError(1);
      sigma = fun->GetParameter(2);
      esigma = fun->GetParError(2);
      fout_run8_neg<<mom<<"\t"<<mean<<"\t"<<emean<<"\t"<<sigma<<"\t"<<esigma<<endl;

      break;

    }

  for(int i=0; i<12; i++)
    {
      mom = i/2.0+0.25;
      int j=i*5;
      sprintf(posfigname,"proton/figs/protonrun8pos_mom_rebin_%d.gif",j);
      hh_run8_pos->ProjectionY("hpos",j+1,j+5);
      hpos->Fit("funF","","",0.6,1.2);
      c1->Print(posfigname);
      mean = funF->GetParameter(1);
      emean = funF->GetParError(1);
      sigma = funF->GetParameter(2);
      esigma = funF->GetParError(2);
      fout_run8_pos<<mom<<"\t"<<mean<<"\t"<<emean<<"\t"<<sigma<<"\t"<<esigma<<endl;

      sprintf(negfigname,"proton/figs/protonrun8neg_mom_rebin_%d.gif",j);
      hh_run8_neg->ProjectionY("hneg",j+1,j+5);
      hneg->Fit("funF","","",0.6,1.2);
      c1->Print(negfigname);
      mean = funF->GetParameter(1);
      emean = funF->GetParError(1);
      sigma = funF->GetParameter(2);
      esigma = funF->GetParError(2);
      fout_run8_neg<<mom<<"\t"<<mean<<"\t"<<emean<<"\t"<<sigma<<"\t"<<esigma<<endl;

      break;

    }

  TF1 *funproton = new TF1("funproton","gaus",0.6,1.2);
  funproton->FixParameter(1,0.88035);
  funproton->SetLineColor(kBlue);
  TF1 *funproton2 = new TF1("funproton2","gaus",0.6,1.2);
  //funproton2->FixParameter(1,0.88035);
  funproton2->SetLineColor(kBlue);

  TF1 *funpion = new TF1("funpion","gaus",-0.5,0.3);
  //funpion->FixParameter(1,0.01948);
  funpion->SetLineColor(kGreen+2);
  TF1 *funpion2 = new TF1("funpion2","gaus",-0.5,0.3);
  //funpion2->FixParameter(1,0.01948);
  funpion2->SetLineColor(kGreen+2);

  TF1 *funS = new TF1("funS","gaus(0)+gaus(3)",-0.5,1.2);
  funS->FixParameter(4,0.88035);
  //funS->FixParameter(4,0.01948);
  funS->SetLineColor(kRed);

  float pionconst, pionmean, pionsigma, protonconst, protonmean, protonsigma;

  for(int i=0; i<12; i++)
    {
      mom = i/2.0+0.25;
      int j=i*5;
      sprintf(posfigname,"proton/figs/protonrun8pos_mom_DGrebin_%d.gif",j);
      hh_run8_pos->ProjectionY("hpos",j+1,j+5);
      //funpion->SetRange(-0.5,0.3)
      hpos->Fit("funpion","R");
      //funproton->SetRange(0.6,1.2)
      hpos->Fit("funproton","R");
      pionconst = funpion->GetParameter(0);
      pionmean  = funpion->GetParameter(1);
      pionsigma = funpion->GetParameter(2);
      protonconst = funproton->GetParameter(0);
      protonmean  = funproton->GetParameter(1);
      protonsigma = funproton->GetParameter(2);
      funS->SetParameter(0,pionconst);
      funS->SetParameter(1,pionmean);
      funS->SetParameter(2,pionsigma);
      funS->SetParameter(3,protonconst);
      //funS->SetParameter(4,protonmean);
      funS->SetParameter(5,protonsigma);
      funpion2->SetParameter(0,pionconst);
      funpion2->SetParameter(1,pionmean);
      funpion2->SetParameter(2,pionsigma);
      //cout<<endl<<endl<<"proton const is "<<protonconst<<endl<<endl<<endl;;
      funproton2->SetParameter(0,protonconst);
      funproton2->SetParameter(1,protonmean);
      //funproton2->SetParameter(2,protonsigma);
      funproton2->SetParameter(2,funS->GetParameter(5));
      hpos->Fit("funS","R");
      cout<<endl<<endl<<endl<<"invidual proton fit sigma is "<<protonsigma<<endl;
      cout<<"but proton sigma from double gauss fit is "<<funS->GetParameter(5)<<endl<<endl<<endl;;
      funproton2->SetRange(protonmean-2.0*protonsigma,protonmean+2.0*protonsigma);
      funproton2->Draw("same");
      funpion2->SetRange(pionmean-2.0*pionsigma,pionmean+2.0*pionsigma);
      funpion2->Draw("same");
      c1->Print(posfigname);
      mean = funS->GetParameter(1);
      emean = funS->GetParError(1);
      sigma = funS->GetParameter(2);
      esigma = funS->GetParError(2);
      fout_run8_pos<<mom<<"\t"<<mean<<"\t"<<emean<<"\t"<<sigma<<"\t"<<esigma<<endl;

      sprintf(negfigname,"proton/figs/protonrun8neg_mom_DGrebin_%d.gif",j);
      hh_run8_neg->ProjectionY("hneg",j+1,j+5);
      hneg->Fit("funS","R");
      c1->Print(negfigname);
      mean = funS->GetParameter(1);
      emean = funS->GetParError(1);
      sigma = funS->GetParameter(2);
      esigma = funS->GetParError(2);
      fout_run8_neg<<mom<<"\t"<<mean<<"\t"<<emean<<"\t"<<sigma<<"\t"<<esigma<<endl;

      if(j>40) break;

    }

  cout<<"done. have a nice day!"<<endl;

}

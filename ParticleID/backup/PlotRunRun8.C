void PlotRunRun8()
{

  cout<<"starting!"<<endl;

  //gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);

  ifstream fin_run8pp_pos("runrun8pppos.dat");
  ifstream fin_run8pp_neg("runrun8ppneg.dat");
  ifstream fin_run8mm_pos("runrun8mmpos.dat");
  ifstream fin_run8mm_neg("runrun8mmneg.dat");

  float run_pppos[848], mean_pppos[848], emean_pppos[848], sigma_pppos[848], esigma_pppos[848];
  float run_ppneg[848], mean_ppneg[848], emean_ppneg[848], sigma_ppneg[848], esigma_ppneg[848];
  float run_mmpos[848], mean_mmpos[848], emean_mmpos[848], sigma_mmpos[848], esigma_mmpos[848];
  float run_mmneg[848], mean_mmneg[848], emean_mmneg[848], sigma_mmneg[848], esigma_mmneg[848];
  float zero[848]={0};

  TF1 *fprot = new TF1("fprot","pol0",0,847);
  fprot->SetLineWidth(2);
  fprot->SetLineColor(kRed);
  fprot->SetParameter(0,0.88);

  for(int i=0; i<848; i++)
    {
      fin_run8pp_pos>>run_pppos[i]>>mean_pppos[i]>>emean_pppos[i]>>sigma_pppos[i]>>esigma_pppos[i];
      //if(emean_pppos[i]==(float)1.41421)
      if(emean_pppos[i]>0.1)
	{
	  //cout<<emean_pppos[i]<<endl;
	  mean_pppos[i]=-9;
	  emean_pppos[i]=0;
	  //cout<<emean_pppos[i]<<endl;
	}
      fin_run8pp_neg>>run_ppneg[i]>>mean_ppneg[i]>>emean_ppneg[i]>>sigma_ppneg[i]>>esigma_ppneg[i];
      //if(emean_ppneg[i]==(float)1.41421)
      if(emean_ppneg[i]>0.1)
	{
	  mean_ppneg[i]=-9; emean_ppneg[i]=0;
	}
      fin_run8mm_pos>>run_mmpos[i]>>mean_mmpos[i]>>emean_mmpos[i]>>sigma_mmpos[i]>>esigma_mmpos[i];
      //if(emean_mmpos[i]==(float)1.41421)
      if(emean_mmpos[i]>0.1)
	{
	  mean_mmpos[i]=-9; emean_mmpos[i]=0;
	}
      fin_run8mm_neg>>run_mmneg[i]>>mean_mmneg[i]>>emean_mmneg[i]>>sigma_mmneg[i]>>esigma_mmneg[i];
      //if(emean_mmneg[i]==(float)1.41421)
      if(emean_mmneg[i]>0.1)
	{
	  mean_mmneg[i]=-9; emean_mmneg[i]=0;
	}
    }

  TGraphErrors *tg_run8pp_pos = new TGraphErrors(848,run_pppos,mean_pppos,zero,emean_pppos);
  tg_run8pp_pos->SetMarkerColor(kBlack);
  tg_run8pp_pos->SetMarkerStyle(20);

  TGraphErrors *tg_run8pp_neg = new TGraphErrors(848,run_ppneg,mean_ppneg,zero,emean_ppneg);
  tg_run8pp_neg->SetMarkerColor(kBlack);
  tg_run8pp_neg->SetMarkerStyle(20);

  TGraphErrors *tg_run8mm_pos = new TGraphErrors(848,run_mmpos,mean_mmpos,zero,emean_mmpos);
  tg_run8mm_pos->SetMarkerColor(kBlack);
  tg_run8mm_pos->SetMarkerStyle(20);

  TGraphErrors *tg_run8mm_neg = new TGraphErrors(848,run_mmneg,mean_mmneg,zero,emean_mmneg);
  tg_run8mm_neg->SetMarkerColor(kBlack);
  tg_run8mm_neg->SetMarkerStyle(20);


  tg_run8pp_pos->SetTitle("Run8, ++ field, protons");
  tg_run8pp_pos->GetXaxis()->SetLimits(-1,848);
  tg_run8pp_pos->SetMinimum(0.0);
  tg_run8pp_pos->SetMaximum(1.5);
  tg_run8pp_pos->GetXaxis()->SetTitle("Run Index");
  tg_run8pp_pos->GetYaxis()->SetTitle("mean m^{2}");
  tg_run8pp_pos->GetXaxis()->CenterTitle();
  tg_run8pp_pos->GetYaxis()->CenterTitle();
  tg_run8pp_pos->Draw("AP");
  fprot->Draw("same");
  c1->Print("figure_run_run8pp_pos.gif");
  c1->Print("figure_run_run8pp_pos.eps");

  tg_run8pp_neg->SetTitle("Run8, ++ field, antiprotons");
  tg_run8pp_neg->GetXaxis()->SetLimits(-1,848);
  tg_run8pp_neg->SetMinimum(0.0);
  tg_run8pp_neg->SetMaximum(1.5);
  tg_run8pp_neg->GetXaxis()->SetTitle("Run Index");
  tg_run8pp_neg->GetYaxis()->SetTitle("mean m^{2}");
  tg_run8pp_neg->GetXaxis()->CenterTitle();
  tg_run8pp_neg->GetYaxis()->CenterTitle();
  tg_run8pp_neg->Draw("AP");
  fprot->Draw("same");
  c1->Print("figure_run_run8pp_neg.gif");
  c1->Print("figure_run_run8pp_neg.eps");

  tg_run8mm_pos->SetTitle("Run8, -- field, protons");
  tg_run8mm_pos->GetXaxis()->SetLimits(-1,848);
  tg_run8mm_pos->SetMinimum(0.0);
  tg_run8mm_pos->SetMaximum(1.5);
  tg_run8mm_pos->GetXaxis()->SetTitle("Run Index");
  tg_run8mm_pos->GetYaxis()->SetTitle("mean m^{2}");
  tg_run8mm_pos->GetXaxis()->CenterTitle();
  tg_run8mm_pos->GetYaxis()->CenterTitle();
  tg_run8mm_pos->Draw("AP");
  fprot->Draw("same");
  c1->Print("figure_run_run8mm_pos.gif");
  c1->Print("figure_run_run8mm_pos.eps");

  tg_run8mm_neg->SetTitle("Run8, -- field, antiprotons");
  tg_run8mm_neg->GetXaxis()->SetLimits(-1,848);
  tg_run8mm_neg->SetMinimum(0.0);
  tg_run8mm_neg->SetMaximum(1.5);
  tg_run8mm_neg->GetXaxis()->SetTitle("Run Index");
  tg_run8mm_neg->GetYaxis()->SetTitle("mean m^{2}");
  tg_run8mm_neg->GetXaxis()->CenterTitle();
  tg_run8mm_neg->GetYaxis()->CenterTitle();
  tg_run8mm_neg->Draw("AP");
  fprot->Draw("same");
  c1->Print("figure_run_run8mm_neg.gif");
  c1->Print("figure_run_run8mm_neg.eps");

  cout<<"done. have a nice day!"<<endl;

}

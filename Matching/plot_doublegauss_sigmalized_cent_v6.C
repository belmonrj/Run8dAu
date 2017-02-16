void plot_doublegauss_sigmalized_cent_v6(
					char *field="minusminus",
					char *type="pos"
					)
{

  gStyle->SetOptTitle(0);

  cout<<"starting!"<<endl;

  char label[20];
  char zedselection[30];

  int fieldflag = -9999;
  if(strcmp("plusplus",field)==0) fieldflag = 0;
  else if(strcmp("minusminus",field)==0) fieldflag = 1;
  else cerr<<"DANGER!!!  Unknown field label!!!"<<endl;

  int charge;

  if(strcmp("pos",type)==0) charge = 1;
  else if(strcmp("neg",type)==0) charge = -1;
  else cerr<<"DANGER!!!  Unknown charge label!!!"<<endl;

  sprintf(label,"sigmalized residual");

  char filenamedz[80];
  sprintf(filenamedz,"DoubleGauss_SigmaCent/hh_%s_cent_tofwsdz_%s.dat",type,field);
  cout<<"name of tofwsdz input file is "<<filenamedz<<endl;

  char filenamedphi[80];
  sprintf(filenamedphi,"DoubleGauss_SigmaCent/hh_%s_cent_tofwsdphi_%s.dat",type,field);
  cout<<"name of tofwsdphi input file is "<<filenamedphi<<endl;

  // ---

  char figname_mean_dz_gif[80];
  sprintf(figname_mean_dz_gif,"DoubleGauss_SigmaCent/hh_mean_%s_cent_tofwsdz_%s.gif",type,field);
  cout<<"name of tofwsdz figure file is "<<figname_mean_dz_gif<<endl;

  char figname_mean_dphi_gif[80];
  sprintf(figname_mean_dphi_gif,"DoubleGauss_SigmaCent/hh_mean_%s_cent_tofwsdphi_%s.gif",type,field);
  cout<<"name of tofwsdphi figure file is "<<figname_mean_dphi_gif<<endl;

  char figname_mean_dz_eps[80];
  sprintf(figname_mean_dz_eps,"DoubleGauss_SigmaCent/hh_mean_%s_cent_tofwsdz_%s.eps",type,field);
  cout<<"name of tofwsdz figure file is "<<figname_mean_dz_eps<<endl;

  char figname_mean_dphi_eps[80];
  sprintf(figname_mean_dphi_eps,"DoubleGauss_SigmaCent/hh_mean_%s_cent_tofwsdphi_%s.eps",type,field);
  cout<<"name of tofwsdphi figure file is "<<figname_mean_dphi_eps<<endl;

  // ---

  char figname_sigma_dz_gif[80];
  sprintf(figname_sigma_dz_gif,"DoubleGauss_SigmaCent/hh_sigma_%s_cent_tofwsdz_%s.gif",type,field);
  cout<<"name of tofwsdz figure file is "<<figname_sigma_dz_gif<<endl;

  char figname_sigma_dphi_gif[80];
  sprintf(figname_sigma_dphi_gif,"DoubleGauss_SigmaCent/hh_sigma_%s_cent_tofwsdphi_%s.gif",type,field);
  cout<<"name of tofwsdphi figure file is "<<figname_sigma_dphi_gif<<endl;

  char figname_sigma_dz_eps[80];
  sprintf(figname_sigma_dz_eps,"DoubleGauss_SigmaCent/hh_sigma_%s_cent_tofwsdz_%s.eps",type,field);
  cout<<"name of tofwsdz figure file is "<<figname_sigma_dz_eps<<endl;

  char figname_sigma_dphi_eps[80];
  sprintf(figname_sigma_dphi_eps,"DoubleGauss_SigmaCent/hh_sigma_%s_cent_tofwsdphi_%s.eps",type,field);
  cout<<"name of tofwsdphi figure file is "<<figname_sigma_dphi_eps<<endl;

  ifstream findz(filenamedz);
  ifstream findphi(filenamedphi);

  if(!findz) {cout<<"input file "<<filenamedz<<" does not exist!"<<endl;return;}
  if(!findphi) {cout<<"input file "<<filenamedphi<<" does not exist!"<<endl;return;}

  char figname[110];

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);

  float zero[90]={0};

  float cent_dz[90], maximum_dz[90], par1_dz[90], epar1_dz[90], par2_dz[90], epar2_dz[90];
  float cent_dphi[90], maximum_dphi[90], par1_dphi[90], epar1_dphi[90], par2_dphi[90], epar2_dphi[90];

  for(int i=0; i<90; i++)
    {
      float CENT = float(i);
      findz>>cent_dz[i]>>maximum_dz[i]>>par1_dz[i]>>epar1_dz[i]>>par2_dz[i]>>epar2_dz[i];
      if((float)cent_dz[i]!=(float)CENT) cout<<"WARNING!!!  Cententum values do not match!"<<endl;
      findphi>>cent_dphi[i]>>maximum_dphi[i]>>par1_dphi[i]>>epar1_dphi[i]>>par2_dphi[i]>>epar2_dphi[i];
      if((float)cent_dphi[i]!=(float)CENT) cout<<"WARNING!!!  Cententum values do not match!"<<endl;
      if(epar1_dz[i]>1.0)
	{
	  par1_dz[i] = -9;
	  epar1_dz[i] = -0;
	  par2_dz[i] = -9;
	  epar2_dz[i] = -0;
	}
      if(epar1_dphi[i]>1.0)
	{
	  par1_dphi[i] = -9;
	  epar1_dphi[i] = -0;
	  par2_dphi[i] = -9;
	  epar2_dphi[i] = -0;
	}
    }

  //TF1 *funmeandz = new TF1("funmeandz","[0]+[1]/x+[2]/x/x+[3]/sqrt(x)",0.9,88.1);
  TF1 *funmeandz = new TF1("funmeandz","pol0",0.9,88.1);
  funmeandz->SetLineColor(kRed);
  //TF1 *funmeandphi = new TF1("funmeandphi","[0]+[1]/x+[2]/x/x+[3]/sqrt(x)",0.9,88.1);
  TF1 *funmeandphi = new TF1("funmeandphi","pol0",0.9,88.1);
  funmeandphi->SetLineColor(kRed);

  // --------
  // --- MEAN
  // --------

  TGraphErrors *tg_mean_dz = new TGraphErrors(90,cent_dz,par1_dz,zero,epar1_dz);
  tg_mean_dz->SetMarkerColor(kBlack);
  tg_mean_dz->SetMarkerStyle(20);
  tg_mean_dz->Draw("AP");
  tg_mean_dz->Fit(funmeandz,"R");
  tg_mean_dz->GetXaxis()->SetTitle("Centrality");
  tg_mean_dz->GetXaxis()->CenterTitle();
  tg_mean_dz->GetXaxis()->SetLimits(-1,91);
  tg_mean_dz->GetYaxis()->SetTitle("mean of tofwsdz");
  tg_mean_dz->GetYaxis()->CenterTitle();
  tg_mean_dz->SetMaximum(1.0);
  tg_mean_dz->SetMinimum(-1.0);
  TLegend *leg_mean_dz = new TLegend(0.68,0.68,0.88,0.88);
  leg_mean_dz->SetFillColor(kWhite);
  leg_mean_dz->SetBorderSize(0);
  leg_mean_dz->AddEntry(tg_mean_dz,label,"p");
  //leg_mean_dz->Draw(); // temp, blocks data for now
  c1->Print(figname_mean_dz_gif);
  c1->Print(figname_mean_dz_eps);

  TGraphErrors *tg_mean_dphi = new TGraphErrors(90,cent_dphi,par1_dphi,zero,epar1_dphi);
  tg_mean_dphi->SetMarkerColor(kBlack);
  tg_mean_dphi->SetMarkerStyle(20);
  tg_mean_dphi->Draw("AP");
  tg_mean_dphi->Fit(funmeandphi,"R");
  tg_mean_dphi->GetXaxis()->SetTitle("Centrality");
  tg_mean_dphi->GetXaxis()->CenterTitle();
  tg_mean_dphi->GetXaxis()->SetLimits(-1,91);
  tg_mean_dphi->GetYaxis()->SetTitle("mean of tofwsdphi");
  tg_mean_dphi->GetYaxis()->CenterTitle();
  tg_mean_dphi->SetMaximum(1.0);
  tg_mean_dphi->SetMinimum(-1.0);
  TLegend *leg_mean_dphi = new TLegend(0.68,0.68,0.88,0.88);
  leg_mean_dphi->SetFillColor(kWhite);
  leg_mean_dphi->SetBorderSize(0);
  leg_mean_dphi->AddEntry(tg_mean_dphi,label,"p");
  //leg_mean_dphi->Draw(); // temp, blocks data for now
  c1->Print(figname_mean_dphi_gif);
  c1->Print(figname_mean_dphi_eps);

  //TF1 *funsigmadz = new TF1("funsigmadz","[0]+[1]/x+[2]/x/x+[3]/sqrt(x)",0.9,88.1);
  //TF1 *funsigmadz = new TF1("funsigmadz","pol1",0.9,88.1);
  TF1 *funsigmadz = new TF1("funsigmadz","pol0",0.9,88.1);
  funsigmadz->SetLineColor(kRed);
  //TF1 *funsigmadphi = new TF1("funsigmadphi","[0]+[1]/x+[2]/x/x+[3]/sqrt(x)",0.9,88.1);
  TF1 *funsigmadphi = new TF1("funsigmadphi","pol0",0.9,88.1);
  funsigmadphi->SetLineColor(kRed);

  // ---------
  // --- SIGMA
  // ---------

  TGraphErrors *tg_sigma_dz = new TGraphErrors(90,cent_dz,par2_dz,zero,epar2_dz);
  tg_sigma_dz->SetMarkerColor(kBlack);
  tg_sigma_dz->SetMarkerStyle(20);
  tg_sigma_dz->Draw("AP");
  tg_sigma_dz->Fit(funsigmadz,"R");
  tg_sigma_dz->GetXaxis()->SetTitle("Centrality");
  tg_sigma_dz->GetXaxis()->CenterTitle();
  tg_sigma_dz->GetXaxis()->SetLimits(-1,91);
  tg_sigma_dz->GetYaxis()->SetTitle("sigma of tofwsdz");
  tg_sigma_dz->GetYaxis()->CenterTitle();
  tg_sigma_dz->SetMaximum(2.0);
  tg_sigma_dz->SetMinimum(0.5);
  TLegend *leg_sigma_dz = new TLegend(0.68,0.68,0.88,0.88);
  leg_sigma_dz->SetFillColor(kWhite);
  leg_sigma_dz->SetBorderSize(0);
  leg_sigma_dz->AddEntry(tg_sigma_dz,label,"p");
  //leg_sigma_dz->Draw(); // temp, blocks data for now
  c1->Print(figname_sigma_dz_gif);
  c1->Print(figname_sigma_dz_eps);

  TGraphErrors *tg_sigma_dphi = new TGraphErrors(90,cent_dphi,par2_dphi,zero,epar2_dphi);
  tg_sigma_dphi->SetMarkerColor(kBlack);
  tg_sigma_dphi->SetMarkerStyle(20);
  tg_sigma_dphi->Draw("AP");
  tg_sigma_dphi->Fit(funsigmadphi,"R");
  tg_sigma_dphi->GetXaxis()->SetTitle("Centrality");
  tg_sigma_dphi->GetXaxis()->CenterTitle();
  tg_sigma_dphi->GetXaxis()->SetLimits(-1,91);
  tg_sigma_dphi->GetYaxis()->SetTitle("sigma of tofwsdphi");
  tg_sigma_dphi->GetYaxis()->CenterTitle();
  tg_sigma_dphi->SetMaximum(2.0);
  tg_sigma_dphi->SetMinimum(0.5);
  TLegend *leg_sigma_dphi = new TLegend(0.68,0.68,0.88,0.88);
  leg_sigma_dphi->SetFillColor(kWhite);
  leg_sigma_dphi->SetBorderSize(0);
  leg_sigma_dphi->AddEntry(tg_sigma_dphi,label,"p");
  //leg_sigma_dphi->Draw(); // temp, blocks data for now
  c1->Print(figname_sigma_dphi_gif);
  c1->Print(figname_sigma_dphi_eps);

  // ---
  // ---
  // ---

  char fcodeoutdz[100];
  sprintf(fcodeoutdz,"DoubleGauss_SigmaCent/parameters_hh_%s_cent_tofwsdz_%s.dat",type,field);
  char fcodeoutdphi[100];
  sprintf(fcodeoutdphi,"DoubleGauss_SigmaCent/parameters_hh_%s_cent_tofwsdphi_%s.dat",type,field);

  char runselection[100];
  if(fieldflag==0) sprintf(runselection,"if(run<250593"); // ++
  if(fieldflag==1) sprintf(runselection,"if(run>250484"); // --

  ofstream foutdz(fcodeoutdz);
  foutdz << runselection << "&&charge==" << charge << ")" <<endl;
  foutdz << "{" << endl;
  foutdz << "mean = " << funmeandz->GetParameter(0) << " + " << funmeandz->GetParameter(1) << "/cent" 
	 << " + " << funmeandz->GetParameter(2) << "/cent/cent" << " + " << funmeandz->GetParameter(3) << "/sqrt(cent);" << endl;
  //foutdz << "sigma = " << funsigmadz->GetParameter(0) << " + " << funsigmadz->GetParameter(1) << "/cent" 
  //     << " + " << funsigmadz->GetParameter(2) << "/cent/cent" << " + " << funsigmadz->GetParameter(3) << "/sqrt(cent);" << endl;
  foutdz << "sigma = " << funsigmadz->GetParameter(0) << " + " << funsigmadz->GetParameter(1) << "*cent;" << endl;
  foutdz << "}" << endl;
  foutdz.close();
  cout<<"file "<< fcodeoutdz << " has been written! " <<endl;

  ofstream foutdphi(fcodeoutdphi);
  foutdphi << runselection << "&&charge==" << charge << ")" <<endl;
  foutdphi << "{" << endl;
  foutdphi << "mean = " << funmeandphi->GetParameter(0) << ";" << endl;
  foutdphi << "sigma = " << funsigmadphi->GetParameter(0) << ";" << endl;
  //foutdphi << "mean = " << funmeandphi->GetParameter(0) << " + " << funmeandphi->GetParameter(1) << "/cent" 
  //	   << " + " << funmeandphi->GetParameter(2) << "/cent/cent" << " + " << funmeandphi->GetParameter(3) << "/sqrt(cent);" << endl;
  //foutdphi << "sigma = " << funsigmadphi->GetParameter(0) << " + " << funsigmadphi->GetParameter(1) << "/cent" 
  //	   << " + " << funsigmadphi->GetParameter(2) << "/cent/cent" << " + " << funsigmadphi->GetParameter(3) << "/sqrt(cent);" << endl;
  foutdphi << "}" << endl;
  foutdphi.close();
  cout<<"file "<< fcodeoutdphi << " has been written! " <<endl;


}

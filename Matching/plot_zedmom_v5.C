void plot_zedmom_v5(
		    char *field="plusplus",
		    char *sector="sector1",
		    char *type="posmom_poszed4"
		    )
{

  gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);

  cout<<"starting!"<<endl;

  char label[20];
  char zedselection[30];

  int fieldflag = -9999;
  if(strcmp("plusplus",field)==0) fieldflag = 0;
  else if(strcmp("minusminus",field)==0) fieldflag = 1;
  else cerr<<"DANGER!!!  Unknown field label!!!"<<endl;

  int sectorflag = -9999;
  if(strcmp("sector1",sector)==0) sectorflag = 1;
  else if(strcmp("sector2",sector)==0) sectorflag = 2;
  else cerr<<"DANGER!!!  Unknown sector label!!!"<<endl;

  int charge;

  if(strcmp("posmom_poszed0",type)==0
     ||strcmp("posmom_poszed1",type)==0
     ||strcmp("posmom_poszed2",type)==0
     ||strcmp("posmom_poszed3",type)==0
     ||strcmp("posmom_poszed4",type)==0
     ||strcmp("posmom_negzed0",type)==0
     ||strcmp("posmom_negzed1",type)==0
     ||strcmp("posmom_negzed2",type)==0
     ||strcmp("posmom_negzed3",type)==0
     ||strcmp("posmom_negzed4",type)==0) charge = 1;

  if(strcmp("negmom_poszed0",type)==0
     ||strcmp("negmom_poszed1",type)==0
     ||strcmp("negmom_poszed2",type)==0
     ||strcmp("negmom_poszed3",type)==0
     ||strcmp("negmom_poszed4",type)==0
     ||strcmp("negmom_negzed0",type)==0
     ||strcmp("negmom_negzed1",type)==0
     ||strcmp("negmom_negzed2",type)==0
     ||strcmp("negmom_negzed3",type)==0
     ||strcmp("negmom_negzed4",type)==0) charge = -1;

  if(strcmp("posmom_poszed0",type)==0||strcmp("negmom_poszed0",type)==0)
    {
      sprintf(label,"0<zed<15");
      sprintf(zedselection,"zed>=0&&zed<15");
    }
  else if(strcmp("posmom_negzed0",type)==0||strcmp("negmom_negzed0",type)==0) 
    {
      sprintf(label,"-15<zed<0");
      sprintf(zedselection,"zed>-15&&zed<0");
    }
  else if(strcmp("posmom_poszed1",type)==0||strcmp("negmom_poszed1",type)==0) 
    {
      sprintf(label,"15<zed<30");
      sprintf(zedselection,"zed>=15&&zed<30");
    }
  else if(strcmp("posmom_negzed1",type)==0||strcmp("negmom_negzed1",type)==0) 
    {
      sprintf(label,"-30<zed<-15");
      sprintf(zedselection,"zed>-30&&zed<=-15");
    }
  else if(strcmp("posmom_poszed2",type)==0||strcmp("negmom_poszed2",type)==0) 
    {
      sprintf(label,"30<zed<45");
      sprintf(zedselection,"zed>=30&&zed<45");
    }
  else if(strcmp("posmom_negzed2",type)==0||strcmp("negmom_negzed2",type)==0) 
    {
      sprintf(label,"-45<zed<-30");
      sprintf(zedselection,"zed>-45&&zed<=-30");
    }
  else if(strcmp("posmom_poszed3",type)==0||strcmp("negmom_poszed3",type)==0) 
    {
      sprintf(label,"45<zed<60");
      sprintf(zedselection,"zed>=45&&zed<60");
    }
  else if(strcmp("posmom_negzed3",type)==0||strcmp("negmom_negzed3",type)==0) 
    {
      sprintf(label,"-60<zed<-45");
      sprintf(zedselection,"zed>-60&&zed<=-45");
    }
  else if(strcmp("posmom_poszed4",type)==0||strcmp("negmom_poszed4",type)==0) 
    {
      sprintf(label,"60<zed<75");
      sprintf(zedselection,"zed>=60&&zed<75");
    }
  else if(strcmp("posmom_negzed4",type)==0||strcmp("negmom_negzed4",type)==0) 
    {
      sprintf(label,"-75<zed<-60");
      sprintf(zedselection,"zed>-75&&zed<=-60");
    }
  else 
    {
      cerr<<"DANGER!!!  Unknown zed label!!!"<<endl;
    }

  char filenamedz[80];
  sprintf(filenamedz,"ZedMom/hh_%s_tofwdz_%s_%s.dat",sector,type,field);
  cout<<"name of tofwdz input file is "<<filenamedz<<endl;

  char filenamedphi[80];
  sprintf(filenamedphi,"ZedMom/hh_%s_tofwdphi_%s_%s.dat",sector,type,field);
  cout<<"name of tofwdphi input file is "<<filenamedphi<<endl;

  // ---

  char figname_mean_dz_gif[80];
  sprintf(figname_mean_dz_gif,"ZedMom/hh_mean_%s_tofwdz_%s_%s.gif",sector,type,field);
  cout<<"name of tofwdz figure file is "<<figname_mean_dz_gif<<endl;

  char figname_mean_dphi_gif[80];
  sprintf(figname_mean_dphi_gif,"ZedMom/hh_mean_%s_tofwdphi_%s_%s.gif",sector,type,field);
  cout<<"name of tofwdphi figure file is "<<figname_mean_dphi_gif<<endl;

  char figname_mean_dz_eps[80];
  sprintf(figname_mean_dz_eps,"ZedMom/hh_mean_%s_tofwdz_%s_%s.eps",sector,type,field);
  cout<<"name of tofwdz figure file is "<<figname_mean_dz_eps<<endl;

  char figname_mean_dphi_eps[80];
  sprintf(figname_mean_dphi_eps,"ZedMom/hh_mean_%s_tofwdphi_%s_%s.eps",sector,type,field);
  cout<<"name of tofwdphi figure file is "<<figname_mean_dphi_eps<<endl;

  // ---

  char figname_sigma_dz_gif[80];
  sprintf(figname_sigma_dz_gif,"ZedMom/hh_sigma_%s_tofwdz_%s_%s.gif",sector,type,field);
  cout<<"name of tofwdz figure file is "<<figname_sigma_dz_gif<<endl;

  char figname_sigma_dphi_gif[80];
  sprintf(figname_sigma_dphi_gif,"ZedMom/hh_sigma_%s_tofwdphi_%s_%s.gif",sector,type,field);
  cout<<"name of tofwdphi figure file is "<<figname_sigma_dphi_gif<<endl;

  char figname_sigma_dz_eps[80];
  sprintf(figname_sigma_dz_eps,"ZedMom/hh_sigma_%s_tofwdz_%s_%s.eps",sector,type,field);
  cout<<"name of tofwdz figure file is "<<figname_sigma_dz_eps<<endl;

  char figname_sigma_dphi_eps[80];
  sprintf(figname_sigma_dphi_eps,"ZedMom/hh_sigma_%s_tofwdphi_%s_%s.eps",sector,type,field);
  cout<<"name of tofwdphi figure file is "<<figname_sigma_dphi_eps<<endl;

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

  float zero[50]={0};

  float mom_dz[50], maximum_dz[50], par1_dz[50], epar1_dz[50], par2_dz[50], epar2_dz[50];
  float mom_dphi[50], maximum_dphi[50], par1_dphi[50], epar1_dphi[50], par2_dphi[50], epar2_dphi[50];

  for(int i=0; i<44; i++)
    {
      float MOM = i/10.0+0.05;
      findz>>mom_dz[i]>>maximum_dz[i]>>par1_dz[i]>>epar1_dz[i]>>par2_dz[i]>>epar2_dz[i];
      //if((float)mom_dz[i]!=(float)MOM) cout<<"WARNING!!!  Momentum values do not match!"<<endl;
      findphi>>mom_dphi[i]>>maximum_dphi[i]>>par1_dphi[i]>>epar1_dphi[i]>>par2_dphi[i]>>epar2_dphi[i];
      //if((float)mom_dphi[i]!=(float)MOM) cout<<"WARNING!!!  Momentum values do not match!"<<endl;
    }

  TF1 *funmeandzL = new TF1("funmeandzL","[0]+[1]/x+[2]/x/x+[3]/sqrt(x)",0.3,1);
  funmeandzL->SetLineColor(kRed);
  TF1 *funmeandphiL = new TF1("funmeandphiL","[0]+[1]/x+[2]/x/x+[3]/sqrt(x)",0.3,1);
  funmeandphiL->SetLineColor(kRed);

  TF1 *funmeandzH = new TF1("funmeandzH","[0]+[1]/x+[2]/x/x+[3]/sqrt(x)",1,5);
  funmeandzH->SetLineColor(kBlue);
  TF1 *funmeandphiH = new TF1("funmeandphiH","[0]+[1]/x+[2]/x/x+[3]/sqrt(x)",1,5);
  funmeandphiH->SetLineColor(kBlue);

  // --------
  // --- MEAN
  // --------

  TGraphErrors *tg_mean_dz = new TGraphErrors(50,mom_dz,par1_dz,zero,epar1_dz);
  tg_mean_dz->SetMarkerColor(kBlack);
  tg_mean_dz->SetMarkerStyle(20);
  tg_mean_dz->Draw("AP");
  tg_mean_dz->Fit(funmeandzL,"R");
  tg_mean_dz->Fit(funmeandzH,"R");
  funmeandzL->Draw("same"); // draw it again because it disappears after the second fit
  tg_mean_dz->GetXaxis()->SetTitle("p (GeV/c)");
  tg_mean_dz->GetXaxis()->CenterTitle();
  tg_mean_dz->GetXaxis()->SetLimits(0.3,5.0);
  tg_mean_dz->GetYaxis()->SetTitle("mean of tofwdz");
  tg_mean_dz->GetYaxis()->CenterTitle();
  tg_mean_dz->SetMaximum(1.75);
  tg_mean_dz->SetMinimum(-1.75);
  TLegend *leg_mean_dz = new TLegend(0.68,0.68,0.88,0.88);
  leg_mean_dz->SetFillColor(kWhite);
  leg_mean_dz->SetBorderSize(0);
  leg_mean_dz->AddEntry(tg_mean_dz,label,"p");
  //leg_mean_dz->Draw(); // temp, blocks data for now
  c1->Print(figname_mean_dz_gif);
  c1->Print(figname_mean_dz_eps);

  TGraphErrors *tg_mean_dphi = new TGraphErrors(50,mom_dphi,par1_dphi,zero,epar1_dphi);
  tg_mean_dphi->SetMarkerColor(kBlack);
  tg_mean_dphi->SetMarkerStyle(20);
  tg_mean_dphi->Draw("AP");
  tg_mean_dphi->Fit(funmeandphiL,"R");
  tg_mean_dphi->Fit(funmeandphiH,"R");
  funmeandphiL->Draw("same"); // draw it again because it disappears after the second fit
  tg_mean_dphi->GetXaxis()->SetTitle("p (GeV/c)");
  tg_mean_dphi->GetXaxis()->CenterTitle();
  tg_mean_dphi->GetXaxis()->SetLimits(0.3,5.0);
  tg_mean_dphi->GetYaxis()->SetTitle("mean of tofwdphi");
  tg_mean_dphi->GetYaxis()->CenterTitle();
  tg_mean_dphi->SetMaximum(0.010);
  tg_mean_dphi->SetMinimum(-0.010);
  TLegend *leg_mean_dphi = new TLegend(0.68,0.68,0.88,0.88);
  leg_mean_dphi->SetFillColor(kWhite);
  leg_mean_dphi->SetBorderSize(0);
  leg_mean_dphi->AddEntry(tg_mean_dphi,label,"p");
  //leg_mean_dphi->Draw(); // temp, blocks data for now
  c1->Print(figname_mean_dphi_gif);
  c1->Print(figname_mean_dphi_eps);

  TF1 *funsigmadz = new TF1("funsigmadz","[0]+[1]/x+[2]/x/x+[3]/sqrt(x)",0.3,5);
  funsigmadz->SetLineColor(kRed);
  TF1 *funsigmadphi = new TF1("funsigmadphi","[0]+[1]/x+[2]/x/x+[3]/sqrt(x)",0.3,5);
  funsigmadphi->SetLineColor(kRed);

  // ---------
  // --- SIGMA
  // ---------

  TGraphErrors *tg_sigma_dz = new TGraphErrors(50,mom_dz,par2_dz,zero,epar2_dz);
  tg_sigma_dz->SetMarkerColor(kBlack);
  tg_sigma_dz->SetMarkerStyle(20);
  tg_sigma_dz->Draw("AP");
  tg_sigma_dz->Fit(funsigmadz,"R");
  tg_sigma_dz->GetXaxis()->SetTitle("p (GeV/c)");
  tg_sigma_dz->GetXaxis()->CenterTitle();
  tg_sigma_dz->GetXaxis()->SetLimits(0.3,5.0);
  tg_sigma_dz->GetYaxis()->SetTitle("sigma of tofwdz");
  tg_sigma_dz->GetYaxis()->CenterTitle();
  tg_sigma_dz->SetMaximum(4.0);
  tg_sigma_dz->SetMinimum(1.0);
  TLegend *leg_sigma_dz = new TLegend(0.68,0.68,0.88,0.88);
  leg_sigma_dz->SetFillColor(kWhite);
  leg_sigma_dz->SetBorderSize(0);
  leg_sigma_dz->AddEntry(tg_sigma_dz,label,"p");
  //leg_sigma_dz->Draw(); // temp, blocks data for now
  c1->Print(figname_sigma_dz_gif);
  c1->Print(figname_sigma_dz_eps);

  TGraphErrors *tg_sigma_dphi = new TGraphErrors(50,mom_dphi,par2_dphi,zero,epar2_dphi);
  tg_sigma_dphi->SetMarkerColor(kBlack);
  tg_sigma_dphi->SetMarkerStyle(20);
  tg_sigma_dphi->Draw("AP");
  tg_sigma_dphi->Fit(funsigmadphi,"R");
  tg_sigma_dphi->GetXaxis()->SetTitle("p (GeV/c)");
  tg_sigma_dphi->GetXaxis()->CenterTitle();
  tg_sigma_dphi->GetXaxis()->SetLimits(0.3,5.0);
  tg_sigma_dphi->GetYaxis()->SetTitle("sigma of tofwdphi");
  tg_sigma_dphi->GetYaxis()->CenterTitle();
  tg_sigma_dphi->SetMaximum(0.009);
  tg_sigma_dphi->SetMinimum(0.001);
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
  sprintf(fcodeoutdz,"ZedMom/parameters_hh_%s_tofwdz_%s_%s.dat",sector,type,field);
  char fcodeoutdphi[100];
  sprintf(fcodeoutdphi,"ZedMom/parameters_hh_%s_tofwdphi_%s_%s.dat",sector,type,field);

  char runselection[100];
  if(fieldflag==0) sprintf(runselection,"if(run<250593"); // ++
  if(fieldflag==1) sprintf(runselection,"if(run>250484"); // --

  char sectorselection[100];
  if(sectorflag==1) sprintf(sectorselection,"striptofw<256"); // W1
  if(sectorflag==2) sprintf(sectorselection,"striptofw>255"); // W2

  ofstream foutdz(fcodeoutdz);
  foutdz << runselection << "&&" << sectorselection << "&&charge==" << charge << "&&(" << zedselection << "))" <<endl;
  foutdz << "{" << endl;
  foutdz << "if(mom<1.0) mean = " << funmeandzL->GetParameter(0) << " + " << funmeandzL->GetParameter(1) << "/mom" 
	 << " + " << funmeandzL->GetParameter(2) << "/mom/mom" << " + " << funmeandzL->GetParameter(3) << "/sqrt(mom);" << endl;
  foutdz << "else if(mom>=1.0) mean = " << funmeandzH->GetParameter(0) << " + " << funmeandzH->GetParameter(1) << "/mom" 
	 << " + " << funmeandzH->GetParameter(2) << "/mom/mom" << " + " << funmeandzH->GetParameter(3) << "/sqrt(mom);" << endl;
  foutdz << "sigma = " << funsigmadz->GetParameter(0) << " + " << funsigmadz->GetParameter(1) << "/mom" 
	   << " + " << funsigmadz->GetParameter(2) << "/mom/mom" << " + " << funsigmadz->GetParameter(3) << "/sqrt(mom);" << endl;
  foutdz << "}" << endl;
  foutdz.close();
  cout<<"file "<< fcodeoutdz << " has been written! " <<endl;

  ofstream foutdphi(fcodeoutdphi);
  foutdphi << runselection << "&&" << sectorselection << "&&charge==" << charge << "&&(" << zedselection << "))" <<endl;
  foutdphi << "{" << endl;
  foutdphi << "if(mom<1.0) mean = " << funmeandphiL->GetParameter(0) << " + " << funmeandphiL->GetParameter(1) << "/mom" 
	 << " + " << funmeandphiL->GetParameter(2) << "/mom/mom" << " + " << funmeandphiL->GetParameter(3) << "/sqrt(mom);" << endl;
  foutdphi << "else if(mom>=1.0) mean = " << funmeandphiH->GetParameter(0) << " + " << funmeandphiH->GetParameter(1) << "/mom" 
	 << " + " << funmeandphiH->GetParameter(2) << "/mom/mom" << " + " << funmeandphiH->GetParameter(3) << "/sqrt(mom);" << endl;
  foutdphi << "sigma = " << funsigmadphi->GetParameter(0) << " + " << funsigmadphi->GetParameter(1) << "/mom" 
	   << " + " << funsigmadphi->GetParameter(2) << "/mom/mom" << " + " << funsigmadphi->GetParameter(3) << "/sqrt(mom);" << endl;
  foutdphi << "}" << endl;
  foutdphi.close();
  cout<<"file "<< fcodeoutdphi << " has been written! " <<endl;


}

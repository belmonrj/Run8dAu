void compare()
{

  // doit();
  // return;

  cout<<"now doing systematic comparisons!"<<endl;

  for(int iswitch=0; iswitch<2; iswitch++)
    {
      //for(int itype=0; itype<8; itype++)
      for(int itype=0; itype<9; itype++)
	{
	  for(int ipid=0; ipid<3; ipid++)
	    {
	      doit(ipid,itype,iswitch);
	      //cout<<"doit("<<isec<<","<<ipid<<","<<icent<<");"<<endl;
	    }
	}
    }




  cout<<"all done!  i hope you have a great day!"<<endl;

}

void doit(int ipid=0, int itype=0, int iswitch=0)
{

  float high = 6.0;
  float errheight = 0.5;

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->SetLogy(1);

  // TLine *line = new TLine(0.0,1.0,high,1.0);
  // TLine *line0 = new TLine(0.0,0.0,high,0.0);
  TLine *line = new TLine(0.0,1.0,high,1.0);
  TLine *line0 = new TLine(0.0,0.0,high,0.0);

  char gifname[100];
  char epsname[100];



  int pidnumber = 0; // default
  if(ipid==0) pidnumber = 1;
  if(ipid==1) pidnumber = 3;
  if(ipid==2) pidnumber = 5;

  char pidstring[5];
  sprintf(pidstring,"pion"); // "default"
  if(ipid==0) sprintf(pidstring,"pion");
  if(ipid==1) sprintf(pidstring,"kaon");
  if(ipid==2) sprintf(pidstring,"prot");

  char typestring[5];
  sprintf(typestring,"tfwm"); // "default"
  if(itype==0) sprintf(typestring,"tfwm");
  if(itype==1) sprintf(typestring,"pc3m");
  if(itype==2) sprintf(typestring,"pc3f");
  if(itype==3) sprintf(typestring,"pc1f");
  if(itype==4) sprintf(typestring,"dcfc");
  if(itype==5) sprintf(typestring,"dzed");
  if(itype==6) sprintf(typestring,"spid");
  if(itype==7) sprintf(typestring,"tpid");
  if(itype==8) sprintf(typestring,"gadc");

  char typelongstring[50];
  sprintf(typelongstring,"tofw matching"); // "default"
  // if(itype==0) sprintf(typelongstring,"TOFW matching");
  // if(itype==1) sprintf(typelongstring,"PC3 matching");
  // if(itype==2) sprintf(typelongstring,"PC3 fiducial");
  // if(itype==3) sprintf(typelongstring,"PC1 fiducial");
  // if(itype==4) sprintf(typelongstring,"DCh fiducial");
  // if(itype==5) sprintf(typelongstring,"DC zed");
  // if(itype==6) sprintf(typelongstring,"PID function");

  if(iswitch==0)
    {
      if(itype==0) sprintf(typelongstring,"TOFW matching (1.5 #sigma)");
      if(itype==1) sprintf(typelongstring,"PC3 matching (1.5 #sigma)");
      if(itype==2) sprintf(typelongstring,"PC3 fiducial (tighter)");
      if(itype==3) sprintf(typelongstring,"PC1 fiducial (tighter)");
      if(itype==4) sprintf(typelongstring,"DCh fiducial (tighter)");
      if(itype==5) sprintf(typelongstring,"DCh zed cut (|zed|<40)");
      if(itype==6) sprintf(typelongstring,"PID function (diff pars)");
      if(itype==7) sprintf(typelongstring,"PID function (1.5 #sigma, 2 #sigma veto)");
      if(itype==8) sprintf(typelongstring,"TOFW ADC cut (550>qtofw>65)");
    }
  if(iswitch==1)
    {
      if(itype==0) sprintf(typelongstring,"TOFW matching (2.5 #sigma)");
      if(itype==1) sprintf(typelongstring,"PC3 matching (2.5 #sigma)");
      if(itype==2) sprintf(typelongstring,"PC3 fiducial (no cut)");
      if(itype==3) sprintf(typelongstring,"PC1 fiducial (no cut)");
      if(itype==4) sprintf(typelongstring,"DCh fiducial (no cut)");
      if(itype==5) sprintf(typelongstring,"DCh zed cut (|zed|>40)");
      if(itype==6) sprintf(typelongstring,"PID function (diff pars)");
      if(itype==7) sprintf(typelongstring,"PID function (2 #sigma, 1.5 #sigma veto)");
      if(itype==8) sprintf(typelongstring,"TOFW ADC cut (650>qtofw>55)");
    }


  char switchstring[2];
  sprintf(switchstring,"A"); // "default"
  if(iswitch==0) sprintf(switchstring,"A");
  if(iswitch==1) sprintf(switchstring,"B");





  char fnameinposref[100];
  char fnameinnegref[100];
  sprintf(fnameinposref,"Data/ptpid_tofw_pos_%d_dis.dat",pidnumber);
  sprintf(fnameinnegref,"Data/ptpid_tofw_neg_%d_dis.dat",pidnumber);
  ifstream finposref;
  ifstream finnegref;
  finposref.open(fnameinposref);
  finnegref.open(fnameinnegref);

  char fnameinpossys[100];
  char fnameinnegsys[100];
  sprintf(fnameinpossys,"Data/ptsys_%s_pos_%s%s.dat",pidstring,typestring,switchstring);
  sprintf(fnameinnegsys,"Data/ptsys_%s_neg_%s%s.dat",pidstring,typestring,switchstring);
  ifstream finpossys;
  ifstream finnegsys;
  finpossys.open(fnameinpossys);
  finnegsys.open(fnameinnegsys);

  float pt_U_syspos[100], yield_U_syspos[100], eyield_U_syspos[100];
  float pt_U_sysneg[100], yield_U_sysneg[100], eyield_U_sysneg[100];
  float pt_U_refpos[100], yield_U_refpos[100], eyield_U_refpos[100];
  float pt_U_refneg[100], yield_U_refneg[100], eyield_U_refneg[100];

  float ept_U_syspos[100]={0};
  float ept_U_sysneg[100]={0};
  float ept_U_refpos[100]={0};
  float ept_U_refneg[100]={0};

  for(int i=0; i<100; i++)
    {
      // sys
      finpossys>>pt_U_syspos[i]>>yield_U_syspos[i]>>eyield_U_syspos[i];
      finnegsys>>pt_U_sysneg[i]>>yield_U_sysneg[i]>>eyield_U_sysneg[i];
      // ref
      finposref>>pt_U_refpos[i]>>yield_U_refpos[i]>>eyield_U_refpos[i];
      finnegref>>pt_U_refneg[i]>>yield_U_refneg[i]>>eyield_U_refneg[i];
    }

  finpossys.close();
  finnegsys.close();
  finposref.close();
  finnegref.close();

  // ------------- //
  // --- rebin --- //
  // ------------- //

  float pt_syspos[100], yield_syspos[100], eyield_syspos[100];
  float pt_sysneg[100], yield_sysneg[100], eyield_sysneg[100];
  float pt_refpos[100], yield_refpos[100], eyield_refpos[100];
  float pt_refneg[100], yield_refneg[100], eyield_refneg[100];

  float ept_syspos[100]={0};
  float ept_sysneg[100]={0};
  float ept_refpos[100]={0};
  float ept_refneg[100]={0};

  for(int i=0; i<100; i++)
    {
      int k;
      if(i<30)
	{
	  pt_syspos[i] = pt_U_syspos[i];
	  pt_sysneg[i] = pt_U_sysneg[i];
	  yield_syspos[i] = yield_U_syspos[i];
	  yield_sysneg[i] = yield_U_sysneg[i];
	  eyield_syspos[i] = eyield_U_syspos[i];
	  eyield_sysneg[i] = eyield_U_sysneg[i];
	  pt_refpos[i] = pt_U_refpos[i];
	  pt_refneg[i] = pt_U_refneg[i];
	  yield_refpos[i] = yield_U_refpos[i];
	  yield_refneg[i] = yield_U_refneg[i];
	  eyield_refpos[i] = eyield_U_refpos[i];
	  eyield_refneg[i] = eyield_U_refneg[i];
	}
      if(i>=30)
	{
	  k=i/5+24;
	  if(i%5!=0) continue;
	  // ---
	  pt_syspos[k] = (pt_U_syspos[i]+pt_U_syspos[i+1]+pt_U_syspos[i+2]+
			  pt_U_syspos[i+3]+pt_U_syspos[i+4])/5.0;
	  yield_syspos[k] = (yield_U_syspos[i]+yield_U_syspos[i+1]+yield_U_syspos[i+2]+
			     yield_U_syspos[i+3]+yield_U_syspos[i+4])/5.0;
	  eyield_syspos[k] = sqrt(eyield_U_syspos[i]**2+eyield_U_syspos[i+1]**2+eyield_U_syspos[i+2]**2+
				  eyield_U_syspos[i+3]**2+eyield_U_syspos[i+4]**2)/5.0;
	  pt_sysneg[k] = (pt_U_sysneg[i]+pt_U_sysneg[i+1]+ pt_U_sysneg[i+2]+
			  pt_U_sysneg[i+3]+pt_U_sysneg[i+4])/5.0;
	  yield_sysneg[k] = (yield_U_sysneg[i]+yield_U_sysneg[i+1]+yield_U_sysneg[i+2]+
			     yield_U_sysneg[i+3]+yield_U_sysneg[i+4])/5.0;
	  eyield_sysneg[k] = sqrt(eyield_U_sysneg[i]**2+eyield_U_sysneg[i+1]**2+eyield_U_sysneg[i+2]**2+
				  eyield_U_sysneg[i+3]**2+eyield_U_sysneg[i+4]**2)/5.0;
	  // ---
	  pt_refpos[k] = (pt_U_refpos[i]+pt_U_refpos[i+1]+ pt_U_refpos[i+2]+
			  pt_U_refpos[i+3]+pt_U_refpos[i+4])/5.0;
	  yield_refpos[k] = (yield_U_refpos[i]+yield_U_refpos[i+1]+yield_U_refpos[i+2]+
			     yield_U_refpos[i+3]+yield_U_refpos[i+4])/5.0;
	  eyield_refpos[k] = sqrt(eyield_U_refpos[i]**2+eyield_U_refpos[i+1]**2+eyield_U_refpos[i+2]**2+
				  eyield_U_refpos[i+3]**2+eyield_U_refpos[i+4]**2)/5.0;
	  pt_refneg[k] = (pt_U_refneg[i]+pt_U_refneg[i+1]+ pt_U_refneg[i+2]+
			  pt_U_refneg[i+3]+pt_U_refneg[i+4])/5.0;
	  yield_refneg[k] = (yield_U_refneg[i]+yield_U_refneg[i+1]+yield_U_refneg[i+2]+
			     yield_U_refneg[i+3]+yield_U_refneg[i+4])/5.0;
	  eyield_refneg[k] = sqrt(eyield_U_refneg[i]**2+eyield_U_refneg[i+1]**2+eyield_U_refneg[i+2]**2+
				  eyield_U_refneg[i+3]**2+eyield_U_refneg[i+4]**2)/5.0;
	  // ---
	  //cout<<"i is "<<i<<"\t k is "<<k<<"\t pt is "<<pt_syspos[k]<<endl;
	}
    }

  // ------------- //
  // --- rebin --- //
  // ------------- //


  TGraphErrors *tge_syspos = new TGraphErrors(100,pt_syspos,yield_syspos,ept_syspos,eyield_syspos);
  tge_syspos->SetMarkerStyle(kFullCircle);
  tge_syspos->SetMarkerColor(kBlack);
  TGraphErrors *tge_sysneg = new TGraphErrors(100,pt_sysneg,yield_sysneg,ept_sysneg,eyield_sysneg);
  tge_sysneg->SetMarkerStyle(kFullCircle);
  tge_sysneg->SetMarkerColor(kBlack);

  TGraphErrors *tge_refpos = new TGraphErrors(100,pt_refpos,yield_refpos,ept_refpos,eyield_refpos);
  tge_refpos->SetMarkerStyle(kFullCircle);
  tge_refpos->SetMarkerColor(kBlack);
  TGraphErrors *tge_refneg = new TGraphErrors(100,pt_refneg,yield_refneg,ept_refneg,eyield_refneg);
  tge_refneg->SetMarkerStyle(kFullCircle);
  tge_refneg->SetMarkerColor(kBlack);



  tge_syspos->SetMarkerColor(kRed);
  tge_syspos->SetMarkerStyle(kOpenSquare);
  TMultiGraph *tmg_pos = new TMultiGraph();
  tmg_pos->Add(tge_syspos);
  tmg_pos->Add(tge_refpos);
  tmg_pos->Draw("ap");
  tmg_pos->SetMaximum(1e3);
  tmg_pos->SetMinimum(1e-7);
  tmg_pos->GetXaxis()->SetLimits(0.0,high);
  tmg_pos->GetYaxis()->SetTitle("Invariant Yield (c^{2}/GeV^{2})");
  tmg_pos->GetYaxis()->CenterTitle();
  tmg_pos->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_pos->GetXaxis()->CenterTitle();
  TLegend *leg_pos = new TLegend(0.48,0.68,0.88,0.88);
  leg_pos->SetFillColor(kWhite);
  leg_pos->SetBorderSize(0);
  leg_pos->AddEntry(tge_syspos,typelongstring,"p");
  leg_pos->AddEntry(tge_refpos,"standard","p");
  leg_pos->Draw();

  sprintf(gifname,"Figures/single_spectra_%s_pos_%s%s.gif",pidstring,typestring,switchstring);
  sprintf(epsname,"Figures/single_spectra_%s_pos_%s%s.eps",pidstring,typestring,switchstring);
  c1->Print(gifname);
  c1->Print(epsname);



  tge_sysneg->SetMarkerColor(kRed);
  tge_sysneg->SetMarkerStyle(kOpenSquare);
  TMultiGraph *tmg_neg = new TMultiGraph();
  tmg_neg->Add(tge_sysneg);
  tmg_neg->Add(tge_refneg);
  tmg_neg->Draw("ap");
  tmg_neg->SetMaximum(1e3);
  tmg_neg->SetMinimum(1e-7);
  tmg_neg->GetXaxis()->SetLimits(0.0,high);
  tmg_neg->GetYaxis()->SetTitle("Invariant Yield (c^{2}/GeV^{2})");
  tmg_neg->GetYaxis()->CenterTitle();
  tmg_neg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg_neg->GetXaxis()->CenterTitle();
  TLegend *leg_neg = new TLegend(0.48,0.68,0.88,0.88);
  leg_neg->SetFillColor(kWhite);
  leg_neg->SetBorderSize(0);
  leg_neg->AddEntry(tge_sysneg,typelongstring,"p");
  leg_neg->AddEntry(tge_refneg,"standard","p");
  leg_neg->Draw();

  sprintf(gifname,"Figures/single_spectra_%s_neg_%s%s.gif",pidstring,typestring,switchstring);
  sprintf(epsname,"Figures/single_spectra_%s_neg_%s%s.eps",pidstring,typestring,switchstring);
  c1->Print(gifname);
  c1->Print(epsname);



  // -------------------------- //
  // --- now do some ratios --- //
  // -------------------------- //

  char textoutratioposname[100];
  sprintf(textoutratioposname,"Text/single_ratio_%s_pos_%s%s.dat",pidstring,typestring,switchstring);
  ofstream foutratiopos(textoutratioposname);

  char textoutsuncertposname[100];
  sprintf(textoutsuncertposname,"Text/single_suncert_%s_pos_%s%s.dat",pidstring,typestring,switchstring);
  ofstream foutsuncertpos(textoutsuncertposname);

  float ptr[100], ratio[100], eratio[100];
  float eptr[100]={0};
  float error[100], derror[100];

  for(int i=0; i<100; i++)
    {
      ptr[i]=pt_syspos[i];

      float A, dA, B, dB;
      A = yield_syspos[i];
      dA = eyield_syspos[i];
      B = yield_refpos[i];
      dB = eyield_refpos[i];

      if(A>0&&B>0)
	{
	  ratio[i]= A/B;
	  eratio[i] = ratio[i]*sqrt((dA/A)**2+(dB/B)**2);
	}
      else
	{
	  ratio[i]=10;
	  eratio[i]=0;
	}
      //if((ipid==1&&i<3)||(ipid==2&&i<4))
      //if(i<5||i>49||(ipid==3&&i>34))
      //if(pt_syspos[i]<0.5||pt_syspos[i]>5.0||(ipid==1&&pt_syspos[i]>3.0))
      if(pt_syspos[i]<0.5||pt_syspos[i]>5.0||(ipid==1&&pt_syspos[i]>3.5))
	//if(pt_syspos[i]<1.0||pt_syspos[i]>5.0||(ipid==1&&pt_syspos[i]>3.5))
	{
	  ratio[i]=10;
	  eratio[i]=0;
	}

      error[i] = fabs(1.0-ratio[i]);
      derror[i] = eratio[i];
      foutratiopos<<ptr[i]<<"\t"<<ratio[i]<<"\t"<<eratio[i]<<endl;
      foutsuncertpos<<ptr[i]<<"\t"<<error[i]<<"\t"<<derror[i]<<endl;
    }
  TGraphErrors *tge_ratpos = new TGraphErrors(100,ptr,ratio,eptr,eratio);
  tge_ratpos->SetMarkerStyle(kFullCircle);
  tge_ratpos->SetMarkerColor(kBlack);
  //TGraphErrors *tge_errpos = new TGraphErrors(100,ptr,error,eptr,derror);
  TGraphErrors *tge_errpos = new TGraphErrors(34,ptr,error,eptr,derror);
  tge_errpos->SetMarkerStyle(kFullCircle);
  tge_errpos->SetMarkerColor(kBlack);



  c1->Clear();
  c1->SetLogy(0);
  tge_ratpos->Draw("ap");
  line->Draw("same");
  //tge_ratpos->SetMaximum(2.0);
  //tge_ratpos->SetMinimum(0.0);
  tge_ratpos->SetMaximum(2.4);
  tge_ratpos->SetMinimum(0.6);
  tge_ratpos->GetXaxis()->SetLimits(0.0,high);
  tge_ratpos->GetYaxis()->SetTitle("Systematic Ratio");
  tge_ratpos->GetYaxis()->CenterTitle();
  tge_ratpos->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_ratpos->GetXaxis()->CenterTitle();
  leg_pos = new TLegend(0.48,0.78,0.88,0.88);
  leg_pos->SetFillColor(kWhite);
  leg_pos->SetBorderSize(0);
  leg_pos->AddEntry(tge_ratpos,typelongstring,"p");
  leg_pos->Draw();

  sprintf(gifname,"Figures/single_ratio_%s_pos_%s%s.gif",pidstring,typestring,switchstring);
  sprintf(epsname,"Figures/single_ratio_%s_pos_%s%s.eps",pidstring,typestring,switchstring);
  c1->Print(gifname);
  c1->Print(epsname);

  c1->Clear();
  tge_errpos->Draw("ap");
  line0->Draw("same");
  tge_errpos->SetMaximum(errheight);
  tge_errpos->SetMinimum(-0.1);
  tge_errpos->GetXaxis()->SetLimits(0.0,high);
  tge_errpos->GetYaxis()->SetTitle("Systematic Uncertainty");
  tge_errpos->GetYaxis()->CenterTitle();
  tge_errpos->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_errpos->GetXaxis()->CenterTitle();
  leg_pos = new TLegend(0.48,0.78,0.88,0.88);
  leg_pos->SetFillColor(kWhite);
  leg_pos->SetBorderSize(0);
  leg_pos->AddEntry(tge_errpos,typelongstring,"p");
  leg_pos->Draw();

  sprintf(gifname,"Figures/single_suncert_%s_pos_%s%s.gif",pidstring,typestring,switchstring);
  sprintf(epsname,"Figures/single_suncert_%s_pos_%s%s.eps",pidstring,typestring,switchstring);
  c1->Print(gifname);
  c1->Print(epsname);


  // -- neg


  char textoutrationegname[100];
  sprintf(textoutrationegname,"Text/single_ratio_%s_neg_%s%s.dat",pidstring,typestring,switchstring);
  ofstream foutrationeg(textoutrationegname);

  char textoutsuncertnegname[100];
  sprintf(textoutsuncertnegname,"Text/single_suncert_%s_neg_%s%s.dat",pidstring,typestring,switchstring);
  ofstream foutsuncertneg(textoutsuncertnegname);

  float ptr[100], ratio[100], eratio[100];
  float eptr[100]={0};
  float error[100], derror[100];

  for(int i=0; i<100; i++)
    {
      ptr[i]=pt_sysneg[i];

      float A, dA, B, dB;
      A = yield_sysneg[i];
      dA = eyield_sysneg[i];
      B = yield_refneg[i];
      dB = eyield_refneg[i];

      if(A>0&&B>0)
	{
	  ratio[i]= A/B;
	  eratio[i] = ratio[i]*sqrt((dA/A)**2+(dB/B)**2);
	}
      else
	{
	  ratio[i]=10;
	  eratio[i]=0;
	}
      //if(pt_sysneg[i]<0.5||pt_sysneg[i]>5.0||(ipid==3&&pt_sysneg[i]>3.0))
      if(pt_sysneg[i]<0.5||pt_sysneg[i]>5.0||(ipid==1&&pt_sysneg[i]>3.5))
	//if(pt_sysneg[i]<1.0||pt_sysneg[i]>5.0||(ipid==1&&pt_sysneg[i]>3.5))
	{
	  ratio[i]=10;
	  eratio[i]=0;
	}

      error[i] = fabs(1.0-ratio[i]);
      derror[i] = eratio[i];
      foutrationeg<<ptr[i]<<"\t"<<ratio[i]<<"\t"<<eratio[i]<<endl;
      foutsuncertneg<<ptr[i]<<"\t"<<error[i]<<"\t"<<derror[i]<<endl;
    }
  TGraphErrors *tge_ratneg = new TGraphErrors(100,ptr,ratio,eptr,eratio);
  tge_ratneg->SetMarkerStyle(kFullCircle);
  tge_ratneg->SetMarkerColor(kBlack);
  //TGraphErrors *tge_errneg = new TGraphErrors(100,ptr,error,eptr,derror);
  TGraphErrors *tge_errneg = new TGraphErrors(34,ptr,error,eptr,derror);
  tge_errneg->SetMarkerStyle(kFullCircle);
  tge_errneg->SetMarkerColor(kBlack);



  c1->Clear();
  c1->SetLogy(0);
  tge_ratneg->Draw("ap");
  line->Draw("same");
  //tge_ratneg->SetMaximum(2.0);
  //tge_ratneg->SetMinimum(0.0);
  tge_ratneg->SetMaximum(2.4);
  tge_ratneg->SetMinimum(0.6);
  tge_ratneg->GetXaxis()->SetLimits(0.0,high);
  tge_ratneg->GetYaxis()->SetTitle("Systematic Ratio");
  tge_ratneg->GetYaxis()->CenterTitle();
  tge_ratneg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_ratneg->GetXaxis()->CenterTitle();
  leg_neg = new TLegend(0.48,0.78,0.88,0.88);
  leg_neg->SetFillColor(kWhite);
  leg_neg->SetBorderSize(0);
  leg_neg->AddEntry(tge_ratneg,typelongstring,"p");
  leg_neg->Draw();

  sprintf(gifname,"Figures/single_ratio_%s_neg_%s%s.gif",pidstring,typestring,switchstring);
  sprintf(epsname,"Figures/single_ratio_%s_neg_%s%s.eps",pidstring,typestring,switchstring);
  c1->Print(gifname);
  c1->Print(epsname);

  c1->Clear();
  tge_errneg->Draw("ap");
  line0->Draw("same");
  tge_errneg->SetMaximum(errheight);
  tge_errneg->SetMinimum(-0.1);
  tge_errneg->GetXaxis()->SetLimits(0.0,high);
  tge_errneg->GetYaxis()->SetTitle("Systematic Uncertainty");
  tge_errneg->GetYaxis()->CenterTitle();
  tge_errneg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge_errneg->GetXaxis()->CenterTitle();
  leg_neg = new TLegend(0.48,0.78,0.88,0.88);
  leg_neg->SetFillColor(kWhite);
  leg_neg->SetBorderSize(0);
  leg_neg->AddEntry(tge_errneg,typelongstring,"p");
  leg_neg->Draw();

  sprintf(gifname,"Figures/single_suncert_%s_neg_%s%s.gif",pidstring,typestring,switchstring);
  sprintf(epsname,"Figures/single_suncert_%s_neg_%s%s.eps",pidstring,typestring,switchstring);
  c1->Print(gifname);
  c1->Print(epsname);








}


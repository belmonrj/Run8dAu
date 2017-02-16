void rcp()
{

  doit_file(0,4);
  doit_file(1,5);
  doit_fileK(0,2);
  doit_fileK(1,3);

}



void doit_file(int pionid=0, int protonid=6)
{

  float ymin = 0.0;
  float xmin = 0.0;
  float ymax = 3.0;
  float xmax = 6.0;
  const int nbin = 44;
  if(nbin < (xmax-3.0)*2+30)
    {
      cout<<"incorrect number of bins"<<endl;
      cout<<"number of bins is "<<nbin<<" but number of bins needed is "<<(xmax-3.0)*2+30<<endl;
    }

  const float normal = 15.061/3.198;

  TLine *line = new TLine(xmin,1.0,xmax,1.0);

  TCanvas *c1 = new TCanvas("c1","",800,600);

  TF1 *fun = new TF1("fun","pol0",0,10);
  fun->SetParameter(0,1);

  float tmp;

  char centstring_C[10];
  sprintf(centstring_C,"0020");
  char centstring_P[10];
  sprintf(centstring_P,"6088");

  char fnameinposcb_C[100];
  char fnameinnegcb_C[100];
  char fnameinposcb_P[100];
  char fnameinnegcb_P[100];

  float ept[nbin]={0};

  // ----------------------- //
  // ----------------------- //
  // ---                 --- //
  // --- first the pions --- //
  // ---                 --- //
  // ----------------------- //
  // ----------------------- //

  // ---------------------- //
  // --- do the central --- //
  // ---------------------- //
  sprintf(fnameinposcb_C,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_C);
  ifstream finposcb_C;
  ifstream finnegcb_C;
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  float pT_poscb_C[nbin], yield_poscb_C[nbin], eyield_poscb_C[nbin];
  float pT_negcb_C[nbin], yield_negcb_C[nbin], eyield_negcb_C[nbin];
  for(int i=0; i<30; i++)
    {
      finposcb_C>>pT_poscb_C[i]>>yield_poscb_C[i]>>eyield_poscb_C[i];
      finnegcb_C>>pT_negcb_C[i]>>yield_negcb_C[i]>>eyield_negcb_C[i];
    }
  finposcb_C.close();
  finnegcb_C.close();
  sprintf(fnameinposcb_C,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_C);
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  for(int i=0; i<nbin-24; i++)
    {
      if(i<6)
	{
	  finposcb_C>>tmp>>tmp>>tmp;
	  finnegcb_C>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_C>>pT_poscb_C[i+24]>>yield_poscb_C[i+24]>>eyield_poscb_C[i+24];
	  finnegcb_C>>pT_negcb_C[i+24]>>yield_negcb_C[i+24]>>eyield_negcb_C[i+24];
	}
    }
  finposcb_C.close();
  finnegcb_C.close();

  // ---------------------- //
  // --- now peripheral --- //
  // ---------------------- //
  sprintf(fnameinposcb_P,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_P);
  ifstream finposcb_P;
  ifstream finnegcb_P;
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  float pT_poscb_P[nbin], yield_poscb_P[nbin], eyield_poscb_P[nbin];
  float pT_negcb_P[nbin], yield_negcb_P[nbin], eyield_negcb_P[nbin];
  for(int i=0; i<30; i++)
    {
      finposcb_P>>pT_poscb_P[i]>>yield_poscb_P[i]>>eyield_poscb_P[i];
      finnegcb_P>>pT_negcb_P[i]>>yield_negcb_P[i]>>eyield_negcb_P[i];
    }
  finposcb_P.close();
  finnegcb_P.close();
  sprintf(fnameinposcb_P,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_P);
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  for(int i=0; i<nbin-24; i++)
    {
      if(i<6)
	{
	  finposcb_P>>tmp>>tmp>>tmp;
	  finnegcb_P>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_P>>pT_poscb_P[i+24]>>yield_poscb_P[i+24]>>eyield_poscb_P[i+24];
	  finnegcb_P>>pT_negcb_P[i+24]>>yield_negcb_P[i+24]>>eyield_negcb_P[i+24];
	}
    }
  finposcb_P.close();
  finnegcb_P.close();

  float pTpos[nbin], ratiopos[nbin], eratiopos[nbin], esysratiopos[nbin];
  float pTneg[nbin], rationeg[nbin], erationeg[nbin], esysrationeg[nbin];

  float pTpos_pion_nq[nbin], epTpos_pion_nq[nbin];
  float pTneg_pion_nq[nbin], epTneg_pion_nq[nbin];
  float ratiopos_pion_nq[nbin], eratiopos_pion_nq[nbin], esysratiopos_pion_nq[nbin];
  float rationeg_pion_nq[nbin], erationeg_pion_nq[nbin], esysrationeg_pion_nq[nbin];
  char filename[100];
  sprintf(filename,"regular/rcp_%d.txt",pionid);
  ofstream ftxt(filename);
  sprintf(filename,"regular/rcp_%d.tex",pionid);
  ofstream ftex(filename);
  for(int i=0; i<nbin; i++)
    {
      if(yield_poscb_P[i]>0&&yield_negcb_P[i]>0)
	{
	  pTpos[i] = pT_poscb_C[i];
	  ratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i];
	  eratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i]
	    *sqrt((eyield_poscb_C[i]/yield_poscb_C[i])**2+(eyield_poscb_P[i]/yield_poscb_P[i])**2);
	  pTneg[i] = pT_negcb_C[i];
	  rationeg[i] = yield_negcb_C[i]/yield_negcb_P[i];
	  erationeg[i] = yield_negcb_C[i]/yield_negcb_P[i]
	    *sqrt((eyield_negcb_C[i]/yield_negcb_C[i])**2+(eyield_negcb_P[i]/yield_negcb_P[i])**2);
	}
      else
	{
	  pTpos[i]=0;
	  pTneg[i]=0;
	  ratiopos[i]=-9;
	  rationeg[i]=-9;
	  eratiopos[i]=0;
	  erationeg[i]=0;
	}
      ratiopos[i] /= normal;
      rationeg[i] /= normal;
      eratiopos[i] /= normal;
      erationeg[i] /= normal;
      esysratiopos[i] = ratiopos[i]*0.1; // 10% sys uncert
      esysrationeg[i] = rationeg[i]*0.1; // 10% sys uncert
      // nq scaling?
      pTpos_pion_nq[i] = pTpos[i]/2.0;
      epTpos_pion_nq[i] = 0;
      ratiopos_pion_nq[i] = ratiopos[i]/2.0;
      eratiopos_pion_nq[i] = eratiopos[i]/2.0;
      esysratiopos_pion_nq[i] = esysratiopos[i]/2.0;
      pTneg_pion_nq[i] = pTneg[i]/2.0;
      epTneg_pion_nq[i] = 0;
      rationeg_pion_nq[i] = rationeg[i]/2.0;
      erationeg_pion_nq[i] = erationeg[i]/2.0;
      esysrationeg_pion_nq[i] = esysrationeg[i]/2.0;
      ftxt<<pTpos[i]<<"\t"<<ratiopos[i]<<"\t"<<eratiopos[i]<<"\t"<<rationeg[i]<<"\t"<<erationeg[i]<<endl;
      ftex<<pTpos[i]<<" & "<<ratiopos[i]<<" & "<<eratiopos[i]<<" & "<<rationeg[i]<<" & "<<erationeg[i]<<" \\\\ "<<endl;
      if(pTpos[i]<0.5||pTpos[i]>5.0)
	{
	  // enforce limit here
	  ratiopos[i] = -9;
	  rationeg[i] = -9;
	}
    }

  TGraphErrors *tge_pospion = new TGraphErrors(nbin,pTpos,ratiopos,ept,eratiopos);
  TGraphErrors *tge_negpion = new TGraphErrors(nbin,pTneg,rationeg,ept,erationeg);
  TGraphErrors *tge_syspospion = new TGraphErrors(nbin,pTpos,ratiopos,ept,esysratiopos);
  TGraphErrors *tge_sysnegpion = new TGraphErrors(nbin,pTneg,rationeg,ept,esysrationeg);

  TGraphErrors *tge_pospion_nq = new TGraphErrors(nbin,pTpos_pion_nq,ratiopos,ept,eratiopos);
  TGraphErrors *tge_pospion_NQ = new TGraphErrors(nbin,pTpos_pion_nq,ratiopos_pion_nq,ept,eratiopos_pion_nq);
  TGraphErrors *tge_negpion_nq = new TGraphErrors(nbin,pTneg_pion_nq,rationeg,ept,erationeg);
  TGraphErrors *tge_negpion_NQ = new TGraphErrors(nbin,pTneg_pion_nq,rationeg_pion_nq,ept,erationeg_pion_nq);
  TGraphErrors *tge_syspospion_nq = new TGraphErrors(nbin,pTpos_pion_nq,ratiopos,ept,esysratiopos);
  TGraphErrors *tge_syspospion_NQ = new TGraphErrors(nbin,pTpos_pion_nq,ratiopos_pion_nq,ept,esysratiopos_pion_nq);
  TGraphErrors *tge_sysnegpion_nq = new TGraphErrors(nbin,pTneg_pion_nq,rationeg,ept,esysrationeg);
  TGraphErrors *tge_sysnegpion_NQ = new TGraphErrors(nbin,pTneg_pion_nq,rationeg_pion_nq,ept,esysrationeg_pion_nq);


  // ----------------------- //
  // ----------------------- //
  // ---                 --- //
  // --- now the protons --- //
  // ---                 --- //
  // ----------------------- //
  // ----------------------- //

  // ---------------------- //
  // --- do the central --- //
  // ---------------------- //
  sprintf(fnameinposcb_C,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring_C);
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  for(int i=0; i<30; i++)
    {
      finposcb_C>>pT_poscb_C[i]>>yield_poscb_C[i]>>eyield_poscb_C[i];
      finnegcb_C>>pT_negcb_C[i]>>yield_negcb_C[i]>>eyield_negcb_C[i];
    }
  finposcb_C.close();
  finnegcb_C.close();
  sprintf(fnameinposcb_C,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring_C);
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  for(int i=0; i<nbin-24; i++)
    {
      if(i<6)
	{
	  finposcb_C>>tmp>>tmp>>tmp;
	  finnegcb_C>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_C>>pT_poscb_C[i+24]>>yield_poscb_C[i+24]>>eyield_poscb_C[i+24];
	  finnegcb_C>>pT_negcb_C[i+24]>>yield_negcb_C[i+24]>>eyield_negcb_C[i+24];
	}
    }
  finposcb_C.close();
  finnegcb_C.close();

  // ---------------------- //
  // --- now peripheral --- //
  // ---------------------- //
  sprintf(fnameinposcb_P,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring_P);
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  for(int i=0; i<30; i++)
    {
      finposcb_P>>pT_poscb_P[i]>>yield_poscb_P[i]>>eyield_poscb_P[i];
      finnegcb_P>>pT_negcb_P[i]>>yield_negcb_P[i]>>eyield_negcb_P[i];
    }
  finposcb_P.close();
  finnegcb_P.close();
  sprintf(fnameinposcb_P,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring_P);
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  for(int i=0; i<nbin-24; i++)
    {
      if(i<6)
	{
	  finposcb_P>>tmp>>tmp>>tmp;
	  finnegcb_P>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_P>>pT_poscb_P[i+24]>>yield_poscb_P[i+24]>>eyield_poscb_P[i+24];
	  finnegcb_P>>pT_negcb_P[i+24]>>yield_negcb_P[i+24]>>eyield_negcb_P[i+24];
	}
    }
  finposcb_P.close();
  finnegcb_P.close();

  float pTpos_proton_nq[nbin], epTpos_proton_nq[nbin];
  float pTneg_proton_nq[nbin], epTneg_proton_nq[nbin];
  float ratiopos_proton_nq[nbin], eratiopos_proton_nq[nbin], esysratiopos_proton_nq[nbin];
  float rationeg_proton_nq[nbin], erationeg_proton_nq[nbin], esysrationeg_proton_nq[nbin];
  sprintf(filename,"regular/rcp_%d.txt",protonid);
  ofstream ftxt(filename);
  sprintf(filename,"regular/rcp_%d.tex",protonid);
  ofstream ftex(filename);
  for(int i=0; i<nbin; i++)
    {
      if(yield_poscb_P[i]>0&&yield_negcb_P[i]>0)
	{
	  pTpos[i] = pT_poscb_C[i];
	  ratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i];
	  eratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i]
	    *sqrt((eyield_poscb_C[i]/yield_poscb_C[i])**2+(eyield_poscb_P[i]/yield_poscb_P[i])**2);
	  pTneg[i] = pT_negcb_C[i];
	  rationeg[i] = yield_negcb_C[i]/yield_negcb_P[i];
	  erationeg[i] = yield_negcb_C[i]/yield_negcb_P[i]
	    *sqrt((eyield_negcb_C[i]/yield_negcb_C[i])**2+(eyield_negcb_P[i]/yield_negcb_P[i])**2);
	}
      else
	{
	  pTpos[i]=0;
	  pTneg[i]=0;
	  ratiopos[i]=-9;
	  rationeg[i]=-9;
	  eratiopos[i]=0;
	  erationeg[i]=0;
	}
      ratiopos[i] /= normal;
      rationeg[i] /= normal;
      eratiopos[i] /= normal;
      erationeg[i] /= normal;
      esysratiopos[i] = ratiopos[i]*0.1; // 10% sys uncert
      esysrationeg[i] = rationeg[i]*0.1; // 10% sys uncert
      // nq scaling?
      pTpos_proton_nq[i] = pTpos[i]/3.0;
      epTpos_proton_nq[i] = 0;
      ratiopos_proton_nq[i] = ratiopos[i]/3.0;
      eratiopos_proton_nq[i] = eratiopos[i]/3.0;
      esysratiopos_proton_nq[i] = esysratiopos[i]/3.0;
      pTneg_proton_nq[i] = pTneg[i]/3.0;
      epTneg_proton_nq[i] = 0;
      rationeg_proton_nq[i] = rationeg[i]/3.0;
      erationeg_proton_nq[i] = erationeg[i]/3.0;
      esysrationeg_proton_nq[i] = esysrationeg[i]/3.0;
      ftxt<<pTpos[i]<<"\t"<<ratiopos[i]<<"\t"<<eratiopos[i]<<"\t"<<rationeg[i]<<"\t"<<erationeg[i]<<endl;
      ftex<<pTpos[i]<<" & "<<ratiopos[i]<<" & "<<eratiopos[i]<<" & "<<rationeg[i]<<" & "<<erationeg[i]<<" \\\\ "<<endl;
      if(pTpos[i]<0.5||pTpos[i]>5.0)
	{
	  // enforce limit here
	  ratiopos[i] = -9;
	  rationeg[i] = -9;
	}
    }

  TGraphErrors *tge_posproton = new TGraphErrors(nbin,pTpos,ratiopos,ept,eratiopos);
  TGraphErrors *tge_negproton = new TGraphErrors(nbin,pTneg,rationeg,ept,erationeg);
  TGraphErrors *tge_sysposproton = new TGraphErrors(nbin,pTpos,ratiopos,ept,esysratiopos);
  TGraphErrors *tge_sysnegproton = new TGraphErrors(nbin,pTneg,rationeg,ept,esysrationeg);

  TGraphErrors *tge_posproton_nq = new TGraphErrors(nbin,pTpos_proton_nq,ratiopos,ept,eratiopos);
  TGraphErrors *tge_posproton_NQ = new TGraphErrors(nbin,pTpos_proton_nq,ratiopos_proton_nq,ept,eratiopos_proton_nq);
  TGraphErrors *tge_negproton_nq = new TGraphErrors(nbin,pTneg_proton_nq,rationeg,ept,erationeg);
  TGraphErrors *tge_negproton_NQ = new TGraphErrors(nbin,pTneg_proton_nq,rationeg_proton_nq,ept,erationeg_proton_nq);
  TGraphErrors *tge_sysposproton_nq = new TGraphErrors(nbin,pTpos_proton_nq,ratiopos,ept,esysratiopos);
  TGraphErrors *tge_sysposproton_NQ = new TGraphErrors(nbin,pTpos_proton_nq,ratiopos_proton_nq,ept,esysratiopos_proton_nq);
  TGraphErrors *tge_sysnegproton_nq = new TGraphErrors(nbin,pTneg_proton_nq,rationeg,ept,esysrationeg);
  TGraphErrors *tge_sysnegproton_NQ = new TGraphErrors(nbin,pTneg_proton_nq,rationeg_proton_nq,ept,esysrationeg_proton_nq);



  tge_pospion->SetMarkerColor(kRed);
  tge_negpion->SetMarkerColor(kBlue);
  tge_posproton->SetMarkerColor(kRed);
  tge_negproton->SetMarkerColor(kBlue);

  tge_pospion->SetMarkerStyle(kFullCircle);
  tge_negpion->SetMarkerStyle(kFullCircle);
  tge_posproton->SetMarkerStyle(kFullSquare);
  tge_negproton->SetMarkerStyle(kFullSquare);

  tge_syspospion->SetMarkerColor(kRed);
  tge_syspospion->SetMarkerStyle(1);
  tge_syspospion->SetLineColor(kRed-10);
  tge_syspospion->SetLineWidth(15);
  tge_sysnegpion->SetMarkerColor(kBlue);
  tge_sysnegpion->SetMarkerStyle(1);
  tge_sysnegpion->SetLineColor(kBlue-10);
  tge_sysnegpion->SetLineWidth(15);

  tge_sysposproton->SetMarkerColor(kRed);
  tge_sysposproton->SetMarkerStyle(1);
  tge_sysposproton->SetLineColor(kRed-10);
  tge_sysposproton->SetLineWidth(15);
  tge_sysnegproton->SetMarkerColor(kBlue);
  tge_sysnegproton->SetMarkerStyle(1);
  tge_sysnegproton->SetLineColor(kBlue-10);
  tge_sysnegproton->SetLineWidth(15);


  // ----------------------- //
  // --- do the plotting --- //
  // ----------------------- //

  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tge_syspospion);
  tmg->Add(tge_sysnegpion);
  tmg->Add(tge_sysposproton);
  tmg->Add(tge_sysnegproton);
  tmg->Add(tge_pospion);
  tmg->Add(tge_negpion);
  tmg->Add(tge_posproton);
  tmg->Add(tge_negproton);
  tmg->Draw("apz");
  line->Draw("same");
  tmg->SetMaximum(ymax);
  tmg->SetMinimum(ymin);
  tmg->GetXaxis()->SetLimits(xmin,xmax);
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetYaxis()->SetTitle("R_{CP}");
  tmg->GetXaxis()->CenterTitle();
  tmg->GetYaxis()->CenterTitle();

  //TPaveText *tpt_coll = new TPaveText(xmin+0.5,ymax+0.01,xmax-0.5,ymax+0.16);
  TPaveText *tpt_coll = new TPaveText(xmin+0.5,ymax*1.01,xmax-0.5,ymax*1.1);
  tpt_coll->SetFillColor(kWhite);
  tpt_coll->SetBorderSize(0);
  tpt_coll->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tpt_coll->Draw();

  //TPaveText *tpt_cent = new TPaveText(xmin+0.25,ymax-0.4,xmin+1.5,ymax-0.2);
  TPaveText *tpt_cent = new TPaveText(xmax*0.4,ymax*0.85,xmax*0.6,ymax*0.95);
  tpt_cent->SetFillColor(kWhite);
  tpt_cent->SetBorderSize(0);
  tpt_cent->AddText("0-20%/60-88%");
  tpt_cent->Draw();

  TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->AddEntry(tge_pospion,"#pi^{+}","p");
  leg->AddEntry(tge_negpion,"#pi^{-}","p");
  leg->AddEntry(tge_posproton,"p","p");
  leg->AddEntry(tge_negproton,"#bar{p}","p");
  leg->Draw();

  char figname[100];
  sprintf(figname,"regular/rcp_%d%d.gif",pionid,protonid);
  c1->Print(figname);
  sprintf(figname,"regular/rcp_%d%d.eps",pionid,protonid);
  c1->Print(figname);

  c1->Clear();

  float pt[18];
  float ept[18]={0};
  float ratio[18], eratio[18];

  ifstream fpion1("ppg030/RCP/pion.dat");
  for(int i=0; i<18;i++)
    {
      fpion1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fpion1.close();
  TGraphErrors *ppgpion = new TGraphErrors(18, pt, ratio, ept, eratio);

  // ifstream fkaon1("ppg030/RCP/kaon.dat");
  // for(int i=0; i<16;i++)
  //   {
  //     fkaon1>>pt[i]>>ratio[i]>>eratio[i];
  //   }
  // fkaon1.close();
  // TGraphErrors *ppgkaon = new TGraphErrors(16, pt, ratio, ept, eratio);

  ifstream fproton1("ppg030/RCP/proton.dat");
  for(int i=0; i<17;i++)
    {
      fproton1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fproton1.close();
  TGraphErrors *ppgproton = new TGraphErrors(17, pt, ratio, ept, eratio);

  fpion1.open("ppg044/RCP/pi0.dat");
  //fpion1.open("ppg044/RCP/pi0_0169.dat");
  for(int i=0; i<18;i++)
    {
      fpion1>>pt[i]>>ratio[i]>>eratio[i];
      //cout<<pt[i]<<"\t"<<ratio[i]<<"\t"<<eratio[i]<<endl;
    }
  fpion1.close();
  TGraphErrors *ppgpion0 = new TGraphErrors(18, pt, ratio, ept, eratio);

  float ptstar[29];
  float eptstar[29]={0};
  float ratiostar[29];
  float eratiostar[29];

  ifstream fstarpi("StarData/pionrcp.dat");
  for(int i=0; i<29;i++)
    {
      fstarpi>>ptstar[i]>>ratiostar[i]>>eratiostar[i];
      // cout<<ptstar[i]<<" "<<ratiostar[i]<<endl;
    }
  fstarpi.close();
  TGraphErrors *starpion = new TGraphErrors(29, ptstar, ratiostar, eptstar, eratiostar);

  ifstream fstarpr("StarData/protonrcp.dat");
  for(int i=0; i<25;i++)
    {
      fstarpr>>ptstar[i]>>ratiostar[i]>>eratiostar[i];
      // cout<<ptstar[i]<<" "<<ratiostar[i]<<endl;
    }
  fstarpr.close();
  TGraphErrors *starproton = new TGraphErrors(25, ptstar, ratiostar, eptstar, eratiostar);

  ppgpion->SetMarkerStyle(kFullCircle);
  ppgpion->SetMarkerColor(kBlack);
  // ppgkaon->SetMarkerStyle(kFullTriangleUp);
  // ppgkaon->SetMarkerColor(kBlack);
  ppgproton->SetMarkerStyle(kFullSquare);
  ppgproton->SetMarkerColor(kBlack);
  ppgpion0->SetMarkerStyle(kOpenCircle);
  ppgpion0->SetMarkerColor(kBlack);

  starpion->SetMarkerStyle(kFullStar);
  starproton->SetMarkerStyle(kFullStar);
  starpion->SetMarkerSize(1.5);
  starproton->SetMarkerSize(1.5);

  c1->Clear();

  TMultiGraph *tmg2 = new TMultiGraph();
  tmg2->Add(tge_syspospion);
  tmg2->Add(tge_sysnegpion);
  tmg2->Add(tge_sysposproton);
  tmg2->Add(tge_sysnegproton);
  tmg2->Add(tge_pospion);
  tmg2->Add(tge_negpion);
  tmg2->Add(tge_posproton);
  tmg2->Add(tge_negproton);
  tmg2->Add(ppgpion);
  tmg2->Add(ppgproton);
  tmg2->Add(ppgpion0);
  tmg2->Draw("apz");
  line->Draw("same");
  tmg2->SetMaximum(ymax);
  tmg2->SetMinimum(ymin);
  tmg2->GetXaxis()->SetLimits(xmin,xmax);
  tmg2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg2->GetYaxis()->SetTitle("R_{CP}");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->CenterTitle();

  tpt_coll->Draw();
  tpt_cent->Draw();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(kWhite);
  leg2->AddEntry(tge_pospion,"#pi^{+}","p");
  leg2->AddEntry(tge_negpion,"#pi^{-}","p");
  leg2->AddEntry(tge_posproton,"p","p");
  leg2->AddEntry(tge_negproton,"#bar{p}","p");
  leg2->Draw();

  TLegend *leg3 = new TLegend(0.18,0.68,0.38,0.88);
  leg3->SetBorderSize(0);
  leg3->SetFillColor(kWhite);
  leg3->AddEntry(ppgpion,"#pi Run3","p");
  leg3->AddEntry(ppgproton,"p Run3","p");
  leg3->AddEntry(ppgpion0,"#pi^{0} Run3","p");
  leg3->Draw();

  sprintf(figname,"regular/rcp_ppg_%d%d.gif",pionid,protonid);
  c1->Print(figname);
  sprintf(figname,"regular/rcp_ppg_%d%d.eps",pionid,protonid);
  c1->Print(figname);

  c1->Clear();


  // STARSTARSTAR

  TMultiGraph *tmgS2 = new TMultiGraph();
  tmgS2->Add(tge_syspospion);
  tmgS2->Add(tge_sysnegpion);
  tmgS2->Add(tge_sysposproton);
  tmgS2->Add(tge_sysnegproton);
  tmgS2->Add(tge_pospion);
  tmgS2->Add(tge_negpion);
  tmgS2->Add(tge_posproton);
  tmgS2->Add(tge_negproton);
  tmgS2->Add(starpion);
  tmgS2->Add(starproton);
  tmgS2->Draw("apz");
  line->Draw("same");
  tmgS2->SetMaximum(ymax);
  tmgS2->SetMinimum(ymin);
  tmgS2->GetXaxis()->SetLimits(xmin,xmax);
  tmgS2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmgS2->GetYaxis()->SetTitle("R_{CP}");
  tmgS2->GetXaxis()->CenterTitle();
  tmgS2->GetYaxis()->CenterTitle();

  tpt_coll->Draw();
  tpt_cent->Draw();

  TLegend *legS2 = new TLegend(0.68,0.68,0.88,0.88);
  legS2->SetBorderSize(0);
  legS2->SetFillColor(kWhite);
  legS2->AddEntry(tge_pospion,"#pi^{+}","p");
  legS2->AddEntry(tge_negpion,"#pi^{-}","p");
  legS2->AddEntry(tge_posproton,"p","p");
  legS2->AddEntry(tge_negproton,"#bar{p}","p");
  legS2->Draw();

  TLegend *legS3 = new TLegend(0.18,0.68,0.38,0.88);
  legS3->SetBorderSize(0);
  legS3->SetFillColor(kWhite);
  legS3->AddEntry(starpion,"(#pi^{+}+#pi^{-})/2 STAR","p");
  legS3->AddEntry(starproton,"(p+#bar{p})/2 STAR","p");
  legS3->Draw();

  sprintf(figname,"regular/rcp_star_%d%d.gif",pionid,protonid);
  //c1->Print(figname);
  sprintf(figname,"regular/rcp_star_%d%d.eps",pionid,protonid);
  //c1->Print(figname);

  c1->Clear();


  // here

  TMultiGraph *tmg2 = new TMultiGraph();
  //tmg2->Add(tge_syspospion);
  //tmg2->Add(tge_sysnegpion);
  tmg2->Add(tge_sysposproton);
  tmg2->Add(tge_sysnegproton);
  //tmg2->Add(tge_pospion);
  //tmg2->Add(tge_negpion);
  tmg2->Add(tge_posproton);
  tmg2->Add(tge_negproton);
  //tmg2->Add(ppgpion);
  tmg2->Add(ppgproton);
  tmg2->Add(starproton);
  //tmg2->Add(ppgpion0);
  tmg2->Draw("apz");
  //line->Draw("same");
  TLine lineS(0.0,1.0,8.0,1.0);
  lineS.Draw();
  tmg2->SetMaximum(ymax);
  tmg2->SetMinimum(ymin);
  //tmg2->GetXaxis()->SetLimits(xmin,xmax);
  tmg2->GetXaxis()->SetLimits(0.0,8.0);
  tmg2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg2->GetYaxis()->SetTitle("R_{CP}");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->CenterTitle();

  // tpt_coll->Draw();
  // tpt_cent->Draw();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(kWhite);
  //leg2->AddEntry(tge_pospion,"#pi^{+}","p");
  //leg2->AddEntry(tge_negpion,"#pi^{-}","p");
  leg2->AddEntry(tge_posproton,"p","p");
  leg2->AddEntry(tge_negproton,"#bar{p}","p");
  leg2->Draw();

  TLegend *leg3 = new TLegend(0.18,0.68,0.38,0.88);
  leg3->SetBorderSize(0);
  leg3->SetFillColor(kWhite);
  //leg3->AddEntry(ppgpion,"#pi Run3","p");
  leg3->AddEntry(ppgproton,"p Run3","p");
  leg3->AddEntry(starproton,"(p+#bar{p})/2 STAR","p");
  //leg3->AddEntry(ppgpion0,"#pi^{0} Run3","p");
  leg3->Draw();

  sprintf(figname,"special/rcp_ppg_%d.gif",protonid);
  c1->Print(figname);
  sprintf(figname,"special/rcp_ppg_%d.eps",protonid);
  c1->Print(figname);

  c1->Clear();


  // here

  TMultiGraph *tmg2 = new TMultiGraph();
  tmg2->Add(tge_syspospion);
  tmg2->Add(tge_sysnegpion);
  //tmg2->Add(tge_sysposproton);
  //tmg2->Add(tge_sysnegproton);
  tmg2->Add(tge_pospion);
  tmg2->Add(tge_negpion);
  //tmg2->Add(tge_posproton);
  //tmg2->Add(tge_negproton);
  tmg2->Add(ppgpion);
  tmg2->Add(starpion);
  //tmg2->Add(ppgproton);
  tmg2->Add(ppgpion0);
  tmg2->Draw("apz");
  //line->Draw("same");
  lineS.Draw();
  tmg2->SetMaximum(ymax);
  tmg2->SetMinimum(ymin);
  //tmg2->GetXaxis()->SetLimits(xmin,xmax);
  tmg2->GetXaxis()->SetLimits(0.0,8.0);
  tmg2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg2->GetYaxis()->SetTitle("R_{CP}");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->CenterTitle();

  // tpt_coll->Draw();
  // tpt_cent->Draw();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(kWhite);
  leg2->AddEntry(tge_pospion,"#pi^{+}","p");
  leg2->AddEntry(tge_negpion,"#pi^{-}","p");
  //leg2->AddEntry(tge_posproton,"p","p");
  //leg2->AddEntry(tge_negproton,"#bar{p}","p");
  leg2->Draw();

  TLegend *leg3 = new TLegend(0.18,0.68,0.38,0.88);
  leg3->SetBorderSize(0);
  leg3->SetFillColor(kWhite);
  leg3->AddEntry(ppgpion,"#pi Run3","p");
  leg3->AddEntry(starpion,"#pi STAR","p");
  //leg3->AddEntry(ppgproton,"p Run3","p");
  leg3->AddEntry(ppgpion0,"#pi^{0} Run3","p");
  leg3->Draw();

  sprintf(figname,"special/rcp_ppg_%d.gif",pionid);
  c1->Print(figname);
  sprintf(figname,"special/rcp_ppg_%d.eps",pionid);
  c1->Print(figname);

  c1->Clear();






  tge_pospion_nq->SetMarkerColor(kRed);
  tge_negpion_nq->SetMarkerColor(kBlue);
  tge_posproton_nq->SetMarkerColor(kRed);
  tge_negproton_nq->SetMarkerColor(kBlue);

  tge_pospion_nq->SetMarkerStyle(kFullCircle);
  tge_negpion_nq->SetMarkerStyle(kFullCircle);
  tge_posproton_nq->SetMarkerStyle(kFullSquare);
  tge_negproton_nq->SetMarkerStyle(kFullSquare);

  tge_syspospion_nq->SetMarkerColor(kRed);
  tge_syspospion_nq->SetMarkerStyle(1);
  tge_syspospion_nq->SetLineColor(kRed-10);
  tge_syspospion_nq->SetLineWidth(15);
  tge_sysnegpion_nq->SetMarkerColor(kBlue);
  tge_sysnegpion_nq->SetMarkerStyle(1);
  tge_sysnegpion_nq->SetLineColor(kBlue-10);
  tge_sysnegpion_nq->SetLineWidth(15);

  tge_sysposproton_nq->SetMarkerColor(kRed);
  tge_sysposproton_nq->SetMarkerStyle(1);
  tge_sysposproton_nq->SetLineColor(kRed-10);
  tge_sysposproton_nq->SetLineWidth(15);
  tge_sysnegproton_nq->SetMarkerColor(kBlue);
  tge_sysnegproton_nq->SetMarkerStyle(1);
  tge_sysnegproton_nq->SetLineColor(kBlue-10);
  tge_sysnegproton_nq->SetLineWidth(15);

  TMultiGraph *tmg2 = new TMultiGraph();
  // tmg2->Add(tge_syspospion_nq);
  // tmg2->Add(tge_sysnegpion_nq);
  // tmg2->Add(tge_sysposproton_nq);
  // tmg2->Add(tge_sysnegproton_nq);
  tmg2->Add(tge_pospion_nq);
  //tmg2->Add(tge_negpion_nq);
  tmg2->Add(tge_posproton_nq);
  //tmg2->Add(tge_negproton_nq);
  tmg2->Draw("apz");
  tmg2->SetMaximum(ymax);
  tmg2->SetMinimum(ymin);
  tmg2->GetXaxis()->SetLimits(0.0,2.0);
  tmg2->GetXaxis()->SetTitle("p_{T}/n_{q} (GeV/c)");
  tmg2->GetYaxis()->SetTitle("R_{CP}");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->CenterTitle();

  tpt_coll->Draw();
  tpt_cent->Draw();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(kWhite);
  leg2->AddEntry(tge_pospion_nq,"#pi^{+}","p");
  //leg2->AddEntry(tge_negpion_nq,"#pi^{-}","p");
  leg2->AddEntry(tge_posproton_nq,"p","p");
  //leg2->AddEntry(tge_negproton_nq,"#bar{p}","p");
  leg2->Draw();

  sprintf(figname,"regular/rcp_nq_%d%d.gif",pionid,protonid);
  //c1->Print(figname);
  sprintf(figname,"regular/rcp_nq_%d%d.eps",pionid,protonid);
  //c1->Print(figname);



  c1->Clear();

  tge_pospion_NQ->SetMarkerColor(kRed);
  tge_negpion_NQ->SetMarkerColor(kBlue);
  tge_posproton_NQ->SetMarkerColor(kRed);
  tge_negproton_NQ->SetMarkerColor(kBlue);

  tge_pospion_NQ->SetMarkerStyle(kFullCircle);
  tge_negpion_NQ->SetMarkerStyle(kFullCircle);
  tge_posproton_NQ->SetMarkerStyle(kFullSquare);
  tge_negproton_NQ->SetMarkerStyle(kFullSquare);

  tge_syspospion_NQ->SetMarkerColor(kRed);
  tge_syspospion_NQ->SetMarkerStyle(1);
  tge_syspospion_NQ->SetLineColor(kRed-10);
  tge_syspospion_NQ->SetLineWidth(15);
  tge_sysnegpion_NQ->SetMarkerColor(kBlue);
  tge_sysnegpion_NQ->SetMarkerStyle(1);
  tge_sysnegpion_NQ->SetLineColor(kBlue-10);
  tge_sysnegpion_NQ->SetLineWidth(15);

  tge_sysposproton_NQ->SetMarkerColor(kRed);
  tge_sysposproton_NQ->SetMarkerStyle(1);
  tge_sysposproton_NQ->SetLineColor(kRed-10);
  tge_sysposproton_NQ->SetLineWidth(15);
  tge_sysnegproton_NQ->SetMarkerColor(kBlue);
  tge_sysnegproton_NQ->SetMarkerStyle(1);
  tge_sysnegproton_NQ->SetLineColor(kBlue-10);
  tge_sysnegproton_NQ->SetLineWidth(15);

  TMultiGraph *tmg2 = new TMultiGraph();
  // tmg2->Add(tge_syspospion_NQ);
  // tmg2->Add(tge_sysnegpion_NQ);
  // tmg2->Add(tge_sysposproton_NQ);
  // tmg2->Add(tge_sysnegproton_NQ);
  tmg2->Add(tge_pospion_NQ);
  //tmg2->Add(tge_negpion_NQ);
  tmg2->Add(tge_posproton_NQ);
  //tmg2->Add(tge_negproton_NQ);
  tmg2->Draw("apz");
  tmg2->SetMaximum(0.5);
  tmg2->SetMinimum(ymin);
  tmg2->GetXaxis()->SetLimits(0.0,2.0);
  tmg2->GetXaxis()->SetTitle("p_{T}/n_{q} (GeV/c)");
  tmg2->GetYaxis()->SetTitle("R_{CP}/n_{q}");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->CenterTitle();

  tpt_coll->Draw();
  tpt_cent->Draw();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(kWhite);
  leg2->AddEntry(tge_pospion_NQ,"#pi^{+}","p");
  //leg2->AddEntry(tge_negpion_NQ,"#pi^{-}","p");
  leg2->AddEntry(tge_posproton_NQ,"p","p");
  //leg2->AddEntry(tge_negproton_NQ,"#bar{p}","p");
  leg2->Draw();

  sprintf(figname,"regular/rcp_NQ_%d%d.gif",pionid,protonid);
  //c1->Print(figname);
  sprintf(figname,"regular/rcp_NQ_%d%d.eps",pionid,protonid);
  //c1->Print(figname);


  c1->Clear();
  delete c1;

}




void doit_fileK(int pionid=0, int kaonid=4)
{

  float ymin = 0.0;
  float xmin = 0.0;
  float ymax = 3.0;
  float xmax = 6.0;
  const int nbin = 40;
  if(nbin < (xmax-3.0)*2+30)
    {
      cout<<"incorrect number of bins"<<endl;
      cout<<"number of bins is "<<nbin<<" but number of bins needed is "<<(xmax-3.0)*2+30<<endl;
    }

  const float normal = 15.061/3.198;

  TLine *line = new TLine(xmin,1.0,xmax,1.0);

  TCanvas *c1 = new TCanvas("c1","",800,600);

  TF1 *fun = new TF1("fun","pol0",0,10);
  fun->SetParameter(0,1);

  float tmp;

  char centstring_C[10];
  sprintf(centstring_C,"0020");
  char centstring_P[10];
  sprintf(centstring_P,"6088");

  char fnameinposcb_C[100];
  char fnameinnegcb_C[100];
  char fnameinposcb_P[100];
  char fnameinnegcb_P[100];

  float ept[nbin]={0};

  // ----------------------- //
  // ----------------------- //
  // ---                 --- //
  // --- first the pions --- //
  // ---                 --- //
  // ----------------------- //
  // ----------------------- //

  // ---------------------- //
  // --- do the central --- //
  // ---------------------- //
  sprintf(fnameinposcb_C,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_C);
  ifstream finposcb_C;
  ifstream finnegcb_C;
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  float pT_poscb_C[nbin], yield_poscb_C[nbin], eyield_poscb_C[nbin];
  float pT_negcb_C[nbin], yield_negcb_C[nbin], eyield_negcb_C[nbin];
  for(int i=0; i<30; i++)
    {
      finposcb_C>>pT_poscb_C[i]>>yield_poscb_C[i]>>eyield_poscb_C[i];
      finnegcb_C>>pT_negcb_C[i]>>yield_negcb_C[i]>>eyield_negcb_C[i];
    }
  finposcb_C.close();
  finnegcb_C.close();
  sprintf(fnameinposcb_C,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_C);
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  for(int i=0; i<nbin-24; i++)
    {
      if(i<6)
	{
	  finposcb_C>>tmp>>tmp>>tmp;
	  finnegcb_C>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_C>>pT_poscb_C[i+24]>>yield_poscb_C[i+24]>>eyield_poscb_C[i+24];
	  finnegcb_C>>pT_negcb_C[i+24]>>yield_negcb_C[i+24]>>eyield_negcb_C[i+24];
	}
    }
  finposcb_C.close();
  finnegcb_C.close();

  // ---------------------- //
  // --- now peripheral --- //
  // ---------------------- //
  sprintf(fnameinposcb_P,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_P);
  ifstream finposcb_P;
  ifstream finnegcb_P;
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  float pT_poscb_P[nbin], yield_poscb_P[nbin], eyield_poscb_P[nbin];
  float pT_negcb_P[nbin], yield_negcb_P[nbin], eyield_negcb_P[nbin];
  for(int i=0; i<30; i++)
    {
      finposcb_P>>pT_poscb_P[i]>>yield_poscb_P[i]>>eyield_poscb_P[i];
      finnegcb_P>>pT_negcb_P[i]>>yield_negcb_P[i]>>eyield_negcb_P[i];
    }
  finposcb_P.close();
  finnegcb_P.close();
  sprintf(fnameinposcb_P,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring_P);
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  for(int i=0; i<nbin-24; i++)
    {
      if(i<6)
	{
	  finposcb_P>>tmp>>tmp>>tmp;
	  finnegcb_P>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_P>>pT_poscb_P[i+24]>>yield_poscb_P[i+24]>>eyield_poscb_P[i+24];
	  finnegcb_P>>pT_negcb_P[i+24]>>yield_negcb_P[i+24]>>eyield_negcb_P[i+24];
	}
    }
  finposcb_P.close();
  finnegcb_P.close();

  float pTpos[nbin], ratiopos[nbin], eratiopos[nbin], esysratiopos[nbin];
  float pTneg[nbin], rationeg[nbin], erationeg[nbin], esysrationeg[nbin];

  for(int i=0; i<nbin; i++)
    {
      if(yield_poscb_P[i]>0&&yield_negcb_P[i]>0)
	{
	  pTpos[i] = pT_poscb_C[i];
	  ratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i];
	  eratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i]
	    *sqrt((eyield_poscb_C[i]/yield_poscb_C[i])**2+(eyield_poscb_P[i]/yield_poscb_P[i])**2);
	  pTneg[i] = pT_negcb_C[i];
	  rationeg[i] = yield_negcb_C[i]/yield_negcb_P[i];
	  erationeg[i] = yield_negcb_C[i]/yield_negcb_P[i]
	    *sqrt((eyield_negcb_C[i]/yield_negcb_C[i])**2+(eyield_negcb_P[i]/yield_negcb_P[i])**2);
	}
      else
	{
	  pTpos[i]=0;
	  pTneg[i]=0;
	  ratiopos[i]=-9;
	  rationeg[i]=-9;
	  eratiopos[i]=0;
	  erationeg[i]=0;
	}
      ratiopos[i] /= normal;
      rationeg[i] /= normal;
      eratiopos[i] /= normal;
      erationeg[i] /= normal;
      esysratiopos[i] = ratiopos[i]*0.1; // 10% sys uncert
      esysrationeg[i] = rationeg[i]*0.1; // 10% sys uncert
      if(pTpos[i]<0.5||pTpos[i]>5.0)
	{
	  // enforce limit here
	  ratiopos[i] = -9;
	  rationeg[i] = -9;
	}
    }

  TGraphErrors *tge_pospion = new TGraphErrors(nbin,pTpos,ratiopos,ept,eratiopos);
  TGraphErrors *tge_negpion = new TGraphErrors(nbin,pTneg,rationeg,ept,erationeg);
  TGraphErrors *tge_syspospion = new TGraphErrors(nbin,pTpos,ratiopos,ept,esysratiopos);
  TGraphErrors *tge_sysnegpion = new TGraphErrors(nbin,pTneg,rationeg,ept,esysrationeg);



  // ----------------------- //
  // ----------------------- //
  // ---                 --- //
  // --- now the kaons --- //
  // ---                 --- //
  // ----------------------- //
  // ----------------------- //

  // ---------------------- //
  // --- do the central --- //
  // ---------------------- //
  sprintf(fnameinposcb_C,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",kaonid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",kaonid,centstring_C);
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  for(int i=0; i<30; i++)
    {
      finposcb_C>>pT_poscb_C[i]>>yield_poscb_C[i]>>eyield_poscb_C[i];
      finnegcb_C>>pT_negcb_C[i]>>yield_negcb_C[i]>>eyield_negcb_C[i];
    }
  finposcb_C.close();
  finnegcb_C.close();
  sprintf(fnameinposcb_C,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",kaonid,centstring_C);
  sprintf(fnameinnegcb_C,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",kaonid,centstring_C);
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  for(int i=0; i<nbin-24; i++)
    {
      if(i<6)
	{
	  finposcb_C>>tmp>>tmp>>tmp;
	  finnegcb_C>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_C>>pT_poscb_C[i+24]>>yield_poscb_C[i+24]>>eyield_poscb_C[i+24];
	  finnegcb_C>>pT_negcb_C[i+24]>>yield_negcb_C[i+24]>>eyield_negcb_C[i+24];
	}
    }
  finposcb_C.close();
  finnegcb_C.close();

  // ---------------------- //
  // --- now peripheral --- //
  // ---------------------- //
  sprintf(fnameinposcb_P,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",kaonid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",kaonid,centstring_P);
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  for(int i=0; i<30; i++)
    {
      finposcb_P>>pT_poscb_P[i]>>yield_poscb_P[i]>>eyield_poscb_P[i];
      finnegcb_P>>pT_negcb_P[i]>>yield_negcb_P[i]>>eyield_negcb_P[i];
    }
  finposcb_P.close();
  finnegcb_P.close();
  sprintf(fnameinposcb_P,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",kaonid,centstring_P);
  sprintf(fnameinnegcb_P,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",kaonid,centstring_P);
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  for(int i=0; i<nbin-24; i++)
    {
      if(i<6)
	{
	  finposcb_P>>tmp>>tmp>>tmp;
	  finnegcb_P>>tmp>>tmp>>tmp;
	}
      else
	{
	  finposcb_P>>pT_poscb_P[i+24]>>yield_poscb_P[i+24]>>eyield_poscb_P[i+24];
	  finnegcb_P>>pT_negcb_P[i+24]>>yield_negcb_P[i+24]>>eyield_negcb_P[i+24];
	}
    }
  finposcb_P.close();
  finnegcb_P.close();

  char filename[100];
  sprintf(filename,"regular/rcp_%d.txt",kaonid);
  ofstream ftxt(filename);
  sprintf(filename,"regular/rcp_%d.tex",kaonid);
  ofstream ftex(filename);
  for(int i=0; i<nbin; i++)
    {
      if(yield_poscb_P[i]>0&&yield_negcb_P[i]>0)
	{
	  pTpos[i] = pT_poscb_C[i];
	  ratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i];
	  eratiopos[i] = yield_poscb_C[i]/yield_poscb_P[i]
	    *sqrt((eyield_poscb_C[i]/yield_poscb_C[i])**2+(eyield_poscb_P[i]/yield_poscb_P[i])**2);
	  pTneg[i] = pT_negcb_C[i];
	  rationeg[i] = yield_negcb_C[i]/yield_negcb_P[i];
	  erationeg[i] = yield_negcb_C[i]/yield_negcb_P[i]
	    *sqrt((eyield_negcb_C[i]/yield_negcb_C[i])**2+(eyield_negcb_P[i]/yield_negcb_P[i])**2);
	}
      else
	{
	  pTpos[i]=0;
	  pTneg[i]=0;
	  ratiopos[i]=-9;
	  rationeg[i]=-9;
	  eratiopos[i]=0;
	  erationeg[i]=0;
	}
      ratiopos[i] /= normal;
      rationeg[i] /= normal;
      eratiopos[i] /= normal;
      erationeg[i] /= normal;
      esysratiopos[i] = ratiopos[i]*0.1; // 10% sys uncert
      esysrationeg[i] = rationeg[i]*0.1; // 10% sys uncert
      if(pTpos[i]<0.5||pTpos[i]>3.0)
	{
	  // enforce limit here
	  ratiopos[i] = -9;
	  rationeg[i] = -9;
	}
      ftxt<<pTpos[i]<<"\t"<<ratiopos[i]<<"\t"<<eratiopos[i]<<"\t"<<rationeg[i]<<"\t"<<erationeg[i]<<endl;
      ftex<<pTpos[i]<<" & "<<ratiopos[i]<<" & "<<eratiopos[i]<<" & "<<rationeg[i]<<" & "<<erationeg[i]<<" \\\\ "<<endl;
    }

  TGraphErrors *tge_poskaon = new TGraphErrors(nbin,pTpos,ratiopos,ept,eratiopos);
  TGraphErrors *tge_negkaon = new TGraphErrors(nbin,pTneg,rationeg,ept,erationeg);
  TGraphErrors *tge_sysposkaon = new TGraphErrors(nbin,pTpos,ratiopos,ept,esysratiopos);
  TGraphErrors *tge_sysnegkaon = new TGraphErrors(nbin,pTneg,rationeg,ept,esysrationeg);




  tge_pospion->SetMarkerColor(kRed);
  tge_negpion->SetMarkerColor(kBlue);
  tge_poskaon->SetMarkerColor(kRed);
  tge_negkaon->SetMarkerColor(kBlue);

  tge_pospion->SetMarkerStyle(kFullCircle);
  tge_negpion->SetMarkerStyle(kFullCircle);
  tge_poskaon->SetMarkerStyle(kFullSquare);
  tge_negkaon->SetMarkerStyle(kFullSquare);

  tge_syspospion->SetMarkerColor(kRed);
  tge_syspospion->SetMarkerStyle(1);
  tge_syspospion->SetLineColor(kRed-10);
  tge_syspospion->SetLineWidth(15);
  tge_sysnegpion->SetMarkerColor(kBlue);
  tge_sysnegpion->SetMarkerStyle(1);
  tge_sysnegpion->SetLineColor(kBlue-10);
  tge_sysnegpion->SetLineWidth(15);

  tge_sysposkaon->SetMarkerColor(kRed);
  tge_sysposkaon->SetMarkerStyle(1);
  tge_sysposkaon->SetLineColor(kRed-10);
  tge_sysposkaon->SetLineWidth(15);
  tge_sysnegkaon->SetMarkerColor(kBlue);
  tge_sysnegkaon->SetMarkerStyle(1);
  tge_sysnegkaon->SetLineColor(kBlue-10);
  tge_sysnegkaon->SetLineWidth(15);


  // ----------------------- //
  // --- do the plotting --- //
  // ----------------------- //

  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tge_syspospion);
  tmg->Add(tge_sysnegpion);
  tmg->Add(tge_sysposkaon);
  tmg->Add(tge_sysnegkaon);
  tmg->Add(tge_pospion);
  tmg->Add(tge_negpion);
  tmg->Add(tge_poskaon);
  tmg->Add(tge_negkaon);
  tmg->Draw("apz");
  line->Draw("same");
  tmg->SetMaximum(ymax);
  tmg->SetMinimum(ymin);
  tmg->GetXaxis()->SetLimits(xmin,xmax);
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetYaxis()->SetTitle("R_{CP}");
  tmg->GetXaxis()->CenterTitle();
  tmg->GetYaxis()->CenterTitle();

  //TPaveText *tpt_coll = new TPaveText(xmin+0.5,ymax+0.01,xmax-0.5,ymax+0.16);
  TPaveText *tpt_coll = new TPaveText(xmin+0.5,ymax*1.01,xmax-0.5,ymax*1.1);
  tpt_coll->SetFillColor(kWhite);
  tpt_coll->SetBorderSize(0);
  tpt_coll->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tpt_coll->Draw();

  //TPaveText *tpt_cent = new TPaveText(xmin+0.25,ymax-0.4,xmin+1.5,ymax-0.2);
  //TPaveText *tpt_cent = new TPaveText(xmax*0.1,ymax*0.75,xmax*0.4,ymax*0.88);
  TPaveText *tpt_cent = new TPaveText(xmax*0.4,ymax*0.75,xmax*0.6,ymax*0.88);
  tpt_cent->SetFillColor(kWhite);
  tpt_cent->SetBorderSize(0);
  tpt_cent->AddText("0-20%/60-88%");
  tpt_cent->Draw();

  TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->AddEntry(tge_pospion,"#pi^{+}","p");
  leg->AddEntry(tge_negpion,"#pi^{-}","p");
  leg->AddEntry(tge_poskaon,"K^{+}","p");
  leg->AddEntry(tge_negkaon,"K^{-}","p");
  leg->Draw();

  char figname[100];
  sprintf(figname,"regular/rcp_%d%d.gif",pionid,kaonid);
  c1->Print(figname);
  sprintf(figname,"regular/rcp_%d%d.eps",pionid,kaonid);
  c1->Print(figname);

  c1->Clear();

  float pt[18];
  float ept[18]={0};
  float ratio[18], eratio[18];

  ifstream fpion1("ppg030/RCP/pion.dat");
  for(int i=0; i<18;i++)
    {
      fpion1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fpion1.close();
  TGraphErrors *ppgpion = new TGraphErrors(18, pt, ratio, ept, eratio);

  ifstream fkaon1("ppg030/RCP/kaon.dat");
  for(int i=0; i<13;i++)
    {
      fkaon1>>pt[i]>>ratio[i]>>eratio[i];
    }
  fkaon1.close();
  TGraphErrors *ppgkaon = new TGraphErrors(13, pt, ratio, ept, eratio);

  // ifstream fkaon1("ppg030/RCP/kaon.dat");
  // for(int i=0; i<22;i++)
  //   {
  //     fkaon1>>pt[i]>>ratio[i]>>eratio[i];
  //   }
  // fkaon1.close();
  // TGraphErrors *ppgkaon = new TGraphErrors(22, pt, ratio, ept, eratio);

  fpion1.open("ppg044/RCP/pi0.dat");
  for(int i=0; i<18;i++)
    {
      fpion1>>pt[i]>>ratio[i]>>eratio[i];
      //cout<<pt[i]<<"\t"<<ratio[i]<<"\t"<<eratio[i]<<endl;
    }
  fpion1.close();
  TGraphErrors *ppgpion0 = new TGraphErrors(18, pt, ratio, ept, eratio);

  ppgpion->SetMarkerStyle(kFullCircle);
  ppgpion->SetMarkerColor(kBlack);
  // ppgkaon->SetMarkerStyle(kFullTriangleUp);
  // ppgkaon->SetMarkerColor(kBlack);
  ppgkaon->SetMarkerStyle(kFullSquare);
  ppgkaon->SetMarkerColor(kBlack);
  ppgpion0->SetMarkerStyle(kOpenCircle);
  ppgpion0->SetMarkerColor(kBlack);



  TMultiGraph *tmg2 = new TMultiGraph();
  tmg2->Add(tge_syspospion);
  tmg2->Add(tge_sysnegpion);
  tmg2->Add(tge_sysposkaon);
  tmg2->Add(tge_sysnegkaon);
  tmg2->Add(tge_pospion);
  tmg2->Add(tge_negpion);
  tmg2->Add(tge_poskaon);
  tmg2->Add(tge_negkaon);
  tmg2->Add(ppgpion);
  tmg2->Add(ppgkaon);
  tmg2->Add(ppgpion0);
  tmg2->Draw("apz");
  line->Draw("same");
  tmg2->SetMaximum(ymax);
  tmg2->SetMinimum(ymin);
  tmg2->GetXaxis()->SetLimits(xmin,xmax);
  tmg2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg2->GetYaxis()->SetTitle("R_{CP}");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->CenterTitle();

  tpt_coll->Draw();
  tpt_cent->Draw();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(kWhite);
  leg2->AddEntry(tge_pospion,"#pi^{+}","p");
  leg2->AddEntry(tge_negpion,"#pi^{-}","p");
  leg2->AddEntry(tge_poskaon,"K^{+}","p");
  leg2->AddEntry(tge_negkaon,"K^{-}","p");
  leg2->Draw();

  TLegend *leg3 = new TLegend(0.18,0.68,0.38,0.88);
  leg3->SetBorderSize(0);
  leg3->SetFillColor(kWhite);
  leg3->AddEntry(ppgpion,"#pi Run3","p");
  leg3->AddEntry(ppgkaon,"K Run3","p");
  leg3->AddEntry(ppgpion0,"#pi^{0} Run3","p");
  leg3->Draw();

  sprintf(figname,"regular/rcp_ppg_%d%d.gif",pionid,kaonid);
  c1->Print(figname);
  sprintf(figname,"regular/rcp_ppg_%d%d.eps",pionid,kaonid);
  c1->Print(figname);





  c1->Clear();
  delete c1;

}



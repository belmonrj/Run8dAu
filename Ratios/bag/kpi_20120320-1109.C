void kpi()
{

  for(int i=0; i<5; i++)
    {
      doit_file(i,0,4);
    }
}


void doit_file(int centid=0, int pionid=0, int kaonid=4)
{

  float ymin = 0.0;
  float xmin = 0.0;
  float ymax = 1.6;
  float xmax = 4.0;

  TCanvas *c1 = new TCanvas("c1","",800,600);

  char centstring[5];
  if(centid==0) sprintf(centstring,"0010");
  else if(centid==1) sprintf(centstring,"1020");
  else if(centid==2) sprintf(centstring,"2040");
  else if(centid==3) sprintf(centstring,"4060");
  else if(centid==4) sprintf(centstring,"6092");
  else {cout<<"you gonna die"<<endl; return;}

  char bigcentstring[10];
  sprintf(bigcentstring,"MinBias"); // "default"
  if(centid==0) sprintf(bigcentstring,"0-10%%");
  if(centid==1) sprintf(bigcentstring,"10-20%%");
  if(centid==2) sprintf(bigcentstring,"20-40%%");
  if(centid==3) sprintf(bigcentstring,"40-60%%");
  if(centid==4) sprintf(bigcentstring,"60-92%%");


  char filename[100];
  ifstream fin;

  float pt[36], ept[36];
  float pionpos[36], epionpos[36];
  float kaonpos[36], ekaonpos[36];
  float pionneg[36], epionneg[36];
  float kaonneg[36], ekaonneg[36];
  float tmp;

  // --------------- //
  // --- pionpos --- //
  // --------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring);
  fin.open(filename);
  for(int i=0; i<30; i++)
    {
      fin>>pt[i]>>pionpos[i]>>epionpos[i];
      if((float)pt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring);
  fin.open(filename);
  for(int i=0; i<12; i++)
    {
      if(i<6) fin>>tmp>>tmp>>tmp;
      else
	{
	  fin>>pt[i+24]>>pionpos[i+24]>>epionpos[i+24];
	  if((float)pt[i+24]!=float(i)/2.0+0.25)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+24]<<" but pt is "<<i/2.0+0.25<<endl;
	    }
	}
    }
  fin.close();

  // --------------- //
  // --- pionneg --- //
  // --------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring);
  fin.open(filename);
  for(int i=0; i<30; i++)
    {
      fin>>pt[i]>>pionneg[i]>>epionneg[i];
      if((float)pt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring);
  fin.open(filename);
  for(int i=0; i<12; i++)
    {
      if(i<6) fin>>tmp>>tmp>>tmp;
      else
	{
	  fin>>pt[i+24]>>pionneg[i+24]>>epionneg[i+24];
	  if((float)pt[i+24]!=float(i)/2.0+0.25)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+24]<<" but pt is "<<i/2.0+0.25<<endl;
	    }
	}
    }
  fin.close();


  // ----------------- //
  // --- kaonpos --- //
  // ----------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",kaonid,centstring);
  fin.open(filename);
  for(int i=0; i<30; i++)
    {
      fin>>pt[i]>>kaonpos[i]>>ekaonpos[i];
      if((float)pt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",kaonid,centstring);
  fin.open(filename);
  for(int i=0; i<12; i++)
    {
      if(i<6) fin>>tmp>>tmp>>tmp;
      else
	{
	  fin>>pt[i+24]>>kaonpos[i+24]>>ekaonpos[i+24];
	  if((float)pt[i+24]!=float(i)/2.0+0.25)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+24]<<" but pt is "<<i/2.0+0.25<<endl;
	    }
	}
    }
  fin.close();

  // ----------------- //
  // --- kaonneg --- //
  // ----------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",kaonid,centstring);
  fin.open(filename);
  for(int i=0; i<30; i++)
    {
      fin>>pt[i]>>kaonneg[i]>>ekaonneg[i];
      if((float)pt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",kaonid,centstring);
  fin.open(filename);
  for(int i=0; i<12; i++)
    {
      if(i<6) fin>>tmp>>tmp>>tmp;
      else
	{
	  fin>>pt[i+24]>>kaonneg[i+24]>>ekaonneg[i+24];
	  if((float)pt[i+24]!=float(i)/2.0+0.25)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+24]<<" but pt is "<<i/2.0+0.25<<endl;
	    }
	}
    }
  fin.close();



  float ratiopos[36], eratiopos[36], esysratiopos[36];
  float rationeg[36], erationeg[36], esysrationeg[36];

  float A, dA, B, dB;

  for(int i=0; i<36; i++)
    {
      // pos
      A = pionpos[i];
      dA = epionpos[i];
      B = kaonpos[i];
      dB = ekaonpos[i];
      ratiopos[i] = B/A;
      eratiopos[i] = B/A*sqrt((dA/A)**2+(dB/B)**2);
      esysratiopos[i] = 0.1*(B/A);
      // neg
      A = pionneg[i];
      dA = epionneg[i];
      B = kaonneg[i];
      dB = ekaonneg[i];
      rationeg[i] = B/A;
      erationeg[i] = B/A*sqrt((dA/A)**2+(dB/B)**2);
      esysrationeg[i] = 0.1*(B/A);
    }
  
  
  for(int i=0; i<36; i++) ept[i]=0;  // yeah
  
  
  TGraphErrors *tge_pos = new TGraphErrors(36,pt,ratiopos,ept,eratiopos);
  tge_pos->SetMarkerColor(kRed);
  tge_pos->SetMarkerStyle(kFullSquare);
  TGraphErrors *tge_neg = new TGraphErrors(36,pt,rationeg,ept,erationeg);
  tge_neg->SetMarkerColor(kBlue);
  tge_neg->SetMarkerStyle(kFullSquare);

  TGraphErrors *tge_syspos = new TGraphErrors(36,pt,ratiopos,ept,esysratiopos);
  tge_syspos->SetMarkerColor(kRed);
  tge_syspos->SetMarkerStyle(1);
  tge_syspos->SetLineColor(kRed-10);
  tge_syspos->SetLineWidth(15);
  TGraphErrors *tge_sysneg = new TGraphErrors(36,pt,rationeg,ept,esysrationeg);
  tge_sysneg->SetMarkerColor(kBlue);
  tge_sysneg->SetMarkerStyle(1);
  tge_sysneg->SetLineColor(kBlue-10);
  tge_sysneg->SetLineWidth(15);

  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tge_sysneg);
  tmg->Add(tge_syspos);
  tmg->Add(tge_neg);
  tmg->Add(tge_pos);
  tmg->Draw("apz");
  tmg->SetMaximum(ymax);
  tmg->SetMinimum(ymin);
  tmg->GetXaxis()->SetLimits(xmin,xmax);
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetXaxis()->CenterTitle();
  tmg->GetYaxis()->SetTitle("K/#pi ratio");
  tmg->GetYaxis()->CenterTitle();

  TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->AddEntry(tge_pos,"K^{+}/#pi^{+}","p");
  leg->AddEntry(tge_neg,"K^{-}/#pi^{-}","p");
  leg->Draw();

  TPaveText *tpt_coll = new TPaveText(xmin+0.5,ymax+0.01,xmax-0.5,ymax+0.16);
  tpt_coll->SetFillColor(kWhite);
  tpt_coll->SetBorderSize(0);
  tpt_coll->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tpt_coll->Draw();

  TPaveText *tpt_cent = new TPaveText(xmin+0.5,ymax-0.5,xmin+1.5,ymax-0.1);
  tpt_cent->SetFillColor(kWhite);
  tpt_cent->SetBorderSize(0);
  tpt_cent->AddText(bigcentstring);
  tpt_cent->Draw();

  char figname[100];
  sprintf(figname,"regular/kpi_%d%d_cent%s.gif",pionid,kaonid,centstring);
  c1->Print(figname);
  sprintf(figname,"regular/kpi_%d%d_cent%s.eps",pionid,kaonid,centstring);
  c1->Print(figname);


  c1->Clear();
  // tmg->Clear();
  // tmg->Delete();



  // ----------------- //
  // --- Run2 part --- //
  // ----------------- //

  float ptpion[34];
  float ptkaon[34];
  float eptpion[34]={0};
  float eptkaon[34]={0};
  float ptratio[34];
  float eptratio[34]={0};
  float yieldpionpos[34],yieldpionneg[34];
  float eyieldpionpos[34],eyieldpionneg[34];
  float yieldkaonpos[34],yieldkaonneg[34];
  float eyieldkaonpos[34],eyieldkaonneg[34];
  float newratiopos[34],newrationeg[34];
  float enewratiopos[34],enewrationeg[34];

  float A, dA, B, dB;

  ifstream fin1;
  ifstream fin2;
  char fin1name[100];
  char fin2name[100];
  sprintf(fin1name,"ppg026/pospion_%s.dat",centstring);
  sprintf(fin2name,"ppg026/negpion_%s.dat",centstring);
  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<28; i++)
    {
      fin1>>ptpion[i]>>yieldpionpos[i]>>eyieldpionpos[i];
      fin2>>ptpion[i]>>yieldpionneg[i]>>eyieldpionneg[i];
    }
  fin1.close();  
  fin2.close();
  sprintf(fin1name,"ppg026/poskaon_%s.dat",centstring);
  sprintf(fin2name,"ppg026/negkaon_%s.dat",centstring);
  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<18; i++)
    {
      fin1>>ptkaon[i]>>yieldkaonpos[i]>>eyieldkaonpos[i];
      fin2>>ptkaon[i]>>yieldkaonneg[i]>>eyieldkaonneg[i];
    }
  fin1.close();  
  fin2.close();

  for(int i=0; i<18; i++)
    {
      //positive ratio
      A = yieldkaonpos[i];
      dA = eyieldkaonpos[i];
      B = yieldpionpos[i];
      dB = eyieldpionpos[i];
      newratiopos[i] = A/B;
      enewratiopos[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
      // cout<<"A = "<<A<<" dA = "<<dA<<" B = "<<B<<" dB = "<<dB<<endl;
      // cout<<"ptkaon is "<<ptkaon[i]<<endl;
      // cout<<"ptpion is "<<ptpion[i]<<endl;
      //negative ratio
      A = yieldkaonneg[i];
      dA = eyieldkaonneg[i];
      B = yieldpionneg[i];
      dB = eyieldpionneg[i];
      newrationeg[i] = A/B;
      enewrationeg[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
      if(newratiopos[i]==0) newratiopos[i]=-9;
      if(newrationeg[i]==0) newrationeg[i]=-9;
    }

  TGraphErrors *tposppg = new TGraphErrors(18,ptkaon,newratiopos,eptkaon,enewratiopos);
  tposppg->SetMarkerStyle(25);
  tposppg->SetMarkerColor(2);

  TGraphErrors *tnegppg = new TGraphErrors(18,ptkaon,newrationeg,eptkaon,enewrationeg);
  tnegppg->SetMarkerStyle(25);
  tnegppg->SetMarkerColor(4);

  // ------------------------ //
  // --- end of Run2 part --- //
  // ------------------------ //


  TMultiGraph *tmg2 = new TMultiGraph();
  tmg2->Add(tge_sysneg);
  tmg2->Add(tge_syspos);
  tmg2->Add(tge_neg);
  tmg2->Add(tge_pos);
  tmg2->Add(tnegppg);
  tmg2->Add(tposppg);
  tmg2->Draw("apz");
  tmg2->SetMaximum(ymax);
  tmg2->SetMinimum(ymin);
  tmg2->GetXaxis()->SetLimits(xmin,xmax);
  tmg2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->SetTitle("K/#pi ratio");
  tmg2->GetYaxis()->CenterTitle();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetFillColor(kWhite);
  leg2->SetBorderSize(0);
  leg2->AddEntry(tge_pos,"K^{+}/#pi^{+}","p");
  leg2->AddEntry(tge_neg,"K^{-}/#pi^{-}","p");
  leg2->AddEntry(tposppg,"K^{+}/#pi^{+} Run2","p");
  leg2->AddEntry(tnegppg,"K^{-}/#pi^{-} Run2","p");
  leg2->Draw();

  tpt_coll->Draw();
  tpt_cent->Draw();

  sprintf(figname,"regular/kpi_ppg_%d%d_cent%s.gif",pionid,kaonid,centstring);
  c1->Print(figname);
  sprintf(figname,"regular/kpi_ppg_%d%d_cent%s.eps",pionid,kaonid,centstring);
  c1->Print(figname);







  c1->Clear();
  //c1->Delete();
  delete c1;


}

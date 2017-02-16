void ppi()
{
  for(int i=0; i<5; i++)
    {
      doit_file(i,0,4);
      doit_file(i,1,5);
    }
}



void doit_file(int centid=0, int pionid=0, int protonid=6)
{

  float ymin = 0.0;
  float xmin = 0.0;
  float ymax = 0.6;
  float xmax = 6.0;
  const int nbin = 40;
  if(nbin < (xmax-3.0)*2+30)
    {
      cout<<"incorrect number of bins"<<endl;
      cout<<"number of bins is "<<nbin<<" but number of bins needed is "<<(xmax-3.0)*2+30<<endl;
    }

  //float epscale = 1.18; // same pbarp...

  TCanvas *c1 = new TCanvas("c1","",800,600);

  char centstring[5];
  if(centid==0) sprintf(centstring,"0088");
  else if(centid==1) sprintf(centstring,"0020");
  else if(centid==2) sprintf(centstring,"2040");
  else if(centid==3) sprintf(centstring,"4060");
  else if(centid==4) sprintf(centstring,"6088");
  else {cout<<"you gonna die"<<endl; return;}

  char bigcentstring[10];
  sprintf(bigcentstring,"MinBias"); // "default"
  if(centid==0) sprintf(bigcentstring,"0-88%%");
  if(centid==1) sprintf(bigcentstring,"0-20%%");
  if(centid==2) sprintf(bigcentstring,"20-40%%");
  if(centid==3) sprintf(bigcentstring,"40-60%%");
  if(centid==4) sprintf(bigcentstring,"60-88%%");

  char filename[100];
  ifstream fin;

  float pt[nbin], ept[nbin];
  float pionpos[nbin], epionpos[nbin];
  float protonpos[nbin], eprotonpos[nbin];
  float pionneg[nbin], epionneg[nbin];
  float protonneg[nbin], eprotonneg[nbin];
  float tmp;

  float twolo = 2.0;
  float twohi = 3.0;

  int start = twolo*10;
  int skip = twolo*5;
  int shift = start-skip;
  int end = ((twohi-twolo)*5)+(twolo*5);
  //int start3 = end;
  int skip3 = twohi*2;
  int shift3 = ((twohi-twolo)*5)+start-skip3;
  int end3 = (6-twohi)*2+(6*2);

  cout<< "start"   <<" "<< start  <<endl;
  cout<< "skip"    <<" "<< skip   <<endl;
  cout<< "shift"   <<" "<< shift  <<endl;
  cout<< "end"     <<" "<< end    <<endl;
  cout<< "skip3"   <<" "<< skip3  <<endl;
  cout<< "shift3"  <<" "<< shift3 <<endl;
  cout<< "end3"    <<" "<< end3   <<endl;

  // --------------- //
  // --- pionpos --- //
  // --------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring);
  fin.open(filename);
  for(int i=0; i<start; i++)
    {
      fin>>pt[i]>>pionpos[i]>>epionpos[i];
      if(fabs(pt[i]-(i/10.0+0.05))>0.01)
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R2_ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring);
  fin.open(filename);
  for(int i=0; i<end; i++)
    {
      if(i<skip) fin>>tmp>>tmp>>tmp;
      else
	{
	  fin>>pt[i+shift]>>pionpos[i+shift]>>epionpos[i+shift];
	  if(centid==4&&pionid==3) cout<<"i is "<<i<<" ishift is "<<i+shift<<" pt is "<<pt[i+shift]<<endl;
	  if(fabs(pt[i+shift]-(i/5.0+0.1))>0.01)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+10]<<" but pt is "<<i/5.0+0.1<<endl;
	    }
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring);
  fin.open(filename);
  for(int i=0; i<end3; i++)
    {
      if(i<skip3) fin>>tmp>>tmp>>tmp;
      else
	{
	  if(i+shift3>40) break;
	  fin>>pt[i+shift3]>>pionpos[i+shift3]>>epionpos[i+shift3];
	  if(centid==4&&pionid==3) cout<<"i is "<<i<<" ishift3 is "<<i+shift3<<" pt is "<<pt[i+shift3]<<endl;
	  if((float)pt[i+shift3]!=float(i)/2.0+0.25)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+shift3]<<" but pt is "<<i/2.0+0.25<<endl;
	    }
	}
    }
  fin.close();

  // --------------- //
  // --- pionneg --- //
  // --------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring);
  fin.open(filename);
  for(int i=0; i<start; i++)
    {
      fin>>pt[i]>>pionneg[i]>>epionneg[i];
      if((float)pt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R2_ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring);
  fin.open(filename);
  for(int i=0; i<end; i++)
    {
      if(i<skip) fin>>tmp>>tmp>>tmp;
      else
	{
	  fin>>pt[i+shift]>>pionneg[i+shift]>>epionneg[i+shift];
	  if(fabs(pt[i+shift]-(i/5.0+0.1))>0.01)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+shift]<<" but pt is "<<i/5.0+0.1<<endl;
	    }
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",pionid,centstring);
  fin.open(filename);
  for(int i=0; i<end3; i++)
    {
      if(i<skip3) fin>>tmp>>tmp>>tmp;
      else
	{
	  if(i+shift3>40) break;
	  fin>>pt[i+shift3]>>pionneg[i+shift3]>>epionneg[i+shift3];
	  if((float)pt[i+shift3]!=float(i)/2.0+0.25)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+shift3]<<" but pt is "<<i/2.0+0.25<<endl;
	    }
	}
    }
  fin.close();





  // ----------------- //
  // --- protonpos --- //
  // ----------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring);
  fin.open(filename);
  for(int i=0; i<start; i++)
    {
      fin>>pt[i]>>protonpos[i]>>eprotonpos[i];
      if((float)pt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R2_ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring);
  fin.open(filename);
  for(int i=0; i<end; i++)
    {
      if(i<skip) fin>>tmp>>tmp>>tmp;
      else
	{
	  fin>>pt[i+shift]>>protonpos[i+shift]>>eprotonpos[i+shift];
	  if(fabs(pt[i+shift]-(i/5.0+0.1))>0.01)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+shift]<<" but pt is "<<i/5.0+0.1<<endl;
	    }
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R5_ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring);
  fin.open(filename);
  for(int i=0; i<end3; i++)
    {
      if(i<skip3) fin>>tmp>>tmp>>tmp;
      else
	{
	  if(i+shift3>40) break;
	  fin>>pt[i+shift3]>>protonpos[i+shift3]>>eprotonpos[i+shift3];
	  if((float)pt[i+shift3]!=float(i)/2.0+0.25)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+shift3]<<" but pt is "<<i/2.0+0.25<<endl;
	    }
	}
    }
  fin.close();

  // ----------------- //
  // --- protonneg --- //
  // ----------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring);
  fin.open(filename);
  for(int i=0; i<start; i++)
    {
      fin>>pt[i]>>protonneg[i]>>eprotonneg[i];
      if((float)pt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R2_ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring);
  fin.open(filename);
  for(int i=0; i<end; i++)
    {
      if(i<skip) fin>>tmp>>tmp>>tmp;
      else
	{
	  fin>>pt[i+shift]>>protonneg[i+shift]>>eprotonneg[i+shift];
	  //cout<<protonneg[i+shift]<<endl;
	  if(fabs(pt[i+shift]-(i/5.0+0.1))>0.01)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+shift]<<" but pt is "<<i/5.0+0.1<<endl;
	    }
	}
    }
  fin.close();
  sprintf(filename,"FinalFeed/R5_ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring);
  fin.open(filename);
  for(int i=0; i<end3; i++)
    {
      if(i<skip3) fin>>tmp>>tmp>>tmp;
      else
	{
	  if(i+shift3>40) break;
	  fin>>pt[i+shift3]>>protonneg[i+shift3]>>eprotonneg[i+shift3];
	  if((float)pt[i+shift3]!=float(i)/2.0+0.25)
	    {
	      cout<<"you gonna die"<<endl;
	      cout<<"pt is "<<pt[i+shift3]<<" but pt is "<<i/2.0+0.25<<endl;
	    }
	}
    }
  fin.close();



  float ratiopos[nbin], eratiopos[nbin], esysratiopos[nbin];
  float rationeg[nbin], erationeg[nbin], esysrationeg[nbin];
  float A, dA, B, dB;
  sprintf(filename,"regular/ppi_%d%d_cent%s.txt",pionid,protonid,centstring);
  ofstream ftxt(filename);
  sprintf(filename,"regular/ppi_%d%d_cent%s.tex",pionid,protonid,centstring);
  ofstream ftex(filename);
  for(int i=0; i<nbin; i++)
    {
      // pos
      A = pionpos[i];
      dA = epionpos[i];
      B = protonpos[i];
      dB = eprotonpos[i];
      ratiopos[i] = B/A;
      eratiopos[i] = B/A*sqrt((dA/A)**2+(dB/B)**2);
      esysratiopos[i] = 0.05*(B/A);
      // neg
      A = pionneg[i];
      dA = epionneg[i];
      B = protonneg[i];
      dB = eprotonneg[i];
      rationeg[i] = B/A;
      erationeg[i] = B/A*sqrt((dA/A)**2+(dB/B)**2);
      esysrationeg[i] = 0.05*(B/A);
      if(pt[i]<0.5||pt[i]>5.0)
	{
	  // enforce limit here
	  ratiopos[i] = -9;
	  rationeg[i] = -9;
	  eratiopos[i] = 0;
	  erationeg[i] = 0;
	}
      ftxt<<pt[i]<<"\t"<<ratiopos[i]<<"\t"<<eratiopos[i]<<"\t"<<rationeg[i]<<"\t"<<erationeg[i]<<endl;
      ftex<<pt[i]<<" & "<<ratiopos[i]<<" & "<<eratiopos[i]<<" & "<<rationeg[i]<<" & "<<erationeg[i]<<" \\\\ "<<endl;
    }
  
  
  for(int i=0; i<nbin; i++) ept[i]=0;  // yeah
  
  
  TGraphErrors *tge_pos = new TGraphErrors(nbin,pt,ratiopos,ept,eratiopos);
  tge_pos->SetMarkerColor(kRed);
  tge_pos->SetMarkerStyle(kFullSquare);
  TGraphErrors *tge_neg = new TGraphErrors(nbin,pt,rationeg,ept,erationeg);
  tge_neg->SetMarkerColor(kBlue);
  tge_neg->SetMarkerStyle(kFullSquare);

  TGraphErrors *tge_syspos = new TGraphErrors(nbin,pt,ratiopos,ept,esysratiopos);
  tge_syspos->SetMarkerColor(kRed);
  tge_syspos->SetMarkerStyle(1);
  tge_syspos->SetLineColor(kRed-10);
  tge_syspos->SetLineWidth(15);
  TGraphErrors *tge_sysneg = new TGraphErrors(nbin,pt,rationeg,ept,esysrationeg);
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
  //tmg->SetMaximum(1.4);
  tmg->SetMaximum(ymax); // 1.4 is fine but this is for comparisons...
  tmg->SetMinimum(ymin);
  tmg->GetXaxis()->SetLimits(xmin,xmax);
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetXaxis()->CenterTitle();
  tmg->GetYaxis()->SetTitle("p/#pi ratio");
  tmg->GetYaxis()->CenterTitle();

  TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->AddEntry(tge_pos,"p/#pi^{+}","p");
  leg->AddEntry(tge_neg,"#bar{p}/#pi^{-}","p");
  leg->Draw();

  //TPaveText *tpt_coll = new TPaveText(xmin+0.5,ymax+0.01,xmax-0.5,ymax+0.16);
  TPaveText *tpt_coll = new TPaveText(xmin+0.5,ymax*1.01,xmax-0.5,ymax*1.1);
  tpt_coll->SetFillColor(kWhite);
  tpt_coll->SetBorderSize(0);
  tpt_coll->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tpt_coll->Draw();

  //TPaveText *tpt_cent = new TPaveText(xmin+0.25,ymax-0.4,xmin+1.5,ymax-0.2);
  TPaveText *tpt_cent = new TPaveText(xmax*0.1,ymax*0.75,xmax*0.4,ymax*0.88);
  tpt_cent->SetFillColor(kWhite);
  tpt_cent->SetBorderSize(0);
  tpt_cent->AddText(bigcentstring);
  tpt_cent->Draw();

  char figname[100];
  sprintf(figname,"regular/ppi_%d%d_cent%s.gif",pionid,protonid,centstring);
  c1->Print(figname);
  sprintf(figname,"regular/ppi_%d%d_cent%s.eps",pionid,protonid,centstring);
  c1->Print(figname);


  c1->Clear();
  // tmg->Clear();
  // tmg->Delete();



  // ----------------- //
  // --- Run2 part --- //
  // ----------------- //

  float ptpion[34];
  float ptproton[34];
  float eptpion[34]={0};
  float eptproton[34]={0};
  float ptratio[34];
  float eptratio[34]={0};
  float yieldpionpos[34],yieldpionneg[34];
  float eyieldpionpos[34],eyieldpionneg[34];
  float yieldprotonpos[34],yieldprotonneg[34];
  float eyieldprotonpos[34],eyieldprotonneg[34];
  float newratiopos[34],newrationeg[34];
  float enewratiopos[34],enewrationeg[34];

  float A, dA, B, dB;

  ifstream fin1;
  ifstream fin2;
  char fin1name[100];
  char fin2name[100];
  sprintf(fin1name,"ppg030/pospion_%s.dat",centstring);
  sprintf(fin2name,"ppg030/negpion_%s.dat",centstring);
  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<18; i++)
    {
      fin1>>ptpion[i]>>yieldpionpos[i]>>eyieldpionpos[i];
      fin2>>ptpion[i]>>yieldpionneg[i]>>eyieldpionneg[i];
    }
  fin1.close();  
  fin2.close();
  sprintf(fin1name,"ppg030/posproton_%s.dat",centstring);
  sprintf(fin2name,"ppg030/negproton_%s.dat",centstring);
  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<17; i++)
    {
      fin1>>ptproton[i]>>yieldprotonpos[i]>>eyieldprotonpos[i];
      fin2>>ptproton[i]>>yieldprotonneg[i]>>eyieldprotonneg[i];
    }
  fin1.close();  
  fin2.close();

  for(int i=0; i<15; i++)
    {
      //positive ratio
      A = yieldprotonpos[i];
      dA = eyieldprotonpos[i];
      B = yieldpionpos[i+3];
      dB = eyieldpionpos[i+3];
      newratiopos[i] = A/B;
      enewratiopos[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
      //cout<<"A = "<<A<<" dA = "<<dA<<" B = "<<B<<" dB = "<<dB<<endl;
      //cout<<"ptproton is "<<ptproton[i]<<endl;
      //cout<<"ptpion is "<<ptpion[i+3]<<endl;
      //negative ratio
      A = yieldprotonneg[i];
      dA = eyieldprotonneg[i];
      B = yieldpionneg[i+3];
      dB = eyieldpionneg[i+3];
      newrationeg[i] = A/B;
      enewrationeg[i] = (A/B)*sqrt((dA/A)**2+(dB/B)**2);
    }

  TGraphErrors *tposppg = new TGraphErrors(15,ptproton,newratiopos,eptproton,enewratiopos);
  tposppg->SetMarkerStyle(25);
  tposppg->SetMarkerColor(2);

  TGraphErrors *tnegppg = new TGraphErrors(15,ptproton,newrationeg,eptproton,enewrationeg);
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
  //tmg2->SetMaximum(1.4);
  tmg2->SetMaximum(ymax); // 1.4 is fine but this is for comparisons...
  tmg2->SetMinimum(ymin);
  tmg2->GetXaxis()->SetLimits(xmin,xmax);
  tmg2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg2->GetXaxis()->CenterTitle();
  tmg2->GetYaxis()->SetTitle("p/#pi ratio");
  tmg2->GetYaxis()->CenterTitle();

  TLegend *leg2 = new TLegend(0.68,0.68,0.88,0.88);
  leg2->SetFillColor(kWhite);
  leg2->SetBorderSize(0);
  leg2->AddEntry(tge_pos,"p/#pi^{+}","p");
  leg2->AddEntry(tge_neg,"#bar{p}/#pi^{-}","p");
  leg2->AddEntry(tposppg,"p/#pi^{+} Run2","p");
  leg2->AddEntry(tnegppg,"#bar{p}/#pi^{-} Run2","p");
  leg2->Draw();

  tpt_coll->Draw();
  tpt_cent->Draw();

  sprintf(figname,"regular/ppi_ppg_%d%d_cent%s.gif",pionid,protonid,centstring);
  c1->Print(figname);
  sprintf(figname,"regular/ppi_ppg_%d%d_cent%s.eps",pionid,protonid,centstring);
  c1->Print(figname);







  c1->Clear();
  //c1->Delete();
  delete c1;


}








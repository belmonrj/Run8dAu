void rda()
{

  // doit_file();
  // return;

  for(int i=0; i<5; i++)
    {
      doit_file(i,0,4);
      doit_file(i,1,5);
    }

}


void doit_file(int centid=0, int pionid=0, int protonid=6)
{

  // note that bias factors are already applied for invariant yield data files
  float Ncoll[5] = {7.590,15.061,10.248,6.579,3.198};
  float cross = 42; // 42mb is p+p total inelastic cross section at 200 GeV

  float ymin = 0.0;
  float xmin = 0.0;
  float ymax = 3.0;
  float xmax = 6.0;

  //float epscale = 1.18; // same pbarp...

  TLine *line = new TLine(xmin,1.0,xmax,1.0);

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

  float pt[50], ept[50];
  float tmp;

  float pionpt[30], epionpt[30];
  float pionpos[30], epionpos[30];
  float pionneg[30], epionneg[30];

  // --------------- //
  // --- pionpos --- //
  // --------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",pionid,centstring);
  fin.open(filename);
  for(int i=0; i<30; i++)
    {
      fin>>pionpt[i]>>pionpos[i]>>epionpos[i];
      if((float)pionpt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
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
      fin>>pionpt[i]>>pionneg[i]>>epionneg[i];
      if((float)pionpt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
    }
  fin.close();


  float protonpt[50], epionpt[50];
  float protonpos[50], eprotonpos[50];
  float protonneg[50], eprotonneg[50];

  // ----------------- //
  // --- protonpos --- //
  // ----------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",protonid,centstring);
  fin.open(filename);
  for(int i=0; i<50; i++)
    {
      fin>>protonpt[i]>>protonpos[i]>>eprotonpos[i];
      if((float)protonpt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
      // if(protonid==8&&protonpt[i]>3.0) // THIS IS NEW
      // 	{
      // 	  protonpos[i] *= epscale;
      // 	  eprotonpos[i] *= epscale;
      // 	}
    }
  fin.close();

  // ----------------- //
  // --- protonneg --- //
  // ----------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",protonid,centstring);
  fin.open(filename);
  for(int i=0; i<50; i++)
    {
      fin>>protonpt[i]>>protonneg[i]>>eprotonneg[i];
      if((float)protonpt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
    }
  fin.close();








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



  ifstream fin1;
  ifstream fin2;
  char fin1name[100];
  char fin2name[100];
  sprintf(fin1name,"ppg101/pospion.dat");
  sprintf(fin2name,"ppg101/negpion.dat");
  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<27; i++)
    {
      fin1>>ptpion[i]>>yieldpionpos[i]>>eyieldpionpos[i]>>tmp>>tmp>>tmp>>tmp;
      fin2>>ptpion[i]>>yieldpionneg[i]>>eyieldpionneg[i]>>tmp>>tmp>>tmp>>tmp;
    }
  fin1.close();  
  fin2.close();
  sprintf(fin1name,"ppg101/posproton.dat");
  sprintf(fin2name,"ppg101/negproton.dat");
  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<33; i++)
    {
      fin1>>ptproton[i]>>yieldprotonpos[i]>>eyieldprotonpos[i]>>tmp>>tmp>>tmp>>tmp;
      fin2>>ptproton[i]>>yieldprotonneg[i]>>eyieldprotonneg[i]>>tmp>>tmp>>tmp>>tmp;
    }
  fin1.close();  
  fin2.close();



  float pospionrda[27],epospionrda[27],esyspospionrda[27];
  float negpionrda[27],enegpionrda[27],esysnegpionrda[27];
  sprintf(filename,"regular/rda_%d_cent%s.txt",pionid,centstring);
  ofstream ftxt(filename);
  sprintf(filename,"regular/rda_%d_cent%s.tex",pionid,centstring);
  ofstream ftex(filename);
  for(int i=0; i<27; i++)
    {
      // float pt = float(i)/10.0+0.35;
      // if(pionpt[i+3]!=pt) {break;}
      // if(ptpion[i]!=pt) {break;}
      if(ptpion[i]!=pionpt[i+3])
	{
	  cout<<"AAAAAAAAHHH "<<i<<endl;
	  cout<<ptpion[i]<<endl;
	  cout<<pionpt[i+3]<<endl;
	}
      pospionrda[i] = pionpos[i+3]/yieldpionpos[i];
      epospionrda[i] = pospionrda[i]*sqrt((epionpos[i+3]/pionpos[i+3])**2+(eyieldpionpos[i]/yieldpionpos[i])**2);
      negpionrda[i] = pionneg[i+3]/yieldpionneg[i];
      enegpionrda[i] = negpionrda[i]*sqrt((epionneg[i+3]/pionneg[i+3])**2+(eyieldpionneg[i]/yieldpionneg[i])**2);
      pospionrda[i] /= Ncoll[centid];
      epospionrda[i] /= Ncoll[centid];
      negpionrda[i] /= Ncoll[centid];
      enegpionrda[i] /= Ncoll[centid];
      pospionrda[i] *= cross;
      epospionrda[i] *= cross;
      negpionrda[i] *= cross;
      enegpionrda[i] *= cross;
      esyspospionrda[i] = pospionrda[i]*0.1;
      esysnegpionrda[i] = negpionrda[i]*0.1;
      if(i<2) // remove low pT points...
	{
	  pospionrda[i] = -9;
	  negpionrda[i] = -9;
	  epospionrda[i] = 0;
	  enegpionrda[i] = 0;
	}
      ftxt<<ptpion[i]<<"\t"<<pospionrda[i]<<"\t"<<epospionrda[i]<<"\t"<<negpionrda[i]<<"\t"<<enegpionrda[i]<<endl;
      ftex<<ptpion[i]<<" & "<<pospionrda[i]<<" & "<<epospionrda[i]<<" & "<<negpionrda[i]<<" & "<<enegpionrda[i]<<" \\\\ "<<endl;
    }
  TGraphErrors *tge_pospionrda = new TGraphErrors(27,ptpion,pospionrda,eptpion,epospionrda);
  tge_pospionrda->SetMarkerColor(kRed);
  tge_pospionrda->SetMarkerStyle(kOpenCircle);
  TGraphErrors *tge_negpionrda = new TGraphErrors(27,ptpion,negpionrda,eptpion,enegpionrda);
  tge_negpionrda->SetMarkerColor(kBlue);
  tge_negpionrda->SetMarkerStyle(kOpenCircle);
  TGraphErrors *tge_syspospionrda = new TGraphErrors(27,ptpion,pospionrda,eptpion,esyspospionrda);
  TGraphErrors *tge_sysnegpionrda = new TGraphErrors(27,ptpion,negpionrda,eptpion,esysnegpionrda);




  float A, dA, B, dB;
  float posprotonrda[33],eposprotonrda[33],esysposprotonrda[33];
  float negprotonrda[33],enegprotonrda[33],esysnegprotonrda[33];
  sprintf(filename,"regular/rda_%d_cent%s.txt",protonid,centstring);
  ofstream ftxt(filename);
  sprintf(filename,"regular/rda_%d_cent%s.tex",protonid,centstring);
  ofstream ftex(filename);
  for(int i=0; i<33; i++)
    {
      // float pt = float(i)/10.0+0.35;
      // if(protonpt[i+3]!=pt) {break;}
      // if(ptproton[i]!=pt) {break;}
      if(ptproton[i]!=protonpt[i+5]&&i<25)
	{
	  cout<<"AAAAAAAAHHH "<<i<<endl;
	  cout<<ptproton[i]<<endl;
	  cout<<protonpt[i+5]<<endl;
	}
      if(i<25)
	{
	  posprotonrda[i] = protonpos[i+5]/yieldprotonpos[i];
	  eposprotonrda[i] = posprotonrda[i]*sqrt((eprotonpos[i+5]/protonpos[i+5])**2+(eyieldprotonpos[i]/yieldprotonpos[i])**2);
	  negprotonrda[i] = protonneg[i+5]/yieldprotonneg[i];
	  enegprotonrda[i] = negprotonrda[i]*sqrt((eprotonneg[i+5]/protonneg[i+5])**2+(eyieldprotonneg[i]/yieldprotonneg[i])**2);
	  //cout<<eprotonpos[i+5]/protonpos[i+5]<<" "<<eyieldprotonpos[i]/yieldprotonpos[i]<<endl;
	}
      else
	{
	  float pta = ((protonpt[i*2-20]+protonpt[i*2-19])/2.0);
	  float ptb = ptproton[i];
	  //cout<<"pta is "<<pta<<" and ptb is "<<ptb<<endl;
	  A = ((protonpos[i*2-20]+protonpos[i*2-19])/2.0);
	  dA = (sqrt(eprotonpos[i*2-20]**2+eprotonpos[i*2-19]**2)/2.0);
	  B = yieldprotonpos[i];
	  dB = eyieldprotonpos[i];
	  posprotonrda[i] = A/B;
	  eposprotonrda[i] = posprotonrda[i]*sqrt((dA/A)**2+(dB/B)**2);
	  A = ((protonneg[i*2-20]+protonneg[i*2-19])/2.0);
	  dA = (sqrt(eprotonneg[i*2-20]**2+eprotonneg[i*2-19]**2)/2.0);
	  B = yieldprotonneg[i];
	  dB = eyieldprotonneg[i];
	  //cout<<dA/A<<" "<<dB/B<<endl; // NOTICE!
	  negprotonrda[i] = A/B;
	  enegprotonrda[i] = negprotonrda[i]*sqrt((dA/A)**2+(dB/B)**2);
	}
      posprotonrda[i] /= Ncoll[centid];
      eposprotonrda[i] /= Ncoll[centid];
      negprotonrda[i] /= Ncoll[centid];
      enegprotonrda[i] /= Ncoll[centid];
      posprotonrda[i] *= cross;
      eposprotonrda[i] *= cross;
      negprotonrda[i] *= cross;
      enegprotonrda[i] *= cross;
      esysposprotonrda[i] = posprotonrda[i]*0.1;
      esysnegprotonrda[i] = negprotonrda[i]*0.1;
      ftxt<<ptproton[i]<<"\t"<<posprotonrda[i]<<"\t"<<eposprotonrda[i]<<"\t"<<negprotonrda[i]<<"\t"<<enegprotonrda[i]<<endl;
      ftex<<ptproton[i]<<" & "<<posprotonrda[i]<<" & "<<eposprotonrda[i]<<" & "<<negprotonrda[i]<<" & "<<enegprotonrda[i]<<" \\\\ "<<endl;
    }
  TGraphErrors *tge_posprotonrda = new TGraphErrors(33,ptproton,posprotonrda,eptproton,eposprotonrda);
  tge_posprotonrda->SetMarkerColor(kRed);
  tge_posprotonrda->SetMarkerStyle(kOpenSquare);
  TGraphErrors *tge_negprotonrda = new TGraphErrors(33,ptproton,negprotonrda,eptproton,enegprotonrda);
  tge_negprotonrda->SetMarkerColor(kBlue);
  tge_negprotonrda->SetMarkerStyle(kOpenSquare);
  TGraphErrors *tge_sysposprotonrda = new TGraphErrors(33,ptproton,posprotonrda,eptproton,esysposprotonrda);
  TGraphErrors *tge_sysnegprotonrda = new TGraphErrors(33,ptproton,negprotonrda,eptproton,esysnegprotonrda);








  tge_syspospionrda->SetMarkerColor(kRed-10);
  tge_syspospionrda->SetMarkerStyle(1);
  tge_syspospionrda->SetLineColor(kRed-10);
  tge_syspospionrda->SetLineWidth(15);
  tge_sysnegpionrda->SetMarkerColor(kBlue-10);
  tge_sysnegpionrda->SetMarkerStyle(1);
  tge_sysnegpionrda->SetLineColor(kBlue-10);
  tge_sysnegpionrda->SetLineWidth(15);

  tge_sysposprotonrda->SetMarkerColor(kRed-10);
  tge_sysposprotonrda->SetMarkerStyle(1);
  tge_sysposprotonrda->SetLineColor(kRed-10);
  tge_sysposprotonrda->SetLineWidth(15);
  tge_sysnegprotonrda->SetMarkerColor(kBlue-10);
  tge_sysnegprotonrda->SetMarkerStyle(1);
  tge_sysnegprotonrda->SetLineColor(kBlue-10);
  tge_sysnegprotonrda->SetLineWidth(15);










  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tge_syspospionrda);
  tmg->Add(tge_sysnegpionrda);
  tmg->Add(tge_sysposprotonrda);
  tmg->Add(tge_sysnegprotonrda);
  tmg->Add(tge_pospionrda);
  tmg->Add(tge_negpionrda);
  tmg->Add(tge_posprotonrda);
  tmg->Add(tge_negprotonrda);
  tmg->Draw("apz");
  line->Draw();
  tmg->SetMaximum(ymax);
  tmg->SetMinimum(ymin);
  tmg->GetXaxis()->SetLimits(xmin,xmax);
  tmg->GetYaxis()->SetTitle("R_{dA}");
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetYaxis()->CenterTitle();
  tmg->GetXaxis()->CenterTitle();

  TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->AddEntry(tge_pospionrda,"#pi^{+}","p");
  leg->AddEntry(tge_negpionrda,"#pi^{-}","p");
  leg->AddEntry(tge_posprotonrda,"p","p");
  leg->AddEntry(tge_negprotonrda,"#bar{p}","p");
  leg->Draw();

  //TPaveText *tpt_coll = new TPaveText(xmin+0.5,ymax+0.01,xmax-0.5,ymax+0.16);
  TPaveText *tpt_coll = new TPaveText(xmin+0.5,ymax*1.01,xmax-0.5,ymax*1.1);
  tpt_coll->SetFillColor(kWhite);
  tpt_coll->SetBorderSize(0);
  tpt_coll->AddText("d+Au  #sqrt{s_{NN}} = 200 GeV");
  tpt_coll->Draw();

  //TPaveText *tpt_cent = new TPaveText(xmin+0.25,ymax-0.4,xmin+1.5,ymax-0.2);
  TPaveText *tpt_cent = new TPaveText(xmax*0.05,ymax*0.82,xmax*0.3,ymax*0.95);
  tpt_cent->SetFillColor(kWhite);
  tpt_cent->SetBorderSize(0);
  tpt_cent->AddText(bigcentstring);
  tpt_cent->Draw();





  char figname[100];
  sprintf(figname,"regular/rda_%d%d_cent%s.gif",pionid,protonid,centstring);
  c1->Print(figname);
  sprintf(figname,"regular/rda_%d%d_cent%s.eps",pionid,protonid,centstring);
  c1->Print(figname);


  c1->Clear();
  delete c1;


}

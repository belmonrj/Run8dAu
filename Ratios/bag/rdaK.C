void rdaK()
{

  // doit_file();
  // return;

  for(int i=0; i<5; i++)
    {
      doit_file(i,0,2);
      doit_file(i,1,3);
    }

}


void doit_file(int centid=0, int pionid=0, int kaonid=6)
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


  float kaonpt[50], epionpt[50];
  float kaonpos[50], ekaonpos[50];
  float kaonneg[50], ekaonneg[50];

  // ----------------- //
  // --- kaonpos --- //
  // ----------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_pos_%d_dis_cent%s.dat",kaonid,centstring);
  fin.open(filename);
  for(int i=0; i<50; i++)
    {
      fin>>kaonpt[i]>>kaonpos[i]>>ekaonpos[i];
      if((float)kaonpt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
      // if(kaonid==8&&kaonpt[i]>3.0) // THIS IS NEW
      // 	{
      // 	  kaonpos[i] *= epscale;
      // 	  ekaonpos[i] *= epscale;
      // 	}
    }
  fin.close();

  // ----------------- //
  // --- kaonneg --- //
  // ----------------- //
  sprintf(filename,"FinalFeed/ptpid_tofw_neg_%d_dis_cent%s.dat",kaonid,centstring);
  fin.open(filename);
  for(int i=0; i<50; i++)
    {
      fin>>kaonpt[i]>>kaonneg[i]>>ekaonneg[i];
      if((float)kaonpt[i]!=float(float(i)/10.0+0.05)&&i>0) // they're the same but this evaluates as false
	{
	  cout<<"you gonna die"<<endl;
	  cout<<"pt is "<<pt[i]<<" but pt is "<<i/10.0+0.05<<endl;
	}
    }
  fin.close();








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
  sprintf(fin1name,"ppg101/poskaon.dat");
  sprintf(fin2name,"ppg101/negkaon.dat");
  fin1.open(fin1name);
  fin2.open(fin2name);
  for(int i=0; i<16; i++)
    {
      fin1>>ptkaon[i]>>yieldkaonpos[i]>>eyieldkaonpos[i]>>tmp>>tmp>>tmp>>tmp;
      fin2>>ptkaon[i]>>yieldkaonneg[i]>>eyieldkaonneg[i]>>tmp>>tmp>>tmp>>tmp;
    }
  fin1.close();  
  fin2.close();



  float pospionrda[27],epospionrda[27],esyspospionrda[27];
  float negpionrda[27],enegpionrda[27],esysnegpionrda[27];
  // sprintf(filename,"regular/rda_%d_cent%s.txt",pionid,centstring);
  // ofstream ftxt(filename);
  // sprintf(filename,"regular/rda_%d_cent%s.tex",pionid,centstring);
  // ofstream ftex(filename);
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
      //if(i<5) // remove low pT points...
	{
	  pospionrda[i] = -9;
	  negpionrda[i] = -9;
	  epospionrda[i] = 0;
	  enegpionrda[i] = 0;
	}
      // ftxt<<ptpion[i]<<"\t"<<pospionrda[i]<<"\t"<<epospionrda[i]<<"\t"<<negpionrda[i]<<"\t"<<enegpionrda[i]<<endl;
      // ftex<<ptpion[i]<<" & "<<pospionrda[i]<<" & "<<epospionrda[i]<<" & "<<negpionrda[i]<<" & "<<enegpionrda[i]<<" \\\\ "<<endl;
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
  float poskaonrda[33],eposkaonrda[33],esysposkaonrda[33];
  float negkaonrda[33],enegkaonrda[33],esysnegkaonrda[33];
  sprintf(filename,"regular/rda_%d_cent%s.txt",kaonid,centstring);
  ofstream ftxt(filename);
  sprintf(filename,"regular/rda_%d_cent%s.tex",kaonid,centstring);
  ofstream ftex(filename);
  for(int i=0; i<16; i++)
    {
      // float pt = float(i)/10.0+0.35;
      // if(kaonpt[i+3]!=pt) {break;}
      // if(ptkaon[i]!=pt) {break;}
      if(ptkaon[i]!=kaonpt[i+4])
	{
	  cout<<"AAAAAAAAHHH "<<i<<endl;
	  cout<<ptkaon[i]<<endl;
	  cout<<kaonpt[i+4]<<endl;
	}
      poskaonrda[i] = kaonpos[i+4]/yieldkaonpos[i];
      eposkaonrda[i] = poskaonrda[i]*sqrt((ekaonpos[i+4]/kaonpos[i+4])**2+(eyieldkaonpos[i]/yieldkaonpos[i])**2);
      negkaonrda[i] = kaonneg[i+4]/yieldkaonneg[i];
      enegkaonrda[i] = negkaonrda[i]*sqrt((ekaonneg[i+4]/kaonneg[i+4])**2+(eyieldkaonneg[i]/yieldkaonneg[i])**2);
      if(i<1) // remove low pT points...
	{
	  poskaonrda[i] = -9;
	  negkaonrda[i] = -9;
	  eposkaonrda[i] = 0;
	  enegkaonrda[i] = 0;
	}
      //cout<<ekaonpos[i+4]/kaonpos[i+4]<<" "<<eyieldkaonpos[i]/yieldkaonpos[i]<<endl;
      poskaonrda[i] /= Ncoll[centid];
      eposkaonrda[i] /= Ncoll[centid];
      negkaonrda[i] /= Ncoll[centid];
      enegkaonrda[i] /= Ncoll[centid];
      poskaonrda[i] *= cross;
      eposkaonrda[i] *= cross;
      negkaonrda[i] *= cross;
      enegkaonrda[i] *= cross;
      esysposkaonrda[i] = poskaonrda[i]*0.1;
      esysnegkaonrda[i] = negkaonrda[i]*0.1;
      ftxt<<ptkaon[i]<<"\t"<<poskaonrda[i]<<"\t"<<eposkaonrda[i]<<"\t"<<negkaonrda[i]<<"\t"<<enegkaonrda[i]<<endl;
      ftex<<ptkaon[i]<<" & "<<poskaonrda[i]<<" & "<<eposkaonrda[i]<<" & "<<negkaonrda[i]<<" & "<<enegkaonrda[i]<<" \\\\ "<<endl;
    }
  TGraphErrors *tge_poskaonrda = new TGraphErrors(16,ptkaon,poskaonrda,eptkaon,eposkaonrda);
  tge_poskaonrda->SetMarkerColor(kRed);
  tge_poskaonrda->SetMarkerStyle(kOpenSquare);
  TGraphErrors *tge_negkaonrda = new TGraphErrors(16,ptkaon,negkaonrda,eptkaon,enegkaonrda);
  tge_negkaonrda->SetMarkerColor(kBlue);
  tge_negkaonrda->SetMarkerStyle(kOpenSquare);
  TGraphErrors *tge_sysposkaonrda = new TGraphErrors(33,ptkaon,poskaonrda,eptkaon,esysposkaonrda);
  TGraphErrors *tge_sysnegkaonrda = new TGraphErrors(33,ptkaon,negkaonrda,eptkaon,esysnegkaonrda);








  tge_syspospionrda->SetMarkerColor(kRed-10);
  tge_syspospionrda->SetMarkerStyle(1);
  tge_syspospionrda->SetLineColor(kRed-10);
  tge_syspospionrda->SetLineWidth(15);
  tge_sysnegpionrda->SetMarkerColor(kBlue-10);
  tge_sysnegpionrda->SetMarkerStyle(1);
  tge_sysnegpionrda->SetLineColor(kBlue-10);
  tge_sysnegpionrda->SetLineWidth(15);

  tge_sysposkaonrda->SetMarkerColor(kRed-10);
  tge_sysposkaonrda->SetMarkerStyle(1);
  tge_sysposkaonrda->SetLineColor(kRed-10);
  tge_sysposkaonrda->SetLineWidth(15);
  tge_sysnegkaonrda->SetMarkerColor(kBlue-10);
  tge_sysnegkaonrda->SetMarkerStyle(1);
  tge_sysnegkaonrda->SetLineColor(kBlue-10);
  tge_sysnegkaonrda->SetLineWidth(15);










  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tge_syspospionrda);
  tmg->Add(tge_sysnegpionrda);
  tmg->Add(tge_sysposkaonrda);
  tmg->Add(tge_sysnegkaonrda);
  tmg->Add(tge_pospionrda);
  tmg->Add(tge_negpionrda);
  tmg->Add(tge_poskaonrda);
  tmg->Add(tge_negkaonrda);
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
  leg->AddEntry(tge_poskaonrda,"p","p");
  leg->AddEntry(tge_negkaonrda,"#bar{p}","p");
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
  sprintf(figname,"regular/rda_%d%d_cent%s.gif",pionid,kaonid,centstring);
  c1->Print(figname);
  sprintf(figname,"regular/rda_%d%d_cent%s.eps",pionid,kaonid,centstring);
  c1->Print(figname);


  c1->Clear();
  delete c1;


}

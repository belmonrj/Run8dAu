void add()
{

  //doit();

  //exit(0);

  for(int ipid=0; ipid<3; ipid++)
    {
      doit(ipid,0);
    }

}



void doit(int ipid=0, int centid=0)
{

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetBorderMode(0);
  c1->SetFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->SetFrameFillColor(kWhite);

  TLine *line = new TLine(0.0,0.0,6.0,0.0);

  TF1 *fun = new TF1("fun","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,6.0);

  char pidstring[5];
  sprintf(pidstring,"pion"); // "default"
  if(ipid==0) sprintf(pidstring,"pion");
  if(ipid==1) sprintf(pidstring,"kaon");
  if(ipid==2) sprintf(pidstring,"prot");

  // char centstring[5];
  // if(centid==0) sprintf(centstring,"0010");
  // else if(centid==1) sprintf(centstring,"1020");
  // else if(centid==2) sprintf(centstring,"2040");
  // else if(centid==3) sprintf(centstring,"4060");
  // else if(centid==4) sprintf(centstring,"6092");
  // else {cout<<"you gonna die"<<endl; return;}

  char centstring[10];
  if(centid==0) sprintf(centstring,"cent0010");
  else if(centid==1) sprintf(centstring,"cent1020");
  else if(centid==2) sprintf(centstring,"cent2040");
  else if(centid==3) sprintf(centstring,"cent4060");
  else if(centid==4) sprintf(centstring,"cent6092");
  else {cout<<"you gonna die"<<endl; return;}



  char fnameinpossys_1a[100];
  char fnameinnegsys_1a[100];
  sprintf(fnameinpossys_1a,"Text/single_suncert_%s_pos_dcfcA.dat",pidstring);
  sprintf(fnameinnegsys_1a,"Text/single_suncert_%s_neg_dcfcA.dat",pidstring);
  ifstream finpossys_1a;
  ifstream finnegsys_1a;
  finpossys_1a.open(fnameinpossys_1a);
  finnegsys_1a.open(fnameinnegsys_1a);

  char fnameinpossys_2a[100];
  char fnameinnegsys_2a[100];
  sprintf(fnameinpossys_2a,"Text/single_suncert_%s_pos_dzedA.dat",pidstring);
  sprintf(fnameinnegsys_2a,"Text/single_suncert_%s_neg_dzedA.dat",pidstring);
  ifstream finpossys_2a;
  ifstream finnegsys_2a;
  finpossys_2a.open(fnameinpossys_2a);
  finnegsys_2a.open(fnameinnegsys_2a);

  char fnameinpossys_3a[100];
  char fnameinnegsys_3a[100];
  sprintf(fnameinpossys_3a,"Text/single_suncert_%s_pos_pc3mA.dat",pidstring);
  sprintf(fnameinnegsys_3a,"Text/single_suncert_%s_neg_pc3mA.dat",pidstring);
  ifstream finpossys_3a;
  ifstream finnegsys_3a;
  finpossys_3a.open(fnameinpossys_3a);
  finnegsys_3a.open(fnameinnegsys_3a);

  char fnameinpossys_4a[100];
  char fnameinnegsys_4a[100];
  sprintf(fnameinpossys_4a,"Text/single_suncert_%s_pos_tfwmA.dat",pidstring);
  sprintf(fnameinnegsys_4a,"Text/single_suncert_%s_neg_tfwmA.dat",pidstring);
  ifstream finpossys_4a;
  ifstream finnegsys_4a;
  finpossys_4a.open(fnameinpossys_4a);
  finnegsys_4a.open(fnameinnegsys_4a);

  char fnameinpossys_5a[100];
  char fnameinnegsys_5a[100];
  sprintf(fnameinpossys_5a,"Text/single_suncert_%s_pos_pc1fA.dat",pidstring);
  sprintf(fnameinnegsys_5a,"Text/single_suncert_%s_neg_pc1fA.dat",pidstring);
  ifstream finpossys_5a;
  ifstream finnegsys_5a;
  finpossys_5a.open(fnameinpossys_5a);
  finnegsys_5a.open(fnameinnegsys_5a);

  char fnameinpossys_6a[100];
  char fnameinnegsys_6a[100];
  sprintf(fnameinpossys_6a,"Text/single_suncert_%s_pos_pc3fA.dat",pidstring);
  sprintf(fnameinnegsys_6a,"Text/single_suncert_%s_neg_pc3fA.dat",pidstring);
  ifstream finpossys_6a;
  ifstream finnegsys_6a;
  finpossys_6a.open(fnameinpossys_6a);
  finnegsys_6a.open(fnameinnegsys_6a);

  char fnameinpossys_7a[100];
  char fnameinnegsys_7a[100];
  sprintf(fnameinpossys_7a,"Text/single_suncert_%s_pos_spidA.dat",pidstring);
  sprintf(fnameinnegsys_7a,"Text/single_suncert_%s_neg_spidA.dat",pidstring);
  ifstream finpossys_7a;
  ifstream finnegsys_7a;
  finpossys_7a.open(fnameinpossys_7a);
  finnegsys_7a.open(fnameinnegsys_7a);

  char fnameinpossys_1b[100];
  char fnameinnegsys_1b[100];
  sprintf(fnameinpossys_1b,"Text/single_suncert_%s_pos_dcfcB.dat",pidstring);
  sprintf(fnameinnegsys_1b,"Text/single_suncert_%s_neg_dcfcB.dat",pidstring);
  ifstream finpossys_1b;
  ifstream finnegsys_1b;
  finpossys_1b.open(fnameinpossys_1b);
  finnegsys_1b.open(fnameinnegsys_1b);

  char fnameinpossys_7b[100];
  char fnameinnegsys_7b[100];
  sprintf(fnameinpossys_7b,"Text/single_suncert_%s_pos_spidB.dat",pidstring);
  sprintf(fnameinnegsys_7b,"Text/single_suncert_%s_neg_spidB.dat",pidstring);
  ifstream finpossys_7b;
  ifstream finnegsys_7b;
  finpossys_7b.open(fnameinpossys_7b);
  finnegsys_7b.open(fnameinnegsys_7b);

  float pt_pos_1a[100],pt_pos_2a[100],pt_pos_3a[100],pt_pos_4a[100],pt_pos_5a[100],pt_pos_6a[100],pt_pos_7a[100],pt_pos_1b[100],pt_pos_7b[100];
  float un_pos_1a[100],un_pos_2a[100],un_pos_3a[100],un_pos_4a[100],un_pos_5a[100],un_pos_6a[100],un_pos_7a[100],un_pos_1b[100],un_pos_7b[100];
  float er_pos_1a[100],er_pos_2a[100],er_pos_3a[100],er_pos_4a[100],er_pos_5a[100],er_pos_6a[100],er_pos_7a[100],er_pos_1b[100],er_pos_7b[100];
  float pt_neg_1a[100],pt_neg_2a[100],pt_neg_3a[100],pt_neg_4a[100],pt_neg_5a[100],pt_neg_6a[100],pt_neg_7a[100],pt_neg_1b[100],pt_neg_7b[100];
  float un_neg_1a[100],un_neg_2a[100],un_neg_3a[100],un_neg_4a[100],un_neg_5a[100],un_neg_6a[100],un_neg_7a[100],un_neg_1b[100],un_neg_7b[100];
  float er_neg_1a[100],er_neg_2a[100],er_neg_3a[100],er_neg_4a[100],er_neg_5a[100],er_neg_6a[100],er_neg_7a[100],er_neg_1b[100],er_neg_7b[100];
  float ept[100]={0};



  for(int i=0; i<100; i++)
    {

      finpossys_1a>>pt_pos_1a[i]>>un_pos_1a[i]>>er_pos_1a[i];
      finpossys_2a>>pt_pos_2a[i]>>un_pos_2a[i]>>er_pos_2a[i];
      finpossys_3a>>pt_pos_3a[i]>>un_pos_3a[i]>>er_pos_3a[i];
      finpossys_4a>>pt_pos_4a[i]>>un_pos_4a[i]>>er_pos_4a[i];
      finpossys_5a>>pt_pos_5a[i]>>un_pos_5a[i]>>er_pos_5a[i];
      finpossys_6a>>pt_pos_6a[i]>>un_pos_6a[i]>>er_pos_6a[i];
      finpossys_7a>>pt_pos_7a[i]>>un_pos_7a[i]>>er_pos_7a[i];
      finpossys_1b>>pt_pos_1b[i]>>un_pos_1b[i]>>er_pos_1b[i];
      finpossys_7b>>pt_pos_7b[i]>>un_pos_7b[i]>>er_pos_7b[i];

      finnegsys_1a>>pt_neg_1a[i]>>un_neg_1a[i]>>er_neg_1a[i];
      finnegsys_2a>>pt_neg_2a[i]>>un_neg_2a[i]>>er_neg_2a[i];
      finnegsys_3a>>pt_neg_3a[i]>>un_neg_3a[i]>>er_neg_3a[i];
      finnegsys_4a>>pt_neg_4a[i]>>un_neg_4a[i]>>er_neg_4a[i];
      finnegsys_5a>>pt_neg_5a[i]>>un_neg_5a[i]>>er_neg_5a[i];
      finnegsys_6a>>pt_neg_6a[i]>>un_neg_6a[i]>>er_neg_6a[i];
      finnegsys_7a>>pt_neg_7a[i]>>un_neg_7a[i]>>er_neg_7a[i];
      finnegsys_1b>>pt_neg_1b[i]>>un_neg_1b[i]>>er_neg_1b[i];
      finnegsys_7b>>pt_neg_7b[i]>>un_neg_7b[i]>>er_neg_7b[i];

    }



  finpossys_1a.close();
  finpossys_2a.close();
  finpossys_3a.close();
  finpossys_4a.close();
  finpossys_5a.close();
  finpossys_6a.close();
  finpossys_7a.close();
  finpossys_1b.close();
  finpossys_7b.close();

  finnegsys_1a.close();
  finnegsys_2a.close();
  finnegsys_3a.close();
  finnegsys_4a.close();
  finnegsys_5a.close();
  finnegsys_6a.close();
  finnegsys_7a.close();
  finnegsys_1b.close();
  finnegsys_7b.close();



  // ---
  // ---
  // ---

  float pt_pos_sumA[100];
  float un_pos_sumA[100];
  float er_pos_sumA[100];
  float pt_neg_sumA[100];
  float un_neg_sumA[100];
  float er_neg_sumA[100];

  for(int i=0; i<100; i++)
    {
      pt_pos_sumA[i] = pt_pos_1a[i]; // arbitrary, all same
      un_pos_sumA[i] = sqrt(
			    un_pos_1a[i]**2 + 
			    un_pos_2a[i]**2 + 
			    un_pos_3a[i]**2 + 
			    un_pos_4a[i]**2 + 
			    un_pos_5a[i]**2 + 
			    un_pos_6a[i]**2 + 
			    un_pos_7a[i]**2);
      er_pos_sumA[i] = sqrt(
			    er_pos_1a[i]**2 + 
			    er_pos_2a[i]**2 + 
			    er_pos_3a[i]**2 + 
			    er_pos_4a[i]**2 + 
			    er_pos_5a[i]**2 + 
			    er_pos_6a[i]**2 + 
			    er_pos_7a[i]**2)/7.0;

    }

  TGraphErrors *tge_sumA = new TGraphErrors(100,pt_pos_sumA,un_pos_sumA,ept,er_pos_sumA);
  tge_sumA->SetMarkerStyle(kFullCircle);
  tge_sumA->SetMarkerColor(kBlack);
  tge_sumA->Draw("ap");
  line->Draw("same");
  // tge_sumA->Fit(fun,"R");
  // if(ipid==1) tge_sumA->Fit(fun,"","",0.3,4.5);
  // if(ipid==2) tge_sumA->Fit(fun,"","",0.4,6.0);
  tge_sumA->SetMaximum(0.5);
  tge_sumA->SetMinimum(-0.1);
  tge_sumA->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumA->GetXaxis()->SetTitle("p_{T}");
  tge_sumA->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameA[100];
  sprintf(fignameA,"Added/sys_uncert_pos_%s_sumA.png",pidstring);
  c1->Print(fignameA);
  sprintf(fignameA,"Added/sys_uncert_pos_%s_sumA.eps",pidstring);
  c1->Print(fignameA);

  //continue; // TEMP

  float pt_pos_sumB[100];
  float un_pos_sumB[100];
  float er_pos_sumB[100];
  float pt_neg_sumB[100];
  float un_neg_sumB[100];
  float er_neg_sumB[100];

  for(int i=0; i<100; i++)
    {
      pt_pos_sumB[i] = pt_pos_1a[i]; // arbitrary, all same
      un_pos_sumB[i] = sqrt(
			    un_pos_1b[i]**2 + 
			    un_pos_2a[i]**2 + 
			    un_pos_3a[i]**2 + 
			    un_pos_4a[i]**2 + 
			    un_pos_5a[i]**2 + 
			    un_pos_6a[i]**2 + 
			    un_pos_7a[i]**2);
      er_pos_sumB[i] = sqrt(
			    er_pos_1b[i]**2 + 
			    er_pos_2a[i]**2 + 
			    er_pos_3a[i]**2 + 
			    er_pos_4a[i]**2 + 
			    er_pos_5a[i]**2 + 
			    er_pos_6a[i]**2 + 
			    er_pos_7a[i]**2)/7.0;

    }

  TGraphErrors *tge_sumB = new TGraphErrors(100,pt_pos_sumB,un_pos_sumB,ept,er_pos_sumB);
  tge_sumB->SetMarkerStyle(kFullCircle);
  tge_sumB->SetMarkerColor(kBlack);
  tge_sumB->Draw("ap");
  line->Draw("same");
  // tge_sumB->Fit(fun,"R");
  // if(ipid==1) tge_sumB->Fit(fun,"","",0.3,4.5);
  // if(ipid==2) tge_sumB->Fit(fun,"","",0.4,6.0);
  tge_sumB->SetMaximum(0.5);
  tge_sumB->SetMinimum(-0.1);
  tge_sumB->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumB->GetXaxis()->SetTitle("p_{T}");
  tge_sumB->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameB[100];
  sprintf(fignameB,"Added/sys_uncert_pos_%s_sumB.png",pidstring);
  c1->Print(fignameB);
  sprintf(fignameB,"Added/sys_uncert_pos_%s_sumB.eps",pidstring);
  c1->Print(fignameB);



  float pt_pos_sumAa[100];
  float un_pos_sumAa[100];
  float er_pos_sumAa[100];
  float pt_neg_sumAa[100];
  float un_neg_sumAa[100];
  float er_neg_sumAa[100];

  for(int i=0; i<100; i++)
    {
      pt_pos_sumAa[i] = pt_pos_1a[i]; // arbitrary, all same
      un_pos_sumAa[i] = sqrt(
			    un_pos_1a[i]**2 + 
			    un_pos_2a[i]**2 + 
			    un_pos_3a[i]**2 + 
			    un_pos_4a[i]**2 + 
			    un_pos_5a[i]**2 + 
			    un_pos_6a[i]**2 + 
			    un_pos_7a[i]**2 + 
			    un_pos_7b[i]**2);
      er_pos_sumAa[i] = sqrt(
			    er_pos_1a[i]**2 + 
			    er_pos_2a[i]**2 + 
			    er_pos_3a[i]**2 + 
			    er_pos_4a[i]**2 + 
			    er_pos_5a[i]**2 + 
			    er_pos_6a[i]**2 + 
			    er_pos_7a[i]**2 + 
			    er_pos_7b[i]**2)/7.0;

    }

  TGraphErrors *tge_sumAa = new TGraphErrors(100,pt_pos_sumAa,un_pos_sumAa,ept,er_pos_sumAa);
  tge_sumAa->SetMarkerStyle(kFullCircle);
  tge_sumAa->SetMarkerColor(kBlack);
  tge_sumAa->Draw("ap");
  line->Draw("same");
  // tge_sumAa->Fit(fun,"R");
  // if(ipid==1) tge_sumAa->Fit(fun,"","",0.3,4.0);
  // if(ipid==2) tge_sumAa->Fit(fun,"","",0.4,6.0);
  tge_sumAa->SetMaximum(0.5);
  tge_sumAa->SetMinimum(-0.1);
  tge_sumAa->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumAa->GetXaxis()->SetTitle("p_{T}");
  tge_sumAa->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameAa[100];
  sprintf(fignameAa,"Added/sys_uncert_pos_%s_sumAa.png",pidstring);
  c1->Print(fignameAa);
  sprintf(fignameAa,"Added/sys_uncert_pos_%s_sumAa.eps",pidstring);
  c1->Print(fignameAa);



  float pt_pos_sumBb[100];
  float un_pos_sumBb[100];
  float er_pos_sumBb[100];
  float pt_neg_sumBb[100];
  float un_neg_sumBb[100];
  float er_neg_sumBb[100];

  for(int i=0; i<100; i++)
    {
      pt_pos_sumBb[i] = pt_pos_1a[i]; // arbitrary, all same
      un_pos_sumBb[i] = sqrt(
			    un_pos_1b[i]**2 + 
			    un_pos_2a[i]**2 + 
			    un_pos_3a[i]**2 + 
			    un_pos_4a[i]**2 + 
			    un_pos_5a[i]**2 + 
			    un_pos_6a[i]**2 + 
			    un_pos_7a[i]**2 + 
			    un_pos_7b[i]**2);
      er_pos_sumBb[i] = sqrt(
			    er_pos_1b[i]**2 + 
			    er_pos_2a[i]**2 + 
			    er_pos_3a[i]**2 + 
			    er_pos_4a[i]**2 + 
			    er_pos_5a[i]**2 + 
			    er_pos_6a[i]**2 + 
			    er_pos_7a[i]**2 + 
			    er_pos_7b[i]**2)/7.0;

    }

  TGraphErrors *tge_sumBb = new TGraphErrors(100,pt_pos_sumBb,un_pos_sumBb,ept,er_pos_sumBb);
  tge_sumBb->SetMarkerStyle(kFullCircle);
  tge_sumBb->SetMarkerColor(kBlack);
  tge_sumBb->Draw("ap");
  line->Draw("same");
  // tge_sumBb->Fit(fun,"R");
  // if(ipid==1) tge_sumBb->Fit(fun,"","",0.3,4.0);
  // if(ipid==2) tge_sumBb->Fit(fun,"","",0.4,6.0);
  tge_sumBb->SetMaximum(0.5);
  tge_sumBb->SetMinimum(-0.1);
  tge_sumBb->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumBb->GetXaxis()->SetTitle("p_{T}");
  tge_sumBb->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameBb[100];
  sprintf(fignameBb,"Added/sys_uncert_pos_%s_sumBb.png",pidstring);
  c1->Print(fignameBb);
  sprintf(fignameBb,"Added/sys_uncert_pos_%s_sumBb.eps",pidstring);
  c1->Print(fignameBb);





  // ---
  // ---
  // ---

  float pt_neg_sumA[100];
  float un_neg_sumA[100];
  float er_neg_sumA[100];
  float pt_neg_sumA[100];
  float un_neg_sumA[100];
  float er_neg_sumA[100];

  for(int i=0; i<100; i++)
    {
      pt_neg_sumA[i] = pt_neg_1a[i]; // arbitrary, all same
      un_neg_sumA[i] = sqrt(
			    un_neg_1a[i]**2 + 
			    un_neg_2a[i]**2 + 
			    un_neg_3a[i]**2 + 
			    un_neg_4a[i]**2 + 
			    un_neg_5a[i]**2 + 
			    un_neg_6a[i]**2 + 
			    un_neg_7a[i]**2);
      er_neg_sumA[i] = sqrt(
			    er_neg_1a[i]**2 + 
			    er_neg_2a[i]**2 + 
			    er_neg_3a[i]**2 + 
			    er_neg_4a[i]**2 + 
			    er_neg_5a[i]**2 + 
			    er_neg_6a[i]**2 + 
			    er_neg_7a[i]**2)/7.0;

    }

  TGraphErrors *tge_sumA = new TGraphErrors(100,pt_neg_sumA,un_neg_sumA,ept,er_neg_sumA);
  tge_sumA->SetMarkerStyle(kFullCircle);
  tge_sumA->SetMarkerColor(kBlack);
  tge_sumA->Draw("ap");
  line->Draw("same");
  // tge_sumA->Fit(fun,"R");
  // if(ipid==1) tge_sumA->Fit(fun,"","",0.3,4.5);
  // if(ipid==2) tge_sumA->Fit(fun,"","",0.4,6.0);
  tge_sumA->SetMaximum(0.5);
  tge_sumA->SetMinimum(-0.1);
  tge_sumA->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumA->GetXaxis()->SetTitle("p_{T}");
  tge_sumA->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameA[100];
  sprintf(fignameA,"Added/sys_uncert_neg_%s_sumA.png",pidstring);
  c1->Print(fignameA);
  sprintf(fignameA,"Added/sys_uncert_neg_%s_sumA.eps",pidstring);
  c1->Print(fignameA);



  float pt_neg_sumB[100];
  float un_neg_sumB[100];
  float er_neg_sumB[100];
  float pt_neg_sumB[100];
  float un_neg_sumB[100];
  float er_neg_sumB[100];

  for(int i=0; i<100; i++)
    {
      pt_neg_sumB[i] = pt_neg_1a[i]; // arbitrary, all same
      un_neg_sumB[i] = sqrt(
			    un_neg_1b[i]**2 + 
			    un_neg_2a[i]**2 + 
			    un_neg_3a[i]**2 + 
			    un_neg_4a[i]**2 + 
			    un_neg_5a[i]**2 + 
			    un_neg_6a[i]**2 + 
			    un_neg_7a[i]**2);
      er_neg_sumB[i] = sqrt(
			    er_neg_1b[i]**2 + 
			    er_neg_2a[i]**2 + 
			    er_neg_3a[i]**2 + 
			    er_neg_4a[i]**2 + 
			    er_neg_5a[i]**2 + 
			    er_neg_6a[i]**2 + 
			    er_neg_7a[i]**2)/7.0;

    }

  TGraphErrors *tge_sumB = new TGraphErrors(100,pt_neg_sumB,un_neg_sumB,ept,er_neg_sumB);
  tge_sumB->SetMarkerStyle(kFullCircle);
  tge_sumB->SetMarkerColor(kBlack);
  tge_sumB->Draw("ap");
  line->Draw("same");
  // tge_sumB->Fit(fun,"R");
  // if(ipid==1) tge_sumB->Fit(fun,"","",0.3,4.5);
  // if(ipid==2) tge_sumB->Fit(fun,"","",0.4,6.0);
  tge_sumB->SetMaximum(0.5);
  tge_sumB->SetMinimum(-0.1);
  tge_sumB->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumB->GetXaxis()->SetTitle("p_{T}");
  tge_sumB->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameB[100];
  sprintf(fignameB,"Added/sys_uncert_neg_%s_sumB.png",pidstring);
  c1->Print(fignameB);
  sprintf(fignameB,"Added/sys_uncert_neg_%s_sumB.eps",pidstring);
  c1->Print(fignameB);



  float pt_neg_sumAa[100];
  float un_neg_sumAa[100];
  float er_neg_sumAa[100];
  float pt_neg_sumAa[100];
  float un_neg_sumAa[100];
  float er_neg_sumAa[100];

  for(int i=0; i<100; i++)
    {
      pt_neg_sumAa[i] = pt_neg_1a[i]; // arbitrary, all same
      un_neg_sumAa[i] = sqrt(
			    un_neg_1a[i]**2 + 
			    un_neg_2a[i]**2 + 
			    un_neg_3a[i]**2 + 
			    un_neg_4a[i]**2 + 
			    un_neg_5a[i]**2 + 
			    un_neg_6a[i]**2 + 
			    un_neg_7a[i]**2 + 
			    un_neg_7b[i]**2);
      er_neg_sumAa[i] = sqrt(
			    er_neg_1a[i]**2 + 
			    er_neg_2a[i]**2 + 
			    er_neg_3a[i]**2 + 
			    er_neg_4a[i]**2 + 
			    er_neg_5a[i]**2 + 
			    er_neg_6a[i]**2 + 
			    er_neg_7a[i]**2 + 
			    er_neg_7b[i]**2)/7.0;

    }

  TGraphErrors *tge_sumAa = new TGraphErrors(100,pt_neg_sumAa,un_neg_sumAa,ept,er_neg_sumAa);
  tge_sumAa->SetMarkerStyle(kFullCircle);
  tge_sumAa->SetMarkerColor(kBlack);
  tge_sumAa->Draw("ap");
  line->Draw("same");
  // tge_sumAa->Fit(fun,"R");
  // if(ipid==1) tge_sumAa->Fit(fun,"","",0.3,4.0);
  // if(ipid==2) tge_sumAa->Fit(fun,"","",0.4,6.0);
  tge_sumAa->SetMaximum(0.5);
  tge_sumAa->SetMinimum(-0.1);
  tge_sumAa->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumAa->GetXaxis()->SetTitle("p_{T}");
  tge_sumAa->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameAa[100];
  sprintf(fignameAa,"Added/sys_uncert_neg_%s_sumAa.png",pidstring);
  c1->Print(fignameAa);
  sprintf(fignameAa,"Added/sys_uncert_neg_%s_sumAa.eps",pidstring);
  c1->Print(fignameAa);



  float pt_neg_sumBb[100];
  float un_neg_sumBb[100];
  float er_neg_sumBb[100];
  float pt_neg_sumBb[100];
  float un_neg_sumBb[100];
  float er_neg_sumBb[100];

  for(int i=0; i<100; i++)
    {
      pt_neg_sumBb[i] = pt_neg_1a[i]; // arbitrary, all same
      un_neg_sumBb[i] = sqrt(
			    un_neg_1b[i]**2 + 
			    un_neg_2a[i]**2 + 
			    un_neg_3a[i]**2 + 
			    un_neg_4a[i]**2 + 
			    un_neg_5a[i]**2 + 
			    un_neg_6a[i]**2 + 
			    un_neg_7a[i]**2 + 
			    un_neg_7b[i]**2);
      er_neg_sumBb[i] = sqrt(
			    er_neg_1b[i]**2 + 
			    er_neg_2a[i]**2 + 
			    er_neg_3a[i]**2 + 
			    er_neg_4a[i]**2 + 
			    er_neg_5a[i]**2 + 
			    er_neg_6a[i]**2 + 
			    er_neg_7a[i]**2 + 
			    er_neg_7b[i]**2)/7.0;

    }

  TGraphErrors *tge_sumBb = new TGraphErrors(100,pt_neg_sumBb,un_neg_sumBb,ept,er_neg_sumBb);
  tge_sumBb->SetMarkerStyle(kFullCircle);
  tge_sumBb->SetMarkerColor(kBlack);
  tge_sumBb->Draw("ap");
  line->Draw("same");
  // tge_sumBb->Fit(fun,"R");
  // if(ipid==1) tge_sumBb->Fit(fun,"","",0.3,4.0);
  // if(ipid==2) tge_sumBb->Fit(fun,"","",0.4,6.0);
  tge_sumBb->SetMaximum(0.5);
  tge_sumBb->SetMinimum(-0.1);
  tge_sumBb->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumBb->GetXaxis()->SetTitle("p_{T}");
  tge_sumBb->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameBb[100];
  sprintf(fignameBb,"Added/sys_uncert_neg_%s_sumBb.png",pidstring);
  c1->Print(fignameBb);
  sprintf(fignameBb,"Added/sys_uncert_neg_%s_sumBb.eps",pidstring);
  c1->Print(fignameBb);





}

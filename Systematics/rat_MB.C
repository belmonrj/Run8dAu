void rat_MB()
{

  int pion=0;
  int kaon=1;
  int prot=2;
  int neg=0;
  int pos=1;

  //int icent = -9;
  int icent = 0;

  control(pion,neg,icent,pion,pos,icent); // pipi
  control(kaon,neg,icent,kaon,pos,icent); // kaka
  control(prot,neg,icent,prot,pos,icent); // pbarp
  control(kaon,neg,icent,pion,neg,icent); // pika, neg
  control(kaon,pos,icent,pion,pos,icent); // pika, pos
  control(prot,neg,icent,pion,neg,icent); // ppi, neg
  control(prot,pos,icent,pion,pos,icent); // ppi, pos

  

}

void control(int pid1, int charge1, int cent1, int pid2, int charge2, int cent2)
{

  step1(pid1,charge1,cent1,pid2,charge2,cent2);
  for(int itype=0; itype<10; itype++)
    {
      if(itype==9){cout<<"no ep cut!  skipping!"<<endl;continue;}
      for(int iswitch=0; iswitch<2; iswitch++)
	{
	  step2(pid1,charge1,cent1,pid2,charge2,cent2,itype,iswitch);
	  step3(pid1,charge1,cent1,pid2,charge2,cent2,itype,iswitch);
	}
    }
  step4(pid1,charge1,cent1,pid2,charge2,cent2);

}

// this step calculates the reference ratio
void step1(int ipidX=0, int ichargeX=0, int centidX=0, int ipidY=0, int ichargeY=0, int centidY=0)
{

  char pidstringX[5];
  sprintf(pidstringX,"pion"); // "default"
  if(ipidX==0) sprintf(pidstringX,"pion");
  if(ipidX==1) sprintf(pidstringX,"kaon");
  if(ipidX==2) sprintf(pidstringX,"prot");

  int pidnumberX = 0; // defaul
  if(ipidX==0) pidnumberX = 1;
  if(ipidX==1) pidnumberX = 3;
  if(ipidX==2) pidnumberX = 5;

  char chargestringX[5];
  if(ichargeX==0) sprintf(chargestringX,"neg");
  else if(ichargeX==1) sprintf(chargestringX,"pos");
  else {cout<<"you gonna die"<<endl; return;}

  char centstringX[10];
  if(centidX==0) sprintf(centstringX,"cent0010");
  else if(centidX==1) sprintf(centstringX,"cent1020");
  else if(centidX==2) sprintf(centstringX,"cent2040");
  else if(centidX==3) sprintf(centstringX,"cent4060");
  else if(centidX==4) sprintf(centstringX,"cent6092");
  else {cout<<"you gonna die"<<endl; return;}

  // --

  char pidstringY[5];
  sprintf(pidstringY,"pion"); // "default"
  if(ipidY==0) sprintf(pidstringY,"pion");
  if(ipidY==1) sprintf(pidstringY,"kaon");
  if(ipidY==2) sprintf(pidstringY,"prot");

  int pidnumberY = 0; // defaul
  if(ipidY==0) pidnumberY = 1;
  if(ipidY==1) pidnumberY = 3;
  if(ipidY==2) pidnumberY = 5;
  // if(ipidY==3) pidnumberY = 2;
  // if(ipidY==4) pidnumberY = 4;
  // if(ipidY==5) pidnumberY = 8;

  char chargestringY[5];
  if(ichargeY==0) sprintf(chargestringY,"neg");
  else if(ichargeY==1) sprintf(chargestringY,"pos");
  else {cout<<"you gonna die"<<endl; return;}

  char centstringY[10];
  if(centidY==0) sprintf(centstringY,"cent0010");
  else if(centidY==1) sprintf(centstringY,"cent1020");
  else if(centidY==2) sprintf(centstringY,"cent2040");
  else if(centidY==3) sprintf(centstringY,"cent4060");
  else if(centidY==4) sprintf(centstringY,"cent6092");
  else {cout<<"you gonna die"<<endl; return;}

  // --
  char fnameinX[100];
  char fnameinY[100];
  sprintf(fnameinX,"Data/ptpid_tofw_%s_%d_dis.dat",chargestringX,pidnumberX);
  sprintf(fnameinY,"Data/ptpid_tofw_%s_%d_dis.dat",chargestringY,pidnumberY);
  ifstream finX(fnameinX);
  ifstream finY(fnameinY);

  char fnameout[150];
  sprintf(fnameout,"Data/ratio_reference_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ofstream fout(fnameout);

  float ptuX[100], yielduX[100], eyielduX[100];
  float ptuY[100], yielduY[100], eyielduY[100];
  float ptX[100], yieldX[100], eyieldX[100];
  float ptY[100], yieldY[100], eyieldY[100];
  float pt[36], ratio[36], eratio[36];

  for(int i=0; i<100; i++)
    {
      finX>>ptuX[i]>>yielduX[i]>>eyielduX[i];
      finY>>ptuY[i]>>yielduY[i]>>eyielduY[i];
    }

  for(int i=0; i<100; i++)
    {
      int k;
      if(i<30)
	{
	  ptX[i] = ptuX[i];
	  yieldX[i] = yielduX[i];
	  eyieldX[i] = eyielduX[i];
	  ptY[i] = ptuY[i];
	  yieldY[i] = yielduY[i];
	  eyieldY[i] = eyielduY[i];
	}
      if(i>=30)
	{
	  k=i/5+24;
	  if(i%5!=0) continue;
	  ptX[k] = (ptuX[i]+ptuX[i+1]+ptuX[i+2]+ptuX[i+3]+ptuX[i+4])/5.0;
	  yieldX[k] = (yielduX[i]+yielduX[i+1]+yielduX[i+2]+yielduX[i+3]+yielduX[i+4])/5.0;
	  eyieldX[k] = sqrt(eyielduX[i]**2+eyielduX[i+1]**2+eyielduX[i+2]**2+eyielduX[i+3]**2+eyielduX[i+4]**2)/5.0;
	  ptY[k] = (ptuY[i]+ptuY[i+1]+ptuY[i+2]+ptuY[i+3]+ptuY[i+4])/5.0;
	  yieldY[k] = (yielduY[i]+yielduY[i+1]+yielduY[i+2]+yielduY[i+3]+yielduY[i+4])/5.0;
	  eyieldY[k] = sqrt(eyielduY[i]**2+eyielduY[i+1]**2+eyielduY[i+2]**2+eyielduY[i+3]**2+eyielduY[i+4]**2)/5.0;
	}
    }

  for(int i=0; i<36; i++)
    {
      if(ptX[i]!=ptY[i]){cout<<ptX[i]<<" "<<ptY[i]<<" spells trouble for you"<<endl;}
      pt[i]=ptX[i];
      ratio[i] = yieldX[i]/yieldY[i];
      eratio[i] = yieldX[i]/yieldY[i]*sqrt((eyieldX[i]/yieldX[i])**2+(eyieldY[i]/yieldY[i])**2);
      if(pt[i]<0.5){ratio[i]=-9;eratio[i]=0;}
      fout<<pt[i]<<"\t"<<ratio[i]<<"\t"<<eratio[i]<<endl;
    }

}


// this step calculates the sys-varied ratio
void step2(int ipidX=0, int ichargeX=0, int centidX=0, int ipidY=0, int ichargeY=0, int centidY=0, int itype=0, int iswitch=0)
{

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
  if(itype==9) sprintf(typestring,"tepc");

  char switchstring[2];
  sprintf(switchstring,"A"); // "default"
  if(iswitch==0) sprintf(switchstring,"A");
  if(iswitch==1) sprintf(switchstring,"B");

  // ---

  char pidstringX[5];
  sprintf(pidstringX,"pion"); // "default"
  if(ipidX==0) sprintf(pidstringX,"pion");
  if(ipidX==1) sprintf(pidstringX,"kaon");
  if(ipidX==2) sprintf(pidstringX,"prot");

  int pidnumberX = 0; // defaul
  if(ipidX==0) pidnumberX = 1;
  if(ipidX==1) pidnumberX = 3;
  if(ipidX==2) pidnumberX = 5;
  // if(ipidX==3) pidnumberX = 2;
  // if(ipidX==4) pidnumberX = 4;
  // if(ipidX==5) pidnumberX = 8;

  char chargestringX[5];
  if(ichargeX==0) sprintf(chargestringX,"neg");
  else if(ichargeX==1) sprintf(chargestringX,"pos");
  else {cout<<"you gonna die"<<endl; return;}

  char centstringX[10];
  if(centidX==0) sprintf(centstringX,"cent0010");
  else if(centidX==1) sprintf(centstringX,"cent1020");
  else if(centidX==2) sprintf(centstringX,"cent2040");
  else if(centidX==3) sprintf(centstringX,"cent4060");
  else if(centidX==4) sprintf(centstringX,"cent6092");
  else {cout<<"you gonna die"<<endl; return;}

  // --

  char pidstringY[5];
  sprintf(pidstringY,"pion"); // "default"
  if(ipidY==0) sprintf(pidstringY,"pion");
  if(ipidY==1) sprintf(pidstringY,"kaon");
  if(ipidY==2) sprintf(pidstringY,"prot");

  int pidnumberY = 0; // defaul
  if(ipidY==0) pidnumberY = 1;
  if(ipidY==1) pidnumberY = 3;
  if(ipidY==2) pidnumberY = 5;
  // if(ipidY==3) pidnumberY = 2;
  // if(ipidY==4) pidnumberY = 4;
  // if(ipidY==5) pidnumberY = 8;

  char chargestringY[5];
  if(ichargeY==0) sprintf(chargestringY,"neg");
  else if(ichargeY==1) sprintf(chargestringY,"pos");
  else {cout<<"you gonna die"<<endl; return;}

  char centstringY[10];
  if(centidY==0) sprintf(centstringY,"cent0010");
  else if(centidY==1) sprintf(centstringY,"cent1020");
  else if(centidY==2) sprintf(centstringY,"cent2040");
  else if(centidY==3) sprintf(centstringY,"cent4060");
  else if(centidY==4) sprintf(centstringY,"cent6092");
  else {cout<<"you gonna die"<<endl; return;}

  // --
  char fnameinX[100];
  char fnameinY[100];
  //sprintf(fnameinX,"Data/ptpid_tofw_%s_%d_dis_%s.dat",chargestringX,pidnumberX,centstringX);
  //sprintf(fnameinY,"Data/ptpid_tofw_%s_%d_dis_%s.dat",chargestringY,pidnumberY,centstringY);
  sprintf(fnameinX,"Data/ptsys_%s_%s_%s%s.dat",pidstringX,chargestringX,typestring,switchstring);
  sprintf(fnameinY,"Data/ptsys_%s_%s_%s%s.dat",pidstringY,chargestringY,typestring,switchstring);
  ifstream finX(fnameinX);
  ifstream finY(fnameinY);

  char fnameout[150];
  sprintf(fnameout,"Data/ratio_sys_%s%s_%s%s%s%s_%d%d.dat",typestring,switchstring,chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ofstream fout(fnameout);


  float ptuX[100], yielduX[100], eyielduX[100];
  float ptuY[100], yielduY[100], eyielduY[100];
  float ptX[100], yieldX[100], eyieldX[100];
  float ptY[100], yieldY[100], eyieldY[100];
  float pt[36], ratio[36], eratio[36];

  for(int i=0; i<100; i++)
    {
      finX>>ptuX[i]>>yielduX[i]>>eyielduX[i];
      finY>>ptuY[i]>>yielduY[i]>>eyielduY[i];
    }

  for(int i=0; i<100; i++)
    {
      int k;
      if(i<30)
	{
	  ptX[i] = ptuX[i];
	  yieldX[i] = yielduX[i];
	  eyieldX[i] = eyielduX[i];
	  ptY[i] = ptuY[i];
	  yieldY[i] = yielduY[i];
	  eyieldY[i] = eyielduY[i];
	}
      if(i>=30)
	{
	  k=i/5+24;
	  if(i%5!=0) continue;
	  ptX[k] = (ptuX[i]+ptuX[i+1]+ptuX[i+2]+ptuX[i+3]+ptuX[i+4])/5.0;
	  yieldX[k] = (yielduX[i]+yielduX[i+1]+yielduX[i+2]+yielduX[i+3]+yielduX[i+4])/5.0;
	  eyieldX[k] = sqrt(eyielduX[i]**2+eyielduX[i+1]**2+eyielduX[i+2]**2+eyielduX[i+3]**2+eyielduX[i+4]**2)/5.0;
	  ptY[k] = (ptuY[i]+ptuY[i+1]+ptuY[i+2]+ptuY[i+3]+ptuY[i+4])/5.0;
	  yieldY[k] = (yielduY[i]+yielduY[i+1]+yielduY[i+2]+yielduY[i+3]+yielduY[i+4])/5.0;
	  eyieldY[k] = sqrt(eyielduY[i]**2+eyielduY[i+1]**2+eyielduY[i+2]**2+eyielduY[i+3]**2+eyielduY[i+4]**2)/5.0;
	}
    }

  for(int i=0; i<36; i++)
    {
      if(ptX[i]!=ptY[i]){cout<<ptX[i]<<" "<<ptY[i]<<" spells trouble for you"<<endl;}
      pt[i]=ptX[i];
      ratio[i] = yieldX[i]/yieldY[i];
      eratio[i] = yieldX[i]/yieldY[i]*sqrt((eyieldX[i]/yieldX[i])**2+(eyieldY[i]/yieldY[i])**2);
      if(pt[i]<0.5){ratio[i]=-9;eratio[i]=0;}
      fout<<pt[i]<<"\t"<<ratio[i]<<"\t"<<eratio[i]<<endl;
    }

}

// this step copmare the sys-varied to the reference to determine the uncertainty
void step3(int ipidX=0, int ichargeX=0, int centidX=0, int ipidY=0, int ichargeY=0, int centidY=0, int itype=0, int iswitch=0)
{

  // --

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
  if(itype==9) sprintf(typestring,"tepc");

  char switchstring[2];
  sprintf(switchstring,"A"); // "default"
  if(iswitch==0) sprintf(switchstring,"A");
  if(iswitch==1) sprintf(switchstring,"B");

  // --

  char pidstringX[5];
  sprintf(pidstringX,"pion"); // "default"
  if(ipidX==0) sprintf(pidstringX,"pion");
  if(ipidX==1) sprintf(pidstringX,"kaon");
  if(ipidX==2) sprintf(pidstringX,"prot");

  int pidnumberX = 0; // defaul
  if(ipidX==0) pidnumberX = 1;
  if(ipidX==1) pidnumberX = 3;
  if(ipidX==2) pidnumberX = 5;
  // if(ipidX==3) pidnumberX = 2;
  // if(ipidX==4) pidnumberX = 4;
  // if(ipidX==5) pidnumberX = 8;

  char chargestringX[5];
  if(ichargeX==0) sprintf(chargestringX,"neg");
  else if(ichargeX==1) sprintf(chargestringX,"pos");
  else {cout<<"you gonna die"<<endl; return;}

  char centstringX[10];
  if(centidX==0) sprintf(centstringX,"cent0010");
  else if(centidX==1) sprintf(centstringX,"cent1020");
  else if(centidX==2) sprintf(centstringX,"cent2040");
  else if(centidX==3) sprintf(centstringX,"cent4060");
  else if(centidX==4) sprintf(centstringX,"cent6092");
  else {cout<<"you gonna die"<<endl; return;}

  // --

  char pidstringY[5];
  sprintf(pidstringY,"pion"); // "default"
  if(ipidY==0) sprintf(pidstringY,"pion");
  if(ipidY==1) sprintf(pidstringY,"kaon");
  if(ipidY==2) sprintf(pidstringY,"prot");

  int pidnumberY = 0; // defaul
  if(ipidY==0) pidnumberY = 1;
  if(ipidY==1) pidnumberY = 3;
  if(ipidY==2) pidnumberY = 5;

  char chargestringY[5];
  if(ichargeY==0) sprintf(chargestringY,"neg");
  else if(ichargeY==1) sprintf(chargestringY,"pos");
  else {cout<<"you gonna die"<<endl; return;}

  char centstringY[10];
  if(centidY==0) sprintf(centstringY,"cent0010");
  else if(centidY==1) sprintf(centstringY,"cent1020");
  else if(centidY==2) sprintf(centstringY,"cent2040");
  else if(centidY==3) sprintf(centstringY,"cent4060");
  else if(centidY==4) sprintf(centstringY,"cent6092");
  else {cout<<"you gonna die"<<endl; return;}

  // --

  char fnameref[150];
  sprintf(fnameref,"Data/ratio_reference_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ifstream fref(fnameref);
  char fnamesys[150];
  sprintf(fnamesys,"Data/ratio_sys_%s%s_%s%s%s%s_%d%d.dat",typestring,switchstring,chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ifstream fsys(fnamesys);
  // --
  char fnameout[150];
  sprintf(fnameout,"Data/uncertain_%s%s_%s%s%s%s_%d%d.dat",typestring,switchstring,chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ofstream fout(fnameout);

  float ptref, raref, eraref;
  float ptsys, rasys, erasys;
  float ptout, raout, eraout;
  float pt[36], ratio[36], eratio[36]; // out
  float pe[36], retio[36], eretio[36]; // ref
  float py[36], rytio[36], erytio[36]; // sys

  for(int i=0; i<36; i++)
    {
      fref>>ptref>>raref>>eraref;
      fsys>>ptsys>>rasys>>erasys;
      if(ptsys!=ptref)cout<<ptsys<<" "<<ptref<<" prepare for agony"<<endl;
      ptout=ptsys;
      raout = fabs(1-(rasys/raref));
      eraout = (rasys/raref)*sqrt((eraref/raref)**2+(erasys/rasys)**2);
      if(ptout<0.5){raout=-9;eraout=0;}
      fout<<ptout<<"\t"<<raout<<"\t"<<eraout<<endl;
      pt[i] = ptout;
      ratio[i] = raout;
      eratio[i] = eraout;
      pe[i] = ptref;
      retio[i] = raref;
      eretio[i] = eraref;
      py[i] = ptsys;
      rytio[i] = rasys;
      erytio[i] = erasys;
    }

  float ept[36]={0};
  char figname[150];
  TCanvas *c1 = new TCanvas();
  TGraphErrors *tge = new TGraphErrors(36,pt,ratio,ept,eratio);
  tge->SetMarkerStyle(kFullCircle);
  tge->SetMarkerColor(kBlack);
  tge->Draw("ap");
  TLine line(0.0,0.0,6.0,0.0);
  line.Draw();
  tge->SetMinimum(-0.1);
  tge->SetMaximum(0.5);
  tge->GetXaxis()->SetLimits(0.0,6.0);
  tge->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tge->GetYaxis()->SetTitle("Systematic Uncertainty");
  tge->GetXaxis()->CenterTitle();
  tge->GetYaxis()->CenterTitle();
  sprintf(figname,"UFig/uncertain_%s%s_%s%s%s%s_%d%d.png",typestring,switchstring,chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(figname);
  sprintf(figname,"UFig/uncertain_%s%s_%s%s%s%s_%d%d.eps",typestring,switchstring,chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(figname);
  c1->Clear();
  TGraphErrors *tge_ref = new TGraphErrors(36,pt,retio,ept,eretio);
  tge_ref->SetMarkerStyle(kOpenCircle);
  tge_ref->SetMarkerColor(kBlack);
  TGraphErrors *tge_sys = new TGraphErrors(36,pt,rytio,ept,erytio);
  tge_sys->SetMarkerStyle(kFullCircle);
  tge_sys->SetMarkerColor(kRed);
  TMultiGraph *tmg = new TMultiGraph();
  tmg->Add(tge_ref);
  tmg->Add(tge_sys);
  tmg->Draw("ap");
  tmg->SetMinimum(0.0);
  tmg->SetMaximum(2.0);
  tmg->GetXaxis()->SetLimits(0.0,6.0);
  tmg->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  tmg->GetYaxis()->SetTitle("Ratio");
  tmg->GetXaxis()->CenterTitle();
  tmg->GetYaxis()->CenterTitle();
  TLegend *leg = new TLegend(0.68,0.68,0.88,0.88);
  leg->AddEntry(tge_ref,"reference","p");
  leg->AddEntry(tge_sys,"sys-varied","p");
  leg->Draw();
  sprintf(figname,"UFig/compadraw_%s%s_%s%s%s%s_%d%d.png",typestring,switchstring,chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(figname);
  sprintf(figname,"UFig/compadraw_%s%s_%s%s%s%s_%d%d.eps",typestring,switchstring,chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(figname);
  c1->Clear();
  // delete c1;
  // delete leg;
  // delete tmg;
  // delete tge_ref;
  // delete tge_sys;
  // delete tge;

}


// this step sums up the uncertainties to get the final result
void step4(int ipidX=0, int ichargeX=0, int centidX=0, int ipidY=0, int ichargeY=0, int centidY=0)
{

  TCanvas *c1 = new TCanvas();

  TLine *line = new TLine(0.0,0.0,6.0,0.0);

  TF1 *fun = new TF1("fun","[0]+[1]/x+[2]/x/x+[3]*exp(sqrt(x))+[4]*sqrt(x)",0.2,6.0);

  // --

  char pidstringX[5];
  sprintf(pidstringX,"pion"); // "default"
  if(ipidX==0) sprintf(pidstringX,"pion");
  if(ipidX==1) sprintf(pidstringX,"kaon");
  if(ipidX==2) sprintf(pidstringX,"prot");

  int pidnumberX = 0; // defaul
  if(ipidX==0) pidnumberX = 1;
  if(ipidX==1) pidnumberX = 3;
  if(ipidX==2) pidnumberX = 5;
  // if(ipidX==3) pidnumberX = 2;
  // if(ipidX==4) pidnumberX = 4;
  // if(ipidX==5) pidnumberX = 8;

  char chargestringX[5];
  if(ichargeX==0) sprintf(chargestringX,"neg");
  else if(ichargeX==1) sprintf(chargestringX,"pos");
  else {cout<<"you gonna die"<<endl; return;}

  char centstringX[10];
  if(centidX==0) sprintf(centstringX,"cent0010");
  else if(centidX==1) sprintf(centstringX,"cent1020");
  else if(centidX==2) sprintf(centstringX,"cent2040");
  else if(centidX==3) sprintf(centstringX,"cent4060");
  else if(centidX==4) sprintf(centstringX,"cent6092");
  else {cout<<"you gonna die"<<endl; return;}

  // --

  char pidstringY[5];
  sprintf(pidstringY,"pion"); // "default"
  if(ipidY==0) sprintf(pidstringY,"pion");
  if(ipidY==1) sprintf(pidstringY,"kaon");
  if(ipidY==2) sprintf(pidstringY,"prot");

  int pidnumberY = 0; // defaul
  if(ipidY==0) pidnumberY = 1;
  if(ipidY==1) pidnumberY = 3;
  if(ipidY==2) pidnumberY = 5;
  // if(ipidY==3) pidnumberY = 2;
  // if(ipidY==4) pidnumberY = 4;
  // if(ipidY==5) pidnumberY = 8;

  char chargestringY[5];
  if(ichargeY==0) sprintf(chargestringY,"neg");
  else if(ichargeY==1) sprintf(chargestringY,"pos");
  else {cout<<"you gonna die"<<endl; return;}

  char centstringY[10];
  if(centidY==0) sprintf(centstringY,"cent0010");
  else if(centidY==1) sprintf(centstringY,"cent1020");
  else if(centidY==2) sprintf(centstringY,"cent2040");
  else if(centidY==3) sprintf(centstringY,"cent4060");
  else if(centidY==4) sprintf(centstringY,"cent6092");
  else {cout<<"you gonna die"<<endl; return;}

  // --

  char fnameinX_1a[100];
  char fnameinY_1a[100];
  sprintf(fnameinX_1a,"Data/uncertain_dcfcA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  sprintf(fnameinY_1a,"Data/uncertain_dcfcA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ifstream finX_1a;
  ifstream finY_1a;
  finX_1a.open(fnameinX_1a);
  finY_1a.open(fnameinY_1a);

  char fnameinX_2a[100];
  char fnameinY_2a[100];
  sprintf(fnameinX_2a,"Data/uncertain_dzedA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  sprintf(fnameinY_2a,"Data/uncertain_dzedA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ifstream finX_2a;
  ifstream finY_2a;
  finX_2a.open(fnameinX_2a);
  finY_2a.open(fnameinY_2a);

  char fnameinX_3a[100];
  char fnameinY_3a[100];
  sprintf(fnameinX_3a,"Data/uncertain_pc3mA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  sprintf(fnameinY_3a,"Data/uncertain_pc3mA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ifstream finX_3a;
  ifstream finY_3a;
  finX_3a.open(fnameinX_3a);
  finY_3a.open(fnameinY_3a);

  char fnameinX_4a[100];
  char fnameinY_4a[100];
  sprintf(fnameinX_4a,"Data/uncertain_tfwmA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  sprintf(fnameinY_4a,"Data/uncertain_tfwmA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ifstream finX_4a;
  ifstream finY_4a;
  finX_4a.open(fnameinX_4a);
  finY_4a.open(fnameinY_4a);

  char fnameinX_5a[100];
  char fnameinY_5a[100];
  sprintf(fnameinX_5a,"Data/uncertain_pc1fA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  sprintf(fnameinY_5a,"Data/uncertain_pc1fA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ifstream finX_5a;
  ifstream finY_5a;
  finX_5a.open(fnameinX_5a);
  finY_5a.open(fnameinY_5a);

  char fnameinX_6a[100];
  char fnameinY_6a[100];
  sprintf(fnameinX_6a,"Data/uncertain_pc3fA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  sprintf(fnameinY_6a,"Data/uncertain_pc3fA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ifstream finX_6a;
  ifstream finY_6a;
  finX_6a.open(fnameinX_6a);
  finY_6a.open(fnameinY_6a);

  char fnameinX_7a[100];
  char fnameinY_7a[100];
  sprintf(fnameinX_7a,"Data/uncertain_spidA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  sprintf(fnameinY_7a,"Data/uncertain_spidA_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ifstream finX_7a;
  ifstream finY_7a;
  finX_7a.open(fnameinX_7a);
  finY_7a.open(fnameinY_7a);

  char fnameinX_1b[100];
  char fnameinY_1b[100];
  sprintf(fnameinX_1b,"Data/uncertain_dcfcB_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  sprintf(fnameinY_1b,"Data/uncertain_dcfcB_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ifstream finX_1b;
  ifstream finY_1b;
  finX_1b.open(fnameinX_1b);
  finY_1b.open(fnameinY_1b);

  char fnameinX_7b[100];
  char fnameinY_7b[100];
  sprintf(fnameinX_7b,"Data/uncertain_spidB_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  sprintf(fnameinY_7b,"Data/uncertain_spidB_%s%s%s%s_%d%d.dat",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  ifstream finX_7b;
  ifstream finY_7b;
  finX_7b.open(fnameinX_7b);
  finY_7b.open(fnameinY_7b);

  float pt_X_1a[36],pt_X_2a[36],pt_X_3a[36],pt_X_4a[36],pt_X_5a[36],pt_X_6a[36],pt_X_7a[36],pt_X_1b[36],pt_X_7b[36];
  float un_X_1a[36],un_X_2a[36],un_X_3a[36],un_X_4a[36],un_X_5a[36],un_X_6a[36],un_X_7a[36],un_X_1b[36],un_X_7b[36];
  float er_X_1a[36],er_X_2a[36],er_X_3a[36],er_X_4a[36],er_X_5a[36],er_X_6a[36],er_X_7a[36],er_X_1b[36],er_X_7b[36];
  float pt_Y_1a[36],pt_Y_2a[36],pt_Y_3a[36],pt_Y_4a[36],pt_Y_5a[36],pt_Y_6a[36],pt_Y_7a[36],pt_Y_1b[36],pt_Y_7b[36];
  float un_Y_1a[36],un_Y_2a[36],un_Y_3a[36],un_Y_4a[36],un_Y_5a[36],un_Y_6a[36],un_Y_7a[36],un_Y_1b[36],un_Y_7b[36];
  float er_Y_1a[36],er_Y_2a[36],er_Y_3a[36],er_Y_4a[36],er_Y_5a[36],er_Y_6a[36],er_Y_7a[36],er_Y_1b[36],er_Y_7b[36];
  float ept[36]={0};



  for(int i=0; i<36; i++)
    {

      finX_1a>>pt_X_1a[i]>>un_X_1a[i]>>er_X_1a[i];
      finX_2a>>pt_X_2a[i]>>un_X_2a[i]>>er_X_2a[i];
      finX_3a>>pt_X_3a[i]>>un_X_3a[i]>>er_X_3a[i];
      finX_4a>>pt_X_4a[i]>>un_X_4a[i]>>er_X_4a[i];
      finX_5a>>pt_X_5a[i]>>un_X_5a[i]>>er_X_5a[i];
      finX_6a>>pt_X_6a[i]>>un_X_6a[i]>>er_X_6a[i];
      finX_7a>>pt_X_7a[i]>>un_X_7a[i]>>er_X_7a[i];
      finX_1b>>pt_X_1b[i]>>un_X_1b[i]>>er_X_1b[i];
      finX_7b>>pt_X_7b[i]>>un_X_7b[i]>>er_X_7b[i];

      finY_1a>>pt_Y_1a[i]>>un_Y_1a[i]>>er_Y_1a[i];
      finY_2a>>pt_Y_2a[i]>>un_Y_2a[i]>>er_Y_2a[i];
      finY_3a>>pt_Y_3a[i]>>un_Y_3a[i]>>er_Y_3a[i];
      finY_4a>>pt_Y_4a[i]>>un_Y_4a[i]>>er_Y_4a[i];
      finY_5a>>pt_Y_5a[i]>>un_Y_5a[i]>>er_Y_5a[i];
      finY_6a>>pt_Y_6a[i]>>un_Y_6a[i]>>er_Y_6a[i];
      finY_7a>>pt_Y_7a[i]>>un_Y_7a[i]>>er_Y_7a[i];
      finY_1b>>pt_Y_1b[i]>>un_Y_1b[i]>>er_Y_1b[i];
      finY_7b>>pt_Y_7b[i]>>un_Y_7b[i]>>er_Y_7b[i];

    }



  finX_1a.close();
  finX_2a.close();
  finX_3a.close();
  finX_4a.close();
  finX_5a.close();
  finX_6a.close();
  finX_7a.close();
  finX_1b.close();
  finX_7b.close();

  finY_1a.close();
  finY_2a.close();
  finY_3a.close();
  finY_4a.close();
  finY_5a.close();
  finY_6a.close();
  finY_7a.close();
  finY_1b.close();
  finY_7b.close();



  // ---
  // ---
  // ---

  float pt_X_sumA[36];
  float un_X_sumA[36];
  float er_X_sumA[36];
  float pt_Y_sumA[36];
  float un_Y_sumA[36];
  float er_Y_sumA[36];

  for(int i=0; i<36; i++)
    {
      pt_X_sumA[i] = pt_X_1a[i]; // arbitrary, all same
      un_X_sumA[i] = sqrt(
			    un_X_1a[i]**2 + 
			    un_X_2a[i]**2 + 
			    un_X_3a[i]**2 + 
			    un_X_4a[i]**2 + 
			    un_X_5a[i]**2 + 
			    un_X_6a[i]**2 + 
			    un_X_7a[i]**2);
      er_X_sumA[i] = sqrt(
			    er_X_1a[i]**2 + 
			    er_X_2a[i]**2 + 
			    er_X_3a[i]**2 + 
			    er_X_4a[i]**2 + 
			    er_X_5a[i]**2 + 
			    er_X_6a[i]**2 + 
			    er_X_7a[i]**2)/7.0;

    }

  TGraphErrors *tge_sumA = new TGraphErrors(36,pt_X_sumA,un_X_sumA,ept,er_X_sumA);
  tge_sumA->SetMarkerStyle(kFullCircle);
  tge_sumA->SetMarkerColor(kBlack);
  tge_sumA->Draw("ap");
  line->Draw("same");
  //tge_sumA->Fit(fun,"R");
  //if(ipid==1) tge_sumA->Fit(fun,"","",0.3,4.5);
  //if(ipid==2) tge_sumA->Fit(fun,"","",0.4,6.0);
  tge_sumA->SetMaximum(1.0);
  tge_sumA->SetMinimum(-0.1);
  tge_sumA->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumA->GetXaxis()->SetTitle("p_{T}");
  tge_sumA->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameA[100];
  sprintf(fignameA,"AFig/uncertain_sumA_%s%s%s%s_%d%d.png",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(fignameA);
  sprintf(fignameA,"AFig/uncertain_sumA_%s%s%s%s_%d%d.eps",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(fignameA);

  //continue; // TEMP

  float pt_X_sumB[36];
  float un_X_sumB[36];
  float er_X_sumB[36];
  float pt_Y_sumB[36];
  float un_Y_sumB[36];
  float er_Y_sumB[36];

  for(int i=0; i<36; i++)
    {
      pt_X_sumB[i] = pt_X_1a[i]; // arbitrary, all same
      un_X_sumB[i] = sqrt(
			    un_X_1b[i]**2 + 
			    un_X_2a[i]**2 + 
			    un_X_3a[i]**2 + 
			    un_X_4a[i]**2 + 
			    un_X_5a[i]**2 + 
			    un_X_6a[i]**2 + 
			    un_X_7a[i]**2);
      er_X_sumB[i] = sqrt(
			    er_X_1b[i]**2 + 
			    er_X_2a[i]**2 + 
			    er_X_3a[i]**2 + 
			    er_X_4a[i]**2 + 
			    er_X_5a[i]**2 + 
			    er_X_6a[i]**2 + 
			    er_X_7a[i]**2)/7.0;

    }

  TGraphErrors *tge_sumB = new TGraphErrors(36,pt_X_sumB,un_X_sumB,ept,er_X_sumB);
  tge_sumB->SetMarkerStyle(kFullCircle);
  tge_sumB->SetMarkerColor(kBlack);
  tge_sumB->Draw("ap");
  line->Draw("same");
  //tge_sumB->Fit(fun,"R");
  //if(ipid==1) tge_sumB->Fit(fun,"","",0.3,4.5);
  //if(ipid==2) tge_sumB->Fit(fun,"","",0.4,6.0);
  tge_sumB->SetMaximum(1.0);
  tge_sumB->SetMinimum(-0.1);
  tge_sumB->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumB->GetXaxis()->SetTitle("p_{T}");
  tge_sumB->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameB[100];
  sprintf(fignameB,"AFig/uncertain_sumB_%s%s%s%s_%d%d.png",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(fignameB);
  sprintf(fignameB,"AFig/uncertain_sumB_%s%s%s%s_%d%d.eps",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(fignameB);



  float pt_X_sumAa[36];
  float un_X_sumAa[36];
  float er_X_sumAa[36];
  float pt_Y_sumAa[36];
  float un_Y_sumAa[36];
  float er_Y_sumAa[36];

  for(int i=0; i<36; i++)
    {
      pt_X_sumAa[i] = pt_X_1a[i]; // arbitrary, all same
      un_X_sumAa[i] = sqrt(
			    un_X_1a[i]**2 + 
			    un_X_2a[i]**2 + 
			    un_X_3a[i]**2 + 
			    un_X_4a[i]**2 + 
			    un_X_5a[i]**2 + 
			    un_X_6a[i]**2 + 
			    un_X_7a[i]**2 + 
			    un_X_7b[i]**2);
      er_X_sumAa[i] = sqrt(
			    er_X_1a[i]**2 + 
			    er_X_2a[i]**2 + 
			    er_X_3a[i]**2 + 
			    er_X_4a[i]**2 + 
			    er_X_5a[i]**2 + 
			    er_X_6a[i]**2 + 
			    er_X_7a[i]**2 + 
			    er_X_7b[i]**2)/7.0;

    }

  TGraphErrors *tge_sumAa = new TGraphErrors(36,pt_X_sumAa,un_X_sumAa,ept,er_X_sumAa);
  tge_sumAa->SetMarkerStyle(kFullCircle);
  tge_sumAa->SetMarkerColor(kBlack);
  tge_sumAa->Draw("ap");
  line->Draw("same");
  //tge_sumAa->Fit(fun,"R");
  //if(ipid==1) tge_sumAa->Fit(fun,"","",0.3,4.0);
  //if(ipid==2) tge_sumAa->Fit(fun,"","",0.4,6.0);
  tge_sumAa->SetMaximum(1.0);
  tge_sumAa->SetMinimum(-0.1);
  tge_sumAa->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumAa->GetXaxis()->SetTitle("p_{T}");
  tge_sumAa->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameAa[100];
  sprintf(fignameAa,"AFig/uncertain_sumAa_%s%s%s%s_%d%d.png",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(fignameAa);
  sprintf(fignameAa,"AFig/uncertain_sumAa_%s%s%s%s_%d%d.eps",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(fignameAa);



  float pt_X_sumBb[36];
  float un_X_sumBb[36];
  float er_X_sumBb[36];
  float pt_Y_sumBb[36];
  float un_Y_sumBb[36];
  float er_Y_sumBb[36];

  for(int i=0; i<36; i++)
    {
      pt_X_sumBb[i] = pt_X_1a[i]; // arbitrary, all same
      un_X_sumBb[i] = sqrt(
			    un_X_1b[i]**2 + 
			    un_X_2a[i]**2 + 
			    un_X_3a[i]**2 + 
			    un_X_4a[i]**2 + 
			    un_X_5a[i]**2 + 
			    un_X_6a[i]**2 + 
			    un_X_7a[i]**2 + 
			    un_X_7b[i]**2);
      er_X_sumBb[i] = sqrt(
			    er_X_1b[i]**2 + 
			    er_X_2a[i]**2 + 
			    er_X_3a[i]**2 + 
			    er_X_4a[i]**2 + 
			    er_X_5a[i]**2 + 
			    er_X_6a[i]**2 + 
			    er_X_7a[i]**2 + 
			    er_X_7b[i]**2)/7.0;

    }

  TGraphErrors *tge_sumBb = new TGraphErrors(36,pt_X_sumBb,un_X_sumBb,ept,er_X_sumBb);
  tge_sumBb->SetMarkerStyle(kFullCircle);
  tge_sumBb->SetMarkerColor(kBlack);
  tge_sumBb->Draw("ap");
  line->Draw("same");
  //tge_sumBb->Fit(fun,"R");
  //if(ipid==1) tge_sumBb->Fit(fun,"","",0.3,4.0);
  //if(ipid==2) tge_sumBb->Fit(fun,"","",0.4,6.0);
  tge_sumBb->SetMaximum(1.0);
  tge_sumBb->SetMinimum(-0.1);
  tge_sumBb->GetXaxis()->SetLimits(0.0,6.0);
  tge_sumBb->GetXaxis()->SetTitle("p_{T}");
  tge_sumBb->GetYaxis()->SetTitle("Systematic Uncertainty");

  char fignameBb[100];
  sprintf(fignameBb,"AFig/uncertain_sumBb_%s%s%s%s_%d%d.png",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(fignameBb);
  sprintf(fignameBb,"AFig/uncertain_sumBb_%s%s%s%s_%d%d.eps",chargestringX,pidstringX,chargestringY,pidstringY,pidnumberX,pidnumberY);
  c1->Print(fignameBb);






}



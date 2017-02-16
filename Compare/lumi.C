float numApp = 449986638.0;
float numBpp = 471459131.0;
float numCpp = 428340263.0;
float numDpp = 27399373.0;

float numBmm = 59744470.0;
float numCmm = 291129781.0;
float numDmm = 118645423.0;

void lumi()
{

  doit("C","D","mm","pos",1,"0005",numCmm,numDmm);
  doit("C","D","mm","pos",1,"0020",numCmm,numDmm);
  doit("C","D","mm","pos",3,"0005",numCmm,numDmm);
  doit("C","D","mm","pos",3,"0020",numCmm,numDmm);
  doit("C","D","mm","pos",5,"0005",numCmm,numDmm);
  doit("C","D","mm","pos",5,"0020",numCmm,numDmm);
  doit("C","D","mm","neg",1,"0005",numCmm,numDmm);
  doit("C","D","mm","neg",1,"0020",numCmm,numDmm);
  doit("C","D","mm","neg",3,"0005",numCmm,numDmm);
  doit("C","D","mm","neg",3,"0020",numCmm,numDmm);
  doit("C","D","mm","neg",5,"0005",numCmm,numDmm);
  doit("C","D","mm","neg",5,"0020",numCmm,numDmm);

  doit("B","C","pp","pos",1,"0005",numBpp,numCpp);
  doit("B","C","pp","pos",1,"0020",numBpp,numCpp);
  doit("B","C","pp","pos",3,"0005",numBpp,numCpp);
  doit("B","C","pp","pos",3,"0020",numBpp,numCpp);
  doit("B","C","pp","pos",5,"0005",numBpp,numCpp);
  doit("B","C","pp","pos",5,"0020",numBpp,numCpp);
  doit("B","C","pp","neg",1,"0005",numBpp,numCpp);
  doit("B","C","pp","neg",1,"0020",numBpp,numCpp);
  doit("B","C","pp","neg",3,"0005",numBpp,numCpp);
  doit("B","C","pp","neg",3,"0020",numBpp,numCpp);
  doit("B","C","pp","neg",5,"0005",numBpp,numCpp);
  doit("B","C","pp","neg",5,"0020",numBpp,numCpp);

  doit("A","C","pp","pos",1,"0005",numApp,numCpp);
  doit("A","C","pp","pos",1,"0020",numApp,numCpp);
  doit("A","C","pp","pos",3,"0005",numApp,numCpp);
  doit("A","C","pp","pos",3,"0020",numApp,numCpp);
  doit("A","C","pp","pos",5,"0005",numApp,numCpp);
  doit("A","C","pp","pos",5,"0020",numApp,numCpp);
  doit("A","C","pp","neg",1,"0005",numApp,numCpp);
  doit("A","C","pp","neg",1,"0020",numApp,numCpp);
  doit("A","C","pp","neg",3,"0005",numApp,numCpp);
  doit("A","C","pp","neg",3,"0020",numApp,numCpp);
  doit("A","C","pp","neg",5,"0005",numApp,numCpp);
  doit("A","C","pp","neg",5,"0020",numApp,numCpp);

}

void doit(char *handelow="C",
	  char *handehgh="D",
	  char *field="mm",
	  char *chrg="pos",
	  int pidn=1,
	  char *cent="0005",
	  float low=291129781.0,
	  float hgh=118645423.0
	  )
{

  gStyle->SetOptTitle(0);

  char filenamelow[100];
  char filenamehgh[100];
  char histname[100];

  sprintf(filenamelow,"out%s%s.root",handelow,field);
  sprintf(filenamehgh,"out%s%s.root",handehgh,field);
  sprintf(histname,"ptpid_tofw_%s_%d_dis_cent%s",chrg,pidn,cent);

  TFile *flow = TFile::Open(filenamelow);
  TFile *fhgh = TFile::Open(filenamehgh);

  TH1F *h_1_low = (TH1F *)flow->Get(histname);
  TH1F *h_1_hgh = (TH1F *)fhgh->Get(histname);

  h_1_low->Sumw2();
  h_1_hgh->Sumw2();

  h_1_low->Scale(1.0/low);
  h_1_hgh->Scale(1.0/hgh);

  h_1_low->Divide(h_1_hgh);
  h_1_low->Draw();
  h_1_low->SetMaximum(1.5);
  h_1_low->SetMinimum(0.5);
  h_1_low->GetXaxis()->SetRange(1,50);
  h_1_low->Fit("pol0","","",0.5,5.0);
  h_1_low->SetLineColor(kBlack);
  h_1_low->SetMarkerColor(kBlack);
  h_1_low->SetMarkerStyle(kOpenCircle);
  h_1_low->Draw();


  char figname[100];
  sprintf(figname,"CompLumiFigs/complumi_%s%d_cent%s_%s%s%s.gif",chrg,pidn,cent,handelow,handehgh,field);
  c1->Print(figname);
  sprintf(figname,"CompLumiFigs/complumi_%s%d_cent%s_%s%s%s.eps",chrg,pidn,cent,handelow,handehgh,field);
  c1->Print(figname);

}

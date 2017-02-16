void rawdraw_v2()
{

  cout<<"starting!"<<endl;

  doit();

  cout<<"done!  have a nice day!"<<endl;

}


void doit(
	  int dis=0,
	  char *tfw="tofw",
	  char *charge="pos",
	  char *cent="cent0088"
	  )
{

  TCanvas *c1 = new TCanvas();
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->SetLogy();

  TFile *file = TFile::Open("outsum_low.root");
  //TH1F *hposdis0 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis");
  //TH1F *hposdis0cent0020 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis_cent0020");
  //TH1F *hposw1dis0cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_pos_0_dis_cent0020");
  //TH1F *hposw2dis0cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_pos_0_dis_cent0020");

  char *histoname[50];
  sprintf(histoname,"ptpid_%s_%s_%d_dis_%s",tfw,charge,dis,cent);



}

void draw_shift_v2()
{

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->cd();

  ifstream fstrip1("PASS4_striptofw/striptofw_gaus.dat");
  ifstream fstrip2("strip-by-strip-pass4.dat");
  float tmp;
  float stripid[512], zero[512]; 
  float shift[512], eshift[512];

  for(int i=0; i<512; i++)
    {
      fstrip1>>stripid[i]>>tmp>>tmp>>eshift[i]>>tmp>>tmp;
      fstrip2>>stripid[i]>>tmp>>shift[i]>>tmp>>tmp>>tmp;
      zero[i] = 0;
      if(eshift[i]>1.0)
	{
	  //shift[i] = -9;
	  //eshift[i] = 0;
	  cout<<"whoops?"<<endl;
	}
      //if(i%50==0) cout<<i<<"\t"<<shift[i]<<"\t"<<eshift[i]<<endl;
    }

  TF1 *fun = new TF1("fun","pol0",0,511);
  fun->SetLineColor(kRed);

  TGraphErrors *tg_strip = new TGraphErrors(512,stripid,shift,zero,eshift);
  //tg_strip->SetTitle("timing shift vs strip");
  tg_strip->SetMarkerStyle(20);
  tg_strip->SetMarkerColor(kBlack);
  //tg_strip->SetMarkerSize(0.8); // looks ugly
  tg_strip->Draw("AP");
  //tg_strip->Fit("fun","R");
  tg_strip->SetMaximum(40.0);
  tg_strip->SetMinimum(0.0);
  tg_strip->GetXaxis()->SetLimits(-10,522);
  tg_strip->GetXaxis()->SetTitle("TOFW strip ID");
  tg_strip->GetYaxis()->SetTitle("Timing shift (ns)");
  tg_strip->GetXaxis()->CenterTitle();
  tg_strip->GetYaxis()->CenterTitle();

  c1->Print("figure_shift_strip-by-strip.gif");
  c1->Print("figure_shift_strip-by-strip.eps");

  TCanvas *c2 = new TCanvas("c2","c2",800,600);
  c2->SetFillColor(kWhite);
  c2->SetBorderMode(0);
  c2->SetFrameFillColor(kWhite);
  c2->SetFrameBorderMode(0);
  c2->cd();

  ifstream frun1("PASS4_run/run_gaus.dat");
  ifstream frun2("run-by-run-pass4.dat");
  //ifstream frun("PASS4_run/run_gaus.dat");
  float tmpR;
  float runid[848], zeroR[848]; 
  float shiftR[848], eshiftR[848];

  for(int i=0; i<848; i++)
    {
      //frun>>runid[i]>>tmpR>>tmpR>>tmpR>>shiftR[i]>>eshiftR[i];
      frun1>>runid[i]>>tmp>>tmp>>eshiftR[i]>>tmp>>tmp;
      frun2>>runid[i]>>tmp>>shiftR[i]>>tmp>>tmp>>tmp;
      zeroR[i] = 0;
      if(eshiftR[i]>1.0)
	{
	  //shiftR[i] = -9;
	  eshiftR[i] = 0;
	}
      //if(i%50==0) cout<<i<<"\t"<<shift[i]<<"\t"<<eshift[i]<<endl;
    }

  TF1 *fun1 = new TF1("fun1","pol0",0,848);
  fun1->SetLineColor(kRed);

  TGraphErrors *tg_run = new TGraphErrors(848,runid,shiftR,zeroR,eshiftR);
  //tg_run->SetTitle("timing shift vs run");
  tg_run->SetMarkerStyle(20);
  tg_run->SetMarkerColor(kBlack);
  //tg_run->SetMarkerSize(0.8); // looks ugly
  tg_run->Draw("AP");
  //tg_run->Fit("fun1","R");
  tg_run->SetMaximum(0.1);
  tg_run->SetMinimum(-0.1);
  tg_run->GetXaxis()->SetLimits(-10,858);
  tg_run->GetXaxis()->SetTitle("Run Index");
  tg_run->GetYaxis()->SetTitle("Timing shift (ns)");
  tg_run->GetXaxis()->CenterTitle();
  tg_run->GetYaxis()->CenterTitle();

  c2->Print("figure_shift_run-by-run.gif");
  c2->Print("figure_shift_run-by-run.eps");


}

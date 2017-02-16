void draw_resolution()
{

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->cd();

  ifstream fstrip("PASS2_striptofw/striptofw_gaus.dat");
  float tmp;
  float stripid[512], zero[512]; 
  float res[512], eres[512];

  for(int i=0; i<512; i++)
    {
      fstrip>>stripid[i]>>tmp>>tmp>>tmp>>res[i]>>eres[i];
      zero[i] = 0;
      if(eres[i]>0.1)
	{
	  res[i] = -9;
	  eres[i] = 0;
	}
      //if(i%50==0) cout<<i<<"\t"<<res[i]<<"\t"<<eres[i]<<endl;
    }

  TF1 *fun = new TF1("fun","pol0",0,511);
  fun->SetLineColor(kRed);

  TGraphErrors *tg_strip = new TGraphErrors(512,stripid,res,zero,eres);
  //tg_strip->SetTitle("timing resolution vs strip");
  tg_strip->SetMarkerStyle(20);
  tg_strip->SetMarkerColor(kBlack);
  //tg_strip->SetMarkerSize(0.8); // looks ugly
  tg_strip->Draw("AP");
  tg_strip->Fit("fun","R");
  tg_strip->SetMaximum(0.2);
  tg_strip->SetMinimum(0.0);
  tg_strip->GetXaxis()->SetLimits(-10,522);
  tg_strip->GetXaxis()->SetTitle("TOFW strip ID");
  tg_strip->GetYaxis()->SetTitle("Timing resolution");
  tg_strip->GetXaxis()->CenterTitle();
  tg_strip->GetYaxis()->CenterTitle();

  TCanvas *c2 = new TCanvas("c2","c2",800,600);
  c2->SetFillColor(kWhite);
  c2->SetBorderMode(0);
  c2->SetFrameFillColor(kWhite);
  c2->SetFrameBorderMode(0);
  c2->cd();

  ifstream frun("PASS2_run/run_gaus.dat");
  float tmpR;
  float runid[848], zeroR[848]; 
  float resR[848], eresR[848];

  for(int i=0; i<848; i++)
    {
      frun>>runid[i]>>tmpR>>tmpR>>tmpR>>resR[i]>>eresR[i];
      zeroR[i] = 0;
      if(eresR[i]>0.1)
	{
	  resR[i] = -9;
	  eresR[i] = 0;
	}
      //if(i%50==0) cout<<i<<"\t"<<res[i]<<"\t"<<eres[i]<<endl;
    }

  TF1 *fun1 = new TF1("fun1","pol0",0,848);
  fun1->SetLineColor(kRed);

  TGraphErrors *tg_run = new TGraphErrors(848,runid,resR,zeroR,eresR);
  //tg_run->SetTitle("timing resolution vs run");
  tg_run->SetMarkerStyle(20);
  tg_run->SetMarkerColor(kBlack);
  //tg_run->SetMarkerSize(0.8); // looks ugly
  tg_run->Draw("AP");
  tg_run->Fit("fun1","R");
  tg_run->SetMaximum(0.2);
  tg_run->SetMinimum(0.0);
  tg_run->GetXaxis()->SetLimits(-10,858);
  tg_run->GetXaxis()->SetTitle("Run Index");
  tg_run->GetYaxis()->SetTitle("Timing resolution");
  tg_run->GetXaxis()->CenterTitle();
  tg_run->GetYaxis()->CenterTitle();



}

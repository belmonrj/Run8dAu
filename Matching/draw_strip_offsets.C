void draw_strip_offsets()
{

  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->cd();

  ifstream fstrip0_pp("residuals-plusplus-pass0.dat");
  ifstream fstrip0_mm("residuals-minusminus-pass0.dat");
  ifstream fstrip1_pp("residuals-plusplus-pass4.dat");
  ifstream fstrip1_mm("residuals-minusminus-pass4.dat");
  float tmp;
  float stripid[512], zero[512]; 
  float shift0_posdz_pp[512], shift0_negdz_pp[512];
  float shift0_posdphi_pp[512], shift0_negdphi_pp[512];
  float shift0_posdz_mm[512], shift0_negdz_mm[512];
  float shift0_posdphi_mm[512], shift0_negdphi_mm[512];
  float shift2_posdz_pp[512], shift2_negdz_pp[512];
  float shift2_posdphi_pp[512], shift2_negdphi_pp[512];
  float shift2_posdz_mm[512], shift2_negdz_mm[512];
  float shift2_posdphi_mm[512], shift2_negdphi_mm[512];

  for(int i=0; i<512; i++)
    {
      fstrip0_pp>>stripid[i]>>shift0_posdz_pp[i]>>shift0_negdz_pp[i]>>shift0_posdphi_pp[i]>>shift0_negdphi_pp[i];
      fstrip0_mm>>stripid[i]>>shift0_posdz_mm[i]>>shift0_negdz_mm[i]>>shift0_posdphi_mm[i]>>shift0_negdphi_mm[i];
      fstrip1_pp>>stripid[i]>>shift2_posdz_pp[i]>>shift2_negdz_pp[i]>>shift2_posdphi_pp[i]>>shift2_negdphi_pp[i];
      fstrip1_mm>>stripid[i]>>shift2_posdz_mm[i]>>shift2_negdz_mm[i]>>shift2_posdphi_mm[i]>>shift2_negdphi_mm[i];
      zero[i] = 0;
    }




  // ------------------ //
  // --- NOW SHIFT0 --- //
  // ------------------ //


  TGraphErrors *tg_shift0_posdz_pp = new TGraphErrors(512,stripid,shift0_posdz_pp,zero,zero);
  tg_shift0_posdz_pp->SetTitle("Run8, ++ field, positive particles, tofwdz");
  tg_shift0_posdz_pp->SetMarkerStyle(20);
  tg_shift0_posdz_pp->SetMarkerColor(kBlack);
  tg_shift0_posdz_pp->Draw("AP");
  tg_shift0_posdz_pp->SetMaximum(5.0);
  tg_shift0_posdz_pp->SetMinimum(-5.0);
  tg_shift0_posdz_pp->GetXaxis()->SetLimits(-10,522);
  tg_shift0_posdz_pp->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift0_posdz_pp->GetYaxis()->SetTitle("Residual shift (cm)");
  tg_shift0_posdz_pp->GetXaxis()->CenterTitle();
  tg_shift0_posdz_pp->GetYaxis()->CenterTitle();

  c1->Print("figure_shift0_posdz_pp_strip-by-strip.gif");
  c1->Print("figure_shift0_posdz_pp_strip-by-strip.eps");


  TGraphErrors *tg_shift0_negdz_pp = new TGraphErrors(512,stripid,shift0_negdz_pp,zero,zero);
  tg_shift0_negdz_pp->SetTitle("Run8, ++ field, negitive particles, tofwdz");
  tg_shift0_negdz_pp->SetMarkerStyle(20);
  tg_shift0_negdz_pp->SetMarkerColor(kBlack);
  tg_shift0_negdz_pp->Draw("AP");
  tg_shift0_negdz_pp->SetMaximum(5.0);
  tg_shift0_negdz_pp->SetMinimum(-5.0);
  tg_shift0_negdz_pp->GetXaxis()->SetLimits(-10,522);
  tg_shift0_negdz_pp->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift0_negdz_pp->GetYaxis()->SetTitle("Residual shift (cm)");
  tg_shift0_negdz_pp->GetXaxis()->CenterTitle();
  tg_shift0_negdz_pp->GetYaxis()->CenterTitle();

  c1->Print("figure_shift0_negdz_pp_strip-by-strip.gif");
  c1->Print("figure_shift0_negdz_pp_strip-by-strip.eps");


  TGraphErrors *tg_shift0_posdphi_pp = new TGraphErrors(512,stripid,shift0_posdphi_pp,zero,zero);
  tg_shift0_posdphi_pp->SetTitle("Run8, ++ field, positive particles, tofwdphi");
  tg_shift0_posdphi_pp->SetMarkerStyle(20);
  tg_shift0_posdphi_pp->SetMarkerColor(kBlack);
  tg_shift0_posdphi_pp->Draw("AP");
  tg_shift0_posdphi_pp->SetMaximum(0.01);
  tg_shift0_posdphi_pp->SetMinimum(-0.01);
  tg_shift0_posdphi_pp->GetXaxis()->SetLimits(-10,522);
  tg_shift0_posdphi_pp->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift0_posdphi_pp->GetYaxis()->SetTitle("Residual shift (rad)");
  tg_shift0_posdphi_pp->GetXaxis()->CenterTitle();
  tg_shift0_posdphi_pp->GetYaxis()->CenterTitle();

  c1->Print("figure_shift0_posdphi_pp_strip-by-strip.gif");
  c1->Print("figure_shift0_posdphi_pp_strip-by-strip.eps");


  TGraphErrors *tg_shift0_negdphi_pp = new TGraphErrors(512,stripid,shift0_negdphi_pp,zero,zero);
  tg_shift0_negdphi_pp->SetTitle("Run8, ++ field, negitive particles, tofwdphi");
  tg_shift0_negdphi_pp->SetMarkerStyle(20);
  tg_shift0_negdphi_pp->SetMarkerColor(kBlack);
  tg_shift0_negdphi_pp->Draw("AP");
  tg_shift0_negdphi_pp->SetMaximum(0.01);
  tg_shift0_negdphi_pp->SetMinimum(-0.01);
  tg_shift0_negdphi_pp->GetXaxis()->SetLimits(-10,522);
  tg_shift0_negdphi_pp->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift0_negdphi_pp->GetYaxis()->SetTitle("Residual shift (rad)");
  tg_shift0_negdphi_pp->GetXaxis()->CenterTitle();
  tg_shift0_negdphi_pp->GetYaxis()->CenterTitle();

  c1->Print("figure_shift0_negdphi_pp_strip-by-strip.gif");
  c1->Print("figure_shift0_negdphi_pp_strip-by-strip.eps");




  // -------------------- //
  // --- NOW PLUSPLUS --- //
  // -------------------- //


  // ------------------ //
  // --- NOW SHIFT2 --- //
  // ------------------ //


  TGraphErrors *tg_shift2_posdz_pp = new TGraphErrors(512,stripid,shift2_posdz_pp,zero,zero);
  tg_shift2_posdz_pp->SetTitle("Run8, ++ field, positive particles, tofwdz");
  tg_shift2_posdz_pp->SetMarkerStyle(20);
  tg_shift2_posdz_pp->SetMarkerColor(kBlack);
  tg_shift2_posdz_pp->Draw("AP");
  tg_shift2_posdz_pp->SetMaximum(0.5);
  tg_shift2_posdz_pp->SetMinimum(-0.5);
  tg_shift2_posdz_pp->GetXaxis()->SetLimits(-10,522);
  tg_shift2_posdz_pp->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift2_posdz_pp->GetYaxis()->SetTitle("Residual shift (cm)");
  tg_shift2_posdz_pp->GetXaxis()->CenterTitle();
  tg_shift2_posdz_pp->GetYaxis()->CenterTitle();

  c1->Print("figure_shift2_posdz_pp_strip-by-strip.gif");
  c1->Print("figure_shift2_posdz_pp_strip-by-strip.eps");


  TGraphErrors *tg_shift2_negdz_pp = new TGraphErrors(512,stripid,shift2_negdz_pp,zero,zero);
  tg_shift2_negdz_pp->SetTitle("Run8, ++ field, negitive particles, tofwdz");
  tg_shift2_negdz_pp->SetMarkerStyle(20);
  tg_shift2_negdz_pp->SetMarkerColor(kBlack);
  tg_shift2_negdz_pp->Draw("AP");
  tg_shift2_negdz_pp->SetMaximum(0.5);
  tg_shift2_negdz_pp->SetMinimum(-0.5);
  tg_shift2_negdz_pp->GetXaxis()->SetLimits(-10,522);
  tg_shift2_negdz_pp->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift2_negdz_pp->GetYaxis()->SetTitle("Residual shift (cm)");
  tg_shift2_negdz_pp->GetXaxis()->CenterTitle();
  tg_shift2_negdz_pp->GetYaxis()->CenterTitle();

  c1->Print("figure_shift2_negdz_pp_strip-by-strip.gif");
  c1->Print("figure_shift2_negdz_pp_strip-by-strip.eps");


  TGraphErrors *tg_shift2_posdphi_pp = new TGraphErrors(512,stripid,shift2_posdphi_pp,zero,zero);
  tg_shift2_posdphi_pp->SetTitle("Run8, ++ field, positive particles, tofwdphi");
  tg_shift2_posdphi_pp->SetMarkerStyle(20);
  tg_shift2_posdphi_pp->SetMarkerColor(kBlack);
  tg_shift2_posdphi_pp->Draw("AP");
  tg_shift2_posdphi_pp->SetMaximum(0.001);
  tg_shift2_posdphi_pp->SetMinimum(-0.001);
  tg_shift2_posdphi_pp->GetXaxis()->SetLimits(-10,522);
  tg_shift2_posdphi_pp->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift2_posdphi_pp->GetYaxis()->SetTitle("Residual shift (rad)");
  tg_shift2_posdphi_pp->GetXaxis()->CenterTitle();
  tg_shift2_posdphi_pp->GetYaxis()->CenterTitle();

  c1->Print("figure_shift2_posdphi_pp_strip-by-strip.gif");
  c1->Print("figure_shift2_posdphi_pp_strip-by-strip.eps");


  TGraphErrors *tg_shift2_negdphi_pp = new TGraphErrors(512,stripid,shift2_negdphi_pp,zero,zero);
  tg_shift2_negdphi_pp->SetTitle("Run8, ++ field, negitive particles, tofwdphi");
  tg_shift2_negdphi_pp->SetMarkerStyle(20);
  tg_shift2_negdphi_pp->SetMarkerColor(kBlack);
  tg_shift2_negdphi_pp->Draw("AP");
  tg_shift2_negdphi_pp->SetMaximum(0.001);
  tg_shift2_negdphi_pp->SetMinimum(-0.001);
  tg_shift2_negdphi_pp->GetXaxis()->SetLimits(-10,522);
  tg_shift2_negdphi_pp->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift2_negdphi_pp->GetYaxis()->SetTitle("Residual shift (rad)");
  tg_shift2_negdphi_pp->GetXaxis()->CenterTitle();
  tg_shift2_negdphi_pp->GetYaxis()->CenterTitle();

  c1->Print("figure_shift2_negdphi_pp_strip-by-strip.gif");
  c1->Print("figure_shift2_negdphi_pp_strip-by-strip.eps");


  // ---------------------- //
  // --- NOW MINUSMINUS --- //
  // ---------------------- //


  // ------------------ //
  // --- NOW SHIFT0 --- //
  // ------------------ //


  TGraphErrors *tg_shift0_posdz_mm = new TGraphErrors(512,stripid,shift0_posdz_mm,zero,zero);
  tg_shift0_posdz_mm->SetTitle("Run8, ++ field, positive particles, tofwdz");
  tg_shift0_posdz_mm->SetMarkerStyle(20);
  tg_shift0_posdz_mm->SetMarkerColor(kBlack);
  tg_shift0_posdz_mm->Draw("AP");
  tg_shift0_posdz_mm->SetMaximum(5.0);
  tg_shift0_posdz_mm->SetMinimum(-5.0);
  tg_shift0_posdz_mm->GetXaxis()->SetLimits(-10,522);
  tg_shift0_posdz_mm->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift0_posdz_mm->GetYaxis()->SetTitle("Residual shift (cm)");
  tg_shift0_posdz_mm->GetXaxis()->CenterTitle();
  tg_shift0_posdz_mm->GetYaxis()->CenterTitle();

  c1->Print("figure_shift0_posdz_mm_strip-by-strip.gif");
  c1->Print("figure_shift0_posdz_mm_strip-by-strip.eps");


  TGraphErrors *tg_shift0_negdz_mm = new TGraphErrors(512,stripid,shift0_negdz_mm,zero,zero);
  tg_shift0_negdz_mm->SetTitle("Run8, ++ field, negitive particles, tofwdz");
  tg_shift0_negdz_mm->SetMarkerStyle(20);
  tg_shift0_negdz_mm->SetMarkerColor(kBlack);
  tg_shift0_negdz_mm->Draw("AP");
  tg_shift0_negdz_mm->SetMaximum(5.0);
  tg_shift0_negdz_mm->SetMinimum(-5.0);
  tg_shift0_negdz_mm->GetXaxis()->SetLimits(-10,522);
  tg_shift0_negdz_mm->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift0_negdz_mm->GetYaxis()->SetTitle("Residual shift (cm)");
  tg_shift0_negdz_mm->GetXaxis()->CenterTitle();
  tg_shift0_negdz_mm->GetYaxis()->CenterTitle();

  c1->Print("figure_shift0_negdz_mm_strip-by-strip.gif");
  c1->Print("figure_shift0_negdz_mm_strip-by-strip.eps");


  TGraphErrors *tg_shift0_posdphi_mm = new TGraphErrors(512,stripid,shift0_posdphi_mm,zero,zero);
  tg_shift0_posdphi_mm->SetTitle("Run8, ++ field, positive particles, tofwdphi");
  tg_shift0_posdphi_mm->SetMarkerStyle(20);
  tg_shift0_posdphi_mm->SetMarkerColor(kBlack);
  tg_shift0_posdphi_mm->Draw("AP");
  tg_shift0_posdphi_mm->SetMaximum(0.01);
  tg_shift0_posdphi_mm->SetMinimum(-0.01);
  tg_shift0_posdphi_mm->GetXaxis()->SetLimits(-10,522);
  tg_shift0_posdphi_mm->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift0_posdphi_mm->GetYaxis()->SetTitle("Residual shift (rad)");
  tg_shift0_posdphi_mm->GetXaxis()->CenterTitle();
  tg_shift0_posdphi_mm->GetYaxis()->CenterTitle();

  c1->Print("figure_shift0_posdphi_mm_strip-by-strip.gif");
  c1->Print("figure_shift0_posdphi_mm_strip-by-strip.eps");


  TGraphErrors *tg_shift0_negdphi_mm = new TGraphErrors(512,stripid,shift0_negdphi_mm,zero,zero);
  tg_shift0_negdphi_mm->SetTitle("Run8, ++ field, negitive particles, tofwdphi");
  tg_shift0_negdphi_mm->SetMarkerStyle(20);
  tg_shift0_negdphi_mm->SetMarkerColor(kBlack);
  tg_shift0_negdphi_mm->Draw("AP");
  tg_shift0_negdphi_mm->SetMaximum(0.01);
  tg_shift0_negdphi_mm->SetMinimum(-0.01);
  tg_shift0_negdphi_mm->GetXaxis()->SetLimits(-10,522);
  tg_shift0_negdphi_mm->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift0_negdphi_mm->GetYaxis()->SetTitle("Residual shift (rad)");
  tg_shift0_negdphi_mm->GetXaxis()->CenterTitle();
  tg_shift0_negdphi_mm->GetYaxis()->CenterTitle();

  c1->Print("figure_shift0_negdphi_mm_strip-by-strip.gif");
  c1->Print("figure_shift0_negdphi_mm_strip-by-strip.eps");


  // ------------------ //
  // --- NOW SHIFT2 --- //
  // ------------------ //


  TGraphErrors *tg_shift2_posdz_mm = new TGraphErrors(512,stripid,shift2_posdz_mm,zero,zero);
  tg_shift2_posdz_mm->SetTitle("Run8, ++ field, positive particles, tofwdz");
  tg_shift2_posdz_mm->SetMarkerStyle(20);
  tg_shift2_posdz_mm->SetMarkerColor(kBlack);
  tg_shift2_posdz_mm->Draw("AP");
  tg_shift2_posdz_mm->SetMaximum(0.5);
  tg_shift2_posdz_mm->SetMinimum(-0.5);
  tg_shift2_posdz_mm->GetXaxis()->SetLimits(-10,522);
  tg_shift2_posdz_mm->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift2_posdz_mm->GetYaxis()->SetTitle("Residual shift (cm)");
  tg_shift2_posdz_mm->GetXaxis()->CenterTitle();
  tg_shift2_posdz_mm->GetYaxis()->CenterTitle();

  c1->Print("figure_shift2_posdz_mm_strip-by-strip.gif");
  c1->Print("figure_shift2_posdz_mm_strip-by-strip.eps");


  TGraphErrors *tg_shift2_negdz_mm = new TGraphErrors(512,stripid,shift2_negdz_mm,zero,zero);
  tg_shift2_negdz_mm->SetTitle("Run8, ++ field, negitive particles, tofwdz");
  tg_shift2_negdz_mm->SetMarkerStyle(20);
  tg_shift2_negdz_mm->SetMarkerColor(kBlack);
  tg_shift2_negdz_mm->Draw("AP");
  tg_shift2_negdz_mm->SetMaximum(0.5);
  tg_shift2_negdz_mm->SetMinimum(-0.5);
  tg_shift2_negdz_mm->GetXaxis()->SetLimits(-10,522);
  tg_shift2_negdz_mm->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift2_negdz_mm->GetYaxis()->SetTitle("Residual shift (cm)");
  tg_shift2_negdz_mm->GetXaxis()->CenterTitle();
  tg_shift2_negdz_mm->GetYaxis()->CenterTitle();

  c1->Print("figure_shift2_negdz_mm_strip-by-strip.gif");
  c1->Print("figure_shift2_negdz_mm_strip-by-strip.eps");


  TGraphErrors *tg_shift2_posdphi_mm = new TGraphErrors(512,stripid,shift2_posdphi_mm,zero,zero);
  tg_shift2_posdphi_mm->SetTitle("Run8, ++ field, positive particles, tofwdphi");
  tg_shift2_posdphi_mm->SetMarkerStyle(20);
  tg_shift2_posdphi_mm->SetMarkerColor(kBlack);
  tg_shift2_posdphi_mm->Draw("AP");
  tg_shift2_posdphi_mm->SetMaximum(0.001);
  tg_shift2_posdphi_mm->SetMinimum(-0.001);
  tg_shift2_posdphi_mm->GetXaxis()->SetLimits(-10,522);
  tg_shift2_posdphi_mm->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift2_posdphi_mm->GetYaxis()->SetTitle("Residual shift (rad)");
  tg_shift2_posdphi_mm->GetXaxis()->CenterTitle();
  tg_shift2_posdphi_mm->GetYaxis()->CenterTitle();

  c1->Print("figure_shift2_posdphi_mm_strip-by-strip.gif");
  c1->Print("figure_shift2_posdphi_mm_strip-by-strip.eps");


  TGraphErrors *tg_shift2_negdphi_mm = new TGraphErrors(512,stripid,shift2_negdphi_mm,zero,zero);
  tg_shift2_negdphi_mm->SetTitle("Run8, ++ field, negitive particles, tofwdphi");
  tg_shift2_negdphi_mm->SetMarkerStyle(20);
  tg_shift2_negdphi_mm->SetMarkerColor(kBlack);
  tg_shift2_negdphi_mm->Draw("AP");
  tg_shift2_negdphi_mm->SetMaximum(0.001);
  tg_shift2_negdphi_mm->SetMinimum(-0.001);
  tg_shift2_negdphi_mm->GetXaxis()->SetLimits(-10,522);
  tg_shift2_negdphi_mm->GetXaxis()->SetTitle("TOFW strip ID");
  tg_shift2_negdphi_mm->GetYaxis()->SetTitle("Residual shift (rad)");
  tg_shift2_negdphi_mm->GetXaxis()->CenterTitle();
  tg_shift2_negdphi_mm->GetYaxis()->CenterTitle();

  c1->Print("figure_shift2_negdphi_mm_strip-by-strip.gif");
  c1->Print("figure_shift2_negdphi_mm_strip-by-strip.eps");


}

void rawdraw()
{

  cout<<"starting!"<<endl;

  TCanvas *c1 = new TCanvas();
  c1->SetFillColor(kWhite);
  c1->SetBorderMode(0);
  c1->SetFrameFillColor(kWhite);
  c1->SetFrameBorderMode(0);
  c1->SetLogy();

  TFile *file = TFile::Open("outsum_low.root");
  //TFile *fpp = TFile::Open("outlow_plusplus.root");
  //TFile *fmm = TFile::Open("outlow_minusminus.root");



  // --- pions --- //

  // --------
  // --- dis0 

  //TH1F *hposdis0 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis");
  TH1F *hposdis0cent0020 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis_cent0020");
  TH1F *hposw1dis0cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_pos_0_dis_cent0020");
  TH1F *hposw2dis0cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_pos_0_dis_cent0020");
  TH1F *hposdis0cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis_cent2040");
  TH1F *hposw1dis0cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_pos_0_dis_cent2040");
  TH1F *hposw2dis0cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_pos_0_dis_cent2040");
  TH1F *hposdis0cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis_cent4060");
  TH1F *hposw1dis0cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_pos_0_dis_cent4060");
  TH1F *hposw2dis0cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_pos_0_dis_cent4060");
  TH1F *hposdis0cent6088 = (TH1F *)file->Get("ptpid_tofw_pos_0_dis_cent6088");
  TH1F *hposw1dis0cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_pos_0_dis_cent6088");
  TH1F *hposw2dis0cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_pos_0_dis_cent6088");

  //TH1F *hnegdis0 = (TH1F *)file->Get("ptpid_tofw_neg_0_dis");
  TH1F *hnegdis0cent0020 = (TH1F *)file->Get("ptpid_tofw_neg_0_dis_cent0020");
  TH1F *hnegw1dis0cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_neg_0_dis_cent0020");
  TH1F *hnegw2dis0cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_neg_0_dis_cent0020");
  TH1F *hnegdis0cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_0_dis_cent2040");
  TH1F *hnegw1dis0cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_neg_0_dis_cent2040");
  TH1F *hnegw2dis0cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_neg_0_dis_cent2040");
  TH1F *hnegdis0cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_0_dis_cent4060");
  TH1F *hnegw1dis0cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_neg_0_dis_cent4060");
  TH1F *hnegw2dis0cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_neg_0_dis_cent4060");
  TH1F *hnegdis0cent6088 = (TH1F *)file->Get("ptpid_tofw_neg_0_dis_cent6088");
  TH1F *hnegw1dis0cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_neg_0_dis_cent6088");
  TH1F *hnegw2dis0cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_neg_0_dis_cent6088");



  // --------
  // --- dis1

  //TH1F *hposdis1 = (TH1F *)file->Get("ptpid_tofw_pos_1_dis");
  TH1F *hposdis1cent0020 = (TH1F *)file->Get("ptpid_tofw_pos_1_dis_cent0020");
  TH1F *hposw1dis1cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_pos_1_dis_cent0020");
  TH1F *hposw2dis1cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_pos_1_dis_cent0020");
  TH1F *hposdis1cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_1_dis_cent2040");
  TH1F *hposw1dis1cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_pos_1_dis_cent2040");
  TH1F *hposw2dis1cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_pos_1_dis_cent2040");
  TH1F *hposdis1cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_1_dis_cent4060");
  TH1F *hposw1dis1cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_pos_1_dis_cent4060");
  TH1F *hposw2dis1cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_pos_1_dis_cent4060");
  TH1F *hposdis1cent6088 = (TH1F *)file->Get("ptpid_tofw_pos_1_dis_cent6088");
  TH1F *hposw1dis1cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_pos_1_dis_cent6088");
  TH1F *hposw2dis1cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_pos_1_dis_cent6088");

  //TH1F *hnegdis1 = (TH1F *)file->Get("ptpid_tofw_neg_1_dis");
  TH1F *hnegdis1cent0020 = (TH1F *)file->Get("ptpid_tofw_neg_1_dis_cent0020");
  TH1F *hnegw1dis1cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_neg_1_dis_cent0020");
  TH1F *hnegw2dis1cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_neg_1_dis_cent0020");
  TH1F *hnegdis1cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_1_dis_cent2040");
  TH1F *hnegw1dis1cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_neg_1_dis_cent2040");
  TH1F *hnegw2dis1cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_neg_1_dis_cent2040");
  TH1F *hnegdis1cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_1_dis_cent4060");
  TH1F *hnegw1dis1cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_neg_1_dis_cent4060");
  TH1F *hnegw2dis1cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_neg_1_dis_cent4060");
  TH1F *hnegdis1cent6088 = (TH1F *)file->Get("ptpid_tofw_neg_1_dis_cent6088");
  TH1F *hnegw1dis1cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_neg_1_dis_cent6088");
  TH1F *hnegw2dis1cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_neg_1_dis_cent6088");



  // --- kaons --- //

  // --------
  // --- dis2

  //TH1F *hposdis2 = (TH1F *)file->Get("ptpid_tofw_pos_2_dis");
  TH1F *hposdis2cent0020 = (TH1F *)file->Get("ptpid_tofw_pos_2_dis_cent0020");
  TH1F *hposw1dis2cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_pos_2_dis_cent0020");
  TH1F *hposw2dis2cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_pos_2_dis_cent0020");
  TH1F *hposdis2cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_2_dis_cent2040");
  TH1F *hposw1dis2cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_pos_2_dis_cent2040");
  TH1F *hposw2dis2cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_pos_2_dis_cent2040");
  TH1F *hposdis2cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_2_dis_cent4060");
  TH1F *hposw1dis2cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_pos_2_dis_cent4060");
  TH1F *hposw2dis2cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_pos_2_dis_cent4060");
  TH1F *hposdis2cent6088 = (TH1F *)file->Get("ptpid_tofw_pos_2_dis_cent6088");
  TH1F *hposw1dis2cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_pos_2_dis_cent6088");
  TH1F *hposw2dis2cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_pos_2_dis_cent6088");

  //TH1F *hnegdis2 = (TH1F *)file->Get("ptpid_tofw_neg_2_dis");
  TH1F *hnegdis2cent0020 = (TH1F *)file->Get("ptpid_tofw_neg_2_dis_cent0020");
  TH1F *hnegw1dis2cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_neg_2_dis_cent0020");
  TH1F *hnegw2dis2cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_neg_2_dis_cent0020");
  TH1F *hnegdis2cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_2_dis_cent2040");
  TH1F *hnegw1dis2cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_neg_2_dis_cent2040");
  TH1F *hnegw2dis2cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_neg_2_dis_cent2040");
  TH1F *hnegdis2cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_2_dis_cent4060");
  TH1F *hnegw1dis2cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_neg_2_dis_cent4060");
  TH1F *hnegw2dis2cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_neg_2_dis_cent4060");
  TH1F *hnegdis2cent6088 = (TH1F *)file->Get("ptpid_tofw_neg_2_dis_cent6088");
  TH1F *hnegw1dis2cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_neg_2_dis_cent6088");
  TH1F *hnegw2dis2cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_neg_2_dis_cent6088");



  // --------
  // --- dis3

  //TH1F *hposdis3 = (TH1F *)file->Get("ptpid_tofw_pos_3_dis");
  TH1F *hposdis3cent0020 = (TH1F *)file->Get("ptpid_tofw_pos_3_dis_cent0020");
  TH1F *hposw1dis3cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_pos_3_dis_cent0020");
  TH1F *hposw2dis3cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_pos_3_dis_cent0020");
  TH1F *hposdis3cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_3_dis_cent2040");
  TH1F *hposw1dis3cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_pos_3_dis_cent2040");
  TH1F *hposw2dis3cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_pos_3_dis_cent2040");
  TH1F *hposdis3cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_3_dis_cent4060");
  TH1F *hposw1dis3cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_pos_3_dis_cent4060");
  TH1F *hposw2dis3cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_pos_3_dis_cent4060");
  TH1F *hposdis3cent6088 = (TH1F *)file->Get("ptpid_tofw_pos_3_dis_cent6088");
  TH1F *hposw1dis3cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_pos_3_dis_cent6088");
  TH1F *hposw2dis3cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_pos_3_dis_cent6088");

  //TH1F *hnegdis3 = (TH1F *)file->Get("ptpid_tofw_neg_3_dis");
  TH1F *hnegdis3cent0020 = (TH1F *)file->Get("ptpid_tofw_neg_3_dis_cent0020");
  TH1F *hnegw1dis3cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_neg_3_dis_cent0020");
  TH1F *hnegw2dis3cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_neg_3_dis_cent0020");
  TH1F *hnegdis3cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_3_dis_cent2040");
  TH1F *hnegw1dis3cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_neg_3_dis_cent2040");
  TH1F *hnegw2dis3cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_neg_3_dis_cent2040");
  TH1F *hnegdis3cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_3_dis_cent4060");
  TH1F *hnegw1dis3cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_neg_3_dis_cent4060");
  TH1F *hnegw2dis3cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_neg_3_dis_cent4060");
  TH1F *hnegdis3cent6088 = (TH1F *)file->Get("ptpid_tofw_neg_3_dis_cent6088");
  TH1F *hnegw1dis3cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_neg_3_dis_cent6088");
  TH1F *hnegw2dis3cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_neg_3_dis_cent6088");



  // --- protons --- //

  // --------
  // --- dis4

  //TH1F *hposdis4 = (TH1F *)file->Get("ptpid_tofw_pos_4_dis");
  TH1F *hposdis4cent0020 = (TH1F *)file->Get("ptpid_tofw_pos_4_dis_cent0020");
  TH1F *hposw1dis4cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_pos_4_dis_cent0020");
  TH1F *hposw2dis4cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_pos_4_dis_cent0020");
  TH1F *hposdis4cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_4_dis_cent2040");
  TH1F *hposw1dis4cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_pos_4_dis_cent2040");
  TH1F *hposw2dis4cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_pos_4_dis_cent2040");
  TH1F *hposdis4cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_4_dis_cent4060");
  TH1F *hposw1dis4cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_pos_4_dis_cent4060");
  TH1F *hposw2dis4cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_pos_4_dis_cent4060");
  TH1F *hposdis4cent6088 = (TH1F *)file->Get("ptpid_tofw_pos_4_dis_cent6088");
  TH1F *hposw1dis4cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_pos_4_dis_cent6088");
  TH1F *hposw2dis4cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_pos_4_dis_cent6088");

  //TH1F *hnegdis4 = (TH1F *)file->Get("ptpid_tofw_neg_4_dis");
  TH1F *hnegdis4cent0020 = (TH1F *)file->Get("ptpid_tofw_neg_4_dis_cent0020");
  TH1F *hnegw1dis4cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_neg_4_dis_cent0020");
  TH1F *hnegw2dis4cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_neg_4_dis_cent0020");
  TH1F *hnegdis4cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_4_dis_cent2040");
  TH1F *hnegw1dis4cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_neg_4_dis_cent2040");
  TH1F *hnegw2dis4cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_neg_4_dis_cent2040");
  TH1F *hnegdis4cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_4_dis_cent4060");
  TH1F *hnegw1dis4cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_neg_4_dis_cent4060");
  TH1F *hnegw2dis4cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_neg_4_dis_cent4060");
  TH1F *hnegdis4cent6088 = (TH1F *)file->Get("ptpid_tofw_neg_4_dis_cent6088");
  TH1F *hnegw1dis4cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_neg_4_dis_cent6088");
  TH1F *hnegw2dis4cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_neg_4_dis_cent6088");



  // --------
  // --- dis5

  //TH1F *hposdis5 = (TH1F *)file->Get("ptpid_tofw_pos_5_dis");
  TH1F *hposdis5cent0020 = (TH1F *)file->Get("ptpid_tofw_pos_5_dis_cent0020");
  TH1F *hposw1dis5cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_pos_5_dis_cent0020");
  TH1F *hposw2dis5cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_pos_5_dis_cent0020");
  TH1F *hposdis5cent2040 = (TH1F *)file->Get("ptpid_tofw_pos_5_dis_cent2040");
  TH1F *hposw1dis5cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_pos_5_dis_cent2040");
  TH1F *hposw2dis5cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_pos_5_dis_cent2040");
  TH1F *hposdis5cent4060 = (TH1F *)file->Get("ptpid_tofw_pos_5_dis_cent4060");
  TH1F *hposw1dis5cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_pos_5_dis_cent4060");
  TH1F *hposw2dis5cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_pos_5_dis_cent4060");
  TH1F *hposdis5cent6088 = (TH1F *)file->Get("ptpid_tofw_pos_5_dis_cent6088");
  TH1F *hposw1dis5cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_pos_5_dis_cent6088");
  TH1F *hposw2dis5cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_pos_5_dis_cent6088");

  //TH1F *hnegdis5 = (TH1F *)file->Get("ptpid_tofw_neg_5_dis");
  TH1F *hnegdis5cent0020 = (TH1F *)file->Get("ptpid_tofw_neg_5_dis_cent0020");
  TH1F *hnegw1dis5cent0020 = (TH1F *)file->Get("ptpid_tofw_w1_neg_5_dis_cent0020");
  TH1F *hnegw2dis5cent0020 = (TH1F *)file->Get("ptpid_tofw_w2_neg_5_dis_cent0020");
  TH1F *hnegdis5cent2040 = (TH1F *)file->Get("ptpid_tofw_neg_5_dis_cent2040");
  TH1F *hnegw1dis5cent2040 = (TH1F *)file->Get("ptpid_tofw_w1_neg_5_dis_cent2040");
  TH1F *hnegw2dis5cent2040 = (TH1F *)file->Get("ptpid_tofw_w2_neg_5_dis_cent2040");
  TH1F *hnegdis5cent4060 = (TH1F *)file->Get("ptpid_tofw_neg_5_dis_cent4060");
  TH1F *hnegw1dis5cent4060 = (TH1F *)file->Get("ptpid_tofw_w1_neg_5_dis_cent4060");
  TH1F *hnegw2dis5cent4060 = (TH1F *)file->Get("ptpid_tofw_w2_neg_5_dis_cent4060");
  TH1F *hnegdis5cent6088 = (TH1F *)file->Get("ptpid_tofw_neg_5_dis_cent6088");
  TH1F *hnegw1dis5cent6088 = (TH1F *)file->Get("ptpid_tofw_w1_neg_5_dis_cent6088");
  TH1F *hnegw2dis5cent6088 = (TH1F *)file->Get("ptpid_tofw_w2_neg_5_dis_cent6088");








}

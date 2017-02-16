void simple()
{

  TFile *fcurrent = TFile::Open("current_pp.root");
  TFile *fbefore = TFile::Open("before_pp.root");

  TH1F *h_1_current = (TH1F *)fcurrent->Get("ptpid_tofw_pos_1_dis_cent0020");
  TH1F *h_1_before = (TH1F *)fbefore->Get("ptpid_tofw_pos_1_dis_cent0020");

  h_1_current->Divide(h_1_before);
  h_1_current->Draw();

  // TH1F *h_3_current = (TH1F *)fcurrent->Get("ptpid_tofw_pos_3_dis_cent0020");
  // TH1F *h_3_before = (TH1F *)fbefore->Get("ptpid_tofw_pos_3_dis_cent0020");

  // h_3_current->Divide(h_3_before);
  // h_3_current->Draw();

  // TH1F *h_5_current = (TH1F *)fcurrent->Get("ptpid_tofw_pos_5_dis_cent0020");
  // TH1F *h_5_before = (TH1F *)fbefore->Get("ptpid_tofw_pos_5_dis_cent0020");

  // h_5_current->Divide(h_5_before);
  // h_5_current->Draw();

}

// Author: Ron Belmont
// Date: 2010-05-17
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <map>
 
#include <sys/time.h>
 
#include "hadrontree.h"
 
#include "TROOT.h"
#include "TFile.h" 
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"

using namespace std;



const float phbeta  = 29.9792458;
const float mpion   = 0.13957;
const float mkaon   = 0.493677;
const float mproton = 0.938270;


map<string,int> myMap;
void GetRunIndex();

bool goodStrip(int i);

void fetchRunOffset();
void fetchStripOffset();
void fetchSlewingOffset();
void fetchMatching();

float stripoffset[512]; // 512 = number of strips
float runoffset[848]; // 848 = number of runs
float slewingoffset(int strip, float adc);

float Slewing_A[512];
float Slewing_B[512];

float mean_dz_pos_plusplus[512];
float mean_dz_neg_plusplus[512];
float mean_dphi_pos_plusplus[512];
float mean_dphi_neg_plusplus[512];
float mean_dz_pos_minusminus[512];
float mean_dz_neg_minusminus[512];
float mean_dphi_pos_minusminus[512];
float mean_dphi_neg_minusminus[512];

Long64_t nevents = 0;
Long64_t ntracks = 0;
Long64_t ngoodtofwevents = 0;
Long64_t ngoodtofwtracks = 0;
Long64_t ngoodtofwtracks_snglevent = 0;

float sigma_tofwdz(int charge, float mom, float tofwdz);
float sigma_tofwdphi(int charge, float mom, float tofwdphi);
float sigma_tofwdz_before(float mom, float tofwdz);
float sigma_tofwdphi_before(float mom, float tofwdphi);

float caltofwsdz(int run, int striptofw, int charge, float zed, float mom, float tofwdz);
float caltofwsdphi(int run, int striptofw, int charge, float zed, float mom, float tofwdphi);

//float recaltofwsdz(int run, int striptofw, int charge, float zed, float mom, float tofwsdz);
//float recaltofwsdphi(int run, int striptofw, int charge, float zed, float mom, float tofwsdphi);

float tunetofwsdz(int run, int charge, float mom, float cent, float tofwsdz);
float tunetofwsdphi(int run, int charge, float mom, float cent, float tofwsdphi);

//PID functions
float isPion(float pT, float m2tofw);
float isKaon(float pT, float m2tofw);
float isProton(float pT, float m2tofw);

float isPionE(float pT, float m2tofe);
float isKaonE(float pT, float m2tofe);
float isProtonE(float pT, float m2tofe);

bool GoodDCH(int run, float zed, float alpha, float phi);
bool GoodEdgeDCH(int run, float zed, float alpha, float phi);
bool GoodInnerDCH(int run, float zed, float alpha, float phi);

bool GoodPC1(float ppc1z, float ppc1phi);
bool GoodPC2(float pc2z, float pc2phi);
bool GoodPC3(float pc3z, float pc3phi);
bool NewGoodPC1(float ppc1z, float ppc1phi);
bool NewGoodPC2(float pc2z, float pc2phi);
bool NewGoodPC3(float pc3z, float pc3phi);

// Main part of program
int main() 
{ 

  Char_t inFile[100];
  Char_t outFile[100];

  cout<<"Now beginning program"<<endl;
  cout<<"Please enter input file name"<<endl;
  cin>>inFile;
  cout<<"Input file is "<<inFile<<endl;
  cout<<"Please enter output file name"<<endl;
  cin>>outFile;
  cout<<"Output file is "<<outFile<<endl;

  // ----------------------------

  struct timeval Time;

  gettimeofday(&Time,0);
  int begintime = Time.tv_sec;
  //cout<<"begintime is "<<begintime<<endl;

  // ----------------------------

  TFile *mData = new TFile(outFile,"recreate"); // declare output file

  GetRunIndex(); // get runindex from data file
  fetchRunOffset(); // get the run-by-run timing offsets
  fetchStripOffset(); // get the strip-by-strip timing offsets
  fetchSlewingOffset(); // get the slewing correction
  fetchMatching(); // get the strip-by-strip matching correction

  // -------------------------- //
  // --- Declare histograms --- //
  // -------------------------- //

  // ----------------- //
  // --- new stuff --- //
  // ----------------- //


  TH2F *spech_pc3sdz_cpos_zposA = new TH2F("pc3sdz_cpos_zposA","pc3sdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdz_cneg_zposA = new TH2F("pc3sdz_cneg_zposA","pc3sdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdphi_cpos_zposA = new TH2F("pc3sdphi_cpos_zposA","pc3sdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdphi_cneg_zposA = new TH2F("pc3sdphi_cneg_zposA","pc3sdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);

  TH2F *spech_pc3sdz_cpos_zposB = new TH2F("pc3sdz_cpos_zposB","pc3sdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdz_cneg_zposB = new TH2F("pc3sdz_cneg_zposB","pc3sdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdphi_cpos_zposB = new TH2F("pc3sdphi_cpos_zposB","pc3sdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdphi_cneg_zposB = new TH2F("pc3sdphi_cneg_zposB","pc3sdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);

  TH2F *spech_pc3sdz_cpos_znegA = new TH2F("pc3sdz_cpos_znegA","pc3sdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdz_cneg_znegA = new TH2F("pc3sdz_cneg_znegA","pc3sdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdphi_cpos_znegA = new TH2F("pc3sdphi_cpos_znegA","pc3sdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdphi_cneg_znegA = new TH2F("pc3sdphi_cneg_znegA","pc3sdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);

  TH2F *spech_pc3sdz_cpos_znegB = new TH2F("pc3sdz_cpos_znegB","pc3sdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdz_cneg_znegB = new TH2F("pc3sdz_cneg_znegB","pc3sdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdphi_cpos_znegB = new TH2F("pc3sdphi_cpos_znegB","pc3sdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *spech_pc3sdphi_cneg_znegB = new TH2F("pc3sdphi_cneg_znegB","pc3sdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);

  TH2F *pc3sdz_pT_dis_pos = new TH2F("pc3sdz_pT_dis_pos","pc3sdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *pc3sdz_pT_dis_neg = new TH2F("pc3sdz_pT_dis_neg","pc3sdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *pc3sdphi_pT_dis_pos = new TH2F("pc3sdphi_pT_dis_pos","pc3sdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *pc3sdphi_pT_dis_neg = new TH2F("pc3sdphi_pT_dis_neg","pc3sdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *pc3sdz_cent_dis_pos = new TH2F("pc3sdz_cent_dis_pos","pc3sdz vs cent", 100, 0, 100, 100, -5.0, 5.0);
  TH2F *pc3sdz_cent_dis_neg = new TH2F("pc3sdz_cent_dis_neg","pc3sdz vs cent", 100, 0, 100, 100, -5.0, 5.0);
  TH2F *pc3sdphi_cent_dis_pos = new TH2F("pc3sdphi_cent_dis_pos","pc3sdphi vs cent", 100, 0, 100, 100, -5.0, 5.0);
  TH2F *pc3sdphi_cent_dis_neg = new TH2F("pc3sdphi_cent_dis_neg","pc3sdphi vs cent", 100, 0, 100, 100, -5.0, 5.0);

  TH2F *tofwsdz_pT_dis_pos = new TH2F("tofwsdz_pT_dis_pos","tofwsdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *tofwsdz_pT_dis_neg = new TH2F("tofwsdz_pT_dis_neg","tofwsdz vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *tofwsdphi_pT_dis_pos = new TH2F("tofwsdphi_pT_dis_pos","tofwsdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *tofwsdphi_pT_dis_neg = new TH2F("tofwsdphi_pT_dis_neg","tofwsdphi vs pT", 100, 0, 10, 100, -5.0, 5.0);
  TH2F *tofwsdz_cent_dis_pos = new TH2F("tofwsdz_cent_dis_pos","tofwsdz vs cent", 100, 0, 100, 100, -5.0, 5.0);
  TH2F *tofwsdz_cent_dis_neg = new TH2F("tofwsdz_cent_dis_neg","tofwsdz vs cent", 100, 0, 100, 100, -5.0, 5.0);
  TH2F *tofwsdphi_cent_dis_pos = new TH2F("tofwsdphi_cent_dis_pos","tofwsdphi vs cent", 100, 0, 100, 100, -5.0, 5.0);
  TH2F *tofwsdphi_cent_dis_neg = new TH2F("tofwsdphi_cent_dis_neg","tofwsdphi vs cent", 100, 0, 100, 100, -5.0, 5.0);

  // ----------------- //
  // ---           --- //
  // ----------------- //

  // ---

  TH1F *deltatdis_east = new TH1F("deltatdis_east","deltatdis",800, -2, 2);
  TH1F *deltatdis = new TH1F("deltatdis","deltatdis",800, -2, 2);

  TH1F *etofdis = new TH1F("etofdis","etofdis",500,0,0.05);
  TH1F *qtofwdis = new TH1F("qtofwdis","qtofwdis",1000,0,1000);
  TH1F *tofwadcupdis = new TH1F("tofwadcupdis","tofwadcupdis",1000,0,1000);
  TH1F *tofwadcdwdis = new TH1F("tofwadcdwdis","tofwadcdwdis",1000,0,1000);

  TH2F *deltatrunedis = new TH2F("deltatrunedis","deltatrunedis", 850, 0, 850, 800, -2, 2);
  TH2F *deltatslatdis = new TH2F("deltatslatdis","deltatslatdis", 960, 0, 960, 800, -2, 2);
  TH2F *deltatrundis = new TH2F("deltatrundis","deltatrundis", 850, 0, 850, 800, -2, 2);
  TH2F *deltatstriptofwdis = new TH2F("deltatstriptofwdis","deltatstriptofwdis", 512, 0, 512, 800, -2, 2);

  TH2F *deltatslewingdis_q = new TH2F("deltatslewingdis_q","slewing (qtofw) distribution", 1000, 0, 1000, 800, -2, 2);




  TH2F *m2mom_dis         = new TH2F("m2mom_dis", "mom vs m2",  160, -8.0, 8.0, 300, -1.0, 2.0);
  TH2F *m2mompos_dis      = new TH2F("m2mompos_dis", "mom vs m2",  80, 0.0, 8.0, 300, -1.0, 2.0);
  TH2F *m2momneg_dis      = new TH2F("m2momneg_dis", "mom vs m2",  80, 0.0, 8.0, 300, -1.0, 2.0);

  TH2F *m2pTdis_pos         = new TH2F("m2pTdis_pos", "mom vs m2",  80, 0.0, 8.0, 300, -1.0, 2.0);
  TH2F *m2pTdis_neg         = new TH2F("m2pTdis_neg", "mom vs m2",  80, 0.0, 8.0, 300, -1.0, 2.0);
  TH2F *m2pTdis_pos_east    = new TH2F("m2pTdis_pos_east", "mom vs m2",  80, 0.0, 8.0, 300, -1.0, 2.0);
  TH2F *m2pTdis_neg_east    = new TH2F("m2pTdis_neg_east", "mom vs m2",  80, 0.0, 8.0, 300, -1.0, 2.0);

  //TH2F *ttofwmom_dis         = new TH2F("ttofwmom_dis", "mom vs ttofw",  160, -8.0, 8.0, 500, -2.0, 4.0);
  TH2F *ttofwmompos_dis      = new TH2F("ttofwmompos_dis", "mom vs ttofw",  80, 0.0, 8.0, 500, -2.0, 4.0);
  TH2F *ttofwmomneg_dis      = new TH2F("ttofwmomneg_dis", "mom vs ttofw",  80, 0.0, 8.0, 500, -2.0, 4.0);

  //TH2F *ttofemom_dis         = new TH2F("ttofemom_dis", "mom vs ttofe",  160, -8.0, 8.0, 500, -2.0, 4.0);
  TH2F *ttofemompos_dis      = new TH2F("ttofemompos_dis", "mom vs ttofe",  80, 0.0, 8.0, 500, -2.0, 4.0);
  TH2F *ttofemomneg_dis      = new TH2F("ttofemomneg_dis", "mom vs ttofe",  80, 0.0, 8.0, 500, -2.0, 4.0);





  // ---------------------------- //
  // --- begin sys histograms --- //
  // ---------------------------- //

  TH1F *ptsys_pion_pos_tfwmA = new TH1F("ptsys_pion_pos_tfwmA", "pion pos sys tfwm A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_tfwmA = new TH1F("ptsys_kaon_pos_tfwmA", "kaon pos sys tfwm A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_tfwmA = new TH1F("ptsys_prot_pos_tfwmA", "prot pos sys tfwm A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_pc3mA = new TH1F("ptsys_pion_pos_pc3mA", "pion pos sys pc3m A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_pc3mA = new TH1F("ptsys_kaon_pos_pc3mA", "kaon pos sys pc3m A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_pc3mA = new TH1F("ptsys_prot_pos_pc3mA", "prot pos sys pc3m A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_pc3fA = new TH1F("ptsys_pion_pos_pc3fA", "pion pos sys pc3f A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_pc3fA = new TH1F("ptsys_kaon_pos_pc3fA", "kaon pos sys pc3f A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_pc3fA = new TH1F("ptsys_prot_pos_pc3fA", "prot pos sys pc3f A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_pc1fA = new TH1F("ptsys_pion_pos_pc1fA", "pion pos sys pc1f A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_pc1fA = new TH1F("ptsys_kaon_pos_pc1fA", "kaon pos sys pc1f A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_pc1fA = new TH1F("ptsys_prot_pos_pc1fA", "prot pos sys pc1f A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_gadcA = new TH1F("ptsys_pion_pos_gadcA", "pion pos sys gadc A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_gadcA = new TH1F("ptsys_kaon_pos_gadcA", "kaon pos sys gadc A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_gadcA = new TH1F("ptsys_prot_pos_gadcA", "prot pos sys gadc A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_dcfcA = new TH1F("ptsys_pion_pos_dcfcA", "pion pos sys dcfc A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_dcfcA = new TH1F("ptsys_kaon_pos_dcfcA", "kaon pos sys dcfc A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_dcfcA = new TH1F("ptsys_prot_pos_dcfcA", "prot pos sys dcfc A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_dzedA = new TH1F("ptsys_pion_pos_dzedA", "pion pos sys dzed A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_dzedA = new TH1F("ptsys_kaon_pos_dzedA", "kaon pos sys dzed A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_dzedA = new TH1F("ptsys_prot_pos_dzedA", "prot pos sys dzed A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_spidA = new TH1F("ptsys_pion_pos_spidA", "pion pos sys spid A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_spidA = new TH1F("ptsys_kaon_pos_spidA", "kaon pos sys spid A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_spidA = new TH1F("ptsys_prot_pos_spidA", "prot pos sys spid A", 100, 0.0, 10.0);

  TH1F *ptsys_pion_pos_tfwmB = new TH1F("ptsys_pion_pos_tfwmB", "pion pos sys tfwm B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_tfwmB = new TH1F("ptsys_kaon_pos_tfwmB", "kaon pos sys tfwm B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_tfwmB = new TH1F("ptsys_prot_pos_tfwmB", "prot pos sys tfwm B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_pc3mB = new TH1F("ptsys_pion_pos_pc3mB", "pion pos sys pc3m B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_pc3mB = new TH1F("ptsys_kaon_pos_pc3mB", "kaon pos sys pc3m B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_pc3mB = new TH1F("ptsys_prot_pos_pc3mB", "prot pos sys pc3m B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_pc3fB = new TH1F("ptsys_pion_pos_pc3fB", "pion pos sys pc3f B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_pc3fB = new TH1F("ptsys_kaon_pos_pc3fB", "kaon pos sys pc3f B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_pc3fB = new TH1F("ptsys_prot_pos_pc3fB", "prot pos sys pc3f B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_pc1fB = new TH1F("ptsys_pion_pos_pc1fB", "pion pos sys pc1f B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_pc1fB = new TH1F("ptsys_kaon_pos_pc1fB", "kaon pos sys pc1f B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_pc1fB = new TH1F("ptsys_prot_pos_pc1fB", "prot pos sys pc1f B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_gadcB = new TH1F("ptsys_pion_pos_gadcB", "pion pos sys gadc B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_gadcB = new TH1F("ptsys_kaon_pos_gadcB", "kaon pos sys gadc B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_gadcB = new TH1F("ptsys_prot_pos_gadcB", "prot pos sys gadc B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_dcfcB = new TH1F("ptsys_pion_pos_dcfcB", "pion pos sys dcfc B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_dcfcB = new TH1F("ptsys_kaon_pos_dcfcB", "kaon pos sys dcfc B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_dcfcB = new TH1F("ptsys_prot_pos_dcfcB", "prot pos sys dcfc B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_dzedB = new TH1F("ptsys_pion_pos_dzedB", "pion pos sys dzed B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_dzedB = new TH1F("ptsys_kaon_pos_dzedB", "kaon pos sys dzed B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_dzedB = new TH1F("ptsys_prot_pos_dzedB", "prot pos sys dzed B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_pos_spidB = new TH1F("ptsys_pion_pos_spidB", "pion pos sys spid B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_pos_spidB = new TH1F("ptsys_kaon_pos_spidB", "kaon pos sys spid B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_pos_spidB = new TH1F("ptsys_prot_pos_spidB", "prot pos sys spid B", 100, 0.0, 10.0);

  TH1F *ptsys_pion_neg_tfwmA = new TH1F("ptsys_pion_neg_tfwmA", "pion neg sys tfwm A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_tfwmA = new TH1F("ptsys_kaon_neg_tfwmA", "kaon neg sys tfwm A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_tfwmA = new TH1F("ptsys_prot_neg_tfwmA", "prot neg sys tfwm A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_pc3mA = new TH1F("ptsys_pion_neg_pc3mA", "pion neg sys pc3m A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_pc3mA = new TH1F("ptsys_kaon_neg_pc3mA", "kaon neg sys pc3m A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_pc3mA = new TH1F("ptsys_prot_neg_pc3mA", "prot neg sys pc3m A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_pc3fA = new TH1F("ptsys_pion_neg_pc3fA", "pion neg sys pc3f A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_pc3fA = new TH1F("ptsys_kaon_neg_pc3fA", "kaon neg sys pc3f A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_pc3fA = new TH1F("ptsys_prot_neg_pc3fA", "prot neg sys pc3f A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_pc1fA = new TH1F("ptsys_pion_neg_pc1fA", "pion neg sys pc1f A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_pc1fA = new TH1F("ptsys_kaon_neg_pc1fA", "kaon neg sys pc1f A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_pc1fA = new TH1F("ptsys_prot_neg_pc1fA", "prot neg sys pc1f A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_gadcA = new TH1F("ptsys_pion_neg_gadcA", "pion neg sys gadc A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_gadcA = new TH1F("ptsys_kaon_neg_gadcA", "kaon neg sys gadc A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_gadcA = new TH1F("ptsys_prot_neg_gadcA", "prot neg sys gadc A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_dcfcA = new TH1F("ptsys_pion_neg_dcfcA", "pion neg sys dcfc A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_dcfcA = new TH1F("ptsys_kaon_neg_dcfcA", "kaon neg sys dcfc A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_dcfcA = new TH1F("ptsys_prot_neg_dcfcA", "prot neg sys dcfc A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_dzedA = new TH1F("ptsys_pion_neg_dzedA", "pion neg sys dzed A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_dzedA = new TH1F("ptsys_kaon_neg_dzedA", "kaon neg sys dzed A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_dzedA = new TH1F("ptsys_prot_neg_dzedA", "prot neg sys dzed A", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_spidA = new TH1F("ptsys_pion_neg_spidA", "pion neg sys spid A", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_spidA = new TH1F("ptsys_kaon_neg_spidA", "kaon neg sys spid A", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_spidA = new TH1F("ptsys_prot_neg_spidA", "prot neg sys spid A", 100, 0.0, 10.0);

  TH1F *ptsys_pion_neg_tfwmB = new TH1F("ptsys_pion_neg_tfwmB", "pion neg sys tfwm B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_tfwmB = new TH1F("ptsys_kaon_neg_tfwmB", "kaon neg sys tfwm B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_tfwmB = new TH1F("ptsys_prot_neg_tfwmB", "prot neg sys tfwm B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_pc3mB = new TH1F("ptsys_pion_neg_pc3mB", "pion neg sys pc3m B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_pc3mB = new TH1F("ptsys_kaon_neg_pc3mB", "kaon neg sys pc3m B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_pc3mB = new TH1F("ptsys_prot_neg_pc3mB", "prot neg sys pc3m B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_pc3fB = new TH1F("ptsys_pion_neg_pc3fB", "pion neg sys pc3f B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_pc3fB = new TH1F("ptsys_kaon_neg_pc3fB", "kaon neg sys pc3f B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_pc3fB = new TH1F("ptsys_prot_neg_pc3fB", "prot neg sys pc3f B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_pc1fB = new TH1F("ptsys_pion_neg_pc1fB", "pion neg sys pc1f B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_pc1fB = new TH1F("ptsys_kaon_neg_pc1fB", "kaon neg sys pc1f B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_pc1fB = new TH1F("ptsys_prot_neg_pc1fB", "prot neg sys pc1f B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_gadcB = new TH1F("ptsys_pion_neg_gadcB", "pion neg sys gadc B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_gadcB = new TH1F("ptsys_kaon_neg_gadcB", "kaon neg sys gadc B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_gadcB = new TH1F("ptsys_prot_neg_gadcB", "prot neg sys gadc B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_dcfcB = new TH1F("ptsys_pion_neg_dcfcB", "pion neg sys dcfc B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_dcfcB = new TH1F("ptsys_kaon_neg_dcfcB", "kaon neg sys dcfc B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_dcfcB = new TH1F("ptsys_prot_neg_dcfcB", "prot neg sys dcfc B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_dzedB = new TH1F("ptsys_pion_neg_dzedB", "pion neg sys dzed B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_dzedB = new TH1F("ptsys_kaon_neg_dzedB", "kaon neg sys dzed B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_dzedB = new TH1F("ptsys_prot_neg_dzedB", "prot neg sys dzed B", 100, 0.0, 10.0);
  TH1F *ptsys_pion_neg_spidB = new TH1F("ptsys_pion_neg_spidB", "pion neg sys spid B", 100, 0.0, 10.0);
  TH1F *ptsys_kaon_neg_spidB = new TH1F("ptsys_kaon_neg_spidB", "kaon neg sys spid B", 100, 0.0, 10.0);
  TH1F *ptsys_prot_neg_spidB = new TH1F("ptsys_prot_neg_spidB", "prot neg sys spid B", 100, 0.0, 10.0);

  // -------------------------- //
  // --- end sys histograms --- //
  // -------------------------- //

  // -------------------------- //
  // --- now pid histograms --- //
  // -------------------------- //

  TH1F *ptpid_tofw_pos_0_dis = new TH1F("ptpid_tofw_pos_0_dis", "tofw 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_1_dis = new TH1F("ptpid_tofw_pos_1_dis", "tofw 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_2_dis = new TH1F("ptpid_tofw_pos_2_dis", "tofw 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_3_dis = new TH1F("ptpid_tofw_pos_3_dis", "tofw 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_4_dis = new TH1F("ptpid_tofw_pos_4_dis", "tofw 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_5_dis = new TH1F("ptpid_tofw_pos_5_dis", "tofw 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_neg_0_dis = new TH1F("ptpid_tofw_neg_0_dis", "tofw 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_1_dis = new TH1F("ptpid_tofw_neg_1_dis", "tofw 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_2_dis = new TH1F("ptpid_tofw_neg_2_dis", "tofw 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_3_dis = new TH1F("ptpid_tofw_neg_3_dis", "tofw 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_4_dis = new TH1F("ptpid_tofw_neg_4_dis", "tofw 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_5_dis = new TH1F("ptpid_tofw_neg_5_dis", "tofw 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w1_pos_0_dis = new TH1F("ptpid_tofw_w1_pos_0_dis", "tofw_w1 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_1_dis = new TH1F("ptpid_tofw_w1_pos_1_dis", "tofw_w1 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_2_dis = new TH1F("ptpid_tofw_w1_pos_2_dis", "tofw_w1 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_3_dis = new TH1F("ptpid_tofw_w1_pos_3_dis", "tofw_w1 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_4_dis = new TH1F("ptpid_tofw_w1_pos_4_dis", "tofw_w1 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_5_dis = new TH1F("ptpid_tofw_w1_pos_5_dis", "tofw_w1 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w1_neg_0_dis = new TH1F("ptpid_tofw_w1_neg_0_dis", "tofw_w1 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_1_dis = new TH1F("ptpid_tofw_w1_neg_1_dis", "tofw_w1 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_2_dis = new TH1F("ptpid_tofw_w1_neg_2_dis", "tofw_w1 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_3_dis = new TH1F("ptpid_tofw_w1_neg_3_dis", "tofw_w1 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_4_dis = new TH1F("ptpid_tofw_w1_neg_4_dis", "tofw_w1 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_5_dis = new TH1F("ptpid_tofw_w1_neg_5_dis", "tofw_w1 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w2_pos_0_dis = new TH1F("ptpid_tofw_w2_pos_0_dis", "tofw_w2 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_1_dis = new TH1F("ptpid_tofw_w2_pos_1_dis", "tofw_w2 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_2_dis = new TH1F("ptpid_tofw_w2_pos_2_dis", "tofw_w2 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_3_dis = new TH1F("ptpid_tofw_w2_pos_3_dis", "tofw_w2 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_4_dis = new TH1F("ptpid_tofw_w2_pos_4_dis", "tofw_w2 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_5_dis = new TH1F("ptpid_tofw_w2_pos_5_dis", "tofw_w2 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w2_neg_0_dis = new TH1F("ptpid_tofw_w2_neg_0_dis", "tofw_w2 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_1_dis = new TH1F("ptpid_tofw_w2_neg_1_dis", "tofw_w2 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_2_dis = new TH1F("ptpid_tofw_w2_neg_2_dis", "tofw_w2 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_3_dis = new TH1F("ptpid_tofw_w2_neg_3_dis", "tofw_w2 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_4_dis = new TH1F("ptpid_tofw_w2_neg_4_dis", "tofw_w2 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_5_dis = new TH1F("ptpid_tofw_w2_neg_5_dis", "tofw_w2 5 neg pr asym", 100, 0.0, 10.0);

  // ---
  // ---
  // ---

  TH1F *ptpid_tofw_pos_0_dis_cent0088 = new TH1F("ptpid_tofw_pos_0_dis_cent0088", "tofw 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_1_dis_cent0088 = new TH1F("ptpid_tofw_pos_1_dis_cent0088", "tofw 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_2_dis_cent0088 = new TH1F("ptpid_tofw_pos_2_dis_cent0088", "tofw 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_3_dis_cent0088 = new TH1F("ptpid_tofw_pos_3_dis_cent0088", "tofw 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_4_dis_cent0088 = new TH1F("ptpid_tofw_pos_4_dis_cent0088", "tofw 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_5_dis_cent0088 = new TH1F("ptpid_tofw_pos_5_dis_cent0088", "tofw 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_neg_0_dis_cent0088 = new TH1F("ptpid_tofw_neg_0_dis_cent0088", "tofw 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_1_dis_cent0088 = new TH1F("ptpid_tofw_neg_1_dis_cent0088", "tofw 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_2_dis_cent0088 = new TH1F("ptpid_tofw_neg_2_dis_cent0088", "tofw 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_3_dis_cent0088 = new TH1F("ptpid_tofw_neg_3_dis_cent0088", "tofw 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_4_dis_cent0088 = new TH1F("ptpid_tofw_neg_4_dis_cent0088", "tofw 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_5_dis_cent0088 = new TH1F("ptpid_tofw_neg_5_dis_cent0088", "tofw 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_pos_0_dis_cent0020 = new TH1F("ptpid_tofw_pos_0_dis_cent0020", "tofw 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_1_dis_cent0020 = new TH1F("ptpid_tofw_pos_1_dis_cent0020", "tofw 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_2_dis_cent0020 = new TH1F("ptpid_tofw_pos_2_dis_cent0020", "tofw 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_3_dis_cent0020 = new TH1F("ptpid_tofw_pos_3_dis_cent0020", "tofw 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_4_dis_cent0020 = new TH1F("ptpid_tofw_pos_4_dis_cent0020", "tofw 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_5_dis_cent0020 = new TH1F("ptpid_tofw_pos_5_dis_cent0020", "tofw 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_neg_0_dis_cent0020 = new TH1F("ptpid_tofw_neg_0_dis_cent0020", "tofw 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_1_dis_cent0020 = new TH1F("ptpid_tofw_neg_1_dis_cent0020", "tofw 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_2_dis_cent0020 = new TH1F("ptpid_tofw_neg_2_dis_cent0020", "tofw 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_3_dis_cent0020 = new TH1F("ptpid_tofw_neg_3_dis_cent0020", "tofw 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_4_dis_cent0020 = new TH1F("ptpid_tofw_neg_4_dis_cent0020", "tofw 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_5_dis_cent0020 = new TH1F("ptpid_tofw_neg_5_dis_cent0020", "tofw 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_pos_0_dis_cent2040 = new TH1F("ptpid_tofw_pos_0_dis_cent2040", "tofw 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_1_dis_cent2040 = new TH1F("ptpid_tofw_pos_1_dis_cent2040", "tofw 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_2_dis_cent2040 = new TH1F("ptpid_tofw_pos_2_dis_cent2040", "tofw 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_3_dis_cent2040 = new TH1F("ptpid_tofw_pos_3_dis_cent2040", "tofw 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_4_dis_cent2040 = new TH1F("ptpid_tofw_pos_4_dis_cent2040", "tofw 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_5_dis_cent2040 = new TH1F("ptpid_tofw_pos_5_dis_cent2040", "tofw 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_neg_0_dis_cent2040 = new TH1F("ptpid_tofw_neg_0_dis_cent2040", "tofw 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_1_dis_cent2040 = new TH1F("ptpid_tofw_neg_1_dis_cent2040", "tofw 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_2_dis_cent2040 = new TH1F("ptpid_tofw_neg_2_dis_cent2040", "tofw 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_3_dis_cent2040 = new TH1F("ptpid_tofw_neg_3_dis_cent2040", "tofw 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_4_dis_cent2040 = new TH1F("ptpid_tofw_neg_4_dis_cent2040", "tofw 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_5_dis_cent2040 = new TH1F("ptpid_tofw_neg_5_dis_cent2040", "tofw 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_pos_0_dis_cent4060 = new TH1F("ptpid_tofw_pos_0_dis_cent4060", "tofw 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_1_dis_cent4060 = new TH1F("ptpid_tofw_pos_1_dis_cent4060", "tofw 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_2_dis_cent4060 = new TH1F("ptpid_tofw_pos_2_dis_cent4060", "tofw 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_3_dis_cent4060 = new TH1F("ptpid_tofw_pos_3_dis_cent4060", "tofw 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_4_dis_cent4060 = new TH1F("ptpid_tofw_pos_4_dis_cent4060", "tofw 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_5_dis_cent4060 = new TH1F("ptpid_tofw_pos_5_dis_cent4060", "tofw 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_neg_0_dis_cent4060 = new TH1F("ptpid_tofw_neg_0_dis_cent4060", "tofw 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_1_dis_cent4060 = new TH1F("ptpid_tofw_neg_1_dis_cent4060", "tofw 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_2_dis_cent4060 = new TH1F("ptpid_tofw_neg_2_dis_cent4060", "tofw 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_3_dis_cent4060 = new TH1F("ptpid_tofw_neg_3_dis_cent4060", "tofw 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_4_dis_cent4060 = new TH1F("ptpid_tofw_neg_4_dis_cent4060", "tofw 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_5_dis_cent4060 = new TH1F("ptpid_tofw_neg_5_dis_cent4060", "tofw 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_pos_0_dis_cent6088 = new TH1F("ptpid_tofw_pos_0_dis_cent6088", "tofw 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_1_dis_cent6088 = new TH1F("ptpid_tofw_pos_1_dis_cent6088", "tofw 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_2_dis_cent6088 = new TH1F("ptpid_tofw_pos_2_dis_cent6088", "tofw 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_3_dis_cent6088 = new TH1F("ptpid_tofw_pos_3_dis_cent6088", "tofw 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_4_dis_cent6088 = new TH1F("ptpid_tofw_pos_4_dis_cent6088", "tofw 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_pos_5_dis_cent6088 = new TH1F("ptpid_tofw_pos_5_dis_cent6088", "tofw 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_neg_0_dis_cent6088 = new TH1F("ptpid_tofw_neg_0_dis_cent6088", "tofw 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_1_dis_cent6088 = new TH1F("ptpid_tofw_neg_1_dis_cent6088", "tofw 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_2_dis_cent6088 = new TH1F("ptpid_tofw_neg_2_dis_cent6088", "tofw 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_3_dis_cent6088 = new TH1F("ptpid_tofw_neg_3_dis_cent6088", "tofw 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_4_dis_cent6088 = new TH1F("ptpid_tofw_neg_4_dis_cent6088", "tofw 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_neg_5_dis_cent6088 = new TH1F("ptpid_tofw_neg_5_dis_cent6088", "tofw 5 neg pr asym", 100, 0.0, 10.0);

  // ---
  // ---
  // ---

  TH1F *ptpid_tofw_w1_pos_0_dis_cent0088 = new TH1F("ptpid_tofw_w1_pos_0_dis_cent0088", "tofw_w1 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_1_dis_cent0088 = new TH1F("ptpid_tofw_w1_pos_1_dis_cent0088", "tofw_w1 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_2_dis_cent0088 = new TH1F("ptpid_tofw_w1_pos_2_dis_cent0088", "tofw_w1 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_3_dis_cent0088 = new TH1F("ptpid_tofw_w1_pos_3_dis_cent0088", "tofw_w1 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_4_dis_cent0088 = new TH1F("ptpid_tofw_w1_pos_4_dis_cent0088", "tofw_w1 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_5_dis_cent0088 = new TH1F("ptpid_tofw_w1_pos_5_dis_cent0088", "tofw_w1 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w1_neg_0_dis_cent0088 = new TH1F("ptpid_tofw_w1_neg_0_dis_cent0088", "tofw_w1 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_1_dis_cent0088 = new TH1F("ptpid_tofw_w1_neg_1_dis_cent0088", "tofw_w1 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_2_dis_cent0088 = new TH1F("ptpid_tofw_w1_neg_2_dis_cent0088", "tofw_w1 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_3_dis_cent0088 = new TH1F("ptpid_tofw_w1_neg_3_dis_cent0088", "tofw_w1 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_4_dis_cent0088 = new TH1F("ptpid_tofw_w1_neg_4_dis_cent0088", "tofw_w1 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_5_dis_cent0088 = new TH1F("ptpid_tofw_w1_neg_5_dis_cent0088", "tofw_w1 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w1_pos_0_dis_cent0020 = new TH1F("ptpid_tofw_w1_pos_0_dis_cent0020", "tofw_w1 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_1_dis_cent0020 = new TH1F("ptpid_tofw_w1_pos_1_dis_cent0020", "tofw_w1 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_2_dis_cent0020 = new TH1F("ptpid_tofw_w1_pos_2_dis_cent0020", "tofw_w1 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_3_dis_cent0020 = new TH1F("ptpid_tofw_w1_pos_3_dis_cent0020", "tofw_w1 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_4_dis_cent0020 = new TH1F("ptpid_tofw_w1_pos_4_dis_cent0020", "tofw_w1 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_5_dis_cent0020 = new TH1F("ptpid_tofw_w1_pos_5_dis_cent0020", "tofw_w1 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w1_neg_0_dis_cent0020 = new TH1F("ptpid_tofw_w1_neg_0_dis_cent0020", "tofw_w1 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_1_dis_cent0020 = new TH1F("ptpid_tofw_w1_neg_1_dis_cent0020", "tofw_w1 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_2_dis_cent0020 = new TH1F("ptpid_tofw_w1_neg_2_dis_cent0020", "tofw_w1 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_3_dis_cent0020 = new TH1F("ptpid_tofw_w1_neg_3_dis_cent0020", "tofw_w1 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_4_dis_cent0020 = new TH1F("ptpid_tofw_w1_neg_4_dis_cent0020", "tofw_w1 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_5_dis_cent0020 = new TH1F("ptpid_tofw_w1_neg_5_dis_cent0020", "tofw_w1 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w1_pos_0_dis_cent2040 = new TH1F("ptpid_tofw_w1_pos_0_dis_cent2040", "tofw_w1 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_1_dis_cent2040 = new TH1F("ptpid_tofw_w1_pos_1_dis_cent2040", "tofw_w1 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_2_dis_cent2040 = new TH1F("ptpid_tofw_w1_pos_2_dis_cent2040", "tofw_w1 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_3_dis_cent2040 = new TH1F("ptpid_tofw_w1_pos_3_dis_cent2040", "tofw_w1 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_4_dis_cent2040 = new TH1F("ptpid_tofw_w1_pos_4_dis_cent2040", "tofw_w1 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_5_dis_cent2040 = new TH1F("ptpid_tofw_w1_pos_5_dis_cent2040", "tofw_w1 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w1_neg_0_dis_cent2040 = new TH1F("ptpid_tofw_w1_neg_0_dis_cent2040", "tofw_w1 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_1_dis_cent2040 = new TH1F("ptpid_tofw_w1_neg_1_dis_cent2040", "tofw_w1 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_2_dis_cent2040 = new TH1F("ptpid_tofw_w1_neg_2_dis_cent2040", "tofw_w1 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_3_dis_cent2040 = new TH1F("ptpid_tofw_w1_neg_3_dis_cent2040", "tofw_w1 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_4_dis_cent2040 = new TH1F("ptpid_tofw_w1_neg_4_dis_cent2040", "tofw_w1 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_5_dis_cent2040 = new TH1F("ptpid_tofw_w1_neg_5_dis_cent2040", "tofw_w1 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w1_pos_0_dis_cent4060 = new TH1F("ptpid_tofw_w1_pos_0_dis_cent4060", "tofw_w1 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_1_dis_cent4060 = new TH1F("ptpid_tofw_w1_pos_1_dis_cent4060", "tofw_w1 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_2_dis_cent4060 = new TH1F("ptpid_tofw_w1_pos_2_dis_cent4060", "tofw_w1 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_3_dis_cent4060 = new TH1F("ptpid_tofw_w1_pos_3_dis_cent4060", "tofw_w1 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_4_dis_cent4060 = new TH1F("ptpid_tofw_w1_pos_4_dis_cent4060", "tofw_w1 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_5_dis_cent4060 = new TH1F("ptpid_tofw_w1_pos_5_dis_cent4060", "tofw_w1 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w1_neg_0_dis_cent4060 = new TH1F("ptpid_tofw_w1_neg_0_dis_cent4060", "tofw_w1 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_1_dis_cent4060 = new TH1F("ptpid_tofw_w1_neg_1_dis_cent4060", "tofw_w1 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_2_dis_cent4060 = new TH1F("ptpid_tofw_w1_neg_2_dis_cent4060", "tofw_w1 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_3_dis_cent4060 = new TH1F("ptpid_tofw_w1_neg_3_dis_cent4060", "tofw_w1 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_4_dis_cent4060 = new TH1F("ptpid_tofw_w1_neg_4_dis_cent4060", "tofw_w1 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_5_dis_cent4060 = new TH1F("ptpid_tofw_w1_neg_5_dis_cent4060", "tofw_w1 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w1_pos_0_dis_cent6088 = new TH1F("ptpid_tofw_w1_pos_0_dis_cent6088", "tofw_w1 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_1_dis_cent6088 = new TH1F("ptpid_tofw_w1_pos_1_dis_cent6088", "tofw_w1 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_2_dis_cent6088 = new TH1F("ptpid_tofw_w1_pos_2_dis_cent6088", "tofw_w1 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_3_dis_cent6088 = new TH1F("ptpid_tofw_w1_pos_3_dis_cent6088", "tofw_w1 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_4_dis_cent6088 = new TH1F("ptpid_tofw_w1_pos_4_dis_cent6088", "tofw_w1 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_pos_5_dis_cent6088 = new TH1F("ptpid_tofw_w1_pos_5_dis_cent6088", "tofw_w1 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w1_neg_0_dis_cent6088 = new TH1F("ptpid_tofw_w1_neg_0_dis_cent6088", "tofw_w1 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_1_dis_cent6088 = new TH1F("ptpid_tofw_w1_neg_1_dis_cent6088", "tofw_w1 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_2_dis_cent6088 = new TH1F("ptpid_tofw_w1_neg_2_dis_cent6088", "tofw_w1 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_3_dis_cent6088 = new TH1F("ptpid_tofw_w1_neg_3_dis_cent6088", "tofw_w1 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_4_dis_cent6088 = new TH1F("ptpid_tofw_w1_neg_4_dis_cent6088", "tofw_w1 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w1_neg_5_dis_cent6088 = new TH1F("ptpid_tofw_w1_neg_5_dis_cent6088", "tofw_w1 5 neg pr asym", 100, 0.0, 10.0);

  // ---
  // ---
  // ---

  TH1F *ptpid_tofw_w2_pos_0_dis_cent0088 = new TH1F("ptpid_tofw_w2_pos_0_dis_cent0088", "tofw_w2 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_1_dis_cent0088 = new TH1F("ptpid_tofw_w2_pos_1_dis_cent0088", "tofw_w2 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_2_dis_cent0088 = new TH1F("ptpid_tofw_w2_pos_2_dis_cent0088", "tofw_w2 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_3_dis_cent0088 = new TH1F("ptpid_tofw_w2_pos_3_dis_cent0088", "tofw_w2 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_4_dis_cent0088 = new TH1F("ptpid_tofw_w2_pos_4_dis_cent0088", "tofw_w2 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_5_dis_cent0088 = new TH1F("ptpid_tofw_w2_pos_5_dis_cent0088", "tofw_w2 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w2_neg_0_dis_cent0088 = new TH1F("ptpid_tofw_w2_neg_0_dis_cent0088", "tofw_w2 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_1_dis_cent0088 = new TH1F("ptpid_tofw_w2_neg_1_dis_cent0088", "tofw_w2 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_2_dis_cent0088 = new TH1F("ptpid_tofw_w2_neg_2_dis_cent0088", "tofw_w2 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_3_dis_cent0088 = new TH1F("ptpid_tofw_w2_neg_3_dis_cent0088", "tofw_w2 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_4_dis_cent0088 = new TH1F("ptpid_tofw_w2_neg_4_dis_cent0088", "tofw_w2 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_5_dis_cent0088 = new TH1F("ptpid_tofw_w2_neg_5_dis_cent0088", "tofw_w2 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w2_pos_0_dis_cent0020 = new TH1F("ptpid_tofw_w2_pos_0_dis_cent0020", "tofw_w2 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_1_dis_cent0020 = new TH1F("ptpid_tofw_w2_pos_1_dis_cent0020", "tofw_w2 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_2_dis_cent0020 = new TH1F("ptpid_tofw_w2_pos_2_dis_cent0020", "tofw_w2 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_3_dis_cent0020 = new TH1F("ptpid_tofw_w2_pos_3_dis_cent0020", "tofw_w2 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_4_dis_cent0020 = new TH1F("ptpid_tofw_w2_pos_4_dis_cent0020", "tofw_w2 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_5_dis_cent0020 = new TH1F("ptpid_tofw_w2_pos_5_dis_cent0020", "tofw_w2 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w2_neg_0_dis_cent0020 = new TH1F("ptpid_tofw_w2_neg_0_dis_cent0020", "tofw_w2 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_1_dis_cent0020 = new TH1F("ptpid_tofw_w2_neg_1_dis_cent0020", "tofw_w2 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_2_dis_cent0020 = new TH1F("ptpid_tofw_w2_neg_2_dis_cent0020", "tofw_w2 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_3_dis_cent0020 = new TH1F("ptpid_tofw_w2_neg_3_dis_cent0020", "tofw_w2 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_4_dis_cent0020 = new TH1F("ptpid_tofw_w2_neg_4_dis_cent0020", "tofw_w2 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_5_dis_cent0020 = new TH1F("ptpid_tofw_w2_neg_5_dis_cent0020", "tofw_w2 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w2_pos_0_dis_cent2040 = new TH1F("ptpid_tofw_w2_pos_0_dis_cent2040", "tofw_w2 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_1_dis_cent2040 = new TH1F("ptpid_tofw_w2_pos_1_dis_cent2040", "tofw_w2 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_2_dis_cent2040 = new TH1F("ptpid_tofw_w2_pos_2_dis_cent2040", "tofw_w2 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_3_dis_cent2040 = new TH1F("ptpid_tofw_w2_pos_3_dis_cent2040", "tofw_w2 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_4_dis_cent2040 = new TH1F("ptpid_tofw_w2_pos_4_dis_cent2040", "tofw_w2 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_5_dis_cent2040 = new TH1F("ptpid_tofw_w2_pos_5_dis_cent2040", "tofw_w2 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w2_neg_0_dis_cent2040 = new TH1F("ptpid_tofw_w2_neg_0_dis_cent2040", "tofw_w2 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_1_dis_cent2040 = new TH1F("ptpid_tofw_w2_neg_1_dis_cent2040", "tofw_w2 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_2_dis_cent2040 = new TH1F("ptpid_tofw_w2_neg_2_dis_cent2040", "tofw_w2 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_3_dis_cent2040 = new TH1F("ptpid_tofw_w2_neg_3_dis_cent2040", "tofw_w2 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_4_dis_cent2040 = new TH1F("ptpid_tofw_w2_neg_4_dis_cent2040", "tofw_w2 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_5_dis_cent2040 = new TH1F("ptpid_tofw_w2_neg_5_dis_cent2040", "tofw_w2 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w2_pos_0_dis_cent4060 = new TH1F("ptpid_tofw_w2_pos_0_dis_cent4060", "tofw_w2 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_1_dis_cent4060 = new TH1F("ptpid_tofw_w2_pos_1_dis_cent4060", "tofw_w2 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_2_dis_cent4060 = new TH1F("ptpid_tofw_w2_pos_2_dis_cent4060", "tofw_w2 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_3_dis_cent4060 = new TH1F("ptpid_tofw_w2_pos_3_dis_cent4060", "tofw_w2 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_4_dis_cent4060 = new TH1F("ptpid_tofw_w2_pos_4_dis_cent4060", "tofw_w2 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_5_dis_cent4060 = new TH1F("ptpid_tofw_w2_pos_5_dis_cent4060", "tofw_w2 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w2_neg_0_dis_cent4060 = new TH1F("ptpid_tofw_w2_neg_0_dis_cent4060", "tofw_w2 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_1_dis_cent4060 = new TH1F("ptpid_tofw_w2_neg_1_dis_cent4060", "tofw_w2 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_2_dis_cent4060 = new TH1F("ptpid_tofw_w2_neg_2_dis_cent4060", "tofw_w2 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_3_dis_cent4060 = new TH1F("ptpid_tofw_w2_neg_3_dis_cent4060", "tofw_w2 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_4_dis_cent4060 = new TH1F("ptpid_tofw_w2_neg_4_dis_cent4060", "tofw_w2 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_5_dis_cent4060 = new TH1F("ptpid_tofw_w2_neg_5_dis_cent4060", "tofw_w2 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w2_pos_0_dis_cent6088 = new TH1F("ptpid_tofw_w2_pos_0_dis_cent6088", "tofw_w2 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_1_dis_cent6088 = new TH1F("ptpid_tofw_w2_pos_1_dis_cent6088", "tofw_w2 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_2_dis_cent6088 = new TH1F("ptpid_tofw_w2_pos_2_dis_cent6088", "tofw_w2 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_3_dis_cent6088 = new TH1F("ptpid_tofw_w2_pos_3_dis_cent6088", "tofw_w2 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_4_dis_cent6088 = new TH1F("ptpid_tofw_w2_pos_4_dis_cent6088", "tofw_w2 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_pos_5_dis_cent6088 = new TH1F("ptpid_tofw_w2_pos_5_dis_cent6088", "tofw_w2 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofw_w2_neg_0_dis_cent6088 = new TH1F("ptpid_tofw_w2_neg_0_dis_cent6088", "tofw_w2 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_1_dis_cent6088 = new TH1F("ptpid_tofw_w2_neg_1_dis_cent6088", "tofw_w2 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_2_dis_cent6088 = new TH1F("ptpid_tofw_w2_neg_2_dis_cent6088", "tofw_w2 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_3_dis_cent6088 = new TH1F("ptpid_tofw_w2_neg_3_dis_cent6088", "tofw_w2 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_4_dis_cent6088 = new TH1F("ptpid_tofw_w2_neg_4_dis_cent6088", "tofw_w2 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofw_w2_neg_5_dis_cent6088 = new TH1F("ptpid_tofw_w2_neg_5_dis_cent6088", "tofw_w2 5 neg pr asym", 100, 0.0, 10.0);

  // ---
  // ---
  // ---







  TH1F *ptpid_tofe_pos_0_dis = new TH1F("ptpid_tofe_pos_0_dis", "tofe 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_1_dis = new TH1F("ptpid_tofe_pos_1_dis", "tofe 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_2_dis = new TH1F("ptpid_tofe_pos_2_dis", "tofe 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_3_dis = new TH1F("ptpid_tofe_pos_3_dis", "tofe 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_4_dis = new TH1F("ptpid_tofe_pos_4_dis", "tofe 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_5_dis = new TH1F("ptpid_tofe_pos_5_dis", "tofe 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofe_neg_0_dis = new TH1F("ptpid_tofe_neg_0_dis", "tofe 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_1_dis = new TH1F("ptpid_tofe_neg_1_dis", "tofe 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_2_dis = new TH1F("ptpid_tofe_neg_2_dis", "tofe 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_3_dis = new TH1F("ptpid_tofe_neg_3_dis", "tofe 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_4_dis = new TH1F("ptpid_tofe_neg_4_dis", "tofe 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_5_dis = new TH1F("ptpid_tofe_neg_5_dis", "tofe 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofe_pos_0_dis_cent0088 = new TH1F("ptpid_tofe_pos_0_dis_cent0088", "tofe 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_1_dis_cent0088 = new TH1F("ptpid_tofe_pos_1_dis_cent0088", "tofe 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_2_dis_cent0088 = new TH1F("ptpid_tofe_pos_2_dis_cent0088", "tofe 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_3_dis_cent0088 = new TH1F("ptpid_tofe_pos_3_dis_cent0088", "tofe 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_4_dis_cent0088 = new TH1F("ptpid_tofe_pos_4_dis_cent0088", "tofe 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_5_dis_cent0088 = new TH1F("ptpid_tofe_pos_5_dis_cent0088", "tofe 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofe_neg_0_dis_cent0088 = new TH1F("ptpid_tofe_neg_0_dis_cent0088", "tofe 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_1_dis_cent0088 = new TH1F("ptpid_tofe_neg_1_dis_cent0088", "tofe 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_2_dis_cent0088 = new TH1F("ptpid_tofe_neg_2_dis_cent0088", "tofe 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_3_dis_cent0088 = new TH1F("ptpid_tofe_neg_3_dis_cent0088", "tofe 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_4_dis_cent0088 = new TH1F("ptpid_tofe_neg_4_dis_cent0088", "tofe 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_5_dis_cent0088 = new TH1F("ptpid_tofe_neg_5_dis_cent0088", "tofe 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofe_pos_0_dis_cent0020 = new TH1F("ptpid_tofe_pos_0_dis_cent0020", "tofe 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_1_dis_cent0020 = new TH1F("ptpid_tofe_pos_1_dis_cent0020", "tofe 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_2_dis_cent0020 = new TH1F("ptpid_tofe_pos_2_dis_cent0020", "tofe 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_3_dis_cent0020 = new TH1F("ptpid_tofe_pos_3_dis_cent0020", "tofe 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_4_dis_cent0020 = new TH1F("ptpid_tofe_pos_4_dis_cent0020", "tofe 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_5_dis_cent0020 = new TH1F("ptpid_tofe_pos_5_dis_cent0020", "tofe 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofe_neg_0_dis_cent0020 = new TH1F("ptpid_tofe_neg_0_dis_cent0020", "tofe 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_1_dis_cent0020 = new TH1F("ptpid_tofe_neg_1_dis_cent0020", "tofe 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_2_dis_cent0020 = new TH1F("ptpid_tofe_neg_2_dis_cent0020", "tofe 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_3_dis_cent0020 = new TH1F("ptpid_tofe_neg_3_dis_cent0020", "tofe 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_4_dis_cent0020 = new TH1F("ptpid_tofe_neg_4_dis_cent0020", "tofe 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_5_dis_cent0020 = new TH1F("ptpid_tofe_neg_5_dis_cent0020", "tofe 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofe_pos_0_dis_cent2040 = new TH1F("ptpid_tofe_pos_0_dis_cent2040", "tofe 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_1_dis_cent2040 = new TH1F("ptpid_tofe_pos_1_dis_cent2040", "tofe 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_2_dis_cent2040 = new TH1F("ptpid_tofe_pos_2_dis_cent2040", "tofe 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_3_dis_cent2040 = new TH1F("ptpid_tofe_pos_3_dis_cent2040", "tofe 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_4_dis_cent2040 = new TH1F("ptpid_tofe_pos_4_dis_cent2040", "tofe 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_5_dis_cent2040 = new TH1F("ptpid_tofe_pos_5_dis_cent2040", "tofe 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofe_neg_0_dis_cent2040 = new TH1F("ptpid_tofe_neg_0_dis_cent2040", "tofe 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_1_dis_cent2040 = new TH1F("ptpid_tofe_neg_1_dis_cent2040", "tofe 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_2_dis_cent2040 = new TH1F("ptpid_tofe_neg_2_dis_cent2040", "tofe 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_3_dis_cent2040 = new TH1F("ptpid_tofe_neg_3_dis_cent2040", "tofe 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_4_dis_cent2040 = new TH1F("ptpid_tofe_neg_4_dis_cent2040", "tofe 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_5_dis_cent2040 = new TH1F("ptpid_tofe_neg_5_dis_cent2040", "tofe 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofe_pos_0_dis_cent4060 = new TH1F("ptpid_tofe_pos_0_dis_cent4060", "tofe 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_1_dis_cent4060 = new TH1F("ptpid_tofe_pos_1_dis_cent4060", "tofe 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_2_dis_cent4060 = new TH1F("ptpid_tofe_pos_2_dis_cent4060", "tofe 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_3_dis_cent4060 = new TH1F("ptpid_tofe_pos_3_dis_cent4060", "tofe 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_4_dis_cent4060 = new TH1F("ptpid_tofe_pos_4_dis_cent4060", "tofe 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_5_dis_cent4060 = new TH1F("ptpid_tofe_pos_5_dis_cent4060", "tofe 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofe_neg_0_dis_cent4060 = new TH1F("ptpid_tofe_neg_0_dis_cent4060", "tofe 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_1_dis_cent4060 = new TH1F("ptpid_tofe_neg_1_dis_cent4060", "tofe 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_2_dis_cent4060 = new TH1F("ptpid_tofe_neg_2_dis_cent4060", "tofe 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_3_dis_cent4060 = new TH1F("ptpid_tofe_neg_3_dis_cent4060", "tofe 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_4_dis_cent4060 = new TH1F("ptpid_tofe_neg_4_dis_cent4060", "tofe 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_5_dis_cent4060 = new TH1F("ptpid_tofe_neg_5_dis_cent4060", "tofe 5 neg pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofe_pos_0_dis_cent6088 = new TH1F("ptpid_tofe_pos_0_dis_cent6088", "tofe 0 pos pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_1_dis_cent6088 = new TH1F("ptpid_tofe_pos_1_dis_cent6088", "tofe 1 pos pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_2_dis_cent6088 = new TH1F("ptpid_tofe_pos_2_dis_cent6088", "tofe 2 pos ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_3_dis_cent6088 = new TH1F("ptpid_tofe_pos_3_dis_cent6088", "tofe 3 pos ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_4_dis_cent6088 = new TH1F("ptpid_tofe_pos_4_dis_cent6088", "tofe 4 pos pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_pos_5_dis_cent6088 = new TH1F("ptpid_tofe_pos_5_dis_cent6088", "tofe 5 pos pr asym", 100, 0.0, 10.0);

  TH1F *ptpid_tofe_neg_0_dis_cent6088 = new TH1F("ptpid_tofe_neg_0_dis_cent6088", "tofe 0 neg pi  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_1_dis_cent6088 = new TH1F("ptpid_tofe_neg_1_dis_cent6088", "tofe 1 neg pi asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_2_dis_cent6088 = new TH1F("ptpid_tofe_neg_2_dis_cent6088", "tofe 2 neg ka  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_3_dis_cent6088 = new TH1F("ptpid_tofe_neg_3_dis_cent6088", "tofe 3 neg ka asym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_4_dis_cent6088 = new TH1F("ptpid_tofe_neg_4_dis_cent6088", "tofe 4 neg pr  sym", 100, 0.0, 10.0);
  TH1F *ptpid_tofe_neg_5_dis_cent6088 = new TH1F("ptpid_tofe_neg_5_dis_cent6088", "tofe 5 neg pr asym", 100, 0.0, 10.0);




  // DC fiducial maps

  TH2F *hh_alphaphi_poszed_nc_FW = new TH2F("hh_alphaphi_poszed_nc_FW","alpha vs phi zed>0 no cuts", 920, -0.22, 0.7, 420, -0.21, 0.21);
  TH2F *hh_alphaphi_negzed_nc_FW = new TH2F("hh_alphaphi_negzed_nc_FW","alpha vs phi zed<0 no cuts", 920, -0.22, 0.7, 420, -0.21, 0.21);
  TH2F *hh_alphaphi_poszed_mc_FW = new TH2F("hh_alphaphi_poszed_mc_FW","alpha vs phi zed>0 matching cuts", 920, -0.22, 0.7, 420, -0.21, 0.21);
  TH2F *hh_alphaphi_negzed_mc_FW = new TH2F("hh_alphaphi_negzed_mc_FW","alpha vs phi zed<0 matching cuts", 920, -0.22, 0.7, 420, -0.21, 0.21);
  TH2F *hh_alphaphi_poszed_ec_FW = new TH2F("hh_alphaphi_poszed_ec_FW","alpha vs phi zed>0 edge cuts", 920, -0.22, 0.7, 420, -0.21, 0.21);
  TH2F *hh_alphaphi_negzed_ec_FW = new TH2F("hh_alphaphi_negzed_ec_FW","alpha vs phi zed<0 edge cuts", 920, -0.22, 0.7, 420, -0.21, 0.21);
  TH2F *hh_alphaphi_poszed_ac_FW = new TH2F("hh_alphaphi_poszed_ac_FW","alpha vs phi zed>0 all cuts", 920, -0.22, 0.7, 420, -0.21, 0.21);
  TH2F *hh_alphaphi_negzed_ac_FW = new TH2F("hh_alphaphi_negzed_ac_FW","alpha vs phi zed<0 all cuts", 920, -0.22, 0.7, 420, -0.21, 0.21);

  TH2F *hh_alphaphi_poszed_nc_EAST = new TH2F("hh_alphaphi_poszed_nc_EAST","alpha vs phi zed>0 no cuts", 1500, 2.5, 4.0, 1200, -0.6, 0.6);
  TH2F *hh_alphaphi_negzed_nc_EAST = new TH2F("hh_alphaphi_negzed_nc_EAST","alpha vs phi zed<0 no cuts", 1500, 2.5, 4.0, 1200, -0.6, 0.6);
  TH2F *hh_alphaphi_poszed_mc_EAST = new TH2F("hh_alphaphi_poszed_mc_EAST","alpha vs phi zed>0 matching cuts", 1500, 2.5, 4.0, 1200, -0.6, 0.6);
  TH2F *hh_alphaphi_negzed_mc_EAST = new TH2F("hh_alphaphi_negzed_mc_EAST","alpha vs phi zed<0 matching cuts", 1500, 2.5, 4.0, 1200, -0.6, 0.6);
  TH2F *hh_alphaphi_poszed_ec_EAST = new TH2F("hh_alphaphi_poszed_ec_EAST","alpha vs phi zed>0 edge cuts", 1500, 2.5, 4.0, 1200, -0.6, 0.6);
  TH2F *hh_alphaphi_negzed_ec_EAST = new TH2F("hh_alphaphi_negzed_ec_EAST","alpha vs phi zed<0 edge cuts", 1500, 2.5, 4.0, 1200, -0.6, 0.6);
  TH2F *hh_alphaphi_poszed_ac_EAST = new TH2F("hh_alphaphi_poszed_ac_EAST","alpha vs phi zed>0 all cuts", 1500, 2.5, 4.0, 1200, -0.6, 0.6);
  TH2F *hh_alphaphi_negzed_ac_EAST = new TH2F("hh_alphaphi_negzed_ac_EAST","alpha vs phi zed<0 all cuts", 1500, 2.5, 4.0, 1200, -0.6, 0.6);



  // no cuts
  // zed>0
  TH2F *hh_alphaphi_poszed_nc = new TH2F("hh_alphaphi_poszed_nc","alpha vs phi zed>0 no cuts", 1500, -0.5, 1.0, 1200, -0.6, 0.6);
  TH2F *hh_pos_momphi_poszed_nc = new TH2F("hh_pos_momphi_poszed_nc","pT vs phi zed>0 no cuts", 1500, -0.5, 1.0, 100, 0, 10);
  TH2F *hh_neg_momphi_poszed_nc = new TH2F("hh_neg_momphi_poszed_nc","pT vs phi zed>0 no cuts", 1500, -0.5, 1.0, 100, 0, 10);
  // zed<0
  TH2F *hh_alphaphi_negzed_nc = new TH2F("hh_alphaphi_negzed_nc","alpha vs phi zed<0 no cuts", 1500, -0.5, 1.0, 1200, -0.6, 0.6);
  TH2F *hh_pos_momphi_negzed_nc = new TH2F("hh_pos_momphi_negzed_nc","pT vs phi zed<0 no cuts", 1500, -0.5, 1.0, 100, 0, 10);
  TH2F *hh_neg_momphi_negzed_nc = new TH2F("hh_neg_momphi_negzed_nc","pT vs phi zed<0 no cuts", 1500, -0.5, 1.0, 100, 0, 10);

  // matching cuts
  // zed>0
  TH2F *hh_alphaphi_poszed_mc = new TH2F("hh_alphaphi_poszed_mc","alpha vs phi zed>0 matching cuts", 1500, -0.5, 1.0, 1200, -0.6, 0.6);
  TH2F *hh_pos_momphi_poszed_mc = new TH2F("hh_pos_momphi_poszed_mc","pT vs phi zed>0 matching cuts", 1500, -0.5, 1.0, 100, 0, 10);
  TH2F *hh_neg_momphi_poszed_mc = new TH2F("hh_neg_momphi_poszed_mc","pT vs phi zed>0 matching cuts", 1500, -0.5, 1.0, 100, 0, 10);
  // zed<0
  TH2F *hh_alphaphi_negzed_mc = new TH2F("hh_alphaphi_negzed_mc","alpha vs phi zed<0 matching cuts", 1500, -0.5, 1.0, 1200, -0.6, 0.6);
  TH2F *hh_pos_momphi_negzed_mc = new TH2F("hh_pos_momphi_negzed_mc","pT vs phi zed<0 matching cuts", 1500, -0.5, 1.0, 100, 0, 10);
  TH2F *hh_neg_momphi_negzed_mc = new TH2F("hh_neg_momphi_negzed_mc","pT vs phi zed<0 matching cuts", 1500, -0.5, 1.0, 100, 0, 10);

  // edge cuts
  // zed>0
  TH2F *hh_alphaphi_poszed_ec = new TH2F("hh_alphaphi_poszed_ec","alpha vs phi zed>0 edge cuts", 1500, -0.5, 1.0, 1200, -0.6, 0.6);
  TH2F *hh_pos_momphi_poszed_ec = new TH2F("hh_pos_momphi_poszed_ec","pT vs phi zed>0 edge cuts", 1500, -0.5, 1.0, 100, 0, 10);
  TH2F *hh_neg_momphi_poszed_ec = new TH2F("hh_neg_momphi_poszed_ec","pT vs phi zed>0 edge cuts", 1500, -0.5, 1.0, 100, 0, 10);
  // zed<0
  TH2F *hh_alphaphi_negzed_ec = new TH2F("hh_alphaphi_negzed_ec","alpha vs phi zed<0 edge cuts", 1500, -0.5, 1.0, 1200, -0.6, 0.6);
  TH2F *hh_pos_momphi_negzed_ec = new TH2F("hh_pos_momphi_negzed_ec","pT vs phi zed<0 edge cuts", 1500, -0.5, 1.0, 100, 0, 10);
  TH2F *hh_neg_momphi_negzed_ec = new TH2F("hh_neg_momphi_negzed_ec","pT vs phi zed<0 edge cuts", 1500, -0.5, 1.0, 100, 0, 10);

  // all cuts
  // zed>0
  TH2F *hh_alphaphi_poszed_ac = new TH2F("hh_alphaphi_poszed_ac","alpha vs phi zed>0 all cuts", 1500, -0.5, 1.0, 1200, -0.6, 0.6);
  TH2F *hh_pos_momphi_poszed_ac = new TH2F("hh_pos_momphi_poszed_ac","pT vs phi zed>0 all cuts", 1500, -0.5, 1.0, 100, 0, 10);
  TH2F *hh_neg_momphi_poszed_ac = new TH2F("hh_neg_momphi_poszed_ac","pT vs phi zed>0 all cuts", 1500, -0.5, 1.0, 100, 0, 10);
  // zed<0
  TH2F *hh_alphaphi_negzed_ac = new TH2F("hh_alphaphi_negzed_ac","alpha vs phi zed<0 all cuts", 1500, -0.5, 1.0, 1200, -0.6, 0.6);
  TH2F *hh_pos_momphi_negzed_ac = new TH2F("hh_pos_momphi_negzed_ac","pT vs phi zed<0 all cuts", 1500, -0.5, 1.0, 100, 0, 10);
  TH2F *hh_neg_momphi_negzed_ac = new TH2F("hh_neg_momphi_negzed_ac","pT vs phi zed<0 all cuts", 1500, -0.5, 1.0, 100, 0, 10);



  // dc zed vs phi
  TH2F *hh_zedphi_nc = new TH2F("hh_zedphi_nc","phi vs zed no cuts", 160, -80, 80, 1300, -0.4, 0.9);
  TH2F *hh_zedphi_mc = new TH2F("hh_zedphi_mc","phi vs zed matching cuts", 160, -80, 80, 1300, -0.4, 0.9);
  TH2F *hh_zedphi_ec = new TH2F("hh_zedphi_ec","phi vs zed edge cuts", 160, -80, 80, 1300, -0.4, 0.9);
  TH2F *hh_zedphi_ac = new TH2F("hh_zedphi_ac","phi vs zed all cuts", 160, -80, 80, 1300, -0.4, 0.9);


  TH2F *PC1ZedPhiDisWest  = new TH2F("PC1ZedPhiDisWest", "PC1 phi vs zed FC", 400, -200, 200, 800, -0.6, 1.0);
  TH2F *PC2ZedPhiDisWest  = new TH2F("PC2ZedPhiDisWest", "PC2 phi vs zed FC", 400, -200, 200, 800, -0.6, 1.0);
  TH2F *PC3ZedPhiDisWest  = new TH2F("PC3ZedPhiDisWest", "PC3 phi vs zed FC", 400, -200, 200, 800, -0.6, 1.0);
  TH2F *PC1ZedPhiDisEast  = new TH2F("PC1ZedPhiDisEast", "PC1 phi vs zed FC", 400, -200, 200, 800, 2.55, 4.15);
  TH2F *PC3ZedPhiDisEast  = new TH2F("PC3ZedPhiDisEast", "PC3 phi vs zed FC", 400, -200, 200, 800, 2.55, 4.15);
  TH2F *PC1ZedPhiDisWest_After  = new TH2F("PC1ZedPhiDisWest_After", "PC1 phi vs zed FC", 400, -200, 200, 800, -0.6, 1.0);
  TH2F *PC2ZedPhiDisWest_After  = new TH2F("PC2ZedPhiDisWest_After", "PC2 phi vs zed FC", 400, -200, 200, 800, -0.6, 1.0);
  TH2F *PC3ZedPhiDisWest_After  = new TH2F("PC3ZedPhiDisWest_After", "PC3 phi vs zed FC", 400, -200, 200, 800, -0.6, 1.0);
  TH2F *PC1ZedPhiDisEast_After  = new TH2F("PC1ZedPhiDisEast_After", "PC1 phi vs zed FC", 400, -200, 200, 800, 2.55, 4.15);
  TH2F *PC3ZedPhiDisEast_After  = new TH2F("PC3ZedPhiDisEast_After", "PC3 phi vs zed FC", 400, -200, 200, 800, 2.55, 4.15);



  // tofw fiducial histograms
  TH2F *TOFWZedPhiDis  = new TH2F("TOFWZedPhiDis", "TOFW phi vs zed w/o FC", 400, -200, 200, 500, -0.3, 0.7);
  TH2F *TOFWZedPhiNewDis  = new TH2F("TOFWZedPhiNewDis", "TOFW phi vs zed w/ FC", 400, -200, 200, 500, -0.3, 0.7);
  TH2F *TOFWZedPhiNewNewDis  = new TH2F("TOFWZedPhiNewNewDis", "TOFW phi vs zed w/ all FC", 400, -200, 200, 500, -0.3, 0.7);
  TH2F *TOFEZedPhiDis  = new TH2F("TOFEZedPhiDis", "TOFE phi vs zed w/o FC", 400, -200, 200, 500, -0.3, 0.7);
  TH2F *TOFEZedPhiNewDis  = new TH2F("TOFEZedPhiNewDis", "TOFE phi vs zed w/ FC", 400, -200, 200, 500, -0.3, 0.7);
  TH2F *TOFEZedPhiNewNewDis  = new TH2F("TOFEZedPhiNewNewDis", "TOFE phi vs zed w/ all FC", 400, -200, 200, 500, -0.3, 0.7);




  TH2F *tofwdphidis_w1 = new TH2F("tofwdphidis_w1", "tofwdphi distribution ", 100, 0, 10.0, 120, -0.03, 0.03);
  TH2F *tofwdzdis_w1 = new TH2F("tofwdzdis_w1", "tofwdz distribution ", 100, 0, 10.0, 100 , -10, 10);
  TH2F *tofwdphidis_w2 = new TH2F("tofwdphidis_w2", "tofwdphi distribution ", 100, 0, 10.0, 120, -0.03, 0.03);
  TH2F *tofwdzdis_w2 = new TH2F("tofwdzdis_w2", "tofwdz distribution ", 100, 0, 10.0, 100 , -10, 10);

  TH2F *pc3dphidis = new TH2F("pc3dphidis", "pc3dphi distribution ", 100, 0, 10.0, 120, -0.03, 0.03);
  TH2F *pc3dzdis = new TH2F("pc3dzdis", "pc3dz distribution ", 100, 0, 10.0, 100 , -10, 10);

  TH2F *tofwdphi_posdis_w1 = new TH2F("tofwdphi_posdis_w1", "tofwdphi distribution ", 100, 0, 10.0, 120, -0.03, 0.03);
  TH2F *tofwdz_posdis_w1 = new TH2F("tofwdz_posdis_w1", "tofwdz distribution ", 100, 0, 10.0, 100 , -10, 10);
  TH2F *tofwdphi_posdis_w2 = new TH2F("tofwdphi_posdis_w2", "tofwdphi distribution ", 100, 0, 10.0, 120, -0.03, 0.03);
  TH2F *tofwdz_posdis_w2 = new TH2F("tofwdz_posdis_w2", "tofwdz distribution ", 100, 0, 10.0, 100 , -10, 10);

  TH2F *pc3dphi_posdis = new TH2F("pc3dphi_posdis", "pc3dphi distribution ", 100, 0, 10.0, 120, -0.03, 0.03);
  TH2F *pc3dz_posdis = new TH2F("pc3dz_posdis", "pc3dz distribution ", 100, 0, 10.0, 100 , -10, 10);

  TH2F *tofwdphi_negdis_w1 = new TH2F("tofwdphi_negdis_w1", "tofwdphi distribution ", 100, 0, 10.0, 120, -0.03, 0.03);
  TH2F *tofwdz_negdis_w1 = new TH2F("tofwdz_negdis_w1", "tofwdz distribution ", 100, 0, 10.0, 100 , -10, 10);
  TH2F *tofwdphi_negdis_w2 = new TH2F("tofwdphi_negdis_w2", "tofwdphi distribution ", 100, 0, 10.0, 120, -0.03, 0.03);
  TH2F *tofwdz_negdis_w2 = new TH2F("tofwdz_negdis_w2", "tofwdz distribution ", 100, 0, 10.0, 100 , -10, 10);

  TH2F *pc3dphi_negdis = new TH2F("pc3dphi_negdis", "pc3dphi distribution ", 100, 0, 10.0, 120, -0.03, 0.03);
  TH2F *pc3dz_negdis = new TH2F("pc3dz_negdis", "pc3dz distribution ", 100, 0, 10.0, 100, -10, 10);



  // --- Done with Histograms ---------------------

  //Now read in the pDSTs listed in the input files
  int ifile=0; 
  char filename[100];
  ifstream fin(inFile);
  if(!fin)
    {
      cout<<"list input error: file does not exist "<<endl;
      exit(1);
    }
  while(fin.getline(filename,100))
    {

      ifile++; 
      cout<<ifile<<" "<<filename<<endl;

      TFile *f = TFile::Open(filename);
      if(!f)
	{
	  cout<<"pDST input error: file does not exist "<<endl;
	  continue;
	  //exit(0);
	}

      nevents += (Long64_t)((TH1F *)f->Get("hcent"))->GetEntries();

      TTree *t=(TTree *)f->Get("hadrontree");   
      if(!t)
	{
	  cout<<"pDST input error: cannot find tree "<<endl;
	  continue; 
	  //exit(0); 
	}

      int n=(int)t->GetEntries(); // number of events in tree
      hadrontree *ktree = new hadrontree(t); // pointer to tree
      for(int i=0;i<n;i++) // loop over events
	{

	  //reset to 0 for every event
	  ngoodtofwtracks_snglevent = 0;
	  
	  ktree->GetEntry(i); 

	  int run = ktree->run;
	  //if(run>250484) continue; // ++ only
	  //if(run<250593) continue; // -- only

	  stringstream ss;
	  ss<<run;
	  int runindex = myMap[ss.str()]; 

	  float bbcz = ktree->bbcz;
	  float cent = ktree->cent;
	  //if(fabs(bbcz)>30) continue;
	  //if(cent<0||cent>=100) continue;

	  int icent=-1;
	  if (cent>0 && cent<=20)        icent=0;
	  else if (cent>20 && cent<=40)  icent=1;
	  else if (cent>40 && cent<=60)  icent=2;
	  else if (cent>60 && cent<=90)  icent=3;

	  for(int itrk=0; itrk<ktree->mNtrack; itrk++)
	    {

	      ntracks++; // count total number of tracks

	      //int dcarm       = ktree->HadronTracks_dcarm[itrk];
	      int n0          = ktree->HadronTracks_n0[itrk];
	      int charge      = ktree->HadronTracks_charge[itrk];
	      float alpha     = ktree->HadronTracks_alpha[itrk];
	      float phi       = ktree->HadronTracks_phi[itrk];
	      float phi0      = ktree->HadronTracks_phi0[itrk];
	      float the0      = ktree->HadronTracks_the0[itrk];
	      float mom       = ktree->HadronTracks_mom[itrk];
	      float zed       = ktree->HadronTracks_zed[itrk];
	      float pc3sdz    = ktree->HadronTracks_pc3sdz[itrk];
	      float pc3sdphi  = ktree->HadronTracks_pc3sdphi[itrk];

	      float tofwdz    = ktree->HadronTracks_tofwdz[itrk];
	      float tofwdphi  = ktree->HadronTracks_tofwdphi[itrk];
	      int striptofw   = (int)ktree->HadronTracks_striptofw[itrk];
	      float tofwadcup = ktree->HadronTracks_tofwadcup[itrk];
	      float tofwadcdw = ktree->HadronTracks_tofwadcdw[itrk];
	      float pltofw    = ktree->HadronTracks_pltofw[itrk];
	      float ttofw     = ktree->HadronTracks_ttofw[itrk];

	      float tofedz    = ktree->HadronTracks_tofedz[itrk];
	      float tofedphi  = ktree->HadronTracks_tofedphi[itrk];
	      float tofesdz    = ktree->HadronTracks_tofesdz[itrk];
	      float tofesdphi  = ktree->HadronTracks_tofesdphi[itrk];
	      float etof      = ktree->HadronTracks_etof[itrk];
	      int slat        = (int)ktree->HadronTracks_slat[itrk];
	      float pltofe    = ktree->HadronTracks_pltofe[itrk];
	      float ttofe     = ktree->HadronTracks_ttofe[itrk];

	      //if(n0>-9999) continue;
	      //if(striptofw<0) continue; // how to select west arm for now

	      bool westarm = false;
	      bool eastarm = false;
	      if(striptofw>-9999) westarm = true;
	      if(slat>-9999) eastarm = true;

	      // this is equivalent to good_dc
	      // quality selection is made in pDSTs
	      //if(fabs(zed)<3.0||fabs(zed)>70.0) continue;
	      if(fabs(zed)<3.0||fabs(zed)>75.0) continue; // could this possibly create a 15% difference?  that sounds insane...
	      if(striptofw>0&&!goodStrip(striptofw)) continue;

	      float pt = mom*sin(the0);
	      float pT = pt;

	      if(pT<0.2) continue;
	      //if(pT>1.0) continue; // TEMPORARY!
	      //if(pT<1.0) continue; // TEMPORARY!

	      hh_zedphi_nc->Fill(zed,phi);

	      if(zed>0)
		{
		  hh_alphaphi_poszed_nc->Fill(phi,alpha);
		  hh_alphaphi_poszed_nc_EAST->Fill(phi,alpha);
		  if(pT>0.55) hh_alphaphi_poszed_nc_FW->Fill(phi,alpha);
		  if(charge>0) hh_pos_momphi_poszed_nc->Fill(phi,pT);
		  if(charge<0) hh_neg_momphi_poszed_nc->Fill(phi,pT);
		}
	      if(zed<0)
		{
		  hh_alphaphi_negzed_nc->Fill(phi,alpha);
		  hh_alphaphi_negzed_nc_EAST->Fill(phi,alpha);
		  if(pT>0.55) hh_alphaphi_negzed_nc->Fill(phi,alpha);
		  if(charge>0) hh_pos_momphi_negzed_nc->Fill(phi,pT);
		  if(charge<0) hh_neg_momphi_negzed_nc->Fill(phi,pT);
		}

	      float beta = pltofw/ttofw/phbeta;
	      float qtofw = (tofwadcup+tofwadcdw)/2.0;
	      bool good_adc = qtofw>60 && qtofw<600;

	      //if(westarm&&(qtofw<60||qtofw>600))
	      //{
	      //cout<<"BAD ADC VALUE!!!"<<endl;
	      //continue;
	      //}

	      if(runindex<0||runindex>848)
		{
		  cout<<"BAD RUNINDEX VALUE!!!  WTF!!! "<<runindex<<endl;
		  continue;
		}

	      float tofwsdz_before = sigma_tofwdz_before(mom,tofwdz);
	      float tofwsdphi_before = sigma_tofwdphi_before(mom,tofwdphi);

	      ttofw = ttofw - slewingoffset(striptofw,qtofw) - stripoffset[striptofw] - runoffset[runindex];
	      float deltat = ttofw - pltofw/phbeta*sqrt(mpion*mpion/mom/mom+1);
	      float deltate = ttofe - pltofe/phbeta*sqrt(mpion*mpion/mom/mom+1);

	      if(run<250593) // ++ only
		{
		  if(charge>0) tofwdz = tofwdz - mean_dz_pos_plusplus[striptofw];
		  if(charge<0) tofwdz = tofwdz - mean_dz_neg_plusplus[striptofw];
		  if(charge>0) tofwdphi = tofwdphi - mean_dphi_pos_plusplus[striptofw];
		  if(charge<0) tofwdphi = tofwdphi - mean_dphi_neg_plusplus[striptofw];
		}
	      
	      if(run>250484) // -- field
		{
		  if(charge>0) tofwdz = tofwdz - mean_dz_pos_minusminus[striptofw];
		  if(charge<0) tofwdz = tofwdz - mean_dz_neg_minusminus[striptofw];
		  if(charge>0) tofwdphi = tofwdphi - mean_dphi_pos_minusminus[striptofw];
		  if(charge<0) tofwdphi = tofwdphi - mean_dphi_neg_minusminus[striptofw];
		}


	      float tofwsdz;
	      float tofwsdphi;
	      // first do main calibration
	      tofwsdz = caltofwsdz(run,striptofw,charge,zed,mom,tofwdz);
	      tofwsdphi = caltofwsdphi(run,striptofw,charge,zed,mom,tofwdphi);
	      // then do recalculation with zed dependence
	      //tofwsdz = recaltofwsdz(run,striptofw,charge,zed,mom,tofwsdz);
	      //tofwsdphi = recaltofwsdphi(run,striptofw,charge,zed,mom,tofwsdphi);
	      // then to small retuning
	      tofwsdz = tunetofwsdz(run,charge,mom,cent,tofwsdz);
	      tofwsdphi = tunetofwsdphi(run,charge,mom,cent,tofwsdphi);

	      float pc3_matching = fabs(pc3sdz)<2.0 && fabs(pc3sdphi)<2.0;
	      float tfw_matching = fabs(tofwsdz)<2.0 && fabs(tofwsdphi)<2.0;
	      float tfe_matching = fabs(tofesdz)<2.0 && fabs(tofesdphi)<2.0;

	      if(westarm)
		{
		  // pc3sdphi
		  if(charge>0&&fabs(pc3sdz)<3.0) 
		    {pc3sdphi_cent_dis_pos->Fill(cent,pc3sdphi);
		      pc3sdphi_pT_dis_pos->Fill(pT,pc3sdphi);}
		  if(charge<0&&fabs(pc3sdz)<3.0) 
		    {pc3sdphi_cent_dis_neg->Fill(cent,pc3sdphi);
		      pc3sdphi_pT_dis_neg->Fill(pT,pc3sdphi);}
		  // pc3sdz
		  if(charge>0&&fabs(pc3sdphi)<3.0) 
		    {pc3sdz_cent_dis_pos->Fill(cent,pc3sdz);
		      pc3sdz_pT_dis_pos->Fill(pT,pc3sdz);}
		  if(charge<0&&fabs(pc3sdphi)<3.0) 
		    {pc3sdz_cent_dis_neg->Fill(cent,pc3sdz);
		      pc3sdz_pT_dis_neg->Fill(pT,pc3sdz);}
		  // tofwsdphi
		  if(charge>0&&fabs(tofwsdz)<3.0) 
		    {tofwsdphi_cent_dis_pos->Fill(cent,tofwsdphi);
		      tofwsdphi_pT_dis_pos->Fill(pT,tofwsdphi);}
		  if(charge<0&&fabs(tofwsdz)<3.0) 
		    {tofwsdphi_cent_dis_neg->Fill(cent,tofwsdphi);
		      tofwsdphi_pT_dis_neg->Fill(pT,tofwsdphi);}
		  // tofwsdz
		  if(charge>0&&fabs(tofwsdphi)<3.0) 
		    {tofwsdz_cent_dis_pos->Fill(cent,tofwsdz);
		      tofwsdz_pT_dis_pos->Fill(pT,tofwsdz);}
		  if(charge<0&&fabs(tofwsdphi)<3.0) 
		    {tofwsdz_cent_dis_neg->Fill(cent,tofwsdz);
		      tofwsdz_pT_dis_neg->Fill(pT,tofwsdz);}
		  // ---------------------------------------------- //
		  // --- now for something completely different --- //
		  // ---------------------------------------------- //
		  if(charge>0&&fabs(pc3sdphi)<3.0&&zed>0&&zed<40) spech_pc3sdz_cpos_zposA->Fill(pT,pc3sdz);
		  if(charge<0&&fabs(pc3sdphi)<3.0&&zed>0&&zed<40) spech_pc3sdz_cneg_zposA->Fill(pT,pc3sdz);
		  if(charge>0&&fabs(pc3sdphi)<3.0&&zed>40&&zed<80) spech_pc3sdz_cpos_zposB->Fill(pT,pc3sdz);
		  if(charge<0&&fabs(pc3sdphi)<3.0&&zed>40&&zed<80) spech_pc3sdz_cneg_zposB->Fill(pT,pc3sdz);
		  if(charge>0&&fabs(pc3sdphi)<3.0&&zed>-40&&zed<0) spech_pc3sdz_cpos_znegA->Fill(pT,pc3sdz);
		  if(charge<0&&fabs(pc3sdphi)<3.0&&zed>-40&&zed<0) spech_pc3sdz_cneg_znegA->Fill(pT,pc3sdz);
		  if(charge>0&&fabs(pc3sdphi)<3.0&&zed>-80&&zed<-40) spech_pc3sdz_cpos_znegB->Fill(pT,pc3sdz);
		  if(charge<0&&fabs(pc3sdphi)<3.0&&zed>-80&&zed<-40) spech_pc3sdz_cneg_znegB->Fill(pT,pc3sdz);
		  if(charge>0&&fabs(pc3sdz)<3.0&&zed>0&&zed<40) spech_pc3sdphi_cpos_zposA->Fill(pT,pc3sdphi);
		  if(charge<0&&fabs(pc3sdz)<3.0&&zed>0&&zed<40) spech_pc3sdphi_cneg_zposA->Fill(pT,pc3sdphi);
		  if(charge>0&&fabs(pc3sdz)<3.0&&zed>40&&zed<80) spech_pc3sdphi_cpos_zposB->Fill(pT,pc3sdphi);
		  if(charge<0&&fabs(pc3sdz)<3.0&&zed>40&&zed<80) spech_pc3sdphi_cneg_zposB->Fill(pT,pc3sdphi);
		  if(charge>0&&fabs(pc3sdz)<3.0&&zed>-40&&zed<0) spech_pc3sdphi_cpos_znegA->Fill(pT,pc3sdphi);
		  if(charge<0&&fabs(pc3sdz)<3.0&&zed>-40&&zed<0) spech_pc3sdphi_cneg_znegA->Fill(pT,pc3sdphi);
		  if(charge>0&&fabs(pc3sdz)<3.0&&zed>-80&&zed<-40) spech_pc3sdphi_cpos_znegB->Fill(pT,pc3sdphi);
		  if(charge<0&&fabs(pc3sdz)<3.0&&zed>-80&&zed<-40) spech_pc3sdphi_cneg_znegB->Fill(pT,pc3sdphi);
		}


	      //if(!pc3_matching||!tfw_matching) continue;
	      //if(!tfw_matching) continue;

	      float ppc1x   = ktree->HadronTracks_ppc1x[itrk];
	      float ppc1y   = ktree->HadronTracks_ppc1y[itrk];
	      float ppc1z   = ktree->HadronTracks_ppc1z[itrk];
	      float pc1z    = ppc1z;
	      float pc1phi  = atan2(ppc1y,ppc1x);  
	      bool good_pc1 = GoodPC1(pc1z,pc1phi);
	      bool newgood_pc1 = NewGoodPC1(pc1z,pc1phi);
	      
	      //PC1ZedPhiDis->Fill(pc1z,pc1phi);
	      //if(good_pc1&&pT>0.4) PC1ZedPhiNewDis->Fill(pc1z,pc1phi); // in Run7 code
	      //if(good_pc1) PC1ZedPhiNewDis->Fill(pc1z,pc1phi);
	      //if(!good_pc1) continue; // new

	      // float ppc2x   = ktree->HadronTracks_ppc2x[itrk];
	      // float ppc2y   = ktree->HadronTracks_ppc2y[itrk];
	      // float ppc2z   = ktree->HadronTracks_ppc2z[itrk];
	      // float pc2dz   = ktree->HadronTracks_pc2dz[itrk];
	      // float pc2dphi = ktree->HadronTracks_pc2dphi[itrk];
	      // float pc2z    = ppc2z -pc2dz;
	      // float pc2phi  = atan2(ppc2y,ppc2x) - pc2dphi;
	      // bool good_pc2 = GoodPC2(pc2z,pc2phi);
	      // bool newgood_pc2 = NewGoodPC2(pc2z,pc2phi);
	      
	      // if(pc2_matching) PC2ZedPhiDis->Fill(pc2z,pc2phi);
	      // if(pc2_matching&&good_pc2) PC2ZedPhiNewDis->Fill(pc2z,pc2phi);

	      float ppc3x   = ktree->HadronTracks_ppc3x[itrk];
	      float ppc3y   = ktree->HadronTracks_ppc3y[itrk];
	      float ppc3z   = ktree->HadronTracks_ppc3z[itrk];
	      float pc3dz   = ktree->HadronTracks_pc3dz[itrk];
	      float pc3dphi = ktree->HadronTracks_pc3dphi[itrk];
	      float pc3z    = ppc3z - pc3dz;
	      float pc3phi  = atan2(ppc3y,ppc3x) - pc3dphi;
	      bool good_pc3 = GoodPC3(pc3z,pc3phi);
	      bool newgood_pc3 = NewGoodPC3(pc3z,pc3phi);
	      
	      //if(pc3_matching) PC3ZedPhiDis->Fill(pc3z,pc3phi);
	      //if(pc3_matching&&good_pc3) PC3ZedPhiNewDis->Fill(pc3z,pc3phi);
	      //if(!good_pc3) continue; // new

	      ngoodtofwtracks++;
	      ngoodtofwtracks_snglevent++;

	      // this changes for the systematics
	      // matching cut
	      //if(!pc3_matching||!tfw_matching) continue;
	      //if(!pc3_matching) continue;
	      //if(westarm&&!tfw_matching) continue;
	      //if(eastarm&&!tfe_matching) continue;

	      // west arm
	      //if(dcarm==1)
	      if(westarm)
		{
		  PC1ZedPhiDisWest->Fill(pc1z,pc1phi);
		  //if(pc2_matching) PC2ZedPhiDisWest->Fill(pc2z,pc2phi);
		  if(pc3_matching) PC3ZedPhiDisWest->Fill(pc3z,pc3phi);
		  if(newgood_pc1) PC1ZedPhiDisWest_After->Fill(pc1z,pc1phi);
		  //if(newgood_pc2&&pc2_matching) PC2ZedPhiDisWest_After->Fill(pc2z,pc2phi);
		  if(newgood_pc3&&pc3_matching) PC3ZedPhiDisWest_After->Fill(pc3z,pc3phi);
		}

	      // east arm
	      //if(dcarm==0)
	      if(eastarm)
		{
		  pc1phi = asin(sin(pc1phi))+3.14159265; // correct the phi angle
		  pc3phi = asin(sin(pc3phi))+3.14159265; // correct the phi angle
		  PC1ZedPhiDisEast->Fill(pc1z,pc1phi);
		  if(pc3_matching) PC3ZedPhiDisEast->Fill(pc3z,pc3phi);
		  if(newgood_pc1) PC1ZedPhiDisEast_After->Fill(pc1z,pc1phi);
		  if(newgood_pc3&&pc3_matching) PC3ZedPhiDisEast_After->Fill(pc3z,pc3phi);
		}

	      // -------------- //
	      // --- NORMAL --- //
	      // -------------- //
	      

	      if(striptofw>-1&&striptofw<256)
	      	{
	      	  tofwdphidis_w1->Fill(pt,tofwdphi);
	      	  tofwdzdis_w1->Fill(pt,tofwdz);
	      	}
	      if(striptofw>255&&striptofw<512)
	      	{
	      	  tofwdphidis_w2->Fill(pt,tofwdphi);
	      	  tofwdzdis_w2->Fill(pt,tofwdz);
	      	}

	      pc3dphidis->Fill(pt,pc3dphi);
	      pc3dzdis->Fill(pt,pc3dz);


	      if(charge>0)
	      	{
	      	  if(striptofw>-1&&striptofw<256)
	      	    {
	      	      tofwdphi_posdis_w1->Fill(pt,tofwdphi);
	      	      tofwdz_posdis_w1->Fill(pt,tofwdz);
	      	    }
	      	  if(striptofw>255&&striptofw<512)
	      	    {
	      	      tofwdphi_posdis_w2->Fill(pt,tofwdphi);
	      	      tofwdz_posdis_w2->Fill(pt,tofwdz);
	      	    }
	      	  pc3dphi_posdis->Fill(pt,pc3dphi);
	      	  pc3dz_posdis->Fill(pt,pc3dz);
	      	}
	      if(charge<0)
	      	{
	      	  if(striptofw>-1&&striptofw<256)
	      	    {
	      	      tofwdphi_negdis_w1->Fill(pt,tofwdphi);
	      	      tofwdz_negdis_w1->Fill(pt,tofwdz);
	      	    }
	      	  if(striptofw>255&&striptofw<512)
	      	    {
	      	      tofwdphi_negdis_w2->Fill(pt,tofwdphi);
	      	      tofwdz_negdis_w2->Fill(pt,tofwdz);
	      	    }
	      	  pc3dphi_negdis->Fill(pt,pc3dphi);
	      	  pc3dz_negdis->Fill(pt,pc3dz);
	      	}



	      // ------------------------------ //
	      // --- END OF MATCHING HISTOS --- //
	      // ------------------------------ //

	      // ------------------------------ //
	      // --- NOW DOING TIMING CALIB --- //
	      // ------------------------------ //

	      if(mom>1.1&&mom<1.5&&tfw_matching&&westarm)
		{
		  qtofwdis->Fill(qtofw);
		  tofwadcupdis->Fill(tofwadcup);
		  tofwadcdwdis->Fill(tofwadcdw);

		  deltatslewingdis_q->Fill(qtofw,deltat);

		  deltatdis->Fill(deltat);
		  deltatrundis->Fill(runindex,deltat);
		  deltatstriptofwdis->Fill(striptofw,deltat);
		}

	      if(mom>1.1&&mom<1.5&&tfe_matching&&eastarm)
		{
		  etofdis->Fill(etof);
		  deltatdis_east->Fill(deltate);
		  deltatrunedis->Fill(runindex,deltate);
		  deltatslatdis->Fill(slat,deltate);
		}
	      
	      float m2tofw = mom*mom*(ttofw*ttofw*phbeta*phbeta/(pltofw*pltofw)-1);
	      float m2tofe = mom*mom*(ttofe*ttofe*phbeta*phbeta/(pltofe*pltofe)-1);

	      m2mom_dis->Fill(charge*pT,m2tofw);
	      //ttofwmom_dis->Fill(charge*mom,deltat);
	      
	      if(charge>0)
		{
		  m2mompos_dis->Fill(pT,m2tofw);
		  if(westarm) m2pTdis_pos->Fill(pT,m2tofw);
		  if(eastarm) m2pTdis_pos_east->Fill(pT,m2tofe);
		  if(eastarm) ttofemompos_dis->Fill(mom,deltate);
		  if(westarm) ttofwmompos_dis->Fill(mom,deltat);
		}
	      else
		{
		  m2momneg_dis->Fill(pT,m2tofw);
		  if(westarm) m2pTdis_neg->Fill(pT,m2tofw);
		  if(eastarm) m2pTdis_neg_east->Fill(pT,m2tofe);
		  if(eastarm) ttofemomneg_dis->Fill(mom,deltate);
		  if(westarm) ttofwmomneg_dis->Fill(mom,deltat);
		}

	      // --------------------------- //
	      // --- end of timing calib --- //
	      // --------------------------- //

	      // this is done above, doesn't affect Run7 and Run8 comparisons
	      //if(!good_dc) continue;
	      //if(!goodstrip) continue;

	      bool irregular_cuts = tfe_matching && pc3_matching;
	      bool regular_cuts = tfw_matching && pc3_matching && good_pc1 && good_pc3 && good_adc;
	      bool syst_tfwmatch = pc3_matching && good_pc1 && good_pc3 && good_adc;	
	      bool syst_pc3match = tfw_matching && good_pc1 && good_pc3 && good_adc;
	      bool syst_pc3fiducial = tfw_matching && pc3_matching && good_pc1 && good_adc;
	      bool syst_pc1fiducial = tfw_matching && pc3_matching && good_pc3 && good_adc;
	      bool syst_goodadc = tfw_matching && pc3_matching && good_pc1 && good_pc3;

	      // SUPER DUPER ULTRA MEGA TESTING!
	      //if(!regular_cuts) continue;
	      //if(!syst_tfwmatch) continue;
	      //if(!syst_pc3match) continue;
	      //if(!syst_pc3fiducial) continue;
	      //if(!syst_pc1fiducial) continue;
	      //if(!syst_goodadc) continue;

	      // ----------------------- //
	      // --- dcfc histograms --- //
	      // ----------------------- //

	      if(regular_cuts) hh_zedphi_mc->Fill(zed,phi);

	      if(regular_cuts&&zed>0)
		{
		  hh_alphaphi_poszed_mc->Fill(phi,alpha);
		  hh_alphaphi_poszed_mc_EAST->Fill(phi,alpha);
		  if(pT>0.55) hh_alphaphi_poszed_mc_FW->Fill(phi,alpha);
		  if(charge>0) hh_pos_momphi_poszed_mc->Fill(phi,pT);
		  if(charge<0) hh_neg_momphi_poszed_mc->Fill(phi,pT);
		}
	      if(regular_cuts&&zed<0)
		{
		  hh_alphaphi_negzed_mc->Fill(phi,alpha);
		  hh_alphaphi_negzed_mc_EAST->Fill(phi,alpha);
		  if(pT>0.55) hh_alphaphi_negzed_mc_FW->Fill(phi,alpha);
		  if(charge>0) hh_pos_momphi_negzed_mc->Fill(phi,pT);
		  if(charge<0) hh_neg_momphi_negzed_mc->Fill(phi,pT);
		}

	      // ----------------------- //
	      // ----------------------- //
	      // ----------------------- //


	      //if(westarm&&!GoodEdgeDCH(run,zed,alpha,phi)) continue;
	      //bool edge = westarm && GoodEdgeDCH(run,zed,alpha,phi);
	      bool edge = GoodEdgeDCH(run,zed,alpha,phi);

	      // ----------------------- //
	      // --- dcfc histograms --- //
	      // ----------------------- //

	      if(regular_cuts&&edge) hh_zedphi_ec->Fill(zed,phi);

	      if(regular_cuts&&edge&&zed>0)
		{
		  hh_alphaphi_poszed_ec->Fill(phi,alpha);
		  hh_alphaphi_poszed_ec_EAST->Fill(phi,alpha);
		  if(pT>0.55) hh_alphaphi_poszed_ec_FW->Fill(phi,alpha);
		  if(charge>0) hh_pos_momphi_poszed_ec->Fill(phi,pT);
		  if(charge<0) hh_neg_momphi_poszed_ec->Fill(phi,pT);
		}
	      if(regular_cuts&&edge&&zed<0)
		{
		  hh_alphaphi_negzed_ec->Fill(phi,alpha);
		  hh_alphaphi_negzed_ec_EAST->Fill(phi,alpha);
		  if(pT>0.55) hh_alphaphi_negzed_ec_FW->Fill(phi,alpha);
		  if(charge>0) hh_pos_momphi_negzed_ec->Fill(phi,pT);
		  if(charge<0) hh_neg_momphi_negzed_ec->Fill(phi,pT);
		}

	      // ----------------------- //
	      // ----------------------- //
	      // ----------------------- //

	      //if(westarm&&!GoodInnerDCH(run,zed,alpha,phi)) continue;
	      //bool inner = westarm && GoodInnerDCH(run,zed,alpha,phi);
	      bool inner = GoodInnerDCH(run,zed,alpha,phi);

	      if(regular_cuts&&edge&&inner) hh_zedphi_ac->Fill(zed,phi);

	      if(regular_cuts&&edge&&inner&&zed>0)
		{
		  hh_alphaphi_poszed_ac->Fill(phi,alpha);
		  hh_alphaphi_poszed_ac_EAST->Fill(phi,alpha);
		  if(pT>0.55) hh_alphaphi_poszed_ac_FW->Fill(phi,alpha);
		  if(charge>0) hh_pos_momphi_poszed_ac->Fill(phi,pT);
		  if(charge<0) hh_neg_momphi_poszed_ac->Fill(phi,pT);
		}
	      if(regular_cuts&&edge&&inner&&zed<0)
		{
		  hh_alphaphi_negzed_ac->Fill(phi,alpha);
		  hh_alphaphi_negzed_ac_EAST->Fill(phi,alpha);
		  if(pT>0.55) hh_alphaphi_negzed_ac_FW->Fill(phi,alpha);
		  if(charge>0) hh_pos_momphi_negzed_ac->Fill(phi,pT);
		  if(charge<0) hh_neg_momphi_negzed_ac->Fill(phi,pT);
		}

	      // ----------------------- //
	      // ----------------------- //
	      // ----------------------- //


	      // -------------------------- //
	      // --- now to do tofw pid --- //
	      // -------------------------- //

	      float isPi = isPion(pT,m2tofw);
	      float isK = isKaon(pT,m2tofw);
	      float isP = isProton(pT,m2tofw);

	      // pid distributions
	      bool dis0 = westarm && isPi>=-2 && isPi<=2;
	      bool dis1 = westarm && isPi>=-2 && isPi<=2 && isK<=-2;
	      bool dis2 = westarm && isK>=-2 && isK<=2;
	      bool dis3 = westarm && isK>=-2 && isK<=2 && isPi>=2 && isP<=-2;
	      bool dis4 = westarm && isP>=-2 && isP<=2;
	      bool dis5 = westarm && isP>=-2 && isP<=2 && isK>=2;

	      // sector and charge
	      bool w1pos = charge>0 && striptofw>=0 && striptofw<=255;
	      bool w1neg = charge<0 && striptofw>=0 && striptofw<=255;
	      bool w2pos = charge>0 && striptofw>=256 && striptofw<=511;
	      bool w2neg = charge<0 && striptofw>=256 && striptofw<=511;

	      bool piA = westarm && isPi>=-3 && isPi<=3 && isK<=-3;
	      bool kaA = westarm && isK>=-3 && isK<=3 && isPi>=3 && isP<=-3;
	      bool prA = westarm && isP>=-3 && isP<=3 && isK>=3;
	      bool piB = westarm && isPi>=-1 && isPi<=1 && isK<=-1;
	      bool kaB = westarm && isK>=-1 && isK<=1 && isPi>=1 && isP<=-1;
	      bool prB = westarm && isP>=-1 && isP<=1 && isK>=1;

	      // bool regular_cuts = tfw_matching && pc3_matching && good_pc1 && good_pc3 && good_adc;
	      // bool syst_tfwmatch = pc3_matching && good_pc1 && good_pc3 && good_adc;	
	      // bool syst_pc3match = tfw_matching && good_pc1 && good_pc3 && good_adc;
	      // bool syst_pc3fiducial = tfw_matching && pc3_matching && good_pc1 && good_adc;
	      // bool syst_pc1fiducial = tfw_matching && pc3_matching && good_pc3 && good_adc;
	      // bool syst_goodadc = tfw_matching && pc3_matching && good_pc1 && good_pc3;

	      bool good_dcfc = edge && inner; // define DC fiducial cut
	      //regular_cuts &= good_dcfc; // do NOT redefine
	      // redefine the sytematics to include dcfc
	      syst_tfwmatch &= good_dcfc;
	      syst_pc3match &= good_dcfc;
	      syst_pc3fiducial &= good_dcfc;
	      syst_pc1fiducial &= good_dcfc;
	      syst_goodadc &= good_dcfc;
	      bool syst_dcfc = regular_cuts;

	      // ------------------------------- //
	      // --- begin systematics study --- //
	      // ------------------------------- //

	      if(charge>0)
		{
		  // tofw matching
		  if(syst_tfwmatch)
		    {
		      if(dis1) ptsys_pion_pos_tfwmA->Fill(pT);
		      if(dis3) ptsys_kaon_pos_tfwmA->Fill(pT);
		      if(dis5) ptsys_prot_pos_tfwmA->Fill(pT);
		      if(fabs(tofwsdphi<3.0)&&fabs(tofwsdz<3.0))
			{
			  if(dis1) ptsys_pion_pos_tfwmB->Fill(pT);
			  if(dis3) ptsys_kaon_pos_tfwmB->Fill(pT);
			  if(dis5) ptsys_prot_pos_tfwmB->Fill(pT);
			}
		    }
		  
		  // pc3 matching
		  if(syst_pc3match)
		    {
		      if(dis1) ptsys_pion_pos_pc3mA->Fill(pT);
		      if(dis3) ptsys_kaon_pos_pc3mA->Fill(pT);
		      if(dis5) ptsys_prot_pos_pc3mA->Fill(pT);
		      if(fabs(pc3sdphi<3.0)&&fabs(pc3sdz<3.0))
			{
			  if(dis1) ptsys_pion_pos_pc3mB->Fill(pT);
			  if(dis3) ptsys_kaon_pos_pc3mB->Fill(pT);
			  if(dis5) ptsys_prot_pos_pc3mB->Fill(pT);
			}
		    }
		  
		  // pc3 fiducial
		  if(syst_pc3fiducial)
		    {
		      if(dis1) ptsys_pion_pos_pc3fA->Fill(pT);
		      if(dis3) ptsys_kaon_pos_pc3fA->Fill(pT);
		      if(dis5) ptsys_prot_pos_pc3fA->Fill(pT);
		      if(!good_pc3)
			{
			  if(dis1) ptsys_pion_pos_pc3fB->Fill(pT);
			  if(dis3) ptsys_kaon_pos_pc3fB->Fill(pT);
			  if(dis5) ptsys_prot_pos_pc3fB->Fill(pT);
			}
		    }
		  
		  // pc1 fiducial
		  if(syst_pc1fiducial)
		    {
		      if(dis1) ptsys_pion_pos_pc1fA->Fill(pT);
		      if(dis3) ptsys_kaon_pos_pc1fA->Fill(pT);
		      if(dis5) ptsys_prot_pos_pc1fA->Fill(pT);
		      if(!good_pc1)
			{
			  if(dis1) ptsys_pion_pos_pc1fB->Fill(pT);
			  if(dis3) ptsys_kaon_pos_pc1fB->Fill(pT);
			  if(dis5) ptsys_prot_pos_pc1fB->Fill(pT);
			}
		    }
		  
		  // tofw adc cut
		  if(syst_goodadc)
		    {
		      if(qtofw>60)
			{
			  if(dis1) ptsys_pion_pos_gadcA->Fill(pT);
			  if(dis3) ptsys_kaon_pos_gadcA->Fill(pT);
			  if(dis5) ptsys_prot_pos_gadcA->Fill(pT);
			}
		      if(qtofw<600)
			{
			  if(dis1) ptsys_pion_pos_gadcB->Fill(pT);
			  if(dis3) ptsys_kaon_pos_gadcB->Fill(pT);
			  if(dis5) ptsys_prot_pos_gadcB->Fill(pT);
			}
		    }
		  
		  // fiducial cuts
		  if(syst_dcfc)
		    {
		      if(edge)
			{
			  if(dis1) ptsys_pion_pos_dcfcA->Fill(pT);
			  if(dis3) ptsys_kaon_pos_dcfcA->Fill(pT);
			  if(dis5) ptsys_prot_pos_dcfcA->Fill(pT);
			}
		      if(inner)
			{
			  if(dis1) ptsys_pion_pos_dcfcB->Fill(pT);
			  if(dis3) ptsys_kaon_pos_dcfcB->Fill(pT);
			  if(dis5) ptsys_prot_pos_dcfcB->Fill(pT);
			}
		    }
		  
		  // dc zed
		  if(regular_cuts&&good_dcfc)
		    {
		      if(fabs(zed<40))
			{
			  if(dis1) ptsys_pion_pos_dzedA->Fill(pT);
			  if(dis3) ptsys_kaon_pos_dzedA->Fill(pT);
			  if(dis5) ptsys_prot_pos_dzedA->Fill(pT);
			}
		      if(fabs(zed>40))
			{
			  if(dis1) ptsys_pion_pos_dzedB->Fill(pT);
			  if(dis3) ptsys_kaon_pos_dzedB->Fill(pT);
			  if(dis5) ptsys_prot_pos_dzedB->Fill(pT);
			}
		    }
		  
		  // pid
		  if(regular_cuts&&good_dcfc)
		    {
		      if(piA) ptsys_pion_pos_spidA->Fill(pT);
		      if(kaA) ptsys_kaon_pos_spidA->Fill(pT);
		      if(prA) ptsys_prot_pos_spidA->Fill(pT);
		      if(piB) ptsys_pion_pos_spidB->Fill(pT);
		      if(kaB) ptsys_kaon_pos_spidB->Fill(pT);
		      if(prB) ptsys_prot_pos_spidB->Fill(pT);
		    }
		}//positive
	      if(charge<0)
		{
		  // tofw matching
		  if(syst_tfwmatch)
		    {
		      if(dis1) ptsys_pion_neg_tfwmA->Fill(pT);
		      if(dis3) ptsys_kaon_neg_tfwmA->Fill(pT);
		      if(dis5) ptsys_prot_neg_tfwmA->Fill(pT);
		      if(fabs(tofwsdphi<3.0)&&fabs(tofwsdz<3.0))
			{
			  if(dis1) ptsys_pion_neg_tfwmB->Fill(pT);
			  if(dis3) ptsys_kaon_neg_tfwmB->Fill(pT);
			  if(dis5) ptsys_prot_neg_tfwmB->Fill(pT);
			}
		    }
		  
		  // pc3 matching
		  if(syst_pc3match)
		    {
		      if(dis1) ptsys_pion_neg_pc3mA->Fill(pT);
		      if(dis3) ptsys_kaon_neg_pc3mA->Fill(pT);
		      if(dis5) ptsys_prot_neg_pc3mA->Fill(pT);
		      if(fabs(pc3sdphi<3.0)&&fabs(pc3sdz<3.0))
			{
			  if(dis1) ptsys_pion_neg_pc3mB->Fill(pT);
			  if(dis3) ptsys_kaon_neg_pc3mB->Fill(pT);
			  if(dis5) ptsys_prot_neg_pc3mB->Fill(pT);
			}
		    }
		  
		  // pc3 fiducial
		  if(syst_pc3fiducial)
		    {
		      if(dis1) ptsys_pion_neg_pc3fA->Fill(pT);
		      if(dis3) ptsys_kaon_neg_pc3fA->Fill(pT);
		      if(dis5) ptsys_prot_neg_pc3fA->Fill(pT);
		      if(!good_pc3)
			{
			  if(dis1) ptsys_pion_neg_pc3fB->Fill(pT);
			  if(dis3) ptsys_kaon_neg_pc3fB->Fill(pT);
			  if(dis5) ptsys_prot_neg_pc3fB->Fill(pT);
			}
		    }
		  
		  // pc1 fiducial
		  if(syst_pc1fiducial)
		    {
		      if(dis1) ptsys_pion_neg_pc1fA->Fill(pT);
		      if(dis3) ptsys_kaon_neg_pc1fA->Fill(pT);
		      if(dis5) ptsys_prot_neg_pc1fA->Fill(pT);
		      if(!good_pc1)
			{
			  if(dis1) ptsys_pion_neg_pc1fB->Fill(pT);
			  if(dis3) ptsys_kaon_neg_pc1fB->Fill(pT);
			  if(dis5) ptsys_prot_neg_pc1fB->Fill(pT);
			}
		    }
		  
		  // tofw adc cut
		  if(syst_goodadc)
		    {
		      if(qtofw>60)
			{
			  if(dis1) ptsys_pion_neg_gadcA->Fill(pT);
			  if(dis3) ptsys_kaon_neg_gadcA->Fill(pT);
			  if(dis5) ptsys_prot_neg_gadcA->Fill(pT);
			}
		      if(qtofw<600)
			{
			  if(dis1) ptsys_pion_neg_gadcB->Fill(pT);
			  if(dis3) ptsys_kaon_neg_gadcB->Fill(pT);
			  if(dis5) ptsys_prot_neg_gadcB->Fill(pT);
			}
		    }
		  
		  // fiducial cuts
		  if(syst_dcfc)
		    {
		      if(edge)
			{
			  if(dis1) ptsys_pion_neg_dcfcA->Fill(pT);
			  if(dis3) ptsys_kaon_neg_dcfcA->Fill(pT);
			  if(dis5) ptsys_prot_neg_dcfcA->Fill(pT);
			}
		      if(inner)
			{
			  if(dis1) ptsys_pion_neg_dcfcB->Fill(pT);
			  if(dis3) ptsys_kaon_neg_dcfcB->Fill(pT);
			  if(dis5) ptsys_prot_neg_dcfcB->Fill(pT);
			}
		    }
		  
		  // dc zed
		  if(regular_cuts&&good_dcfc)
		    {
		      if(fabs(zed<40))
			{
			  if(dis1) ptsys_pion_neg_dzedA->Fill(pT);
			  if(dis3) ptsys_kaon_neg_dzedA->Fill(pT);
			  if(dis5) ptsys_prot_neg_dzedA->Fill(pT);
			}
		      if(fabs(zed>40))
			{
			  if(dis1) ptsys_pion_neg_dzedB->Fill(pT);
			  if(dis3) ptsys_kaon_neg_dzedB->Fill(pT);
			  if(dis5) ptsys_prot_neg_dzedB->Fill(pT);
			}
		    }
		  
		  // pid
		  if(regular_cuts&&good_dcfc)
		    {
		      if(piA) ptsys_pion_neg_spidA->Fill(pT);
		      if(kaA) ptsys_kaon_neg_spidA->Fill(pT);
		      if(prA) ptsys_prot_neg_spidA->Fill(pT);
		      if(piB) ptsys_pion_neg_spidB->Fill(pT);
		      if(kaB) ptsys_kaon_neg_spidB->Fill(pT);
		      if(prB) ptsys_prot_neg_spidB->Fill(pT);
		    }
		}//negative

	      // -------------------------------- //
	      // --- end of systematics study --- //
	      // -------------------------------- //

	      // ---

	      if(regular_cuts&&edge&&inner)
		{
		  // both sectors together
		  if(charge>0)
		    {
		      if(dis0) ptpid_tofw_pos_0_dis->Fill(pT);
		      if(dis1) ptpid_tofw_pos_1_dis->Fill(pT);
		      if(dis2) ptpid_tofw_pos_2_dis->Fill(pT);
		      if(dis3) ptpid_tofw_pos_3_dis->Fill(pT);
		      if(dis4) ptpid_tofw_pos_4_dis->Fill(pT);
		      if(dis5) ptpid_tofw_pos_5_dis->Fill(pT);
		    }
		  if(charge<0)
		    {
		      //1-d
		      if(dis0) ptpid_tofw_neg_0_dis->Fill(pT);
		      if(dis1) ptpid_tofw_neg_1_dis->Fill(pT);
		      if(dis2) ptpid_tofw_neg_2_dis->Fill(pT);
		      if(dis3) ptpid_tofw_neg_3_dis->Fill(pT);
		      if(dis4) ptpid_tofw_neg_4_dis->Fill(pT);
		      if(dis5) ptpid_tofw_neg_5_dis->Fill(pT);
		    }
		  
		  // centrality, both sectors together
		  if(cent>0&&cent<=88)
		    {
		      if(charge>0)
			{
			  if(dis0) ptpid_tofw_pos_0_dis_cent0088->Fill(pT);
			  if(dis1) ptpid_tofw_pos_1_dis_cent0088->Fill(pT);
			  if(dis2) ptpid_tofw_pos_2_dis_cent0088->Fill(pT);
			  if(dis3) ptpid_tofw_pos_3_dis_cent0088->Fill(pT);
			  if(dis4) ptpid_tofw_pos_4_dis_cent0088->Fill(pT);
			  if(dis5) ptpid_tofw_pos_5_dis_cent0088->Fill(pT);
			}
		      if(charge<0)
			{
			  //1-d
			  if(dis0) ptpid_tofw_neg_0_dis_cent0088->Fill(pT);
			  if(dis1) ptpid_tofw_neg_1_dis_cent0088->Fill(pT);
			  if(dis2) ptpid_tofw_neg_2_dis_cent0088->Fill(pT);
			  if(dis3) ptpid_tofw_neg_3_dis_cent0088->Fill(pT);
			  if(dis4) ptpid_tofw_neg_4_dis_cent0088->Fill(pT);
			  if(dis5) ptpid_tofw_neg_5_dis_cent0088->Fill(pT);
			}
		    }
		  if(cent>0&&cent<=20)
		    {
		      if(charge>0)
			{
			  if(dis0) ptpid_tofw_pos_0_dis_cent0020->Fill(pT);
			  if(dis1) ptpid_tofw_pos_1_dis_cent0020->Fill(pT);
			  if(dis2) ptpid_tofw_pos_2_dis_cent0020->Fill(pT);
			  if(dis3) ptpid_tofw_pos_3_dis_cent0020->Fill(pT);
			  if(dis4) ptpid_tofw_pos_4_dis_cent0020->Fill(pT);
			  if(dis5) ptpid_tofw_pos_5_dis_cent0020->Fill(pT);
			}
		      if(charge<0)
			{
			  //1-d
			  if(dis0) ptpid_tofw_neg_0_dis_cent0020->Fill(pT);
			  if(dis1) ptpid_tofw_neg_1_dis_cent0020->Fill(pT);
			  if(dis2) ptpid_tofw_neg_2_dis_cent0020->Fill(pT);
			  if(dis3) ptpid_tofw_neg_3_dis_cent0020->Fill(pT);
			  if(dis4) ptpid_tofw_neg_4_dis_cent0020->Fill(pT);
			  if(dis5) ptpid_tofw_neg_5_dis_cent0020->Fill(pT);
			}
		    }
		  if(cent>20&&cent<=40)
		    {
		      if(charge>0)
			{
			  if(dis0) ptpid_tofw_pos_0_dis_cent2040->Fill(pT);
			  if(dis1) ptpid_tofw_pos_1_dis_cent2040->Fill(pT);
			  if(dis2) ptpid_tofw_pos_2_dis_cent2040->Fill(pT);
			  if(dis3) ptpid_tofw_pos_3_dis_cent2040->Fill(pT);
			  if(dis4) ptpid_tofw_pos_4_dis_cent2040->Fill(pT);
			  if(dis5) ptpid_tofw_pos_5_dis_cent2040->Fill(pT);
			}
		      if(charge<0)
			{
			  //1-d
			  if(dis0) ptpid_tofw_neg_0_dis_cent2040->Fill(pT);
			  if(dis1) ptpid_tofw_neg_1_dis_cent2040->Fill(pT);
			  if(dis2) ptpid_tofw_neg_2_dis_cent2040->Fill(pT);
			  if(dis3) ptpid_tofw_neg_3_dis_cent2040->Fill(pT);
			  if(dis4) ptpid_tofw_neg_4_dis_cent2040->Fill(pT);
			  if(dis5) ptpid_tofw_neg_5_dis_cent2040->Fill(pT);
			}
		    }
		  if(cent>40&&cent<=60)
		    {
		      if(charge>0)
			{
			  if(dis0) ptpid_tofw_pos_0_dis_cent4060->Fill(pT);
			  if(dis1) ptpid_tofw_pos_1_dis_cent4060->Fill(pT);
			  if(dis2) ptpid_tofw_pos_2_dis_cent4060->Fill(pT);
			  if(dis3) ptpid_tofw_pos_3_dis_cent4060->Fill(pT);
			  if(dis4) ptpid_tofw_pos_4_dis_cent4060->Fill(pT);
			  if(dis5) ptpid_tofw_pos_5_dis_cent4060->Fill(pT);
			}
		      if(charge<0)
			{
			  //1-d
			  if(dis0) ptpid_tofw_neg_0_dis_cent4060->Fill(pT);
			  if(dis1) ptpid_tofw_neg_1_dis_cent4060->Fill(pT);
			  if(dis2) ptpid_tofw_neg_2_dis_cent4060->Fill(pT);
			  if(dis3) ptpid_tofw_neg_3_dis_cent4060->Fill(pT);
			  if(dis4) ptpid_tofw_neg_4_dis_cent4060->Fill(pT);
			  if(dis5) ptpid_tofw_neg_5_dis_cent4060->Fill(pT);
			}
		    }
		  if(cent>60&&cent<=88)
		    {
		      if(charge>0)
			{
			  if(dis0) ptpid_tofw_pos_0_dis_cent6088->Fill(pT);
			  if(dis1) ptpid_tofw_pos_1_dis_cent6088->Fill(pT);
			  if(dis2) ptpid_tofw_pos_2_dis_cent6088->Fill(pT);
			  if(dis3) ptpid_tofw_pos_3_dis_cent6088->Fill(pT);
			  if(dis4) ptpid_tofw_pos_4_dis_cent6088->Fill(pT);
			  if(dis5) ptpid_tofw_pos_5_dis_cent6088->Fill(pT);
			}
		      if(charge<0)
			{
			  //1-d
			  if(dis0) ptpid_tofw_neg_0_dis_cent6088->Fill(pT);
			  if(dis1) ptpid_tofw_neg_1_dis_cent6088->Fill(pT);
			  if(dis2) ptpid_tofw_neg_2_dis_cent6088->Fill(pT);
			  if(dis3) ptpid_tofw_neg_3_dis_cent6088->Fill(pT);
			  if(dis4) ptpid_tofw_neg_4_dis_cent6088->Fill(pT);
			  if(dis5) ptpid_tofw_neg_5_dis_cent6088->Fill(pT);
			}
		    }
		  
		  // --- 
		  
		  // now do sectors separately
		  if(w1pos)
		    {
		      //1-d
		      if(dis0) ptpid_tofw_w1_pos_0_dis->Fill(pT);
		      if(dis1) ptpid_tofw_w1_pos_1_dis->Fill(pT);
		      if(dis2) ptpid_tofw_w1_pos_2_dis->Fill(pT);
		      if(dis3) ptpid_tofw_w1_pos_3_dis->Fill(pT);
		      if(dis4) ptpid_tofw_w1_pos_4_dis->Fill(pT);
		      if(dis5) ptpid_tofw_w1_pos_5_dis->Fill(pT);
		    }
		  if(w1neg)
		    {
		      //1-d
		      if(dis0) ptpid_tofw_w1_neg_0_dis->Fill(pT);
		      if(dis1) ptpid_tofw_w1_neg_1_dis->Fill(pT);
		      if(dis2) ptpid_tofw_w1_neg_2_dis->Fill(pT);
		      if(dis3) ptpid_tofw_w1_neg_3_dis->Fill(pT);
		      if(dis4) ptpid_tofw_w1_neg_4_dis->Fill(pT);
		      if(dis5) ptpid_tofw_w1_neg_5_dis->Fill(pT);
		    }
		  if(w2pos)
		    {
		      //1-d
		      if(dis0) ptpid_tofw_w2_pos_0_dis->Fill(pT);
		      if(dis1) ptpid_tofw_w2_pos_1_dis->Fill(pT);
		      if(dis2) ptpid_tofw_w2_pos_2_dis->Fill(pT);
		      if(dis3) ptpid_tofw_w2_pos_3_dis->Fill(pT);
		      if(dis4) ptpid_tofw_w2_pos_4_dis->Fill(pT);
		      if(dis5) ptpid_tofw_w2_pos_5_dis->Fill(pT);
		    }
		  if(w2neg)
		    {
		      //1-d
		      if(dis0) ptpid_tofw_w2_neg_0_dis->Fill(pT);
		      if(dis1) ptpid_tofw_w2_neg_1_dis->Fill(pT);
		      if(dis2) ptpid_tofw_w2_neg_2_dis->Fill(pT);
		      if(dis3) ptpid_tofw_w2_neg_3_dis->Fill(pT);
		      if(dis4) ptpid_tofw_w2_neg_4_dis->Fill(pT);
		      if(dis5) ptpid_tofw_w2_neg_5_dis->Fill(pT);
		    }
		  
		  // centrality
		  if(cent>0&&cent<=88)
		    {
		      if(w1pos)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w1_pos_0_dis_cent0088->Fill(pT);
			  if(dis1) ptpid_tofw_w1_pos_1_dis_cent0088->Fill(pT);
			  if(dis2) ptpid_tofw_w1_pos_2_dis_cent0088->Fill(pT);
			  if(dis3) ptpid_tofw_w1_pos_3_dis_cent0088->Fill(pT);
			  if(dis4) ptpid_tofw_w1_pos_4_dis_cent0088->Fill(pT);
			  if(dis5) ptpid_tofw_w1_pos_5_dis_cent0088->Fill(pT);
			}
		      if(w1neg)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w1_neg_0_dis_cent0088->Fill(pT);
			  if(dis1) ptpid_tofw_w1_neg_1_dis_cent0088->Fill(pT);
			  if(dis2) ptpid_tofw_w1_neg_2_dis_cent0088->Fill(pT);
			  if(dis3) ptpid_tofw_w1_neg_3_dis_cent0088->Fill(pT);
			  if(dis4) ptpid_tofw_w1_neg_4_dis_cent0088->Fill(pT);
			  if(dis5) ptpid_tofw_w1_neg_5_dis_cent0088->Fill(pT);
			}
		      if(w2pos)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w2_pos_0_dis_cent0088->Fill(pT);
			  if(dis1) ptpid_tofw_w2_pos_1_dis_cent0088->Fill(pT);
			  if(dis2) ptpid_tofw_w2_pos_2_dis_cent0088->Fill(pT);
			  if(dis3) ptpid_tofw_w2_pos_3_dis_cent0088->Fill(pT);
			  if(dis4) ptpid_tofw_w2_pos_4_dis_cent0088->Fill(pT);
			  if(dis5) ptpid_tofw_w2_pos_5_dis_cent0088->Fill(pT);
			}
		      if(w2neg)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w2_neg_0_dis_cent0088->Fill(pT);
			  if(dis1) ptpid_tofw_w2_neg_1_dis_cent0088->Fill(pT);
			  if(dis2) ptpid_tofw_w2_neg_2_dis_cent0088->Fill(pT);
			  if(dis3) ptpid_tofw_w2_neg_3_dis_cent0088->Fill(pT);
			  if(dis4) ptpid_tofw_w2_neg_4_dis_cent0088->Fill(pT);
			  if(dis5) ptpid_tofw_w2_neg_5_dis_cent0088->Fill(pT);
			}
		    }
		  if(cent>0&&cent<=20)
		    {
		      if(w1pos)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w1_pos_0_dis_cent0020->Fill(pT);
			  if(dis1) ptpid_tofw_w1_pos_1_dis_cent0020->Fill(pT);
			  if(dis2) ptpid_tofw_w1_pos_2_dis_cent0020->Fill(pT);
			  if(dis3) ptpid_tofw_w1_pos_3_dis_cent0020->Fill(pT);
			  if(dis4) ptpid_tofw_w1_pos_4_dis_cent0020->Fill(pT);
			  if(dis5) ptpid_tofw_w1_pos_5_dis_cent0020->Fill(pT);
			}
		      if(w1neg)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w1_neg_0_dis_cent0020->Fill(pT);
			  if(dis1) ptpid_tofw_w1_neg_1_dis_cent0020->Fill(pT);
			  if(dis2) ptpid_tofw_w1_neg_2_dis_cent0020->Fill(pT);
			  if(dis3) ptpid_tofw_w1_neg_3_dis_cent0020->Fill(pT);
			  if(dis4) ptpid_tofw_w1_neg_4_dis_cent0020->Fill(pT);
			  if(dis5) ptpid_tofw_w1_neg_5_dis_cent0020->Fill(pT);
			}
		      if(w2pos)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w2_pos_0_dis_cent0020->Fill(pT);
			  if(dis1) ptpid_tofw_w2_pos_1_dis_cent0020->Fill(pT);
			  if(dis2) ptpid_tofw_w2_pos_2_dis_cent0020->Fill(pT);
			  if(dis3) ptpid_tofw_w2_pos_3_dis_cent0020->Fill(pT);
			  if(dis4) ptpid_tofw_w2_pos_4_dis_cent0020->Fill(pT);
			  if(dis5) ptpid_tofw_w2_pos_5_dis_cent0020->Fill(pT);
			}
		      if(w2neg)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w2_neg_0_dis_cent0020->Fill(pT);
			  if(dis1) ptpid_tofw_w2_neg_1_dis_cent0020->Fill(pT);
			  if(dis2) ptpid_tofw_w2_neg_2_dis_cent0020->Fill(pT);
			  if(dis3) ptpid_tofw_w2_neg_3_dis_cent0020->Fill(pT);
			  if(dis4) ptpid_tofw_w2_neg_4_dis_cent0020->Fill(pT);
			  if(dis5) ptpid_tofw_w2_neg_5_dis_cent0020->Fill(pT);
			}
		    }
		  if(cent>20&&cent<=40)
		    {
		      if(w1pos)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w1_pos_0_dis_cent2040->Fill(pT);
			  if(dis1) ptpid_tofw_w1_pos_1_dis_cent2040->Fill(pT);
			  if(dis2) ptpid_tofw_w1_pos_2_dis_cent2040->Fill(pT);
			  if(dis3) ptpid_tofw_w1_pos_3_dis_cent2040->Fill(pT);
			  if(dis4) ptpid_tofw_w1_pos_4_dis_cent2040->Fill(pT);
			  if(dis5) ptpid_tofw_w1_pos_5_dis_cent2040->Fill(pT);
			}
		      if(w1neg)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w1_neg_0_dis_cent2040->Fill(pT);
			  if(dis1) ptpid_tofw_w1_neg_1_dis_cent2040->Fill(pT);
			  if(dis2) ptpid_tofw_w1_neg_2_dis_cent2040->Fill(pT);
			  if(dis3) ptpid_tofw_w1_neg_3_dis_cent2040->Fill(pT);
			  if(dis4) ptpid_tofw_w1_neg_4_dis_cent2040->Fill(pT);
			  if(dis5) ptpid_tofw_w1_neg_5_dis_cent2040->Fill(pT);
			}
		      if(w2pos)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w2_pos_0_dis_cent2040->Fill(pT);
			  if(dis1) ptpid_tofw_w2_pos_1_dis_cent2040->Fill(pT);
			  if(dis2) ptpid_tofw_w2_pos_2_dis_cent2040->Fill(pT);
			  if(dis3) ptpid_tofw_w2_pos_3_dis_cent2040->Fill(pT);
			  if(dis4) ptpid_tofw_w2_pos_4_dis_cent2040->Fill(pT);
			  if(dis5) ptpid_tofw_w2_pos_5_dis_cent2040->Fill(pT);
			}
		      if(w2neg)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w2_neg_0_dis_cent2040->Fill(pT);
			  if(dis1) ptpid_tofw_w2_neg_1_dis_cent2040->Fill(pT);
			  if(dis2) ptpid_tofw_w2_neg_2_dis_cent2040->Fill(pT);
			  if(dis3) ptpid_tofw_w2_neg_3_dis_cent2040->Fill(pT);
			  if(dis4) ptpid_tofw_w2_neg_4_dis_cent2040->Fill(pT);
			  if(dis5) ptpid_tofw_w2_neg_5_dis_cent2040->Fill(pT);
			}
		    }
		  if(cent>40&&cent<=60)
		    {
		      if(w1pos)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w1_pos_0_dis_cent4060->Fill(pT);
			  if(dis1) ptpid_tofw_w1_pos_1_dis_cent4060->Fill(pT);
			  if(dis2) ptpid_tofw_w1_pos_2_dis_cent4060->Fill(pT);
			  if(dis3) ptpid_tofw_w1_pos_3_dis_cent4060->Fill(pT);
			  if(dis4) ptpid_tofw_w1_pos_4_dis_cent4060->Fill(pT);
			  if(dis5) ptpid_tofw_w1_pos_5_dis_cent4060->Fill(pT);
			}
		      if(w1neg)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w1_neg_0_dis_cent4060->Fill(pT);
			  if(dis1) ptpid_tofw_w1_neg_1_dis_cent4060->Fill(pT);
			  if(dis2) ptpid_tofw_w1_neg_2_dis_cent4060->Fill(pT);
			  if(dis3) ptpid_tofw_w1_neg_3_dis_cent4060->Fill(pT);
			  if(dis4) ptpid_tofw_w1_neg_4_dis_cent4060->Fill(pT);
			  if(dis5) ptpid_tofw_w1_neg_5_dis_cent4060->Fill(pT);
			}
		      if(w2pos)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w2_pos_0_dis_cent4060->Fill(pT);
			  if(dis1) ptpid_tofw_w2_pos_1_dis_cent4060->Fill(pT);
			  if(dis2) ptpid_tofw_w2_pos_2_dis_cent4060->Fill(pT);
			  if(dis3) ptpid_tofw_w2_pos_3_dis_cent4060->Fill(pT);
			  if(dis4) ptpid_tofw_w2_pos_4_dis_cent4060->Fill(pT);
			  if(dis5) ptpid_tofw_w2_pos_5_dis_cent4060->Fill(pT);
			}
		      if(w2neg)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w2_neg_0_dis_cent4060->Fill(pT);
			  if(dis1) ptpid_tofw_w2_neg_1_dis_cent4060->Fill(pT);
			  if(dis2) ptpid_tofw_w2_neg_2_dis_cent4060->Fill(pT);
			  if(dis3) ptpid_tofw_w2_neg_3_dis_cent4060->Fill(pT);
			  if(dis4) ptpid_tofw_w2_neg_4_dis_cent4060->Fill(pT);
			  if(dis5) ptpid_tofw_w2_neg_5_dis_cent4060->Fill(pT);
			}
		    }
		  if(cent>60&&cent<=88)
		    {
		      if(w1pos)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w1_pos_0_dis_cent6088->Fill(pT);
			  if(dis1) ptpid_tofw_w1_pos_1_dis_cent6088->Fill(pT);
			  if(dis2) ptpid_tofw_w1_pos_2_dis_cent6088->Fill(pT);
			  if(dis3) ptpid_tofw_w1_pos_3_dis_cent6088->Fill(pT);
			  if(dis4) ptpid_tofw_w1_pos_4_dis_cent6088->Fill(pT);
			  if(dis5) ptpid_tofw_w1_pos_5_dis_cent6088->Fill(pT);
			}
		      if(w1neg)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w1_neg_0_dis_cent6088->Fill(pT);
			  if(dis1) ptpid_tofw_w1_neg_1_dis_cent6088->Fill(pT);
			  if(dis2) ptpid_tofw_w1_neg_2_dis_cent6088->Fill(pT);
			  if(dis3) ptpid_tofw_w1_neg_3_dis_cent6088->Fill(pT);
			  if(dis4) ptpid_tofw_w1_neg_4_dis_cent6088->Fill(pT);
			  if(dis5) ptpid_tofw_w1_neg_5_dis_cent6088->Fill(pT);
			}
		      if(w2pos)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w2_pos_0_dis_cent6088->Fill(pT);
			  if(dis1) ptpid_tofw_w2_pos_1_dis_cent6088->Fill(pT);
			  if(dis2) ptpid_tofw_w2_pos_2_dis_cent6088->Fill(pT);
			  if(dis3) ptpid_tofw_w2_pos_3_dis_cent6088->Fill(pT);
			  if(dis4) ptpid_tofw_w2_pos_4_dis_cent6088->Fill(pT);
			  if(dis5) ptpid_tofw_w2_pos_5_dis_cent6088->Fill(pT);
			}
		      if(w2neg)
			{
			  //1-d
			  if(dis0) ptpid_tofw_w2_neg_0_dis_cent6088->Fill(pT);
			  if(dis1) ptpid_tofw_w2_neg_1_dis_cent6088->Fill(pT);
			  if(dis2) ptpid_tofw_w2_neg_2_dis_cent6088->Fill(pT);
			  if(dis3) ptpid_tofw_w2_neg_3_dis_cent6088->Fill(pT);
			  if(dis4) ptpid_tofw_w2_neg_4_dis_cent6088->Fill(pT);
			  if(dis5) ptpid_tofw_w2_neg_5_dis_cent6088->Fill(pT);
			}
		    }
		}//regular cuts
	      
	      
	      // ---------------------------- //
	      // --- end of tofw only pid --- //
	      // ---------------------------- //
	      
	      // -------------------------- //
	      // --- now to do tofe pid --- //
	      // -------------------------- //

	      isPi = isPionE(pT,m2tofe);
	      isK = isKaonE(pT,m2tofe);
	      isP = isProtonE(pT,m2tofe);

	      // pid distributions
	      dis0 = eastarm && isPi>=-2 && isPi<=2;
	      dis1 = eastarm && isPi>=-2 && isPi<=2 && isK<=-2;
	      dis2 = eastarm && isK>=-2 && isK<=2;
	      dis3 = eastarm && isK>=-2 && isK<=2 && isPi>=2 && isP<=-2;
	      dis4 = eastarm && isP>=-2 && isP<=2;
	      dis5 = eastarm && isP>=-2 && isP<=2 && isK>=2;

	      if(irregular_cuts)
		{
		  // both sectors together
		  if(charge>0)
		    {
		      if(dis0) ptpid_tofe_pos_0_dis->Fill(pT);
		      if(dis1) ptpid_tofe_pos_1_dis->Fill(pT);
		      if(dis2) ptpid_tofe_pos_2_dis->Fill(pT);
		      if(dis3) ptpid_tofe_pos_3_dis->Fill(pT);
		      if(dis4) ptpid_tofe_pos_4_dis->Fill(pT);
		      if(dis5) ptpid_tofe_pos_5_dis->Fill(pT);
		    }
		  if(charge<0)
		    {
		      //1-d
		      if(dis0) ptpid_tofe_neg_0_dis->Fill(pT);
		      if(dis1) ptpid_tofe_neg_1_dis->Fill(pT);
		      if(dis2) ptpid_tofe_neg_2_dis->Fill(pT);
		      if(dis3) ptpid_tofe_neg_3_dis->Fill(pT);
		      if(dis4) ptpid_tofe_neg_4_dis->Fill(pT);
		      if(dis5) ptpid_tofe_neg_5_dis->Fill(pT);
		    }
		  
		  // centrality, both sectors together
		  if(cent>0&&cent<=88)
		    {
		      if(charge>0)
			{
			  if(dis0) ptpid_tofe_pos_0_dis_cent0088->Fill(pT);
			  if(dis1) ptpid_tofe_pos_1_dis_cent0088->Fill(pT);
			  if(dis2) ptpid_tofe_pos_2_dis_cent0088->Fill(pT);
			  if(dis3) ptpid_tofe_pos_3_dis_cent0088->Fill(pT);
			  if(dis4) ptpid_tofe_pos_4_dis_cent0088->Fill(pT);
			  if(dis5) ptpid_tofe_pos_5_dis_cent0088->Fill(pT);
			}
		      if(charge<0)
			{
			  //1-d
			  if(dis0) ptpid_tofe_neg_0_dis_cent0088->Fill(pT);
			  if(dis1) ptpid_tofe_neg_1_dis_cent0088->Fill(pT);
			  if(dis2) ptpid_tofe_neg_2_dis_cent0088->Fill(pT);
			  if(dis3) ptpid_tofe_neg_3_dis_cent0088->Fill(pT);
			  if(dis4) ptpid_tofe_neg_4_dis_cent0088->Fill(pT);
			  if(dis5) ptpid_tofe_neg_5_dis_cent0088->Fill(pT);
			}
		    }
		  if(cent>0&&cent<=20)
		    {
		      if(charge>0)
			{
			  if(dis0) ptpid_tofe_pos_0_dis_cent0020->Fill(pT);
			  if(dis1) ptpid_tofe_pos_1_dis_cent0020->Fill(pT);
			  if(dis2) ptpid_tofe_pos_2_dis_cent0020->Fill(pT);
			  if(dis3) ptpid_tofe_pos_3_dis_cent0020->Fill(pT);
			  if(dis4) ptpid_tofe_pos_4_dis_cent0020->Fill(pT);
			  if(dis5) ptpid_tofe_pos_5_dis_cent0020->Fill(pT);
			}
		      if(charge<0)
			{
			  //1-d
			  if(dis0) ptpid_tofe_neg_0_dis_cent0020->Fill(pT);
			  if(dis1) ptpid_tofe_neg_1_dis_cent0020->Fill(pT);
			  if(dis2) ptpid_tofe_neg_2_dis_cent0020->Fill(pT);
			  if(dis3) ptpid_tofe_neg_3_dis_cent0020->Fill(pT);
			  if(dis4) ptpid_tofe_neg_4_dis_cent0020->Fill(pT);
			  if(dis5) ptpid_tofe_neg_5_dis_cent0020->Fill(pT);
			}
		    }
		  if(cent>20&&cent<=40)
		    {
		      if(charge>0)
			{
			  if(dis0) ptpid_tofe_pos_0_dis_cent2040->Fill(pT);
			  if(dis1) ptpid_tofe_pos_1_dis_cent2040->Fill(pT);
			  if(dis2) ptpid_tofe_pos_2_dis_cent2040->Fill(pT);
			  if(dis3) ptpid_tofe_pos_3_dis_cent2040->Fill(pT);
			  if(dis4) ptpid_tofe_pos_4_dis_cent2040->Fill(pT);
			  if(dis5) ptpid_tofe_pos_5_dis_cent2040->Fill(pT);
			}
		      if(charge<0)
			{
			  //1-d
			  if(dis0) ptpid_tofe_neg_0_dis_cent2040->Fill(pT);
			  if(dis1) ptpid_tofe_neg_1_dis_cent2040->Fill(pT);
			  if(dis2) ptpid_tofe_neg_2_dis_cent2040->Fill(pT);
			  if(dis3) ptpid_tofe_neg_3_dis_cent2040->Fill(pT);
			  if(dis4) ptpid_tofe_neg_4_dis_cent2040->Fill(pT);
			  if(dis5) ptpid_tofe_neg_5_dis_cent2040->Fill(pT);
			}
		    }
		  if(cent>40&&cent<=60)
		    {
		      if(charge>0)
			{
			  if(dis0) ptpid_tofe_pos_0_dis_cent4060->Fill(pT);
			  if(dis1) ptpid_tofe_pos_1_dis_cent4060->Fill(pT);
			  if(dis2) ptpid_tofe_pos_2_dis_cent4060->Fill(pT);
			  if(dis3) ptpid_tofe_pos_3_dis_cent4060->Fill(pT);
			  if(dis4) ptpid_tofe_pos_4_dis_cent4060->Fill(pT);
			  if(dis5) ptpid_tofe_pos_5_dis_cent4060->Fill(pT);
			}
		      if(charge<0)
			{
			  //1-d
			  if(dis0) ptpid_tofe_neg_0_dis_cent4060->Fill(pT);
			  if(dis1) ptpid_tofe_neg_1_dis_cent4060->Fill(pT);
			  if(dis2) ptpid_tofe_neg_2_dis_cent4060->Fill(pT);
			  if(dis3) ptpid_tofe_neg_3_dis_cent4060->Fill(pT);
			  if(dis4) ptpid_tofe_neg_4_dis_cent4060->Fill(pT);
			  if(dis5) ptpid_tofe_neg_5_dis_cent4060->Fill(pT);
			}
		    }
		  if(cent>60&&cent<=88)
		    {
		      if(charge>0)
			{
			  if(dis0) ptpid_tofe_pos_0_dis_cent6088->Fill(pT);
			  if(dis1) ptpid_tofe_pos_1_dis_cent6088->Fill(pT);
			  if(dis2) ptpid_tofe_pos_2_dis_cent6088->Fill(pT);
			  if(dis3) ptpid_tofe_pos_3_dis_cent6088->Fill(pT);
			  if(dis4) ptpid_tofe_pos_4_dis_cent6088->Fill(pT);
			  if(dis5) ptpid_tofe_pos_5_dis_cent6088->Fill(pT);
			}
		      if(charge<0)
			{
			  //1-d
			  if(dis0) ptpid_tofe_neg_0_dis_cent6088->Fill(pT);
			  if(dis1) ptpid_tofe_neg_1_dis_cent6088->Fill(pT);
			  if(dis2) ptpid_tofe_neg_2_dis_cent6088->Fill(pT);
			  if(dis3) ptpid_tofe_neg_3_dis_cent6088->Fill(pT);
			  if(dis4) ptpid_tofe_neg_4_dis_cent6088->Fill(pT);
			  if(dis5) ptpid_tofe_neg_5_dis_cent6088->Fill(pT);
			}
		    }
		}//irregular cuts
	      
	      
	      // ---------------------------- //
	      // --- end of tofe only pid --- //
	      // ---------------------------- //


	      // ---------------------------- //
	      // --- Done with track loop --- //
	      // ---------------------------- //
	      
	    } // End of track loop

	  // only count as good event if at least one track is used
	  if(ngoodtofwtracks_snglevent>0) ngoodtofwevents++;
 
	} // End of event loop

      t->Delete();
      delete ktree;
      f->Close();
      delete f;

    } // End of pDST loop

  mData->Write();  
  mData->Close();

  cout<<"Number of events: "<<nevents<<endl;
  cout<<"Number of good TOFW events: "<<ngoodtofwevents<<endl;
  cout<<"Number of tracks: "<<ntracks<<endl;
  cout<<"Number of good TOFW tracks: "<<ngoodtofwtracks<<endl;

  gettimeofday(&Time,0);
  int endtime = Time.tv_sec;
  //cout<<"endtime is "<<endtime<<endl;

  int tdiff = endtime-begintime;

  cout<<"End of program."<<endl;
  cout<<"Execution time: "<<tdiff<<" seconds"<<endl;

  exit(0); 

} 


void GetRunIndex()
{

  string s;
  ifstream f("runs.list");
  if(!f)
    {
      cerr << "Couldn't open file\n";
      exit(1);
    }
  
  int j=0;
  
  while(getline(f,s))
    {
      //cout << s << '\n';
      myMap.insert(make_pair(s,j));
      j++;
    }  

  return;  

}


bool goodStrip(int i)
{
  if((i>=0 &&i<= 7)||
     (i>=12&&i<=15)||
     (i>=20&&i<=23)||
     (i>=28&&i<=31)||
     (i>=36&&i<=39)||
     (i>=44&&i<=47)||
     (i>=52&&i<=55)||
     (i>=60&&i<=63)||
     //i==19||i==161||i==372||i==394||i==460) // from shengli
     i==19||i==79||i==161||i==372||i==394||i==460) // my revision
    //i==176||i==288||i==308||i==316||i==320||i==360) // commented out by shengli, agrees with my results
    return false;//need reproduction
  else return true;
}


void fetchRunOffset()
{
  ifstream fin("run-by-run-pass4.dat");
  if(!fin)
    {
      cout<<"Warning! Cannot open run-by-run offset file"<<endl;
      return;
    }
  float tmp=-9999;
  int runnum=-9999;
  for(int i=0; i<848; i++)
    {
      fin>>runnum;
      fin>>tmp;
      fin>>runoffset[i];
      fin>>tmp>>tmp>>tmp;
    }
  fin.close();
  return;
}


void fetchStripOffset()
{
  ifstream fin("strip-by-strip-pass4.dat");
  if(!fin)
    {
      cout<<"Warning! Cannot open strip-by-strip offset file"<<endl;
      return;
    }
  for(int i=0; i<512; i++)
    {
      float tmp=-9999;
      int striptofw=-9999;
      fin>>striptofw>>tmp>>stripoffset[i]>>tmp>>tmp>>tmp;
      if(striptofw!=i) 
	{
	  cout<<"SERIOUS ERROR! stripid in strip-by-strip offset file does not match index"<<endl;
	  cout<<"stripid is "<<striptofw<<" but index is "<<i<<endl;
	  exit(1);
	}
    }
  fin.close();
  return;
}


void fetchSlewingOffset()
{
  ifstream file("shengli_slewing.dat");
  if(!file)
    {
      cout<<"Warning! Cannot open slewing correction file"<<endl;
      return;
    }

  int istrip;
  float tmp;
  while(!file.eof())
    {
      file>>istrip>>tmp>>Slewing_A[istrip]>>Slewing_B[istrip]>>tmp>>tmp>>tmp>>tmp;
    }
  file.close();
  return ;
}


void fetchMatching()
{
  int stripid;
  ifstream fin_plusplus("residuals-plusplus-pass2.dat");
  if(!fin_plusplus) 
    {
      cout<<"Warning! Cannot find residual matching file"<<endl;
      return;
    }
  for(int i=0; i<512; i++)
    {
      fin_plusplus>>stripid;
      //there needs to be a break here for some reason...........
      fin_plusplus>>mean_dz_pos_plusplus[stripid]>>mean_dz_neg_plusplus[stripid]>>mean_dphi_pos_plusplus[stripid]>>mean_dphi_neg_plusplus[stripid];
      if(stripid!=i)
	{
	  cout<<"SERIOUS ERROR!  stripid in residual matching file does not match index"<<endl;
	  cout<<"strip is is "<<stripid<<" but index is "<<i<<endl;
	  exit(1);
	}
    }
  fin_plusplus.close();
  ifstream fin_minusminus("residuals-minusminus-pass2.dat");
  if(!fin_minusminus) 
    {
      cout<<"Warning! Cannot find residual matching file"<<endl;
      return;
    }
  for(int i=0; i<512; i++)
    {
      fin_minusminus>>stripid;
      //there needs to be a break here for some reason...........
      fin_minusminus>>mean_dz_pos_minusminus[stripid]>>mean_dz_neg_minusminus[stripid]>>mean_dphi_pos_minusminus[stripid]>>mean_dphi_neg_minusminus[stripid];
      if(stripid!=i)
	{
	  cout<<"SERIOUS ERROR!  stripid in residual matching file does not match index"<<endl;
	  cout<<"strip is is "<<stripid<<" but index is "<<i<<endl;
	  exit(1);
	}
    }
  fin_minusminus.close();
  return;
}


float slewingoffset(int strip, float adc)
{
  float par = 0.4;
  float offset = Slewing_A[strip]+Slewing_B[strip]/pow(adc,par);
  return offset;  
}


float sigma_tofwdz(int charge, float mom, float tofwdz)
{
  float mean = -9999;
  float sigma = -9999;
  float value = -9999;
  if(mom<1.1||mom>1.5) return -9999;
  if(charge>0){mean=-2.974e-03; sigma=1.674e+00;}
  if(charge<0){mean=-1.671e-02; sigma=1.678e+00;}
  value = (tofwdz-mean)/sigma;
  return value;
}


float sigma_tofwdphi(int charge, float mom, float tofwdphi)
{
  float mean = -9999;
  float sigma = -9999;
  float value = -9999;
  if(mom<1.1||mom>1.5) return -9999;
  if(charge>0){mean=1.289e-04; sigma=2.095e-03;}
  if(charge<0){mean=-1.568e-03; sigma=2.165e-03;}
  value = (tofwdphi-mean)/sigma;
  return value;
}


float sigma_tofwdz_before(float mom, float tofwdz)
{
  if(mom<1.1||mom>1.5) return -9999;
  float mean = 5.35412e-01;
  float sigma = 1.85677e+00;
  float value = (tofwdz-mean)/sigma;
  return value;
}


float sigma_tofwdphi_before(float mom, float tofwdphi)
{
  if(mom<1.1||mom>1.5) return -9999;
  float mean = -3.82415e-04;
  float sigma = 2.79629e-03;
  float value = (tofwdphi-mean)/sigma;
  return value;
}

// float slewingoffset(float qtofw)
// {

//   float offset = -0.9388 + 11.64/pow(qtofw,0.5);
//   return offset;

// }

float caltofwsdz(int run, int striptofw, int charge, float zed, float mom, float tofwdz)
{

  float mean = -9999;
  float sigma = -9999;
  float value = -9999;

  if(run>250484&&striptofw<256&&charge==-1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = -2.01264 + -2.22923/mom + 0.198624/mom/mom + 4.05608/sqrt(mom);
      else if(mom>=1.0) mean = -4.20534 + -12.962/mom + 3.21798/mom/mom + 13.9799/sqrt(mom);
      sigma = 1.8858 + 0.462482/mom + 0.104371/mom/mom + -0.717956/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = 0.201275 + 0.281806/mom + -0.0311368/mom/mom + -0.430883/sqrt(mom);
      else if(mom>=1.0) mean = 1.84526 + 7.65751/mom + -2.25727/mom/mom + -7.25833/sqrt(mom);
      sigma = 2.05773 + 1.02525/mom + -0.000881981/mom/mom + -1.31723/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 0.125341 + 0.281109/mom + -0.0103479/mom/mom + -0.391107/sqrt(mom);
      else if(mom>=1.0) mean = 1.30427 + 5.90121/mom + -1.61843/mom/mom + -5.6123/sqrt(mom);
      sigma = 1.76621 + 0.216232/mom + 0.140618/mom/mom + -0.373179/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 2.98021 + 3.86248/mom + -0.381395/mom/mom + -6.4654/sqrt(mom);
      else if(mom>=1.0) mean = 0.606218 + 4.12766/mom + -1.36135/mom/mom + -3.38873/sqrt(mom);
      sigma = 2.06437 + 0.943117/mom + 0.0173967/mom/mom + -1.25726/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = -0.0633981 + 0.318759/mom + -0.0238596/mom/mom + -0.23343/sqrt(mom);
      else if(mom>=1.0) mean = 3.54814 + 15.7326/mom + -4.52858/mom/mom + -14.8112/sqrt(mom);
      sigma = 2.02621 + 0.68814/mom + 0.0901361/mom/mom + -1.07381/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = 0.900445 + 1.21436/mom + -0.13086/mom/mom + -1.95768/sqrt(mom);
      else if(mom>=1.0) mean = 0.668389 + 5.60594/mom + -1.92836/mom/mom + -4.36143/sqrt(mom);
      sigma = 1.80564 + 0.375056/mom + 0.105184/mom/mom + -0.527921/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = -0.210075 + 0.578088/mom + -0.0917194/mom/mom + -0.274022/sqrt(mom);
      else if(mom>=1.0) mean = 0.963274 + 9.6754/mom + -3.31536/mom/mom + -7.34767/sqrt(mom);
      sigma = 2.07744 + 0.813355/mom + 0.0804633/mom/mom + -1.22711/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = 1.34188 + 2.41121/mom + -0.324979/mom/mom + -3.39357/sqrt(mom);
      else if(mom>=1.0) mean = 1.98578 + 11.6526/mom + -3.71143/mom/mom + -9.93703/sqrt(mom);
      sigma = 1.95425 + 0.647739/mom + 0.0697672/mom/mom + -0.904098/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = 2.61191 + 4.50081/mom + -0.578052/mom/mom + -6.4041/sqrt(mom);
      else if(mom>=1.0) mean = 1.07424 + 12.8927/mom + -4.50748/mom/mom + -9.38109/sqrt(mom);
      sigma = 1.64426 + 0.18596/mom + 0.179195/mom/mom + -0.239326/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = 2.93192 + 5.10844/mom + -0.743913/mom/mom + -7.15891/sqrt(mom);
      else if(mom>=1.0) mean = 1.85826 + 14.0976/mom + -4.86004/mom/mom + -11.0233/sqrt(mom);
      sigma = 1.79728 + 0.383494/mom + 0.121521/mom/mom + -0.51804/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = -0.984296 + -1.26376/mom + 0.117613/mom/mom + 2.09283/sqrt(mom);
      else if(mom>=1.0) mean = -2.67559 + -10.0934/mom + 2.80997/mom/mom + 9.95667/sqrt(mom);
      sigma = 1.49385 + -0.112198/mom + 0.159713/mom/mom + 0.213054/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = -1.11653 + -1.54128/mom + 0.1579/mom/mom + 2.49549/sqrt(mom);
      else if(mom>=1.0) mean = 1.10518 + 2.80511/mom + -0.568315/mom/mom + -3.32427/sqrt(mom);
      sigma = 2.06495 + 1.06655/mom + -0.00623102/mom/mom + -1.37327/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = -1.25027 + -1.68319/mom + 0.15361/mom/mom + 2.77088/sqrt(mom);
      else if(mom>=1.0) mean = -0.899186 + -5.57989/mom + 1.8125/mom/mom + 4.70074/sqrt(mom);
      sigma = 1.84228 + 0.462316/mom + 0.0885473/mom/mom + -0.63806/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = 0.295173 + 0.211965/mom + -0.00731029/mom/mom + -0.506842/sqrt(mom);
      else if(mom>=1.0) mean = -0.989844 + -4.64626/mom + 1.31855/mom/mom + 4.31434/sqrt(mom);
      sigma = 2.09877 + 1.00515/mom + 0.0140272/mom/mom + -1.36857/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = -1.98492 + -3.21829/mom + 0.33586/mom/mom + 4.89143/sqrt(mom);
      else if(mom>=1.0) mean = -1.03187 + -7.27482/mom + 2.28507/mom/mom + 6.06266/sqrt(mom);
      sigma = 1.72473 + 0.215516/mom + 0.127946/mom/mom + -0.316989/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = 0.356433 + 0.08037/mom + 0.0259917/mom/mom + -0.469411/sqrt(mom);
      else if(mom>=1.0) mean = -2.51385 + -12.8006/mom + 3.99336/mom/mom + 11.3597/sqrt(mom);
      sigma = 2.18518 + 1.07847/mom + 0.01511/mom/mom + -1.53668/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -2.6141 + -4.02929/mom + 0.42801/mom/mom + 6.20533/sqrt(mom);
      else if(mom>=1.0) mean = -1.75443 + -12.1993/mom + 3.89681/mom/mom + 10.0736/sqrt(mom);
      sigma = 1.61384 + -0.0895259/mom + 0.176818/mom/mom + 0.0666991/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -3.87415 + -5.20754/mom + 0.568591/mom/mom + 8.44181/sqrt(mom);
      else if(mom>=1.0) mean = -1.9436 + -11.1138/mom + 3.47018/mom/mom + 9.54135/sqrt(mom);
      sigma = 2.31828 + 1.37733/mom + -0.0242923/mom/mom + -1.91525/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = -1.6169 + -3.17935/mom + 0.447276/mom/mom + 4.24246/sqrt(mom);
      else if(mom>=1.0) mean = -3.75017 + -22.2417/mom + 7.05895/mom/mom + 18.8999/sqrt(mom);
      sigma = 1.47007 + -0.229602/mom + 0.210489/mom/mom + 0.316812/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = -0.294532 + -1.16014/mom + 0.294548/mom/mom + 1.01132/sqrt(mom);
      else if(mom>=1.0) mean = -0.8557 + -11.2929/mom + 4.23867/mom/mom + 7.81223/sqrt(mom);
      sigma = 1.85904 + 0.461763/mom + 0.126445/mom/mom + -0.68716/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = -0.0919229 + 0.00941828/mom + -0.0094649/mom/mom + 0.127198/sqrt(mom);
      else if(mom>=1.0) mean = 2.166 + 6.27738/mom + -1.38601/mom/mom + -6.98305/sqrt(mom);
      sigma = 1.56162 + 0.206245/mom + 0.0984638/mom/mom + -0.0683332/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = 0.299561 + 0.467542/mom + -0.0362706/mom/mom + -0.728446/sqrt(mom);
      else if(mom>=1.0) mean = 1.35228 + 5.04917/mom + -1.36045/mom/mom + -5.05525/sqrt(mom);
      sigma = 1.98632 + 0.671964/mom + 0.0864345/mom/mom + -1.01984/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 2.12027 + 3.01523/mom + -0.320226/mom/mom + -4.8179/sqrt(mom);
      else if(mom>=1.0) mean = 2.73786 + 11.5286/mom + -3.34584/mom/mom + -10.9466/sqrt(mom);
      sigma = 2.12161 + 1.0951/mom + 0.00263339/mom/mom + -1.43535/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = -1.23111 + -1.15415/mom + 0.110677/mom/mom + 2.25362/sqrt(mom);
      else if(mom>=1.0) mean = 0.035215 + 2.42444/mom + -0.862371/mom/mom + -1.61862/sqrt(mom);
      sigma = 2.03289 + 0.792285/mom + 0.0697749/mom/mom + -1.16223/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = -1.48654 + -1.45191/mom + 0.10455/mom/mom + 2.81985/sqrt(mom);
      else if(mom>=1.0) mean = 1.48313 + 7.7362/mom + -2.37972/mom/mom + -6.84741/sqrt(mom);
      sigma = 1.92171 + 0.760257/mom + 0.0497491/mom/mom + -0.94872/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = 0.414626 + 0.822979/mom + -0.0667727/mom/mom + -1.15387/sqrt(mom);
      else if(mom>=1.0) mean = 0.80112 + 6.92233/mom + -2.24199/mom/mom + -5.49689/sqrt(mom);
      sigma = 2.09263 + 0.95895/mom + 0.0506358/mom/mom + -1.3754/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = 1.55399 + 2.87794/mom + -0.388745/mom/mom + -4.02725/sqrt(mom);
      else if(mom>=1.0) mean = 0.384593 + 5.99497/mom + -2.18899/mom/mom + -4.2022/sqrt(mom);
      sigma = 1.99257 + 0.842343/mom + 0.0447718/mom/mom + -1.09415/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = 1.78345 + 2.68829/mom + -0.272149/mom/mom + -4.15272/sqrt(mom);
      else if(mom>=1.0) mean = 2.76149 + 16.4511/mom + -5.16168/mom/mom + -14.0782/sqrt(mom);
      sigma = 1.94065 + 0.687271/mom + 0.0867374/mom/mom + -0.976231/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = -1.35122 + 0.149169/mom + -0.288561/mom/mom + 1.55083/sqrt(mom);
      else if(mom>=1.0) mean = 3.19757 + 18.4137/mom + -5.8794/mom/mom + -15.6724/sqrt(mom);
      sigma = 1.23925 + -0.487187/mom + 0.23234/mom/mom + 0.83731/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = 1.44226 + 3.09605/mom + -0.450693/mom/mom + -3.92814/sqrt(mom);
      else if(mom>=1.0) mean = 3.91614 + 22.603/mom + -7.14364/mom/mom + -19.2925/sqrt(mom);
      sigma = 1.99568 + 0.685269/mom + 0.128296/mom/mom + -1.05883/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = 2.42597 + 2.48386/mom + -0.19825/mom/mom + -4.7197/sqrt(mom);
      else if(mom>=1.0) mean = -1.74229 + -7.23282/mom + 2.11802/mom/mom + 6.83557/sqrt(mom);
      sigma = 1.8592 + 0.575/mom + 0.0801405/mom/mom + -0.745418/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = -1.75228 + -2.185/mom + 0.197892/mom/mom + 3.75025/sqrt(mom);
      else if(mom>=1.0) mean = -0.75157 + -3.38307/mom + 0.970865/mom/mom + 3.18414/sqrt(mom);
      sigma = 1.74648 + 0.490736/mom + 0.0729525/mom/mom + -0.564248/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = -0.446741 + -0.795589/mom + 0.09732/mom/mom + 1.14971/sqrt(mom);
      else if(mom>=1.0) mean = -0.708683 + -3.55498/mom + 1.02082/mom/mom + 3.24161/sqrt(mom);
      sigma = 2.26652 + 1.35997/mom + -0.0242315/mom/mom + -1.83573/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = -0.937332 + -1.33603/mom + 0.122776/mom/mom + 2.16557/sqrt(mom);
      else if(mom>=1.0) mean = -0.161653 + -2.49384/mom + 0.809332/mom/mom + 1.86052/sqrt(mom);
      sigma = 2.13866 + 1.04174/mom + 0.0231952/mom/mom + -1.4645/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = -1.38383 + -1.91602/mom + 0.208927/mom/mom + 3.08538/sqrt(mom);
      else if(mom>=1.0) mean = -1.43927 + -8.00562/mom + 2.43174/mom/mom + 7.01715/sqrt(mom);
      sigma = 2.32916 + 1.44588/mom + -0.0347687/mom/mom + -1.98099/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = -0.944205 + -1.82612/mom + 0.195769/mom/mom + 2.5884/sqrt(mom);
      else if(mom>=1.0) mean = -1.71019 + -9.78175/mom + 2.98334/mom/mom + 8.55365/sqrt(mom);
      sigma = 1.94061 + 0.693698/mom + 0.0640307/mom/mom + -0.958252/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -0.392707 + -1.08489/mom + 0.194746/mom/mom + 1.22933/sqrt(mom);
      else if(mom>=1.0) mean = -1.59604 + -10.7313/mom + 3.57967/mom/mom + 8.74002/sqrt(mom);
      sigma = 1.92456 + 0.776863/mom + 0.0487216/mom/mom + -0.971358/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -0.906115 + -2.12973/mom + 0.269804/mom/mom + 2.75566/sqrt(mom);
      else if(mom>=1.0) mean = -0.545772 + -8.19807/mom + 2.83576/mom/mom + 5.91303/sqrt(mom);
      sigma = 1.9675 + 0.706943/mom + 0.0686683/mom/mom + -0.990997/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = -1.38642 + -2.66637/mom + 0.445851/mom/mom + 3.49318/sqrt(mom);
      else if(mom>=1.0) mean = -2.44319 + -16.8239/mom + 5.71626/mom/mom + 13.4948/sqrt(mom);
      sigma = 1.99755 + 0.73992/mom + 0.105423/mom/mom + -1.06993/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = -1.73286 + -3.3409/mom + 0.475252/mom/mom + 4.45117/sqrt(mom);
      else if(mom>=1.0) mean = -3.81481 + -21.661/mom + 6.79021/mom/mom + 18.6124/sqrt(mom);
      sigma = 1.77706 + 0.332007/mom + 0.142964/mom/mom + -0.496762/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = -0.541892 + -0.812558/mom + 0.0816186/mom/mom + 1.28308/sqrt(mom);
      else if(mom>=1.0) mean = -0.954051 + -3.80387/mom + 1.12444/mom/mom + 3.66547/sqrt(mom);
      sigma = 1.67562 + 0.300812/mom + 0.0784305/mom/mom + -0.316802/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = 1.0942 + 1.29652/mom + -0.108497/mom/mom + -2.26513/sqrt(mom);
      else if(mom>=1.0) mean = -0.884651 + -2.06092/mom + 0.456672/mom/mom + 2.49223/sqrt(mom);
      sigma = 1.93983 + 0.729402/mom + 0.0213795/mom/mom + -0.96863/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 0.673401 + 0.7472/mom + -0.0580085/mom/mom + -1.33381/sqrt(mom);
      else if(mom>=1.0) mean = 0.18287 + 2.79189/mom + -1.14067/mom/mom + -1.85208/sqrt(mom);
      sigma = 1.97346 + 0.74301/mom + 0.0416474/mom/mom + -1.0184/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 1.72163 + 2.41046/mom + -0.24049/mom/mom + -3.91417/sqrt(mom);
      else if(mom>=1.0) mean = -0.0471491 + 2.2174/mom + -0.966346/mom/mom + -1.255/sqrt(mom);
      sigma = 1.93399 + 0.729875/mom + 0.0315069/mom/mom + -0.977921/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = -1.219 + -1.05821/mom + 0.0705652/mom/mom + 2.20626/sqrt(mom);
      else if(mom>=1.0) mean = 1.36458 + 8.17568/mom + -2.59687/mom/mom + -6.96877/sqrt(mom);
      sigma = 1.91599 + 0.776162/mom + 0.0294565/mom/mom + -1.00557/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = 2.34645 + 3.21152/mom + -0.335475/mom/mom + -5.19886/sqrt(mom);
      else if(mom>=1.0) mean = 0.348417 + 4.33744/mom + -1.48867/mom/mom + -3.18548/sqrt(mom);
      sigma = 1.79695 + 0.545148/mom + 0.0526217/mom/mom + -0.69413/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = 1.8148 + 2.84335/mom + -0.333896/mom/mom + -4.28863/sqrt(mom);
      else if(mom>=1.0) mean = 3.48989 + 17.3358/mom + -5.21716/mom/mom + -15.6354/sqrt(mom);
      sigma = 1.9951 + 0.842776/mom + 0.0344874/mom/mom + -1.16012/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = 4.51233 + 6.01986/mom + -0.659352/mom/mom + -9.8031/sqrt(mom);
      else if(mom>=1.0) mean = 0.520017 + 6.80763/mom + -2.43378/mom/mom + -4.8567/sqrt(mom);
      sigma = 1.83018 + 0.606135/mom + 0.0520331/mom/mom + -0.783439/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = 0.880248 + 2.48967/mom + -0.415289/mom/mom + -2.87673/sqrt(mom);
      else if(mom>=1.0) mean = 2.21923 + 15.942/mom + -5.24349/mom/mom + -12.8802/sqrt(mom);
      sigma = 2.05587 + 0.975946/mom + 0.0384069/mom/mom + -1.34651/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = 4.71358 + 6.66297/mom + -0.84591/mom/mom + -10.367/sqrt(mom);
      else if(mom>=1.0) mean = 1.62692 + 13.7291/mom + -4.81663/mom/mom + -10.4483/sqrt(mom);
      sigma = 1.82965 + 0.530109/mom + 0.0917188/mom/mom + -0.738725/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = 2.49232 + 2.67819/mom + -0.239944/mom/mom + -4.95554/sqrt(mom);
      else if(mom>=1.0) mean = -1.52329 + -5.97027/mom + 1.54306/mom/mom + 5.92159/sqrt(mom);
      sigma = 2.03301 + 0.939431/mom + 0.00991868/mom/mom + -1.26076/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = 1.9401 + 2.29346/mom + -0.198128/mom/mom + -4.0523/sqrt(mom);
      else if(mom>=1.0) mean = -0.752947 + -2.57678/mom + 0.632423/mom/mom + 2.65635/sqrt(mom);
      sigma = 2.00484 + 0.891807/mom + 0.00448395/mom/mom + -1.1744/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = 1.0114 + 0.786054/mom + -0.0626547/mom/mom + -1.72174/sqrt(mom);
      else if(mom>=1.0) mean = -1.4926 + -7.0609/mom + 1.95907/mom/mom + 6.60743/sqrt(mom);
      sigma = 1.56446 + 0.147636/mom + 0.104077/mom/mom + -0.0901279/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = -0.803005 + -1.07736/mom + 0.128519/mom/mom + 1.73175/sqrt(mom);
      else if(mom>=1.0) mean = -1.0967 + -5.05832/mom + 1.5255/mom/mom + 4.62059/sqrt(mom);
      sigma = 1.92881 + 0.741317/mom + 0.02987/mom/mom + -0.992277/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = 1.15935 + 0.806861/mom + -0.0548248/mom/mom + -1.90047/sqrt(mom);
      else if(mom>=1.0) mean = 0.627723 + -1.85741/mom + 0.904581/mom/mom + 0.360266/sqrt(mom);
      sigma = 1.93533 + 0.781957/mom + 0.027623/mom/mom + -1.02733/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = -0.578266 + -0.877581/mom + 0.134722/mom/mom + 1.27999/sqrt(mom);
      else if(mom>=1.0) mean = -2.09135 + -10.5544/mom + 3.33467/mom/mom + 9.32838/sqrt(mom);
      sigma = 1.77157 + 0.516464/mom + 0.0576763/mom/mom + -0.64555/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -1.78961 + -3.04845/mom + 0.352865/mom/mom + 4.44657/sqrt(mom);
      else if(mom>=1.0) mean = -1.45018 + -11.4666/mom + 3.65871/mom/mom + 9.26592/sqrt(mom);
      sigma = 1.98359 + 0.788154/mom + 0.0405084/mom/mom + -1.09906/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -1.26011 + -1.86239/mom + 0.279609/mom/mom + 2.76902/sqrt(mom);
      else if(mom>=1.0) mean = -1.42904 + -9.4595/mom + 3.15569/mom/mom + 7.69049/sqrt(mom);
      sigma = 1.62816 + 0.268514/mom + 0.100472/mom/mom + -0.302425/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = 1.33297 + 0.135116/mom + 0.170156/mom/mom + -1.76236/sqrt(mom);
      else if(mom>=1.0) mean = -1.99156 + -16.1317/mom + 5.37007/mom/mom + 12.6741/sqrt(mom);
      sigma = 1.75497 + 0.378449/mom + 0.108098/mom/mom + -0.490607/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = -2.06035 + -3.31739/mom + 0.544676/mom/mom + 4.67947/sqrt(mom);
      else if(mom>=1.0) mean = -2.32279 + -15.0474/mom + 5.0848/mom/mom + 12.1939/sqrt(mom);
      sigma = 1.70199 + 0.165244/mom + 0.169647/mom/mom + -0.340919/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = 0.617972 + 0.509209/mom + -0.0200808/mom/mom + -1.05911/sqrt(mom);
      else if(mom>=1.0) mean = -1.41479 + -4.46073/mom + 1.20103/mom/mom + 4.73255/sqrt(mom);
      sigma = 2.20411 + 1.20838/mom + -0.0267258/mom/mom + -1.65368/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = 0.861156 + 0.874603/mom + -0.0731827/mom/mom + -1.65762/sqrt(mom);
      else if(mom>=1.0) mean = -0.062007 + 0.280841/mom + -0.174998/mom/mom + -0.0611629/sqrt(mom);
      sigma = 2.21696 + 1.30024/mom + -0.0420797/mom/mom + -1.75279/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 0.871573 + 1.58638/mom + -0.182786/mom/mom + -2.30229/sqrt(mom);
      else if(mom>=1.0) mean = 0.285797 + 2.29882/mom + -0.720694/mom/mom + -1.86547/sqrt(mom);
      sigma = 2.09773 + 1.04292/mom + -0.00635903/mom/mom + -1.39424/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 1.25226 + 1.37997/mom + -0.114068/mom/mom + -2.48281/sqrt(mom);
      else if(mom>=1.0) mean = 0.101966 + 1.92509/mom + -0.721933/mom/mom + -1.28112/sqrt(mom);
      sigma = 2.37243 + 1.61028/mom + -0.0750087/mom/mom + -2.19358/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = 2.62302 + 3.51336/mom + -0.362695/mom/mom + -5.74431/sqrt(mom);
      else if(mom>=1.0) mean = -1.15637 + -0.34549/mom + -0.375083/mom/mom + 1.89814/sqrt(mom);
      sigma = 1.9603 + 0.797152/mom + 0.0268146/mom/mom + -1.05801/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = 0.750666 + 1.35552/mom + -0.159444/mom/mom + -1.94538/sqrt(mom);
      else if(mom>=1.0) mean = 1.9128 + 9.85667/mom + -2.95683/mom/mom + -8.83369/sqrt(mom);
      sigma = 2.07362 + 1.12081/mom + -0.0177659/mom/mom + -1.48312/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = 2.80365 + 4.02459/mom + -0.48236/mom/mom + -6.2956/sqrt(mom);
      else if(mom>=1.0) mean = 1.04117 + 9.5854/mom + -3.41551/mom/mom + -7.22264/sqrt(mom);
      sigma = 1.87949 + 0.772704/mom + 0.0274194/mom/mom + -0.950965/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = 1.98176 + 3.17721/mom + -0.376891/mom/mom + -4.74421/sqrt(mom);
      else if(mom>=1.0) mean = 2.895 + 15.8951/mom + -4.96969/mom/mom + -13.8517/sqrt(mom);
      sigma = 2.02135 + 1.02632/mom + -0.000818548/mom/mom + -1.34543/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = 5.31797 + 7.34429/mom + -0.901989/mom/mom + -11.6168/sqrt(mom);
      else if(mom>=1.0) mean = 0.891271 + 11.1655/mom + -4.14171/mom/mom + -7.84374/sqrt(mom);
      sigma = 1.73315 + 0.358343/mom + 0.12339/mom/mom + -0.474741/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = 1.67162 + 3.2025/mom + -0.478006/mom/mom + -4.25661/sqrt(mom);
      else if(mom>=1.0) mean = 3.15481 + 19.7988/mom + -6.39026/mom/mom + -16.4965/sqrt(mom);
      sigma = 1.96597 + 0.859286/mom + 0.0498139/mom/mom + -1.16671/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = 1.32175 + 1.68365/mom + -0.151181/mom/mom + -2.91003/sqrt(mom);
      else if(mom>=1.0) mean = -0.314603 + -1.67456/mom + 0.592112/mom/mom + 1.34399/sqrt(mom);
      sigma = 1.79525 + 0.779027/mom + 0.00333022/mom/mom + -0.820459/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = 0.0832334 + 0.00976643/mom + -0.013692/mom/mom + -0.0919365/sqrt(mom);
      else if(mom>=1.0) mean = -0.376745 + -2.19215/mom + 0.641949/mom/mom + 1.94215/sqrt(mom);
      sigma = 2.14108 + 1.13005/mom + -0.0122511/mom/mom + -1.53911/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = -1.6151 + -2.1408/mom + 0.236926/mom/mom + 3.48708/sqrt(mom);
      else if(mom>=1.0) mean = -1.03215 + -5.42958/mom + 1.70165/mom/mom + 4.73327/sqrt(mom);
      sigma = 2.05207 + 1.0335/mom + -0.00876587/mom/mom + -1.34564/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = 0.886043 + 0.561448/mom + -0.0352962/mom/mom + -1.38518/sqrt(mom);
      else if(mom>=1.0) mean = -0.678945 + -5.13034/mom + 1.66718/mom/mom + 4.19236/sqrt(mom);
      sigma = 2.17876 + 1.13813/mom + -0.00683737/mom/mom + -1.60295/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = -4.31743 + -5.18596/mom + 0.51676/mom/mom + 8.92739/sqrt(mom);
      else if(mom>=1.0) mean = -1.15101 + -7.11444/mom + 2.3709/mom/mom + 5.89955/sqrt(mom);
      sigma = 1.77999 + 0.627806/mom + 0.0451238/mom/mom + -0.729082/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = 1.31406 + 0.729107/mom + -0.0284899/mom/mom + -1.98847/sqrt(mom);
      else if(mom>=1.0) mean = -0.476882 + -5.72849/mom + 1.8797/mom/mom + 4.35448/sqrt(mom);
      sigma = 2.10651 + 1.07632/mom + -0.00314085/mom/mom + -1.48516/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -1.1556 + -1.85716/mom + 0.278838/mom/mom + 2.69102/sqrt(mom);
      else if(mom>=1.0) mean = -1.74602 + -11.7183/mom + 4.03617/mom/mom + 9.43867/sqrt(mom);
      sigma = 1.76217 + 0.572065/mom + 0.062289/mom/mom + -0.676939/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -0.565115 + -1.8374/mom + 0.256077/mom/mom + 2.13428/sqrt(mom);
      else if(mom>=1.0) mean = -3.51874 + -18.7395/mom + 5.70531/mom/mom + 16.6102/sqrt(mom);
      sigma = 1.8924 + 0.659082/mom + 0.0572412/mom/mom + -0.91036/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = -3.35195 + -4.95559/mom + 0.699575/mom/mom + 7.47805/sqrt(mom);
      else if(mom>=1.0) mean = -1.99697 + -14.712/mom + 5.15328/mom/mom + 11.5164/sqrt(mom);
      sigma = 1.74893 + 0.329297/mom + 0.14871/mom/mom + -0.500394/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = -0.801332 + -2.47601/mom + 0.426166/mom/mom + 2.68073/sqrt(mom);
      else if(mom>=1.0) mean = -3.3436 + -20.7108/mom + 6.60627/mom/mom + 17.3687/sqrt(mom);
      sigma = 1.72343 + 0.509166/mom + 0.081141/mom/mom + -0.58115/sqrt(mom);
    }
  else
    {
      cout<<"significant issue in caltofwsdz"<<endl;
      return -9999;
    }
  
  value = (tofwdz - mean)/sigma;

  return value;
  
}

float caltofwsdphi(int run, int striptofw, int charge, float zed, float mom, float tofwdphi)
{

  float mean = -9999;
  float sigma = -9999;
  float value = -9999;

  if(run>250484&&striptofw<256&&charge==-1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = -0.0111693 + -0.0179804/mom + 0.00222222/mom/mom + 0.0270516/sqrt(mom);
      else if(mom>=1.0) mean = 0.00183304 + 0.00492135/mom + -0.00137131/mom/mom + -0.00524524/sqrt(mom);
      sigma = 0.00191169 + 0.00135976/mom + 0.000109287/mom/mom + -0.00130868/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = -0.000919912 + 0.0001305/mom + -0.000223512/mom/mom + 0.00086823/sqrt(mom);
      else if(mom>=1.0) mean = -0.00129849 + -0.00972102/mom + 0.00252642/mom/mom + 0.00819793/sqrt(mom);
      sigma = 0.00212381 + 0.000325305/mom + 0.00032085/mom/mom + -0.000531452/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = -0.015294 + -0.023321/mom + 0.00271271/mom/mom + 0.0360358/sqrt(mom);
      else if(mom>=1.0) mean = 0.0019924 + 0.00667001/mom + -0.00231375/mom/mom + -0.0062737/sqrt(mom);
      sigma = 0.00104359 + -0.000946742/mom + 0.00054678/mom/mom + 0.00144582/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 0.00534339 + 0.00588622/mom + -0.000439138/mom/mom + -0.0109084/sqrt(mom);
      else if(mom>=1.0) mean = -0.00602378 + -0.0237317/mom + 0.00594976/mom/mom + 0.0235211/sqrt(mom);
      sigma = 0.00110779 + -0.00188478/mom + 0.000692939/mom/mom + 0.00232669/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = -0.0130766 + -0.020681/mom + 0.00223909/mom/mom + 0.0316848/sqrt(mom);
      else if(mom>=1.0) mean = 0.0016696 + 0.00558525/mom + -0.0023808/mom/mom + -0.0048049/sqrt(mom);
      sigma = 0.000974563 + -0.00146289/mom + 0.000717284/mom/mom + 0.00187132/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = 0.0216755 + 0.0273646/mom + -0.00237462/mom/mom + -0.0468154/sqrt(mom);
      else if(mom>=1.0) mean = -0.00447619 + -0.0192878/mom + 0.00547137/mom/mom + 0.0180053/sqrt(mom);
      sigma = 0.00154772 + -0.00142054/mom + 0.000722499/mom/mom + 0.00137071/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = -0.0104444 + -0.0178846/mom + 0.00173669/mom/mom + 0.0266979/sqrt(mom);
      else if(mom>=1.0) mean = 0.00106208 + 0.0017845/mom + -0.00150766/mom/mom + -0.00128626/sqrt(mom);
      sigma = 0.000183525 + -0.00410421/mom + 0.00128057/mom/mom + 0.00473443/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = 0.0135249 + 0.0135683/mom + -0.000249168/mom/mom + -0.0269242/sqrt(mom);
      else if(mom>=1.0) mean = -0.00466344 + -0.0192779/mom + 0.00574216/mom/mom + 0.0179905/sqrt(mom);
      sigma = 0.000713911 + -0.00386405/mom + 0.00128707/mom/mom + 0.00412818/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = 0.000584012 + -0.00391181/mom + -0.000105035/mom/mom + 0.00327875/sqrt(mom);
      else if(mom>=1.0) mean = 0.00407464 + 0.0121303/mom + -0.00474243/mom/mom + -0.0118154/sqrt(mom);
      sigma = 0.00104946 + -0.00286793/mom + 0.00119321/mom/mom + 0.00272217/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = 0.0133224 + 0.0102497/mom + 0.000941732/mom/mom + -0.0242771/sqrt(mom);
      else if(mom>=1.0) mean = -0.00586296 + -0.0231923/mom + 0.00709393/mom/mom + 0.0221364/sqrt(mom);
      sigma = 0.000806618 + -0.00413324/mom + 0.00149992/mom/mom + 0.00415258/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = 0.0195677 + 0.0296051/mom + -0.00312579/mom/mom + -0.0462729/sqrt(mom);
      else if(mom>=1.0) mean = 0.0016173 + 0.0066212/mom + -0.00232467/mom/mom + -0.00604846/sqrt(mom);
      sigma = 0.00309977 + 0.00430701/mom + -0.000321822/mom/mom + -0.00487254/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = -0.00465823 + -0.00190454/mom + -0.000223039/mom/mom + 0.00642224/sqrt(mom);
      else if(mom>=1.0) mean = 0.00193268 + 0.00582236/mom + -0.00258719/mom/mom + -0.00564887/sqrt(mom);
      sigma = 0.00100654 + -0.0018007/mom + 0.000621958/mom/mom + 0.00241433/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = 0.0146175 + 0.0236627/mom + -0.0027167/mom/mom + -0.0357543/sqrt(mom);
      else if(mom>=1.0) mean = 0.00159524 + 0.00523706/mom + -0.00186079/mom/mom + -0.00503391/sqrt(mom);
      sigma = 0.00325753 + 0.00480982/mom + -0.00041734/mom/mom + -0.00542232/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = -0.00492154 + -0.00334746/mom + 0.000168475/mom/mom + 0.00778783/sqrt(mom);
      else if(mom>=1.0) mean = 0.000478822 + 0.000597555/mom + -0.000763624/mom/mom + -0.000738741/sqrt(mom);
      sigma = 0.0010575 + -0.00185852/mom + 0.000688697/mom/mom + 0.00233713/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = 0.0174326 + 0.0273568/mom + -0.00340357/mom/mom + -0.0414791/sqrt(mom);
      else if(mom>=1.0) mean = 0.000440835 + 0.000210714/mom + -0.000714988/mom/mom + 4.56835e-05/sqrt(mom);
      sigma = 0.00386167 + 0.00581463/mom + -0.000503255/mom/mom + -0.00694218/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = -0.00939194 + -0.00967108/mom + 0.0011311/mom/mom + 0.0176254/sqrt(mom);
      else if(mom>=1.0) mean = 0.000103603 + -0.000331632/mom + -0.000157332/mom/mom + -5.03372e-05/sqrt(mom);
      sigma = 0.0010201 + -0.00292075/mom + 0.00102372/mom/mom + 0.00308206/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = 0.00887053 + 0.01669/mom + -0.00274246/mom/mom + -0.0228844/sqrt(mom);
      else if(mom>=1.0) mean = -0.000282363 + -0.00276853/mom + -0.000289164/mom/mom + 0.00333343/sqrt(mom);
      sigma = 0.00437885 + 0.00645232/mom + -0.000508818/mom/mom + -0.00808212/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -0.0137176 + -0.0159055/mom + 0.00219178/mom/mom + 0.0271417/sqrt(mom);
      else if(mom>=1.0) mean = 0.00175411 + 0.00521533/mom + -0.000584753/mom/mom + -0.00677979/sqrt(mom);
      sigma = 0.00168475 + -0.00194291/mom + 0.00106099/mom/mom + 0.00137252/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = 0.00286314 + 0.00989804/mom + -0.00256251/mom/mom + -0.0106085/sqrt(mom);
      else if(mom>=1.0) mean = -0.000129154 + -0.00201676/mom + -0.000793747/mom/mom + 0.00257634/sqrt(mom);
      sigma = 0.00386224 + 0.00494676/mom + -0.000200333/mom/mom + -0.006409/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = -0.0133634 + -0.0173316/mom + 0.00295682/mom/mom + 0.0277825/sqrt(mom);
      else if(mom>=1.0) mean = -0.00404202 + -0.0134408/mom + 0.0040691/mom/mom + 0.0133807/sqrt(mom);
      sigma = -0.000240179 + -0.00685185/mom + 0.00191014/mom/mom + 0.00738224/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = 0.00497067 + 0.00504253/mom + -0.000397867/mom/mom + -0.0096885/sqrt(mom);
      else if(mom>=1.0) mean = -0.00686102 + -0.0257015/mom + 0.00645914/mom/mom + 0.0259457/sqrt(mom);
      sigma = 0.000391535 + -0.00314856/mom + 0.00088079/mom/mom + 0.00409002/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = -0.00658244 + -0.0132434/mom + 0.00184724/mom/mom + 0.018177/sqrt(mom);
      else if(mom>=1.0) mean = 0.00336873 + 0.00882874/mom + -0.00227332/mom/mom + -0.00981799/sqrt(mom);
      sigma = 0.00260359 + 0.00173333/mom + 0.000198245/mom/mom + -0.00242864/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 0.0118383 + 0.0116558/mom + -0.000731536/mom/mom + -0.0227902/sqrt(mom);
      else if(mom>=1.0) mean = -0.00646069 + -0.0240832/mom + 0.00614939/mom/mom + 0.0242385/sqrt(mom);
      sigma = 0.000988982 + -0.00162494/mom + 0.000638322/mom/mom + 0.0022495/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = -0.0153786 + -0.0235636/mom + 0.00270747/mom/mom + 0.0363761/sqrt(mom);
      else if(mom>=1.0) mean = 0.00556701 + 0.0165567/mom + -0.00445607/mom/mom + -0.0175503/sqrt(mom);
      sigma = 0.00246597 + 0.00136651/mom + 0.000259801/mom/mom + -0.00195345/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = 0.0277379 + 0.032566/mom + -0.00260573/mom/mom + -0.0577676/sqrt(mom);
      else if(mom>=1.0) mean = -0.00586375 + -0.0214244/mom + 0.00562504/mom/mom + 0.0214211/sqrt(mom);
      sigma = 0.00159138 + -0.00169025/mom + 0.000866726/mom/mom + 0.00145931/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = -0.0160061 + -0.0256034/mom + 0.00284247/mom/mom + 0.0389646/sqrt(mom);
      else if(mom>=1.0) mean = 0.00654846 + 0.0192498/mom + -0.00536735/mom/mom + -0.0203165/sqrt(mom);
      sigma = 0.00179042 + -0.000254583/mom + 0.00056777/mom/mom + 1.71917e-05/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = 0.015944 + 0.0149373/mom + -0.000199132/mom/mom + -0.0307251/sqrt(mom);
      else if(mom>=1.0) mean = -0.00420032 + -0.0141359/mom + 0.00380043/mom/mom + 0.0143589/sqrt(mom);
      sigma = 0.000196024 + -0.00509817/mom + 0.00157324/mom/mom + 0.00557836/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = -0.0155145 + -0.0241601/mom + 0.00226057/mom/mom + 0.0375435/sqrt(mom);
      else if(mom>=1.0) mean = 0.00237876 + 0.00529648/mom + -0.00224988/mom/mom + -0.00535953/sqrt(mom);
      sigma = 0.00143368 + -0.00185358/mom + 0.000968618/mom/mom + 0.00159879/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = 0.00644759 + 0.000963176/mom + 0.00193926/mom/mom + -0.00912479/sqrt(mom);
      else if(mom>=1.0) mean = -0.0030578 + -0.012929/mom + 0.00397234/mom/mom + 0.0121364/sqrt(mom);
      sigma = 0.000789651 + -0.00382715/mom + 0.00144045/mom/mom + 0.00390959/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = -0.0197629 + -0.0317104/mom + 0.00292317/mom/mom + 0.0483129/sqrt(mom);
      else if(mom>=1.0) mean = 0.000134067 + -0.00115549/mom + -0.00119301/mom/mom + 0.00188604/sqrt(mom);
      sigma = 0.00134475 + -0.00215417/mom + 0.00105832/mom/mom + 0.00192813/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = -0.00334595 + -0.00257423/mom + 9.42772e-05/mom/mom + 0.00556476/sqrt(mom);
      else if(mom>=1.0) mean = -0.00212209 + -0.0061724/mom + 0.00049983/mom/mom + 0.00744338/sqrt(mom);
      sigma = 0.00146502 + -0.000973019/mom + 0.000550749/mom/mom + 0.00118402/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = 0.0112664 + 0.0181233/mom + -0.00192965/mom/mom + -0.027632/sqrt(mom);
      else if(mom>=1.0) mean = 0.00508141 + 0.0168378/mom + -0.0048183/mom/mom + -0.0172226/sqrt(mom);
      sigma = 0.00372493 + 0.00521081/mom + -0.000407918/mom/mom + -0.0063168/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = -0.00316202 + -0.00221388/mom + 0.00017731/mom/mom + 0.00493534/sqrt(mom);
      else if(mom>=1.0) mean = -0.00117097 + -0.00311082/mom + -0.000162393/mom/mom + 0.00403029/sqrt(mom);
      sigma = 0.00100455 + -0.00211671/mom + 0.000769257/mom/mom + 0.00253085/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = 0.0124325 + 0.0195136/mom + -0.00218234/mom/mom + -0.0298942/sqrt(mom);
      else if(mom>=1.0) mean = 0.00378734 + 0.0113938/mom + -0.00330086/mom/mom + -0.0119498/sqrt(mom);
      sigma = 0.00413372 + 0.00586509/mom + -0.000470723/mom/mom + -0.00731797/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = -0.00950612 + -0.0110111/mom + 0.00146137/mom/mom + 0.0187512/sqrt(mom);
      else if(mom>=1.0) mean = -0.00680386 + -0.0219407/mom + 0.0052146/mom/mom + 0.0231411/sqrt(mom);
      sigma = 0.00118249 + -0.00283605/mom + 0.00108526/mom/mom + 0.00270569/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = 0.0119743 + 0.0198206/mom + -0.00258994/mom/mom + -0.029287/sqrt(mom);
      else if(mom>=1.0) mean = 0.00520967 + 0.0151219/mom + -0.00447717/mom/mom + -0.0159136/sqrt(mom);
      sigma = 0.00452915 + 0.00656287/mom + -0.000533057/mom/mom + -0.00834097/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -0.00805064 + -0.009515/mom + 0.00166024/mom/mom + 0.0156881/sqrt(mom);
      else if(mom>=1.0) mean = -0.000731162 + -0.00112739/mom + 0.000704835/mom/mom + 0.000779115/sqrt(mom);
      sigma = 0.00137405 + -0.00282142/mom + 0.00126289/mom/mom + 0.00233208/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = 0.0054322 + 0.0118652/mom + -0.00221914/mom/mom + -0.0151661/sqrt(mom);
      else if(mom>=1.0) mean = 0.000128165 + -0.00300757/mom + 8.70517e-05/mom/mom + 0.00279913/sqrt(mom);
      sigma = 0.00480329 + 0.00701564/mom + -0.000548736/mom/mom + -0.00900075/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = -0.0106116 + -0.0143839/mom + 0.00275205/mom/mom + 0.0223392/sqrt(mom);
      else if(mom>=1.0) mean = -0.00131478 + -0.00542669/mom + 0.00210068/mom/mom + 0.00461257/sqrt(mom);
      sigma = 0.000417882 + -0.00542497/mom + 0.00173107/mom/mom + 0.00545199/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = 0.00229806 + 0.00883081/mom + -0.00241183/mom/mom + -0.00915319/sqrt(mom);
      else if(mom>=1.0) mean = -0.000744112 + -0.00327571/mom + -0.000597993/mom/mom + 0.00421884/sqrt(mom);
      sigma = 0.00428314 + 0.00582874/mom + -0.000362426/mom/mom + -0.00748534/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = 0.0150518 + 0.019115/mom + -0.00181246/mom/mom + -0.0322523/sqrt(mom);
      else if(mom>=1.0) mean = 0.00168405 + 0.00500783/mom + -0.00118996/mom/mom + -0.00538902/sqrt(mom);
      sigma = 0.000934249 + -0.000297245/mom + 0.000183313/mom/mom + 0.0013952/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = -0.0245686 + -0.028583/mom + 0.00249109/mom/mom + 0.0504303/sqrt(mom);
      else if(mom>=1.0) mean = -0.00378089 + -0.0115843/mom + 0.00266955/mom/mom + 0.0125527/sqrt(mom);
      sigma = 0.00160332 + 0.000275894/mom + 0.000182243/mom/mom + 1.13411e-05/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 0.00293425 + 0.00488742/mom + -0.00060633/mom/mom + -0.00712365/sqrt(mom);
      else if(mom>=1.0) mean = -0.000397719 + -0.00646269/mom + 0.00261868/mom/mom + 0.00428986/sqrt(mom);
      sigma = -0.000315782 + -0.00277596/mom + 0.00055071/mom/mom + 0.00483398/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 0.00208679 + 0.00464515/mom + -0.000524755/mom/mom + -0.00651239/sqrt(mom);
      else if(mom>=1.0) mean = -0.00439634 + -0.0124428/mom + 0.00232458/mom/mom + 0.0142139/sqrt(mom);
      sigma = -0.000941359 + -0.00529102/mom + 0.000976552/mom/mom + 0.00741683/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = 0.00863763 + 0.0110055/mom + -0.00137707/mom/mom + -0.0179944/sqrt(mom);
      else if(mom>=1.0) mean = 0.00269171 + 0.00424032/mom + -0.000639582/mom/mom + -0.00600465/sqrt(mom);
      sigma = 0.00019161 + -0.00264161/mom + 0.000685036/mom/mom + 0.00397294/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = -0.0244563 + -0.027964/mom + 0.0027828/mom/mom + 0.0492034/sqrt(mom);
      else if(mom>=1.0) mean = -0.0040733 + -0.0121524/mom + 0.00310502/mom/mom + 0.0128271/sqrt(mom);
      sigma = 0.000565877 + -0.00308507/mom + 0.000902665/mom/mom + 0.00369277/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = 0.00807054 + 0.01059/mom + -0.00172233/mom/mom + -0.0167201/sqrt(mom);
      else if(mom>=1.0) mean = -0.00152662 + -0.0104726/mom + 0.00288963/mom/mom + 0.00936782/sqrt(mom);
      sigma = -8.79339e-05 + -0.0036825/mom + 0.000976747/mom/mom + 0.00499278/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = -0.0127216 + -0.0140849/mom + 0.0018727/mom/mom + 0.0245996/sqrt(mom);
      else if(mom>=1.0) mean = -0.00201549 + -0.00477047/mom + 0.00154286/mom/mom + 0.00494989/sqrt(mom);
      sigma = 0.000348629 + -0.00454768/mom + 0.00136758/mom/mom + 0.00489214/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = -0.000527628 + 0.0008419/mom + -0.00128823/mom/mom + 0.000814781/sqrt(mom);
      else if(mom>=1.0) mean = 0.00210107 + 0.00200451/mom + -0.000926133/mom/mom + -0.00332982/sqrt(mom);
      sigma = 0.000616358 + -0.00264165/mom + 0.000927417/mom/mom + 0.00327186/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = -0.0180575 + -0.0215866/mom + 0.003169/mom/mom + 0.0364398/sqrt(mom);
      else if(mom>=1.0) mean = -0.00316988 + -0.00827443/mom + 0.00281248/mom/mom + 0.00867462/sqrt(mom);
      sigma = -0.00043605 + -0.00698349/mom + 0.00189348/mom/mom + 0.00759933/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = 0.0229129 + 0.021823/mom + -0.00158183/mom/mom + -0.0425446/sqrt(mom);
      else if(mom>=1.0) mean = 0.00619534 + 0.0250281/mom + -0.00654733/mom/mom + -0.0242121/sqrt(mom);
      sigma = -0.00103989 + -0.00554054/mom + 0.000985785/mom/mom + 0.00788904/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = -0.0265797 + -0.0307563/mom + 0.00268573/mom/mom + 0.0543832/sqrt(mom);
      else if(mom>=1.0) mean = -0.00697722 + -0.0203184/mom + 0.00453138/mom/mom + 0.0225178/sqrt(mom);
      sigma = 0.00158346 + 0.000309575/mom + 0.000156873/mom/mom + 0.000117302/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = 0.0158875 + 0.0136284/mom + -0.000977841/mom/mom + -0.027939/sqrt(mom);
      else if(mom>=1.0) mean = 0.003921 + 0.0188411/mom + -0.00557224/mom/mom + -0.0168326/sqrt(mom);
      sigma = -0.00112818 + -0.00597026/mom + 0.00110392/mom/mom + 0.00827921/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = -0.0138975 + -0.0160326/mom + 0.00151023/mom/mom + 0.0281766/sqrt(mom);
      else if(mom>=1.0) mean = -0.00693999 + -0.0196232/mom + 0.00450151/mom/mom + 0.0218498/sqrt(mom);
      sigma = 0.000463528 + -0.00214549/mom + 0.000548826/mom/mom + 0.00333483/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = 0.0122775 + 0.0101563/mom + -0.00100993/mom/mom + -0.020815/sqrt(mom);
      else if(mom>=1.0) mean = 0.00170264 + 0.0058075/mom + -0.00141918/mom/mom + -0.00558536/sqrt(mom);
      sigma = -0.00157399 + -0.00765202/mom + 0.00150265/mom/mom + 0.0100118/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = -0.00617191 + -0.00776933/mom + 0.00112159/mom/mom + 0.0125769/sqrt(mom);
      else if(mom>=1.0) mean = -0.00623092 + -0.0175247/mom + 0.00436918/mom/mom + 0.019116/sqrt(mom);
      sigma = -0.000332252 + -0.00442572/mom + 0.00101768/mom/mom + 0.00594409/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = 0.0136757 + 0.0131587/mom + -0.00178179/mom/mom + -0.0245288/sqrt(mom);
      else if(mom>=1.0) mean = 0.00115421 + 0.00454635/mom + -0.00177914/mom/mom + -0.00353489/sqrt(mom);
      sigma = -0.000892073 + -0.00645965/mom + 0.0014467/mom/mom + 0.00815186/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -0.00239261 + -0.0042506/mom + 0.00130935/mom/mom + 0.0051162/sqrt(mom);
      else if(mom>=1.0) mean = -0.004718 + -0.0111943/mom + 0.00293121/mom/mom + 0.0126972/sqrt(mom);
      sigma = -0.0010567 + -0.00667119/mom + 0.00153094/mom/mom + 0.00840046/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = 0.0279204 + 0.0343174/mom + -0.00453105/mom/mom + -0.0576967/sqrt(mom);
      else if(mom>=1.0) mean = -0.00175497 + -0.0102372/mom + 0.0028026/mom/mom + 0.00919784/sqrt(mom);
      sigma = 0.000730295 + -0.00300285/mom + 0.00102019/mom/mom + 0.00348338/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = -0.000422815 + -0.00386144/mom + 0.00191616/mom/mom + 0.00253134/sqrt(mom);
      else if(mom>=1.0) mean = -0.00742087 + -0.0198281/mom + 0.00547491/mom/mom + 0.0218903/sqrt(mom);
      sigma = -0.000450233 + -0.00559022/mom + 0.00144669/mom/mom + 0.00679286/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = -0.0192455 + -0.0225693/mom + 0.0019896/mom/mom + 0.039623/sqrt(mom);
      else if(mom>=1.0) mean = -0.00726099 + -0.0219162/mom + 0.00521991/mom/mom + 0.0238511/sqrt(mom);
      sigma = 0.00178016 + 0.000534475/mom + 0.000181486/mom/mom + -0.000418003/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-15&&zed<0))
    {
      if(mom<1.0) mean = 0.00796952 + 0.0107908/mom + -0.00108552/mom/mom + -0.017587/sqrt(mom);
      else if(mom>=1.0) mean = 0.0049583 + 0.0142444/mom + -0.00333584/mom/mom + -0.015798/sqrt(mom);
      sigma = 0.00250988 + 0.00246705/mom + -0.000137394/mom/mom + -0.00268295/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = 0.00282511 + 0.00531444/mom + -0.000555582/mom/mom + -0.00785994/sqrt(mom);
      else if(mom>=1.0) mean = -0.0100941 + -0.0307787/mom + 0.00711995/mom/mom + 0.0335103/sqrt(mom);
      sigma = -0.000886689 + -0.00501879/mom + 0.000978759/mom/mom + 0.0070667/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-30&&zed<=-15))
    {
      if(mom<1.0) mean = -0.0033627 + -0.00189407/mom + -7.5255e-05/mom/mom + 0.00539209/sqrt(mom);
      else if(mom>=1.0) mean = 0.00522032 + 0.011838/mom + -0.00212/mom/mom + -0.014945/sqrt(mom);
      sigma = 0.00138682 + 0.000402657/mom + 0.000160806/mom/mom + 0.000282295/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = -0.0236892 + -0.0275781/mom + 0.00279082/mom/mom + 0.0480828/sqrt(mom);
      else if(mom>=1.0) mean = -0.00785671 + -0.0218373/mom + 0.00513933/mom/mom + 0.024266/sqrt(mom);
      sigma = 0.000874412 + -0.00241567/mom + 0.000839411/mom/mom + 0.00277019/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-45&&zed<=-30))
    {
      if(mom<1.0) mean = 0.00356937 + 0.00548438/mom + -0.000952027/mom/mom + -0.00783958/sqrt(mom);
      else if(mom>=1.0) mean = 0.00470801 + 0.00977546/mom + -0.00198162/mom/mom + -0.0122641/sqrt(mom);
      sigma = 0.00138923 + -0.000357262/mom + 0.000396536/mom/mom + 0.00075861/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = -0.0153723 + -0.0172962/mom + 0.00218312/mom/mom + 0.030158/sqrt(mom);
      else if(mom>=1.0) mean = -0.00597598 + -0.017135/mom + 0.00468087/mom/mom + 0.0182038/sqrt(mom);
      sigma = -0.000148274 + -0.00543036/mom + 0.0015111/mom/mom + 0.00614371/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-60&&zed<=-45))
    {
      if(mom<1.0) mean = 0.000438052 + 0.00174869/mom + -0.000938639/mom/mom + -0.00107016/sqrt(mom);
      else if(mom>=1.0) mean = 0.00146945 + -0.000776049/mom + 0.000349083/mom/mom + -0.000843265/sqrt(mom);
      sigma = 0.00138028 + -0.000633222/mom + 0.000549582/mom/mom + 0.000899618/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = -0.0207332 + -0.0245253/mom + 0.00340292/mom/mom + 0.0418194/sqrt(mom);
      else if(mom>=1.0) mean = -0.00321394 + -0.00963409/mom + 0.00338963/mom/mom + 0.00955568/sqrt(mom);
      sigma = -0.000381408 + -0.00678677/mom + 0.00186752/mom/mom + 0.00737771/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-75&&zed<=-60))
    {
      if(mom<1.0) mean = 0.00235525 + 0.00531669/mom + -0.00185515/mom/mom + -0.00599814/sqrt(mom);
      else if(mom>=1.0) mean = -0.00269547 + -0.0134437/mom + 0.00313092/mom/mom + 0.0128704/sqrt(mom);
      sigma = 0.000827205 + -0.00219639/mom + 0.000879618/mom/mom + 0.00269047/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = -0.0259888 + -0.0302742/mom + 0.00269081/mom/mom + 0.0532961/sqrt(mom);
      else if(mom>=1.0) mean = -0.00808909 + -0.0217068/mom + 0.00453431/mom/mom + 0.0250489/sqrt(mom);
      sigma = 0.00146462 + 0.000380385/mom + 0.000154586/mom/mom + 0.000172139/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=0&&zed<15))
    {
      if(mom<1.0) mean = 0.0149774 + 0.0126916/mom + -0.000788262/mom/mom + -0.0263278/sqrt(mom);
      else if(mom>=1.0) mean = 0.0112894 + 0.0402018/mom + -0.0102535/mom/mom + -0.0408511/sqrt(mom);
      sigma = 0.00126593 + -0.00160634/mom + 0.00053463/mom/mom + 0.00201931/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = -0.00947534 + -0.011962/mom + 0.0012709/mom/mom + 0.0199843/sqrt(mom);
      else if(mom>=1.0) mean = -0.00876473 + -0.0237449/mom + 0.00528444/mom/mom + 0.0270477/sqrt(mom);
      sigma = 0.0013381 + -0.000504025/mom + 0.00038554/mom/mom + 0.000968167/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=15&&zed<30))
    {
      if(mom<1.0) mean = 0.00767852 + 0.00416046/mom + -0.00014392/mom/mom + -0.0111481/sqrt(mom);
      else if(mom>=1.0) mean = 0.0107129 + 0.0377651/mom + -0.00975121/mom/mom + -0.0383664/sqrt(mom);
      sigma = 0.000218044 + -0.00413124/mom + 0.000959441/mom/mom + 0.0051898/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = -0.00444575 + -0.00615191/mom + 0.00102972/mom/mom + 0.00935856/sqrt(mom);
      else if(mom>=1.0) mean = -0.0104358 + -0.027825/mom + 0.00639597/mom/mom + 0.0316207/sqrt(mom);
      sigma = 0.000194868 + -0.00331273/mom + 0.000902405/mom/mom + 0.00440426/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=30&&zed<45))
    {
      if(mom<1.0) mean = 0.0114909 + 0.00913036/mom + -0.000922316/mom/mom + -0.0190636/sqrt(mom);
      else if(mom>=1.0) mean = 0.00936342 + 0.0313681/mom + -0.00808637/mom/mom + -0.0322231/sqrt(mom);
      sigma = -0.000488869 + -0.00581663/mom + 0.00131574/mom/mom + 0.00721865/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = -0.00228134 + -0.0049997/mom + 0.00149358/mom/mom + 0.00561084/sqrt(mom);
      else if(mom>=1.0) mean = -0.00513401 + -0.0118049/mom + 0.00297391/mom/mom + 0.0137058/sqrt(mom);
      sigma = -0.000460288 + -0.00519419/mom + 0.00131399/mom/mom + 0.00655468/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=45&&zed<60))
    {
      if(mom<1.0) mean = 0.00627704 + 0.00395804/mom + -0.000912967/mom/mom + -0.00880627/sqrt(mom);
      else if(mom>=1.0) mean = 0.00416215 + 0.0126033/mom + -0.0034174/mom/mom + -0.0129492/sqrt(mom);
      sigma = -0.000538445 + -0.00598059/mom + 0.00142679/mom/mom + 0.00735372/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = -0.00287085 + -0.00781433/mom + 0.0024171/mom/mom + 0.0084786/sqrt(mom);
      else if(mom>=1.0) mean = -0.00664132 + -0.0174918/mom + 0.00486693/mom/mom + 0.019421/sqrt(mom);
      sigma = -0.000818906 + -0.00639409/mom + 0.00162316/mom/mom + 0.00781553/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=60&&zed<75))
    {
      if(mom<1.0) mean = 0.0254615 + 0.0314769/mom + -0.00426499/mom/mom + -0.0526869/sqrt(mom);
      else if(mom>=1.0) mean = -0.00250221 + -0.0123778/mom + 0.00341901/mom/mom + 0.0114449/sqrt(mom);
      sigma = 0.001134 + -0.00178234/mom + 0.00079769/mom/mom + 0.00214561/sqrt(mom);
    }
  else
    {
      cout<<"significant issue in caltofwsdphi"<<endl;
      return -9999;
    }
  
  value = (tofwdphi - mean)/sigma;

  return value;
  
}






float tunetofwsdz(int run, int charge, float mom, float cent, float tofwsdz)
{

  float mean = -9999;
  float sigma = -9999;
  float value = -9999;

  if(run>250484&&charge==-1)
    {
      mean = -0.00565153 + -0.0170638/mom + 0.00335309/mom/mom + 0.0166101/sqrt(mom);
      sigma = 0.916739 + -0.0706207/mom + 0.0111088/mom/mom + 0.125801/sqrt(mom);
    }
  if(run<250593&&charge==-1)
    {
      mean = -0.016311 + -0.0278699/mom + 0.00352864/mom/mom + 0.0386405/sqrt(mom);
      sigma = 0.83138 + -0.212727/mom + 0.0294335/mom/mom + 0.333165/sqrt(mom);
    }
  if(run>250484&&charge==1)
    {
      mean = 0.00968331 + 0.00842975/mom + -4.97472e-05/mom/mom + -0.0219147/sqrt(mom);
      sigma = 0.764554 + -0.331884/mom + 0.0388235/mom/mom + 0.527434/sqrt(mom);
    }
  if(run<250593&&charge==1)
    {
      mean = -0.0141964 + -0.0222397/mom + 0.00321578/mom/mom + 0.0302044/sqrt(mom);
      sigma = 0.797409 + -0.250537/mom + 0.0278151/mom/mom + 0.42065/sqrt(mom);
    }

  if(run>250484&&charge==-1)
    {
      mean += -0.209883 + -1.27492/cent + 0.447868/cent/cent + 1.22479/sqrt(cent);
      sigma *= 0.931064 + 0.00213625*cent;
    }
  if(run<250593&&charge==-1)
    {
      mean += -0.183573 + -1.06332/cent + 0.358501/cent/cent + 1.05742/sqrt(cent);
      sigma *= 0.935782 + 0.0020964*cent;
    }
  if(run>250484&&charge==1)
    {
      mean += -0.204872 + -1.21461/cent + 0.414129/cent/cent + 1.18977/sqrt(cent);
      sigma *= 0.928696 + 0.00229116*cent;
    }
  if(run<250593&&charge==1)
    {
      mean += -0.184366 + -1.07374/cent + 0.364514/cent/cent + 1.05733/sqrt(cent);
      sigma *= 0.930854 + 0.00224951*cent;
    }


  value = (tofwsdz - mean)/sigma;
  return value;

}

float tunetofwsdphi(int run, int charge, float mom, float cent, float tofwsdphi)
{

  float mean = -9999;
  float sigma = -9999;
  float value = -9999;

  if(run>250484&&charge==-1)
    {
      mean = 0.175144 + 0.550273/mom + -0.0999333/mom/mom + -0.606328/sqrt(mom);
      sigma = 0.513865 + -0.90656/mom + 0.133787/mom/mom + 1.2629/sqrt(mom);
    }
  if(run<250593&&charge==-1)
    {
      mean = -0.578024 + -1.29717/mom + 0.184724/mom/mom + 1.72076/sqrt(mom);
      sigma = 0.813399 + -0.15248/mom + 0.00753161/mom/mom + 0.34745/sqrt(mom);
    }
  if(run>250484&&charge==1)
    {
      mean = -0.385368 + -0.970492/mom + 0.143773/mom/mom + 1.23642/sqrt(mom);
      sigma = 0.814729 + -0.132461/mom + 0.00318168/mom/mom + 0.318003/sqrt(mom);
    }
  if(run<250593&&charge==1)
    {
      mean = 0.100131 + 0.474586/mom + -0.0924466/mom/mom + -0.466119/sqrt(mom);
      sigma = 0.410412 + -1.05308/mom + 0.150811/mom/mom + 1.48642/sqrt(mom);
    }

  if(run>250484&&charge==-1)
    {
      mean += 0.00590256;
      sigma *= 0.999172;
    }
  if(run<250593&&charge==-1)
    {
      mean += -0.00945991;
      sigma *= 1.00515;
    }
  if(run>250484&&charge==1)
    {
      mean += -0.00929133;
      sigma *= 1.00342;
    }
  if(run<250593&&charge==1)
    {
      mean += 0.00588407;
      sigma *= 0.999539;
    }
 
 
  value = (tofwsdphi - mean)/sigma;
  return value;
  
}





float isPion(float x, float m2tofw)
{

  if(x<0.2) return -9999;

  float mean = mpion*mpion;

  float  p0   =       -5.20841e-02;
  float  p1   =        4.62591e-03;
  float  p2   =       -6.07273e-04;
  float  p3   =        6.15347e-02;
  float  p4   =       -1.03104e-01;
  float sigma = p0+p1/x+p2/x/x+p3*exp(sqrt(x))+p4*sqrt(x);
  
  return (m2tofw - mean)/sigma;

}



float isKaon(float x, float m2tofw)
{
  
  if(x<0.3) return -9999;

  float mean = mkaon*mkaon;

  float  p0   =        1.10981e-01;
  float  p1   =       -6.74987e-02;
  float  p2   =        1.31111e-02;
  float  p3   =        1.03992e-01;
  float  p4   =       -3.17107e-01;
  float sigma = p0+p1/x+p2/x/x+p3*exp(sqrt(x))+p4*sqrt(x);

  return (m2tofw - mean)/sigma;

}



float isProton(float x, float m2tofw)
{

  if(x<0.4) return -9999;

  float mean = mproton*mproton;

  float  p0    =       1.50217e-01;  
  float  p1    =      -1.13316e-01;
  float  p2    =       3.67417e-02;
  float  p3    =       1.06479e-01;
  float  p4    =      -3.26890e-01;
  float sigma = p0+p1/x+p2/x/x+p3*exp(sqrt(x))+p4*sqrt(x);

  return (m2tofw - mean)/sigma;

}





float isPionE(float x, float m2tofe)
{

  if(x<0.2) return -9999;

  float mean = mpion*mpion;

  float  p0   =       -6.95458e-02;
  float  p1   =        7.55715e-03;
  float  p2   =       -8.99881e-04;
  float  p3   =        6.20465e-02;
  float  p4   =       -8.71664e-02;
  float sigma = p0+p1/x+p2/x/x+p3*exp(sqrt(x))+p4*sqrt(x);
  
  return (m2tofe - mean)/sigma;

}



float isKaonE(float x, float m2tofe)
{
  
  if(x<0.3) return -9999;

  float mean = mkaon*mkaon;

  float  p0   =       -1.13181e-02;
  float  p1   =       -1.44832e-02;
  float  p2   =        3.24844e-03;
  float  p3   =        5.76146e-02;
  float  p4   =       -1.12985e-01;
  float sigma = p0+p1/x+p2/x/x+p3*exp(sqrt(x))+p4*sqrt(x);

  return (m2tofe - mean)/sigma;

}



float isProtonE(float x, float m2tofe)
{

  if(x<0.4) return -9999;

  float mean = mproton*mproton;

  float  p0    =       1.41079e-01;  
  float  p1    =      -6.87282e-02;
  float  p2    =       1.36918e-02;
  float  p3    =       1.47264e-01;
  float  p4    =      -4.47749e-01;
  float sigma = p0+p1/x+p2/x/x+p3*exp(sqrt(x))+p4*sqrt(x);

  return (m2tofe - mean)/sigma;

}



bool GoodPC1(float ppc1z, float ppc1phi)
{

  float zed = ppc1z;
  float phi = ppc1phi;

  if(zed>0&&zed<13&&phi>0.9&&phi<0.95) return false;
  if(zed>61&&zed<65&&phi>0.9&&phi<0.95) return false;
  if(zed>-55&&zed<-48&&phi>0.81&&phi<0.88) return false;
  if(zed>-70&&zed<-57&&phi>0.78&&phi<0.83) return false;
  if(zed>-30&&zed<-18&&phi>0.55&&phi<0.6) return false;
  if(zed>-30&&zed<-18&&phi>0.35&&phi<0.45) return false;
  if(zed>-3&&zed<0&&phi>0.4&&phi<0.45) return false;
  if(zed>70&&zed<82&&phi>0.35&&phi<0.45) return false;
  if(zed>28&&zed<41&&phi>0.16&&phi<0.2) return false;
  if(zed>-52&&zed<-39&&phi>0.12&&phi<0.16) return false;
  //if(zed>0&&zed<11&&phi>-0.26&&phi<-0.22) return false;
  if(zed>0&&zed<8&&phi>-0.27&&phi<-0.22) return false;
  if(zed>-30&&zed<-18&&phi>-0.4&&phi<-0.35) return false;

  // These holes are probably DC holes since they don't appear on a pc1phi vs pc1z plot
  // But it seems you can cut on these holes using the PC1 anyway
  //if(zed<0&&phi<-0.075&&phi>-0.095) return false; // modified
  if(zed<0&&phi<-0.065&&phi>-0.105) return false; // modified
  if(zed>49&&zed<60&&phi>0.008&&phi<0.05) return false;
  if(zed>-71&&zed<-59&&phi>0.398&&phi<0.44) return false;
 
  return true;  
  
}



bool GoodPC2(float pc2z, float pc2phi)
{

  float zed = pc2z;
  float phi = pc2phi;

  //if(zed>-70&&zed<-50&&phi>0.51&&phi<0.55) return false; // modified
  //if(zed>-25&&zed<0&&phi>0.46&&phi<0.516) return false; // modified
  //if(zed>20&&zed<42&&phi>0.46&&phi<0.516) return false; // modified
  //if(zed>-70&&zed<-50&&phi>0.4&&phi<0.44) return false; // modified
  //if(zed>73&&zed<94&&phi>-0.076&&phi<0.02) return false; // modified

  if(zed>-73&&zed<-53&&phi>0.508&&phi<0.552) return false;
  if(zed>-23&&zed<0&&phi>0.472&&phi<0.520) return false;
  if(zed>22&&zed<41&&phi>0.472&&phi<0.520) return false;
  if(zed>-100&&zed<-87&&phi>0.370&&phi<0.438) return false;
  if(zed>-73&&zed<-53&&phi>0.370&&phi<0.438) return false;
  if(zed>61&&zed<72&&phi>0.370&&phi<0.438) return false;
  if(zed>73&&zed<93&&phi>-0.076&&phi<-0.022) return false;
  if(zed>81&&zed<93&&phi>-0.022&&phi<0.012) return false;
  if(zed>81&&zed<93&&phi>-0.150&&phi<-0.076) return false;

  if(zed>-85&&zed<-70&&phi>-0.060&&phi<-0.018) return false;

  // holes in simulation that don't exist in real data
  if(zed>-74&&zed<-52&&phi>-0.080&&phi<-0.030) return false;
  if(zed>71&&zed<90&&phi>0.032&&phi<0.070) return false;

  return true;

}



bool GoodPC3(float pc3z, float pc3phi)
{

  // --- these are the pc3 fiducial cuts, similar to the old
  // --- this is a pc3 fiducial map of the whole west arm

  float zed = pc3z;
  float phi = pc3phi;

  //if(zed>-125&&zed<-90&&phi>0.45&&phi<0.5) return false;
  //if(zed>63&&zed<90&&phi>0.45&&phi<0.52) return false; // modified
  //if(zed>-105&&zed<-80&&phi>0.4&&phi<0.45) return false;
  //if(zed>-65&&zed<0&&phi>0.4&&phi<0.45) return false;
  //if(zed>66&&zed<84&&phi>0.04&&phi<0.1) return false;
  //if(zed>-86&&zed<-73&&phi>0&&phi<0.1) return false; // modified
  //if(zed>-86&&zed<-60&&phi>0.038&&phi<0.1) return false; // modified
  //if(zed>85&&zed<115&&phi>-0.02&&phi<0.01) return false;

  //if(zed>-126&&zed<-100&&phi>0.476&&phi<0.508) return false;
  if(zed>-126&&zed<-90&&phi>0.470&&phi<0.512) return false;
  if(zed>62&&zed<88&&phi>0.472&&phi<0.516) return false;
  if(zed>-104&&zed<-84&&phi>0.370&&phi<0.444) return false;
  if(zed>-64&&zed<0&&phi>0.370&&phi<0.444) return false;
  if(zed>67&&zed<80&&phi>0.040&&phi<0.100) return false;
  if(zed>-86&&zed<-74&&phi>0.006&&phi<0.100) return false;
  if(zed>-86&&zed<-61&&phi>0.036&&phi<0.100) return false;
  if(zed>84&&zed<112&&phi>-0.034&&phi<0.012) return false;

  if(zed>148&&zed<154&&phi>0.014&&phi<0.048) return false;
  if(zed>155&&zed<161&&phi>-0.100&&phi<-0.076) return false;

  if(zed>14&&zed<28&&phi>0.488&&phi<0.508) return false;
  //if(zed>94&&zed<105&&phi>0.492&&phi<0.506) return false;
  if(zed>94&&zed<105&&phi>0.476&&phi<0.510) return false;

  if(zed>-45&&zed<-30&&phi>0.498&&phi<0.600) return false;





  return true;

}



bool GoodEdgeDCH(int run, float zed, float alpha, float phi)
{

  float slope = 1.72; // 1.72 is latest and greatest, Monday 10/25/1010
  float sline = 25.0;
  float slire = 8.1;

  // === W1 === //
  // --- box edges
  if(alpha<slope*phi-slope*-0.200 && alpha>slope*phi-slope*-0.103) return false; // w1 below box
  if(alpha<slope*phi-slope*-0.021 && alpha>slope*phi-slope*-0.014) return false; // w1 center of box
  if(alpha<slope*phi-slope*0.060  && alpha>slope*phi-slope*0.200) return false; // w1 above box
  // --- internal wires
  // both w1 wires are much less pronounced than w2  
  //if(alpha<slire*phi-slire*-0.191 && alpha>slire*phi-slire*-0.188) return false; // w1 wire // problematically not straight
  //if(alpha<slire*phi-slire*0.006 && alpha>slire*phi-slire*0.009) return false; // w1 wire // leave out
  // === W2 === //
  // --- box edges
  if(alpha<slope*phi-slope*0.300 && alpha>slope*phi-slope*0.415) return false; // w2 below box
  if(alpha<slope*phi-slope*0.494 && alpha>slope*phi-slope*0.501) return false; // w2 center of box
  if(alpha<slope*phi-slope*0.577 && alpha>slope*phi-slope*0.700) return false; // w2 above box
  // --- internal wires
  if(alpha<slire*phi-slire*0.397 && alpha>slire*phi-slire*0.400) return false; // w2 wire, low
  if(alpha<slire*phi-slire*0.543 && alpha>slire*phi-slire*0.547) return false; // w2 wire, middle
  if(alpha<slire*phi-slire*0.593 && alpha>slire*phi-slire*0.596) return false; // w2 wire, high
  
  return true;

}



bool GoodInnerDCH(int run, float zed, float alpha, float phi)
{

  float slope = 1.72; // 1.72 is latest and greatest, Monday 10/25/1010
  float sline = 25.0;
  float slire = 8.1;

  // large stripe covering far upper alpha of w1 and far lower alpha of w2
  if(alpha<22.0*phi-22.0*0.175 && alpha>22.0*phi-22.0*0.276) return false; // checked

  // === W1 ===//
  // --- patchy region, upper alpha
  if(alpha<-14.8469*phi+14.8469*0.199158 && alpha>-21.3095*phi+21.3095*0.0383544 && alpha>0) return false; // checked, 4/11/2011

  // now do zed dependence
  if(zed>0)
    {
      // === W1 === //
      // --- left-most corner
      if(phi<-0.373) return false; // checked
      // --- small stripe, lower alpha, lower phi
      if(alpha>23.7666*phi-23.7666*-0.225933 && alpha<14.5819*phi-14.5819*-0.227896) return false; // checked
      // --- corner, lower alpha lower phi, -- field only
      if(run>250484 && alpha>7.31094*phi-7.31094*-0.184557) return false;
      if(run>250484 && phi<-0.238) return false;
      // === W2 === //
      // --- triangular hole, lower alpha
      if(alpha<26.4147*phi-26.4147*0.393654 && alpha<-23.0095*phi+23.0095*0.435974) return false; // checked
    }
  if(zed<0)
    {
      // === W1 === //
      // --- triangular hole for lower alpha, higher phi
      if(alpha<25.5628*phi-25.5628*-0.115491 && alpha<-19.9631*phi+19.9631*-0.092522) return false; // checked
      // --- triangular hole, lower alpha higher phi, simulation hole is larger and more complicated than real
      if(alpha>8.27513*phi-8.27513*-0.0636948 && alpha<8.27513*phi-8.27513*-0.105588) return false; // checked
      if(alpha<-20.6432*phi+20.6432*-0.0917881 && phi>-0.119) return false;
      // --- A-shaped hole, lower alpha lower phi, egregious mismatch between sim and real requires large hole
      if(alpha<29.0282*phi-29.0282*-0.217561 && alpha<-16.4706*phi+16.4706*-0.192351) return false;
      // === W2 === //
      // --- small stripe, upper alpha, higher phi
      if(alpha<22.0*phi-22.0*0.725 && alpha>22.0*phi-22.0*0.745) return false; // checked
      // --- inverted triangular shape, upper alpha lower phi
      if(alpha>13.7928*phi-13.7928*0.666602 && alpha>-48.9766*phi+48.9766*0.653529) return false; // checked
    }

  return true;

}






bool NewGoodPC1(float ppc1z, float ppc1phi)
{

  float zed = ppc1z;
  float phi = ppc1phi;

  // west

  if(zed>0&&zed<10&&phi>0.9&&phi<0.95) return false; // same
  if(zed>61&&zed<65&&phi>0.9&&phi<0.94) return false; // same
  if(zed>-55&&zed<-49&&phi>0.82&&phi<0.87) return false; // same
  if(zed>-40&&zed<-28&&phi>0.82&&phi<0.87) return false; // new for Run8
  if(zed>-71&&zed<-59&&phi>0.79&&phi<0.83) return false; // same
  if(zed>-30&&zed<-19&&phi>0.55&&phi<0.6) return false; // same
  if(zed>-30&&zed<-19&&phi>0.36&&phi<0.44) return false; // same
  if(zed>-3&&zed<0&&phi>0.4&&phi<0.44) return false; // same (~)
  if(zed>70&&zed<81&&phi>0.36&&phi<0.44) return false; // same
  if(zed>28&&zed<41&&phi>0.16&&phi<0.21) return false; // same
  if(zed>-51&&zed<-39&&phi>0.12&&phi<0.17) return false; // same
  if(zed>0&&zed<8&&phi>-0.27&&phi<-0.23) return false; // same (~)
  if(zed>-30&&zed<-19&&phi>-0.38&&phi<-0.35) return false; // same
 
  // east

  if(zed>-90&&zed<-79&&phi>4.09&&phi<4.15) return false; // same
  if(zed>80&&zed<86&&phi>4.09&&phi<4.15) return false; // same
  if(zed>-82&&zed<-68&&phi>3.89&&phi<3.94) return false; // same
  if(zed>-61&&zed<-54&&phi>3.89&&phi<3.94) return false; // same
  if(zed>-57&&zed<-49&&phi>3.81&&phi<3.86) return false; // same
  if(zed>9&&zed<20&&phi>3.81&&phi<3.86) return false; // same
  if(zed>75&&zed<81&&phi>3.81&&phi<3.86) return false; // same
  if(zed>19&&zed<30&&phi>3.74&&phi<3.78) return false; // same
  if(zed>0&&zed<10&&phi>3.5&&phi<3.55) return false; // same
  if(zed>19&&zed<30&&phi>3.38&&phi<3.43) return false; // nfr8
  if(zed>22&&zed<27&&phi>3.34&&phi<3.39) return false; // same
  if(zed>22&&zed<25&&phi>3.26&&phi<3.32) return false; // same
  if(zed>-20&&zed<-9&&phi>3.22&&phi<3.27) return false; // nfr8
  if(zed>-81&&zed<-70&&phi>3.18&&phi<3.23) return false; // same
  if(zed>-31&&zed<-19&&phi>3.18&&phi<3.23) return false; // same
  //if(zed>60&&zed<70&&phi>3.18&&phi<3.23) return false; // run7
  if(zed>59&&zed<71&&phi>3.18&&phi<3.23) return false; // bigger
  if(zed>-90&&zed<-80&&phi>3.11&&phi<3.15) return false; // same
  if(zed>-20&&zed<0&&phi>2.98&&phi<3.04) return false; // same
  if(zed>-46&&zed<-39&&phi>2.95&&phi<2.99) return false; // same
  if(zed>-90&&zed<-80&&phi>2.95&&phi<2.99) return false; // same
  if(zed>-81&&zed<-75&&phi>2.71&&phi<2.76) return false; // same
  if(zed>-10&&zed<0&&phi>2.71&&phi<2.76) return false; // same
  if(zed>39&&zed<51&&phi>2.63&&phi<2.68) return false; // same

  return true;  
  
}



bool NewGoodPC2(float pc2z, float pc2phi)
{

  float zed = pc2z;
  float phi = pc2phi;

  // move along folks there's nothing to see here

  if(zed>-55&&zed<-35&&phi>0.9&&phi>-1) return false; // 3S
  if(zed>-122&&zed<-105&&phi>0.9&&phi>0.95) return false; // 3S
  if(zed>-55&&zed<-35&&phi>0.82&&phi>0.875) return false; // 3S
  if(zed>-125&&zed<-102&&phi>0.67&&phi>0.73) return false; // 3S
  if(zed>-75&&zed<-50&&phi>0.63&&phi>0.69) return false; // 3S

  if(zed>90&&zed<112&&phi>0.75&&phi>0.795) return false; // 3N
  if(zed>55&&zed<78&&phi>0.67&&phi>0.73) return false; // 3N - new

  if(zed>-75&&zed<-50&&phi>0.505&&phi>0.555) return false; // 2S
  if(zed>-25&&zed<0&&phi>0.46&&phi>0.52) return false; // 2S
  if(zed>-75&&zed<-50&&phi>0.39&&phi>0.44) return false; // 2S
  if(zed>-102&&zed<-88&&phi>0.39&&phi>0.44) return false; // 2S - new

  if(zed>20&&zed<45&&phi>0.46&&phi>0.52) return false; // 2N
  if(zed>72&&zed<98&&phi>0.36&&phi>0.4) return false; // 2N
  if(zed>50&&zed<78&&phi>0.32&&phi>0.37) return false; // 2N

  if(zed>-160&&zed<-140&&phi>-0.13&&phi>-0.2) return false; // 1S

  if(zed>58&&zed<75&&phi>0.15&&phi>0.2) return false; // 1N
  if(zed>80&&zed<94&&phi>0.15&&phi>0.2) return false; // 1N - new
  if(zed>35&&zed<60&&phi>0.11&&phi>0.17) return false; // 1N
  if(zed>70&&zed<95&&phi>-0.08&&phi>0.01) return false; // 1N
  if(zed>20&&zed<40&&phi>-0.13&&phi>-0.2) return false; // 1N


  return true;

}



bool NewGoodPC3(float pc3z, float pc3phi)
{

  float zed = pc3z;
  float phi = pc3phi;

  // west

  if(zed>-45&&zed<-20&&phi>0.90&&phi<0.95) return false; // 3S - same
  if(zed>-125&&zed<-100&&phi>0.86&&phi<0.91) return false; // 3S - same
  if(zed>-130&&zed<-85&&phi>0.47&&phi<0.52) return false;  // 2S - same
  if(zed>-105&&zed<-82&&phi>0.395&&phi<0.445) return false; // 2S - same
  if(zed>-64&&zed<0&&phi>0.395&&phi<0.445) return false; // 2S - same
  if(zed>-65&&zed<-40&&phi>0.245&&phi<0.295) return false; // 2S - same
  if(zed>62&&zed<88&&phi>0.465&&phi<0.52) return false; // 2N - same
  if(zed>92&&zed<108&&phi>0.465&&phi<0.52) return false; // 2N - same
  if(zed>136&&zed<148&&phi>0.29&&phi<0.33) return false; // 2N - same
  if(zed>-86&&zed<-75&&phi>0.001&&phi<0.09) return false; // 1S - same
  if(zed>-86&&zed<-62&&phi>0.05&&phi<0.09) return false; // 1S - same
  if(zed>125&&zed<145&&phi>0.12&&phi<0.165) return false; // 1N - same
  if(zed>-100&&zed<-85&&phi>-0.315&&phi<-0.28) return false; // 0S - same
  if(zed>-52&&zed<-42&&phi>-0.315&&phi<-0.28) return false; // 0S - same
  //if(zed>-145&&zed<-125&&phi>-0.36&&phi<-0.30) return false; // 0S - absent in Run8
  if(zed>-200&&zed<-160&&phi>-0.54&&phi<-0.455) return false; // 0S - same
  if(zed>-200&&zed<-122&&phi>-0.54&&phi<-0.49) return false; // 0S - bigger in Run8
  if(zed>-145&&zed<-135&&phi>-0.495&&phi<-0.455) return false; // 0S - same
  if(zed>-85&&zed<-73&&phi>-0.495&&phi<-0.455) return false; // 0S - same
  //if(zed>85&&zed<107&&phi>-0.35&&phi<-0.3) return false; // 0N - not present in Run8
  if(zed>125&&zed<165&&phi>-0.6&&phi<-0.535) return false;// 0N - bigger in Run8



  // east

  // Sector 3, South Side (all same)
  if(zed>-65&&zed<-50&&phi>4.04&&phi<4.08) return false;
  if(zed>-146&&zed<-122&&phi>3.74&&phi<4.01) return false; // a
  if(zed>-165&&zed<-122&&phi>3.85&&phi<3.90) return false; // b
  if(zed>-200&&zed<-164&&phi>3.92&&phi<3.98) return false;
  if(zed>-200&&zed<-164&&phi>3.77&&phi<3.83) return false;
  if(zed>-200&&zed<-164&&phi>3.82&&phi<3.86) return false;
  if(zed>-110&&zed<-60&&phi>3.82&&phi<3.86) return false; // a
  if(zed>-110&&zed<-83&&phi>3.72&&phi<3.86) return false; // b
  if(zed>-25&&zed<0&&phi>3.82&&phi<3.86) return false;
  // Sector 3, North Side
  if(zed>0&&zed<30&&phi>4.04&&phi<4.15) return false; // new
  if(zed>42&&zed<68&&phi>3.93&&phi<3.98) return false; // same
  if(zed>113&&zed<128&&phi>3.93&&phi<3.98) return false; // same
  if(zed>42&&zed<68&&phi>3.78&&phi<3.86) return false; // same
  if(zed>23&&zed<47&&phi>3.74&&phi<3.78) return false; // bigger
  // Sector 2, South Side
  //if(zed>-165&&zed<-145&&phi>3.61&&phi<3.66) return false; gone
  if(zed>-48&&zed<-20&&phi>3.61&&phi<3.66) return false; // new
  if(zed>-48&&zed<-20&&phi>3.53&&phi<3.59) return false; // same
  if(zed>-200&&zed<-165&&phi>3.35&&phi<3.39) return false; // same
  if(zed>-145&&zed<-105&&phi>3.35&&phi<3.39) return false; // same
  if(zed>-85&&zed<0&&phi>3.35&&phi<3.39) return false; // bigger
  //if(zed>-30&&zed<0&&phi>3.35&&phi<3.39) return false; // mod
  // Sector 2, North Side (all same)
  if(zed>25&&zed<125&&phi>3.69&&phi<3.74) return false;
  if(zed>164&&zed<200&&phi>3.66&&phi<3.695) return false;
  if(zed>144&&zed<200&&phi>3.42&&phi<3.48) return false;
  // Sector 1, South Side
  if(zed>-128&&zed<-100&&phi>3.25&&phi<3.31) return false; // same
  if(zed>-200&&zed<-142&&phi>3.21&&phi<3.27) return false; // bigger
  if(zed>-166&&zed<-145&&phi>3.11&&phi<3.15) return false; // same
  if(zed>-130&&zed<-102&&phi>3.11&&phi<3.15) return false; // same
  if(zed>-8&&zed<-63&&phi>3.11&&phi<3.15) return false; // same
  // Sector 1, North Side (all same)
  //upper left
  if(zed>45&&zed<64&&phi>3.26&&phi<3.35) return false; // a
  if(zed>0&&zed<64&&phi>3.26&&phi<3.3) return false; // b
  //upper right
  if(zed>125&&zed<165&&phi>3.26&&phi<3.3) return false; // a
  if(zed>125&&zed<145&&phi>3.18&&phi<3.3) return false; // b
  // lower right
  if(zed>145&&zed<165&&phi>3.07&&phi<3.19) return false; // a
  if(zed>105&&zed<200&&phi>3.115&&phi<3.15) return false; // b
  if(zed>85&&zed<165&&phi>3.075&&phi<3.115) return false; // c
  if(zed>125&&zed<145&&phi>2.995&&phi<3.15) return false; // d
  // middle
  if(zed>43&&zed<64&&phi>3.15&&phi<3.19) return false;
  if(zed>83&&zed<105&&phi>2.99&&phi<3.04) return false;
  // right side
  if(zed>165&&zed<200&&phi>3.3&&phi<3.35) return false;
  if(zed>165&&zed<200&&phi>3.18&&phi<3.23) return false;
  // left side
  if(zed>0&&zed<25&&phi>3.11&&phi<3.15) return false;
  if(zed>0&&zed<25&&phi>3.03&&phi<3.08) return false;
  // Sector 0, South Side (all same)
  if(zed>-65&&zed<-43&&phi>2.905&&phi<2.95) return false;
  if(zed>-25&&zed<0&&phi>2.905&&phi<2.95) return false;
  if(zed>-25&&zed<0&&phi>2.79&&phi<2.835) return false;
  if(zed>-25&&zed<0&&phi>2.64&&phi<2.685) return false;
  if(zed>-15&&zed<0&&phi>2.55&&phi<2.61) return false;
  if(zed>-65&&zed<-43&&phi>2.83&&phi<2.87) return false;
  if(zed>-105&&zed<-82&&phi>2.71&&phi<2.76) return false;
  // Sector 0, North Side
  //upper left
  if(zed>25&&zed<43&&phi>2.83&&phi<2.95) return false; // a
  if(zed>0&&zed<105&&phi>2.83&&phi<2.87) return false; // b
  if(zed>85&&zed<105&&phi>2.83&&phi<2.91) return false; // c
  //upper right
  if(zed>125&&zed<200&&phi>2.87&&phi<2.91) return false; // a
  if(zed>145&&zed<165&&phi>2.83&&phi<2.91) return false; // b
  // lower right
  if(zed>85&&zed<145&&phi>2.72&&phi<2.755) return false; // a
  if(zed>125&&zed<165&&phi>2.755&&phi<2.795) return false; // b
  // middle
  if(zed>43&&zed<65&&phi>2.72&&phi<2.755) return false;
  if(zed>144&&zed<165&&phi>2.64&&phi<2.685) return false;
  if(zed>23&&zed<45&&phi>2.60&&phi<2.65) return false;
  if(zed>102&&zed<115&&phi>2.64&&phi<2.68) return false; // new
  if(zed>125&&zed<145&&phi>2.55&&phi<2.61) return false; // new



  return true;

}

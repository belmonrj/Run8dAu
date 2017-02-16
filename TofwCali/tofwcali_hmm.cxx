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
//float slewingoffset(float qtofw);
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

float recaltofwsdz(int run, int charge, float mom, float cent, float tofwsdz);
float recaltofwsdphi(int run, int charge, float mom, float cent, float tofwsdphi);

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

  TH1F *deltatdis = new TH1F("deltatdis","deltatdis",800, -2, 2);
  TH1F *qtofwdis = new TH1F("qtofwdis","qtofwdis",1000,0,1000);
  TH1F *tofwadcupdis = new TH1F("tofwadcupdis","tofwadcupdis",1000,0,1000);
  TH1F *tofwadcdwdis = new TH1F("tofwadcdwdis","tofwadcdwdis",1000,0,1000);

  TH2F *deltatrundis = new TH2F("deltatrundis","deltatrundis", 850,0,850, 800, -2, 2);
  TH2F *deltatstriptofwdis = new TH2F("deltatstriptofwdis","deltatstriptofwdis", 512, 0, 512, 800, -2, 2);

  TH2F *deltatslewingdis_q = new TH2F("deltatslewingdis_q","slewing (qtofw) distribution", 1000, 0, 1000, 800, -2, 2);
  TH2F *deltatslewingdis_u = new TH2F("deltatslewingdis_u","slewing (adcup) distribution", 1000, 0, 1000, 800, -2, 2);
  TH2F *deltatslewingdis_d = new TH2F("deltatslewingdis_d","slewing (adcdw) distribution", 1000, 0, 1000, 800, -2, 2);

  TH2F *m2mom_dis         = new TH2F("m2mom_dis", "mom vs m2",  160, -8.0, 8.0, 700, -1.5, 5.5);
  TH2F *m2mompos_dis      = new TH2F("m2mompos_dis", "mom vs m2",  80, 0.0, 8.0, 700, -1.5, 5.5);
  TH2F *m2momneg_dis      = new TH2F("m2momneg_dis", "mom vs m2",  80, 0.0, 8.0, 700, -1.5, 5.5);

  TH2F *ttofwmom_dis         = new TH2F("ttofwmom_dis", "mom vs ttofw",  160, -8.0, 8.0, 500, -2.0, 4.0);
  TH2F *ttofwmompos_dis      = new TH2F("ttofwmompos_dis", "mom vs ttofw",  80, 0.0, 8.0, 500, -2.0, 4.0);
  TH2F *ttofwmomneg_dis      = new TH2F("ttofwmomneg_dis", "mom vs ttofw",  80, 0.0, 8.0, 500, -2.0, 4.0);

  TH2F *m2mom_w1_dis         = new TH2F("m2mom_w1_dis", "mom vs m2 sector 1 west",  80, 0.0, 8.0, 700, -1.5, 5.5);
  TH2F *m2mom_w2_dis         = new TH2F("m2mom_w2_dis", "mom vs m2 sector 2 west",  80, 0.0, 8.0, 700, -1.5, 5.5);
  TH2F *m2mompos_w1_dis      = new TH2F("m2mompos_w1_dis", "mom vs m2 sector 1 west",  80, 0.0, 8.0, 700, -1.5, 5.5);
  TH2F *m2momneg_w1_dis      = new TH2F("m2momneg_w1_dis", "mom vs m2 sector 1 west",  80, 0.0, 8.0, 700, -1.5, 5.5);
  TH2F *m2mompos_w2_dis      = new TH2F("m2mompos_w2_dis", "mom vs m2 sector 2 west",  80, 0.0, 8.0, 700, -1.5, 5.5);
  TH2F *m2momneg_w2_dis      = new TH2F("m2momneg_w2_dis", "mom vs m2 sector 2 west",  80, 0.0, 8.0, 700, -1.5, 5.5);

  TH2F *m2pos_strip_dis      = new TH2F("m2pos_strip_dis", "m2 vs strip ",  512, 0, 511, 300, -1.0, 2.0);
  TH2F *m2neg_strip_dis      = new TH2F("m2neg_strip_dis", "m2 vs strip ",  512, 0, 511, 300, -1.0, 2.0);

  TH2F *m2pos_run_dis      = new TH2F("m2pos_run_dis", "m2 vs run ",  512, 0, 511, 300, -1.0, 2.0);
  TH2F *m2neg_run_dis      = new TH2F("m2neg_run_dis", "m2 vs run ",  512, 0, 511, 300, -1.0, 2.0);

  TH1F *htofwdz = new TH1F("htofwdz","htofwdz",100, -20,20);
  TH1F *htofwdphi = new TH1F("htofwdphi","htofwdphi",100, -0.02,0.02);
  TH1F *htofwsdz = new TH1F("htofwsdz","htofwdz",100, -20,20);
  TH1F *htofwsdphi = new TH1F("htofwsdphi","htofwdphi",100, -0.02,0.02);
  TH1F *hpc3sdz = new TH1F("hpc3sdz","hpc3sdz",100, -5,5);
  TH1F *hpc3sdphi = new TH1F("hpc3sdphi","hpc3sdphi",100, -5,5);

  // -------------- //
  // --- NORMAL --- //
  // -------------- //

  // ---
  // ---
  // ---

  TH2F *hh_sector1_tofwdz_posmom_poszed0 = new TH2F("hh_sector1_tofwdz_posmom_poszed0","hh_sector1_tofwdz_posmom_poszed0",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_posmom_poszed0 = new TH2F("hh_sector1_tofwdphi_posmom_poszed0","hh_sector1_tofwdz_posmom_poszed0",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector1_tofwdz_negmom_poszed0 = new TH2F("hh_sector1_tofwdz_negmom_poszed0","hh_sector1_tofwdz_negmom_poszed0",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_negmom_poszed0 = new TH2F("hh_sector1_tofwdphi_negmom_poszed0","hh_sector1_tofwdz_negmom_poszed0",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector1_tofwdz_posmom_poszed1 = new TH2F("hh_sector1_tofwdz_posmom_poszed1","hh_sector1_tofwdz_posmom_poszed1",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_posmom_poszed1 = new TH2F("hh_sector1_tofwdphi_posmom_poszed1","hh_sector1_tofwdz_posmom_poszed1",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector1_tofwdz_negmom_poszed1 = new TH2F("hh_sector1_tofwdz_negmom_poszed1","hh_sector1_tofwdz_negmom_poszed1",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_negmom_poszed1 = new TH2F("hh_sector1_tofwdphi_negmom_poszed1","hh_sector1_tofwdz_negmom_poszed1",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector1_tofwdz_posmom_poszed2 = new TH2F("hh_sector1_tofwdz_posmom_poszed2","hh_sector1_tofwdz_posmom_poszed2",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_posmom_poszed2 = new TH2F("hh_sector1_tofwdphi_posmom_poszed2","hh_sector1_tofwdz_posmom_poszed2",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector1_tofwdz_negmom_poszed2 = new TH2F("hh_sector1_tofwdz_negmom_poszed2","hh_sector1_tofwdz_negmom_poszed2",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_negmom_poszed2 = new TH2F("hh_sector1_tofwdphi_negmom_poszed2","hh_sector1_tofwdz_negmom_poszed2",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector1_tofwdz_posmom_poszed3 = new TH2F("hh_sector1_tofwdz_posmom_poszed3","hh_sector1_tofwdz_posmom_poszed3",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_posmom_poszed3 = new TH2F("hh_sector1_tofwdphi_posmom_poszed3","hh_sector1_tofwdz_posmom_poszed3",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector1_tofwdz_negmom_poszed3 = new TH2F("hh_sector1_tofwdz_negmom_poszed3","hh_sector1_tofwdz_negmom_poszed3",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_negmom_poszed3 = new TH2F("hh_sector1_tofwdphi_negmom_poszed3","hh_sector1_tofwdz_negmom_poszed3",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector1_tofwdz_posmom_poszed4 = new TH2F("hh_sector1_tofwdz_posmom_poszed4","hh_sector1_tofwdz_posmom_poszed4",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_posmom_poszed4 = new TH2F("hh_sector1_tofwdphi_posmom_poszed4","hh_sector1_tofwdz_posmom_poszed4",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector1_tofwdz_negmom_poszed4 = new TH2F("hh_sector1_tofwdz_negmom_poszed4","hh_sector1_tofwdz_negmom_poszed4",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_negmom_poszed4 = new TH2F("hh_sector1_tofwdphi_negmom_poszed4","hh_sector1_tofwdz_negmom_poszed4",80,0,8,100,-0.02,0.02);

  // ---
  // ---
  // ---

  TH2F *hh_sector1_tofwdz_posmom_negzed0 = new TH2F("hh_sector1_tofwdz_posmom_negzed0","hh_sector1_tofwdz_posmom_negzed0",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_posmom_negzed0 = new TH2F("hh_sector1_tofwdphi_posmom_negzed0","hh_sector1_tofwdz_posmom_negzed0",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector1_tofwdz_negmom_negzed0 = new TH2F("hh_sector1_tofwdz_negmom_negzed0","hh_sector1_tofwdz_negmom_negzed0",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_negmom_negzed0 = new TH2F("hh_sector1_tofwdphi_negmom_negzed0","hh_sector1_tofwdz_negmom_negzed0",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector1_tofwdz_posmom_negzed1 = new TH2F("hh_sector1_tofwdz_posmom_negzed1","hh_sector1_tofwdz_posmom_negzed1",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_posmom_negzed1 = new TH2F("hh_sector1_tofwdphi_posmom_negzed1","hh_sector1_tofwdz_posmom_negzed1",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector1_tofwdz_negmom_negzed1 = new TH2F("hh_sector1_tofwdz_negmom_negzed1","hh_sector1_tofwdz_negmom_negzed1",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_negmom_negzed1 = new TH2F("hh_sector1_tofwdphi_negmom_negzed1","hh_sector1_tofwdz_negmom_negzed1",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector1_tofwdz_posmom_negzed2 = new TH2F("hh_sector1_tofwdz_posmom_negzed2","hh_sector1_tofwdz_posmom_negzed2",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_posmom_negzed2 = new TH2F("hh_sector1_tofwdphi_posmom_negzed2","hh_sector1_tofwdz_posmom_negzed2",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector1_tofwdz_negmom_negzed2 = new TH2F("hh_sector1_tofwdz_negmom_negzed2","hh_sector1_tofwdz_negmom_negzed2",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_negmom_negzed2 = new TH2F("hh_sector1_tofwdphi_negmom_negzed2","hh_sector1_tofwdz_negmom_negzed2",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector1_tofwdz_posmom_negzed3 = new TH2F("hh_sector1_tofwdz_posmom_negzed3","hh_sector1_tofwdz_posmom_negzed3",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_posmom_negzed3 = new TH2F("hh_sector1_tofwdphi_posmom_negzed3","hh_sector1_tofwdz_posmom_negzed3",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector1_tofwdz_negmom_negzed3 = new TH2F("hh_sector1_tofwdz_negmom_negzed3","hh_sector1_tofwdz_negmom_negzed3",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_negmom_negzed3 = new TH2F("hh_sector1_tofwdphi_negmom_negzed3","hh_sector1_tofwdz_negmom_negzed3",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector1_tofwdz_posmom_negzed4 = new TH2F("hh_sector1_tofwdz_posmom_negzed4","hh_sector1_tofwdz_posmom_negzed4",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_posmom_negzed4 = new TH2F("hh_sector1_tofwdphi_posmom_negzed4","hh_sector1_tofwdz_posmom_negzed4",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector1_tofwdz_negmom_negzed4 = new TH2F("hh_sector1_tofwdz_negmom_negzed4","hh_sector1_tofwdz_negmom_negzed4",80,0,8,100,-20,20);
  TH2F *hh_sector1_tofwdphi_negmom_negzed4 = new TH2F("hh_sector1_tofwdphi_negmom_negzed4","hh_sector1_tofwdz_negmom_negzed4",80,0,8,100,-0.02,0.02);

  // ---
  // ---
  // ---

  // ---
  // ---
  // ---

  TH2F *hh_sector2_tofwdz_posmom_poszed0 = new TH2F("hh_sector2_tofwdz_posmom_poszed0","hh_sector2_tofwdz_posmom_poszed0",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_posmom_poszed0 = new TH2F("hh_sector2_tofwdphi_posmom_poszed0","hh_sector2_tofwdz_posmom_poszed0",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector2_tofwdz_negmom_poszed0 = new TH2F("hh_sector2_tofwdz_negmom_poszed0","hh_sector2_tofwdz_negmom_poszed0",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_negmom_poszed0 = new TH2F("hh_sector2_tofwdphi_negmom_poszed0","hh_sector2_tofwdz_negmom_poszed0",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector2_tofwdz_posmom_poszed1 = new TH2F("hh_sector2_tofwdz_posmom_poszed1","hh_sector2_tofwdz_posmom_poszed1",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_posmom_poszed1 = new TH2F("hh_sector2_tofwdphi_posmom_poszed1","hh_sector2_tofwdz_posmom_poszed1",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector2_tofwdz_negmom_poszed1 = new TH2F("hh_sector2_tofwdz_negmom_poszed1","hh_sector2_tofwdz_negmom_poszed1",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_negmom_poszed1 = new TH2F("hh_sector2_tofwdphi_negmom_poszed1","hh_sector2_tofwdz_negmom_poszed1",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector2_tofwdz_posmom_poszed2 = new TH2F("hh_sector2_tofwdz_posmom_poszed2","hh_sector2_tofwdz_posmom_poszed2",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_posmom_poszed2 = new TH2F("hh_sector2_tofwdphi_posmom_poszed2","hh_sector2_tofwdz_posmom_poszed2",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector2_tofwdz_negmom_poszed2 = new TH2F("hh_sector2_tofwdz_negmom_poszed2","hh_sector2_tofwdz_negmom_poszed2",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_negmom_poszed2 = new TH2F("hh_sector2_tofwdphi_negmom_poszed2","hh_sector2_tofwdz_negmom_poszed2",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector2_tofwdz_posmom_poszed3 = new TH2F("hh_sector2_tofwdz_posmom_poszed3","hh_sector2_tofwdz_posmom_poszed3",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_posmom_poszed3 = new TH2F("hh_sector2_tofwdphi_posmom_poszed3","hh_sector2_tofwdz_posmom_poszed3",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector2_tofwdz_negmom_poszed3 = new TH2F("hh_sector2_tofwdz_negmom_poszed3","hh_sector2_tofwdz_negmom_poszed3",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_negmom_poszed3 = new TH2F("hh_sector2_tofwdphi_negmom_poszed3","hh_sector2_tofwdz_negmom_poszed3",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector2_tofwdz_posmom_poszed4 = new TH2F("hh_sector2_tofwdz_posmom_poszed4","hh_sector2_tofwdz_posmom_poszed4",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_posmom_poszed4 = new TH2F("hh_sector2_tofwdphi_posmom_poszed4","hh_sector2_tofwdz_posmom_poszed4",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector2_tofwdz_negmom_poszed4 = new TH2F("hh_sector2_tofwdz_negmom_poszed4","hh_sector2_tofwdz_negmom_poszed4",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_negmom_poszed4 = new TH2F("hh_sector2_tofwdphi_negmom_poszed4","hh_sector2_tofwdz_negmom_poszed4",80,0,8,100,-0.02,0.02);

  // ---
  // ---
  // ---

  TH2F *hh_sector2_tofwdz_posmom_negzed0 = new TH2F("hh_sector2_tofwdz_posmom_negzed0","hh_sector2_tofwdz_posmom_negzed0",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_posmom_negzed0 = new TH2F("hh_sector2_tofwdphi_posmom_negzed0","hh_sector2_tofwdz_posmom_negzed0",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector2_tofwdz_negmom_negzed0 = new TH2F("hh_sector2_tofwdz_negmom_negzed0","hh_sector2_tofwdz_negmom_negzed0",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_negmom_negzed0 = new TH2F("hh_sector2_tofwdphi_negmom_negzed0","hh_sector2_tofwdz_negmom_negzed0",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector2_tofwdz_posmom_negzed1 = new TH2F("hh_sector2_tofwdz_posmom_negzed1","hh_sector2_tofwdz_posmom_negzed1",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_posmom_negzed1 = new TH2F("hh_sector2_tofwdphi_posmom_negzed1","hh_sector2_tofwdz_posmom_negzed1",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector2_tofwdz_negmom_negzed1 = new TH2F("hh_sector2_tofwdz_negmom_negzed1","hh_sector2_tofwdz_negmom_negzed1",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_negmom_negzed1 = new TH2F("hh_sector2_tofwdphi_negmom_negzed1","hh_sector2_tofwdz_negmom_negzed1",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector2_tofwdz_posmom_negzed2 = new TH2F("hh_sector2_tofwdz_posmom_negzed2","hh_sector2_tofwdz_posmom_negzed2",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_posmom_negzed2 = new TH2F("hh_sector2_tofwdphi_posmom_negzed2","hh_sector2_tofwdz_posmom_negzed2",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector2_tofwdz_negmom_negzed2 = new TH2F("hh_sector2_tofwdz_negmom_negzed2","hh_sector2_tofwdz_negmom_negzed2",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_negmom_negzed2 = new TH2F("hh_sector2_tofwdphi_negmom_negzed2","hh_sector2_tofwdz_negmom_negzed2",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector2_tofwdz_posmom_negzed3 = new TH2F("hh_sector2_tofwdz_posmom_negzed3","hh_sector2_tofwdz_posmom_negzed3",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_posmom_negzed3 = new TH2F("hh_sector2_tofwdphi_posmom_negzed3","hh_sector2_tofwdz_posmom_negzed3",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector2_tofwdz_negmom_negzed3 = new TH2F("hh_sector2_tofwdz_negmom_negzed3","hh_sector2_tofwdz_negmom_negzed3",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_negmom_negzed3 = new TH2F("hh_sector2_tofwdphi_negmom_negzed3","hh_sector2_tofwdz_negmom_negzed3",80,0,8,100,-0.02,0.02);

  TH2F *hh_sector2_tofwdz_posmom_negzed4 = new TH2F("hh_sector2_tofwdz_posmom_negzed4","hh_sector2_tofwdz_posmom_negzed4",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_posmom_negzed4 = new TH2F("hh_sector2_tofwdphi_posmom_negzed4","hh_sector2_tofwdz_posmom_negzed4",80,0,8,100,-0.02,0.02);
  TH2F *hh_sector2_tofwdz_negmom_negzed4 = new TH2F("hh_sector2_tofwdz_negmom_negzed4","hh_sector2_tofwdz_negmom_negzed4",80,0,8,100,-20,20);
  TH2F *hh_sector2_tofwdphi_negmom_negzed4 = new TH2F("hh_sector2_tofwdphi_negmom_negzed4","hh_sector2_tofwdz_negmom_negzed4",80,0,8,100,-0.02,0.02);

  // ---
  // ---
  // ---

  TH2F *hh_strip_tofwdz = new TH2F("hh_strip_tofwdz","hh_strip_tofwdz",512,0,511,100,-20,20);
  TH2F *hh_strip_tofwdphi = new TH2F("hh_strip_tofwdphi","hh_strip_tofwdphi",512,0,511,100,-0.02,0.02);
  TH2F *hh_cent_tofwdz = new TH2F("hh_cent_tofwdz","hh_cent_tofwdz",100,0,100,100,-20,20);
  TH2F *hh_cent_tofwdphi = new TH2F("hh_cent_tofwdphi","hh_cent_tofwdphi",100,0,100,100,-0.02,0.02);
  TH2F *hh_mom_tofwdz = new TH2F("hh_mom_tofwdz","hh_mom_tofwdz",80,0,8,100,-20,20);
  TH2F *hh_mom_tofwdphi = new TH2F("hh_mom_tofwdphi","hh_mom_tofwdphi",80,0,8,100,-0.02,0.02);
  TH2F *hh_zed_tofwdz = new TH2F("hh_zed_tofwdz","hh_zed_tofwdz",160,-80,80,100,-20,20);
  TH2F *hh_zed_tofwdphi = new TH2F("hh_zed_tofwdphi","hh_zed_tofwdphi",160,-80,80,100,-0.02,0.02);

  TH2F *hh_pos_strip_tofwdz = new TH2F("hh_pos_strip_tofwdz","hh_pos_strip_tofwdz",512,0,511,100,-20,20);
  TH2F *hh_pos_strip_tofwdphi = new TH2F("hh_pos_strip_tofwdphi","hh_pos_strip_tofwdphi",512,0,511,100,-0.02,0.02);
  TH2F *hh_pos_cent_tofwdz = new TH2F("hh_pos_cent_tofwdz","hh_pos_cent_tofwdz",100,0,100,100,-20,20);
  TH2F *hh_pos_cent_tofwdphi = new TH2F("hh_pos_cent_tofwdphi","hh_pos_cent_tofwdphi",100,0,100,100,-0.02,0.02);
  TH2F *hh_pos_mom_tofwdz = new TH2F("hh_pos_mom_tofwdz","hh_pos_mom_tofwdz",80,0,8,100,-20,20);
  TH2F *hh_pos_mom_tofwdphi = new TH2F("hh_pos_mom_tofwdphi","hh_pos_mom_tofwdphi",80,0,8,100,-0.02,0.02);
  TH2F *hh_pos_zed_tofwdz = new TH2F("hh_pos_zed_tofwdz","hh_pos_zed_tofwdz",160,-80,80,100,-20,20);
  TH2F *hh_pos_zed_tofwdphi = new TH2F("hh_pos_zed_tofwdphi","hh_pos_zed_tofwdphi",160,-80,80,100,-0.02,0.02);

  TH2F *hh_neg_strip_tofwdz = new TH2F("hh_neg_strip_tofwdz","hh_neg_strip_tofwdz",512,0,511,100,-20,20);
  TH2F *hh_neg_strip_tofwdphi = new TH2F("hh_neg_strip_tofwdphi","hh_neg_strip_tofwdphi",512,0,511,100,-0.02,0.02);
  TH2F *hh_neg_cent_tofwdz = new TH2F("hh_neg_cent_tofwdz","hh_neg_cent_tofwdz",100,0,100,100,-20,20);
  TH2F *hh_neg_cent_tofwdphi = new TH2F("hh_neg_cent_tofwdphi","hh_neg_cent_tofwdphi",100,0,100,100,-0.02,0.02);
  TH2F *hh_neg_mom_tofwdz = new TH2F("hh_neg_mom_tofwdz","hh_neg_mom_tofwdz",80,0,8,100,-20,20);
  TH2F *hh_neg_mom_tofwdphi = new TH2F("hh_neg_mom_tofwdphi","hh_neg_mom_tofwdphi",80,0,8,100,-0.02,0.02);
  TH2F *hh_neg_zed_tofwdz = new TH2F("hh_neg_zed_tofwdz","hh_neg_zed_tofwdz",160,-80,80,100,-20,20);
  TH2F *hh_neg_zed_tofwdphi = new TH2F("hh_neg_zed_tofwdphi","hh_neg_zed_tofwdphi",160,-80,80,100,-0.02,0.02);



  // ------------------ //
  // --- SIGMALIZED --- //
  // ------------------ //

  // ---
  // ---
  // ---

  TH2F *hh_sector1_tofwsdz_posmom_poszed0 = new TH2F("hh_sector1_tofwsdz_posmom_poszed0","hh_sector1_tofwsdz_posmom_poszed0",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_posmom_poszed0 = new TH2F("hh_sector1_tofwsdphi_posmom_poszed0","hh_sector1_tofwsdz_posmom_poszed0",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdz_negmom_poszed0 = new TH2F("hh_sector1_tofwsdz_negmom_poszed0","hh_sector1_tofwsdz_negmom_poszed0",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_negmom_poszed0 = new TH2F("hh_sector1_tofwsdphi_negmom_poszed0","hh_sector1_tofwsdz_negmom_poszed0",80,0,8,200,-10,10);

  TH2F *hh_sector1_tofwsdz_posmom_poszed1 = new TH2F("hh_sector1_tofwsdz_posmom_poszed1","hh_sector1_tofwsdz_posmom_poszed1",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_posmom_poszed1 = new TH2F("hh_sector1_tofwsdphi_posmom_poszed1","hh_sector1_tofwsdz_posmom_poszed1",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdz_negmom_poszed1 = new TH2F("hh_sector1_tofwsdz_negmom_poszed1","hh_sector1_tofwsdz_negmom_poszed1",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_negmom_poszed1 = new TH2F("hh_sector1_tofwsdphi_negmom_poszed1","hh_sector1_tofwsdz_negmom_poszed1",80,0,8,200,-10,10);

  TH2F *hh_sector1_tofwsdz_posmom_poszed2 = new TH2F("hh_sector1_tofwsdz_posmom_poszed2","hh_sector1_tofwsdz_posmom_poszed2",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_posmom_poszed2 = new TH2F("hh_sector1_tofwsdphi_posmom_poszed2","hh_sector1_tofwsdz_posmom_poszed2",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdz_negmom_poszed2 = new TH2F("hh_sector1_tofwsdz_negmom_poszed2","hh_sector1_tofwsdz_negmom_poszed2",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_negmom_poszed2 = new TH2F("hh_sector1_tofwsdphi_negmom_poszed2","hh_sector1_tofwsdz_negmom_poszed2",80,0,8,200,-10,10);

  TH2F *hh_sector1_tofwsdz_posmom_poszed3 = new TH2F("hh_sector1_tofwsdz_posmom_poszed3","hh_sector1_tofwsdz_posmom_poszed3",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_posmom_poszed3 = new TH2F("hh_sector1_tofwsdphi_posmom_poszed3","hh_sector1_tofwsdz_posmom_poszed3",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdz_negmom_poszed3 = new TH2F("hh_sector1_tofwsdz_negmom_poszed3","hh_sector1_tofwsdz_negmom_poszed3",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_negmom_poszed3 = new TH2F("hh_sector1_tofwsdphi_negmom_poszed3","hh_sector1_tofwsdz_negmom_poszed3",80,0,8,200,-10,10);

  TH2F *hh_sector1_tofwsdz_posmom_poszed4 = new TH2F("hh_sector1_tofwsdz_posmom_poszed4","hh_sector1_tofwsdz_posmom_poszed4",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_posmom_poszed4 = new TH2F("hh_sector1_tofwsdphi_posmom_poszed4","hh_sector1_tofwsdz_posmom_poszed4",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdz_negmom_poszed4 = new TH2F("hh_sector1_tofwsdz_negmom_poszed4","hh_sector1_tofwsdz_negmom_poszed4",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_negmom_poszed4 = new TH2F("hh_sector1_tofwsdphi_negmom_poszed4","hh_sector1_tofwsdz_negmom_poszed4",80,0,8,200,-10,10);

  // ---
  // ---
  // ---

  TH2F *hh_sector1_tofwsdz_posmom_negzed0 = new TH2F("hh_sector1_tofwsdz_posmom_negzed0","hh_sector1_tofwsdz_posmom_negzed0",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_posmom_negzed0 = new TH2F("hh_sector1_tofwsdphi_posmom_negzed0","hh_sector1_tofwsdz_posmom_negzed0",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdz_negmom_negzed0 = new TH2F("hh_sector1_tofwsdz_negmom_negzed0","hh_sector1_tofwsdz_negmom_negzed0",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_negmom_negzed0 = new TH2F("hh_sector1_tofwsdphi_negmom_negzed0","hh_sector1_tofwsdz_negmom_negzed0",80,0,8,200,-10,10);

  TH2F *hh_sector1_tofwsdz_posmom_negzed1 = new TH2F("hh_sector1_tofwsdz_posmom_negzed1","hh_sector1_tofwsdz_posmom_negzed1",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_posmom_negzed1 = new TH2F("hh_sector1_tofwsdphi_posmom_negzed1","hh_sector1_tofwsdz_posmom_negzed1",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdz_negmom_negzed1 = new TH2F("hh_sector1_tofwsdz_negmom_negzed1","hh_sector1_tofwsdz_negmom_negzed1",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_negmom_negzed1 = new TH2F("hh_sector1_tofwsdphi_negmom_negzed1","hh_sector1_tofwsdz_negmom_negzed1",80,0,8,200,-10,10);

  TH2F *hh_sector1_tofwsdz_posmom_negzed2 = new TH2F("hh_sector1_tofwsdz_posmom_negzed2","hh_sector1_tofwsdz_posmom_negzed2",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_posmom_negzed2 = new TH2F("hh_sector1_tofwsdphi_posmom_negzed2","hh_sector1_tofwsdz_posmom_negzed2",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdz_negmom_negzed2 = new TH2F("hh_sector1_tofwsdz_negmom_negzed2","hh_sector1_tofwsdz_negmom_negzed2",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_negmom_negzed2 = new TH2F("hh_sector1_tofwsdphi_negmom_negzed2","hh_sector1_tofwsdz_negmom_negzed2",80,0,8,200,-10,10);

  TH2F *hh_sector1_tofwsdz_posmom_negzed3 = new TH2F("hh_sector1_tofwsdz_posmom_negzed3","hh_sector1_tofwsdz_posmom_negzed3",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_posmom_negzed3 = new TH2F("hh_sector1_tofwsdphi_posmom_negzed3","hh_sector1_tofwsdz_posmom_negzed3",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdz_negmom_negzed3 = new TH2F("hh_sector1_tofwsdz_negmom_negzed3","hh_sector1_tofwsdz_negmom_negzed3",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_negmom_negzed3 = new TH2F("hh_sector1_tofwsdphi_negmom_negzed3","hh_sector1_tofwsdz_negmom_negzed3",80,0,8,200,-10,10);

  TH2F *hh_sector1_tofwsdz_posmom_negzed4 = new TH2F("hh_sector1_tofwsdz_posmom_negzed4","hh_sector1_tofwsdz_posmom_negzed4",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_posmom_negzed4 = new TH2F("hh_sector1_tofwsdphi_posmom_negzed4","hh_sector1_tofwsdz_posmom_negzed4",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdz_negmom_negzed4 = new TH2F("hh_sector1_tofwsdz_negmom_negzed4","hh_sector1_tofwsdz_negmom_negzed4",80,0,8,200,-10,10);
  TH2F *hh_sector1_tofwsdphi_negmom_negzed4 = new TH2F("hh_sector1_tofwsdphi_negmom_negzed4","hh_sector1_tofwsdz_negmom_negzed4",80,0,8,200,-10,10);

  // ---
  // ---
  // ---

  // ---
  // ---
  // ---

  TH2F *hh_sector2_tofwsdz_posmom_poszed0 = new TH2F("hh_sector2_tofwsdz_posmom_poszed0","hh_sector2_tofwsdz_posmom_poszed0",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_posmom_poszed0 = new TH2F("hh_sector2_tofwsdphi_posmom_poszed0","hh_sector2_tofwsdz_posmom_poszed0",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdz_negmom_poszed0 = new TH2F("hh_sector2_tofwsdz_negmom_poszed0","hh_sector2_tofwsdz_negmom_poszed0",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_negmom_poszed0 = new TH2F("hh_sector2_tofwsdphi_negmom_poszed0","hh_sector2_tofwsdz_negmom_poszed0",80,0,8,200,-10,10);

  TH2F *hh_sector2_tofwsdz_posmom_poszed1 = new TH2F("hh_sector2_tofwsdz_posmom_poszed1","hh_sector2_tofwsdz_posmom_poszed1",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_posmom_poszed1 = new TH2F("hh_sector2_tofwsdphi_posmom_poszed1","hh_sector2_tofwsdz_posmom_poszed1",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdz_negmom_poszed1 = new TH2F("hh_sector2_tofwsdz_negmom_poszed1","hh_sector2_tofwsdz_negmom_poszed1",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_negmom_poszed1 = new TH2F("hh_sector2_tofwsdphi_negmom_poszed1","hh_sector2_tofwsdz_negmom_poszed1",80,0,8,200,-10,10);

  TH2F *hh_sector2_tofwsdz_posmom_poszed2 = new TH2F("hh_sector2_tofwsdz_posmom_poszed2","hh_sector2_tofwsdz_posmom_poszed2",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_posmom_poszed2 = new TH2F("hh_sector2_tofwsdphi_posmom_poszed2","hh_sector2_tofwsdz_posmom_poszed2",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdz_negmom_poszed2 = new TH2F("hh_sector2_tofwsdz_negmom_poszed2","hh_sector2_tofwsdz_negmom_poszed2",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_negmom_poszed2 = new TH2F("hh_sector2_tofwsdphi_negmom_poszed2","hh_sector2_tofwsdz_negmom_poszed2",80,0,8,200,-10,10);

  TH2F *hh_sector2_tofwsdz_posmom_poszed3 = new TH2F("hh_sector2_tofwsdz_posmom_poszed3","hh_sector2_tofwsdz_posmom_poszed3",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_posmom_poszed3 = new TH2F("hh_sector2_tofwsdphi_posmom_poszed3","hh_sector2_tofwsdz_posmom_poszed3",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdz_negmom_poszed3 = new TH2F("hh_sector2_tofwsdz_negmom_poszed3","hh_sector2_tofwsdz_negmom_poszed3",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_negmom_poszed3 = new TH2F("hh_sector2_tofwsdphi_negmom_poszed3","hh_sector2_tofwsdz_negmom_poszed3",80,0,8,200,-10,10);

  TH2F *hh_sector2_tofwsdz_posmom_poszed4 = new TH2F("hh_sector2_tofwsdz_posmom_poszed4","hh_sector2_tofwsdz_posmom_poszed4",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_posmom_poszed4 = new TH2F("hh_sector2_tofwsdphi_posmom_poszed4","hh_sector2_tofwsdz_posmom_poszed4",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdz_negmom_poszed4 = new TH2F("hh_sector2_tofwsdz_negmom_poszed4","hh_sector2_tofwsdz_negmom_poszed4",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_negmom_poszed4 = new TH2F("hh_sector2_tofwsdphi_negmom_poszed4","hh_sector2_tofwsdz_negmom_poszed4",80,0,8,200,-10,10);

  // ---
  // ---
  // ---

  TH2F *hh_sector2_tofwsdz_posmom_negzed0 = new TH2F("hh_sector2_tofwsdz_posmom_negzed0","hh_sector2_tofwsdz_posmom_negzed0",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_posmom_negzed0 = new TH2F("hh_sector2_tofwsdphi_posmom_negzed0","hh_sector2_tofwsdz_posmom_negzed0",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdz_negmom_negzed0 = new TH2F("hh_sector2_tofwsdz_negmom_negzed0","hh_sector2_tofwsdz_negmom_negzed0",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_negmom_negzed0 = new TH2F("hh_sector2_tofwsdphi_negmom_negzed0","hh_sector2_tofwsdz_negmom_negzed0",80,0,8,200,-10,10);

  TH2F *hh_sector2_tofwsdz_posmom_negzed1 = new TH2F("hh_sector2_tofwsdz_posmom_negzed1","hh_sector2_tofwsdz_posmom_negzed1",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_posmom_negzed1 = new TH2F("hh_sector2_tofwsdphi_posmom_negzed1","hh_sector2_tofwsdz_posmom_negzed1",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdz_negmom_negzed1 = new TH2F("hh_sector2_tofwsdz_negmom_negzed1","hh_sector2_tofwsdz_negmom_negzed1",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_negmom_negzed1 = new TH2F("hh_sector2_tofwsdphi_negmom_negzed1","hh_sector2_tofwsdz_negmom_negzed1",80,0,8,200,-10,10);

  TH2F *hh_sector2_tofwsdz_posmom_negzed2 = new TH2F("hh_sector2_tofwsdz_posmom_negzed2","hh_sector2_tofwsdz_posmom_negzed2",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_posmom_negzed2 = new TH2F("hh_sector2_tofwsdphi_posmom_negzed2","hh_sector2_tofwsdz_posmom_negzed2",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdz_negmom_negzed2 = new TH2F("hh_sector2_tofwsdz_negmom_negzed2","hh_sector2_tofwsdz_negmom_negzed2",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_negmom_negzed2 = new TH2F("hh_sector2_tofwsdphi_negmom_negzed2","hh_sector2_tofwsdz_negmom_negzed2",80,0,8,200,-10,10);

  TH2F *hh_sector2_tofwsdz_posmom_negzed3 = new TH2F("hh_sector2_tofwsdz_posmom_negzed3","hh_sector2_tofwsdz_posmom_negzed3",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_posmom_negzed3 = new TH2F("hh_sector2_tofwsdphi_posmom_negzed3","hh_sector2_tofwsdz_posmom_negzed3",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdz_negmom_negzed3 = new TH2F("hh_sector2_tofwsdz_negmom_negzed3","hh_sector2_tofwsdz_negmom_negzed3",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_negmom_negzed3 = new TH2F("hh_sector2_tofwsdphi_negmom_negzed3","hh_sector2_tofwsdz_negmom_negzed3",80,0,8,200,-10,10);

  TH2F *hh_sector2_tofwsdz_posmom_negzed4 = new TH2F("hh_sector2_tofwsdz_posmom_negzed4","hh_sector2_tofwsdz_posmom_negzed4",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_posmom_negzed4 = new TH2F("hh_sector2_tofwsdphi_posmom_negzed4","hh_sector2_tofwsdz_posmom_negzed4",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdz_negmom_negzed4 = new TH2F("hh_sector2_tofwsdz_negmom_negzed4","hh_sector2_tofwsdz_negmom_negzed4",80,0,8,200,-10,10);
  TH2F *hh_sector2_tofwsdphi_negmom_negzed4 = new TH2F("hh_sector2_tofwsdphi_negmom_negzed4","hh_sector2_tofwsdz_negmom_negzed4",80,0,8,200,-10,10);

  // ---
  // ---
  // ---

  TH2F *hh_strip_tofwsdz = new TH2F("hh_strip_tofwsdz","hh_strip_tofwsdz",512,0,511,200,-10,10);
  TH2F *hh_strip_tofwsdphi = new TH2F("hh_strip_tofwsdphi","hh_strip_tofwsdphi",512,0,511,200,-10,10);
  TH2F *hh_cent_tofwsdz = new TH2F("hh_cent_tofwsdz","hh_cent_tofwsdz",100,0,100,200,-10,10);
  TH2F *hh_cent_tofwsdphi = new TH2F("hh_cent_tofwsdphi","hh_cent_tofwsdphi",100,0,100,200,-10,10);
  TH2F *hh_mom_tofwsdz = new TH2F("hh_mom_tofwsdz","hh_mom_tofwsdz",80,0,8,200,-10,10);
  TH2F *hh_mom_tofwsdphi = new TH2F("hh_mom_tofwsdphi","hh_mom_tofwsdphi",80,0,8,200,-10,10);
  TH2F *hh_zed_tofwsdz = new TH2F("hh_zed_tofwsdz","hh_zed_tofwsdz",160,-80,80,200,-10,10);
  TH2F *hh_zed_tofwsdphi = new TH2F("hh_zed_tofwsdphi","hh_zed_tofwsdphi",160,-80,80,200,-10,10);

  TH2F *hh_pos_strip_tofwsdz = new TH2F("hh_pos_strip_tofwsdz","hh_pos_strip_tofwsdz",512,0,511,200,-10,10);
  TH2F *hh_pos_strip_tofwsdphi = new TH2F("hh_pos_strip_tofwsdphi","hh_pos_strip_tofwsdphi",512,0,511,200,-10,10);
  TH2F *hh_pos_cent_tofwsdz = new TH2F("hh_pos_cent_tofwsdz","hh_pos_cent_tofwsdz",100,0,100,200,-10,10);
  TH2F *hh_pos_cent_tofwsdphi = new TH2F("hh_pos_cent_tofwsdphi","hh_pos_cent_tofwsdphi",100,0,100,200,-10,10);
  TH2F *hh_pos_mom_tofwsdz = new TH2F("hh_pos_mom_tofwsdz","hh_pos_mom_tofwsdz",80,0,8,200,-10,10);
  TH2F *hh_pos_mom_tofwsdphi = new TH2F("hh_pos_mom_tofwsdphi","hh_pos_mom_tofwsdphi",80,0,8,200,-10,10);
  TH2F *hh_pos_zed_tofwsdz = new TH2F("hh_pos_zed_tofwsdz","hh_pos_zed_tofwsdz",160,-80,80,200,-10,10);
  TH2F *hh_pos_zed_tofwsdphi = new TH2F("hh_pos_zed_tofwsdphi","hh_pos_zed_tofwsdphi",160,-80,80,200,-10,10);

  TH2F *hh_neg_strip_tofwsdz = new TH2F("hh_neg_strip_tofwsdz","hh_neg_strip_tofwsdz",512,0,511,200,-10,10);
  TH2F *hh_neg_strip_tofwsdphi = new TH2F("hh_neg_strip_tofwsdphi","hh_neg_strip_tofwsdphi",512,0,511,200,-10,10);
  TH2F *hh_neg_cent_tofwsdz = new TH2F("hh_neg_cent_tofwsdz","hh_neg_cent_tofwsdz",100,0,100,200,-10,10);
  TH2F *hh_neg_cent_tofwsdphi = new TH2F("hh_neg_cent_tofwsdphi","hh_neg_cent_tofwsdphi",100,0,100,200,-10,10);
  TH2F *hh_neg_mom_tofwsdz = new TH2F("hh_neg_mom_tofwsdz","hh_neg_mom_tofwsdz",80,0,8,200,-10,10);
  TH2F *hh_neg_mom_tofwsdphi = new TH2F("hh_neg_mom_tofwsdphi","hh_neg_mom_tofwsdphi",80,0,8,200,-10,10);
  TH2F *hh_neg_zed_tofwsdz = new TH2F("hh_neg_zed_tofwsdz","hh_neg_zed_tofwsdz",160,-80,80,200,-10,10);
  TH2F *hh_neg_zed_tofwsdphi = new TH2F("hh_neg_zed_tofwsdphi","hh_neg_zed_tofwsdphi",160,-80,80,200,-10,10);



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

	      int charge      = ktree->HadronTracks_charge[itrk];
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

	      if(fabs(zed)<3.0||fabs(zed)>75.0) continue;

	      if(!goodStrip(striptofw)) continue;

	      float pt = mom*sin(the0);
	      float beta = pltofw/ttofw/phbeta;
	      float qtofw = (tofwadcup+tofwadcdw)/2.0;

	      if(striptofw<0||striptofw>511)
		{
		  cout<<"BAD STRIP NUMBER!!! WTF!!! "<<striptofw<<endl;
		  continue;
		}

	      if(qtofw<60||qtofw>600)
		{
		  //cout<<"BAD ADC VALUE!!!"<<endl;
		  continue;
		}

	      if(runindex<0||runindex>848)
		{
		  cout<<"BAD RUNINDEX VALUE!!!  WTF!!! "<<runindex<<endl;
		  continue;
		}

	      float tofwsdz_before = sigma_tofwdz_before(mom,tofwdz);
	      float tofwsdphi_before = sigma_tofwdphi_before(mom,tofwdphi);

	      ttofw = ttofw - slewingoffset(striptofw,qtofw) - stripoffset[striptofw] - runoffset[runindex];
	      float deltat = ttofw - pltofw/phbeta*sqrt(mpion*mpion/mom/mom+1);

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
	      // then to small retuning
	      tofwsdz = recaltofwsdz(run,charge,mom,cent,tofwsdz);
	      tofwsdphi = recaltofwsdphi(run,charge,mom,cent,tofwsdphi);

	      float pc3_matching = fabs(pc3sdz)<2.0 && fabs(pc3sdphi)<2.0;
	      float tfw_matching = fabs(tofwsdz)<2.0 && fabs(tofwsdphi)<2.0;

	      hpc3sdz->Fill(pc3sdz);
	      hpc3sdphi->Fill(pc3sdphi);

	      //if(!pc3_matching||!tfw_matching) continue;
	      //if(!tfw_matching) continue;

	      ngoodtofwtracks++;
	      ngoodtofwtracks_snglevent++;

	      // -------------- //
	      // --- NORMAL --- //
	      // -------------- //
	      
	      htofwdz->Fill(tofwdz);
	      htofwdphi->Fill(tofwdphi);
	
	      hh_strip_tofwdz->Fill(striptofw,tofwdz);
	      hh_strip_tofwdphi->Fill(striptofw,tofwdphi);
	      hh_cent_tofwdz->Fill(cent,tofwdz);
	      hh_cent_tofwdphi->Fill(cent,tofwdphi);
	      hh_mom_tofwdz->Fill(mom,tofwdz);
	      hh_mom_tofwdphi->Fill(mom,tofwdphi);
	      hh_zed_tofwdz->Fill(zed,tofwdz);
	      hh_zed_tofwdphi->Fill(zed,tofwdphi);

	      if(charge>0)
		{
		  hh_pos_strip_tofwdz->Fill(striptofw,tofwdz);
		  hh_pos_strip_tofwdphi->Fill(striptofw,tofwdphi);
		  hh_pos_cent_tofwdz->Fill(cent,tofwdz);
		  hh_pos_cent_tofwdphi->Fill(cent,tofwdphi);
		  hh_pos_mom_tofwdz->Fill(mom,tofwdz);
		  hh_pos_mom_tofwdphi->Fill(mom,tofwdphi);
		  hh_pos_zed_tofwdz->Fill(zed,tofwdz);
		  hh_pos_zed_tofwdphi->Fill(zed,tofwdphi);
		}

	      if(charge<0)
		{
		  hh_neg_strip_tofwdz->Fill(striptofw,tofwdz);
		  hh_neg_strip_tofwdphi->Fill(striptofw,tofwdphi);
		  hh_neg_cent_tofwdz->Fill(cent,tofwdz);
		  hh_neg_cent_tofwdphi->Fill(cent,tofwdphi);
		  hh_neg_mom_tofwdz->Fill(mom,tofwdz);
		  hh_neg_mom_tofwdphi->Fill(mom,tofwdphi);
		  hh_neg_zed_tofwdz->Fill(zed,tofwdz);
		  hh_neg_zed_tofwdphi->Fill(zed,tofwdphi);
		}

	      if(charge>0&&striptofw<256)
		{
		  if(zed>0&&zed<15)
		    {
		      hh_sector1_tofwdz_posmom_poszed0->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_posmom_poszed0->Fill(mom,tofwdphi);
		    }
		  if(zed>15&&zed<30)
		    {
		      hh_sector1_tofwdz_posmom_poszed1->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_posmom_poszed1->Fill(mom,tofwdphi);
		    }
		  if(zed>30&&zed<45)
		    {
		      hh_sector1_tofwdz_posmom_poszed2->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_posmom_poszed2->Fill(mom,tofwdphi);
		    }
		  if(zed>45&&zed<60)
		    {
		      hh_sector1_tofwdz_posmom_poszed3->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_posmom_poszed3->Fill(mom,tofwdphi);
		    }
		  if(zed>60&&zed<75)
		    {
		      hh_sector1_tofwdz_posmom_poszed4->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_posmom_poszed4->Fill(mom,tofwdphi);
		    }
		  if(zed<0&&zed>-15)
		    {
		      hh_sector1_tofwdz_posmom_negzed0->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_posmom_negzed0->Fill(mom,tofwdphi);
		    }
		  if(zed<-15&&zed>-30)
		    {
		      hh_sector1_tofwdz_posmom_negzed1->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_posmom_negzed1->Fill(mom,tofwdphi);
		    }
		  if(zed<-30&&zed>-45)
		    {
		      hh_sector1_tofwdz_posmom_negzed2->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_posmom_negzed2->Fill(mom,tofwdphi);
		    }
		  if(zed<-45&&zed>-60)
		    {
		      hh_sector1_tofwdz_posmom_negzed3->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_posmom_negzed3->Fill(mom,tofwdphi);
		    }
		  if(zed<-60&&zed>-75)
		    {
		      hh_sector1_tofwdz_posmom_negzed4->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_posmom_negzed4->Fill(mom,tofwdphi);
		    }
		}
	      if(charge<0&&striptofw<256)
		{
		  if(zed>0&&zed<15)
		    {
		      hh_sector1_tofwdz_negmom_poszed0->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_negmom_poszed0->Fill(mom,tofwdphi);
		    }
		  if(zed>15&&zed<30)
		    {
		      hh_sector1_tofwdz_negmom_poszed1->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_negmom_poszed1->Fill(mom,tofwdphi);
		    }
		  if(zed>30&&zed<45)
		    {
		      hh_sector1_tofwdz_negmom_poszed2->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_negmom_poszed2->Fill(mom,tofwdphi);
		    }
		  if(zed>45&&zed<60)
		    {
		      hh_sector1_tofwdz_negmom_poszed3->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_negmom_poszed3->Fill(mom,tofwdphi);
		    }
		  if(zed>60&&zed<75)
		    {
		      hh_sector1_tofwdz_negmom_poszed4->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_negmom_poszed4->Fill(mom,tofwdphi);
		    }
		  if(zed<0&&zed>-15)
		    {
		      hh_sector1_tofwdz_negmom_negzed0->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_negmom_negzed0->Fill(mom,tofwdphi);
		    }
		  if(zed<-15&&zed>-30)
		    {
		      hh_sector1_tofwdz_negmom_negzed1->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_negmom_negzed1->Fill(mom,tofwdphi);
		    }
		  if(zed<-30&&zed>-45)
		    {
		      hh_sector1_tofwdz_negmom_negzed2->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_negmom_negzed2->Fill(mom,tofwdphi);
		    }
		  if(zed<-45&&zed>-60)
		    {
		      hh_sector1_tofwdz_negmom_negzed3->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_negmom_negzed3->Fill(mom,tofwdphi);
		    }
		  if(zed<-60&&zed>-75)
		    {
		      hh_sector1_tofwdz_negmom_negzed4->Fill(mom,tofwdz);
		      hh_sector1_tofwdphi_negmom_negzed4->Fill(mom,tofwdphi);
		    }
		}

	      // ------------------------

	      if(charge>0&&striptofw>255)
		{
		  if(zed>0&&zed<15)
		    {
		      hh_sector2_tofwdz_posmom_poszed0->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_posmom_poszed0->Fill(mom,tofwdphi);
		    }
		  if(zed>15&&zed<30)
		    {
		      hh_sector2_tofwdz_posmom_poszed1->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_posmom_poszed1->Fill(mom,tofwdphi);
		    }
		  if(zed>30&&zed<45)
		    {
		      hh_sector2_tofwdz_posmom_poszed2->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_posmom_poszed2->Fill(mom,tofwdphi);
		    }
		  if(zed>45&&zed<60)
		    {
		      hh_sector2_tofwdz_posmom_poszed3->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_posmom_poszed3->Fill(mom,tofwdphi);
		    }
		  if(zed>60&&zed<75)
		    {
		      hh_sector2_tofwdz_posmom_poszed4->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_posmom_poszed4->Fill(mom,tofwdphi);
		    }
		  if(zed<0&&zed>-15)
		    {
		      hh_sector2_tofwdz_posmom_negzed0->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_posmom_negzed0->Fill(mom,tofwdphi);
		    }
		  if(zed<-15&&zed>-30)
		    {
		      hh_sector2_tofwdz_posmom_negzed1->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_posmom_negzed1->Fill(mom,tofwdphi);
		    }
		  if(zed<-30&&zed>-45)
		    {
		      hh_sector2_tofwdz_posmom_negzed2->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_posmom_negzed2->Fill(mom,tofwdphi);
		    }
		  if(zed<-45&&zed>-60)
		    {
		      hh_sector2_tofwdz_posmom_negzed3->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_posmom_negzed3->Fill(mom,tofwdphi);
		    }
		  if(zed<-60&&zed>-75)
		    {
		      hh_sector2_tofwdz_posmom_negzed4->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_posmom_negzed4->Fill(mom,tofwdphi);
		    }
		}
	      if(charge<0&&striptofw>255)
		{
		  if(zed>0&&zed<15)
		    {
		      hh_sector2_tofwdz_negmom_poszed0->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_negmom_poszed0->Fill(mom,tofwdphi);
		    }
		  if(zed>15&&zed<30)
		    {
		      hh_sector2_tofwdz_negmom_poszed1->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_negmom_poszed1->Fill(mom,tofwdphi);
		    }
		  if(zed>30&&zed<45)
		    {
		      hh_sector2_tofwdz_negmom_poszed2->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_negmom_poszed2->Fill(mom,tofwdphi);
		    }
		  if(zed>45&&zed<60)
		    {
		      hh_sector2_tofwdz_negmom_poszed3->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_negmom_poszed3->Fill(mom,tofwdphi);
		    }
		  if(zed>60&&zed<75)
		    {
		      hh_sector2_tofwdz_negmom_poszed4->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_negmom_poszed4->Fill(mom,tofwdphi);
		    }
		  if(zed<0&&zed>-15)
		    {
		      hh_sector2_tofwdz_negmom_negzed0->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_negmom_negzed0->Fill(mom,tofwdphi);
		    }
		  if(zed<-15&&zed>-30)
		    {
		      hh_sector2_tofwdz_negmom_negzed1->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_negmom_negzed1->Fill(mom,tofwdphi);
		    }
		  if(zed<-30&&zed>-45)
		    {
		      hh_sector2_tofwdz_negmom_negzed2->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_negmom_negzed2->Fill(mom,tofwdphi);
		    }
		  if(zed<-45&&zed>-60)
		    {
		      hh_sector2_tofwdz_negmom_negzed3->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_negmom_negzed3->Fill(mom,tofwdphi);
		    }
		  if(zed<-60&&zed>-75)
		    {
		      hh_sector2_tofwdz_negmom_negzed4->Fill(mom,tofwdz);
		      hh_sector2_tofwdphi_negmom_negzed4->Fill(mom,tofwdphi);
		    }
		}

	      // ------------------ //
	      // --- SIGMALIZED --- //
	      // ------------------ //

	      //if(!tfw_matching) continue;
	      
	      htofwsdz->Fill(tofwsdz);
	      htofwsdphi->Fill(tofwsdphi);
	
	      if(fabs(tofwsdphi)<2.0) hh_strip_tofwsdz->Fill(striptofw,tofwsdz);
	      if(fabs(tofwsdz)<2.0)   hh_strip_tofwsdphi->Fill(striptofw,tofwsdphi);
	      if(fabs(tofwsdphi)<2.0) hh_cent_tofwsdz->Fill(cent,tofwsdz);
	      if(fabs(tofwsdz)<2.0)   hh_cent_tofwsdphi->Fill(cent,tofwsdphi);
	      if(fabs(tofwsdphi)<2.0) hh_mom_tofwsdz->Fill(mom,tofwsdz);
	      if(fabs(tofwsdz)<2.0)   hh_mom_tofwsdphi->Fill(mom,tofwsdphi);
	      if(fabs(tofwsdphi)<2.0) hh_zed_tofwsdz->Fill(zed,tofwsdz);
	      if(fabs(tofwsdz)<2.0)   hh_zed_tofwsdphi->Fill(zed,tofwsdphi);

	      if(charge>0)
		{
		  if(fabs(tofwsdphi)<2.0) hh_pos_strip_tofwsdz->Fill(striptofw,tofwsdz);
		  if(fabs(tofwsdz)<2.0)   hh_pos_strip_tofwsdphi->Fill(striptofw,tofwsdphi);
		  if(fabs(tofwsdphi)<2.0) hh_pos_cent_tofwsdz->Fill(cent,tofwsdz);
		  if(fabs(tofwsdz)<2.0)   hh_pos_cent_tofwsdphi->Fill(cent,tofwsdphi);
		  if(fabs(tofwsdphi)<2.0) hh_pos_mom_tofwsdz->Fill(mom,tofwsdz);
		  if(fabs(tofwsdz)<2.0)   hh_pos_mom_tofwsdphi->Fill(mom,tofwsdphi);
		  if(fabs(tofwsdphi)<2.0) hh_pos_zed_tofwsdz->Fill(zed,tofwsdz);
		  if(fabs(tofwsdz)<2.0)   hh_pos_zed_tofwsdphi->Fill(zed,tofwsdphi);
		}

	      if(charge<0)
		{
		  if(fabs(tofwsdphi)<2.0) hh_neg_strip_tofwsdz->Fill(striptofw,tofwsdz);
		  if(fabs(tofwsdz)<2.0)   hh_neg_strip_tofwsdphi->Fill(striptofw,tofwsdphi);
		  if(fabs(tofwsdphi)<2.0) hh_neg_cent_tofwsdz->Fill(cent,tofwsdz);
		  if(fabs(tofwsdz)<2.0)   hh_neg_cent_tofwsdphi->Fill(cent,tofwsdphi);
		  if(fabs(tofwsdphi)<2.0) hh_neg_mom_tofwsdz->Fill(mom,tofwsdz);
		  if(fabs(tofwsdz)<2.0)   hh_neg_mom_tofwsdphi->Fill(mom,tofwsdphi);
		  if(fabs(tofwsdphi)<2.0) hh_neg_zed_tofwsdz->Fill(zed,tofwsdz);
		  if(fabs(tofwsdz)<2.0)   hh_neg_zed_tofwsdphi->Fill(zed,tofwsdphi);
		}

	      if(charge>0&&striptofw<256)
		{
		  if(zed>0&&zed<15)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_posmom_poszed0->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_posmom_poszed0->Fill(mom,tofwsdphi);
		    }
		  if(zed>15&&zed<30)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_posmom_poszed1->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_posmom_poszed1->Fill(mom,tofwsdphi);
		    }
		  if(zed>30&&zed<45)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_posmom_poszed2->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_posmom_poszed2->Fill(mom,tofwsdphi);
		    }
		  if(zed>45&&zed<60)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_posmom_poszed3->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_posmom_poszed3->Fill(mom,tofwsdphi);
		    }
		  if(zed>60&&zed<75)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_posmom_poszed4->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_posmom_poszed4->Fill(mom,tofwsdphi);
		    }
		  if(zed<0&&zed>-15)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_posmom_negzed0->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_posmom_negzed0->Fill(mom,tofwsdphi);
		    }
		  if(zed<-15&&zed>-30)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_posmom_negzed1->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_posmom_negzed1->Fill(mom,tofwsdphi);
		    }
		  if(zed<-30&&zed>-45)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_posmom_negzed2->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_posmom_negzed2->Fill(mom,tofwsdphi);
		    }
		  if(zed<-45&&zed>-60)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_posmom_negzed3->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_posmom_negzed3->Fill(mom,tofwsdphi);
		    }
		  if(zed<-60&&zed>-75)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_posmom_negzed4->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_posmom_negzed4->Fill(mom,tofwsdphi);
		    }
		}
	      if(charge<0&&striptofw<256)
		{
		  if(zed>0&&zed<15)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_negmom_poszed0->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_negmom_poszed0->Fill(mom,tofwsdphi);
		    }
		  if(zed>15&&zed<30)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_negmom_poszed1->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_negmom_poszed1->Fill(mom,tofwsdphi);
		    }
		  if(zed>30&&zed<45)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_negmom_poszed2->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_negmom_poszed2->Fill(mom,tofwsdphi);
		    }
		  if(zed>45&&zed<60)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_negmom_poszed3->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_negmom_poszed3->Fill(mom,tofwsdphi);
		    }
		  if(zed>60&&zed<75)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_negmom_poszed4->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_negmom_poszed4->Fill(mom,tofwsdphi);
		    }
		  if(zed<0&&zed>-15)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_negmom_negzed0->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_negmom_negzed0->Fill(mom,tofwsdphi);
		    }
		  if(zed<-15&&zed>-30)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_negmom_negzed1->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_negmom_negzed1->Fill(mom,tofwsdphi);
		    }
		  if(zed<-30&&zed>-45)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_negmom_negzed2->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_negmom_negzed2->Fill(mom,tofwsdphi);
		    }
		  if(zed<-45&&zed>-60)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_negmom_negzed3->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_negmom_negzed3->Fill(mom,tofwsdphi);
		    }
		  if(zed<-60&&zed>-75)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector1_tofwsdz_negmom_negzed4->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector1_tofwsdphi_negmom_negzed4->Fill(mom,tofwsdphi);
		    }
		}

	      // ------------------------

	      if(charge>0&&striptofw>255)
		{
		  if(zed>0&&zed<15)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_posmom_poszed0->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_posmom_poszed0->Fill(mom,tofwsdphi);
		    }
		  if(zed>15&&zed<30)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_posmom_poszed1->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_posmom_poszed1->Fill(mom,tofwsdphi);
		    }
		  if(zed>30&&zed<45)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_posmom_poszed2->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_posmom_poszed2->Fill(mom,tofwsdphi);
		    }
		  if(zed>45&&zed<60)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_posmom_poszed3->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_posmom_poszed3->Fill(mom,tofwsdphi);
		    }
		  if(zed>60&&zed<75)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_posmom_poszed4->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_posmom_poszed4->Fill(mom,tofwsdphi);
		    }
		  if(zed<0&&zed>-15)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_posmom_negzed0->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_posmom_negzed0->Fill(mom,tofwsdphi);
		    }
		  if(zed<-15&&zed>-30)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_posmom_negzed1->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_posmom_negzed1->Fill(mom,tofwsdphi);
		    }
		  if(zed<-30&&zed>-45)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_posmom_negzed2->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_posmom_negzed2->Fill(mom,tofwsdphi);
		    }
		  if(zed<-45&&zed>-60)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_posmom_negzed3->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_posmom_negzed3->Fill(mom,tofwsdphi);
		    }
		  if(zed<-60&&zed>-75)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_posmom_negzed4->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_posmom_negzed4->Fill(mom,tofwsdphi);
		    }
		}
	      if(charge<0&&striptofw>255)
		{
		  if(zed>0&&zed<15)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_negmom_poszed0->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_negmom_poszed0->Fill(mom,tofwsdphi);
		    }
		  if(zed>15&&zed<30)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_negmom_poszed1->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_negmom_poszed1->Fill(mom,tofwsdphi);
		    }
		  if(zed>30&&zed<45)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_negmom_poszed2->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_negmom_poszed2->Fill(mom,tofwsdphi);
		    }
		  if(zed>45&&zed<60)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_negmom_poszed3->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_negmom_poszed3->Fill(mom,tofwsdphi);
		    }
		  if(zed>60&&zed<75)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_negmom_poszed4->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_negmom_poszed4->Fill(mom,tofwsdphi);
		    }
		  if(zed<0&&zed>-15)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_negmom_negzed0->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_negmom_negzed0->Fill(mom,tofwsdphi);
		    }
		  if(zed<-15&&zed>-30)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_negmom_negzed1->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_negmom_negzed1->Fill(mom,tofwsdphi);
		    }
		  if(zed<-30&&zed>-45)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_negmom_negzed2->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_negmom_negzed2->Fill(mom,tofwsdphi);
		    }
		  if(zed<-45&&zed>-60)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_negmom_negzed3->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_negmom_negzed3->Fill(mom,tofwsdphi);
		    }
		  if(zed<-60&&zed>-75)
		    {
		      if(fabs(tofwsdphi)<2.0) hh_sector2_tofwsdz_negmom_negzed4->Fill(mom,tofwsdz);
		      if(fabs(tofwsdz)<2.0)   hh_sector2_tofwsdphi_negmom_negzed4->Fill(mom,tofwsdphi);
		    }
		}

	      // ------------------------------ //
	      // --- END OF MATCHING HISTOS --- //
	      // ------------------------------ //

	      // ------------------------------ //
	      // --- NOW DOING TIMING CALIB --- //
	      // ------------------------------ //

	      if(mom>1.1&&mom<1.5&&tfw_matching)
		{
		  qtofwdis->Fill(qtofw);
		  tofwadcupdis->Fill(tofwadcup);
		  tofwadcdwdis->Fill(tofwadcdw);

		  deltatslewingdis_q->Fill(qtofw,deltat);
		  deltatslewingdis_u->Fill(tofwadcup,deltat);
		  deltatslewingdis_d->Fill(tofwadcdw,deltat);

		  deltatdis->Fill(deltat);
		  deltatrundis->Fill(runindex,deltat);
		  deltatstriptofwdis->Fill(striptofw,deltat);
		}
	      
	      float m2tofw = mom*mom*(ttofw*ttofw*phbeta*phbeta/(pltofw*pltofw)-1);

	      if(striptofw<256) m2mom_w1_dis->Fill(mom,m2tofw);
	      if(striptofw>255) m2mom_w2_dis->Fill(mom,m2tofw);

	      m2mom_dis->Fill(charge*mom,m2tofw);
	      ttofwmom_dis->Fill(charge*mom,deltat);
	      
	      if(charge>0)
		{
		  m2mompos_dis->Fill(mom,m2tofw);
		  ttofwmompos_dis->Fill(mom,deltat);
		  if(mom>1.1&&mom<1.5) m2pos_strip_dis->Fill(striptofw,m2tofw);
		  if(mom>1.1&&mom<1.5) m2pos_run_dis->Fill(runindex,m2tofw);
		  if(striptofw<256)   m2mompos_w1_dis->Fill(mom,m2tofw);
		  else m2mompos_w2_dis->Fill(mom,m2tofw);
		}
	      else
		{
		  m2momneg_dis->Fill(mom,m2tofw);
		  ttofwmomneg_dis->Fill(mom,deltat);
		  if(mom>1.1&&mom<1.5) m2neg_strip_dis->Fill(striptofw,m2tofw);
		  if(mom>1.1&&mom<1.5) m2neg_run_dis->Fill(runindex,m2tofw);
		  if(striptofw<256) m2momneg_w1_dis->Fill(mom,m2tofw);
		  else m2momneg_w2_dis->Fill(mom,m2tofw);
		}

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
  ifstream fin_plusplus("residuals-plusplus-pass0.dat");
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
  ifstream fin_minusminus("residuals-minusminus-pass0.dat");
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
      mean = 0.118857 + 0.44832/mom + -0.0670782/mom/mom + -0.470917/sqrt(mom);
      sigma = 1.85196 + 0.377207/mom + 0.121847/mom/mom + -0.615347/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-15&&zed<0))
    {
      mean = -0.887929 + -1.65139/mom + 0.238711/mom/mom + 2.33161/sqrt(mom);
      sigma = 2.45112 + 1.91209/mom + -0.147316/mom/mom + -2.44926/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-30&&zed<=-15))
    {
      mean = -0.318636 + 0.278464/mom + -0.0942135/mom/mom + 0.13127/sqrt(mom);
      sigma = 1.99126 + 0.86878/mom + 0.00770114/mom/mom + -1.11388/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-30&&zed<=-15))
    {
      mean = -1.6583 + -3.20044/mom + 0.494653/mom/mom + 4.35826/sqrt(mom);
      sigma = 2.99898 + 3.12418/mom + -0.353956/mom/mom + -3.99796/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-45&&zed<=-30))
    {
      mean = -2.19141 + -3.46518/mom + 0.517439/mom/mom + 5.14008/sqrt(mom);
      sigma = 2.32582 + 1.42119/mom + -0.0394429/mom/mom + -1.97489/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-45&&zed<=-30))
    {
      mean = -1.67791 + -2.7042/mom + 0.356897/mom/mom + 4.04736/sqrt(mom);
      sigma = 2.30131 + 1.5728/mom + -0.102653/mom/mom + -2.0109/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-60&&zed<=-45))
    {
      mean = -3.13567 + -4.93415/mom + 0.700394/mom/mom + 7.3987/sqrt(mom);
      sigma = 2.3354 + 1.50035/mom + -0.0552019/mom/mom + -2.03258/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-60&&zed<=-45))
    {
      mean = -2.2795 + -3.38023/mom + 0.408581/mom/mom + 5.3004/sqrt(mom);
      sigma = 2.3235 + 1.56445/mom + -0.0920534/mom/mom + -2.02554/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>-75&&zed<=-60))
    {
      mean = -5.01817 + -7.98609/mom + 1.07013/mom/mom + 12.0822/sqrt(mom);
      sigma = 1.62755 + 0.186647/mom + 0.170964/mom/mom + -0.210921/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>-75&&zed<=-60))
    {
      mean = -3.47709 + -5.38258/mom + 0.614885/mom/mom + 8.40917/sqrt(mom);
      sigma = 1.93967 + 0.810534/mom + 0.0373117/mom/mom + -0.995694/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=0&&zed<15))
    {
      mean = 0.284131 + 0.408777/mom + -0.0590066/mom/mom + -0.679911/sqrt(mom);
      sigma = 1.57288 + -0.050345/mom + 0.162942/mom/mom + 0.0667512/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=0&&zed<15))
    {
      mean = 0.309394 + 0.595149/mom + -0.105596/mom/mom + -0.803163/sqrt(mom);
      sigma = 2.24002 + 1.47797/mom + -0.0746522/mom/mom + -1.88627/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=15&&zed<30))
    {
      mean = 1.17709 + 1.95104/mom + -0.295115/mom/mom + -2.8358/sqrt(mom);
      sigma = 2.1538 + 1.25177/mom + -0.0544929/mom/mom + -1.5935/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=15&&zed<30))
    {
      mean = 0.668639 + 0.820013/mom + -0.083035/mom/mom + -1.41691/sqrt(mom);
      sigma = 2.60122 + 2.18897/mom + -0.187476/mom/mom + -2.85114/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=30&&zed<45))
    {
      mean = 1.93723 + 2.91336/mom + -0.430552/mom/mom + -4.40627/sqrt(mom);
      sigma = 2.16409 + 1.31525/mom + -0.0687775/mom/mom + -1.65664/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=30&&zed<45))
    {
      mean = 2.00953 + 3.21961/mom + -0.418311/mom/mom + -4.83906/sqrt(mom);
      sigma = 2.3427 + 1.49319/mom + -0.0608056/mom/mom + -2.03119/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=45&&zed<60))
    {
      mean = 3.39511 + 5.33321/mom + -0.739443/mom/mom + -8.01402/sqrt(mom);
      sigma = 1.93878 + 0.759397/mom + 0.019147/mom/mom + -0.946384/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=45&&zed<60))
    {
      mean = 2.69913 + 4.39169/mom + -0.557706/mom/mom + -6.60741/sqrt(mom);
      sigma = 2.70525 + 2.29834/mom + -0.181995/mom/mom + -3.06365/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==-1&&(zed>=60&&zed<75))
    {
      mean = 4.83086 + 7.5049/mom + -0.960219/mom/mom + -11.5073/sqrt(mom);
      sigma = 1.9763 + 1.07484/mom + -0.0323894/mom/mom + -1.24551/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==-1&&(zed>=60&&zed<75))
    {
      mean = 3.99431 + 6.3529/mom + -0.722833/mom/mom + -9.80686/sqrt(mom);
      sigma = 2.23846 + 1.45713/mom + -0.0593411/mom/mom + -1.87151/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-15&&zed<0))
    {
      mean = -0.548375 + -1.26574/mom + 0.209797/mom/mom + 1.65638/sqrt(mom);
      sigma = 1.52207 + 0.175477/mom + 0.101533/mom/mom + 0.00237232/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-15&&zed<0))
    {
      mean = -0.326846 + -0.606593/mom + 0.112963/mom/mom + 0.827888/sqrt(mom);
      sigma = 2.3754 + 1.60766/mom + -0.0811662/mom/mom + -2.17488/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-30&&zed<=-15))
    {
      mean = -1.44339 + -2.66415/mom + 0.403652/mom/mom + 3.71072/sqrt(mom);
      sigma = 2.03475 + 0.930868/mom + 0.0268905/mom/mom + -1.20627/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-30&&zed<=-15))
    {
      mean = -0.996564 + -1.34013/mom + 0.189923/mom/mom + 2.14019/sqrt(mom);
      sigma = 2.16487 + 1.14845/mom + 0.000613678/mom/mom + -1.57922/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-45&&zed<=-30))
    {
      mean = -1.35035 + -2.1261/mom + 0.267944/mom/mom + 3.2255/sqrt(mom);
      sigma = 2.24002 + 1.58303/mom + -0.103115/mom/mom + -1.93371/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-45&&zed<=-30))
    {
      mean = -2.00598 + -2.77994/mom + 0.367476/mom/mom + 4.43519/sqrt(mom);
      sigma = 2.17043 + 1.24619/mom + -0.0154762/mom/mom + -1.67137/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-60&&zed<=-45))
    {
      mean = -2.38677 + -3.81788/mom + 0.515507/mom/mom + 5.71924/sqrt(mom);
      sigma = 1.71708 + 0.237803/mom + 0.147182/mom/mom + -0.316847/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-60&&zed<=-45))
    {
      mean = -3.76807 + -5.87265/mom + 0.799884/mom/mom + 8.888/sqrt(mom);
      sigma = 2.05932 + 1.09563/mom + -0.00489511/mom/mom + -1.40773/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>-75&&zed<=-60))
    {
      mean = -4.29002 + -6.93102/mom + 0.839055/mom/mom + 10.5251/sqrt(mom);
      sigma = 1.87369 + 0.949164/mom + -0.00818276/mom/mom + -0.988759/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>-75&&zed<=-60))
    {
      mean = -4.81944 + -7.5784/mom + 0.993798/mom/mom + 11.5921/sqrt(mom);
      sigma = 2.32011 + 1.52623/mom + -0.0313512/mom/mom + -2.05697/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=0&&zed<15))
    {
      mean = 0.464557 + 0.825474/mom + -0.124259/mom/mom + -1.2185/sqrt(mom);
      sigma = 1.42964 + -0.495333/mom + 0.270289/mom/mom + 0.565728/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=0&&zed<15))
    {
      mean = 0.312731 + 0.504146/mom + -0.0787295/mom/mom + -0.727859/sqrt(mom);
      sigma = 2.22523 + 1.57137/mom + -0.106864/mom/mom + -1.94069/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=15&&zed<30))
    {
      mean = 0.629459 + 0.80929/mom + -0.084544/mom/mom + -1.35801/sqrt(mom);
      sigma = 2.16877 + 1.19697/mom + -0.00403697/mom/mom + -1.59377/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=15&&zed<30))
    {
      mean = 1.1932 + 1.83005/mom + -0.258668/mom/mom + -2.75013/sqrt(mom);
      sigma = 2.48895 + 1.86628/mom + -0.116078/mom/mom + -2.49884/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=30&&zed<45))
    {
      mean = 1.98369 + 3.20557/mom + -0.421325/mom/mom + -4.77635/sqrt(mom);
      sigma = 2.16301 + 1.08854/mom + 0.0257505/mom/mom + -1.51806/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=30&&zed<45))
    {
      mean = 1.9219 + 2.80807/mom + -0.403595/mom/mom + -4.32112/sqrt(mom);
      sigma = 2.11105 + 1.12451/mom + -0.0134816/mom/mom + -1.48048/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=45&&zed<60))
    {
      mean = 2.84861 + 4.63242/mom + -0.590897/mom/mom + -6.96465/sqrt(mom);
      sigma = 2.26233 + 1.57835/mom + -0.0876356/mom/mom + -1.97074/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=45&&zed<60))
    {
      mean = 3.10954 + 4.54664/mom + -0.603995/mom/mom + -7.08445/sqrt(mom);
      sigma = 2.59936 + 2.19635/mom + -0.186667/mom/mom + -2.85461/sqrt(mom);
    }
  else if(run>250484&&striptofw<256&&charge==1&&(zed>=60&&zed<75))
    {
      mean = 4.07977 + 6.64099/mom + -0.791734/mom/mom + -10.0782/sqrt(mom);
      sigma = 2.15407 + 1.15433/mom + 0.0293931/mom/mom + -1.56303/sqrt(mom);
    }
  else if(run<250593&&striptofw<256&&charge==1&&(zed>=60&&zed<75))
    {
      mean = 4.27726 + 6.42452/mom + -0.788475/mom/mom + -10.0816/sqrt(mom);
      sigma = 2.4856 + 2.06497/mom + -0.165635/mom/mom + -2.62459/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-15&&zed<0))
    {
      mean = 0.0926492 + 0.154977/mom + -0.0377246/mom/mom + -0.189855/sqrt(mom);
      sigma = 1.47242 + -0.090414/mom + 0.13363/mom/mom + 0.225057/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-15&&zed<0))
    {
      mean = -0.154461 + -0.0457669/mom + -0.00444047/mom/mom + 0.215456/sqrt(mom);
      sigma = 2.52042 + 2.09284/mom + -0.212162/mom/mom + -2.67583/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-30&&zed<=-15))
    {
      mean = -0.894383 + -1.64938/mom + 0.241348/mom/mom + 2.32793/sqrt(mom);
      sigma = 1.88304 + 0.651134/mom + 0.039407/mom/mom + -0.830914/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-30&&zed<=-15))
    {
      mean = -1.0908 + -1.98589/mom + 0.310546/mom/mom + 2.74794/sqrt(mom);
      sigma = 2.82846 + 2.82668/mom + -0.330174/mom/mom + -3.60372/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-45&&zed<=-30))
    {
      mean = -1.50945 + -2.13346/mom + 0.264437/mom/mom + 3.39734/sqrt(mom);
      sigma = 1.67232 + 0.201493/mom + 0.133784/mom/mom + -0.293039/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-45&&zed<=-30))
    {
      mean = -1.67263 + -2.54671/mom + 0.323876/mom/mom + 3.92028/sqrt(mom);
      sigma = 2.5558 + 2.31323/mom + -0.247514/mom/mom + -2.91826/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-60&&zed<=-45))
    {
      mean = -2.52307 + -3.57283/mom + 0.424225/mom/mom + 5.7137/sqrt(mom);
      sigma = 2.29138 + 1.59385/mom + -0.101139/mom/mom + -2.06929/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-60&&zed<=-45))
    {
      mean = -2.77362 + -4.44267/mom + 0.55129/mom/mom + 6.73039/sqrt(mom);
      sigma = 2.45029 + 2.09654/mom + -0.208547/mom/mom + -2.62993/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>-75&&zed<=-60))
    {
      mean = -3.95421 + -5.81549/mom + 0.692123/mom/mom + 9.19154/sqrt(mom);
      sigma = 2.22862 + 1.4371/mom + -0.0469274/mom/mom + -1.893/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>-75&&zed<=-60))
    {
      mean = -4.35646 + -7.18593/mom + 0.864017/mom/mom + 10.8461/sqrt(mom);
      sigma = 2.40814 + 1.91155/mom + -0.148504/mom/mom + -2.45544/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=0&&zed<15))
    {
      mean = -0.00442025 + -0.707844/mom + 0.144751/mom/mom + 0.520531/sqrt(mom);
      sigma = 1.47995 + -0.450066/mom + 0.269138/mom/mom + 0.420051/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=0&&zed<15))
    {
      mean = 0.29114 + 0.482772/mom + -0.0450469/mom/mom + -0.766982/sqrt(mom);
      sigma = 2.90142 + 2.88738/mom + -0.323781/mom/mom + -3.73569/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=15&&zed<30))
    {
      mean = 0.682381 + 0.479583/mom + -0.0378244/mom/mom + -1.12262/sqrt(mom);
      sigma = 1.27471 + -0.439322/mom + 0.193853/mom/mom + 0.698075/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=15&&zed<30))
    {
      mean = 0.978699 + 1.76836/mom + -0.236944/mom/mom + -2.5342/sqrt(mom);
      sigma = 2.47868 + 2.00646/mom + -0.181638/mom/mom + -2.59445/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=30&&zed<45))
    {
      mean = 1.5732 + 1.99154/mom + -0.267465/mom/mom + -3.29353/sqrt(mom);
      sigma = 2.25547 + 1.53131/mom + -0.0995947/mom/mom + -1.96847/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=30&&zed<45))
    {
      mean = 1.53016 + 2.42181/mom + -0.278644/mom/mom + -3.71847/sqrt(mom);
      sigma = 2.49883 + 2.21432/mom + -0.231053/mom/mom + -2.77927/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=45&&zed<60))
    {
      mean = 3.31061 + 4.59405/mom + -0.574366/mom/mom + -7.36833/sqrt(mom);
      sigma = 1.85311 + 0.535455/mom + 0.0792243/mom/mom + -0.753986/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=45&&zed<60))
    {
      mean = 2.37377 + 3.78019/mom + -0.418585/mom/mom + -5.81988/sqrt(mom);
      sigma = 2.65017 + 2.68687/mom + -0.316344/mom/mom + -3.32126/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==-1&&(zed>=60&&zed<75))
    {
      mean = 4.54425 + 6.60116/mom + -0.794781/mom/mom + -10.5138/sqrt(mom);
      sigma = 2.37939 + 1.93069/mom + -0.169826/mom/mom + -2.38403/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==-1&&(zed>=60&&zed<75))
    {
      mean = 3.66704 + 5.96924/mom + -0.653699/mom/mom + -9.15552/sqrt(mom);
      sigma = 2.45787 + 1.95686/mom + -0.139586/mom/mom + -2.57564/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-15&&zed<0))
    {
      mean = -0.0375001 + 0.135592/mom + -0.0379052/mom/mom + -0.0171405/sqrt(mom);
      sigma = 2.7032 + 2.47668/mom + -0.254436/mom/mom + -3.18541/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-15&&zed<0))
    {
      mean = -0.129831 + -0.198001/mom + 0.0126297/mom/mom + 0.320624/sqrt(mom);
      sigma = 2.24849 + 1.40758/mom + -0.0660383/mom/mom + -1.86509/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-30&&zed<=-15))
    {
      mean = -0.97984 + -1.73595/mom + 0.270629/mom/mom + 2.43877/sqrt(mom);
      sigma = 3.03152 + 3.25708/mom + -0.39262/mom/mom + -4.15107/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-30&&zed<=-15))
    {
      mean = -0.950882 + -1.64138/mom + 0.21705/mom/mom + 2.40744/sqrt(mom);
      sigma = 2.54865 + 2.06241/mom + -0.157171/mom/mom + -2.73787/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-45&&zed<=-30))
    {
      mean = -2.26839 + -4.01311/mom + 0.578061/mom/mom + 5.73338/sqrt(mom);
      sigma = 2.49208 + 2.03679/mom + -0.186065/mom/mom + -2.61432/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-45&&zed<=-30))
    {
      mean = -1.77171 + -2.63088/mom + 0.340697/mom/mom + 4.07302/sqrt(mom);
      sigma = 2.20746 + 1.45998/mom + -0.0771526/mom/mom + -1.89571/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-60&&zed<=-45))
    {
      mean = -2.92277 + -4.70065/mom + 0.583519/mom/mom + 7.09753/sqrt(mom);
      sigma = 2.68127 + 2.62277/mom + -0.287135/mom/mom + -3.28529/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-60&&zed<=-45))
    {
      mean = -2.8682 + -4.34834/mom + 0.558313/mom/mom + 6.70585/sqrt(mom);
      sigma = 2.22717 + 1.55093/mom + -0.0945925/mom/mom + -1.9803/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>-75&&zed<=-60))
    {
      mean = -4.45313 + -7.41983/mom + 0.904725/mom/mom + 11.1116/sqrt(mom);
      sigma = 1.89262 + 0.745123/mom + 0.0591121/mom/mom + -0.95576/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>-75&&zed<=-60))
    {
      mean = -4.61218 + -7.09011/mom + 0.86467/mom/mom + 10.9987/sqrt(mom);
      sigma = 2.06084 + 1.1392/mom + -0.0051513/mom/mom + -1.48479/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=0&&zed<15))
    {
      mean = 0.0884734 + 0.327215/mom + -0.0426264/mom/mom + -0.44258/sqrt(mom);
      sigma = 2.94555 + 3.34951/mom + -0.419652/mom/mom + -4.11522/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=0&&zed<15))
    {
      mean = 0.0665919 + -0.469105/mom + 0.104013/mom/mom + 0.284039/sqrt(mom);
      sigma = 2.38707 + 1.70833/mom + -0.111043/mom/mom + -2.26219/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=15&&zed<30))
    {
      mean = 1.3599 + 2.51784/mom + -0.348411/mom/mom + -3.56819/sqrt(mom);
      sigma = 2.11665 + 1.19054/mom + -0.0333198/mom/mom + -1.54245/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=15&&zed<30))
    {
      mean = 0.975301 + 1.14092/mom + -0.149871/mom/mom + -1.95228/sqrt(mom);
      sigma = 2.42814 + 1.75236/mom + -0.114701/mom/mom + -2.35718/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=30&&zed<45))
    {
      mean = 2.03334 + 3.74313/mom + -0.518695/mom/mom + -5.29154/sqrt(mom);
      sigma = 2.23103 + 1.72425/mom + -0.147584/mom/mom + -2.08032/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=30&&zed<45))
    {
      mean = 1.67597 + 2.00863/mom + -0.255469/mom/mom + -3.42685/sqrt(mom);
      sigma = 2.0682 + 1.029/mom + 0.000698977/mom/mom + -1.40265/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=45&&zed<60))
    {
      mean = 2.91679 + 5.044/mom + -0.636306/mom/mom + -7.39109/sqrt(mom);
      sigma = 2.22674 + 1.68376/mom + -0.129035/mom/mom + -2.05946/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=45&&zed<60))
    {
      mean = 3.08236 + 4.29672/mom + -0.556553/mom/mom + -6.85298/sqrt(mom);
      sigma = 2.11299 + 1.21567/mom + -0.041905/mom/mom + -1.58668/sqrt(mom);
    }
  else if(run>250484&&striptofw>255&&charge==1&&(zed>=60&&zed<75))
    {
      mean = 3.94841 + 6.61854/mom + -0.780877/mom/mom + -9.92479/sqrt(mom);
      sigma = 2.02333 + 1.0383/mom + 0.01765/mom/mom + -1.34973/sqrt(mom);
    }
  else if(run<250593&&striptofw>255&&charge==1&&(zed>=60&&zed<75))
    {
      mean = 4.04044 + 5.52947/mom + -0.624857/mom/mom + -9.13369/sqrt(mom);
      sigma = 1.99925 + 1.20458/mom + -0.0410261/mom/mom + -1.4274/sqrt(mom);
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

  else
    {
      cout<<"significant issue in caltofwsdphi"<<endl;
      return -9999;
    }
  
  value = (tofwdphi - mean)/sigma;

  return value;
  
}


float recaltofwsdz(int run, int charge, float mom, float cent, float tofwsdz)
{

  float mean = -9999;
  float sigma = -9999;
  float value = -9999;
  
  // first momentum dependence

  if(run>250484&&charge==-1)
    {
      mean = -0.048906 + -0.0996663/mom + 0.0152957/mom/mom + 0.130708/sqrt(mom);
      sigma = 0.962432 + 0.00122781/mom + 0.00337/mom/mom + 0.0152555/sqrt(mom);
    }
  if(run<250593&&charge==-1)
    {
      mean = 0.00274288 + 0.0189732/mom + -0.00460276/mom/mom + -0.018987/sqrt(mom);
      sigma = 0.747479 + -0.449013/mom + 0.0760965/mom/mom + 0.604721/sqrt(mom);
    }
  if(run>250484&&charge==1)
    {
      mean = -0.0346139 + -0.087025/mom + 0.014171/mom/mom + 0.104199/sqrt(mom);
      sigma = 0.920034 + -0.0468048/mom + 0.00173597/mom/mom + 0.121399/sqrt(mom);
    }
  if(run<250593&&charge==1)
    {
      mean = -0.00459538 + 0.00295452/mom + -0.00152985/mom/mom + 0.000196185/sqrt(mom);
      sigma = 0.840336 + -0.196013/mom + 0.0250453/mom/mom + 0.324501/sqrt(mom);
    }

  // then centrality dependence

  if(run>250484&&charge==-1)
    {
      mean += -0.210696 + -1.26551/cent + 0.44462/cent/cent + 1.21433/sqrt(cent);
      //sigma *= 1.17394 + 1.81453/cent + -0.751032/cent/cent + -1.31427/sqrt(cent);
      sigma *= 0.919473 + 0.00214718*cent;
    }
  if(run<250593&&charge==-1)
    {
      mean += -0.183921 + -1.05239/cent + 0.355434/cent/cent + 1.04479/sqrt(cent);
      //sigma *= 1.16481 + 1.69363/cent + -0.687156/cent/cent + -1.24422/sqrt(cent);
      sigma *= 0.920799 + 0.00208961*cent;
    }
  if(run>250484&&charge==1)
    {
      mean += -0.20897 + -1.21498/cent + 0.414318/cent/cent + 1.18956/sqrt(cent);
      //sigma *= 1.19494 + 1.88858/cent + -0.782993/cent/cent + -1.37349/sqrt(cent);
      sigma *= 0.926313 + 0.00230289*cent;
    }
  if(run<250593&&charge==1)
    {
      mean += -0.186609 + -1.08037/cent + 0.367849/cent/cent + 1.06068/sqrt(cent);
      //sigma *= 1.19407 + 1.8811/cent + -0.772013/cent/cent + -1.37096/sqrt(cent);
      sigma *= 0.926858 + 0.00226635*cent;
    }

  value = (tofwsdz - mean)/sigma;
  return value;

}

float recaltofwsdphi(int run, int charge, float mom, float cent, float tofwsdphi)
{

  float mean = -9999;
  float sigma = -9999;
  float value = -9999;
  
  // first momentum dependence

  if(run>250484&&charge==-1)
    {
      mean = 0.22416 + 0.842227/mom + -0.176679/mom/mom + -0.864182/sqrt(mom);
      sigma = 0.487433 + -1.08226/mom + 0.183494/mom/mom + 1.41135/sqrt(mom);
    }
  if(run<250593&&charge==-1)
    {
      mean = -0.563194 + -1.14519/mom + 0.139156/mom/mom + 1.60343/sqrt(mom);
      sigma = 0.63278 + -0.57265/mom + 0.078391/mom/mom + 0.876973/sqrt(mom);
    }
  if(run>250484&&charge==1)
    {
      mean = -0.247006 + -0.522812/mom + 0.0479351/mom/mom + 0.75035/sqrt(mom);
      sigma = 0.552407 + -0.69677/mom + 0.0911059/mom/mom + 1.05629/sqrt(mom);
    }
  if(run<250593&&charge==1)
    {
      mean = -0.1857 + -0.0237715/mom + -0.0338682/mom/mom + 0.264768/sqrt(mom);
      sigma = 0.286994 + -1.39448/mom + 0.219534/mom/mom + 1.87989/sqrt(mom);
    }
  
  // then centrality dependence
  
  if(run>250484&&charge==-1)
    {
      mean += 0.020819 + 0.00606675/cent + -0.00298826/cent/cent + -0.00817771/sqrt(cent);
      sigma *= 1.00161 + -0.0307094/cent + 0.0144807/cent/cent + 0.025686/sqrt(cent);
    }
  if(run<250593&&charge==-1)
    {
      mean += 0.0047856 + -0.0718823/cent + 0.0301139/cent/cent + 0.0510441/sqrt(cent);
      sigma *= 1.01746 + -0.0200882/cent + 0.00469142/cent/cent + 0.02088/sqrt(cent);
    }
  if(run>250484&&charge==1)
    {
      mean += -0.00117254 + -0.102764/cent + 0.0442156/cent/cent + 0.0719253/sqrt(cent);
      sigma *= 0.993903 + -0.088683/cent + 0.0309082/cent/cent + 0.0687418/sqrt(cent);
    }
  if(run<250593&&charge==1)
    {
      mean += 0.0201114 + 0.0188802/cent + -0.00477109/cent/cent + -0.0169551/sqrt(cent);
      sigma *= 0.989184 + -0.0446839/cent + 0.0197513/cent/cent + 0.033173/sqrt(cent);
    }
  
  value = (tofwsdphi - mean)/sigma;
  return value;
  
}

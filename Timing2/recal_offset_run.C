#include <iostream>
#include <iomanip>
using namespace std;

void recal_offset_run()
{

  //ifstream fpass0("PASS0_run/run_gaus.dat");
  //ifstream fpass1("PASS1_run/run_gaus.dat");
  //ofstream fcomb("run-by-run-pass1.dat");

  //ifstream fpass0("run-by-run-pass1.dat");
  //ifstream fpass1("PASS2_run/run_gaus.dat");
  //ofstream fcomb("run-by-run-pass2.dat");

  //ifstream fpass0("run-by-run-pass2.dat");
  //ifstream fpass1("PASS3_run/run_gaus.dat");
  //ofstream fcomb("run-by-run-pass3.dat");

  ifstream fpass0("run-by-run-pass3.dat");
  ifstream fpass1("PASS4_run/run_gaus.dat");
  ofstream fcomb("run-by-run-pass4a.dat");

  double tmp, pass0, pass1;
  double test0, test1;
  double run, naan;
  naan = -9999;

  for(int i=0; i<848; i++)
    {
      fpass0>>run>>tmp>>pass0>>tmp>>tmp>>tmp;
      fpass1>>run>>tmp>>pass1>>tmp>>tmp>>tmp;
      if(test0==(double)1.41421||
	 test1==(double)1.41421||
	 pass0==(double)-9999||
	 pass1==(double)-9999)
	fcomb<<run<<"\t"<<naan<<"\t"<<naan<<"\t"<<naan<<"\t"<<naan<<"\t"<<naan<<endl;
      else fcomb<<run<<"\t"<<naan<<"\t"<<pass0+pass1<<"\t"<<naan<<"\t"<<naan<<"\t"<<naan<<endl;
    }





}

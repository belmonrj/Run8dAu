#include <iostream>
#include <iomanip>
using namespace std;

void recal_offset_strip()
{


  //ifstream fpass0("PASS0_striptofw/striptofw_gaus.dat");
  //ifstream fpass1("PASS1_striptofw/striptofw_gaus.dat");
  //ofstream fcomb("strip-by-strip-pass1.dat");

  //ifstream fpass0("strip-by-strip-pass1.dat");
  //ifstream fpass1("PASS2_striptofw/striptofw_gaus.dat");
  //ofstream fcomb("strip-by-strip-pass2.dat");

  //ifstream fpass0("strip-by-strip-pass2.dat");
  //ifstream fpass1("PASS3_striptofw/striptofw_gaus.dat");
  //ofstream fcomb("strip-by-strip-pass3.dat");

  ifstream fpass0("strip-by-strip-pass3.dat");
  ifstream fpass1("PASS4_striptofw/striptofw_gaus.dat");
  ofstream fcomb("strip-by-strip-pass4_NEW.dat");

  double tmp, pass0, pass1;
  double test0, test1;
  double strip, naan;
  naan = -9999;

  //cout.precision(8);

  for(int i=0; i<512; i++)
    {
      fpass0>>strip>>tmp>>pass0>>test0>>tmp>>tmp;
      fpass1>>strip>>tmp>>pass1>>test1>>tmp>>tmp;
      double toff = pass0+pass1;
      if(test0==(double)1.41421||
	 test1==(double)1.41421||
	 pass0==(double)-9999||
	 pass1==(double)-9999)
	{fcomb<<strip<<"\t"<<naan<<"\t"<<naan<<"\t"<<naan<<"\t"<<naan<<"\t"<<naan<<endl;}
      else 
	{
	  fcomb<<strip<<"\t"<<naan<<"\t"<<setprecision(8)<<pass0+pass1<<"\t"<<naan<<"\t"<<naan<<"\t"<<naan<<endl;
	  //cout<<strip<<"\t"<<naan<<"\t"<<double(pass0+pass1)<<"\t"<<naan<<"\t"<<naan<<"\t"<<naan<<endl;
	  //cout<<strip<<"\t"<<naan<<"\t"<<toff<<"\t"<<naan<<"\t"<<naan<<"\t"<<naan<<endl;
	  //printf("%d \t -9999 \t %f \t -9999 \t -9999 \t -9999 \n",strip,toff);
	}
    }





}

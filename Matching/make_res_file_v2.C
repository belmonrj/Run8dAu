void make_res_file_v2()
{

  int stripid;
  float tmp;
  float posdz, negdz, posdphi, negdphi;
  float test1, test2, test3, test4;

  ifstream fposdz("residual/res_strip_posdz_plusplus.dat");
  ifstream fnegdz("residual/res_strip_negdz_plusplus.dat");
  ifstream fposdphi("residual/res_strip_posdphi_plusplus.dat");
  ifstream fnegdphi("residual/res_strip_negdphi_plusplus.dat");
  ofstream fout("residuals-plusplus-pass0.dat");
  for(int i=0; i<512; i++)
    {
      fposdz>>stripid>>tmp>>posdz>>test1>>tmp>>tmp;
      fnegdz>>stripid>>tmp>>negdz>>test2>>tmp>>tmp;
      fposdphi>>stripid>>tmp>>posdphi>>test3>>tmp>>tmp;
      fnegdphi>>stripid>>tmp>>negdphi>>test4>>tmp>>tmp;
      if(i!=stripid)
	{
	  cout<<"CRITICAL ERROR!!!"<<endl<<"Now crashing and burning..."<<endl; 
	  break;
	}
      if(test1==(float)1.41421||
	 test2==(float)1.41421||
	 test3==(float)1.41421||
	 test4==(float)1.41421)
	{
	  posdz=-9999; 
	  negdz=-9999; 
	  posdphi=-9999; 
	  negdphi=-9999;
	}
      if(fabs(test1)>fabs(posdz)) posdz=0;
      if(fabs(test2)>fabs(negdz)) negdz=0;
      if(fabs(test3)>fabs(posdphi)) posdphi=0;
      if(fabs(test4)>fabs(negdphi)) negdphi=0;

      fout<<stripid<<"\t"<<posdz<<"\t"<<negdz<<"\t"<<posdphi<<"\t"<<negdphi<<endl;
    }
  fposdz.close();
  fnegdz.close();
  fposdphi.close();
  fnegdphi.close();
  fout.close();

  // ---
  // --- BREAK!!!
  // ---

  fposdz.open("residual/res_strip_posdz_minusminus.dat");
  fnegdz.open("residual/res_strip_negdz_minusminus.dat");
  fposdphi.open("residual/res_strip_posdphi_minusminus.dat");
  fnegdphi.open("residual/res_strip_negdphi_minusminus.dat");
  fout.open("residuals-minusminus-pass0.dat");
  for(int i=0; i<512; i++)
    {
      fposdz>>stripid>>tmp>>posdz>>test1>>tmp>>tmp;
      fnegdz>>stripid>>tmp>>negdz>>test2>>tmp>>tmp;
      fposdphi>>stripid>>tmp>>posdphi>>test3>>tmp>>tmp;
      fnegdphi>>stripid>>tmp>>negdphi>>test4>>tmp>>tmp;
      if(i!=stripid)
	{
	  cout<<"CRITICAL ERROR!!!"<<endl<<"Now crashing and burning..."<<endl; 
	  break;
	}
      if(test1==(float)1.41421||
	 test2==(float)1.41421||
	 test3==(float)1.41421||
	 test4==(float)1.41421)
	{
	  posdz=-9999; 
	  negdz=-9999; 
	  posdphi=-9999; 
	  negdphi=-9999;
	}
      if(fabs(test1)>fabs(posdz)) posdz=0;
      if(fabs(test2)>fabs(negdz)) negdz=0;
      if(fabs(test3)>fabs(posdphi)) posdphi=0;
      if(fabs(test4)>fabs(negdphi)) negdphi=0;

      fout<<stripid<<"\t"<<posdz<<"\t"<<negdz<<"\t"<<posdphi<<"\t"<<negdphi<<endl;
    }


}

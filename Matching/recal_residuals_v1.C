void recal_residuals_v1()
{

  ifstream fpass0("residuals-pass0.dat");
  ifstream fpass1("residuals-pass01.dat");
  ofstream fout("residuals-pass1.dat");

  int strip;
  float posdz0, negdz0, posdphi0, negdphi0;
  float posdz1, negdz1, posdphi1, negdphi1;
  float posdz, negdz, posdphi, negdphi;
  float tmp;

  for(int i=0; i<512; i++)
    {
      fpass0>>strip>>posdz0>>negdz0>>posdphi0>>negdphi0;
      fpass1>>strip>>posdz1>>negdz1>>posdphi1>>negdphi1;
      posdz=posdz0+posdz1;
      negdz=negdz0+negdz1;
      posdphi=posdphi0+posdphi1;
      negdphi=negdphi0+negdphi1;
      if(posdz==-19998) posdz=-9999;
      if(negdz==-19998) negdz=-9999;
      if(posdphi==-19998) posdphi=-9999;
      if(negdphi==-19998) negdphi=-9999;
      fout<<strip<<"\t"<<posdz<<"\t"<<negdz<<"\t"<<posdphi<<"\t"<<negdphi<<endl;
    }



}

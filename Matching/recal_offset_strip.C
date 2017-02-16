void recal_offset_strip()
{

  ifstream fpass0("residuals-plusplus-pass0.dat");
  ifstream fpass1("residuals-plusplus-pass1.dat");
  ofstream fcomb("residuals-plusplus-pass2.dat");

  //double tmp, pass0, pass1;
  //double test0, test1;
  double strip, naan;
  double posdz,  negdz,  posdphi,  negdphi;
  double posdz0, negdz0, posdphi0, negdphi0;
  double posdz1, negdz1, posdphi1, negdphi1;
  naan = -9999;

  for(int i=0; i<512; i++)
    {
      fpass0>>strip>>posdz0>>negdz0>>posdphi0>>negdphi0;
      fpass1>>strip>>posdz1>>negdz1>>posdphi1>>negdphi1;
      posdz = posdz0+posdz1;      
      negdz = negdz0+negdz1;
      posdphi = posdphi0+posdphi1;      
      negdphi = negdphi0+negdphi1;      
      if(posdz0==-9999||posdz1==-9999) {posdz = -9999;}
      if(negdz0==-9999||negdz1==-9999) {negdz = -9999;}
      if(posdphi0==-9999||posdphi1==-9999) {posdphi = -9999;}
      if(negdphi0==-9999||negdphi1==-9999) {negdphi = -9999;}
      fcomb<<strip<<"\t"<<posdz<<"\t"<<negdz<<"\t"<<posdphi<<"\t"<<negdphi<<"\t"<<endl;
    }


}

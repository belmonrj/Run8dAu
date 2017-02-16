float tunepc3sdphi()
{

  float mean = -9999;
  float sigma = -9999;

  float p0 = -9999;
  float p1 = -9999;
  float p2 = -9999;
  float p3 = -9999;
  
  float q0 = -9999;
  float q1 = -9999;
  float q2 = -9999;
  float q3 = -9999;
  
  // ------ //
  // sigmas //
  // ------ //

  if(fabs(zed)>=40.0)
    {
      p0    =       2.36553e-01;
      p1    =      -1.83119e+00;
      p2    =       3.28143e-01;
      p3    =       2.29250e+00;
    }
  if(fabs(zed)<40.0)
    {  
      p0    =       8.27162e-01;
      p1    =      -5.04889e-01;
      p2    =       9.24650e-02;
      p3    =       5.99640e-01;
    }

  // ----- //
  // means //
  // ----- //

  bool typeA = false;
  bool typeB = false;
  bool typeC = false;
  bool typeD = false;

  bool pos = charge==1;
  bool neg = charge==-1;
  bool fieldpp = field==0;
  bool fieldmm = field==1;
  bool northouter = zed>=40.0&&zed<80.0;
  bool northinner = zed>0.0&&zed<40.0;
  bool southinner = zed>-40.0&&zed<0.0;
  bool southouter = zed>-80.0&&zed<=-40.0;  

  if(neg&&fieldpp&&southouter) typeA = true;
  if(pos&&fieldpp&&northinner) typeA = true;
  if(pos&&fieldmm&&southouter) typeA = true;
  if(neg&&fieldmm&&northinner) typeA = true;

  if(pos&&fieldpp&&southouter) typeB = true;
  if(neg&&fieldpp&&northinner) typeB = true;
  if(neg&&fieldmm&&southouter) typeB = true;
  if(pos&&fieldmm&&northinner) typeB = true;

  if(neg&&fieldpp&&northouter) typeC = true;
  if(pos&&fieldpp&&southinner) typeC = true;
  if(pos&&fieldmm&&northouter) typeC = true;
  if(neg&&fieldmm&&southinner) typeC = true;

  if(pos&&fieldpp&&northouter) typeD = true;
  if(neg&&fieldpp&&southinner) typeD = true;
  if(neg&&fieldmm&&northouter) typeD = true;
  if(pos&&fieldmm&&southinner) typeD = true;

  if(typeA)
    {
      q0    =       7.92655e-03;
      q1    =       7.09935e-04;
      q2    =      -4.97479e-04;
      q3    =       1.93510e-01;
    }
  if(typeB)
    {
      q0    =       6.56031e-01;
      q1    =       4.96598e-01;
      q2    =      -5.14296e-02;
      q3    =      -1.19513e+00;
    }
  if(typeC)
    {
      q0    =      -4.49270e-01;
      q1    =       2.68957e-01;
      q2    =      -3.63317e-02;
      q3    =       1.86793e-01;
    }
  if(typeD)
    {
      q0    =      -2.27032e-01;
      q1    =      -2.24444e-01;
      q2    =       1.38080e-02;
      q3    =       9.56444e-02;
    }

  float mean = q0 + q1/pT + q2/pT/pT + q3/sqrt(pT);
  float sigma = p0 + p1/pT + p2/pT/pT + p3/sqrt(pT);

  return (pc3sdphi-mean)/sigma;

}


float tunepc3dz
{

  float mean = -9999;
  float sigma = -9999;

  float p0 = -9999;
  float p1 = -9999;
  float p2 = -9999;
  float p3 = -9999;
  
  float q0 = -9999;
  float q1 = -9999;
  float q2 = -9999;
  float q3 = -9999;
  
  // ------ //
  // sigmas //
  // ------ //
  
  if(fabs(zed)>=40.0)
    {
      p0    =       1.10592e+00;
      p1    =       4.12057e-01;
      p2    =      -6.23527e-03;
      p3    =      -6.14927e-01;
    }
  if(fabs(zed)<40.0)
    {  
      p0    =       1.12195e+00;
      p1    =       3.86600e-01;
      p2    =      -1.86309e-03;
      p3    =      -6.06582e-01;
    }

  // ----- //
  // means //
  // ----- //
  
  if(zed>=40.0&&zed<80.0)
    {
      if(pT<1.5)
	{
	  q0    =       4.88925e-01;
	  q1    =       6.29561e-01;
	  q2    =      -4.43880e-02;
	  q3    =      -1.02325e+00;
	}
      else if(pT>=1.5)
	{
	  q0    =      -9.97348e-01;
	  q1    =      -5.46059e+00;
	  q2    =       7.61192e-01;
	  q3    =       5.30897e+00;
	}
    }

  if(zed>0.0&&zed<40.0)
    {
      q0    =       4.01829e-01;
      q1    =       4.73078e-01;
      q2    =      -3.06584e-02;
      q3    =      -7.55174e-01;
    }

  if(zed>-80&&zed<=-40)
    {
      if(pT<1.5)
	{
	  q0    =       3.16918e-01;
	  q1    =       3.30577e-02;
	  q2    =      -2.25056e-03;
	  q3    =      -2.70442e-01;
	}
      else if(pT>=1.5)
	{
	  q0    =       2.71757e-02;
	  q1    =       1.34167e+00;
	  q2    =       4.20926e-01;
	  q3    =      -1.22779e+00;
	}
    }

  if(zed>-40.0&&zed<0)
    {
      q0    =       2.56177e-02;
      q1    =      -2.29174e-01;
      q2    =       1.43592e-02;
      q3    =       2.32639e-01;
    }

  float mean = q0 + q1/pT + q2/pT/pT + q3/sqrt(pT);
  float sigma = p0 + p1/pT + p2/pT/pT + p3/sqrt(pT);

  return (pc3sdz-mean)/sigma;

}

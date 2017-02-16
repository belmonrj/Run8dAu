void physratios()
{





  for(int isec=0; isec<3; isec++)
    {
      if(isec>0) continue; // new
      for(int ipid=0; ipid<3; ipid++)
	{
	  rcp(ipid,isec);
	  //cout<<"rcp("<<ipid<<","<<isec<<");"<<endl;
	  for(int icent=0; icent<5; icent++)
	    {
	      opi(ipid,isec,icent);
	      pon(ipid,isec,icent);
	      ponfield(ipid,isec,icent);
	    }
	}
    }


}




void rcp(int ipid=0, int sector=0)
{

  const float normal = 4.709; // phenix ana note AN900

  int pid=1;
  if(ipid==0) pid=1;
  if(ipid==1) pid=3;
  if(ipid==2) pid=5;

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");

  //char centstring[10];
  //if(centid==0) sprintf(centstring,"0020");
  //if(centid==11) sprintf(centstring,"6088");

  char centstring_C[10];
  sprintf(centstring_C,"0020");

  char centstring_P[10];
  sprintf(centstring_P,"6088");






  char fnameinposcb_C[100];
  char fnameinnegcb_C[100];
  char fnameinposcb_P[100];
  char fnameinnegcb_P[100];

  char fnameout[100];

  // ---

  sprintf(fnameinposcb_C,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring_C);
  sprintf(fnameinnegcb_C,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring_C);
  ifstream finposcb_C;
  ifstream finnegcb_C;
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  float pT_poscb_C[100], yield_poscb_C[100], eyield_poscb_C[100];
  float pT_negcb_C[100], yield_negcb_C[100], eyield_negcb_C[100];
  for(int i=0; i<100; i++)
    {
      finposcb_C>>pT_poscb_C[i]>>yield_poscb_C[i]>>eyield_poscb_C[i];
      finnegcb_C>>pT_negcb_C[i]>>yield_negcb_C[i]>>eyield_negcb_C[i];
    }
  finposcb_C.close();
  finnegcb_C.close();
  // ---
  sprintf(fnameinposcb_C,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring_C);
  sprintf(fnameinnegcb_C,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring_C);
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  float pTR_poscb_C[20], yieldR_poscb_C[20], eyieldR_poscb_C[20];
  float pTR_negcb_C[20], yieldR_negcb_C[20], eyieldR_negcb_C[20];
  for(int i=0; i<20; i++)
    {
      finposcb_C>>pTR_poscb_C[i]>>yieldR_poscb_C[i]>>eyieldR_poscb_C[i];
      finnegcb_C>>pTR_negcb_C[i]>>yieldR_negcb_C[i]>>eyieldR_negcb_C[i];
    }
  finposcb_C.close();
  finnegcb_C.close();

  // ---

  sprintf(fnameinposcb_P,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring_P);
  sprintf(fnameinnegcb_P,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring_P);
  ifstream finposcb_P;
  ifstream finnegcb_P;
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  float pT_poscb_P[100], yield_poscb_P[100], eyield_poscb_P[100];
  float pT_negcb_P[100], yield_negcb_P[100], eyield_negcb_P[100];
  for(int i=0; i<100; i++)
    {
      finposcb_P>>pT_poscb_P[i]>>yield_poscb_P[i]>>eyield_poscb_P[i];
      finnegcb_P>>pT_negcb_P[i]>>yield_negcb_P[i]>>eyield_negcb_P[i];
    }
  finposcb_P.close();
  finnegcb_P.close();
  // ---
  sprintf(fnameinposcb_P,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring_P);
  sprintf(fnameinnegcb_P,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring_P);
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  float pTR_poscb_P[20], yieldR_poscb_P[20], eyieldR_poscb_P[20];
  float pTR_negcb_P[20], yieldR_negcb_P[20], eyieldR_negcb_P[20];
  for(int i=0; i<20; i++)
    {
      finposcb_P>>pTR_poscb_P[i]>>yieldR_poscb_P[i]>>eyieldR_poscb_P[i];
      finnegcb_P>>pTR_negcb_P[i]>>yieldR_negcb_P[i]>>eyieldR_negcb_P[i];
    }
  finposcb_P.close();
  finnegcb_P.close();

  // ---
  // ---
  // ---

  float pTpos[44], epTpos[44], ratiopos[44], eratiopos[44];
  float pTneg[44], epTneg[44], rationeg[44], erationeg[44];
  float pT_C[44], epT_C[44], yield_C[44], eyield_C[44];
  float pT_P[44], epT_P[44], yield_P[44], eyield_P[44];

  int j;

  for(int i=0; i<30; i++)
    {
      //i=i;
      pT_C[i] = -9;
      epT_C[i] = 0;
      yield_C[i] = -9;
      eyield_C[i] = 0;
      //i=i;
      pT_C[i] = pT_poscb_C[i];
      epT_C[i] = 0;
      yield_C[i] = yield_poscb_C[i];
      eyield_C[i] = eyield_poscb_C[i];
      pTpos[i] = pT_C[i];
      epTpos[i] = 0;
      ratiopos[i] = -9;
      eratiopos[i] = 0;

      pT_P[i] = pT_poscb_P[i];
      epT_P[i] = 0;
      yield_P[i] = yield_poscb_P[i];
      eyield_P[i] = eyield_poscb_P[i];

      // now do ratio
      if(yield_C[i]>0&&yield_P[i]>0)
	{
	  pTpos[i] = (pT_C[i]+pT_P[i])/2.0;
	  epTpos[i] = 0;
	  ratiopos[i] = yield_C[i]/yield_P[i];
	  eratiopos[i] = ratiopos[i]*sqrt((eyield_C[i]/yield_C[i])**2+(eyield_P[i]/yield_P[i])**2);
	}
      else
	{
	  pTpos[i] = pT_C[i];
	  epTpos[i] = 0;
	  ratiopos[i] = -9;
	  eratiopos[i] = 0;
	}
    }

  for(int i=0; i<6; i++)
    {
      pT_C[i+30] = pTR_poscb_C[i+6];
      epT_C[i+30] = 0;
      yield_C[i+30] = yieldR_poscb_C[i+6];
      eyield_C[i+30] = eyieldR_poscb_C[i+6];

      pT_P[i+30] = pTR_poscb_P[i+6];
      epT_P[i+30] = 0;
      yield_P[i+30] = yieldR_poscb_P[i+6];
      eyield_P[i+30] = eyieldR_poscb_P[i+6];

      // now do ratio
      if(yield_C[i+30]>0&&yield_P[i+30]>0)
	{
	  pTpos[i+30] = (pT_C[i+30]+pT_P[i+30])/2.0;
	  epTpos[i+30] = 0;
	  ratiopos[i+30] = yield_C[i+30]/yield_P[i+30];
	  eratiopos[i+30] = ratiopos[i+30]*sqrt((eyield_C[i+30]/yield_C[i+30])**2+(eyield_P[i+30]/yield_P[i+30])**2);
	}
      else
	{
	  pTpos[i+30] = pT_C[i+30];
	  epTpos[i+30] = 0;
	  ratiopos[i+30] = -9;
	  eratiopos[i+30] = 0;
	}
    }

  // now neg

  for(int i=0; i<30; i++)
    {
      //i=i;
      pT_C[i] = -9;
      epT_C[i] = 0;
      yield_C[i] = -9;
      eyield_C[i] = 0;
      //i=i;
      pT_C[i] = pT_negcb_C[i];
      epT_C[i] = 0;
      yield_C[i] = yield_negcb_C[i];
      eyield_C[i] = eyield_negcb_C[i];
      pTneg[i] = pT_C[i];
      epTneg[i] = 0;
      rationeg[i] = -9;
      erationeg[i] = 0;

      pT_P[i] = pT_negcb_P[i];
      epT_P[i] = 0;
      yield_P[i] = yield_negcb_P[i];
      eyield_P[i] = eyield_negcb_P[i];

      // now do ratio
      if(yield_C[i]>0&&yield_P[i]>0)
	{
	  pTneg[i] = (pT_C[i]+pT_P[i])/2.0;
	  epTneg[i] = 0;
	  rationeg[i] = yield_C[i]/yield_P[i];
	  erationeg[i] = rationeg[i]*sqrt((eyield_C[i]/yield_C[i])**2+(eyield_P[i]/yield_P[i])**2);
	}
      else
	{
	  pTneg[i] = pT_C[i];
	  epTneg[i] = 0;
	  rationeg[i] = -9;
	  erationeg[i] = 0;
	}
    }

  for(int i=0; i<6; i++)
    {
      pT_C[i+30] = pTR_negcb_C[i+6];
      epT_C[i+30] = 0;
      yield_C[i+30] = yieldR_negcb_C[i+6];
      eyield_C[i+30] = eyieldR_negcb_C[i+6];

      pT_P[i+30] = pT_negcb_P[i+6];
      epT_P[i+30] = 0;
      yield_P[i+30] = yieldR_negcb_P[i+6];
      eyield_P[i+30] = eyieldR_negcb_P[i+6];

      // now do ratio
      if(yield_C[i+30]>0&&yield_P[i+30]>0)
	{
	  pTneg[i+30] = (pT_C[i+30]+pT_P[i+30])/2.0;
	  epTneg[i+30] = 0;
	  rationeg[i+30] = yield_C[i+30]/yield_P[i+30];
	  erationeg[i+30] = rationeg[i+30]*sqrt((eyield_C[i+30]/yield_C[i+30])**2+(eyield_P[i+30]/yield_P[i+30])**2);
	}
      else
	{
	  pTneg[i+30] = pT_C[i+30];
	  epTneg[i+30] = 0;
	  rationeg[i+30] = -9;
	  erationeg[i+30] = 0;
	}
    }


  for(int i=0; i<44; i++)
    {
      ratiopos[i] /= normal;
      eratiopos[i] /= normal;
      rationeg[i] /= normal;
      erationeg[i] /= normal;
    }


  sprintf(fnameout,"PhysRatios/RCP_%s_%d_dis.dat",sectorstring,pid);
  ofstream fout;
  fout.open(fnameout);
  for(int i=0; i<44; i++)
    {
      fout<<pTpos[i]<<"\t"<<ratiopos[i]<<"\t"<<eratiopos[i]<<"\t"<<rationeg[i]<<"\t"<<erationeg[i]<<endl;
    }
  fout.close();



}




void opi(int ipid=0, int sector=0, int centid=0)
{

  int pid=0;
  if(ipid==0) pid=1;
  if(ipid==1) pid=3;
  if(ipid==2) pid=5;

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");

  char centstring[10];
  sprintf(centstring,"0088"); // "default"
  if(centid==0) sprintf(centstring,"0088");
  if(centid==1) sprintf(centstring,"0020");
  if(centid==2) sprintf(centstring,"2040");
  if(centid==3) sprintf(centstring,"4060");
  if(centid==4) sprintf(centstring,"6088");






  char fnameinposcb_C[100];
  char fnameinnegcb_C[100];
  char fnameinposcb_P[100];
  char fnameinnegcb_P[100];

  char fnameout[100];

  // ---

  sprintf(fnameinposcb_C,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb_C,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  ifstream finposcb_C;
  ifstream finnegcb_C;
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  float pT_poscb_C[100], yield_poscb_C[100], eyield_poscb_C[100];
  float pT_negcb_C[100], yield_negcb_C[100], eyield_negcb_C[100];
  for(int i=0; i<100; i++)
    {
      finposcb_C>>pT_poscb_C[i]>>yield_poscb_C[i]>>eyield_poscb_C[i];
      finnegcb_C>>pT_negcb_C[i]>>yield_negcb_C[i]>>eyield_negcb_C[i];
    }
  finposcb_C.close();
  finnegcb_C.close();
  // ---
  sprintf(fnameinposcb_C,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb_C,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  finposcb_C.open(fnameinposcb_C);
  finnegcb_C.open(fnameinnegcb_C);
  float pTR_poscb_C[20], yieldR_poscb_C[20], eyieldR_poscb_C[20];
  float pTR_negcb_C[20], yieldR_negcb_C[20], eyieldR_negcb_C[20];
  for(int i=0; i<20; i++)
    {
      finposcb_C>>pTR_poscb_C[i]>>yieldR_poscb_C[i]>>eyieldR_poscb_C[i];
      finnegcb_C>>pTR_negcb_C[i]>>yieldR_negcb_C[i]>>eyieldR_negcb_C[i];
    }
  finposcb_C.close();
  finnegcb_C.close();

  // ---

  // DONT FORGET ABOUT HOW STUPID THIS IS
  sprintf(fnameinposcb_P,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,1,centstring);
  sprintf(fnameinnegcb_P,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,1,centstring);
  ifstream finposcb_P;
  ifstream finnegcb_P;
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  float pT_poscb_P[100], yield_poscb_P[100], eyield_poscb_P[100];
  float pT_negcb_P[100], yield_negcb_P[100], eyield_negcb_P[100];
  for(int i=0; i<100; i++)
    {
      finposcb_P>>pT_poscb_P[i]>>yield_poscb_P[i]>>eyield_poscb_P[i];
      finnegcb_P>>pT_negcb_P[i]>>yield_negcb_P[i]>>eyield_negcb_P[i];
    }
  finposcb_P.close();
  finnegcb_P.close();
  // ---
  // DONT FORGET ABOUT HOW STUPID THIS IS
  sprintf(fnameinposcb_P,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,1,centstring);
  sprintf(fnameinnegcb_P,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,1,centstring);
  finposcb_P.open(fnameinposcb_P);
  finnegcb_P.open(fnameinnegcb_P);
  float pTR_poscb_P[20], yieldR_poscb_P[20], eyieldR_poscb_P[20];
  float pTR_negcb_P[20], yieldR_negcb_P[20], eyieldR_negcb_P[20];
  for(int i=0; i<20; i++)
    {
      finposcb_P>>pTR_poscb_P[i]>>yieldR_poscb_P[i]>>eyieldR_poscb_P[i];
      finnegcb_P>>pTR_negcb_P[i]>>yieldR_negcb_P[i]>>eyieldR_negcb_P[i];
    }
  finposcb_P.close();
  finnegcb_P.close();

  // ---
  // ---
  // ---

  float pTpos[36], epTpos[36], ratiopos[36], eratiopos[36];
  float pTneg[36], epTneg[36], rationeg[36], erationeg[36];
  float pT_C[36], epT_C[36], yield_C[36], eyield_C[36];
  float pT_P[36], epT_P[36], yield_P[36], eyield_P[36];

  int j;

  for(int i=0; i<30; i++)
    {
      //i=i;
      pT_C[i] = -9;
      epT_C[i] = 0;
      yield_C[i] = -9;
      eyield_C[i] = 0;
      //i=i;
      pT_C[i] = pT_poscb_C[i];
      epT_C[i] = 0;
      yield_C[i] = yield_poscb_C[i];
      eyield_C[i] = eyield_poscb_C[i];
      pTpos[i] = pT_C[i];
      epTpos[i] = 0;
      ratiopos[i] = -9;
      eratiopos[i] = 0;

      pT_P[i] = pT_poscb_P[i];
      epT_P[i] = 0;
      yield_P[i] = yield_poscb_P[i];
      eyield_P[i] = eyield_poscb_P[i];

      // now do ratio
      if(yield_C[i]>0&&yield_P[i]>0)
	{
	  pTpos[i] = (pT_C[i]+pT_P[i])/2.0;
	  epTpos[i] = 0;
	  ratiopos[i] = yield_C[i]/yield_P[i];
	  eratiopos[i] = ratiopos[i]*sqrt((eyield_C[i]/yield_C[i])**2+(eyield_P[i]/yield_P[i])**2);
	}
      else
	{
	  pTpos[i] = pT_C[i];
	  epTpos[i] = 0;
	  ratiopos[i] = -9;
	  eratiopos[i] = 0;
	}
    }

  for(int i=0; i<6; i++)
    {
      pT_C[i+30] = pTR_poscb_C[i+6];
      epT_C[i+30] = 0;
      yield_C[i+30] = yieldR_poscb_C[i+6];
      eyield_C[i+30] = eyieldR_poscb_C[i+6];

      pT_P[i+30] = pTR_poscb_P[i+6];
      epT_P[i+30] = 0;
      yield_P[i+30] = yieldR_poscb_P[i+6];
      eyield_P[i+30] = eyieldR_poscb_P[i+6];

      // now do ratio
      if(yield_C[i+30]>0&&yield_P[i+30]>0)
	{
	  pTpos[i+30] = (pT_C[i+30]+pT_P[i+30])/2.0;
	  epTpos[i+30] = 0;
	  ratiopos[i+30] = yield_C[i+30]/yield_P[i+30];
	  eratiopos[i+30] = ratiopos[i+30]*sqrt((eyield_C[i+30]/yield_C[i+30])**2+(eyield_P[i+30]/yield_P[i+30])**2);
	}
      else
	{
	  pTpos[i+30] = pT_C[i+30];
	  epTpos[i+30] = 0;
	  ratiopos[i+30] = -9;
	  eratiopos[i+30] = 0;
	}
    }

  // now neg

  for(int i=0; i<30; i++)
    {
      //i=i;
      pT_C[i] = -9;
      epT_C[i] = 0;
      yield_C[i] = -9;
      eyield_C[i] = 0;
      //i=i;
      pT_C[i] = pT_negcb_C[i];
      epT_C[i] = 0;
      yield_C[i] = yield_negcb_C[i];
      eyield_C[i] = eyield_negcb_C[i];
      pTneg[i] = pT_C[i];
      epTneg[i] = 0;
      rationeg[i] = -9;
      erationeg[i] = 0;

      pT_P[i] = pT_negcb_P[i];
      epT_P[i] = 0;
      yield_P[i] = yield_negcb_P[i];
      eyield_P[i] = eyield_negcb_P[i];

      // now do ratio
      if(yield_C[i]>0&&yield_P[i]>0)
	{
	  pTneg[i] = (pT_C[i]+pT_P[i])/2.0;
	  epTneg[i] = 0;
	  rationeg[i] = yield_C[i]/yield_P[i];
	  erationeg[i] = rationeg[i]*sqrt((eyield_C[i]/yield_C[i])**2+(eyield_P[i]/yield_P[i])**2);
	}
      else
	{
	  pTneg[i] = pT_C[i];
	  epTneg[i] = 0;
	  rationeg[i] = -9;
	  erationeg[i] = 0;
	}
    }

  for(int i=0; i<4; i++)
    {
      pT_C[i+30] = pTR_negcb_C[i+6];
      epT_C[i+30] = 0;
      yield_C[i+30] = yieldR_negcb_C[i+6];
      eyield_C[i+30] = eyieldR_negcb_C[i+6];

      pT_P[i+30] = pT_negcb_P[i+6];
      epT_P[i+30] = 0;
      yield_P[i+30] = yieldR_negcb_P[i+6];
      eyield_P[i+30] = eyieldR_negcb_P[i+6];

      // now do ratio
      if(yield_C[i+30]>0&&yield_P[i+30]>0)
	{
	  pTneg[i+30] = (pT_C[i+30]+pT_P[i+30])/2.0;
	  epTneg[i+30] = 0;
	  rationeg[i+30] = yield_C[i+30]/yield_P[i+30];
	  erationeg[i+30] = rationeg[i+30]*sqrt((eyield_C[i+30]/yield_C[i+30])**2+(eyield_P[i+30]/yield_P[i+30])**2);
	}
      else
	{
	  pTneg[i+30] = pT_C[i+30];
	  epTneg[i+30] = 0;
	  rationeg[i+30] = -9;
	  erationeg[i+30] = 0;
	}
    }




  sprintf(fnameout,"PhysRatios/opi_%s_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  ofstream fout;
  fout.open(fnameout);
  for(int i=0; i<36; i++)
    {
      fout<<pTpos[i]<<"\t"<<ratiopos[i]<<"\t"<<eratiopos[i]<<"\t"<<rationeg[i]<<"\t"<<erationeg[i]<<endl;
    }
  fout.close();



}




void pon(int ipid=0, int sector=0, int centid=0)
{

  int pid=0;
  if(ipid==0) pid=1;
  if(ipid==1) pid=3;
  if(ipid==2) pid=5;

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");

  char centstring[10];
  sprintf(centstring,"0088"); // "default"
  if(centid==0) sprintf(centstring,"0088");
  if(centid==1) sprintf(centstring,"0020");
  if(centid==2) sprintf(centstring,"2040");
  if(centid==3) sprintf(centstring,"4060");
  if(centid==4) sprintf(centstring,"6088");






  char fnameinposcb[100];
  char fnameinnegcb[100];

  char fnameout[100];

  // ---

  sprintf(fnameinposcb,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  ifstream finposcb;
  ifstream finnegcb;
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);
  float pT_poscb[100], yield_poscb[100], eyield_poscb[100];
  float pT_negcb[100], yield_negcb[100], eyield_negcb[100];
  for(int i=0; i<100; i++)
    {
      finposcb>>pT_poscb[i]>>yield_poscb[i]>>eyield_poscb[i];
      finnegcb>>pT_negcb[i]>>yield_negcb[i]>>eyield_negcb[i];
    }
  finposcb.close();
  finnegcb.close();
  // ---
  sprintf(fnameinposcb,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);
  float pTR_poscb[20], yieldR_poscb[20], eyieldR_poscb[20];
  float pTR_negcb[20], yieldR_negcb[20], eyieldR_negcb[20];
  for(int i=0; i<20; i++)
    {
      finposcb>>pTR_poscb[i]>>yieldR_poscb[i]>>eyieldR_poscb[i];
      finnegcb>>pTR_negcb[i]>>yieldR_negcb[i]>>eyieldR_negcb[i];
    }
  finposcb.close();
  finnegcb.close();

  // ---


  // ---
  // ---
  // ---

  float pTpos[36], epTpos[36], ratiopos[36], eratiopos[36];
  float pTneg[36], epTneg[36], rationeg[36], erationeg[36];
  float pT[36], epT[36], ratio[36], eratio[36];


  int j;

  for(int i=0; i<36; i++)
    {
      if(i<30)
	{
	  pT[i]=pT_poscb[i];
	  epT[i]=0;
	  ratio[i]=-9;
	  eratio[i]=0;
	  if(yield_poscb[i]>0&&yield_negcb[i]>0)
	    {
	      ratio[i]=yield_negcb[i]/yield_poscb[i];
	      eratio[i]=ratio[i]*sqrt((eyield_poscb[i]/yield_poscb[i])**2+(eyield_negcb[i]/yield_negcb[i])**2);
	    }
	}
      if(i>=30)
	{
	  pT[i]=pTR_poscb[i-24];
	  epT[i]=0;
	  ratio[i]=-9;
	  eratio[i]=0;
	  if(yieldR_poscb[i-24]>0&&yieldR_negcb[i-24]>0)
	    {
	      ratio[i]=yieldR_negcb[i-24]/yieldR_poscb[i-24];
	      eratio[i]=ratio[i]*sqrt((eyieldR_poscb[i-24]/yieldR_poscb[i-24])**2+(eyieldR_negcb[i-24]/yieldR_negcb[i-24])**2);
	    }
	}

    }



  sprintf(fnameout,"PhysRatios/pon_%s_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  ofstream fout;
  fout.open(fnameout);
  for(int i=0; i<36; i++)
    {
      fout<<pT[i]<<"\t"<<ratio[i]<<"\t"<<eratio[i]<<endl;
    }
  fout.close();



}




void ponfield(int ipid=0, int sector=0, int centid=0)
{

  int pid=0;
  if(ipid==0) pid=1;
  if(ipid==1) pid=3;
  if(ipid==2) pid=5;

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");

  char centstring[10];
  sprintf(centstring,"0088"); // "default"
  if(centid==0) sprintf(centstring,"0088");
  if(centid==1) sprintf(centstring,"0020");
  if(centid==2) sprintf(centstring,"2040");
  if(centid==3) sprintf(centstring,"4060");
  if(centid==4) sprintf(centstring,"6088");






  char fnameinposcb[100];
  char fnameinnegcb[100];

  char fnameout[100];

  // ---

  sprintf(fnameinposcb,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  ifstream finposcb;
  ifstream finnegcb;
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);
  float pT_poscb[100], yield_poscb[100], eyield_poscb[100];
  float pT_negcb[100], yield_negcb[100], eyield_negcb[100];
  for(int i=0; i<100; i++)
    {
      finposcb>>pT_poscb[i]>>yield_poscb[i]>>eyield_poscb[i];
      finnegcb>>pT_negcb[i]>>yield_negcb[i]>>eyield_negcb[i];
    }
  finposcb.close();
  finnegcb.close();
  // ---
  sprintf(fnameinposcb,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);
  float pTR_poscb[20], yieldR_poscb[20], eyieldR_poscb[20];
  float pTR_negcb[20], yieldR_negcb[20], eyieldR_negcb[20];
  for(int i=0; i<20; i++)
    {
      finposcb>>pTR_poscb[i]>>yieldR_poscb[i]>>eyieldR_poscb[i];
      finnegcb>>pTR_negcb[i]>>yieldR_negcb[i]>>eyieldR_negcb[i];
    }
  finposcb.close();
  finnegcb.close();

  // ---


  // ---
  // ---
  // ---

  float pTpos[36], epTpos[36], ratiopos[36], eratiopos[36];
  float pTneg[36], epTneg[36], rationeg[36], erationeg[36];
  float pT[36], epT[36], ratio[36], eratio[36];


  int j;

  for(int i=0; i<36; i++)
    {
      if(i<30)
	{
	  pT[i]=pT_poscb[i];
	  epT[i]=0;
	  ratio[i]=-9;
	  eratio[i]=0;
	  if(yield_poscb[i]>0&&yield_negcb[i]>0)
	    {
	      ratio[i]=yield_negcb[i]/yield_poscb[i];
	      eratio[i]=ratio[i]*sqrt((eyield_poscb[i]/yield_poscb[i])**2+(eyield_negcb[i]/yield_negcb[i])**2);
	    }
	}
      if(i>=30)
	{
	  pT[i]=pTR_poscb[i-24];
	  epT[i]=0;
	  ratio[i]=-9;
	  eratio[i]=0;
	  if(yieldR_poscb[i-24]>0&&yieldR_negcb[i-24]>0)
	    {
	      ratio[i]=yieldR_negcb[i-24]/yieldR_poscb[i-24];
	      eratio[i]=ratio[i]*sqrt((eyieldR_poscb[i-24]/yieldR_poscb[i-24])**2+(eyieldR_negcb[i-24]/yieldR_negcb[i-24])**2);
	    }
	}

    }



  sprintf(fnameout,"PhysRatios/ponfield_%s_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  ofstream fout;
  fout.open(fnameout);
  for(int i=0; i<36; i++)
    {
      fout<<pT[i]<<"\t"<<ratio[i]<<"\t"<<eratio[i]<<endl;
    }
  fout.close();



}

void feed()
{

  cout<<"hello!  now doing feeddown correction!"<<endl;

  for(int icent=0; icent<5; icent++)
    {
      for(int ipid=0; ipid<6; ipid++)
  	{
  	  for(int isec=0; isec<3; isec++)
  	    {
  	      doit(isec,ipid,icent);
  	      //cout<<"doit("<<isec<<","<<ipid<<","<<icent<<");"<<endl;
  	    }
  	}
    }



  cout<<"done!  have a nice day!"<<endl;

}

void doit(int sector=0, int pid=0, int centid=0)
{

  // --- beginning of code




  // --- strings for filenames

  char sectorstring[10];
  sprintf(sectorstring,"tofw"); // "default"
  if(sector==0) sprintf(sectorstring,"tofw");
  if(sector==1) sprintf(sectorstring,"tofw_w1");
  if(sector==2) sprintf(sectorstring,"tofw_w2");

  char centstring[10];
  sprintf(centstring,"0088"); // "default"
  if(centid==0) sprintf(centstring,"0020");
  if(centid==1) sprintf(centstring,"2040");
  if(centid==2) sprintf(centstring,"4060");
  if(centid==3) sprintf(centstring,"6088");
  if(centid==4) sprintf(centstring,"0088");






  // --- input data

  char fnameinpospp[100];
  char fnameinnegpp[100];
  char fnameinposmm[100];
  char fnameinnegmm[100];
  char fnameinposcb[100];
  char fnameinnegcb[100];

  sprintf(fnameinpospp,"Data/ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegpp,"Data/ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinposmm,"Data/ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegmm,"Data/ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinposcb,"Data/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  ifstream finpospp;
  ifstream finnegpp;
  ifstream finposmm;
  ifstream finnegmm;
  ifstream finposcb;
  ifstream finnegcb;

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pT_pospp[100], yield_pospp[100], eyield_pospp[100];
  float pT_negpp[100], yield_negpp[100], eyield_negpp[100];
  float pT_posmm[100], yield_posmm[100], eyield_posmm[100];
  float pT_negmm[100], yield_negmm[100], eyield_negmm[100];
  float pT_poscb[100], yield_poscb[100], eyield_poscb[100];
  float pT_negcb[100], yield_negcb[100], eyield_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pT_pospp[i]>>yield_pospp[i]>>eyield_pospp[i];
      // negpp
      finnegpp>>pT_negpp[i]>>yield_negpp[i]>>eyield_negpp[i];
      // posmm
      finposmm>>pT_posmm[i]>>yield_posmm[i]>>eyield_posmm[i];
      // negmm
      finnegmm>>pT_negmm[i]>>yield_negmm[i]>>eyield_negmm[i];
      // poscb
      finposcb>>pT_poscb[i]>>yield_poscb[i]>>eyield_poscb[i];
      // negcb
      finnegcb>>pT_negcb[i]>>yield_negcb[i]>>eyield_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();


  // --- now input the rebinned data

  sprintf(fnameinpospp,"Data/R2_ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegpp,"Data/R2_ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinposmm,"Data/R2_ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegmm,"Data/R2_ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinposcb,"Data/R2_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/R2_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pTR2_pospp[100], yieldR2_pospp[100], eyieldR2_pospp[100];
  float pTR2_negpp[100], yieldR2_negpp[100], eyieldR2_negpp[100];
  float pTR2_posmm[100], yieldR2_posmm[100], eyieldR2_posmm[100];
  float pTR2_negmm[100], yieldR2_negmm[100], eyieldR2_negmm[100];
  float pTR2_poscb[100], yieldR2_poscb[100], eyieldR2_poscb[100];
  float pTR2_negcb[100], yieldR2_negcb[100], eyieldR2_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pTR2_pospp[i]>>yieldR2_pospp[i]>>eyieldR2_pospp[i];
      // negpp
      finnegpp>>pTR2_negpp[i]>>yieldR2_negpp[i]>>eyieldR2_negpp[i];
      // posmm
      finposmm>>pTR2_posmm[i]>>yieldR2_posmm[i]>>eyieldR2_posmm[i];
      // negmm
      finnegmm>>pTR2_negmm[i]>>yieldR2_negmm[i]>>eyieldR2_negmm[i];
      // poscb
      finposcb>>pTR2_poscb[i]>>yieldR2_poscb[i]>>eyieldR2_poscb[i];
      // negcb
      finnegcb>>pTR2_negcb[i]>>yieldR2_negcb[i]>>eyieldR2_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();






  // --- now input the rebinned data

  sprintf(fnameinpospp,"Data/R5_ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegpp,"Data/R5_ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameinposmm,"Data/R5_ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegmm,"Data/R5_ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameinposcb,"Data/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameinnegcb,"Data/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  finpospp.open(fnameinpospp);
  finnegpp.open(fnameinnegpp);
  finposmm.open(fnameinposmm);
  finnegmm.open(fnameinnegmm);
  finposcb.open(fnameinposcb);
  finnegcb.open(fnameinnegcb);

  float pTR5_pospp[100], yieldR5_pospp[100], eyieldR5_pospp[100];
  float pTR5_negpp[100], yieldR5_negpp[100], eyieldR5_negpp[100];
  float pTR5_posmm[100], yieldR5_posmm[100], eyieldR5_posmm[100];
  float pTR5_negmm[100], yieldR5_negmm[100], eyieldR5_negmm[100];
  float pTR5_poscb[100], yieldR5_poscb[100], eyieldR5_poscb[100];
  float pTR5_negcb[100], yieldR5_negcb[100], eyieldR5_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      finpospp>>pTR5_pospp[i]>>yieldR5_pospp[i]>>eyieldR5_pospp[i];
      // negpp
      finnegpp>>pTR5_negpp[i]>>yieldR5_negpp[i]>>eyieldR5_negpp[i];
      // posmm
      finposmm>>pTR5_posmm[i]>>yieldR5_posmm[i]>>eyieldR5_posmm[i];
      // negmm
      finnegmm>>pTR5_negmm[i]>>yieldR5_negmm[i]>>eyieldR5_negmm[i];
      // poscb
      finposcb>>pTR5_poscb[i]>>yieldR5_poscb[i]>>eyieldR5_poscb[i];
      // negcb
      finnegcb>>pTR5_negcb[i]>>yieldR5_negcb[i]>>eyieldR5_negcb[i];
    }

  finpospp.close();
  finnegpp.close();
  finposmm.close();
  finnegmm.close();
  finposcb.close();
  finnegcb.close();


  // ---

  // --- now do feeddown correction --- //

  //TF1 *funfeedpr = new TF1("funfeedpr","pol0",0.01,10.0);
  //TF1 *funfeedpb = new TF1("funfeedpb","pol0",0.01,10.0);

  //funfeedpr->SetParameter(0,0.0);
  //funfeedpr->SetParameter(0,0.0);

  // TF1 *funfeedpr = new TF1("funfeedpr","sqrt(([0]/x)**2+[1]**2)-[2]*x-[3]*x*x",0.01,10.0);
  // TF1 *funfeedpb = new TF1("funfeedpb","sqrt(([0]/x)**2+[1]**2)-[2]*x-[3]*x*x",0.01,10.0);
  
  // funfeedpr->SetParameter(0,-0.1515);
  // funfeedpr->SetParameter(1,0.3674);
  // funfeedpr->SetParameter(2,0.05166);
  // funfeedpr->SetParameter(3,-0.008488);

  // funfeedpb->SetParameter(0,-0.2064);
  // funfeedpb->SetParameter(1,0.3848);
  // funfeedpb->SetParameter(2,0.03909);
  // funfeedpb->SetParameter(3,-0.005475);

  TF1 *funfeedpr = new TF1("funfeedpr","expo(0)+pol0(2)",0.01,10.0);
  TF1 *funfeedpb = new TF1("funfeedpb","expo(0)+pol0(2)",0.01,10.0);

  //funfeedpr->SetParameter(0,-0.10);//-0.32
  //funfeedpr->SetParameter(1,-1.40);//-1.35
  //funfeedpr->SetParameter(2,0.13);//0.11
  // green
  funfeedpr->SetParameter(0,-0.32);//-0.32
  funfeedpr->SetParameter(1,-1.35);//-1.35
  funfeedpr->SetParameter(2,0.11);//0.11

  // green
  // funfeedpb->SetParameter(0,-0.10);//d
  // funfeedpb->SetParameter(1,-1.40);//d
  // funfeedpb->SetParameter(2,0.13);//d
  // blue
  funfeedpb->SetParameter(0,-0.10);//d
  funfeedpb->SetParameter(1,-1.65);//d
  funfeedpb->SetParameter(2,0.13);//d



  /* holy fucking shit
  if(pid==4||pid==5)
    {
      for(int i=0; i<100; i++)
	{
	  //pospp
	  yield_pospp[i] *= 1.0 - funfeedpr->Eval(pT_pospp[i]);
	  eyield_pospp[i] *= 1.0 - funfeedpr->Eval(pT_pospp[i]);
	  //negpp
	  yield_negpp[i] *= 1.0 - funfeedpb->Eval(pT_negpp[i]);
	  eyield_negpp[i] *= 1.0 - funfeedpb->Eval(pT_negpp[i]);
	  //posmm
	  yield_posmm[i] *= 1.0 - funfeedpr->Eval(pT_posmm[i]);
	  eyield_posmm[i] *= 1.0 - funfeedpr->Eval(pT_posmm[i]);
	  //negmm
	  yield_negmm[i] *= 1.0 - funfeedpb->Eval(pT_negmm[i]);
	  eyield_negmm[i] *= 1.0 - funfeedpb->Eval(pT_negmm[i]);
	  //poscb
	  yield_poscb[i] *= 1.0 - funfeedpr->Eval(pT_poscb[i]);
	  eyield_poscb[i] *= 1.0 - funfeedpr->Eval(pT_poscb[i]);
	  //negcb
	  yield_negcb[i] *= 1.0 - funfeedpb->Eval(pT_negcb[i]);
	  eyield_negcb[i] *= 1.0 - funfeedpb->Eval(pT_negcb[i]);
	  // ---------------- //
	  // --- rebinned --- //
	  // ---------------- //
	  //pospp
	  yieldR_pospp[i] *= 1.0 - funfeedpr->Eval(pTR_pospp[i]);
	  eyieldR_pospp[i] *= 1.0 - funfeedpr->Eval(pTR_pospp[i]);
	  //negpp
	  yieldR_negpp[i] *= 1.0 - funfeedpb->Eval(pTR_negpp[i]);
	  eyieldR_negpp[i] *= 1.0 - funfeedpb->Eval(pTR_negpp[i]);
	  //posmm
	  yieldR_posmm[i] *= 1.0 - funfeedpr->Eval(pTR_posmm[i]);
	  eyieldR_posmm[i] *= 1.0 - funfeedpr->Eval(pTR_posmm[i]);
	  //negmm
	  yieldR_negmm[i] *= 1.0 - funfeedpb->Eval(pTR_negmm[i]);
	  eyieldR_negmm[i] *= 1.0 - funfeedpb->Eval(pTR_negmm[i]);
	  //poscb
	  yieldR_poscb[i] *= 1.0 - funfeedpr->Eval(pTR_poscb[i]);
	  eyieldR_poscb[i] *= 1.0 - funfeedpr->Eval(pTR_poscb[i]);
	  //negcb
	  yieldR_negcb[i] *= 1.0 - funfeedpb->Eval(pTR_negcb[i]);
	  eyieldR_negcb[i] *= 1.0 - funfeedpb->Eval(pTR_negcb[i]);
	}
    }
  */ // matches holy fucking shit



  float pbarK = 1.14;
  if(pid==4||pid==5)
    {
      for(int i=0; i<100; i++)
	{
	  //pospp
	  yield_pospp[i] *= 1.0 - funfeedpr->Eval(pT_pospp[i]);
	  eyield_pospp[i] *= 1.0 - funfeedpr->Eval(pT_pospp[i]);
	  //negpp
	  yield_negpp[i] *= 1.0 - pbarK*funfeedpr->Eval(pT_negpp[i]);
	  eyield_negpp[i] *= 1.0 - pbarK*funfeedpr->Eval(pT_negpp[i]);
	  //posmm
	  yield_posmm[i] *= 1.0 - funfeedpr->Eval(pT_posmm[i]);
	  eyield_posmm[i] *= 1.0 - funfeedpr->Eval(pT_posmm[i]);
	  //negmm
	  yield_negmm[i] *= 1.0 - pbarK*funfeedpr->Eval(pT_negmm[i]);
	  eyield_negmm[i] *= 1.0 - pbarK*funfeedpr->Eval(pT_negmm[i]);
	  //poscb
	  yield_poscb[i] *= 1.0 - funfeedpr->Eval(pT_poscb[i]);
	  eyield_poscb[i] *= 1.0 - funfeedpr->Eval(pT_poscb[i]);
	  //negcb
	  yield_negcb[i] *= 1.0 - pbarK*funfeedpr->Eval(pT_negcb[i]);
	  eyield_negcb[i] *= 1.0 - pbarK*funfeedpr->Eval(pT_negcb[i]);
	  // ---------------- //
	  // --- rebinned --- //
	  // ---------------- //
	  //pospp
	  yieldR2_pospp[i] *= 1.0 - funfeedpr->Eval(pTR2_pospp[i]);
	  eyieldR2_pospp[i] *= 1.0 - funfeedpr->Eval(pTR2_pospp[i]);
	  //negpp
	  yieldR2_negpp[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR2_negpp[i]);
	  eyieldR2_negpp[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR2_negpp[i]);
	  //posmm
	  yieldR2_posmm[i] *= 1.0 - funfeedpr->Eval(pTR2_posmm[i]);
	  eyieldR2_posmm[i] *= 1.0 - funfeedpr->Eval(pTR2_posmm[i]);
	  //negmm
	  yieldR2_negmm[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR2_negmm[i]);
	  eyieldR2_negmm[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR2_negmm[i]);
	  //poscb
	  yieldR2_poscb[i] *= 1.0 - funfeedpr->Eval(pTR2_poscb[i]);
	  eyieldR2_poscb[i] *= 1.0 - funfeedpr->Eval(pTR2_poscb[i]);
	  //negcb
	  yieldR2_negcb[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR2_negcb[i]);
	  eyieldR2_negcb[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR2_negcb[i]);
	  // ---------------- //
	  // --- rebinned --- //
	  // ---------------- //
	  //pospp
	  yieldR5_pospp[i] *= 1.0 - funfeedpr->Eval(pTR5_pospp[i]);
	  eyieldR5_pospp[i] *= 1.0 - funfeedpr->Eval(pTR5_pospp[i]);
	  //negpp
	  yieldR5_negpp[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR5_negpp[i]);
	  eyieldR5_negpp[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR5_negpp[i]);
	  //posmm
	  yieldR5_posmm[i] *= 1.0 - funfeedpr->Eval(pTR5_posmm[i]);
	  eyieldR5_posmm[i] *= 1.0 - funfeedpr->Eval(pTR5_posmm[i]);
	  //negmm
	  yieldR5_negmm[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR5_negmm[i]);
	  eyieldR5_negmm[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR5_negmm[i]);
	  //poscb
	  yieldR5_poscb[i] *= 1.0 - funfeedpr->Eval(pTR5_poscb[i]);
	  eyieldR5_poscb[i] *= 1.0 - funfeedpr->Eval(pTR5_poscb[i]);
	  //negcb
	  yieldR5_negcb[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR5_negcb[i]);
	  eyieldR5_negcb[i] *= 1.0 - pbarK*funfeedpr->Eval(pTR5_negcb[i]);
	}
    }





  // --- output data

  char fnameoutpospp[100];
  char fnameoutnegpp[100];
  char fnameoutposmm[100];
  char fnameoutnegmm[100];
  char fnameoutposcb[100];
  char fnameoutnegcb[100];

  sprintf(fnameoutpospp,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegpp,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameoutposmm,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegmm,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameoutposcb,"Data/FinalFeed/ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegcb,"Data/FinalFeed/ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  ofstream foutpospp;
  ofstream foutnegpp;
  ofstream foutposmm;
  ofstream foutnegmm;
  ofstream foutposcb;
  ofstream foutnegcb;

  foutpospp.open(fnameoutpospp);
  foutnegpp.open(fnameoutnegpp);
  foutposmm.open(fnameoutposmm);
  foutnegmm.open(fnameoutnegmm);
  foutposcb.open(fnameoutposcb);
  foutnegcb.open(fnameoutnegcb);

  float pT_pospp[100], yield_pospp[100], eyield_pospp[100];
  float pT_negpp[100], yield_negpp[100], eyield_negpp[100];
  float pT_posmm[100], yield_posmm[100], eyield_posmm[100];
  float pT_negmm[100], yield_negmm[100], eyield_negmm[100];
  float pT_poscb[100], yield_poscb[100], eyield_poscb[100];
  float pT_negcb[100], yield_negcb[100], eyield_negcb[100];

  for(int i=0; i<100; i++)
    {
      // pospp
      foutpospp<<pT_pospp[i]<<"\t"<<yield_pospp[i]<<"\t"<<eyield_pospp[i]<<endl;
      // negpp
      foutnegpp<<pT_negpp[i]<<"\t"<<yield_negpp[i]<<"\t"<<eyield_negpp[i]<<endl;
      // posmm
      foutposmm<<pT_posmm[i]<<"\t"<<yield_posmm[i]<<"\t"<<eyield_posmm[i]<<endl;
      // negmm
      foutnegmm<<pT_negmm[i]<<"\t"<<yield_negmm[i]<<"\t"<<eyield_negmm[i]<<endl;
      // poscb
      foutposcb<<pT_poscb[i]<<"\t"<<yield_poscb[i]<<"\t"<<eyield_poscb[i]<<endl;
      // negcb
      foutnegcb<<pT_negcb[i]<<"\t"<<yield_negcb[i]<<"\t"<<eyield_negcb[i]<<endl;
    }

  foutpospp.close();
  foutnegpp.close();
  foutposmm.close();
  foutnegmm.close();
  foutposcb.close();
  foutnegcb.close();



  // come back here
  // --- now output the rebinned data

  sprintf(fnameoutpospp,"Data/FinalFeed/R2_ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegpp,"Data/FinalFeed/R2_ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameoutposmm,"Data/FinalFeed/R2_ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegmm,"Data/FinalFeed/R2_ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameoutposcb,"Data/FinalFeed/R2_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegcb,"Data/FinalFeed/R2_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  foutpospp.open(fnameoutpospp);
  foutnegpp.open(fnameoutnegpp);
  foutposmm.open(fnameoutposmm);
  foutnegmm.open(fnameoutnegmm);
  foutposcb.open(fnameoutposcb);
  foutnegcb.open(fnameoutnegcb);

  float pTR2_pospp[100], yieldR2_pospp[100], eyieldR2_pospp[100];
  float pTR2_negpp[100], yieldR2_negpp[100], eyieldR2_negpp[100];
  float pTR2_posmm[100], yieldR2_posmm[100], eyieldR2_posmm[100];
  float pTR2_negmm[100], yieldR2_negmm[100], eyieldR2_negmm[100];
  float pTR2_poscb[100], yieldR2_poscb[100], eyieldR2_poscb[100];
  float pTR2_negcb[100], yieldR2_negcb[100], eyieldR2_negcb[100];

  //for(int i=0; i<100; i++)
  for(int i=0; i<50; i++)
    {
      // pospp
      foutpospp<<pTR2_pospp[i]<<"\t"<<yieldR2_pospp[i]<<"\t"<<eyieldR2_pospp[i]<<endl;
      // negpp
      foutnegpp<<pTR2_negpp[i]<<"\t"<<yieldR2_negpp[i]<<"\t"<<eyieldR2_negpp[i]<<endl;
      // posmm
      foutposmm<<pTR2_posmm[i]<<"\t"<<yieldR2_posmm[i]<<"\t"<<eyieldR2_posmm[i]<<endl;
      // negmm
      foutnegmm<<pTR2_negmm[i]<<"\t"<<yieldR2_negmm[i]<<"\t"<<eyieldR2_negmm[i]<<endl;
      // poscb
      foutposcb<<pTR2_poscb[i]<<"\t"<<yieldR2_poscb[i]<<"\t"<<eyieldR2_poscb[i]<<endl;
      // negcb
      foutnegcb<<pTR2_negcb[i]<<"\t"<<yieldR2_negcb[i]<<"\t"<<eyieldR2_negcb[i]<<endl;
    }

  foutpospp.close();
  foutnegpp.close();
  foutposmm.close();
  foutnegmm.close();
  foutposcb.close();
  foutnegcb.close();














  // --- now output the rebinned data

  sprintf(fnameoutpospp,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegpp,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s_pp.dat",sectorstring,pid,centstring);
  sprintf(fnameoutposmm,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegmm,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s_mm.dat",sectorstring,pid,centstring);
  sprintf(fnameoutposcb,"Data/FinalFeed/R5_ptpid_%s_pos_%d_dis_cent%s.dat",sectorstring,pid,centstring);
  sprintf(fnameoutnegcb,"Data/FinalFeed/R5_ptpid_%s_neg_%d_dis_cent%s.dat",sectorstring,pid,centstring);

  foutpospp.open(fnameoutpospp);
  foutnegpp.open(fnameoutnegpp);
  foutposmm.open(fnameoutposmm);
  foutnegmm.open(fnameoutnegmm);
  foutposcb.open(fnameoutposcb);
  foutnegcb.open(fnameoutnegcb);

  float pTR5_pospp[100], yieldR5_pospp[100], eyieldR5_pospp[100];
  float pTR5_negpp[100], yieldR5_negpp[100], eyieldR5_negpp[100];
  float pTR5_posmm[100], yieldR5_posmm[100], eyieldR5_posmm[100];
  float pTR5_negmm[100], yieldR5_negmm[100], eyieldR5_negmm[100];
  float pTR5_poscb[100], yieldR5_poscb[100], eyieldR5_poscb[100];
  float pTR5_negcb[100], yieldR5_negcb[100], eyieldR5_negcb[100];

  //for(int i=0; i<100; i++)
  for(int i=0; i<20; i++)
    {
      // pospp
      foutpospp<<pTR5_pospp[i]<<"\t"<<yieldR5_pospp[i]<<"\t"<<eyieldR5_pospp[i]<<endl;
      // negpp
      foutnegpp<<pTR5_negpp[i]<<"\t"<<yieldR5_negpp[i]<<"\t"<<eyieldR5_negpp[i]<<endl;
      // posmm
      foutposmm<<pTR5_posmm[i]<<"\t"<<yieldR5_posmm[i]<<"\t"<<eyieldR5_posmm[i]<<endl;
      // negmm
      foutnegmm<<pTR5_negmm[i]<<"\t"<<yieldR5_negmm[i]<<"\t"<<eyieldR5_negmm[i]<<endl;
      // poscb
      foutposcb<<pTR5_poscb[i]<<"\t"<<yieldR5_poscb[i]<<"\t"<<eyieldR5_poscb[i]<<endl;
      // negcb
      foutnegcb<<pTR5_negcb[i]<<"\t"<<yieldR5_negcb[i]<<"\t"<<eyieldR5_negcb[i]<<endl;
    }

  foutpospp.close();
  foutnegpp.close();
  foutposmm.close();
  foutnegmm.close();
  foutposcb.close();
  foutnegcb.close();










}

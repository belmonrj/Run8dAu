void feed()
{

  cout<<"hello!  now doing feeddown correction!"<<endl;


  doit();


  cout<<"done!  have a nice day!"<<endl;

}

void doit()
{

  // --- beginning of code

  //ppg030/negproton_0020.dat
  //ppg030/negproton_0088.dat
  //ppg030/negproton_2040.dat
  //ppg030/negproton_4060.dat
  //ppg030/negproton_6088.dat
  //ppg030/posproton_0020.dat
  //ppg030/posproton_0088.dat
  //ppg030/posproton_2040.dat
  //ppg030/posproton_4060.dat
  //ppg030/posproton_6088.dat



  // --- strings for filenames


  // ---

  // --- now do feeddown correction --- //

  TF1 *funfeedpr = new TF1("funfeedpr","sqrt(([0]/x)**2+[1]**2)-[2]*x-[3]*x*x",0.01,10.0);
  TF1 *funfeedpb = new TF1("funfeedpb","sqrt(([0]/x)**2+[1]**2)-[2]*x-[3]*x*x",0.01,10.0);

  funfeedpr->SetParameter(0,-0.1515);
  funfeedpr->SetParameter(1,0.3674);
  funfeedpr->SetParameter(2,0.05166);
  funfeedpr->SetParameter(3,-0.008488);

  funfeedpb->SetParameter(0,-0.2064);
  funfeedpb->SetParameter(1,0.3848);
  funfeedpb->SetParameter(2,0.03909);
  funfeedpb->SetParameter(3,-0.005475);








}

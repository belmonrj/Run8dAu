float caltofwsdphi(int run, int striptofw, int charge, float zed, float mom, float tofwdphi)
{

  float mean = -9999;
  float sigma = -9999;
  float value = -9999;

  if(run>250484&&striptofw<256&&charge==-1&&(zed>-15&&zed<0))
    {
      mean = 0.00109229 + 0.00187656/mom + -0.000442779/mom/mom + -0.00237213/sqrt(mom);
      sigma = 0.00388891 + 0.00625168/mom + -0.000797702/mom/mom + -0.0072504/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>-15&&zed<0))
    {
      mean = 0.00470421 + 0.00701884/mom + -0.000839072/mom/mom + -0.011049/sqrt(mom);
      sigma = 0.00159156 + -0.000892318/mom + 0.000528177/mom/mom + 0.00101575/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>-30&&zed<=-15))
    {
      mean = 0.001277 + 0.0021213/mom + -0.000542008/mom/mom + -0.00268482/sqrt(mom);
      sigma = 0.00193173 + 0.00146152/mom + 6.94032e-05/mom/mom + -0.00135972/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>-30&&zed<=-15))
    {
      mean = 0.00256615 + 0.00232302/mom + -1.40519e-05/mom/mom + -0.00506241/sqrt(mom);
      sigma = 0.000598091 + -0.00305503/mom + 0.000895321/mom/mom + 0.00380296/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>-45&&zed<=-30))
    {
      mean = 0.00083905 + 0.000549576/mom + -0.000438196/mom/mom + -0.000770053/sqrt(mom);
      sigma = 0.00146839 + -0.0001581/mom + 0.000463594/mom/mom + 0.000333076/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>-45&&zed<=-30))
    {
      mean = 0.00112993 + -0.000802611/mom + 0.000829214/mom/mom + -0.00142521/sqrt(mom);
      sigma = 0.00145426 + -0.00150668/mom + 0.000715041/mom/mom + 0.00156105/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>-60&&zed<=-45))
    {
      mean = 0.00126941 + 0.000641813/mom + -0.000715529/mom/mom + -0.00106759/sqrt(mom);
      sigma = 0.000566423 + -0.00291098/mom + 0.00101942/mom/mom + 0.00342857/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>-60&&zed<=-45))
    {
      mean = 0.00026901 + -0.00230156/mom + 0.00129386/mom/mom + 0.000521513/sqrt(mom);
      sigma = 0.00069827 + -0.00383458/mom + 0.00127868/mom/mom + 0.00412206/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>-75&&zed<=-60))
    {
      mean = 0.000897134 + -7.74066e-06/mom + -0.00097639/mom/mom + -0.000123837/sqrt(mom);
      sigma = 0.00129951 + -0.00236009/mom + 0.00110699/mom/mom + 0.00205628/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>-75&&zed<=-60))
    {
      mean = -0.00183636 + -0.00776037/mom + 0.00263246/mom/mom + 0.00705724/sqrt(mom);
      sigma = 0.000271943 + -0.00499083/mom + 0.00158989/mom/mom + 0.00545857/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>=0&&zed<15))
    {
      mean = -0.00401752 + -0.0127304/mom + 0.00281526/mom/mom + 0.0138338/sqrt(mom);
      sigma = 0.00450204 + 0.00775855/mom + -0.000945465/mom/mom + -0.00908856/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>=0&&zed<15))
    {
      mean = 0.0026243 + 0.0019889/mom + 7.70286e-05/mom/mom + -0.00491516/sqrt(mom);
      sigma = 0.000989057 + -0.0016463/mom + 0.000569114/mom/mom + 0.0023369/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>=15&&zed<30))
    {
      mean = -0.00255356 + -0.00954756/mom + 0.00215743/mom/mom + 0.00990725/sqrt(mom);
      sigma = 0.00413723 + 0.00705198/mom + -0.000827612/mom/mom + -0.00811995/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>=15&&zed<30))
    {
      mean = 0.00245028 + 0.00241692/mom + 7.64213e-05/mom/mom + -0.00517052/sqrt(mom);
      sigma = 0.00153685 + -0.000506565/mom + 0.000415391/mom/mom + 0.000787657/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>=30&&zed<45))
    {
      mean = -0.0019365 + -0.00864205/mom + 0.00180257/mom/mom + 0.00879471/sqrt(mom);
      sigma = 0.00494148 + 0.00863059/mom + -0.00103618/mom/mom + -0.0102881/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>=30&&zed<45))
    {
      mean = 0.00284624 + 0.00412754/mom + -1.08503e-05/mom/mom + -0.00720164/sqrt(mom);
      sigma = 0.00116497 + -0.00238212/mom + 0.000899192/mom/mom + 0.00252806/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>=45&&zed<60))
    {
      mean = -0.000238828 + -0.00469396/mom + 0.000744167/mom/mom + 0.00425458/sqrt(mom);
      sigma = 0.0058253 + 0.0103161/mom + -0.00126574/mom/mom + -0.0126127/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>=45&&zed<60))
    {
      mean = 0.00291953 + 0.00666092/mom + -0.000243012/mom/mom + -0.0096088/sqrt(mom);
      sigma = 0.00169923 + -0.00171224/mom + 0.0009872/mom/mom + 0.00120526/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>=60&&zed<75))
    {
      mean = 0.000874503 + -0.00151226/mom + -0.000194071/mom/mom + 0.000566069/sqrt(mom);
      sigma = 0.0047347 + 0.00731468/mom + -0.000674383/mom/mom + -0.00916216/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>=60&&zed<75))
    {
      mean = 0.000953473 + 0.000624478/mom + 0.0012131/mom/mom + -0.00270899/sqrt(mom);
      sigma = -0.0011316 + -0.0089325/mom + 0.00227822/mom/mom + 0.00998359/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>-15&&zed<0))
    {
      mean = 0.00255162 + 0.00327803/mom + -0.000388217/mom/mom + -0.00556908/sqrt(mom);
      sigma = -0.000176699 + -0.0052951/mom + 0.00136874/mom/mom + 0.00631574/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>-15&&zed<0))
    {
      mean = 0.00205311 + 0.00384791/mom + -0.000784882/mom/mom + -0.00495605/sqrt(mom);
      sigma = 0.0037722 + 0.00455193/mom + -0.000313379/mom/mom + -0.00589102/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>-30&&zed<=-15))
    {
      mean = 0.00034529 + -0.00178953/mom + 0.000526013/mom/mom + 0.000768418/sqrt(mom);
      sigma = 0.000846795 + -0.00184054/mom + 0.000658689/mom/mom + 0.00258936/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>-30&&zed<=-15))
    {
      mean = 0.00198927 + 0.00371452/mom + -0.000861501/mom/mom + -0.00466058/sqrt(mom);
      sigma = 0.00269352 + 0.00204491/mom + 0.000119345/mom/mom + -0.00271423/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>-45&&zed<=-30))
    {
      mean = -0.00114449 + -0.00536478/mom + 0.00146648/mom/mom + 0.00480343/sqrt(mom);
      sigma = 0.00181866 + -0.000993063/mom + 0.000718893/mom/mom + 0.000687647/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>-45&&zed<=-30))
    {
      mean = 0.00250239 + 0.00450826/mom + -0.00118243/mom/mom + -0.00562533/sqrt(mom);
      sigma = 0.00216433 + 0.000864583/mom + 0.000329743/mom/mom + -0.00123022/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>-60&&zed<=-45))
    {
      mean = -0.00293286 + -0.00881041/mom + 0.00223004/mom/mom + 0.00933329/sqrt(mom);
      sigma = -0.000585947 + -0.00691501/mom + 0.00189772/mom/mom + 0.00784951/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>-60&&zed<=-45))
    {
      mean = 0.00201603 + 0.00253868/mom + -0.00108812/mom/mom + -0.00331999/sqrt(mom);
      sigma = 0.00181229 + -0.000644352/mom + 0.000699192/mom/mom + 0.000290482/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>-75&&zed<=-60))
    {
      mean = -0.00202079 + -0.00880266/mom + 0.00283137/mom/mom + 0.00810797/sqrt(mom);
      sigma = 0.000484455 + -0.00469348/mom + 0.00163454/mom/mom + 0.00488246/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>-75&&zed<=-60))
    {
      mean = 0.00124738 + 0.000861024/mom + -0.00114856/mom/mom + -0.00120051/sqrt(mom);
      sigma = 0.0014472 + -0.00175362/mom + 0.000954958/mom/mom + 0.00154593/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>=0&&zed<15))
    {
      mean = 0.00123161 + -0.000180029/mom + 0.000296852/mom/mom + -0.00152761/sqrt(mom);
      sigma = 0.000622238 + -0.00302391/mom + 0.000919393/mom/mom + 0.00371634/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>=0&&zed<15))
    {
      mean = -0.00165903 + -0.00733822/mom + 0.00183847/mom/mom + 0.00711624/sqrt(mom);
      sigma = 0.00398948 + 0.00566395/mom + -0.000455977/mom/mom + -0.006982/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>=15&&zed<30))
    {
      mean = 0.00176976 + 0.00125968/mom + 0.000194677/mom/mom + -0.00342248/sqrt(mom);
      sigma = -7.44695e-05 + -0.00474064/mom + 0.0012426/mom/mom + 0.00575282/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>=15&&zed<30))
    {
      mean = -0.00165246 + -0.00751983/mom + 0.00178611/mom/mom + 0.00736559/sqrt(mom);
      sigma = 0.00433168 + 0.00629498/mom + -0.000530062/mom/mom + -0.00788407/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>=30&&zed<45))
    {
      mean = 0.00160765 + 0.0013774/mom + 0.000452611/mom/mom + -0.00367991/sqrt(mom);
      sigma = 0.0010407 + -0.00302237/mom + 0.00109483/mom/mom + 0.00302715/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>=30&&zed<45))
    {
      mean = -0.000658789 + -0.0057385/mom + 0.0012901/mom/mom + 0.00513811/sqrt(mom);
      sigma = 0.00521022 + 0.00831393/mom + -0.00085778/mom/mom + -0.0104383/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>=45&&zed<60))
    {
      mean = 0.00171107 + 0.00426685/mom + 0.000124131/mom/mom + -0.00634049/sqrt(mom);
      sigma = 0.000600309 + -0.00465922/mom + 0.00159469/mom/mom + 0.00460812/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>=45&&zed<60))
    {
      mean = 0.000458454 + -0.00335717/mom + 0.000533658/mom/mom + 0.00241407/sqrt(mom);
      sigma = 0.00625919 + 0.0108792/mom + -0.00130316/mom/mom + -0.0135432/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>=60&&zed<75))
    {
      mean = 0.0016611 + 0.00167069/mom + 0.00110358/mom/mom + -0.00432706/sqrt(mom);
      sigma = -0.000428807 + -0.00740691/mom + 0.00208329/mom/mom + 0.00792526/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>=60&&zed<75))
    {
      mean = 0.000134164 + -0.00291705/mom + 7.3576e-06/mom/mom + 0.00247988/sqrt(mom);
      sigma = 0.00513457 + 0.00816428/mom + -0.000831614/mom/mom + -0.010189/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>-15&&zed<0))
    {
      mean = -0.00137297 + -0.003953/mom + 0.000817254/mom/mom + 0.00458009/sqrt(mom);
      sigma = 0.00200518 + 0.00236291/mom + -0.000307189/mom/mom + -0.00183163/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>-15&&zed<0))
    {
      mean = 0.00109918 + 0.00256701/mom + -0.000439922/mom/mom + -0.00331628/sqrt(mom);
      sigma = -6.28503e-05 + -0.00369957/mom + 0.000874413/mom/mom + 0.00495791/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>-30&&zed<=-15))
    {
      mean = 0.00403541 + 0.00853072/mom + -0.00126881/mom/mom + -0.0112568/sqrt(mom);
      sigma = 0.00143712 + 0.00194685/mom + -0.000361261/mom/mom + -0.000697335/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>-30&&zed<=-15))
    {
      mean = -0.00167995 + -0.00592064/mom + 0.00132587/mom/mom + 0.00605806/sqrt(mom);
      sigma = -0.00228963 + -0.00830366/mom + 0.00146561/mom/mom + 0.0112902/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>-45&&zed<=-30))
    {
      mean = 0.0017819 + 0.00254092/mom + -0.000552148/mom/mom + -0.00353348/sqrt(mom);
      sigma = 0.00216073 + 0.00247771/mom + -0.00028654/mom/mom + -0.00211734/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>-45&&zed<=-30))
    {
      mean = 0.000922682 + 0.00211782/mom + 8.07157e-06/mom/mom + -0.0032995/sqrt(mom);
      sigma = -0.000599456 + -0.00584556/mom + 0.00139407/mom/mom + 0.0071224/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>-60&&zed<=-45))
    {
      mean = 0.00217429 + 0.00310485/mom + -0.000959786/mom/mom + -0.00413338/sqrt(mom);
      sigma = 0.00079904 + -0.00108159/mom + 0.000435514/mom/mom + 0.00206575/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>-60&&zed<=-45))
    {
      mean = 0.000173753 + 0.000736029/mom + 0.000588168/mom/mom + -0.00173984/sqrt(mom);
      sigma = -0.000481798 + -0.00642373/mom + 0.00168973/mom/mom + 0.00727546/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>-75&&zed<=-60))
    {
      mean = 0.00337123 + 0.00588347/mom + -0.00182236/mom/mom + -0.00757011/sqrt(mom);
      sigma = 0.000850197 + -0.00164564/mom + 0.000676224/mom/mom + 0.0023067/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>-75&&zed<=-60))
    {
      mean = -0.000211104 + -0.000116291/mom + 0.00114668/mom/mom + -0.000735762/sqrt(mom);
      sigma = -0.00137239 + -0.00913759/mom + 0.00227279/mom/mom + 0.0103084/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>=0&&zed<15))
    {
      mean = -0.00620839 + -0.0100759/mom + 0.000993814/mom/mom + 0.0156349/sqrt(mom);
      sigma = -0.00185447 + -0.00714399/mom + 0.00121257/mom/mom + 0.0100801/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>=0&&zed<15))
    {
      mean = 0.00206311 + 0.00540018/mom + -0.000960802/mom/mom + -0.0066248/sqrt(mom);
      sigma = 4.11023e-05 + -0.00337202/mom + 0.000800242/mom/mom + 0.00469469/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>=15&&zed<30))
    {
      mean = -0.00430383 + -0.00594485/mom + 0.000225637/mom/mom + 0.0103762/sqrt(mom);
      sigma = -0.000710891 + -0.00465552/mom + 0.000824579/mom/mom + 0.00683759/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>=15&&zed<30))
    {
      mean = -0.000536223 + -0.000459916/mom + 0.000125877/mom/mom + 0.000711221/sqrt(mom);
      sigma = 0.000380205 + -0.00218947/mom + 0.000529201/mom/mom + 0.00348573/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>=30&&zed<45))
    {
      mean = -0.00146444 + -0.000689408/mom + -0.00077498/mom/mom + 0.0033216/sqrt(mom);
      sigma = -0.000606835 + -0.00498217/mom + 0.000977042/mom/mom + 0.00691506/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>=30&&zed<45))
    {
      mean = -0.00122559 + -0.0017187/mom + 0.000564067/mom/mom + 0.00214273/sqrt(mom);
      sigma = 3.73163e-05 + -0.00329567/mom + 0.00077974/mom/mom + 0.00469157/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>=45&&zed<60))
    {
      mean = -0.00114301 + -0.000654185/mom + -0.00103853/mom/mom + 0.00316975/sqrt(mom);
      sigma = -0.000198005 + -0.00437385/mom + 0.00101123/mom/mom + 0.00582226/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>=45&&zed<60))
    {
      mean = -0.00257375 + -0.00451307/mom + 0.00137878/mom/mom + 0.00545986/sqrt(mom);
      sigma = -0.000575501 + -0.00527409/mom + 0.00124251/mom/mom + 0.00681979/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>=60&&zed<75))
    {
      mean = 0.000765797 + 0.00227934/mom + -0.00158524/mom/mom + -0.00164887/sqrt(mom);
      sigma = 0.00148106 + -0.000719762/mom + 0.000532918/mom/mom + 0.000955478/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>=60&&zed<75))
    {
      mean = -0.00421918 + -0.00840643/mom + 0.00238746/mom/mom + 0.0103413/sqrt(mom);
      sigma = -0.000138846 + -0.00439356/mom + 0.00115976/mom/mom + 0.00558512/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>-15&&zed<0))
    {
      mean = -0.000410378 + -0.000583288/mom + 6.21387e-05/mom/mom + 0.000834728/sqrt(mom);
      sigma = 0.000796772 + -0.00186731/mom + 0.000601555/mom/mom + 0.00255248/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>-15&&zed<0))
    {
      mean = 0.000957651 + 0.00134387/mom + -7.18909e-05/mom/mom + -0.00214825/sqrt(mom);
      sigma = 0.00422511 + 0.00653166/mom + -0.000852401/mom/mom + -0.00772913/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>-30&&zed<=-15))
    {
      mean = -0.0022438 + -0.0068003/mom + 0.00146681/mom/mom + 0.00736422/sqrt(mom);
      sigma = -0.00196514 + -0.00729559/mom + 0.00133119/mom/mom + 0.0100754/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>-30&&zed<=-15))
    {
      mean = 0.00536361 + 0.0114115/mom + -0.0017193/mom/mom + -0.0150022/sqrt(mom);
      sigma = 0.00353069 + 0.00585588/mom + -0.00085218/mom/mom + -0.00627399/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>-45&&zed<=-30))
    {
      mean = -0.000467694 + -0.000292527/mom + 0.000326443/mom/mom + 0.000198947/sqrt(mom);
      sigma = -0.000187537 + -0.00489358/mom + 0.00127601/mom/mom + 0.00587024/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>-45&&zed<=-30))
    {
      mean = 0.00356768 + 0.00630515/mom + -0.00114129/mom/mom + -0.00848806/sqrt(mom);
      sigma = 0.00282916 + 0.00338237/mom + -0.000311723/mom/mom + -0.00369367/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>-60&&zed<=-45))
    {
      mean = -0.000474419 + -0.000502654/mom + 0.000779378/mom/mom + -1.63061e-05/sqrt(mom);
      sigma = -0.000753246 + -0.00679882/mom + 0.0017455/mom/mom + 0.00788208/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>-60&&zed<=-45))
    {
      mean = 0.00343206 + 0.00584421/mom + -0.00139081/mom/mom + -0.0077011/sqrt(mom);
      sigma = 0.00256396 + 0.0026289/mom + -0.000107246/mom/mom + -0.00287075/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>-75&&zed<=-60))
    {
      mean = -2.3297e-05 + -7.83939e-05/mom + 0.00118354/mom/mom + -0.000975268/sqrt(mom);
      sigma = -0.00174889 + -0.0101547/mom + 0.00249564/mom/mom + 0.0114778/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>-75&&zed<=-60))
    {
      mean = 0.00286669 + 0.0052353/mom + -0.00174304/mom/mom + -0.00653206/sqrt(mom);
      sigma = 0.0013228 + -0.000507541/mom + 0.000492877/mom/mom + 0.000909534/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>=0&&zed<15))
    {
      mean = -6.5075e-05 + 0.0011111/mom + -0.000313293/mom/mom + -0.000839412/sqrt(mom);
      sigma = 0.000269304 + -0.00276689/mom + 0.000743021/mom/mom + 0.00392039/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>=0&&zed<15))
    {
      mean = -0.00327715 + -0.00416811/mom + 9.11764e-05/mom/mom + 0.00768575/sqrt(mom);
      sigma = 0.000216267 + -0.00421667/mom + 0.000995067/mom/mom + 0.00522346/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>=15&&zed<30))
    {
      mean = -0.0021168 + -0.00351352/mom + 0.000545371/mom/mom + 0.00494352/sqrt(mom);
      sigma = -2.2096e-05 + -0.00365481/mom + 0.000928903/mom/mom + 0.00493135/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>=15&&zed<30))
    {
      mean = -0.00205649 + -0.00127107/mom + -0.000507737/mom/mom + 0.0041855/sqrt(mom);
      sigma = -0.000421524 + -0.00549062/mom + 0.0011721/mom/mom + 0.00697836/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>=30&&zed<45))
    {
      mean = -0.00350039 + -0.00619558/mom + 0.00122339/mom/mom + 0.00826701/sqrt(mom);
      sigma = 0.00023017 + -0.00295374/mom + 0.000791439/mom/mom + 0.0041321/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>=30&&zed<45))
    {
      mean = -0.000877402 + 0.000923871/mom + -0.00106791/mom/mom + 0.00142369/sqrt(mom);
      sigma = -0.000307761 + -0.00513115/mom + 0.00115491/mom/mom + 0.00652061/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>=45&&zed<60))
    {
      mean = -0.00305615 + -0.00527034/mom + 0.00145387/mom/mom + 0.00665126/sqrt(mom);
      sigma = -0.00044794 + -0.00488414/mom + 0.00121315/mom/mom + 0.0063412/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>=45&&zed<60))
    {
      mean = 0.00080905 + 0.00397175/mom + -0.00183735/mom/mom + -0.00260217/sqrt(mom);
      sigma = 7.05386e-05 + -0.00411534/mom + 0.00103236/mom/mom + 0.00528772/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>=60&&zed<75))
    {
      mean = -0.00393761 + -0.00791732/mom + 0.00229985/mom/mom + 0.00970526/sqrt(mom);
      sigma = -0.000697533 + -0.00577443/mom + 0.00145716/mom/mom + 0.00724979/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>=60&&zed<75))
    {
      mean = 0.00140444 + 0.00440758/mom + -0.0019758/mom/mom + -0.00404196/sqrt(mom);
      sigma = 0.00170568 + 0.000123038/mom + 0.000364896/mom/mom + 0.000119511/sqrt(mom);
    }
  
  value = (tofwdphi - mean)/sigma;
  return value;
  
}

float caltofwsdz(int run, int striptofw, int charge, float zed, float mom, float tofwdz)
{

  float mean = -9999;
  float sigma = -9999;
  float value = -9999;

  if(run>250484&&striptofw<256&&charge==-1&&(zed>-15||zed<0))
    {
      mean = 0.118857 + 0.44832/mom + -0.0670782/mom/mom + -0.470917/sqrt(mom);
      sigma = 1.85196 + 0.377207/mom + 0.121847/mom/mom + -0.615347/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>-15||zed<0))
    {
      mean = -0.887929 + -1.65139/mom + 0.238711/mom/mom + 2.33161/sqrt(mom);
      sigma = 2.45112 + 1.91209/mom + -0.147316/mom/mom + -2.44926/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>-30||zed<=-15))
    {
      mean = -0.318636 + 0.278464/mom + -0.0942135/mom/mom + 0.13127/sqrt(mom);
      sigma = 1.99126 + 0.86878/mom + 0.00770114/mom/mom + -1.11388/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>-30||zed<=-15))
    {
      mean = -1.6583 + -3.20044/mom + 0.494653/mom/mom + 4.35826/sqrt(mom);
      sigma = 2.99898 + 3.12418/mom + -0.353956/mom/mom + -3.99796/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>-45||zed<=-30))
    {
      mean = -2.19141 + -3.46518/mom + 0.517439/mom/mom + 5.14008/sqrt(mom);
      sigma = 2.32582 + 1.42119/mom + -0.0394429/mom/mom + -1.97489/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>-45||zed<=-30))
    {
      mean = -1.67791 + -2.7042/mom + 0.356897/mom/mom + 4.04736/sqrt(mom);
      sigma = 2.30131 + 1.5728/mom + -0.102653/mom/mom + -2.0109/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>-60||zed<=-45))
    {
      mean = -3.13567 + -4.93415/mom + 0.700394/mom/mom + 7.3987/sqrt(mom);
      sigma = 2.3354 + 1.50035/mom + -0.0552019/mom/mom + -2.03258/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>-60||zed<=-45))
    {
      mean = -2.2795 + -3.38023/mom + 0.408581/mom/mom + 5.3004/sqrt(mom);
      sigma = 2.3235 + 1.56445/mom + -0.0920534/mom/mom + -2.02554/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>-75||zed<=-60))
    {
      mean = -5.01817 + -7.98609/mom + 1.07013/mom/mom + 12.0822/sqrt(mom);
      sigma = 1.62755 + 0.186647/mom + 0.170964/mom/mom + -0.210921/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>-75||zed<=-60))
    {
      mean = -3.47709 + -5.38258/mom + 0.614885/mom/mom + 8.40917/sqrt(mom);
      sigma = 1.93967 + 0.810534/mom + 0.0373117/mom/mom + -0.995694/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>=0||zed<15))
    {
      mean = 0.284131 + 0.408777/mom + -0.0590066/mom/mom + -0.679911/sqrt(mom);
      sigma = 1.57288 + -0.050345/mom + 0.162942/mom/mom + 0.0667512/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>=0||zed<15))
    {
      mean = 0.309394 + 0.595149/mom + -0.105596/mom/mom + -0.803163/sqrt(mom);
      sigma = 2.24002 + 1.47797/mom + -0.0746522/mom/mom + -1.88627/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>=15||zed<30))
    {
      mean = 1.17709 + 1.95104/mom + -0.295115/mom/mom + -2.8358/sqrt(mom);
      sigma = 2.1538 + 1.25177/mom + -0.0544929/mom/mom + -1.5935/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>=15||zed<30))
    {
      mean = 0.668639 + 0.820013/mom + -0.083035/mom/mom + -1.41691/sqrt(mom);
      sigma = 2.60122 + 2.18897/mom + -0.187476/mom/mom + -2.85114/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>=30||zed<45))
    {
      mean = 1.93723 + 2.91336/mom + -0.430552/mom/mom + -4.40627/sqrt(mom);
      sigma = 2.16409 + 1.31525/mom + -0.0687775/mom/mom + -1.65664/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>=30||zed<45))
    {
      mean = 2.00953 + 3.21961/mom + -0.418311/mom/mom + -4.83906/sqrt(mom);
      sigma = 2.3427 + 1.49319/mom + -0.0608056/mom/mom + -2.03119/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>=45||zed<60))
    {
      mean = 3.39511 + 5.33321/mom + -0.739443/mom/mom + -8.01402/sqrt(mom);
      sigma = 1.93878 + 0.759397/mom + 0.019147/mom/mom + -0.946384/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>=45||zed<60))
    {
      mean = 2.69913 + 4.39169/mom + -0.557706/mom/mom + -6.60741/sqrt(mom);
      sigma = 2.70525 + 2.29834/mom + -0.181995/mom/mom + -3.06365/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==-1&&(zed>=60||zed<75))
    {
      mean = 4.83086 + 7.5049/mom + -0.960219/mom/mom + -11.5073/sqrt(mom);
      sigma = 1.9763 + 1.07484/mom + -0.0323894/mom/mom + -1.24551/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==-1&&(zed>=60||zed<75))
    {
      mean = 3.99431 + 6.3529/mom + -0.722833/mom/mom + -9.80686/sqrt(mom);
      sigma = 2.23846 + 1.45713/mom + -0.0593411/mom/mom + -1.87151/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>-15||zed<0))
    {
      mean = -0.548375 + -1.26574/mom + 0.209797/mom/mom + 1.65638/sqrt(mom);
      sigma = 1.52207 + 0.175477/mom + 0.101533/mom/mom + 0.00237232/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>-15||zed<0))
    {
      mean = -0.326846 + -0.606593/mom + 0.112963/mom/mom + 0.827888/sqrt(mom);
      sigma = 2.3754 + 1.60766/mom + -0.0811662/mom/mom + -2.17488/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>-30||zed<=-15))
    {
      mean = -1.44339 + -2.66415/mom + 0.403652/mom/mom + 3.71072/sqrt(mom);
      sigma = 2.03475 + 0.930868/mom + 0.0268905/mom/mom + -1.20627/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>-30||zed<=-15))
    {
      mean = -0.996564 + -1.34013/mom + 0.189923/mom/mom + 2.14019/sqrt(mom);
      sigma = 2.16487 + 1.14845/mom + 0.000613678/mom/mom + -1.57922/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>-45||zed<=-30))
    {
      mean = -1.35035 + -2.1261/mom + 0.267944/mom/mom + 3.2255/sqrt(mom);
      sigma = 2.24002 + 1.58303/mom + -0.103115/mom/mom + -1.93371/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>-45||zed<=-30))
    {
      mean = -2.00598 + -2.77994/mom + 0.367476/mom/mom + 4.43519/sqrt(mom);
      sigma = 2.17043 + 1.24619/mom + -0.0154762/mom/mom + -1.67137/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>-60||zed<=-45))
    {
      mean = -2.38677 + -3.81788/mom + 0.515507/mom/mom + 5.71924/sqrt(mom);
      sigma = 1.71708 + 0.237803/mom + 0.147182/mom/mom + -0.316847/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>-60||zed<=-45))
    {
      mean = -3.76807 + -5.87265/mom + 0.799884/mom/mom + 8.888/sqrt(mom);
      sigma = 2.05932 + 1.09563/mom + -0.00489511/mom/mom + -1.40773/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>-75||zed<=-60))
    {
      mean = -4.29002 + -6.93102/mom + 0.839055/mom/mom + 10.5251/sqrt(mom);
      sigma = 1.87369 + 0.949164/mom + -0.00818276/mom/mom + -0.988759/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>-75||zed<=-60))
    {
      mean = -4.81944 + -7.5784/mom + 0.993798/mom/mom + 11.5921/sqrt(mom);
      sigma = 2.32011 + 1.52623/mom + -0.0313512/mom/mom + -2.05697/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>=0||zed<15))
    {
      mean = 0.464557 + 0.825474/mom + -0.124259/mom/mom + -1.2185/sqrt(mom);
      sigma = 1.42964 + -0.495333/mom + 0.270289/mom/mom + 0.565728/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>=0||zed<15))
    {
      mean = 0.312731 + 0.504146/mom + -0.0787295/mom/mom + -0.727859/sqrt(mom);
      sigma = 2.22523 + 1.57137/mom + -0.106864/mom/mom + -1.94069/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>=15||zed<30))
    {
      mean = 0.629459 + 0.80929/mom + -0.084544/mom/mom + -1.35801/sqrt(mom);
      sigma = 2.16877 + 1.19697/mom + -0.00403697/mom/mom + -1.59377/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>=15||zed<30))
    {
      mean = 1.1932 + 1.83005/mom + -0.258668/mom/mom + -2.75013/sqrt(mom);
      sigma = 2.48895 + 1.86628/mom + -0.116078/mom/mom + -2.49884/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>=30||zed<45))
    {
      mean = 1.98369 + 3.20557/mom + -0.421325/mom/mom + -4.77635/sqrt(mom);
      sigma = 2.16301 + 1.08854/mom + 0.0257505/mom/mom + -1.51806/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>=30||zed<45))
    {
      mean = 1.9219 + 2.80807/mom + -0.403595/mom/mom + -4.32112/sqrt(mom);
      sigma = 2.11105 + 1.12451/mom + -0.0134816/mom/mom + -1.48048/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>=45||zed<60))
    {
      mean = 2.84861 + 4.63242/mom + -0.590897/mom/mom + -6.96465/sqrt(mom);
      sigma = 2.26233 + 1.57835/mom + -0.0876356/mom/mom + -1.97074/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>=45||zed<60))
    {
      mean = 3.10954 + 4.54664/mom + -0.603995/mom/mom + -7.08445/sqrt(mom);
      sigma = 2.59936 + 2.19635/mom + -0.186667/mom/mom + -2.85461/sqrt(mom);
    }
  if(run>250484&&striptofw<256&&charge==1&&(zed>=60||zed<75))
    {
      mean = 4.07977 + 6.64099/mom + -0.791734/mom/mom + -10.0782/sqrt(mom);
      sigma = 2.15407 + 1.15433/mom + 0.0293931/mom/mom + -1.56303/sqrt(mom);
    }
  if(run<250593&&striptofw<256&&charge==1&&(zed>=60||zed<75))
    {
      mean = 4.27726 + 6.42452/mom + -0.788475/mom/mom + -10.0816/sqrt(mom);
      sigma = 2.4856 + 2.06497/mom + -0.165635/mom/mom + -2.62459/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>-15||zed<0))
    {
      mean = 0.0926492 + 0.154977/mom + -0.0377246/mom/mom + -0.189855/sqrt(mom);
      sigma = 1.47242 + -0.090414/mom + 0.13363/mom/mom + 0.225057/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>-15||zed<0))
    {
      mean = -0.154461 + -0.0457669/mom + -0.00444047/mom/mom + 0.215456/sqrt(mom);
      sigma = 2.52042 + 2.09284/mom + -0.212162/mom/mom + -2.67583/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>-30||zed<=-15))
    {
      mean = -0.894383 + -1.64938/mom + 0.241348/mom/mom + 2.32793/sqrt(mom);
      sigma = 1.88304 + 0.651134/mom + 0.039407/mom/mom + -0.830914/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>-30||zed<=-15))
    {
      mean = -1.0908 + -1.98589/mom + 0.310546/mom/mom + 2.74794/sqrt(mom);
      sigma = 2.82846 + 2.82668/mom + -0.330174/mom/mom + -3.60372/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>-45||zed<=-30))
    {
      mean = -1.50945 + -2.13346/mom + 0.264437/mom/mom + 3.39734/sqrt(mom);
      sigma = 1.67232 + 0.201493/mom + 0.133784/mom/mom + -0.293039/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>-45||zed<=-30))
    {
      mean = -1.67263 + -2.54671/mom + 0.323876/mom/mom + 3.92028/sqrt(mom);
      sigma = 2.5558 + 2.31323/mom + -0.247514/mom/mom + -2.91826/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>-60||zed<=-45))
    {
      mean = -2.52307 + -3.57283/mom + 0.424225/mom/mom + 5.7137/sqrt(mom);
      sigma = 2.29138 + 1.59385/mom + -0.101139/mom/mom + -2.06929/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>-60||zed<=-45))
    {
      mean = -2.77362 + -4.44267/mom + 0.55129/mom/mom + 6.73039/sqrt(mom);
      sigma = 2.45029 + 2.09654/mom + -0.208547/mom/mom + -2.62993/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>-75||zed<=-60))
    {
      mean = -3.95421 + -5.81549/mom + 0.692123/mom/mom + 9.19154/sqrt(mom);
      sigma = 2.22862 + 1.4371/mom + -0.0469274/mom/mom + -1.893/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>-75||zed<=-60))
    {
      mean = -4.35646 + -7.18593/mom + 0.864017/mom/mom + 10.8461/sqrt(mom);
      sigma = 2.40814 + 1.91155/mom + -0.148504/mom/mom + -2.45544/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>=0||zed<15))
    {
      mean = -0.00442025 + -0.707844/mom + 0.144751/mom/mom + 0.520531/sqrt(mom);
      sigma = 1.47995 + -0.450066/mom + 0.269138/mom/mom + 0.420051/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>=0||zed<15))
    {
      mean = 0.29114 + 0.482772/mom + -0.0450469/mom/mom + -0.766982/sqrt(mom);
      sigma = 2.90142 + 2.88738/mom + -0.323781/mom/mom + -3.73569/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>=15||zed<30))
    {
      mean = 0.682381 + 0.479583/mom + -0.0378244/mom/mom + -1.12262/sqrt(mom);
      sigma = 1.27471 + -0.439322/mom + 0.193853/mom/mom + 0.698075/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>=15||zed<30))
    {
      mean = 0.978699 + 1.76836/mom + -0.236944/mom/mom + -2.5342/sqrt(mom);
      sigma = 2.47868 + 2.00646/mom + -0.181638/mom/mom + -2.59445/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>=30||zed<45))
    {
      mean = 1.5732 + 1.99154/mom + -0.267465/mom/mom + -3.29353/sqrt(mom);
      sigma = 2.25547 + 1.53131/mom + -0.0995947/mom/mom + -1.96847/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>=30||zed<45))
    {
      mean = 1.53016 + 2.42181/mom + -0.278644/mom/mom + -3.71847/sqrt(mom);
      sigma = 2.49883 + 2.21432/mom + -0.231053/mom/mom + -2.77927/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>=45||zed<60))
    {
      mean = 3.31061 + 4.59405/mom + -0.574366/mom/mom + -7.36833/sqrt(mom);
      sigma = 1.85311 + 0.535455/mom + 0.0792243/mom/mom + -0.753986/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>=45||zed<60))
    {
      mean = 2.37377 + 3.78019/mom + -0.418585/mom/mom + -5.81988/sqrt(mom);
      sigma = 2.65017 + 2.68687/mom + -0.316344/mom/mom + -3.32126/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==-1&&(zed>=60||zed<75))
    {
      mean = 4.54425 + 6.60116/mom + -0.794781/mom/mom + -10.5138/sqrt(mom);
      sigma = 2.37939 + 1.93069/mom + -0.169826/mom/mom + -2.38403/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==-1&&(zed>=60||zed<75))
    {
      mean = 3.66704 + 5.96924/mom + -0.653699/mom/mom + -9.15552/sqrt(mom);
      sigma = 2.45787 + 1.95686/mom + -0.139586/mom/mom + -2.57564/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>-15||zed<0))
    {
      mean = -0.0375001 + 0.135592/mom + -0.0379052/mom/mom + -0.0171405/sqrt(mom);
      sigma = 2.7032 + 2.47668/mom + -0.254436/mom/mom + -3.18541/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>-15||zed<0))
    {
      mean = -0.129831 + -0.198001/mom + 0.0126297/mom/mom + 0.320624/sqrt(mom);
      sigma = 2.24849 + 1.40758/mom + -0.0660383/mom/mom + -1.86509/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>-30||zed<=-15))
    {
      mean = -0.97984 + -1.73595/mom + 0.270629/mom/mom + 2.43877/sqrt(mom);
      sigma = 3.03152 + 3.25708/mom + -0.39262/mom/mom + -4.15107/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>-30||zed<=-15))
    {
      mean = -0.950882 + -1.64138/mom + 0.21705/mom/mom + 2.40744/sqrt(mom);
      sigma = 2.54865 + 2.06241/mom + -0.157171/mom/mom + -2.73787/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>-45||zed<=-30))
    {
      mean = -2.26839 + -4.01311/mom + 0.578061/mom/mom + 5.73338/sqrt(mom);
      sigma = 2.49208 + 2.03679/mom + -0.186065/mom/mom + -2.61432/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>-45||zed<=-30))
    {
      mean = -1.77171 + -2.63088/mom + 0.340697/mom/mom + 4.07302/sqrt(mom);
      sigma = 2.20746 + 1.45998/mom + -0.0771526/mom/mom + -1.89571/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>-60||zed<=-45))
    {
      mean = -2.92277 + -4.70065/mom + 0.583519/mom/mom + 7.09753/sqrt(mom);
      sigma = 2.68127 + 2.62277/mom + -0.287135/mom/mom + -3.28529/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>-60||zed<=-45))
    {
      mean = -2.8682 + -4.34834/mom + 0.558313/mom/mom + 6.70585/sqrt(mom);
      sigma = 2.22717 + 1.55093/mom + -0.0945925/mom/mom + -1.9803/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>-75||zed<=-60))
    {
      mean = -4.45313 + -7.41983/mom + 0.904725/mom/mom + 11.1116/sqrt(mom);
      sigma = 1.89262 + 0.745123/mom + 0.0591121/mom/mom + -0.95576/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>-75||zed<=-60))
    {
      mean = -4.61218 + -7.09011/mom + 0.86467/mom/mom + 10.9987/sqrt(mom);
      sigma = 2.06084 + 1.1392/mom + -0.0051513/mom/mom + -1.48479/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>=0||zed<15))
    {
      mean = 0.0884734 + 0.327215/mom + -0.0426264/mom/mom + -0.44258/sqrt(mom);
      sigma = 2.94555 + 3.34951/mom + -0.419652/mom/mom + -4.11522/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>=0||zed<15))
    {
      mean = 0.0665919 + -0.469105/mom + 0.104013/mom/mom + 0.284039/sqrt(mom);
      sigma = 2.38707 + 1.70833/mom + -0.111043/mom/mom + -2.26219/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>=15||zed<30))
    {
      mean = 1.3599 + 2.51784/mom + -0.348411/mom/mom + -3.56819/sqrt(mom);
      sigma = 2.11665 + 1.19054/mom + -0.0333198/mom/mom + -1.54245/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>=15||zed<30))
    {
      mean = 0.975301 + 1.14092/mom + -0.149871/mom/mom + -1.95228/sqrt(mom);
      sigma = 2.42814 + 1.75236/mom + -0.114701/mom/mom + -2.35718/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>=30||zed<45))
    {
      mean = 2.03334 + 3.74313/mom + -0.518695/mom/mom + -5.29154/sqrt(mom);
      sigma = 2.23103 + 1.72425/mom + -0.147584/mom/mom + -2.08032/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>=30||zed<45))
    {
      mean = 1.67597 + 2.00863/mom + -0.255469/mom/mom + -3.42685/sqrt(mom);
      sigma = 2.0682 + 1.029/mom + 0.000698977/mom/mom + -1.40265/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>=45||zed<60))
    {
      mean = 2.91679 + 5.044/mom + -0.636306/mom/mom + -7.39109/sqrt(mom);
      sigma = 2.22674 + 1.68376/mom + -0.129035/mom/mom + -2.05946/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>=45||zed<60))
    {
      mean = 3.08236 + 4.29672/mom + -0.556553/mom/mom + -6.85298/sqrt(mom);
      sigma = 2.11299 + 1.21567/mom + -0.041905/mom/mom + -1.58668/sqrt(mom);
    }
  if(run>250484&&striptofw>255&&charge==1&&(zed>=60||zed<75))
    {
      mean = 3.94841 + 6.61854/mom + -0.780877/mom/mom + -9.92479/sqrt(mom);
      sigma = 2.02333 + 1.0383/mom + 0.01765/mom/mom + -1.34973/sqrt(mom);
    }
  if(run<250593&&striptofw>255&&charge==1&&(zed>=60||zed<75))
    {
      mean = 4.04044 + 5.52947/mom + -0.624857/mom/mom + -9.13369/sqrt(mom);
      sigma = 1.99925 + 1.20458/mom + -0.0410261/mom/mom + -1.4274/sqrt(mom);
    }

  value = (tofwdz - mean)/sigma;
  return value;
  
}

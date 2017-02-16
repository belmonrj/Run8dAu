if(run>250484&&charge==-1)
{
mean = -0.00565153 + -0.0170638/mom + 0.00335309/mom/mom + 0.0166101/sqrt(mom);
sigma = 0.916739 + -0.0706207/mom + 0.0111088/mom/mom + 0.125801/sqrt(mom);
}
if(run<250593&&charge==-1)
{
mean = -0.016311 + -0.0278699/mom + 0.00352864/mom/mom + 0.0386405/sqrt(mom);
sigma = 0.83138 + -0.212727/mom + 0.0294335/mom/mom + 0.333165/sqrt(mom);
}
if(run>250484&&charge==1)
{
mean = 0.00968331 + 0.00842975/mom + -4.97472e-05/mom/mom + -0.0219147/sqrt(mom);
sigma = 0.764554 + -0.331884/mom + 0.0388235/mom/mom + 0.527434/sqrt(mom);
}
if(run<250593&&charge==1)
{
mean = -0.0141964 + -0.0222397/mom + 0.00321578/mom/mom + 0.0302044/sqrt(mom);
sigma = 0.797409 + -0.250537/mom + 0.0278151/mom/mom + 0.42065/sqrt(mom);
}
if(run>250484&&charge==-1)
{
mean = -0.181197 + -1.10986/cent + 0.393046/cent/cent + 1.06504/sqrt(cent);
sigma = 0.939996 + 0.00202958*cent;
}
if(run<250593&&charge==-1)
{
mean = -0.156578 + -0.930063/cent + 0.314694/cent/cent + 0.923737/sqrt(cent);
sigma = 0.964493 + 0.00207052*cent;
}
if(run>250484&&charge==1)
{
mean = -0.186171 + -1.10323/cent + 0.38063/cent/cent + 1.0722/sqrt(cent);
sigma = 0.964944 + 0.0021342*cent;
}
if(run<250593&&charge==1)
{
mean = -0.159955 + -0.935099/cent + 0.316482/cent/cent + 0.924966/sqrt(cent);
sigma = 0.946206 + 0.00201562*cent;
}

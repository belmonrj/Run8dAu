float isPionLow(float pT, float m2tofw)
{
float x = pT;
float a0 = 0;
float a1 = 0;
float a2 = 0;
float a3 = 0;
float a4 = 0;
float mean = a0+a1/x+a2/x/x+a3*exp(sqrt(x))+a4*sqrt(x);
float b0 = -0.0520841;
float b1 = 0.00462591;
float b2 = -0.000607273;
float b3 = 0.0615347;
float b4 = -0.103104;
float sigma = b0+b1/x+b2/x/x+b3*exp(sqrt(x))+b4*sqrt(x);
return (m2tofw - mean)/sigma;
}


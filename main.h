#define ON  1
#define OFF 0

unsigned short ADC_DATA;
float centreTap = 0.0;

//ALL unsigned short VALUES HAVE BEEN CHANGED TO FLOATS OTHERWISE THE COEFFICIENT MULTIPLICATIONS WILL BE ROUNDED TO THE NEAREST INTEGER WHICH IN SOME CASES IS ZERO.
float xn   = 0.0;       
float xnm1 = 0.0;
float xnm2 = 0.0;
float xnm3 = 0.0;
float xnm4 = 0.0;


float yn   = 0.0;
float ynm1 = 0.0;
float ynm2 = 0.0;
float ynm3 = 0.0;
float ynm4 = 0.0;

#include "mbed.h"
#include "main.h"

// #include "BP_4KHz_Fc_35KHz_Fs_5N.h"
#include "BP_4kHzFc_96kHzFs_5N.h"

//MBED Class Instances follows
DigitalOut SampLED(LED1);               //Digital Output  (GREEN LED on the NUCLEO Board)
DigitalOut SampPin(PB_3);               //is PB_3 you can use an Oscilloscope on This pin to confirm sample rate)
                                        //YOU CAN PROBE SCLK ON SPI1 BY THE BMP280 ON THE MEGA SHELL BOARD !!!! PB_3

AnalogIn  Ain(PA_6);                    //Analog Input (Signal Input 0 to +3 Volts)   "SIG IN" on BREAKOUT MEGA SHELL PCB
AnalogOut Aout(PA_4);                   //Analog Output (Signal Input 0 to +3 Volts)  "DAC1 OUT" on BREAKOUT MEGA SHELL PCB

Ticker sample_timer;

//Ticker routine PROTOTYPE to service samples from Analogue IP and port to Analogue Output
void sampler(void);

int main() {
   
    float sample_rate=(1.0/Fs)*1000000.0; //Calculate the number of uS required for a Frequency Sampling Rate
                                          //Fs held in init.h
    sample_timer.attach_us(&sampler,(int)sample_rate);
                                          //Ticker Instance serviced by routine at a repeat rate in microseconds
  
    while(1) {
          sleep();
    }
}

//Ticker routine to service samples from Analogue IP and port to Analogue Output
void sampler(void)
{
    SampLED = ON;       //LED Indicates start of sampling
    SampPin = ON;

    xn=Ain;               //Input ADC. N.B. ADC in MBED is 0.0 to 1.0 float!!!!!!

    centreTap = xn*b0 + xnm1*b1 + xnm2*b2 + xnm3*b3 + xnm4*b4;  //IIR Filter
    yn = centreTap*a0 - a1*ynm1 - a2*ynm2  - a3*ynm3 - a4*ynm4; //Result in yn
  
    Aout=yn+0.5f;       //Output resultant to DAC. Again MBED uses 0.0 to 1.0 float!!!!!! and Offset to give 0 to 3V3 range
  
    //THESE NEED TO BE LOADED IN THIS ORDER OTHERWISE ALL xnm VALUES WILL BECOME THE SAME AS xn
    xnm4 = xnm3;
    xnm3 = xnm2;
    xnm2 = xnm1;
    xnm1 = xn;  
    
    //THESE NEED TO BE LOADED IN THIS ORDER OTHERWISE ALL ynm VALUES WILL BECOME THE SAME AS yn
    ynm4 = ynm3;
    ynm3 = ynm2;
    ynm2 = ynm1;
    ynm1 = yn;

    SampLED = OFF;      //LED Indicates end of sampling
    SampPin = OFF;
}


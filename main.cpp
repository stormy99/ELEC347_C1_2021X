#include "mbed.h"
#include "rtFilter.hpp"

#define Fs  96000 // Sampling Frequency, Fs
#define N   5 // Number of nodes, N
#define ON  1
#define OFF 0

unsigned short ADC_DATA;

//MBED Class Instances follows
DigitalOut SampLED(LED1);               //Digital Output  (GREEN LED on the NUCLEO Board)
DigitalOut SampPin(PB_3);               //is PB_3 you can use an Oscilloscope on This pin to confirm sample rate)
                                        //YOU CAN PROBE SCLK ON SPI1 BY THE BMP280 ON THE MEGA SHELL BOARD !!!! PB_3

AnalogIn  Ainput(PA_6);                    //Analog Input (Signal Input 0 to +3 Volts)   "SIG IN" on BREAKOUT MEGA SHELL PCB
AnalogOut Aoutput(PA_4);                   //Analog Output (Signal Input 0 to +3 Volts)  "DAC1 OUT" on BREAKOUT MEGA SHELL PCB

Ticker sample_timer;

int fo[5] = {125, 500, 4000, 8000, 16000};
RTFILTER filter(96000, fo[1], 20, 2);
float input = 0.0;

//Ticker routine to service samples from Analogue IP and port to Analogue Output
void sampler(void)
{
    SampLED = ON;       //LED Indicates start of sampling
    SampPin = ON;

    input = Ainput;
    filter.rtFilterSetValue(input);
    Aoutput = filter.rtFilterGetValue();
    

    SampLED = OFF;      //LED Indicates end of sampling
    SampPin = OFF;
}

int main() 
{
    filter.rtFilterDefine();
    filter.rtFilterPrint();

    float sample_rate=(1.0/Fs)*1000000.0; //Calculate the number of uS required for a Frequency Sampling Rate
                                          //Fs held in init.h

    sample_timer.attach_us(&sampler,(int)sample_rate);
                                          //Ticker Instance serviced by routine at a repeat rate in microseconds
    sample_timer.detach();

    while(1) {
        sampler();
        //sleep();
    }
}

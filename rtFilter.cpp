// Included Libraries
#include "mbed.h"
#include "math.h"
#include "rtFilter.hpp"

// Definitions
#define Pi 3.141592653

AnalogIn  Ain(PA_6);                    //Analog Input (Signal Input 0 to +3 Volts)   "SIG IN" on BREAKOUT MEGA SHELL PCB
AnalogOut Aout(PA_4);                   //Analog Output (Signal Input 0 to +3 Volts)  "DAC1 OUT" on BREAKOUT MEGA SHELL PCB

// RTFILTER Class Constructor
RTFILTER::RTFILTER(int fs, int Fo, double boost, int Q)
{
    // Storing 'Filter Parameters' for the RTFILTER class
    this -> _fs = fs;
    this -> _Fo = Fo;
    this -> _boost = boost;
    this -> _Q = Q;

    // Initialising 'Filter Variables' with default values for the RTFILTER class
    _G = 0;
    _k = 0;
    _Wo = 0;
    _centreTap = 1;

    // Initialising 'Filter Coefficient Calculation Variables' with default values for the RTFILTER class
    _Wo1 = 0;
    _Wo2 = 0;
    _cDen = 0;
    _n0 = 0;
    _n1 = 0;
    _n2 = 0;
    _d0 = 1;
    _d1 = 0;
    _d2 = 0;

    // Initialising 'rtFilter Input Variables' with default values for the RTFILTER class
    _xn = 0;
    _xnm1 = 0;
    _xnm2 = 0;

    // Initialising '' with default values for the RTFILTER class
    _yn = 0;
    _ynm1 = 0;
    _ynm2 = 0;
}

// RTFILTER Class Deconstructor
RTFILTER::~RTFILTER() {}

void RTFILTER::rtFilterDefine(void)
{
    // Calculating Variables
    _G = pow(10, _boost/20.0);
    _k = 3 * ((_G - 1) / (_G + 1));
    _Wo = 2 * Pi * _Fo;

    // Calculations for Coefficients
    _Wo1 = tan(_Wo / (2 * _fs));
    _Wo2 = pow(_Wo1, 2);
    _cDen = 1 + ((3 - _k) * _Wo1 / _Q) + _Wo2;

    _n0 = 1 + ((3 + _k) * _Wo1 / _Q) + _Wo2;
    _n1 = -2 + (2 * _Wo2);
    _n2 = 1 - ((3 - _k) * _Wo1 / _Q) + _Wo2;
    _d0 = 1.0000;
    _d1 = _n1;
    _d2 = 1 - ((3 - _k) * _Wo1 / _Q) + _Wo2;

    // Coefficients
    _b0 = _n0 / _cDen;
    _b1 = _n1 / _cDen;
    _b2 = _n2 / _cDen;
    _a0 = _d0;
    _a1 = _d1 / _cDen;
    _a2 = _d2 / _cDen;
}

void RTFILTER::rtFilterPrint(void)
{
    printf("---Print Coefficients---\n\r");
    printf("Numerator 1: %f\n\rNumerator 2: %f\n\rNumerator 3: %f\n\n\r", _b0, _b1, _b2);
    printf("Denominator 1: %f\n\rDenominator 2: %f\n\rDenominator 3: %f\n\r", _a0, _a1, _a2);
    printf("------------------------\n\n\r");
}

void RTFILTER::rtFilterUpdateFo(int newFo)
{
    _Fo = newFo;
}

int RTFILTER::rtFilterGetFo(void) 
{
    return _Fo;
}

void RTFILTER::rtFilterUpdateBoost(double newBoost)
{
    _boost = newBoost;
}

double RTFILTER::rtFilterGetBoost(void)
{
    return _boost;
}

void RTFILTER::rtFilterUpdateQ(int newQ)
{
    _Q = newQ;
}

int RTFILTER::rtFilterGetQ(void) 
{
    return _Q;
}

// Set latest rtFilter xn input sample
void RTFILTER::rtFilterSetValue(void)
{
    _xn = Ain; // Input ADC, xn, Mbed uses 0.0 -> 1.0 float
    _centreTap = (_xn * _b0) + (_xnm1 * _b1) + (_xnm2 * _b2) + (_xnm3 * _b3) + (_xnm4 * _b4); // Graphic EQ - IIR Filter (Real-time)
    _yn = (_centreTap * _a0) - (_ynm1 * _a1) - (_ynm2 * _a2) - (_ynm3 * _a3) - (_ynm4 * _a4); // Output yn

    _filterOutput = _yn + 0.5f; // Mbed uses 0.0 -> 1.0 float
    Aout = _filterOutput; // Output resultant value to the DAC

    // Loaded in this specific order because otherwise all xnm values will become equal to xn
    _xnm4 = _xnm3;
    _xnm3 = _xnm2;
    _xnm2 = _xnm1;
    _xnm1 = _xn;

    // Loaded in this specific order because otherwise all ynm values will become equal to yn
    _ynm4 = _ynm3;
    _ynm3 = _ynm2;
    _ynm2 = _ynm1;
    _ynm1 = _yn;
}

// Get latest rtFilter yn output sample
float RTFILTER::rtFilterGetValue(void)
{
    return _filterOutput;
}

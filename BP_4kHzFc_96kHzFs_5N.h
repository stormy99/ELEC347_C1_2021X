#define Fs 96000 // Sampling-rate Frequency (96kHz - Task 3 specification)
#define N 5 // Number of Nodes, N

// Five-band graphic equaliser
// 125Hz, 500Hz, 4000Hz, 8000Hz, 16000Hz
unsigned int f[N] = {125, 500, 4000, 8000, 16000};

// Coeffs for the analogue filter
// B - Numerator coefficients
float b0 = 0.0000;
float b1 = 0.0000;
float b2 = 1.5546;
float b3 = 0.2098;
float b4 = 0.0038;

// A - Denominator coefficients
float a0 = 0.0000; 
float a1 = 0.0000; 
float a2 = 1.5546; 
float a3 = 0.0210; 
float a4 = 0.0038;

// Coeffs for the discrete-time, IIR filter
float b[3] = {1.9506, -0.8944, -0.1618};
float a[3] = {1.0000, -0.8944, 0.7888};

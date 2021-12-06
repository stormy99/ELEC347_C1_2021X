class RTFILTER
{
    private:
            // Filter Parameters
            int _fs;
            int _Fo;
            double _boost;
            int _Q;

            // Filter Variables
            float _G;
            float _k;
            float _Wo;
            float _filterOutput;
            float _centreTap;

            // Filter Coefficient Calculation Variables
            double _Wo1;
            double _Wo2;
            float _cDen;
            float _n0;
            float _n1;
            float _n2;
            float _d0;
            float _d1;
            float _d2;
            
            // B - Numerator Coefficients
            float _b0;
            float _b1;
            float _b2;
            float _b3;
            float _b4;

            // A - Denominator Coefficients
            float _a0;
            float _a1;
            float _a2;
            float _a3;
            float _a4;

            // rtFilter Input Variables
            float _xn; // Curent rtFilter input sample       
            float _xnm1; // ...
            float _xnm2;
            float _xnm3;
            float _xnm4;

            // rtFilter Output Variables
            float _yn; // Current rtFilter output sample
            float _ynm1; // ...
            float _ynm2;
            float _ynm3;
            float _ynm4;


    public:
            RTFILTER(int fs, int Fo, double boost, int Q); // rtFilter Constructor
            ~RTFILTER(void); // rtFilter Deconstructor

            void rtFilterDefine(void); // Calculate rtFilter Coefficients
            void rtFilterPrint(void); // Print rtFilter Coefficients
            
            void rtFilterUpdateFo(int newFo); // Set rtFilter Centre Frequency
            int rtFilterGetFo(void); // Get current rtFilter Centre Frequency

            void rtFilterUpdateBoost(double newBoost); // Set rtFilter Boost
            double rtFilterGetBoost(void); // Get current rtFilter Boost 

            void rtFilterUpdateQ(int newQ); // Set rtFilter Q-factor
            int rtFilterGetQ(void); // Get current rtFilter Q-factor

            void rtFilterSetValue(float input); // Set latest rtFilter xn input sample
            float rtFilterGetValue(void); // Get latest rtFilter yn output sample
};
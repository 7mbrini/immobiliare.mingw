/******************************************************************************
	author:	Francesco Settembrini
	last update: 23/6/2021, 28/11/2021
	e-mail:	mailto:francesco.settembrini@poliba.it
******************************************************************************/

#pragma once

#include <vector>
#include <string>
//#pragma hdrstop

using namespace std;


typedef vector<double> TVecDoubles;

namespace stats
{
	double Sum(TVecDoubles& Values);
	void Sort(TVecDoubles& Values, bool bAscending = true);

	double Min(TVecDoubles& Values);
	double Max(TVecDoubles& Values);
	double Min(TVecDoubles& Values, int& nIndex);
	double Max(TVecDoubles& Values, int& nIndex);
	double RMS(TVecDoubles& Values);
	double Mean(TVecDoubles& Values);
	double Mode(TVecDoubles Values, int nClasses);
	double Median(TVecDoubles Values);
	double Variance(TVecDoubles& Values);
	double StdDev(TVecDoubles& Values);

	void Outliers(TVecDoubles Values, double &OutMin, double &OutMax);


class THistogram
{
public:
    struct THistPair
    {
        THistPair ()
        {
            Value = 0;
            nFreqs = 0;
        }

        int nFreqs;
        double Value;
    };

    typedef vector<THistPair> TVecHistPairs;


public:
    THistogram(double Min, double Max, int nClasses);
    THistogram(TVecDoubles Vals, int nClasses);

    inline double GetMin();
    inline double GetMax();
    inline int GetClasses();

    inline void Add(double Value);
    TVecHistPairs GetValues();
    inline TVecDoubles GetNormalizedFreqs();

    inline std::string Print();

protected:
    double m_Min, m_Max;
    TVecHistPairs m_Values;

    void Setup(double Min, double Max, int nClasses);
};


};




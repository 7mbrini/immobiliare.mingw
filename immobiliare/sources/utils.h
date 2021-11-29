/******************************************************************************
	author:	Francesco Settembrini
	last update: 23/6/2021, 28/11/2021
	e-mail:	mailto:francesco.settembrini@poliba.it
******************************************************************************/

#ifndef utilsH
#define utilsH

#include <string>
#include <algorithm>

#include "../sources/maths.h"

namespace utils
{
	std::string GetExePath();
    std::string GetDataPath();

	bool FileExists(std::string strFileName);

    std::string LowerCase(std::string strString);
	std::string WideToString(std::wstring wstrString);

	bool ParseDate(std::string strDate,
    	unsigned short& nYear, unsigned short& nMonth, unsigned short& nDay);
			
	template <class T>
	void Shuffle(std::vector<T> &Vec, int nHowMany)
	{
		for(int i=0; i<nHowMany; i++)
		{
			int nFirst = maths::Rand(0, Vec.size()-1);
			int nSecond = maths::Rand(0, Vec.size()-1);

			if( nFirst != nSecond )
			{
				std::swap(Vec[nFirst], Vec[nSecond]);
			}
		}
	}
};

//---------------------------------------------------------------------------
#endif

/******************************************************************************
	author:	Francesco Settembrini
	last update: 8/11/2021, 28/11/2021
	e-mail:	mailto:francesco.settembrini@poliba.it
******************************************************************************/

#ifndef citiesH
#define citiesH

//#include <vcl.h>
//#pragma hdrstop

#include <vector>
#include <string>


typedef std::vector<std::string> TVecStrings;

struct TCity;
typedef std::vector<TCity> TVecCities;

struct TCity
{
	std::string AsString()
    {
        char strTemp[4096];

        sprintf(strTemp,
        	"\ncomune: %s"
            "\nprovincia: %s"
            "\ncap: %s"
            "\nregione: %s",

            m_strName.c_str(),
            m_strProv.c_str(),
            m_strCap.c_str(),
            m_strRegion.c_str()
        );

        return strTemp;
    }

	std::string m_strName, m_strProv, m_strCap, m_strRegion;
};

class TCitiesArchive
{
public:
	TCitiesArchive();

	void Clear();
    int GetCount();

    void GetCities(TVecCities& Cities);
	void GetRegions(TVecStrings& Regions);

	bool LoadFromFile(std::string strFileName);

protected:
	TVecCities m_Cities;

    bool Parse(std::string strTuple, TCity& City);
	bool IsUnique(TVecStrings& Strings, std::string strVal);
};


//---------------------------------------------------------------------------
#endif

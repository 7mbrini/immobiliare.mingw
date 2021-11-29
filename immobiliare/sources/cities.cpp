/*!****************************************************************************

	@file	cities.h
	@file	cities.cpp

	@brief	Data access for "cities" file archive

	@noop	author:	Francesco Settembrini
	@noop	last update: 08/11/2021, 28/11/2021
	@noop	e-mail:	mailto:francesco.settembrini@poliba.it

******************************************************************************/

#include <windows.h>
#include <assert.h>
#include <stdio.h>
#include <iostream>

#include "../sources/utils.h"
#include "../sources/cities.h"


/*!****************************************************************************
* @brief	Constructor
******************************************************************************/
TCitiesArchive::TCitiesArchive()
{
	;
}

/*!****************************************************************************
* @brief	Clear the archive
******************************************************************************/
void TCitiesArchive::Clear()
{
	m_Cities.clear();
}

/*!****************************************************************************
* @brief	Gets the number of elements in the archive
* @return	The number of element in the archive
******************************************************************************/
int TCitiesArchive::GetCount()
{
	return m_Cities.size();
}

/*!****************************************************************************
* @brief	Loads the archive from file
* @param	strFileName The file name containing the archive
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TCitiesArchive::LoadFromFile(std::string strFileName)
{
	bool bResult = false;

    if( utils::FileExists(strFileName) )
    {
                                            // First of all, clear old data!
        Clear();

		const int nSize = 4096;
		char pBuffer[nSize];

        FILE* pFile = NULL;

        if( (pFile = fopen(strFileName.c_str(), "r")) )
        {
												// skip first heading row
        	fgets(pBuffer, nSize-1, pFile);

        	while(!feof(pFile) )
            {
				fgets(pBuffer, nSize-1, pFile);

				TCity City;
                if( Parse(pBuffer, City) )
                {
                	m_Cities.push_back(City);
                }
            }


        	fclose(pFile);

            bResult = true;
		}
	}

	return bResult;
}

/*!****************************************************************************
* @brief	Parse a string record into single fields
* @param	strTuple The string of values separated by comma
* @param	City Reference to a City object
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TCitiesArchive::Parse(std::string strTuple, TCity& City)
{
    City.m_strName = strTuple.substr(0, strTuple.find(",") );

    strTuple = strTuple.substr(strTuple.find(",") + 1, strTuple.length());
    City.m_strProv = strTuple.substr(0, strTuple.find(","));

    strTuple = strTuple.substr(strTuple.find(",") + 1, strTuple.length());
    City.m_strCap = strTuple.substr(0, strTuple.find(","));

    strTuple = strTuple.substr(strTuple.find(",") + 1, strTuple.length());
    City.m_strRegion = strTuple;


#ifdef _DEBUG
//	FormDebug->Print(City.AsString());
//	std::cout << City.AsString();
#endif
										// some little checks ...
	return bool (City.m_strName.length() + City.m_strProv.length()
        + City.m_strCap.length() + City.m_strRegion.length() );
}

/*!****************************************************************************
* @brief	Gets the archive records
* @param	Cities Reference to a vector of cities objects
******************************************************************************/
void TCitiesArchive::GetCities(TVecCities& Cities)
{
	Cities = m_Cities;
}

/*!****************************************************************************
* @brief	Verify the uniqueness of a string in a vector of strings
* @param	Strings Vector of string
* @param	strVal The string to verify the uniqueness of
******************************************************************************/
bool TCitiesArchive::IsUnique(TVecStrings& Strings, std::string strVal)
{
	bool bUnique = true;

	for(unsigned int i=0; i<Strings.size(); i++)
    {
		if( strVal == Strings[i] )
        {
        	bUnique = false;
            break;
        }
    }

    return bUnique;
}

/*!****************************************************************************
* @brief	Gets all the "regions" field contained in a "cities" archive
* @param	Regions Reference to a vector of "region" strings
******************************************************************************/
void TCitiesArchive::GetRegions(TVecStrings& Regions)
{
	for(unsigned int i=0; i<m_Cities.size(); i++)
    {
		if( IsUnique(Regions, m_Cities[i].m_strRegion.c_str()) )
        {
            Regions.push_back(m_Cities[i].m_strRegion.c_str());
        }
    }
}



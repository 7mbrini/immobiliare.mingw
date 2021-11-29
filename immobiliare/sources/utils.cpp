/*!****************************************************************************

	@file	utils.h
	@file	utils.cpp

	@brief	Utility routines

	@noop	author:	Francesco Settembrini
	@noop	last update: 22/11/2021, 28/11/2021
	@noop	e-mail:	mailto:francesco.settembrini@poliba.it

******************************************************************************/

//#include <vcl.h>
//#pragma hdrstop

#include <windows.h>
#include <fileapi.h>
#include <stdlib.h>
#include <locale>
#include <codecvt>
#include <string>
#include <iostream>

//#include <boost/filesystem.hpp>
//#include <boost/algorithm/string.hpp>

#include "../sources/utils.h"
#include "../sources/commdefs.h"

//---------------------------------------------------------------------------
//#pragma package(smart_init)

//using namespace boost::filesystem;


namespace utils
{

/*!****************************************************************************
* @brief	Gets the full path for the executable file
* @return	Returns the full path to the exe file name
******************************************************************************/
std::string GetExePath()
{
	std::string strResult;
	char ownPath[MAX_PATH];

											// When NULL is passed to GetModuleHandle,
											// the handle of the exe itself is returned
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule != NULL)
    {
											// Use GetModuleFileName() with module handle to get the path
		GetModuleFileNameA(hModule, ownPath, (sizeof(ownPath)));

		{
			const int BUFSIZE = 260;

			DWORD  retval=0;

			char buffer[BUFSIZE];
			char* lppPart;
												// Retrieve the full path name for a file.
												// The file does not need to exist.

			retval = GetFullPathNameA( ownPath, BUFSIZE, (LPSTR) buffer, &lppPart);

			if( retval )
			{
				int nPos = strstr((char*)buffer, (char*)lppPart) - buffer;

				char DirName[BUFSIZE];
				memset(DirName, 0, BUFSIZE);
				strncpy(DirName, buffer, nPos-1);

				strResult = std::string(DirName);
			}
		}
	}

	return strResult;
}



/*!****************************************************************************
* @brief	Gets the full path for the data folder
* @return	Returns the full path to the data folder
******************************************************************************/
std::string GetDataPath()
{
	std::string strDataPath = GetExePath() + DATAPATH;


#ifdef _DEBUG
    std::cout << strDataPath;
#endif

	return std::string(strDataPath.c_str());
}

/*!****************************************************************************
* @brief	Parses a date string
* @param	strDate The date string
* @param	nYear Reference to the Year value
* @param	nMonth Reference to the Month value
* @param	nDay Reference to the Day value
* @return	Returns true for success, false otherwise
******************************************************************************/
bool ParseDate(std::string strDate,
	unsigned short& nYear, unsigned short& nMonth, unsigned short& nDay)
{
	bool bResult = true;

	std::string strDay = strDate.substr(0, strDate.find("/"));

    strDate = strDate.substr(strDate.find("/")+1, strDate.length());
    std::string strMonth = strDate.substr(0, strDate.find("/"));

    std::string strYear = strDate.substr(strDate.find("/")+1, strDate.length());

    try
    {
        nDay = atoi(strDay.c_str());
        nMonth = atoi(strMonth.c_str());
        nYear = atoi(strYear.c_str());
    }
    catch(...)
    {
    	bResult = false;
    }

    return bResult;
}

/*!****************************************************************************
* @brief	Checks for file existence
* @param	strFileName The filename to check for
* @return	Returns true if the file exists, false otherwise
******************************************************************************/
bool FileExists(std::string strFileName)
{
	DWORD dwAttrib = GetFileAttributesA(strFileName.c_str());

	return bool(dwAttrib != INVALID_FILE_ATTRIBUTES &&
		 !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

/*!****************************************************************************
* @brief	Converts a string to lower case
* @param	strVal The string to convert
* @return	Returns the given string in lower case
******************************************************************************/
std::string LowerCase(std::string strVal)
{
    std::string strResult = strVal;
												// boost
    //boost::algorithm::to_lower(strResult);
												// stl
    strResult.resize(strVal.size());
    std::transform(strVal.begin(), strVal.end(), strResult.begin(), ::tolower);

	return strResult;
}

/*!****************************************************************************
* @brief	Converts a wide char (unicode) string to a regular string
* @param	wstrString The wide char string to convert
* @return	Returns the input wide char string as regular (multi byte) string
******************************************************************************/
std::string WideToString(std::wstring wstrString)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string strString = converter.to_bytes(wstrString);

	return strString;
}

};



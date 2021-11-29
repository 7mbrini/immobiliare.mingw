/*!****************************************************************************

	@file	assets.h
	@file	assets.cpp

	@brief	Assets modelling

	@noop	author:	Francesco Settembrini
	@noop	last update: 8/11/2021, 28/11/2021
	@noop	e-mail:	mailto:francesco.settembrini@poliba.it

******************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../sources/utils.h"
#include "../sources/sorting.h"
#include "../sources/assets.h"


//---------------------------------------------------------------------------

#define _USECUSTOMSORT

static const char MAGICWORD[ASSET_MAGICLEN] = "IMMOBILIARE-ASSETS-(C)2021-StudioWARE";


using namespace sort;



/*!****************************************************************************
* @brief	Constructor
******************************************************************************/
TAsset::TAsset()
{
	memset(m_strDescription, 0, ASSET_DESCRMAXLEN);
	memset(m_strAddress, 0, ASSET_NAMESMAXLEN);
	memset(m_strCity, 0, ASSET_NAMESMAXLEN);

    m_nStatus = asNone;
	m_nTypology = atNone;

	m_SoldDate = m_BuildDate = 0;
    m_nValue = m_nCap = m_nPrice = 0;
	//m_nFloor = m_nRooms = m_nBathrooms = m_nArea = 0;
	m_nRooms = m_nBathrooms = m_nArea = 0;

	m_bImage = false;
	memset(m_pImage, 0, ASSET_IMAGEMAXSIZE);
}

/*!****************************************************************************
* @brief	Return the record fields as a standard String
* @return	The string with record field descriptions
******************************************************************************/
std::string TAsset::AsString()
{
    char strResult[4096];

    sprintf(strResult,
    	"\nDescription: %s"
        "\nAddress: %s"
        "\nCity: %s"
        "\nCAP: %d"
        "\nTypology: %d"
        "\nStatus: %d"
        "\nRooms: %d"
		"\nBathrooms: %d"
        "\nArea: %d"
		"\nCadastral value: %d"
        "\nPrice: %d"
        "\nSold date: %f"
        "\nHave Image: %s",

		m_strDescription,
        m_strAddress,
        m_strCity,
        m_nCap,
        m_nTypology,
 		m_nStatus,
        m_nRooms,
        m_nBathrooms,
        m_nArea,
        m_nValue,
        m_nPrice,
        m_SoldDate,
        m_bImage ? "Yes" : "No"
    );

    return strResult;
}

/*!****************************************************************************
* @brief	Reads the record from file
* @param	fp Pointer to FILE struct
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TAsset::Read(FILE* fp)
{
	assert(fp);

    return fread(this, sizeof(*this), 1, fp);
}

/*!****************************************************************************
* @brief	Writes the record to file
* @param	fp Pointer to FILE struct
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TAsset::Write(FILE* fp)
{
	assert(fp);

	return fwrite(this, sizeof(*this), 1, fp);
}

/*!****************************************************************************
* @brief	Constructor
******************************************************************************/
TAssetsArchive::TAssetsArchive()
{
	;
}

/*!****************************************************************************
* @brief	Destructor
******************************************************************************/
TAssetsArchive::~TAssetsArchive()
{
	Clear();
}

/*!****************************************************************************
* @brief	Loads archives from file
* @param	strFileName The file name for Assets archives
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TAssetsArchive::LoadFromFile(std::string strFileName)
{
	bool bResult = false;

    FILE* pFile = fopen(strFileName.c_str(), "rb");

    if( pFile )
    {
		Clear();

		TFileHeader Header;
        memset(&Header, 0, sizeof(Header));

        fread(&Header, sizeof(Header), 1, pFile);

		//if( strcmpi(Header.pMagic, MAGICWORD) )
		if( _strcmpi(Header.pMagic, MAGICWORD) )
        {
			fclose(pFile);
			bResult = false;
        }
		else
        {
			for(int i=0; i<Header.nRecords; i++)
            {
                TAsset *pAsset = new TAsset;
                assert(pAsset);
                pAsset->Read(pFile);
                Add(pAsset);
            }

            fclose(pFile);
            bResult = true;
		}
    }

    return bResult;
}

/*!****************************************************************************
* @brief	Saves archives to file
* @param	strFileName The file name for Assets archives
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TAssetsArchive::SaveToFile(std::string strFileName)
{
	bool bResult = false;

	FILE *pFile = fopen(strFileName.c_str(), "wb");

    if( pFile )
    {
        TFileHeader Header;
        memset(&Header, 0, sizeof(Header));
        strcpy(Header.pMagic, MAGICWORD);
        Header.nRecords = m_PtrAssets.size();
        fwrite(&Header, sizeof(Header), 1, pFile);

        for(unsigned i=0; i<m_PtrAssets.size(); i++)
        {
            m_PtrAssets[i]->Write(pFile);
        }

        fclose(pFile);
        bResult = true;
	}

    return bResult;
}

/*!****************************************************************************
* @brief	Clears the archive
******************************************************************************/
void TAssetsArchive::Clear()
{
	for(unsigned i=0; i<m_PtrAssets.size(); i++)
    {
		delete m_PtrAssets[i];
    }

	m_PtrAssets.clear();
}

/*!****************************************************************************
* @brief	Adds a record to the archive
******************************************************************************/
void TAssetsArchive::Add(TAsset* pAsset)
{
	assert(pAsset);

	m_PtrAssets.push_back(pAsset);
}

/*!****************************************************************************
* @brief	Deletes a record from the archive
******************************************************************************/
void TAssetsArchive::Delete(unsigned nIndex)
{
	if( (nIndex >= 0) && (nIndex < m_PtrAssets.size()) )
    {
		assert(m_PtrAssets[nIndex]);
        delete m_PtrAssets[nIndex];

		m_PtrAssets.erase( m_PtrAssets.begin() + nIndex );
    }
}

/*!****************************************************************************
* @brief	Updates a record of the archive
* @param	nIndex The position of the record in the archive
* @param	Asset The Asset record
******************************************************************************/
void TAssetsArchive::Update(unsigned nIndex, TAsset const& Asset)
{
	if( (nIndex >= 0) && (nIndex < m_PtrAssets.size()) )
    {
		*(m_PtrAssets[nIndex]) = Asset;
    }
}

/*!****************************************************************************
* @brief	Gets a record corresponding to a given index in the archive
* @param	nId The position of the record in the archive
* @return	Returns a pointer to an Asset object
******************************************************************************/
TAsset* const TAssetsArchive::GetRecord(unsigned nId)
{
	TAsset *pAsset = NULL;

	if( nId >=0 && nId < m_PtrAssets.size() )
    {
		pAsset = m_PtrAssets[nId];
    }

    return pAsset;
}

/*!****************************************************************************
* @brief	Gets the count of the assets contained in the archive
* @return	Returns the count of Assets in the archive
******************************************************************************/
unsigned TAssetsArchive::GetCount()
{
	return m_PtrAssets.size();
}

/*!****************************************************************************
* @brief	Gets the Assets contained in the archive
* @return	Returns a vector of pointers to the Assets
******************************************************************************/
TVecPtrAssets TAssetsArchive::GetAssets()
{
	return m_PtrAssets;
}

/*!****************************************************************************
* @brief	Gets the position in the archive corresponding to a specified Asset
* @param	pAsset Pointer to an Asset object
* @param	nId Reference for the position of pAsset in the archive
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TAssetsArchive::GetRecordId(TAsset* pAsset, unsigned& nId)
{
	bool bResult = false;

	for(unsigned i=0; i<m_PtrAssets.size(); i++)
    {
		if( m_PtrAssets[i] == pAsset )
        {
        	nId = i;

            bResult = true;
            break;
        }
    }

    return bResult;
}

/*!****************************************************************************
* @brief	Sorts a vector of Assets objects by "city" field
* @param	PtrAssets Reference to a vector of pointers to Assets
* @param	bAsc Flag specifying the sorting type, true for ascending
******************************************************************************/
void SortByCity(TVecPtrAssets& PtrAssets, bool bAsc)
{
	if( PtrAssets.size() )
    {
        std::vector<TStringSort> Temp;

        for(unsigned i=0; i<PtrAssets.size(); i++)
        {
			Temp.push_back(TStringSort(PtrAssets[i]->m_strCity, (void*) PtrAssets[i]));
        }

#ifdef _USECUSTOMSORT
		sort::Sort(&Temp[0], Temp.size());
#else
        std::sort(Temp.begin(), Temp.end());
#endif

        assert(Temp.size() == PtrAssets.size());

        TVecPtrAssets TempPtrAssets = PtrAssets;


        for(unsigned i=0; i<Temp.size(); i++)
        {
            PtrAssets[i] = static_cast<TAsset*>(Temp[i].m_pPtr);
        }

        if( !bAsc ) std::reverse(PtrAssets.begin(), PtrAssets.end());
	}
}

/*!****************************************************************************
* @brief	Sorts a vector of Assets object by "value" field
* @param	PtrAssets Reference to a vector of pointers to Assets
* @param	bAsc Flag specifying the sorting type, true for ascending ordering
******************************************************************************/
void SortByValue(TVecPtrAssets& PtrAssets, bool bAsc)
{
	if( PtrAssets.size() )
    {
        std::vector<TIntegerSort> Temp;

        for(unsigned i=0; i<PtrAssets.size(); i++)
        {
			Temp.push_back(TIntegerSort(PtrAssets[i]->m_nValue, (void*) PtrAssets[i]));
        }

#ifdef _USECUSTOMSORT
		sort::Sort(&Temp[0], Temp.size());
#else
        std::sort(Temp.begin(), Temp.end());
#endif

        assert(Temp.size() == PtrAssets.size());

        TVecPtrAssets TempPtrAssets = PtrAssets;

        for(unsigned int i=0; i<Temp.size(); i++)
        {
            PtrAssets[i] = static_cast<TAsset*>(Temp[i].m_pPtr);
        }

        if( !bAsc ) std::reverse(PtrAssets.begin(), PtrAssets.end());
	}
}

/*!****************************************************************************
* @brief	Sorts a vector of Assets object by "price" field
* @param	PtrAssets Reference to a vector of pointers to Assets
* @param	bAsc Flag specifying the sorting type, true for ascending ordering
******************************************************************************/
void SortByPrice(TVecPtrAssets& PtrAssets, bool bAsc)
{
	if( PtrAssets.size() )
    {
        std::vector<TIntegerSort> Temp;

        for(unsigned int i=0; i<PtrAssets.size(); i++)
        {
			Temp.push_back(TIntegerSort(PtrAssets[i]->m_nPrice, (void*) PtrAssets[i]));
        }

#ifdef _USECUSTOMSORT
		sort::Sort(&Temp[0], Temp.size());
#else
        std::sort(Temp.begin(), Temp.end());
#endif

        assert(Temp.size() == PtrAssets.size());

        TVecPtrAssets TempPtrAssets = PtrAssets;

        for(unsigned int i=0; i<Temp.size(); i++)
        {
            PtrAssets[i] = static_cast<TAsset*>(Temp[i].m_pPtr);
        }

        if( !bAsc ) std::reverse(PtrAssets.begin(), PtrAssets.end());
	}
}

/*!****************************************************************************
* @brief	Sorts a vector of Assets object by "area" field
* @param	PtrAssets Reference to a vector of pointers to Assets
* @param	bAsc Flag specifying the sorting type, true for ascending ordering
******************************************************************************/
void SortByArea(TVecPtrAssets& PtrAssets, bool bAsc)
{
	if( PtrAssets.size() )
    {
        std::vector<TIntegerSort> Temp;

        for(unsigned int i=0; i<PtrAssets.size(); i++)
        {
			Temp.push_back(TIntegerSort(PtrAssets[i]->m_nArea, (void*) PtrAssets[i]));
        }

#ifdef _USECUSTOMSORT
		sort::Sort(&Temp[0], Temp.size());
#else
        std::sort(Temp.begin(), Temp.end());
#endif

        assert(Temp.size() == PtrAssets.size());

        TVecPtrAssets TempPtrAssets = PtrAssets;

        for(unsigned int i=0; i<Temp.size(); i++)
        {
            PtrAssets[i] = static_cast<TAsset*>(Temp[i].m_pPtr);
        }

        if( !bAsc ) std::reverse(PtrAssets.begin(), PtrAssets.end());
	}
}

/*!****************************************************************************
* @brief	Filters a vector of Assets object by "status" field
* @param	Assets Reference to a vector of pointers to Assets
* @param	nStatus Status enumeration specifier
******************************************************************************/
void FilterByStatus(TVecPtrAssets& Assets, enAssetStatus nStatus)
{
    TVecPtrAssets TempQuery = Assets;
    Assets.clear();

    for(unsigned int i=0; i<TempQuery.size(); i++)
    {
        if( TempQuery[i]->m_nStatus == nStatus )
        {
            Assets.push_back(TempQuery[i]);
        }
    }
}

/*!****************************************************************************
* @brief	Filters a vector of Assets object by "typology" field
* @param	Assets Reference to a vector of pointers to Assets
* @param	nTypology Typology enumeration specifier
******************************************************************************/
void FilterByTypology(TVecPtrAssets& Assets, enAssetTypology nTypology)
{
    TVecPtrAssets TempQuery = Assets;

    Assets.clear();

    for(unsigned int i=0; i<TempQuery.size(); i++)
    {
        if( TempQuery[i]->m_nTypology == nTypology )
        {
            Assets.push_back(TempQuery[i]);
        }
    }
}

/*!****************************************************************************
* @brief	Filters a vector of Assets object by "city" field
* @param	Assets Reference to a vector of pointers to Assets
* @param	strCityName String to search for
* @param	bFullMatch Flag specifying a full match to search for
******************************************************************************/
void FilterByCity(TVecPtrAssets& Assets, std::string strCityName, bool bFullMatch)
{
    TVecPtrAssets TempQuery = Assets;

    Assets.clear();

	if( bFullMatch )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( utils::LowerCase(std::string(TempQuery[i]->m_strCity)) == utils::LowerCase(strCityName) )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
    }
    else
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( utils::LowerCase(std::string(TempQuery[i]->m_strCity)).find( utils::LowerCase(strCityName) ) )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
}

/*!****************************************************************************
* @brief	Filters a vector of Assets object by "address" field
* @param	Assets Reference to a vector of pointers to Assets
* @param	strAddress String to search for
* @param	bFullMatch Flag specifying a full match to search for
* ******************************************************************************/
void FilterByAddress(TVecPtrAssets& Assets, std::string strAddress, bool bFullMatch)
{
    TVecPtrAssets TempQuery = Assets;
    Assets.clear();

	if( bFullMatch )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( utils::LowerCase(std::string(TempQuery[i]->m_strAddress)) == utils::LowerCase(strAddress) )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
    }
    else
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( utils::LowerCase(std::string(TempQuery[i]->m_strAddress)).find( utils::LowerCase(strAddress) ) )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
}

/*!****************************************************************************
* @brief	Filters a vector of Assets object by "date" field
* @param	Assets Reference to a vector of pointers to Assets
* @param	Date Date to searching for
* @param	strIneq String specifying the searching criteria
* note		Date is coded as a double type, zero corresponding to 31/12/1899
******************************************************************************/
void FilterByBuildDate(TVecPtrAssets& Assets, double Date, std::string strIneq)
{
    TVecPtrAssets TempQuery = Assets;

    Assets.clear();

    if( strIneq == "=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_BuildDate == Date)
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == ">=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_BuildDate >= Date)
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == "<=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_BuildDate <= Date)
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
}

/*!****************************************************************************
* @brief	Filters a vector of Assets object by "epgl" field
* @param	Assets Reference to a vector of pointers to Assets
* @param	nEpgl Enumerated value for Epgl
* @param	strIneq String specifying the searching criteria
******************************************************************************/
void FilterByEpgl(TVecPtrAssets& Assets, enAssetEpgl nEpgl, std::string strIneq)
{
    TVecPtrAssets TempQuery = Assets;

    Assets.clear();

    if( strIneq == "=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nEpgl == nEpgl )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == ">=" )
    {
		for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nEpgl >= nEpgl )
            {
                Assets.push_back(TempQuery[i]);
            }
		}
    }
    else if( strIneq == "<=" )
    {
    	for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nEpgl <= nEpgl )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
    }
}

/*!****************************************************************************
* @brief	Filters a vector of Assets object by "value" field
* @param	Assets Reference to a vector of pointers to Assets
* @param	nValue The value for the Asset
* @param	strIneq String specifying the searching criteria
******************************************************************************/
void FilterByValue(TVecPtrAssets& Assets, unsigned nValue, std::string strIneq)
{
    TVecPtrAssets TempQuery = Assets;
    Assets.clear();

    if( strIneq == "=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nValue == nValue )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == ">=" )
	{
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nValue >= nValue )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == "<=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nValue <= nValue )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
    }
}

/*!****************************************************************************
* @brief	Filters a vector of Assets object by "price" field
* @param	Assets Reference to a vector of pointers to Assets
* @param	nPrice The price for the Asset
* @param	strIneq String specifying the searching criteria
******************************************************************************/
void FilterByPrice(TVecPtrAssets& Assets, unsigned nPrice, std::string strIneq)
{
    TVecPtrAssets TempQuery = Assets;
    Assets.clear();

    if( strIneq == "=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nPrice == nPrice )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == ">=" )
	{
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nPrice >= nPrice )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == "<=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nPrice <= nPrice )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
    }
}

/*!****************************************************************************
* @brief	Filters a vector of Assets object by "rooms" field
* @param	Assets Reference to a vector of pointers to Assets
* @param	nRooms The number of rooms to search for
* @param	strIneq String specifying the searching criteria
******************************************************************************/
void FilterByRooms(TVecPtrAssets& Assets, unsigned nRooms, std::string strIneq)
{
    TVecPtrAssets TempQuery = Assets;
    Assets.clear();

    if( strIneq == "=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nRooms == nRooms )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == ">=" )
	{
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nRooms >= nRooms )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == "<=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nRooms <= nRooms )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
    }
}

/*!****************************************************************************
* @brief	Filters a vector of Assets object by "bathrooms" field
* @param	Assets Reference to a vector of pointers to Assets
* @param	nBathrooms The number of bathrooms to search for
* @param	strIneq String specifying the searching criteria
******************************************************************************/
void FilterByBathrooms(TVecPtrAssets& Assets, unsigned nBathrooms, std::string strIneq)
{
    TVecPtrAssets TempQuery = Assets;
    Assets.clear();

    if( strIneq == "=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nBathrooms == nBathrooms )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == ">=" )
	{
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nBathrooms >= nBathrooms )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == "<=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nBathrooms <= nBathrooms )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
    }
}

/*!****************************************************************************
* @brief	Filters a vector of Assets object by "area" field
* @param	Assets Reference to a vector of pointers to Assets
* @param	nArea The area to search for
* @param	strIneq String specifying the searching criteria
******************************************************************************/
void FilterByArea(TVecPtrAssets& Assets, unsigned nArea, std::string strIneq)
{
    TVecPtrAssets TempQuery = Assets;
    Assets.clear();

    if( strIneq == "=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nArea == nArea )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == ">=" )
	{
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nArea >= nArea )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == "<=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nArea <= nArea )
            {
                Assets.push_back(TempQuery[i]);
            }
        }
    }
}

/*!****************************************************************************
* @brief	Facility function for Epgl enumerations conversion
* @param	nEpgl Enumeration for EPgl (Global Energy Performance)
* @return	Returns the string corresponding to the Egpl enumeration
******************************************************************************/
std::string AsString(enAssetEpgl nEpgl)
{
	std::string strEpgl[] =
    	{ "none", "G", "F", "E", "D", "C", "B", "A4", "A3", "A2", "A1" };

    return strEpgl[nEpgl];
}

/*!****************************************************************************
* @brief	Facility function for Status enumerations conversion
* @param	nStatus Enumeration for Assets status
* @return	Returns the string corresponding to the Status enumeration
******************************************************************************/
std::string AsString(enAssetStatus nStatus)
{
	std::string strStatus[] =
    	{ "none", "for rent", "rented", "for sale", "sold out" };

    return strStatus[nStatus];
}



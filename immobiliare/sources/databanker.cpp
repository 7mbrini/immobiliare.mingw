/*!****************************************************************************

	@file	databanker.h
	@file	databanker.cpp

	@brief	Database read/write routines

	@noop	author:	Francesco Settembrini
	@noop	last update: 08/11/2021, 28/11/2021
	@noop	e-mail:	mailto:francesco.settembrini@poliba.it

******************************************************************************/

//#include <vcl.h>
//#pragma hdrstop
#include <assert.h>

#include "../sources/utils.h"
#include "../sources/databanker.h"
#include "../sources/commdefs.h"

//---------------------------------------------------------------------------
//#pragma package(smart_init)


/*!****************************************************************************
* @brief	Constructor
******************************************************************************/
TDataBanker::TDataBanker()
{
	m_pCities = NULL;
    m_pAssets = NULL;
    m_pCustomers = NULL;
}

/*!****************************************************************************
* @brief	Destructor
******************************************************************************/
TDataBanker::~TDataBanker()
{
    if( m_pCities ) delete m_pCities;
	if( m_pAssets ) delete m_pAssets;
    if( m_pCustomers ) delete m_pCustomers;
}

/*!****************************************************************************
* @brief	Creates an empty Cities archive
******************************************************************************/
void TDataBanker::CitiesCreateArchive()
{
	if( m_pCities ) delete m_pCities;

    m_pCities = new TCitiesArchive();
    assert(m_pCities);
}

/*!****************************************************************************
* @brief	Creates an empty Assets archive
******************************************************************************/
void TDataBanker::AssetsCreateArchive()
{
	if( m_pAssets ) delete m_pAssets;

	m_pAssets = new TAssetsArchive();
    assert(m_pAssets);
}

/*!****************************************************************************
* @brief	Creates an empty Customers archive
******************************************************************************/
void TDataBanker::CustomersCreateArchive()
{
	if( m_pCustomers ) delete m_pCustomers;

	m_pCustomers = new TCustomersArchive();
    assert(m_pCustomers);
}

/*!****************************************************************************
* @brief	Gets the Cities contained in the archive
* @return	Returns a pointer to the Cities vector
******************************************************************************/
TCitiesArchive* const TDataBanker::GetCities()
{
	return m_pCities;
}

/*!****************************************************************************
* @brief	Gets the Cities contained in the archive
* @param	Cities Reference to a Cities vector
******************************************************************************/
void TDataBanker::GetCities(TVecCities& Cities)
{
	assert(m_pCities);

    m_pCities->GetCities(Cities);
}

/*!****************************************************************************
* @brief	Gets the Assets contained in the archive
* @return	Returns a pointer to the Assets vector
******************************************************************************/
TAssetsArchive* const TDataBanker::GetAssets()
{
	return m_pAssets;
}

/*!****************************************************************************
* @brief	Gets the Customers contained in the archive
* @return	Returns a pointer to the Customers vector
******************************************************************************/
TCustomersArchive* const TDataBanker::GetCustomers()
{
	return m_pCustomers;
}

/*!****************************************************************************
* @brief	Load from file a Cities archive
* @param	strFileName The file name for Cities archive
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TDataBanker::CitiesLoadFromFile(std::string strFileName)
{
	if( m_pCities ) delete m_pCities;

    m_pCities = new TCitiesArchive();
    assert(m_pCities);

	return m_pCities->LoadFromFile(strFileName);
}

/*!****************************************************************************
* @brief	Load from file an Assets archive
* @param	strFileName The file name for Assets archive
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TDataBanker::AssetsLoadFromFile(std::string strFileName)
{
	if( m_pAssets ) delete m_pAssets;

    m_pAssets = new TAssetsArchive();
    assert(m_pAssets);

    return m_pAssets->LoadFromFile(strFileName);
}

/*!****************************************************************************
* @brief	Load from file an Customers archive
* @param	strFileName The file name for Customers archive
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TDataBanker::CustomersLoadFromFile(std::string strFileName)
{
	if( m_pCustomers ) delete m_pCustomers;

    m_pCustomers = new TCustomersArchive();
    assert(m_pCustomers);

    return m_pCustomers->LoadFromFile(strFileName);
}

/*!****************************************************************************
* @brief	Saves to file an Assets archive
* @param	strFileName The file name for Assets archive
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TDataBanker::AssetsSaveToFile(std::string strFileName)
{
	bool bResult = false;

	if( m_pAssets )
    {
		bResult = m_pAssets->SaveToFile(strFileName);
    }

    return bResult;
}

/*!****************************************************************************
* @brief	Saves to file an Customers archive
* @param	strFileName The file name for Customers archive
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TDataBanker::CustomersSaveToFile(std::string strFileName)
{
	bool bResult = false;

	if( m_pCustomers )
    {
    	bResult = m_pCustomers->SaveToFile(strFileName);
    }

    return bResult;
}

/*!****************************************************************************
* @brief	Checks for Cities archive emptiness
* @return	Returns true if Cities archive is not empty, false otherwise
******************************************************************************/
bool TDataBanker::HaveCities()
{
	bool bResult = false;

    if( m_pCities)
    {
    	if( m_pCities->GetCount() )
        {
			bResult = true;
        }
    }

    return bResult;
}

/*!****************************************************************************
* @brief	Checks for Assets archive emptiness
* @return	Returns true if Assets archive is not empty, false otherwise
******************************************************************************/
bool TDataBanker::HaveAssets()
{
	bool bResult = false;

    if( m_pAssets )
    {
    	if( m_pAssets->GetCount() )
        {
        	bResult = true;
        }
    }

    return bResult;
}

/*!****************************************************************************
* @brief	Checks for Customers archive emptiness
* @return	Returns true if Customers archive is not empty, false otherwise
******************************************************************************/
bool TDataBanker::HaveCustomers()
{
	bool bResult = false;

    if( m_pCustomers )
    {
    	if( m_pCustomers->GetCount() )
        {
        	bResult = true;
        }
    }

    return bResult;
}




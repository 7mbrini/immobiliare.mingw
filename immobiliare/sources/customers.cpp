/*!****************************************************************************

	@file	customers.h
	@file	customers.cpp

	@brief	Customers modelling

	@noop	author:	Francesco Settembrini
	@noop	last update: 08/11/2021, 28/11/2021
	@noop	e-mail:	mailto:francesco.settembrini@poliba.it

******************************************************************************/

//#include <vcl.h>
//#pragma hdrstop

#include <assert.h>
#include <string.h>

#include "../sources/utils.h"
#include "../sources/sorting.h"
#include "../sources/customers.h"

//---------------------------------------------------------------------------
//#pragma package(smart_init)


static const char MAGICWORD[CUSTOMER_MAGICLEN] = "IMMOBILIARE-CUSTOMERS-(C)2021-StudioWARE";

using namespace sort;


/*!****************************************************************************
* @brief	Constructor
******************************************************************************/
TCustomer::TCustomer()
{
    m_nCap = 0;
    m_nBudget = 0;
	m_nOwnership = cotNone;
    memset(m_strFirstName, 0, CUSTOMER_NAMESMAXLEN);
    memset(m_strLastName, 0, CUSTOMER_NAMESMAXLEN);
	memset(m_strAddress, 0, CUSTOMER_NAMESMAXLEN);
	memset(m_strCity, 0, CUSTOMER_NAMESMAXLEN);
    memset(m_strEmail, 0, CUSTOMER_NAMESMAXLEN);
    memset(m_strPhone, 0, CUSTOMER_NAMESMAXLEN);
}

/*!****************************************************************************
* @brief	Return the record fields as a standard String
* @return	The string with record field descriptions
******************************************************************************/
std::string TCustomer::AsString()
{
    char strResult[4096];

    sprintf(strResult,
    	"\nFirst Name: %s"
        "\nLast Name: %s"
        "\nAddress: %s"
        "\nCity: %s"
        "\nCAP: %d"
        "\nEmail: %s"
        "\nPhone: %s"
        "\nBudget: %d"
        "\nOwnership: %d",

		m_strFirstName,
        m_strLastName,
        m_strAddress,
        m_strCity,
        m_nCap,
        m_strEmail,
        m_strPhone,
        m_nBudget,
        m_nOwnership
    );

    return strResult;
}

/*!****************************************************************************
* @brief	Reads the record from file
* @param	fp Pointer to FILE struct
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TCustomer::Read(FILE* fp)
{
	assert(fp);

    return fread(this, sizeof(*this), 1, fp);
}

/*!****************************************************************************
* @brief	Writes the record to file
* @param	fp Pointer to FILE struct
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TCustomer::Write(FILE* fp)
{
	assert(fp);

	return fwrite(this, sizeof(*this), 1, fp);
}


/*!****************************************************************************
* @brief	Constructor
******************************************************************************/
TCustomersArchive::TCustomersArchive()
{
	;
}

/*!****************************************************************************
* @brief	Destructor
******************************************************************************/
TCustomersArchive::~TCustomersArchive()
{
	Clear();
}

/*!****************************************************************************
* @brief	Loads archives from file
* @param	strFileName The file name for Customers archives
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TCustomersArchive::LoadFromFile(std::string strFileName)
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
			for(unsigned int i=0; i<Header.nRecords; i++)
            {
                TCustomer* pCustomer = new TCustomer;
                assert(pCustomer);

				pCustomer->Read(pFile);
                m_PtrCustomers.push_back(pCustomer);
            }

            fclose(pFile);
            bResult = true;
		}
    }

    return bResult;
}

/*!****************************************************************************
* @brief	Saves archives to file
* @param	strFileName The file name for Customers archives
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TCustomersArchive::SaveToFile(std::string strFileName)
{
	bool bResult = false;

	FILE *pFile = fopen(strFileName.c_str(), "wb");

    if( pFile )
    {
        TFileHeader Header;
        memset(&Header, 0, sizeof(Header));
        strcpy(Header.pMagic, MAGICWORD);
        Header.nRecords = m_PtrCustomers.size();
        fwrite(&Header, sizeof(Header), 1, pFile);

        for(unsigned i=0; i<m_PtrCustomers.size(); i++)
        {
            m_PtrCustomers[i]->Write(pFile);
        }

        fclose(pFile);
        bResult = true;
	}

    return bResult;
}

/*!****************************************************************************
* @brief	Clears the archive
******************************************************************************/
void TCustomersArchive::Clear()
{
    for(unsigned i=0; i<m_PtrCustomers.size(); i++)
    {
    	assert(m_PtrCustomers[i]);
        delete m_PtrCustomers[i];
    }

    m_PtrCustomers.clear();
}

/*!****************************************************************************
* @brief	Adds a record to the archive
******************************************************************************/
void TCustomersArchive::Add(TCustomer *pCustomer)
{
	assert(pCustomer);

	m_PtrCustomers.push_back(pCustomer);
}

/*!****************************************************************************
* @brief	Deletes a record from the archive
* @param	nIndex The index of the record to delete
******************************************************************************/
void TCustomersArchive::Delete(unsigned nIndex)
{
	if( (nIndex >= 0) && (nIndex < m_PtrCustomers.size()) )
    {
		assert(m_PtrCustomers[nIndex]);
        delete m_PtrCustomers[nIndex];

		m_PtrCustomers.erase( m_PtrCustomers.begin() + nIndex );
    }
}

/*!****************************************************************************
* @brief	Updates a record of the archive
* @param	nIndex The position of the record in the archive
* @param	Customer The Customer record
******************************************************************************/
void TCustomersArchive::Update(unsigned nIndex, TCustomer const& Customer)
{
	if( (nIndex >= 0) && (nIndex < m_PtrCustomers.size()) )
    {
		*m_PtrCustomers[nIndex] = Customer;
    }
}

/*!****************************************************************************
* @brief	Gets a record corresponding to a given index in the archive
* @param	nId The position of the record in the archive
* @return	Returns a pointer to an Customers object
******************************************************************************/
TCustomer* TCustomersArchive::GetRecord(unsigned nId)
{
	TCustomer* pCustomer = NULL;

    if( nId >= 0 && nId < m_PtrCustomers.size() )
    {
    	pCustomer = m_PtrCustomers[nId];
    }

    return pCustomer;
}

/*!****************************************************************************
Returns the count of Assets in the archive
******************************************************************************/
int TCustomersArchive::GetCount()
{
	//return m_Customers.size();
    return m_PtrCustomers.size();
}

/*!****************************************************************************
* @brief	Gets the Customers contained in the archive
* @return	Returns a vector of pointers to the Customers
******************************************************************************/
TVecPtrCustomers TCustomersArchive::GetCustomers()
{
	return m_PtrCustomers;
}

/*!****************************************************************************
* @brief	Gets the position in the archive corresponding
* 			to a specified Customer.
* @param	pCustomer Pointer to an Customer object
* @param	nId Reference for the position of pCustomer in the archive
* @return	Returns true for success, false otherwise
******************************************************************************/
bool TCustomersArchive::GetRecordId(TCustomer* pCustomer, unsigned& nId)
{
	bool bResult = false;

	for(unsigned int i=0; i<m_PtrCustomers.size(); i++)
    {
		if( m_PtrCustomers[i] == pCustomer )
        {
        	nId = i;

            bResult = true;
            break;
        }
    }

    return bResult;
}

/*!****************************************************************************
* @brief	Sorts a vector of Customer objects by "first name" field
* @param	PtrCustomers Reference to a vector of pointers to Customers
* @param	bAsc Flag specifying the sorting type, true for ascending
******************************************************************************/
void SortByFirstName(TVecPtrCustomers& PtrCustomers, bool bAsc)
{
	if( PtrCustomers.size() )
    {
        std::vector<TStringSort> Temp;

        for(unsigned int i=0; i<PtrCustomers.size(); i++)
        {
			Temp.push_back(TStringSort(PtrCustomers[i]->m_strFirstName, (void*) PtrCustomers[i]));
        }

#ifdef _USECUSTOMSORT
		sort::Sort(&Temp[0], Temp.size());
#else
        std::sort(Temp.begin(), Temp.end());
#endif

        assert(Temp.size() == PtrCustomers.size());

        TVecPtrCustomers TempPtrCustomers = PtrCustomers;


        for(unsigned int i=0; i<Temp.size(); i++)
        {
            PtrCustomers[i] = static_cast<TCustomer*>(Temp[i].m_pPtr);
        }

        if( !bAsc ) std::reverse(PtrCustomers.begin(), PtrCustomers.end());
	}
}

/*!****************************************************************************
* @brief	Sorts a vector of Customer objects by "last name" field
* @param	PtrCustomers Reference to a vector of pointers to Customers
* @param	bAsc Flag specifying the sorting type, true for ascending
******************************************************************************/
void SortByLastName(TVecPtrCustomers& PtrCustomers, bool bAsc)
{
	if( PtrCustomers.size() )
    {
        std::vector<TStringSort> Temp;

        for(unsigned int i=0; i<PtrCustomers.size(); i++)
        {
			Temp.push_back(TStringSort(PtrCustomers[i]->m_strLastName, (void*) PtrCustomers[i]));
        }

#ifdef _USECUSTOMSORT
		sort::Sort(&Temp[0], Temp.size());
#else
        std::sort(Temp.begin(), Temp.end());
#endif

        assert(Temp.size() == PtrCustomers.size());

        TVecPtrCustomers TempPtrCustomers = PtrCustomers;


        for(unsigned int i=0; i<Temp.size(); i++)
        {
            PtrCustomers[i] = static_cast<TCustomer*>(Temp[i].m_pPtr);
        }

        if( !bAsc ) std::reverse(PtrCustomers.begin(), PtrCustomers.end());
	}
}

/*!****************************************************************************
* @brief	Sorts a vector of Customer objects by "city" field
* @param	PtrCustomers Reference to a vector of pointers to Customers
* @param	bAsc Flag specifying the sorting type, true for ascending
******************************************************************************/
void SortByCity(TVecPtrCustomers& PtrCustomers, bool bAsc)
{
	if( PtrCustomers.size() )
    {
        std::vector<TStringSort> Temp;

        for(unsigned int i=0; i<PtrCustomers.size(); i++)
        {
			Temp.push_back(TStringSort(PtrCustomers[i]->m_strCity, (void*) PtrCustomers[i]));
        }

#ifdef _USECUSTOMSORT
		sort::Sort(&Temp[0], Temp.size());
#else
        std::sort(Temp.begin(), Temp.end());
#endif

        assert(Temp.size() == PtrCustomers.size());

        TVecPtrCustomers TempPtrCustomers = PtrCustomers;


        for(unsigned int i=0; i<Temp.size(); i++)
        {
            PtrCustomers[i] = static_cast<TCustomer*>(Temp[i].m_pPtr);
        }

        if( !bAsc ) std::reverse(PtrCustomers.begin(), PtrCustomers.end());
	}
}

/*!****************************************************************************
* @brief	Sorts a vector of Customer objects by "budget" field
* @param	PtrCustomers Reference to a vector of pointers to Customers
* @param	bAsc Flag specifying the sorting type, true for ascending
******************************************************************************/
void SortByBudget(TVecPtrCustomers& PtrCustomers, bool bAsc)
{
	if( PtrCustomers.size() )
    {
        std::vector<TIntegerSort> Temp;

        for(unsigned int i=0; i<PtrCustomers.size(); i++)
        {
			Temp.push_back(TIntegerSort(PtrCustomers[i]->m_nBudget, (void*) PtrCustomers[i]));
        }

#ifdef _USECUSTOMSORT
		sort::Sort(&Temp[0], Temp.size());
#else
        std::sort(Temp.begin(), Temp.end());
#endif

        assert(Temp.size() == PtrCustomers.size());

        TVecPtrCustomers TempPtrCustomers = PtrCustomers;

        for(unsigned int i=0; i<Temp.size(); i++)
        {
            PtrCustomers[i] = static_cast<TCustomer*>(Temp[i].m_pPtr);
        }

        if( !bAsc ) std::reverse(PtrCustomers.begin(), PtrCustomers.end());
	}
}

/*!****************************************************************************
* @brief	Filters a vector of Customers object by "first name" field
* @param	Customers Reference to a vector of pointers to Customers
* @param	strFirstName String to search for
* @param	bFullMatch Flag specifying a full match to search for
******************************************************************************/
void FilterByFirstName(TVecPtrCustomers& Customers,
	std::string strFirstName, bool bFullMatch)
{
    TVecPtrCustomers TempQuery = Customers;
    Customers.clear();

	if( bFullMatch )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( utils::LowerCase(std::string(TempQuery[i]->m_strFirstName))
            	== utils::LowerCase(strFirstName) )
            {
                Customers.push_back(TempQuery[i]);
            }
        }
    }
    else
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( utils::LowerCase(std::string(TempQuery[i]->m_strFirstName)).find( utils::LowerCase(strFirstName) ) )
            {
                Customers.push_back(TempQuery[i]);
            }
        }
	}
}

/*!****************************************************************************
* @brief	Filters a vector of Customers object by "last name" field
* @param	Customers Reference to a vector of pointers to Customers
* @param	strLastName String to search for
* @param	bFullMatch Flag specifying a full match to search for
******************************************************************************/
void FilterByLastName(TVecPtrCustomers& Customers, std::string strLastName, bool bFullMatch)
{
    TVecPtrCustomers TempQuery = Customers;
    Customers.clear();

	if( bFullMatch )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( utils::LowerCase(std::string(TempQuery[i]->m_strLastName)) == utils::LowerCase(strLastName) )
            {
                Customers.push_back(TempQuery[i]);
            }
        }
    }
    else
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( utils::LowerCase(std::string(TempQuery[i]->m_strLastName)).find( utils::LowerCase(strLastName) ) )
            {
                Customers.push_back(TempQuery[i]);
            }
        }
	}
}

/*!****************************************************************************
* @brief	Filters a vector of Customers object by "city" field
* @param	Customers Reference to a vector of pointers to Customers
* @param	strCity String to search for
* @param	bFullMatch Flag specifying a full match to search for
******************************************************************************/
void FilterByCity(TVecPtrCustomers& Customers, std::string strCity, bool bFullMatch)
{
    TVecPtrCustomers TempQuery = Customers;
    Customers.clear();

	if( bFullMatch )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( utils::LowerCase(std::string(TempQuery[i]->m_strCity)) == utils::LowerCase(strCity) )
            {
                Customers.push_back(TempQuery[i]);
            }
        }
    }
    else
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( utils::LowerCase(std::string(TempQuery[i]->m_strCity)).find( utils::LowerCase(strCity) ) )
            {
                Customers.push_back(TempQuery[i]);
            }
        }
	}
}

/*!****************************************************************************
* @brief	Filters a vector of Customers object by "ownership" field
* @param	Customers Reference to a vector of pointers to Customers
* @param	nOwnership Ownership enumerated type to match for
******************************************************************************/
void FilterByOwnership(TVecPtrCustomers& Customers, enCustomerOwnershipType nOwnership)
{
    TVecPtrCustomers TempQuery = Customers;

    Customers.clear();

    for(unsigned int i=0; i<TempQuery.size(); i++)
    {
        if( TempQuery[i]->m_nOwnership == nOwnership )
        {
            Customers.push_back(TempQuery[i]);
        }
    }
}

/*!****************************************************************************
* @brief	Filters a vector of Customers object by "budget" field
* @param	Customers Reference to a vector of pointers to Customers
* @param	nBudget The budget value to filter for
* @param	strIneq String specifying the searching criteria
******************************************************************************/
void FilterByBudget(TVecPtrCustomers& Customers, unsigned nBudget, std::string strIneq)
{
    TVecPtrCustomers TempQuery = Customers;

    Customers.clear();

    if( strIneq == "=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nBudget == nBudget )
            {
                Customers.push_back(TempQuery[i]);
            }
        }
	}
    else if( strIneq == ">=" )
	{
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nBudget >= nBudget )
            {
                Customers.push_back(TempQuery[i]);
            }
        }
    }
    else if( strIneq == "<=" )
    {
        for(unsigned int i=0; i<TempQuery.size(); i++)
        {
            if( TempQuery[i]->m_nBudget <= nBudget )
            {
                Customers.push_back(TempQuery[i]);
            }
        }
    }
}




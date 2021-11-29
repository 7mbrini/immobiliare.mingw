/******************************************************************************
	author:	Francesco Settembrini
	last update: 8/11/2021, 28/11/2021
	e-mail:	mailto:francesco.settembrini@poliba.it
******************************************************************************/

#ifndef customersH
#define customersH

#include <string>
#include <vector>
#include <list>

#define CUSTOMER_MINBUDGET		10
#define CUSTOMER_NAMESMINLEN	1
#define CUSTOMER_NAMESMAXLEN	50
#define CUSTOMER_MAGICLEN		64


enum enCustomerOwnershipType { cotNone=0, cotForRent, cotForPurchase };

class TCustomer;
typedef std::vector<TCustomer> TVecCustomers;
typedef std::vector<TCustomer*> TVecPtrCustomers;

class TCustomer
{
public:
	TCustomer();

public:
	bool Read(FILE* fp);
    bool Write(FILE* fp);

	std::string AsString();

public:
    unsigned m_nBudget, m_nCap;
    enum enCustomerOwnershipType m_nOwnership;
    char m_strFirstName[CUSTOMER_NAMESMAXLEN];
    char m_strLastName[CUSTOMER_NAMESMAXLEN];
	char m_strAddress[CUSTOMER_NAMESMAXLEN];
	char m_strCity[CUSTOMER_NAMESMAXLEN];
    char m_strEmail[CUSTOMER_NAMESMAXLEN];
    char m_strPhone[CUSTOMER_NAMESMAXLEN];
};

class TCustomersArchive
{
public:
	TCustomersArchive();
	~TCustomersArchive();

	void Clear();

    void Add(TCustomer *pCustomer);
    void Delete(unsigned nIndex);
    void Update(unsigned nIndex, TCustomer const& Customer);

    bool LoadFromFile(std::string strFileName);
    bool SaveToFile(std::string strFileName);

	int GetCount();

    TCustomer* GetRecord(unsigned nId);

    bool GetRecordId(TCustomer* pCustomer, unsigned& nId);

	TVecPtrCustomers GetCustomers();

protected:
	struct TFileHeader
    {
    	char pMagic[CUSTOMER_MAGICLEN];
        unsigned int nRecords;
    };

protected:
	//TVecCustomers m_Customers;
    TVecPtrCustomers m_PtrCustomers;

};

void FilterByFirstName(TVecPtrCustomers& Customers,
    std::string strFirstName, bool bFullMatch=true);
void FilterByLastName(TVecPtrCustomers& Customers,
    std::string strLastName, bool bFullMatch=true);
void FilterByCity(TVecPtrCustomers& Customers,
    std::string strCity, bool bFullMatch=true);
void FilterByOwnership(TVecPtrCustomers& Customers,
    enCustomerOwnershipType nType);
void FilterByBudget(TVecPtrCustomers& Customers,
    unsigned nBudget, std::string strIneq);

void SortByFirstName(TVecPtrCustomers& PtrCustomers, bool bAsc);
void SortByLastName(TVecPtrCustomers& PtrCustomers, bool bAsc);
void SortByCity(TVecPtrCustomers& PtrCustomers, bool bAsc);
void SortByBudget(TVecPtrCustomers& PtrCustomers, bool bAsc);

//---------------------------------------------------------------------------
#endif



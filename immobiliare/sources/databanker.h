/******************************************************************************
	author:	Francesco Settembrini
	last update: 8/11/2021, 28/11/2021
	e-mail:	mailto:francesco.settembrini@poliba.it
******************************************************************************/

#ifndef databankerH
#define databankerH

//#include <vcl.h>
//#pragma hdrstop

#include <string>

#include "../sources/assets.h"
#include "../sources/cities.h"
#include "../sources/customers.h"


class TDataBanker
{
public:
	TDataBanker();
	~TDataBanker();

	void CitiesCreateArchive();
    void AssetsCreateArchive();
    void CustomersCreateArchive();

    bool HaveCities();
	bool HaveAssets();
    bool HaveCustomers();

	TAssetsArchive* const GetAssets();
	TCustomersArchive* const GetCustomers();

	TCitiesArchive* const GetCities();
	void GetCities(TVecCities& Cities);

	bool CitiesLoadFromFile(std::string strFileName);
	bool AssetsLoadFromFile(std::string strFileName);
    bool CustomersLoadFromFile(std::string strFileName);

	bool AssetsSaveToFile(std::string strFileName);
    bool CustomersSaveToFile(std::string strFileName);

protected:
    TCitiesArchive* m_pCities;
    TAssetsArchive* m_pAssets;
	TCustomersArchive* m_pCustomers;
};

//---------------------------------------------------------------------------
#endif

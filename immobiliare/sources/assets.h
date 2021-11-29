/******************************************************************************
	author:	Francesco Settembrini
	last update: 8/11/2021, 28/11/2021
	e-mail:	mailto:francesco.settembrini@poliba.it
******************************************************************************/

#ifndef assetsH
#define assetsH

#include <vector>
#include <string>
#include <stdio.h>


#define ASSET_MINPRICE		10
#define ASSET_NAMESMINLEN	1
#define ASSET_NAMESMAXLEN	50
#define ASSET_MAGICLEN      64
#define ASSET_DESCRMAXLEN	(2<<10)	// max 2 KB for descriptions
#define ASSET_IMAGEMAXSIZE	(2<<14)	// max ~32 KB for jpeg images


enum enAssetStatus { asNone = 0, asForRent, asRented, asForSale, asSoldOut };
enum enAssetTypology { atNone = 0, atTerrain, atGarage, atVilla,
	atApartment, atOffice, atCommercial, atIndustrial };
enum enAssetEpgl { aeNone = 0, aeG, aeF, aeE, aeD, aeC, aeB, aeA4, aeA3, aeA2, aeA1 };

struct TAsset;
typedef std::vector<TAsset> TVecAssets;
typedef std::vector<TAsset*> TVecPtrAssets;


struct TAsset
{
public:
	TAsset();

public:
	bool Read(FILE* fp);
    bool Write(FILE* fp);

	std::string AsString();

public:
	char m_strAddress[ASSET_NAMESMAXLEN];
	char m_strCity[ASSET_NAMESMAXLEN];
	char m_strDescription[ASSET_DESCRMAXLEN];

	enAssetEpgl m_nEpgl;
	enAssetTypology m_nTypology;
	enAssetStatus m_nStatus;

    double m_BuildDate, m_SoldDate;

	unsigned m_nValue; // cadastral value
	unsigned m_nPrice; // rent or selling price
    unsigned m_nCap, m_nArea;
	unsigned short m_nRooms, m_nBathrooms;

    bool m_bImage;
    unsigned char m_pImage[ASSET_IMAGEMAXSIZE];
};

struct TAssetsArchive
{
public:
	TAssetsArchive();
	~TAssetsArchive();

	void Clear();

    void Add(TAsset* pAsset);
    void Delete(unsigned nIndex);
    void Update(unsigned nIndex, TAsset const& Asset);

    bool LoadFromFile(std::string strFileName);
    bool SaveToFile(std::string strFileName);

	unsigned GetCount();

    TAsset* const GetRecord(unsigned nId);
    bool GetRecordId(TAsset* pAsset, unsigned& nId);

    TVecPtrAssets GetAssets();

protected:
	struct TFileHeader
    {
    	char pMagic[ASSET_MAGICLEN];
        int nRecords;
    };

protected:
    TVecPtrAssets m_PtrAssets;
};


std::string AsString(enAssetEpgl nEpgl);
std::string AsString(enAssetStatus nStatus);

void FilterByStatus(TVecPtrAssets& Assets, enAssetStatus nStatus);
void FilterByTypology(TVecPtrAssets& Assets, enAssetTypology nTypology);
void FilterByCity(TVecPtrAssets& Assets, std::string strCityName, bool bFullMatch=true);
void FilterByAddress(TVecPtrAssets& Assets, std::string strAddress, bool bFullMatch=false);
void FilterByEpgl(TVecPtrAssets& Assets, enAssetEpgl nEpgl, std::string strIneq);
void FilterByBuildDate(TVecPtrAssets& Assets, double Date, std::string strIneq);
void FilterByPrice(TVecPtrAssets& Assets, unsigned nPrice, std::string strIneq);
void FilterByRooms(TVecPtrAssets& Assets, unsigned nRooms, std::string strIneq);
void FilterByBathrooms(TVecPtrAssets& Assets, unsigned nRooms, std::string strIneq);
void FilterByArea(TVecPtrAssets& Assets, unsigned nArea, std::string strIneq);
void FilterByValue(TVecPtrAssets& Assets, unsigned nValue, std::string strIneq);

void SortByCity(TVecPtrAssets& Assets, bool bAsc = true);
void SortByPrice(TVecPtrAssets& Assets, bool bAsc = true);
void SortByArea(TVecPtrAssets& Assets, bool bAsc = true);
void SortByValue(TVecPtrAssets& Assets, bool bAsc = true);

//---------------------------------------------------------------------------
#endif



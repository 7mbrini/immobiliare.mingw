/*!****************************************************************************

	@file	main.h
	@file	main.cpp

	@brief	Defines the main "Immobiliare" application module

	@noop	author:	Francesco Settembrini
	@noop	last update: 08/11/2021, 28/11/2021
	@noop	e-mail:	mailto:francesco.settembrini@poliba.it

******************************************************************************/

#include <windows.h>
#include <assert.h>
#include <vector>
#include <string>
#include <algorithm>

#include "../sources/main.h"
#include "../sources/commdefs.h"
#include "../sources/errormsgs.h"
#include "../sources/databanker.h"
#include "../sources/assets.h"
#include "../sources/customers.h"
#include "../sources/utils.h"
#include "../sources/maths.h"
#include "../sources/sorting.h"
#include "../sources/statistics.h"
#include "../sources/dialogs.h"
#include "../sources/libguidll.h"

#include "resource.h"


#define LPCSTR_ASSETS_FILTER		"Immobiliare Assets (*.ast)\0*.ast\0All Files (*.*)\0*.*\0"
#define LPCSTR_CUSTOMERS_FILTER		"Immobiliare Customers (*.cst)\0*.cst\0All Files (*.*)\0*.*\0"


/*!****************************************************************************
* @brief	Constructor
* @param	hInst Main application handle
* @param	hWnd Main window handle
******************************************************************************/
TMainModule::TMainModule(HINSTANCE hInst, HWND hWnd)
{
	m_hInst = hInst;
	assert(m_hInst);

	m_hWnd = hWnd;
	assert(m_hWnd);

	m_hLibGui = 0;

	m_pDB = m_pFormDebug = m_pFormQueries = nullptr;
	m_pFormAssets = m_pFormCustomers = nullptr;
	m_pFormFindAssets = m_pFormFindCustomers = nullptr;

	Setup();
}

/*!****************************************************************************
* @brief	Destructor
******************************************************************************/
TMainModule::~TMainModule()
{
	Cleanup();
}

/*!****************************************************************************
* @brief	Setup
******************************************************************************/
void TMainModule::Setup()
{
	assert(m_hWnd);
	assert(m_hInst);

											// some settings on startup
    LONG lStyle = GetWindowLong(m_hWnd, GWL_STYLE);
    lStyle &= ~ ( WS_MINIMIZEBOX | WS_MAXIMIZEBOX );
    SetWindowLong(m_hWnd, GWL_STYLE, lStyle);

											// main window title
	::SetWindowTextW(m_hWnd, L"SweetHome Immobiliare");

											// center on screen the main window
	int nLeft = (::GetSystemMetrics(SM_CXSCREEN) - APPWIDTH) / 2;
	int nTop = (::GetSystemMetrics(SM_CYSCREEN) - APPHEIGHT) / 2;
	::MoveWindow(m_hWnd, nLeft, nTop, APPWIDTH, APPHEIGHT, true);


											// load backgroud image
	LoadImage();
											// load "libgui.dll" module
	m_hLibGui = LoadLibraryA("libgui.dll");
	assert(m_hLibGui);
											// initialize "libgui" pointers
	libgui_Init(m_hLibGui);

											// create the debug form
	m_pFormDebug = fpCreateFormDebug();
	assert(m_pFormDebug);
	fpFormMove(m_pFormDebug, 200, 100, APPWIDTH*3/4, APPHEIGHT);

											// create the database
	m_pDB = fpDBCreate();
	assert(m_pDB);
											// load "cities" archive
    std::string strFileName = utils::GetDataPath() + CITIES;
	DBCitiesLoadFromFile(strFileName.c_str());

											// create the DB forms
	m_pFormAssets = fpCreateFormAssets(m_pDB, m_hWnd);
	assert(m_pFormAssets);

	m_pFormCustomers = fpCreateFormCustomers(m_pDB, m_hWnd);
	assert(m_pFormCustomers);

	m_pFormFindAssets = fpCreateFormFindAssets(m_pDB, m_hWnd);
	assert(m_pFormFindAssets);

	m_pFormFindCustomers = fpCreateFormFindCustomers(m_pDB, m_hWnd);
	assert(m_pFormFindCustomers);

	m_pFormQueries = fpCreateFormQueries(m_pDB, m_hWnd);
	assert(m_pFormQueries);

}

/*!****************************************************************************
* @brief	Cleanup
******************************************************************************/
void TMainModule::Cleanup()
{
	assert(m_hLibGui);
	assert(m_pDB);
	assert(m_pFormDebug);
	assert(m_pFormAssets);
	assert(m_pFormCustomers);
	assert(m_pFormFindAssets);
	assert(m_pFormFindCustomers);
	assert(m_pFormQueries);

	fpDestroyFormDebug(m_pFormDebug);
	fpDestroyFormAssets(m_pFormAssets);
	fpDestroyFormCustomers(m_pFormCustomers);
	fpDestroyFormFindAssets(m_pFormFindAssets);
	fpDestroyFormFindCustomers(m_pFormFindCustomers);
	fpDestroyFormQueries(m_pFormQueries);

	FreeLibrary(m_hLibGui);
}

/*!****************************************************************************
* @brief	Loads a bitmap from application resource
******************************************************************************/
void TMainModule::LoadImage()
{
	m_hBmpBack = (HBITMAP) ::LoadImage(m_hInst,
			MAKEINTRESOURCE(IDB_BITMAP_SPLASH), IMAGE_BITMAP, 0, 0, 0);
}

/*!****************************************************************************
* @brief	Draws an image on client area
******************************************************************************/
void TMainModule::DrawImage()
{
	assert(m_hWnd);
	assert(m_hBmpBack);

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hWnd, &ps);

	HDC hMemDC = ::CreateCompatibleDC(hdc);

	if( hMemDC )
	{
		RECT Rect;
		::GetClientRect(m_hWnd, &Rect);

		::SelectObject(hMemDC, m_hBmpBack);

		::StretchBlt(hdc,
			0, 0, Rect.right, Rect.bottom,
			hMemDC, 0, 0, 640, 480, SRCCOPY);

		::DeleteDC(hMemDC);
	}

	EndPaint(m_hWnd, &ps);
}

/*!****************************************************************************
* @brief	Loads from file a Cities archive
* @param	pFileName Pointer to a filename string
******************************************************************************/
void TMainModule::DBCitiesLoadFromFile(LPCSTR pFileName)
{
	assert(m_pDB);

	fpDBCitiesLoadFromFile(m_pDB, pFileName);
}

/*!****************************************************************************
* @brief	Shows the Debug form
******************************************************************************/
void TMainModule::ShowFormDebug()
{
	assert(m_pFormDebug);

	fpFormShow(m_pFormDebug);
}

/*!****************************************************************************
* @brief	Prints a string on the Debug form
******************************************************************************/
void TMainModule::DebugPrint(std::string strMsg)
{
	assert(m_pFormDebug);

	fpDebugPrint(m_pFormDebug, strMsg.c_str());
}

/*!****************************************************************************
* @brief	Creates an empty Assets archive
******************************************************************************/
void TMainModule::CreateAssetsArchive()
{
	if( m_pDB )
	{
		fpDBAssetsCreateArchive(m_pDB);

		::MessageBoxW(0, L"Assets archive successfully created.", L"Info:",
			MB_OK | MB_ICONINFORMATION | MB_TOPMOST | MB_TASKMODAL);
	}
}

/*!****************************************************************************
* @brief	Creates and empty Customers archive
******************************************************************************/
void TMainModule::CreateCustomersArchive()
{
	if( m_pDB )
	{
		fpDBCustomersCreateArchive(m_pDB);

		::MessageBoxW(0, L"Customers archive successfully created.", L"Info:",
			MB_OK | MB_ICONINFORMATION | MB_TOPMOST | MB_TASKMODAL);
	}
}

/*!****************************************************************************
* @brief	Shows the Assets form
******************************************************************************/
void TMainModule::ShowFormAssets()
{
	if( m_pFormAssets && fpDBHaveAssets(m_pDB) )
	{
		fpFormShowModal(m_pFormAssets);
	}
	else
	{
		ShowErrorMsg(ERR_DBNOASSETS);
	}
}

/*!****************************************************************************
* @brief	Shows the Customers form
******************************************************************************/
void TMainModule::ShowFormCustomers()
{
	if( m_pFormCustomers && fpDBHaveCustomers(m_pDB) )
	{
		fpFormShowModal(m_pFormCustomers);
	}
	else
	{
		ShowErrorMsg(ERR_DBNOCUSTOMERS);
	}
}

/*!****************************************************************************
* @brief	Display the About Box
******************************************************************************/
void TMainModule::ShowAboutBox()
{
	::MessageBoxW(0,
		L"SweetHome Immobiliare"
		"\n\n(C) 2021 Francesco Settembrini"
		"\n\nfrancesco.settembrini@poliba.it"
		"\nf.settembrini1@studenti.uniba.it",
		L"About:", MB_OK | MB_ICONINFORMATION | MB_TOPMOST | MB_TASKMODAL);
}


/*!****************************************************************************
* @brief	Opens an Assets archive
******************************************************************************/
void TMainModule::OpenAssetsArchive()
{
	assert(m_pDB);

	std::string strFileName = dialogs::OpenFileDialog(LPCSTR_ASSETS_FILTER, "ast", m_hWnd);

	if( strFileName.length() )
	{
		fpDBAssetsLoadFromFile(m_pDB, strFileName.c_str());
	}
}

/*!****************************************************************************
* @brief	Opens a Customers archive
******************************************************************************/
void TMainModule::OpenCustomersArchive()
{
	assert(m_pDB);

	std::string strFileName = dialogs::OpenFileDialog(LPCSTR_CUSTOMERS_FILTER, "cst", m_hWnd);

	if( strFileName.length() )
	{
		fpDBCustomersLoadFromFile(m_pDB, strFileName.c_str());
	}
}

/*!****************************************************************************
* @brief	Saves an Assets archive
******************************************************************************/
void TMainModule::SaveAssetsArchive()
{
	assert(m_pDB);

	std::string strFileName = dialogs::SaveFileDialog(LPCSTR_ASSETS_FILTER, "ast", m_hWnd);

	if( strFileName.length() )
	{
		fpDBAssetsSaveToFile(m_pDB, strFileName.c_str());
	}
}

/*!****************************************************************************
* @brief	Saves a Customers archive
******************************************************************************/
void TMainModule::SaveCustomersArchive()
{
	assert(m_pDB);

	std::string strFileName = dialogs::SaveFileDialog(LPCSTR_CUSTOMERS_FILTER, "cst", m_hWnd);

	if( strFileName.length() )
	{
		fpDBCustomersSaveToFile(m_pDB, strFileName.c_str());
	}
}

/*!****************************************************************************
* @brief	Shows the "FindAssets" form
******************************************************************************/
void TMainModule::ShowFormFindAssets()
{
	assert(m_pDB);
	assert(m_pFormFindAssets);

	if( m_pFormFindAssets && fpDBHaveAssets(m_pDB) )
	{
		fpFormShowModal(m_pFormFindAssets);
	}
	else
	{
		ShowErrorMsg(ERR_DBNOASSETS);
	}
}

/*!****************************************************************************
* @brief	Shows the "FindCustomers" form
******************************************************************************/
void TMainModule::ShowFormFindCustomers()
{
	assert(m_pDB);
	assert(m_pFormFindCustomers);

	if( m_pFormFindCustomers && fpDBHaveCustomers(m_pDB))
	{
		fpFormShowModal(m_pFormFindCustomers);
	}
	else
	{
		ShowErrorMsg(ERR_DBNOCUSTOMERS);
	}
}

/*!****************************************************************************
* @brief	Shows the "Queries" form
******************************************************************************/
void TMainModule::ShowFormQueries()
{
	if( m_pFormQueries )
	{
		fpFormShow(m_pFormQueries);
	}
}

/*!****************************************************************************
* @brief	Invoked when Assets archive has been modified
******************************************************************************/
void TMainModule::MsgAssetsDBModify()
{
	m_bAssetsDBModify = true;
}

/*!****************************************************************************
* @brief	Invoked when Customers archive has benn modified
******************************************************************************/
void TMainModule::MsgCustomersDBModify()
{
	m_bCustomersDBModify = true;
}

/*!****************************************************************************
* @brief	Checks if any archive has been modified
* @return	Returns true if Assets or Customers archive has been modified
******************************************************************************/
bool TMainModule::IsDirty()
{
	return bool( m_bAssetsDBModify || m_bCustomersDBModify );
}

/*!****************************************************************************
* @brief	Invoked on applicaton closing
******************************************************************************/
bool TMainModule::CanClose()
{
	bool bResult = true;

	if( IsDirty() )
	{
		bResult = false;

		::MessageBeep(-1);

		if( ::MessageBoxW(0,
			L"Assets or Customers archives have been modified:"
				" Confirm exit without saving?",
			L"Exit :",
			MB_OKCANCEL | MB_TOPMOST | MB_TASKMODAL) == IDOK )
		{
			bResult = true;
		}
	}

	return bResult;
}

/*!****************************************************************************
* @brief	Test Unit procedure
******************************************************************************/
void TMainModule::debug_SortStrings()
{
	sort::TVecStrings VecStrings;

	VecStrings.push_back("Maria");
	VecStrings.push_back("Angela");
	VecStrings.push_back("Alessia");
	VecStrings.push_back("Roberta");
	VecStrings.push_back("Giorgia");
	VecStrings.push_back("Marianna");
	VecStrings.push_back("Francesca");
	VecStrings.push_back("Alessandra");
	VecStrings.push_back("Giovanna");
	VecStrings.push_back("Eleonora");


	utils::Shuffle(VecStrings, 10);

	sort::TVecStrings StlSorts = VecStrings;
	sort::TVecStrings CustomSorts = VecStrings;

											// show string vector
	LPVOID pFormDebug = fpCreateFormDebug();
	assert(pFormDebug);

	char Buffer[256];
	sprintf(Buffer, "\n Sorts a vector of %d strings:", VecStrings.size());
	fpDebugPrint(pFormDebug, Buffer);

	fpDebugPrint(pFormDebug, "\n Unsorted values:");

	for(int i=0; i<VecStrings.size(); i++)
	{
		sprintf(Buffer, "   [%d] %s", i, VecStrings[i].c_str());
		fpDebugPrint(pFormDebug, Buffer);
	}

											// sorts values with CUSTOM
	sort::Sort(CustomSorts);

											// show sorted values
	fpDebugPrint(pFormDebug, "\n Sorted values with CUSTOM algorithm:");

	for(int i=0; i<CustomSorts.size(); i++)
	{
		sprintf(Buffer, "   [%d] %s", i, CustomSorts[i].c_str());
		fpDebugPrint(pFormDebug, Buffer);
	}

											// sorts values with STL
	std::sort(StlSorts.begin(), StlSorts.end());

											// show sorted values
	fpDebugPrint(pFormDebug, "\n Sorted values with STL algorithm:");

	for(int i=0; i<StlSorts.size(); i++)
	{
		sprintf(Buffer, "   [%d] %s", i, StlSorts[i].c_str());
		fpDebugPrint(pFormDebug, Buffer);
	}

											// show debug form
	fpFormMove(pFormDebug, 200, 100, 380, 570);
	fpFormShow(pFormDebug);
}

/*!****************************************************************************
* @brief	Test Unit procedure
******************************************************************************/
void TMainModule::debug_SortIntegers()
{
	int nItems = 10;
	sort::TVecIntegers VecInts;

	for(int i=0; i<nItems; i++)
	{
		VecInts.push_back( maths::Rand(1000, 5000) );
	}

	sort::TVecIntegers StlSorts = VecInts;
	sort::TVecIntegers CustomSorts = VecInts;

											// show int vector
	char Buffer[256];
	sprintf(Buffer, "\n Sorts a vector of %d integers:", nItems);

	LPVOID pFormDebug = fpCreateFormDebug();
	assert(pFormDebug);
	fpDebugPrint(pFormDebug, Buffer);

	fpDebugPrint(pFormDebug, "\n Unsorted values:");

	for(int i=0; i<VecInts.size(); i++)
	{
		sprintf(Buffer, "   [%d] %d", i, VecInts[i]);
		fpDebugPrint(pFormDebug, Buffer);
	}

											// sorts values with CUSTOM
	sort::Sort(CustomSorts);

											// show sorted values
	fpDebugPrint(pFormDebug, "\n Sorted values with CUSTOM algorithm:");

	for(int i=0; i<CustomSorts.size(); i++)
	{
		sprintf(Buffer, "   [%d] %d", i, CustomSorts[i]);
		fpDebugPrint(pFormDebug, Buffer);
	}

											// sorts values with STL
	std::sort(StlSorts.begin(), StlSorts.end());

											// show sorted values
	fpDebugPrint(pFormDebug, "\n Sorted values with STL algorithm:");

	for(int i=0; i<StlSorts.size(); i++)
	{
		sprintf(Buffer, "   [%d] %d", i, StlSorts[i]);
		fpDebugPrint(pFormDebug, Buffer);
	}

											// show debug form
	fpFormMove(pFormDebug, 200, 100, 380, 570);
	fpFormShow(pFormDebug);
}

/*!****************************************************************************
* @brief	Test Unit procedure
******************************************************************************/
void TMainModule::debug_PrintCities()
{
	LPVOID pFormDebug = fpCreateFormDebug();
	assert(pFormDebug);

	TDataBanker *pDB = new TDataBanker();
	assert(pDB);


	std::string strFileName = dialogs::OpenFileDialog(
			"Immobiliare Cities (*.csv)\0*.csv\0All Files (*.*)\0*.*\0" );

	if( strFileName.length() )
	{
		pDB->CitiesLoadFromFile(strFileName);

		TVecCities Cities;
		pDB->GetCities()->GetCities(Cities);

		int nCount = std::min( int(5), int(Cities.size()));

		for(unsigned i=0; i<nCount; i++)
		{
			std::string strTemp = Cities[i].AsString();

			fpDebugPrint(pFormDebug, strTemp.c_str());
		}
	}

	delete pDB;

	fpFormMove(pFormDebug, 200, 100, 380, 570);
	fpFormShow(pFormDebug);
}

/*!****************************************************************************
* @brief	Test Unit procedure
******************************************************************************/
void TMainModule::debug_PrintAssets()
{
	LPVOID pFormDebug = fpCreateFormDebug();
	assert(pFormDebug);

	TDataBanker *pDB = new TDataBanker();
	assert(pDB);

	std::string strFileName = dialogs::OpenFileDialog(
			"Immobiliare Assets (*.ast)\0*.ast\0All Files (*.*)\0*.*\0" );

	if( strFileName.length() )
	{
		pDB->AssetsLoadFromFile(strFileName);

		TVecPtrAssets Assets = pDB->GetAssets()->GetAssets();

		int nCount = std::min( int(5), int(Assets.size()));

		for(unsigned i=0; i<nCount; i++)
		{
			std::string strTemp = Assets[i]->AsString();

			fpDebugPrint(pFormDebug, strTemp.c_str());
		}
	}

	delete pDB;

	fpFormMove(pFormDebug, 200, 100, 380, 570);
	fpFormShow(pFormDebug);
}

/*!****************************************************************************
* @brief	Test Unit procedure
******************************************************************************/
void TMainModule::debug_PrintCustomers()
{
	LPVOID pFormDebug = fpCreateFormDebug();
	assert(pFormDebug);

	TDataBanker *pDB = new TDataBanker();
	assert(pDB);

	std::string strFileName = dialogs::OpenFileDialog(
			"Immobiliare Customers (*.cst)\0*.cst\0All Files (*.*)\0*.*\0" );

	if( strFileName.length() )
	{
		pDB->CustomersLoadFromFile(strFileName);

		TVecPtrCustomers Customers = pDB->GetCustomers()->GetCustomers();

		int nCount = std::min( int(5), int(Customers.size()));

		for(unsigned i=0; i<nCount; i++)
		{
			std::string strTemp = Customers[i]->AsString();

			fpDebugPrint(pFormDebug, strTemp.c_str());
		}
	}

	delete pDB;

	fpFormMove(pFormDebug, 200, 100, 380, 570);
	fpFormShow(pFormDebug);
}

/*!****************************************************************************
* @brief	Test Unit procedure
******************************************************************************/
void TMainModule::debug_MoreTestings()
{
	ShowFormDebug();

	{
		char Buffer[256];
		SYSTEMTIME lt, st;

		GetLocalTime(&lt);
		GetSystemTime(&st);

		sprintf(Buffer, "\n  The local time is: %02d:%02d", lt.wHour, lt.wMinute);
		DebugPrint(Buffer);

		sprintf(Buffer, "  The system time is: %02d:%02d", st.wHour, st.wMinute);
		DebugPrint(Buffer);
	}

	//------------------------------------  place your code here !



}





















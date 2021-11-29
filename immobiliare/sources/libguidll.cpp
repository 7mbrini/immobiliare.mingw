/*!****************************************************************************

	@file	libguidll.h
	@file	libguidll.cpp

	@brief	LibGui dll hooks functions

	@noop	author:	Francesco Settembrini
	@noop	last update: 08/11/2021, 28/11/2021
	@noop	e-mail:	mailto:francesco.settembrini@poliba.it

******************************************************************************/

#include <windows.h>
#include <assert.h>

#include "../sources/libguidll.h"

											// function pointers
libgui_ShowHello fpShowHello = nullptr;
libgui_ShowMessage fpShowMessage = nullptr;

libgui_Show fpFormShow = nullptr;
libgui_Hide fpFormHide = nullptr;
libgui_Move fpFormMove = nullptr;
libgui_ShowModal fpFormShowModal = nullptr;

libgui_CreateFormDebug fpCreateFormDebug = nullptr;
libgui_DebugPrint fpDebugPrint = nullptr;

libgui_CreateFormAssets fpCreateFormAssets = nullptr;
libgui_CreateFormCustomers fpCreateFormCustomers = nullptr;

libgui_CreateFormFindAssets fpCreateFormFindAssets = nullptr;
libgui_CreateFormFindCustomers fpCreateFormFindCustomers = nullptr;

libgui_CreateFormQueries fpCreateFormQueries = nullptr;

libgui_DestroyFormDebug fpDestroyFormDebug = nullptr;
libgui_DestroyFormAssets fpDestroyFormAssets = nullptr;
libgui_DestroyFormCustomers fpDestroyFormCustomers = nullptr;
libgui_DestroyFormFindAssets fpDestroyFormFindAssets = nullptr;
libgui_DestroyFormFindCustomers fpDestroyFormFindCustomers = nullptr;
libgui_DestroyFormQueries fpDestroyFormQueries = nullptr;


libgui_DBCreate fpDBCreate = nullptr;
libgui_DBAssetsCreateArchive fpDBAssetsCreateArchive = nullptr;
libgui_DBCustomersCreateArchive fpDBCustomersCreateArchive = nullptr;
libgui_DBCitiesLoadFromFile fpDBCitiesLoadFromFile = nullptr;
libgui_DBAssetsLoadFromFile fpDBAssetsLoadFromFile = nullptr;
libgui_DBCustomersLoadFromFile fpDBCustomersLoadFromFile = nullptr;
libgui_DBAssetsSaveToFile fpDBAssetsSaveToFile = nullptr;
libgui_DBCustomersSaveToFile fpDBCustomersSaveToFile = nullptr;

libgui_DBHaveAssets fpDBHaveAssets = nullptr;
libgui_DBHaveCustomers fpDBHaveCustomers = nullptr;


/*!****************************************************************************
* @brief	Initialize the hooks functions for "LibGui" DLL Library
* @param	hInst The instance of the library
******************************************************************************/
void libgui_Init(HINSTANCE hInst)
{
	assert(hInst);

	fpShowMessage = (libgui_ShowMessage) GetProcAddress(hInst, "libgui_ShowMessage");
	assert(fpShowMessage);

	fpShowHello = (libgui_ShowHello) GetProcAddress(hInst, "libgui_ShowHello");
	assert(fpShowHello);

	fpCreateFormDebug = (libgui_CreateFormDebug) GetProcAddress(hInst, "libgui_CreateFormDebug");
	assert(fpCreateFormDebug);

	fpDebugPrint = (libgui_DebugPrint) GetProcAddress(hInst, "libgui_DebugPrint");
	assert(fpDebugPrint);

	fpFormShow = (libgui_Show) GetProcAddress(hInst, "libgui_Show");
	fpFormHide = (libgui_Hide) GetProcAddress(hInst, "libgui_Hide");
	fpFormMove = (libgui_Move) GetProcAddress(hInst, "libgui_Move");
	fpFormShowModal = (libgui_ShowModal) GetProcAddress(hInst, "libgui_ShowModal");

	fpDBCreate = (libgui_DBCreate) GetProcAddress(hInst, "libgui_DBCreate");
	assert(fpDBCreate);

	fpDBAssetsCreateArchive = (libgui_DBAssetsCreateArchive) GetProcAddress(hInst, "libgui_DBAssetsCreateArchive");
	assert(fpDBAssetsCreateArchive);

	fpDBCustomersCreateArchive = (libgui_DBCustomersCreateArchive) GetProcAddress(hInst, "libgui_DBCustomersCreateArchive");
	assert(fpDBCustomersCreateArchive);

	fpDBCitiesLoadFromFile = (libgui_DBCitiesLoadFromFile) GetProcAddress(hInst, "libgui_DBCitiesLoadFromFile");
	assert(fpDBCitiesLoadFromFile);

	fpDBAssetsLoadFromFile = (libgui_DBAssetsLoadFromFile) GetProcAddress(hInst, "libgui_DBAssetsLoadFromFile");
	assert(fpDBAssetsLoadFromFile);

	fpDBCustomersLoadFromFile = (libgui_DBCustomersLoadFromFile) GetProcAddress(hInst, "libgui_DBCustomersLoadFromFile");
	assert(fpDBCustomersLoadFromFile);

	fpDBAssetsSaveToFile = (libgui_DBAssetsSaveToFile) GetProcAddress(hInst, "libgui_DBAssetsSaveToFile");
	assert(fpDBAssetsSaveToFile);

	fpDBCustomersSaveToFile = (libgui_DBCustomersSaveToFile) GetProcAddress(hInst, "libgui_DBCustomersSaveToFile");
	assert(fpDBCustomersSaveToFile);

	fpDBHaveAssets = (libgui_DBHaveAssets) GetProcAddress(hInst, "libgui_DBHaveAssets");
	assert(fpDBHaveAssets);

	fpDBHaveCustomers = (libgui_DBHaveCustomers) GetProcAddress(hInst, "libgui_DBHaveCustomers");
	assert(fpDBHaveCustomers);

	fpCreateFormAssets = (libgui_CreateFormAssets) GetProcAddress(hInst, "libgui_CreateFormAssets");
	assert(fpCreateFormAssets);

	fpCreateFormCustomers = (libgui_CreateFormAssets) GetProcAddress(hInst, "libgui_CreateFormCustomers");
	assert(fpCreateFormCustomers);

	fpCreateFormFindAssets = (libgui_CreateFormFindAssets) GetProcAddress(hInst, "libgui_CreateFormFindAssets");
	assert(fpCreateFormFindAssets);

	fpCreateFormFindCustomers = (libgui_CreateFormFindCustomers) GetProcAddress(hInst, "libgui_CreateFormFindCustomers");
	assert(fpCreateFormFindCustomers);

	fpCreateFormQueries = (libgui_CreateFormQueries) GetProcAddress(hInst, "libgui_CreateFormQueries");
	assert(fpCreateFormQueries);


	fpDestroyFormDebug = (libgui_DestroyFormDebug) GetProcAddress(hInst, "libgui_DestroyFormDebug");
	assert(fpDestroyFormDebug);

	fpDestroyFormAssets = (libgui_DestroyFormAssets) GetProcAddress(hInst, "libgui_DestroyFormAssets");
	assert(fpDestroyFormAssets);

	fpDestroyFormCustomers = (libgui_DestroyFormCustomers) GetProcAddress(hInst, "libgui_DestroyFormCustomers");
	assert(fpDestroyFormCustomers);

	fpDestroyFormFindAssets = (libgui_DestroyFormFindAssets) GetProcAddress(hInst, "libgui_DestroyFormFindAssets");
	assert(fpDestroyFormFindAssets);

	fpDestroyFormFindCustomers = (libgui_DestroyFormFindCustomers) GetProcAddress(hInst, "libgui_DestroyFormFindCustomers");
	assert(fpDestroyFormFindCustomers);

	fpDestroyFormQueries = (libgui_DestroyFormQueries) GetProcAddress(hInst, "libgui_DestroyFormQueries");
	assert(fpDestroyFormQueries);

}























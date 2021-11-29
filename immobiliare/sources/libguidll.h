/******************************************************************************
	author:	Francesco Settembrini
	last update: 8/11/2021, 28/11/2021
	e-mail:	mailto:francesco.settembrini@poliba.it
******************************************************************************/

#pragma once

#include <windows.h>


void libgui_Init(HINSTANCE hInst);

											// function pointer prototypes

typedef VOID (WINAPI __stdcall *libgui_ShowHello)();
typedef VOID (WINAPI __stdcall *libgui_ShowMessage)(LPCSTR pMessage);

typedef VOID (WINAPI __stdcall *libgui_Show)(LPVOID pForm);
typedef VOID (WINAPI __stdcall *libgui_Hide)(LPVOID pForm);
typedef VOID (WINAPI __stdcall *libgui_Move)(LPVOID pForm,
	int nLeft, int nTop, int nWidth, int nHeight);
typedef VOID (WINAPI __stdcall *libgui_ShowModal)(LPVOID pForm);

typedef LPVOID (WINAPI __stdcall *libgui_CreateFormDebug)();
typedef LPVOID (WINAPI __stdcall *libgui_DebugPrint)(LPVOID pDebugForm, LPCSTR pString);

typedef LPVOID (WINAPI __stdcall *libgui_CreateFormAssets)(LPVOID pDB, HWND hWndMsgs);
typedef LPVOID (WINAPI __stdcall *libgui_CreateFormCustomers)(LPVOID pDB, HWND hWndMsgs);

typedef LPVOID (WINAPI __stdcall *libgui_CreateFormFindAssets)(LPVOID pDB, HWND hWndMsgs);
typedef LPVOID (WINAPI __stdcall *libgui_CreateFormFindCustomers)(LPVOID pDB, HWND hWndMsgs);

typedef LPVOID (WINAPI __stdcall *libgui_CreateFormQueries)(LPVOID pDB, HWND hWndMsgs);

typedef LPVOID (WINAPI __stdcall *libgui_DestroyFormDebug)(LPVOID pForm);
typedef LPVOID (WINAPI __stdcall *libgui_DestroyFormAssets)(LPVOID pForm);
typedef LPVOID (WINAPI __stdcall *libgui_DestroyFormCustomers)(LPVOID pForm);
typedef LPVOID (WINAPI __stdcall *libgui_DestroyFormFindAssets)(LPVOID pForm);
typedef LPVOID (WINAPI __stdcall *libgui_DestroyFormFindCustomers)(LPVOID pForm);
typedef LPVOID (WINAPI __stdcall *libgui_DestroyFormQueries)(LPVOID pForm);


typedef LPVOID (WINAPI __stdcall *libgui_DBCreate)();
typedef VOID (WINAPI __stdcall *libgui_DBAssetsCreateArchive)(LPVOID pDB);
typedef VOID (WINAPI __stdcall *libgui_DBCustomersCreateArchive)(LPVOID pDB);
typedef LPVOID (WINAPI __stdcall *libgui_DBCitiesLoadFromFile)(LPVOID pDB, LPCSTR pFileName);
typedef LPVOID (WINAPI __stdcall *libgui_DBAssetsLoadFromFile)(LPVOID pDB, LPCSTR pFileName);
typedef LPVOID (WINAPI __stdcall *libgui_DBCustomersLoadFromFile)(LPVOID pDB, LPCSTR pFileName);
typedef LPVOID (WINAPI __stdcall *libgui_DBAssetsSaveToFile)(LPVOID pDB, LPCSTR pFileName);
typedef LPVOID (WINAPI __stdcall *libgui_DBCustomersSaveToFile)(LPVOID pDB, LPCSTR pFileName);

typedef BOOL (WINAPI __stdcall *libgui_DBHaveAssets)(LPVOID pDB);
typedef BOOL (WINAPI __stdcall *libgui_DBHaveCustomers)(LPVOID pDB);

											// function pointers
extern libgui_ShowHello fpShowHello;
extern libgui_ShowMessage fpShowMessage;

extern libgui_Show fpFormShow;
extern libgui_Hide fpFormHide;
extern libgui_Move fpFormMove;
extern libgui_ShowModal fpFormShowModal;

extern libgui_CreateFormDebug fpCreateFormDebug;
extern libgui_DebugPrint fpDebugPrint;

extern libgui_CreateFormAssets fpCreateFormAssets;
extern libgui_CreateFormCustomers fpCreateFormCustomers;

extern libgui_CreateFormFindAssets fpCreateFormFindAssets;
extern libgui_CreateFormFindCustomers fpCreateFormFindCustomers;

extern libgui_CreateFormQueries fpCreateFormQueries;

extern libgui_DestroyFormDebug fpDestroyFormDebug;
extern libgui_DestroyFormAssets fpDestroyFormAssets;
extern libgui_DestroyFormCustomers fpDestroyFormCustomers;
extern libgui_DestroyFormFindAssets fpDestroyFormFindAssets;
extern libgui_DestroyFormFindCustomers fpDestroyFormFindCustomers;
extern libgui_DestroyFormQueries fpDestroyFormQueries;


extern libgui_DBCreate fpDBCreate;
extern libgui_DBAssetsCreateArchive fpDBAssetsCreateArchive;
extern libgui_DBCustomersCreateArchive fpDBCustomersCreateArchive;
extern libgui_DBCitiesLoadFromFile fpDBCitiesLoadFromFile;
extern libgui_DBAssetsLoadFromFile fpDBAssetsLoadFromFile;
extern libgui_DBCustomersLoadFromFile fpDBCustomersLoadFromFile;
extern libgui_DBAssetsSaveToFile fpDBAssetsSaveToFile;
extern libgui_DBCustomersSaveToFile fpDBCustomersSaveToFile;

extern libgui_DBHaveAssets fpDBHaveAssets;
extern libgui_DBHaveCustomers fpDBHaveCustomers;


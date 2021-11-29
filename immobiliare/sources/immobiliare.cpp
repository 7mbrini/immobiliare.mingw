/*!****************************************************************************

	@file	immobiliare.cpp

	@brief	Defines the "Immobiliare" application entry point

	@noop	author:	Francesco Settembrini
	@noop	last update: 08/11/2021, 28/11/2021
	@noop	e-mail:	mailto:francesco.settembrini@poliba.it

******************************************************************************/

#include <windows.h>
#include <assert.h>

#include "main.h"
#include "commdefs.h"
#include "resource.h"


//-------------------------------------------------------------------------------

#define MAX_LOADSTRING 100
											// Global Variables:

HINSTANCE hInst;                            // current instance
WCHAR szTitle[MAX_LOADSTRING];              // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];        // the main window class name

											// Forward declarations of functions
											// included in this code module
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


//-------------------------------------------------------------------------------

TMainModule *g_pMainModule = nullptr;


/*!****************************************************************************
* @brief	Windows entry-point for application
* @param	hInstance Handle to the application instance
* @param	hPrevInstance Handle to the previous application instance
* @param	lpCmdLine Pointer to the command line string
* @param	nCmdShow Modality to show for the main window
* @return	Returns success or failure status codes
******************************************************************************/
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR     lpCmdLine,
   _In_ int       nCmdShow
)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    										// Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_IMMOBILIARE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    										// Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IMMOBILIARE));

    MSG msg;

    										// Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

/*!****************************************************************************
* @brief	Registers the window class.
* @param	hInstance	Handle to the application instance
* @return	Returns success or failure status codes
******************************************************************************/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_HOUSE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_IMMOBILIARE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON_HOUSE));

    return RegisterClassExW(&wcex);
}

/*!****************************************************************************
* @brief	Saves instance handle and creates main window
* @param	hInstance Handle to the application instance
* @param	nCmdShow Specifies the appearance for main window
* @return	Returns true for success, false otherwise
* @note		In this function, we save the instance handle in a global
* 			variable and create and display the main program window.
******************************************************************************/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

/*!****************************************************************************
* @brief	Processes messages for the main window.
* @param	hWnd Handle to main window
* @param	message Message Identifier
* @param	wParam Message Word Int specifier
* @param	lParam Message Long Int specifier
* @return	Returns success or failure status codes
******************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		case WM_CREATE:
			{
											// create the main module
				g_pMainModule = new TMainModule(hInst, hWnd);
				assert(g_pMainModule);
			}
		break;

		case WM_GETMINMAXINFO:
			{
				LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;

				lpMMI->ptMinTrackSize.x = APPWIDTH;
				lpMMI->ptMinTrackSize.y = APPHEIGHT;
				lpMMI->ptMaxTrackSize.x = APPWIDTH;
				lpMMI->ptMaxTrackSize.y = APPHEIGHT;
			}
		break;

		case WM_COMMAND:
			{
				int wmId = LOWORD(wParam);

											// Parse the menu selections:
				switch (wmId)
				{
					case IDM_FILE_EXIT:
						if( g_pMainModule->CanClose() )
						{
							PostQuitMessage(0);
						}
					break;

					case IDM_FILE_NEW_ASSETS:
						 g_pMainModule->CreateAssetsArchive();
					break;

					case IDM_FILE_NEW_CUSTOMERS:
						g_pMainModule->CreateCustomersArchive();
					break;

					case IDM_FILE_OPEN_ASSETS:
						g_pMainModule->OpenAssetsArchive();
					break;

					case IDM_FILE_OPEN_CUSTOMERS:
						g_pMainModule->OpenCustomersArchive();
					break;

					case IDM_FILE_SAVE_ASSETS:
						g_pMainModule->SaveAssetsArchive();
					break;

					case IDM_FILE_SAVE_CUSTOMERS:
						g_pMainModule->SaveCustomersArchive();
					break;

					case IDM_FORMS_ASSETS:
						g_pMainModule->ShowFormAssets();
					break;

					case IDM_FORMS_CUSTOMERS:
						g_pMainModule->ShowFormCustomers();
					break;

					case IDM_QUERIES_FINDASSETS:
						g_pMainModule->ShowFormFindAssets();
					break;

					case IDM_QUERIES_FINDCUSTOMERS:
						g_pMainModule->ShowFormFindCustomers();
					break;

					case IDM_QUERIES_MOREQUERIES:
						g_pMainModule->ShowFormQueries();
					break;

					case IDM_HELP_ABOUT:
						g_pMainModule->ShowAboutBox();
					break;

					case IDM_DEBUG_SHOW:
						g_pMainModule->ShowFormDebug();
					break;

					case IDM_DEBUG_SORT_STRINGS:
						g_pMainModule->debug_SortStrings();
					break;

					case IDM_DEBUG_SORT_INTEGERS:
						g_pMainModule->debug_SortIntegers();
					break;

					case IDM_DEBUG_PRINT_CITIES:
						g_pMainModule->debug_PrintCities();
					break;

					case IDM_DEBUG_PRINT_ASSETS:
						g_pMainModule->debug_PrintAssets();
					break;

					case IDM_DEBUG_PRINT_CUSTOMERS:
						g_pMainModule->debug_PrintCustomers();
					break;

					case IDM_DEBUG_MORE_TESTINGS:
						g_pMainModule->debug_MoreTestings();
					break;

					default:
						return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}
		break;

		case UM_ASSETSDBMODIFY:
			g_pMainModule->MsgAssetsDBModify();
		break;

		case UM_CUSTOMERSDBMODIFY:
			g_pMainModule->MsgCustomersDBModify();
		break;

		case UM_GETFORMASSETS:
			{
				LPVOID pFormAssets = g_pMainModule->GetFormAssets();
				assert(pFormAssets);

				*((LPVOID*) wParam) = pFormAssets;
			}
		break;

		case UM_GETFORMCUSTOMERS:
			{
				LPVOID pFormCustomers = g_pMainModule->GetFormCustomers();
				assert(pFormCustomers);

				*((LPVOID*) wParam) = pFormCustomers;
			}
		break;

		case WM_PAINT:
				g_pMainModule->DrawImage();
		break;

		case WM_CLOSE:
			if( g_pMainModule->CanClose() )
			{
				PostQuitMessage(0);
			}
		break;

		case WM_DESTROY:
			{
				delete g_pMainModule;
				g_pMainModule = nullptr;
			}
		break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



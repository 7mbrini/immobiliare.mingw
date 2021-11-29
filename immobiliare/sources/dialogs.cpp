/*!****************************************************************************

	@file	dialogs.h
	@file	dialogs.cpp

	@brief	Commong dialogs facilities functions

	@noop	author:	Francesco Settembrini
	@noop	last update: 08/11/2021, 28/11/2021
	@noop	e-mail:	mailto:francesco.settembrini@poliba.it

******************************************************************************/


#include <windows.h>
//#pragma hdrstop

#include <string>

#include "../sources/dialogs.h"


namespace dialogs
{

/*!****************************************************************************
* @brief	Shows a File Open dialog
* @param	strFilter The filter for files to shows for
* @param	strDefExt The default extension filter for files
* @param	hWndOwner The handle of the window for the z-order overlap
* @return	Returns the selected filename
******************************************************************************/
std::string OpenFileDialog(LPCSTR strFilter, LPCSTR strDefExt, HWND hWndOwner )
{
	std::string strFileName;

	char szFileName[MAX_PATH] = { 0 };

	OPENFILENAMEA openFileDialog;
	ZeroMemory(&openFileDialog, sizeof(openFileDialog));
	openFileDialog.lStructSize= sizeof(openFileDialog);
	openFileDialog.hwndOwner = hWndOwner;
	openFileDialog.lpstrFilter = strFilter;
	openFileDialog.lpstrFile = szFileName;
	openFileDialog.nMaxFile = MAX_PATH;
	openFileDialog.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	openFileDialog.lpstrDefExt = strDefExt;

	if( GetOpenFileNameA(&openFileDialog) )
	{
		strFileName = std::string(szFileName);
	}

	return strFileName;
}

/*!****************************************************************************
* @brief	Shows a File Save dialog
* @param	strFilter The filter for files to shows for
* @param	strDefExt The default extension filter for files
* @param	hWndOwner The handle of the window for the z-order overlap
* @return	Returns the selected filename
******************************************************************************/
std::string SaveFileDialog(LPCSTR strFilter, LPCSTR strDefExt, HWND hWndOwner )
{
	std::string strFileName;

	char szFileName[MAX_PATH] = { 0 };

	OPENFILENAMEA openFileDialog;
	ZeroMemory(&openFileDialog, sizeof(openFileDialog));
	openFileDialog.lStructSize= sizeof(openFileDialog);
	openFileDialog.hwndOwner = hWndOwner;
	openFileDialog.lpstrFilter = strFilter;
	openFileDialog.lpstrFile = szFileName;
	openFileDialog.nMaxFile = MAX_PATH;
	openFileDialog.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	openFileDialog.lpstrDefExt = strDefExt;

	if( GetSaveFileNameA(&openFileDialog) )
	{
		strFileName = std::string(szFileName);
	}

	return strFileName;
}

};

/******************************************************************************
	author:	Francesco Settembrini
	last update: 8/11/2021, 28/11/2021
	e-mail:	mailto:francesco.settembrini@poliba.it
******************************************************************************/

#pragma once

#include <windows.h>
#include <commdlg.h>
//#pragma hdrstop

#include <string>

namespace dialogs
{
	std::string OpenFileDialog(LPCSTR strFilter = "All Files (*.*)\0*.*\0", LPCSTR strDefExt = "", HWND hWndOwner = NULL );
	std::string SaveFileDialog(LPCSTR strFilter = "All Files (*.*)\0*.*\0", LPCSTR strDefExt = "", HWND hWndOwner = NULL );
};


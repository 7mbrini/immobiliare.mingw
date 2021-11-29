/******************************************************************************
	author:	Francesco Settembrini
	last update: 8/11/2021, 28/11/2021
	e-mail:	mailto:francesco.settembrini@poliba.it
******************************************************************************/

#pragma once

#include <windows.h>
#include <string>
//#pragma hdrstop


class TMainModule
{
public:
	TMainModule(HINSTANCE hInst, HWND hWnd);
	~TMainModule();

public:
	void DBCitiesLoadFromFile(LPCSTR pFileName);

	void ShowAboutBox();

	void ShowFormDebug();
	void DebugPrint(std::string strMsg);

	void ShowFormAssets();
	void ShowFormCustomers();

	void CreateAssetsArchive();
	void CreateCustomersArchive();

	void OpenAssetsArchive();
	void OpenCustomersArchive();

	void SaveAssetsArchive();
	void SaveCustomersArchive();

	void ShowFormFindAssets();
	void ShowFormFindCustomers();
	void ShowFormQueries();

	void MsgAssetsDBModify();
	void MsgCustomersDBModify();

	bool IsDirty();

	bool CanClose();

	LPVOID GetFormAssets() { return m_pFormAssets; }
	LPVOID GetFormCustomers() { return m_pFormCustomers; }

public:
	void DrawImage();

public:
	void debug_SortStrings();
	void debug_SortIntegers();

	void debug_PrintCities();
	void debug_PrintAssets();
	void debug_PrintCustomers();

	void debug_MoreTestings();

protected:
	void Setup();
	void Cleanup();
	void LoadImage();

protected:
	HWND m_hWnd;
	HBITMAP m_hBmpBack;
	HINSTANCE m_hInst, m_hLibGui;
	LPVOID m_pDB, m_pFormDebug, m_pFormAssets, m_pFormCustomers,
		m_pFormFindAssets, m_pFormFindCustomers, m_pFormQueries;

	bool m_bAssetsDBModify, m_bCustomersDBModify;
};



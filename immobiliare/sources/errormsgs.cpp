/*!****************************************************************************

	@file	errormsgs.h
	@file	errormsgs.cpp

	@brief	Error message heandler

	@noop	author:	Francesco Settembrini
	@noop	last update: 23/6/2021, 28/11/2021
	@noop	e-mail:	mailto:francesco.settembrini@poliba.it

******************************************************************************/

//#include <vcl.h>
//#pragma hdrstop
#include <assert.h>
#include <string>

#include "../sources/commdefs.h"
#include "../sources/errormsgs.h"

//---------------------------------------------------------------------------
//#pragma package(smart_init)


/*!****************************************************************************
* @brief
******************************************************************************/
void ShowErrorMsg(int nErrCode, enErrMsgType nType)
{
    //AnsiString strMsgType;
	std::string strMsgType;

    switch(nType)
    {
    	case emtError: strMsgType = "Error: "; break;
        case emtWarning: strMsgType = "Warning: "; break;
        case emtNotice: strMsgType = "Notice: "; break;
    }

	//AnsiString strMsg = strMsgType;
	std::string strMsg = strMsgType;

    switch(nErrCode)
    {
		case ERR_DBNOASSETS: strMsg += "No \"Assets\" data."; break;
		case ERR_DBNOCUSTOMERS: strMsg += "No \"Customers\" data."; break;
        case ERR_DBRECORDNOTFOUND: strMsg += "Record not found."; break;
        case ERR_DBEMPTYASSETS: strMsg += "\"Assets\" database is empty."; break;
        case ERR_DBEMPTYCUSTOMERS: strMsg += "\"Customers\" database is empty."; break;
        case ERR_DBNOCITIESFILE: strMsg += "Unable to load \"cities\" data.\n\nHit any key to exit."; break;
		case ERR_DBNODATA: strMsg += "No \"Assets\" and/or \"Customers\" data."; break;
        case ERR_DBSAVEASSETS: strMsg += "Unable to save \"Assets\" data to file."; break;
        case ERR_DBSAVECUSTOMERS: strMsg += "Unable to save \"Customers\" data to file."; break;

		case ERR_OPENASSETS: strMsg += "Unable to load \"Assets\" data."; break;
        case ERR_OPENCUSTOMERS: strMsg += "Unable to load \"Customers\" data."; break;
    }

	//AnsiString strCaption = AnsiString(APPNAME) + " " + strMsgType;
	std::string strCaption = std::string(APPNAME) + " " + strMsgType;

    ::MessageBoxA(0, strMsg.c_str(), strCaption.c_str(), MB_OK | MB_ICONERROR | MB_TASKMODAL | MB_TOPMOST );
}



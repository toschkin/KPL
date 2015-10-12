// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "ClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
{
	//cView = pView;
}

CClientSocket::~CClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

void CClientSocket::OnClose(int nErrorCode) 
{
//	AfxMessageBox("Connection Closed",MB_OK);
	
	CAsyncSocket::OnClose(nErrorCode);	
	AfxMessageBox("Связь с КПЛ потеряна.");
}

void CClientSocket::OnConnect(int nErrorCode) 
{
	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSocket::OnOutOfBandData(int nErrorCode) 
{
	ASSERT(FALSE); //Telnet should not have OOB data
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void CClientSocket::OnReceive(int nErrorCode) 
{
	//cView->ProcessMessage(this);
}

void CClientSocket::OnSend(int nErrorCode) 
{
	CAsyncSocket::OnSend(nErrorCode);
}

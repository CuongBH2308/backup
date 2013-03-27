#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include "xcad.h"

interface IFWWinApp;
interface IFWDocuments;
class FW_AddInManager;
class FW_UIManager;
class FW_CmdManager;
class FW_EventManager;
class FW_EnvironmentManager;
class MM_Manager;
class XCAD_EXPORT FW_WinApp : public CApcApplication<FW_WinApp,CWinApp>
{
public:
	FW_WinApp();
	~FW_WinApp();

	static FW_WinApp*		GetWinApp();

	// Get m_spIFWWinApp;
	CComPtr<IFWWinApp>		GetInterface();

	// Set m_spIFWWinApp to NULL
	void					ResetInterface();

	// Get m_spIFWDocuments;
	CComPtr<IFWDocuments>	GetDocsInterface();

	// Set m_spIFWDocuments to NULL
	void					ResetDocsInterface();

	// Init the instance
	virtual BOOL			InitInstance();

	// Exit the instance.
	virtual int				ExitInstance();

	// Controlling function for threads with a message pump
	// Override to customize the default message loop.
	virtual int				Run();

	// For VBA
	// When ApcHost is created, this function will be called
	virtual HRESULT			ApcHost_OnCreate();

	// When open a project, this function will be called
	virtual HRESULT			ApcHost_OpenProject(BSTR,IApcProject*,IApcProject**);

	// Set the value of m_bCloseFrame
	void					SetCloseFrame(BOOL bCloseFrame);

	// Get the value of m_bCloseFrame
	BOOL					GetCloseFrame() const;

	// Get AddIn Manager
	FW_AddInManager*		GetAddInManager();

	// Get UI Manager
	FW_UIManager*			GetUIManager();

	// Get Command Manager
	FW_CmdManager*			GetCmdManager();

	// Get Event Manager
	FW_EventManager*		GetEventManager();

	// Get Env Manager
	FW_EnvironmentManager*	GetEnvironmentManager();

protected:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	COleTemplateServer m_server;

	// IFWWinApp pointer
	CComPtr<IFWWinApp>		m_spIFWWinApp;

	// IFWDocuments pointer
	CComPtr<IFWDocuments>	m_spIFWDocuments;

	// Whether the main frame is closed
	BOOL m_bCloseFrame;

	// Add-In Manager
	FW_AddInManager*		m_pAddInManager;

	// UI Manager
	FW_UIManager*			m_pUIManager;

	// Command Manager
	FW_CmdManager*			m_pCmdManager;

	// Event Manager
	FW_EventManager*		m_pEventManager;

	// Env Manager
	FW_EnvironmentManager*	m_pEnvironmentManager;
};

extern FW_WinApp theApp;

// Dictionary.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Dictionary.h"
#include "DictionaryDlg.h"
#include "GlobalHooker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
static void init();
static void ShiftDown();

// CDictionaryApp

BEGIN_MESSAGE_MAP(CDictionaryApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDictionaryApp ����

CDictionaryApp::CDictionaryApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDictionaryApp ����

CDictionaryApp theApp;


// CDictionaryApp ��ʼ��
#include <processthreadsapi.h>
#include <stdio.h>
#include <conio.h>
BOOL CDictionaryApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CDictionaryDlg dlg;
	m_pMainWnd = &dlg;



	GlobalHooker::HookKeyboard();
	GlobalHooker::addKeyDownHandler(ShiftDown, 160);


	init();

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



static bool timing = false;
DWORD tId; 


static int m_wndState = SW_SHOW;
static DWORD m_tickCount1;
static DWORD m_tickCount2;



VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	timing = false;
}


void ShiftDoubleClick() {
	CDictionaryDlg* pWnd = (CDictionaryDlg*)theApp.GetMainWnd();
	pWnd->ShowWindow(SW_SHOWNORMAL);
	pWnd->SetFocusOnEdit();
}
void ShiftDown() {
	if (timing) {
		timing = false;
		m_tickCount2 = GetTickCount();
		if (m_tickCount2-m_tickCount1 < 500)
		{
			ShiftDoubleClick();
		}
	}
	else {
		timing = true;
		m_tickCount1 = GetTickCount();
		KillTimer(NULL, tId);
		tId = SetTimer(NULL, 111, 500, TimerProc);
	}


}






DWORD CALLBACK Thread(PVOID pvoid)
{
	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	tId = SetTimer(NULL, 111, 500, TimerProc);
	BOOL bRet;

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit 
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	KillTimer(NULL, tId);
	printf("thread end heren");
	return 0;
}
void init() {
	DWORD dwThreadId;
	HANDLE hThread = CreateThread(NULL, 0, Thread, 0, 0, &dwThreadId);
}

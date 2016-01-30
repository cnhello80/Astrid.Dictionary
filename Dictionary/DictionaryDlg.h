
// DictionaryDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "YoudaoHelper.h"

// CDictionaryDlg �Ի���
class CDictionaryDlg : public CDialogEx
{
// ����
public:
	CDictionaryDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void SetFocusOnEdit();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DICTIONARY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CEdit m_editMain;
	afx_msg void OnEnKillfocusEditMain();
	afx_msg void OnEnChangeEditMain();


private:
	YoudaoHelper m_youdao;
public:
	CEdit editOutput;
};

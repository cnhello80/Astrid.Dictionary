
// DictionaryDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "YoudaoHelper.h"

// CDictionaryDlg 对话框
class CDictionaryDlg : public CDialogEx
{
// 构造
public:
	CDictionaryDlg(CWnd* pParent = NULL);	// 标准构造函数
	void SetFocusOnEdit();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DICTIONARY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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

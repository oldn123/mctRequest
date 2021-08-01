
// UrlRequestDlg.h : 头文件
//

#pragma once

#include "CMctRequest.h"

// CUrlRequestDlg 对话框
class CUrlRequestDlg : public CDialogEx, public IReportMsg
{
// 构造
public:
	CUrlRequestDlg(CWnd* pParent = NULL);	// 标准构造函数
	bool DoRequest2(std::string& sRet);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_URLREQUEST_DIALOG };
#endif


	virtual void Clear() override;


	virtual void AppendMsg(const string&) override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	CMctRequest		m_mr;
	void	OnDecodeMsg(const CString &);

	int		GetRequestMode();
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_nRequestMode;
	afx_msg void OnTimer(UINT_PTR nIDEvent);


	std::wstring		m_msgInfo;
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonAddcart();
	afx_msg void OnBnClickedButtonCheckout();
	afx_msg void OnBnClickedButtonCheckout2();
	afx_msg void OnBnClickedButtonCheckout3();
	afx_msg void OnBnClickedButtonCheckout4();
};

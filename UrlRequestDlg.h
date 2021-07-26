
// UrlRequestDlg.h : 头文件
//

#pragma once


// CUrlRequestDlg 对话框
class CUrlRequestDlg : public CDialogEx
{
// 构造
public:
	CUrlRequestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_URLREQUEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

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
};

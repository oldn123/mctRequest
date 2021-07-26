
// UrlRequestDlg.h : ͷ�ļ�
//

#pragma once


// CUrlRequestDlg �Ի���
class CUrlRequestDlg : public CDialogEx
{
// ����
public:
	CUrlRequestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_URLREQUEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	void	OnDecodeMsg(const CString &);

	int		GetRequestMode();
	// ���ɵ���Ϣӳ�亯��
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
